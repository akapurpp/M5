
#include <iostream>
#include <string>
#include "Personaje.h"
#include "Enemigo.h"
#include "EnemigoFinal.h"
#include <conio.h>
#include <Windows.h>
#include "colors.h"


const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 30;

using namespace std;

Enemigo* variosEnemigos(int numEnemigos) {
	Enemigo* arrayEnemigos = new Enemigo[numEnemigos];

	for (size_t i = 0; i < numEnemigos; i++)
	{

		arrayEnemigos[i] = Enemigo("Enemigo", 100, 12, 0, 0);

	}
	return arrayEnemigos;
}

void encabezado() {				//El "diseño" del juego
	cout << MAGENTA << "===========================================================================" << endl;
	cout << "=                                Bienvenido a                             =" << endl;
	cout << "=                              EL TEMPLO PERDIDO                          =" << endl;
	cout << "=                                 by Jonathan                             =" << endl;
	cout << "===========================================================================" << RESET << endl;

}

void imprimirMapa(char mapa[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			std::cout << mapa[i][j] << " ";
		} std::cout << std::endl;
	}
}

void batallaEnemigo(Personaje& heroe, Enemigo& enemigo) {

	do {
		system("CLS");
		std::cout << "Te has encontrado a un enemigo comun.\n" << std::endl;
		bool gameOver = false;

		while (!gameOver) {
			// Mostrar estado del héroe y del enemigo
			
			heroe.mostrarEstado();
			Sleep(500);
			cout << "\n\n";
			enemigo.mostrarEstado();
			Sleep(500);
			
			// Turno del héroe
			std::cout << "\nEs tu turno de atacar! Elige una opcion:" << std::endl;
			std::cout << "1. Ataque normal" << std::endl;

			int opcion;
			std::cin >> opcion;
			system("cls");

			switch (opcion) {
			case 1:
				// getAtaque() normal
				enemigo.setVida(enemigo.getVida() - heroe.getAtaque());
				break;
			default:
				std::cout << "Opcion invalida." << std::endl;
				break;
				
			}

			// Verificar si el enemigo ha sido derrotado
			if (enemigo.getVida() <= 0) {
				std::cout <<GREEN << "Has derrotado al enemigo! ¡Has ganado la batalla!" <<RESET << std::endl;
				enemigo.setVida(0);
				break;
			}

			// Turno del enemigo 
			std::cout << "Es el turno del enemigo!\n" << std::endl;
			heroe.setVida(heroe.getVida() - enemigo.getAtaque());

			// Verificar si el héroe ha sido derrotado
			if (heroe.getVida() <= 0) {
				std::cout <<RED << "El enemigo te ha derrotado! Game over!" << RESET<< std::endl;
				heroe.setVida(0);
			}
		}


	} while (heroe.getVida() <= 0 && enemigo.getVida() <= 0);
}

