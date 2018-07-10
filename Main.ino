/**
 * 
 * Drink Machine
 * Creation Date: 07-09-2018 (mm-dd-yyyy)
 */

 void setup(void) {
  Serial.begin(115200);

  LCDInit();
  initESPInterpreter();

  setState(STATE_WAITING);
}

void loop(void) {
  loopESPInterpreter();
  LCDDRaw();
}
