use std::env;
use std::path::PathBuf;

fn generate_bindings() {
	println!("cargo:rerun-if-changed=src/c");

	let bindings = bindgen::Builder::default()
		.header("src/c/api_wrapper.h")
		// Tell cargo to invalidate the built crate whenever any of the
		// included header files changed.
		.parse_callbacks(Box::new(bindgen::CargoCallbacks))
		.ctypes_prefix("cty")
		// make the generated code #![no_std] compatible
		.use_core()
		.generate()
		.expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}

fn main() {	
	generate_bindings();

    cc::Build::new()
        .file("src/c/fun.c")
		.file("src/c/capi.c")
		.file("src/c/mx_int8.c")
		.static_flag(true)
		.std("gnu17")
		.opt_level(3)
		.flag("-ffreestanding")
		.flag("-nostdlib")
		.warnings(true)
		.warnings_into_errors(true)
        .compile("cfun");
}
