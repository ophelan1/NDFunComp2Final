/* oursdllib.h
 * Initial Author:	John Westhoff
 * Date:	        02/29/2016
 * Course:	        CSE20212
 *
 * Header file for useful functions for the SDL library. 
 *
 */
#include <SDL/SDL.h>
#include <string>
#ifndef OURSDL_H
#define OURSDL_H
// A namespace for ANSI color constants
namespace color
{
                                    //AARRGGBB
    static const Uint32 RED     =   0xFFFF0000;
    static const Uint32 GREEN   =   0xFF00FF00;
    static const Uint32 BLUE    =   0xFF0000FF;
    static const Uint32 WHITE   =   0xFFFFFFFF;
    static const Uint32 BLACK   =   0xFF000000;
    static const Uint32 YELLOW  =   0xFFFFFF00;
    static const Uint32 CYAN    =   0xFF00FFFF;
    static const Uint32 PURPLE  =   0xFFFF00FF;
}
// Loads and optimizes an image from a file
SDL_Surface *load_image(std::string fname);
// Draws a src at (x,y) onto dst, using clip for formatting
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip = NULL );
// Sets the pixel at (x,y) to color on screen
void draw_point( int x, int y, Uint32 color, SDL_Surface* screen );
// Draws a line from (x1,y1) to (x2,y2) on screen with color color
void draw_line( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen );
// Draws a filled rectangle from (x1,y1) to (x2,y2) on screen with color color
void fill_rect( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen );
#endif
