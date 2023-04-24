#include "CliApi.hpp"
#include "../Engine/Perft.hpp"
#include "fen.hpp"
#include <string>

void CliApi::run() {
	command_t command;

	// will always be of needed size
	std::vector<std::string> command_args_raw;

	while (true) {
		std::string command_raw;
		getline(std::cin, command_raw);
		try {
			command = _command_parser.Parse(command_raw, command_args_raw);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Invalid command format" << std::endl;
			continue;
		}

		if (command == (Command::position | Command::move)) {
			move_t move = _command_parser.parse_move(command_args_raw[0], command_args_raw[1]);
			try {
				_game.play_move(move);
			}
			catch (std::invalid_argument& ex) {
				std::cout << "Illegal move" << std::endl;
			}
		}
		else if (command == (Command::position | Command::show)) {
			std::cout << _game.current_position() << std::endl;
		}
		else if (command == (Command::position | Command::legal_moves)) {
			std::vector<move_t> legal_moves = MoveGenerator::generate_legal_moves(_game.current_position());
			std::cout << "Legal moves:" << std::endl;
			for (auto&& legal_move : legal_moves) {
				std::cout << legal_move << std::endl;
			}
		}
		else if (command == (Command::position | Command::fen)) {
			try {
				_game.set_position(FEN::parse(command_args_raw[0]));
			}
			catch (std::exception& ex) {
				std::cout << "Invalid fen" << std::endl;
			}
		}
		else if (command == (Command::engine | Command::eval)) {
			try {
				int eval = _engine->evaluate(_game.current_position(), _command_parser.parse_depth(command_args_raw[0]));
				std::cout << "evaluation: " << eval << std::endl;
			}
			catch (std::exception& ex) {
				std::cout << "Command invalid format" << std::endl;
			}
		}
		else if (command == (Command::engine | Command::best_moves)) {
			std::vector<move_t> best_moves;
			std::vector<double> score;

			try {
				_engine->best_moves(_game.current_position(), best_moves, score, _command_parser.parse_depth(command_args_raw[0]));

				std::cout << "Best moves:" << std::endl;
				for (std::size_t i = 0; i < best_moves.size(); ++i) {
					std::cout << "move: " << best_moves[i] << " eval: " << score[i] << std::endl;
				}
			}
			catch (std::exception& ex) {
				std::cout << "Command invalid format" << std::endl;
			}
		}
		else if (command == (Command::engine | Command::play_best)) {
			std::vector<move_t> best_moves;
			std::vector<double> score;

			try {
				_engine->best_moves(_game.current_position(), best_moves, score, _command_parser.parse_depth(command_args_raw[0]));
				std::size_t best = 0;
				for (std::size_t i = 0; i < best_moves.size(); ++i) {
					if (_game.current_position().to_play() == Color::White ? score[i] > score[best] : score[i] < score[best]) {
						best = i;
					}
				}

				_game.play_move(best_moves[best]);
			}
			catch (std::exception& ex) {
				std::cout << "Command invalid format" << std::endl;
			}
		}
		else if (command == (Command::engine | Command::perft)) {
			std::cout << "Perft:" << std::endl;
			try {
				Perft::go(_game.current_position(), _command_parser.parse_depth(command_args_raw[0]), true);
			}
			catch (std::exception& ex) {
				std::cout << "Command invalid format" << std::endl;
			}
		}
		else {
			std::cout << "Unknown command" << std::endl;
		}

		std::cout << std::endl;
		command_args_raw.clear();
	}
}

