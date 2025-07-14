import os
import argparse
import datetime
import pytz
import numpy as np
import matplotlib.pyplot as plt
from skyfield.api import Topos, load, EarthSatellite

# Constellation to TLE file mapping
constellation_map = {
    'beidou': 'tle_data/beidou.tle',
    'gps': 'tle_data/gps.tle',
    'galileo': 'tle_data/galileo.tle'
}

def parse_args():
    parser = argparse.ArgumentParser(description="Visualize visible satellites at specified time for given coordinates.")
    parser.add_argument('--c', '--constellation', type=str, default='gps',
                        help="Specify constellation(s): beidou, gps, galileo (comma-separated list)")
    parser.add_argument('--latlon', type=str, default=None,
                        help="Latitude and longitude (e.g., 39.9042,116.4074), defaults to Beijing if not specified.")
    parser.add_argument('--time', type=str, default=None,
                        help="Specify local time in format 'YYYY-MM-DD HH:MM' (e.g., '2025-08-01 10:30'), defaults to local noon.")
    return parser.parse_args()

def get_observation_time(lat_deg, lon_deg, user_time_str):
    from timezonefinder import TimezoneFinder

    tf = TimezoneFinder()
    timezone_str = tf.timezone_at(lat=lat_deg, lng=lon_deg)

    if not timezone_str:
        raise ValueError("Could not determine timezone from latitude and longitude.")

    local_tz = pytz.timezone(timezone_str)

    # Use local noon if no time is provided
    if user_time_str is None:
        today = datetime.datetime.now(tz=local_tz).date()
        user_time = datetime.datetime(today.year, today.month, today.day, 12, 0, 0, tzinfo=local_tz)
    else:
        try:
            naive_time = datetime.datetime.strptime(user_time_str, "%Y-%m-%d %H:%M")
            user_time = local_tz.localize(naive_time)
        except Exception as e:
            raise ValueError(f"Invalid time format: {user_time_str}. Use 'YYYY-MM-DD HH:MM'.") from e

    # Convert to UTC
    utc_time = user_time.astimezone(pytz.utc)

    print(f"Local time: {user_time}")
    print(f"Converted to UTC time: {utc_time}")

    # Load Skyfield timescale and convert to Time object
    ts = load.timescale()
    return ts.utc(utc_time), ts

def load_tle_from_file(filename, ts):
    satellites = []
    with open(filename, 'r', encoding='utf-8') as f:
        lines = [line.strip() for line in f if line.strip()]

    for i in range(0, len(lines), 3):
        try:
            name = lines[i]
            l1 = lines[i+1]
            l2 = lines[i+2]
            sat = EarthSatellite(l1, l2, name, ts)  # Pass the timescale
            satellites.append(sat)
        except Exception as e:
            print(f"Error parsing TLE: {e}")
    return satellites

def calculate_cn0(altitude_deg, distance_km):
    elevation_angle = max(altitude_deg, 5)
    base_cn0 = 45
    elevation_factor = 1 / np.sin(np.radians(elevation_angle))
    atmospheric_loss = 2.5 / elevation_factor
    ionospheric_loss = 4.0 / elevation_factor
    total_loss = atmospheric_loss + ionospheric_loss
    cn0 = base_cn0 - total_loss
    return cn0

def is_visible(satellite, observer_topos, time):
    difference = satellite - observer_topos
    topocentric = difference.at(time)
    alt, az, distance = topocentric.altaz()

    altitude = alt.degrees
    distance_km = distance.km
    cn0 = calculate_cn0(altitude, distance_km)

    visible = altitude > 5.0
    strong_signal = cn0 > 35

    return visible and strong_signal, altitude, az.degrees, cn0

def plot_satellites(visible_satellites, obs_time):
    if not visible_satellites:
        print("⚠️ No satellites to plot.")
        return

    fig = plt.figure(figsize=(8, 8))
    ax = fig.add_subplot(111, projection='polar')

    cn0_values = [sat['cn0'] for sat in visible_satellites]
    max_cn0 = max(cn0_values)
    min_cn0 = min(cn0_values)

    for sat in visible_satellites:
        alt = sat['altitude']
        az = sat['azimuth']
        r = 90 - alt
        cn0 = sat['cn0']

        color_norm = (cn0 - min_cn0) / (max_cn0 - min_cn0)
        color = plt.cm.viridis(color_norm)

        ax.plot(np.radians(az), r, 'o', markersize=8, color=color)
        ax.text(np.radians(az), r, f"{sat['name']} ({alt:.1f}°)", fontsize=8, ha='left', va='center')

    # Polar plot settings
    ax.set_rmax(90)
    ax.set_rticks([15, 30, 45, 60, 75])
    ax.set_rlabel_position(-22.5)
    ax.set_theta_zero_location('N')
    ax.set_theta_direction(-1)
    ax.set_title(f"Visible Satellites on {obs_time.utc_datetime().strftime('%Y-%m-%d %H:%M UTC')}\n(Elevation > 5°, Signal Strength Filtered)", va='bottom')

    # Add colorbar
    sm = plt.cm.ScalarMappable(cmap='viridis', norm=plt.Normalize(vmin=min_cn0, vmax=max_cn0))
    sm._A = []  # Dummy array to avoid warning
    cbar = plt.colorbar(sm, ax=ax, orientation='vertical', shrink=0.6, pad=0.1)
    cbar.set_label('C/N0 (dBHz)', rotation=270, labelpad=15)

    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    args = parse_args()

    # Default to Beijing if latlon not provided
    if args.latlon:
        lat, lon = map(float, args.latlon.split(','))
    else:
        lat, lon = 39.9042, 116.4074  # Beijing

    print(f"Using location: Latitude={lat}, Longitude={lon}")

    # Get observation time and timescale
    observation_time, ts = get_observation_time(lat, lon, args.time)

    # Create observer position
    observer = Topos(latitude_degrees=lat, longitude_degrees=lon, elevation_m=50)

    # Parse constellations
    constellations = args.c.split(',') if args.c else ['gps']
    valid_constellations = []

    for cons in constellations:
        cons = cons.strip().lower()
        if cons in constellation_map:
            valid_constellations.append(cons)
        else:
            print(f"❌ Invalid constellation '{cons}', ignored.")

    all_satellites = []
    for cons in valid_constellations:
        tle_path = constellation_map[cons]
        if not os.path.exists(tle_path):
            print(f"⚠️ TLE file not found: {tle_path}, skipping {cons}.")
            continue

        print(f"Loading TLE data from file: {tle_path}")
        satellites = load_tle_from_file(tle_path, ts)  # Pass ts explicitly
        print(f"Loaded {len(satellites)} satellites from {cons.upper()}")
        all_satellites.extend(satellites)

    visible_satellites = []

    print("\nChecking each satellite visibility and signal strength...")
    for sat in all_satellites:
        ok, alt, az, cn0 = is_visible(sat, observer, observation_time)
        if ok:
            visible_satellites.append({
                'name': sat.name,
                'altitude': alt,
                'azimuth': az,
                'cn0': cn0
            })

    visible_satellites.sort(key=lambda x: x['cn0'], reverse=True)

    print("\n✅ Final list of visible satellites:")
    if visible_satellites:
        for sat in visible_satellites:
            print(f"{sat['name']} - Altitude: {sat['altitude']:.2f}°, Azimuth: {sat['azimuth']:.2f}°, C/N0: {sat['cn0']:.2f}")
    else:
        print("No satellites met the criteria.")

    print(f"\n📊 Found {len(visible_satellites)} visible satellites with elevation > 5° and sufficient signal strength")

    plot_satellites(visible_satellites, observation_time)