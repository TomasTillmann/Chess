#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class QueenTest : public ::testing::Test {
protected:
	position_t position = position_t(Color::White);

	void SetUp() override {
		position.place(square_t(0, 1), Piece::King | Color::White);
		position.place(square_t(0, 3), Piece::King | Color::Black);
	}
};

TEST_F(QueenTest, get_attacked_squares_free) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);

	std::set<square_t> expected = {
		square_t(4,5),
		square_t(4,6),
		square_t(4,7),

		square_t(5,5),
		square_t(6,6),
		square_t(7,7),

		square_t(5,4),
		square_t(6,4),
		square_t(7,4),

		square_t(5,3),
		square_t(6,2),
		square_t(7,1),

		square_t(4,3),
		square_t(4,2),
		square_t(4,1),
		square_t(4,0),

		square_t(3,3),
		square_t(2,2),
		square_t(1,1),
		square_t(0,0),

		square_t(3,4),
		square_t(2,4),
		square_t(1,4),
		square_t(0,4),

		square_t(3,5),
		square_t(2,6),
		square_t(1,7),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(actual, expected);
}

TEST_F(QueenTest, get_attacked_squares_friendly_obstacles) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);
	position.place(square_t(5, 5), Piece::Knight | Color::White);
	position.place(square_t(3, 4), Piece::Rook | Color::White);
	position.place(square_t(2, 2), Piece::Bishop | Color::White);
	position.place(square_t(7, 1), Piece::Rook | Color::White);

	std::set<square_t> expected = {
		square_t(4,5),
		square_t(4,6),
		square_t(4,7),

		square_t(5,5),

		square_t(5,4),
		square_t(6,4),
		square_t(7,4),

		square_t(5,3),
		square_t(6,2),
		square_t(7,1),

		square_t(4,3),
		square_t(4,2),
		square_t(4,1),
		square_t(4,0),

		square_t(3,3),
		square_t(2,2),

		square_t(3,4),

		square_t(3,5),
		square_t(2,6),
		square_t(1,7),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(actual, expected);
}
