#include <iomanip>
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
using namespace std;

class Macierzkosztu
{
	//pole
	int **tab;				//tablica przechowuj¹ca macierz kosztu
	int wielkosc;
	int minvalue;
	int *tablicaKrawedzi;


public:

	Macierzkosztu(int wielkosc);
	~Macierzkosztu();
	void wyswietl();
	void losowaMacierz(int wielkosc);
	void bruteForce();
	int** getTab();
	int getVaule();
	void setvaule(int x);
	int getwielkosc();
	void wczytajzPliku();
	void branchAndBound();
	void setTablicaKrawedzi(int *tablica);
	void wyswietlKrawedzie();
};