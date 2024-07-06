#include "Mesh.h"

namespace ToToEng
{
    Mesh::Mesh(Renderer* renderer): Entity3D(renderer)
    {
        VAO = 0;
        VBO = 0;
        IBO = 0;
        indexQty = 0;
    }

    Mesh::~Mesh()
    {
        clearMesh();
    }

    void Mesh::createMesh(float* vertices, int vertexCount, unsigned int* indices, int indexQty)
    {
        this->indexQty = indexQty;

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexQty, indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
        glEnableVertexAttribArray(positionLocation);

        glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(texLocation);

        glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
        glEnableVertexAttribArray(normalLocation);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

    }

    void Mesh::draw()
    {
        renderer->drawEntity3D(VAO, indexQty, *material, transform.getTransformMatrix());
    }

    void Mesh::clearMesh()
    {
        if (IBO != 0)
        {
            glDeleteBuffers(1, &IBO);
            IBO = 0;
        }
        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
        
            VAO = 0;
        }

        indexQty = 0;
    }
}
