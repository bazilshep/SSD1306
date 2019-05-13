
//note: adapted from https://github.com/adafruit/Adafruit_SSD1306


#include <Wire.h> //i2c com
#include "glcdfont.c"
#include "SSD1306.h"

SSD1306::SSD1306(uint8_t ignored) {
  _vccstate = SSD1306_SWITCHCAPVCC;
	
}

void SSD1306::begin(TwoWire *comm, uint8_t i2caddr) {
	_wireInst = comm;
	_i2caddr = i2caddr;
	
	// Init sequence for 128x64 OLED module
    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    ssd1306_command(0x80);                                  // the suggested ratio 0x80
    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(0x3F);
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x0);                                   // no offset
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
    if (_vccstate == SSD1306_EXTERNALVCC) 
      { ssd1306_command(0x10); }
    else 
      { ssd1306_command(0x14); }
    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x00);                                  // horizontal
    ssd1306_command(SSD1306_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMSCANDEC);
    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
    if (_vccstate == SSD1306_EXTERNALVCC) 
      { ssd1306_command(0x9F); }
    else 
      { ssd1306_command(0xCF); }
    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
    if (_vccstate == SSD1306_EXTERNALVCC) 
      { ssd1306_command(0x22); }
    else 
      { ssd1306_command(0xF1); }
    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
	
	ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
	//ssd1306_command(SSD1306_DISPLAYALLON);
}

void SSD1306::invertDisplay(uint8_t i) {
  uint8_t cmd;
  if (i) {
    cmd= SSD1306_INVERTDISPLAY;
  } else {
    cmd= SSD1306_NORMALDISPLAY;
  }
  ssd1306_command(cmd);
}

void SSD1306::ssd1306_command(uint8_t c) { 
  _wireInst->beginTransmission(_i2caddr);
  
  /*
  A control byte mainly consists of Co and D/C# bits following by
  six “0” ‘s.
  
  If the Co bit is set as logic “0”, the transmission of the following
  information will contain data bytes only.
  
  The D/C# bit determines the next data byte is acted as a command
  or a data. If the D/C# bit is set to logic “0”, it defines the
  following data byte as a command. If the D/C# bit is set
  to logic “1”, it defines the following data byte as a data which
  will be stored at the GDDRAM.The GDDRAM column address pointer
  will be increased by one automatically after each data write.
  */
  _wireInst->write(0x00);
  _wireInst->write(c);
  _wireInst->endTransmission();
  //yield();
}

void SSD1306::ssd1306_data(uint8_t c) {
    _wireInst->beginTransmission(_i2caddr);
    _wireInst->write(0x40);
    _wireInst->write(c);
    _wireInst->endTransmission();
}

// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F) 
void SSD1306::startscrollright(uint8_t start, uint8_t stop){
  ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X00);
  ssd1306_command(0XFF);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F) 
void SSD1306::startscrollleft(uint8_t start, uint8_t stop){
  ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X00);
  ssd1306_command(0XFF);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F) 
void SSD1306::startscrolldiagright(uint8_t start, uint8_t stop){
  ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);  
  ssd1306_command(0X00);
  ssd1306_command(SSD1306_LCDHEIGHT);
  ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X01);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagleft
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F) 
void SSD1306::startscrolldiagleft(uint8_t start, uint8_t stop){
  ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);  
  ssd1306_command(0X00);
  ssd1306_command(SSD1306_LCDHEIGHT);
  ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X01);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

