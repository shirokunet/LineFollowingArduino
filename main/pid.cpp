#include "Arduino.h"
#include "pid.h"

float PID::CalcPID (float error, bool reset)
{
  float manipulate = 0.0;

  /* reset */
  if (reset){
    integral_ = 0;
    error_z1_ = 0;
  }

  /* P */
  proportional_ = error * pgain_;

  /* I */
  integral_ += error * igain_;
  if (integral_ > max_*0.4)
    integral_ = max_*0.4;
  else if (integral_ < -max_*0.4)
    integral_ = -max_*0.4;

  /* D */
  derivative_ = (error - error_z1_) * dgain_;

  /* control variable */
  manipulate = proportional_ + integral_ + derivative_;

  /* limit */
  if(manipulate > max_)
    manipulate = max_;
  else if(manipulate < -max_)
    manipulate = -max_;

  /* z1 */
  error_z1_ = error;

  return manipulate;
}

float PID::CalcSpeedPID (float error, bool reset)
{
  float d_manipulate = 0.0;
  float manipulate = 0.0;

  /* reset */
  if (reset){
    integral_ = 0;
    error_z1_ = 0;
  }

  /* P */
  proportional_ = (error - error_z1_) / float(cycle_hz_)  * pgain_;

  /* I */
  integral_ = error * igain_;

  /* D */
  derivative_ = ((error - error_z1_) / float(cycle_hz_) -  (error_z1_ - error_z2_) / float(cycle_hz_))  / float(cycle_hz_) * dgain_;

  /* control variable */
  d_manipulate = proportional_ + integral_ + derivative_;
  manipulate = manipulate_z1_ + d_manipulate;

  /* limit */
  if(manipulate > max_)
    manipulate = max_;
  else if(manipulate < -max_)
    manipulate = -max_;

  /* z1 */
  error_z2_ = error_z1_;
  error_z1_ = error;
  manipulate_z1_ = manipulate;

  return manipulate;
}

float PID::GetProportional()
{
  return proportional_;
}

float PID::GetIntegral()
{
  return integral_;
}

float PID::GetDerivative()
{
  return derivative_;
}