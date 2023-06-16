#ifndef CONSTANTES_H
#define CONSTANTES_H


typedef enum {jaune,vert,rouge,bleu} touche ;

/**
 * @brief	Declaration de la structure des seuils de CO2.
 * utilise pour choisir une couleur lors de l'affichage des valeurs.
 */
typedef struct {
	int low;
	int high;
} co2_thresholds;

/**
 * @brief	Declaration de la structure des seuils de temperature.
 * utilise pour choisir une couleur lors de l'affichage des valeurs.
 */
typedef struct {
	int low;
	int high;
} temp_thresholds;






#endif
