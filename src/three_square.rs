use std::mem::{uninitialized,size_of};
use foreign_types::{ForeignType, ForeignTypeRef};
use libc::c_int;
use std::fmt;
use std::ptr;
use std::error::Error;
use crate::util::*;
use crate::{cvt, cvt_n, cvt_p, ParseError};
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