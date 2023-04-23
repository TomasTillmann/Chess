#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "../Chess/Chess.hpp"

class Evaluator {
public:
	int fast_evaluate(const Position& position) const;

	int full_evaluate(const Position& position) const;

	int evaluate_piece_score(const Position& position, square_t square) const;

private:
	int piece_cost(piece_t piece) const;

	int piece_positioning_cost(const Position& position, piece_t piece, square_t square) const;

	int evaluate_defending_score(const Position& position, square_t square) const;

	int evaluate_mobility(const Position& position) const;

	int evaluate_attacking_penalty(const Position& position, square_t square) const;

	int evaluate_enprise_penalty(const Position& position, square_t square) const;

	inline static int get_table_index(square_t square, color_t player) {
		int white_index = Position::from_square(square);
		return player == Color::White ? white_index : 63 - white_index;
	}

	std::vector<short> _pawn_table = std::vector<short>
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		50, 50, 50, 50, 50, 50, 50, 50,
		10, 10, 20, 30, 30, 20, 10, 10,
		5, 5, 10, 27, 27, 10, 5, 5,
		0, 0, 0, 25, 25, 0, 0, 0,
		5, -5, -10, 0, 0, -10, -5, 5,
		5, 10, 10, -25, -25, 10, 10, 5,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	std::vector<short> _knight_table = std::vector<short>
	{
		-50, -40, -30, -30, -30, -30, -40, -50,
		-40, -20, 0, 0, 0, 0, -20, -40,
		-30, 0, 10, 15, 15, 10, 0, -30,
		-30, 5, 15, 20, 20, 15, 5, -30,
		-30, 0, 15, 20, 20, 15, 0, -30,
		-30, 5, 10, 15, 15, 10, 5, -30,
		-40, -20, 0, 5, 5, 0, -20, -40,
		-50, -40, -20, -30, -30, -20, -40, -50,
	};

	std::vector<short> _bishop_table = std::vector<short>
	{
		-20, -10, -10, -10, -10, -10, -10, -20,
		-10, 0, 0, 0, 0, 0, 0, -10,
		-10, 0, 5, 10, 10, 5, 0, -10,
		-10, 5, 5, 10, 10, 5, 5, -10,
		-10, 0, 10, 10, 10, 10, 0, -10,
		-10, 10, 10, 10, 10, 10, 10, -10,
		-10, 5, 0, 0, 0, 0, 5, -10,
		-20, -10, -40, -10, -10, -40, -10, -20,
	};

	std::vector<short> _king_table = std::vector<short> 
	{
		-30, -40, -40, -50, -50, -40, -40, -30,
		-30, -40, -40, -50, -50, -40, -40, -30,
		-30, -40, -40, -50, -50, -40, -40, -30,
		-30, -40, -40, -50, -50, -40, -40, -30,
		-20, -30, -30, -40, -40, -30, -30, -20,
		-10, -20, -20, -20, -20, -20, -20, -10,
		20, 20, 0, 0, 0, 0, 20, 20,
		20, 30, 10, 0, 0, 10, 30, 20
	};

	std::vector<short> _king_table_endgame = std::vector<short> 
	{
		-50, -40, -30, -20, -20, -30, -40, -50,
		-30, -20, -10, 0, 0, -10, -20, -30,
		-30, -10, 20, 30, 30, 20, -10, -30,
		-30, -10, 30, 40, 40, 30, -10, -30,
		- 30, -10, 30, 40, 40, 30, -10, -30,
		-30, -10, 20, 30, 30, 20, -10, -30,
		-30, -30, 0, 0, 0, 0, -30, -30,
		-50, -30, -30, -30, -30, -30, -30, -50
	};
};

#endif