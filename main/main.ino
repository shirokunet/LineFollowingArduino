#include "L298nController.h"
#include "SensorManager.h"

#define M_SPEED1   80  //motor speed
#define M_SPEED2   80  //motor speed

/* Instance setting */
L298nController l298n = L298nController(7, 8, 9, 10, 5, 6);
SensorManager sensor = SensorManager(4, 2, 3);

/* Grobal Structure */
typedef enum Mode
{
  STANDBY, 
  LINE_FOLLOWING, 
  STOP
};


void LineFollowing(bool ir_l_on_black, bool ir_r_on_black)
{
  l298n.SetMotorSpeed(M_SPEED1,M_SPEED1);

  if((!ir_l_on_black) && ir_r_on_black)
    l298n.TurnRight();
  else if(ir_l_on_black && (!ir_r_on_black))
    l298n.TurnLeft();
  else if((!ir_l_on_black) && (!ir_r_on_black))
    l298n.GoAhead();
  else
    l298n.Stop();

  return;
 }

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /* Variables */
  bool button_is_pushed = false;
  bool ir_l_on_black = false;
  bool ir_r_on_black = false;
  enum Mode mode;
  static int button_counter = 0;
  static bool button_is_pushed_z1 = false;
  static int last_loop_time = 0;
  const int loop_interval_msec = 10;

  /* Manage loop */
  if((millis() - last_loop_time) <= loop_interval_msec)
    return;
  else
    last_loop_time = millis();

  /* Update sensors */
  button_is_pushed = sensor.ButtonIsPushed();
  ir_l_on_black = sensor.LeftIRSensorIsOnBlackLine();
  ir_r_on_black = sensor.LeftIRSensorIsOnBlackLine();

  /* Decide Mode and Movement */
  switch (mode) {
    case STANDBY:
      if((!button_is_pushed_z1) && button_is_pushed)
        mode = LINE_FOLLOWING;
      break;
    case LINE_FOLLOWING:
      LineFollowing(ir_l_on_black, ir_r_on_black);
      if((!button_is_pushed_z1) && button_is_pushed)
        mode = STOP;
      break;
    case STOP:
      l298n.Stop();
      mode = STANDBY;
      break;
    default:
      break;
  }

  /* Debug Console */
  switch (mode) {
    case STANDBY:
      Serial.print("STANDBY");
      break;
    case LINE_FOLLOWING:
      Serial.print("LINE_FOLLOWING");
      break;
    case STOP:
      Serial.print("STOP");
      break;
    default:
      break;
  }
  Serial.println("");

  /* Store laset variables */
  button_is_pushed_z1 = button_is_pushed;
}
