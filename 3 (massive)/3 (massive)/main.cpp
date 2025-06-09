#include <iostream>

using namespace std;

void Input(int*, int);
void Output(int*, int);
void displacement(int*, int, int);
int FindReplicates(int*, int);

int main() {
	int n = 10;
	int* array = new int[n];
	cout << "Enter the array: ";
	Input(array, n);

	n = FindReplicates(array, n);
	cout << n << endl;
	Output(array, n);
}

void Input(int* array, int n)
{
	for (int i = 0; i < n; i++)
		cin >> array[i];
}

void Output(int* array, int n)
{
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;
}

//удаление элемента и сдвиг остальных
void displacement(int* array, int n, int k)
{
	for (int i = k; i < n ; i++)
		array[i] = array[i + 1];
}

//нахождение повтор€ющихс€ чисел
int FindReplicates(int* array, int n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (array[i] == array[j])
			{
				displacement(array, n, j);
				n--;
			}
		}
		count++;
	}
	return count;
}
