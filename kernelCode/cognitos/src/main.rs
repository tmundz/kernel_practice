#![no_std]
#![no_main]
#![feature(asm)]

mod vga_buffer;
use core::panic::PanicInfo;

/// This function is called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}


static HELLO: &[u8] = b"Hello Cognito";

#[no_mangle]
pub extern "C" fn _start() -> ! {
    vga_buffer::vga_test();

    loop {}
}
