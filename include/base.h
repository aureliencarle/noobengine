#pragma once
#include <cube.h>
#include <memory>
// Standard library
#include <array>

class Base : public Object{

    private:

        std::array<std::unique_ptr<Cube>, 3> e;
    
    protected:

        void setup(std::vector<float> const &vertices) override;
        unsigned int initTexture(std::string const &textureName) override;
        unsigned int initTexture(std::vector<std::string> const &textureName) override;
        void destroy() override;

    public:

        Base();
        ~Base();
        void draw(sf::Shader      &shader, 
                  glm::mat4       &view, 
                  glm::mat4       &projection,
                  glm::vec3 const &position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 const &scale    = glm::vec3(1.0f, 1.0f, 1.0f)
                 ) override;
};