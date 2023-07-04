#include "meter.h"
#include "hurdle.h"

#include <Arduino.h>

float Distance::start_sampling() {
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trigPin, LOW);
  this->isSampling = true;
}

float Distance::get_distance(){
  float m = (((float)(340 * dura) / 10000) / 2) * 100;
  return m;
}

void Distance::polling_echo(){
  if (!this->isSampling) return;
  if (!this->echo_started) {
    if (digitalRead(this->echoPin)) {
      this->echo_start_time = micros();
      this->echo_started = true;
    }
  } else {
    if (!digitalRead(this->echoPin)) {
      this->dura = micros() - this->echo_start_time;
      this->ready = true;
      this->isSampling = false;
      this->echo_started = false;
    }
  }
}