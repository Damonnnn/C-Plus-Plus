#include<iostream>
#include<map>

using namespace std;


int main(void)
{
	map<const string,int>name_age = {{"dongming", 28},{"hongmei", 28}}; // using initlist
	name_age.insert({"dad", 61}); // using initlist
	name_age.insert(map<const string, int>::value_type("mom", 62)); // using value_type
	name_age.insert(pair<const string, int>("sister", 35)); //using pair
	name_age.insert(make_pair("second sister", 31));  // using make_pair
	name_age["brother"] = 24; // access element directly
	
	name_age.erase("brother"); // use erase() function

	cout << "the total key/value number is : " << name_age.size() << endl; // use size() function
	cout << "the maximum number is : " << name_age.max_size() << endl; // use max_size() function.

	

	cout << "the number of dongming is : " << name_age.count("dongming") << endl; // use count() function.
	if(name_age.end() != name_age.find("brother")) {  // use find() function
		cout << "we find brother in name_age map." << endl;
	} else {
		cout << "we cannot find brother in name_age map." << endl;
	}

	map<const string,int>::iterator pos;// using iterator
	for(pos = name_age.begin(); pos != name_age.end(); ++pos) {
		cout << pos->first << ", " << pos->second << endl;
	}
	cout << "=============================================" << endl;
	for(auto elem: name_age) { // using rage-based for loop
		cout << elem.first << ", " << elem.second << endl;
	}
	return 0;
}

