#ifndef PIECES_HPP
#define PIECES_HPP

#include "Types.hpp"
#include "Debug.hpp"
#include <set>


class PieceBase {
};

class SlidingPiece : public PieceBase {
public:
	std::set<square_t> get_attacked_squares(const position_t& position, const std::vector<square_t>& directions, int expand_factor, color_t friendly_color, square_t square) const;
};

class King : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;

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

class Queen : public SlidingPiece {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;

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
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;

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
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;

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
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;

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
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position, square_t square) const;
};

#endif
