/*
 * funkcje_rysujace.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "funkcje_rysujace.h"
#include "stm32f429i_discovery_lcd.h"
#include <stdio.h>


void inicjalizujRysowanie() {
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font12);
	rysujGranicePlanszy();
	rysujInformacje();
	rysujPozycje(0,0);
	rysujPredkosc(500);
}

void rysujGranicePlanszy() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawRect(0, 0, 239, 239);
}

void rysujInformacje() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, 240, (uint8_t*)"Ruch: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 250, (uint8_t*)"Pozycja: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 260, (uint8_t*)"Predkosc: ", LEFT_MODE);
}

void rysujPozycje(int x, int y) {
	char posX[2];
	char posY[2];
	sprintf(posX, "%d", x);
	sprintf(posY, "%d", y);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(70, 250, (uint8_t*)posX, LEFT_MODE);
	BSP_LCD_DisplayStringAt(80, 250, (uint8_t*)",", LEFT_MODE);
	BSP_LCD_DisplayStringAt(90, 250, (uint8_t*)posY, LEFT_MODE);
}

void rysujPredkosc(int predkosc) {
	char predkoscStr[5];
	sprintf(predkoscStr, "%d", predkosc);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(70, 260, (uint8_t*)predkoscStr, LEFT_MODE);
}

void rysujKwadratPusty(Robot* robot) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(robot->posX*30+4, robot->posY*30+4, 22, 22);
}

void rysujKwadratPelny(Robot* robot) {
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(robot->posX*30+4, robot->posY*30+4, 22, 22);
}

void rysujPolaczeniePrzedWejsciem(Robot* robot){
	switch (robot->orientacja){
	case 0:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30, 2, 4);
		break;
	case 1:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+26, robot->posY*30+14, 4, 2);
		break;
	case 2:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30+26, 2, 4);
		break;
	case 3:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30, robot->posY*30+14, 4, 2);
		break;
	}
}

void rysujPolaczeniePoWejsciu(Robot* robot){
	switch (robot->orientacja){
	case 0:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30+26, 2, 4);
		break;
	case 1:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30, robot->posY*30+14, 4, 2);
		break;
	case 2:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30, 2, 4);
		break;
	case 3:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+26, robot->posY*30+14, 4, 2);
		break;
	}
}
