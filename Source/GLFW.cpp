#include <GLFW/glfw3.h>
#include <iostream>

// A private static class used for handling GLFW
class GLFW
{
    static GLFW _instance;

    // Prints out any GLFW errors
    static void ErrorCallback( int code, const char* message )
    {
        std::cout << "GLFW Error: " << message << ". (Code: " << code << ")" << std::endl;
    }

    // Creates the GLFW instance
    GLFW()
    {
        glfwSetErrorCallback( ErrorCallback );
        if ( !glfwInit() )
        {
            std::cout << "Failed to initialize GLFW. Exiting." << std::endl;
            exit( -1 );
        }
    }

    // Destroys the GLFW instance
    ~GLFW()
    {
        glfwTerminate();
    }
};

// Declare the instance
GLFW GLFW::_instance;
