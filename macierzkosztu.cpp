#include "macierzkosztu.h"

void permute(int *a, int l, int r, Macierzkosztu *test)
{
	// liœæ w drzewie, koñcowa permutacja 
	if (l == r)
	{
		int suma = 0;
		int **tab = test->getTab();
		suma += tab[0][a[0]];

		for (int i = 0; i < r; i++)
		{
			suma += tab[a[i]][a[i + 1]];
		}
		suma += tab[a[r]][0];

		if (suma < test->getVaule() || test->getVaule() == -1)
		{
			int *tab;
			tab = new int[test->getwielkosc() + 1];
			tab[0] = 0;
			tab[test->getwielkosc()] = 0;
			for (int i = 0; i < test->getwielkosc() - 1; i++)
			{
				tab[i + 1] = a[i];
			}
			test->setTablicaKrawedzi(tab);
				
			test->setvaule(suma);

			
		}
	}
	else
	{
		for (int i = l; i <= r; i++)
		{			 
			swap(a[l], a[i]);
			//rekurancja
			permute(a, l + 1, r,test);
			swap(a[l], a[i]);
		}
	}
}



void Branch(int **nowaTablica,int **tablicaKrawedzi, int wielkosc, int iter, Macierzkosztu *test,int wartosc,int *tablicaOznaczen)
{
	//ostateczny przypadek, koñcz¹cy rekurenjê dla tablicy 2x2
	if (wielkosc == 2)
	{	

		int a = 0;
		for(int i = 1; i < 3; i++)
		{
			for(int j = 1; j < 3; j++)
			{
				if (nowaTablica[i][j] != -1)
				{
					wartosc += nowaTablica[i][j];
					tablicaKrawedzi[test->getwielkosc() - 2 + a][0] = nowaTablica[i][0];
					tablicaKrawedzi[test->getwielkosc() - 2 + a][1] = nowaTablica[0][j];
					a++;
				}
			}
		}
		if (test->getVaule() > wartosc)
		{
			int *tab;
			tab = new int[test->getwielkosc() + 1];
			int prev;
			tab[0] = tablicaKrawedzi[0][0];
			prev = 0;
			tab[test->getwielkosc()] = tablicaKrawedzi[0][0];
			
			for (int i = 0; i < test->getwielkosc(); i++)
			{
				for (int j = 0; j < test->getwielkosc(); j++)
				{
					if (tablicaKrawedzi[j][0] == tablicaKrawedzi[prev][1])
					{
						tab[i + 1] = tablicaKrawedzi[j][0];
						prev = j;
						break;
					}
				}
			}
			test->setTablicaKrawedzi(tab);
			delete[] tab;

			test->setvaule(wartosc);
		}

	}
	else
	{
		int temp = 0;
		//tablica do modyfikowania na potrzeby algorytmu
		int **tablica;
		tablica = new int *[wielkosc + 1];
		for (int i = 0; i < wielkosc + 1; i++)
		{
			tablica[i] = new int[wielkosc + 1];
			for (int j = 0; j < wielkosc + 1; j++)
			{
				tablica[i][j] = nowaTablica[i][j];
			}

		}

		//kopia tablicy, na potrzeby tego kiedy nie wybieramy danej krawêdzi
	


		

		//redukowanie macierzy

		//redukowanie wierszy
		for (int i = 1; i < wielkosc + 1; i++)
		{
			//szukanie minimum w ka¿dym wierszu
			int min = -1;
			for (int j = 1; j < wielkosc + 1; j++)
			{
				if (tablica[i][j] != -1)
				{
					if (min == -1)
					{
						min = tablica[i][j];
					}
					if (min > tablica[i][j])
					{
						min = tablica[i][j];
					}
				}
			}
			//redukowanie ka¿dego wiersza, jak min = 0, to nie trzeba
			if (min != 0)
			{
				for (int j = 1; j < wielkosc + 1; j++)
				{
					if (tablica[i][j] != -1)
					{
						tablica[i][j] -= min;

					}

				}
				temp += min;
			}

		}

		//redukowanie kolumn
		for (int i = 1; i < wielkosc+1; i++)
		{
			//szukanie minimum w ka¿dej kolumnie
			int min = -1;
			for (int j = 1; j < wielkosc+1; j++)
			{
				if (tablica[j][i] != -1)
				{
					if (min == -1)
					{
						min = tablica[j][i];
					}
					if (min > tablica[j][i])
					{
						min = tablica[j][i];
					}
				}
			}
			//redukowanie ka¿dej kolumny, jak min = 0, to nie trzeba
			if (min != 0)
			{
				for (int j = 1; j < wielkosc+1; j++)
				{
					if (tablica[j][i] != -1)
					{
						tablica[j][i] -= min;
					}
				}
				temp += min;
			}
		}


		//zwiekszamy dolne ograniczenie
		wartosc += temp;

		int **tablicawartosci; //przechowywanie wartoœci wzrostu LB dla danego 0
		tablicawartosci = new int *[wielkosc];
		for (int i = 0; i < wielkosc; i++)
		{
			tablicawartosci[i] = new int[wielkosc];
		}
		for (int i = 0; i < wielkosc; i++)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				tablicawartosci[i][j] = -1;
			}

		}




		for (int i = 0; i < wielkosc; i++)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				if (tablica[i+1][j+1] == 0)
				{
					int min = -1;
					int suma = 0;
					//po wierszach
					for (int w = 0; w < wielkosc; w++)
					{
						if (tablica[w+1][j+1] != -1 && w != i)
						{
							if (min == -1)
							{
								min = tablica[w + 1][j + 1];
							}
							if (min > tablica[w + 1][j + 1])
							{
								min = tablica[w + 1][j + 1];
							}
						}
					}
					suma += min;
					//po kolumnach
					min = -1;
					for (int k = 0; k < wielkosc; k++)
					{
						if (tablica[i+1][k+1] != -1 && k != j)
						{
							if (min == -1)
							{
								min = tablica[i+1][k + 1];
							}
							if (min > tablica[i + 1][k + 1])
							{
								min = tablica[i + 1][k + 1];
							}
						}
					}

					suma += min;
					tablicawartosci[i][j] = suma;
				}
			}
		}

		
		int wiersze, kolumny;
		int max = -1;
		for (int i = 0; i < wielkosc; i++)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				if (max < tablicawartosci[i][j])
				{
					max = tablicawartosci[i][j];
					tablicaKrawedzi[iter][0] = tablica[i+1][0];
					tablicaKrawedzi[iter][1] = tablica[0][j+1];
					wiersze = i + 1;
					kolumny = j + 1;
				}
			}
		}


		
	

		int **tablicaKopia; 
		tablicaKopia = new int *[wielkosc + 1];
		for (int i = 0; i < wielkosc + 1; i++)
		{
			tablicaKopia[i] = new int[wielkosc + 1];
			for (int j = 0; j < wielkosc + 1; j++)
			{
				tablicaKopia[i][j] = tablica[i][j];
			}

		}

		




		//Kopia tablicy oznaczeñ, na potrzeby tego kiedy nie wybieramy danej krawêdzi
		int *tablicaOznaczenKopia;
		tablicaOznaczenKopia = new int[test->getwielkosc()];
		for (int i = 0;i < test->getwielkosc(); i++)
		{
			tablicaOznaczenKopia[i] = tablicaOznaczen[i];
		}




		//wybieramy poddrzewo z dan¹ krawêdzi¹
		//blokowanie mo¿liwoœci cyklu
		for (int i = 0; i < wielkosc + 1; i++)
		{
			if (tablica[i][0] == tablicaKrawedzi[iter][1]) //je¿eli dopiero co dodana krawêdŸ koñczy siê w tym wierzcho³ku
			{
				for (int j = 0; j < wielkosc + 1; j++)
				{
					if (tablica[0][j] == tablicaKrawedzi[iter][0])
					{
						tablica[i][j] = -1;
					}
				}
			}
		}
		//blokowanie reszty cykli
		for (int i = 0; i < test->getwielkosc(); i++)
		{
			if (tablicaOznaczen[i] == tablicaKrawedzi[iter][0])
			{
				tablicaOznaczen[i] = tablicaOznaczen[tablicaKrawedzi[iter][1]]; // tablicaOznaczen[tablicaKrawedzi[iter][1]] to jest sygnatura tego ci¹gu który nie ma byc cyklem
			}
		}
		

		for (int j = 0; j < wielkosc + 1; j++)
		{
			if (tablica[j][0] == tablicaOznaczen[tablicaKrawedzi[iter][1]])

			{
				for (int i = 0; i < wielkosc +1; i++)
				{
					if (tablicaOznaczen[tablica[0][i]] == tablica[j][0])
					{
						tablica[j][i] = -1;
					}
				}


			}
		}
		





		//tablica[kolumny][wiersze] = -1;




		//pomniejszona tablica
		int **nowaTablica2;
		nowaTablica2 = new int *[wielkosc];
		for (int i = 0; i < wiersze; i++)
		{
			nowaTablica2[i] = new int[wielkosc];
			for (int j = 0; j < kolumny; j++)
			{
				nowaTablica2[i][j] = tablica[i][j];
			}

			for (int j = kolumny +1; j < wielkosc+1; j++)
			{
				nowaTablica2[i][j - 1] = tablica[i][j];
			}

		}

		for (int i = wiersze +1; i < wielkosc+1; i++)
		{
			nowaTablica2[i-1] = new int[wielkosc];
			for (int j = 0; j < kolumny; j++)
			{
				nowaTablica2[i-1][j] = tablica[i][j];;
			}

			for (int j = kolumny +1; j < wielkosc+1; j++)
			{
				nowaTablica2[i-1][j - 1] = tablica[i][j];
			}

		}

		
		iter++;
		if(wartosc<test->getVaule())
			Branch(nowaTablica2, tablicaKrawedzi, wielkosc - 1, iter, test, wartosc,tablicaOznaczen);

	


		wartosc += max;

		if (wartosc < test->getVaule())
		{
			iter--;
			

			int min = -1;
			//odejmujemy pionowo
			for (int w = 0; w < wielkosc; w++)
			{
				if (tablicaKopia[w + 1][kolumny] != -1 && w+1 != wiersze)
				{
					if (min == -1)
					{
						min = tablicaKopia[w + 1][kolumny];
					}
					if (min > tablicaKopia[w + 1][kolumny])
					{
						min = tablicaKopia[w + 1][kolumny];
					}
				}
			}
			for (int w = 0; w < wielkosc; w++)
			{
				if (tablicaKopia[w + 1][kolumny] != -1 && w+1 != wiersze)
				{
					tablicaKopia[w + 1][kolumny] -= min;
				}
			}

			//odejmujemy poziomo
			
			min = -1;
			for (int w = 0; w < wielkosc; w++)
			{
				if (tablicaKopia[wiersze][w + 1] != -1 && w + 1 != kolumny)
				{
					if (min == -1)
					{
						min = tablicaKopia[wiersze][w + 1];
					}
					if (min > tablicaKopia[wiersze][w + 1])
					{
						min = tablicaKopia[wiersze][w + 1];
					}
				}
			}
			for (int w = 0; w < wielkosc; w++)
			{
				if (tablicaKopia[wiersze][w + 1] != -1 && w + 1 != kolumny)
				{
					tablicaKopia[wiersze][w + 1] -= min;
				}
			}

















			






			tablicaKopia[wiersze][kolumny] = -1;
			

			Branch(tablicaKopia, tablicaKrawedzi, wielkosc , iter, test, wartosc,tablicaOznaczenKopia);
		}

		//USUWANIE TABLIC

		for (int i = 0; i < wielkosc + 1; i++)
			delete[] tablica[i];
		delete[] tablica;



		for (int i = 0; i < wielkosc + 1; i++)
			delete[] tablicaKopia[i];
		delete[] tablicaKopia;

		delete[] tablicaOznaczenKopia;

		for (int i = 0; i < wielkosc; i++)
			delete[] nowaTablica2[i];
		delete[] nowaTablica2;

		for (int i = 0; i < wielkosc; i++)
			delete[] tablicawartosci[i];
		delete[] tablicawartosci;



	}



}




