//#pragma once
//
//template <typename T>
//class list
//{
//protected:
//	// Node
//	struct node
//	{
//		T m_element;
//		node* m_prev;
//		node* m_next;
//
//		node(T element,node* prev = nullptr,node* next = nullptr)
//			:m_element(element),m_prev(prev),m_next(next){}
//	};
//
//public:
//	// Iterator For list
//	class iterator
//	{
//	friend class list;
//	private:
//		node* m_pointer;
//		iterator(node* nodePointer);
//	public:
//		iterator& operator++();
//		iterator& operator--();
//		bool operator==(const iterator& rhs);
//		bool operator!=(const iterator& rhs);
//		iterator operator+(int increment);
//		iterator operator-(int increment);
//		T& operator*() const;
//	};
//
//	
//	//////
//
//protected:
//	node* header;
//	node* trailer;
//	int m_size;
//public:
//	list();
//	int size()const;
//	void insert(const iterator& position, const T& element);
//	void earse(const iterator& position);
//
//	// created and copied to user -- not a reference
//	iterator begin() const;
//	iterator end() const;
//
//
//};
//
//template <typename T>
//list<T>::iterator::iterator(node* nodePointer)
//	:m_pointer(nodePointer){}
//template <typename T>
//int list<T>::size() const
//{
//	return m_size;
//}
//
//
//template <typename T>
//typename list<T>::iterator& list<T>::iterator::operator++()
//{
//	m_pointer = m_pointer->m_next;
//	return *this;
//}
//
//template <typename T>
//typename list<T>::iterator& list<T>::iterator::operator--()
//{
//	m_pointer = m_pointer->m_prev;
//	return *this;
//}
//template <typename T>
//bool list<T>::iterator::operator==(const iterator& rhs)
//{
//	return rhs.m_pointer == m_pointer;
//}
//template <typename T>
//bool list<T>::iterator::operator!=(const iterator& rhs)
//{
//	return rhs.m_pointer != m_pointer;
//}
//
//template<typename T>
//typename list<T>::iterator list<T>::iterator::operator+(int increment)
//{
//	iterator it = *this;
//	for (int i = 0; i < increment; ++i)
//	{
//		++it;
//	}
//	return it;
//}
//
//template<typename T>
//typename list<T>::iterator list<T>::iterator::operator-(int increment)
//{
//	iterator it = *this;
//	for (int i = 0; i < increment; ++i)
//	{
//		--it;
//	}
//	return it;
//
//}
//
//template <typename T>
//T& list<T>::iterator::operator*() const
//{
//	// You have to Make sure it's valid
//	assert(m_pointer != nullptr);
//	return m_pointer->m_element;
//}
//
//
//
//
//
//
////
//template <typename T>
//list<T>::list()
//{
//	// what is the element here?
//	header = new node(T());
//	trailer = new node(T());
//	header->m_next = trailer;
//	trailer->m_prev = header;
//	m_size = 0;
//}
//
//template <typename T>
//void list<T>::insert(const iterator& position, const T& element)
//{
//	node* next = position.m_pointer;
//	node* prev = next->m_prev;
//	node* newNode = new node(element, prev, next);
//	next->m_prev = newNode;
//	prev->m_next = newNode;
//
//	m_size++;
//}
//
//template <typename T>
//void list<T>::earse(const iterator& position)
//{
//	node* next = position.m_pointer->m_next;
//	node* prev = position.m_pointer->m_prev;
//	next->m_prev = prev;
//	prev->m_next = next;
//	delete position.m_pointer;
//
//	m_size--;
//
//}
//
//// what is typename?
//template <typename T>
//typename list<T>::iterator list<T>::begin() const
//{
//	return iterator(header->m_next);
//}
//// Remember the Sentinel Nodes?
//template <typename T>
//typename list<T>::iterator list<T>::end() const
//{
//	return iterator(trailer);
//}
//
