#include "switch.h"
#include <Arduino.h>


Switch switches[] = {
  Switch(0,13)
};

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}

void loop() {
  String input;
  while(Serial.available()) {
      input = Serial.readString();// read the incoming data as string
      parseCommand(input);
  }
  delay(100);
}

void parseCommand(String input) {
  String command;
  String param1, param2;
  int length = input.length();
  
  String _str;
  char c;
  int i = 0;
  while(i < length) {
    c = input[i];
    if (c != ' ' && c != '\n') {
      _str += c;
    };
    if ((i+1 == length || c == ' ') && _str.length() > 0) {
      if (command.length() == 0) {
        command = _str;
      } else if (param1.length() == 0) {
        param1 = _str;
      } else if (param2.length() == 0) {
        param2 = _str;
        break;
      }
      _str = "";
    }
    i++;
  };
  Serial.println("# "+command+":"+param1+":"+param2);
  
  // do command
  if (command == "help") {
      printHelp();
  } else if (command == "toggle") {
      toggle(param1.toInt());
  } else if (command == "on") {
      on(param1.toInt());
  } else if (command == "off") {
      off(param1.toInt());
  } else if (command == "status") {
      int st = getStatus(param1.toInt());
      Serial.print("status: ");
      Serial.println(st);
  } else {
      Serial.println("Unknown command: " + command);
  }
}

void toggle(int pin)
{
  int index = switchIndex(pin);
  switches[index].toggle();
  Serial.println("toggle: ok");
}

void on(int pin)
{
  int index = switchIndex(pin);
  switches[index].on();
  Serial.println("on: ok");
}

void off(int pin)
{
  int index = switchIndex(pin);
  switches[index].off();
  Serial.println("off: ok");
}

int getStatus(int pin)
{
  int index = switchIndex(pin);
  return switches[index].getStatus();
}

int switchIndex(int pin) {
  for (int i = 0; i < sizeof(switches); i++) {
    if (switches[i].getSwitchPin() == pin) {
      return i;
    }
  }
  Serial.println("Switch not found");
}

void printHelp()
{
  Serial.println("help - display this help");
  Serial.println("on N - switch ON pin N");
  Serial.println("off N - switch OFF pin N");
  Serial.println("toggle N - toggle switch N");
  Serial.println("status N - get status of N switch");
}
