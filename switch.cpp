#include "switch.h"
#include "Arduino.h"
#include "config.h"

Switch::Switch(int buttonPin, int switchPin)
{
  this->_button_pin = buttonPin;
  this->_switch_pin = switchPin;
  
  pinMode(switchPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  this->off();
};

boolean Switch::on() {
  this->_switch_status = 1;
  digitalWrite(this->_switch_pin, SWITCH_MODE? HIGH: LOW);
};

boolean Switch::off() {
  this->_switch_status = 0;
  digitalWrite(this->_switch_pin, SWITCH_MODE? LOW: HIGH);
};

int Switch::toggle() {
  if (this->_switch_status == 1) {
    this->off();
  } else {
    this->on();
  }
  
  return this->_switch_status;
};

int Switch::getStatus() {
  return this->_switch_status;
};

void Switch::check() {
  int pressed = digitalRead(this->_button_pin);
  //int pressed = this->_button_status == HIGH? LOW: HIGH;

  if (pressed != this->_button_status && pressed == HIGH) {
      this->toggle();
  }
  this->_button_status = pressed;
};

int Switch::getSwitchPin() {
  return this->_switch_pin;
};

int Switch::getButtonPin() {
  return this->_button_pin;
}
