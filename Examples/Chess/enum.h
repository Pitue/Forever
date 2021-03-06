#ifndef __CHESS_ENUM_H__
#define __CHESS_ENUM_H__

enum TEXTURES : size_t {
	MENU_BACKGROUND = 0,
	MENU_BUTTON,
	MENU_BUTTON_FOCUS,

	GAME_BOARD,

	GAME_BLACK_PAWN,
	GAME_BLACK_ROOK,
	GAME_BLACK_BISHOP,
	GAME_BLACK_KNIGHT,
	GAME_BLACK_KING,
	GAME_BLACK_QUEEN,

	GAME_WHITE_PAWN,
	GAME_WHITE_ROOK,
	GAME_WHITE_BISHOP,
	GAME_WHITE_KNIGHT,
	GAME_WHITE_KING,
	GAME_WHITE_QUEEN,

	GAME_MARKING
};

enum class FIGURE : int {
	PAWN = 0,
	ROOK,
	BISHOP,
	KNIGHT,
	KING,
	QUEEN
};

#endif // !__CHESS_ENUM_H__
