// Obiektowy_podejscie2.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "baza.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");

	Figura f1;					//Utworzenie obiektu klasy figura
	ekran_startowy();			//Pierwszy ekran - dane studenta i projektu
	f1.okresl();				//Dezycja, czy wczyta� dane domy�lne, czy z klawiatury. Nast�pnie narysowanie na ekranie figury i stosowanie komend u�ytkownika. 

	return 0;
}

