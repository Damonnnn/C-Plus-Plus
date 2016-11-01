// BigPower.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include "BigPower.h"


void BigPower::calculateBigPower(void)
{
	unsigned int i,j;
	unsigned int multiply;
	unsigned int extend_flag = 0;
	mTotalBits = 1;
	mResult[0] = 1;
	for (i = 0; i < mPowerTimes; ++i) {
		for (j = 0; j < mTotalBits; ++j) {
			/*****************************************************
			the code:
			multiply = mResult[j] * mBase + extend_flag; 
			is optimized from below:
			if (0 == extend_flag) { //if  NOT extend before
				multiply = mResult[j] * mBase;
			}
			else { //if  extend before
				multiply = mResult[j] * mBase + extend_flag;
			}
			******************************************************/
			multiply = mResult[j] * mBase + extend_flag;
			/*****************************************************************
			the code:
			mResult[j] = multiply % 10;
			extend_flag = multiply / 10;
			if ((extend_flag > 0) && (mTotalBits == (j + 1))) {
			mTotalBits++;
			}
			is optimized from below:

			 Below code can be simplified from:
				if (multiply > MAX_VALUE) { // need extend. MAX_VALUE=9
					mResult[j] = multiply % 10;
					extend_flag = multiply / 10;
					if ((extend_flag > 0) && (mTotalBits == (j + 1))) {
						mTotalBits++;
					}
				}
				else { // no need extend
					mResult[j] = multiply;
					extend_flag = 0;
				}
			******************************************************************/
			mResult[j] = multiply % 10;
			extend_flag = multiply / 10;
			if ((extend_flag > 0) && (mTotalBits == (j + 1))) {
				mTotalBits++;
			}
			
		}
	}
}

ostream & operator<<(ostream & os, const BigPower & bigPower)
{
	int i;
	for (i = bigPower.mTotalBits - 1; i >= 0; --i) {
		os << bigPower.mResult[i];
	}
	return os;
}

int main()
{
	unsigned int base, powerTimes;
	while (1) {
		cout << "Please intput the base number and power times:" << endl;
		cout << "base = ";
		cin >> base;
		cout << "powerTimes = ";
		cin >> powerTimes;
		BigPower data(base, powerTimes);
		data.calculateBigPower();
		cout << base << " ^ " << powerTimes << " = " << data << endl;
	}
	
    return 0;
}

