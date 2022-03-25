

#include "DriverJeuLaser.h"

extern void CallbackSon(void);
extern int PeriodeSonMicroSec;
extern short SortieSon;
extern int i;

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

Timer_1234_Init_ff(TIM4,PeriodeSonMicroSec*72000000);
Active_IT_Debordement_Timer(TIM4,2,CallbackSon);
	
	
	

//============================================================================	
	
	
while	(1)
	{
	}
}

