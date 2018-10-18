#include "switch.h"
#include "Arduino.h"

Switch::Switch(int buttonPin, int switchPin)
{
  this->_button_pin = buttonPin;
  this->_switch_pin = switchPin;
  pinMode(switchPin, OUTPUT);
  this->off();
};

boolean Switch::on() {
  this->_switch_status = 1;
  digitalWrite(this->_switch_pin, HIGH);
};

boolean Switch::off() {
  this->_switch_status = 0;
  digitalWrite(this->_switch_pin, LOW);
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

boolean Switch::check() {};

int Switch::getSwitchPin() {
  return this->_switch_pin;
};
