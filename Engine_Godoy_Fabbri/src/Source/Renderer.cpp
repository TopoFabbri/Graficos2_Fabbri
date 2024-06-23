#include "Renderer.h"

#include <fstream>

namespace ToToEng
{
    Renderer::Renderer(Window* window, Camera* camera)
    {
        this->window = window;

        ShaderProgramSource shaderSource = parseShader("../res/shaders/Basic.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        shader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/Shape.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        shapeShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        shaderSource = parseShader("../res/shaders/3D.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        shader3D = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());

        glCall(u_TransformLocation = glGetUniformLocation(shader, "u_Transform"));
        _ASSERT(u_TransformLocation != -1);

        glCall(u_ShapeTransformLocation = glGetUniformLocation(shapeShader, "u_Transform"));
        _ASSERT(u_TransformLocation != -1);

        glCall(glEnable(GL_DEPTH_TEST));
        glCall(glDepthFunc(GL_LESS));

        glCall(glEnable(GL_BLEND));
        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        glCall(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE));
        glCall(glEnable(GL_SAMPLE_ALPHA_TO_ONE));

        glCall(glEnable(GL_ALPHA_TEST));
        glCall(glAlphaFunc(GL_GREATER, 0.1f));

        setProjection(perspective(radians(45.f),
                                  static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
                                  0.1f, 100.f));
        cameraPos = vec3(0.0f, 0.0f, 3.0f);

        view = lookAt(cameraPos, {0, 0, 0}, {0, 1, 0});
    }

    Renderer::~Renderer()
    {
        glDeleteProgram(shader);
    }

    void Renderer::beginDraw()
    {
        glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::endDraw()
    {
        glCall(glfwSwapBuffers(window->getWindow()));
    }

    void Renderer::genVertexBuffer(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id,
                                   unsigned int qty)
    {
        glCall(glGenVertexArrays(id, &VAO));
        glCall(glGenBuffers(id, &VBO));

        glCall(glBindVertexArray(VAO));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * qty * 12, vertices, GL_STATIC_DRAW));

        glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), static_cast<void*>(0)));
        glCall(glEnableVertexAttribArray(0));

        glCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))));
        glCall(glEnableVertexAttribArray(1));

        glCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))));
        glCall(glEnableVertexAttribArray(1));

        glCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), reinterpret_cast<void*>(7 * sizeof(float))));
        glCall(glEnableVertexAttribArray(2));
    }

    void Renderer::genIndexBuffer(unsigned int& IBO, unsigned int indices[], unsigned int id, unsigned int qty)
    {
        glCall(glGenBuffers(id, &IBO));
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * qty, indices, GL_STATIC_DRAW));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        glCall(glBindVertexArray(0));
    }

    void Renderer::deleteBuffers(unsigned int& VBO, unsigned int& IBO, unsigned int& EBO, unsigned int id)
    {
        glDeleteVertexArrays(id, &VBO);
        glDeleteBuffers(id, &IBO);
        glDeleteBuffers(id, &EBO);
        glDeleteProgram(shader);
    }

    void Renderer::drawEntity2D(unsigned int& VAO, unsigned int indexQty, vec4 color, mat4 trans, unsigned int texture)
    {
        mat4 pvm = projection * view * trans;

        glCall(glUseProgram(shader));
        glCall(glUniform1i(glGetUniformLocation(shader, "ourTexture"), 0));
        glCall(u_ColorLocation = glGetUniformLocation(shader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));

        glCall(glActiveTexture(GL_TEXTURE0));
        glCall(glBindTexture(GL_TEXTURE_2D, texture));
        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_TransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawEntity3D(unsigned& VAO, unsigned indexQty, Material mat, mat4 trans)
    {
        glCall(glUseProgram(shader3D));

        glCall(glUniformMatrix4fv(glGetUniformLocation(shader3D, "model"), 1, GL_FALSE, glm::value_ptr(trans)));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shader3D, "view"), 1, GL_FALSE, glm::value_ptr(view)));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shader3D, "projection"), 1, GL_FALSE, glm::value_ptr(projection)));

        glCall(glUniform3f(glGetUniformLocation(shader3D, "material.ambient"), mat.getAmbient().x, mat.getAmbient().y, mat.getAmbient().z));
        glCall(glUniform3f(glGetUniformLocation(shader3D, "material.diffuse"), mat.getDiffuse().x, mat.getDiffuse().y, mat.getDiffuse().z));
        glCall(glUniform3f(glGetUniformLocation(shader3D, "material.specular"), mat.getSpecular().x, mat.getSpecular().y, mat.getSpecular().z));
        glCall(glUniform1f(glGetUniformLocation(shader3D, "material.shininess"), mat.getShininess()));
        
        glCall(glUniform3f(glGetUniformLocation(shader3D, "light.ambient"), light.getAmbient().x, light.getAmbient().y, light.getAmbient().z));
        glCall(glUniform3f(glGetUniformLocation(shader3D, "light.diffuse"), light.getDiffuse().x, light.getDiffuse().y, light.getDiffuse().z));
        glCall(glUniform3f(glGetUniformLocation(shader3D, "light.specular"), light.getSpecular().x, light.getSpecular().y, light.getSpecular().z));
        glCall(glUniform3f(glGetUniformLocation(shader3D, "light.direction"), light.getDirection().x, light.getPos().y, light.getPos().z));

        glCall(glUniform3f(glGetUniformLocation(shader3D, "viewPos"), cameraPos.x, cameraPos.y, cameraPos.z));

        glCall(glBindVertexArray(VAO));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawShape(unsigned& VAO, unsigned indexQty, vec4 color, mat4 trans)
    {
        mat4 pvm = projection * view * trans;

        glCall(glUseProgram(shapeShader));
        glCall(u_ColorLocation = glGetUniformLocation(shapeShader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));

        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_ShapeTransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::setProjection(mat4 projection)
    {
        this->projection = projection;
    }

    void Renderer::setView(mat4 view)
    {
        this->view = view;
    }

    unsigned int Renderer::compileShader(unsigned int type, const char* source)
    {
        unsigned int id = glCreateShader(type);
        glCall(glShaderSource(id, 1, &source, nullptr));
        glCall(glCompileShader(id));

        int result;
        glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (!result)
        {
            int length;
            glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = new char[length];
            glCall(glGetShaderInfoLog(id, length, &length, message));

            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
                std::endl;
            std::cout << message << std::endl;

            glCall(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int Renderer::createShader(const char* vShader, const char* fShader)
    {
        glCall(unsigned int program = glCreateProgram());
        glCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vShader));
        glCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fShader));

        glCall(glAttachShader(program, vs));
        glCall(glAttachShader(program, fs));
        glCall(glLinkProgram(program));
        glCall(glValidateProgram(program));

        glCall(glDeleteShader(vs));
        glCall(glDeleteShader(fs));

        return program;
    }

    Renderer::ShaderProgramSource Renderer::parseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        enum class ShaderType
        {
            None = -1,
            Vertex = 0,
            Fragment = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::None;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::Vertex;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::Fragment;
            }
            else
            {
                ss[static_cast<int>(type)] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    void Renderer::glClearError()
    {
        while (glGetError());
    }

    bool Renderer::glLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (" << error << "): "
                << function << " " << file << ": " << line << std::endl;
            return false;
        }

        return true;
    }
}
