#include <msp430fg4619.h>

int doISR = 0;
int testInterrupt(){ return doISR == 1; }
int resetInterruptCounter() {doISR = 0;}

void Init_timer_interrupt_10ms(){
  TACTL = 0;
  TACTL |= TASSEL_2 | ID_1 | MC_1;

  TACCTL0 = 0;
  TACCTL0 |= CCIE ;
  
  TACCR0 =  40000;

}
// 8MHz/2 = 4MHz, 1/(4M)*40000s=0.01s=10ms

void Run_timer_interrupt(){
	TACTL &=~ TACLR;
	TACTL |= MC_1;
	TACTL |= ID_1;
}

#pragma vector=TIMERA0_VECTOR 
__interrupt void Timer_A (void) 
{
	static int cnt = 60;

	if (cnt == 0) {
		cnt = 60;
		doISR = 1;
	}

	cnt--;
}
