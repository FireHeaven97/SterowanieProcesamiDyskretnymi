#include <iostream>
#include <vector>
using namespace std;

struct Job
{
	Job(int P, int W, int D): P(P), W(W), D(D)
	{};
	int P;//dlugosc realizacji
	int W;//kara
	int D;//wymagany czas dostarczenia
};

int punishment(Job a, int fin)//wylicza wartosc kary dla pracy i jej czasu zakonczenia
{
	int pun = (fin - a.D) * a.W;
	if (pun > 0)
		return pun;
	else
	return 0;
}

int witi(const vector<Job> &job)
{
	unsigned long long U = 1;
	int num_of_combinations = (U << job.size()); //ilośc kombinacji dla n elementów (2^n)

	int * combinations = new int[num_of_combinations]; //tablica kar dla kolejnych kombinacji
	combinations[0] = 0;

	for (int i = 1; i < num_of_combinations; i++) //dla każdej kombinacji po kolei
	{
		int fin = 0; //czas zakonczenia
		combinations[i] = 9999999; //duża wartość

		// wyliczanie cmax dla danej kombinacji
		for (unsigned int j = 0; j < job.size(); j++)
			if (i & (1 << j)) //jeśli zadanie j nalezy do kombinacji i
				fin += job[j].P; //dodaj je

		for (unsigned int j = 0; j < job.size(); j++) //liczenie kary
			if (i & (1 << j)) //jeśli zadanie j nalezy do kombinacji i
			{
				int tmp = combinations[i & (~(1 << j))] + punishment(job[j], fin); //kobminacja bez j + zadanie j jako ostatnie
				if (combinations[i] > tmp) //jak najmniejsze to zapamiętaj
					combinations[i] = tmp;
			}
	}

	return combinations[num_of_combinations - 1];
}

int main()
{
	//pobieranie danych z pliku jak zawsze
		int n;
		vector<Job> job;
		cin >> n;
		while(n--)
		{
			int a, b, c;
			cin >> a;
			cin >> b;
			cin >> c;
			job.push_back(Job(a, b, c));
		}

		cout << "wyliczony:  " << witi(job) << endl;

	return 0;
}
