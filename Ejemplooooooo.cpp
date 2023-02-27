#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sstream>
#include <Windows.h>
#include <ctype.h>
#include <cctype>
#include <random>

//------------------------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------------------------

//Variables globales
const int NUM_CARTAS_PALO = 13;
const int NUM_PALO = 4;
int numj;
float dinero[2], dineror;
string nom[5];
float apuesta[2];
bool gameOver = false;
int pointsPlayer[5];
bool winner[5];
bool surrender[5];
bool empate = 0;
string cartas[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
int cartasValor[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };


//------------------------------------------------------------------------------------------------

void menu() {
	do {
		cout << "        Cuantos jugadores desean ingresar a la sala--> ";
		cin >> numj;
		cout << endl;

		if (numj > 2) {
			cout << "Error Maximo 2 jugadores" << endl;
		}
		else if (numj < 1) {
			cout << "Error Elige de 1 a 2 jugadores" << endl;
		}

		system("Pause");
		system("cls");
	} while (numj < 1 || numj > 2);

}

void encabezado() {				//El "diseño" del juego
	cout << "===========================================================================" << endl;
	cout << "=                             CASINO - LUCKY'S                            =" << endl;
	cout << "=                               21 BLACK JACK                             =" << endl;
	cout << "=                                Bienvenido                               =" << endl;
	cout << "===========================================================================" << endl;

}				

void nombres() {
	encabezado();

	for (int i = 0; i < numj; i++)
	{
		cout << "Ingresa el nombre del jugador " << i + 1 << " --> ";
		cin >> nom[i];
		cout << "Cuanto dinero desea ingresar a la mesa el jugador " << i +
			1 << " --> ";
		cin >> dinero[i];
		cout << endl;
	}
	//nom[3] = "Banca";

	system("cls");

}				

void apuestas() {
	encabezado();
	cout << "***************************************" << endl;
	for (int i = 0; i < numj; i++) {
		cout << "Cuantos creditos quieres apostar? " << nom[i] << " --> ";
		cin >> apuesta[i];
		while (apuesta[i] > dinero[i]) {
			cout << "No tienes suficientes creditos. Tienes " << dinero[i] << " creditos." << endl;
			cout << "Cuantos creditos quieres apostar? " << nom[i] << " --> ";
			cin >> apuesta[i];
		}
		dineror = dinero[i] - apuesta[i];
		cout << "Te quedan " << dineror << " creditos" << endl;
		cout << "***************************************" << endl;
		cout << " " << endl;

	}
	system("Pause");
	system("cls");

	encabezado();
	cout << "============Tabla de Apuestas==========" << endl;
	for (int i = 0; i < numj; i++) {
		cout << "Jugador " << nom[i] << " aposto--> " << apuesta[i] << " creditos" << endl;
	}
	system("Pause");
	system("cls");
}			

void eligeCartas(int& totalPoints, string nom) {
	bool choosed = false;
	int indiceCarta = 0;
	int indicePalo = 0;
	string tipoPalo;

	bool picas[NUM_CARTAS_PALO]{};
	bool diamantes[NUM_CARTAS_PALO]{};
	bool corazones[NUM_CARTAS_PALO]{};
	bool treboles[NUM_CARTAS_PALO]{};




	for (int i = 0; i < NUM_CARTAS_PALO; i++) {
		picas[i] = true;
		diamantes[i] = true;
		corazones[i] = true;
		treboles[i] = true;

	}

	while (!choosed) {
		indiceCarta = rand() % NUM_CARTAS_PALO;
		indicePalo = rand() % NUM_PALO;

		if (indicePalo == 0 && picas[indiceCarta]) {
			picas[indiceCarta] = false;
			choosed = true;
			tipoPalo = "Picas";
		}
		else if (indicePalo == 1 && diamantes[indiceCarta]) {
			diamantes[indiceCarta] = false;
			choosed = true;
			tipoPalo = "Diamantes";
		}
		else if (indicePalo == 2 && corazones[indiceCarta]) {
			corazones[indiceCarta] = false;
			choosed = true;
			tipoPalo = "Corazones";
		}
		else if (indicePalo == 3 && treboles[indiceCarta]) {
			treboles[indiceCarta] = false;
			choosed = true;
			tipoPalo = "Treboles";
		}




	}



	if (indiceCarta == 0) {
		int valor = 0;
		cout << "Te ha tocado una carta AS: Elige si quieres que la carta valga 1 o 11 puntos" << endl;
		cin >> valor;
		if (valor == 1) {
			totalPoints += 1;
		}
		else if (valor == 11) {
			totalPoints += 11;
		}


		cout << "El jugador " << nom << " ha sacado un " << cartas[indiceCarta] << " de " << tipoPalo << " y tiene un total de " << totalPoints << " puntos." << endl;


	}
	else {
		totalPoints += cartasValor[indiceCarta];
		cout << "El jugador " << nom << " ha sacado un " << cartas[indiceCarta] << " de " << tipoPalo << " y tiene un total de " << totalPoints << " puntos." << endl;

	}


}

bool checkPuntos(int& points) {
	if (points == 21) {
		return true;
	}
	else if (points > 21) {
		return true;
	}
	return false;
}

bool checkGanador(int points1, int points, bool& winner) {
	if (points > points1) {
		winner = true;
		return true;
	}
	else {
		return false;
	}
}

void repartoCartas() {

	while (!surrender[0]) {
		int choice = 0;
		while (choice != 1 && choice != 2) {
			cout << nom[0] << ", Tienes " << pointsPlayer[0] << ".  Quieres pedir otra carta ?" << endl;
			cout << "1.- Si" << endl;
			cout << "2.- No" << endl;
			cin >> choice;
			if (choice != 1 && choice != 2) {
				cout << "Por favor, elije una opción válida." << endl;
			}
		}
		cout <<"" << endl;
		if (choice == 1) {
			eligeCartas(pointsPlayer[0], nom[0]);
			surrender[0] = checkPuntos(pointsPlayer[0]);
		}
		else {
			surrender[0] = true;
		}
	}

	system("Pause");
	system("cls");

}

void repartoCartas2() {
	while (!surrender[1]) {
		int choice = 0;
		while (choice != 1 && choice != 2) {
			cout << nom[1] << ", Tienes " << pointsPlayer[1] << ".  Quieres pedir otra carta ?" << endl;
			cout << "1.- Si" << endl;
			cout << "2.- No" << endl;
			cin >> choice;
			if (choice != 1 && choice != 2) {
				cout << "Por favor, elije una opción válida." << endl;
			}
		}
		if (choice == 1) {
			eligeCartas(pointsPlayer[1], nom[1]);
			surrender[1] = checkPuntos(pointsPlayer[1]);
		}
		else {
			surrender[1] = true;
		}
	}
	system("Pause");
	system("cls");
}

void ganador() {
	int points = 0;
	encabezado();
	cout << "============Tabla de Resultados==========" << endl;
	for (int i = 0; i < numj; i++) {
		if (pointsPlayer[i] > 21) {
			winner[i] = false;
			cout << "El jugador " << nom[i] << " pierde" << endl;
		}
		else {
			if (pointsPlayer[i] > points) {
				points = pointsPlayer[i];
				winner[i] = true;
			}
		}
	}

	if (winner[1]) {
		cout << "El jugador " << nom[1] << " gana" << endl;
	}
	else if (winner[0]) {
		cout << "El jugador " << nom[0] << " gana" << endl;
	}
	else  if (winner[0] && winner[1]) {
		empate = true;
		cout << "Los jugadores " << nom[0] << " y " << nom[1] << " han empatado" << endl;
	}

	system("Pause");
	system("cls");

}

void apuestas2() {
	encabezado();
	cout << "============Tabla de Apuestas Finales==========" << endl;

	if (winner[0]) {
		cout << "Jugador " << nom[0] << " gano--> " << (apuesta[0] * 2) << " creditos" << endl;
	}
	else if (winner[1]) {
		cout << "Jugador " << nom[1] << " gano--> " << (apuesta[1] * 2) << " creditos" << endl;

	}
	else if (winner[0] && winner[1]) {
		cout << "Se han devuelto los creditos por un empate." << endl;

	}



	system("Pause");
	system("cls");
}

void jugador1() {
	encabezado();
	cout << "Cartas De " << nom[0] << endl;
	eligeCartas(pointsPlayer[0], nom[0]);
	Sleep(10);
	eligeCartas(pointsPlayer[0], nom[0]);
	Sleep(10);
	surrender[0] = checkPuntos(pointsPlayer[0]);
	Sleep(10);
	repartoCartas();
}

void jugador2() {
	if (numj == 2) {
		encabezado();
		cout << "Cartas De " << nom[1] << endl;
		eligeCartas(pointsPlayer[1], nom[1]);
		Sleep(10);
		repartoCartas2();
	}
}





//------------------------------------------------------------------------------------------------

int main() {
	srand(time(NULL));

	encabezado();
	menu();
	nombres();
	apuestas();

	jugador1();
	Sleep(10);

	jugador2();
	Sleep(10);


	ganador();
	Sleep(10);
	apuestas2();

}

//------------------------------------------------------------------------------------------------









