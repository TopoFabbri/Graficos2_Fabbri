#pragma once
#include "Camera.h"

namespace ToToEng
{
    class TOTO_API TpCamera : public Camera
    {
    protected:
        glm::vec3 reference;
        glm::vec3 offset;
        
    public:
        TpCamera(glm::vec3 reference = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 offset = glm::vec3(0.0f, 0.5f, -2.0f));
        ~TpCamera() override;

        void setReference(glm::vec3 reference);
        void setOffset(glm::vec3 offset);
        void updateCamera();
    };
}
