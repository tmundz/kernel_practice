/*
 * Setting up Vga buffers and rules for displaying
 * create macros for the rust print println _print
 *
 * */

use spin::Mutex;
use lazy_static::lazy_static;
use volatile::Volatile;
use core::fmt;

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => ($crate::vga_buffer::_print(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! println {
    () => ($crate::print!("\n"));
    ($($arg:tt)*) => ($crate::print!("{}\n", format_args!($($arg)*)));
}

#[doc(hidden)]
pub fn _print(args: fmt::Arguments) {
    use core::fmt::Write;
    PRINT.lock().write_fmt(args).unwrap();
}

#[allow(dead_code)]
#[derive(Debug, Clone, PartialEq, Eq)]
#[repr(u8)]
pub enum Color {
    //basic colours
    Black = 0x0,
    Blue = 0x1,
    Green = 0x2,
    Cyan = 0x3,
    Red = 0x4,
    Magenta = 0x5,
    Brown = 0x6,
    Pink = 0xd,
    Yellow = 0xe,
    White = 0xf,
    //bright bit aka light blue 
    LightGray = 0x7,
    DarkGray = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xa,
    LightCyan = 0xb,
    LightRed = 0xc
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(transparent)]
struct ColorCode(u8);
impl ColorCode {
    fn new(foreground: Color, background: Color) -> ColorCode {
        ColorCode((background as u8) << 4 | (foreground as u8))
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(C)]
struct ScreenChar {
    ascii_character: u8,
    color_code: ColorCode,
}

const BUFFER_HEIGHT: usize = 25;
const BUFFER_WIDTH: usize = 80;

#[repr(transparent)]
struct Buffer {
    //add the volatile to force the use of the write method
    chars: [[Volatile<ScreenChar>; BUFFER_WIDTH]; BUFFER_HEIGHT],
}

//use mutex to safely change the static global variable
lazy_static! {
    pub static ref PRINT: Mutex<Print> = Mutex::new(Print {
        column_position: 0,
        color_code: ColorCode::new(Color::Cyan, Color::Pink),
        buffer: unsafe {&mut *(0xb8000 as *mut Buffer)},
    });
}

pub struct Print {
    column_position: usize,
    color_code: ColorCode,
    buffer: &'static mut Buffer,
}


impl fmt::Write for Print {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        self.print_string(s);
        Ok(())
    }
}

impl Print {
    pub fn print_byte(&mut self, byte: u8) {
        match byte {
            b'\n' => self.new_line(),
            byte => {
                if self.column_position >= BUFFER_WIDTH {
                    self.new_line();
                }

                let row = BUFFER_HEIGHT - 1;
                let col = self.column_position;
                let color_code = self.color_code;

                self.buffer.chars[row][col].write(ScreenChar {
                    ascii_character: byte,
                    color_code,
                });
                self.column_position += 1;
            }
        }
    }

    fn new_line(&mut self) {
        for row in 1..BUFFER_HEIGHT {
            for col in 0..BUFFER_WIDTH {
                let character = self.buffer.chars[row][col].read();
                self.buffer.chars[row -1][col].write(character);
            }
        }
        self.clear_row(BUFFER_HEIGHT - 1);
        self.column_position = 0;
    }
    
    fn clear_row(&mut self, row: usize) {
        let blank = ScreenChar {
            ascii_character: b' ',
            color_code: self.color_code,
        };
        for col in 0..BUFFER_HEIGHT {
            self.buffer.chars[row][col].write(blank);
        }
    }

    pub fn print_string(&mut self, s:&str) {
        for byte in s.bytes() {
            match byte {
                0x20..=0x7e | b'\n' => self.print_byte(byte),
                _ => self.print_byte(0xfe),
            }
        }
    }
}



