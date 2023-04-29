# User Guide

## Lenochod engine

- This program is a full implementation of [chess](https://en.wikipedia.org/wiki/Chess) and a custom chess engine - Lenochod engine.
- User can interact with the board and command Lenochod to provide evaluation of the position, move evaluation distribution and play against him.

## System requirements

- Windows / Linux / Mac
- Have [g++](https://gcc.gnu.org/) installed.
- Or have [Visual Studio](https://visualstudio.microsoft.com/) with `C++` support.

## Installation

- Navigate to root folder and run: `g++ -std=c++2a -Werror -Wall -O3 Chess/*.cpp Engine/*.cpp .\Api\*.cpp -o engine`.
- Binary named `engine` will be created in the root folder.
- Or open `.sln` file in Visual Studio, build the solution.
  - The file tree structure where the binary is located is dependent on your CPU and platform, see Micrososft guide for [building and running C++](https://learn.microsoft.com/en-us/cpp/build/vscpp-step-2-build?view=msvc-170) for further details.
  - don't forget to set the compilation method to release (not debug, which is default)

## Usage

- Run the `engine` binary.
- Communication with the engine is done via commands.

## Commands

- Program provides several commands, which allow user to communicate with the chess engine.
- User can setup a position from fen, show current position, play his moves, get list of legal moves, get evaluation of the position, perform perft or play against the engine.

### Position command

1. `show`

   - Shows the current position.
   - `position show`

1. `move`

   - Makes the move on the current board.
   - Move is in [UCI](https://en.wikipedia.org/wiki/Universal_Chess_Interface) format. e.g. `b1c3`, `e1g1` (short castle), `d7d8q` (queen promotion).
   - `position move e2e4`

1. `fen`
   - Loads position from [fen](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation) string.
   - `position fen 6k1/8/6K1/5R2/8/8/8/8 w - - 0 1`

### Engine

1. `eval`

   - Gives evaluation of the current position.
   - The higher the number, the better the position is for white, and vice versa.
   - User must specify depth parameter.

   - `engine eval 4`

1. `moves_eval`

   - Returns normalized moves distribution in current position for given depth.
   - `engine moves_eval 4`

1. `play_best`

   - Plays the best move according to the distribution for given depth.
   - `engine play_best 4`

1. `perft`
   - Makes [perft](https://www.chessprogramming.org/Perft) from the current position to given depth.
   - `engine perft 3`

---

# Technical documentation

## Program structure

- Program consists of 3 modules.

1. [Chess](##chess)
   - Complete implementation of chess.
   - [Is thoroughly tested](###testing).
1. [Engine](##chess-engine)

   - Evalutates the position and specific moves.

1. API
   - Puts everything together to allow user interaction.

## Chess

- Complete [chess rules](https://en.wikipedia.org/wiki/Rules_of_chess) are implemented.
- This includes correct castling, promotion moves, en passant moves etc ...
- What is not implemented are some tournament rules.
  - Specifically: 50 moves draw rule, 3 move repetition.

### Testing

- The chess implementation is thoroughly tested.
- See Chess_Tests module.
- Tests test many edge cases ranging from pieces in pins to weird enpassants, ...
  - Look at the concrete tests for more information.
- Tests were also performed using [perft method](https://www.chessprogramming.org/Perft).
- On starting position, but also on [positions](https://www.chessprogramming.org/Perft_Results) on which bugs were found in many engines in production.
  - These positions can be found in the Chess_Tests project.

## Chess Engine

- Uses [minimax with alpha beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning).
- When searching for best positions mid minimax, legal moves are sorted according to quick evaluation function, to further utilize alpha-beta.
- In the final depth, [full evaluation function](###evaluation-function) is used.
- This score / evaluation is then backpropagated.
  - In case of win for white, `INT_MAX` is returned (for black `INT_MIN`). In case of draw, `0` is returned.

### Evaluation function

- `double Evaluator::full_evaluate(const Position& position) const` implemented in `Evaluator.cpp`

- The full evaluation function takes into account:

1. Piece cost
1. Piece positioning
1. How well pieces cooperate
   1. How are they defended
   1. Their mobility
1. Whether pieces are hanging for free
   - This is useful to at least a littlbe bit account for the [Horizon effect](https://en.wikipedia.org/wiki/Horizon_effect).
1. How cut off is opposite king
   - This is useful in many endgames (e.g. king + rook vs king), so the engine can make progress with giving a mate.

- The quick evaluation function takes into account only piece cost.

## Remarks

### Chess

Chess was harder to implement than I originally thought. As a chess player, I wanted to figure out all the algorithms for piece move generating and proper data structures on my own, but I don't recommend this approach.

It is very easy to miss certaing edge scenarios. Even though I was writing tests during development, it still led me to many hours in perft debugging, because of many situations that didn't occur to me at the time of implementation.

Also for data structures and move implementing, the engine can't be very fast, because the chess implementation is quite basic.

### Evaluation function

In evaluation function, it is an interesting idea to return not `0` on a draw, but some number indicating the position is worse. This way, the engine can be programmed to be more aggressive.

### Future Improvements

1. [Quiscence search](https://en.wikipedia.org/wiki/Quiescence_search)
1. [Transposition tables](https://www.chessprogramming.org/Transposition_Table)
1. [Zobrist hashing](https://www.chessprogramming.org/Zobrist_Hashing)
1. Improve evaluation function
   1. constant tweaking - Genetic algorithms
   1. pawn structure
1. [Better position representation](https://www.chessprogramming.org/Board_Representation)
1. [Memento pattern for make move](https://www.chessprogramming.org/Copy-Make)
1. Try completely different approach with [Monte Carlo Tree search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)
