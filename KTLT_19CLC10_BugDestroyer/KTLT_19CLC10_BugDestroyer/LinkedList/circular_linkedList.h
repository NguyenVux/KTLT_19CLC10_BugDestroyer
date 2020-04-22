#pragma once

template<typename T>
struct node
{
	T data;
	node<T>* next;
};

template<typename T>
class CircularLinkedList
{
public:
	node<T>* start = 0;
	node<T>* current = 0;
	void insert(T data)
	{
		if (start == 0)
		{
			start = new node<T>;
			start->next = start;
			start->data = data;
		}
		else
		{
			node<T>* tmp = new node<T>;
			tmp->next = start;
			tmp->data = data;
			current = start;
			while (current->next != start)
			{
				current = current->next;
			}
			current->next = tmp;
		}
	}
	~CircularLinkedList()
	{
		current = start;
		while (current->next != start)
		{
			start = current->next;
			delete current;
			current = start;
		}
		delete start;
		start = 0;
	}
};