void batallaFinal(Personaje& heroe, EnemigoFinal& enemigo) {
	system("CLS");
	std::cout << "Te has encontrado a el enemigo final.\n" << std::endl;
	bool gameOver = false;
	do {
		system("CLS");
		std::cout << "Te has encontrado a el enemigo final.\n" << std::endl;
		bool gameOver = false;

		while (!gameOver) {
			// Mostrar estado del héroe y del enemigo final
			heroe.mostrarEstado();
			Sleep(500);
			cout << "\n\n";
			enemigo.mostrarEstado();
			Sleep(500);
			// Turno del héroe
			std::cout << "\nEs tu turno de atacar! Elige una opción:" << std::endl;
			std::cout << "1. Ataque normal " << std::endl;
			
			

			int opcion;
			std::cin >> opcion;
			system("cls");

			switch (opcion) {
			case 1:
				// Ataque normal
				enemigo.setVida(enemigo.getVida() - heroe.getAtaque());
				break;
		
			default:
				std::cout << "Opcion invalida." << std::endl;
				
				break;
			}

			// Verificar si el enemigo final ha sido derrotado
			if (enemigo.getVida() <= 0) {
				std::cout <<GREEN << "\nHas derrotado al enemigo final y has encontrado la SALIDA! ¡Has ganado la batalla!" <<RESET << std::endl;
				enemigo.setVida(0);
				system("pause");
				gameOver = true;
				
			}

			// Turno del enemigo final
			std::cout << "Es el turno del enemigo final!\n" << std::endl;
			int atak = rand() % 3 + 1;
			switch (atak)
			{case 1:
				heroe.setVida(heroe.getVida() - enemigo.getAtaqueMistico());
				std::cout << "El enemigo final te ha atacado con su ataque mistico\n" << std::endl;

				break;
			case 2: 
				heroe.setVida(heroe.getVida() - enemigo.getAtaqueAstral());
				std::cout << "El enemigo final te ha atacado con su ataque astral\n" << std::endl;
				
				break;

				case 3:
					heroe.setVida(heroe.getVida() - enemigo.getAtaque());
					std::cout << "El enemigo final te ha atacado con su ataque normal\n" << std::endl;
					break;
			default:
				break;
			}
			heroe.setVida(heroe.getVida() - enemigo.getAtaque());

			// Verificar si el héroe ha sido derrotado
			if (heroe.getVida() <= 0) {
				system("CLS");
				encabezado();
				std::cout << RED<< "El enemigo final te ha derrotado! Game over!" << RESET<< std::endl;
				heroe.setVida(0);
				system("pause");
				gameOver = true;
			}
		}


	} while (heroe.getVida() <= 0 && enemigo.getVida() <= 0);
}



