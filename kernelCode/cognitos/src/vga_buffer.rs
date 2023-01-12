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
    chars: [[ScreenChar; BUFFER_WIDTH]; BUFFER_HEIGHT],
}

pub struct Print {
    column_position: usize,
    color_code: ColorCode,
    buffer: &'static mut Buffer,
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

                self.buffer.chars[row][col] = ScreenChar {
                    ascii_character: byte,
                    color_code,
                };
                self.column_position += 1;
            }
        }
    }

    fn new_line(&mut self) {
        todo!() 
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


pub fn vga_test() {
    let mut print = Print {
    column_position: 0,
    color_code: ColorCode::new(Color::Pink, Color::Black),
    buffer: unsafe{&mut *(0xb8000 as *mut Buffer)}
    };
    print.print_byte(b'W');
    print.print_string("elcome to ");
    print.print_string("Cognito");
}

