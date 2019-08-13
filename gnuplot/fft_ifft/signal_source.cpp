/***************************************************************************
 *   Copyright (C) 2008 by Paul Lutus                                      *
 *   lutusp@arachnoid.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

template <class T> void scan_string(T& t,char* s) {
  stringstream ss(s);
  ss >> t;
}

class SignalSource {
  double cf,mf,noise_level;
  unsigned long array_size, samples_per_second;
  bool continuous;
  
  public:
  SignalSource() {
    array_size = 2048;
    samples_per_second = 1000;
    continuous = false;
    cf = 100;
    mf = 10;
    noise_level = 0.3;
  }
  
  long convert_pwr2(long v) {
    double q = floor(log(v) / log(2));
    q = pow(2.0,q);
    return (long)q;
  }
  
  bool decode_comline(int argc,char **argv)
  {
    for(int i = 1;i < argc;i++) {
      string arg = (string) argv[i];
      if(arg.length() == 2 && arg[0] == '-') {
        char c = arg[1];
        switch (c) {
          case 'h':
          cerr << "Usage: [-a(rray_size, must be a power of 2, default " << array_size << ")]" << endl;
          cerr << "       [-s(amples_per_second, default " << samples_per_second << ")]" << endl;
          cerr << "       [-c(ontinuous)]" << endl;
          cerr << "       [-f carrier freq, default " << cf << "] [-m modulation freq default " << mf << "]" << endl;
          cerr << "       [-n noise level, default " << noise_level << "]" << endl;
          return true;
          case 'c':
            continuous = true;
          break;
          case 'a':
            sscanf(argv[++i],"%lud",&array_size);
          break;
          case 's':
            sscanf(argv[++i],"%lud",&samples_per_second);
          break;
          case 'f':
            sscanf(argv[++i],"%lf",&cf);
          break;
          case 'm':
            sscanf(argv[++i],"%lf",&mf);
          break;
          case 'n':
            sscanf(argv[++i],"%lf",&noise_level);
          break;
        }
      }
    }
    return false;
  }
  
  void process(int argc, char **argv) {
    if(decode_comline(argc,argv)) {
      return;
    }
    // force entry to be a power of 2
    array_size = convert_pwr2(array_size);
    
    // initialize random generator
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    srand(tv.tv_usec);
    double slice = 1.0/samples_per_second;
    double noise = 0.0;
    double omega = 2.0 * M_PI * slice;
    
    double mod,sig;
    
    while(true) {
      cout << array_size << endl;
      cout << samples_per_second << endl;
      for(unsigned long t = 0;t < array_size;t++) {
        try {
          mod = sin(omega * mf * t) + 1.0;
          noise = ((rand()/(RAND_MAX+1.0)) - 0.5) * noise_level;
          sig = (sin(omega * cf * t) * mod) + noise;
          cout << sig << " " << 0 << endl;
        }
        catch(ios::failure const &problem) {
          cerr << "signal_source: " << problem.what() << endl;
        }
      }
      if(!continuous) {
        break;
      }
    }
  }
};

int main(int argc, char **argv)
{
  SignalSource ss;
  ss.process(argc,argv);
  return 0;
}

