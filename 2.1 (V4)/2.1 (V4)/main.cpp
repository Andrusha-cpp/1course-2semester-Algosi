#include <iostream>
#include <fstream>

using namespace std;

void OutputMatrix(int**, int);
void ExtractFromFile(fstream& datafile, int** matrix, int* reagents, int matters_amount, int add_matters);
void Mixing(int** matrix, int* reagents, int add_matters);

int main() {
	ofstream result("example.txt", ios::trunc); //delete information in result file
	result.close();

	fstream datafile("test.txt");
	int matters_amount; 
	int reagents_amount;

	datafile >> matters_amount;
	cout << matters_amount << " ";
	datafile >> reagents_amount;
	cout << reagents_amount << " ";
	cout << endl;

	int** matrix = new int* [matters_amount];
	for (int i = 0; i < matters_amount; i++)
		matrix[i] = new int[matters_amount];
	int* reagents = new int[reagents_amount];

	ExtractFromFile(datafile, matrix, reagents, matters_amount, reagents_amount);
	OutputMatrix(matrix, matters_amount);

	for (int i = 0; i < reagents_amount; i++)
		cout << reagents[i] << " ";
	cout << endl;

	Mixing(matrix, reagents, reagents_amount);

	datafile.close();
	for (int i = 0; i < matters_amount; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] reagents;
}

//extract matrix of reagents and list of reagents
void ExtractFromFile(fstream& datafile, int** matrix, int* reagents, int matters_amount, int reagents_amount)
{
	for (int i = 0; i < matters_amount; i++)
		for (int j = 0; j < matters_amount; j++)
			datafile >> matrix[i][j];
	for (int i = 0; i < reagents_amount; i++)
		datafile >> reagents[i];
}

void OutputMatrix(int** matrix, int matters_amount)
{
	for (int i = 0; i < matters_amount; i++)
	{
		for (int j = 0; j < matters_amount; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
}

//find result of reaction and input in result file
void Mixing(int** matrix, int* reagents, int reagents_amount)
{
	fstream resultfile("result.txt");
	if (resultfile)
		cout << "ok" << endl;
	int index = 1;
	int first = reagents[0] - 1;//translate from number of reagent to it's index
	int second = reagents[1] - 1;
	int exception = 0; // show how many reactions don't go
	int k = 0;
	while (true)
	{
		for (int i = 1; i < reagents_amount; i++)
		{
			if (matrix[second][first] != 0) //if reaction goes
			{
				reagents[k] = matrix[second][first];
				first = matrix[second][first] - 1;
				second = reagents[index++] - 1;
			}
			else
			{
				exception++;
				k++;
				first = second;
				second = reagents[index++] - 1;
			}
		}
		if (exception == 0) // check on amount of exceptions
		{
			reagents_amount = 1;
			break;
		}
		else if (exception == reagents_amount - 1)
			break;
		else
		{
			reagents_amount = exception + 1;
		}
	}
	for (int i = 0; i < reagents_amount; i++)
	{
		resultfile << reagents[i] << " ";
	}
	resultfile.close();
}

//  |          |
//  |__________|
//  |    3     |
//  |__________|
//  |    2     |
//  |__________|
//  |    1     |
//  |__________|