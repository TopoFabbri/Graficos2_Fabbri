#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include "Exports.h"

namespace ToToEng
{
	class TOTO_API Camera
	{
	private:
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 rot;

		glm::vec3 getRight();
		void updateRotation();
	
	public:
		Camera();
		~Camera();

		glm::mat4 getView();

		void moveUp(float amount);
		void moveRight(float amount);
		void moveForward(float amount);
		void rotateYaw(float amount);
		void rotatePitch(float amount);
	};
}