void SSD1306::stopscroll(void){
  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

// Dim the display
// dim = true: display is dimmed
// dim = false: display is normal
void SSD1306::dimDisplay(bool dim) {
  uint8_t contrast;

  if (dim) {
    contrast = 0; // Dimmed display
  } else {
    if (_vccstate == SSD1306_EXTERNALVCC) {
      contrast = 0x9F;
    } else {
      contrast = 0xCF;
    }
  }
  // the range of contrast to too small to be really useful
  // it is useful to dim the display
  ssd1306_command(SSD1306_SETCONTRAST);
  ssd1306_command(contrast);
}

//send the whole screen
void SSD1306::frame( uint8_t *buffer ) {
  /*
  Wire.beginTransmission(_i2caddr);
  Wire.write(0x80);
  Wire.write(SSD1306_COLUMNADDR);
  Wire.write(0x80);
  Wire.write(0); // Column start address (0 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_PAGEADDR);
  Wire.write(0x80);
  Wire.write(0); // Page start address (0 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_LCDHEIGHT/8-1);  // Page end address
  Wire.endTransmission();
  */
  ssd1306_command(SSD1306_COLUMNADDR);
  ssd1306_command(0);
  ssd1306_command(SSD1306_LCDWIDTH-1);
  ssd1306_command(SSD1306_PAGEADDR);
  ssd1306_command(0);
  ssd1306_command(SSD1306_LCDHEIGHT/8-1);

  for (uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
    // Send a bunch of data in one transmission.
	// can't send more than 32 bytes at once or
	// it will truncate.
    _wireInst->beginTransmission(_i2caddr);
    _wireInst->write(0x40); // D/C bit set - we are sending data.
    for (uint8_t x=0; x<16; x++) {
        _wireInst->write(buffer[i]);
        i++;
    }
    i--;
    _wireInst->endTransmission();
    //yield();
  }
}

//send the whole screen
void SSD1306::clearDisplay() {
  /*
  Wire.beginTransmission(_i2caddr);
  Wire.write(0x80);
  Wire.write(SSD1306_COLUMNADDR);
  Wire.write(0x80);
  Wire.write(0); // Column start address (0 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_PAGEADDR);
  Wire.write(0x80);
  Wire.write(0); // Page start address (0 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_LCDHEIGHT/8-1);  // Page end address
  Wire.endTransmission();
  */
  ssd1306_command(SSD1306_COLUMNADDR);
  ssd1306_command(0);
  ssd1306_command(SSD1306_LCDWIDTH-1);
  ssd1306_command(SSD1306_PAGEADDR);
  ssd1306_command(0);
  ssd1306_command(SSD1306_LCDHEIGHT/8-1);

  for (uint16_t i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
    // Send a bunch of data in one transmission.
	// can't send more than 32 bytes at once or
	// it will truncate.
    _wireInst->beginTransmission(_i2caddr);
    _wireInst->write(0x40); // D/C bit set - we are sending data.
    for (uint8_t x=0; x<16; x++) {
        _wireInst->write(0);
        i++;
    }
    i--;
    _wireInst->endTransmission();
    //yield();
  }
}

void SSD1306::text(
     const char *text, uint8_t startCol,
	 uint8_t startRow, uint8_t lineChars,
	 uint8_t count) {
  /*
  Wire.beginTransmission(_i2caddr);
  Wire.write(0x80);
  Wire.write(SSD1306_MEMORYMODE);
  Wire.write(0x80);
  Wire.write(0); //horizontal memory mode
  Wire.write(0x80);
  Wire.write(SSD1306_COLUMNADDR);
  Wire.write(0x80);
  Wire.write(startCol); // Column start address
  Wire.write(0x80);
  Wire.write(startCol + 5*lineChars); // Column end address, to line break at proper character.
  Wire.write(0x80);
  Wire.write(SSD1306_PAGEADDR);
  Wire.write(0x80);
  Wire.write(startRow); // Page start address (0 = reset)
  Wire.write(0x80);
  Wire.write(SSD1306_LCDHEIGHT/8-1);  // Page end address
  Wire.endTransmission();
  */
  ssd1306_command(SSD1306_COLUMNADDR);
  ssd1306_command(startCol);
  ssd1306_command(startCol + 6*lineChars-1);
  ssd1306_command(SSD1306_PAGEADDR);
  ssd1306_command(startRow);
  ssd1306_command(SSD1306_LCDHEIGHT/8-1);

  const char *stop= &text[count];
  _wireInst->beginTransmission(_i2caddr);
  _wireInst->write(0x40); // D/C bit set - we are sending data.
  uint8_t t=0;
  for (const char *c=text; c<stop; c++) {
	  if (t>=4) {
		_wireInst->endTransmission(); //hit send buffer limit, break here.
		t=0;
		//yield(); //incase the system has something to do.
		_wireInst->beginTransmission(_i2caddr); //continue
        _wireInst->write(0x40); // D/C bit set - we are sending data.
	  }
	  int16_t d= (int16_t)*c * 5; //the starting index into the font bitmap array.
	  _wireInst->write(pgm_read_byte(font+d));
	  _wireInst->write(pgm_read_byte(font+d+1));
	  _wireInst->write(pgm_read_byte(font+d+2));
	  _wireInst->write(pgm_read_byte(font+d+3));
	  _wireInst->write(pgm_read_byte(font+d+4));
	  _wireInst->write(0x00);
	  t++;
  }
  _wireInst->endTransmission();
  
}
