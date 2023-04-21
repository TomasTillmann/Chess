#include "../Chess/Chess.hpp"
#include <queue>
#include <vector>

position_t position3 = position_t(Color::White);

void setup_position3()
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
	setup_position3();
	position3 = position3.make_move(move_t::h("g2g4"));
	//position3 = position3.make_move(move_t::h("f4f3"));
	//position3 = position3.make_move(move_t::h("g2g3"));

	//std::vector<std::string> args = std::vector<std::string>(argv + 1, argv + argc);
	//int depth = stoi(args[0]);
	int depth = 1;

	//position_t position = position_t::get_starting();

	//position = position
	//	.make_move(move_t(square_t(3, 1), square_t(3, 2)))
	//	.make_move(move_t(square_t(2, 6), square_t(2, 5)))
	//	.make_move(move_t(square_t(4, 0), square_t(3, 1)))
	//	.make_move(move_t(square_t(3, 7), square_t(0,4)));

	std::cout << position3 << std::endl << std::endl;

	std::size_t count = perft(position3, depth);
	std::cout << "depth " << depth << ": " << count << std::endl;
	std::cout << std::endl;
}
