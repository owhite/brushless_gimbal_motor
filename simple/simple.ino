// code based on 
// http://www.berryjam.eu/2015/04/driving-bldc-gimbals-at-super-slow-speeds-with-arduino/
//
// uses Martinez gimbal controller driver boards
// see: https://github.com/owhite/brushless_gimbal_motor/blob/master/docs/BGC.pdf
//
// these defines are relevant to those boards.
#define PWM_A_MOTOR1 3
#define PWM_B_MOTOR1 5
#define PWM_C_MOTOR1 6

#define PWM_A_MOTOR2 9 
#define PWM_B_MOTOR2 10
#define PWM_C_MOTOR2 11

const int pwmSin[] = {128, 132, 136, 140, 143, 147, 151, 155, 159, 162, 166,
		      170, 174, 178, 181, 185, 189, 192, 196, 200, 203, 207,
		      211, 214, 218, 221, 225, 228, 232, 235, 238, 239, 240,
		      241, 242, 243, 244, 245, 246, 247, 248, 248, 249, 250,
		      250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255,
		      255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		      255, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250,
		      250, 249, 248, 248, 247, 246, 245, 244, 243, 242, 241,
		      240, 239, 238, 239, 240, 241, 242, 243, 244, 245, 246,
		      247, 248, 248, 249, 250, 250, 251, 252, 252, 253, 253,
		      253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255,
		      255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253,
		      253, 252, 252, 251, 250, 250, 249, 248, 248, 247, 246,
		      245, 244, 243, 242, 241, 240, 239, 238, 235, 232, 228,
		      225, 221, 218, 214, 211, 207, 203, 200, 196, 192, 189,
		      185, 181, 178, 174, 170, 166, 162, 159, 155, 151, 147,
		      143, 140, 136, 132, 128, 124, 120, 116, 113, 109, 105,
		      101, 97, 94, 90, 86, 82, 78, 75, 71, 67, 64, 60, 56, 53,
		      49, 45, 42, 38, 35, 31, 28, 24, 21, 18, 17, 16, 15,
		      14, 13, 12, 11, 10, 9, 8, 8, 7, 6, 6, 5, 4, 4, 3, 3, 3,
		      2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
		      3, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14,
		      15, 16, 17, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 8,
		      7, 6, 6, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
		      1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 6, 7, 8,
		      8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 21, 24, 28, 31,
		      35, 38, 42, 45, 49, 53, 56, 60, 64, 67, 71, 75, 78, 82,
		      86, 90, 94, 97, 101, 105, 109, 113, 116, 120, 124};

int sineArraySize = 360;
int phaseShift = sineArraySize / 3; 
int currentStepA = 0;
int currentStepB = currentStepA + phaseShift;
int currentStepC = currentStepB + phaseShift;

void setup() {
  Serial.begin(115200);

  initBGC();
}

void loop() {
  // sweep back and forth
  for (int x = 0; x <= 1000; x += 1) { 
    setMotorPosition(2, x, 50);
    delayMicroseconds(500); 
  }
  for (int x = 1000; x >= 0; x -= 1) { 
    setMotorPosition(2, x, 50);
    delayMicroseconds(500); 
  }
}

void setMotorPosition(int motor, int position, int power) {
  int pin1, pin2, pin3;
  int pwm_a, pwm_b, pwm_c;

  power = constrain(power, 0, 255); // if only it were that easy

  if (motor == 1) {
    pin1 = PWM_A_MOTOR1;
    pin2 = PWM_B_MOTOR1;
    pin3 = PWM_C_MOTOR1;
  }
  if (motor == 2) {
    pin1 = PWM_A_MOTOR2;
    pin2 = PWM_B_MOTOR2;
    pin3 = PWM_C_MOTOR2;
  }

  // get number from the sin table, change amplitude from max
  pwm_a = (pwmSin[(position + currentStepA) % 360]) * (power / 255.0);
  pwm_b = (pwmSin[(position + currentStepB) % 360]) * (power / 255.0);
  pwm_c = (pwmSin[(position + currentStepC) % 360]) * (power / 255.0);

  analogWrite(pin1, pwm_a);
  analogWrite(pin2, pwm_b);
  analogWrite(pin3, pwm_c);
}

void initBGC() {
  // sets the speed of PWM signals. 
  TCCR0B = TCCR0B & 0b11111000 | 0x01;
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  pinMode(PWM_A_MOTOR1, OUTPUT); 
  pinMode(PWM_B_MOTOR1, OUTPUT); 
  pinMode(PWM_C_MOTOR1, OUTPUT); 
  
  pinMode(PWM_A_MOTOR2, OUTPUT); 
  pinMode(PWM_B_MOTOR2, OUTPUT); 
  pinMode(PWM_C_MOTOR2, OUTPUT); 
}

