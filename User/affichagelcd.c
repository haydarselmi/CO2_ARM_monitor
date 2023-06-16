#include "affichagelcd.h"

void dessiner_ligne(unsigned int x, unsigned int y, unsigned int l,unsigned int e, char orientation, unsigned short color)
{
	int i,j;
	if(orientation=='v')
	{
		for(j=y;j<=y+l;j++)
		{
			lcd_SetCursor(x,j);//on place le curseur à la bonne position
			rw_data_prepare();
			for(i=0;i<=e;i++)
			{
				write_data(color);//on trace un point et on passe à la position suivante
			}
		}
	}
	else//orientation='h'
	{
		for(j=y;j<=y+e;j++)
		{
			lcd_SetCursor(x,j);//on place le curseur à la bonne position
			rw_data_prepare();
			for(i=0;i<=l;i++)
			{
				write_data(color);//on trace un point et on passe à la position suivante
			}
		}
	}
}

void dessiner_rect(unsigned int x, unsigned int y, unsigned int lng, unsigned int lrg, unsigned int e, unsigned short plein, unsigned short e_color, unsigned short bg_color)
{
	//dessiner fond
	if(plein==1)
	{
		dessiner_ligne(x,y,lng,lrg,'h',bg_color);
	}
	
	//dessiner bordures
	dessiner_ligne(x,y,lng,e,'h',e_color);
	dessiner_ligne(x+lng-e,y,lrg,e,'v',e_color);
	dessiner_ligne(x,y+lrg-e,lng,e,'h',e_color);
	dessiner_ligne(x,y,lrg,e,'v',e_color);
}

/**
 * @brief Permet d'afficher sur l'écran lcd les informations des capteurs. 
 * Taux co2 et temperature.
 * @param float co2.
 * @param float temperature.
 */
void affichage_interface(int co2, int temperature) {
		char temp_string[4];
		unsigned int co2_text_color = White;
		unsigned int temp_text_color = White;
		
		if(temperature > temp_levels.high) {
			temp_text_color = Red;
		} else if(temperature < temp_levels.low) {
			temp_text_color = Green;	
		}
		
		if(co2 > co2_levels.high) {
			co2_text_color = Red;
		} else if(co2 < co2_levels.low) {
			co2_text_color = Green;
		}
		
		
		sprintf(temp_string, "%d", co2);
	  LCD_write_english_string (22,50,"Taux de CO2 ppm",White,Blue);
		dessiner_rect(20,110,180,2,2,1,White,White);
		LCD_write_english_string (40,65, temp_string, co2_text_color, Blue);
		LCD_write_english_string (100,65, "ppm",White,Blue);
		
		LCD_write_english_string (22,120,"Temperature C",White,Blue);
		sprintf(temp_string, "%d", temperature);
		LCD_write_english_string (40,135, temp_string ,temp_text_color, Blue);
		LCD_write_english_string (100,135, "C" ,White,Blue);
		dessiner_rect(20,190,180,2,2,1,White,White);
}

/**
 * @brief Permet d'effacer les informations affichées sur l'ecran.
 * A utiliser uniquement quand ces valeurs changent.
 */
void clear_screen() {
	dessiner_rect(39, 64, 119, 20, 2, 1, Blue, Blue);
	dessiner_rect(39, 134, 119, 20, 2, 1, Blue, Blue);
}
