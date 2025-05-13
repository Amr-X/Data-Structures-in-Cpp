
#include <iostream>

#include "Vector.h"
//#include "List.h"
//#include "Sequence.h"

// 1. How algorithm functions work? sort(iterator,iterator) with every iterator is different and whether it's const or not and const_iterator)
//  ex. vector<int> v(list.begin(),list.end()) -- vector should know about container::iterator , container::const_iterator , container::r_iterator
//		-- Polymorphism?
//  ex. vector<int> v(Array,Array+size) Array is a pointer to array .. How?



int main() {

	vector<int> int_vector(10);
	for (int i = 0; i < 10; ++i)
	{
		int_vector.set(i, i);
	}
	for (auto num : int_vector)
	{
		std::cout << num << " ";
		
	}
	return 0;
}