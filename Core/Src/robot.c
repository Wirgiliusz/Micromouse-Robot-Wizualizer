/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "robot.h"
#include "tim.h"
#include "funkcje_rysujace.h"
#include "adc.h"

#define MAX_PREDKOSC 1000


void regulator(Robot* robot, float odleglosc, int czyObrot, enum Strony strona) {
	unsigned int impulsyNaZadanaOdleglosc = odlegloscNaImpulsy(odleglosc);

	int praweOK = 0;
	int leweOK = 0;

	robot->e = 0;
	robot->e_poprzednie = 0;
	int u = 0;
	float Kp = 0.005;
	float Kd = 50;
	int V0 = 300;

	// Wyzeruj predkosc
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
	// Wyzeruj liczniki impulsow
	__HAL_TIM_SetCounter(&htim5, 0);
	__HAL_TIM_SetCounter(&htim3, 0);
	robot->impulsyEnkoderaR = __HAL_TIM_GetCounter(&htim5);
	robot->impulsyEnkoderaL = __HAL_TIM_GetCounter(&htim3);
	// Skok
	if(czyObrot == 0) {
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 300); // prawe do przodu
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 300); // lewe do przodu
	}
	else {
		switch(strona) {
		case Lewo:
			__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 300); // prawe do przodu
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 300); // lewe do tylu
			break;
		case Prawo:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 300); // lewe do przodu
			__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 300); // prawe do tylu
			break;
		}
	}

	// Regulacja
	while(praweOK == 0 || leweOK == 0) {
		rysujEnkoder(robot->impulsyEnkoderaR, 0);
		rysujEnkoder(robot->impulsyEnkoderaL, 1);

		if(!praweOK) {
			robot->impulsyEnkoderaR = __HAL_TIM_GetCounter(&htim5);
		}
		if(!leweOK) {
			robot->impulsyEnkoderaL = __HAL_TIM_GetCounter(&htim3);
		}

		robot->e = robot->impulsyEnkoderaL - robot->impulsyEnkoderaR;
		if(robot->e > 0) {
			u = Kp * robot->e + Kd * (robot->e - robot->e_poprzednie);
			if(u > 300) {
				u = 300;
			}
			if(czyObrot == 0) {
				if(!praweOK)
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 + u);
				if(!leweOK)
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 - u);
			}
			else {
				switch(strona) {
				case Lewo:
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 + u); // prawe do przodu
					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, V0 - u); // lewe do tylu
					break;
				case Prawo:
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 - u); // lewe do przodu
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, V0 + u); // prawe do tylu
					break;
				}
			}
		}
		else if(robot->e < 0) {
			u = -(Kp * robot->e + Kd * (robot->e - robot->e_poprzednie));
			if(u > 300) {
				u = 300;
			}
			if(czyObrot == 0) {
				if(!praweOK)
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 - u);
				if(!leweOK)
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 + u);
			}
			else {
				switch(strona) {
				case Lewo:
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 - u); // prawe do przodu
					__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, V0 + u); // lewe do tylu
					break;
				case Prawo:
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 + u); // lewe do przodu
					__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, V0 - u); // prawe do tylu
					break;
				}
			}
		}

		robot->e_poprzednie = robot->e;

		if(robot->impulsyEnkoderaL >= impulsyNaZadanaOdleglosc && leweOK != 1) {
			//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1000);
			//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1000);
			leweOK = 1;
			//praweOK = 1;
		}
		if(robot->impulsyEnkoderaR >= impulsyNaZadanaOdleglosc && praweOK != 1) {
			//__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 1000);
			//__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 1000);
			praweOK = 1;
			//leweOK = 1;
		}
	}
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 1000);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 1000);

	HAL_Delay(300);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
}

void jedzProsto(Robot* robot) {

	regulator(robot, 18, 0, Prawo);

	rysujPolaczeniePrzedWejsciem(robot);
	HAL_Delay(500);
	rysujKwadratPusty(robot->posX, robot->posY);
	switch(robot->orientacja) {
	case Polnoc:
		robot->posY--;
		break;
	case Zachod:
		robot->posX--;
		break;
	case Poludnie:
		robot->posY++;
		break;
	case Wschod:
		robot->posX++;
		break;
	}

	rysujKwadratPelny(robot->posX, robot->posY);
	rysujPolaczeniePoWejsciu(robot);

	rysujPozycje(robot->posX, robot->posY);
}

void obroc(Robot* robot, enum Strony strona) {
	switch(strona) {
	case Lewo:
		robot->orientacja++;
		robot->orientacja %=4;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0.25*MAX_PREDKOSC);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0.25*MAX_PREDKOSC);
		break;
	case Prawo:
		robot->orientacja--;
		robot->orientacja %=4;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0.25*MAX_PREDKOSC);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0.25*MAX_PREDKOSC);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
		break;
	}

	HAL_Delay(300);

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);

	HAL_Delay(500);
}

void jedzPrawo(Robot* robot) {
	obroc(robot, Prawo);
	jedzProsto(robot);
}

void jedzLewo(Robot* robot) {
	obroc(robot, Lewo);
	jedzProsto(robot);
}

void jedzTyl(Robot* robot) {
	obroc(robot, Prawo);
	obroc(robot, Prawo);
	jedzProsto(robot);
}

void skanujObszar(Robot* robot) {
	void ADC_SetActiveChannel(ADC_HandleTypeDef *hadc, uint32_t AdcChannel);

	if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		robot->odczytCzujnikow[0] = HAL_ADC_GetValue(&hadc1);
		ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_11);
		HAL_ADC_Start(&hadc1);
	}
	if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		robot->odczytCzujnikow[1] = HAL_ADC_GetValue(&hadc1);
		ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_13);
		HAL_ADC_Start(&hadc1);
	}
	if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		robot->odczytCzujnikow[2] = HAL_ADC_GetValue(&hadc1);
		ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_7);
		HAL_ADC_Start(&hadc1);
	}

	if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
		robot->odczytCzujnikow[3] = HAL_ADC_GetValue(&hadc1);
		ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_5);
		HAL_ADC_Start(&hadc1);
	}

	rysujCzujniki(robot->odczytCzujnikow[0], robot->odczytCzujnikow[1], robot->odczytCzujnikow[2], robot->odczytCzujnikow[3]);
}

int odlegloscNaImpulsy(int odleglosc) {
	return ((odleglosc)*1920)/(2*3.141592*7.96);
}
