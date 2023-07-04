#ifndef _METER_H_
#define _METER_H_

struct Distance {
  float start_sampling();
  float get_distance();
  void polling_echo();

  int echoPin;
  int trigPin;
  int start_time;
  int echo_start_time;
  float dura;
  float meter;
  bool isSampling=false;
  bool ready = false;
  bool echo_started;
};

/*void meter_loop() {
  if (!a.isSampling) {
    a.start_sampling();
  } 
  if (a.ready) {
    float dist = a.get_distance();
  }
}

Foo a;
a.echoPin = 3;
Foo b;
b.echoPin = 7;*/

#endif /* _METER_H_ */