int main()
{
	int numEnemigos = 100;
	encabezado();
	// Semilla para generar números aleatorios
	std::srand(std::time(0));
	int salidaX = 18;
	int salidaY = 1;
	// Crear el mapa y el personaje inicial 
	char mapa[MAP_HEIGHT][MAP_WIDTH] = {};
	// Inicializar el mapa con guiones 
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
				mapa[i][j] = '#';
				// Bordes del mapa 
			}
			else {
				mapa[i][j] = '-'; // Relleno del mapa 
			}
			if (i == 14) {
				mapa[i][j] = '#';
			}
			if (i == 14 && j == 35) {
				mapa[i][j] = '-';
			}
			if (j==19)
			{
				mapa[i][j] = '#';
			}
			if (j==19 && i== 5)
			{
				mapa[i][j] = '-';
			}if (j == 19 && i == 26)
			{
				mapa[i][j] = '-';
			}
		}
	}
	
	mapa[18][0] = 'S';
	

	

	Enemigo* enemigos = new Enemigo[50];
	enemigos = variosEnemigos(numEnemigos);
	for (size_t i = 0; i <= 14; i++)
	{
		int rand1 = 1 + rand() % (40 - 1);
		int rand2 = 1 + rand() % (30 - 1);
		enemigos[i].setPosicionX(rand1);
		enemigos[i].setPosicionY(rand2);
	}


	cout << "Bienvenido al juego!" << endl;
	cout <<"El objetivo del juego consiste en que el"<<CYAN<<" heroe"<< RESET<< "llegue a la salida sin "<<RED<< "morir"<< RESET<<" en el intento, buena suerte :) \n" << endl;
	string nombreHeroe;
	cout << "Elige un nombre para el"<<CYAN<< " heroe: " << RESET << endl;
	cin >> nombreHeroe;
	system("CLS");
	Sleep(500);


	// Crear héroe y enemigo final
	Personaje heroe(nombreHeroe, 500, 20, 0, 0);
	heroe.setNombre(nombreHeroe);
	EnemigoFinal enemigoFinal("Enemigo Final", 200, 50, salidaX, salidaY, 30, 40);


	int pos1 = 1 + rand() % (MAP_WIDTH/2 - 1);
	heroe.setPosicionX(pos1);
	heroe.setPosicionY(1);



	bool juegoTerminado = false;

	// Bucle principal del juego
	while (!juegoTerminado) {

		encabezado();
		std::cout << "Bienvenido al juego!" << std::endl;
		std::cout << "Estado actual del" << CYAN<< " heroe:" << RESET<< std::endl;
		heroe.mostrarEstado();


		// Imprimir el mapa
		imprimirMapa(mapa);

		// Obtener la entrada del usuarios
		char tecla = _getch();

		// Borrar la posición anterior del jugador en el mapa
		mapa[heroe.getPosicionY()][heroe.getPosicionX()] = ' ';

		// Mover el jugador según la tecla presionada
		switch (tecla) {
		case 'w':
		case 'W':
			if (mapa[heroe.getPosicionY() - 1][heroe.getPosicionX()] != '#')
				heroe.setPosicionY(heroe.getPosicionY() - 1);
			for (size_t i = 0; i < numEnemigos; i++)
			{
				if (heroe.getPosicionX() == enemigos[i].getPosicionX() && heroe.getPosicionY() == enemigos[i].getPosicionY())
				{
					batallaEnemigo(heroe, enemigos[i]);
				}
				
			}
			if (heroe.getPosicionX() == enemigoFinal.getPosicionX() && heroe.getPosicionY() == enemigoFinal.getPosicionY())
			{
				batallaFinal(heroe, enemigoFinal);
			}
			break;
		case 'a':
		case 'A':
			if (mapa[heroe.getPosicionY()][heroe.getPosicionX() - 1] != '#')
				heroe.setPosicionX(heroe.getPosicionX() - 1);
			for (size_t i = 0; i < numEnemigos; i++)
			{
				if (heroe.getPosicionX() == enemigos[i].getPosicionX() && heroe.getPosicionY() == enemigos[i].getPosicionY())
				{
					batallaEnemigo(heroe, enemigos[i]);
				}
			}
			if (heroe.getPosicionX() == enemigoFinal.getPosicionX() && heroe.getPosicionY() == enemigoFinal.getPosicionY())
			{
				batallaFinal(heroe, enemigoFinal);
			}
			break;
		case 's':
		case 'S':
			if (mapa[heroe.getPosicionY() + 1][heroe.getPosicionX()] != '#')
				heroe.setPosicionY(heroe.getPosicionY() + 1);
			for (size_t i = 0; i < numEnemigos; i++)
			{
				if (heroe.getPosicionX() == enemigos[i].getPosicionX() && heroe.getPosicionY() == enemigos[i].getPosicionY())
				{
					batallaEnemigo(heroe, enemigos[i]);
				}
			}
			if (heroe.getPosicionX() == enemigoFinal.getPosicionX() && heroe.getPosicionY() == enemigoFinal.getPosicionY())
			{
				batallaFinal(heroe, enemigoFinal);
			}
			break;
		case 'd':
		case 'D':
			if (mapa[heroe.getPosicionY()][heroe.getPosicionX() + 1] != '#')
				heroe.setPosicionX(heroe.getPosicionX() + 1);
			for (size_t i = 0; i < numEnemigos; i++)
			{
				if (heroe.getPosicionX() == enemigos[i].getPosicionX() && heroe.getPosicionY() == enemigos[i].getPosicionY())
				{
					batallaEnemigo(heroe, enemigos[i]);
				}
			}
			if (heroe.getPosicionX() == enemigoFinal.getPosicionX() && heroe.getPosicionY() == enemigoFinal.getPosicionY())
			{
				batallaFinal(heroe, enemigoFinal);
			}

			break;
		}

		if (heroe.getVida() <= 0) {
			system("cls");
			encabezado();
			std::cout << RED << "Has perdido el juego!" << RESET<< std::endl;
			std::cout << RED << "Hasta la proxima!" << RESET << std::endl;
			system("pause");
			juegoTerminado = true;
		}

		if (enemigoFinal.getVida() <= 0) {
			system("cls");
			encabezado();
			std::cout << GREEN<< "Has ganado el juego!" << RESET<< std::endl;
			std::cout << GREEN << "Hasta la proxima!" << RESET << std::endl;
			system("pause");
			juegoTerminado = true;
		}

		// Colocar al jugador en la nueva posición en el mapa
		mapa[heroe.getPosicionY()][heroe.getPosicionX()] = 'H';

		// Limpiar la consola
		system("cls");
	}

}





