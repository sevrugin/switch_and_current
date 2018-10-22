#include "config.h"
#include "switch.h"
#include <Arduino.h>
#include <Wire.h> 


Switch switches[] = {
  Switch(4, 2),
  Switch(5, 3),
  Switch(6, 30),
  Switch(7, 8),
  Switch(10, 29),
  Switch(11, 28),
  Switch(12, 27),
  Switch(13, 26)
};

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  Wire.begin(I2C_ARRDESS);                // join i2c bus with address #2 
  // Wire.onRequest(requestEvents);
  // Wire.onReceive(receiveEvents);
}

void loop() {
  String input;
  while(Serial.available()) {
      input = Serial.readString();// read the incoming data as string
      parseCommand(input);
  }
  checkAll();
  
  delay(100);
}

void checkAll() {
  int count = sizeof(switches) / sizeof(Switch);
  for (int i = 0; i < count; i++) {
    switches[i].check();
  }  
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
  } else if (command == "list") {
      printList();
  } else if (command == "i2c") {
      Serial.println(getI2CStatus());
  } else if (command == "toggle") {
      toggle(param1.toInt()-1);
  } else if (command == "on") {
      on(param1.toInt()-1);
  } else if (command == "off") {
      off(param1.toInt()-1);
  } else if (command == "status") {
      int st = getStatus(param1.toInt()-1);
      Serial.print("status: ");
      Serial.println(st);
  } else {
      Serial.println("Unknown command: " + command);
  }
}

void toggle(int index)
{
  switches[index].toggle();
  Serial.println("toggle: ok");
}

void on(int index)
{
  switches[index].on();
  Serial.println("on: ok");
}

void off(int index)
{
  switches[index].off();
  Serial.println("off: ok");
}

int getStatus(int index)
{
  return switches[index].getStatus();
}

String getI2CStatus() {
  String result;
  
  char b[8];
  int count = sizeof(switches) / sizeof(Switch);
  for (int i = 0; i < 8; i++) {
    if (i >= count) {
      b[i] = 0;
    } else {
      b[i] = switches[i].getStatus();
    }
  }  
  result = b;
  
  int value = 1022;
  byte highbyte=value>>8; //shift right 8 bits, leaving only the 8 high bits. 
  byte lowbyte=value & 0xFF; //bitwise AND with 0xFF  
  result += char(highbyte);
  result += char(lowbyte);
  
  return result;
}

void printList() {
  Serial.println("index\t| button pin\t| switch pin\t| status");
  int count = sizeof(switches) / sizeof(Switch);
  for (int i = 0; i < count; i++) {
    Serial.print(i+1);
    Serial.print("\t| ");
    Serial.print(switches[i].getButtonPin());
    Serial.print("\t\t| ");
    Serial.print(switches[i].getSwitchPin());
    Serial.print("\t\t| ");
    Serial.println(switches[i].getStatus()? 'on': 'off');
  }  
}
  

void printHelp()
{
  Serial.println("help - display this help");
  Serial.println("list - display list of switches");
  Serial.println("on N - switch ON switch N");
  Serial.println("off N - switch OFF switch N");
  Serial.println("toggle N - toggle switch N");
  Serial.println("status N - get status of N switch");
  Serial.println("i2c - get status in i2c format");
}


