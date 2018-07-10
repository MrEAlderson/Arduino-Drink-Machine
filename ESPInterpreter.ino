/**
 * 
 * Drink Machine
 * Creation Date: 07-10-2018 (mm-dd-yyyy)
 */

SoftwareSerial espSerial(10, 11);

void initESPInterpreter(void) {
  espSerial.begin(9600);
}

void loopESPInterpreter(void) {
  if ( espSerial.available() ) { Serial.write( espSerial.read() ); }
  if ( Serial.available() ) { espSerial.write( Serial.read() ); }
}

