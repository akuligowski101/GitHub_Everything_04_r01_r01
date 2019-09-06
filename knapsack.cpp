#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <stdlib.h>
#include <iomanip>

using namespace std;
struct item {
	int weight;
	int value;
	float ratio;
	item(int x, int y)
	{
		weight = x;
		value = y;
		ratio = float(y) / float(x);
	}
};
struct sortweight {
	bool operator () (const item& x, const item& y) {
		return x.weight > y.weight;
	}
};
struct sortratio {
	bool operator () (const item& x, const item& y) {
		return x.ratio < y.ratio;
	}
};

priority_queue<item, vector<item>, sortratio> loot;
priority_queue<item, vector<item>, sortweight> lootweight;

struct backpack {
	int space;
	int value;
	int cap;
	vector<item> loot;
	backpack(int x)
	{
		cap = x;
		space = x;
		value = 0;
	}
};

void showAllItems(priority_queue<item, vector<item>, sortweight> lootweigth)
{
	cout << "Waga\tWartosc\tiloraz\t" << endl;
	while (!lootweigth.empty())
	{
		cout << lootweigth.top().weight << "\t";
		cout << lootweigth.top().value << "\t";
		cout << lootweigth.top().ratio << endl;
		lootweigth.pop();
	}
}

void greedy(backpack &plecak, priority_queue<item, vector<item>, sortratio> loot)
{
	cout << endl;
	cout << "ALGORYTM ZACHLANNY " << endl;
	cout << "Ilosc przedmiotow: " << loot.size();

	int m = loot.top().weight;
	while (!loot.empty())
	{
		if (plecak.space >= m)
		{
			plecak.loot.push_back(loot.top());
			plecak.value += loot.top().value;
			plecak.space -= m;
			loot.pop();
			m = loot.top().weight;
		}
		else
		{
			loot.pop();
			m = loot.top().weight;
		}
	}

	int wartosccalk = 0;
	int wagacalk = 0;
	cout << " Wykorzystane przedmioty: " << plecak.loot.size() << endl << endl;
	cout << "Waga\tWartosc\tiloraz\t" << endl;
	for (vector<item>::iterator it = plecak.loot.begin(); it != plecak.loot.end(); ++it)
	{
		wagacalk += it[0].weight;
		wartosccalk += it[0].value;
		cout << (it[0].weight) << "\t" << it[0].value << "\t" << it[0].ratio << "\t";
		cout << endl;
	}
	cout << "------------------------" << endl;
	cout << wagacalk << "\t" << wartosccalk << "\t" << endl;

}


int max(int a, int b) { return (a > b) ? a : b; }

void dynamicKnapsack(int Capacity, int wt[], int val[], int itemnumber)
{
	float T[itemnumber + 1][Capacity + 1];
	for (int i = 0; i <= itemnumber; i++)
		for (int j = 0; j <= Capacity; j++)
		{
			if (i == 0)
				T[i][j] = 0;
			else if (wt[i - 1] > j)
				T[i][j] = T[i - 1][j];
			else
				T[i][j] = max(val[i - 1] + T[i - 1][j - wt[i - 1]], T[i - 1][j]);
		}

	vector<item> przedmioty;
	vector<item> useditems;

	while (!lootweight.empty())
	{
		przedmioty.push_back(lootweight.top());
		lootweight.pop();
	}


	int n = itemnumber;
	int C = Capacity;
	while (n > 0 && C != 0)           //Wyszukanie przedmiotow, ktore zostaly zapakowane do plecaka
	{
		while (T[n][C] == T[n - 1][C])
			n--;
		while (T[n][C] == T[n][C - 1])
			C--;
		item przedmiot = przedmioty[n - 1];
		useditems.push_back(przedmiot);
		n--;
		C = C - przedmiot.weight;
	}


	cout << endl;
	int wartosccalk = 0;
	int wagacalk = 0;

	cout << "PROGRAMOWANIE DYMANICZNE " << endl;
	cout << "Ilosc przedmiotow: " << przedmioty.size();
	cout << " Wykorzystane przedmioty: " << useditems.size() << endl << endl;
	cout << "Waga\tWartosc\tiloraz\t" << endl;
	for (vector<item>::iterator it = useditems.begin(); it != useditems.end(); ++it)
	{
		wagacalk += it[0].weight;
		wartosccalk += it[0].value;
		cout << (it[0].weight) << "\t" << it[0].value << "\t" << it[0].ratio << "\t";
		cout << endl;
	}
	cout << "------------------------" << endl;
	cout << wagacalk << "\t" << wartosccalk << "\t" << endl << endl;

}

void dynamic(backpack b, priority_queue<item, vector<item>, sortweight> lootweight)
{

	int wt[lootweight.size()];
	int val[lootweight.size()];
	int i = 0;
	int n = lootweight.size();
	while (!lootweight.empty())
	{
		wt[i] = lootweight.top().weight;
		val[i] = lootweight.top().value;
		i++;
		lootweight.pop();
	}
	dynamicKnapsack(b.cap, wt, val, n);
}


int main()
{

	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		item x(rand() % 20 + 1, rand() % 100 + 1);
		loot.push(x);
		lootweight.push(x);
	}

    backpack plecak(100);

/*
	loot.push( item( 1 , 1 ) );
	loot.push( item( 3 , 4 ) );
	loot.push( item( 4 , 5 ) );
	loot.push( item( 5 , 7 ) );
	lootweight.push( item( 1 , 1 ) );
	lootweight.push( item( 3 , 4 ) );
	lootweight.push( item( 4 , 5 ) );
	lootweight.push( item( 5 , 7 ) );
*/

	showAllItems(lootweight);
	greedy(plecak, loot);
	dynamic(plecak, lootweight);

	return 0;
}
