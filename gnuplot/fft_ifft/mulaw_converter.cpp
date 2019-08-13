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
#include "mulaw_converter.h"

MulawConverter::MulawConverter() {}


MulawConverter::~MulawConverter() {}

const short MulawConverter::MuLaw[256] = {
  // negative values
  (short)0x8284, (short)0x8684, (short)0x8a84, (short)0x8e84,
  (short)0x9284, (short)0x9684, (short)0x9a84, (short)0x9e84,
  (short)0xa284, (short)0xa684, (short)0xaa84, (short)0xae84,
  (short)0xb284, (short)0xb684, (short)0xba84, (short)0xbe84,
  (short)0xc184, (short)0xc384, (short)0xc584, (short)0xc784,
  (short)0xc984, (short)0xcb84, (short)0xcd84, (short)0xcf84,
  (short)0xd184, (short)0xd384, (short)0xd584, (short)0xd784,
  (short)0xd984, (short)0xdb84, (short)0xdd84, (short)0xdf84,
  (short)0xe104, (short)0xe204, (short)0xe304, (short)0xe404,
  (short)0xe504, (short)0xe604, (short)0xe704, (short)0xe804,
  (short)0xe904, (short)0xea04, (short)0xeb04, (short)0xec04,
  (short)0xed04, (short)0xee04, (short)0xef04, (short)0xf004,
  (short)0xf0c4, (short)0xf144, (short)0xf1c4, (short)0xf244,
  (short)0xf2c4, (short)0xf344, (short)0xf3c4, (short)0xf444,
  (short)0xf4c4, (short)0xf544, (short)0xf5c4, (short)0xf644,
  (short)0xf6c4, (short)0xf744, (short)0xf7c4, (short)0xf844,
  (short)0xf8a4, (short)0xf8e4, (short)0xf924, (short)0xf964,
  (short)0xf9a4, (short)0xf9e4, (short)0xfa24, (short)0xfa64,
  (short)0xfaa4, (short)0xfae4, (short)0xfb24, (short)0xfb64,
  (short)0xfba4, (short)0xfbe4, (short)0xfc24, (short)0xfc64,
  (short)0xfc94, (short)0xfcb4, (short)0xfcd4, (short)0xfcf4,
  (short)0xfd14, (short)0xfd34, (short)0xfd54, (short)0xfd74,
  (short)0xfd94, (short)0xfdb4, (short)0xfdd4, (short)0xfdf4,
  (short)0xfe14, (short)0xfe34, (short)0xfe54, (short)0xfe74,
  (short)0xfe8c, (short)0xfe9c, (short)0xfeac, (short)0xfebc,
  (short)0xfecc, (short)0xfedc, (short)0xfeec, (short)0xfefc,
  (short)0xff0c, (short)0xff1c, (short)0xff2c, (short)0xff3c,
  (short)0xff4c, (short)0xff5c, (short)0xff6c, (short)0xff7c,
  (short)0xff88, (short)0xff90, (short)0xff98, (short)0xffa0,
  (short)0xffa8, (short)0xffb0, (short)0xffb8, (short)0xffc0,
  (short)0xffc8, (short)0xffd0, (short)0xffd8, (short)0xffe0,
  (short)0xffe8, (short)0xfff0, (short)0xfff8, (short)0x0000,
  // positive values
  (short)0x7d7c, (short)0x797c, (short)0x757c, (short)0x717c,
  (short)0x6d7c, (short)0x697c, (short)0x657c, (short)0x617c,
  (short)0x5d7c, (short)0x597c, (short)0x557c, (short)0x517c,
  (short)0x4d7c, (short)0x497c, (short)0x457c, (short)0x417c,
  (short)0x3e7c, (short)0x3c7c, (short)0x3a7c, (short)0x387c,
  (short)0x367c, (short)0x347c, (short)0x327c, (short)0x307c,
  (short)0x2e7c, (short)0x2c7c, (short)0x2a7c, (short)0x287c,
  (short)0x267c, (short)0x247c, (short)0x227c, (short)0x207c,
  (short)0x1efc, (short)0x1dfc, (short)0x1cfc, (short)0x1bfc,
  (short)0x1afc, (short)0x19fc, (short)0x18fc, (short)0x17fc,
  (short)0x16fc, (short)0x15fc, (short)0x14fc, (short)0x13fc,
  (short)0x12fc, (short)0x11fc, (short)0x10fc, (short)0x0ffc,
  (short)0x0f3c, (short)0x0ebc, (short)0x0e3c, (short)0x0dbc,
  (short)0x0d3c, (short)0x0cbc, (short)0x0c3c, (short)0x0bbc,
  (short)0x0b3c, (short)0x0abc, (short)0x0a3c, (short)0x09bc,
  (short)0x093c, (short)0x08bc, (short)0x083c, (short)0x07bc,
  (short)0x075c, (short)0x071c, (short)0x06dc, (short)0x069c,
  (short)0x065c, (short)0x061c, (short)0x05dc, (short)0x059c,
  (short)0x055c, (short)0x051c, (short)0x04dc, (short)0x049c,
  (short)0x045c, (short)0x041c, (short)0x03dc, (short)0x039c,
  (short)0x036c, (short)0x034c, (short)0x032c, (short)0x030c,
  (short)0x02ec, (short)0x02cc, (short)0x02ac, (short)0x028c,
  (short)0x026c, (short)0x024c, (short)0x022c, (short)0x020c,
  (short)0x01ec, (short)0x01cc, (short)0x01ac, (short)0x018c,
  (short)0x0174, (short)0x0164, (short)0x0154, (short)0x0144,
  (short)0x0134, (short)0x0124, (short)0x0114, (short)0x0104,
  (short)0x00f4, (short)0x00e4, (short)0x00d4, (short)0x00c4,
  (short)0x00b4, (short)0x00a4, (short)0x0094, (short)0x0084,
  (short)0x0078, (short)0x0070, (short)0x0068, (short)0x0060,
  (short)0x0058, (short)0x0050, (short)0x0048, (short)0x0040,
  (short)0x0038, (short)0x0030, (short)0x0028, (short)0x0020,
  (short)0x0018, (short)0x0010, (short)0x0008, (short)0x0000
};


short MulawConverter::mu2linfast(unsigned char index) {
  
  return MuLaw[index];
}

int MulawConverter::mu2lin(unsigned char b) {
  int mu = b ^ 0xFF;  // bit flipping
  int s = (mu & 0x80) >> 7 ; // X------- sign bit
  int e = (mu & 0x70) >> 4 ; // -XXX---- exponent
  int f = (mu & 0x0F) >> 0 ; // ----XXXX mantissa
  //System.out.print(" s=" + s + " e=" + e + " f=" + f );
  int lin;
  lin =  (f<<(e+1)) - 0x20 + (0x20<<e) ;
  return (s==1)?-lin:lin;
}

unsigned char MulawConverter::lin2mu(int lin) {
  int s,e,f; // sign, exp, mant
  int topp;
  if (lin < 0) {
    lin = -lin;
    s=1;
  } else
  s=0;
  for(int n=0;n<8;n++) {
    topp=(0x20<<(n+1)) - 0x20 ;
    if (lin < topp ) {
      e = n;
      f = ( lin - (0x20<<e) + 0x20 ) >> (e+1);
      //System.out.print(" s=" + s + " e=" + e + " f=" + f );
      return (unsigned char)( ( (s << 7) | (e << 4) | (f & 0x0F)) ^ 0xFF);
    }
  }
  return (unsigned char) (s<<8) ;
}
