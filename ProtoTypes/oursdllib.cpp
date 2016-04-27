/* oursdllib.cpp
 *
 * Implementation for OurSDLLib utility functions.
 * 
 */
#include "oursdllib.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
// Loads an image from a file as a surface
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
// Draws the src surface on dst at (x,y) formatted with clip
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip)
{
	// Prepare temporary rectangle for offsets
	SDL_Rect off;
	off.x = x;
	off.y = y;
	// Blit the surface
	SDL_BlitSurface( src, clip, dst, &off );
}
// Draws a filled rectangle
void fill_rect( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen )
{
    // Create the rectangle
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = abs( x1-x2 );
    rect.h = abs( y1-y2 );
    // Draw it
    SDL_FillRect( screen, &rect, color );
}
// Draws a single point
void draw_point( int x, int y, Uint32 color, SDL_Surface* screen )
{
    // Verify that it is a valid location, and then edit the memory address
    if ( ( x >= 0 )  && ( x < screen->w ) && ( y >= 0 ) && ( y < screen->h ) )
        *(((Uint32*)(screen->pixels)) + ((y*screen->w)) + x) = color;
}
// Draws a line using Bresenham's line algorithm
void draw_line( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen )
{
    // Swap the points if they're swapped
    if (x1 > x2)
    {
        int t = x2;
        x2 = x1;
        x1 = t;
        t = y2;
        y2 = y1;
        y1 = t;
    }
    
    // Calculate slopes
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    // Calculate steps for Bresenham's algorithm
    int ystep = ( dy > 0 ? 1 : dy == 0 ? 0 : -1 );
    
    // Check for verticality - the algorithm doesn't work for vertical lines
    if ( dx == 0 )
    {
        // If it is vertical, just draw a vertical line
        for (int y = y1; y != y2; y += ystep)
        {
            draw_point( x1, y, color, screen );
        }
    }
    else
    {
        // Calulate derr and err
        double err = 0;
        double derr = fabs( dy / dx );
        // Begin drawing
        int y = y1;
        draw_point( x1, y1, color, screen );
        // Apply the algorithm and draw the points
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
