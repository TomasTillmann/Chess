#include "Types.hpp"
#include "Pieces.hpp"

square_t square_t::None = square_t(-1, -1);

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
			throw "panic";
		}
	}

	return new_position;
}
