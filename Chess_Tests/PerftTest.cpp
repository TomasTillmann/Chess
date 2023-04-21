#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"
#include <queue>
#include <vector>

// Positions taken from here
// https://www.chessprogramming.org/Perft_Results
class PerftTest : public ::testing::Test {
private:
	int perft_rec(const position_t& position, int depth) {
		//std::cout << position << std::endl;

		if (depth <= 0) {
			return 1;
		}

		std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(position);
		std::size_t sum = 0;
		std::size_t count;

		for (auto&& move : legal_moves) {
			count = perft_rec(position.make_move(move), depth - 1);
			sum += count;
		}

		return sum;
	}

	void position3_setup()
	{
		position3.place(square_t::h("a5"), Piece::King | Color::White);
		position3.place(square_t::h("b5"), Piece::Pawn | Color::White);
		position3.place(square_t::h("b4"), Piece::Rook | Color::White);
		position3.place(square_t::h("e2"), Piece::Pawn | Color::White);
		position3.place(square_t::h("g2"), Piece::Pawn | Color::White);

		position3.place(square_t::h("c7"), Piece::Pawn | Color::Black);
		position3.place(square_t::h("d6"), Piece::Pawn | Color::Black);
		position3.place(square_t::h("f4"), Piece::Pawn | Color::Black);
		position3.place(square_t::h("h4"), Piece::King | Color::Black);
		position3.place(square_t::h("h5"), Piece::Rook | Color::Black);

		position3.add_info(PositionInfo::Wking_moved);
		position3.add_info(PositionInfo::Bking_moved);
	}

protected:
	position_t position3 = position_t(Color::White);

	void SetUp() override {
		position3_setup();
	}

	int perft(const position_t& position, int depth) {
		std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(position);
		std::size_t sum = 0;
		std::size_t count;

		for (auto&& move : legal_moves) {
			count = perft_rec(position.make_move(move), depth - 1);
			sum += count;
			std::cout << move << ": " << count << std::endl;
		}

		return sum;
	}
};

TEST_F(PerftTest, Position_3_depth_1)
{
	int actual = perft(position3, 1);

	ASSERT_EQ(14, actual);
}

TEST_F(PerftTest, Position_3_depth_2)
{
	int actual = perft(position3, 2);

	ASSERT_EQ(191, actual);
}

TEST_F(PerftTest, Position_3_depth_3)
{
	int actual = perft(position3, 3);

	ASSERT_EQ(2812, actual);
}

TEST_F(PerftTest, Position_3_depth_4)
{
	int actual = perft(position3, 4);

	ASSERT_EQ(43238, actual);
}

TEST_F(PerftTest, Position_3_depth_5)
{
	int actual = perft(position3, 5);

	ASSERT_EQ(674624, actual);
}

TEST_F(PerftTest, en_passant)
{
	position3 = position3.make_move(move_t::h("e2e4"));
	position3 = position3.make_move(move_t::h("f4f3"));
	position3 = position3.make_move(move_t::h("g2g3"));

	int actual = perft(position3, 1);

	ASSERT_EQ(4, actual);
}
