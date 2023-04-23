#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <algorithm>
#include <cmath>
#include "../Chess/Chess.hpp"
#include "Evaluator.hpp"

class Engine {
public:
	/// <summary>
	/// Returns value in (-1,1) interval
	/// Numbers closer to -1 indicate black is better.
	/// Numbers closer to 1 indicate white is better.
	/// Values around zero indicate equality.
	/// </summary>
	/// <param name="position">Position to evaluate.</param>
	/// <param name="depth">Evaluation depth.</param>
	virtual int evaluate(const Position& position, int depth) const = 0;
};

class EngineMinimax : Engine {
private:
	Evaluator _evaluator;

public:
	int evaluate(const Position& position, int depth) const;

private:
	/// <summary>
	/// Since minimax with alpha beta pruning is used, it is extremely important to order the positions in a good order.
	/// This means to explore positions after good move first.
	/// </summary>
	/// <param name="position"></param>
	/// <param name="next_positions"></param>
	std::vector<move_t> get_next_moves(const Position& position) const;

	int fast_evaluate(const Position& position) const;

	int full_evaluate(const Position& position) const;

	double damp(double value) const;

	double sigmoid(double value) const;

	int minimax(const Position& position, bool depth, bool is_maximizing_player, int alpha, int beta) const;
};

#endif
