#pragma once

#include <list>

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Exports.h"

using namespace glm;

namespace ToToEng
{
	class TOTO_API Transform
	{
	private:
		Transform* parent;
		std::list<Transform*> children;
		
		vec3 pos;
		vec3 scale;
		vec3 rot;

		vec3 prevPos;

		mat4 transformMatrix;

		mat4 posMat;
		mat4 scaleMat;
		mat4 rotMat;
		void updateTransformMatrix();

	public:
		Transform(Transform* parent = nullptr);
		~Transform();

		void moveForward(float dist);
		void moveRight(float dist);
		void moveUp(float dist);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void rotateX(float x);
		void rotateY(float y);
		void rotateZ(float z);
		void addChild(Transform* child);
		void removeChild(Transform* child);

#pragma region GETTERS

		Transform* getParent() const;
		std::list<Transform*> getChildren(bool childrenOfChildren = false);
		
		vec3 getPos() const;
		vec3 getScale() const;
		vec3 getRot() const;

		vec3 getPrevPos() const;
		
		mat4 getTransformMatrix() const;

		vec3 up();
		vec3 right();
		vec3 forward();

		void lerpPos(vec3 target, float t);
		void lerpPos(vec2 target, float t);
		void lerpPos2D(vec3 target, float t);

#pragma endregion

#pragma region SETTERS

		void setParent(Transform* parent);
		void setPos(const vec3& v);

		void setScale(const vec3& v);

		void setRot(const vec3& v);

#pragma endregion
	};
}
