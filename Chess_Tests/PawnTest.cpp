#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class PawnTest : public ::testing::Test {
protected:
	position_t position = position_t(Color::White);

	void SetUp() override {
		position.place(square_t(0,0), Piece::King | Color::Black);
	}
};

TEST_F(PawnTest, get_attacked_squares_white) {
	square_t origin = square_t(4, 4);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);

	std::set<square_t> expected = {
		square_t(5,5),
		square_t(3,5),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(expected, actual);
}

TEST_F(PawnTest, get_attacked_squares_black) {
	square_t origin = square_t(4, 4);
	piece_t bpawn = Piece::Pawn | Color::Black;

	position.place(origin, bpawn);

	std::set<square_t> expected = {
		square_t(3,3),
		square_t(5,3),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(expected, actual);

}
