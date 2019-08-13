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

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include "mulaw_converter.h"

using namespace std;


class SoundSource {
  
  string input_source;
  int format;
  unsigned long array_size,samples_per_second;
  
  static const int data_formats[];
  
  public:
  
  SoundSource() {
    input_source = "/dev/dsp";
    array_size = 2048;
    samples_per_second = 1000;
    format = 0;
  }
  
  bool decode_comline(int argc,char **argv)
  {
    for(int i = 1;i < argc;i++) {
      string arg = (string) argv[i];
      if(arg.length() == 2 && arg[0] == '-') {
        char c = arg[1];
        switch (c) {
          case 'h':
          cerr << "Usage: [-i(nput, default " << input_source << ")]" << endl;
          cerr << "       [-f(ormat: 0=unsigned 16-bit, 1=signed 16-bit, 2=muLaw, default " << format << ")]" << endl;
          cerr << "       [-a(rray_size, must be a power of 2, default " << array_size << ")]" << endl;
          cerr << "       [-s(amples_per_second, default " << samples_per_second << ")]" << endl;
          return true;
          case 'a':
            sscanf(argv[++i],"%lud",&array_size);
          break;
          case 's':
            sscanf(argv[++i],"%lud",&samples_per_second);
          break;
          case 'f':
            sscanf(argv[++i],"%d",&format);
          break;
          case 'i':
            input_source = (string) argv[++i];
          break;
        }
      }
    }
    return false;
  }
  
  template <class T> void scan_string(T& t,char* s) {
    stringstream ss(s);
    ss >> t;
  }
  
  long convert_pwr2(long v) {
    double q = floor(log(v) / log(2));
    q = pow(2.0,q);
    return (long)q;
  }
  
  void set_options(int audio) {
    
    int fmt = data_formats[format];
    ioctl ( audio, SNDCTL_DSP_SETFMT, &fmt );
    unsigned long v = samples_per_second;
    ioctl ( audio, SNDCTL_DSP_SPEED, &v );
    // did the DSP accept our sample rate?
    if ( v != samples_per_second )
    {
      // if not, accept the reply
      samples_per_second = v;
      cerr << "sound_source error: forced sample rate: " << samples_per_second << endl;
    }
    // this produces more reliable performance
    int val = ( int ) ( ( 2 << 16 ) + log2 ( 512 ) );
    ioctl ( audio, SNDCTL_DSP_SETFRAGMENT, &val );
    
  }
  
  void process_stream(int audio) {
    double volume_constant = 1.0/1024.0;
    double v;
    unsigned short s;
    unsigned char c;
    // continuous output
    while(true) {
      cout << array_size << endl;
      cout << samples_per_second << endl;
      for(unsigned long t = 0;t < array_size;t++) {
        if(format < 2) {
          if(read ( audio,&s,2) == 2 ) {
            if(format == 0) {
              v = ( ( double ) s-32768.0 ) * volume_constant;
            }
            else {
              v = ( double ) s * volume_constant;
            }
            cout << v << " " << 0 << endl;
          }
        }
        else {
          if(read ( audio,&c,1) == 1) {
            v = MulawConverter::mu2linfast ( c ) * volume_constant;
            cout << v << " " << 0 << endl;
          }
        }
      }
    }
  }
  
  void process(int argc,char **argv) {
    if(decode_comline(argc,argv)) {
      return;
    }
    // force entry to be a power of 2
    array_size = convert_pwr2(array_size);
    int audio = open (input_source.c_str(),O_RDONLY);
    set_options(audio);
    process_stream(audio);
  }
};

const int SoundSource::data_formats[] =
{
  AFMT_U16_LE, AFMT_S16_LE,AFMT_MU_LAW,0
};


int main(int argc, char **argv)
{
  SoundSource ss;
  ss.process(argc,argv);
  return 0;
}

