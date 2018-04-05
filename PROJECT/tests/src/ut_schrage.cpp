#include "../../code/src/carlier.h"

#include "gtest/gtest.h"

namespace {

class ut_scharage: public ::testing::Test
{
protected:
	permutacja glowna;
	void start(int carlierr)
	{
		wczytaj_z_pliku(carlierr, glowna);
	}
};

TEST_F(ut_scharage, positive1)
{
	start(1);
	std::vector<std::shared_ptr<proces>> test {
		std::make_shared<proces>(1, 5, 9),
		std::make_shared<proces>(4, 5, 4),
		std::make_shared<proces>(1, 4, 6),
		std::make_shared<proces>(7, 3, 3),
		std::make_shared<proces>(3, 6, 8),
		std::make_shared<proces>(4, 7, 1)
	};
	for (int i=0;i<6;i++) {
		EXPECT_EQ(test[i]->Rpi, glowna.procesy[i]->Rpi);
		EXPECT_EQ(test[i]->Ppi, glowna.procesy[i]->Ppi);
		EXPECT_EQ(test[i]->Qpi, glowna.procesy[i]->Qpi);
	}
}

} // no name namespace
