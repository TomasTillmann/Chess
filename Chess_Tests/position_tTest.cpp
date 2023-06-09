#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <set>

class Position_tTest : public ::testing::Test {
protected:
	Position position = Position(Color::White);
	Position new_position_expected = Position(Color::White);

	void SetUp() override {
		position.place(square_t(0, 1), Piece::King | Color::White);
		position.place(square_t(0, 3), Piece::King | Color::Black);
		new_position_expected = Position(position);
	}

	void clear_pos() {
		position.place(square_t(0, 1), Piece::None);
		position.place(square_t(0, 3), Piece::None);
		new_position_expected = Position(position);
	}
};

TEST_F(Position_tTest, make_move_normal) {
	piece_t piece = Piece::Rook | Color::White;

	position.place(square_t(4, 4), piece);
	move_t move = move_t(square_t(4, 4), square_t(4, 6));

	new_position_expected.place(move.to(), piece);

	Position new_position_actual = position.cmake_move(move);

	ASSERT_EQ(new_position_expected, new_position_actual) << "Expected:\n" << new_position_expected << "Actual:\n" << new_position_actual << std::endl;
}

TEST_F(Position_tTest, make_move_castle_short_white) {
	position.place(square_t(0, 1), Piece::None);
	new_position_expected = Position(position);

	position.place(square_t(4, 0), Piece::King | Color::White);
	position.place(square_t(7, 0), Piece::Rook | Color::White);

	move_t move = move_t(square_t(4, 0), square_t(6, 0), MoveType::Castle);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(6, 0), Piece::King | Color::White);
	new_position_expected.place(square_t(5, 0), Piece::Rook | Color::White);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_castle_long_white) {
	position.place(square_t(0, 1), Piece::None);
	new_position_expected = Position(position);

	position.place(square_t(4, 0), Piece::King | Color::White);
	position.place(square_t(0, 0), Piece::Rook | Color::White);

	move_t move = move_t(square_t(4, 0), square_t(2, 0), MoveType::Castle);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(2,0), Piece::King | Color::White);
	new_position_expected.place(square_t(3,0), Piece::Rook | Color::White);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_castle_short_black) {
	position.place(square_t(0, 3), Piece::None);
	new_position_expected = Position(position);

	position.place(square_t(4, 7), Piece::King | Color::Black);
	position.place(square_t(7, 7), Piece::Rook | Color::Black);

	move_t move = move_t(square_t(4, 7), square_t(6, 7), MoveType::Castle);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(6, 7), Piece::King | Color::Black);
	new_position_expected.place(square_t(5, 7), Piece::Rook | Color::Black);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_castle_long_black) {
	position.place(square_t(0, 3), Piece::None);
	new_position_expected = Position(position);

	position.place(square_t(4, 7), Piece::King | Color::Black);
	position.place(square_t(0, 7), Piece::Rook | Color::Black);

	move_t move = move_t(square_t(4, 7), square_t(2, 7), MoveType::Castle);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(2,7), Piece::King | Color::Black);
	new_position_expected.place(square_t(3,7), Piece::Rook | Color::Black);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_enpassant_white) {
	new_position_expected = Position(position);
	position.place(square_t(4, 4), Piece::Pawn | Color::White);
	position.place(square_t(3, 4), Piece::Pawn | Color::Black);


	move_t move = move_t(square_t(4, 4), square_t(3, 5), MoveType::EnPassant);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(3, 5), Piece::Pawn | Color::White);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_enpassant_black) {
	new_position_expected = Position(position);
	position.place(square_t(4, 3), Piece::Pawn | Color::Black);
	position.place(square_t(3, 3), Piece::Pawn | Color::White);

	move_t move = move_t(square_t(4, 3), square_t(3, 2), MoveType::EnPassant);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(3, 2), Piece::Pawn | Color::Black);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_promotion_white) {
	new_position_expected = Position(position);
	position.place(square_t(4, 6), Piece::Pawn | Color::White);

	move_t move = move_t(square_t(4, 6), square_t(4, 7), MoveType::Promotion | Piece::Queen);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(4, 7), Piece::Queen | Color::White);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, make_move_promotion_black) {
	new_position_expected = Position(position);
	position.place(square_t(4, 1), Piece::Pawn | Color::Black);

	move_t move = move_t(square_t(4, 1), square_t(4, 0), MoveType::Promotion | Piece::Bishop);
	Position new_position_actual = position.cmake_move(move);

	new_position_expected.place(square_t(4, 0), Piece::Bishop | Color::Black);
	ASSERT_EQ(new_position_expected, new_position_actual);
}

TEST_F(Position_tTest, is_stalemate) {
	clear_pos();
	position.place(square_t(7, 0), Piece::King | Color::White);
	position.place(square_t(7, 2), Piece::King | Color::Black);

	position.place(square_t(6, 5), Piece::Rook | Color::Black);
	position.add_info(PositionInfo::Wking_moved);

	EXPECT_TRUE(position.is_stalemate());
}
