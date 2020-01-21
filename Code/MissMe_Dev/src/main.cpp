#include <Arduino.h>

const int kPinBanks = 4;
const int kPinAmounts = 3;
const int kButtonInputs = 4;

const int pin_list[kPinBanks][kPinAmounts] = {{6,7,8},{18,10,11},{12,13,14},{15,16,17}};
const int button_list[kButtonInputs] = {2,3,4,5};

unsigned long button_time = 0;  
unsigned long last_button_time = 0; 
volatile bool button_press_flag = true;

void ButtonDebounce();
void PciInit();

void setup() {
  PciInit();
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
}

ISR (PCINT2_vect){
  ButtonDebounce();
}

void loop() {
  for(int i = 0; i < kPinBanks; i++){
    for(int j = 0; j < kPinAmounts; j++){
      digitalWrite(pin_list[i][j],HIGH);
      while(1){
        if (button_press_flag == true) break;
      }      
      delay(300);
      digitalWrite(pin_list[i][j],LOW);
    }
  }
}

void ButtonDebounce(){
  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    if (button_press_flag == true){
      button_press_flag = false;
    }
    else{
      button_press_flag = true;
    }
    last_button_time = button_time;
  }  
}

void PciInit(){
  cli();
  PCICR |= (1UL << PCIE2);
  PCMSK2 |= (1UL << PCINT18) | (1UL << PCINT19) | (1UL << PCINT20) | (1UL << PCINT21);
  sei();
}
