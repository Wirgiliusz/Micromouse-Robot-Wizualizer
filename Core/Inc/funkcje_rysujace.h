/*
 * funkcje_rysujace.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_FUNKCJE_RYSUJACE_H_
#define INC_FUNKCJE_RYSUJACE_H_

#include "robot.h"

void rysujGranicePlanszy();
void rysujInformacje();
void rysujPozycje(int x, int y);

void rysujKwadratPusty(Robot* robot);
void rysujKwadratPelny(Robot* robot);
void rysujPolaczeniePrzedWejsciem(Robot* robot);
void rysujPolaczeniePoWejsciu(Robot* robot);

#endif /* INC_FUNKCJE_RYSUJACE_H_ */
