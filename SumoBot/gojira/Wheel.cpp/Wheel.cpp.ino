/*
  Wheel.cpp - Library for SumoBot Gojira wheel class
*/

#include "Arduino.h"
#include "Wheel.h"

Wheel::Wheel(int value_pin, int cw_rot_pin, int ccw_rot_pin)
{
  pinMode(value_pin, OUTPUT);
  pinMode(cw_rot_pin, OUTPUT);
  pinMode(ccw_rot_pin, OUTPUT);
  
  _value_pin = value_pin;
  _cw_rot_pin = cw_rot_pin;
  _ccw_rot_pin = ccw_rot_pin;

  _wheel_state = wheel_state NO_ROT

  //MAXIMUM WHEEL SPEED AS DEFINED BY VOLTAGE
  const unsigned int maxSpeed = 255;
  unsigned int speed = 1 * maxSpeed;
}

Wheel::~Wheel()
{
  /* deconstructor */
}

void Wheel::changeState(wheel_state new_state)
{
  _wheel_state = new_state
}

void Wheel::setMotor(int speed, wheel_state state)
{
  if (state == NOT_ROT) {
    digitalWrite(_cw_rot_pin, false);
    digitalWrite(_ccw_rot_pin, false);
  } else if (state == CW) {
    if (_wheel_state == CCW) {
      digitalWrite(_value_pin, 0);
      delay(10);
    }
    digitalWrite(_cw_rot_pin, true);
    digitalWrite(_ccw_rot_pin, false);
  } else if (state == CCW) {
    if (_wheel_state == CW) {
      digitalWrite(_value_pin, 0);
      delay(10);
    }
    digitalWrite(_cw_rot_pin, false);
    digitalWrite(_ccw_rot_pin, true);
  }

  changeState(state);
  
  analogWrite(_value_pin, speed);
}

