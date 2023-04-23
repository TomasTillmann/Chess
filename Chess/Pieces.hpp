#ifndef PIECES_HPP
#define PIECES_HPP

#include "Types.hpp"
#include "Debug.hpp"
#include "Position.hpp"
#include <set>


class PieceBase {
public:
	inline static std::string to_string(piece_t piece) {
		switch (piece & Piece::Mask) {
			case Piece::None: return ".";
			case Piece::King: return (piece & Color::Mask) == Color::White ? "K" : "k";
			case Piece::Queen: return (piece & Color::Mask) == Color::White ? "Q" : "q";
			case Piece::Bishop: return (piece & Color::Mask) == Color::White ? "B" : "b";
			case Piece::Knight: return (piece & Color::Mask) == Color::White ? "N" : "n";
			case Piece::Rook: return (piece & Color::Mask) == Color::White ? "R" : "r";
			case Piece::Pawn: return (piece & Color::Mask) == Color::White ? "P" : "p";
			default: throw std::invalid_argument("panic");
		}
	}
};

class SlidingPiece : public PieceBase {
public:
	std::set<square_t> get_attacked_squares(const Position& position, const std::vector<square_t>& directions, int expand_factor, square_t square) const;
	std::vector<move_t> get_legal_moves(const Position& position, const std::vector<square_t>& directions, int expand_factor, color_t friendly_color, square_t square) const;
};

class King : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	void castling(const Position& position, square_t square, piece_t king, std::vector<move_t>& legal_moves) const;

	std::vector<square_t> _directions = {
		square_t(0,1),
		square_t(1,1),
		square_t(1,0),
		square_t(1,-1),
		square_t(0,-1),
		square_t(-1,-1),
		square_t(-1,0),
		square_t(-1,1),
	};
};

class Queen : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	std::vector<square_t> _directions = {
		square_t(0,1),
		square_t(1,1),
		square_t(1,0),
		square_t(1,-1),
		square_t(0,-1),
		square_t(-1,-1),
		square_t(-1,0),
		square_t(-1,1),
	};
};

class Bishop : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	std::vector<square_t> _directions = {
		square_t(1,1),
		square_t(1,-1),
		square_t(-1,-1),
		square_t(-1,1),
	};
};

class Knight : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	std::vector<square_t> _directions = {
		square_t(1,2),
		square_t(-1,2),
		square_t(2,1),
		square_t(2,-1),
		square_t(1,-2),
		square_t(-1,-2),
		square_t(-2,-1),
		square_t(-2,1),
	};
};

class Rook : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	std::vector<square_t> _directions = {
		square_t(0,1),
		square_t(1,0),
		square_t(0,-1),
		square_t(-1,0),
	};
};

class Pawn : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const Position& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const Position& position, square_t square) const;

private:
	void add_promotion_moves(move_t move, std::vector<move_t>& legal_moves) const;
};

#endif
