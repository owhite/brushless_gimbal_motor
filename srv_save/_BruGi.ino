// Brushless Gimbal Controller Software by Christian Winkler and Alois Hahn (C) 2013
// Ludwig Fäerber, Alexander Rehfeld and Martin Eckart

#define VERSION_EEPROM 15 // change this number when eeprom data structure has changed

/*************************/
/* Include Header Files  */
/*************************/
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "definitions.h"
#include "SerialCommand.h"
#include "EEPROMAnything.h"
#include "PinChangeInt.h"
#include "Timer1.h"
#include "Trace.h"
#include "variables.h"

SerialCommand sCmd;     // Create SerialCommand object

#include "fastMathRoutines.h"     // fast Math functions required by orientationRoutines.h
#include "RCdecode.h"             // RC Decoder to move camera by servo signal input
#include "BLcontroller.h"         // Motor Movement Functions and Timer Config
#include "SerialCom.h"            // Serial Protocol for Configuration and Communication

int Owencount = 0;
int Owendirection = 1;

/**********************************************/
/* Initialization                             */
/**********************************************/
void setup() {

  LEDPIN_PINMODE
  
  CH2_PINMODE
  CH3_PINMODE

  // Start Serial Port
  Serial.begin(115200);

  // send Version Number and welcome message
  printMessage(MSG_INFO, F("BruGi ready"));
  printMessage(MSG_VERSION, F(""));

  // Set Serial Protocol Commands
  setSerialProtocol();

  // Init BL Controller
  initBlController();

  // Init Sinus Arrays
  initMotorStuff();
  
  // switch off PWM Power
  motorPowerOff();
    
  // Read Config, initialize if version does not match or CRC fails
  readEEPROM();
  if (config.versEEPROM != VERSION_EEPROM) {
    printMessage(MSG_WARNING, F("EEPROM version mismatch, initialized to default"));
    setDefaultParameters();
    writeEEPROM();
  }
  
  // Init PIDs parameters
  initPIDs();

  // init RC variables
  initRC();

  // Init RC-Input
  initRCPins();

  LEDPIN_OFF
  CH2_OFF
  CH3_OFF

}

/************************/
/* PID Controller       */
/************************/
int32_t ComputePID(int32_t DTms, int32_t DTinv, int32_t in, int32_t setPoint, int32_t *errorSum, int32_t *errorOld, int32_t Kp, int16_t Ki, int32_t Kd)
{
  int32_t error = setPoint - in;
  int32_t Ierr;
   
  Ierr = error * Ki * DTms;
  Ierr = constrain_int32(Ierr, -(int32_t)1000*100, (int32_t)1000*100);
  *errorSum += Ierr;
 
  /*Compute PID Output*/
  int32_t out = (Kp * error) + *errorSum + Kd * (error - *errorOld) * DTinv;
  *errorOld = error;

  out = out / 4096 / 8;
  
  return out;
}

/**********************************************/
/* Main Loop                                  */
/**********************************************/
void loop() { 
  int32_t pitchPIDVal;
  int32_t rollPIDVal;
  
  static char pOutCnt = 0;
  static char tOutCnt = 0;
  static char tOutCntSub = 0;
  static int stateCount = 0;
  static uint8_t ledBlinkCnt = 0;
  static uint8_t ledBlinkOnTime = 10;
  static uint8_t ledBlinkPeriod = 20;

  CH2_ON

  // ComputePID variables (ALL int32_t)
  // DTms  ... sample period (ms)
  // DTinv ... sample frequency (Hz), inverse of DT (just to avoid division)
  // input
  // setPoint
  // errorSum
  // errorOld
  // Kp
  // Ki
  // Kd

  // pitch PID
  // pitchPIDVal = ComputePID(DT_INT_MS, DT_INT_INV, 0, 0, &pitchErrorSum, &pitchErrorOld, pitchPIDpar.Kp, pitchPIDpar.Ki, pitchPIDpar.Kd);
  if (abs(Owencount) > 250) {
    Owendirection *= -1;
  }
  delay(250);
  Owencount += Owendirection;
  Serial.println(Owencount);
  maxPWMmotorPitchScaled = 40;
  // pitchMotorDrive = pitchPIDVal * config.dirMotorPitch;   // motor control
  pitchMotorDrive = Owencount * config.dirMotorPitch;   // motor control
  MoveMotorPosSpeed(config.motorNumberPitch, pitchMotorDrive, maxPWMmotorPitchScaled); 

 
  // roll PID
  rollPIDVal = ComputePID(DT_INT_MS, DT_INT_INV, 0, 0, &rollErrorSum, &rollErrorOld, rollPIDpar.Kp, rollPIDpar.Ki, rollPIDpar.Kd);
  rollMotorDrive = rollPIDVal * config.dirMotorRoll;
  rollMotorDrive = 10000;
  // MoveMotorPosSpeed(config.motorNumberRoll, rollMotorDrive, maxPWMmotorRollScaled);


  sCmd.readSerial();

  CH2_OFF
}
