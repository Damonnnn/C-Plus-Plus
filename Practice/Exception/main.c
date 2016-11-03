#include <iostream>
#include <string>
using namespace std;

class Except
{
private:
	string exceptionInfo;
public:
	Except(string s = "") : exceptionInfo(s) {}
	string getExceptInfo() {return exceptionInfo;}
};

int main()
{
	try 
	{
		Except info("I am a programmer");
		throw info;
	}

	catch (const char * s) 
	{
		cout << "I get a : " << s << endl;
	}
	catch (Except & error)
	{
		cout << "I get a exception: " << error.getExceptInfo() << endl;
	}
	catch (...) 
	{
		cout << "I get a unpredictable string" << endl;
	}


}
