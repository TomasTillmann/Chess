#include "Pieces.hpp"
#include "PositionHandler.hpp"

std::set<square_t> SlidingPiece::get_attacked_squares(const position_t& position, const std::vector<square_t>& directions, int expand_factor, square_t square) const {
	std::set<square_t> attacked_squares;

	for (auto&& direction : directions) {
		for (int k = 1; k <= expand_factor; ++k) {
			square_t new_destination = square + (k * direction);

			// not on board
			if (!new_destination.is_on_board()) {
				break;
			}

			attacked_squares.emplace(new_destination);

			if ((position.at(new_destination) & Piece::Mask) != Piece::None) {
				break;
			}
		}
	}

	return attacked_squares;
}

std::vector<move_t> SlidingPiece::get_legal_moves(const position_t& position, const std::vector<square_t>& directions, int expand_factor, color_t friendly_color, square_t square) const {
#if DEBUG
	if ((position.at(square) & Piece::Mask) == Piece::King) {
		throw "Even though king is sliding piece, it can't be processed here";
	}
#endif

	std::vector<move_t> legal_moves;
	square_t king_destination = PositionHandler::get_king(position, friendly_color);

	for (auto&& direction : directions) {
		for (int k = 1; k <= expand_factor; ++k) {
			square_t new_destination = square + (k * direction);

			// not on board
			if (!new_destination.is_on_board()) {
				break;
			}

			// there already is friendly piece
			if ((position.at(new_destination) & Color::Mask) == friendly_color) {
				break;
			}

			// can't make the move if the move releases attack to my king 
			move_t move = move_t(square, new_destination);
			if (PositionHandler::get_attacked_squares(position.make_move(move), Color::op(friendly_color)).contains(king_destination)) {
				continue;
			}

			legal_moves.push_back(move);

			// will capture enemy piece -> sliding piece can't move further.
			if ((position.at(new_destination) & Color::Mask) == Color::op(friendly_color)) {
				break;
			}
		}
	}

	return legal_moves;
}


std::vector<move_t> King::generate_legal_moves(const position_t& position, square_t square) const {
	piece_t king = position.at(square);
	std::vector<move_t> legal_moves;

	#if DEBUG
	if ((king & Piece::Mask) != Piece::King) {
		throw "Not king";
	}
	#endif

	for (auto&& direction : _directions) {
		square_t new_destination = square + direction;
		std::set<square_t> attacked_squares = PositionHandler::get_attacked_squares(position, Color::op(king & Color::Mask));

		// not on board
		if (!new_destination.is_on_board()) {
			continue;
		}

		// there already is friendly piece
		if ((position.at(new_destination) & Color::Mask) == (king & Color::Mask)) {
			continue;
		}

		// can't move to square attacked by enemy's piece 
		if (attacked_squares.contains(new_destination)) {
			continue;
		}

		legal_moves.push_back(move_t(square, new_destination));
	}

	// TODO: castles

	return legal_moves;
}

std::set<square_t> King::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t king = position.at(square);

	#if DEBUG
	if ((king & Piece::Mask) != Piece::King) {
		throw "Not king";
	}
	#endif

	return SlidingPiece::get_attacked_squares(position, _directions, 1, square);
}


std::vector<move_t> Queen::generate_legal_moves(const position_t& position, square_t square) const {
	piece_t queen = position.at(square);

	#if DEBUG
	if ((queen & Piece::Mask) != Piece::Queen) {
		throw "Not queen";
	}
	#endif

	return SlidingPiece::get_legal_moves(position, _directions, 7, queen & Color::Mask, square);
}

std::set<square_t> Queen::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t queen = position.at(square);
	std::set<square_t> attacked_squares;

	#if DEBUG
	if ((queen & Piece::Mask) != Piece::Queen) {
		throw "Not queen";
	}
	#endif

	return SlidingPiece::get_attacked_squares(position, _directions, 7, square);
}


std::vector<move_t> Bishop::generate_legal_moves(const position_t& position, square_t square) const {
	piece_t bishop = position.at(square);

	#if DEBUG
	if ((bishop & Piece::Mask) != Piece::Bishop) {
		throw "Not bishop";
	}
	#endif

	return SlidingPiece::get_legal_moves(position, _directions, 7, bishop & Color::Mask, square);
}

std::set<square_t> Bishop::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t bishop = position.at(square);
	std::set<square_t> attacked_squares;

	#if DEBUG
	if ((bishop & Piece::Mask) != Piece::Bishop) {
		throw "Not bishop";
	}
	#endif

	return SlidingPiece::get_attacked_squares(position, _directions, 7, square);
}


std::vector<move_t> Knight::generate_legal_moves(const position_t& position, square_t square) const {
	throw "not implemented";
}

std::set<square_t> Knight::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t knight = position.at(square);
	std::set<square_t> attacked_squares;

	#if DEBUG
	if ((knight & Piece::Mask) != Piece::Knight) {
		throw "Not knight";
	}
	#endif

	for (auto&& direction : _directions) {
		square_t new_destination = square + direction;
		if (!new_destination.is_on_board()) {
			continue;
		}

		attacked_squares.emplace(new_destination);
	}

	return attacked_squares;
}


std::vector<move_t> Rook::generate_legal_moves(const position_t& position, square_t square) const {
	piece_t rook = position.at(square);

	#if DEBUG
	if ((rook & Piece::Mask) != Piece::Rook) {
		throw "Not rook";
	}
	#endif

	return SlidingPiece::get_legal_moves(position, _directions, 7, rook & Color::Mask, square);
}

std::set<square_t> Rook::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t rook = position.at(square);
	std::set<square_t> attacked_squares;

	#if DEBUG
	if ((rook & Piece::Mask) != Piece::Rook) {
		throw "Not rook";
	}
	#endif

	return SlidingPiece::get_attacked_squares(position, _directions, 7, square);
}


std::vector<move_t> Pawn::generate_legal_moves(const position_t& position, square_t square) const {
	throw "not implemented";
}

std::set<square_t> Pawn::get_attacked_squares(const position_t& position, square_t square) const {
	piece_t pawn = position.at(square);
	std::set<square_t> attacked_squares;

	#if DEBUG
	if ((pawn & Piece::Mask) != Piece::Pawn) {
		throw "Not pawn";
	}
	#endif

	square_t left_attacked = square + square_t(-1, (pawn & Color::Mask) == Color::White ? 1 : -1);
	square_t right_attacked = square + square_t(1, (pawn & Color::Mask) == Color::White ? 1 : -1);

	if (left_attacked.is_on_board()) {
		attacked_squares.emplace(left_attacked);
	}

	if (right_attacked.is_on_board()) {
		attacked_squares.emplace(right_attacked);
	}

	return attacked_squares;
}
