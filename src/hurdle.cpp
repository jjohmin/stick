#include <Arduino.h>
#include "hurdle.h"

static
void hurdle_hendler(int meter);
static Distance front;

void hurdle_start(){
  front.trigPin = 3;
  front.echoPin = 4;
  static int Buzzer = 7;
  pinMode(Buzzer,OUTPUT);
}

float hurdle_loop(){
  if(!front.isSampling){
    front.start_sampling();
  }
  front.polling_echo();
  if(front.ready){
    float meter = front.get_distance();
    hurdle_hendler(meter);
  }
}

static
void hurdle_hendler(int meter) {
  int m = meter;
  static int Buzzer = 7;
  static int time = 0;
  if(m<=10){
    tone(Buzzer,349);
    if(millis()-time>500){
      time=millis();
      noTone(Buzzer);
    }
  }
  else if(m<=7){
    tone(Buzzer,393);
    if(millis()-time>500){
      time=millis();
      noTone(Buzzer);
    }
  }
  else if(m<=5){
    tone(Buzzer,440);
    if(millis()-time>500){
      time=millis();
      noTone(Buzzer);
    }
  }
  else if(m<=3){
    tone(Buzzer,494);
    if(millis()-time>500){
      time=millis();
      noTone(Buzzer);
    }
  }
  else if(m<=1){
    tone(Buzzer,523);
    if(millis()-time>500){
      time=millis();
      noTone(Buzzer);
    }
  }
}