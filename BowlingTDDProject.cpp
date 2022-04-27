#include "catch/catch.hpp"
#include "BowlingGame.h"

class SimpleCalculator {
public:
    int add(int a, int b) {
        return a + b;
    }
};

TEST_CASE("SimpleCalculator_add_test") {
    SimpleCalculator testObj;

    REQUIRE( testObj.add(2, 2) == 4);
    REQUIRE( testObj.add(2, 4) == 6);
}

TEST_CASE("OneRoundWith0PinsShouldScore0")
{
	BowlingGame game;
	game.roll(0);
	game.roll(0);

	REQUIRE(game.getScore() == 0);
}

TEST_CASE("OneRoundWithXPinsWhereXIsLowerThan10ShouldScoreX")
{
	auto test = [](int x, int y) -> int
	{
		BowlingGame game;
		game.roll(x);
		game.roll(y);
		return game.getScore();
	};

	REQUIRE(test(1,2) == 3);
	REQUIRE(test(2,1) == 3);
	REQUIRE(test(4,5) == 9);
	REQUIRE(test(3,4) == 7);
	REQUIRE(test(1,1) == 2);
	REQUIRE(test(0,2) == 2);
	REQUIRE(test(0,6) == 6);
}

TEST_CASE("EveryRoundWithPinsLowerThan10RiseScoreByPinsNumber")
{
	BowlingGame game;

	game.roll(3);
	game.roll(6);
	REQUIRE(game.getScore() == 9);

	game.roll(3);
	game.roll(6);
	REQUIRE(game.getScore() == 18);

	game.roll(1);
	game.roll(5);
	REQUIRE(game.getScore() == 24);

	game.roll(0);
	game.roll(3);
	REQUIRE(game.getScore() == 27);

	game.roll(4);
	game.roll(5);
	REQUIRE(game.getScore() == 36);

	game.roll(0);
	game.roll(0);
	REQUIRE(game.getScore() == 36);
}

TEST_CASE("ThereIsOnly20ThrowsWhenNoBonuses")
{
	BowlingGame game;
	for(int i = 0; i < 20; ++i)
		game.roll(1);
	REQUIRE(game.getScore() == 20);

	game.roll(1);
	REQUIRE(game.getScore() == 20);
}


TEST_CASE("RoundWithSumOf10PinsInTwoThrowsResultInSpareSoNextThrowAddDoublePoints")
{
	BowlingGame game;

	game.roll(3);
	game.roll(6);//9

	game.roll(4);
	game.roll(6);//10
	REQUIRE(game.getScore() == 19);

	game.roll(3);
	game.roll(5);//8
	REQUIRE(game.getScore() == 30);

	game.roll(1);
	game.roll(9);//10
	REQUIRE(game.getScore() == 40);

	game.roll(3);
	game.roll(7);//10
	REQUIRE(game.getScore() == 53);

	game.roll(1);
	game.roll(0);//1
	REQUIRE(game.getScore() == 55);
}

TEST_CASE("SpareIn10thRoundResultInOneAdditionalThrow")
{
	BowlingGame game;
	for(int i = 0; i < 19; ++i)
		game.roll(1);
	game.roll(9);
	//28

	game.roll(1);
	REQUIRE(game.getScore() == 29);
}

TEST_CASE("WithEveryRoundTheres9+1PinsAndAsResultThereShouldBe190")
{
	BowlingGame game;
	for(int i = 0; i < 21; i+=2)
	{
		game.roll(9);
		game.roll(1);
	}

	REQUIRE(game.getScore() == 190);
}

TEST_CASE("WhenFirstThrowInRoundResultIn10PinsItsStrikeSoNext2ThrowsResultInDoublePointsAnd2ndThrowIsSkipped")
{
	BowlingGame game;
	game.roll(10);

	game.roll(4);
	game.roll(4);

	REQUIRE(game.getScore() == 26);


	game.roll(10);

	game.roll(10);

	game.roll(3);
	game.roll(3);
	REQUIRE(game.getScore() == 71);
}

TEST_CASE("StrikeIn10thRoundResultIn2(AndOnly2)AdditionalThrows")
{
	BowlingGame game;
	for(int i = 0; i < 9; ++i)
	{
		game.roll(1);
		game.roll(1);
	}

	game.roll(10);
	game.roll(10);
	game.roll(10);

	REQUIRE(game.getScore() == 48);

	game.roll(10);
	game.roll(10);

	REQUIRE(game.getScore() == 48);
}

TEST_CASE("IfTheresOnlyStrikesScoreShouldBe300")
{
	BowlingGame game;
	for(int i = 0; i < 13; ++i)
		game.roll(10);

	REQUIRE(game.getScore() == 300);

	game.roll(10);
	game.roll(3);
	REQUIRE(game.getScore() == 300);
}

TEST_CASE("FullTestCase1")
{
	BowlingGame game;

	game.roll(3);
	game.roll(4);

	game.roll(8);
	game.roll(2);

	game.roll(10);

	game.roll(5);
	game.roll(5);

	game.roll(10);

	game.roll(8);
	game.roll(2);

	game.roll(3);
	game.roll(2);

	game.roll(6);
	game.roll(3);

	game.roll(3);
	game.roll(3);

	game.roll(3);
	game.roll(7);

	game.roll(3);

	REQUIRE(game.getScore() == 133);
}

TEST_CASE("FullTestCase2")
{
	BowlingGame game;

	game.roll(4);
	game.roll(2);

	game.roll(6);
	game.roll(4);

	game.roll(10);

	game.roll(6);
	game.roll(2);

	game.roll(3);
	game.roll(7);

	game.roll(4);
	game.roll(1);

	game.roll(8);
	game.roll(2);

	game.roll(3);
	game.roll(1);

	game.roll(10);

	game.roll(10);

	game.roll(3);
	game.roll(7);

	REQUIRE(game.getScore() == 131);
}

TEST_CASE("FullTestCase3")
{
	BowlingGame game;

	for(int i = 0; i < 16; ++i)
		game.roll(0);

	game.roll(7);
	game.roll(3);

	game.roll(7);
	game.roll(3);

	game.roll(10);

	REQUIRE(game.getScore() == 37);
}
