#include "ClockManager.h"
#include <Globals.h>
#include <Arduino.h>  // Inclua o cabeçalho Arduino.h para usar o Serial


void ClockManager::setAllTimes(int time1, int time2){
  time_1 = time1;
  time_2 = time2;

  printTimes();
}
void ClockManager::setAllBonuses(int b1, int b2){
  bonus_1 = b1;
  bonus_2 = b2;
}

void ClockManager::start(int button){
  if(SERIAL_ENABLED) Serial.print("ClockManager::start(");
  if(SERIAL_ENABLED) Serial.print(button);
  if(SERIAL_ENABLED) Serial.println(")");
  if(button == 1){
    which_time_counting = 2;
    is_started = true;
    is_counting = true;

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    
    if(SERIAL_ENABLED) Serial.print("started couting 2");
  }else{
    which_time_counting = 1;
    is_started = true;
    is_counting = true;

    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW );
    
    if(SERIAL_ENABLED) Serial.print("started couting 1");
  }
}

void ClockManager::pause(){
  is_counting = false;
  is_paused = true;

  pause_counter = 0;
  ok_counter = 0;
}

void ClockManager::pullBtn(int button){
  if(SERIAL_ENABLED) Serial.print("ClockManager::pullBtn(");
  if(SERIAL_ENABLED) Serial.print(button);
  if(SERIAL_ENABLED) Serial.println(")");

  if(!is_started){
    return ClockManager::start(button);
  }
  
  is_counting = true;
  is_paused = false;
  
  if(button == 1){
    if(which_time_counting == 1){
      time_1 = time_1 + bonus_1;
    }
    
    which_time_counting = 2;

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
  }else{
    if(which_time_counting == 2){
      time_2 = time_2 + bonus_2;
    }
    
    which_time_counting = 1;

    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
  }
}
void ClockManager::count(){
  if(SERIAL_ENABLED) Serial.println("--clock--");
  if(which_time_counting > 0){
    switch(which_time_counting){
      case 1:
        sub(1);
        break;
      case 2:
        sub(2);
        break;
    }

    printTime(time_1,1);
    if(SERIAL_ENABLED) Serial.print(" - ");
    printTime(time_2,2);
    if(SERIAL_ENABLED) Serial.println("");
  } 
}
void ClockManager::sub(int which){
  if(which == 1){
    time_1 = time_1 - 100;
    if(time_1 < 0){
      time_1 = 0;
  
      which_time_counting = 0;
      is_finished = true;
      flag_1 = true;
    }  
  }else{
    time_2 = time_2 - 100;
    if(time_2 < 0){
      time_2 = 0;
  
      which_time_counting = 0;
      is_finished = true;
      flag_2 = true;
    }  
  } 
}

void ClockManager::loop(){
  if(SERIAL_ENABLED) Serial.println("ClockManager::loop");
  if(is_finished){
    blinkFinished();
  }else{
    if(is_started && is_counting){
      if(SERIAL_ENABLED) Serial.println("is_started && is_counting");
      count();
    }

    if(is_paused){
      pause_counter++;
      if(pause_counter <= 7){
        if(SERIAL_ENABLED) Serial.println("PAUSED = PRINT");
        printTimes();
      }else{
        if(SERIAL_ENABLED) Serial.println("PAUSED = CLEAR");
        lc.clearSegment(0);
      }

      if(pause_counter >= 14){
        pause_counter = 0;
      }
      if(digitalRead(BTN_OK) == LOW){
        ok_counter++;
        delay(500);
      }

      if(ok_counter >= 3){
        ok_counter = 0;
        editTime();  
      }
    }
  
    if(digitalRead(BTN_1) == LOW){
      if(SERIAL_ENABLED) Serial.println("BTN_1 == LOW");
      pullBtn(1);
    }
  
    if(digitalRead(BTN_2) == LOW){
      if(SERIAL_ENABLED) Serial.println("BTN_2 == LOW");
      pullBtn(2);
    }
  
    if(digitalRead(BTN_OK) == LOW){
      if(SERIAL_ENABLED) Serial.println("BTN_OK == LOW");
      if(is_started && is_counting){
        pause();
      }
    }
    
  }

  if(is_started && SERIAL_ENABLED){
    delay(95);
  }else{
    delay(100);
  }
}

