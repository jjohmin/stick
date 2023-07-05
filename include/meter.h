#ifndef _METER_H_
#define _METER_H_

class Distance {
private:
  static constexpr const unsigned long DLPF_CNT = 3;

public:
  Distance(int echoPin, int trigPin)
    : echoPin{ echoPin }, trigPin{ trigPin }
  { }
  unsigned int get_cm();
  void begin();

private:
  void trigger();

private:
  int echoPin;
  int trigPin;
  unsigned long fail_dlpf = 0;
};

#endif /* _METER_H_ */