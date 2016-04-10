#include <SDL/SDL.h>
#include "oursdllib.h"
#include "tank.h"
#include <string>
#include <iostream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int SCREEN_FPS = 60;
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

	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	if ( screen == NULL )
		return 1;

	SDL_WM_SetCaption( SCREEN_CAPTION.c_str(), NULL );

	background = load_image( "back.bmp" );

	Tank p1;	

	bool quit = false;
	unsigned char keyStates[400] = {0};
	 while ( !quit )
	{
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
					#ifdef VERBOSE
						cout << "PRESSED " << e.key.keysym.sym << " " << SDLK_LEFT << endl;
					#endif
				break;
			}
		}
		p1.onUpdate ( keyStates );
		apply_surface( 0, 0, background, screen );
		p1.drawSprite( screen );
		if ( SDL_Flip( screen ) == -1 )
			return 1;
		frame++;
		if ( ( SDL_GetTicks() - start ) < 1000 / SCREEN_FPS )
			SDL_Delay( ( 1000 / SCREEN_FPS ) - ( SDL_GetTicks() - start ) ); 
	}
	SDL_FreeSurface( background );

	SDL_Quit();
	return 0;
}
