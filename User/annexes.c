#include "annexes.h"

////==============================================================================//
//// But: Fonctions annexes aux proc�dures de traitement des commandes bluetooth
////==============================================================================//

/* ------------------------- Fonctions priv�es ---------------------------- */
/**
	* @brief Exponentiation rapide
	* @param (int) x
	* @param (int) y
	* @return x � la puissance y
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
	* @brief Obtenir la longueur d'ue chaine de caract�re
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
/* ---------------------- Fin des fonctions priv�es -------------------------- */

/* ------------------------- Fonctions publiques ----------------------------- */
/**
	* @brief V�rifier qu'une chaine contient une aure chaine
	* @param (char[]) chaine1
	* @param (char[]) chaine2
	* @return (int) L'indice dans chaine1 � partir duquel chaine2 commence. -1 si chaine1 ne contient pas chaine2
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
	* @brief Changer une partie d�limit�e d'une cha�ne en entier
	* @param chaine   : (char[])
	* @param offset   : (int) Indice indiquant o� commencer la conversion
	* @param end      : (int) Indice indiquant ou arr�ter la conversion
	* @return (int)   : r�sultat de la conversion
	* @note La chaine � convertir doi repr�senter un entier
*/
int atoint(char chaine[], int offset, int end){

	char t[5]; // Contient le seuil i,diqu� par l'utilisateur
	for(i=offset; i<end; i++){
		t[i-offset] = chaine[i];
		//res = res + (puiss(10, end-start-1)*(chaine[i]-'0'));
	}
	return atoi(t); //sign*res;
}

/* -------------------------------------- EOF ------------------------------------------ */
