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

// a utility complex data class

#include "Complex.h"

Complex::Complex() {
  re = 0;
  im = 0;
}

Complex::Complex(const Complex& v) {
  re = v.re;
  im = v.im;
}

Complex::Complex(const DATATYPE& re, const DATATYPE& im) {
  this->re = re;
  this->im = im;
}

void Complex::operator=(Complex v) {
  re = v.re;
  im = v.im;
}

void Complex::operator=(DATATYPE v) {
  re = v;
  im = v;
}

Complex Complex::operator-(Complex v) {
  return Complex(re-v.re,im-v.im);
}

Complex Complex::operator*(DATATYPE v) {
  return Complex(re*v,im*v);
}

Complex* Complex::operator+=(Complex v)
{
  re += v.re;
  im += v.im;
  return this;
}

Complex* Complex::operator-=(Complex v)
{
  re -= v.re;
  im -= v.im;
  return this;
}

void Complex::operator*=(Complex v)
{
  re *= v.re;
  im *= v.im;
}

void Complex::operator*=(DATATYPE v)
{
  re *= v;
  im *= v;
}

DATATYPE Complex::m() {
  return sqrt(re*re+im*im);
}

DATATYPE Complex::sumsq() {
  return re*re+im*im;
}

DATATYPE Complex::a() {
  DATATYPE a = atan2(re,im);
  if(a < 0) {
    a = (M_PI * 2) + a;
  }
  return a;
}

