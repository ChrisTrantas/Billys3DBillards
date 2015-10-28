#include <iostream>
#include "OpenGL.hpp"
#include "Game.hpp"

int main( int argc, char** argv )
{
    Game* game = Game::GetInstance();

    // Set the clear color to be cornflower blue
    game->SetClearColor( 100 / 255.0f,
                         149 / 255.0f,
                         237 / 255.0f,
                         1.0f );

    // Run the game
    game->Run();

    return 0;
}
