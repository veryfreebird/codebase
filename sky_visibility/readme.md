# 🌍 Satellite Visibility Analyzer

> A Python script to visualize visible GNSS satellites (GPS, BeiDou, Galileo) at a given time and location.

---

## 📌 Overview

This script calculates the visibility of GNSS satellites using TLE orbital data and displays the results in a **polar plot**, showing elevation and azimuth. It supports multiple satellite constellations, custom geographic coordinates, and user-defined local times. The signal strength (C/N0) is visualized with color-coded markers.

---

## ✅ Features

| Feature | Description |
|--------|-------------|
| 🛰️ Constellation Support | Supports GPS, BeiDou, Galileo |
| 🌐 Custom Location | Specify any latitude and longitude |
| ⏰ Custom Time | Define local time in `"YYYY-MM-DD HH:MM"` format |
| 📊 Polar Plot Visualization | Shows satellite positions using azimuth and elevation |
| 🔵 Signal Strength Coloring | Color gradient indicates C/N0 value |
| 📈 Multi-Constellation Overlay | View multiple systems simultaneously |

---

## 🔧 Installation

Make sure you have Python 3 installed, then install required dependencies:

```bash
pip install skyfield matplotlib numpy pytz
```

Optional (for automatic timezone detection):

```bash
pip install timezonefinder
```

Place your TLE files in the `tle_data/` directory:

```
tle_data/
├── gps.tle
├── beidou.tle
└── galileo.tle
```

You can download the latest TLE files from:
- [Celestrak - GNSS Constellations](https://celestrak.org/NORAD/elements/gnss.asp)

---

## 🧪 Usage

### Basic Command:

```bash
python skyVisibility.py --c gps --latlon "39.9042,116.4074"
```

### With Custom Time:

```bash
python skyVisibility.py --c beidou --latlon "30.2741,120.1551" --time "2025-08-01 10:30"
```

### Multiple Constellations:

```bash
python skyVisibility.py --c gps,galileo --latlon "52.5200,13.4050" --time "2025-08-05 08:15"
```

---

## 📋 Arguments

| Argument | Description |
|---------|-------------|
| `--c`, `--constellation` | Choose one or more constellations: `gps`, `beidou`, `galileo` |
| `--latlon` | Latitude and longitude as a string, e.g., `"39.9042,116.4074"` |
| `--time` | Local time in `"YYYY-MM-DD HH:MM"` format |
| `--tz` *(optional)* | Manually specify timezone (e.g., `Asia/Shanghai`) |

> If no arguments are provided, the default is Beijing (GPS constellation, local noon).

---

## 🖼️ Example Output

The script will display a polar chart like this:

```
Visible Satellites on 2025-08-01 02:30 UTC
(Elevation > 5°, Signal Strength Filtered)
```

Each dot represents a visible satellite:
- **Color intensity**: Represents signal strength (C/N0)
- **Label**: Includes name, elevation angle
- **Azimuth/Elevation**: Plotted in polar coordinates

---

## ⚠️ Notes & Known Issues

- Make sure TLE files are correctly formatted and placed in the `tle_data/` folder.
- The script assumes UTC+8:00 (Beijing time) if no timezone is specified.
- Some versions of Skyfield may raise warnings about leap seconds — these are safe to ignore.
- For best results, ensure your system clock is accurate.


