#ifndef BLUETOOTH_COMMANDS_H
#define BLUETOOTH_COMMANDS_H

#include "globaldecimport.h"
#include "bluetooth.h"
#include "annexes.h"

// EN-TETE : TRAITEMENT DES COMMANDES BLUETOOTH

void set_temp_tresh_high(int newTreshold);
void set_temp_tresh_low(int newTreshold);
void set_co2_tresh_high(int newTreshold);
void set_co2_tresh_low(int newTreshold);
void execute_command(char command[]);

#endif
