#include "Trace.h"


void printTrace(traceModeType traceMode)
{
 
  Serial.print(F("traceData"));

  switch (traceMode) {
    case TRC_RC:
      // *******  RC  *********
      Serial.print(F(" RC"));
      for (char id = 0; id < RC_DATA_SIZE; id++)
      {
        printTrace_int(rcData[id].rx);
      }
      
      for (char id = 0; id < RC_DATA_SIZE; id++)
      {
        printTrace_int(rcData[id].valid);
      }

      for (char id = 0; id < RC_DATA_SIZE; id++)
      {
        printTrace_int(rcData[id].rcAuxSwitch1);
        printTrace_int(rcData[id].rcAuxSwitch2);
      }
      break;
      
    case TRC_AUX:
      // *******  AUX  *********
      Serial.print(F(" AUX"));
      printTrace_int(fpvModeMotor1 || fpvModeFreezeMotor1);
      printTrace_int(fpvModeMotor2 || fpvModeFreezeMotor2);
      printTrace_int(altModeAccTime);
      break;
      
    case TRC_IMU:
      // *******  IMU  *********
      Serial.print(F(" IMU"));
      printTrace_float(EstG.V.X);
      printTrace_float(EstG.V.Y);
      printTrace_float(EstG.V.Z);
      printTrace_int(angle[MOTOR2]);
      printTrace_int(angle[MOTOR1]);  
      break;

    case TRC_GYRO:
      // *******  Gyro Sensor  *********
      Serial.print(F(" GYRO"));

      for (char axis = 0; axis < 3; axis++)
      {
        printTrace_int(gyroADC[axis]);
      }
      break;
     
    case TRC_ACC:
      // *******  ACC Sensor  *********
      Serial.print(F(" SENSOR_ACC"));

      for (char axis = 0; axis < 3; axis++)
      {
        printTrace_int(accADC[axis]);      
      }
      printTrace_int((int)accMag); 
      break;

    case TRC_PID_MOTOR1:
      // *******  PID Motor1  *********
      Serial.print(F(" PID_MOTOR1"));
      printTrace_float(motor1AngleSet);
      printTrace_int(angle[MOTOR1]);
      printTrace_int(motor1MotorDrive);
      printTrace_float((motor1AngleSet*1000-angle[MOTOR1])*0.001); // PID error
      printTrace_int(motor1ErrorSum);
      break;

    case TRC_PID_MOTOR2:
      // *******  PID Motor2  *********
      Serial.print(F(" PID_MOTOR2"));
      printTrace_float(motor2AngleSet);
      printTrace_int(angle[MOTOR2]);
      printTrace_int(motor2MotorDrive);
      printTrace_float((motor2AngleSet*1000-angle[MOTOR2])*0.001); // PID error
      printTrace_int(motor2ErrorSum);
      break;

    case TRC_OAC:
      // *******  OAC mode 2 (replaces oac/acc mode)  *********
      Serial.print(F(" ACC2"));
      printTrace_float(angle[MOTOR1]);
      printTrace_float(angle[MOTOR2]);
      break;
            
    default:
      break;
  }
  
  Serial.println(F(""));
}

void printTrace_int(int32_t value)
{
  Serial.print(F(" "));
  Serial.print(value);
}

void printTrace_float(float value)
{
  Serial.print(F(" "));
  Serial.print(value, 4);
}


void printMessage(msgSeverity_t msgSeverity, const __FlashStringHelper * msg) {

  Serial.print(F("message "));
  switch (msgSeverity) {
    case MSG_INFO:
      Serial.print(F("INFO: "));
      Serial.println(msg);
      break;
    case MSG_WARNING:
      Serial.print(F("WARNING: "));
      Serial.println(msg);
      break;
    case MSG_ERROR:   
      Serial.print(F("ERROR: "));
      Serial.println(msg);
      break;
  }
}
