#include "PositionHandler.hpp"

std::set<square_t> PositionHandler::get_attacked_squares(const position_t& position, color_t color) {
	std::set<square_t> attacked_squares;
	std::set<square_t> attacked_squares_piece;

	piece_t piece;
	for (index_t file = 0; file < 8; ++file) {
		for (index_t rank = 0; rank < 8; ++rank) {
			piece = position.at(square_t(file, rank));

			if (piece != Piece::None || (piece & Color::Mask) != color) {
				attacked_squares_piece = get_attacked_squares(position, square_t(file, rank), piece);
				attacked_squares.insert(attacked_squares.begin(), attacked_squares.end());
			}
		}
	}

	return attacked_squares;
}

std::set<square_t> PositionHandler::get_attacked_squares(const position_t& position, square_t square, piece_t piece) {
	switch (piece) {
	case Piece::None:
		return std::set<square_t>();
		break;

	case Piece::King:
		return king.get_attacked_squares(position);
		break;

	case Piece::Queen:
		return queen.get_attacked_squares(position);
		break;

	case Piece::Bishop:
		return bishop.get_attacked_squares(position);
		break;

	case Piece::Knight:
		return knight.get_attacked_squares(position);
		break;

	case Piece::Rook:
		return rook.get_attacked_squares(position);
		break;

	case Piece::Pawn:
		return pawn.get_attacked_squares(position);
		break;
	}
}
