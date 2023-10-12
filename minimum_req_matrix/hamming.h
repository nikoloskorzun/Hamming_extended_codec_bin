#ifndef HAMMING_H

#define HAMMING_H

#include "mat.h"


class Hamming_codec
{


public:
    Hamming_codec(my_size_t m);
    ~Hamming_codec();
    
    my_size_t get_k();


    void print_params();

    Bit_matrix code(Bit_matrix word);
    Bit_matrix decode(Bit_matrix word);
    Bit_matrix decode_extended(Bit_matrix word);
    Bit_matrix get_syndrome(Bit_matrix coded_word);


    void convert_to_extended_matrix();
    Bit_matrix convert_to_extended(Bit_matrix word);

private:
    
    Bit_matrix generator_matrix;
    Bit_matrix parity_check_matrix;
    Bit_matrix B1_matrix;
    
    
    my_size_t m;
    my_size_t n;
    my_size_t k;
    my_size_t r;


    


    void create_generator_matrix();

    void create_parity_check_matrix();
    void create_B1_matrix();





};

#endif

