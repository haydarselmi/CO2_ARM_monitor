#include "LPC17xx_timer.h"
#include "timer.h"


void T0_Init()
{
	TIM_TIMERCFG_Type		Timer_Config_Structure;
  TIM_MATCHCFG_Type		Timer_MatchConfig_Structure;
	
	// Timer0  Initialization
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;					
	Timer_Config_Structure.PrescaleValue	= 1;							

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&Timer_Config_Structure);
	

	// Configuration of Match channels
	Timer_MatchConfig_Structure.MatchChannel = 1;	// MR1												
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;	// Interruption lorsqu'il y a un match									
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;	// remise  0 lorsqu'il y a un match										
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;	// ne pas arrter le timer lorsqu'il y a un match										
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	NVIC->ISER[0] = (1<<1); // Autoriser les interruptions du provenant du Timer 0
	
	Timer_MatchConfig_Structure.MatchValue = 50;	// valeur pour avoir une precision de 1 ms 
	TIM_ConfigMatch(LPC_TIM0,&Timer_MatchConfig_Structure);	// configuration de T0 selon les valeurs spcifies						
	
	
	TIM_Cmd(LPC_TIM0,ENABLE);	// start timer T0																					

	
}
