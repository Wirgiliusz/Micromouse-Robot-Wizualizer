/*
 * robot.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

typedef struct Robot {
	int posX;
	int posY;
	enum Orientacje{Polnoc, Zachod, Poludnie, Wschod} orientacja;
	enum Strony{Lewo, Prawo} strona;
	int odczytCzujnikow[4];
} Robot;

void jedzProsto(Robot* robot);
void obroc(Robot* robot, enum Strony strona);
void jedzPrawo(Robot* robot);
void jedzLewo(Robot* robot);
void jedzTyl(Robot* robot);

void skanujObszar(Robot* robot);

#endif /* INC_ROBOT_H_ */
