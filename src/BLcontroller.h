// owen change: needed to make platformio compiler happy
extern void TIMER0_isr_emulation();

#include "definitions.h"

/*
https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328

// CS BITS
CS02	CS01    CS00 	 DESCRIPTION
0	0 	0 	 Timer/Counter0 Disabled 
0	0 	1 	 No Prescaling
0	1 	0 	 Clock / 8
0	1 	1 	 Clock / 64
1	0 	0 	 Clock / 256
1	0 	1 	 Clock / 1024

CS12	 CS11 	 CS10 	 DESCRIPTION
0	0 	0 	 Timer/Counter1 Disabled 
0	0 	1 	 No Prescaling
0	1 	0 	 Clock / 8
0	1 	1 	 Clock / 64
1	0 	0 	 Clock / 256
1	0 	1 	 Clock / 1024

CS22	 CS21 	 CS20 	 DESCRIPTION
0	0 	0 	 Timer/Counter2 Disabled 
0	0 	1 	 No Prescaling
0	1 	0 	 Clock / 8
0	1 	1 	 Clock / 32
1	0 	0 	 Clock / 64
1	0 	1 	 Clock / 128
1	1 	0 	 Clock / 256
1	1 	1 	 Clock / 1024 


// WAVEFORM GENERATOR BITS
	WGM02	WGM01	WGM00	 DESCRIPTION	 	TOP
0	0 	0	0	 Normal 	 	0xFF
1	0	0	1	 PWM, Phase Corrected	0xFF
2	0	1	0	 CTC			OCR0A
3	0	1	1	 Fast PWM		0xFF
4	1	0	0	 Reserved	 	-
5	1	0	1	 Fast PWM, Phase Corr	OCR0A
6	1	1	0	 Reserved		-
7	1	1	1	 Fast PWM		OCR0A

MODE	WGM13	WGM12	WGM11	WGM10	 DESCRIPTION            	 TOP
0	 0	 0 	0	0	 Normal 	                 0xFFFF
1	0	0	0	1	 PWM, Phase Corrected, 8bit	 0x00FF
2	0	0	1	0	 PWM, Phase Corrected, 9bit	 0x01FF
3	0	0	1	1	 PWM, Phase Corrected, 10bit 	 0x03FF 
4	0	1	0	0        CTC	                         OCR1A 
5	0	1	0	1	 Fast PWM, 8bit 	          0x00FF 
6	0	1	1	0	 Fast PWM, 9bit 	          0x01FF 
7	0	1	1	1	 Fast PWM, 10bit 	          0x03FF 
8	1	0	0	0	 PWM, Phase and Frequency Corr    ICR1 
9	1	0	0	1	 PWM, Phase and Frequency Corr    OCR1A 
10	1	0	1	0	 PWM, Phase Correct 	          ICR1 
11	1	0	1	1	 PWM, Phase Correct 	         OCR1A
12	1	1	0	0	 CTC	                         ICR1
13	1	1	0	1	 RESERVED	 
14	1	1	1	0	 Fast PWM 	                  ICR1 
15	1	1	1	1	 Fast PWM	                  OCR1A 

MODE	WGM21	WGM20	 DESCRIPTION	          TOP
0	0	0	 Normal 	         0xFF
1	0	1	 PWM Phase Corrected	 
2	1	0	 CTC	                  OCR2
3	1	1	 Fast PWM 	 



x = Timer Number
 	7 bit	 6 bit 	 5 bit 	 4 bit 	 3 bit 	 2 bit 	 1 bit 	 0 bit     Description
TCCRxA	COMxA1	 COMxA0  COMxB1  COMxB0  -	 -	 WGMx1	 WGMx0     Timer/Counter Control Register x A (x=0,2)

TCCR1B	ICNC1	 ICES1	 -	 WGM13	 WGM12	 CS12	 CS11	CS10 
TCCRxB	FOCxA    FOCxB   -       -       WGMx2   CSx2    CSx1    CSx0      Timer/Counter Control Register x B

TIMSKx	-        -       -       -       -       OCIExB  OCIExA  TOIEx     Timer/Counter Interrupt Mask Register
TIFRx	-	 -	 -	 -       -       OCFxB	 OCFxA   TOVx      Timer/Counter Interrupt Flag Register
TCNTx                                                                      Timer/Counter Register (stores the counter value)
OCRxA                                                                      Output Compare Register x A
OCRxB                                                                      Output Compare Register x B


*/
void initBlContmotor2er() 
{
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

#ifdef PWM_8KHZ_FAST
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01)| _BV(WGM10); 
  TCCR0B = _BV(CS01);
  TCCR1A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM10); 
  TCCR1B = _BV(WGM12) | _BV(CS11);
  TCCR2A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM21)| _BV(WGM20);
  TCCR2B = _BV(CS21);
#endif

#ifdef PWM_32KHZ_PHASE
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); 
  TCCR0B = _BV(CS00);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(CS10);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS20);
#endif

#ifdef PWM_4KHZ_PHASE
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); 
  TCCR0B = _BV(CS01);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(CS11);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS21);
