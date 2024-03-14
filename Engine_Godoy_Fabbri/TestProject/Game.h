#pragma once

#include "Character.h"
#include "../src/Headers/BaseGame.h"

using namespace ToToEng;

class Game :
	public BaseGame
{
private:
	Character* character;
	
public:
	Game(bool is3D, int width, int height, const char* title);
	~Game() override;

	void update() override;
};