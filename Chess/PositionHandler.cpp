#include "PositionHandler.hpp"
#include <iostream>

std::set<square_t> PositionHandler::get_attacked_squares(const Position& position, color_t color) {
	std::set<square_t> attacked_squares;
	std::set<square_t> attacked_squares_piece;

	piece_t piece;
	for (index_t file = 0; file < 8; ++file) {
		for (index_t rank = 0; rank < 8; ++rank) {
			piece = position.at(square_t(file, rank));

			if ((piece & Piece::Mask) != Piece::None && (piece & Color::Mask) == color) {
				attacked_squares_piece = get_attacked_squares(position, square_t(file, rank));
				attacked_squares.insert(attacked_squares_piece.begin(), attacked_squares_piece.end());
			}
		}
	}

	return attacked_squares;
}

std::set<square_t> PositionHandler::get_attacked_squares(const Position& position, square_t square) {
	piece_t piece = position.at(square);

	switch (piece & Piece::Mask) {
		case Piece::None: {
			std::set<square_t> empty;
			return empty;
		}

		case Piece::King: {
			return king.get_attacked_squares(position, square);
		}

		case Piece::Queen: {
			return queen.get_attacked_squares(position, square);
		}

		case Piece::Bishop: {
			return bishop.get_attacked_squares(position, square);
		}

		case Piece::Knight: {
			return knight.get_attacked_squares(position, square);
		}

		case Piece::Rook: {
			return rook.get_attacked_squares(position, square);
		}

		case Piece::Pawn: {
			return pawn.get_attacked_squares(position, square);
		}

		default:
			throw std::invalid_argument("panic");
	}
}


square_t PositionHandler::get_king(const Position& position, color_t color) {
	for (index_t i = 0; i < 64; ++i) {
		if ((position._pieces[i] & Piece::Mask) == Piece::King && (position._pieces[i] & Color::Mask) == color) {
			return Position::to_square(i);
		}
	}

	return square_t::None;
}
