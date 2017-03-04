// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER1_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC_T1 (MICROSECONDS_PER_TIMER1_OVERFLOW / 1000)

volatile unsigned long timer1_millis;

/***************************************************************************/
/* Timer0 interrupt emulation
/***************************************************************************/
void TIMER0_isr_emulation (void) {

  unsigned long m = timer1_millis;
  
  m += MILLIS_INC_T1;
  timer1_millis = m;

}


unsigned long millisT1() {
  unsigned long m;
  uint8_t oldSREG = SREG;
  // disable interrupts while we read timer1_millis or we might get an
  // inconsistent value (e.g. in the middle of a write to timer1_millis)
  cli();
  m = timer1_millis;
  SREG = oldSREG;
  return m;
}

unsigned long microsT1() {
  
  unsigned long m;
  
  uint8_t oldSREG = SREG;
  uint8_t f;
  	
  cli();
  m = timer1_millis;
  f = (freqCounter & 0x01f) << 3;
  SREG = oldSREG;

  return ((m << 8) + f) * (64 / clockCyclesPerMicrosecond());
}

void delayT1(unsigned long ms)
{
  uint16_t start = (uint16_t)millisT1();
  while (ms > 0) {
    if (((uint16_t)millisT1() - start) >= 1) {
      ms--;
      start += 1;
    }
  }
}



