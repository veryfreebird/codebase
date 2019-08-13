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

#ifndef FFT_H
#define FFT_H

#include <cstdio>
#include <cmath>

// NOTE: for greater speed, set DATATYPE float
// for greater accuracy, set DATATYPE double

#define DATATYPE float

#include "Complex.h"

class FFT {
  unsigned int size;
  DATATYPE scale;
  Complex *input_data;
  Complex **bitrev_data;
  bool valid;
  
  void del_all();
  bool test_pwr2(unsigned int n);
  int rev_bits(unsigned int index,int size);
  void initialize(unsigned int n, bool del = false);
  
  public:
  
  DATATYPE pi2;
  
  FFT(int n);
  ~FFT();
  
  void resize(int n);
  Complex* array_input();
  Complex** array_output();
  void fft1(bool inverse = false);
};

#endif
