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
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

class GnuplotDriver {
  string xlabel,ylabel,title;
  bool inverse,raise,persist;
  string trace_color,background_color;
  FILE *gp;
  public:
  GnuplotDriver() {
    ylabel = "Amplitude";
    title = "FFT Results";
    inverse = false;
    raise = false;
    persist = false;
    trace_color = "blue";
    background_color = "white";
    gp = NULL;
  }
  
  ~GnuplotDriver() {
    if(gp) {
      fclose(gp);
    }
  }
  
  bool decode_comline(int argc,char **argv)
  {
    for(int i = 1;i < argc;i++) {
      string arg = (string) argv[i];
      if(arg.length() == 2 && arg[0] == '-') {
        char c = arg[1];
        switch (c) {
          case 'h':
            cerr << "Usage: [-i(nverse mode)]" << endl;
          cerr << "       [-t (chart title, default \"" << title << "\"]" << endl;
          cerr << "       [-x (x axis title, default \"Frequency Hz\")]" << endl;
          cerr << "       [-y (y axis title, default \"" << ylabel << "\")]" << endl;
          cerr << "       [-r (raise)]" << endl;
          cerr << "       [-p (persist)]" << endl;
          cerr << "       [-c (trace color, default \"" << trace_color << "\")]" << endl;
          cerr << "       [-b (background color, default \"" << background_color << "\")]" << endl;
          return true;
          case 'i':
            inverse = true;
          break;
          case 't':
            title = (string) argv[++i];
          break;
          case 'x':
            xlabel = (string) argv[++i];
          break;
          case 'y':
            ylabel = (string) argv[++i];
          break;
          case 'c':
            trace_color = (string) argv[++i];
          break;
          case 'b':
            background_color = (string) argv[++i];
          break;
          case 'r':
            raise = true;
          break;
          case 'p':
            persist = true;
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
    if(xlabel.length() == 0) {
      if(inverse) {
        xlabel = "Time Seconds";
      }
      else {
        xlabel = "Frequency Hz";
      }
    }
    double array_size,output_size,samples_per_second;
    double vmin = 1e30,vmax = -1e30;
    double re,im,m;
    try {
      while(cin >> array_size && cin >> samples_per_second) {
        double xscale;
        if(inverse) {
          output_size = array_size;
          xscale = 1.0 / samples_per_second;
        }
        else {
          output_size = array_size / 2;
          xscale = samples_per_second / array_size;
        }
        stringstream buf;
        buf << "set style data line" << endl;
        buf << "set title '" << title << "'" << endl;
        buf << "set xlabel '" << xlabel << "'" << endl;
        buf << "set ylabel '" << ylabel << "'" << endl;
        buf << "unset cblabel" << endl;
        stringstream data;
        for(int i = 0;i < array_size;i++) {
          cin >> re >> im;
          if(inverse) {
            m = re;
          }
          else {
            m = sqrt(re*re+im*im);
          }
          if(i < output_size) {
            data << xscale * i << " " << m << endl;
            if(i > 0) {
              vmin = (m < vmin)?m:vmin;
              vmax = (m > vmax)?m:vmax;
            }
          }
        }
        vmax = ceil(vmax);
        vmin = -ceil(-vmin);
        buf << "plot [0:";
        buf << xscale * output_size;
        buf << "] [" << vmin << ":" << vmax << "] \"-\"";
        buf << " notitle lc rgb \"" << trace_color << "\"" << endl;
        buf << data.str();
        buf << "e" << endl;
        if(!gp) {
          string com = (string) "gnuplot -background " + background_color + "";
          if(raise) {
            com += " -raise";
          }
          if(persist) {
            com += " -persist";
          }
          gp = popen(com.c_str(),"w");
        }
        fprintf(gp,"%s",buf.str().c_str());
      }
    }
    catch (ios::failure const &problem) {
      cerr << "gnuplot_driver: " << problem.what() << endl;
    }
  }
};

int main(int argc, char **argv) {
  GnuplotDriver gpd;
  gpd.process(argc,argv);
  return 0;
}
