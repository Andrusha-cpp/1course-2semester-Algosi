#include "header.h"

void ExtractFromFile(fstream& datafile, int* h, int* m, int* n, Objects** data)
{
	datafile >> *h;
	datafile >> *m;
	datafile >> *n;
	*data = new Objects[*n];
	for (int i = 0; i < *n; i++)
	{
		datafile >> (*data)[i].operation;
		datafile >> (*data)[i].id;
		datafile >> (*data)[i].hash;
	}
}