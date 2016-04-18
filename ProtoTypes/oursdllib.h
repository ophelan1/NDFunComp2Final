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
namespace color
{
                                    //RRGGBBAA
    static const Uint32 RED     =   0xFF0000FF;
    static const Uint32 GREEN   =   0x00FF08FF;
    static const Uint32 BLUE    =   0x0000FFFF;
    static const Uint32 WHITE   =   0xFFFFFFFF;
    static const Uint32 BLACK   =   0x000000FF;
    static const Uint32 YELLOW  =   0xFFFF00FF;
    static const Uint32 CYAN    =   0x00FFFFFF;
    static const Uint32 PURPLE  =   0x9933FFFF;
}
// Loads and optimizes an image from a file
SDL_Surface *load_image(std::string fname);
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip = NULL );
void draw_point( int x, int y, Uint32 color, SDL_Surface* screen );
void draw_line( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen );
void fill_rect( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen );
#endif
