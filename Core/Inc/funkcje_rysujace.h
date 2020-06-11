/*
 * funkcje_rysujace.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_FUNKCJE_RYSUJACE_H_
#define INC_FUNKCJE_RYSUJACE_H_

#include "robot.h"

#define WSP_WIELKOSCI 2 // Labirynt 4x4
//#define WSP_WIELKOSCI 1 // Labirynt 8x8
//#define WSP_WIELKOSCI 0.5 // Labirynt 16x16

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
void rysujDebug(int wiedomosc);

#endif /* INC_FUNKCJE_RYSUJACE_H_ */
