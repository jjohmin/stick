#if 1

#include <Arduino.h>

#include "hurdle.h"
#include "miss.h"
#include "pins.h"

void setup() {
  Serial.begin(9600);
  miss_begin();
  hurdle_start();
}

void loop() {
  hurdle_loop();
  // miss_loop();
  // Serial.println(digitalRead(PIN_BUTTON));
#if 0
  if (!digitalRead(PIN_BUTTON)) {
    tone(PIN_BUZZER, 349);
    delay(500);
    tone(PIN_BUZZER, 600, 500);
  }
#endif
}

#endif