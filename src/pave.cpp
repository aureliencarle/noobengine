#include <pave.h>
// OpenGL library
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
// SFML library
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Image.hpp>
// Standard library
#include <iostream>

////////////////////
constexpr float PAVE_SIZE = 100;
constexpr float TEXT      = 50;
std::vector<float> VERTICES_PAVE // n = 30
{    
        -PAVE_SIZE,  0.0f, -PAVE_SIZE,  0.0f, TEXT,
         PAVE_SIZE,  0.0f, -PAVE_SIZE,  TEXT, TEXT,
         PAVE_SIZE,  0.0f,  PAVE_SIZE,  TEXT, 0.0f,
         PAVE_SIZE,  0.0f,  PAVE_SIZE,  TEXT, 0.0f,
        -PAVE_SIZE,  0.0f,  PAVE_SIZE,  0.0f, 0.0f,
        -PAVE_SIZE,  0.0f, -PAVE_SIZE,  0.0f, TEXT,
};

////////////////////
Pave::Pave(std::string const &textureName)
{
    setup(VERTICES_PAVE);
    textureID = initTexture(textureName);    
}

////////////////////
Pave::Pave(std::vector<std::string> const &textureName)
{
    setup(VERTICES_PAVE);
    textureID = initTexture(textureName); 
}

////////////////////
void Pave::setup(std::vector<float> const &vertices)
{
    // Declare VAO and VBO with OpenGL
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    // Fill array buffer with vertices table
    glBufferData(GL_ARRAY_BUFFER, 
                 vertices.size() * sizeof(vertices), 
                 &vertices.front(), 
                 GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 
                          3, 
                          GL_FLOAT, GL_FALSE, 
                          5 * sizeof(float), 
                          (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coord attribute
    glVertexAttribPointer(1, 
                          2, 
                          GL_FLOAT, GL_FALSE, 
                          5 * sizeof(float), 
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);    
}

////////////////////
Pave::~Pave(){
    destroy();
}

////////////////////
unsigned int Pave::initTexture(std::string const &textureName)
{
    unsigned int textureID; 
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // load image, create texture and generate mipmaps
    sf::Image image;
    image.loadFromFile(textureName);
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;
    if(image.getPixelsPtr()){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture "<< textureName << std::endl;
    }
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}   

////////////////////
unsigned int Pave::initTexture(std::vector<std::string> const &textureName)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // load image, create texture and generate mipmaps
    sf::Image image;
    image.loadFromFile(textureName.front());
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;
    if(image.getPixelsPtr()){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture "<< textureName.front() << std::endl;
    }
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}

////////////////////
void Pave::destroy()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
}

////////////////////
void Pave::draw(sf::Shader      &shader, 
                glm::mat4       &view, 
                glm::mat4       &projection, 
                glm::vec3 const &position,
                glm::vec3 const &scale)
{
    shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr((view))));
    shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, position);
    //float angle = 20.0f * position.x;
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    model = glm::scale(model, scale);
    shader.setUniform("model", sf::Glsl::Mat4(glm::value_ptr(model)));
    
    sf::Shader::bind(&shader);
    glBindVertexArray(vertexArrayObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    sf::Shader::bind(NULL);
}