#endif

  // enable Timer 1 interrupt
  TIMSK1 |= _BV(TOIE1);
  
  // disable arduino standard timer interrupt
  TIMSK0 &= ~_BV(TOIE1);
  
  sei();

  // Enable Timer1 Interrupt for Motor Control
  OCR2A = 0;  //11  APIN
  OCR2B = 0;  //D3
  OCR1A = 0;  //D9  CPIN
  OCR1B = 0;  //D10 BPIN
  OCR0A = 0;  //D6
  OCR0B = 0;  //D5 
}

 
void MoveMotorPosSpeed(uint8_t motorNumber, int MotorPos, uint16_t maxPWM)
{
  uint16_t posStep;
  uint16_t pwm_a;
  uint16_t pwm_b;
  uint16_t pwm_c;

  // fetch pwm from sinus table
  posStep = MotorPos & 0xff;
  pwm_a = pwmSinMotor[(uint8_t)posStep];
  pwm_b = pwmSinMotor[(uint8_t)(posStep + 85)];
  pwm_c = pwmSinMotor[(uint8_t)(posStep + 170)];
 
  // apply power factor
  pwm_a = maxPWM * pwm_a;
  pwm_a = pwm_a >> 8;
  pwm_a += 128;

  pwm_b = maxPWM * pwm_b;
  pwm_b = pwm_b >> 8;
  pwm_b += 128;
  
  pwm_c = maxPWM * pwm_c;
  pwm_c = pwm_c >> 8;
  pwm_c += 128;
  
  // set motor pwm variables
  if (motorNumber == 0)
  {
    pwm_a_motor0 = (uint8_t)pwm_a;
    pwm_b_motor0 = (uint8_t)pwm_b;
    pwm_c_motor0 = (uint8_t)pwm_c;
  }
 
  if (motorNumber == 1)
  {
    pwm_a_motor1 = (uint8_t)pwm_a;
    pwm_b_motor1 = (uint8_t)pwm_b;
    pwm_c_motor1 = (uint8_t)pwm_c;
  }
}


void calcSinusArray()
{
  for(int i=0; i<N_SIN; i++)
  {
    pwmSinMotor[i] =  sin(2.0 * i / N_SIN * 3.14159265) * 127.0;
  }  
}

void initMotorStuff()
{
  cli();
  calcSinusArray();
  sei();
}

/********************************/
/* Motor Control IRQ Routine    */
/********************************/
// is called every 31.5us
// minimize interrupt code (20 instructions) 
ISR( TIMER1_OVF_vect )
{
  freqCounter++;  
  if(freqCounter==(CC_FACTOR*1000/MOTORUPDATE_FREQ))
  {
    freqCounter=0;
    
    PWM_A_MOTOR0 = pwm_a_motor0;
    PWM_B_MOTOR0 = pwm_b_motor0;
    PWM_C_MOTOR0 = pwm_c_motor0;

    PWM_A_MOTOR1 = pwm_a_motor1;
    PWM_B_MOTOR1 = pwm_b_motor1;
    PWM_C_MOTOR1 = pwm_c_motor1;  
    
    // update event
    motorUpdate = true;
  }
 
  
  // care for standard timers every 1 ms
  if ((freqCounter & 0x01f) == 0) {
    TIMER0_isr_emulation();
  }


}


/**********************************************************/
/* voltage compensation                                   */
/*   measure power supply voltage and compensate          */
/*   motor power accordingly                              */
/**********************************************************/
void voltageCompensation () {
  int uBatValue;
  float pwmMotorScale;
  
  // measure uBat, 190 us
  uBatValue = analogRead(ADC_VCC_PIN); // 118 us
  uBatValue_f = (float)uBatValue * UBAT_ADC_SCALE * UBAT_SCALE;   
  utilLP_float(&voltageBat, uBatValue_f, LOWPASS_K_FLOAT(0.1)); // tau = 1 sec
   
  if (config.motorPowerScale) {
    // calculate scale factor for motor power (70us)
    if (voltageBat*100 > config.cutoffVoltage) {  // switch off if battery voltage below cutoff
      pwmMotorScale = (config.refVoltageBat * 0.01)/voltageBat;
    } else {
      pwmMotorScale = 0;
    }
  } else {
    pwmMotorScale = 1.0;
  }
  
  // 44us
  if (fpvModeFreezeMotor1==true) {
    maxPWMmotorMotor1Scaled = config.maxPWMfpvMotor1 * pwmMotorScale;  // fpv freeze mode
  } else {
    maxPWMmotorMotor1Scaled = config.maxPWMmotorMotor1 * pwmMotorScale;
  }
  maxPWMmotorMotor1Scaled = constrain(maxPWMmotorMotor1Scaled, 0, 255);

  if (fpvModeFreezeMotor2==true) {
    maxPWMmotorMotor2Scaled = config.maxPWMfpvMotor2 * pwmMotorScale; // fpv freeze mode
  } else {
    maxPWMmotorMotor2Scaled = config.maxPWMmotorMotor2 * pwmMotorScale;
  }
  maxPWMmotorMotor2Scaled = constrain(maxPWMmotorMotor2Scaled, 0, 255);
  
}


// switch off motor power
void motorPowerOff() {
  MoveMotorPosSpeed(config.motorNumberMotor1, 0, 0); 
  MoveMotorPosSpeed(config.motorNumberMotor2, 0, 0);
}