void ClockManager::editTime(){
  bool is_finished = false;
  bool is_time_editing = true;

  edit_position = 7;

  while(!is_finished){
    lc.clearSegment(0);
    
    if(edit_position >= 4){
      printTime(time_2,2);
    }else{
      printTime(time_1,1);
    }

    if(edit_blink_counter++ < 3){
      if(edit_position >= 4){
        printTime(time_1,1);
      }else{
        printTime(time_2,2);
      }
    }else{
      if(edit_position >= 4){
        std::string t = getTimeValue(time_1);

        
        if(edit_position != 7) lc.setDigit(0,7,t[0],false);
        if(edit_position != 6) lc.setDigit(0,6,t[1],false);
        if(edit_position != 5) lc.setDigit(0,5,t[2],false);
        if(edit_position != 4) lc.setDigit(0,4,t[3],false);
      }else{
        std::string t = getTimeValue(time_2);

        
        if(edit_position != 3) lc.setDigit(0,3,t[0],false);
        if(edit_position != 2) lc.setDigit(0,2,t[1],false);
        if(edit_position != 1) lc.setDigit(0,1,t[2],false);
        if(edit_position != 0) lc.setDigit(0,0,t[3],false);
      }
    }

    if(digitalRead(BTN_OK) == LOW){
      if(edit_position <= 0){
        is_time_editing = false;  
        is_finished = true;

        printTimes();
      }else{
        edit_position--;
      }

      delay(500);
    }

    if(digitalRead(BTN_PLUS) == LOW){
      if(edit_position >= 4){
        std::string t = getTimeValue(time_1);
        if(time_1 >= (1000*60*60)){
          // HH:MM
          switch(edit_position){
            case 7:
              if(t[0] == '9'){
                time_1 = time_1 - (1000*60*60*99); // -100 hours  
              }else{
                time_1 = time_1 + (1000*60*60*10); // +10 hour
              }
              break;
            case 6:
              if(t[1] == '9'){
                time_1 = time_1 - (1000*60*60*9); // -10 hours  
              }else{
                time_1 = time_1 + (1000*60*60); // +1 hour
              }
              break;
            case 5:
              if(t[2] == '5'){
                time_1 = time_1 - (1000*60*59); // -60 minutes  
              }else{
                time_1 = time_1 + (1000*60*10); // +10 minutes
              }
              break;
            case 4:
              if(t[3] == '9'){
                time_1 = time_1 - (1000*60*9); // -10 minutes  
              }else{
                time_1 = time_1 + (1000*60); // +1 minute
              }
              break;
          }
        }else{
          // MM:SS
          switch(edit_position){
            case 7:
              if(t[0] == '5'){
                time_1 = time_1 - (1000*60*50); // -60 minutes  
              }else{
                time_1 = time_1 + (1000*60*10); // +10 minutes
              }
              break;
            case 6:
              if(t[1] == '9'){
                time_1 = time_1 - (1000*60*9); // -10 minutes  
              }else{
                time_1 = time_1 + (1000*60); // +1 minute
              }
              break;
            case 5:
              if(t[2] == '5'){
                time_1 = time_1 - (1000*59); // -60 seconds  
              }else{
                time_1 = time_1 + (1000*10); // +10 seconds
              }
              break;
            case 4:
              if(t[3] == '9'){
                time_1 = time_1 - (1000*9); // -10 seconds  
              }else{
                time_1 = time_1 + (1000); // +1 second
              }
              break;
          }
        }
      }else{
        std::string t = getTimeValue(time_2);
        if(time_1 >= (1000*60*60)){
          // HH:MM
          switch(edit_position){
            case 3:
              if(t[0] == '9'){
                time_2 = time_2 - (1000*60*60*99); // -100 hours  
              }else{
                time_2 = time_2 + (1000*60*60*10); // +10 hour
              }
              break;
            case 2:
              if(t[1] == '9'){
                time_2 = time_2 - (1000*60*60*9); // -10 hours  
              }else{
                time_2 = time_2 + (1000*60*60); // +1 hour
              }
              break;
            case 1:
              if(t[2] == '5'){
                time_2 = time_2 - (1000*60*59); // -60 minutes  
              }else{
                time_2 = time_2 + (1000*60*10); // +10 minutes
              }
              break;
            case 0:
              if(t[3] == '9'){
                time_2 = time_2 - (1000*60*9); // -10 minutes  
              }else{
                time_2 = time_2 + (1000*60); // +1 minute
              }
              break;
          }
        }else{
          // MM:SS
          switch(edit_position){
            case 3:
              if(t[0] == '5'){
                time_2 = time_2 - (1000*60*59); // -60 minutes  
              }else{
                time_2 = time_2 + (1000*60*10); // +10 minutes
              }
              break;
            case 2:
              if(t[1] == '9'){
                time_2 = time_2 - (1000*60*9); // -10 minutes  
              }else{
                time_2 = time_2 + (1000*60); // +1 minute
              }
              break;
            case 1:
              if(t[2] == '5'){
                time_2 = time_2 - (1000*59); // -60 seconds  
              }else{
                time_2 = time_2 + (1000*10); // +10 seconds
              }
              break;
            case 0:
              if(t[3] == '9'){
                time_2 = time_2 - (1000*9); // -10 seconds  
              }else{
                time_2 = time_2 + (1000); // +1 second
              }
              break;
          }
        }
      }

      delay(500);
    }

    if(digitalRead(BTN_MINUS) == LOW){
      if(edit_position >= 4){
        std::string t = getTimeValue(time_1);
        if(time_1 >= (1000*60*60)){
          // HH:MM
          switch(edit_position){
            case 7:
              if(t[0] == '0'){
                time_1 = time_1 + (1000*60*60*99); // -100 hours  
              }else{
                time_1 = time_1 - (1000*60*60*10); // +10 hour
              }
              break;
            case 6:
              if(t[1] == '0'){
                time_1 = time_1 + (1000*60*60*9); // -10 hours  
              }else{
                time_1 = time_1 - (1000*60*60); // +1 hour
              }
              break;
            case 5:
              if(t[2] == '0'){
                time_1 = time_1 + (1000*60*59); // -60 minutes  
              }else{
                time_1 = time_1 - (1000*60*10); // +10 minutes
              }
              break;
            case 4:
              if(t[3] == '0'){
                time_1 = time_1 + (1000*60*9); // -10 minutes  
              }else{
                time_1 = time_1 - (1000*60); // +1 minute
              }
              break;
          }
        }else{
          // MM:SS
          switch(edit_position){
            case 7:
              if(t[0] == '0'){
                time_1 = time_1 + (1000*60*50); // -60 minutes  
              }else{
                time_1 = time_1 - (1000*60*10); // +10 minutes
              }
              break;
            case 6:
              if(t[1] == '0'){
                time_1 = time_1 + (1000*60*9); // -10 minutes  
              }else{
                time_1 = time_1 - (1000*60); // +1 minute
              }
              break;
            case 5:
              if(t[2] == '0'){
                time_1 = time_1 + (1000*59); // -60 seconds  
              }else{
                time_1 = time_1 - (1000*10); // +10 seconds
              }
              break;
            case 4:
              if(t[3] == '0'){
                time_1 = time_1 + (1000*9); // -10 seconds  
              }else{
                time_1 = time_1 - (1000); // +1 second
              }
              break;
          }
        }
      }else{
        std::string t = getTimeValue(time_2);
        if(time_1 >= (1000*60*60)){
          // HH:MM
          switch(edit_position){
            case 3:
              if(t[0] == '0'){
                time_2 = time_2 + (1000*60*60*99); // -100 hours  
              }else{
                time_2 = time_2 - (1000*60*60*10); // +10 hour
              }
              break;
            case 2:
              if(t[1] == '0'){
                time_2 = time_2 + (1000*60*60*9); // -10 hours  
              }else{
                time_2 = time_2 - (1000*60*60); // +1 hour
              }
              break;
            case 1:
              if(t[2] == '0'){
                time_2 = time_2 + (1000*60*59); // -60 minutes  
              }else{
                time_2 = time_2 - (1000*60*10); // +10 minutes
              }
              break;
            case 0:
              if(t[3] == '0'){
                time_2 = time_2 + (1000*60*9); // -10 minutes  
              }else{
                time_2 = time_2 - (1000*60); // +1 minute
              }
              break;
          }
        }else{
          // MM:SS
          switch(edit_position){
            case 3:
              if(t[0] == '0'){
                time_2 = time_2 + (1000*60*59); // -60 minutes  
              }else{
                time_2 = time_2 - (1000*60*10); // +10 minutes
              }
              break;
            case 2:
              if(t[1] == '0'){
                time_2 = time_2 + (1000*60*9); // -10 minutes  
              }else{
                time_2 = time_2 - (1000*60); // +1 minute
              }
              break;
            case 1:
              if(t[2] == '0'){
                time_2 = time_2 + (1000*59); // -60 seconds  
              }else{
                time_2 = time_2 - (1000*10); // +10 seconds
              }
              break;
            case 0:
              if(t[3] == '0'){
                time_2 = time_2 + (1000*9); // -10 seconds  
              }else{
                time_2 = time_2 - (1000); // +1 second
              }
              break;
          }
        }
      }

      delay(500);
    }

    if(edit_blink_counter >= 6){
      edit_blink_counter = 0;
    }
    
    delay(100);
  }
  
}

