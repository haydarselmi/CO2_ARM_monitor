#include "pinconfig.h"

/**
 * @brief Configuer les broches P0.2 (resp P0.3) en mode TXD (resp RXD) 
 */
void bluetoothPinConfig(void) {
	// Structures de config
	PINSEL_CFG_Type config2; // P0.2
	PINSEL_CFG_Type config3; // P0.3
	
	// Config de P0.2 en TXD0
	config2.Portnum = PINSEL_PORT_0;
	config2.Pinnum =PINSEL_PIN_2;
	config2.Funcnum = PINSEL_FUNC_1; // Fonction TXD0
	config2.Pinmode =PINSEL_PINMODE_PULLDOWN; // Rsistance de pulldown 
	config2.OpenDrain = PINSEL_PINMODE_NORMAL; // Opendrain normal

	// Config de P0.3 en RXD0
	config3.Portnum = PINSEL_PORT_0;
	config3.Pinnum =PINSEL_PIN_3;
	config3.Funcnum = PINSEL_FUNC_1; // Fonction RXD0
	config3.Pinmode =PINSEL_PINMODE_PULLUP; // Rsistance de pullup 
	config3.OpenDrain = PINSEL_PINMODE_NORMAL; // Opendrain normal

	// Choix des entres sorties
	LPC_GPIO0->FIODIR |= ~(1<<3)|(1<<2);
	LPC_GPIO0->FIOMASK &= ~((1<<3)|(1<<2));
	
	
  PINSEL_ConfigPin(&config2);
	PINSEL_ConfigPin(&config3);
}

/**
 * @brief Permet de configurer les broches pour le péripherique du son.
 */
void sonPinConfig(void) {
	LPC_GPIO1->FIODIR |= (1<<9); // P1.9 en sortie (pour interruption)
	LPC_GPIO1->FIOMASK &= ~(1<<9);//Empêche la modification du bit 8 du registre 1
}

/**
 * @brief Permet de configurer les PINS P0.27 et P0.28
 * en mode SDA et SCL respectivement pour le bus I2C0. 
 */
void i2c0PinConfig(void) {
	// Instanciation de structures afin de configurer les PINS du I2C0
	PINSEL_CFG_Type config_i2c0_sda;
	PINSEL_CFG_Type config_i2c0_scl;
	
	// Paramétrage de la strucutre de configuration pour le pin des données serie.
	config_i2c0_sda.Portnum = PINSEL_PORT_0;
	config_i2c0_sda.Pinnum = PINSEL_PIN_27;
	config_i2c0_sda.Funcnum = PINSEL_FUNC_1;
	config_i2c0_sda.Pinmode = PINSEL_PINMODE_PULLUP;
	config_i2c0_sda.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	// Paramétrage de la strucutre de configuration pour le pin de l'horloge.
	config_i2c0_scl.Portnum = PINSEL_PORT_0;
	config_i2c0_scl.Pinnum = PINSEL_PIN_28;
	config_i2c0_scl.Funcnum = PINSEL_FUNC_1;
	config_i2c0_scl.Pinmode = PINSEL_PINMODE_PULLUP;
	config_i2c0_scl.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	// Configuration des PINS pous la communication avec le bus I2C0
	PINSEL_ConfigPin(&config_i2c0_sda);
	PINSEL_ConfigPin(&config_i2c0_scl);
}
