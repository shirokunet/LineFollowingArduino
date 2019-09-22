#ifndef SensorManager_h
#define SensorManager_h

class SensorManager
{
  public:
    SensorManager(char button_pin, char ir_pin_l, char ir_pin_r);
    bool ButtonIsPushed();
    bool LeftIRSensorIsOnBlackLine();
    bool RightIRSensorIsOnBlackLine();

  private:
    char button_pin_;
    char ir_pin_l_;
    char ir_pin_r_;
    bool IRSensorIsOnBlackLine(char ir_pin);
};

#endif
