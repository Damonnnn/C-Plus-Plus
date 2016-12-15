#include<iostream>
#include<list>
#include<string>

using namespace std;

template <typename T>
void print_elements(const T& coll, const string & str)
{
	cout << str << ": ";
	for(const auto& elem : coll) {
		cout << elem << " ";
	}
	cout << endl;
}

int main(void)
{
	list<string> my_list = {"China", "NewZealand"}; // use initialize list
	my_list.push_back("Thailand"); // use push_back function to insert element.
	my_list.push_front("Hongkong"); // use push_front function to insert element.
	my_list.emplace_back("Korea"); // use emplace_back function
	my_list.insert(my_list.end(), "Korea"); // use insert function
	my_list.remove("Korea"); // use remove function
	print_elements(my_list, "my_list");
	cout << "my_list: size = " << my_list.size() << endl; //use size function
	cout << "my_list: max_size = " << my_list.max_size() << endl; // use max_size function
	cout << "my_list: the first element is : " << my_list.front() << endl;// use front function
	cout << "my_list: the last element is : " << my_list.back() << endl; // use back function
	
	cout << "my_list: ";
	for(auto pos = my_list.rbegin(); pos != my_list.rend(); ++pos) {// use reverse iterator functions.
		cout << *pos << " ";
	}
	cout << endl;

	cout << "=================================" << endl;
	list<string> my_list2(my_list); // equal my_list2 = my_list;
	my_list2.push_back("Thailand");
	print_elements(my_list2, "my_list2");
	my_list2.unique(); //use unique function. this function will only handle the consecutive elements
	print_elements(my_list2, "my_list2");
	my_list2.splice(my_list2.end(), my_list); //use splice function
	print_elements(my_list2, "my_list2");
	my_list2.sort();// use sort function
	print_elements(my_list2, "my_list2");
	cout << "=================================" << endl;
	list<string> my_list3 = {"Taiwai", "USA"};
	my_list3.merge(my_list2);// use merge function
	print_elements(my_list3, "my_list3");
	my_list3.reverse(); // use reverse function.
	print_elements(my_list3, "my_list3");
	return 0;
}
