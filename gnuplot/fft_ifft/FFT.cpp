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

#include "FFT.h"
#include "Complex.h"

void FFT::del_all() {
  delete input_data;
  delete bitrev_data;
}

bool FFT::test_pwr2(unsigned int n)
{
  if( n < 2 || (n & (n-1)) ) return false;
  return true;
}

// reverse bits in provided index

int FFT::rev_bits(unsigned int index,int size)
{
  int rev = 0;
  for(;size > 1; size>>=1)
  {
    rev = (rev << 1) | (index & 1);
    index >>= 1;
  }
  return rev;
}

FFT::FFT(int n) {
  size = 0;
  input_data = NULL;
  bitrev_data = NULL;
  initialize(n);
}

FFT::~FFT() {
  del_all();
}

void FFT::initialize(unsigned int n, bool del) {
  if(!test_pwr2(n)) {
    valid = false;
    fprintf(stderr,"Error: array size is not a power of 2\n");
  }
  else {
    valid = true;
    if(size != n) {
      size = n;
      pi2 = M_PI * 2.0;
      scale = 1.0/size;
      if(del) {
        del_all();
      }
      input_data  = new Complex[n];
      bitrev_data = new Complex*[n];
      // preload array of bit-reversed
      // pointers to input data
      int rb;
      for(unsigned int i = 0;i < n;i++) {
        rb = rev_bits(i,n);
        bitrev_data[rb] = &input_data[i];
      }
    }
  }
}

void FFT::resize(int n) {
  initialize(n,true);
}

Complex* FFT::array_input() {
  return input_data;
}

Complex** FFT::array_output() {
  return bitrev_data;
}

void FFT::fft1(bool inverse)
{
  if(valid) {
    unsigned long imax,istep,m,i,j;
    // these variables are used to maintain trig arguments by iteration,
    // so they should always be doubles to avoid erosion of accuracy
    double wtemp,wr,wpr,wpi,wi,theta;
    Complex tc;
    // Danielson-Lanzcos routine
    imax = 1;
    istep = 2;
    DATATYPE ps = (inverse)?-pi2:pi2;
    while (imax < size)
    {
      istep = imax << 1;
      theta= ps/istep;
      wtemp=sin(0.5*theta);
      wpr = -2.0*wtemp*wtemp;
      wpi = sin(theta);
      wr = 1.0;
      wi = 0.0;
      for (m=0; m<imax; ++m) {
        for (i=m; i<size; i+=istep) {
          j = i+imax;
          tc.re = wr * bitrev_data[j]->re - wi * bitrev_data[j]->im;
          tc.im = wr * bitrev_data[j]->im + wi * bitrev_data[j]->re;
          *bitrev_data[j] = *bitrev_data[i] - tc;
          *bitrev_data[i] += tc;
        }
        wr=(wtemp=wr)*wpr-wi*wpi+wr;
        wi=wi*wpr+wtemp*wpi+wi;
      }
      imax = istep;
    } 
    if(!inverse) {
      for(unsigned int i = 0;i < size;i++) {
        *bitrev_data[i] *= scale;
      }
    }
  }
}

