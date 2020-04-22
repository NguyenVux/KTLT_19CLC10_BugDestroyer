template<class T>
struct node
{
	T data;
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
	void insert(T data)
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
	}
	void insertTop(T data)
	{
		node<T>* tmp = new node<T>;
		tmp->data = data;
		tmp->next = head;
		head = tmp;
	}
	~linkedList()
	{
		current = head;
		while (current != 0)
		{
			head = head->next;
			delete current;
			current = head;
		}
	}
};
