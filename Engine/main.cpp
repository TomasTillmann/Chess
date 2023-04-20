#include "../Chess/Chess.hpp"
#include <queue>
#include <vector>

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

int main(int argc, char** argv) {
	std::vector<std::string> args = std::vector<std::string>(argv + 1, argv + argc);
	int depth = stoi(args[0]);

	position_t position = position_t::get_starting();
	//position = position
	//	.make_move(move_t(square_t(1, 0), square_t(0,2)))
	//	.make_move(move_t(square_t(0, 6), square_t(0,5)));

	std::cout << position << std::endl << std::endl;

	std::size_t count = perft(position, depth);
	std::cout << "depth " << depth << ": " << count << std::endl;
	std::cout << std::endl;
}
