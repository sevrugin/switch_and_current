#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

class Switch 
{
  private:
    int _button_pin;
    int _switch_pin;
    int _switch_status;
    int _button_status = 0;
  public:
    Switch(int buttonPin, int switchPin);
    boolean on();
    boolean off();
    int toggle();
    int getStatus();
    void check();
    int getSwitchPin();
    int getButtonPin();
};

#endif
