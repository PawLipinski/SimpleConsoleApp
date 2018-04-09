#include "stdafx.h"
#include "baza.h"

using namespace std;

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//----------------------------------------------------------------------------
int wherex()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}
//---------------------------------------------------------------------------- 
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}
//----------------------------------------------------------------------------  
void clreol()
{
	int x, y;
	x = wherex();
	y = wherey();
	gotoxy(x, y);
	for (int i = x; i <= 79; i++)
		cout << " ";
	gotoxy(x, y);
}
//----------------------------------------------------------------------------
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
//----------------------------------------------------------------------------
void ShowCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = TRUE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

//-------------------------------------------------------------------------
void ustaw_kolor(int kolor)
{
	HANDLE uchwyt;
	uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(uchwyt, kolor);
}
//-------------------------------------------------------------------------

void legenda()
{
	gotoxy(0, 25);
	cout << "Sterowanie za pomoc¹ strza³ek. Zmiana rozmiaru: +/-. Wyjœcie - Esc.";
}

void ekran_startowy()
{
	gotoxy(1, 1);
	cout << "Pawe³ Lipiñski";
	gotoxy(1, 3);
	cout << "Sem. 1, Informatyka, niestacjonarne";
	gotoxy(30, 10);
	cout << "Podstawy Programowania";
	gotoxy(5, 12);
	cout << "Program generuj¹cy wybran¹ geometriê i pozwalaj¹cy na jej modyfikacjê." ; 
	gotoxy(5, 13);
	cout<<"Z wykorzystaniem programowania obiektowego.";
	gotoxy(45, 16);
	cout << "Naciœnij dowolny klawisz...";
	_getch();

	system("cls");
}

void Odcinek::okresl_rozmiar()
{
	int rozmiar, x, y;
	bool err;

	gotoxy(5, 17);
	cout << "Podaj rozmiar figury (3-13): ";

	x = wherex();
	y = wherey();
	do
	{
		err = false;
		gotoxy(x, y);
		clreol();
		cin >> rozmiar;

		if (!cin.good())  // Zabezpieczenie przed wprowadzeniem niewlasciwego znaku
		{
			err = true;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (rozmiar < 3 || rozmiar > 13 || err);

	l = rozmiar-1;

}

void Punkt::okresl_znak()
{
	char znak1;
	int x, y;
	bool err = true;

	gotoxy(22, 18);
	cout << "Podaj znak: ";

	x = wherex();
	y = wherey();


	while (err == true)
	{
		znak1 = _getch();
		if ((znak1<33) || (znak1>126)) {
			gotoxy(x, y);
			clreol();
			err = true;
		}
		else {
			err = false;
		}
	}

	znak = znak1;
}

void Punkt::rysuj()
{
	gotoxy(x, y);
	cout << znak;
}

Punkt::Punkt(char z, int xx, int yy)
{
	znak = z;
	x = xx;
	y = yy;
}

Punkt::~Punkt()
{}

void Odcinek::pionowy()
{
	for (int i = 0; i <= l; i++)
	{
		rysuj();
		y++;
	}
}

void Odcinek::skos_prawy()
{
	for (int i = 0; i <= l / 2; i++)
	{
		rysuj();
		x--;
		y++;
	}
}

void Odcinek::skos_lewy()
{
	for (int i = 0; i <= l / 2; i++)
	{
		rysuj();
		x++;
		y++;
	}
}

Odcinek::Odcinek(char z, int xx, int yy, int ll)
:Punkt(z, xx, yy)
{
	l = ll;
}

Odcinek::~Odcinek()
{
}

void Figura::rysuj_figure()
{
	int x1 = x;
	int y1 = y;
	int x2, y2;

	skos_prawy();
	x = x1;
	y = y1;
	pionowy();
	y--;
	skos_prawy();
	x2 = x1 - l;
	y2 = y1;
	x = x2;
	y = y2;
	skos_lewy();
	x = x2;
	y = y2;
	pionowy();
	y--;
	skos_lewy();

	x = x1;
	y = y1;
}

void Figura::czysc()
{
	char znak1 = znak;
	znak = ' ';
	rysuj_figure();
	znak = znak1;
	
}

void Figura::zmiana_pozycji()
{
	int x1 = x;
	int y1 = y;
	const int Esc = 27;

	

	char wybor;

	do{
		wybor = _getch();

		czysc();

		switch (wybor)						//instrukcja pozwalaj¹ca na wykonywanie wskazanych przez u¿ytkownika dzia³añ 
		{
		case '+':	
		{if (l >= 13) l = 13;
		else if ((x <= l) || (y+ l+ l / 2 >=24) && (l % 2 == 0) || (y + l +1 + l / 2>=24) && (l % 2 == 1)) break;
		else l++;
		break; }	//Zwiêkszanie figury

		case '-':	
		{l--; 
		if (l < 2) l = 2; 
		break; }	//Zmniejszanie figury
		case 'K':	
		{if (x < l + 1) break;
		else x--; 
		break; }			//Przesuwanie figury w lewo

		case 'M':	
		{if (x+1>79) x=79;
		else x++; 
		break; }			//Przesuwanie figury w prawo

		case 'H':	
		{if (y <= 1) y = 1;
		else	y--; 
		break; }			//Przesuwanie figury w górê

		case 'P':	
		{if (y + l + l / 2>23) break;
		else y++; 
		break; }			//Przesuwanie figury w dó³
		case Esc:	{break; }				//Wy³¹czenie programu - wyjœcie z konsoli
		};

		rysuj_figure();

	} while (wybor != Esc);

	x = x1;
	y = y1;
}

void Figura::okresl()
{
	char wyb;
	const char Esc = 27;

	


		do
		{
			system("cls");
			gotoxy(5, 17);
			cout << "Wczytaæ dane z klawiatury? [t/n]";
			gotoxy(5, 18);
			cout << "Zamkniêcie programu        [Esc]";

			wyb = _getch();
			system("cls");

			if (wyb == 't')
			{
				okresl_rozmiar();
				okresl_znak();
				system("cls");
				HideCursor();
				rysuj_figure();
				legenda();
				zmiana_pozycji();
				continue;
			}

			else if (wyb == 'n')
			{
				system("cls");
				HideCursor();
				rysuj_figure();
				legenda();
				zmiana_pozycji();
				continue;
			}

			else if (wyb == Esc)
			{
				break;
			}

			else continue;

		} while (1);
		
}

void Figura::menu()
{

}

Figura::Figura(char z, int xx, int yy, int ll)
:Odcinek(z, xx, yy, ll)
{
}

Figura::~Figura()
{
}
