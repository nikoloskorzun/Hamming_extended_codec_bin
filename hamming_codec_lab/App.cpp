#include "App.h"


Bit_matrix App::noise(Bit_matrix& v, my_size_t error_count, my_size_t* errors=NULL)
{
    Bit_matrix arr(1, v.get_amount_column());
    Bit_matrix temp(v);
    arr.set_zero();
    my_size_t ptr;
    my_size_t i = 0;
    while (i < error_count)
    {
        do {
            ptr = rand() % v.get_amount_column();
        } while (arr.get_element(0, ptr));
        arr.set_element(0, ptr, 1);
        if(errors)
            errors[i] = ptr;
        temp.reverse_element(0, ptr);
        i++;
    }
    return temp;
}

bit get_rand()
{
    return rand() % 2;
}


App::App()
{


}
App::~App()
{


}


void App::print_pointer(my_size_t pos)
{
    for (my_size_t i = 0; i < pos; i++)
        std::cout << "  ";
    std::cout << "^\n";

}

void App::run()
{
    srand(time(0));
    my_size_t r = 6, l;


    Hamming_codec codec(r);

    codec.print_params();


    l = codec.get_k();



    Bit_matrix w = get_random_vector(l, get_rand);
    std::cout << "\n>>> ";
    w.print();
    std::cout << "\n";


    Bit_matrix res = codec.code(w);
    std::cout << "coded word without noise\n";
    res.print();

    
    my_size_t error;
    res = this->noise(res, 1, &error);
    std::cout << "coded word with noise\n";

    res.print();


    this->print_pointer(error);
    std::cout << "syndrome\n";

    codec.get_syndrome(res).print();
    Bit_matrix ans = codec.decode(res);
    std::cout << "decoded word\n";
    ans.print();
    this->print_pointer(error);
    Bit_matrix w_ = codec.get_word(ans);
    std::cout << "\n>>> ";
    w_.print();
    std::cout << "\n\n\n\n";




    if (w_ == w)
        std::cout << "SUCCESS\n";
    else
        std::cout << "FAILURE\n";

}