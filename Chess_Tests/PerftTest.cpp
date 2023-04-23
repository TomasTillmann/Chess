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
	int perft_rec(const Position& position, int depth) {
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

	void position2_setup()
	{
		position2.place(square_t::h("a2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("b2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("c2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("d5"), Piece::Pawn | Color::White);
		position2.place(square_t::h("e4"), Piece::Pawn | Color::White);
		position2.place(square_t::h("f2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("g2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("h2"), Piece::Pawn | Color::White);
		position2.place(square_t::h("a1"), Piece::Rook | Color::White);
		position2.place(square_t::h("c3"), Piece::Knight | Color::White);
		position2.place(square_t::h("d2"), Piece::Bishop | Color::White);
		position2.place(square_t::h("e2"), Piece::Bishop | Color::White);
		position2.place(square_t::h("e5"), Piece::Knight | Color::White);
		position2.place(square_t::h("f3"), Piece::Queen | Color::White);
		position2.place(square_t::h("e1"), Piece::King | Color::White);
		position2.place(square_t::h("h1"), Piece::Rook | Color::White);

		position2.place(square_t::h("a7"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("b4"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("c7"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("d7"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("e6"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("f7"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("g6"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("h3"), Piece::Pawn | Color::Black);
		position2.place(square_t::h("a8"), Piece::Rook | Color::Black);
		position2.place(square_t::h("a6"), Piece::Bishop | Color::Black);
		position2.place(square_t::h("b6"), Piece::Knight | Color::Black);
		position2.place(square_t::h("e7"), Piece::Queen | Color::Black);
		position2.place(square_t::h("e8"), Piece::King | Color::Black);
		position2.place(square_t::h("f6"), Piece::Knight | Color::Black);
		position2.place(square_t::h("g7"), Piece::Bishop | Color::Black);
		position2.place(square_t::h("h8"), Piece::Rook | Color::Black);
	}

	void position5_setup()
	{
		position5.place(square_t::h("a2"), Piece::Pawn | Color::White);
		position5.place(square_t::h("b2"), Piece::Pawn | Color::White);
		position5.place(square_t::h("c2"), Piece::Pawn | Color::White);
		position5.place(square_t::h("d7"), Piece::Pawn | Color::White);
		position5.place(square_t::h("g2"), Piece::Pawn | Color::White);
		position5.place(square_t::h("h2"), Piece::Pawn | Color::White);
		position5.place(square_t::h("a1"), Piece::Rook | Color::White);
		position5.place(square_t::h("b1"), Piece::Knight | Color::White);
		position5.place(square_t::h("c1"), Piece::Bishop | Color::White);
		position5.place(square_t::h("c4"), Piece::Bishop | Color::White);
		position5.place(square_t::h("d1"), Piece::Queen | Color::White);
		position5.place(square_t::h("e2"), Piece::Knight | Color::White);
		position5.place(square_t::h("h1"), Piece::Rook | Color::White);
		position5.place(square_t::h("e1"), Piece::King | Color::White);

		position5.place(square_t::h("a7"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("b7"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("c6"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("f7"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("g7"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("h7"), Piece::Pawn | Color::Black);
		position5.place(square_t::h("a8"), Piece::Rook | Color::Black);
		position5.place(square_t::h("b8"), Piece::Knight | Color::Black);
		position5.place(square_t::h("c8"), Piece::Bishop | Color::Black);
		position5.place(square_t::h("d8"), Piece::Queen | Color::Black);
		position5.place(square_t::h("e7"), Piece::Bishop | Color::Black);
		position5.place(square_t::h("f8"), Piece::King | Color::Black);
		position5.place(square_t::h("h8"), Piece::Rook | Color::Black);
		position5.place(square_t::h("f2"), Piece::Knight | Color::Black);

		position5.add_info(PositionInfo::Bking_moved);
	}

protected:
	Position position2 = Position(Color::White);
	Position position3 = Position(Color::White);
	Position position5 = Position(Color::White);

	void SetUp() override {
		position2_setup();
		position3_setup();
		position5_setup();
	}

	int perft(const Position& position, int depth) {
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
	//ASSERT_TRUE(false) << "takes long - not run" << std::endl;
}

TEST_F(PerftTest, Position_3_en_passant)
{
	position3 = position3.make_move(move_t::h("e2e4"));
	position3 = position3.make_move(move_t::h("f4f3"));
	position3 = position3.make_move(move_t::h("g2g3"));

	int actual = perft(position3, 1);

	ASSERT_EQ(4, actual);
}

TEST_F(PerftTest, Position_2_depth_1)
{
	int actual = perft(position2, 1);

	ASSERT_EQ(48, actual);
}

TEST_F(PerftTest, Position_2_depth_2)
{
	int actual = perft(position2, 2);

	ASSERT_EQ(2039, actual);
}

TEST_F(PerftTest, Position_2_depth_3)
{
	int actual = perft(position2, 3);

	ASSERT_EQ(97862, actual);
}

TEST_F(PerftTest, Position_2_depth_4)
{
	// int actual = perft(position2, 4);

	// ASSERT_EQ(4085603, actual);

	ASSERT_TRUE(false) << "takes too long - not run" << std::endl;
}

TEST_F(PerftTest, Position_5_depth_1)
{
	std::cout << position5 << std::endl;
	int actual = perft(position5, 1);

	ASSERT_EQ(44, actual);
}

TEST_F(PerftTest, Position_5_depth_2)
{
	std::cout << position5 << std::endl;
	int actual = perft(position5, 2);

	ASSERT_EQ(1486, actual);
}

TEST_F(PerftTest, Position_5_depth_3)
{
	std::cout << position5 << std::endl;
	int actual = perft(position5, 3);

	ASSERT_EQ(62379, actual);
}

TEST_F(PerftTest, Position_5_depth_4)
{
	//std::cout << position5 << std::endl;
	//int actual = perft(position5, 4);

	//ASSERT_EQ(2103487, actual);
	ASSERT_TRUE(false) << "runs for 10 mins";
}
