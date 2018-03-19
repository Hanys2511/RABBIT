//#include "../../code/src/prmtS.h"
#include "../../code/src/carlier.h"

#include "gtest/gtest.h"

namespace {

TEST(test, positive1)
{
	EXPECT_EQ(32, start(1));
}

TEST(test, positive2)
{
	EXPECT_EQ(641, start(2));
}

TEST(test, positive3)
{
	EXPECT_EQ(1267, start(3));
}

TEST(test, positive4)
{
	EXPECT_EQ(1386, start(4));
}

TEST(test, positive5)
{
	EXPECT_EQ(3472, start(5));
}

TEST(test, positive6)
{
	EXPECT_EQ(3617, start(6));
}

TEST(test, positive7)
{
	EXPECT_EQ(6885, start(7));
}

TEST(test, positive8)
{
	EXPECT_EQ(6904, start(8));
}

TEST(test, positive9)
{
	EXPECT_EQ(72852, start(9));
}

TEST(test, positive10)
{
	EXPECT_EQ(3486, start(10));
}

} // no name namespace
