#include "Arduino.h"
#include "SensorManager.h"

SensorManager::SensorManager(char button_pin, char ir_pin_l, char ir_pin_r)
{
  button_pin_ = button_pin;
  ir_pin_l_ = ir_pin_l;
  ir_pin_r_ = ir_pin_r;

  pinMode(button_pin_, INPUT_PULLUP); 
  pinMode(ir_pin_l_, INPUT);
  pinMode(ir_pin_r_, INPUT);
}

bool SensorManager::ButtonIsPushed()
{
  if(digitalRead(button_pin_) == LOW)
    return true;
  else
    return false;
}

bool SensorManager::IRSensorIsOnBlackLine(char ir_pin)
{
  if(digitalRead(ir_pin) == HIGH)
    return true;
  else
    return false;
}

bool SensorManager::LeftIRSensorIsOnBlackLine()
{
  return IRSensorIsOnBlackLine(ir_pin_l_);
}

bool SensorManager::RightIRSensorIsOnBlackLine()
{
  return IRSensorIsOnBlackLine(ir_pin_r_);
}
