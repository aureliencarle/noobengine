#include <controller.h>

////////////////////
Controller::Controller()
{

}

////////////////////
void Controller::processMouseMovement(Camera &camera)
{
    //sf::Vector2i center(WIDTH/2., HEIGHT/2.);
    sf::Vector2i center(100, 100);
    float xOffset = sf::Mouse::getPosition().x - center.x;
    float yOffset = center.y - sf::Mouse::getPosition().y;

    camera.processMouseMovement(xOffset, yOffset);
    sf::Mouse::setPosition(center);
}

////////////////////
void Controller::processKeyboard(Camera &camera)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camera.processKeyboard(Movement::FORWARD, Control::SPEED);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camera.processKeyboard(Movement::BACKWARD, Control::SPEED);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camera.processKeyboard(Movement::LEFT, Control::SPEED);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camera.processKeyboard(Movement::RIGHT, Control::SPEED);
}


////////////////////
void Controller::processEvent(Camera    &camera,
                              sf::Event &event
                             )
{
    if(event.type == sf::Event::KeyPressed)
        if(event.key.code == sf::Keyboard::I)
            camera.switchIsometric();
}