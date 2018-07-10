/**
 * 
 * Drink Machine
 * Creation Date: 07-09-2018 (mm-dd-yyyy)
 */

void randomSeed(void){
  randomSeed(analogRead(0));
}

void setState(byte newState){
  if(state != newState){
    lcd_stateChanged = true;
    
    if(newState == STATE_WAITING){
      randomSeed();
      
      for(int i=0; i<sizeof(authCode)-1; i++)
        authCode[i] = random(9)+'0';
    }
  }
  
  state = newState;
}
