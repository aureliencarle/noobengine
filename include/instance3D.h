#pragma once
// Intern inclusion
#include <skybox.h>
#include <cube.h>
#include <base.h>
#include <pave.h>
#include <hitbox.h>

class Instance3D
{

    public:

        std::unique_ptr<Object> object;
        sf::Shader              shader;
        std::string             tag      = "none";
        glm::vec3               position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3               scale    = glm::vec3(1.0f, 1.0f, 1.0f);

        void draw(glm::mat4 &view, 
                  glm::mat4 &projection
                 )
        {
            object->draw(shader, view, projection, position, scale);
        }

/*
        std::array<float, 3> min()
        {
            return std::array<float, 3>{
                    position[0] - scale[0]*std::abs(object->vertices[0]), 
                    position[1] - scale[1]*std::abs(object->vertices[1]), 
                    position[2] - scale[2]*std::abs(object->vertices[2])
                };
        }

        std::array<float, 3> max()
        {
            return std::array<float, 3>{
                position[0] + scale[0]*std::abs(object->vertices[0]), 
                position[1] + scale[1]*std::abs(object->vertices[1]), 
                position[2] + scale[2]*std::abs(object->vertices[2])
            };
        }

        std::array<std::array<float, 3>, 6> normal()
        {
            return std::array<std::array<float, 3>, 6>{
                {0.0f,0.0f,0.0f},
                {0.0f,0.0f,0.0f},
                {0.0f,0.0f,0.0f},
                {0.0f,0.0f,0.0f},
                {0.0f,0.0f,0.0f},
                {0.0f,0.0f,0.0f}
            };
        }
*/
};