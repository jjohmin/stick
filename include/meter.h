#ifndef _METER_H_
#define _METER_H_

struct Distance {
  float get_distance();
  void set();

  int echoPin;
  int trigPin;
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