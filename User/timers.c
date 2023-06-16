#include "timers.h"

/**
 *	@brief Initialisation du timer 0 pour la gestion du son
 */
void timer0Config() {
	TIM_TIMERCFG_Type		Timer_Config_Structure;
  TIM_MATCHCFG_Type		Timer_MatchConfig_Structure;
	
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;					
	Timer_Config_Structure.PrescaleValue	= 1;	

	// Configuration of Match channels
	Timer_MatchConfig_Structure.MatchChannel = 1;											
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	Timer_MatchConfig_Structure.MatchValue = 50;
	
	NVIC->ISER[0] = (1<<1);
	
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&Timer_Config_Structure);
	TIM_ConfigMatch(LPC_TIM0,&Timer_MatchConfig_Structure);
	TIM_Cmd(LPC_TIM0,ENABLE);
}

/**
 * @brief Initialise le timer 1 avec une précision de 1ms
 * afin de cadancer et d'initier les lectures des valeurs de taux de CO2
 * à partir du capteur CO2 en effectuant une interruption à chaque match.
 * interruption toutes les 1s, fréquence de 1Hz car le capteur CO2 SGP30
 * utilise un algorithme de compensation qui ralentit le processus mais la lecture
 * est en réel de l'ordre de quelques ms.
 */
void timer1Config(void) {
	TIM_TIMERCFG_Type Timer_Config_Structure;
	TIM_MATCHCFG_Type Timer_MatchConfig_Structure;

	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;
	Timer_Config_Structure.PrescaleValue = 1000;
	
	Timer_MatchConfig_Structure.MatchChannel = 0;
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	Timer_MatchConfig_Structure.MatchValue = 1000;

	NVIC->ISER[0] |= (1<<2);
	
	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &Timer_Config_Structure);
	TIM_ConfigMatch(LPC_TIM1,&Timer_MatchConfig_Structure);
	TIM_Cmd(LPC_TIM1,ENABLE);
}

/**
 *	@brief Mettre en place un temps d'attente de 14s après l'envoi d'une commande I2C afin
 *	de laisser le temps au capteur SGP30 de calculer le taux de co2.
 *	Puis, renvoyer une requête de lecture de ce taux.
 */
void timer2Config(void) {
	TIM_TIMERCFG_Type Timer_Config_Structure;
	TIM_MATCHCFG_Type Timer_MatchConfig_Structure;
	
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;
	Timer_Config_Structure.PrescaleValue = 1000;
	
	Timer_MatchConfig_Structure.MatchChannel = 0;
	Timer_MatchConfig_Structure.IntOnMatch   = FALSE;
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	Timer_MatchConfig_Structure.MatchValue = 14;
	
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &Timer_Config_Structure);
	TIM_ConfigMatch(LPC_TIM2,&Timer_MatchConfig_Structure);
	TIM_Cmd(LPC_TIM2,ENABLE);
}
