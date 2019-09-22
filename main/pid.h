#ifndef PID_h
#define PID_h

class PID
{
  public:
    PID(float pgain, float igain, float dgain, float max=1.0)
    {
      max_ = max;
      pgain_ = pgain;
      igain_ = igain;
      dgain_ = dgain;
      proportional_ = 0.0;
      integral_ = 0.0;
      derivative_ = 0.0;
      error_z1_ = 0.0;
      error_z2_ = 0.0;
      manipulate_z1_ = 0.0;
      cycle_hz_ = 100;
    }

    float CalcPID(float error, bool reset = false);
    float CalcSpeedPID(float error, bool reset = false);
    float GetProportional();
    float GetIntegral();
    float GetDerivative();

  private:
    int cycle_hz_;
    float max_;
    float pgain_;
    float igain_;
    float dgain_;
    volatile float proportional_;
    volatile float integral_;
    volatile float derivative_;
    float error_z1_;
    float error_z2_;
    float manipulate_z1_;
};

#endif /* PID_h */
