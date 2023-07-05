#include "meter.h"
#include "hurdle.h"

#include <Arduino.h>
#include <limits.h>

#define PULSE_IN_TIMEOUT (50UL * 1000)
#define MAX_SENSOR_DELAY 18000
#define MAX_SENSOR_DISTANCE 500


void Distance::begin() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

#if 1
/*
pulse는 최대 38ms 지속되므로 최대 거리는 6.46[m]이다.
*/
unsigned int Distance::get_cm() {
  trigger();
  auto duration = pulseIn(echoPin, HIGH, PULSE_IN_TIMEOUT);
  // Serial.print(duration);

  if (!duration) {
    fail_dlpf = DLPF_CNT;
    // Serial.println();
    return UINT_MAX;
  }

  if (fail_dlpf) {
    --fail_dlpf;
    return UINT_MAX;
  }

  unsigned int cm = 0.017 * duration; // centi meter
  // Serial.print(' '); Serial.println(cm);
  return cm;
}
#endif

void Distance::trigger() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}