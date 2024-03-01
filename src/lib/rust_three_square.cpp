#include "three_square.cpp"


extern "C"{
    //JL_decrypt(unsigned long int s, unsigned long int l, mpz_ptr recover_m, JL_Ciphertext *jl_ciphertext, JL_PK *pk, JL_SK *sk)
    void find_three_squares_rust(mpz_srcptr n, mpz_ptr x0, mpz_ptr x1, mpz_ptr x2){
        find_three_squares(n, x0, x1, x2);
    }
}
