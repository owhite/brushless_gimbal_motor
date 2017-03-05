Configuration of the paramters is accomplished by a serial protocol.
The user will not access the serial line directly, he will use a graphical user interface (GUI) running on a host pc.
A proper gui tool (blg-tool) is located in the GUI folder.

The Arduino Serial Monitor can be used for debugging purposes.

Arduino -> Tools -> Serial Monitor Settings
  Baudrate: 11200 Baud, NL and CR

######################################
 List of serial commands
######################################

sd   # set defaults
we   # write config to eeprom
re   # restore config from eeprom
gc   # calibrate gyro
ac   # calibrate acc
sbv  # save battery voltage
par <parName> <parValue> # general parameter read/set command
 e.g.
   par                   # list all config parameters
   par gyroPitchKi       # list gyroPitchKi
   par gyroPitchKi 12000 # set gyroPitchKi to 12000

he  # print help


The firmware version string is printed at the end of a "par" list command
e.g. "BruGi version 49 r190"



######################################
 Config Parameters (list with "par")
######################################

vers 49
  firmware version
  
gyroPitchKp/gyroRollKp
  pid controller P-value
  
gyroPitchKi/gyroRollKi
  pid controller I-value
  
gyroPitchKd/gyroRollKd
  pid controller D-value
  
accTimeConstant
  time constant of ACC complementary filter.
  controls how fast the gimbal follows ACC.
  unit = 1 sec, e.g. 7 = 7 seconds
  
angleOffsetPitch/angleOffsetRoll
  offset of gimbal zero position
  unit = 0.01 deg, e.g. 500 = 5.00 deg

dirMotorPitch
dirMotorRoll
  motor direction
  1 = normal, -1 = reverse direction

motorNumberPitch
motorNumberRoll
  assign motor output for pitch and roll, legal values are 0 or 1

maxPWMmotorPitch
maxPWMmotorRoll
  motor power, legal range 0 to 255

refVoltageBat
  reference voltage for power scale mode
  In power scale mode the motor power is compensated for power supply changes
  Save the voltage value at which the PWM paramters have been set, as a reference.

cutoffVoltage
  if supply voltage drops below this value motor power is switched off.
  Can be used to avoid low battery discharge.

motorPowerScale
  voltage divider resistors must be mounted to use the power scale feature (see Voltage-Sense-Modification folder)
  0 ... power scale mode off
  1 ... power scale mode ON 

rcAbsolutePitch
rcAbsoluteRoll
   0 ... RC Relative Mode, gimbal position is incremented/decremented by RC
   1 ... RC Absolute Mode, RC controls gimbal directly

minRCPitch
minRCRoll
  RC minimum set point angle, unit = 1 deg
maxRCPitch
maxRCRoll
  RC maximum set point angle, unit = 1 deg

rcGainPitch
rcGainRoll
  RC gain in Relative mode, specifies speed of gimbal movement

rcLPFPitch
rcLPFRoll
  RC low pass filter in Absolute mode, specifies speed of gimbal movement
  unit = 0.1 sec, e.g. 20 = 2.0 seconds

rcModePPMPitch
rcModePPMRoll
rcModePPMAux
rcModePPMFpvP
rcModePPMFpvR
  selects the RC input mode for Pitch,Roll,Aux, FpvPitch and FpvRoll functions
  0 ... use RC PWM (pulse width modulation, 1.0-2.0 ms) input source
  1 ... use RC PPM (rc sum signal) input source
  
  input A2 = PWM channel 1 or PPM, if rcModePPM is select for at least once
  input A1 = PWM channel 2
  input A0 = PWM channel 3
    
rcChannelPitch
rcChannelRoll
rcChannelAux
rcChannelFpvP
rcChannelFpvR
  select the source channel number for each Pitch,Roll,Aux, FpvPitch and FpvRoll function
  
  in PPM mode: channel numbers 0...15 select PPM channel 1...16
  in PWM mode: channel numbers 0...2 refer to the input channel 1...3
               note: if PPM is used, PWM channel 1 is not available for PWM

fpvGainPitch
fpvGainRoll
  gain of FPV (first person view) channel.
  When switch into FPV mode (my switch fpvSw) the fpv channel controls the camera postion,
  instead of the primary Rc channel.
  The amount of travel can be set by this number.  

rcLPFPitchFpv
rcLPFRollFpv
  low pass filter constant in FPV mode

rcMid
  pulse withc of the center position of pwm/ppm rc channels
  default 1500 usec  

fTrace
  fast trace mode
  data and status information is sent regulary with 25 Hz rate
  0 ... off
  1 ... trace RC data
  2 ... trace AUX 
  3 ... trace IMU
  4 ... trace ACC
  5 ... trace GYRO
  6 ... trace PID pitch
  7 ... trace PID roll
  8 ... trace angles (legacy OAC)

sTrace
  slow trace mode
  data and status information is sent regulary with 10 Hz rate
  0 ... off
  1 ... trace RC data
  2 ... trace AUX 
  3 ... trace IMU
  4 ... trace ACC
  5 ... trace GYRO
  6 ... trace PID pitch
  7 ... trace PID roll
  8 ... trace angles (legacy OAC)
  9 ... trace ALL (cycles through 1...7)
  (see Trace.ino for actual modes)
  
enableGyro
enableACC
   1 ... enable Gyro/ACC update in control loop
         just for test and adjustment purposes

axisReverseZ
   0 ... sensor is mounted with component side up
   1 ... sensor is mounted with component side down

   axisSwapXY
   0 ... standard X/Y sensor orientation
   1 ... swap X/Y, exchange roll/pitch function, when sensor is rotated 90 degrees

fpvSwPitch
fpvSwRoll
  select switch function (sw1 or sw2) for fpv mode switchover

altSwAccTime
  select switch function (sw1 or sw2) for alternate acc time switchover
  
accTimeConstant2
  alternate acc time constant, as activated by alsSwAccTime

gyroCal
  enable gyro calibration at startup
  0 ... no gyro calibration at startup, use gyroOffset values from EEPROM/flash instead
  1 ... perform gyro calibartion each time at startup (default)

gyrOffsetX
gyrOffsetY
gyrOffsetZ
  gyro offset values, set at gyro calibration (gc command)

accOffsetX
accOffsetY
accOffsetZ
  acc offset values, they are set  at acc calibration (ac command).
  Acc calibration should be done for at least to sensor positions.
  e.g. for vertical (90 deg) and for horizontal (0 deg). 
