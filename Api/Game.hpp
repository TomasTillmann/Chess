#ifndef GAME_HPP
#define GAME_HPP

#include "../Chess/Chess.hpp"
#include <algorithm>

class Game {
private:
	Position _position;

public:
	Game()
		: _position(Position::get_starting()) { }

	color_t player_to_play() const
	{
		return _position.to_play();
	}

	Position current_position() const {
		return _position;
	}

	void set_position(const Position& position) {
		_position = position;
	}

	bool is_over() const {
		return _position.is_over();
	}

	void play_move(move_t move) {
#if DEBUG
		std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(_position);
		if (std::find(legal_moves.begin(), legal_moves.end(), move) == legal_moves.end()) {
			throw std::invalid_argument("illegal move");
		}
#endif

		_position.make_move(move);
	}

	std::vector<move_t> legal_moves() const {
		return MoveGenerator::generate_legal_moves(_position);
	}
};

#endif