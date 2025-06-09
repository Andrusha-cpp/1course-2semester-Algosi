#include "header.h"

int main() {
	fstream datafile("data.txt");
	int* h = new int;
	int* m = new int;
	int* n = new int;
	Objects* info = nullptr;
	ExtractFromFile(datafile, h, m, n, &info);

	Dictionary<int, int> hash_spreadsheet;
	int collisions = AddToHash(info, hash_spreadsheet, *h, *m, *n);
	cout << collisions << endl;

	delete h;
	delete m;
	delete n;
	delete[] info;
	datafile.close();
}