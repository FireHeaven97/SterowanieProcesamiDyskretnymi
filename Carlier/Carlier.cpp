#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <conio.h>
#define duzo 100000

using namespace std;

struct zadanie
{
	int ri; //termin dostepnosci zadania i
	int pi;//czas wykonania zadania i
	int qi;//czas dostarczenia zadania i
	int n;//liczba zadan
};

class Program
{
	vector<zadanie> zadania;
	vector<int> permutacja;
	vector<int> cZad;
	int a = -1, b = -1, c = -1; //deklaracja zmiennych a,b z bloku, oraz c zadanie referencyjne

	//Porownywanie zadan wg termin dostepnosci rosnaco
	struct porownaj_Rmin
	{
		bool operator()(const zadanie& a, const zadanie& b)
		{
			if (a.ri>b.ri)
				return true;
			else
				return false;
		}
	};

	//Porownywanie wg czasu dostarczania, malejaco
	struct porownaj_Qmax
	{
		bool operator()(const zadanie& a, const zadanie& b)
		{
			if (a.qi<b.qi)
				return true;
			else
				return false;
		}
	};

public:
	//wczytywanie danych
	void wczytajDane(vector<zadanie> kopiowaneDane)
	{
		zadania = kopiowaneDane;
	}

	void wczytajDane()
	{
		int n;
		fstream plik_odczyt;
		plik_odczyt.open("dane.txt", ios::in);
		zadanie tymczasowe;      //obiekt tymczasowy sluzy do przepisania danych d wektora
		plik_odczyt >> n;    //odczytuje z pliki pierwsza linijke - liczbe zadan

		for (int i = 0; i < n; i++)
		{
			tymczasowe.n = i;                    //przypisanie numeru zadania
			plik_odczyt >> tymczasowe.ri;        //wczytanie r
			plik_odczyt >> tymczasowe.pi;            //wczytanie p
			plik_odczyt >> tymczasowe.qi;            //wczytanie q --- drugie zad
			zadania.push_back(tymczasowe);                    //przypisanie calego obiektu na koniec kolejki priorytetowej.
		}
		plik_odczyt.close();
	}



	int schrage()
	{
		int t = 0;
		int Cmax = 0;
		zadanie e;

		priority_queue <zadanie, vector<zadanie>, porownaj_Rmin> nieuszeregowane; //kolejka zadan nieuszeregowanych
		priority_queue <zadanie, vector<zadanie>, porownaj_Qmax> gotowe; //kolejka zadan gotowych do wykonania

		for (int i = 0; i < zadania.size(); i++) {
			nieuszeregowane.push(zadania[i]);
		}
		while (!(gotowe.empty()) || !(nieuszeregowane.empty())) { //jesli obydwie kolejki nie sa puste
			while (!(nieuszeregowane.empty()) && (nieuszeregowane.top().ri <= t)) {
				e = nieuszeregowane.top();
				gotowe.push(e);
				nieuszeregowane.pop();
			}
			if (gotowe.empty()) {
				t = nieuszeregowane.top().ri;
			}
			else {
				e = gotowe.top();
				gotowe.pop();
				permutacja.push_back(e.n);
				t = t + e.pi;
				Cmax = max(Cmax, t + e.qi);
				cZad.push_back(t);
			}
		}
		return Cmax; //zwraca najwieksza wartosc ze zbioru
	}



	int schrageZpodzialem() //wykorzystanie algorytmu schrage z podzialem
	{
		zadanie obecne;
		obecne.qi = duzo;
		int t = 0; //
		int Cmax = 0;
		zadanie e;

		priority_queue <zadanie, vector<zadanie>, porownaj_Rmin> nieuszeregowane;
		priority_queue <zadanie, vector<zadanie>, porownaj_Qmax> gotowe;

		for (int i = 0; i < zadania.size(); i++) {
			nieuszeregowane.push(zadania[i]);
		}
		while (!(gotowe.empty()) || !(nieuszeregowane.empty())) {
			while (!(nieuszeregowane.empty()) && (nieuszeregowane.top().ri <= t))
			{
				e = nieuszeregowane.top();
				gotowe.push(e);
				nieuszeregowane.pop();
				if (e.qi > obecne.qi) {
					obecne.pi = t - e.ri;
					t = e.ri;
					if (obecne.pi > 0) {
						gotowe.push(obecne);
					}
				}
			}
			if (gotowe.empty()) {
				t = nieuszeregowane.top().ri;
			}
			else {
				e = gotowe.top();
				gotowe.pop();
				obecne = e;
				t = t + e.pi;
				Cmax = max(Cmax, t + e.qi);
			}
		}
		return Cmax;
	}

