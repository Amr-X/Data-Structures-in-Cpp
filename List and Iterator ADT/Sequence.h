//#pragma once
//
//#include "List.h"
//template <typename T>
//class sequence : public list<T>
//{
//public:
//	sequence::iterator atIndex(int index) const;
//	int indexOf(const typename sequence::iterator& it) const;
//};
//
//template <typename T>
//typename sequence<T>::iterator sequence<T>::atIndex(int index) const
//{
//	// atIndex(4)
//	auto curr = this->begin();
//	
//	
//	for (int i = 0; i < index; ++i)
//	{
//		++curr;
//	}
//	return curr;
//}
//template <typename T>
//int sequence<T>::indexOf(const typename sequence::iterator& it) const
//{
//	auto curr = this->begin();
//	int index = 0;
//	while (curr != it)
//	{
//		++curr; ++index;
//	}
//	return index;
//}

