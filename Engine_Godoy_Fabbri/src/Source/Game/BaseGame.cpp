#include "BaseGame.h"

#include "CollisionManager.h"
#include "Model.h"
#include "Sprite.h"
#include "TpCamera.h"

namespace ToToEng
{
	BaseGame::BaseGame(int width, int height, const char* title)
	{
		camera = new Camera();
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

			onDraw();
			
			renderer->endDraw();

			glfwPollEvents();
		}
	}

	void BaseGame::endGame()
	{
		window->close();
	}

	void BaseGame::drawLine(vec3 start, vec3 end, vec4 color)
	{
		renderer->drawLine(start, end, color);
	}

	void BaseGame::drawWireBox(vec3 center, vec3 size, vec4 color)
	{
		const vec3 aa = center - size / 2.f;
		const vec3 bb = center + size / 2.f;

		drawLine(aa, vec3(bb.x, aa.y, aa.z), color);
		drawLine(aa, vec3(aa.x, bb.y, aa.z), color);
		drawLine(aa, vec3(aa.x, aa.y, bb.z), color);
		
		drawLine(bb, vec3(aa.x, bb.y, bb.z), color);
		drawLine(bb, vec3(bb.x, aa.y, bb.z), color);
		drawLine(bb, vec3(bb.x, bb.y, aa.z), color);

		drawLine({aa.x, aa.y, bb.z}, {bb.x, aa.y, bb.z}, color);
		drawLine({aa.x, aa.y, bb.z}, {aa.x, bb.y, bb.z}, color);
		drawLine({aa.x, bb.y, aa.z}, {aa.x, bb.y, bb.z}, color);
		drawLine({aa.x, bb.y, aa.z}, {bb.x, bb.y, aa.z}, color);
		drawLine({bb.x, aa.y, aa.z}, {bb.x, bb.y, aa.z}, color);
		drawLine({bb.x, aa.y, aa.z}, {bb.x, aa.y, bb.z}, color);
	}
}
