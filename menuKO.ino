#include <Globals.h>

class MenuKO {
  private:
    int item = 1;
    int lastOption = 9;
    bool selected = false;
    int blinkCount = 0;
    bool showPoint = false;
    void doBlink();
    void showOption(int opt);
    void setOption(int opt);

  public:
    void start();  //member functions
};


void MenuKO::start(){

  do{
    showOption(item);

    if(digitalRead(BTN_OK) == LOW){

      selected = true;
      delay(500);
    }else if(digitalRead(BTN_PLUS) == LOW){
      item++;

      if(item > lastOption){
        item = lastOption;
      }
      delay(500);
    }else if(digitalRead(BTN_MINUS) == LOW){
      item--;

      if(item < 0){
        item = 0;
      }
      delay(500);
    }


    doBlink();
    delay(100);
  }while(!selected);

  lc.setDigit(0,7,item+1,false);  

  setOption(item);
}

void MenuKO::showOption(int option){
  switch(option){
    case 1:
      // 5 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*5,2);
      break;
    case 2:
      // 10 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*10,2);
      break;
    case 3:
      // 15 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*15,2);
      break;
    case 4:
      // 20 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*20,2);
      break;
    case 5:
      // 25 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*25,2);
      break;
    case 6:
      // 30 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*30,2);
      break;
    case 7:
      // 45 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*45,2);
      break;
    case 8:
      // 60 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*60,2);
      break;
    case 9:
      // 90 min
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*90,2);
      break;
  }
  
}
void MenuKO::setOption(int option){
  int time_1, time_2;
  switch(option){
    case 1:
      // 5 min
      time_1 = 1000*60*5;
      time_2 = 1000*60*5;
      break;
    case 2:
      // 10 min
      time_1 = 1000*60*10;
      time_2 = 1000*60*10;
      break;
    case 3:
      // 15 min
      time_1 = 1000*60*15;
      time_2 = 1000*60*15;
      break;
    case 4:
      // 20 min
      time_1 = 1000*60*20;
      time_2 = 1000*60*20;
      break;
    case 5:
      // 25 min
      time_1 = 1000*60*25;
      time_2 = 1000*60*25;
      break;
    case 6:
      // 30 min
      time_1 = 1000*60*30;
      time_2 = 1000*60*30;
      break;
    case 7:
      // 45 min
      time_1 = 1000*60*45;
      time_2 = 1000*60*45;
      break;
    case 8:
      // 60 min
      time_1 = 1000*60*60;
      time_2 = 1000*60*60;
      break;
    case 9:
      // 90 min
      time_1 = 1000*60*90;
      time_2 = 1000*60*90;
      break;
  }

  clock_manager.setAllTimes(time_1,time_2);
  
}

void MenuKO::doBlink(){
  blinkCount++;
  if(blinkCount >= 10){
    blinkCount = 0;
    showPoint = false;
  }

  if(blinkCount >= 5){
    showPoint = true;
  }
}




void menuKO(){
  lc.clearSegment(0);
  
  MenuKO menu;
  menu.start();
}
