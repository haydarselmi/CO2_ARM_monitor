#ifndef GLOBALDECIMPORT_H
#define GLOBALDECIMPORT_H

#include <stdint.h>
#include "constantes.h"
#include "lpc17xx_i2c.h"

// Gestion des seuils de temperature et du taux de co2
extern temp_thresholds temp_levels;
extern co2_thresholds co2_levels;

// Texte des commandes bluetooth
extern char setTempTreshHigh[4];
extern char setTempTreshLow[4];
extern char setCo2TreshHigh[4];
extern char setCo2TreshLow[4];

// Buffers d'envoi et de réception de texte par bluetooth
extern char receivedBuff[25]; // Buffer de réception

// Son
extern int cptSon;
extern int cptINT;
extern int cptINT2;
extern int drapeau;		// variables qui conditonne l'émission d'un son si sa valeur vaut 1, rien sinon
extern int frequence;

// Temp
extern int cptTemp;
extern int valeur_brute;
extern int Temp_Celsius;

// I2C communication buffer et flag ainsi que le drapeau afin
extern uint8_t I2C_master_write_buffer[2];
extern uint8_t I2C_master_read_buffer[6];
extern I2C_M_SETUP_Type I2C_M_init_cfg;
/* 
	Drapeau qui au bout d'une seconde indique qu'il est temps de faire
	une mesure du taux de CO2
*/
extern uint8_t measure_1s_co2;

#endif
