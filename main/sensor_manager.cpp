#include "Arduino.h"
#include "sensor_manager.h"

SensorManager::SensorManager(char button_pin, char ir_pin_l, char ir_pin_r)
{
  button_pin_ = button_pin;
  ir_pin_l_ = ir_pin_l;
  ir_pin_r_ = ir_pin_r;

  pinMode(button_pin_, INPUT_PULLUP);
}

bool SensorManager::ButtonIsPushed()
{
  if(digitalRead(button_pin_) == LOW)
    return true;
  else
    return false;
}

float SensorManager::LeftIRSensor()
{
  return float(analogRead(ir_pin_l_)) / 1024.0;
}

float SensorManager::RightIRSensor()
{
  return float(analogRead(ir_pin_r_)) / 1024.0;
}
