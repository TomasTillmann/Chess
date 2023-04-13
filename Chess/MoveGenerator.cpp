#include "MoveGenerator.hpp"

std::vector<move_t> MoveGenerator::generate_legal_moves(const position_t& position) {
	std::vector<move_t> legal_moves;
	std::vector<move_t> legal_moves_piece;
	piece_t piece;

	for (index_t file = 0; file < 8; ++file) {
		for (index_t rank = 0; rank < 8; ++rank) {
			piece = position.at(square_t(file, rank));

			if (piece != Piece::None || (piece & Color::Mask) != position.to_play()) {
				legal_moves_piece = generate_legal_moves(position, square_t(file, rank));
				legal_moves.insert(legal_moves.end(), legal_moves_piece.begin(), legal_moves_piece.end());
			}
		}
	}

	return legal_moves;
}

std::vector<move_t> MoveGenerator::generate_legal_moves(const position_t& position, square_t square) {
	piece_t piece = position.at(square);

	switch (piece) {
	case Piece::None:
		return std::vector<move_t>();
		break;

	case Piece::King:
		return king.generate_legal_moves(position, square);
		break;

	case Piece::Queen:
		return queen.generate_legal_moves(position, square);
		break;

	case Piece::Bishop:
		return bishop.generate_legal_moves(position, square);
		break;

	case Piece::Knight:
		return knight.generate_legal_moves(position, square);
		break;

	case Piece::Rook:
		return rook.generate_legal_moves(position, square);
		break;

	case Piece::Pawn:
		return pawn.generate_legal_moves(position, square);
		break;
	}
}
