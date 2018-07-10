/**
 * 
 * Nokia5110 screen
 * The base hasn't been created by me
 * 
 * Drink Machine
 * Creation Date: 07-09-2018 (mm-dd-yyyy)
 */


void LCDDRaw(void){
  if(!lcd_stateChanged) return;
  
  LCDClear();

  switch(state){
    case STATE_WAITING:
    Serial.println(authCode);
    LCDString(strcat("Wartend                 Code: ", authCode));
    break;
  }

  lcd_stateChanged = false;
}

void gotoXY(int x, int y) {
  LCDWrite(0, 0x80 | x);
  LCDWrite(0, 0x40 | y);
}

void LCDBitmap(char *my_array[]){
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, my_array[index]);
}

void LCDCharacter(char character) {
  LCDWrite(LCD_DATA, 0x00);
  
  for (int index = 0; index < 5; index++)
    LCDWrite(LCD_DATA, LCD_ASCII[character - 0x20][index]);

  LCDWrite(LCD_DATA, 0x00);
}

void LCDString(char *characters) {
  while (*characters)
    LCDCharacter(*characters++);
}

void LCDClear(void) {
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, 0x00);
    
  gotoXY(0, 0);
}

void LCDInit(void) {
  //Configure control pins
  pinMode(LCD_PIN_SCE, OUTPUT);
  pinMode(LCD_PIN_RESET, OUTPUT);
  pinMode(LCD_PIN_DC, OUTPUT);
  pinMode(LCD_PIN_SDIN, OUTPUT);
  pinMode(LCD_PIN_SCLK, OUTPUT);

  //Reset the LCD to a known state
  digitalWrite(LCD_PIN_RESET, LOW);
  digitalWrite(LCD_PIN_RESET, HIGH);

  LCDWrite(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
  LCDWrite(LCD_COMMAND, 0xB0); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  LCDWrite(LCD_COMMAND, 0x04); //Set Temp coefficent
  LCDWrite(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14

  LCDWrite(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  LCDWrite(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse
}

void LCDWrite(byte data_or_command, byte data) {
  digitalWrite(LCD_PIN_DC, data_or_command); //Tell the LCD that we are writing either to data or a command

  //Send the data
  digitalWrite(LCD_PIN_SCE, LOW);
  shiftOut(LCD_PIN_SDIN, LCD_PIN_SCLK, MSBFIRST, data);
  digitalWrite(LCD_PIN_SCE, HIGH);
}
