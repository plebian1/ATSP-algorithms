#include "macierzkosztu.h"

typedef std::chrono::high_resolution_clock Clock;
using namespace std;
double PCFreq = 0.0;
__int64 CounterStart = 0;




//losowania
double losujDouble()
{

	double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX+1);
	return r;
}

int losujOsobnika(double *tablica, double rand)
{
	int index = 0;
	while (rand >= tablica[index])
	{
		index++;
	}
	return index;

}



//krzy¿owania
int *PMX(int *osobnik1, int *osobnik2, int wielkosc, int *osobnikNowy)
{
	//int *osobnikNowy = new int[wielkosc];

	for (int i = 0; i < wielkosc; i++)
	{
		osobnikNowy[i] = -1;
	}

	//wylosowanie punktów krzy¿owania
	int w, k;
	w = rand() % wielkosc;
	k = rand() % wielkosc;
	//Mog¹ byæ te same, wartoœci, wtedy kopiujemy tylko ten 1 punkt

	if (w > k)
	{
		swap(w, k);
	}

	int roznica = k - w + 1;
	int *uzyte = new int[roznica];

	

	//kopiowanie g³ównego segmentu od rodzica, zapisanie jakie wierzcho³ki skopiowano, mapowanie przejœæ
	for (int i = w; i <= k; i++)
	{
		osobnikNowy[i] = osobnik1[i];
		uzyte[i - w] = osobnik1[i];
		
	}

	for (int i = w; i <= k; i++)
	{

		//czy dany wierzcho³ek zosta³ ju¿ przeniesiony do nowej tablicy
		bool nieZostaloUzyte = true;
		for (int j = 0; j < roznica; j++)
		{
			if (osobnik2[i] == uzyte[j])
			{
				nieZostaloUzyte = false;
			}
		}

		if (nieZostaloUzyte) 
		{
			bool dalej = true;

			int index = i;
			while (dalej)
			{
				for (int j = 0; j < wielkosc; j++)
				{
					if (osobnik2[j] == osobnik1[index])
					{
						//SprawdŸ czy to jest poza t¹ skopiowan¹ tabel¹
						bool nieNaLiscie = true;
						for (int a = 0; a < roznica; a++)
						{
							if (osobnik1[j] == uzyte[a])
							{
								nieNaLiscie = false;
							}


						}
						if (nieNaLiscie)
						{
							osobnikNowy[j] = osobnik2[i];
							dalej = false;
						}
						else
						{
							index = j;
						}



					}
				}


			}
		}



	}

	for (int i = 0; i < wielkosc; i++)
	{
		if (osobnikNowy[i] == -1)
		{

			osobnikNowy[i] = osobnik2[i];
		}
	}




	delete[] uzyte;





	return osobnikNowy;
}

int *OX(int *osobnik1, int *osobnik2, int wielkosc, int *osobnikNowy)
{



	
	//wylosowanie punktów krzy¿owania
	int w, k;
	w = rand() % wielkosc;
	k = rand() % wielkosc;
	//Mog¹ byæ te same, wartoœci, wtedy kopiujemy tylko ten 1 punkt

	/*while (w == k)
	{
		k = rand() % wielkosc;
	}*/


	if (w > k)
	{
		swap(w, k);
	}

	int roznica = k - w+1;
	int *uzyte = new int[roznica];


	//kopiowanie g³ównego segmentu od rodzica, zapisanie jakie wierzcho³ki skopiowano
	for (int i = w; i <= k; i++)
	{
		osobnikNowy[i] = osobnik1[i];
		uzyte[i - w] = osobnik1[i];
	}





	//kopiowanie z drugiego rodzica
	int indexNowy = (k + 1) % wielkosc;

	for (int i = 0; i < wielkosc; i++)
	{
		int index = (k+1 + i) % wielkosc;


		bool nieNaLiscie = true;

		for (int j = 0; j < roznica; j++)
		{
			if (osobnik2[index] == uzyte[j])
			{
				nieNaLiscie = false;
			}
		}

		if (nieNaLiscie)
		{
			osobnikNowy[indexNowy] = osobnik2[index];
			indexNowy = (indexNowy + 1) % wielkosc;
		}


	}

	delete[] uzyte;

	return osobnikNowy;
}



//Mutacje
int *Scrabmle(int *osobnik, double wspMutacji, int wielkosc)
{

	for (int i = 0; i < wielkosc; i++)
	{
		double szansa = losujDouble();
		if (szansa <= wspMutacji)
		{
			int w, k;

			w = rand() % wielkosc;

			k = rand() % wielkosc;
			while (w == k)
			{
				k = rand() % wielkosc;
			}

			swap(osobnik[w], osobnik[k]);
		}


	}
	return osobnik;

}


