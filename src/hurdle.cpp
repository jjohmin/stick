#include "hurdle.h"

#include <Arduino.h>
#include "meter.h"
#include "miss.h"
#include "pins.h"
#include <limits.h>

#define INTERVAL_MS 50 

static void hurdle_hendler(unsigned int cm);

static constexpr const unsigned int HURDLE_THRESHOLD = 100; // cm
static constexpr const unsigned long TONE_DURATION = 500;
static constexpr const unsigned int BUZZER_MIN_FREQ = 400;
static constexpr const unsigned int BUZZER_MAX_FREQ = 1500;

static Distance front(ULTRASONIC_ECHO, ULTRASONIC_TRIG);

static int Buzzer = 7;
static bool is_first = true;
static unsigned int prev_cm;

static inline
unsigned int cm2freq(unsigned int cm) {
  return BUZZER_MAX_FREQ - map(cm, 0, 100, BUZZER_MAX_FREQ - BUZZER_MIN_FREQ, BUZZER_MAX_FREQ);
}

void hurdle_start() {
  front.begin();
  pinMode(Buzzer, OUTPUT);
}

void hurdle_reset() {
  is_first = true;
  prev_cm = UINT_MAX;
}

void hurdle_loop() {
  if (miss_is_cane()) {
    hurdle_reset();
    return;
  }

  static unsigned long prev_ms;
  auto curr_ms = millis();
  if (curr_ms - prev_ms < INTERVAL_MS) return;
  prev_ms = curr_ms;

  auto cm = front.get_cm();
  // Serial.println(cm);
  hurdle_hendler(cm);
}

static
void hurdle_hendler(unsigned int cm) {
  if (cm > HURDLE_THRESHOLD) {
    if (!is_first) {
      noTone(PIN_BUZZER);
      hurdle_reset();
    }
    return;
  }

  if (!(is_first || cm + 5 < prev_cm)) return;
  is_first = false;
  prev_cm = cm;
  tone(PIN_BUZZER, cm2freq(cm), TONE_DURATION);
}

#if 0
static
void hurdle_hendler(int meter) {
  int m = meter;

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
}
#endif