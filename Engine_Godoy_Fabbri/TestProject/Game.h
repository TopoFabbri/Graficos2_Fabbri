#pragma once

#include "../src/Headers/BaseGame.h"

using namespace ToToEng;

class Game :
	public BaseGame
{
private:
	std::list<vec3> rotations = std::list<vec3>();
	 float camSpeed;
	
public:
	Game(int width, int height, const char* title);
	~Game() override;

	void update() override;
};