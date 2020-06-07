/*
 * robot.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

#define NORTH   1 //00001000
#define WEST    2 //00000100
#define SOUTH   4 //00000010
#define EAST    8 //00000001

#define KONIEC  2 //00000001

typedef struct Robot {
	int jedz;
	int posX;
	int posY;
	enum Orientacje{Polnoc, Zachod, Poludnie, Wschod} orientacja;
	enum Strony{Lewo, Prawo} strona;
	int odczytCzujnikow[4];
	unsigned int impulsyEnkoderaR;
	unsigned int impulsyEnkoderaL;
	unsigned int odlegloscCzujnikaR;
	unsigned int odlegloscCzujnikaL;
	int e1;
	int e1_poprzednie;
	int e2;
	int e2_poprzednie;
	unsigned char labiryntPoznawany[4][4];
	int tabSciezki[4][4];
	int obecnosc[4][4];

} Robot;

Robot konstruktorRobota(int poczatkoweX, int poczatkoweY, enum Orientacje poczatkowaOrientacja);

void jedzProsto(Robot* robot);
void obroc(Robot* robot, enum Strony strona);
void jedzPrawo(Robot* robot);
void jedzLewo(Robot* robot);
void jedzTyl(Robot* robot);

void skanujObszar(Robot* robot);
void jedzKierunek(Robot* robot, enum Orientacje kierunek);
void znajdzNajkrotszaSciezkeRekurencja(Robot* robot, int posX, int posY);
void znajdzNajkrotszaSciezkeStart(Robot* robot);
void przejedzLabirynt(Robot* robot);
void przeszukajLabirynt(Robot* robot);

int odlegloscNaImpulsy(int odleglosc);

void wyslijWiadomosc(Robot* robot, enum Orientacje kierunek);

#endif /* INC_ROBOT_H_ */
