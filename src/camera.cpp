#include <camera.h>
// Intern library
#include <instance3D.h>
#include <debugger.h>
// OpenGL (glm) include
#include <glm/gtc/matrix_transform.hpp>

////////////////////
Camera::Camera(glm::vec3 position_p,
               glm::vec3 up_p,
               float     yaw_p,
               float     pitch_p
              )
    : position(position_p), front(glm::vec3(0.0f, 0.0f, -1.0f)), 
      worldUp(up_p), canMove(true), yaw(yaw_p), pitch(pitch_p),
      movementSpeed(Cam::SPEED), mouseSensitivity(Cam::SENSITIVITY), zoom(Cam::ZOOM),
      isometricView(false), freezeY(false)
{
    updateCameraVectors();
}

////////////////////
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position+front, up);
}

////////////////////
glm::mat4 Camera::getPerspectiveMatrix(float windowRatio)
{
    float projectView = glm::radians(zoom);
    if(isometricView){
        projectView = glm::radians(10.0f);
    }
    return glm::perspective(projectView, windowRatio, Cam::NEAR, Cam::FAR);    
}            

////////////////////
void Camera::switchIsometric()
{
    isometricView = not isometricView;
}

////////////////////
void Camera::processKeyboard(Movement direction,
                             float    deltaTime
                            )
{
    float velocity = movementSpeed * deltaTime;
    if (direction == Movement::FORWARD)
        position += front * velocity;
    if (direction == Movement::BACKWARD)
        position -= front * velocity;
    if (direction == Movement::LEFT)
        position -= right * velocity;
    if (direction == Movement::RIGHT)
        position += right * velocity;
}

////////////////////
void Camera::processMouseMovement(float xOffset,
                                  float yOffset,
                                  bool  constrainPitch
                                 )
{
    xOffset *= mouseSensitivity;
    yaw     += xOffset;

    if(!freezeY){
        yOffset *= mouseSensitivity;
        pitch   += yOffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;
        }
    }

    updateCameraVectors();
}


void Camera::processMouseScroll(float yOffset)
{
    zoom = -yOffset;
    if(zoom < 1.0f)
        zoom = 1.0f;
    if(zoom > 45.0f)
        zoom = 45.0f; 
}

////////////////////
void Camera::updateCameraVectors()
{
    // calculate new front vector
    glm::vec3 newFront;
    newFront.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    newFront.y = std::sin(glm::radians(pitch));
    newFront.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    
    front = glm::normalize(newFront);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

////////////////////
void Camera::checkCollision(Instance3D &other)
{
    /*
    if(position[0]+0.5 < other.min()[0]) return;
    if(position[0]-0.5 > other.max()[0]) return;
    if(position[1]+0.5 < other.min()[1]) return;
    if(position[1]-0.5 > other.max()[1]) return;
    if(position[2]+0.5 < other.min()[2]) return;
    if(position[2]-0.5 > other.max()[2]) return;
    canMove = false;
    */
}