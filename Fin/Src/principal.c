#include "DriverJeuLaser.h"
#include "DFT.h"
#include "GestionSon.h"
#include "bruitverre.h"
#include "Affichage_Valise.h"

int tab_dft[6];
short int signal[64];

//variables fin
//cod� pour six joueurs mais en realite on a que 4 afficheurs de score donc il ne faut utiliser que les quatres premieres frequences du pistolet ( ou changer dans le code le tableau de freq des joueurs) 
int tab_touches[6]={0};
int tab_score[6]={0};
short int tab_freq_joueur[6]={17,18,19,20,23,24};
int LEDACTIV;
int check_joueur(int joueur){
		if(tab_dft[joueur]>100000){
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
				Prepare_Afficheur(i+1,tab_score[i]);
				Prepare_Clear_LED(LEDACTIV-1);
				LEDACTIV=tab_dft[0]%4+1;
				Choix_Capteur(LEDACTIV);
				Prepare_Set_LED(LEDACTIV-1);
				Mise_A_Jour_Afficheurs_LED();
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
	
// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers

Systick_Period_ff(360000);
Systick_Prio_IT(12,callback_systick);


Init_TimingADC_ActiveADC_ff(ADC1,72);
Single_Channel_ADC(ADC1,2);
Init_Conversion_On_Trig_Timer_ff(ADC1,TIM2_CC2,225);
Init_ADC1_DMA1(0,signal);

Init_Affichage();
for (int j=0;j<4;j++)
{
	Prepare_Afficheur(j,0);

}
LEDACTIV=1;
Choix_Capteur(LEDACTIV);
Prepare_Set_LED(LEDACTIV-1);
Mise_A_Jour_Afficheurs_LED();
SysTick_On;
SysTick_Enable_IT;
//============================================================================	

while(1){}
}

