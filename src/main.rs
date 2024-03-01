use foreign_types::{ForeignType, ForeignTypeRef};
use libc::c_int;
use std::time::Instant;
use gmp::rand::RandState;
use gmp::mpz::*;

pub mod util;
pub mod cfun;
pub mod three_square;

#[derive(Debug)]
pub struct ParseError {
    _priv: ()
}

fn cvt_p<T>(r: *mut T) -> Result<*mut T, ParseError> {
    if r.is_null() {
        Err(ParseError{ _priv: () })
    } else {
        Ok(r)
    }
}

fn cvt(r: c_int) -> Result<c_int, ParseError> {
    if r <= 0 {
        Err(ParseError{ _priv: () })
    } else {
        Ok(r)
    }
}

fn cvt_n(r: c_int) -> Result<c_int, ParseError> {
    if r < 0 {
        Err(ParseError{ _priv: () })
    } else {
        Ok(r)
    }
}
fn main() {
    let mut n: Mpz = From::<i64>::from(54);
    let mut x0: Mpz = From::<i64>::from(0);
    let mut x1: Mpz = From::<i64>::from(0);
    let mut x2: Mpz = From::<i64>::from(0);
    three_square::find_three_squares(&n, &x0, &x1, &x2);
    println!("x0: {}",x0.to_string());
    println!("x1: {}",x1.to_string());
    println!("x1: {}",x2.to_string());
    
}
