#include "Position.hpp"
#include "Pieces.hpp"
#include "MoveGenerator.hpp"
#include "PositionHandler.hpp"

Position Position::get_starting() {
	Position starting_position = Position(Color::White);
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

std::string Position::to_string() const {
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

Position Position::cmake_move(move_t move) const {
	Position new_position = Position(*this);
	auto str = new_position.to_string();
	new_position.make_move(move);
	return new_position;
}

void Position::make_move(move_t move) {
	to_play(Color::op(to_play()));
	_last_move = move;

	switch (move.type() & MoveType::TypeMask) {
	case MoveType::Normal: {
		this->move(move);
		break;
	}

	case MoveType::Castle: {
		// move the king
		this->move(move);

		// short castle
		if (move.to().file() == 6) {
			this->move(move_t(square_t(7, move.to().rank()), square_t(5, move.to().rank())));
		}
		// long castle
		else {
			this->move(move_t(square_t(0, move.to().rank()), square_t(3, move.to().rank())));
		}

		break;
	}

	case MoveType::EnPassant: {
		// where is behind
		int k = (at(move.from()) & Color::Mask) == Color::White ? -1 : 1;

		// move the pawn
		this->move(move);

		// remove the taken pawn
		square_t behind = move.to() + square_t(0, k);
		this->place(behind, Piece::None);

		break;
	}

	case MoveType::Promotion: {
		piece_t piece_to_promote = (move.type() & Piece::Mask) | (at(move.from()) & Color::Mask);
		this->move(move);
		this->place(move.to(), piece_to_promote);

		break;
	}

	default: {
		throw std::invalid_argument("panic-nonexistent move type");
	}
	}
}

bool Position::is_check() const {
	square_t king = PositionHandler::get_king(*this, to_play());
	std::set<square_t> attacked_squares = PositionHandler::get_attacked_squares(*this, Color::op(to_play()));
	return (attacked_squares.find(king) != attacked_squares.end());
}

bool Position::is_checkmate() const {
	return is_check() && (MoveGenerator::generate_legal_moves(*this).size() == 0);
}

bool Position::is_stalemate() const {
	return (!is_check()) && (MoveGenerator::generate_legal_moves(*this).size() == 0);
}
