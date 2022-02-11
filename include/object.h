#pragma once
// Intern inclusion
#include <camera.h>
#include <debugger.h>
// OpenGL library
#include <GL/glew.h>
// SFML library
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>
// Standard library
#include <vector>
#include <string>


class Object{

    protected:

        /**
         *
         */
        unsigned int vertexArrayObject;
        
        /**
         *
         */
        unsigned int vertexBufferObject;
        
        /**
         *
         */
        unsigned int textureID;

        /**
         *
         */
        virtual void setup(std::vector<float> const &vertices) = 0;

        /**
         *
         */
        virtual unsigned int initTexture(std::string const &textureName) = 0;

        /**
         *
         */
        virtual unsigned int initTexture(std::vector<std::string> const &textureName) = 0;

        /**
         *
         */
        virtual void destroy() = 0;

    public:

        /**
         *
         */
        Object() = default;

        /**
         *
         */
        virtual ~Object() = default;

        /**
         *
         */
        virtual void draw(sf::Shader      &shader, 
                          glm::mat4       &view, 
                          glm::mat4       &projection, 
                          glm::vec3 const &position = glm::vec3(0.0f, 0.0f, 0.0f),
                          glm::vec3 const &scale    = glm::vec3(1.0f, 1.0f, 1.0f)
                         ) = 0;

};
