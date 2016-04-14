// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete[] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;

	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand(time(NULL));
	vectorOfSlavs.push_back(slavs); // dodaję/tworze pierwszy element do wektora, nazwa tabicy to ADRES pierwszego jej elementu = &slavs[0]
	for (int i = 1; i < n; i++)
	{
		int x = rand() % vectorOfSlavs.size();
		vectorOfSlavs.insert(vectorOfSlavs.begin() + x, &slavs[i]); // miejsce, wartość
	}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector <Slav *>::iterator iter_vectorOfSlavs = vectorOfSlavs.begin();
	for (iter_vectorOfSlavs; iter_vectorOfSlavs != vectorOfSlavs.end(); iter_vectorOfSlavs++)
	{
		cout << (*iter_vectorOfSlavs)->description() << endl; // działam na wskaźnikach, stąd operator "->", a nie "."
	}

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektora do zbioru.
	for (int i = n - 1; i >= 0; i--) // idę od końca, gdyż pop_back usuwa ostatni element
	{
		setOfSlavs.insert(vectorOfSlavs[i]); //kopiuje ostatni element, insert wstawia to przed wskazywany element
		vectorOfSlavs.pop_back(); //usuwa ostatni element
	}

	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set <Slav *>::iterator iter_setOfSlavs = setOfSlavs.begin();

	while (iter_setOfSlavs != setOfSlavs.end())
	{
		mapOfSlavs[*iter_setOfSlavs] = *(iter_setOfSlavs = setOfSlavs.erase(iter_setOfSlavs)); // erase zwraca iterator wskazujący na pierwszy element za usuniętym elementem
		iter_setOfSlavs = setOfSlavs.erase(iter_setOfSlavs);
	}

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	map <Slav *, Slav *>::iterator iter_mapOfSlav = mapOfSlavs.begin();

	for (iter_mapOfSlav; iter_mapOfSlav != mapOfSlavs.end(); iter_mapOfSlav++)
	{
		int nr = 1;
		cout << "Para nr " << nr << ": " << (*(*iter_mapOfSlav).first).description() << " i " << (iter_mapOfSlav->second)->description() << endl;
		nr++;
	}

	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs; // kolejka
	stack <Slav *> stackOfSlavs; // stos

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for (int i = 0; i < n; i++)
	{
		queueOfSlavs.push(&slavs[i]); // umieszczam element na końcu kolejki
	}

	REPORT_ADAPTERS;

	printf("## stack\n");

	// Przenieś Słowian z kolejki do stosu.
	while (!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front()); // zwracam wartość 1szego elementu kolejki i dodaje ją na stos
		queueOfSlavs.pop(); //usuwam pierwszy istniejący element kolejki
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	while (!stackOfSlavs.empty())
	{
		cout << stackOfSlavs.top()->description() << endl; // zwracam wartosc szczytowego elementu na stosie
		stackOfSlavs.pop(); // zdejmuję istniejący element ze szczytu stosu
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());
}
// Zadanie na 5

void sortOfSex(Slav *slavs, int n)
{
	vector <Slav*> vectorMale;
	vector <Slav*> vectorFemale;
	map <sex, vector <Slav*>> mapOfSex;

	for (int i = 0; i < n; i++)
	{
		if (slavs[i].sexOfSlav() == female)
			vectorFemale.push_back(&slavs[i]);
		else
			vectorMale.push_back(&slavs[i]);
	}

	mapOfSex[female] = vectorFemale;
	mapOfSex[male] = vectorMale;
}
