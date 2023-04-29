#include "Engine.hpp"

int EngineMinimax::evaluate(const Position& position, int depth) const {
	int eval = minimax(position, depth, position.to_play() == Color::White, INT_MIN, INT_MAX);
	return eval;
}

void EngineMinimax::moves_distribution(const Position& position, std::vector<move_t>& moves, std::vector<double>& scores, int depth) const {
	 moves = MoveGenerator::generate_legal_moves(position);
	 scores.resize(moves.size());

	 // TODO: can paralelize
	 for (std::size_t i = 0; i < moves.size(); ++i)
	 {
		 double score = evaluate(position.cmake_move(moves[i]), depth - 1);
		 scores[i] = score;
	 }

	 // normalize
	 double sum = 0;
	 for (std::size_t i = 0; i < scores.size(); ++i)
	 {
		 sum += scores[i];
	 }

	 for (std::size_t i = 0; i < scores.size(); ++i)
	 {
		 scores[i] /= sum;
	 }
	 //
}


std::vector<move_t> EngineMinimax::get_next_moves(const Position& position) const {
	std::vector<move_t> next_moves = MoveGenerator::generate_legal_moves(position);

	std::sort(next_moves.begin(), next_moves.end(), [&](const move_t& move_a, const move_t& move_b) {
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

int EngineMinimax::minimax(const Position& position, int depth, bool is_maximizing_player, int alpha, int beta) const {
	if (position.is_over() || depth == 0) {
		return full_evaluate(position);
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
