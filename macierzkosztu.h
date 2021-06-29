#include <iomanip>
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <algorithm> 
#include <cstdio>
#include <windows.h>
#include <chrono>
using namespace std;

class Macierzkosztu
{
	//pole
	int **tab;				//tablica przechowuj¹ca macierz kosztu
	int wielkosc;
	int minvalue;
	int *tablicaKrawedzi;
	double besttime;
	int  *timeResult;


public:

	Macierzkosztu(int wielkosc);
	~Macierzkosztu();
	void wyswietl();
	void losowaMacierz(int wielkosc);
	int** getTab();
	int getVaule();
	void setvaule(int x);
	int getwielkosc();
	void wczytajzPliku(string nazwa);
	void setTablicaKrawedzi(int *tablica);
	void wyswietlKrawedzie();
	
	void Genetyczny(int populacja, double wspKrzyzowania, double wspMutacji, int rodzajKrzyzowania, int rodzajMutacji, double czas);

	int policzKoszt(int *tablica);
	void zachlanny();

	double gettime();
	int* gettabelaCzasow();
};