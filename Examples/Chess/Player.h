#ifndef __CHESS_PLAYER_H__
#define __CHESS_PLAYER_H__

#include <vector>
#include "Figure.h"

class GameScene;
class Spielfeld;
class Figure;

class Player {
public:
	GameScene* scene_;
	Spielfeld* spielfeld_;
	std::vector<Figure*> figures;

	Figure* king_;

	Player(GameScene* scene, Spielfeld* spielfeld) 
		:scene_{ scene }, king_{ nullptr }, spielfeld_{ spielfeld } {}

	inline void DeleteAll() {
		king_ = nullptr;
		figures.clear();
	}

	bool IsInCheck(Player& other);
	bool IsInCheckmate(Player& other);
};

#endif // !__CHESS_PLAYER_H__