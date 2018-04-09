
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale>

using namespace std;

void gotoxy(int x, int y);
void ekran_startowy();
int wherex();
int wherey();
void clreol();
void HideCursor();
int okresl_rozmiar();
char okresl_znak();
void ShowCursor();
void ustaw_kolor(int kolor);
void legenda();

class Punkt
{
protected:
	int x, y;
	char znak;

public:
	void rysuj();
	void okresl_znak();
	Punkt(char='*', int=79, int=1);
	~Punkt();

	friend void gotoxy(int x, int y);
	
};

class Odcinek: public Punkt
{
protected:
	int l;

public:
	void pionowy();
	void skos_prawy();
	void skos_lewy();
	void okresl_rozmiar();
	Odcinek(char = '*', int = 79, int = 1, int = 8);
	~Odcinek();

	friend void gotoxy(int x, int y);
	
	
};

class Figura: public Odcinek
{
public:
	void rysuj_figure();
	void czysc();
	void zmiana_pozycji();
	void okresl();

	void menu();
	Figura(char = '*', int = 79, int = 1, int = 8);
	~Figura();

	friend void gotoxy(int x, int y);
};