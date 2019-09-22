#include "Arduino.h"
#include "l298n_controller.h"

L298nController::L298nController(char pin1, char pin2, char pin3, char pin4, char enableA, char enableB)
{
  pin1_ = pin1;
  pin2_ = pin2;
  pin3_ = pin3;
  pin4_ = pin4;
  enableA_ = enableA;
  enableB_ = enableB;

  pinMode(pin1_, OUTPUT);
  pinMode(pin2_, OUTPUT);
  pinMode(pin3_, OUTPUT);
  pinMode(pin4_, OUTPUT);
  pinMode(enableA_, OUTPUT);
  pinMode(enableB_, OUTPUT);
}

void L298nController::GoBack(void)
{
  digitalWrite(pin1_, LOW);
  digitalWrite(pin2_, HIGH);
  digitalWrite(pin3_, LOW);
  digitalWrite(pin4_, HIGH);
}

void L298nController::GoAhead(void)
{
  digitalWrite(pin1_, HIGH);
  digitalWrite(pin2_, LOW);
  digitalWrite(pin3_, HIGH);
  digitalWrite(pin4_, LOW); 
}

void L298nController::Stop(void)
{
  digitalWrite(pin1_, LOW);
  digitalWrite(pin2_, LOW);
  digitalWrite(pin3_, LOW);
  digitalWrite(pin4_, LOW); 
}

void L298nController::TurnLeft(void)
{
  digitalWrite(pin1_, HIGH);
  digitalWrite(pin2_, LOW);
  digitalWrite(pin3_, LOW);
  digitalWrite(pin4_, HIGH);
}

void L298nController::TurnRight(void)
{
  digitalWrite(pin1_, LOW);
  digitalWrite(pin2_, HIGH);
  digitalWrite(pin3_, HIGH);
  digitalWrite(pin4_, LOW);
}

void L298nController::SetMotorSpeed(char enable_pin, float pwm_rate)
{
  if (pwm_rate > 1.0)
    pwm_rate = 1.0;
  else if (pwm_rate < 0.0)
    pwm_rate = 0.0;
  analogWrite(enable_pin, int(pwm_rate * 255));
}

void L298nController::SetMotorLRSpeed(float l_pwm_rate, float r_pwm_rate)
{
  SetMotorSpeed(enableA_, l_pwm_rate);
  SetMotorSpeed(enableB_, r_pwm_rate);
}
