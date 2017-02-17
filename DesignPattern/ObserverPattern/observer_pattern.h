#ifndef __OBSERVER_PATTERN_H__
#define __OBSERVER_PATTERN_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Observer;
//===================abstract class definition========================
// define the abstract class for wheather data class.
class Subject {
public:
	virtual void registerObserver(Observer *observer) { cout << "Error0!!!\n"; }
	virtual void removeObserver(Observer *observer) { cout << "Error1!!!\n"; }
	virtual void notifyObserver(Observer *observer) { cout << "Error2!!!\n"; }
};

// define the abstract class for observer.
class Observer {
private:
	string observer;
public:
	Observer(string who) { 
		observer = who; 
		//cout << "Observer():" << observer << endl;
	}
	virtual void update(float temp, float humidity, float pressure){ cout << "Error!!!3\n"; }
	string who(void) { return observer; }
};

//define the abstract class for display.
class Display {
public:
	virtual void display(void) { cout << "Error!!!4\n"; };
};

//====================concrete class definition========================
// define the wheather data class.
class WheatherData : public Subject
{
private:
	vector<Observer *> observers;
	float temperature;
	float humidity;
	float pressure;
public:
	WheatherData() { 
		observers.clear(); 
		temperature = 0;
		humidity = 0;
		pressure = 0;
	}
	void registerObserver(Observer *observer) { observers.push_back(observer); }
	void removeObserver(Observer *observer) {
		//vector<Observer *>::interator pos;
		for(auto pos = observers.begin(); pos != observers.end(); ) {
			if((*pos)->who() == observer->who()) {
				pos = observers.erase(pos);
			} else {
				++pos;
			}
		}
	
	}
	void notifyObserver(void) {
		for(auto pos = observers.begin(); pos != observers.end(); ++pos) {
			(*pos)->update(temperature, humidity, pressure);
		}
	}

	void measurementsChanged() { this->notifyObserver(); }

	int setMeasurements(float temp, float humidity, float pressure) {
		this->temperature = temp;
		this->humidity = humidity;
		this->pressure = pressure;
		this->measurementsChanged();
		return 0;
	}
};

//define the display observer
class ConditionDisplayObserver : virtual public Observer, virtual public Display
{
private:
	float temperature;
	float humidity;
	Subject *wheatherData; // this is the subject
public:
	ConditionDisplayObserver(Subject *wheatherData, string who) : Observer(who) {
		this->wheatherData = wheatherData;
		this->wheatherData->registerObserver(this);
	}
	void update(float temp, float humidity, float pressure) {
		this->temperature = temp;
		this->humidity = humidity;
		this->display();
	}
	void display(void) {
		cout << who() << " Current conditions: temperature=" << temperature << " humidity=" << humidity << endl;
	}
};

#endif
