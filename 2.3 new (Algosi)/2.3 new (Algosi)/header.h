#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct offer
{
	int cost;
	int store;
	int amount;

	bool operator<(const offer& other) const {
		return cost < other.cost;
	}

};

template <typename T>
class PriorityQueue
{
private:
	vector<T> heap; // vector as a base for heap
	void GoUp(int index)
	{
		while (index > 0)
		{
			int parentNode = (index - 1) / 2;
			if (heap[index] < heap[parentNode])
			{
				swap(heap[index], heap[parentNode]);
				index = parentNode;
			}
			else
				break;
		}
	}

	void GoDown(int index)
	{
		int size = heap.size();
		while (index < size)
		{
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int smallest = index;

			if (left < size && heap[left] < heap[smallest])
				smallest = left;
			if (right < size && heap[right] < heap[smallest])
				smallest = right;

			if (smallest != index)
			{
				swap(heap[smallest], heap[index]);
				index = smallest;
			}
			else
				break;
		}
	}
public:
	void push(T value)
	{
		heap.push_back(value);
		GoUp(heap.size() - 1);
	}

	T top()
	{
		return heap[0];
	}

	void pop()
	{
		heap[0] = heap.back(); //now last element is first element
		heap.pop_back(); //delete last element
		GoDown(0);
	}

};

void ExtractFromFile(fstream& datafile, int n, int* a, int* b)
{
	for (int i = 0; i < n; i++)
	{
		datafile >> a[i];
		datafile >> b[i];
	}
}

int Calculate(int n, int k, int* a, int* b)
{
	PriorityQueue<offer> price;
	int totalPrice = 0;
	for (int i = 0; i < n; i++) //fill queue with 0 sold products
		price.push({ a[i], i, 0 });

	for (int i = 0; i < k; i++)
	{
		offer current = price.top();
		price.pop();

		totalPrice += current.cost;
		current.amount++;
		current.cost +=  current.amount * b[current.store];

		price.push(current);
	}

	return totalPrice;
}