int *Insert(int *osobnik, double wspMutacji, int wielkosc)
{

	int *osobnikZapas = new int[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		double szansa = losujDouble();
		if (szansa <= wspMutacji)
		{
			//kopiujemy œcie¿kê
			for (int j = 0; j < wielkosc; j++)
			{
				osobnikZapas[j] = osobnik[j];
			}




			int w, k;

			w = rand() % wielkosc;
			k = rand() % wielkosc;
			while (w == k)
			{
				k = rand() % wielkosc;
			}


			if (w < k)
			{
				for (int z = w; z < k; z++)
				{
					osobnik[z] = osobnikZapas[z + 1];
					osobnik[k] = osobnikZapas[w];

				}
				
			}

			if (w > k)
			{

				for (int z = k; z < w; z++)
				{
					osobnik[z+1] = osobnikZapas[z];
					osobnik[k] = osobnikZapas[w];
				}


			}



			
		}


	}
	delete[] osobnikZapas;





	return osobnik;
}















Macierzkosztu::Macierzkosztu(int wielkosc)
{
	this->besttime = 0;
	this->wielkosc = wielkosc;
	this->minvalue = -1;
	this->timeResult = new int[13];
	this->tablicaKrawedzi = new int[wielkosc];
	this->tab = new int *[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		this->tab[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
			this->tab[i][j] = 0;

	}

}

Macierzkosztu::~Macierzkosztu()
{
	for (int i = 0; i < wielkosc; i++)
		delete[] tab[i]; //uwolnienie pamieci
	delete[] tab; //uwolnienie pamieci

	delete[] tablicaKrawedzi;
}

void Macierzkosztu::wyswietl()
{
	int wielkosc = this->wielkosc;
	cout << "  ";

	for (int k = 0; k < wielkosc; k++)
	{
		cout << setw(3) << k << " ";
	}
	cout << endl;

	for (int w = 0; w < wielkosc; w++)
	{
		cout << w << " ";
		for (int k = 0; k < wielkosc; k++)
		{
			cout << setw(3) << tab[w][k] << " ";
		}
		cout << endl;
	}
}

void Macierzkosztu::losowaMacierz(int wielkosc)
{
	int **tablica;
	tablica = new int *[wielkosc];

	for (int i = 0; i < wielkosc; i++)
	{
		tablica[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			tablica[i][j] = 1 + rand() % 99;
			if (i == j)
			{
				tablica[i][j] = -1;
			}
		}

	}

	for (int i = 0; i < this->wielkosc; i++)
		delete[] this->tab[i]; //uwolnienie pamieci
	delete[] this->tab; //uwolnienie pamieci

	this->tab = tablica;
	this->wielkosc = wielkosc;

}int ** Macierzkosztu::getTab()
{
	return this->tab;
}

int Macierzkosztu::getVaule()
{

	return this->minvalue;
}

void Macierzkosztu::setvaule(int x)
{
	this->minvalue = x;

}

int Macierzkosztu::getwielkosc()
{
	return this->wielkosc;
}

void Macierzkosztu::wczytajzPliku(string nazwa)
{

	string plik = nazwa;
	fstream handler;
	//while (true) {     //sprawdza czy plik istnieje
	//	cout << "Podaj nazwe pliku" << endl;
	//	cin >> plik;
	//	handler.open(plik.c_str());
	//	if (handler.is_open())
	//	{
	//		break;
	//	}

	//}
	string xd, b;

	handler.open(plik.c_str());
	int wielkosc;
	//pomijam pierwsze 3 wiersze
	for (int i = 0; i < 3; i++)
	{
		getline(handler, xd);
	}
	//zapisujê podan¹ wielkoœæ

	handler >> b;
	handler >> wielkosc;
	//pomijam ostatnie 3 wiersze
	for (int i = 0; i < 4; i++)
	{
		getline(handler, xd);

	}



	int **tablica;
	int a;
	tablica = new int *[wielkosc];

	for (int i = 0; i < wielkosc; i++)
	{
		tablica[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			handler >> a;
			tablica[i][j] = a;
			if (i == j)
			{
				//dane s¹ modyifkowane tak aby pasowa³y do algorytmu, tzn œcie¿ka do samego siebie jest oznaczona jako -1
				tablica[i][j] = -1;
			}

		}

	}

	for (int i = 0; i < this->wielkosc; i++)
		delete[] this->tab[i]; //uwolnienie pamieci
	delete[] this->tab; //uwolnienie pamieci

	this->tab = tablica;
	this->wielkosc = wielkosc;


}

void Macierzkosztu::setTablicaKrawedzi(int * tablica)
{
	for (int i = 0; i < this->wielkosc + 1; i++)
	{
		tablicaKrawedzi[i] = tablica[i];
	}
}

void Macierzkosztu::wyswietlKrawedzie()
{
	cout << tablicaKrawedzi[0];
	for (int i = 1; i < this->wielkosc; i++)
	{
		cout << " - " << tablicaKrawedzi[i];
	}
	cout << " - " << tablicaKrawedzi[0];
	cout << endl;
}

void Macierzkosztu::Genetyczny(int populacja, double wspKrzyzowania, double wspMutacji, int rodzajKrzyzowania, int rodzajMutacji, double czas)
{
	double start;
	start = std::clock();

	this->minvalue = INT_MAX;

	//miejsce na dane ogólne
	wielkosc = this->wielkosc;

	//tablica do przechowywania aktualnej populacji
	int **tablicaPopulacji;
	tablicaPopulacji = new int *[populacja];


	for (int i = 0; i < populacja; i++)
	{
		tablicaPopulacji[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			tablicaPopulacji[i][j] = j;
		}
	}

	//Wylosowanie pierwszej populacji, populacja zapisywana jest w reprezentacji œcie¿kowej
	for (int i = 0; i < populacja; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			random_shuffle(tablicaPopulacji[i], tablicaPopulacji[i] + wielkosc-1);

		}
	}
	

	//TUTAJ ZACZ¥Æ PÊTLÊ G£ÓWN¥ OD CZASU

	double timer = 0;
	int czasIndex =0;
	//this->besttime = timer;
	
	while(timer<czas)
	{
	
		timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	


		//Ewaluacja konkretnych populacji 
		//tablica przechowuj¹ca koszty œcie¿ek
		int *tablicaWartosci = new int[populacja];

		int najgorszy = 0;
		int najlepszy = INT_MAX;

		for (int i = 0; i < populacja; i++)
		{
			
			tablicaWartosci[i] = policzKoszt(tablicaPopulacji[i]);

			//poprawianie najlepszej œcie¿ki i najlepszej wartoœci w tym zbiorze
			if (tablicaWartosci[i] < najlepszy)
			{
				najlepszy = tablicaWartosci[i];

				if (tablicaWartosci[i] < this->minvalue)
				{
					this->minvalue = tablicaWartosci[i];

					for (int j = 0; j < wielkosc; j++)
					{
						tablicaKrawedzi[j] = tablicaPopulacji[i][j];
					}

				}
			}
			//zapisywanie najgorszej œcie¿ki
			if (tablicaWartosci[i] > najgorszy)
			{
				najgorszy = tablicaWartosci[i];
			}



			//suma += tablicaWartosci[i];
		}


		if (timer > czasIndex*(czas / 12))
		{
			
			this->timeResult[czasIndex] = this->minvalue;
			czasIndex++;

		}





		//dostosywanie do wartoœæi, faworyzowanie du¿o lepszy wyników
		double dif = double(najgorszy) / double(najlepszy);
		double base = (1 - 1 / dif) * double(najlepszy);  // to bêdzie odejmowane od 


		//mapowanie 
		double suma = 0;
		double *tablicaWartosciMapped = new double[populacja];
		for (int i = 0; i < populacja; i++)
		{
			double temp = double(tablicaWartosci[i]) - base;
			tablicaWartosciMapped[i] = 1 / temp; //im mniejsza wartoœæ tym lepiej wiêc funkcja odwrotna
			suma += tablicaWartosciMapped[i];
		}

		// to powinno wszystkie wartoœci zmieœciæ pomiêdzy 0 i 1 na obszarach odpowiadaj¹cych prawdopodobieñstwu ich wylosowania
		tablicaWartosciMapped[0] = tablicaWartosciMapped[0] / suma;
		for (int i = 1; i < populacja; i++)
		{
			tablicaWartosciMapped[i] = tablicaWartosciMapped[i] / suma + tablicaWartosciMapped[i - 1];
		}






		//Ci¹g losowañ, kolejno osobnika, czy krzy¿ujemy (wylosuj z kim), co mutujemy
		
		//tablica pomocnicza
		int **tablicaPopulacjiNowa;
		tablicaPopulacjiNowa = new int *[populacja];
		for (int i = 0; i < populacja; i++)
		{
			tablicaPopulacjiNowa[i] = new int[wielkosc];

		}

		
		int pop = 0;
		//tworzenie nowej populacji, jeszcze bez mutacji
		int osobnik1;
		while (pop < populacja - 1)
		{
			bool krzyz = false;
			double osRand = losujDouble();
			osobnik1 = losujOsobnika(tablicaWartosciMapped, osRand);

			//tablica powi¹zana z tym indeksem, czyli œcie¿ka któr¹ wylosowano

			int *osobnik1tab = new int[wielkosc];
			for (int i = 0; i < wielkosc; i++)
			{
				osobnik1tab[i] = tablicaPopulacji[osobnik1][i];
			}


			//Krzy¿owanie
			double krzyzRand = losujDouble();
			if (krzyzRand < wspKrzyzowania)
			{
				double os2Rand = losujDouble();
				int osobnik2 = losujOsobnika(tablicaWartosciMapped, os2Rand);

				//nie krzy¿ujemy ze samym sob¹;
				while (osobnik2 == osobnik1)
				{
					os2Rand = losujDouble();
					osobnik2 = losujOsobnika(tablicaWartosciMapped, os2Rand);
				}

				int *osobnik2tab = new int[wielkosc];
				for (int i = 0; i < wielkosc; i++)
				{
					osobnik2tab[i] = tablicaPopulacji[osobnik2][i];
				}


				int *os1 = new int[wielkosc];
				int *os2 = new int[wielkosc];

				if (rodzajKrzyzowania == 1)
				{
					//dokonujemy krzy¿owania w obie strony wiêc 2 osobniki powstaj¹

					//tu siê dzia³y z³e rzeczy z zarz¹dzaniem pamiêci¹, wiêc wygl¹da to jak wygl¹da
					int* osobnikPomTab = new int[wielkosc];
					int* osobnikPomTab2 = new int[wielkosc];
					osobnikPomTab = PMX(osobnik1tab, osobnik2tab, wielkosc, osobnikPomTab);
					osobnikPomTab2 = PMX(osobnik2tab, osobnik1tab, wielkosc, osobnikPomTab2);



					for (int i = 0; i < wielkosc; i++)
					{
						os1[i] = osobnikPomTab[i];
						os2[i] = osobnikPomTab2[i];
					}

					// Przypisujemy do tablicy nowych osobników
					for (int i = 0; i < wielkosc; i++)
					{
						tablicaPopulacjiNowa[pop][i] = os1[i];
						tablicaPopulacjiNowa[pop + 1][i] = os2[i];

					}



					delete[] os1;
					delete[] os2;
					delete[] osobnikPomTab;
					delete[] osobnikPomTab2;

				

				}
				else if (rodzajKrzyzowania == 2)
				{
					//dokonujemy krzy¿owania w obie strony wiêc 2 osobniki powstaj¹

					//tu siê dzia³y z³e rzeczy z zarz¹dzaniem pamiêci¹, wiêc wygl¹da to jak wygl¹da
					int* osobnikPomTab = new int[wielkosc];
					int* osobnikPomTab2 = new int[wielkosc];
					osobnikPomTab = OX(osobnik1tab, osobnik2tab, wielkosc, osobnikPomTab);
					osobnikPomTab2 = OX(osobnik2tab, osobnik1tab, wielkosc, osobnikPomTab2);



					for (int i = 0; i < wielkosc; i++)
					{
						os1[i] = osobnikPomTab[i];
						os2[i] = osobnikPomTab2[i];
					}

					// Przypisujemy do tablicy nowych osobników
					for (int i = 0; i < wielkosc; i++)
					{
						tablicaPopulacjiNowa[pop][i] = os1[i];
						tablicaPopulacjiNowa[pop + 1][i] = os2[i];

					}



					delete[] os1;
					delete[] os2;
					delete[] osobnikPomTab;
					delete[] osobnikPomTab2;
					
				}

				krzyz = true;

				delete[] osobnik2tab;

			}







			if (krzyz)
			{
				pop += 2;
			}
			else
			{
			
				for (int i = 0; i < wielkosc; i++)
				{
					tablicaPopulacjiNowa[pop][i] = osobnik1tab[i];
				}


				pop += 1;
			}

			delete[] osobnik1tab;
		}

		if (pop < populacja)
		{
			double osRand = losujDouble();
			int osobnik1 = losujOsobnika(tablicaWartosciMapped, osRand);

			//tablica powi¹zana z tym indeksem, czyli œcie¿ka któr¹ wylosowano
			int *osobnik1tab = new int[wielkosc];
			for (int i = 0; i < wielkosc; i++)
			{
				osobnik1tab[i] = tablicaPopulacji[osobnik1][i];
			}


			for (int i = 0; i < wielkosc; i++)
			{
				tablicaPopulacjiNowa[populacja - 1][i] = osobnik1tab[i];
			}

			delete[] osobnik1tab;

		}



		//Mutacje 

		for (int i = 0; i < populacja; i++)
		{
			if (rodzajMutacji == 1)
			{

				tablicaPopulacjiNowa[i] = Scrabmle(tablicaPopulacjiNowa[i], wspMutacji, wielkosc);

			}
			else if (rodzajMutacji == 2)
			{
				tablicaPopulacjiNowa[i] = Insert(tablicaPopulacjiNowa[i], wspMutacji, wielkosc);
			}
		}

		



		//Kopiowanie do tablicy g³ównej

		for (int i = 0; i < populacja; i++)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				tablicaPopulacji[i][j] = tablicaPopulacjiNowa[i][j];
			}
		}


		//cout << this->getVaule() << endl;
		/*this->wyswietlKrawedzie();*/



		delete[] tablicaWartosci;
		delete[] tablicaWartosciMapped;

		for (int i = 0; i < populacja; i++)
			delete[] tablicaPopulacjiNowa[i]; 
		delete[] tablicaPopulacjiNowa; 


		timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}



	//finalne sprawdzenie najlepszych wartoœci 
	for (int i = 0; i < populacja; i++)
	{
		//poprawianie najlepszej œcie¿ki i najlepszej wartoœci w tym zbiorze
		if (policzKoszt(tablicaPopulacji[i]) < this->minvalue)
		{

				this->minvalue = policzKoszt(tablicaPopulacji[i]);

				for (int j = 0; j < wielkosc; j++)
				{
					tablicaKrawedzi[j] = tablicaPopulacji[i][j];
				}

			
		}

	} 

	timeResult[12] = this->minvalue;






	for (int i = 0; i < populacja; i++)
		delete[] tablicaPopulacji[i];
	delete[] tablicaPopulacji;

}









