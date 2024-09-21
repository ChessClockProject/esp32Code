#include <string>
class ClockManager {
  private:
    int time_1 = 0;
    int time_2 = 0;
    int bonus_1 = 0;
    int bonus_2 = 0;
    bool is_finished = false;
    bool flag_1 = false;
    bool flag_2 = false;
    bool is_started = false;
    bool is_counting = false;
    bool is_paused = false;
    bool is_time_editing = false;
    int which_time_counting = 0;

    int pause_counter = 0;
    int edit_blink_counter = 0;
    int edit_position = 7;
    
    int ok_counter = 0;
    
    void count();
    void sub(int which);
    void blinkFinished();
    void editTime();
    std::string getTimeValues();
    std::string getTimeValue(int currentMillis);

  public:
    void setAllTimes(int time_1, int time_2);
    void setAllBonuses(int b1, int b2);
    void start(int button);
    void pause();
    void pullBtn(int button);
    void loop();
    void printTimes();
    void printTime(int currentMillis, int which);
};
