//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2022     							 //
//===========================================================//
// File                : Programme de d�part
// Hardware Environment: Open1768	
// Build Environment   : Keil �Vision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_adc.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "touch\touch_panel.h"

#include "pinconfig.h"
#include "globaldec.h"
#include "affichagelcd.h"
#include "bluetooth.h"
#include "bluetoothCommands.h"
#include "son.h"
#include "timers.h"
#include "adc.h"
#include "co2_sensor.h"

//===========================================================//
// Function: Main
//===========================================================//
int main(void) {	
	
	// Initialisation du bus I2C
	i2c0PinConfig();
	I2C_Init(LPC_I2C0, 400000);
	I2C_Cmd(LPC_I2C0, ENABLE);
	// Initialisation du bluetooth
	bluetoothPinConfig();
	UART0_Init();
	
	lcd_Initializtion();
	
	timer0Config();
	sonPinConfig();
	initAdc();
	
	confirmConnection();
	timer2Config();
	timer1Config();
	
	while (1) {
		if(measure_1s_co2) {
			measure_read_co2_levels(LPC_I2C0);
			measure_1s_co2 = 0;
		}
		if(cptTemp == 20000) {					//Quand 1 seconde s'est �coul�e (50 micro secondes * 20000 =1s)
			LPC_ADC->ADCR |= (1<<24);	  	//ADC starts now
		}
		if(cptTemp == 40000) {					  //Quand 1 seconde de plus s'est �coul�e (50 micro secondes * 40000 =2s)
			cptTemp = 0;								  //Remise � z�ro du compteur
			valeur_brute = ADC_ChannelGetData(LPC_ADC, 1); //Lecture de la nouvelle valeur de la temp�rature
			
			Temp_Celsius = valeur_brute * 330 / (4096);     // 330 : Vref : 3.3 * 100 car 10mV=1�C divis� par 2^12 nb de bits de l'adc
			clear_screen();						                     //Screen clear avant le nouvel affichage
			//Nouvel affichage de la temp�rature et du taux de CO2
			affichage_interface(I2C_master_read_buffer[1] + (I2C_master_read_buffer[0] << 8), (int)Temp_Celsius);
			Actualisation_Buzzer();                        //Enable ou disable le buzzer selon la nouvelle valeur de temp�rature mesur�e
		}
	}
}

/**
 * @brief Interruption permettant de r�cup�rer la commande envoy�e par bluetooth.
 * Elle met � jour recievedBuff et ex�cute la commande afin de changer le seuil choisi.
 */
void UART0_IRQHandler(void) {
	unsigned int receivedChars = 0;    // nombre de caract�res re�us
	uint8_t receivedChar;              // caract�re re�u
	
	// On r�cup�re les caract�res envoy�s l'un apr�s l'autre en les pla�ant dans le buffer.
	do {
		receivedChar = UART_ReceiveByte(LPC_UART0);
		receivedBuff[receivedChars] = receivedChar;
		receivedChars++;
	} while((receivedChars <= MAX_TRANSMIT_LENGTH) && receivedChar != 0x2E);
	
	sendData(receivedBuff, receivedChars);
	sendData("\n",1);
	execute_command(receivedBuff);
	
	UART_ABClearIntPending(LPC_UART0, UART_AUTOBAUD_INTSTAT_ABEO);
}

/**
 * @brief Interruption qui permet de g�n�rer le bip lorque les seuils ne sont pas respect�s
 */
void TIMER0_IRQHandler(void) {
	cptSon += 50; 															// Incr�mentation du compteur de son de 50 micro secondes.
	++cptTemp; 																	// Incr�mentation du compteur de Temp�rature (+1 correspond � +50 micro secondes)
	NoteSound(frequence,drapeau); 							// drapeau d�signe la variable qui d�cide si oui ou non on fait quelque chose
	TIM_ClearIntPending(LPC_TIM0, TIM_MR1_INT); // Acquittement
}

/**
 * @brief Permet de passer le drapeau de mesure du taux de CO2 � 1,
 * interruption toutes les secondes.
 */
void TIMER1_IRQHandler(void) {
	measure_1s_co2 = 1;
	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
}


//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
