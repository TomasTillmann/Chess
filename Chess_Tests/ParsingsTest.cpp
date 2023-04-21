#include "pch.h"
#include "gtest/gtest.h"
#include "../Chess/Chess.hpp"
#include "TestUtils.hpp"

class ParsingsTest : public ::testing::Test {
};

TEST_F(ParsingsTest, square_t_parsing_a1)
{
	square_t sq = square_t::h("a1");
	square_t expected = square_t(0, 0);

	ASSERT_EQ(expected, sq);
}

TEST_F(ParsingsTest, square_t_parsing_a8)
{
	square_t sq = square_t::h("a8");
	square_t expected = square_t(0, 7);

	ASSERT_EQ(expected, sq);
}

TEST_F(ParsingsTest, square_t_parsing_h1)
{
	square_t sq = square_t::h("h1");
	square_t expected = square_t(7, 0);

	ASSERT_EQ(expected, sq);
}

TEST_F(ParsingsTest, square_t_parsing_h8)
{
	square_t sq = square_t::h("h8");
	square_t expected = square_t(7, 7);

	ASSERT_EQ(expected, sq);
}

TEST_F(ParsingsTest, square_t_parsing_d4)
{
	square_t sq = square_t::h("d4");
	square_t expected = square_t(3, 3);

	ASSERT_EQ(expected, sq);
}

TEST_F(ParsingsTest, move_t_parsing_a1a8)
{
	move_t actual = move_t::h("a1a8");
	move_t expected = move_t(square_t::h("a1"), square_t::h("a8"));

	ASSERT_EQ(expected, actual);
}
