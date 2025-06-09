#include "header.h"

int main(){
	fstream datafile("data.txt");
	ofstream result("result.txt");

	int n, k; //amount of stores and amount of products that we need to buy
	int* a;
	int* b; //price and rise of price
	datafile >> n;
	datafile >> k;

	a = new int[n];
	b = new int[n];
	ExtractFromFile(datafile, n, a, b);

	int totalPrice = Calculate(k, n, a, b);
	cout << totalPrice << endl;

	datafile.close();
	result.close();
}