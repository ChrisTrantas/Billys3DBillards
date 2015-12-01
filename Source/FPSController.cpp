#include "FPSController.h"
#include <iostream>

using namespace std;

FPSController::FPSController(GameObject* gameObject)
    : Component(gameObject)
{
    m_pCamera = _gameObject->GetComponent<Camera>();

    m_fSpeed = 10.0f;
    m_fSensitivity = 1.0f / 10.0f;

    window = glfwGetCurrentContext();

    EventListener* eventListener = gameObject->GetEventListener();


    // std::bind doesn't have a universal return type. Because of that, we need to force-cast the return
    // type into something we can directly use, like an std::function. Note, though, that we can still
    // use function signatures with any number and type of arguments, as long as the return type is void.
    // I.e. std::function<void(void)> and std::function<void(Collider*, Collider*)> are both valid.
    std::function<void( void )> callback = std::bind( &FPSController::HandleCameraMove, this );
    eventListener->AddEventListener("OnMove", callback );

    callback = std::bind( &FPSController::HandleCameraRotate, this );
    eventListener->AddEventListener("OnRotateCamera", callback);
}


FPSController::~FPSController()
{
}

void FPSController::HandleCameraMove()
{
    //std::cout << "I am moving: " << _gameObject->GetName() << endl;
}

void FPSController::HandleCameraRotate()
{
    //std::cout << "I am rotating the camera | Mouse Position: x: " << m_v2MousePosition.x << " y: " << m_v2MousePosition.y << endl;
}

void FPSController::Update()
{
    float fDeltaTime = Time::GetElapsedTime();

    // Movement Controls
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
    {
        m_pCamera->MoveForward(m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
    {
        m_pCamera->MoveForward(-m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
    {
        m_pCamera->MoveRight(-m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
    {
        m_pCamera->MoveRight(m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q))
    {
        m_pCamera->MoveUp(-m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E))
    {
        m_pCamera->MoveUp(m_fSpeed * fDeltaTime);
        _gameObject->SendEvent("OnMove");
    }

    // Mouse Aiming
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    glm::vec2 v2NewMousePosition = glm::vec2(x, y);
    glm::vec2 v2MouseMovement = v2NewMousePosition - m_v2MousePosition;

    if (v2MouseMovement.x != 0)
    {
        m_pCamera->ChangeYaw(-v2MouseMovement.x * m_fSensitivity * fDeltaTime);
        _gameObject->SendEvent("OnRotateCamera");
    }

    if (v2MouseMovement.y != 0)
    {
        m_pCamera->ChangePitch(-v2MouseMovement.y * m_fSensitivity * fDeltaTime);
        _gameObject->SendEvent("OnRotateCamera");
    }

    m_v2MousePosition = v2NewMousePosition;
}