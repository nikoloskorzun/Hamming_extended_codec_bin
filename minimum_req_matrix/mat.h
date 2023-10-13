#ifndef MAT_H
#define MAT_H

#include "init.h"

#ifndef WIN_COMPILE_DEBUG
typedef unsigned char uint8_t;
#endif

typedef size_t my_size_t;
typedef uint8_t byte;
typedef uint8_t bit;


class Bit_matrix
{
/*
    data in matrix before initialization undefined. But last byte in this.matrix equal zero until it's changed 


*/
 
public:
    
    Bit_matrix();
    Bit_matrix(bit n);
    /*
    * mat[0][0] == n
    */
    Bit_matrix(my_size_t amount_rows, my_size_t amount_column); 
    /* 3, 4 ->
    ####
    ####
    ####
    */
    Bit_matrix(const Bit_matrix& other);
    Bit_matrix(Bit_matrix* other);

    ~Bit_matrix();

    void reset(my_size_t amount_rows, my_size_t amount_column);

  
    bit get_element(my_size_t i, my_size_t j);
    void set_element(my_size_t i, my_size_t j, bit value);
    void reverse_element(my_size_t i, my_size_t j);

    void set_zero();
    void set_ones();

    my_size_t get_amount_rows();
    my_size_t get_amount_column();

    bool operator== (Bit_matrix& other);
    Bit_matrix& operator=(const Bit_matrix& matrix);


    void transpose();
    void reset_to_identity();


    void right_append(Bit_matrix& other);
    void down_append(Bit_matrix& other);


    Bit_matrix slice(my_size_t i_start, my_size_t i_end,my_size_t j_start,my_size_t j_end);


    void print();
    inline bool is_square();

private:

#ifdef MEM_COUNTING

    static my_size_t mem_used;
#endif // 

    byte* matrix;

    my_size_t amount_rows;
    my_size_t amount_column;
    my_size_t size_allocated_memory;

    inline byte bit_mask(my_size_t bit_pos);

    //memory functions
    byte *allocate_bits(my_size_t m, my_size_t n);
    void free_bits(void *mem);

};


Bit_matrix get_random_vector(my_size_t len, bit(*get_rand)());
Bit_matrix get_zeros_vector(my_size_t n);
bool is_zeros_vector(Bit_matrix& v);
Bit_matrix get_ones_vector(my_size_t n);
bit xor_sum(Bit_matrix& m);
my_size_t bit_vector_to_number(Bit_matrix& vector);
Bit_matrix operator* (Bit_matrix& left, Bit_matrix& right);

#endif // !MAT_H