//Funkcja do liczenia kosztu wybranej œcie¿ki dla danej macierzy kosztów
int Macierzkosztu::policzKoszt(int * tablica)
{
	int koszt = 0;
	int wierzcholek1, wierzcholek2;

	for (int i = 0; i < wielkosc-1; i++)
	{
		wierzcholek1 = tablica[i];
		wierzcholek2 = tablica[i + 1];
		koszt += tab[wierzcholek1][wierzcholek2];
	}

	wierzcholek1 = tablica[wielkosc-1];
	wierzcholek2 = tablica[0];
	koszt += tab[wierzcholek1][wierzcholek2];

	return koszt;
}

void Macierzkosztu::zachlanny()
{


	int wielkosc = this->wielkosc;
	int **tablica;
	tablica = new int *[wielkosc];

	//przepisanie tablicy
	for (int i = 0; i < wielkosc; i++)
	{
		tablica[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			tablica[i][j] = tab[i][j];
		}
	}

	//generowanie 1 rozwi¹zania
	int wierzcholek;
	int min = INT_MAX;
	int wartosc = 0;
	for (int i = 0; i < wielkosc; i++)
	{
		if (tablica[0][i] < min && tablica[0][i] != -1)
		{
			min = tablica[0][i];
			wierzcholek = i;
		}
	}
	tablicaKrawedzi[0] = 0;
	tablicaKrawedzi[1] = wierzcholek;
	wartosc += tablica[0][wierzcholek];

	for (int i = 0; i < wielkosc; i++)
	{
		tablica[i][0] = -1;
		tablica[i][wierzcholek] = -1;
	}


	for (int j = 0; j < wielkosc - 2; j++)
	{
		min = INT_MAX;
		int old = wierzcholek;
		for (int i = 0; i < wielkosc; i++)
		{
			if (tablica[old][i] != -1 && tablica[old][i] < min)
			{
				min = tablica[old][i];
				wierzcholek = i;
			}
		}

		tablicaKrawedzi[j + 2] = wierzcholek;
		wartosc += min;
		for (int i = 0; i < wielkosc; i++)
		{
			tablica[i][wierzcholek] = -1;
		}



	}
	tablicaKrawedzi[wielkosc] = 0;
	wartosc += tab[tablicaKrawedzi[wielkosc - 1]][0];


	this->minvalue = wartosc;

	for (int i = 0; i < wielkosc; i++)
		delete[] tablica[i]; //uwolnienie pamieci
	delete[] tablica; //uwolnienie pamieci

}



double Macierzkosztu::gettime()
{
	return this->besttime;
}

int * Macierzkosztu::gettabelaCzasow()
{
	

	return this->timeResult;
}




