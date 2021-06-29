#include "macierzkosztu.h"

typedef std::chrono::high_resolution_clock Clock;
using namespace std;
double PCFreq = 0.0;
__int64 CounterStart = 0;



Macierzkosztu::Macierzkosztu(int wielkosc)
{
	this->besttime = 0;
	this->wielkosc = wielkosc;
	this->minvalue = -1;
	this->tablicaKrawedzi = new int[wielkosc + 1];
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
	string xd,b;
	
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
	for (int i = 1; i < this->wielkosc + 1; i++)
	{
		cout << " - " << tablicaKrawedzi[i];
	}
	cout << endl;
}

void Macierzkosztu::symWyw( double time)
{
	int wielkosc = this->wielkosc;


	int wartosc = INT_MAX ;



	
	this->zachlanny();
	wartosc = this->minvalue;
	



	
	//algorytm wy¿arzania czêœæ w³aœciwa
	double tempmax= pow(wielkosc,2); //temperatura pocz¹tkowa
	double temperatura = tempmax; // to bêdzie aktualna temperatura
	double tempmin = wielkosc;  //temperatura koñcowa dla podstawowego sch³adzania
	int iteracje = 1000*wielkosc; //ioœæ iteracji na danej temperaturze, d³ugoœæ epoki
	float wsp = 0.98; //wspó³czynnik zmiany temperatury
	int tempwartosc = wartosc;

	//czas
	double timer = 0;
	double start;

	//przepisanie tablicy z krawedziami
	int *tablicaKrawedziTemp;
	tablicaKrawedziTemp = new int[wielkosc + 1];


	for (int i = 0; i < wielkosc+1; i++)
	{
		tablicaKrawedziTemp[i] = tablicaKrawedzi[i];
	}



	int *tablicaKrawedziTemp2;
	tablicaKrawedziTemp2 = new int[wielkosc + 1];

	start =  std::clock();
	this->besttime = timer;
	while (timer < time) //zewnêtrzna pêtla zapewniaj¹ca dzia³anie algorytmu przez pewien okreœlony czas, zaczêta próba musi siê skoñczyæ
	{	
		temperatura = tempmax;
		while (temperatura > tempmin && timer <time )
		{
			timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			for (int i = 0; i < iteracje; i++)
			{

				//tablica do zapisywania nowych krawedzi
				for (int i = 0; i < wielkosc + 1; i++)
				{
					tablicaKrawedziTemp2[i] = tablicaKrawedziTemp[i];
				}



				int w, k;

				w = rand() % wielkosc;
				k = rand() % wielkosc;

				if (w < k)
				{
					for (int z = w; z < k; z++)
					{
						tablicaKrawedziTemp2[z] = tablicaKrawedziTemp[z + 1];
						tablicaKrawedziTemp2[k] = tablicaKrawedziTemp[w];
					}
					tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje
				}

				if (w > k)
				{

					for (int z = k; z < w; z++)
					{
						tablicaKrawedziTemp2[z + 1] = tablicaKrawedziTemp[z];
						tablicaKrawedziTemp2[k] = tablicaKrawedziTemp[w];
					}
					tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

				}




				tempwartosc = this->policzKoszt(tablicaKrawedziTemp2);
				//je¿eli wylosowane po³¹czenia daj¹ mniejszy koszt ni¿ aktualna œcie¿ka to j¹ zamieniamy
				if (tempwartosc < wartosc)
				{

					wartosc = tempwartosc;
					for (int i = 0; i < wielkosc + 1; i++)
					{
						tablicaKrawedziTemp[i] = tablicaKrawedziTemp2[i];
					}

					if (wartosc < minvalue)
					{
						minvalue = wartosc;
						for (int i = 0; i < wielkosc + 1; i++)
						{

							tablicaKrawedzi[i] = tablicaKrawedziTemp2[i];
						}
						//to jest w sumie tylko do sprawozdania
						timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
						this->besttime = timer;
						
					}



				}
				else // je¿eli nie to odwo³ujemy siê do magicznego wzoru który mówi nam czy przyjmujemy wynik czy nie
				{
					float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float x = exp(float(wartosc - tempwartosc) / float(temperatura));
					if (r < x)
					{
						wartosc = tempwartosc;
						for (int i = 0; i < wielkosc + 1; i++)
						{

							tablicaKrawedziTemp[i] = tablicaKrawedziTemp2[i];
						}
					}



				}




			}


			temperatura *= wsp;

		}
	}
	delete[] tablicaKrawedziTemp2;
	delete[] tablicaKrawedziTemp;


}

