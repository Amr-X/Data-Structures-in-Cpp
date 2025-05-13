#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <exception>
#include <fstream>
using namespace std;



void Dynamic_Cast() {
	class Person {
	protected:
		string name;
		int age;
	public:
		Person(const string& name, int age) :
			name(name), age(age) {
		}
		virtual void print() const {
			cout << setw(20) << left << name << right << age << endl;
		}
		virtual ~Person() = default;

	};

	class Student :public Person {
	private:
		string major;
	public:
		Student(const string& name, int age, const string& major) :
			Person{ name,age }, major(major) {
		}
		virtual void print() const {
			cout << setw(20) << left << name << age << "   " << major << endl;
		}
		void changeMajor(const string& major) {
			this->major = major;
		}
		virtual ~Student() = default;
	};
	Person* PersonsArray[10];
	PersonsArray[0] = new Person{ "Amr",20 };
	PersonsArray[1] = new Student{ "Amr",20,"CS" };
	PersonsArray[0]->print(); //Person::print()
	PersonsArray[1]->print(); //Person::Print(); if Static Binding
	//No Access 
//	(*PersonsArray[1]).changeMajor("bla");

	//Dynamic Objects (Virtual) Casted with Dynamic_cast
	auto sp = dynamic_cast<Student*>(PersonsArray[1]);

	//You can't Person* to Student* because Person* is pointing to person
	//but the Oposite can be done (I  think)
	auto sp_null = dynamic_cast<Student*>(PersonsArray[0]);
	//Shall we Try? But i think we will lose data (Oh we did not)
	// We are just changing the type of the pointer not the object itself
	auto pp = dynamic_cast<Person*>(sp); // Can it return Nullptr in anycase?
	if (sp != nullptr) {
		sp->changeMajor("bla");
		sp->print();
	}
	//Can be here also but who know what it will return if failed
	auto sp_static = static_cast<Student*> (PersonsArray[1]);
	//Im losing my mind.
}
class OutofboundException {
public:
	const char* what() const {
		return "Out of Bound Index";
	}
};

void Reinforcement13() {
	const int size = 10;
	int arr[size]{ 1,2,3,4,5,6,7,8,9,10 };
	int n;
	cout << "Enter Index to Modify on array: ";
	cin >> n;
	try {
		if (n < size && n >= 0) {
			arr[n] = 10;
			cout << "Modifed to 10" << endl;
		}
		else {
			throw OutofboundException();
		}

	}
	catch(OutofboundException &ex){
		cerr << ex.what() << endl;
	}
}

void Reinforcement14() {
	class Object
	{
	public: virtual void printMe() = 0;
	};
	class Place : public Object
	{
	public: virtual void printMe() { cout << "Buy it.\n"; }
	};
	class Region : public Place
	{
	public: virtual void printMe() { cout << "Box it.\n"; }
	};
	class State : public Region
	{
	public: virtual void printMe() { cout << "Ship it.\n"; }
	};
	class Maryland : public State
	{
	public: virtual void printMe() { cout << "Read it.\n"; }
	};

	Region* mid = new State;
	State* md = new Maryland;
	Object* obj = new Place;
	Place* usa = new Region;
	md->printMe();
	mid->printMe();
	(dynamic_cast<Place*>(obj))->printMe();
	obj = md;
	(dynamic_cast<Maryland*>(obj))->printMe();
	obj = usa;
	(dynamic_cast<Place*>(obj))->printMe();
	usa = md;
	(dynamic_cast<Place*>(usa))->printMe();
}

