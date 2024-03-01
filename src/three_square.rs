
use gmp::mpz::*;
//#[macro_use]
//use super::macros::*;
mod cfun{
    pub use crate::cfun::*;
}  

pub fn find_three_squares(
    n: &Mpz,
    x0: &Mpz,
    x1: &Mpz,
    x2: &Mpz
){
    unsafe {
        cfun::find_three_squares_rust(&n, &x0, &x1, &x2);
    }
}