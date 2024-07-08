#include "BaseGame.h"

#include "CollisionManager.h"
#include "Model.h"
#include "Sprite.h"
#include "TpCamera.h"

namespace ToToEng
{
	BaseGame::BaseGame(int width, int height, const char* title)
	{
		camera = new TpCamera();
		window = new Window(width, height, title);
		renderer = new Renderer(window);
		collisionManager = new CollisionManager();

		Input::setCursorVisibility(false);
		
		GameTime::resetTime();
	}

	BaseGame::~BaseGame()
	{
		delete renderer;
		delete window;
		delete camera;
		delete collisionManager;

		const int size = static_cast<int>(entities.size());
		
		for (int i = 0; i < size; i++)
		{
			Entity* tmp = entities.front();
			entities.pop_front();
			delete tmp;
		}

		entities.clear();
	}

	void BaseGame::run()
	{
		while (!window->shouldClose())
		{
			GameTime::update();
			
			for (Entity* entity : entities)
				entity->update();
			update();
			
			renderer->beginDraw();

			for (Entity* entity : entities)
				entity->draw();
			
			renderer->endDraw();

			glfwPollEvents();
		}
	}

	void BaseGame::endGame()
	{
		window->close();
	}
}
