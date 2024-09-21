#include <Globals.h>

class StartMenu {
  private:
    int item = 0;
    int lastOption = 1;
    bool selected = false;
    int blinkCount = 0;
    void doBlink();
    void showKO();
    void showBonus();

  public:
    void start();  //member functions
};


void StartMenu::start(){

  do{
    switch(item){
      case 0:
        showKO();
        break;
      case 1:
        showBonus();
        break;
    }

    if(digitalRead(BTN_OK) == LOW){
//      lc.setDigit(0,6,0,true);

      selected = true;
    }else if(digitalRead(BTN_PLUS) == LOW){
//      lc.setDigit(0,5,item,false); 
      item++;

      if(item > lastOption){
        item = lastOption;
      }
    }else if(digitalRead(BTN_MINUS) == LOW){
//      lc.setDigit(0,4,item,false); 
      item--;

      if(item < 0){
        item = 0;
      }
    }


    doBlink();
    delay(100);
  }while(!selected);

  lc.setDigit(0,7,item+1,false);  

  switch(item){
    case 0:
      menuKO();
      break;
    case 1:
      menuBonus();
      break;
   }
}

void StartMenu::showKO(){
  lc.setDigit(0,7,item+1,blinkCount >= 5);  
}
void StartMenu::showBonus(){
  lc.setDigit(0,7,item+1,blinkCount >= 5);  
}

void StartMenu::doBlink(){
  blinkCount++;
  if(blinkCount >= 10){
    blinkCount = 0;
  }
}




void startMenu(){
  StartMenu menu;
  menu.start();
}
