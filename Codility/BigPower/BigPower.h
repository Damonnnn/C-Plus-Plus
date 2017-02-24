#ifndef _BIG_POWER_H_
#define _BIG_POWER_H_
#include <iostream>
using namespace std;
class BigPower
{
	private:
		unsigned int mBase;
		unsigned int mPowerTimes;
		unsigned int mTotalBits = 0;
		unsigned int mResult[100000] = { 0 };/* the result should not exceed 10000 bits */
	public:
		BigPower(int base, int powerTimes) { mBase = base; mPowerTimes = powerTimes; }
		~BigPower() {}
		void calculateBigPower(void);
		friend ostream & operator<<(ostream & os, const BigPower & bigPower);
};



#endif