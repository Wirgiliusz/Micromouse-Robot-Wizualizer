/*
 * funkcje_rysujace.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_FUNKCJE_RYSUJACE_H_
#define INC_FUNKCJE_RYSUJACE_H_

#include "robot.h"

void inicjalizujRysowanie();

void rysujGranicePlanszy();
void rysujInformacje();
void rysujPozycje(int x, int y);
void rysujPredkosc(int predkosc);
void rysujEnkoder(int impulsy, int lewy);
void rysujCzujniki(int czujnik1, int czujnik2, int czujnik3, int czujnik4);

void rysujKwadratPusty(int posX, int posY);
void rysujKwadratPelny(int posX, int posY);
void rysujPolaczeniePrzedWejsciem(Robot* robot);
void rysujPolaczeniePoWejsciu(Robot* robot);
void rysujPolaczenia(Robot* robot);

#endif /* INC_FUNKCJE_RYSUJACE_H_ */
