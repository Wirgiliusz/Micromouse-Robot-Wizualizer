/*
 * funkcje_rysujace.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "funkcje_rysujace.h"

void rysujKwadratPusty(Robot* robot) {
	BSP_LCD_DrawRect(robot->posX*30+4, robot->posY*30+4, 22, 22);
}

void rysujKwadratPelny(Robot* robot) {
	BSP_LCD_FillRect(robot->posX*30+4, robot->posY*30+4, 22, 22);
}
