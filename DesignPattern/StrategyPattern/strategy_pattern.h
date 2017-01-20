#ifndef __STRATEGY_PATTERN_H__
#define __STRATEGY_PATTERN_H__

#include <iostream>

using namespace std;

//here we use  pure vitual function to make FlyBehavior a abstract class.
class FlyBehavior
{
public:
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
	void fly() { cout << "I am flying!!" << endl; }
};

class FlyNoWay : public FlyBehavior
{
public:
	void fly() { cout << "I can't flying!!" << endl; } // just do nothing. can't fly.
};

//here we use  pure vitual function to make QuackBehavior a abstract class.
class QuackBehavior
{
public:
	virtual void quack() = 0;
};

class Quack : public QuackBehavior
{
public:
	void quack() { cout << "Quack" << endl; }
};

class Squeak : public QuackBehavior
{
public:
	void quack() { cout << "Squeak" << endl; }
};

class MuteQuack : public QuackBehavior
{
public:
	void quack() { cout << "<< Silence >>" << endl; } // do nothing, cannot quack.
};


//here we use  pure vitual function to make Duck a abstract class.
class Duck 
{
public:
	virtual ~Duck() {};
	int swim() { cout << "All ducks float, even decoys." << endl; return 0;}
	virtual int display() = 0;
	int performQuack() { quackBehavior->quack(); return 0;}
	int performFly() { flyBehavior->fly(); return 0;}
protected:	 // we use protected key word to make the member variable available to the child class.
	FlyBehavior *flyBehavior; //different ducks may have different fly behavior.
	QuackBehavior *quackBehavior; //different ducks may have different quack behavior.

};

class MallardDuck : public Duck
{
public:
	virtual ~MallardDuck() {};
	MallardDuck() { 
		flyBehavior = new FlyWithWings();
		quackBehavior = new Quack();
	}
	int display() { cout << "I am a real mallar duck!" << endl; return 0;}
};

class ChinaDuck : public Duck
{
public:
	virtual ~ChinaDuck() {};
	ChinaDuck() { 
		flyBehavior = new FlyNoWay();
		quackBehavior = new Squeak();
	}
	int display() { cout << "I am a real China duck!" << endl; return 0;}
};


#endif


