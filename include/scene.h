#pragma once
// Intern inclusion
#include <camera.h>
#include <controller.h>
#include <instance3D.h>
// SFML library
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
// Standard library
#include <memory>

class Scene
{
    private:

        Controller controller;
        Camera camera;

        std::unique_ptr<sf::ContextSettings> settings;
        std::unique_ptr<sf::Window>    window;

        std::vector<Instance3D> level;


    public:

        /**
         *
         */
        Scene();

        /**
         *
         */
        void init();

        /**
         *
         */
        void loop();

        /**
         *
         */
        void updateControl();

        /**
         *
         */
        void updateObject();

        /**
         *
         */
        void over();

};