/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "robot.h"
#include "funkcje_rysujace.h"


void jedzProsto(Robot* robot) {
	// TODO //
	// Funkcja obslugujace jazde na wprost o 1 pole

	rysujPolaczeniePrzedWejsciem(robot);
	HAL_Delay(500);
	rysujKwadratPusty(robot);
	switch(robot->orientacja) {
	case 0:
		robot->posY--;
		break;
	case 1:
		robot->posX++;
		break;
	case 2:
		robot->posY++;
		break;
	case 3:
		robot->posX--;
		break;
	}

	rysujKwadratPelny(robot);
	rysujPolaczeniePoWejsciu(robot);

	rysujPozycje(robot->posX, robot->posY);
}

// strona = 0 - obrot w lewo;
// strona = 1 - obrot w prawo
void obroc(Robot* robot, int strona) {
	// TODO //
	// Funkcja obslugujaca obrot w zadanym kierunku

	switch(strona) {
	case 0:
		robot->orientacja--;
		robot->orientacja %=4;
		break;
	case 1:
		robot->orientacja++;
		robot->orientacja %=4;
		break;
	}
}

void jedzPrawo(Robot* robot) {
	obroc(robot, 1);
	jedzProsto(robot);
}

void jedzLewo(Robot* robot) {
	obroc(robot, 0);
	jedzProsto(robot);
}

void jedzTyl(Robot* robot) {
	obroc(robot, 1);
	obroc(robot, 1);
	jedzProsto(robot);
}

void skanujObszar() {

}
