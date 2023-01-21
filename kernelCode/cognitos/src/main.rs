#![no_std]
#![no_main]
#![feature(asm)]

mod vga_buffer;
use core::panic::PanicInfo;

/// This function is called on panic.
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}


#[no_mangle]
pub extern "C" fn _start() -> ! {
    println!("Hello cognito{}","!!!");
    panic!("Some panic message");
    loop {}
}
