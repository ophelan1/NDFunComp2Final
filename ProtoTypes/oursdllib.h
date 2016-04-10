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

// Loads and optimizes an image from a file
SDL_Surface *load_image(std::string fname);
void apply_surface( int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect *clip = NULL );

#endif
