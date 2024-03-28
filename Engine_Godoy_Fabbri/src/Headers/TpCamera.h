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
        TpCamera();
        ~TpCamera() override;

        void setReference(glm::vec3 reference);
        void updateCamera();
    };
}
