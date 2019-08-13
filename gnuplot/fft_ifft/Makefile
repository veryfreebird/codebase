# set strict rules

CPPFLAGS = -ansi -pedantic-errors -Wall -O3
CC = g++ ${CPPFLAGS}

objects = Complex.o FFT.o DFT.o fft_processor.o

all : fft_processor signal_source sound_source gnuplot_driver

Complex : Complex.o

FFT : FFT.o
DFT : DFT.o

mulaw_converter : mulaw_converter.o

fft_processor : ${objects}
	${CC} -o fft_processor ${objects}

Complex.o : Complex.h

FFT.o : FFT.h Complex.h
DFT.o : DFT.h Complex.h

mulaw_converter.o : mulaw_converter.h

fft_processor.o : FFT.h DFT.h Complex.h

# standalone utilities

signal_source : signal_source.o
sound_source : sound_source.o mulaw_converter.o
gnuplot_driver : gnuplot_driver.o

signal_source.o : signal_source.cpp
sound_source.o : sound_source.cpp

gnuplot_driver.o : gnuplot_driver.cpp

.PHONY : clean
clean : 
	-rm *.o

