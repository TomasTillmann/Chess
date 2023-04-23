#include "../Chess/Chess.hpp"
#include <queue>
#include <vector>

Position position3 = Position(Color::White);
Position position2 = Position(Color::White);

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

int main(int argc, char** argv) {
	setup_position3();
	position3 = position3.make_move(move_t::h("a5a6"));
	position3 = position3.make_move(move_t::h("d6d5"));
	position3 = position3.make_move(move_t::h("b4d4"));
	position3 = position3.make_move(move_t::h("h5h6"));

	position2_setup();
	position2= position2.make_move(move_t::h("e1g1", MoveType::Castle));
	position2= position2.make_move(move_t::h("b4b3"));

	std::vector<std::string> args = std::vector<std::string>(argv + 1, argv + argc);
	int depth = 1;

	if (args.size() != 0) {
		depth = stoi(args[0]);
	}

	//position_t position = position_t::get_starting();

	//position = position
	//	.make_move(move_t(square_t(3, 1), square_t(3, 2)))
	//	.make_move(move_t(square_t(2, 6), square_t(2, 5)))
	//	.make_move(move_t(square_t(4, 0), square_t(3, 1)))
	//	.make_move(move_t(square_t(3, 7), square_t(0,4)));

	std::cout << position2 << std::endl << std::endl;

	std::size_t count = perft(position2, depth);
	std::cout << "depth " << depth << ": " << count << std::endl;
	std::cout << std::endl;
}
