#pragma once
// OpenGL library
#include <glm/glm.hpp>
// Standard library
#include <vector>

enum class Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT   
};

namespace Cam{
    // Default camera values
    constexpr float YAW         = -90.0f;
    constexpr float PITCH       =  0.0f;
    constexpr float SPEED       =  20.f;
    constexpr float SENSITIVITY =  0.1f;
    constexpr float ZOOM        =  45.0f;

    constexpr float NEAR        =  0.1f;
    constexpr float FAR         =  1000.0f;
}

class Instance3D;
class Camera
{
    private:

        /**
         * Calculates the front vector from the Camera's (updated) Euler Angles
         */
        void updateCameraVectors();

    public:

        // Camera attributes
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        bool canMove;

        // Euler angles
        float yaw;
        float pitch;

        //Camera options 
        float movementSpeed;
        float mouseSensitivity;
        float zoom;
        bool  isometricView;
        bool  freezeY;

        /**
         * Constructor with glm objects
         */
        Camera(glm::vec3 position = glm::vec3(0.0f, 2.0f, 0.0f),
               glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
               float     yaw      = Cam::YAW,
               float     pitch    = Cam::PITCH
              );

        /**
         * Constructor with floats
         */
        Camera(float posX,
               float posY,
               float posZ,
               float upX, 
               float upY,
               float upZ,
               float yaw,
               float pitch
              );

        /**
         * Returns the view matrix calculated using Euler angles and LookAt matrix
         */
        glm::mat4 getViewMatrix();

        /**
         * Returns the perspective matrix calculated using perspective and ratio of render window
         */
        glm::mat4 getPerspectiveMatrix(float windowRatio);

        /**
         *
         */
        void switchIsometric();

        /**
         * \brief Processes input received from any keyboard-like input system. 
         * Accepts input parameter in the form of camera defined Enum Class (to abstract it from windowing systems)
         */
        void processKeyboard(Movement movement,
                             float    deltaTime
                            );

        /**
         * Processes input received from a mouse input system. 
         * Expects the offset value in both the x and y direction.
         */
        void processMouseMovement(float xOffset,
                                  float yOffset,
                                  bool  constrainPitch = true
                                 );

        /**
         * Processes input received from a mouse scroll-wheel event. 
         * Only requires input on the vertical wheel-axis
         */
        void processMouseScroll(float yOffset);

        /**
         *
         */
        void checkCollision(Instance3D &other);

};
