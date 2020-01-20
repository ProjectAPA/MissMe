#include <Arduino.h>

const int kPinBanks = 4;
const int kPinAmounts = 3;
const int kButtonInputs = 4;

const int pin_list[kPinBanks][kPinAmounts] = {{6,7,8},{18,10,11},{12,13,14},{15,16,17}};
const int button_list[kButtonInputs] = {2,3,4,5};

unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void buttonpress();

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < kButtonInputs; i++){
    pinMode(button_list[i],INPUT_PULLUP);
  }

  for(int i = 0; i < kPinBanks; i++){
    for(int j = 0; j < kPinAmounts; j++){
      Serial.println(pin_list[i][j]);
      pinMode(pin_list[i][j],OUTPUT);
    }
  }
  attachInterrupt(digitalPinToInterrupt(4),buttonpress,FALLING);
}

void loop() {
  for(int i = 0; i < kPinBanks; i++){
    for(int j = 0; j < kPinAmounts; j++){
      digitalWrite(pin_list[i][j],HIGH);
      delay(300);
      digitalWrite(pin_list[i][j],LOW);
    }
  }  
}

void buttonpress(){
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    digitalWrite(6, HIGH);
    last_button_time = button_time;
  }  

}