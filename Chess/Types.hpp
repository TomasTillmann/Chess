#ifndef POSITION_HPP
#define POSITION_HPP

#include <vector>
#include <cstdint>
#include <string>
#include "Debug.hpp"

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

typedef uint8_t index_t;
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
		return _file < square.file() || _file == square.file() && _rank < square.rank();
	}

	std::string to_string() const {
		return "[file: " + std::to_string(_file) + " rank: " + std::to_string(_rank) + "]";
	}

private:
	index_t _file;
	index_t _rank;
};

typedef uint8_t moveType_t;
namespace MoveType {
	const moveType_t Normal = moveType_t{ 0b00000000 };
	const moveType_t Castle = moveType_t{ 0b00000001 };
	const moveType_t EnPassant = moveType_t{ 0b00000010 };
	const moveType_t Promotion = moveType_t{ 0b00000011 };
	const moveType_t Mask = moveType_t{ 0b00000011 };
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

private:
	square_t _from;
	square_t _to;
	moveType_t _type;
};

struct position_t {
private:
	std::vector<piece_t> _pieces;
	color_t _to_play;

	index_t fromSquare(square_t square) const {
		return (7 - square.rank()) * 8 + square.file();
	}

	square_t toSquare(index_t i) const {
		return square_t(i % 8, i / 8);
	}

public:
	position_t(color_t to_play)
	: _to_play(to_play) {
		_pieces.resize(64);
	}

	color_t to_play() const { return _to_play; }

	position_t move(move_t move) const {
		throw "not implemented";
	}

	void place(square_t square, piece_t piece) {
		#if DEBUG
		if (!square.is_on_board()) { throw "not on board"; }
		#endif

		_pieces[fromSquare(square)] = piece;
	}

	piece_t at(square_t square) const {
		#if DEBUG
		if (!square.is_on_board()) { throw "not on board"; }
		#endif

		return _pieces[fromSquare(square)];
	}
};

#endif
