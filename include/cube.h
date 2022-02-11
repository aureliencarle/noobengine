#pragma once
// Intern inclusion
#include <camera.h>
#include <object.h>
// OpenGL library
#include <GL/glew.h>
// SFML library
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>

class Cube : public Object{

    protected:

        void setup(std::vector<float> const &vertices) override;
        unsigned int initTexture(std::string const &textureName) override;
        unsigned int initTexture(std::vector<std::string> const &textureName) override;
        void destroy() override;

    public:

        Cube(std::string const &textureName);
        Cube(std::vector<std::string> const &textureName);
        ~Cube() override;
        void draw(sf::Shader      &shader, 
                  glm::mat4       &view, 
                  glm::mat4       &projection, 
                  glm::vec3 const &position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 const &scale    = glm::vec3(1.0f, 1.0f, 1.0f)
                 ) override;
};