#pragma once
template<class T>
struct node
{
	T *data = 0;
	node* next = 0;
};

template<class T>
class linkedList
{
public:
	node<T>* head = 0;
	node<T>* current = 0;
	node<T>* tail = 0;
	//int lenght = 0;
	/*void insert(T data)
	{
		if (head == 0)
		{
			head = new node<T>;
			head->data = data;
		}
		else
		{
			current = head;
			while (current->next != 0)
			{
				current = current->next;
			}
			current->next = new node<T>;
			current->next->data = data;
		}
	}*/
	/*void insertTop(T data)
	{
		node<T>* tmp = new node<T>;
		tmp->data = data;
		tmp->next = head;
		head = tmp;
	}*/
	///<summary>Join List
	///<para>return the head node of joined list</para>
	///</summary>
	static node<T>* joinList(linkedList<T>* list1,linkedList<T> *list2)
	{
		node<T> *tmp1 = list1->head;
		node<T>* List1head = list1->head;
		while (tmp1->next != 0)
		{
			tmp1 = tmp1->next;
		}
		tmp1->next = list2->head;
		return List1head;
	}
	void insertTop(node<T> *data)
	{
		data->next = head;
		head = data;
	}
	bool isEmpty()
	{
		if (head)
		{
			return true;
		}
		return false;
	}
	~linkedList()
	{
		current = head;
		while (current != 0)
		{
			head = head->next;
			if (current->data != 0)
			{
				delete current->data;
			}			
			delete current;
			current = head;
		}
	}
};
