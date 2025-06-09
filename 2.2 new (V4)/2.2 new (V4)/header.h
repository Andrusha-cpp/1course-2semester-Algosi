#pragma once
#include <iostream>
#include <typeinfo>
#include <fstream>

using namespace std;

struct Objects
{
	char operation;
	int id;
	int hash;
};

void ExtractFromFile(fstream&, int*, int*, int*, Objects**);

template <typename K, typename V>
class Dictionary
{
private:
	struct Node
	{
		K key;
		V value;
		bool existance;
	};
	Node* data;
	int amount_of_nodes; //amount of nodes of dictionary (filled and unfilled)
	int amount_of_data; //amount of filled nodes
public:
	Dictionary();
	Dictionary(int);
	Dictionary(Dictionary&);
	Dictionary operator= (Dictionary&);
	Dictionary(Dictionary&&) noexcept;
	Dictionary operator= (Dictionary&&) noexcept;
	~Dictionary();

    int size();
	//add element on exect key
	void add(V, K);
	void del(V);
	V getValue(K);
	bool keyCheck(K);
};

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	data = nullptr;
	amount_of_nodes = 0;
	amount_of_data = 0;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(int amount)
{
	data = new Node[amount];
	amount_of_nodes = amount;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(Dictionary& copied)
{
	this->amount_of_nodes = copied.amount_of_nodes;
	this->data = new Node[amount_of_nodes];
	for (int i = 0; i < amount_of_nodes; i++)
		this->data[i] = copied.data[i];
}

template <typename K, typename V>
Dictionary<K, V> Dictionary<K, V>::operator=(Dictionary& copied)
{
	if (this != &copied) { //check on equality
		delete[] this->data; // clear old data

		this->amount_of_nodes = copied.amount_of_nodes;
		this->data = new Node[amount_of_nodes];
		for (int i = 0; i < amount_of_nodes; i++) {
			this->data[i] = copied.data[i];
		}
	}
	return *this;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary(Dictionary&& transfered) noexcept
{
	this->data = transfered.data;
	this->amount_of_nodes = transfered.amount_of_nodes;
	transfered.data = nullptr;
	transfered.amount_of_nodes = 0;
}

template <typename K, typename V>
Dictionary<K, V> Dictionary<K, V>::operator=(Dictionary&& transfered) noexcept
{
	if (this != &transfered) { // check on equality
		delete[] this->data; //clear old data

		this->data = transfered.data;
		this->amount_of_nodes = transfered.amount_of_nodes;

		transfered.data = nullptr;
		transfered.amount_of_nodes = 0;
	}
	return *this;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
	delete[] data;
}

////////////////////////////////////////////////////////////////////////

//return amount of filled nodes
template <typename K, typename V>
int Dictionary<K, V>::size()
{
	return amount_of_data;
}

template <typename K, typename V>
void Dictionary<K, V>::add(V add_value, K add_key)
{
	if (add_key >= amount_of_nodes)
	{
		Node* new_data = new Node[add_key + 1];

		for (int i = 0; i < amount_of_nodes; i++)
				new_data[i] = data[i];

		for (int i = amount_of_nodes; i < add_key + 1; i++)
			new_data[i].existance = false;

		delete[] data;
		data = new_data;
		amount_of_nodes = add_key + 1;
	}
	data[add_key].existance = true;
	data[add_key].key = add_key;
	data[add_key].value = add_value;
	amount_of_data++;
}

//delete element by it's key
template <typename K, typename V>
void Dictionary<K, V>::del(V del_value)
{
	for (int i = 0; i < amount_of_nodes; i++)
	{
		if (data[i].value == del_value)
		{
			data[i].existance = false;
			amount_of_data--;
			break;
		}
	}
}

//return value by it's key 
template <typename K, typename V>
V Dictionary<K, V>::getValue(K get_key)
{
	if (get_key >= amount_of_nodes)
		return false;
	else
		return data[get_key].value;
}

//return key existance 
template <typename K, typename V>
bool Dictionary<K, V>::keyCheck(K get_key)
{
	if (get_key >= amount_of_nodes)
		return false;
	else
		return data[get_key].existance;
}

template <typename K, typename V>
int AddToHash(Objects* info, Dictionary<K, V>& hash_spreadsheet, int h, int m, int n)
{
	int amount_of_collisions = 0;
	for (int i = 0; i < n; i++)
	{
		if (info[i].operation == '+')
		{
			if (!hash_spreadsheet.keyCheck(info[i].hash)) //check on existance in hash
				hash_spreadsheet.add(info[i].id, info[i].hash);
			else
			{
				for (int j = 1;; j++)
				{
					int index = (info[i].hash + j * m) % h;
					if (!hash_spreadsheet.keyCheck(index))
					{
						hash_spreadsheet.add(info[i].id, index);
						amount_of_collisions += j;
						break;
					}
				}
			}
		}
		else
			hash_spreadsheet.del(info[i].id);
	}
	return amount_of_collisions;
}

