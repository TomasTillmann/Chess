#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include "Debug.hpp"

class PositionHandler;

typedef uint8_t piece_t;
namespace Piece {
	const piece_t None = piece_t{ 0b00000000 };
	const piece_t Pawn = piece_t{ 0b00000001 };
	const piece_t Rook = piece_t{ 0b00000010 };
	const piece_t Knight = piece_t{ 0b00000011 };
	const piece_t Bishop = piece_t{ 0b00000100 };
	const piece_t Queen = piece_t{ 0b00000101 };
	const piece_t King = piece_t{ 0b00000111 };
	const piece_t Mask = piece_t{ 0b00000111 };
};

typedef uint8_t color_t;
namespace Color {
	const color_t White = color_t{ 0b00001000 };
	const color_t Black = color_t{ 0b00010000 };
	const color_t Mask = color_t{ 0b00011000 };

	inline static color_t op(color_t color) {
		return color == White ? Black : White;
	}
};

typedef int8_t index_t;
struct square_t {
public:
	index_t file() const { return _file; }
	index_t rank() const { return _rank; }

	bool is_on_board() const {
		return 0 <= _file && _file < 8 && 0 <= _rank && _rank < 8;
	}

	square_t(index_t file, index_t rank)
		: _file(file), _rank(rank) { }

	square_t operator +(square_t sq) const {
		return square_t(_file + sq.file(), _rank + sq.rank());
	}

	bool operator<(square_t square) const {
		return (_file < square.file()) || (_file == square.file() && _rank < square.rank());
	}

	bool operator ==(square_t square) const {
		return (_file == square.file()) && (_rank == square.rank());
	}

	bool operator !=(square_t square) const {
		return (_file != square.file()) && (_rank != square.rank());
	}

	static square_t None;

	inline static square_t h(const std::string &sq_human_notation)
	{
		if (sq_human_notation.size() != 2) {
			throw std::invalid_argument("wrong length of sq_human_notation: " + sq_human_notation);
		}

		index_t file, rank;
		file = sq_human_notation[0] - 'a';

		if (!(0 <= file && file <= 7)) {
			throw std::invalid_argument("file is invalid: " + sq_human_notation[0]);
		}

		rank = (int)(sq_human_notation[1] - '1');

		if (!(0 <= rank && rank <= 7)) {
			throw std::invalid_argument("rank is invalid: " + sq_human_notation[1]);
		}

		return square_t(file, rank);
	}

	std::string to_string() const {
		return ((char)('a' + _file)) + std::to_string(_rank + 1);
	}

private:
	index_t _file;
	index_t _rank;
};

inline square_t operator *(int k, square_t sq) {
	return square_t(k * sq.file(), k * sq.rank());
}

typedef uint8_t moveType_t;
namespace MoveType {
	const moveType_t Normal = moveType_t{ 0b00000000 };
	const moveType_t Castle = moveType_t{ 0b0001000 };
	const moveType_t EnPassant = moveType_t{ 0b00010000 };
	const moveType_t Promotion = moveType_t{ 0b00011000 };
	const moveType_t TypeMask = moveType_t{ 0b00011000 };
};

typedef uint8_t positionInfo_t;
namespace PositionInfo {
	const positionInfo_t Default = positionInfo_t{ 0b00000000 };
	const positionInfo_t WLrook_moved = positionInfo_t{ 0b00000001 };
	const positionInfo_t WRrook_moved = positionInfo_t{ 0b00000010 };
	const positionInfo_t BLrook_moved = positionInfo_t{ 0b00000100 };
	const positionInfo_t BRrook_moved = positionInfo_t{ 0b00001000 };
	const positionInfo_t Wking_moved = positionInfo_t{ 0b00010000 };
	const positionInfo_t Bking_moved = positionInfo_t{ 0b00100000 };
};

struct move_t {
public:
	square_t from() const { return _from; }
	square_t to() const { return _to; }
	moveType_t type() const { return _type; }

	move_t(square_t from, square_t to)
		: move_t(from, to, MoveType::Normal) { }

	move_t(square_t from, square_t to, moveType_t type)
		: _from(from), _to(to), _type(type) { }

	bool operator ==(move_t move) const {
		return _from == move.from() && _to == move.to();
	}

	bool operator !=(move_t move) const {
		return _from != move.from() && _to != move.to();
	}

	static move_t None;

	inline static move_t h(const std::string &move_human_readable, moveType_t move_type)
	{
		if (move_human_readable.size() != 4) {
			throw std::invalid_argument("wrong length of human_raedable_move: " + move_human_readable);
		}

		square_t from = square_t::h(move_human_readable.substr(0, 2));
		square_t to = square_t::h(move_human_readable.substr(2, 2));

		return move_t(from, to, move_type);
	}

	inline static move_t h(const std::string& move_human_readable) {
		return h(move_human_readable, MoveType::Normal);
	}

	// TODO: promotion represent
	std::string to_string() const {
		return _from.to_string() + _to.to_string();
	}

	friend std::ostream& operator <<(std::ostream& os, move_t move) {
		os << move.to_string();
		return os;
	}

private:
	square_t _from;
	square_t _to;
	moveType_t _type;
};

#endif
