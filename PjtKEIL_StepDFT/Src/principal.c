

#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, short int k);
extern short int LeSignal;
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	

//============================================================================	
	
		int tab[64];
		//tab	= malloc(64 * sizeof(int));
		//int tab[64]={0}; 
		for (short int i=0;i<64;i++){
			tab[i]=DFT_ModuleAuCarre(&LeSignal,i);
		}

}

