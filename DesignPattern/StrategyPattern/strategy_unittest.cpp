#include "strategy_pattern.cpp"

#include "gtest/gtest.h"

//use google test fixture class to test
class DuckTest : public ::testing::Test
{
protected:
	virtual void SetUp() {
		chinaduck = new ChinaDuck();
		mallard = new MallardDuck();
	}

	virtual void TearDown() {
		delete chinaduck;
		delete mallard;
	}

	Duck *chinaduck;
	Duck *mallard;
};

TEST_F(DuckTest, ChinaDuckFunctionalTest) {
  // You can access data in the test fixture here.
 	EXPECT_EQ(0, chinaduck->display());
	EXPECT_EQ(0, chinaduck->performQuack());
	EXPECT_EQ(0, chinaduck->performFly());
}

TEST_F(DuckTest, MallardDuckFunctionalTest) {
  // You can access data in the test fixture here.
 	EXPECT_EQ(0, mallard->display());
	EXPECT_EQ(0, mallard->performQuack());
	EXPECT_EQ(0, mallard->performFly());
}

