/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "robot.h"
#include "tim.h"
#include "funkcje_rysujace.h"

#define MAX_PREDKOSC 1000

void jedzProsto(Robot* robot) {
	// TODO //
	// Funkcja obslugujace jazde na wprost o 1 pole
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);

	for(int i = 1; i<=1; ++i){
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, i*0.1*MAX_PREDKOSC);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, i*0.1*MAX_PREDKOSC);
		HAL_Delay(300);
	}
	HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);

	rysujPolaczeniePrzedWejsciem(robot);
	HAL_Delay(500);
	rysujKwadratPusty(robot->posX, robot->posY);
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

	rysujKwadratPelny(robot->posX, robot->posY);
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
