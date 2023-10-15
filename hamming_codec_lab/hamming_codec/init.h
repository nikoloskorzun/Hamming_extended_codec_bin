#ifndef INIT_H
#define INIT_H

#define WIN_COMPILE_DEBUG

#define MATRIX_PRINTING


//#define ARDUINO_COMPILE_OPT



#define MEM_COUNTING

#define DEBUG 3


#ifdef WIN_COMPILE_DEBUG
	#include <iostream>
	typedef size_t my_size_t;

#else
	typedef size_t my_size_t;
	typedef unsigned char uint8_t;
#endif


#ifdef ARDUINO_COMPILE_OPT
	typedef uint16_t my_size_t;
#endif


typedef uint8_t byte;
typedef uint8_t bit;



#endif
