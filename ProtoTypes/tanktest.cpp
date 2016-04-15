#include <SDL/SDL.h>
#include "oursdllib.h"
#include "tank.h"
#include "bullet.h"
#include <string>
#include <iostream>
#include <list>
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
    SDL_Surface *background = NULL;

    SDL_Event e;

    Uint32 start = 0;

    int frame = 0;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return 1;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );

    if ( screen == NULL )
        return 1;

    SDL_WM_SetCaption( SCREEN_CAPTION.c_str(), NULL );

    background = load_image( "back.bmp" );

    list<Bullet*> bulList;

    Tank p1( SDLK_LEFT, SDLK_RIGHT, 0, SCREEN_WIDTH/2, SDLK_UP, SDLK_DOWN, SDLK_RCTRL, &bulList );   
    Tank p2( SDLK_a, SDLK_d, SCREEN_WIDTH/2, SCREEN_WIDTH, SDLK_s, SDLK_w, SDLK_LCTRL, &bulList );   
    

    bool quit = false;
    unsigned char keyStates[400] = {0};
    set<int> keyTaps;
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
                    #ifdef VERBOSE
                        cout << "PRESSED " << e.key.keysym.sym << " " << SDLK_LEFT << endl;
                    #endif
                break;
            }
        }
        if (keyStates[ SDLK_q ])
            quit = true;
        apply_surface( 0, 0, background, screen );
        p1.onUpdate ( keyStates, &keyTaps );
        p1.drawSprite( screen );
        p2.onUpdate ( keyStates, &keyTaps );
        p2.drawSprite( screen );
        for (auto i = bulList.begin(); i != bulList.end(); i++)
        {
            (**i).onUpdate();
            (**i).drawSprite( screen );
            if ((**i).get_y() > SCREEN_HEIGHT - 32)
            {
                delete *i;
                i = bulList.erase(i);
            }
        }
        if ( SDL_Flip( screen ) == -1 )
            return 1;
        frame++;
        if ( ( SDL_GetTicks() - start ) < 1000 / SCREEN_FPS )
            SDL_Delay( ( 1000 / SCREEN_FPS ) - ( SDL_GetTicks() - start ) ); 
    }
    SDL_FreeSurface( background );
    for (auto i = bulList.begin(); i != bulList.end(); i++)
    {
        delete (*i);
    }
    SDL_Quit();
    return 0;
}
