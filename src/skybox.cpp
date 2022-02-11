#include <skybox.h>
// OpenGL library
#include <glm/gtc/type_ptr.hpp>
// SFML library
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Image.hpp>
// Standard library
#include <iostream>

////////////////////
constexpr float SIZE = 0.5f;

std::vector<float> VERTICES_SKYBOX // n = 108
{    
    -SIZE,  SIZE, -SIZE,
    -SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,

    -SIZE, -SIZE,  SIZE,
    -SIZE, -SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE,  SIZE,
    -SIZE, -SIZE,  SIZE,

     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,

    -SIZE, -SIZE,  SIZE,
    -SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE, -SIZE,  SIZE,
    -SIZE, -SIZE,  SIZE,

    -SIZE,  SIZE, -SIZE,
     SIZE,  SIZE, -SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
    -SIZE,  SIZE,  SIZE,
    -SIZE,  SIZE, -SIZE,

    -SIZE, -SIZE, -SIZE,
    -SIZE, -SIZE,  SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
    -SIZE, -SIZE,  SIZE,
     SIZE, -SIZE,  SIZE         
};

////////////////////
Skybox::Skybox(std::vector<std::string> &faces)
{
    setup(VERTICES_SKYBOX);
    textureID = initTexture(faces);
}

////////////////////
Skybox::~Skybox(){
    destroy();
}

////////////////////
void Skybox::setup(std::vector<float> const &vertices)
{
    // Declare VAO and VBO with OpenGL
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    // Fill array buffer with vertices table
    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(float), 
                 &vertices.front(),
                 GL_STATIC_DRAW
                );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 
                          3, 
                          GL_FLOAT, GL_FALSE, 
                          3 * sizeof(float), 
                          (void*)0
                         );
}

////////////////////
unsigned int Skybox::initTexture([[maybe_unused]] std::string const& faces)
{
    return 0;
}

////////////////////
unsigned int Skybox::initTexture(std::vector<std::string> const& faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for(size_t i = 0; i != faces.size(); ++i){
        sf::Image image;
        image.loadFromFile(faces[i]);
        unsigned int width = image.getSize().x;
        unsigned int height = image.getSize().y;
        if (image.getPixelsPtr()){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        }
        else{
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);    

    return textureID;
}

////////////////////
void Skybox::destroy()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexArrayObject);      
}

////////////////////
void Skybox::draw(sf::Shader      &shader,
                  glm::mat4       &view,
                  glm::mat4       &projection,
                  [[maybe_unused]] glm::vec3 const &position,
                  [[maybe_unused]] glm::vec3 const &scale
                 )
{
    shader.setUniform("skybox", int(0));    
    // change depth function so depth test passes when values are equal to depth buffer's content
    shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(glm::mat4(glm::mat3(view)))));
    shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));

    sf::Shader::bind(&shader);
    // change depth function so depth test passes when values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL); 
    glBindVertexArray(vertexArrayObject);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    sf::Shader::bind(NULL);
}
