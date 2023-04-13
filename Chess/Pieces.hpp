#ifndef PIECES_HPP
#define PIECES_HPP

#include "Types.hpp"
#include "Debug.hpp"
#include <set>


class PieceBase {
};

class King : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;

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

class Queen : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;
};

class Bishop : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;
};

class Knight : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;
};

class Rook : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;
};

class Pawn : public PieceBase {
public:
	std::vector<move_t> generate_legal_moves(const position_t& position, square_t square) const;
	std::set<square_t> get_attacked_squares(const position_t& position) const;
};

#endif
