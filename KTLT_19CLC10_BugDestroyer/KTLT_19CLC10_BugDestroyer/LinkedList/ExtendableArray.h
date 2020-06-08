#ifndef _EXTEND_ARRAY_H
#define _EXTEND_ARRAY_H
#include <stdexcept>
template<class T>
class ExtendableArray
{
private:
	T* item;
	size_t size;
public:
	ExtendableArray(size_t size) 
	{ 
		this->size = size;
		this->item = new T[this->size];
	}
	ExtendableArray() 
	{ 
	}

	size_t getSize()
	{
		return this->size;
	}
	void fill(T value)
	{
		if (size == 0)
		{
			throw std::out_of_range("Array is Empty");
		}
		for (int i = 0; i < size; i++)
		{
			item[i] = value;
		}
	}
	void push_back(T value)
	{
		T* tmp = new T[size + 1];
		for (int i = 0; i < this->size; i++)
		{
			tmp[i] = item[i];
		}
		tmp[size] = value;
		delete[] item;
		item = tmp;
		size++;
	}

	void pop()
	{
		if (size == 0)
		{
			throw std::out_of_range("Array is Empty");
		}
		T* tmp = new T[--size];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = item[i];
		}
		delete[]item;
		item = tmp;
	}


	T at(size_t Pos)
	{
		if (Pos >= size)
		{
			throw std::out_of_range("Array out of range");
		}
		return item[Pos];
	}
	void set(size_t Pos, T value)
	{
		if (Pos >= size)
		{
			throw std::out_of_range("Array out of range");
		}
		item[Pos] = value;
	}
	~ExtendableArray()
	{
		delete[]item;
	}
};
#endif

