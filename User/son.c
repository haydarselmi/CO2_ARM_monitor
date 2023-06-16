#include "globaldecimport.h"
/**
 * @brief Produit un son selon si Actualisation_Buzzer l'a autoris� ou non.
 * @param int frequence la frequence du son emit.
 * @param int drapeau autorisation de l'�mission du son.
 */
void NoteSound(int frequence,int drapeau){
	//drapeau 1 sigifie : on fait du bruit
	if(drapeau==1) {
		++cptINT;
		//20 000 repr�sente 1 s(20000*50 micro secondes =1s) plus la valeur est petite plus le silence est court
		if(cptINT > 20000) {
			++cptINT2;
			//quand le compteur repr�sente la moiti� de la p�riode du son voulant �tre �mis
			if(cptSon == frequence) {
				cptSon = 0;										//RAZ du compteur
				LPC_GPIO1->FIOPIN ^= (1<<9);	//OU exclusif afin de r�aliser un TOGGLE sur P1.9
			}
			//plus la valeur est grande plus le temps de bruit est long
			if(cptINT2 > 20000) {
				cptINT2 = 0;
				cptINT = 0;
			}
		}
		else{ cptSon=0; } //Afin de ne pas laisser cptSon d�passer la valeur de "fr�quence" lorsque le buzzer est disable
	}
}

/**
 * @brief Enable ou disable le buzzer selon la nouvelle valeur de temp�rature mesur�e.
 */
void Actualisation_Buzzer() {
	//Lorsque la valeur de la temp�rature lue n'est pas dans l'intervalle autoris�
	if ((Temp_Celsius > temp_levels.high) | (Temp_Celsius < temp_levels.low)) {
		drapeau = 1; //On active le buzzer
	}
	else{
		drapeau = 0; //On le rend disabled
	}
}
