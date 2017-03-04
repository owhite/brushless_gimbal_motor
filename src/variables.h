#include "Trace.h"

/*************************/
/* Config Structure      */
/*************************/

struct config_t
{
  uint8_t versEEPROM;
  int32_t gyroMotor1Kp; 
  int32_t gyroMotor1Ki;   
  int32_t gyroMotor1Kd;
  int32_t gyroMotor2Kp;
  int32_t gyroMotor2Ki;
  int32_t gyroMotor2Kd;
  int16_t accTimeConstant;
  int16_t angleOffsetMotor1;   // angle offset, deg*100
  int16_t angleOffsetMotor2;
  int8_t dirMotorMotor1;
  int8_t dirMotorMotor2;
  uint8_t motorNumberMotor1;
  uint8_t motorNumberMotor2;
  uint8_t maxPWMmotorMotor1;
  uint8_t maxPWMmotorMotor2;
  uint16_t refVoltageBat;    // Ubat reference, unit = volts*100
  uint16_t cutoffVoltage;    // Ubat cutoff, unit = volts*100
  bool motorPowerScale;
  bool rcAbsoluteMotor1;
  bool rcAbsoluteMotor2;
  int8_t maxRCMotor1;
  int8_t maxRCMotor2;
  int8_t minRCMotor1;
  int8_t minRCMotor2;
  int16_t rcGainMotor1;
  int16_t rcGainMotor2;
  int16_t rcLPFMotor1;        // low pass filter for RC absolute mode, units=1/10 sec
  int16_t rcLPFMotor2;         
  bool rcModePPMMotor1;       // RC mode, true=common RC PPM channel, false=separate RC channels 
  bool rcModePPMMotor2;
  bool rcModePPMAux;
  bool rcModePPMFpvMotor1;
  bool rcModePPMFpvMotor2;

  uint8_t rcPinModeCH0;      // 0=Channel OFF, 1=use digital PWM/PPM control, 2=use analog control
  uint8_t rcPinModeCH1;      // 
  uint8_t rcPinModeCH2;      // 
 
  int8_t rcChannelMotor1;     // input channel for motor1
  int8_t rcChannelMotor2;      // input channel for motor2
  int8_t rcChannelAux;       // input channel for auxiliary functions
  int8_t rcChannelFpvMotor1;  // input channel for fpv channel motor1
  int8_t rcChannelFpvMotor2;   // input channel for fpv channel motor2
  
  int8_t fpvGainMotor1;       // gain of FPV channel motor1
  int8_t fpvGainMotor2;        // gain of FPV channel motor2
  
  int16_t rcLPFMotor1Fpv;     // low pass filter in FPV mode
  int16_t rcLPFMotor2Fpv;      // low pass filter in FPV mode
  
  int16_t rcMid;             // rc channel center ms
  
  traceModeType fTrace;       // trace output mode (uint8_t)
  traceModeType sTrace;       // trace output mode (uint8_t)
  
  bool enableGyro;           // enable gyro attitude update
  bool enableACC;            // enable acc attitude update
  bool axisReverseZ;
  bool axisSwapXY;
  
  bool fpvFreezeMotor1;
  bool fpvFreezeMotor2;
  
  uint8_t maxPWMfpvMotor1;    // motor PWM power in FPV freeze mode
  uint8_t maxPWMfpvMotor2;
  
  int8_t fpvSwMotor1;         // fpv switch motor1: -1=always on, 0=off, 1=auxSW1, 2=auxSW2 
  int8_t fpvSwMotor2;          // fpv switch motor2: -1=alwas on, 0=off, 1=auxSW1, 2=auxSW2 
  int8_t altSwAccTime;       // switch alternate Acc time: -1=always on, 0=off, 1=auxSW1, 2=auxSW2
  int16_t accTimeConstant2;  // alternate constant
  
  bool gyroCal;              // gyro calibration at startup 
  int16_t  gyrOffsetX;       // gyyro calibration offsets
  int16_t  gyrOffsetY;
  int16_t  gyrOffsetZ;
  
  int16_t  accOffsetX;       // acc calibration offsets
  int16_t  accOffsetY;
  int16_t  accOffsetZ;
  
  uint8_t crc8;
} config;

