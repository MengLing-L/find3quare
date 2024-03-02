#define DEBUG
#define BHJL_HE_MR_INTERATIONS 16

#include <map>
#include <gmp.h>
//#include <iostream>

using namespace std;


void mods(mpz_srcptr a, mpz_srcptr n, mpz_ptr aout){
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set (aout, a);
    mpz_mod (aout, aout, n);
    mpz_mul_ui (tmp, aout, 2);

    if(mpz_cmp (tmp, n) > 0){
        mpz_sub (aout, aout, n);
    }
    mpz_clear(tmp);
}

/*
def powmods(a, r, n):
    out = 1
    while r > 0:
        if (r % 2) == 1:
            r -= 1
            out = mods(out * a, n)
        r //= 2
        a = mods(a * a, n)
    return out*/
void powmods(mpz_srcptr a, mpz_srcptr r, mpz_srcptr n, mpz_ptr out){
    mpz_t rem, tmp_r, out_a, tmp_a, a_a;
    mpz_init(rem);
    mpz_init(tmp_r);
    mpz_init(out_a);
    mpz_init(tmp_a);
    mpz_init(a_a);
    mpz_set (tmp_r, r);
    mpz_set_ui (out, 1);
    mpz_set (tmp_a, a);
    while(mpz_cmp_ui (tmp_r, 0) > 0){
        mpz_mod_ui (rem, tmp_r, 2);
        if(mpz_cmp_ui (rem, 1) == 0){
            mpz_sub_ui (tmp_r, tmp_r, 1);
            mpz_mul (out_a, out, tmp_a);
            mods(out_a, n, out);
        }
        mpz_fdiv_q_ui (tmp_r, tmp_r, 2);
        mpz_mul (a_a, tmp_a, tmp_a);
        mods(a_a, n, tmp_a);
    }
    mpz_clear(rem);
    mpz_clear(tmp_r);
    mpz_clear(out_a);
    mpz_clear(tmp_a);
    mpz_clear(a_a);
}
/*
def quos(a, n):
    if n <= 0:
        return "negative modulus"
    return (a - mods(a, n))//n
*/

void quos(mpz_srcptr a, mpz_srcptr n, mpz_ptr out){

    if (mpz_cmp_ui (n, 0) <= 0){
        //cout << "quos n <=0" << endl;
    }

    mods(a, n, out);

    mpz_sub (out, a, out);

    mpz_fdiv_q (out, out, n);    

}

/*
def grem(w, z):
    # remainder in Gaussian integers when dividing w by z
    (w0, w1) = w
    (z0, z1) = z
    n = z0 * z0 + z1 * z1
    if n == 0:
        return "division by zero"
    u0 = quos(w0 * z0 + w1 * z1, n)
    u1 = quos(w1 * z0 - w0 * z1, n)
    return(w0 - z0 * u0 + z1 * u1,
           w1 - z0 * u1 - z1 * u0)
*/

void grem(mpz_srcptr w0, mpz_srcptr w1, mpz_srcptr z0, mpz_srcptr z1, mpz_ptr x1, mpz_ptr x2){
    mpz_t tmp_n, tmp_z0z0, tmp_z1z1, tmp_w0z0, tmp_w1z1, tmp_w1z0, tmp_w0z1, tmp_add, tmp_add1, u0, u1, z0u0, z1u1, z0u1, z1u0;
    mpz_init(tmp_n);
    mpz_init(tmp_z0z0);
    mpz_init(tmp_z1z1);
    mpz_init(tmp_w0z0);
    mpz_init(tmp_w1z1);
    mpz_init(tmp_w1z0);
    mpz_init(tmp_w0z1);
    mpz_init(tmp_add);
    mpz_init(tmp_add1);
    mpz_init(u0);
    mpz_init(u1);
    mpz_init(z0u0);
    mpz_init(z1u1);
    mpz_init(z0u1);
    mpz_init(z1u0);

    mpz_mul (tmp_z0z0, z0, z0);
    mpz_mul (tmp_z1z1, z1, z1);

    mpz_add (tmp_n, tmp_z0z0, tmp_z1z1);

    if (mpz_cmp_ui (tmp_n, 0) == 0){
        //cout << "grem n ==0" << endl;
    }

    mpz_mul (tmp_w0z0, w0, z0);
    mpz_mul (tmp_w1z1, w1, z1);

    mpz_add (tmp_add, tmp_w0z0, tmp_w1z1);

    mpz_mul (tmp_w1z0, w1, z0);
    mpz_mul (tmp_w0z1, w0, z1);

    mpz_sub (tmp_add1, tmp_w1z0, tmp_w0z1);

    quos(tmp_add, tmp_n, u0);
    quos(tmp_add1, tmp_n, u1);

    mpz_mul (z0u0, z0, u0);
    mpz_mul (z1u1, z1, u1);
    mpz_mul (z0u1, z0, u1);
    mpz_mul (z1u0, z1, u0);

    mpz_sub (x1, w0, z0u0);
    mpz_add (x1, x1, z1u1);

    mpz_sub (x2, w1, z0u1);
    mpz_add (x2, x2, z1u0);

    mpz_clear(tmp_n);
    mpz_clear(tmp_z0z0);
    mpz_clear(tmp_z1z1);
    mpz_clear(tmp_w0z0);
    mpz_clear(tmp_w1z1);
    mpz_clear(tmp_w1z0);
    mpz_clear(tmp_w0z1);
    mpz_clear(tmp_add);
    mpz_clear(tmp_add1);
    mpz_clear(u0);
    mpz_clear(u1);
    mpz_clear(z0u0);
    mpz_clear(z1u1);
    mpz_clear(z0u1);
    mpz_clear(z1u0);
}

