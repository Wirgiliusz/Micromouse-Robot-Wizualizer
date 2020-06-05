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
	rysujKwadratPelny(0,0);
	BSP_LCD_SetFont(&Font12);
	rysujGranicePlanszy();
	rysujInformacje();
	rysujPozycje(0,0);
	rysujEnkoder(0, 0);
	rysujEnkoder(0, 1);
}

void rysujGranicePlanszy() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DrawRect(0, 0, 239, 239);
}

void rysujInformacje() {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, 240, (uint8_t*)"Pozycja: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 250, (uint8_t*)"EnkoderR: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 260, (uint8_t*)"EnkoderL: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 270, (uint8_t*)"Czujniki: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 280, (uint8_t*)"Predkosc: ", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 300, (uint8_t*)"DEBUG: ", LEFT_MODE);
}

void rysujPozycje(int x, int y) {
	char posX[2];
	char posY[2];
	sprintf(posX, "%d", x);
	sprintf(posY, "%d", y);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(70, 240, (uint8_t*)posX, LEFT_MODE);
	BSP_LCD_DisplayStringAt(80, 240, (uint8_t*)",", LEFT_MODE);
	BSP_LCD_DisplayStringAt(90, 240, (uint8_t*)posY, LEFT_MODE);
}

void rysujPredkosc(int predkosc) {
	char predkoscStr[5];
	sprintf(predkoscStr, "%d", predkosc);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(70, 280, (uint8_t*)predkoscStr, LEFT_MODE);
}

void rysujDebug(int wiadomosc) {
	char debugStr[5];
	sprintf(debugStr, "%d", wiadomosc);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(70, 300, (uint8_t*)debugStr, LEFT_MODE);
}

void rysujEnkoder(int impulsy, int lewy) {
	if(lewy) {
		char impulsyStr[5];
		sprintf(impulsyStr, "%d", impulsy);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(70, 260, (uint8_t*)impulsyStr, LEFT_MODE);
	}
	else {
		char impulsyStr[5];
		sprintf(impulsyStr, "%d", impulsy);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		BSP_LCD_DisplayStringAt(70, 250, (uint8_t*)impulsyStr, LEFT_MODE);
	}
}

void rysujCzujniki(int czujnik1, int czujnik2, int czujnik3, int czujnik4) {
	char czujnik1str[5], czujnik2str[5], czujnik3str[5], czujnik4str[5];
	sprintf(czujnik1str, "%d", czujnik1);
	sprintf(czujnik2str, "%d", czujnik2);
	sprintf(czujnik3str, "%d", czujnik3);
	sprintf(czujnik4str, "%d", czujnik4);
	if(czujnik1 < 1000) {
		czujnik1str[0] = '0';
	}
	if(czujnik2 < 1000) {
		czujnik2str[0] = '0';
	}
	if(czujnik3 < 1000) {
		czujnik3str[0] = '0';
	}
	if(czujnik4 < 1000) {
		czujnik4str[0] = '0';
	}
	if(czujnik1 < 100) {
		czujnik1str[1] = '0';
	}
	if(czujnik2 < 100) {
		czujnik2str[1] = '0';
	}
	if(czujnik3 < 100) {
		czujnik3str[1] = '0';
	}
	if(czujnik4 < 100) {
		czujnik4str[1] = '0';
	}

	BSP_LCD_DisplayStringAt(70, 270, (uint8_t*)czujnik3str, LEFT_MODE);
	BSP_LCD_DisplayStringAt(100, 270, (uint8_t*)czujnik1str, LEFT_MODE);
	BSP_LCD_DisplayStringAt(130, 270, (uint8_t*)czujnik2str, LEFT_MODE);
	BSP_LCD_DisplayStringAt(160, 270, (uint8_t*)czujnik4str, LEFT_MODE);

}

void rysujKwadratPusty(int posX, int posY) {
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(posX*30+4, posY*30+4, 22, 22);
}

void rysujKwadratPelny(int posX, int posY) {
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(posX*30+4, posY*30+4, 22, 22);
}

void rysujPolaczeniePrzedWejsciem(Robot* robot){
	switch (robot->orientacja){
	case Polnoc:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30, 2, 4);
		break;
	case Wschod:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+26, robot->posY*30+14, 4, 2);
		break;
	case Poludnie:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30+26, 2, 4);
		break;
	case Zachod:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30, robot->posY*30+14, 4, 2);
		break;
	}
}

void rysujPolaczeniePoWejsciu(Robot* robot){
	switch (robot->orientacja){
	case Polnoc:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30+26, 2, 4);
		break;
	case Wschod:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30, robot->posY*30+14, 4, 2);
		break;
	case Poludnie:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30, 2, 4);
		break;
	case Zachod:
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+26, robot->posY*30+14, 4, 2);
		break;
	}
}

void rysujPolaczenia(Robot* robot) {
	if(robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH) {
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30, 2, 4);
	}
	if(robot->labiryntPoznawany[robot->posY][robot->posX] & WEST) {
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30, robot->posY*30+14, 4, 2);
	}
	if(robot->labiryntPoznawany[robot->posY][robot->posX] & EAST) {
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+26, robot->posY*30+14, 4, 2);

	}
	if(robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH) {
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_FillRect(robot->posX*30+14, robot->posY*30+26, 2, 4);

	}
}