std::string ClockManager::getTimeValues(){
//  printTime(time_1,1);
//  printTime(time_2,2);

  return getTimeValue(time_1)+""+getTimeValue(time_2);
}
void ClockManager::printTimes(){
  printTime(time_1,1);
  printTime(time_2,2);
}

std::string ClockManager::getTimeValue(int currentMillis){
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int v4 = 0;

  if(hours > 0){
    if(hours < 10){
      v2 = hours;  
    }
    if(hours >= 10){
      v2 = hours % 10;  
      v1 = (hours - v2)/10; 
    }
    if(minutes < 10){
      v4 = minutes;  
    }
    if(minutes >= 10){
      v4 = minutes % 10; 
      v3 = (minutes - v4)/10;  
    }
  }else{
    if(minutes < 10){
      v2 = minutes;  
    }
    if(minutes >= 10){
      v2 = minutes % 10;  
      v1 = (minutes - v2)/10; 
    }
    if(seconds < 10){
      v4 = seconds;  
    }
    if(seconds >= 10){
      v4 = seconds % 10; 
      v3 = (seconds - v4)/10;  
    }
  }

  std::string retorno = std::to_string(v1) + std::to_string(v2) + std::to_string(v3) + std::to_string(v4);

  return retorno;
}

void ClockManager::printTime(int currentMillis, int which){
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int v4 = 0;

  bool point1 = false;
  bool point2 = false;
  bool point3 = false;
  bool point4 = false;

  if(hours > 0){
    if(hours < 10){
      v2 = hours;  
    }
    if(hours >= 10){
      v2 = hours % 10;  
      v1 = (hours - v2)/10; 
    }
    if(minutes < 10){
      v4 = minutes;  
    }
    if(minutes >= 10){
      v4 = minutes % 10; 
      v3 = (minutes - v4)/10;  
    }
    
    if(which_time_counting == which && is_counting){
      if(seconds % 2 == 0){
        point2 = true;
      }
    }else{
      point2 = true;
    }
  }else{
    if(minutes < 10){
      v2 = minutes;  
    }
    if(minutes >= 10){
      v2 = minutes % 10;  
      v1 = (minutes - v2)/10; 
    }
    if(seconds < 10){
      v4 = seconds;  
    }
    if(seconds >= 10){
      v4 = seconds % 10; 
      v3 = (seconds - v4)/10;  
    }
  }

  if(which == 1){
     lc.setDigit(0,7,v1,point1);
     lc.setDigit(0,6,v2,point2);
     lc.setDigit(0,5,v3,point3);
     lc.setDigit(0,4,v4,point4);
  }else{
     lc.setDigit(0,3,v1,point1);
     lc.setDigit(0,2,v2,point2);
     lc.setDigit(0,1,v3,point3);
     lc.setDigit(0,0,v4,point4);
  }

  if(SERIAL_ENABLED) Serial.print(hours);
  if(SERIAL_ENABLED) Serial.print(":");
  if(SERIAL_ENABLED) Serial.print(minutes);
  if(SERIAL_ENABLED) Serial.print(":");
  if(SERIAL_ENABLED) Serial.print(seconds);
  if(SERIAL_ENABLED) Serial.print(".");
  if(SERIAL_ENABLED) Serial.print(currentMillis);
}

void ClockManager::blinkFinished(){
  if(is_finished){
    if(flag_1){
      digitalWrite(LED_2,LOW);

      if(digitalRead(LED_1) == LOW){
        digitalWrite(LED_1,HIGH);
      }else{
        digitalWrite(LED_1,LOW);
      }
    }else{
      digitalWrite(LED_1,LOW);

      if(digitalRead(LED_2) == LOW){
        digitalWrite(LED_2,HIGH);
      }else{
        digitalWrite(LED_2,LOW);
      }
    }
  }
}

//void clock_loop(){
//  clock_manager.loop();
//}
//void clock_set_time(int time, int witch){
//  clock.setTime(time,witch);
//}
//void clock_set_all_times(int t1, int t2){
//  clock.setAllTimes(t1,t2);
//}
