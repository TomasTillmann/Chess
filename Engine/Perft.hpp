#ifndef PERFT_HPP
#define PERFT_HPP

#include "../Chess/Chess.hpp"

class Perft {
private:
	inline static int perft_rec(const Position& position, int depth) {
		if (depth <= 0) {
			return 1;
		}

		std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(position);
		std::size_t sum = 0;
		std::size_t count;

		for (auto&& move : legal_moves) {
			count = perft_rec(position.cmake_move(move), depth - 1);
			sum += count;
		}

		return sum;
	}

public:
	inline static int go(const Position& position, int depth, bool print) {
		std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(position);
		std::size_t sum = 0;
		std::size_t count;

		for (auto&& move : legal_moves) {
			count = perft_rec(position.cmake_move(move), depth - 1);
			sum += count;
			if(print)
				std::cout << move << ": " << count << std::endl;
		}

		if(print)
			std::cout << "searched nodes in depth " << depth << ": " << sum << std::endl;
		return sum;
	}
};

#endif
