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

Robot konstruktorRobota(int poczatkoweX, int poczatkoweY, enum Orientacje poczatkowaOrientacja) {
    Robot robot;
    robot.posX = poczatkoweX;
    robot.posY = poczatkoweY;
    robot.orientacja = poczatkowaOrientacja;

    unsigned char labiryntPoznawany[4][4];

    for(int i=0; i<4; i++) {
    	for(int j=0; j<4; j++) {
            robot.tabSciezki[i][j] = 0;
            robot.obecnosc[i][j] = 0;
            robot.labiryntPoznawany[i][j] = 0;
        }
    }
    return robot;
}

void regulator(Robot* robot, float odleglosc, int czyObrot, enum Strony strona) {
	unsigned int impulsyNaZadanaOdleglosc = odlegloscNaImpulsy(odleglosc);

	int praweOK = 0;
	int leweOK = 0;

	robot->e1 = 0;
	robot->e1_poprzednie = 0;
	int u1 = 0;
	float Kp1 = 0.05;
	float Kd1 = 3;

	robot->e2 = 0;
	robot->e2_poprzednie = 0;
	int u2 = 0;
	float Kp2 = 0.01;
	float Kd2 = 1;

	int V0 = 300;

	// Wyzeruj predkosc
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
	// Wyzeruj liczniki impulsow
	__HAL_TIM_SetCounter(&htim5, 0);
	__HAL_TIM_SetCounter(&htim3, 0);
	// Odczytaj wartosci
	robot->impulsyEnkoderaR = __HAL_TIM_GetCounter(&htim5);
	robot->impulsyEnkoderaL = __HAL_TIM_GetCounter(&htim3);
	skanujObszar(robot);
	robot->odlegloscCzujnikaR = robot->odczytCzujnikow[3] - 50;
	robot->odlegloscCzujnikaL = robot->odczytCzujnikow[2];

	// Skok
	if(czyObrot == 0) {
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0); // prawe do przodu
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0); // lewe do przodu
	}
	else {
		switch(strona) {
		case Lewo:
			__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0); // prawe do przodu
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, V0); // lewe do tylu
			break;
		case Prawo:
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0); // lewe do przodu
			__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, V0); // prawe do tylu
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
		skanujObszar(robot);
		robot->odlegloscCzujnikaR = robot->odczytCzujnikow[3] - 50;
		robot->odlegloscCzujnikaL = robot->odczytCzujnikow[2];
		if(robot->odlegloscCzujnikaR <= 3300 && robot->odlegloscCzujnikaL <= 3300) {
			robot->e2 = robot->odlegloscCzujnikaL - robot->odlegloscCzujnikaR;
		}
		else {
			robot->e2 = 0;
		}
		robot->e1 = robot->impulsyEnkoderaL - robot->impulsyEnkoderaR;

		u1 = Kp1 * robot->e1 + Kd1 * (robot->e1 - robot->e1_poprzednie);
		u2 = Kp2 * robot->e2 + Kd2 * (robot->e2 - robot->e2_poprzednie);
		if(u1 > 300) {
			u1 = 300;
		}
		else if(u1 < -300) {
			u1 = - 300;
		}
		if(u2 > 300) {
			u2 = 300;
		}
		else if(u2 < -300) {
			u2 = -300;
		}

		if(czyObrot == 0) {
			if(!praweOK)
				__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 + u1 + u2);
			if(!leweOK)
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 - u1 - u2);
		}
		else {
			switch(strona) {
			case Lewo:
				__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, V0 + u1 + u2); // prawe do przodu
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, V0 - u1 - u2); // lewe do tylu
				break;
			case Prawo:
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, V0 - u1 - u2); // lewe do przodu
				__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, V0 + u1 + u2); // prawe do tylu
				break;
			}
		}

		robot->e1_poprzednie = robot->e1;
		robot->e2_poprzednie = robot->e2;

		if(robot->impulsyEnkoderaL >= impulsyNaZadanaOdleglosc && leweOK != 1) {
			leweOK = 1;
		}
		if(robot->impulsyEnkoderaR >= impulsyNaZadanaOdleglosc && praweOK != 1) {
			praweOK = 1;
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

	regulator(robot, 17.5, 0, Prawo);

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
		regulator(robot, 8.247, 1, Lewo);
		break;
	case Prawo:
		robot->orientacja--;
		robot->orientacja %=4;
		regulator(robot, 8.247, 1, Prawo);
		break;
	}
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

