#include <Globals.h>

class MenuBonus {
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


void MenuBonus::start(){
  showOption(item);
  delay(500);
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

void MenuBonus::showOption(int option){
  switch(option){
    case 1:
      // 3+2
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*3 + (1000*2),2);
      break;
    case 2:
      // 5+2
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*5 + (1000*2),2);
      break;
    case 3:
      // 7+5
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*7 + (1000*5),2);
      break;
    case 4:
      // 10+5
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*10 + (1000*5),2);
      break;
    case 5:
      // 15+5
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*15 + (1000*5),2);
      break;
    case 6:
      // 20+5
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*20 + (1000*5),2);
      break;
    case 7:
      // 20+10
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*20 + (1000*10),2);
      break;
    case 8:
      // 30+30
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*30 + (1000*30),2);
      break;
    case 9:
      // 45+30
      lc.setDigit(0,7,0,false);
      lc.setDigit(0,6,item,showPoint);
      clock_manager.printTime(1000*60*45 + (1000*30),2);
      break;
    case 10:
      // 60+30
      lc.setDigit(0,7,1,false);
      lc.setDigit(0,6,0,showPoint);
      clock_manager.printTime(1000*60*60 + (1000*30),2);
      break;
  }
  
}
void MenuBonus::setOption(int option){
  int time_1, time_2;
  switch(option){
    case 1:
      // 3+2
      time_1 = 1000*60*3;
      time_2 = 1000*60*3;

      clock_manager.setAllBonuses(1000*2,1000*2);      
      break;
    case 2:
      // 5+2
      time_1 = 1000*60*5;
      time_2 = 1000*60*5;

      clock_manager.setAllBonuses(1000*2,1000*2);   
      break;
    case 3:
      // 7+5
      time_1 = 1000*60*7;
      time_2 = 1000*60*7;

      clock_manager.setAllBonuses(1000*5,1000*5); 
      break;
    case 4:
      // 10+5
      time_1 = 1000*60*10;
      time_2 = 1000*60*10;

      clock_manager.setAllBonuses(1000*5,1000*5); 
      break;
    case 5:
      // 15+5
      time_1 = 1000*60*15;
      time_2 = 1000*60*15;

      clock_manager.setAllBonuses(1000*5,1000*5);
      break;
    case 6:
      // 20+5
      time_1 = 1000*60*20;
      time_2 = 1000*60*20;

      clock_manager.setAllBonuses(1000*5,1000*5);
      break;
    case 7:
      // 20+10
      time_1 = 1000*60*20;
      time_2 = 1000*60*20;

      clock_manager.setAllBonuses(1000*10,1000*10);
      break;
    case 8:
      // 30+30
      time_1 = 1000*60*30;
      time_2 = 1000*60*30;

      clock_manager.setAllBonuses(1000*30,1000*30);
      break;
    case 9:
      // 45+30
      time_1 = 1000*60*45;
      time_2 = 1000*60*45;

      clock_manager.setAllBonuses(1000*30,1000*30);
      break;
    case 10:
      // 60+30
      time_1 = 1000*60*60;
      time_2 = 1000*60*60;

      clock_manager.setAllBonuses(1000*30,1000*30);
      break;
  }

  clock_manager.setAllTimes(time_1,time_2);
  
}

void MenuBonus::doBlink(){
  blinkCount++;
  if(blinkCount >= 10){
    blinkCount = 0;
    showPoint = false;
  }

  if(blinkCount >= 5){
    showPoint = true;
  }
}




void menuBonus(){
  lc.clearSegment(0);
  
  MenuBonus menu;
  menu.start();
}
