#include "../Chess/Chess.hpp"
#include <queue>
#include <vector>
#include "Game.hpp"
#include "CliApi.hpp"
#include "fen.hpp"

int main(int argc, char** argv) {
	std::vector<std::string> args(argv + 1, argc + argv);

	CliApi api(args);
	api.run();
}