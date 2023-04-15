#include "Types.hpp"
#include "Pieces.hpp"

std::string position_t::to_string() const {
	std::string pos = "";
	std::string row = "";

	for (index_t i = 0; i < 64; ++i) {
		if (i % 8 == 0) {
			pos += row + '\n';
			row = "";
		}

		row += PieceBase::to_string(_pieces[i]);
	}

	return pos;
}
