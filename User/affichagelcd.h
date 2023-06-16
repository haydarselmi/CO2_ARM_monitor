#ifndef AFFICHAGELCD_H
#define AFFICHAGELCD_H

#include "touch/ili_lcd_general.h"
#include "touch/lcd_api.h"
#include "touch/touch_panel.h"
#include "globaldecimport.h"
#include <stdio.h>

/*
Fonction permettant de dessiner un rectangle de coordonnées (x,y)
de longueur lng, de largeur lrg, d'épaisseur de trait de bordure e,
plein ou vide, de couleur de bordure e_color et de fond bg_color
*/
void dessiner_rect(unsigned int x, unsigned int y, unsigned int lng, unsigned int lrg, unsigned int e, unsigned short plein, unsigned short e_color, unsigned short bg_color);
void dessiner_ligne(unsigned int x, unsigned int y, unsigned int l,unsigned int e, char orientation, unsigned short color);
void affichage_interface(int co2, int temperature);
void clear_screen(void);

#endif
