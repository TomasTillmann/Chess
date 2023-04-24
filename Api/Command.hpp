#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include "../Chess/Types.hpp"

// position move <move>
// position show
// engine eval <depth>
// engine best_moves <depth>
// engine perft <depth>

// <move> : a2a4, b1c3, c6c7 queen, e1g1 castle, c6c7 rook, h5g3 enpassant, ...
// <depth> = <int>: 4, ...

typedef uint16_t command_t;
namespace Command {
	const command_t engine{ 0b1000000000000000 };
	const command_t position{ 0b0100000000000000 };

	const command_t move{ 0b0000000000000001 };
	const command_t eval{ 0b0000000000000010 };
	const command_t best_moves{ 0b0000000000000011 };
	const command_t show{ 0b0000000000000100 };
	const command_t perft{ 0b0000000000000101 };
	const command_t legal_moves{ 0b0000000000000111 };

	class CommandArgsParser;
	class Parser {
	public:
		command_t Parse(std::string raw_command, std::vector<std::string>& args) const;

		move_t parse_move(const std::string& move_raw, const std::string& move_type_raw) const {
			moveType_t type = MoveType::Normal;
			if (move_type_raw == "castle") {
				type = MoveType::Castle;
			}
			else if (move_type_raw == "enpassant") {
				type = MoveType::EnPassant;
			}
			else if (move_type_raw == "queen") {
				type = MoveType::Promotion | Piece::Queen;
			}
			else if (move_type_raw == "bishop") {
				type = MoveType::Promotion | Piece::Bishop;
			}
			else if (move_type_raw == "knight") {
				type = MoveType::Promotion | Piece::Knight;
			}
			else if (move_type_raw == "rook") {
				type = MoveType::Promotion | Piece::Rook;
			}

			return move_t::h(move_raw, type);
		}

		int parse_depth(const std::string& depth_raw) const {
			return stoi(depth_raw);
		}

	private:
		std::vector<std::string> tokenize(std::string str) const;
	};
};

#endif