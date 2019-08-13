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
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "Complex.h"
#include "FFT.h"
#include "DFT.h"

using namespace std;

class fft_processor {
  bool inverse;
  bool dft_mode;
  
  FFT *fft;
  DFT *dft;
  
  public:
  
  fft_processor() {
    fft = NULL;
    dft = NULL;
    inverse = false;
    dft_mode = false;
  }
  
  ~fft_processor() {
    delete fft;
    delete dft;
  }
  
  template <class T> void scan_string(T& t,char* s) {
    stringstream ss(s);
    ss >> t;
  }
  
  bool decode_comline(int argc,char **argv)
  {
    for(int i = 1;i < argc;i++) {
      string arg = (string) argv[i];
      if(arg.length() == 2 && arg[0] == '-') {
        char c = arg[1];
        switch (c) {
          case 'h':
            cerr << "Usage: [-i (inverse FFT/DFT)]" << endl;
          cerr << "       [-d (DFT instead of FFT)]" << endl;
          return true;
          case 'i':
            inverse = true;
          break;
          case 'd':
            dft_mode = true;
          break;
        }
      }
    }
    return false;
  }
  
  void process(int argc, char **argv)
  {
    if(decode_comline(argc,argv)) {
      return;
    }
    unsigned long array_size,samples_per_second;
    try {
      while(cin >> array_size && cin >> samples_per_second) {
        if(dft_mode) {
          if(dft) {
            dft->resize(array_size);
          }
          else {
            dft = new DFT(array_size);
          }
          Complex* array_input = dft->array_input();
          Complex* array_output = dft->array_output();
          for(unsigned long i = 0;i < array_size;i++) {
            if(!(cin >> array_input[i].re >> array_input[i].im)) {
              cin.clear();
              usleep(250000);
              break;
            }
          }
          dft->dft1(inverse);
          cout << array_size << endl;
          cout << samples_per_second << endl;
          for(unsigned int i = 0;i < array_size;i++) {
            cout << array_output[i].re << " " << array_output[i].im << endl;
          }
        } // if dft mode
        else { // fft mode
          if(fft) {
            fft->resize(array_size);
          }
          else {
            fft = new FFT(array_size);
          }
          Complex* array_input = fft->array_input();
          Complex** array_output = fft->array_output();
          for(unsigned long i = 0;i < array_size;i++) {
            if(!(cin >> array_input[i].re >> array_input[i].im)) {
              cin.clear();
              usleep(250000);
              break;
            }
          }
          fft->fft1(inverse);
          cout << array_size << endl;
          cout << samples_per_second << endl;
          for(unsigned int i = 0;i < array_size;i++) {
            cout << array_output[i]->re << " " << array_output[i]->im << endl;
          }
        } // else fft
      } // while input continues
    }
    catch(ios::failure const &problem) {
      cerr << "fft_processor: " << problem.what() << endl;
    }
  }
};

int main(int argc, char **argv) {
  fft_processor fft;
  fft.process(argc,argv);
  return 0;
}