void jedzKierunek(Robot* robot, enum Orientacje kierunek) {
    switch(kierunek) {
        case Polnoc:
            if(robot->orientacja == Polnoc) {
                jedzProsto(robot);
            }
            else if(robot->orientacja == Zachod) {
                jedzPrawo(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzTyl(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzLewo(robot);
            }
        break;

        case Zachod:
            if(robot->orientacja == Polnoc) {
                jedzLewo(robot);
            }
            else if(robot->orientacja == Zachod) {
                jedzProsto(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzPrawo(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzTyl(robot);
            }
        break;

        case Poludnie:
            if(robot->orientacja == Polnoc) {
                jedzTyl(robot);
            }
            else if(robot->orientacja == Zachod) {
                jedzLewo(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzProsto(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzPrawo(robot);
            }
        break;

        case Wschod:
            if(robot->orientacja == Polnoc) {
                jedzPrawo(robot);
            }
            else if(robot->orientacja == Zachod) {
                jedzTyl(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzLewo(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzProsto(robot);
            }
        break;
    }
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

	if(robot->odczytCzujnikow[0] <= 3300 || robot->odczytCzujnikow[1]) {
		// Sciana z przodu
	}
	if(robot->odczytCzujnikow[2] <= 3300) {
		// Sciana po lewej
	}
	if(robot->odczytCzujnikow[3] <= 3300) {
		// Sciana po prawej
	}

	rysujCzujniki(robot->odczytCzujnikow[0], robot->odczytCzujnikow[1], robot->odczytCzujnikow[2], robot->odczytCzujnikow[3]);
}

void znajdzNajkrotszaSciezkeRekurencja(Robot* robot, int posX, int posY) {
   // Czy osiagniety zostal start
   if(posX == 0 && posY == 0) {
       return;
   }

    // Przejscie do kolejnego pola w zaleznosci od mozliwych polaczen
    if(robot->labiryntPoznawany[posY][posX] & NORTH) {
        if(!robot->tabSciezki[posY-1][posX] || robot->tabSciezki[posY-1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY-1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY-1);
        }
    }
    if(robot->labiryntPoznawany[posY][posX] & WEST) {
        if(!robot->tabSciezki[posY][posX-1] || robot->tabSciezki[posY][posX-1] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY][posX-1] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX-1, posY);
        }
    }
    if(robot->labiryntPoznawany[posY][posX] & SOUTH) {
        if(!robot->tabSciezki[posY+1][posX] || robot->tabSciezki[posY+1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY+1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY+1);
        }
    }
    if(robot->labiryntPoznawany[posY][posX] & EAST) {
        if(!robot->tabSciezki[posY][posX+1] || robot->tabSciezki[posY][posX+1] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY][posX+1] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX+1, posY);
        }
    }
}

void znajdzNajkrotszaSciezkeStart(Robot* robot) {
    int posX = KONIEC;
    int posY = KONIEC;

    znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY);
    robot->tabSciezki[posX][posY] = 0;
}

void przejedzLabirynt(Robot* robot) {
    printf("Zaczynam przejazd wzdluz sciezki\n");
    printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);

    while(!(robot->posX == KONIEC && robot->posY == KONIEC)) {
        if((robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH) && (robot->tabSciezki[robot->posY-1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Polnoc);
            printf("Znalazlem droge Polnoc \t\t");
        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & WEST) && (robot->tabSciezki[robot->posY][robot->posX-1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Zachod);
            printf("Znalazlem droge Zachod \t\t");

        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH) && (robot->tabSciezki[robot->posY+1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Poludnie);
            printf("Znalazlem droge Poludnie \t");

        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & EAST) && (robot->tabSciezki[robot->posY][robot->posX+1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Wschod);
            printf("Znalazlem droge Wschod \t\t");

        }
        printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);

    }

    printf("Przejazd wzdluz sciezki zakonczony\n");
    printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);
}

int odlegloscNaImpulsy(int odleglosc) {
	return ((odleglosc)*1920)/(2*3.141592*7.96);
}