/*
def ggcd(w, z):
    while z != (0,0):
        w, z = z, grem(w, z)
    return w
*/

void ggcd(mpz_srcptr w0, mpz_srcptr w1, mpz_srcptr z0, mpz_srcptr z1, mpz_ptr out_w0, mpz_ptr out_w1){
    mpz_t tmp_z0, tmp_z1, tmp_w0, tmp_w1, out_z0, out_z1;
    mpz_init(tmp_z0);
    mpz_init(tmp_z1);
    mpz_init(tmp_w0);
    mpz_init(tmp_w1);
    mpz_init(out_z0);
    mpz_init(out_z1);
    mpz_set (tmp_z0, z0);
    mpz_set (tmp_z1, z1);
    mpz_set (tmp_w0, w0);
    mpz_set (tmp_w1, w1);

    while(mpz_cmp_ui (tmp_z0, 0) != 0  && mpz_cmp_ui (tmp_z1, 0) != 0){
        grem(tmp_w0, tmp_w1, tmp_z0, tmp_z1, out_z0, out_z1);
        mpz_set (out_w0, tmp_z0);
        mpz_set (out_w1, tmp_z1);

        mpz_set (tmp_z0, out_z0);
        mpz_set (tmp_z1, out_z1);
        mpz_set (tmp_w1, out_w1);
        mpz_set (tmp_w0, out_w0);
    }
    mpz_clear(tmp_z0);
    mpz_clear(tmp_z1);
    mpz_clear(tmp_w0);
    mpz_clear(tmp_w1);
    mpz_clear(out_z0);
    mpz_clear(out_z1);
}

/*
def root4(p):
    # 4th root of 1 modulo p
    if p <= 1:
        return "too small"
    if (p % 4) != 1:
        return "not congruent to 1"
    k = p//4
    j = 2
    while True:
        a = powmods(j, k, p)
        b = mods(a * a, p)
        if b == -1:
            return a
        if b != 1:
            return "not prime"
        j += 1
*/

void root4(mpz_srcptr p, mpz_ptr a){
    mpz_t k,j,a_a, b;
    mpz_init(k);
    mpz_init(j);
    mpz_init(a_a);
    mpz_init(b);
    mpz_fdiv_q_ui (k, p, 4);
    mpz_set_ui (j, 2);

    while (true)
    {
        powmods(j, k, p, a);
        mpz_mul (a_a, a, a);
        mods(a_a, p, b);
        if(mpz_cmp_si (b, -1) == 0){
            break;
        }
        if(mpz_cmp_ui (b, 1) != 0){
            //cout << "root4 not prime" << endl;
            break;
        }
        mpz_add_ui (j, j, 1);
    }

    mpz_clear(k);
    mpz_clear(j);
    mpz_clear(a_a);
    mpz_clear(b);
}

void find_three_squares(mpz_srcptr n, mpz_ptr x0, mpz_ptr x1, mpz_ptr x2){
    mpz_t a, zero, one, seed, p, rem, root;
    mpz_init(a);
    mpz_init(zero);
    mpz_init(one);
    mpz_init(p);
    mpz_init(rem);
    mpz_init(seed);
    mpz_init(root);

    gmp_randstate_t prng;
    gmp_randinit_mt(prng);
    //mpz_set_ui(seed, time(NULL));
    mpz_set_ui(seed, 45634L);
    gmp_randseed(prng, seed);

    mpz_set_ui (zero, 0);
    mpz_set_ui (one, 1);

    mpz_sqrt (root, n);
    size_t bits = mpz_sizeinbase(root, 2);
    int i=1;
    
    do{
        while(true){
            mpz_urandomb(x0, prng, bits);
            if (mpz_cmp(x0, root) < 0) {
                break;
            }
        }
        mpz_mul (p, x0, x0);
        mpz_sub (p, n, p);
        mpz_mod_ui (rem, p, 4);
    }while(!mpz_probab_prime_p(p, BHJL_HE_MR_INTERATIONS) || mpz_cmp_ui (rem, 1) != 0 || mpz_cmp_ui (p, 0) <= 0);

    root4(p, a);

    ggcd(p, zero, a, one, x1, x2);
    
    mpz_clear(a);
    mpz_clear(zero);
    mpz_clear(one);
    mpz_clear(p);
    mpz_clear(rem);
    mpz_clear(seed);
    mpz_clear(root);
    gmp_randclear (prng);
}

/*
int main()
{  
    mpz_t n, x0, x1, x2;
    mpz_init(n);
    mpz_init(x0);
    mpz_init(x1);
    mpz_init(x2);
    mpz_set_ui (n, 11323432);
    find_three_squares(n, x0,x1,x2);

    mpz_t x0_, x1_, x2_, sum;
    mpz_init(x0_);
    mpz_init(x1_);
    mpz_init(x2_);
    mpz_init(sum);

    mpz_mul(x0_, x0, x0);
    mpz_mul(x1_, x1, x1);
    mpz_mul(x2_, x2, x2);
    mpz_add(sum, x0_, x1_);
    mpz_add(sum, sum, x2_);


    if (mpz_cmp (sum, n) == 0){
        cout << "three square success" << endl;
    }else{
        cout << "three square failed" << endl;
    }

    mpz_clear(n);
    mpz_clear(x0);
    mpz_clear(x1);
    mpz_clear(x2);
    mpz_clear(x0_);
    mpz_clear(x1_);
    mpz_clear(x2_);
    
    return 0; 
}*/