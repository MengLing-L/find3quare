
use gmp::mpz::*;

#[link(name = "rust_three_square", kind = "static")]
extern "C" {
    pub fn find_three_squares_rust(
        n: &Mpz,
        x0: &Mpz,
        x1: &Mpz,
        x2: &Mpz
    );
}



