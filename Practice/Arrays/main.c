#include<iostream>
#include<array>

using namespace std;

// template function to print container elements.
//*
template <typename T>
void print_elements(const T& coll, const string& str)
{
	cout << str << " :";
	for(const auto& elem : coll) {
		cout << elem << " ";
	}
	cout << endl;
}
//*/

/*
void print_elements(const array<string,5> &arr, const string &str)
{
	cout << str << " :";
	for(const auto& elem : arr) { // use for loop based
		cout << elem << " ";
	}
	cout << endl;

	for(auto pos = arr.begin(); pos != arr.end(); ++pos) { // iterator
		cout << *pos << " ";
	}
	cout << endl;
}
*/

int main()
{
	array<string, 5> hobbies = {"Pingpang", "Movie", "Reading", "Driving", "Bicycle"}; // init with initial list
	print_elements(hobbies, "hobbies");
	
	array<string, 5> hobbies2;
	hobbies2[0] = "Hiking"; // element access with subscript
	hobbies2[1] = "Running";
	hobbies2.at(2) = "Reading"; // use function at() for direct accessing
	hobbies2.at(3) = "Fishing";
	hobbies2.back() = "Travelling"; // use function back() for direct accessing
	print_elements(hobbies2, "hobbies2");

	swap(hobbies, hobbies2); // use swap function
	print_elements(hobbies, "hobbies");
	print_elements(hobbies2, "hobbies2");

	hobbies.swap(hobbies2); // use memeber function swap
	print_elements(hobbies, "hobbies");
	print_elements(hobbies2, "hobbies2");

	if(hobbies > hobbies2) { // use  logic operator
		cout << "hobibies > hobbies2" << endl;
	} else if( hobbies < hobbies2) {
		cout << "hobibies < hobbies2" << endl;
	} else {
		cout << "hobibies == hobbies2" << endl;
	}
	
	array<int, 5> number;
	print_elements(number, "number");
	number.fill(35); // use of fill function. all element will be set as 35
	print_elements(number, "number");
	cout << "the size of number is : " << number.size() << endl; // use size function

	
	return 0;
}