bool Reinforcement17(int a, int b, int c) {
	if ((a * b == c) ||
		(a + b == c) ||
		(a / b == c) ||
	    (a - b == c) || 
		(c + b == a) ||
		(c / b == a) ||
		(c - b == a) ||
		(c * b == a)
		)
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////

void creativity5() {
	class Progression {
	public:
		Progression(long f = 0)
			: first(f), cur(f) {
		}
		virtual ~Progression() {};
		void printProgression(int n) {};
	protected:
		virtual long firstValue() { return 5; }
		virtual long nextValue() { return 5; };
	protected:
		long first;
		long cur;
	};
	class myProgression : public Progression {

	public:
		myProgression(long f = 2, long s = 200)
			: Progression(f), second(s) {

		}
		long firstValue() {
			first = 2; //Default
			second = 200;
			return first;
		}
		long nextValue() override { // This is it can use std::abs();
			long nextValue = first - second;
			first = second;
			if (nextValue < 0) {
				second = -nextValue;
				return second;
			}
			second = nextValue;
			return second;
		}
	protected:
		long second;
	};


	myProgression p;
	cout << p.nextValue() << " " << p.nextValue() << endl;
}

void creativity9(vector<int>&& arr){
	//Assuming arr provided is in correct manner
	size_t exp = arr.size() -1;
	for (size_t i = 0; i < arr.size() - 1; i++) {
		int coeff = arr[i] * exp;
		if (coeff != 0) {
			cout << coeff;
			if (exp > 1) {
				cout << "x^" << (exp - 1);
			}
			else if (exp == 1) {
				cout << "x";
			}

			if (i < arr.size() - 2) {  // no "+" after the last term
				cout << " + ";
			}
		}
		exp--;
	}
}

int project1(int n) {
	int count{ 0 };
	while (n >= 2) {
		n /= 2;
		count++;
	}
	return count;
}

///////////////////////////////////////////////////////////////////


// 1. Construct things that can be constructed (i know it's basic but to clear confustion)
// 2. T(0) -> 0 , 0.0 , 0f Numerical
// 3. () {} ={} Difference
// 4. Throw Exception if it make sense - A little harsh to abort the program if no catch but it's okay
template <typename T>
class Vector {
private:
	vector<T> vec;
public:
	Vector(size_t size)
		:vec(size, T(0)) { // Initialize vec with size and 0(int) , 0.0 (double) , 0.0f(float)
	}
	Vector(size_t size, T value)
		:vec(size,value) {

	}
	Vector()
		:vec() { // No Size 

	}
	Vector<T> operator+(const Vector<T>& rhs) const{
		size_t mySize = vec.size();
		if (mySize == rhs.vec.size()) {
			Vector<T> returnVec;
			for (int i = 0; i < mySize;i++) {
				returnVec.vec.push_back((vec.at(i) + rhs.vec.at(i)));
			}
			return returnVec;
		}
		throw invalid_argument("Vector Size Doesn't Match");
	}
	Vector<T> operator-(const Vector<T>& rhs) const{
		size_t mySize = vec.size();
		if (mySize == rhs.vec.size()) {
			Vector<T> returnVec;
			for (int i = 0; i < mySize;i++) {
				returnVec.vec.push_back((vec.at(i) - rhs.vec.at(i)));
			}
			return returnVec;
		}
		throw invalid_argument("Vector Size Doesn't Match");
	}
	Vector<T> operator*(int scalar) const{
		size_t mySize = vec.size();
		Vector<T> returnVec;
		for (int i = 0; i < mySize;i++) {
			returnVec.vec.push_back((vec.at(i) * scalar)); 
		}
		return returnVec;
	}
	int dot(const Vector<T>& rhs) const {
		size_t mySize = vec.size();
		int product = 0;
		if (mySize == rhs.vec.size()) {
			for (int i = 0; i < mySize;i++) {
				product += (vec.at(i) * rhs.vec.at(i));
			}
			return product;
		}
		throw invalid_argument("Vector Size Doesn't Match");
	}
	void print() const {
		cout << "[";
		for (size_t i = 0; i < vec.size(); ++i) {
			cout << vec.at(i);
			if (i < vec.size() - 1) cout << ", ";
		}
		cout << "]" << endl;
	}

		
};
void project3() {
	//Only int double float (numerical)
	Vector<int> v1(3, 2);    
	Vector<int> v2(3, 3);    

	Vector<int> v3 = v1 + v2;  
	Vector<int> v4 = v1 - v2;  
	Vector<int> v5 = v1 * 5;   

	cout << "v1: "; v1.print();   
	cout << "v2: "; v2.print();
	cout << "v3 (v1+v2): "; v3.print();
	cout << "v4 (v1-v2): "; v4.print();
	cout << "v5 (v1*5): "; v5.print();

	int dot = v1.dot(v2);    
	cout << "Dot product v1 • v2: " << dot << endl;

}

void project6() {
	ifstream file{ "Doc.txt" };
	if (!file) {
		cout << "Can't Open File" << endl;
		return;
	}
	int arraySize = 'z' + 1; // from 0 to 123
	int* plotChart = new int[arraySize] {0};
	char ch;
	while (file >> ch) {
		if (isalpha(ch)) {
			plotChart[ch]++;
		}
	}
	file.close();
	for (char i = 'A'; i <= 'z';i++) {
		if (plotChart[i] > 0) {
			cout << i << ": ";
			for (int j = (plotChart[i]); j > 0; j--) {
				cout << '#';
			}
			cout << '\n';
		}
	}
	delete[] plotChart;

}

void project7() {
	//Done Before
	//Efficency is Problem
	//Get word search for it in the entire file
	//Store words while you scan in map or double vector
}

int main() {
	//Dynamic_Cast();
	//Reinforcement13();
	//Reinforcement14();
	//cout << std::boolalpha << Reinforcement17(5,4,10) << endl;
	//creativity9(vector<int>{4,3,1,-5});
	//cout << project(33);
	//project3();
	project6();

	return 0;
} 

