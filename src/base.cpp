#include <base.h>
// OpenGL library
#include <glm/gtc/matrix_transform.hpp>

////////////////////
constexpr float BASE_WIDTH = 0.05f;


////////////////////
Base::Base()
{
    e[0] = std::make_unique<Cube>("./assets/sample/red.png");
    e[1] = std::make_unique<Cube>("./assets/sample/blue.png");
    e[2] = std::make_unique<Cube>("./assets/sample/green.png");
}

////////////////////
Base::~Base()
{
}

////////////////////
void Base::destroy()
{}

////////////////////
void Base::setup([[maybe_unused]] std::vector<float> const &vertices)
{}

////////////////////
unsigned int Base::initTexture([[maybe_unused]] std::string const &textureName)
{
    return 0;
}

////////////////////
unsigned int Base::initTexture([[maybe_unused]] std::vector<std::string> const &textureName)
{
    return 0;
}

////////////////////
void Base::draw(sf::Shader      &shader, 
                glm::mat4       &view, 
                glm::mat4       &projection,
                glm::vec3 const &position,
                glm::vec3 const &scale)
{
    std::vector<glm::vec3> positionBase{
        glm::vec3(BASE_WIDTH, 0.0f, 0.0f),
        glm::vec3(0.0f, BASE_WIDTH, 0.0f),
        glm::vec3(0.0f, 0.0f, BASE_WIDTH)
    };
    std::vector<glm::vec3> scaleBase{
        glm::vec3(1.0f, 0.01f, 0.01f),
        glm::vec3(0.01f, 1.0f, 0.01f),
        glm::vec3(0.01f, 0.01f, 1.0f)
    };

    for(unsigned int i = 0; i < e.size(); ++i){
        for(unsigned int j = 0; j < e.size(); ++j){
            positionBase[i][j] += position[j];
            scaleBase[i][j]    *= scale[j];
        }
        e[i]->draw(shader, view, projection, positionBase[i], scaleBase[i]);
    }  
}
