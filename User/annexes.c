#include "annexes.h"

////==============================================================================//
//// But: Fonctions annexes aux procédures de traitement des commandes bluetooth
////==============================================================================//

/* ------------------------- Fonctions privées ---------------------------- */
/**
	* @brief Exponentiation rapide
	* @param (int) x
	* @param (int) y
	* @return x à la puissance y
*/
int puiss(int x, int y){
	int Y = y;
	int X = x;
	int p = 1; // result
	while(Y>0){
		if(Y%2==1){
			p = p*X;
		}
		X = X*X;
		Y = Y/2;
	}
	return p;
}

/**
	* @brief Obtenir la longueur d'ue chaine de caractère
	* @param chaine : la chaine
	* @return longueur de la chaine
*/
int length(char chaine[]){

	int res = 0;
	while(chaine[res] != '\n' & chaine[res] != '\0'){
		res ++;
	}
	return res;
}
/* ---------------------- Fin des fonctions privées -------------------------- */

/* ------------------------- Fonctions publiques ----------------------------- */
/**
	* @brief Vérifier qu'une chaine contient une aure chaine
	* @param (char[]) chaine1
	* @param (char[]) chaine2
	* @return (int) L'indice dans chaine1 à partir duquel chaine2 commence. -1 si chaine1 ne contient pas chaine2
*/
int contains(char chaine1[], char chaine2[]){
	int l1 = length(chaine1);
	int l2 = length(chaine2);
	int res = -1;
	
	if(l1 > l2){
		if(l2 != 0){
			int i = 0;
			while(chaine1[i] == chaine2[i]){
				i++;
			}
			if (i == l2){
				res = i-1;
			}
		}
	}
	return res;
}

int i;

/**
	* @brief Changer une partie délimitée d'une chaîne en entier
	* @param chaine   : (char[])
	* @param offset   : (int) Indice indiquant où commencer la conversion
	* @param end      : (int) Indice indiquant ou arrêter la conversion
	* @return (int)   : résultat de la conversion
	* @note La chaine à convertir doi représenter un entier
*/
int atoint(char chaine[], int offset, int end){

	char t[5]; // Contient le seuil i,diqué par l'utilisateur
	for(i=offset; i<end; i++){
		t[i-offset] = chaine[i];
		//res = res + (puiss(10, end-start-1)*(chaine[i]-'0'));
	}
	return atoi(t); //sign*res;
}

/* -------------------------------------- EOF ------------------------------------------ */
