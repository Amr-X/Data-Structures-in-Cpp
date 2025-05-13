#pragma once
#pragma once

// I Stared at that piece of code for about 1.5 hours 
template<typename IteratorType>
// From now on, I'm using auto forever - I don't wanna know how to return anything other than auto
auto sum(IteratorType start, IteratorType end) -> std::remove_reference_t<decltype(*start)>
{
	// int sum = 0; // This assumes the iterator is pointing to int type
	// What if Not? Like double or even object with opeator+

	// Yeah , We still have a problem -- it returns int& so we use remove_reference_t
	typedef std::remove_reference_t<decltype(*start)> ValueType;

	ValueType sum = ValueType(); // if int -> int sum = int();

	for (auto it = start ; it != end; ++it)
	{
		sum += *it;
	}
	return sum;
}

template<typename Iterator,typename ValueType>
auto accumulate(Iterator start , Iterator end, ValueType initial)
{
	while (start != end)
	{
		initial += *start;
		++start;
	}
	return initial;
}
