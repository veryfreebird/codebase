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

#include "DFT.h"
#include "Complex.h"

/*
 *
 * This source file and class exists only to show
 * the simplicity of the DFT. The DFT is very slow
 * and inefficient, its value lies only in clarifying
 * the Discrete Fourier Transform.
 *
 */

void DFT::del_all() {
  delete input_data;
  delete output_data;
}

DFT::DFT(int n) {
  size = 0;
  input_data = NULL;
  output_data = NULL;
  initialize(n);
}

DFT::~DFT() {
  del_all();
}

void DFT::initialize(unsigned int n, bool del) {
  if(size != n) {
    size = n;
    pi2 = M_PI * 2.0;
    scale = 1.0/size;
    if(del) {
      del_all();
    }
    input_data  = new Complex[n];
    output_data = new Complex[n];
  }
}

void DFT::resize(int n) {
  initialize(n,true);
}

Complex* DFT::array_input() {
  return input_data;
}

Complex* DFT::array_output() {
  return output_data;
}

void DFT::dft1(bool inverse)
{
  double pi2 = (inverse)?2.0 * M_PI:-2.0 * M_PI;
  double a,ca,sa;
  double invs = 1.0 / size;
  for(unsigned int y = 0;y < size;y++) {
    output_data[y] = 0;
    for(unsigned int x = 0;x < size;x++) {
      a = pi2 * y * x * invs;
      ca = cos(a);
      sa = sin(a);
      output_data[y].re += input_data[x].re * ca - input_data[x].im * sa;
      output_data[y].im += input_data[x].re * sa + input_data[x].im * ca;
    }
    if(!inverse) {
      output_data[y] *= invs;
    }
  }
}
