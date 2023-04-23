#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class QueenTest : public ::testing::Test {
protected:
	Position position = Position(Color::White);

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
	ASSERT_CONTAINER_EQ(expected, actual);
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
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(QueenTest, get_legal_moves_friendly_obstacles) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);
	position.place(square_t(5, 5), Piece::Knight | Color::White);
	position.place(square_t(3, 4), Piece::Rook | Color::White);
	position.place(square_t(2, 2), Piece::Bishop | Color::White);
	position.place(square_t(7, 1), Piece::Rook | Color::White);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,5)),
		move_t(origin, square_t(4,6)),
		move_t(origin, square_t(4,7)),

		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(6,4)),
		move_t(origin, square_t(7,4)),

		move_t(origin, square_t(5,3)),
		move_t(origin, square_t(6,2)),

		move_t(origin, square_t(4,3)),
		move_t(origin, square_t(4,2)),
		move_t(origin, square_t(4,1)),
		move_t(origin, square_t(4,0)),

		move_t(origin, square_t(3,3)),

		move_t(origin, square_t(3,5)),
		move_t(origin, square_t(2,6)),
		move_t(origin, square_t(1,7)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(QueenTest, get_legal_moves_enemy_obstacles) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);
	position.place(square_t(5, 5), Piece::Knight | Color::Black);
	position.place(square_t(3, 4), Piece::Rook | Color::Black);
	position.place(square_t(2, 2), Piece::Bishop | Color::Black);
	position.place(square_t(7, 1), Piece::Knight | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,5)),
		move_t(origin, square_t(4,6)),
		move_t(origin, square_t(4,7)),

		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(6,4)),
		move_t(origin, square_t(7,4)),

		move_t(origin, square_t(5,3)),
		move_t(origin, square_t(6,2)),

		move_t(origin, square_t(4,3)),
		move_t(origin, square_t(4,2)),
		move_t(origin, square_t(4,1)),
		move_t(origin, square_t(4,0)),

		move_t(origin, square_t(3,3)),

		move_t(origin, square_t(3,5)),
		move_t(origin, square_t(2,6)),
		move_t(origin, square_t(1,7)),

		move_t(origin, square_t(5,5)),
		move_t(origin, square_t(3,4)),
		move_t(origin, square_t(2,2)),
		move_t(origin, square_t(7,1)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(QueenTest, get_legal_moves_in_pin) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);
	position.place(square_t(0, 1), Piece::None);
	position.place(square_t(7, 4), Piece::King | Color::White);
	position.place(square_t(1, 4), Piece::Rook | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(1,4)),
		move_t(origin, square_t(2,4)),
		move_t(origin, square_t(3,4)),
		move_t(origin, square_t(5,4)),
		move_t(origin, square_t(6,4)),

	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(QueenTest, get_legal_moves_capture_or_interfere_checking_piece) {
	square_t origin = square_t(4, 4);
	piece_t queen = Piece::Queen | Color::White;

	position.place(origin, queen);
	position.place(square_t(7, 1), Piece::Rook | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(1,1)),
		move_t(origin, square_t(4,1)),
		move_t(origin, square_t(7,1)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}
