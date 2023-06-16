#include "bluetoothCommands.h"

////===================================================================//
//// But: Définir les procédures de traitement des commandes bluetooth
////===================================================================//

/**
 * @brief Permet de changer le seuil haut de la temperature
 * @param int le nouveau seuil haut à affecter dans la structure.
 */
void set_temp_tresh_high(int newTreshold){
	temp_levels.high = newTreshold;
}

/**
 * @brief Permet de changer le seuil bas de la temperature
 * @param int le nouveau seuil bas à affecter dans la structure.
 */
void set_temp_tresh_low(int newTreshold){
	temp_levels.low = newTreshold;
}

/**
 * @brief Permet de changer le seuil haut du taux de CO2
 * @param int le nouveau seuil haut à affecter dans la structure.
 */
void set_co2_tresh_high(int newTreshold){
	co2_levels.high = newTreshold;
}

/**
 * @brief Permet de changer le seuil bas du taux de CO2
 * @param int le nouveau seuil bas à affecter dans la structure.
 */
void set_co2_tresh_low(int newTreshold){
	co2_levels.low = newTreshold;
}

/**
 * @brief Permet d'executer la commande reçue par bluetooth
 * qui est contenue dans receivedBuff.
 * @param char[] la commande à executer.
 */
void execute_command(char command[]) {
	// Comportement dépendant de la commande reçue
	int tresh = 0; // Nouveau seuil fourni par l'utilisateur
	
	// Commandes de changement de seuil ------------------------------------------
	if(contains(command, setTempTreshHigh) != -1){
		tresh = atoint(command, contains(command, setTempTreshHigh)+2, length(command));
    set_temp_tresh_high(tresh);
		sendData("Done !\n", 7);
	}
	else if(contains(command, setTempTreshLow) != -1){
		tresh = atoint(command, contains(command, setTempTreshLow)+2, length(command));
		set_temp_tresh_low(tresh);
		sendData("Done !\n", 7);
	}
	else if(contains(command, setCo2TreshHigh) != -1){
		tresh = atoint(command, contains(command, setCo2TreshHigh)+2, length(command));
		set_co2_tresh_high(tresh);
		sendData("Done !\n", 7);
	}
	else if(contains(command, setCo2TreshLow) != -1){
		tresh = atoint(command, contains(command, setCo2TreshLow)+2, length(command));
		set_co2_tresh_low(tresh);
		sendData("Done !\n", 7);
	}
	else{ // Commande invalide --------------------------------------
		sendData("Invalid request\n", 16);
	}
}
