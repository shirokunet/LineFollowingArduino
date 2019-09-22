#ifndef L298nController_h
#define L298nController_h

class L298nController
{
  public:
    L298nController(char pin1, char pin2, char pin3, char pin4, char enableA, char enableB);
    void GoBack();
    void GoAhead();
    void Stop();
    void TurnLeft();
    void TurnRight();
    void SetMotorLRSpeed(float l_pwm_rate, float r_pwm_rate);  // 0~1.0

  private:
    char pin1_;     // K1、K2 motor direction
    char pin2_;     // K1、K2 motor direction
    char pin3_;     // K3、K4 motor direction
    char pin4_;     // K3、K4 motor direction
    char enableA_;  // Needs to be a PWM pin to be able to control motor speed ENA
    char enableB_;  // Needs to be a PWM pin to be able to control motor speed ENB
    void SetMotorSpeed(char enable_pin, float pwm_rate);
};

#endif
