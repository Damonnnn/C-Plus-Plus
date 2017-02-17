#include "observer_pattern.h"

#include "gtest/gtest.h"

//use google test fixture class to test
class WheatherDataTest : public ::testing::Test
{
protected:
	virtual void SetUp() {
		//Observer = new ConditionDisplayObserver(wheatherData, "Damon");
		//Observer2 = new ConditionDisplayObserver(wheatherData, "Hongmei");
		wheatherData = new WheatherData;
	}

	virtual void TearDown() {
		//delete Observer;
		//delete Observer2; //can only test one class.
		delete wheatherData;
	}

	WheatherData *wheatherData;
	//ConditionDisplayObserver *Observer;
	//ConditionDisplayObserver *Observer2;
};

TEST_F(WheatherDataTest, ObserverPatternTest) {
  // You can access data in the test fixture here.
 	EXPECT_EQ(0, wheatherData->setMeasurements(80, 60, 23.5f));
	EXPECT_EQ(0, wheatherData->setMeasurements(60, 30, 22.5f));
	EXPECT_EQ(0, wheatherData->setMeasurements(20, 90, 27.5f));
}

/*
TEST_F(ObserverTest, MallardDuckFunctionalTest) {
  // You can access data in the test fixture here.
 	EXPECT_EQ(0, mallard->display());
	EXPECT_EQ(0, mallard->performQuack());
	EXPECT_EQ(0, mallard->performFly());
}
*/

