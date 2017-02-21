#ifndef __DECORATOR__
#define __DECORATOR__

#include <iostream>
#include <string>

using namespace std;

//abstraction base class for Beverage
class Beverage
{
private:
	string description;
public:
	virtual string getDescription() { return description; }
	virtual void setDescription(string s) { description = s; }
	virtual double cost() { cout << "Error!!!" << endl;  return 0; }
};

class CondimentDecorator : public Beverage
{
	//we no need to define anything here.
};

//coding beverages
class Espresso : public Beverage
{
public:
	Espresso() { setDescription("Espresso"); }
	double cost() { return 1.99; }
};

class HouseBlend : public Beverage
{
public:
	HouseBlend() { setDescription("House Blend Coffee"); }
	double cost() { return 0.89; }
};


//coding condiments
class Mocha : public CondimentDecorator
{
private:
	Beverage *beverage;
public:
	Mocha(Beverage *beverage) { this->beverage = beverage; }
	~Mocha() { delete beverage; }
	string getDescription() { return beverage->getDescription() + ", Mocha"; }
	double cost() { return 0.2 + beverage->cost(); }
};

class Whip : public CondimentDecorator
{
private:
	Beverage *beverage;
public:
	Whip(Beverage *beverage) { this->beverage = beverage; }
	~Whip() { delete beverage; }
	string getDescription() { return beverage->getDescription() + ", Whip"; }
	double cost() { return 0.3 + beverage->cost(); }
};


#endif
