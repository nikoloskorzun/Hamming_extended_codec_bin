#ifndef APP_H

#define APP_H

#include <iostream>

#include "hamming.h"
#include "mat.h"



class App
{
public:
	App();
	~App();

	void run();


private:

    
    Bit_matrix noise(Bit_matrix& v, my_size_t error_count, my_size_t *errors);


	void print_pointer(my_size_t pos);


};

#endif

