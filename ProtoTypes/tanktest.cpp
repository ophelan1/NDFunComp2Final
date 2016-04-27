/*tanktest.cpp
 *
 * Top level of program, designed to handle minimum aspects of game
 * logic and instead focus on big picture.
 *
 */
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "scene.h"
#include "gamescene.h"
#include "menuscene.h"
#include <string>
#include <set>
const int SCREEN_WIDTH = 1280; // Width of game window
const int SCREEN_HEIGHT = 720; // height of game window
const int SCREEN_BPP = 32; // screen color size
const int SCREEN_FPS = 120; // maximum framerate
const std::string SCREEN_CAPTION = "Tank Wars"; // Window title

using namespace std;

int main( int argc, char** args )
{
    // Define some assets
    SDL_Surface *screen = NULL;
    Mix_Music *music = NULL;
    // Start some music
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("beat.wav");
    Mix_PlayMusic(music, -1);

    // to hold events
    SDL_Event e;
    // For timing
    Uint32 start = 0;
    // Init sdl
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return 1;
    // open window
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );

    if ( screen == NULL )
        return 1;
    // set caption
    SDL_WM_SetCaption( SCREEN_CAPTION.c_str(), NULL );

    bool quit = false; // whether or not someone pressed q or closed the window
    unsigned char keyStates[400] = {0}; // CURRENT states of all keys
    set<int> keyTaps; // set of all keys JUST pressed
    Scene::addScene( "menu", new MenuScene() ); // main menu scene
    Scene::addScene( "game", new GameScene() ); // game scene
    // main application loop
    while ( !quit )
    {
        // start frame time
        start = SDL_GetTicks();
        // clear the press set
        keyTaps.clear();
        // get events
        while ( SDL_PollEvent ( &e ) != 0 )
        {
            switch ( e.type )
            {
                case SDL_QUIT: // quit the game
                    quit = true;
                break;
                case SDL_KEYUP: // release a key
                    keyStates[e.key.keysym.sym] = 0;
                break;
                case SDL_KEYDOWN: // press a key
                    keyStates[e.key.keysym.sym] = 1;
                    keyTaps.insert(e.key.keysym.sym);
                break;
            }
        }
        // Update our current scene
        Scene::update( keyStates, keyTaps );
        // Handle quit press
        if (keyStates[ SDLK_q ])
            quit = true;
        // draw our current scene
        Scene::draw( screen );
        // flip the screen
        if ( SDL_Flip( screen ) == -1 )
            quit = true;
        // handle timing
        if ( ( SDL_GetTicks() - start ) < 1000 / SCREEN_FPS )
            SDL_Delay( ( 1000 / SCREEN_FPS ) - ( SDL_GetTicks() - start ) ); 
    }
    // free all scenes
    Scene::free();
    // free sdl stuff
    SDL_Quit();
    // Free music
    Mix_FreeMusic( music );
    // Quit SDL Mixer
    Mix_CloseAudio();
    // exit successfully
    return 0;
}
