/*
  wheel.h - SumoBot Gojira wheel class
*/

#ifndef Wheel_h
#define Wheel_h

#include "Arduino.h"

enum wheel_state
{
  NO_ROT,
  CW,
  CCW,
};

class Wheel
{
  public:
    Wheel(int value_pin, int cw_rot_pin, int ccw_rot_pin);
    ~Wheel();
    
    void setMotor(int speed, wheel_state new_state);
    
  private:
    int _value_pin;
    int _cw_rot_pin;
    int _ccw_rot_pin;
    wheel_state _wheel_state;

    void changeState(wheel_state new_state);
};

#endif
