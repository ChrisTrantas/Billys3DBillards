#include <iostream>
#include "OpenGL.hpp"
#include "GameWindow.hpp"

int main( int argc, char** argv )
{
    // Create a window
    GameWindow window( 800, 600, "Billy's 3D Billiards" );
    if ( !window )
    {
        return -1;
    }

    // Set the clear color to be cornflower blue
    glClearColor( 100 / 255.0f,
                  149 / 255.0f,
                  237 / 255.0f,
                  1.0f );

    // Loop until the window should close
    window.SetVisible( true );
    while ( window.IsOpen() )
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Swap the buffers and allow the window to process events
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}
