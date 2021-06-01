#ifndef __CHESS_GAME_H__
#define __CHESS_GAME_H__

#include <vector>
#include <thread>

#include <Forever.h>

#include "Figure.h"
#include "Player.h"
#include "Feld.h"
#include "Spielfeld.h"

class GameScene : public fr::Scene {
	Spielfeld spielfeld_;

	/*
	0: White won
	1: Black won
	2: Remis
	*/
	void EndGame(Uint8 ergebnis);

public:
	Uint8 game_over_;
	static constexpr int feld_size_ = 8, boarder_ = 18;

	GameScene(fr::Engine* engine, fr::Camera* cam);
	~GameScene();

	inline fr::Engine* Engine() {
		return engine_;
	}
	inline void SetAiMode(bool val) {
		spielfeld_.computer_ = val;
	}

	bool Finished();
	void EventHandle(const fr::Event& evt) override;
	void Tick(const fr::Time& time) override;
	void Draw() override;
};

#endif // !__CHESS_GAME_H__
