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
	ASSERT_CONTAINER_EQ(expected, actual);
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
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KingTest, get_legal_moves_free) {
	square_t origin = square_t(4, 4);
	piece_t wking = Piece::King | Color::White;
	position.place(origin, wking);
	position.add_info(PositionInfo::Wking_moved);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,5)),
		move_t(origin, square_t(5,5)),
		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(5,3)),
		move_t(origin, square_t(4,3)),
		move_t(origin, square_t(3,3)),
		move_t(origin, square_t(3,4)),
		move_t(origin, square_t(3,5)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KingTest, get_legal_moves_friendly_obstacles) {
	square_t origin = square_t(4, 4);
	piece_t wking = Piece::King | Color::White;
	position.place(origin, wking);
	position.place(square_t(5,5), Piece::Bishop | Color::White);
	position.place(square_t(4,3), Piece::Queen | Color::White);
	position.add_info(PositionInfo::Wking_moved);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,5)),
		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(5,3)),
		move_t(origin, square_t(3,3)),
		move_t(origin, square_t(3,4)),
		move_t(origin, square_t(3,5)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KingTest, get_legal_moves_board_side) {
	square_t origin = square_t(0, 4);
	piece_t wking = Piece::King | Color::White;
	position.place(origin, wking);
	position.add_info(PositionInfo::Wking_moved);

	std::vector<move_t> expected = {
		move_t(origin, square_t(0,5)),
		move_t(origin, square_t(0,3)),
		move_t(origin, square_t(1,4)),
		move_t(origin, square_t(1,5)),
		move_t(origin, square_t(1,3)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KingTest, get_legal_moves_attacked_squares) {
	square_t origin = square_t(4, 4);
	piece_t wking = Piece::King | Color::White;
	position.place(origin, wking);

	position.place(square_t(3, 0), Piece::Rook | Color::Black);
	position.place(square_t(7, 3), Piece::Bishop | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,5)),
		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(5,3)),
		move_t(origin, square_t(4,3)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(KingTest, get_legal_moves_castling) {
	square_t origin = square_t(4, 0);
	piece_t wking = Piece::King | Color::White;
	position.place(origin, wking);

	position.place(square_t(0, 0), Piece::Rook | Color::White);
	position.place(square_t(7, 0), Piece::Rook | Color::White);

	std::vector<move_t> expected = {
		move_t(origin, square_t(6,0), MoveType::Castle),
		move_t(origin, square_t(2,0), MoveType::Castle),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}
