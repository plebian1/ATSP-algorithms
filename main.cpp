#include<iostream>
#include<cmath>
#include "macierzkosztu.h"
#include <sstream>
#include <cstdio>
#include <windows.h>
#include <chrono>
using namespace std;


int main()
{
	srand(time(NULL));


	bool zewn = true;
	int wybor = 0;
	cout << "Program do testowania problemu komiwojazera" << endl << "Autor: Jedrzej Piatek" << endl;

	while (zewn)
	{
		if (wybor == 0)
		{
			cout << "Co chcesz teraz zrobic? Wpisz cyfre odpowiadajaca wybranej opcji i potwierdz enterem" << endl;
			cout << "1.Testuj Program recznie" << endl;
			cout << "2.Uruchom testy do sprawozdania" << endl;
			cout << "3.Zakoncz program" << endl;
			cin >> wybor;
		}
		else if (wybor == 1)
		{
			bool wewlista = true;
			Macierzkosztu *test = new Macierzkosztu(450);
			wybor = 0;
			bool wczytano = false;
			int *timeTable =  new int[13];

			int populacja = 1000;
			double  wspMut = 0.01;
			double  wspKrzyz = 0.8;
			int metodaKrzyzowania = 1;
			int metodaMutacji = 1;

			double czas = 180;
			while (wewlista)
			{
				if (wybor == 0)
				{
					cout << "Testowanie reczne" << endl;
					cout << "Co chcesz teraz zrobic? Wpisz cyfre odpowiadajaca wybranej opcji i potwierdz enterem" << endl;
					cout << "1. Wczytaj dane z pliku. " << endl;
					cout << "2. Wprowadz kryterium stopu " << endl;
					cout << "3. Ustaw populacje poczatkowa" << endl;
					cout << "4. Ustaw wspolczynnik mutacji" << endl;
					cout << "5. Ustaw wspolczynnik krzyzowania" << endl;
					cout << "6. Wybierz metode krzyzowania " << endl;
					cout << "7. Wybierz metode mutacji " << endl;
					cout << "8. Uruchom algorytm " << endl;
					cout << "9. Zakoncz testy " << endl;
					cout << "10. Wyczysc konsole " << endl;
					cin >> wybor;
				}
				if (wybor == 1)
				{
					string plik;
					fstream handler;
					while (true) {     //sprawdza czy plik istnieje
						cout << "Podaj nazwe pliku" << endl;
						cin >> plik;
						handler.open(plik.c_str());
						if (handler.is_open())
						{
							break;
						}

					}
					test->wczytajzPliku(plik);
					wczytano = true;
					wybor = 0;
				}
				else if (wybor == 2)
				{
					cout << "Aktualny czas to: " << czas << endl;
					cout << "Podaj czas (w sekundach) po ktorym ma zakonczyc sie dzialanie algorytmu" << endl;
					cin >> czas;

					wybor = 0;
				}
				else if (wybor == 3)
				{

					cout << "Aktualna Populacja to : " << populacja << endl;
					cout << "Podaj wielkosc populacji" << endl;
					cin >> populacja;
					wybor = 0;
				}
				else if (wybor == 4)
				{
					
					cout << "Aktualna wspolczynnik mutacji to  : " << wspMut << endl;
					cout << "Podaj wspolczynnik mutacji" << endl;
					cin >> wspMut;
					wybor = 0;

				}
				else if (wybor == 5)
				{
					cout << "Aktualna wspolczynnik krzyzowania to  : " << wspKrzyz << endl;
					cout << "Podaj wspolczynnik krzyzowania" << endl;
					cin >> wspKrzyz;
					wybor = 0;

				}
				else if (wybor == 6)
				{
					cout << "Dostepne metody krzyzowania to: " << endl;
					cout << "1.PMX" << endl;
					cout << "2.OX" << endl;
					cout << "Aktualna metoda krzyzowania to metoda o numerze : " << metodaKrzyzowania << endl;
					cout << "Podaj numer odpowiadajacy metodzie krzyzowania" << endl;
					cin >> metodaKrzyzowania;
					wybor = 0;

				}
				else if (wybor == 7)
				{
					cout << "Dostepne metody mutacji to: " << endl;
					cout << "1.Scrambler" << endl;
					cout << "2.Insert" << endl;
					cout << "Aktualna metoda mutacji to metoda o numerze : " << metodaMutacji << endl;
					cout << "Podaj numer odpowiadajacy metodzie mutacji" << endl;
					cin >> metodaMutacji;
					wybor = 0;

				}
				else if (wybor == 8)
				{
					if (wczytano)
					{
						test->Genetyczny(populacja,wspKrzyz,wspMut,metodaKrzyzowania,metodaMutacji,czas);
						cout << "sciezka po algorytmie genetycznym to: ";
						test->wyswietlKrawedzie();
						cout << endl;
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "minimalne wartosci w kolejnych momentach czasu: " << endl;
						timeTable = test->gettabelaCzasow();
						for (int i = 0; i < 13; i++)
						{
							cout << timeTable[i] << " ";
						}
						system("pause");
						wybor = 0;
					}
					else
					{
						cout << "najpierw wczytaj plik" << endl;
					}

				}
				else if (wybor == 9)
				{
					wybor = 0;
					break;

				}
				else if (wybor == 10)
				{
					system("cls");
					system("pause");
					wybor = 0;
				}
				else
				{
					cout << "Podaj mozliwa liczbe <1-10>";
					cin.clear();
					cin.ignore(123, '\n');

					while (!(cin >> wybor) || wybor < 0 || wybor>10)
					{
						cout << "Podaj mozliwa liczbe <1-7>";
						cin.clear();
						cin.ignore(123, '\n');


					}

				}
			}
			//TESTY


		}
		else if (wybor == 2)
		{
			Macierzkosztu *test = new Macierzkosztu(450);
			clock_t start;

			ofstream outData;
			outData.open("tempTest.csv");

			int *timeTable = new int[13];
			int populacja[3] = { 100,1000,3000 };
			double mut[3] = { 0.01,0.05,0.10 };
			double krzyz[3] = { 0.5,0.7,0.9 };

			//Ma³y plik
			outData << "Maly plik" << endl;
			test->wczytajzPliku("ftv47.atsp");

			cout << "MALY PLIK: " << endl;
			for (int k = 1; k < 3; k++)
			{
				for (int m = 1; m < 3; m++)
				{
					for (int wsp = 0;wsp < 3; wsp++)
					{
						test->Genetyczny(1000,krzyz[wsp], 0.01, k, m, 120);
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "minimalne wartosci w danym momencie czasu: " << endl;
						timeTable = test->gettabelaCzasow();
						for (int i = 0; i < 13; i++)
						{
							cout << timeTable[i] << " ";
							outData << timeTable[i] << ";";
						}
						outData << endl;
						cout << endl;
						cout << endl;
					}
				}
			}
			//Œredni plik
			outData << "Sredni plik" << endl;
			test->wczytajzPliku("ftv170.atsp");
			cout << "SREDNI PLIK: " << endl;
			for (int k = 1; k < 3; k++)
			{
				for (int m = 1; m < 3; m++)
				{
					for (int wsp = 0; wsp < 3; wsp++)
					{
						test->Genetyczny(1000, krzyz[wsp], 0.01, k, m, 240);
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "minimalne wartosci w danym momencie czasu: " << endl;
						timeTable = test->gettabelaCzasow();
						for (int i = 0; i < 13; i++)
						{
							cout << timeTable[i] << " ";
							outData << timeTable[i] << ";";
						}
						outData << endl;
						cout << endl;
						cout << endl;
					}
				}
			}
			//Du¿y Plik
			outData << "Duzy plik" << endl;
			cout << "Duzy plik" << endl;
			test->wczytajzPliku("rbg403.atsp");
			for (int k = 1; k < 3; k++)
			{
				for (int m = 1; m < 3; m++)
				{
					for (int wsp = 0; wsp < 3; wsp++)
					{
						test->Genetyczny(3000, krzyz[wsp], 0.01, k, m, 360);
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "minimalne wartosci w danym momencie czasu: " << endl;
						timeTable = test->gettabelaCzasow();
						for (int i = 0; i < 13; i++)
						{
							cout << timeTable[i] << " ";
							outData << timeTable[i] << ";";
						}
						outData << endl;
						cout << endl;
						cout << endl;
					}
				}
			}
			



			

				
	

				
			


			int x;
			cin >> x;
			wybor = 0;


		}
		else if (wybor == 3)
		{
			zewn = false;
		}
		else if (wybor < 0 || wybor> 3)
		{
			cout << "Podaj mozliwa liczbe <1-3>" << endl;
			cin.clear();
			cin.ignore(123, '\n');
			while (!(cin >> wybor) || wybor < 0 || wybor>3)
			{
				cout << "Podaj mozliwa liczbe <1-3>" << endl;
				cin.clear();
				cin.ignore(123, '\n');


			}

		}












	}


	return 0;

}