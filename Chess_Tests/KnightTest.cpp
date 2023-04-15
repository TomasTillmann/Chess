#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class KnightTest : public ::testing::Test {
protected:
	position_t position = position_t(Color::White);

	void SetUp() override {
		position.place(square_t(0, 1), Piece::King | Color::White);
		position.place(square_t(0, 3), Piece::King | Color::Black);
	}
};

TEST_F(KnightTest, get_attacked_squares_free) {
	square_t origin = square_t(4, 4);
	piece_t knight = Piece::Knight | Color::White;

	position.place(origin, knight);

	std::set<square_t> expected = {
		square_t(5,6),
		square_t(3,6),
		square_t(6,5),
		square_t(6,3),
		square_t(5,2),
		square_t(3,2),
		square_t(2,3),
		square_t(2,5),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KnightTest, get_attacked_squares_friendly_obstacles) {
	square_t origin = square_t(4, 4);
	piece_t knight = Piece::Knight | Color::White;

	position.place(origin, knight);
	position.place(square_t(5, 6), Piece::Bishop | Color::White);
	position.place(square_t(3, 4), Piece::Rook | Color::White);
	position.place(square_t(2, 3), Piece::Knight | Color::White);
	position.place(square_t(7, 1), Piece::Rook | Color::White);

	std::set<square_t> expected = {
		square_t(3,6),
		square_t(6,5),
		square_t(6,3),
		square_t(5,2),
		square_t(3,2),
		square_t(2,5),
		square_t(5,6),
		square_t(2,3),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);

}
