#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class PositionHandlerTest : public ::testing::Test {
protected:
	Position position = Position(Color::White);

	void SetUp() override {
		position.place(square_t(4,4), Piece::King | Color::Black);
		position.place(square_t(1,0), Piece::King | Color::White);
	}
};

TEST_F(PositionHandlerTest, get_all_squares_attacked_by_black) {
	position.place(square_t(3,0), Piece::Rook | Color::Black);

	std::set<square_t> expected = {
		square_t(4,5),
		square_t(5,5),
		square_t(5,4),
		square_t(5,3),
		square_t(4,3),
		square_t(3,3),
		square_t(3,4),
		square_t(3,5),

		square_t(2,0),
		square_t(1,0),

		square_t(3,1),
		square_t(3,2),
		square_t(3,6),
		square_t(3,7),

		square_t(4,0),
		square_t(5,0),
		square_t(6,0),
		square_t(7,0),
	};

	std::set<square_t> actual = PositionHandler::get_attacked_squares(position, Color::Black);
	ASSERT_CONTAINER_EQ(expected, actual);
}
