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
      printTrace_int(fpvModePitch || fpvModeFreezePitch);
      printTrace_int(fpvModeRoll || fpvModeFreezeRoll);
      printTrace_int(altModeAccTime);
      break;
      
    case TRC_IMU:
      // *******  IMU  *********
      Serial.print(F(" IMU"));
      printTrace_float(EstG.V.X);
      printTrace_float(EstG.V.Y);
      printTrace_float(EstG.V.Z);
      printTrace_int(angle[ROLL]);
      printTrace_int(angle[PITCH]);  
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

    case TRC_PID_PITCH:
      // *******  PID Pitch  *********
      Serial.print(F(" PID_PITCH"));
      printTrace_float(pitchAngleSet);
      printTrace_int(angle[PITCH]);
      printTrace_int(pitchMotorDrive);
      printTrace_float((pitchAngleSet*1000-angle[PITCH])*0.001); // PID error
      printTrace_int(pitchErrorSum);
      break;

    case TRC_PID_ROLL:
      // *******  PID Roll  *********
      Serial.print(F(" PID_ROLL"));
      printTrace_float(rollAngleSet);
      printTrace_int(angle[ROLL]);
      printTrace_int(rollMotorDrive);
      printTrace_float((rollAngleSet*1000-angle[ROLL])*0.001); // PID error
      printTrace_int(rollErrorSum);
      break;

    case TRC_OAC:
      // *******  OAC mode 2 (replaces oac/acc mode)  *********
      Serial.print(F(" ACC2"));
      printTrace_float(angle[PITCH]);
      printTrace_float(angle[ROLL]);
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
