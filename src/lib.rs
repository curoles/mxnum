include!(concat!(env!("OUT_DIR"), "/bindings.rs"));


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_c_fun() {
        assert_eq!(unsafe { fun(6) }, 7);
    }

    #[test]
    fn test_c_src_unittest() {
        assert_eq!(unsafe { c_src_unittest() }, 0);
    }
}
