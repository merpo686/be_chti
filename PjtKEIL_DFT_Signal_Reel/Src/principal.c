

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, short int k);
int tab[64];
short int signal[64];

void callback_systick(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (short int i=0;i<64;i++){
			tab[i]=DFT_ModuleAuCarre(signal,i);
	}
}
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
Systick_Period_ff(360000);
Systick_Prio_IT(12,callback_systick);


Init_TimingADC_ActiveADC_ff(ADC1,72);
Single_Channel_ADC(ADC1,2);
Init_Conversion_On_Trig_Timer_ff(ADC1,TIM2_CC2,225);
Init_ADC1_DMA1(0,signal);

SysTick_On;
SysTick_Enable_IT;	

//============================================================================	

while(1){}
	
		

}

