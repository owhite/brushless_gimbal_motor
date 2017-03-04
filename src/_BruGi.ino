// Brushless Gimbal Contmotor2er Software by Christian Winkler and Alois Hahn (C) 2013
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

/**********************************************/
/* Initialization                             */
/**********************************************/
int Owencount = 0;
int Owendirection = 1;

void setup() {

  state = S_INIT_UP;

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

  // Init BL Contmotor2er
  initBlContmotor2er();

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

  maxPWMmotorMotor1Scaled = 40;

  LEDPIN_OFF
  CH2_OFF
  CH3_OFF

}

/************************/
/* PID Contmotor2er       */
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
  
  int pumpNum = 0;
  int pumpCount = 0;

  switch (state) {
  case S_INIT_UP:
    range = FLAP_RANGE;
    config.dirMotorMotor1 = -1;
    state = S_FLAP_UP;
    break;
  case S_FLAP_UP:
    motor1MotorDrive += config.dirMotorMotor1;
    MoveMotorPosSpeed(config.motorNumberMotor1, motor1MotorDrive, maxPWMmotorMotor1Scaled); 
    delay(250);
    if (motor1MotorDrive < 0) {
      state = S_INIT_DOWN;
    }
    break;
  case S_INIT_DOWN:
    range = FLAP_RANGE;
    if (random(100) > 50) {
      state = S_INIT_PUMP;
      break;
    }
    config.dirMotorMotor1 = 1;
    state = S_FLAP_DOWN;
    break;
  case S_FLAP_DOWN:
    motor1MotorDrive += config.dirMotorMotor1;
    MoveMotorPosSpeed(config.motorNumberMotor1, motor1MotorDrive, maxPWMmotorMotor1Scaled); 
    delay(250);
    if (motor1MotorDrive > range) {
      if (pumpCount > 0) {
	range = FLAP_RANGE * .3;
	config.dirMotorMotor1 = 1;
	state = S_PUMP_DOWN;
      }
      else {
	state = S_INIT_UP;
      }
    }
    pumpCount--;
    break;
  case S_INIT_PUMP:
    range = FLAP_RANGE * .3;
    pumpNum = 4;
    pumpCount = 0;
    config.dirMotorMotor1 = 1;
    state = S_PUMP_DOWN;
    break;
  case S_PUMP_DOWN:
    motor1MotorDrive += config.dirMotorMotor1;
    MoveMotorPosSpeed(config.motorNumberMotor1, motor1MotorDrive, maxPWMmotorMotor1Scaled); 
    delay(250);
    if (motor1MotorDrive > range) {
      state = S_INIT_UP;
    }
    pumpCount++;
    break;
  default:
    Serial.println ("Unknown state") ;
    break;
  }


}
