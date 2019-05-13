
//note: adapted from https://github.com/adafruit/Adafruit_SSD1306

#define SSD1306_128_64
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

/*
Set Display Offset (D3h)
This is a double byte command. The second command specifies the mapping of the display start line to one of
COM0~COM63 (assuming that COM0 is the display start line then the display start line register is equal to 0).
For example, to move the COM16 towards the COM0 direction by 16 lines the 6-bit data in the second byte
should be given as 010000b. To move in the opposite direction by 16 lines the 6-bit data should be given by
64 – 16, so the second byte would be 100000b. The following two tables (Table 10-1, Table 10-2) show the
example of setting the command C0h/C8h and D3h.
*/
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

/*
Set Lower Column Start Address for Page Addressing Mode (00h~0Fh):
This command specifies the lower nibble of the 8-bit column start address for the display data RAM under
Page Addressing Mode. The column address will be incremented by each data access. Please refer to Section
Table 9-1 and Section 10.1.3 for details.
*/
#define SSD1306_SETLOWCOLUMN 0x00

/*
Set Higher Column Start Address for Page Addressing Mode (10h~1Fh)
This command specifies the higher nibble of the 8-bit column start address for the display data RAM under
Page Addressing Mode. The column address will be incremented by each data access. Please refer to Section
Table 9-1 and Section 10.1.3 for details.
*/
#define SSD1306_SETHIGHCOLUMN 0x10

/*
Set Display Start Line (40h~7Fh)
This command sets the Display Start Line register to determine starting address of display RAM, by selecting
a value from 0 to 63. With value equal to 0, RAM row 0 is mapped to COM0. With value equal to 1, RAM
row 1 is mapped to COM0 and so on.
*/
#define SSD1306_SETSTARTLINE 0x40

/*
Set Memory Addressing Mode:
Two byte command, second byte sets addressing mode.

Horizontal addressing mode: 00xb
In horizontal addressing mode, after the display RAM is read/written, the column address pointer is increased
automatically by 1. If the column address pointer reaches column end address, the column address pointer is
reset to column start address and page address pointer is increased by 1. The sequence of movement of the
page and column address point for horizontal addressing mode is shown in Figure 10-3. When both column
and page address pointers reach the end address, the pointers are reset to column start address and page start
address 


Page addressing mode: 10xb
In page addressing mode, after the display RAM is read/written, the column address pointer is increased
automatically by 1. If the column address pointer reaches column end address, the column address pointer is
reset to column start address and page address pointer is not changed. Users have to set the new page and
column addresses in order to access the next page RAM content.

Vertical addressing mode: 01xb
In vertical addressing mode, after the display RAM is read/written, the page address pointer is increased
automatically by 1. If the page address pointer reaches the page end address, the page address pointer is reset
to page start address and column address pointer is increased by 1. The sequence of movement of the page
and column address point for vertical addressing mode is shown in Figure 10-4. When both column and page
address pointers reach the end address, the pointers are reset to column start address and page start address
*/
#define SSD1306_MEMORYMODE 0x20

/*
Set Column Address (21h)
This triple byte command specifies column start address and end address of the display data RAM. This
command also sets the column address pointer to column start address. This pointer is used to define the
current read/write column address in graphic display data RAM. If horizontal address increment mode is
enabled by command 20h, after finishing read/write one column data, it is incremented automatically to the
next column address. Whenever the column address pointer finishes accessing the end column address, it is
reset back to start column address and the row address is incremented to the next row.
*/
#define SSD1306_COLUMNADDR 0x21

/*
Set Page Address (22h)

This triple byte command specifies page start address and end address of the display data RAM. This
command also sets the page address pointer to page start address. This pointer is used to define the current
read/write page address in graphic display data RAM. If vertical address increment mode is enabled by
command 20h, after finishing read/write one page data, it is incremented automatically to the next page
address. Whenever the page address pointer finishes accessing the end page address, it is reset back to start
page address.
*/
#define SSD1306_PAGEADDR 0x22

/*
Set Column Address (21h)
This triple byte command specifies column start address and end address of the display data RAM. This
command also sets the column address pointer to column start address. This pointer is used to define the
current read/write column address in graphic display data RAM. If horizontal address increment mode is
enabled by command 20h, after finishing read/write one column data, it is incremented automatically to the
next column address. Whenever the column address pointer finishes accessing the end column address, it is
reset back to start column address and the row address is incremented to the next row.
*/
#define SSD1306_SETCOLADDR 0x21

/*
Set COM Output Scan Direction (C0h/C8h)
This command sets the scan direction of the COM output, allowing layout flexibility in the OLED module
design. Additionally, the display will show once this command is issued. For example, if this command is
sent during normal display then the graphic display will be vertically flipped immediately. Please refer to
Table 10-3 for details.
*/
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define SSD1306_I2C_DEFAULTADDRESS 0x3C

//This is intended as a minimal library to send display data to a SSD1306
//unlike https://github.com/adafruit/Adafruit_SSD1306 it does not declare a framebuffer,
//which is expensive on some systems.
class SSD1306 {
 public:
  SSD1306(uint8_t);

  void begin(TwoWire *comm, uint8_t i2caddr = SSD1306_I2C_DEFAULTADDRESS);

  void clearDisplay(void);
  void invertDisplay(uint8_t i);
 
  void startscrollright(uint8_t start, uint8_t stop);
  void startscrollleft(uint8_t start, uint8_t stop);

  void startscrolldiagright(uint8_t start, uint8_t stop);
  void startscrolldiagleft(uint8_t start, uint8_t stop);
  void stopscroll(void);

  void dimDisplay(bool dim);

  void frame( uint8_t *buffer );
  
  //Writes text to the display (directly without rendering to a framebuffer first).
  void text(const char *text, uint8_t startCol, uint8_t startRow, uint8_t lineChars, uint8_t count);

 private:
  int8_t _i2caddr, _vccstate;
  TwoWire *_wireInst;
  
  void ssd1306_command(uint8_t c);
  void ssd1306_data(uint8_t c);
  
};