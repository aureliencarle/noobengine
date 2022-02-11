#pragma once 
// Intern inclusion
#include <object.h>

class Pave : public Object
{
    protected:

        void setup(std::vector<float> const &vertices) override;
        unsigned int initTexture(std::string const &textureName) override;
        unsigned int initTexture(std::vector<std::string> const &textureName) override;
        void destroy() override;

    public:

        Pave(std::string const &textureName);
        Pave(std::vector<std::string> const &textureName);
        ~Pave() override;
        void draw(sf::Shader      &shader, 
                  glm::mat4       &view, 
                  glm::mat4       &projection, 
                  glm::vec3 const &position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 const &scale    = glm::vec3(1.0f, 1.0f, 1.0f)
                 ) override;
};