#include <Globals.h>

void showStart(){
  digitalWrite(LED_1,HIGH);
  digitalWrite(LED_2,HIGH);
  
  delay(100);
  for(int i = 0; i < 8; i++){
    lc.setDigit(0,i,0,true);
    delay(100);
  }
  lc.clearSegment(0);
  delay(300);
  for(int i = 3; i >= 0; i--){
    for(int i = 0; i < 8; i++){
      lc.setDigit(0,i,0,true);
    }
    digitalWrite(LED_1,HIGH);
    digitalWrite(LED_2,HIGH);
    delay(300);
    lc.clearSegment(0);
    digitalWrite(LED_1,LOW);
    digitalWrite(LED_2,LOW);
    delay(300);
  }
}
