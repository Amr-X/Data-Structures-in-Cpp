#pragma once
#include <assert.h>
#include <stdexcept>
// External Linkage with this

template<typename T>
class vector {
public:
	// Declaring To know it's existence
	// Public To give user access to (Instantiating)
	class iterator;
private:
	int m_size;
	int m_capacity; // note -- number of elements
	T* m_array;

	void reserve(int n);
public:
	vector(int size);
	~vector();
	T& at(int i) const;
	T& operator[](int i) const;
	void set(int i, const T& value);
	void insert(int i, const T& value); 
	void erase(int i);

	// Iterator -- More Here
	iterator begin() const;
	iterator end() const;
};



template<typename T>
vector<T>::vector(int size)
	:m_size(size),m_capacity(0),m_array(new T[size])
{
}

template<typename T>
vector<T>::~vector()
{
	// Should this loop on every element and delete it?
	delete[] m_array;
}

template <typename T>
T& vector<T>::at(int i) const
{
	if (i >= m_size || i < 0) throw std::out_of_range("Index Invalid");
	return m_array[i];
}

template <typename T>
T& vector<T>::operator[](int i) const
{
	// No Bound Checking 
	return m_array[i];
}

template <typename T>
void vector<T>::set(int i, const T& value)
{
	if (i < 0 || i >= m_size) throw std::out_of_range("Index Invalid");
	m_array[i] = value;
}

template <typename T>
void vector<T>::reserve(int N)
{
	if (N <= m_size) return;


	T* newArray = new T[N]; // could fail -- newarray = NULL
	if (!newArray) { std::cout << "Memory Allocation Failed"; return; };

	for (int i = 0; i < m_capacity; ++i)
	{
		newArray[i] = m_array[i];
	}
	// Again -- Should this loop on every element and delete it?
	delete[] m_array;
	m_array = newArray;

	m_size = N;
}


template <typename T>
void vector<T>::insert(int i,const T& value) 
{
	if (i < 0 || i >= m_size) throw std::out_of_range("Index Invalid");
	// Just be careful here
	if (m_capacity >= m_size)
	{
		// Expandable -- Dynamic
		reserve(2 * m_size);
	};

	for (int j = m_capacity-1;j >= i;j--)
	{
		m_array[j + 1] = m_array[j];
	}

	m_array[i] = value;

	m_capacity++;
}
template <typename T>
void vector<T>::erase(int i)
{
	if (i < 0 || i >= m_size) throw std::out_of_range("Index Invalid");
	if (m_capacity == 0) return;

	for (int j = i+1; j < m_capacity; ++j)
	{
		m_array[j - 1] = m_array[j];
	}

	m_capacity--;
}
// Vector Iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() const
{
	return iterator(0);
}
template <typename T>
typename vector<T>::iterator vector<T>::end() const
{
	return iterator(m_size);
}

///////////////////////////////////////////////////////

// What if i want this to be private?
// Iterator Class

template<typename T>
class vector<T>::iterator
{
	// Pointer Based Iterator
private:
	T* m_pointer;
	// I don't think the user would need this -- He wants the copy/move constructor
	iterator(T* pointer);
public:
	// Dependent and Independent Members

	// Note : Any iterator can become invalid  
	iterator& operator++();
	iterator& operator--();
	bool operator==(const iterator& rhs) const;
	bool operator!=(const iterator& rhs) const;
	T& operator*() const;
	iterator operator+(int increment) const;
	iterator operator-(int increment) const;
	// copy / move
};

/// Iterator Class Implementation
template <typename T>
vector<T>::iterator::iterator(T* pointer)
	:m_pointer(pointer){}

// Why Typedef?
template <typename T>
vector<T>::iterator& vector<T>::iterator::operator++()
{
	// ++it -- Pointer arithmetic -- p + 1 * sizeof(datatype)
	++m_pointer; return *this;
}

template <typename T>
vector<T>::iterator& vector<T>::iterator::operator--()
{
	--m_pointer; return *this;
}

template<typename T>
inline bool vector<T>::iterator::operator==(const iterator& rhs) const
{
	return rhs.m_pointer == m_pointer;
}

template<typename T>
inline bool vector<T>::iterator::operator!=(const iterator& rhs) const
{
	return rhs.m_pointer == m_pointer;
}

template <typename T>
T& vector<T>::iterator::operator*() const
{

	return *m_pointer;
}

template <typename T>
 vector<T>::iterator vector<T>::iterator::operator+(int increment) const
{
	// How to do this in index-based Iterator?
	 return iterator(m_pointer + increment);
}

template <typename T>
 vector<T>::iterator vector<T>::iterator::operator-(int increment) const
{
	 return iterator(m_pointer - increment);
}





