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

#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

// NOTE: change to DATATYPE double for more data resolution and accuracy
// but somewhat slower conversion speed

#define DATATYPE float

// a utility complex data class

class Complex {
  public:
  DATATYPE re;
  DATATYPE im;
  
  Complex();
  Complex(const Complex& v);
  Complex(const DATATYPE& re, const DATATYPE& im);
  void operator=(Complex v);
  void operator=(DATATYPE v);
  Complex operator-(Complex v);
  Complex operator*(DATATYPE v);
  Complex* operator+=(Complex v);
  Complex* operator-=(Complex v);
  void operator*=(Complex v);
  void operator*=(DATATYPE v);
  DATATYPE m();
  DATATYPE sumsq();
  DATATYPE a();
};

#endif