//Funkcja do liczenia kosztu wybranej œcie¿ki dla danej macierzy kosztów
int Macierzkosztu::policzKoszt(int * tablica)
{
	int koszt = 0;
	int wierzcholek1, wierzcholek2;

	for (int i = 0; i < wielkosc ; i++)
	{
			wierzcholek1 = tablica[i];
			wierzcholek2 = tablica[i + 1];
			koszt += tab[wierzcholek1][wierzcholek2];
	}

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

bool Dopuszczalny(int w, int k, int ** tablicaTabu, int wielkosc)
{
	bool jest = true;

	for (int i = 0; i < wielkosc; i++)
	{
		if ((w == tablicaTabu[i][0] && k == tablicaTabu[i][1]) || (k == tablicaTabu[i][0] && w == tablicaTabu[i][1]))
		{
			jest = false;
			break;
		}
	}




	return jest;
}


double Macierzkosztu::gettime()
{
	return this->besttime;
}

void Macierzkosztu::tabuSearch(int sasiad, double time)
{

	int wielkosc = this->wielkosc;
	

	this->zachlanny();

	//czêœæ w³aœciwa algorytmu
	
	int  reset = wielkosc*4 ; // po ilu iteracjach algorytmu losujemy nowy pocz¹tek
	int kadencja = reset/4; //definiuje jak d³ugo wynik znajduje siê w tablicy tabu
	int iteracje = wielkosc; // ile razy resetujemy (losujemy na nowo) pozycjê




	//pocz¹tkowe ustawienie tablic s³u¿¹cych do operowania na zamianianych krawêdziach
	int *tablicaKrawedziTemp;
	tablicaKrawedziTemp = new int[wielkosc + 1];
	for (int i = 0; i < wielkosc + 1; i++)
	{
		tablicaKrawedziTemp[i] = tablicaKrawedzi[i];
	}
	int *tablicaKrawedziTemp2;
	tablicaKrawedziTemp2 = new int[wielkosc + 1];
	for (int i = 0; i < wielkosc + 1; i++)
	{
		tablicaKrawedziTemp2[i] = tablicaKrawedziTemp[i];
	}

	double timer = 0;
	double start;

	int i=0;
	start = std::clock();
	this->besttime = timer;
	while(timer < time)
	{
		//losowanie nowego punktu startowego
		random_shuffle(tablicaKrawedziTemp, tablicaKrawedziTemp + wielkosc - 1);
		tablicaKrawedziTemp[wielkosc] = tablicaKrawedziTemp[0];

		timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		
		//deklaracja lub reset tablicy tabu przy nowo losowanej instancji
		//blokada jest usuwana poprzez nadpisywanie najstarszego dodanego wyniku kiedy tablica jest ju¿ wype³niona
		int **tablicaTabu;
		tablicaTabu = new int*[kadencja];
		for (int g = 0; g < kadencja; g++)
		{
			tablicaTabu[g] = new int[2];
			for (int j = 0; j <2; j++)
				tablicaTabu[g][j] = -1;
		}

		for (int j = 0; j < reset; j++)
		{
			if (timer < time)
			{
				int max = INT_MAX;
				int koszt;
				int wierzcholek1, wierzcholek2;

				//przypisanie tablicy tymczasowej odpowiednich wartoœci
				for (int h = 0; h < wielkosc + 1; h++)
				{
					tablicaKrawedziTemp2[h] = tablicaKrawedziTemp[h];
				}

				//ewaluacja dostêpnych ruchów ruchów
				for (int w = 0; w < wielkosc; w++)
				{
					for (int k = w + 1; k < wielkosc; k++)
					{



						if (sasiad == 1) //zamiana miejscami dwóch wierzcho³ków ( swap)
						{

							if (Dopuszczalny(tablicaKrawedziTemp2[w], tablicaKrawedziTemp2[k], tablicaTabu, kadencja))
							{
								swap(tablicaKrawedziTemp2[w], tablicaKrawedziTemp2[k]);
								tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

								koszt = policzKoszt(tablicaKrawedziTemp2);



								/*if (i > 1)
								{
									cout << i << ". " << koszt << endl;
								}*/

								if (koszt < max)
								{
									max = koszt;
									wierzcholek1 = w;
									wierzcholek2 = k;
								}

								//przywracanie starej wersji tablicy

								swap(tablicaKrawedziTemp2[w], tablicaKrawedziTemp2[k]);
								tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0]; //kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

							}
						}
						else if (sasiad == 2) //zamiana kolejnoœci wierzcho³ków pomiêdzy pierwszym i drugim w³¹cznie
						{
							if (Dopuszczalny(tablicaKrawedziTemp2[w], tablicaKrawedziTemp2[k], tablicaTabu, kadencja))
							{

								//zamiana

								int roznica = k - w;
								for (int z = 0; z <= roznica; z++)
								{
									tablicaKrawedziTemp2[w + z] = tablicaKrawedziTemp[k - z];
								}




								tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

								//liczenie kosztu
								koszt = policzKoszt(tablicaKrawedziTemp2);
								if (koszt < max)
								{
									max = koszt;
									wierzcholek1 = w;
									wierzcholek2 = k;
								}
								//przywracanie starej wersji tablicy
								for (int h = 0; h < wielkosc + 1; h++)
								{
									tablicaKrawedziTemp2[h] = tablicaKrawedziTemp[h];
								}
							}

						}
						else if (sasiad == 3) //wstawianie wierzcho³ka na konkretne miejsce 
						{
							if (Dopuszczalny(tablicaKrawedziTemp2[w], k, tablicaTabu, kadencja))
							{
								//w -> k

								for (int z = w; z < k; z++)
								{
									tablicaKrawedziTemp2[z] = tablicaKrawedziTemp[z + 1];
									tablicaKrawedziTemp2[k] = tablicaKrawedziTemp[w];
								}
								tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

								//liczenie kosztu
								koszt = policzKoszt(tablicaKrawedziTemp2);
								if (koszt < max)
								{
									max = koszt;
									wierzcholek1 = w;
									wierzcholek2 = k;
								}
								//przywracanie starej wersji tablicy
								for (int h = 0; h < wielkosc + 1; h++)
								{
									tablicaKrawedziTemp2[h] = tablicaKrawedziTemp[h];
								}
							}


							if (Dopuszczalny(tablicaKrawedziTemp2[k], w, tablicaTabu, kadencja))
							{


								//k -> w
								for (int z = w; z < k; z++)
								{
									tablicaKrawedziTemp2[z + 1] = tablicaKrawedziTemp[z];
									tablicaKrawedziTemp2[w] = tablicaKrawedziTemp[k];
								}
								tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

								//liczenie kosztu
								koszt = policzKoszt(tablicaKrawedziTemp2);
								if (koszt < max)
								{
									max = koszt;
									wierzcholek1 = k;
									wierzcholek2 = w;
								}
								//przywracanie starej wersji tablicy
								for (int h = 0; h < wielkosc + 1; h++)
								{
									tablicaKrawedziTemp2[h] = tablicaKrawedziTemp[h];
								}

							}
						}


					}


				}

				if (sasiad == 1)
				{
					swap(tablicaKrawedziTemp[wierzcholek1], tablicaKrawedziTemp[wierzcholek2]);
					tablicaKrawedziTemp[wielkosc] = tablicaKrawedziTemp[0]; //kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

					//cout << i << ". " << koszt << endl;

					if (koszt < this->minvalue)
					{
						this->minvalue = koszt;
						for (int h = 0; h < wielkosc + 1; h++)
						{
							this->tablicaKrawedzi[h] = tablicaKrawedziTemp[h];


						}

						//to jest w sumie tylko do sprawozdania
						timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
						this->besttime = timer;
					}
					//dodawanie to tablicyTabu
					tablicaTabu[j%kadencja][0] = tablicaKrawedziTemp[wierzcholek1];
					tablicaTabu[j%kadencja][1] = tablicaKrawedziTemp[wierzcholek2];
				}
				else if (sasiad == 2)
				{

					//cout << i << ". " << koszt << endl;


					//zamiana
					int roznica = wierzcholek2 - wierzcholek1;
					for (int z = 0; z <= roznica; z++)
					{
						tablicaKrawedziTemp2[wierzcholek1 + z] = tablicaKrawedziTemp[wierzcholek2 - z];
					}
					tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje
					for (int h = 0; h < wielkosc + 1; h++)
					{
						tablicaKrawedziTemp[h] = tablicaKrawedziTemp2[h];
					}



					//ewentualne poprawienie wyniku
					if (koszt < this->minvalue)
					{
						this->minvalue = koszt;
						for (int h = 0; h < wielkosc + 1; h++)
						{
							this->tablicaKrawedzi[h] = tablicaKrawedziTemp[h];


						}
						//to jest w sumie tylko do sprawozdania
						timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
						this->besttime = timer;
					}
					//dodanie do tablicy tabu
					tablicaTabu[j%kadencja][0] = tablicaKrawedziTemp[wierzcholek1];
					tablicaTabu[j%kadencja][1] = tablicaKrawedziTemp[wierzcholek2];

				}
				else if (sasiad == 3)
				{
					// w -> k
					if (wierzcholek1 < wierzcholek2)
					{
						//zamiana 
						for (int z = wierzcholek1; z < wierzcholek2; z++)
						{
							tablicaKrawedziTemp2[z] = tablicaKrawedziTemp[z + 1];
							tablicaKrawedziTemp2[wierzcholek2] = tablicaKrawedziTemp[wierzcholek1];
						}
						tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje

						for (int h = 0; h < wielkosc + 1; h++)
						{
							tablicaKrawedziTemp[h] = tablicaKrawedziTemp2[h];
						}
						//ewentualne poprawienie wyniku
						if (koszt < this->minvalue)
						{
							this->minvalue = koszt;
							for (int h = 0; h < wielkosc + 1; h++)
							{
								this->tablicaKrawedzi[h] = tablicaKrawedziTemp[h];

							}
							//to jest w sumie tylko do sprawozdania
							timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
							this->besttime = timer;
						}

						//dodanie do tablicy tabu
						tablicaTabu[j%kadencja][0] = tablicaKrawedziTemp[wierzcholek2];
						tablicaTabu[j%kadencja][1] = wierzcholek1;





					}
					// k -> w
					else if (wierzcholek2 < wierzcholek1)
					{
						//zamiana 
						for (int z = wierzcholek2; z < wierzcholek1; z++)
						{
							tablicaKrawedziTemp2[z + 1] = tablicaKrawedziTemp[z];
							tablicaKrawedziTemp2[wierzcholek2] = tablicaKrawedziTemp[wierzcholek1];
						}
						tablicaKrawedziTemp2[wielkosc] = tablicaKrawedziTemp2[0];//kiedy zamieniamy 1, jak nie zamieniamy 1 to sie nic nie dzieje
						for (int h = 0; h < wielkosc + 1; h++)
						{
							tablicaKrawedziTemp[h] = tablicaKrawedziTemp2[h];
						}
						//ewentualne poprawienie wyniku
						if (koszt < this->minvalue)
						{
							this->minvalue = koszt;
							for (int h = 0; h < wielkosc + 1; h++)
							{
								this->tablicaKrawedzi[h] = tablicaKrawedziTemp[h];

							}
							//to jest w sumie tylko do sprawozdania
							timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
							this->besttime = timer;
						}

						//dodanie do tablicy tabu
						tablicaTabu[j%kadencja][0] = tablicaKrawedziTemp[wierzcholek2];
						tablicaTabu[j%kadencja][1] = wierzcholek1;

					}



				}



			}

		}



		for(int j=0; j<kadencja;j++)
			delete[] tablicaTabu[j]; //uwolnienie pamieci
		delete[] tablicaTabu; //uwolnienie pamieci

		
	}




}



