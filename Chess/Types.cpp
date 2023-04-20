#include "Types.hpp"
#include "Pieces.hpp"
#include "PositionHandler.hpp"
#include "MoveGenerator.hpp"

square_t square_t::None = square_t(-1, -1);

position_t position_t::get_starting() {
	position_t starting_position = position_t(Color::White);
	starting_position.place(square_t(0, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(1, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(2, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(3, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(4, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(5, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(6, 1), Piece::Pawn | Color::White);
	starting_position.place(square_t(7, 1), Piece::Pawn | Color::White);

	starting_position.place(square_t(0, 0), Piece::Rook | Color::White);
	starting_position.place(square_t(1, 0), Piece::Knight | Color::White);
	starting_position.place(square_t(2, 0), Piece::Bishop | Color::White);
	starting_position.place(square_t(3, 0), Piece::Queen | Color::White);
	starting_position.place(square_t(4, 0), Piece::King | Color::White);
	starting_position.place(square_t(5, 0), Piece::Bishop | Color::White);
	starting_position.place(square_t(6, 0), Piece::Knight | Color::White);
	starting_position.place(square_t(7, 0), Piece::Rook | Color::White);

	starting_position.place(square_t(0, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(1, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(2, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(3, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(4, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(5, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(6, 6), Piece::Pawn | Color::Black);
	starting_position.place(square_t(7, 6), Piece::Pawn | Color::Black);

	starting_position.place(square_t(0, 7), Piece::Rook | Color::Black);
	starting_position.place(square_t(1, 7), Piece::Knight | Color::Black);
	starting_position.place(square_t(2, 7), Piece::Bishop | Color::Black);
	starting_position.place(square_t(3, 7), Piece::Queen | Color::Black);
	starting_position.place(square_t(4, 7), Piece::King | Color::Black);
	starting_position.place(square_t(5, 7), Piece::Bishop | Color::Black);
	starting_position.place(square_t(6, 7), Piece::Knight | Color::Black);
	starting_position.place(square_t(7, 7), Piece::Rook | Color::Black);

	return starting_position;
}

std::string position_t::to_string() const {
	std::string pos = "";
	std::string row = "";

	for (index_t i = 0; i < 64; ++i) {
		if (i % 8 == 0) {
			pos += row + '\n';
			row = "";
		}

		row += PieceBase::to_string(_pieces[i]);
	}
	pos += row;

	return pos;
}

position_t position_t::make_move(move_t move) const {
	position_t new_position = position_t(*this);
	new_position.to_play(Color::op(to_play()));

	switch (move.type() & MoveType::TypeMask) {
		case MoveType::Normal: {
			new_position.move(move);
			break;
		}

		case MoveType::Castle: {
			// move the king
			new_position.move(move);

			// short castle
			if (move.to().file() == 6) {
				new_position.move(move_t(square_t(7, move.to().rank()), square_t(5, move.to().rank())));
			}
			// long castle
			else {
				new_position.move(move_t(square_t(0, move.to().rank()), square_t(3, move.to().rank())));
			}

			break;
		}

		case MoveType::EnPassant: {
			// move the pawn
			new_position.move(move);

			int k = (at(move.from()) & Color::Mask) == Color::White ? -1 : 1;
			square_t behind = move.to() + square_t(0, k);
			new_position.place(behind, Piece::None);

			break;
		}

		case MoveType::Promotion: {
			piece_t piece_to_promote = (move.type() & Piece::Mask) | (at(move.from()) & Color::Mask);
			new_position.move(move);
			new_position.place(move.to(), piece_to_promote);

			break;
		}

		default: {
			throw std::invalid_argument("panic");
		}
	}

	return new_position;
}

bool position_t::is_check() const {
	square_t king = PositionHandler::get_king(*this, to_play());
	std::set<square_t> attacked_squares = PositionHandler::get_attacked_squares(*this, Color::op(to_play()));
	return (attacked_squares.find(king) != attacked_squares.end());
}

bool position_t::is_checkmate() const {
	return is_check() && (MoveGenerator::generate_legal_moves(*this).size() == 0);
}

bool position_t::is_stalemate() const {
	return (!is_check()) && (MoveGenerator::generate_legal_moves(*this).size() == 0);
}

