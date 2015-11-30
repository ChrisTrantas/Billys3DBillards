#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"
#if defined(DEBUG) || defined(_DEBUG)
#   define _CRTDBG_MAP_ALLOC
#   include <crtdbg.h>
#endif

int main( int argc, char** argv )
{
#if defined( DEBUG ) || defined( _DEBUG )
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    Game* game = Game::GetInstance();

    // Set the clear color to be cornflower blue
    game->SetClearColor( Colors::CornflowerBlue );

    // Run the game
    game->Run();

    return 0;
}
