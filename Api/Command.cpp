#include "Command.hpp"

std::vector<std::string> Command::Parser::tokenize(std::string str) const {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, ' ')) {
		tokens.push_back(token);
	}

	return tokens;
}

command_t Command::Parser::Parse(std::string raw_command, std::vector<std::string>& args) const {
	std::vector<std::string> tokens = tokenize(raw_command);
	if (tokens.size() < 2) {
		throw std::invalid_argument("invalid command");
	}

	command_t command = 0;
	if (tokens[0] == "position") {
		command |= position;

		if (tokens[1] == "move") {
			command |= move;
			if (tokens.size() != 3 && tokens.size() != 4) {
				throw std::invalid_argument("missing move arg");
			}

			args.push_back(tokens[2]);
			args.push_back(tokens.size() == 4 ? tokens[3] : "normal");
		}
		else if (tokens[1] == "show") {
			command |= show;
		}
		else if (tokens[1] == "legal_moves") {
			command |= legal_moves;
		}
		else if (tokens[1] == "fen") {
			command |= fen;
			if (tokens.size() != 6 + 2) {
				throw std::invalid_argument("missing fen argument");
			}

			std::string fen = "";
			for (std::size_t i = 2; i < 6 + 1; ++i) {
				fen += tokens[i] + " ";
			}
			fen += tokens[6 + 1];
			args.push_back(fen);
		}
	}
	else if (tokens[0] == "engine") {
		command |= engine;

		if (tokens[1] == "eval") {
			command |= eval;
			if (tokens.size() != 3) {
				throw std::invalid_argument("missing depth arg");
			}
			args.push_back(tokens[2]);
		}
		else if (tokens[1] == "moves_eval") {
			command |= moves_eval;
			if (tokens.size() != 3) {
				throw std::invalid_argument("missing depth arg");
			}
			args.push_back(tokens[2]);
		}
		else if (tokens[1] == "play_best") {
			command |= play_best;
			if (tokens.size() != 3) {
				throw std::invalid_argument("missing depth arg");
			}
			args.push_back(tokens[2]);
		}
		else if (tokens[1] == "perft") {
			command |= perft;
			if (tokens.size() != 3) {
				throw std::invalid_argument("missing depth arg");
			}
			args.push_back(tokens[2]);
		}
	}

	return command;
}

