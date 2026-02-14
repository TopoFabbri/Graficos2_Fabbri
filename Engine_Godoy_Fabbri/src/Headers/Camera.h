#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <list>

#include "Exports.h"
#include "Plane.h"

namespace ToToEng
{
	class Renderer;

	class TOTO_API Camera
	{
	protected:
		glm::vec3 pos;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 rot;

		float frustumFov;
		float nearPlane;
		float farPlane;
		float aspect;
		glm::vec3 frustumCorners[8];

		std::list<Plane*> frustumPlanes;

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

		void updateFrustum(float aspect, float near, float far);
		std::list<Plane*> getFrustumPlanes() const;

		void setFrustumFov(float fov);
		float getFrustumFov() const;

		void drawFrustum(Renderer* renderer);
	};
}