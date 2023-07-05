#if 0

#include <Arduino.h>

#include "hurdle.h"
#include "miss.h"
#include "pins.h"
#include "meter.h"

static Distance front(ULTRASONIC_ECHO, ULTRASONIC_TRIG);

void setup() {
  Serial.begin(9600);
  // miss_begin();
  // hurdle_start();
}

void loop() {
    Serial.println(front.get_cm());
    delay(500);
}

#endif