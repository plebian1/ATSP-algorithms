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
	//Macierzkosztu *test = new Macierzkosztu(450);
	//
	//double time = 1000;
	//int sasiad = 3;
	//int iteracje = 100;
	//int schladzanie = 2;
	////test->losowaMacierz(20);
	//test->wczytajzPliku("rbg403.atsp");
	////test->wczytajzPliku("ftv170.atsp");
	////test->wczytajzPliku("ftv47.atsp");
	////test->wyswietl();
	//test->zachlanny();
	//cout << "sciezka po zachlannym to: ";
	//test->wyswietlKrawedzie();
	//cout << test->getVaule() << endl;
	//test->symWyw(schladzanie,time);
	//cout << "sciezka po wyzazaniu to: ";
	//test->wyswietlKrawedzie();
	//cout << test->getVaule()<<endl;
	/*test->tabuSearch(sasiad,time);
	cout << "sciezka po tabu to: ";
	test->wyswietlKrawedzie();
	cout << test->getVaule() << endl;*/
	//delete test;
	//int x;
	//cin >> x;


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
			Macierzkosztu *test = new Macierzkosztu(450);
			wybor = 0;
			bool wczytano = false;
			int sasiad = 1;
			double czas = 180;
			while (wewlista)
			{
				if (wybor == 0)
				{
					cout << "Testowanie reczne" << endl;
					cout << "Co chcesz teraz zrobic? Wpisz cyfre odpowiadajaca wybranej opcji i potwierdz enterem" << endl;
					cout << "1. Wczytaj dane z pliku. " << endl;
					cout << "2. Wprowadz kryterium stopu " << endl;
					cout << "3. Dokonaj wyboru definicji sasiedztwa" << endl;
					cout << "4. Uruchom TabuSearch dla wczytanego pliku" << endl;
					cout << "5. Uruchom Symulowane wyzarzanie dla wczytanego pliku" << endl;
					cout << "6. Zakoncz testy " << endl;
					cout << "7. Wyczysc konsole " << endl;
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
					cout << "Uznano, ze jedynym kryterium pozwalajacym porownac efektywanosc algorytmow jest czas" << endl;
					cout << "Dla Symulomanego wyzazania jest to czas po ktorym algorytm odrazu zakonczy dzialania" << endl;
					cout << "Dla Tabu Search algorytm dokonczy przeszukiwanie do nastepnej dywersyfikacji, przy najwiekszym pliku jest to maksymalnie okolo minuty opoznienia" << endl;
					cout << "Aktualny czas to: " << czas << endl;
					cout << "Podaj czas (w sekundach) po ktorym ma zakonczyc sie dzialanie algorytmu" << endl;
					cin >> czas;
									   
					wybor = 0;
				}
				else if (wybor == 3)
				{
					cout << "Dostepne sa nastepujace definicje sasiedztwa / ruchu zmieniajacego aktualne ustawienie: " << endl;
					cout << "1. Zamienienie 2 wierzcholkow" << endl;
					cout << "2. Odwrocenie kolejnosc pomiedzy 2 wierzcholkami" << endl;
					cout << "3. Przesuniecie wierzcholka na okreslona pozycje " << endl;
					cout << "Aktualna definicja to definicja numer: " << sasiad << endl;
					cout << "Podaj numer odpowiadajacy definicji ktora chcesz wybrac" << endl;
					cin >> sasiad;
					wybor = 0;
				}
				else if (wybor == 4)
				{
					if (wczytano)
					{
						test->tabuSearch(sasiad, czas);
						cout << "sciezka po tabu to: ";
						test->wyswietlKrawedzie();
						cout << endl;
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "czas jej osiagnieca to: " << test->gettime() << endl;
						system("pause");
					}
					else
					{
						cout << "najpierw wczytaj plik" << endl;
					}
					wybor = 0;
					
				}
				else if (wybor == 5)
				{
					if (wczytano)
					{
						test->symWyw(czas);
						cout << "sciezka po Symulowanym wyzarzaniu to: ";
						test->wyswietlKrawedzie();
						cout << endl;
						cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
						cout << "czas jej osiagnieca to: " << test->gettime() << endl;
						system("pause");
						wybor = 0;
					}
					else
					{
						cout << "najpierw wczytaj plik" << endl;
					}
					
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
			Macierzkosztu *test = new Macierzkosztu(450);
			clock_t start;


			test->wczytajzPliku("ftv47.atsp");

			cout << "MALY PLIK: " << endl;

			test->symWyw(120);
			cout << "sciezka Symulowanym wyzazaniu to: ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to: " << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime()<<endl;
			cout << endl;

			test->tabuSearch(1, 120);
			cout << "sciezka po tabu z 1 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout <<"Wartosc tej sciezki to:"<< test->getVaule() << endl; 
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(2, 120);
			cout << "sciezka po tabu z 2 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(3, 120);
			cout << "sciezka po tabu z 3 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;


		
			test->wczytajzPliku("ftv170.atsp");
			cout << "SREDNI PLIK: " << endl;

			test->symWyw(240);
			cout << "sciezka Symulowanym wyzazaniu to: ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(1, 240);
			cout << "sciezka po tabu z 1 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(2, 240);
			cout << "sciezka po tabu z 2 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(3, 240);
			cout << "sciezka po tabu z 3 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			

			test->wczytajzPliku("rbg403.atsp");
			cout << "DUZY PLIK: " << endl;

			test->symWyw(360);
			cout << "sciezka Symulowanym wyzazaniu to: ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(1, 360);
			cout << "sciezka po tabu z 1 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(2, 360);
			cout << "sciezka po tabu z 2 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;
			cout << endl;

			test->tabuSearch(3, 360);
			cout << "sciezka po tabu z 3 definicja sasiedztwa to : ";
			test->wyswietlKrawedzie();
			cout << "Wartosc tej sciezki to:" << test->getVaule() << endl;
			cout << "czas jej osiagnieca to: " << test->gettime() << endl;





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