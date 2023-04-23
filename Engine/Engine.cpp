#include "Engine.hpp"

int EngineMinimax::evaluate(const Position& position, int depth) const {
	int fast_evaluate = minimax(position, depth, position.to_play() == Color::White, INT_MIN, INT_MAX);

	// black has forced win
	if (fast_evaluate == INT_MIN) {
		return -1;
	}
	// white has forced win
	else if (fast_evaluate == INT_MAX) {
		return 1;
	}

	return damp(fast_evaluate);
}

std::vector<move_t> EngineMinimax::get_next_moves(const Position& position) const {
	std::vector<move_t> next_moves = MoveGenerator::generate_legal_moves(position);

	std::sort(next_moves.begin(), next_moves.end(), [&](move_t move_a, move_t move_b) {
		Position a_pos = position.cmake_move(move_a);
		Position b_pos = position.cmake_move(move_b);
		return position.to_play() == Color::White ? fast_evaluate(a_pos) > fast_evaluate(b_pos) : fast_evaluate(a_pos) < fast_evaluate(b_pos);
		});

	return next_moves;
}

int EngineMinimax::fast_evaluate(const Position& position) const {
	return _evaluator.fast_evaluate(position);
}

int EngineMinimax::full_evaluate(const Position& position) const {
	return _evaluator.full_evaluate(position);
}

int EngineMinimax::minimax(const Position& position, bool depth, bool is_maximizing_player, int alpha, int beta) const {
	if (position.is_over() || depth == 0) {
		return full_evaluate(position);
	}

	int best_eval;
	int fast_evaluate;
	std::vector<move_t> next_moves;

	if (is_maximizing_player) {
		best_eval = INT_MIN;
		next_moves = get_next_moves(position);
		for (auto&& next_move : next_moves) {
			Position next_position = position.cmake_move(next_move);
			fast_evaluate = minimax(next_position, depth - 1, false, alpha, beta);
			best_eval = std::max(best_eval, fast_evaluate);

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
			fast_evaluate = minimax(next_position, depth - 1, true, alpha, beta);
			best_eval = std::min(best_eval, fast_evaluate);

			beta = std::min(beta, best_eval);
			if (beta <= alpha) {
				break;
			}
		}

		return best_eval;
	}
}

double EngineMinimax::damp(double value) const {
	return 2 * sigmoid(value) - 1;
}

double EngineMinimax::sigmoid(double value) const {
	return 1 / (1 + std::exp(-value));
}
