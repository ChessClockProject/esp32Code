#include <ClockManager.h>
#include <Globals.h>
//#include "LedController.hpp"


// Criação de uma instância global da classe Clock
ClockManager clock_manager;

// the setup function runs once when you press reset or power the board

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_1, OUTPUT);  
  pinMode(LED_2, OUTPUT);
  pinMode(LED_TURNON, OUTPUT);

  pinMode(BTN_1,INPUT_PULLUP);
  pinMode(BTN_2,INPUT_PULLUP);
  
  pinMode(BTN_PLUS,INPUT_PULLUP);
  pinMode(BTN_MINUS,INPUT_PULLUP);
  pinMode(BTN_OK,INPUT_PULLUP);

  if(SERIAL_ENABLED) Serial.begin(9600);

  
  //Here a new LedController object is created without hardware SPI.
  lc=LedController<1,1>(DIN,CLK,CS);
  lc.setIntensity(8); /* Set the brightness to a medium values */
  lc.clearMatrix(); /* and clear the display */


  showStart();

  digitalWrite(LED_TURNON, HIGH);
  
  startMenu();
}

















// the loop function runs over and over again forever
void loop() {  
  clock_manager.loop();
}

//void sub1(){
//  time_1 = time_1 - 100;
//  if(time_1 < 0){
//    time_1 = 0;
//
//    which_counting = 0;
//  }  
//}
//
//void sub2(){
//  time_2 = time_2 - 100;
//  if(time_2 < 0){
//    time_2 = 0;
//
//    which_counting = 0;
//  }  
//}

//void btn1(){
//  digitalWrite(LED_2, LOW);
//  digitalWrite(LED_1, HIGH);   // turn the LED on (HIGH is the voltage level)
//
//  if(SERIAL_ENABLED) Serial.println(1);
//
// which_counting = 2;
//}
//void btn2(){
//  digitalWrite(LED_2, HIGH);
//  digitalWrite(LED_1, LOW);   // turn the LED on (HIGH is the voltage level)
//
//  if(SERIAL_ENABLED) Serial.println(2);
//
//  
//
// which_counting = 1;
//}

void printTime(int currentMillis, int which){
  
  
}
