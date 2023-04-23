#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class PawnTest : public ::testing::Test {
protected:
	Position position = Position(Color::White);

	void SetUp() override {
		position.place(square_t(0,0), Piece::King | Color::Black);
		position.place(square_t(2,0), Piece::King | Color::White);
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
	ASSERT_CONTAINER_EQ(expected, actual);
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
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_white_starting_rank) {
	square_t origin = square_t(4, 1);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,2)),
		move_t(origin, square_t(4,3)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_white_starting_rank_blocked) {
	square_t origin = square_t(4, 1);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);
	position.place(square_t(4,3), Piece::Pawn | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,2)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_white_take) {
	square_t origin = square_t(4, 1);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);
	position.place(square_t(3,2), Piece::Pawn | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4,2)),
		move_t(origin, square_t(4,3)),
		move_t(origin, square_t(3,2)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_pin_white) {
	square_t origin = square_t(2, 1);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);
	position.place(square_t(3,2), Piece::Pawn | Color::Black);
	position.place(square_t(2,3), Piece::Rook | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(2,2)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_side_white) {
	square_t origin = square_t(0, 1);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);
	position.place(square_t(1,2), Piece::Pawn | Color::Black);

	std::vector<move_t> expected = {
		move_t(origin, square_t(1,2)),
		move_t(origin, square_t(0,2)),
		move_t(origin, square_t(0,3)),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_promotion_white) {
	square_t origin = square_t(4, 6);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);

	std::vector<move_t> expected = {
		move_t(origin, square_t(4, 7), MoveType::Promotion | Piece::Queen),
		move_t(origin, square_t(4, 7), MoveType::Promotion | Piece::Bishop),
		move_t(origin, square_t(4, 7), MoveType::Promotion | Piece::Knight),
		move_t(origin, square_t(4, 7), MoveType::Promotion | Piece::Rook),
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}

TEST_F(PawnTest, get_legal_moves_enpassant_white) {
	square_t origin = square_t(4, 4);
	piece_t wpawn = Piece::Pawn | Color::White;

	position.place(origin, wpawn);
	position.place(square_t(3,6), Piece::Pawn | Color::Black);
	position = position.cmake_move(move_t(square_t(3, 6), square_t(3, 4)));

	std::vector<move_t> expected = {
		move_t(origin, square_t(3, 5), MoveType::EnPassant),
		move_t(origin, square_t(4, 5))
	};

	std::vector<move_t> actual = MoveGenerator::generate_legal_moves(position, origin);
	ASSERT_CONTAINER_EQ(expected, actual);
}
