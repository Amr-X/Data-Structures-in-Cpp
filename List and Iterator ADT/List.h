#pragma once

template <typename T>
// List Class
class list
{
protected:
	// Node
	struct node
	{
		T m_element;
		node* m_prev;
		node* m_next;

		node(T element = T(), node* prev = nullptr, node* next = nullptr)
			:m_element(element),m_prev(prev),m_next(next){}
	};

public:
	// Iterator For list
	class iterator
	{
		friend class list;
	private:
		node* m_pointer; // Pointer-based 
		iterator(node* nodePointer);
	public:
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		bool operator==(const iterator& rhs);
		bool operator!=(const iterator& rhs);
		iterator operator+(int increment);
		iterator operator-(int increment);
		T& operator*() const;
		// No destructor
	};
	class const_iterator : public iterator
	{
		// Ofc Friendship is not inherited
		friend class list;

		// can this work?
		// Yeah! It's fine.. Virtual function wouldn't be good since there is overhead
		// It's not that much of an overhead -- But iterators are used extensively

		// How STL do it? They Rewrite the same code .. I think...
	public:
		T& operator*() = delete;
		const T& operator*() const;
	};

	// Can Be Here reverse_iterator But it's just the same except how operator++ and operator-- are defined

protected:
	node* header;
	node* trailer;
	int m_size;
public:
	list();
	int size() const;
	iterator insert(iterator position, const T& element);
	iterator insertFront(const T& element);
	iterator insertBack(const T& element);
	iterator erase(iterator position);
	iterator eraseBack(const T& element);

	// created and copied to user -- not a reference
	iterator begin() const;
	iterator end() const;

	// Copy Constructor
	list(const list& rhs);
	// Copy Assignment
	list& operator=(const list& rhs);
	// Move Constructor
	list(list&& rhs) noexcept; // std::move now can use this - Exception Safe 
	
	// Destructor
	~list();
};


// class iterator implementation
template <typename T>
list<T>::iterator::iterator(node* nodePointer)
	:m_pointer(nodePointer){}
template <typename T>
int list<T>::size() const
{
	return m_size;
}


template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
	m_pointer = m_pointer->m_next;
	return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
	iterator it = *this; // Copy
	m_pointer = m_pointer->m_next; // Why not operator++; Answer : You Can! It's even better
	return it;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator--()
{
	m_pointer = m_pointer->m_prev;
	return *this;
}
template <typename T>
bool list<T>::iterator::operator==(const iterator& rhs)
{
	return rhs.m_pointer == m_pointer;
}
template <typename T>
bool list<T>::iterator::operator!=(const iterator& rhs)
{
	return rhs.m_pointer != m_pointer;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator+(int increment)
{
	// Create a copy of iterator that will return to caller
	iterator it = *this;

	for (int i = 0; i < increment; ++i)
	{
		++it; // or it.operator++();
	}
	return it;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator-(int increment)
{
	iterator it = *this;
	for (int i = 0; i < increment; ++i)
	{
		--it;
	}
	return it;

}

template <typename T>
T& list<T>::iterator::operator*() const
{
	// Dereference the pointer - can be invalid
	return m_pointer->m_element;
}

// const_iterator implementation
template <typename T>
const T& list<T>::const_iterator::operator*() const
{
	// Why it needs this->?

	return this->m_pointer->m_element;
}



// list class implementation
template <typename T>
list<T>::list()
{
	// what is the element here?
	header = new node();
	trailer = new node();
	header->m_next = trailer;
	trailer->m_prev = header;
	m_size = 0;
}
// What if insert(l.end()+1) ??
template <typename T>
typename list<T>::iterator list<T>::insert (iterator position, const T& element)
{
	// position is a copy no ref
	node* next = position.m_pointer;
	node* prev = next->m_prev;
	// New can throw std::bad_alloc if no memory
	node* newNode = new node(element, prev, next);
	next->m_prev = newNode;
	prev->m_next = newNode;
	m_size++;
	return iterator(newNode);
}

template<typename T>
inline typename list<T>::iterator list<T>::insertFront(const T& element)
{
	return insert(begin(), element);
}

template<typename T>
inline typename list<T>::iterator list<T>::insertBack(const T& element)
{
	return insert(end(), element);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator position)
{
	// Can't Delete The Sentinel Nodes
	if (position.m_pointer == header || position.m_pointer == trailer || m_size <= 0) return end(); 

	node* next = position.m_pointer->m_next;
	node* prev = position.m_pointer->m_prev;
	next->m_prev = prev;
	prev->m_next = next;

	delete position.m_pointer;
	m_size--;
	// Don't leave dangling pointers
	// Return one to next node
	return iterator(next); // or return end();
}

template <typename T>
typename list<T>::iterator list<T>::eraseBack(const T& element)
{
	return erase(end() - 1, element);
}


template <typename T>
typename list<T>::iterator list<T>::begin() const
{
	return iterator(header->m_next);
}
// Remember the Sentinel Nodes?
template <typename T>
typename list<T>::iterator list<T>::end() const
{
	return iterator(trailer);
}

template<typename T>
inline list<T>::list(const list& rhs)
{
	header = new node();
	trailer = new node();
	header->m_next = trailer;
	trailer->m_prev = header;

	// Will go from .begin to .end
	for (auto& element : rhs)
	{
		// Don't confuse this up with insertFront... We don't want the reserve of it
		insertBack(element);
	}
	// Count Every Element Being Added? Or just m_size = rhs.m_size; -- Oh, Insert Already Does That...
}

template<typename T>
inline list<T>& list<T>::operator=(const list& rhs)
{
	// This time a list already exist - So
	// Should I preserve the address of the original nodes? -- I think so
	// What about rhs elements Beyond m_size nodes? this* [5,10] - rhs [55,100,"20"]

	// Self-Assignment
	if (this == &rhs) return *this;

	iterator original_it = begin();
	const_iterator rhs_it = rhs.begin();

	while (original_it != end() && rhs_it != rhs.end())
	{
		*original_it = *rhs_it;
		++rhs_it; ++original_it;
	}
	// if there is more elements in rhs
	while (rhs_it != rhs.end())
	{
		insertBack(*rhs_it);
		++rhs_it;
	}
	// if there is more elements in original
	while (original_it != end())
	{
		// This is Tricky - erase will return a copy of the next element
		// So we will advance first - Post-increment
		iterator first = original_it++;
		erase(first);
	}
	return *this;
}

template<typename T>
inline list<T>::list(list&& rhs) noexcept
{
	// Move - Steal
	header = rhs.header; rhs.header = new node();
	trailer = rhs.trailer; rhs.trailer = new node();
	m_size = rhs.m_size; rhs.m_size = 0;

	// It was build on that premise
	rhs.header->m_next = rhs.trailer;
	rhs.trailer->m_prev = rhs.header;


}

template<typename T>
inline list<T>::~list()
{
	// Raw Pointers? or Iterator?
	// Well, I don't know .. but I fell raw pointers since the object is about to be destroyed


	// Node: header->prev = nullptr , trailer->next = nullptr
	// So this should work fine

	node* curr = header;
	node* temp = nullptr;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		delete temp;
	}
	
}