Macierzkosztu::Macierzkosztu(int wielkosc)
{
	this->wielkosc = wielkosc;
	this->minvalue = -1;
	this->tablicaKrawedzi = new int[wielkosc + 1];
	this->tab = new int *[wielkosc];
	for (int i = 0; i < wielkosc ; i++)
	{
		this->tab[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
			this->tab[i][j] = 0;

	}

}

Macierzkosztu::~Macierzkosztu()
{
	for (int i = 0; i <wielkosc; i++)
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
		cout << setw(3)<< k << " ";
	}
	cout << endl;

	for (int w = 0; w < wielkosc; w++)
	{
		cout << w << " ";
		for (int k = 0; k < wielkosc; k++)
		{
			cout << setw(3)<<tab[w][k]<<" ";
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
	
}

void Macierzkosztu::bruteForce()
{
	this->minvalue = INT_MAX;
	int wielkosc = this->wielkosc;
	int *tab;
	tab = new int[wielkosc - 1];

	for (int i = 0; i < wielkosc-1; i++)
	{
		tab[i] = i + 1;
	}
	permute(tab,0,wielkosc-2,this);


	

}

int ** Macierzkosztu::getTab()
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

void Macierzkosztu::wczytajzPliku()
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

	int wielkosc;
	

	handler >> wielkosc;
	int **tablica;
	int a;
	tablica = new int *[wielkosc];
	
	for (int i = 0; i < wielkosc;i++)
	{
		tablica[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			handler >> a;
			tablica[i][j] = a;

			
		}
		
	}

	for (int i = 0; i < this->wielkosc; i++)
		delete[] this->tab[i]; //uwolnienie pamieci
	delete[] this->tab; //uwolnienie pamieci

	this->tab = tablica;
	this->wielkosc = wielkosc;


}

void Macierzkosztu::branchAndBound()
{
	int wielkosc = this->wielkosc;
	this->minvalue = INT_MAX;
	int temp = 0;
	//tablica do modyfikowania na potrzeby algorytmu
	int **tablica;
	tablica = new int *[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		tablica[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			tablica[i][j] = this->tab[i][j];
		}

	}

	//redukowanie macierzy

	//redukowanie wierszy
	for (int i = 0; i < wielkosc; i++)
	{
		//szukanie minimum w ka¿dym wierszu
		int min = -1;
		for (int j = 0; j < wielkosc; j++)
		{
			if (tablica[i][j] != -1)
			{
				if (min == -1)
				{
					min = tablica[i][j];
				}
				if (min > tablica[i][j])
				{
					min = tablica[i][j];
				}
			}
		}
		//redukowanie ka¿dego wiersza, jak min = 0, to nie trzeba
		if (min != 0)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				if (j != i)
				{
					tablica[i][j] -= min;
					
				}

			}
			temp += min;
		}
		
	}

	//redukowanie kolumn
	for (int i = 0; i < wielkosc; i++)
	{
		//szukanie minimum w ka¿dym wierszu
		int min = -1;
		for (int j = 0; j < wielkosc; j++)
		{
			if (j != i)
			{
				if (min == -1)
				{
					min = tablica[j][i];
				}
				if (min > tablica[j][i])
				{
					min = tablica[j][i];
				}
			}
		}
		//redukowanie ka¿dej kolumny, jak min = 0, to nie trzeba
		if (min != 0)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				if (j != i)
				{
					tablica[j][i] -= min;
				}
			}
			temp += min;
		}
	}
	
	//przypisywanie wartoœci do zer

	int **tablicawartosci; //przechowywanie wartoœci wzrostu LB dla danego 0
	tablicawartosci = new int *[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		tablicawartosci[i] = new int[wielkosc];
		for (int j = 0; j < wielkosc; j++)
		{
			tablicawartosci[i][j] = -1;
		}

	}

	for (int i = 0; i < wielkosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			if (tablica[i][j] == 0)
			{
				int min = -1;
				int suma = 0;
				//po wierszach
				for (int w = 0; w < wielkosc; w++)
				{
					if (w != j && w !=i ) 
					{
						if (min == -1)
						{
							min = tablica[w][j];
						}
						if (min > tablica[w][j])
						{
							min = tablica[w][j];
						}
					}
				}
				suma += min;
				//po kolumnach
				min = -1;
				for (int k = 0; k < wielkosc; k++)
				{
					if (k != i && k != j)
					{
						if (min == -1)
						{
							min = tablica[i][k];
						}
						if (min > tablica[i][k])
						{
							min = tablica[i][k];
						}
					}
				}

				suma += min;
				tablicawartosci[i][j] = suma;
			}
		}
	}
	
	
	//wyszukujemy 0 z najwiêksz¹ wartoœci¹
	int max = 0;
	//tablica przechowuj¹ca informacje o u¿ytych krawêdziach 
	int **tablicaKrawedzi;
	tablicaKrawedzi = new int *[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		tablicaKrawedzi[i] = new int[2];
	}
	for (int i = 0; i < wielkosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			if (max < tablicawartosci[i][j])
			{
				max = tablicawartosci[i][j];
				tablicaKrawedzi[0][0] = i;
				tablicaKrawedzi[0][1] = j;
			}
		}
	}

	//blokowanie mo¿liwoœci cyklu
	int tempvalue = tablica[tablicaKrawedzi[0][1]][tablicaKrawedzi[0][0]];
	tablica[tablicaKrawedzi[0][1]][tablicaKrawedzi[0][0]] = -1;
	

	//tablica do blokowania niedozwolonych krawêdzi
	int *tablicaOznaczen;
	tablicaOznaczen = new int[wielkosc];
	for (int i = 0; i < wielkosc; i++)
	{
		tablicaOznaczen[i] = i;
	}
	tablicaOznaczen[tablicaKrawedzi[0][0]] = tablicaOznaczen[tablicaKrawedzi[0][1]];


	//pomniejszona tablica, z indeksami na pierwszych pozycjach
	int **nowaTablica;
	nowaTablica = new int *[wielkosc];
	nowaTablica[0] = new int[wielkosc];
	for (int i = 1; i < tablicaKrawedzi[0][0]+1; i++)
	{
		nowaTablica[i] = new int[wielkosc];
		for (int j = 1; j < tablicaKrawedzi[0][1]+1; j++)
		{
			nowaTablica[i][j] = tablica[i-1][j-1];
		}

		for (int j = tablicaKrawedzi[0][1]+2; j <= wielkosc; j++)
		{
			nowaTablica[i][j-1] = tablica[i-1][j-1];
		}

	}
	
	for (int i = tablicaKrawedzi[0][0]+2; i <= wielkosc; i++)
	{
		nowaTablica[i-1] = new int[wielkosc ];
		for (int j = 1; j < tablicaKrawedzi[0][1]+1; j++)
		{
			nowaTablica[i - 1][j] = tablica[i-1][j-1];;
		}

		for (int j = tablicaKrawedzi[0][1] + 2; j <= wielkosc; j++)
		{
			nowaTablica[i-1][j-1] = tablica[i-1][j-1];
		}

	}

	//indeksy
	nowaTablica[0][0] = -1;
	int *tabpom;
	tabpom = new int[wielkosc];
	for (int i = 0; i < tablicaKrawedzi[0][0]; i++)
	{
		tabpom[i] = i;
	}
	for (int i = tablicaKrawedzi[0][0]; i < wielkosc; i++)
	{
		tabpom[i] = i+1;
	}
	for (int i = 1; i < wielkosc; i++)
	{
		nowaTablica[i][0] = tabpom[i-1];
	}
	for (int i = 0; i < tablicaKrawedzi[0][1]; i++)
	{
		tabpom[i] = i;
	}
	for (int i = tablicaKrawedzi[0][1]; i < wielkosc; i++)
	{
		tabpom[i] = i+1;
	}
	for (int i = 1; i < wielkosc; i++)
	{
		nowaTablica[0][i] = tabpom[i-1];
	}
	delete [] tabpom;

	int iter = 1;  //do okreslania glebokosci rekurencji


	Branch(nowaTablica, tablicaKrawedzi, wielkosc-1,iter,this,temp,tablicaOznaczen);
	//USUWANIE TABLIC 
	for (int i = 0; i < wielkosc ; i++)
		delete[] nowaTablica[i];
	delete[] nowaTablica;







	if (temp + max < this->minvalue)
	{
		iter--;
		int **tablicaKopia2;
		tablicaKopia2 = new int *[wielkosc+1];
		for (int i = 0; i < wielkosc+1; i++)
		{
			tablicaKopia2[i] = new int[wielkosc+1];
			
		}
		for (int i = 0; i < wielkosc; i++)
		{
			tablicaKopia2[0][i+1] = i;
			tablicaKopia2[i+1][0] = i;
		}
		tablicaKopia2[0][0] = -1;
		for (int i = 0; i < wielkosc; i++)
		{
			for (int j = 0; j < wielkosc; j++)
			{
				tablicaKopia2[i + 1][j + 1] = tablica[i][j];
			}
		}
		for (int i = 0; i < wielkosc; i++)
		{
			tablicaOznaczen[i] = i; //resetowanie tablicy oznaczeñ, bo nie wybraliœmy ¿adnej krawêdzi
		}
		tablicaKopia2[tablicaKrawedzi[0][0]+1][tablicaKrawedzi[0][1]+1] = -1;
		tablica[tablicaKrawedzi[0][1]][tablicaKrawedzi[0][0]] = tempvalue;
		Branch(tablicaKopia2, tablicaKrawedzi, wielkosc, iter, this, temp, tablicaOznaczen);



		//USUWANIE TABLIC  2

		for (int i = 0; i < wielkosc + 1; i++)
			delete[] tablicaKopia2[i];
		delete[] tablicaKopia2;
		
	
	}

	//USUWANIE TABLIC  3
	delete[] tablicaOznaczen;

	for (int i = 0; i < wielkosc; i++)
		delete[] tablicaKrawedzi[i];
	delete[] tablicaKrawedzi;

	for (int i = 0; i < wielkosc; i++)
		delete[] tablica[i];
	delete[] tablica;

	for (int i = 0; i < wielkosc; i++)
		delete[] tablicawartosci[i];
	delete[] tablicawartosci;


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
		cout << " - "<<tablicaKrawedzi[i] ;
	}
	cout << endl;
}
