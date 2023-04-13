#ifndef POSITION_HANDLER_HPP
#define POSITION_HANDLER_HPP

#include "Types.hpp"
#include "Pieces.hpp"
#include <set>

class PositionHandler {
private:
	inline static King king = King();
	inline static Queen queen = Queen();
	inline static Bishop bishop = Bishop();
	inline static Knight knight = Knight();
	inline static Rook rook = Rook();
	inline static Pawn pawn = Pawn();

public:
	static std::set<square_t> get_attacked_squares(const position_t& position, color_t color);

	static std::set<square_t> get_attacked_squares(const position_t& position, square_t square, piece_t piece);
};

#endif