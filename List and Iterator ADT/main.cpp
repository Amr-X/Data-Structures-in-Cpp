
#include <iostream>

#include "Vector.h"
#include "List.h"
#include "Algorithm.h"
// 1. How algorithm functions work? sort(iterator,iterator) with every iterator is different and whether it's const or not and const_iterator)
// Answer : Template function


// Can be there more tests
void vectorTest() {

	std::cout << "Vector Test" << std::endl;
	vector<int> int_vector(10);
	for (int i = 0; i < 10; ++i)
	{
		int_vector.set(i, i);
	}
	for (auto num : int_vector)
	{
		std::cout << num << " ";
		
	}
}
void listTest(){

	std::cout << "List Test" << std::endl;
	list<int> int_list;
	for (int i = 0; i < 10; ++i)
	{
		int_list.insert(int_list.end(), i);
	}
	for (auto num : int_list)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	std::cout << "After Erase first element" << std::endl;
	int_list.erase(int_list.begin());
	for (auto num : int_list)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

int main() {

	vectorTest();
	std::cout << "\n\n";
	listTest();
	std::cout << "\n\n";
	vector<int> intvec(10);
	for (int i = 0; i < 10; ++i)
	{
		intvec.set(i, i);
	}
	std::cout << "Sum of vector: " << sum(intvec.begin(), intvec.end()) << std::endl;
}