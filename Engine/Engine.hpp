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
	int evaluate(const Position& position, int depth) const {
		int eval = minimax(position, depth, position.to_play() == Color::White, INT_MIN, INT_MAX);

		// black has forced win
		if (eval == INT_MIN) {
			return -1;
		}
		// white has forced win
		else if (eval == INT_MAX) {
			return 1;
		}

		return damp(eval);
	}

private:
	/// <summary>
	/// Since minimax with alpha beta pruning is used, it is extremely important to order the positions in a good order.
	/// This means to explore positions after good move first.
	/// </summary>
	/// <param name="position"></param>
	/// <param name="next_positions"></param>
	std::vector<move_t> get_next_moves(const Position& position) const {
		std::vector<move_t> next_moves = MoveGenerator::generate_legal_moves(position);

		std::sort(next_moves.begin(), next_moves.end(), [&](const move_t& move_a, const move_t& move_b) {
			return eval(position.cmake_move(move_a)) < eval(position.cmake_move(move_b));
			});

		return next_moves;
	}

	int eval(const Position& position) const {
		return _evaluator.evaluate(position);
	}

	int minimax(const Position& position, bool depth, bool is_maximizing_player, int alpha, int beta) const {
		if (position.is_over() || depth == 0) {
			return eval(position);
		}

		int best_eval;
		int eval;
		std::vector<move_t> next_moves;

		if (is_maximizing_player) {
			best_eval = INT_MIN;
			next_moves = get_next_moves(position);
			for (auto&& next_move : next_moves) {
				Position next_position = position.cmake_move(next_move);
				eval = minimax(next_position, depth - 1, false, alpha, beta);
				best_eval = std::max(best_eval, eval);

				alpha = std::max(alpha, best_eval);
				if (beta <= alpha) {
					break;
				}
			}

			return best_eval;
		}
		else {
			best_eval = INT_MAX;
			next_moves = get_next_moves(position);
			for (auto&& next_move : next_moves) {
				Position next_position = position.cmake_move(next_move);
				eval = minimax(next_position, depth - 1, true, alpha, beta);
				best_eval = std::min(best_eval, eval);

				beta = std::min(beta, best_eval);
				if (beta <= alpha) {
					break;
				}
			}

			return best_eval;
		}
	}

	double damp(double value) const {
		return 2 * sigmoid(value) - 1;
	}

	double sigmoid(double value) const {
		return 1 / (1 + std::exp(-value));
	}
};

#endif
