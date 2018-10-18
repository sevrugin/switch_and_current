#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

class Switch 
{
  private:
    int _button_pin;
    int _switch_pin;
    int _switch_status;
  public:
    Switch(int buttonPin, int switchPin);
    boolean on();
    boolean off();
    int toggle();
    int getStatus();
    boolean check();
    int getSwitchPin();
};

#endif
