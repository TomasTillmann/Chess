#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

#include "Types.hpp"
#include "Debug.hpp"
#include "Pieces.hpp"
#include <set>

class MoveGenerator {
private:
	inline static King king = King();
	inline static Queen queen = Queen();
	inline static Bishop bishop = Bishop();
	inline static Knight knight = Knight();
	inline static Rook rook = Rook();
	inline static Pawn pawn = Pawn();

public:
	static std::vector<move_t> generate_legal_moves(const position_t& position);
	static std::vector<move_t> generate_legal_moves(const position_t& position, square_t square);
};

#endif