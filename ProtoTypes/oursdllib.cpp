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
#include <math.h>
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
	}
	// Free old image
	SDL_FreeSurface( imageIn );
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
void draw_point( int x, int y, Uint32 color, SDL_Surface* screen )
{
    if ( ( x >= 0 )  && ( x < screen->w ) && ( y >= 0 ) && ( y < screen->h ) )
        *(((Uint32*)(screen->pixels)) + ((y*screen->w)) + x) = color;
}
void draw_line( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen )
{
    if (x1 > x2)
    {
        int t = x2;
        x2 = x1;
        x1 = t;
        t = y2;
        y2 = y1;
        y1 = t;
    }
    
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    int ystep = ( dy > 0 ? 1 : dy == 0 ? 0 : -1 );
    
    if ( dx == 0 )
    {
        for (int y = y1; y != y2; y += ystep)
        {
            draw_point( x1, y, color, screen );
        }
    }
    else
    {
        double err = 0;
        double derr = fabs( dy / dx );

        int y = y1;
        draw_point( x1, y1, color, screen );
        for ( int x = x1; x <= x2; x += 1 )
        {
            err = err + derr;
            while ( err >= 0.5 )
            {
                y = y + ystep; 
                err = err - 1;
                draw_point( x, y, color, screen );
            }
        }
    }
}
