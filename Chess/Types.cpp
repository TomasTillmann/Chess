#include "Types.hpp"
#include "Pieces.hpp"
#include "PositionHandler.hpp"
#include "MoveGenerator.hpp"

square_t square_t::None = square_t(-1, -1);

move_t move_t::None = move_t(square_t::None, square_t::None);

