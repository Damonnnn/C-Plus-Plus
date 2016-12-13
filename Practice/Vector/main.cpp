#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T>
void print_elements(const T& coll, const string& str)
{
	cout << str << ": ";
	for(const auto& elem : coll) {
		cout << elem << " ";
	}
	cout << endl;
}

int main(void)
{
	vector<string> fruits = {"Apple", "Banana"};//init list
	fruits.reserve(10); // call reserve to reserve 10 elements space.
	print_elements(fruits, "fruits");
	cout << "fruits: size=" << fruits.size() << " ;max_size=" << fruits.max_size() << " ;capacity=" << fruits.capacity() << endl; // use size,max_size,capacity function.
	fruits.shrink_to_fit(); //use shrink to fit function. after this function, the capacity will be 2.
	cout << "fruits: size=" << fruits.size() << " ;max_size=" << fruits.max_size() << " ;capacity=" << fruits.capacity() << endl;
	fruits.reserve(8); // make its capacity 8 to do following test.
	cout << "fruits: capacity=" << fruits.capacity() << endl; // here, the capacity will be 8.
	
	vector<string> fruits2 = fruits; // init with another vecotr, copy constructor will be used.
	print_elements(fruits2, "fruits2"); 
	cout << "fruits2: capacity=" << fruits2.capacity() << endl; // here, the capacity will be 2.


	vector<string> fruits3 = move(fruits2); // init with another vecotr, move constructor will be used.
	print_elements(fruits2, "fruits2"); // here, the fruits2 has nothing any more.
	print_elements(fruits3, "fruits3");
	cout << "fruits3: capacity=" << fruits3.capacity() << endl; // here, the capacity will be 2.
	fruits3.assign(5, "pear"); // use function assign, all 5 elements will be pear.
	print_elements(fruits3, "fruits3"); 
	cout << "fruits3: capacity=" << fruits3.capacity() << endl; // here, the capacity will be 5.
	fruits3.reserve(10); // make its capacity to 10 to do following test.
	
	vector<string> fruits4 = {"range"};
	fruits4.swap(fruits3); //not only swap their elements, but also swap the capacity.
	print_elements(fruits3, "fruits3"); 
	cout << "fruits3: capacity=" << fruits3.capacity() << endl; // here the capacity will be 1;
	print_elements(fruits4, "fruits4"); 
	cout << "fruits4: capacity=" << fruits4.capacity() << endl; // here the capacity will be 10
	vector<string> temp(fruits4); // not use shrink_to_fit, use swap to shrink the capacity. before C++11
	fruits4.swap(temp); // not use shrink_to_fit, use swap to shrink the capacity. before C++11
	print_elements(fruits4, "fruits4"); 
	cout << "fruits4: capacity=" << fruits4.capacity() << endl; // here the capacity will be 5
	
	for(auto pos = fruits4.begin(); pos != fruits4.end(); ++pos) { //use iterator functions
		cout << *pos << " ";
	}
	cout << endl;
	
	for(int i = 0; i < fruits4.size(); ++i) {
		cout << fruits4[i] << " "; // use direct element access.
	}
	cout << endl;
	
	fruits4.push_back("Apple"); //use push back to insert element
	fruits4.insert(fruits4.end(), "Banana"); // use insert function to insert element.
	fruits4.emplace_back("Pear"); // use emplace function
	print_elements(fruits4, "fruits4"); 
	cout << "fruits4: size=" << fruits4.size() << " ;max_size=" << fruits4.max_size() << " ;capacity=" << fruits4.capacity() << endl; // here the capacity will be 10, size = 8;
	cout << "===========================" << endl;
	fruits4.resize(3); //use  resize functon. only 3 elements are left after this function. if we resize(10), then, 2 empty value will be added and the size will be 10.
	print_elements(fruits4, "fruits4"); //
	cout << "fruits4: size=" << fruits4.size() << " ;max_size=" << fruits4.max_size() << " ;capacity=" << fruits4.capacity() << endl; // here the capacity will be 10, size = 3;
	fruits4.emplace_back("Apple"); // use emplace function
	print_elements(fruits4, "fruits4"); 
	cout << "fruits4: size=" << fruits4.size() << " ;max_size=" << fruits4.max_size() << " ;capacity=" << fruits4.capacity() << endl; // here the capacity will be 10, size = 4;
	
	fruits4.clear(); // use clear function to clear all elements.
	print_elements(fruits4, "fruits4"); 
	cout << "fruits4: size=" << fruits4.size() << " ;max_size=" << fruits4.max_size() << " ;capacity=" << fruits4.capacity() << endl; // here the capacity will be 10, size = 0;

	cout << "===========================" << endl;
	fruits.erase(fruits.end()); // use erase function;
	print_elements(fruits, "fruits"); //only Apple left.

	cout << "==============vector<bool>===========" << endl;
	vector<bool> mybool = {true, true, false, false, true};
	mybool.reserve(10);//this function has nothing effect on mybool. why?
	print_elements(mybool, "mybool"); 
	cout << "mybool: size=" << mybool.size() << " ;max_size=" << mybool.max_size() << " ;capacity=" << mybool.capacity() << endl; // here the capacity will be 64, size = 5;
	cout << "the memeory space occupied by mybool = " << sizeof(mybool) << endl;// the result is 40, why?

	mybool.flip(); // use flip function.
	print_elements(mybool, "mybool"); // every element will be reverced. the result is 0 0 1 1 0
	
	mybool[1].flip(); // only bit 1 be reversed.
	print_elements(mybool, "mybool");

	mybool.push_back(true);
	print_elements(mybool, "mybool");
return 0;
}
