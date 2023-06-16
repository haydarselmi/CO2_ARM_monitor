#include "globaldecimport.h"
/**
 * @brief Produit un son selon si Actualisation_Buzzer l'a autorisé ou non.
 * @param int frequence la frequence du son emit.
 * @param int drapeau autorisation de l'émission du son.
 */
void NoteSound(int frequence,int drapeau){
	//drapeau 1 sigifie : on fait du bruit
	if(drapeau==1) {
		++cptINT;
		//20 000 représente 1 s(20000*50 micro secondes =1s) plus la valeur est petite plus le silence est court
		if(cptINT > 20000) {
			++cptINT2;
			//quand le compteur représente la moitié de la période du son voulant être émis
			if(cptSon == frequence) {
				cptSon = 0;										//RAZ du compteur
				LPC_GPIO1->FIOPIN ^= (1<<9);	//OU exclusif afin de réaliser un TOGGLE sur P1.9
			}
			//plus la valeur est grande plus le temps de bruit est long
			if(cptINT2 > 20000) {
				cptINT2 = 0;
				cptINT = 0;
			}
		}
		else{ cptSon=0; } //Afin de ne pas laisser cptSon dépasser la valeur de "fréquence" lorsque le buzzer est disable
	}
}

/**
 * @brief Enable ou disable le buzzer selon la nouvelle valeur de température mesurée.
 */
void Actualisation_Buzzer() {
	//Lorsque la valeur de la température lue n'est pas dans l'intervalle autorisé
	if ((Temp_Celsius > temp_levels.high) | (Temp_Celsius < temp_levels.low)) {
		drapeau = 1; //On active le buzzer
	}
	else{
		drapeau = 0; //On le rend disabled
	}
}
