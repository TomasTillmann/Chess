#include "Evaluator.hpp"
#include <cmath>

double Evaluator::fast_evaluate(const Position& position) const {
	double white_score = 0;
	std::set<square_t> player_pieces_squares = PositionHandler::get_player_pieces(position, Color::White);
	for (auto&& player_piece_sq : player_pieces_squares)
	{
		white_score += evaluate_piece_score(position, player_piece_sq);
	}

	double black_score = 0;
	player_pieces_squares = PositionHandler::get_player_pieces(position, Color::Black);
	for (auto&& player_piece_sq : player_pieces_squares)
	{
		black_score += evaluate_piece_score(position, player_piece_sq);
	}

	return white_score - black_score;
}

double Evaluator::full_evaluate(const Position& position) const {
	int white_score = 0;
	std::set<square_t> player_pieces_squares = PositionHandler::get_player_pieces(position, Color::White);
	for (auto&& player_piece_sq : player_pieces_squares)
	{
		white_score += evaluate_piece_score(position, player_piece_sq);
		white_score += evaluate_defending_score(position, player_piece_sq);
		white_score += evaluate_mobility(position);

		white_score -= evaluate_attacking_penalty(position, player_piece_sq);
		white_score -= evaluate_enprise_penalty(position, player_piece_sq);
	}

	int black_score = 0;
	player_pieces_squares = PositionHandler::get_player_pieces(position, Color::Black);
	for (auto&& player_piece_sq : player_pieces_squares)
	{
		black_score += evaluate_piece_score(position, player_piece_sq);
		black_score += evaluate_defending_score(position, player_piece_sq);
		black_score += evaluate_mobility(position);

		black_score -= evaluate_attacking_penalty(position, player_piece_sq);
		black_score -= evaluate_enprise_penalty(position, player_piece_sq);
	}

	return white_score - black_score;
}

double Evaluator::piece_cost(piece_t piece) const {
	switch (piece & Piece::Mask) {
	case Piece::None: {
		return 0;
	}

	case Piece::King: {
		return 33000;
	}

	case Piece::Queen: {
		return 975;
	}

	case Piece::Bishop: {
		return 325;
	}

	case Piece::Knight: {
		return 320;
	}

	case Piece::Rook: {
		return 500;
	}

	case Piece::Pawn: {
		return 100;
	}

	default: {
		throw std::invalid_argument("Not known piece.");
	}
	}
}

double Evaluator::piece_positioning_cost(const Position& position, piece_t piece, square_t square) const {
	color_t piece_color = piece & Color::Mask;

	switch (piece & Piece::Mask) {
	case Piece::None: {
		return 0;
	}

	case Piece::King: {
		// endgame
		if (position.pieces_count() < 15) {
			return _king_table_endgame[get_table_index(square, piece_color)];
		}
		else {
			return _king_table[get_table_index(square, piece_color)];
		}
	}

	case Piece::Queen: {
		return PositionHandler::get_attacked_squares(position, square).size() * 5;
	}

	case Piece::Bishop: {
		return _bishop_table[get_table_index(square, piece_color)];
	}

	case Piece::Knight: {
		return _knight_table[get_table_index(square, piece_color)];
	}

	case Piece::Rook: {
		return PositionHandler::get_attacked_squares(position, square).size() * 5;
	}

	case Piece::Pawn: {
		return _pawn_table[get_table_index(square, piece_color)];
	}

	default: {
		throw std::invalid_argument("Not known piece.");
	}
	}
}

double Evaluator::evaluate_piece_score(const Position& position, square_t square) const {
	return piece_positioning_cost(position, position.at(square), square);
}

double Evaluator::evaluate_defending_score(const Position& position, square_t square) const {
	int score = 0;

	std::set<square_t> protecting_pieces = PositionHandler::get_protecting_pieces(position, position.to_play(), square);
	for (auto&& protecting_piece : protecting_pieces)
	{
		// it's better to be protected by a pawn than by for instance a queen
		score += (piece_cost(Piece::Queen) - piece_cost(position.at(protecting_piece))) * 0.2;
	}

	return score;
}

double Evaluator::evaluate_mobility(const Position& position) const {
	return MoveGenerator::generate_legal_moves(position).size() * 7;
}

double Evaluator::evaluate_attacking_penalty(const Position & position, square_t square) const {
	int penalty = 0;
	std::set<square_t> attacking_pieces = PositionHandler::get_attacking_pieces(position, position.to_play(), square);
	for (auto&& attacking_piece : attacking_pieces)
	{
		// it's more okay to be atacked by a queen than by a pawn
		// it's more okay if a pawn is attacked than if a queen is attacked
		penalty += (piece_cost(Piece::Queen) - piece_cost(position.at(attacking_piece)) * 0.4) * piece_cost(position.at(square));
	}

	return penalty;
}

double Evaluator::evaluate_enprise_penalty(const Position& position, square_t square) const {
	int penalty = 0;
	std::set<square_t> attacking_pieces = PositionHandler::get_attacking_pieces(position, position.to_play(), square);
	std::set<square_t> protecting_pieces = PositionHandler::get_protecting_pieces(position, position.to_play(), square);

	// enprise - free piece
	if (attacking_pieces.size() > 1 && protecting_pieces.size() == 0)
	{
		penalty += piece_cost(position.at(square)) * 0.5;
	}

	return penalty;
}

