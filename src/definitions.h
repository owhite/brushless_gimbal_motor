/*************************/
/* Definitions           */
/*************************/

// Define Brushless PWM Mode, uncomment ONE setting
#define PWM_32KHZ_PHASE  // Resolution 8 bit for PWM
//#define PWM_8KHZ_FAST    // Resolution 8 bit for PWM
//#define PWM_4KHZ_PHASE   // Resolution 8 bit for PWM
//#define NO_PWM_LOOP

#define MOTORUPDATE_FREQ 500                 // in Hz, 1000 is default
#define LOOPUPDATE_FREQ MOTORUPDATE_FREQ     // loop control sample rate equals motor update rate
#define DT_FLOAT (1.0/LOOPUPDATE_FREQ*1.024) // loop controller sample period dT
#define DT_INT_MS (1000/MOTORUPDATE_FREQ)    // dT, integer, (ms)
#define DT_INT_INV (MOTORUPDATE_FREQ)        // dT, integer, inverse, (Hz)

#define POUT_FREQ 25      // rate of ACC print output in Hz, 25 Hz is default
#define TRACE_OUT_FREQ 10 // rate of Trace Outoput in Hz, 10Hz is default 
#define LOCK_TIME_SEC 5   // gimbal fast lock time at startup 

// LP filter coefficient
#define LOWPASS_K_FLOAT(TAU) (DT_FLOAT/(TAU+DT_FLOAT))

// Number of sinus values for full 360 deg.
// NOW FIXED TO 256 !!!
// Reason: Fast Motor Routine using uint8_t overflow for stepping
#define N_SIN 256

#define SCALE_ACC 10000.0
#define SCALE_PID_PARAMS 1000.0f

// specifie input for VCC/Ubat measurement
#define ADC_VCC_PIN A3 

#define UBAT_ADC_SCALE (5.0 / 1023.0)
// voltage divider 
#define UBAT_R1 10000.0
#define UBAT_R2 2200.0
#define UBAT_SCALE ( (UBAT_R1 + UBAT_R2) / UBAT_R2 )

// STATES
#define S_FLAP_UP    1
#define S_FLAP_DOWN  2
#define S_INIT_UP    3
#define S_INIT_DOWN  4
#define S_INIT_PUMP  5
#define S_PUMP_DOWN  6

// Owen stuff
#define FLAP_RANGE 500

// RC data size and channel assigment
#define RC_DATA_SIZE  5
#define RC_DATA_MOTOR1 0
#define RC_DATA_MOTOR2  1
#define RC_DATA_AUX   2
#define RC_DATA_FPV_MOTOR1 3
#define RC_DATA_FPV_MOTOR2 4

// RC PPM pin A0, A1 or A2
#define RC_PIN_PPM_A2
//#define RC_PIN_PPM_A1
//#define RC_PIN_PPM_A0

#define RC_PIN_CH0 A2 
#define RC_PIN_CH1 A1 
#define RC_PIN_CH2 A0 

#define MIN_RC 1000
#define MID_RC 1500
#define MAX_RC 2000
#define MIN_RC_VALID 900
#define MAX_RC_VALID 2100
#define RC_DEADBAND 50
#define RC_TIMEOUT 100000

// rc switch on/off threshold (as offset from MID_RC)
#define RC_SW_THRESH 150

// PPM Decoder
#define RC_PPM_GUARD_TIME 4000
#define RC_PPM_RX_MAX_CHANNELS 32

// I2C Frequency
//#define I2C_SPEED 100000L     //100kHz normal mode
//#define I2C_SPEED 400000L   //400kHz fast mode
#define I2C_SPEED 800000L   //800kHz ultra fast mode

// Hardware Abstraction for Motor connectors,
// DO NOT CHANGE UNLES YOU KNOW WHAT YOU ARE DOING !!!
#define PWM_A_MOTOR1 OCR2A
#define PWM_B_MOTOR1 OCR1B
#define PWM_C_MOTOR1 OCR1A

#define PWM_A_MOTOR0 OCR0A
#define PWM_B_MOTOR0 OCR0B
#define PWM_C_MOTOR0 OCR2B


#ifdef DEBUG
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTF(x, y) Serial.print(x, y)
    #define DEBUG_PRINTLN(x) Serial.println(x)
    #define DEBUG_PRINTLNF(x, y) Serial.println(x, y)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTF(x, y)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_PRINTLNF(x, y)
#endif


#ifdef PWM_32KHZ_PHASE
  #define CC_FACTOR 32
#endif
#ifdef PWM_4KHZ_PHASE
  #define CC_FACTOR 4
#endif
#ifdef PWM_8KHZ_FAST
  #define CC_FACTOR 8
#endif
#ifdef NO_PWM_LOOP
  #define CC_FACTOR 1
#endif


#define LEDPIN_PINMODE             pinMode (8, OUTPUT);
#define LEDPIN_SWITCH              digitalWrite(8,!bitRead(PORTB,0));
#define LEDPIN_OFF                 digitalWrite(8, LOW);
#define LEDPIN_ON                  digitalWrite(8, HIGH);

// note: execution time for CH2_ON/CH2_OFF = 4 us
#define CH2_PINMODE                pinMode (4, OUTPUT);
#define CH2_OFF                    digitalWrite(4, LOW);
#define CH2_ON                     digitalWrite(4, HIGH);

#define CH3_PINMODE                pinMode (7, OUTPUT);
#define CH3_OFF                    digitalWrite(7, LOW);
#define CH3_ON                     digitalWrite(7, HIGH);