	// Wyznaczanie a, b, c
	void wyznaczABC(int C_max)
	{
		int n = zadania.size();

		// Wyznaczanie b
		for (int j = 0; j < n; j++)
		{
			if (C_max == cZad[j] + zadania[permutacja[j]].qi)//
			{
				b = j;
			}
		}

		if (b == -1)
		{
			cout << "blad na b!" << endl;
		}

		// Wyznaczanie a
		for (int j = 0; j < n; j++)
		{
			int suma = 0;
			for (int s = j; s <= b; s++)
			{
				suma += zadania[permutacja[s]].pi;
			}

			if (C_max == zadania[permutacja[j]].ri + suma + zadania[permutacja[b]].qi)
			{
				a = j;
				break;
			}
		}
		if (a == -1)
			cout << "blad na a!" << endl;

		// Wyznaczanie c
		for (int j = a; j <= b; j++)
		{
			if (zadania[permutacja[j]].qi < zadania[permutacja[b]].qi)
			{
				c = j;
			}
		}
	}

	int znajdzNajmniejszeR()
	{
		int minR = duzo;
		for (int j = c + 1; j <= b; j++)
		{
			if (zadania[permutacja[j]].ri < minR)
				minR = zadania[permutacja[j]].ri;
		}
		return minR;
	}

	int znajdzNajmniejszeQ()
	{
		int minQ = duzo;
		for (int j = c + 1; j <= b; j++)
		{
			if (zadania[permutacja[j]].qi < minQ)
				minQ = zadania[permutacja[j]].qi;
		}
		return minQ;
	}

	// Suma wszystkich p
	int znajdzPPrim()
	{
		int p = 0;
		for (int j = c + 1; j <= b; j++)
		{
			p += zadania[permutacja[j]].pi;//termin dostepnosci zadania referencyjnego
		}
		return p;
	}



	int wykonajCarlier(int UB = duzo)
	{
		int U, LB, C_max = 0;
		int rprim, qprim, pprim;
		int rpic, qpic;
		//wyznaczenie permutacji wykonywaia zadan algorytmem schrage
		U = schrage();                                     
	    //uaktualniane jest najlepsze do tej pory znalezione rozwiazanie
	
		if (U < UB)     //UB gorne oszacowanie wartosci, U wartosc funkcji celu                                     
		{
			UB = U;
		}
		// wyznaczenie bloku AB
		wyznaczABC(U);                                     

		if (c == -1)   //jesli c nie istnieje                       
		{
			cout << "Cmax = " << UB << endl;
			getchar();
			//Jezeli tego typu zadanie nie stnieje alg shrage wygenerowal rozwiazanie optymalne i nastepuje powrot do procedury
			return UB;
		}
	
		rprim = znajdzNajmniejszeR(); //najmniejsza wartosc ze zbior R
		qprim = znajdzNajmniejszeQ(); //najniejsza wartosc ze zbior Q
		pprim = znajdzPPrim();  //suma wszystkich P od permutacji

		rpic = zadania[permutacja[c]].ri;   //zapamietujemy r Pi C
		//Modyfikujemy termin dostepnosci zadania referencyjnego( wymuszane jest aby zadanie referencyjne bylo wykonywane za wszystkimi
		//zadaniami na tych pozycjach nastepnie wyznaczane jest dolne ograniczenie dla wszystkich permutacji spelniajacych to wymaganie
		zadania[permutacja[c]].ri = max(zadania[permutacja[c]].ri, rprim + pprim);	
	//wyznaczanie najmniejszy z terminow dostepnosci oraz najwiekszy z terminow dostarczenia zadan stojacych na pozycjach od
	//c+1 do b dodatkowo wyzaczana jest suma czasow wykonywania zadan
		LB = schrageZpodzialem();                          
	//Wywolanie rekurencyjne nowego problemu
		if (LB < UB)                                   
		{
			Program nowyProgram;
			nowyProgram.wczytajDane(zadania);
			C_max = nowyProgram.wykonajCarlier(UB);
		}
		//Po powrocie odtwarzamy termin dostepnosci rozwiazania referencyjnego
		zadania[permutacja[c]].ri = rpic;    

		qpic = zadania[permutacja[c]].qi;
		//wykonywane sa analogiczne czynnosci przy czym modyfikowany jest termin dostarczenia zadania
		//referencyjnego( wymuszone jest aby zadanie referencyjne wykonywane bylo przed wszystkimi zadaniami na pozycjach od c+1 do b)
		zadania[permutacja[c]].qi = max(zadania[permutacja[c]].qi, qprim + pprim);

		LB = schrageZpodzialem();                           
		if (LB < UB)                                                   
		{
			Program nowyProgram;
			nowyProgram.wczytajDane(zadania);
			C_max = nowyProgram.wykonajCarlier(UB);
		}

		zadania[permutacja[c]].qi = qpic;      

		return C_max;
	}


};


int main()
{
	Program program;
	program.wczytajDane();
	cout << "Cmax = " << program.wykonajCarlier() << endl;
	getchar();


}
/*
z³o¿onoœæ obliczeniowa:
- n! (wyk³adnicza)

dwa ciêcia:
- gdy nie ma c
- gdy LB >= UB */
