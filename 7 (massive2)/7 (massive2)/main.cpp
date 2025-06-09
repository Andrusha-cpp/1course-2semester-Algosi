#include <iostream>

using namespace std;

void Input(int*, int);
void Output(int*, int);
void MoveZeros(int*, int, int);
void FindZeros(int*, int);

int main() {
	int n = 10;
	int* array = new int[n];
	cout << "Enter the array: ";
	Input(array, n);
	FindZeros(array, n);
	Output(array, n);
	cout << n;
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

//сдвиг найденого нуля в конец
void MoveZeros(int* array, int n, int k)
{
	for (int i = k; i < n - 1; i++)
		swap(array[i], array[i++]);
}

//нахождение нулей
void FindZeros(int* array, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (array[i] == 0)
		{
			MoveZeros(array, n, i);
			n--;
		}
	}
}