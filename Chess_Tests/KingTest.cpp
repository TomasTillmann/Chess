#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class KingTest : public ::testing::Test {
protected:
	position_t position = position_t(Color::White);

	void SetUp() override {
		position.place(square_t(0,0), Piece::King | Color::Black);
	}
};

TEST_F(KingTest, get_attacked_squares_free_white) {
	square_t origin = square_t(4, 4);
	piece_t wking = Piece::King | Color::White;

	position.place(origin, wking);

	std::set<square_t> expected = {
		square_t(4,5),
		square_t(5,5),
		square_t(5,4),
		square_t(5,3),
		square_t(4,3),
		square_t(3,3),
		square_t(3,4),
		square_t(3,5),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(expected, actual);
}

TEST_F(KingTest, get_attacked_squares_friendly_obstacles_white) {
	square_t origin = square_t(0, 4);
	piece_t wking = Piece::King | Color::White;

	position.place(origin, wking);
	position.place(square_t(0,5), Piece::Knight | Color::White);
	position.place(square_t(1,4), Piece::Rook | Color::White);
	position.place(square_t(1,3), Piece::Bishop | Color::White);

	std::set<square_t> expected = {
		square_t(0,5),
		square_t(1,5),
		square_t(1,4),
		square_t(1,3),
		square_t(0,3),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_SET_EQ(expected, actual);

}

