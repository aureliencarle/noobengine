#pragma once 
// Intern inclusion
#include <camera.h>
// SFML library
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

namespace Control{
    // Default Control values
    constexpr float SPEED = 0.01f;
    constexpr float JUMP  = 0.01f;
}

class Controller
{
    private:


    public:

        /**
         *
         */
        Controller();

        /**
         *
         */
        void processMouseMovement(Camera &camera);

        /**
         *
         */
        void processKeyboard(Camera &camera);

        /**
         *
         */
        void processEvent(Camera    &camera,
                          sf::Event &event);

};