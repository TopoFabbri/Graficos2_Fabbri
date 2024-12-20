#include "Renderer.h"

#include <fstream>
#include <sstream>

#include "Camera.h"

namespace ToToEng
{
    Camera* Camera::main = nullptr;
    
    Renderer::Renderer(Window* window)
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

        shaderSource = parseShader("../res/shaders/Mesh.shader");
        std::cout << glGetString(GL_VERSION) << std::endl;
        meshShader = createShader(shaderSource.vertexSource.c_str(), shaderSource.fragmentSource.c_str());
        
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

    void Renderer::bindTexture(const char* name, unsigned int &i, unsigned int &textureId)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glUniform1i(glGetUniformLocation(meshShader, name), i);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    void Renderer::genVertexBuffer(unsigned int& VBO, unsigned int& VAO, float vertices[], unsigned int id, unsigned int qty)
    {
        glCall(glGenVertexArrays(id, &VAO));
        glCall(glGenBuffers(id, &VBO));
        
        glCall(glBindVertexArray(VAO));

        glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * qty * 8, vertices, GL_STATIC_DRAW));
        
        glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(0)));
        glCall(glEnableVertexAttribArray(0));
        
        glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))));
        glCall(glEnableVertexAttribArray(1));
        
        glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float))));
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
        mat4 pvm = projection * Camera::main->getView() * trans;

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
        glCall(glUniformMatrix4fv(glGetUniformLocation(shader3D, "view"), 1, GL_FALSE, glm::value_ptr(Camera::main->getView())));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shader3D, "projection"), 1, GL_FALSE, glm::value_ptr(projection)));

        glCall(glUniform1i(glGetUniformLocation(shader3D, "material.diffuse"), 0));
        glCall(glUniform1i(glGetUniformLocation(shader3D, "material.specular"), 1));
        glCall(glUniform1f(glGetUniformLocation(shader3D, "material.shininess"), mat.getShininess()));

        glCall(glActiveTexture(GL_TEXTURE0));
        glCall(glBindTexture(GL_TEXTURE_2D, mat.getDiffuse()));
        glCall(glActiveTexture(GL_TEXTURE1));
        glCall(glBindTexture(GL_TEXTURE_2D, mat.getSpecular()));

        int i = 0;

        for (LightSource* light : LightSource::lights)
        {
            switch (light->getType())
            {
            case LightSource::Type::Dir:
                sendDirectionalLight(static_cast<DirectionalLight*>(light), i, shader3D);
                break;
            
            case LightSource::Type::Point:
                sendPointLight(static_cast<PointLight*>(light), i, shader3D);
                break;
            
            case LightSource::Type::Spot:
                sendSpotLight(static_cast<SpotLight*>(light), i, shader3D);
                break;
            }
        
            i++;
        }
        
        for (int j = i; j < maxLights; j++)
        {
            DirectionalLight* light = new DirectionalLight();
            light->setAmbient({ 0.0f, 0.0f, 0.0f });
            light->setDiffuse({ 0.0f, 0.0f, 0.0f });
            light->setSpecular({ 0.0f, 0.0f, 0.0f });
            sendDirectionalLight(light, j, shader3D);
        
            delete light;
        }

        glCall(glUniform3f(glGetUniformLocation(shader3D, "viewPos"), Camera::main->getPos().x, Camera::main->getPos().y, Camera::main->getPos().z));

        glCall(glBindVertexArray(VAO));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }
    
    void Renderer::drawShape(unsigned& VAO, unsigned indexQty, vec4 color, mat4 trans)
    {
        mat4 pvm = projection * Camera::main->getView() * trans;

        glCall(glUseProgram(shapeShader));
        glCall(u_ColorLocation = glGetUniformLocation(shapeShader, "u_Color"));

        glCall(glUniform4f(u_ColorLocation, color.x, color.y, color.z, color.w));

        glCall(glBindVertexArray(VAO));

        glCall(glUniformMatrix4fv(u_ShapeTransformLocation, 1, GL_FALSE, glm::value_ptr(pvm)));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
    }

    void Renderer::drawMesh(unsigned int& VAO, unsigned int indexQty, mat4 trans)
    {
        glUseProgram(meshShader);

        glUniformMatrix4fv(glGetUniformLocation(meshShader, "model"), 1, GL_FALSE, value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(meshShader, "view"), 1, GL_FALSE, value_ptr(Camera::main->getView()));
        glUniformMatrix4fv(glGetUniformLocation(meshShader, "projection"), 1, GL_FALSE, value_ptr(projection));
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

    void Renderer::setProjection(mat4 projection)
    {
        this->projection = projection;
    }

    void Renderer::sendDirectionalLight(DirectionalLight* light, int i, unsigned int shaderId)
    {
        std::string index = "lights[" + std::to_string(i) + "].";
        
        glUniform1i(glGetUniformLocation(shaderId, (index + "type").c_str()), static_cast<int>(light->getType()));
        glUniform3f(glGetUniformLocation(shaderId, (index + "ambient").c_str()), light->getAmbient().x, light->getAmbient().y, light->getAmbient().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "diffuse").c_str()), light->getDiffuse().x, light->getDiffuse().y, light->getDiffuse().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "specular").c_str()), light->getSpecular().x, light->getSpecular().y, light->getSpecular().z);

        glUniform3f(glGetUniformLocation(shaderId, (index + "direction").c_str()), light->getDirection().x, light->getDirection().y, light->getDirection().z);
    }

    void Renderer::sendPointLight(PointLight* light, int i, unsigned int shaderId)
    {
        std::string index = "lights[" + std::to_string(i) + "].";
        
        glUniform1i(glGetUniformLocation(shaderId, (index + "type").c_str()), static_cast<int>(light->getType()));
        glUniform3f(glGetUniformLocation(shaderId, (index + "ambient").c_str()), light->getAmbient().x, light->getAmbient().y, light->getAmbient().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "diffuse").c_str()), light->getDiffuse().x, light->getDiffuse().y, light->getDiffuse().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "specular").c_str()), light->getSpecular().x, light->getSpecular().y, light->getSpecular().z);

        glUniform3f(glGetUniformLocation(shaderId, (index + "position").c_str()), light->getPos().x, light->getPos().y, light->getPos().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "attenuation").c_str()), light->getAttenuation().x, light->getAttenuation().y, light->getAttenuation().z);
    }

    void Renderer::sendSpotLight(SpotLight* light, int i, unsigned int shaderId)
    {
        std::string index = "lights[" + std::to_string(i) + "].";
        
        glUniform1i(glGetUniformLocation(shaderId, (index + "type").c_str()), static_cast<int>(light->getType()));
        glUniform3f(glGetUniformLocation(shaderId, (index + "ambient").c_str()), light->getAmbient().x, light->getAmbient().y, light->getAmbient().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "diffuse").c_str()), light->getDiffuse().x, light->getDiffuse().y, light->getDiffuse().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "specular").c_str()), light->getSpecular().x, light->getSpecular().y, light->getSpecular().z);

        glUniform3f(glGetUniformLocation(shaderId, (index + "position").c_str()), light->getPos().x, light->getPos().y, light->getPos().z);
        glUniform3f(glGetUniformLocation(shaderId, (index + "direction").c_str()), light->getDirection().x, light->getDirection().y, light->getDirection().z);
        glUniform1f(glGetUniformLocation(shaderId, (index + "cutoff").c_str()), light->getCutoff());
        glUniform1f(glGetUniformLocation(shaderId, (index + "outerCutoff").c_str()), light->getOuterCutoff());
        glUniform3f(glGetUniformLocation(shaderId, (index + "attenuation").c_str()), light->getAttenuation().x, light->getAttenuation().y, light->getAttenuation().z);
    }

    void Renderer::drawModel3D(unsigned int& VAO, unsigned int indexQty, mat4 trans, std::vector<Texture> textures)
    {
        glCall(glUseProgram(meshShader));
        glCall(glUniformMatrix4fv(glGetUniformLocation(meshShader, "model"), 1, GL_FALSE, value_ptr(trans)));
        glCall(glUniformMatrix4fv(glGetUniformLocation(meshShader, "view"), 1, GL_FALSE, value_ptr(Camera::main->getView())));
        glCall(glUniformMatrix4fv(glGetUniformLocation(meshShader, "projection"), 1, GL_FALSE, value_ptr(projection)));
        
        GLint u_Material;

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            u_Material = glGetUniformLocation(meshShader, ("material." + name + number).c_str());
            glUniform1f(u_Material, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        glCall(glUniform1f(glGetUniformLocation(meshShader, "material.shininess"), 32.0f));
        
        int i = 0;

        for (LightSource* light : LightSource::lights)
        {
            switch (light->getType())
            {
            case LightSource::Type::Dir:
                sendDirectionalLight(static_cast<DirectionalLight*>(light), i, meshShader);
                break;
            
            case LightSource::Type::Point:
                sendPointLight(static_cast<PointLight*>(light), i, meshShader);
                break;
            
            case LightSource::Type::Spot:
                sendSpotLight(static_cast<SpotLight*>(light), i, meshShader);
                break;
            }
        
            i++;
        }
        
        for (int j = i; j < maxLights; j++)
        {
            DirectionalLight* light = new DirectionalLight();
            light->setAmbient({ 0.0f, 0.0f, 0.0f });
            light->setDiffuse({ 0.0f, 0.0f, 0.0f });
            light->setSpecular({ 0.0f, 0.0f, 0.0f });
            sendDirectionalLight(light, j, meshShader);
        
            delete light;
        }
        
        glUniform3f(glGetUniformLocation(meshShader, "viewPos"), Camera::main->getPos().x, Camera::main->getPos().y, Camera::main->getPos().z);

        glCall(glBindVertexArray(VAO));

        glCall(glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, 0));

        glCall(glBindVertexArray(0));
        glCall(glUseProgram(0));
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
