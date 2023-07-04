#include <Arduino.h>
#include "hurdle.h"

static
void hurdle_hendler(int meter);
static Distance front;
static int Buzzer = 7;

void hurdle_start(){
  front.trigPin = 3;
  front.echoPin = 4;
  front.set();
  pinMode(Buzzer,OUTPUT);
}

void hurdle_loop(){
  float meter = front.get_distance();
  hurdle_hendler(meter);
}

static
void hurdle_hendler(int meter) {
  int m = meter;
  static int time = 0;

  if(m<=10){
    noTone(Buzzer);
    tone(Buzzer,349,500);
  }
  else if(m<=7){
    noTone(Buzzer);
    tone(Buzzer,393,500);
  }
  else if(m<=5){
    noTone(Buzzer);
    tone(Buzzer,440,500);
  }
  else if(m<=3){
    noTone(Buzzer);
    tone(Buzzer,494,500);
  }
  else if(m<=1 && m!=0){
    noTone(Buzzer);
    tone(Buzzer,523,500);
}