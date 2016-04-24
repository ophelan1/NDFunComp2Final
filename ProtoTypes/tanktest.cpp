#include <SDL/SDL.h>
#include "scene.h"
#include "gamescene.h"
#include "menuscene.h"
#include <string>
#include <set>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const int SCREEN_FPS = 120;
const std::string SCREEN_CAPTION = "Testing the Tank";

using namespace std;

int main( int argc, char** args )
{
    SDL_Surface *screen = NULL;

    SDL_Event e;

    Uint32 start = 0;

    int frame = 0;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return 1;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );

    if ( screen == NULL )
        return 1;

    SDL_WM_SetCaption( SCREEN_CAPTION.c_str(), NULL );

    bool quit = false;
    unsigned char keyStates[400] = {0};
    set<int> keyTaps;
    Scene::addScene( "menu", new MenuScene() );
    Scene::addScene( "game", new GameScene() );
    while ( !quit )
    {
        keyTaps.clear();
        start = SDL_GetTicks();
        while ( SDL_PollEvent ( &e ) != 0 )
        {
            switch ( e.type )
            {
                case SDL_QUIT:
                    quit = true;
                break;
                case SDL_KEYUP:
                    keyStates[e.key.keysym.sym] = 0;
                break;
                case SDL_KEYDOWN:
                    keyStates[e.key.keysym.sym] = 1;
                    keyTaps.insert(e.key.keysym.sym);
                break;
            }
        }
        Scene::update( keyStates, keyTaps );
        if (keyStates[ SDLK_q ])
            quit = true;
        if (keyStates[ SDLK_r ])
            Scene::switchScenes( "menu" );
        Scene::draw( screen );
        if ( SDL_Flip( screen ) == -1 )
            return 1;
        frame++;
        if ( ( SDL_GetTicks() - start ) < 1000 / SCREEN_FPS )
            SDL_Delay( ( 1000 / SCREEN_FPS ) - ( SDL_GetTicks() - start ) ); 
    }
    Scene::free();
    SDL_Quit();
    return 0;
}
