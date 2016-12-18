#include<iostream>
#include<unordered_set>
#include<numeric>
#include<string>
#include "hashval.h"
using namespace std;

class Customer {
private:
	string fname;
	string lname;
	long no;
public:
	Customer (const string& fn, const string& ln, long n) : fname(fn), lname(ln), no(n) {}
	friend ostream& operator << (ostream& strm, const Customer& c) {
		return strm << "[" << c.fname << "," << c.lname << "," << c.no << "]";
	}
	friend class CustomerHash;
	friend class CustomerEqual;
};

class CustomerEqual {
public:
	bool operator() (const Customer& c1, Customer& c2) const {
		return c1.no == c2.no;
	}

};

class CustomerHash {
public:
	size_t operator() (const Customer& c) const {
		return hash_val(c.fname, c.lname, c.no);
	}
};


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
	//create an initialize unordered set
	unordered_set<int> coll = {1,2,3,5,7,11,13,17,19,77};
	print_elements(coll, "coll"); // elements are in arbitrary order.
	coll.insert({-7,17,33,-11,17,19,1,13});//insert might cause rehashing and create different order.
	print_elements(coll, "coll"); 
	
	coll.erase(33); //remove element with specific value.
	print_elements(coll, "coll"); 

	coll.insert(accumulate(coll.begin(), coll.end(), 0));
	print_elements(coll, "coll"); 

	if(coll.find(19) != coll.end()) {
		cout << "19 is available " << endl;
	}
	
	//remove all negative values
	unordered_set<int>::iterator pos;
	for(pos = coll.begin(); pos != coll.end();) {
		if(*pos < 0) {
			pos = coll.erase(pos);
		} else {
			++pos;
		}
	}
	print_elements(coll, "coll"); 
	cout << "==========================================" << endl;

	//CustomerHash is hash function. we use it to calculate hash value. the container will use this hash value to define the bucket.
	//hash function is important so that the performance would be better.
	//CustomerEqual is used to compare two elements to decicide if they are equal or not.
	unordered_set<Customer, CustomerHash, CustomerEqual> custset;
	custset.insert(Customer("nico", "josuttis", 42));
	custset.insert(Customer("damon", "li", 20));
	custset.insert(Customer("damon", "li", 22));// it is different from above. so, the custset will have 3 elements.
	print_elements(custset, "custset"); 
	return 0;
}
