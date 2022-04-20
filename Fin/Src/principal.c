#include "DriverJeuLaser.h"
#include "DFT.h"
#include "GestionSon.h"
#include "bruitverre.h"
#include "Affichage_Valise.h"

int tab_dft[4];
short int signal[64];

//variables fin

int tab_touches[6]={0};
int tab_score[6]={0};
short int tab_freq_joueur[6]={17,18,19,20,23,24};

int check_joueur(int joueur){
		if(tab_dft[joueur]>1000000){
			return 1;
		}
		else
		{
			return 0;
		}
}

void callback_systick(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	short int i;
	for (i=0; i<6; i++){
			tab_dft[i]=DFT_ModuleAuCarre(signal,tab_freq_joueur[i]);
	}
	for (i=0; i<6; i++){
		if(check_joueur(i)==1){
			tab_touches[i]+=1;
			if (tab_touches[i]>10)
			{
				tab_score[i]+=1;
				StartSon();
				tab_touches[i]=0;
			}
		}
		else 
		{
			tab_touches[i]=0;
		}
	}
}
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================
CLOCK_Configure();
StopSon();
Timer_1234_Init_ff(TIM4,PeriodeSonMicroSec*72);
Active_IT_Debordement_Timer(TIM4,2,CallbackSon);

PWM_Init_ff(TIM3,3, 720);
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers

Systick_Period_ff(360000);
Systick_Prio_IT('0',callback_systick);
SysTick_On;
SysTick_Enable_IT;

Init_TimingADC_ActiveADC_ff(ADC1,72);
Single_Channel_ADC(ADC1,2);
Init_Conversion_On_Trig_Timer_ff(ADC1,TIM2_CC2,225);
Init_ADC1_DMA1(0,signal);

Init_Affichage();

//============================================================================	

while(1){}
}

