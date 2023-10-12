
#include "hamming.h"

my_size_t Hamming_codec::get_k()
{
    return this->k;
}

my_size_t pow(my_size_t a, my_size_t n)
{

    my_size_t res = 1;
    for (my_size_t i = 0; i < n; i++)
        res *= a;
    return res;
}
inline bool is_2_power(my_size_t n)
{
    return ((n > 0) && ((n & (n - 1)) == 0));
}



void Hamming_codec::convert_to_extended_matrix()
{
    //not using.
    Bit_matrix temp = this->parity_check_matrix;
    Bit_matrix v = get_zeros_vector(this->m);
    v.transpose();
    temp.right_append(v);
    v = get_ones_vector(this->n + 1);
    temp.down_append(v);
    this->n++;
    this->parity_check_matrix = temp;
}





Bit_matrix Hamming_codec::convert_to_extended(Bit_matrix coded_word)
{
    Bit_matrix temp(coded_word);
    if (coded_word.get_amount_rows() == 1)
    {
        Bit_matrix el(xor_sum(coded_word));
        temp.right_append(el);
    }
    return temp;
}


void Hamming_codec::print_params()
{
#ifdef WIN_COMPILE_DEBUG
    std::cout << "Hamming code with params:\n\tm = " << this->m << "\n\tn = " << this->n << "\n\tk = " << this->k << "\n\tr = " << this->r << "\n";

    std::cout << "B1 matrix:\n";
    this->B1_matrix.print();
    std::cout << "parity check matrix:\n";
    this->parity_check_matrix.print();
    std::cout << "generator matrix:\n";
    this->generator_matrix.print();
#endif // WIN_COMPILE_DEBUG



}
Hamming_codec::~Hamming_codec()
{


}








Bit_matrix Hamming_codec::code(Bit_matrix word)
{
    Bit_matrix temp;
    if ((word.get_amount_rows() == 1) && (word.get_amount_column() == this->k))
    {
        temp = word * this->generator_matrix;
    }
    return temp;

}
Bit_matrix Hamming_codec::get_syndrome(Bit_matrix coded_word)
{

    Bit_matrix temp;
    if ((coded_word.get_amount_rows() == 1) && (coded_word.get_amount_column() == this->n))
    {
        Bit_matrix t = this->parity_check_matrix;
        t.transpose();
        temp = coded_word * t;

    }
    return temp;


}


Bit_matrix Hamming_codec::decode(Bit_matrix coded_word)
{

    Bit_matrix syndrome = this->get_syndrome(coded_word);

    if (is_zeros_vector(syndrome))
        return coded_word.slice(0, 0, 0, this->k - 1);
    my_size_t pos = bit_vector_to_number(syndrome);

    coded_word.reverse_element(0, coded_word.get_amount_column() - 2 - pos);

    return coded_word.slice(0, 0, 0, this->k - 1);


}


Bit_matrix Hamming_codec::decode_extended(Bit_matrix coded_word)
{

    bit check_bit = coded_word.get_element(0, coded_word.get_amount_column() - 1);

    Bit_matrix coded_word_without_last_bit = coded_word.slice(0, 0, 0, coded_word.get_amount_column() - 2);
    bit s = xor_sum(coded_word_without_last_bit);


    Bit_matrix syndrome = this->get_syndrome(coded_word_without_last_bit);
    bool syndrome_zeros = is_zeros_vector(syndrome);

    if (s == check_bit)
    {
        if (syndrome_zeros)
        {
#ifdef WIN_COMPILE_DEBUG
#if DEBUG > 0
            std::cout << "Errors not found\n";

#endif
#endif
            return coded_word.slice(0, 0, 0, this->k - 1);
        }
        else
        {
#ifdef WIN_COMPILE_DEBUG
#if DEBUG > 0
            std::cout << "Two errors found\n";
            std::cout << "Syndrom = ";
            syndrome.print();


#endif
#endif

            return coded_word.slice(0, 0, 0, this->k - 1);
        }

    }
    else
    {

        if (syndrome_zeros)
        {
#ifdef WIN_COMPILE_DEBUG
#if DEBUG > 0
            std::cout << "many errors or error in last bit\n";
            std::cout << "Syndrom = ";
            syndrome.print();


#endif
#endif

            return coded_word.slice(0, 0, 0, this->k - 1);

        }
        else
        {
#ifdef WIN_COMPILE_DEBUG
#if DEBUG > 0
            std::cout << "single error\n";
            std::cout << "Syndrom = ";
            syndrome.print();


#endif
#endif

            return this->decode(coded_word_without_last_bit);
        }



    }


}




void Hamming_codec::create_B1_matrix()
{

    Bit_matrix t(this->m, this->k);
    this->B1_matrix = t;

    this->B1_matrix.set_zero();

    my_size_t i;
    my_size_t j = 0;

    for (my_size_t iter = n; iter > 0; iter--)
    {
        if (!is_2_power(iter))
        {
            my_size_t temp = iter;
            i = this->m - 1;
            while (temp)
            {
                this->B1_matrix.set_element(i, j, (temp & 1));


                i--;
                temp >>= 1;
            }

            j++;
        }

    }






}
void Hamming_codec::create_generator_matrix()
{
    Bit_matrix t(this->k, this->k);
    this->generator_matrix = t;
    this->generator_matrix.reset_to_identity();

    Bit_matrix temp(this->B1_matrix);
    temp.transpose();

    this->generator_matrix.right_append(temp);



}

void Hamming_codec::create_parity_check_matrix()
{





    Bit_matrix t(this->B1_matrix);
    this->parity_check_matrix = t;

    Bit_matrix temp(this->m, this->m);
    temp.reset_to_identity();
    this->parity_check_matrix.right_append(temp);


}

Hamming_codec::Hamming_codec(my_size_t m)
{
    this->m = m;
    this->n = pow(2, this->m) - 1;
    this->k = this->n - this->m;
    this->r = this->n - this->k;

    this->create_B1_matrix();
    this->create_generator_matrix();
    this->create_parity_check_matrix();

}