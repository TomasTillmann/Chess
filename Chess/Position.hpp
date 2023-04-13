#include <cstdint>
#include <vector>

typedef uint8_t piece_t;
typedef uint8_t color_t;

static piece_t None		= piece_t{ 0b00000000 };
static piece_t Pawn		= piece_t{ 0b00000001 };
static piece_t Rook		= piece_t{ 0b00000010 };
static piece_t Knight	= piece_t{ 0b00000011 };
static piece_t Bishop	= piece_t{ 0b00000100 };
static piece_t Queen	= piece_t{ 0b00000101 };
static piece_t King		= piece_t{ 0b00000111 };

static color_t White	= color_t{ 0b00001000 };
static color_t Black	= color_t{ 0b00010000 };

struct square_t {
public:
	uint8_t file() { return _file; }
	uint8_t rank() { return _rank; }

	square_t(uint8_t file, uint8_t rank) 
		: _file(file), _rank(rank) { }

private:
	uint8_t _file;
	uint8_t _rank;
};

typedef uint8_t moveType_t;

static moveType_t Normal		= moveType_t{ 0b00000000 };
static moveType_t Castle		= moveType_t{ 0b00000001 };
static moveType_t EnPassant		= moveType_t{ 0b00000010 };
static moveType_t Promotion		= moveType_t{ 0b00000011 };

struct move_t {
public:
	square_t from() { return _from; }
	square_t to() { return _to; }
	moveType_t type() { return _type; }

	move_t(square_t from, square_t to, moveType_t type) 
		: _from(from), _to(to), _type(type) { }

private:
	square_t _from;
	square_t _to;
	moveType_t _type;
};

struct position_t {
private:
	std::vector<piece_t> pieces;

public:
	position_t() {
		pieces.resize(64);
	}

	position_t move(move_t move) const {
		throw "not implemented";
	}

	void place(square_t square, piece_t piece) {
		throw "not implemented";
	}
};
