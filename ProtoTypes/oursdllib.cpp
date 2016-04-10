/* oursdllib.cpp
 * InitialAuthor:	John Westhoff
 * Date:	        02/29/2016
 * Course:	        CSE20212
 *
 * Implementation for JohnSDL utility functions.
 * 
 */
#include "oursdllib.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
SDL_Surface *load_image(std::string fname)
{
	SDL_Surface* imageIn = NULL;
	SDL_Surface* imageOp = NULL;
	// Load image from file
	imageIn = IMG_Load(fname.c_str());
	if ( imageIn != NULL )
	{
		// Optimize
		imageOp = SDL_DisplayFormatAlpha( imageIn );
		// Free old image
		SDL_FreeSurface( imageIn );
	}
	return imageOp;
}
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip)
{
	// Prepare temporary rectangle for offsets
	SDL_Rect off;
	off.x = x;
	off.y = y;
	// Blit the surface
	SDL_BlitSurface( src, clip, dst, &off );
}
