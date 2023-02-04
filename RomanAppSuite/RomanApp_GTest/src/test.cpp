

#include "Dec2Roman.h"
#include <gtest/gtest.h>


// https://google.github.io/googletest/quickstart-cmake.html


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST( DecRoman_TestSuite, ChainTest )
{
	bool result = Decimal_2_Roman_Chain_UnitTest();

	// Niekrytyczna asercja
	EXPECT_EQ( result, true ) << "All decimals 1..3999 should pass and vice versa";

	// Krytyczna asercja
	ASSERT_EQ( result, true ) << "All decimals 1..3999 should pass and vice versa";
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



