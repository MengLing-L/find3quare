//use libloading;
use foreign_types::{ForeignType, ForeignTypeRef};
use libc::c_int;

pub mod util;
pub mod cfun;
pub mod three_square;

#[macro_use]
mod macros;


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
