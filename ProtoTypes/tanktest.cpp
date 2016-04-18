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

    // the offsets of the background
    int bgX = 0, bgY = 0;

    SDL_Event e;

    Uint32 start = 0;

    int frame = 0;

    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return 1;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );

    if ( screen == NULL )
        return 1;

    SDL_WM_SetCaption( SCREEN_CAPTION.c_str(), NULL );

    background = load_image( "background.png" );

    list<object*> objList;
  
    Tank* p1 = new Tank( SDLK_a, SDLK_d, 0, SCREEN_WIDTH/2, SDLK_s, SDLK_w, SDLK_f, &objList );
    Tank* p2 = new Tank( SDLK_LEFT, SDLK_RIGHT, SCREEN_WIDTH/2, SCREEN_WIDTH, SDLK_UP, SDLK_DOWN, SDLK_RALT, &objList ); 
    
    objList.push_back(p1);
    objList.push_back(p2);

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

        // Scroll background
        bgX -= 2;
        // If background has gone too far
        if ( bgX <= -background->w ) {
            // Reset the offset
            bgX = 0;
        }
        // Show the background
        apply_surface( bgX, bgY, background, screen);
        apply_surface( bgX + screen->w, bgY, background, screen);
        apply_surface( bgX + background->w, bgY, background, screen);
        p1->onUpdate ( keyStates, &keyTaps );
        p1->drawSprite( screen );
        p2->onUpdate ( keyStates, &keyTaps );
        p2->drawSprite( screen );
        for (auto i = objList.begin(); i != objList.end(); i++)
        {
            (**i).onUpdate();
            (**i).drawSprite( screen );
            for (auto t = objList.begin(); t != objList.end(); t++)
            {   if ( *i != *t )
                    (*i)->checkCollision(**t);
            }
            if ( (**i).is_dead() )
            {
                (**i).onDeath(&objList);
                delete *i;
                i = objList.erase(i);
            }
        }
        if ( SDL_Flip( screen ) == -1 )
            return 1;
        frame++;
        if ( ( SDL_GetTicks() - start ) < 1000 / SCREEN_FPS )
            SDL_Delay( ( 1000 / SCREEN_FPS ) - ( SDL_GetTicks() - start ) ); 
    }
    SDL_FreeSurface( background );
    for (auto i = objList.begin(); i != objList.end(); i++)
    {
        delete (*i);
    }
    SDL_Quit();
    return 0;
}
