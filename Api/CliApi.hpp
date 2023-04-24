#ifndef CLI_API_HPP
#define CLI_API_HPP

#include "../Engine/Engine.hpp"
#include "Game.hpp"
#include "Command.hpp"

class CliApi {
private:
	const Engine* _engine = nullptr;
	Command::Parser _command_parser;
	Game _game;
	EngineMinimax _minimax;

public:
	CliApi(const std::vector<std::string>& args) {
		parse_engine(args);
		if (_engine == nullptr) {
			throw std::invalid_argument("Invalid args");
		}
	}

	void run();

	void parse_engine(const std::vector<std::string>& args) {
		// default
		_engine = &_minimax;

		for (std::size_t i = 0; i < args.size(); ++i) {
			if (args[i] == "--engine" || args[i] == "-e") {
				if (args.size() != i) {
					if (args[i + 1] == "minimax") {
						_engine = &_minimax;
					}
					// add others here
				}
			}
		}
	}
};

#endif