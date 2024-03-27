#include "Input.h"

namespace ToToEng
{
	std::list<Input::KeyCode> Input::keysPressed;

	Input* Input::instance = nullptr;
	
	Input::Input()
	{
		if (instance != nullptr && this != instance)
		{
			delete this;
			return;
		}
		
		instance = this;

		window = Window::getInstance()->getWindow();

		mouseLastPos = { 0, 0 };
		mouseDelta = { 0, 0 };

		glfwSetCursorPosCallback(window, mouseCallback);
		glfwSetKeyCallback(window, keyCallback);
	}

	Input* Input::getInstance()
	{
		if (!instance)
			instance = new Input();

		return instance;
	}

	bool Input::getKey(const KeyCode keyCode, const Action action)
	{
		switch (action)
		{
			case Pressed:
			{
				const bool pressed = std::find(keysPressed.begin(), keysPressed.end(), keyCode) != keysPressed.end();
				keysPressed.remove(keyCode);
				return pressed;
			}

			case Repeated:
			{
				return glfwGetKey(getInstance()->window, keyCode) == Pressed;
			}

			case Released:
			{
				return glfwGetKey(getInstance()->window, keyCode) == Released;
			}
		}

		return false;
	}

	glm::vec2 Input::getMouseDelta()
	{
		glm::vec2 delta = getInstance()->mouseDelta;
		getInstance()->mouseDelta = glm::vec2(0, 0);
		
		return delta;
	}

	bool Input::setCursorVisibility(bool visibility)
	{
		if (visibility)
			glfwSetInputMode(Window::getInstance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(Window::getInstance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		return visibility;
	}

	void Input::updateCursor(double xpos, double ypos)
	{
		instance->mouseDelta = glm::vec2(instance->mouseLastPos.x - xpos, instance->mouseLastPos.y - ypos);
		instance->mouseLastPos = glm::vec2(xpos, ypos);
	}

	void mouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::updateCursor(xpos, ypos);
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, const int action, int mods)
	{
		switch (action)
		{
		case GLFW_RELEASE:
			Input::keysPressed.remove(static_cast<Input::KeyCode>(key));
			break;

		case GLFW_PRESS:
			Input::keysPressed.push_back(static_cast<Input::KeyCode>(key));
			break;

		default:;
		}
	}
}