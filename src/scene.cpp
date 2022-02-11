// Intern inclusion
#include <scene.h>
#include <debugger.h>
// OpenGL library
#include <glm/gtc/matrix_transform.hpp>
// SFML library
#include <SFML/Graphics.hpp>
// Standard library
#include <iostream>

unsigned int WIDTH = 1200; 
unsigned int HEIGHT = 800;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

////////////////////
Scene::Scene()
{
    init();
}

////////////////////
void Scene::init()
{
    // Context setting
    settings = std::make_unique<sf::ContextSettings>();
    settings->depthBits         = 24;
    settings->stencilBits       = 8;
    settings->antialiasingLevel = 4;

    // Render window
    window = std::make_unique<sf::Window> (sf::VideoMode(WIDTH, HEIGHT), 
                                           "Noob Engine !!!",
                                           sf::Style::Default, 
                                           *settings
                                          );
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);
    window->setVerticalSyncEnabled(true);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS); // default depth test

    std::string skyboxDirectory = "tropical";
    std::vector<std::string> faces
    {
        "./assets/skybox/"+skyboxDirectory+"/right.png",   // right    nx
        "./assets/skybox/"+skyboxDirectory+"/left.png",    // left     px
        "./assets/skybox/"+skyboxDirectory+"/top.png",     // top      py 180deg
        "./assets/skybox/"+skyboxDirectory+"/bottom.png",  // bottom   ny 180deg
        "./assets/skybox/"+skyboxDirectory+"/front.png",   // front    nz
        "./assets/skybox/"+skyboxDirectory+"/back.png"     // back     pz
    };

    level = std::vector<Instance3D>(6);

    level[0].object   = std::make_unique<Skybox>(faces);
    level[0].tag      = "skybox";
    level[0].shader.loadFromFile("./shaders/skybox.vert", "./shaders/skybox.frag");

    level[1].object   = std::make_unique<Base>();
    level[1].tag      = "base";
    level[1].shader.loadFromFile("./shaders/cube.vert", "./shaders/cube.frag");

    level[2].object   = std::make_unique<Cube>("./assets/sample/metal.png");
    level[2].shader.loadFromFile("./shaders/cube.vert", "./shaders/cube.frag");    
    level[2].position = glm::vec3(1.0f, 1.0f, -3.0f);

    level[3].object   = std::make_unique<Cube>("./assets/sample/metal.png");
    level[3].shader.loadFromFile("./shaders/cube.vert", "./shaders/cube.frag");    
    level[3].position = glm::vec3(1.0f, 1.0f, 3.0f);

    level[4].object   = std::make_unique<Cube>("./assets/sample/cyber.png");
    level[4].shader.loadFromFile("./shaders/cube.vert", "./shaders/cube.frag");    
    level[4].position = glm::vec3(1.5f, 1.0f, 2.0f);

    level[5].object   = std::make_unique<Pave>("./assets/sample/dalle.png");
    level[5].shader.loadFromFile("./shaders/cube.vert", "./shaders/cube.frag");    
    //level[5].scale    = glm::vec3(0.5f, 0.5f, 0.5f);

}

////////////////////
void Scene::updateControl()
{
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();
        else if (event.type == sf::Event::Resized)
        {
            // adjust the viewport when the window is resized
            glViewport(0, 0, event.size.width, event.size.height);
        }
        controller.processEvent(camera, event);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window->close();
}

////////////////////
void Scene::updateObject()
{
    controller.processKeyboard(camera);
    controller.processMouseMovement(camera);

    glm::mat4 view       = camera.getViewMatrix();
    glm::mat4 projection = camera.getPerspectiveMatrix((float)WIDTH/(float)HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    //level[0].draw(view, projection);
    //level[1].draw(view, projection);
    for(auto &element : level){
        element.draw(view, projection);
        if(element.tag != "skybox" and element.tag != "base")
            camera.checkCollision(element);
    }

    window->display();

}

////////////////////
void Scene::loop()
{
     while(window->isOpen())
    {
        updateControl();
        updateObject();
    }
}

////////////////////
void Scene::over()
{
}
