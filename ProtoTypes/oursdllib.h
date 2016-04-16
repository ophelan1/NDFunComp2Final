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
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip = NULL );
void draw_point( int x, int y, Uint32 color, SDL_Surface* screen );
void draw_line( int x1, int y1, int x2, int y2, Uint32 color, SDL_Surface* screen );
#endif
