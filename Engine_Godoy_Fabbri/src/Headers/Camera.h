#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include "Exports.h"

namespace ToToEng
{
	class TOTO_API Camera
	{
	protected:
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 rot;

		glm::vec3 getRight();
		void updateRotation();
	
	public:
		static Camera* main;

		Camera();
		virtual ~Camera();

		glm::mat4 getView();

		glm::vec3 getPos();
		glm::vec3 getForward();

		void moveUp(float amount);
		void moveRight(float amount);
		void moveForward(float amount);
		
		void rotateYaw(float amount);
		void rotatePitch(float amount);
	};
}