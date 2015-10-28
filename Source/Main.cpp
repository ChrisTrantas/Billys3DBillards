#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"

int main( int argc, char** argv )
{
    Game* game = Game::GetInstance();

    // Set the clear color to be cornflower blue
    game->SetClearColor( Colors::CornflowerBlue );

    // Run the game
    game->Run();

    return 0;
}
