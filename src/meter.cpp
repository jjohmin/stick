#include "meter.h"
#include "hurdle.h"

#include <Arduino.h>

float Distance::get_distance() {
  int echo = this->echoPin;
  int trig = this->trigPin;
  float duration;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
    digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  float m = (((float)(340 * duration) / 10000) / 2) * 100;
  return m;
}

void Distance::set(){
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}