void setDefaultParameters()
{
  config.versEEPROM = VERSION_EEPROM;
  config.gyroMotor1Kp = 20000;
  config.gyroMotor1Ki = 10000;
  config.gyroMotor1Kd = 40000;
  config.gyroMotor2Kp = 20000;
  config.gyroMotor2Ki = 8000;
  config.gyroMotor2Kd = 30000;
  config.accTimeConstant = 7;
  config.angleOffsetMotor1 = 0;
  config.angleOffsetMotor2 = 0;
  config.dirMotorMotor1 = 1;
  config.dirMotorMotor2 = -1;
  config.motorNumberMotor1 = 0;
  config.motorNumberMotor2 = 1;
  config.maxPWMmotorMotor1 = 80;
  config.maxPWMmotorMotor2 = 80;
  config.refVoltageBat = 800;
  config.cutoffVoltage = 600;
  config.motorPowerScale = 0;
  config.rcAbsoluteMotor1 = true;
  config.rcAbsoluteMotor2 = true;
  config.maxRCMotor1 = 30;
  config.minRCMotor1 = -30;
  config.maxRCMotor2 = 30;
  config.minRCMotor2 = -30;
  config.rcGainMotor1 = 5;
  config.rcGainMotor2 = 5;
  config.rcLPFMotor1 = 20;             // 2 sec
  config.rcLPFMotor2 = 20;              // 2 sec
  config.rcModePPMMotor1 = false;
  config.rcModePPMMotor2 = false;
  config.rcModePPMAux = false;
  config.rcModePPMFpvMotor1 = false;
  config.rcModePPMFpvMotor2 = false;
  config.rcChannelMotor1 = 1;
  config.rcChannelMotor2 = 0;
  config.rcChannelAux = -1;
  config.rcChannelFpvMotor1 = -1;
  config.rcChannelFpvMotor2 = -1;
  config.fpvGainMotor1 = 0;
  config.fpvGainMotor2 = 0;
  config.rcPinModeCH0 = 1;      // 1 = use digital control
  config.rcPinModeCH1 = 1;
  config.rcPinModeCH2 = 1;
  config.rcLPFMotor1Fpv = 10;  // 1 sec
  config.rcLPFMotor2Fpv = 10;  // 1 sec
  config.rcMid = MID_RC;
  config.fTrace=TRC_OFF; // fast trace
  config.sTrace=TRC_OFF; // slow trace
  config.enableGyro=true;
  config.enableACC=true;
  config.axisReverseZ=true;
  config.axisSwapXY=false;
  config.fpvFreezeMotor1=false;
  config.fpvFreezeMotor2=false;
  config.maxPWMfpvMotor1=80;
  config.maxPWMfpvMotor2=80;
  config.fpvSwMotor1=0;
  config.fpvSwMotor2=0;
  config.altSwAccTime=0;
  config.accTimeConstant2 = 2;
  config.gyroCal = true;
  config.gyrOffsetX = 0;       // gyyro calibration offset
  config.gyrOffsetY = 0;
  config.gyrOffsetZ = 0;
  config.accOffsetX = 0;       // acc calibration offset
  config.accOffsetY = 0;
  config.accOffsetZ = 0;
  config.crc8 = 0;  
}


typedef struct PIDdata {
  int32_t   Kp, Ki, Kd;
} PIDdata_t;

PIDdata_t motor1PIDpar,motor2PIDpar;

void initPIDs(void)
{
  motor2PIDpar.Kp = config.gyroMotor2Kp/10;
  motor2PIDpar.Ki = config.gyroMotor2Ki/1000;
  motor2PIDpar.Kd = config.gyroMotor2Kd/10/250;  // divide by 250 to keep compatibility to previous version 

  motor1PIDpar.Kp = config.gyroMotor1Kp/10;
  motor1PIDpar.Ki = config.gyroMotor1Ki/1000;
  motor1PIDpar.Kd = config.gyroMotor1Kd/10/250;  // divide by 250 to keep compatibility to previous version
  
}

static int32_t motor1ErrorSum = 0;
static int32_t motor2ErrorSum = 0;
static int32_t motor1ErrorOld = 0;
static int32_t motor2ErrorOld = 0;


// CRC definitions
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
typedef uint8_t crc;



/*************************/
/* Variables             */
/*************************/
int8_t state;
int range = FLAP_RANGE;

// motor drive

int8_t pwmSinMotor[256];

