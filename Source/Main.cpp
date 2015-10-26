#include <iostream>
#include <GLFW/glfw3.h>

int main( int argc, char** argv )
{
    // Attempt to initialize GLFW
    if ( !glfwInit() )
    {
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow( 800, 600, "Billy's 3D Billiards", nullptr, nullptr );
    if ( !window )
    {
        glfwTerminate();
        return -1;
    }

    // Make the window the current context
    glfwMakeContextCurrent( window );

    // Set the clear color to be cornflower blue
    glClearColor( 100 / 255.0f,
                  149 / 255.0f,
                  237 / 255.0f,
                  1.0f );

    // Loop until the window should close
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Swap the buffers and allow the window to process events
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // Cleanup GLFW before exiting
    glfwTerminate();
    return 0;
}
