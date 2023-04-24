#include "../Chess/Chess.hpp"
#include <string>

class FEN {
public:
    inline static Position parse(const std::string& fen) {
        Position position;

        const size_t size = fen.size();
        size_t iter = 0;
        int index = 0;

        // parse the board first
        for (; (iter < size) and (fen[iter] != ' '); iter++)
        {
            if (fen[iter] == '/')
                continue;


            if (isdigit(fen[iter]))
                index += (fen[iter] - '0'); // converts char digit to int. `5` to 5

            else
            {
                position.place(Position::to_square(index), char_to_piece(fen[iter]));
                ++index;
            }
        }

        position.to_play(fen[iter + 1] == 'w' ? Color::White : Color::Black);

        bool wking_castle = false;
        bool bking_castle = false;
        bool bqueen_castle = false;
        bool wqueen_castle = false;

        for (iter += 3; (iter < size) and (fen[iter] != ' '); iter++)
        {
            if (fen[iter] == 'k')
                bking_castle = true;

            else if (fen[iter] == 'K')
                wking_castle = true;

            else if (fen[iter] == 'q')
                bqueen_castle = true;

            else if (fen[iter] == 'Q')
                wqueen_castle = true;
        }

        if (!wking_castle) {
            position.add_info(PositionInfo::WRrook_moved);
        }

        if (!bking_castle) {
            position.add_info(PositionInfo::BRrook_moved);
        }

        if (!bqueen_castle) {
            position.add_info(PositionInfo::BLrook_moved);
        }

        if (!wqueen_castle) {
            position.add_info(PositionInfo::WLrook_moved);
        }

        try {
			square_t enpassant = square_t::h(fen.substr(iter + 1, 3));
            index_t k = position.to_play() == Color::White ? 1 : -1;
            position.last_move(move_t(square_t(enpassant.rank(), enpassant.file() + k), square_t(enpassant.rank(), enpassant.file() - k)));
        }
        catch(std::exception&) { /* - */ }

        return position;
    }

private:
    inline static piece_t char_to_piece(char p) {
        switch (p) {
        case 'k':
            return Piece::King | Color::Black;
        case 'q':
            return Piece::Queen | Color::Black;
        case 'b':
            return Piece::Bishop | Color::Black;
        case 'n':
            return Piece::Knight | Color::Black;
        case 'r':
            return Piece::Rook | Color::Black;
        case 'p':
            return Piece::Pawn | Color::Black;
        case 'K':
            return Piece::King | Color::White;
        case 'Q':
            return Piece::Queen | Color::White;
        case 'B':
            return Piece::Bishop | Color::White;
        case 'N':
            return Piece::Knight | Color::White;
        case 'R':
            return Piece::Rook | Color::White;
        case 'P':
            return Piece::Pawn | Color::White;
        default:
            throw std::invalid_argument("invalid character. Can't convert to piece.");
        }
    }
};