int currentStepMotor0 = 0;
int currentStepMotor1 = 0;
bool motorUpdate = false; 

int8_t motor1Direction = 1;
int8_t motor2Direction = 1;

uint8_t freqCounter = 0;

int motor1MotorDrive = 0;
int motor2MotorDrive = 0;

// control motor update in ISR
bool enableMotorUpdates = false;

uint8_t pwm_a_motor0 = 128;
uint8_t pwm_b_motor0 = 128;
uint8_t pwm_c_motor0 = 128;

uint8_t pwm_a_motor1 = 128;
uint8_t pwm_b_motor1 = 128;
uint8_t pwm_c_motor1 = 128;

// battery voltage
float voltageBat = 0;
float uBatValue_f = 0;


//scaled Motor Power
uint16_t maxPWMmotorMotor1Scaled;
uint16_t maxPWMmotorMotor2Scaled;

// Variables for MPU6050
float gyroMotor1;
float gyroMotor2; //in deg/s

float resolutionDevider;
int16_t x_val;
int16_t y_val;
int16_t z_val;

float Motor1PhiSet = 0;
float Motor2PhiSet = 0;
static float motor1AngleSet=0;
static float motor2AngleSet=0;

static float qLPMotor1[3] = {0,0,0};
static float qLPMotor2[3] = {0,0,0};


int count=0;

// RC control

struct rcData_t
{
 uint32_t microsRisingEdge;
 uint32_t microsLastUpdate;
 uint16_t rx;
 uint16_t rx1;
 bool     update;
 bool     valid;
 float    rcSpeed;
 float    setpoint;
 bool     rcAuxSwitch1;
 bool     rcAuxSwitch2;
};

rcData_t rcData[RC_DATA_SIZE];

float rcLPFMotor1_tc = 1.0;
float rcLPFMotor2_tc = 1.0;

float rcLPFMotor1Fpv_tc = 1.0;
float rcLPFMotor2Fpv_tc = 1.0;

// Gimbal State
enum gimStateType {
 GIM_IDLE=0,      // no PID
 GIM_UNLOCKED,    // PID on, fast ACC
 GIM_LOCKED,      // PID on, slow ACC
 GIM_ERROR        // error condition
};

gimStateType gimState = GIM_IDLE;
int stateCount = 0;

// rc fpv mode
bool fpvModeMotor1 = false;
bool fpvModeMotor2 = false;

bool fpvModeFreezeMotor1 = false;
bool fpvModeFreezeMotor2 = false;

// rc alternate ACC time
bool altModeAccTime = false;

//*************************************
//
//  IMU
//
//*************************************
enum axisDef {
  MOTOR2,
  MOTOR1,
  YAW
};

typedef struct fp_vector {
  float X;
  float Y;
  float Z;
} t_fp_vector_def;

typedef union {
  float   A[3];
  t_fp_vector_def V;
} t_fp_vector;



//********************
// sensor orientation
//********************
typedef struct sensorAxisDef {
  char idx;
  int  dir;
} t_sensorAxisDef;

typedef struct sensorOrientationDef {
  t_sensorAxisDef Gyro[3];
  t_sensorAxisDef Acc[3];
} t_sensorOrientationDef;

t_sensorOrientationDef sensorDef = { 
    {{0, 1}, {1, 1}, {2, 1}},    // Gyro
    {{0, 1}, {1, 1}, {2, 1}}     // Acc
  };


static float gyroScale=0;

static int16_t gyroADC[3];
static int16_t accADC[3];

static t_fp_vector EstG;

static float accLPF[3] = {0.0,0.0,0.0};
static float accMag = 0;
static bool disableAccGtest = false;

static float AccComplFilterConst = 0;  // filter constant for complementary filter

static int16_t acc_25deg = 25;      //** TODO: check

static int32_t angle[2]    = {0,0};  // absolute angle inclination in multiple of 0.01 degree    180 deg = 18000

static float angleOffsetMotor2_f = 0;
static float angleOffsetMotor1_f = 0;

static int32_t angleOffsetMotor2 = 0;
static int32_t angleOffsetMotor1 = 0;


// DEBUG only
uint32_t stackTop = 0xffffffff;
uint32_t stackBottom = 0;

uint32_t heapTop = 0;
uint32_t heapBottom = 0xffffffff;

