#ifndef POSITION_HPP
#define POSITION_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include "Debug.hpp"
#include "Types.hpp"

class Position {
private:
	std::vector<piece_t> _pieces;
	color_t _to_play;
	positionInfo_t _info;
	move_t _last_move;

	void update_info(move_t move) {
		if (move.from() == square_t(0, 0) || move.to() == square_t(0, 0)) {
			_info = _info | PositionInfo::WLrook_moved;
		}
		else if (move.from() == square_t(7, 0) || move.to() == square_t(7, 0)) {
			_info = _info | PositionInfo::WRrook_moved;
		}
		else if (move.from() == square_t(0, 7) || move.to() == square_t(0, 7)) {
			_info = _info | PositionInfo::BLrook_moved;
		}
		else if (move.from() == square_t(7, 7) || move.to() == square_t(7, 7)) {
			_info = _info | PositionInfo::BRrook_moved;
		}
		else if (move.from() == square_t(4, 0)) {
			_info = _info | PositionInfo::Wking_moved;
		}
		else if (move.from() == square_t(4, 7)) {
			_info = _info | PositionInfo::Bking_moved;
		}
	}

	void move(move_t move) {
		update_info(move);

		piece_t piece = at(move.from());
		place(move.from(), Piece::None);
		place(move.to(), piece);
	}

	friend std::ostream& operator <<(std::ostream& os, const Position& position) {
		os << position.to_string();
		return os;
	}

public:
	friend PositionHandler;

	Position(color_t to_play)
		: _to_play(to_play), _info(), _last_move(move_t::None) {
		_pieces.resize(64);
	}

	inline static index_t from_square(square_t square) {
		return (7 - square.rank()) * 8 + square.file();
	}

	inline static square_t to_square(index_t i) {
		return square_t(i % 8, 7 - (i / 8));
	}

	static Position get_starting();

	std::string to_string() const;

	int pieces_count() const {
		int count = 0;
		for (auto&& piece : _pieces)
		{
			if ((piece & Piece::Mask) != Piece::None) {
				++count;
			}
		}

		return count;
	}

	bool operator ==(const Position& pos) const {
		for (index_t i = 0; i < 64; ++i) {
			if (_pieces[i] != pos._pieces[i]) {
				return false;
			}
		}

		return true;
	}

	color_t to_play() const { return _to_play; }

	void to_play(color_t color) { _to_play = color; }

	positionInfo_t info() const { return _info; }

	move_t last_move() const { return _last_move; }

	void add_info(positionInfo_t info) {
		_info |= info;
	}

	Position cmake_move(move_t move) const;

	void make_move(move_t move);

	void place(square_t square, piece_t piece) {
#if DEBUG
		if (!square.is_on_board()) {
			throw std::invalid_argument("square not on board");
		}
#endif

		_pieces[from_square(square)] = piece;
	}

	piece_t at(square_t square) const {
#if DEBUG
		if (!square.is_on_board()) {
			throw std::invalid_argument("square not on board");
		}
#endif

		return _pieces[from_square(square)];
	}

	piece_t at(index_t index) const {
#if DEBUG
		if (!(0 <= index && index <= 63))
		{
			throw std::invalid_argument("index not on board");
		}
#endif
		return _pieces[index];
	}

	bool is_check() const;

	bool is_checkmate() const;

	bool is_stalemate() const;

	bool is_over() const {
		return is_checkmate() || is_stalemate();
	}
};

#endif
