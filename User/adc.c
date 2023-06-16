#include "adc.h"

/**
 *	@brief Initialisation de l'ADC en le faisant fonctionner sur son channel 1
 */
void initAdc(void) {
  LPC_PINCON->PINSEL1 |= (1<<16);// AD0.1 is available
  LPC_SC->PCONP |= (1<<12);			 // Vcc is going to ADC
	LPC_ADC->ADCR |=  (1<<1)|			 // AD0.1 input enable
										(1<<21)|		 // ADC is operational (not in power down)
										(1<<24);	   // starts now
}
