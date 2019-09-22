#include "l298n_controller.h"
#include "sensor_manager.h"
#include "pid.h"

/* Macro setting */
#define DEBUG_CONSOLE

/* Instance setting */
L298nController l298n = L298nController(8, 7, 10, 9, 6, 5);
SensorManager sensor = SensorManager(4, A0, A1);
PID pid_velocity = PID(0.5, 0.001, 0.1);

/* Grobal Structure */
typedef enum Mode
{
  STANDBY, 
  LINE_FOLLOWING, 
  STOP
};


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /* Parameter */
  const int loop_interval_msec = 1;
  const float max_velocity_rate_l = 0.37;
  const float max_velocity_rate_r = 0.37;
  const float end_line_th = 0.6; 

  /* Variables */
  bool button_is_pushed = false;
  float ir_l_black_rate = 0.0;
  float ir_r_black_rate = 0.0;
  static enum Mode mode = STANDBY;
  static enum Mode mode_z1 = STANDBY;
  static bool button_is_pushed_z1 = false;
  static int last_loop_time = 0;

  /* Manage loop */
  if((millis() - last_loop_time) <= loop_interval_msec)
    return;
  else
    last_loop_time = millis();

  /* Update sensors */
  button_is_pushed = sensor.ButtonIsPushed();
  ir_l_black_rate = sensor.LeftIRSensor();
  ir_r_black_rate = sensor.RightIRSensor();

  /* Calc error and pid */
  float line_error_rate = (ir_l_black_rate - ir_r_black_rate) / 2.0;
  float u_velocity = pid_velocity.CalcPID(line_error_rate);

  /* Decide Mode and Movement */
  switch (mode) {
    case STANDBY:
      if ((!button_is_pushed_z1) && button_is_pushed)
        mode = LINE_FOLLOWING;
      break;
    case LINE_FOLLOWING:
      if (u_velocity > 0)
        l298n.SetMotorLRSpeed(max_velocity_rate_l - u_velocity, max_velocity_rate_r);
      else
        l298n.SetMotorLRSpeed(max_velocity_rate_l, max_velocity_rate_r + u_velocity);
      l298n.GoAhead();

      if (((!button_is_pushed_z1) && button_is_pushed)
        || (ir_l_black_rate > end_line_th && ir_r_black_rate > end_line_th))
      {
        mode = STOP;
      }
      break;
    case STOP:
      l298n.Stop();
      mode = STANDBY;
      break;
    default:
      break;
  }

#ifdef DEBUG_CONSOLE
  /* Debug Console */
  Serial.print("m:");
  Serial.print(mode);
  Serial.print(", b:");
  Serial.print(button_is_pushed);
  Serial.print(", sl");
  Serial.print(ir_l_black_rate);
  Serial.print(", sr");
  Serial.print(ir_r_black_rate);
  Serial.print(", er:");
  Serial.print(line_error_rate);
  Serial.print(", p:");
  Serial.print(pid_velocity.GetProportional());
  Serial.print(", i:");
  Serial.print(pid_velocity.GetIntegral());
  Serial.print(", d:");
  Serial.print(pid_velocity.GetDerivative());
  Serial.print(", u");
  Serial.print(u_velocity);
  Serial.print("\n");
#endif

  /* Store last variables */
  mode_z1 = mode;
  button_is_pushed_z1 = button_is_pushed;

  return;
}
