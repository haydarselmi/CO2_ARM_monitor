#ifndef GLOBALDEC_H
#define GLOBALDEC_H

#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

#define MAX_TRANSMIT_LENGTH 25


////////// SUPERGLOBAL VARS ///////////

temp_thresholds temp_levels = {0, 30};
co2_thresholds co2_levels = {400, 1000};

// Commandes bluetooth
char setTempTreshHigh[4] = "sth";
char setTempTreshLow[4] = "stl";
char setCo2TreshHigh[4] = "sch";
char setCo2TreshLow[4] = "scl";;

// Envoi et réception bluetooth
char receivedBuff[MAX_TRANSMIT_LENGTH]; // Buffer de réception

// Son
int cptSon 			= 0;
int cptINT 			= 0;
int cptINT2 		= 0;
int drapeau 		= 0;			// variables qui fait le son si sa valeur vaut 1, rien sinon
int frequence 	= 150;		//3000 hz, ((1/3000)/2)*10puissance6 représente la demi_période de 3000hz

// Température
int cptTemp 		 = 0;
int valeur_brute = 0;
int Temp_Celsius = 0;

// I2C
uint8_t I2C_master_write_buffer[2];
uint8_t I2C_master_read_buffer[6];

I2C_M_SETUP_Type I2C_M_init_cfg;
uint8_t measure_1s_co2 = 0;  // conditionne la demande de mesure du taux de CO2 au capteur SGP30

#endif
