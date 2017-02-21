#include "DecoratorPattern.h"

int main()
{
	Beverage *beverage = new Espresso;
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;

	Beverage *beverage2 = new HouseBlend();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
	delete beverage2;
	
    return 0;
}

