#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <array>
#include <set>
using namespace std;

bool creativiy2(const int arr[],int size) {
	//Should Return if there is two number's product is even
	//Isn't if there is one even number it will 100% produce even number? even *even | even * odd is even
	//Just search for one even number?
	for (int i = 0; i < size; i++) {
		if (arr[i] % 2 == 0)
			return true;
	}
	return false;
}

bool creativity3(vector<int>& vec) {
	//True if No Duplicates
	size_t size = vec.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			if (vec.at(i) == vec.at(j))
				return false; //Caught a Duplicate!
		}
	}
	return true;
}

vector<double> creativity8(vector<double>& vec1, vector<double>& vec2) {
	vector<double> c;
	for (size_t i = 0; i < vec1.size(); i++) {
		c.push_back(vec1[i] * vec2[i]);
	}
	return c;
}

void displayVec(const vector<double>& vec) {
	cout << "[ ";
	for (const auto& item : vec) {
		cout << item << " ";
	}
	cout << "]";
}

string makeTypo(string str) {
	if (!str.empty()) {
		str[0] = 'N';
	}
	return str;
}

void project1() {
	//Make Mistake on string 8 times.
	//Just get a Random number 

	//It is not Guaranteed to get the 8 mistakes (Maybe less mistakes based on the random number)
	string str = "What ever what ever.";
	int mistakes{};
	srand(time((0)));
	for (size_t i = 1; i <= 100; i++) {
		int random = rand() % 10 + 1 ;
		if (random <= 9 || mistakes > 8) {
			cout << i << ". " << str << endl;
		}
		else {
			cout << i << ". " << makeTypo(str) << endl;
			mistakes++;
		}
	}

}

void weekLine() {
	cout << left << setw(4) << "Sun"
		<< setw(4) << "Mon"
		<< setw(4) << "Tue"
		<< setw(4) << "Wed"
		<< setw(4) << "Thu"
		<< setw(4) << "Fri"
		<< setw(4) << "Sat" << endl;
}
void printDays(int pos,int days) {
	//Naming is confusing
	//Alot of checking Don't know if there is better elegant way
	int postion = 1;
	int emptyLeft = pos;
	for (size_t i = 1;i <= days;) {
		if (postion % 8 == 0) {
			cout << '\n';
			postion = 1;
		}
		cout << setw(4) << left;
		if (emptyLeft) {
			cout << "";
			emptyLeft--;
		}
		else {
			cout << i;
			i++;
		}
		postion++;
	}
	cout << endl;
}
void project2(const string &day, int year) { // Monday 2022
	//Could have been much better.
	//But it is a start nevertheless

	array<string,12> months{ "Junary","Feburay", "March", "April",
						 "May", "June" , "July" , "August",
						 "September", "October", "November", "December" };
	array<int, 12> monthsDays{ 31,28,31,30,31,30,31,31,30,31,30,31 };
	//Has to be easier way
	map<string, int> daysIndex{
		{"Sunday",0},
		{"Monday",1},
		{"Tuesday",2},
		{"Wednesday",3},
		{"Thursday",4},
		{"Friday",5},
		{"Saturday",6},
	};
	//Problem if not found
	int currentDay{ daysIndex[day]};
	//Logic here is good
	bool leapYear{false};
	if (year % 4 == 0)
		leapYear = true;

	for (size_t i = 0; i < 12; i++) {
		cout << setw(12) << months[i] << " " << year << endl;
		weekLine();

		//But the Logic usage here feel like a problem
		if(leapYear && i == 1) {
			printDays(currentDay, monthsDays[i] + 1);
		}
		else {
			printDays(currentDay, monthsDays[i]);
		}

		cout << endl;
		currentDay = (currentDay+monthsDays[i]) % 7;
	}
}

int main() {
	//int arr[5]{1,2,3,4,5};
	//cout << boolalpha;
	//cout << "Array Passed: " << creativiy2(arr, 5) << endl;
	//vector<int> vec{1,2,3,4,5,5};
	//cout << "Vector Has no Duplicate: " << creativity3(vec) << endl;
	//vector<double> vecd1{ 1.2,1.0,2.2 };
	//vector<double> vecd2{ 1.2,2.0,2.5 };
	//displayVec(creativity8(vecd1, vecd2));
//	project1();
//	project2(string{"Monday"},2024);

	return 0;

}