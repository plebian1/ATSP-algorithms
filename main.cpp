#include<iostream>
#include<cmath>
#include "macierzkosztu.h"
#include <sstream>
#include <cstdio>
#include <windows.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;
double PCFreq = 0.0;
__int64 CounterStart = 0;



int main()
{
	srand(time(NULL));
	//Macierzkosztu *test = new Macierzkosztu(20);

	bool zewn = true;
	int wybor = 0;
	cout << "Program do testowania problemu komiwoja¿era" << endl << "Autor: Jedrzej Piatek" << endl;

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
			Macierzkosztu *test = new Macierzkosztu(20);
			wybor = 0;
			while (wewlista)
			{
				if (wybor == 0)
				{
					cout << "Testowanie reczne" << endl;
					cout << "Co chcesz teraz zrobic? Wpisz cyfre odpowiadajaca wybranej opcji i potwierdz enterem" << endl;
					cout << "1. Wczytaj dane z pliku. " << endl;
					cout << "2. Wygeneruj macierz losowo. " << endl;
					cout << "3. Wyœwietl macierz na ekranie. " << endl;
					cout << "4. Brute Force, dla macierz wiekszych niz 14 silnie odradzane ze wzgledu na dlugosc obliczen " << endl;
					cout << "5. BranchAndBound " << endl;
					cout << "6. Wroc do menu glownego " << endl;
					cout << "7. Wyczysc konsole " << endl;
					cin >> wybor;
				}
				if (wybor == 1)
				{
					test->wczytajzPliku();
					wybor = 0;
				}
				else if (wybor == 2)
				{
					int wielkosc;
					cout << "Podaj wielkosc " << endl;
					cin >> wielkosc;
					test->losowaMacierz(wielkosc);
					wybor = 0;
				}
				else if (wybor == 3)
				{
					test->wyswietl();
					wybor = 0;
				}
				else if (wybor == 4)
				{
					test->bruteForce();
					test->wyswietlKrawedzie();
					cout << "Laczny koszt to: " << test->getVaule()<<endl;
					wybor = 0;
				}
				else if (wybor == 5)
				{
					test->branchAndBound();
					test->wyswietlKrawedzie();
					cout << "Laczny koszt to: " << test->getVaule()<<endl;
					wybor = 0;
				}
				else if (wybor == 6)
				{
					wybor = 0;
					break;

				}
				else if (wybor == 7)
				{
					system("cls");
					system("pause");
					wybor = 0;
				}
				else
				{
					cout << "Podaj mozliwa liczbe <1-7>";
					cin.clear();
					cin.ignore(123, '\n');

					while (!(cin >> wybor) || wybor < 0 || wybor>7)
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
			Macierzkosztu *test = new Macierzkosztu(20);
			clock_t start;
			double czas = 0;
			double wynik = 0;
			double czas2 = 0;
			double wynik2 = 0;
			int wielkosc1[7] = {6,7,8,9,10,11,12}; //wielkosci N dla bruteforce
			int wielkosc2[7] = { 6,10,15,20,30,40,50 }; //wielkosci N dla B&B
			cout << "WYNIKI DLA BRUTE FORCE" << endl;
			for (int i = 0; i < 7; i++)
			{
				czas = 0;
				for (int j = 0; j < 100; j++)
				{
					test->losowaMacierz(wielkosc1[i]);

					start = std::clock();
					test->bruteForce();
					czas += (std::clock() - start) / (double)CLOCKS_PER_SEC;
				}
				wynik = czas / 100;
				cout << "Wynik dla N = " << wielkosc1[i] << " to:" << wynik<<endl;
			}

			cout << "WYNIKI DLA B&B" << endl;
			for (int i = 0; i < 7; i++)
			{
				czas2 = 0;
				for (int j = 0; j < 100; j++)
				{
					test->losowaMacierz(wielkosc2[i]);

					start = std::clock();
					test->branchAndBound();
					czas2 += (std::clock() - start) / (double)CLOCKS_PER_SEC;
				}
				wynik2 = czas2 / 100;
				cout << "Wynik dla N = " << wielkosc2[i] << " to:" << wynik2 << endl;
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