include!(concat!(env!("OUT_DIR"), "/bindings.rs"));


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_c_fun() {
        assert_eq!(unsafe { fun(6) }, 7);
    }

    #[test]
    fn test_c_src_unittest_bitops() {
        assert_eq!(unsafe { capi_unittest_bitops() }, 1);
    }
	
    #[test]
    fn test_c_src_unittest_max_32_ints() {
        assert_eq!(unsafe { capi_unittest_max_32_ints() }, 1);
    }
}
