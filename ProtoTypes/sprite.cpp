/* sprite.cpp
 * Author:	John Westhoff
 * Date:	03/20/2016
 * Course:	CSE20212
 *
 * Implementation file for the Sprite class.
 * 
 */
#include "sprite.h"
#include "oursdllib.h"
#include <SDL/SDL.h>
/* Sprite constructor
 * sprite_file is the string containing the name of the sprite file
 * sp_x is the x coordinate of the sprite within the image
 * sp_y is the y coordinate
 * sp_w is the width of the frame of the sprite
 * sp_h is the height of the frame
 * im_num is the number of frames within the sprite
 *
 */
Sprite::Sprite(std::string sprite_file, int sp_x, int sp_y, int sp_w, int sp_h, int im_num)
{
	sprite = load_image(sprite_file);
	off = SDL_Rect();
	off.x = sp_x;
	off.y = sp_y;
	off.h = sp_h;
	off.w = sp_w;
    image_number = im_num;
}
// draws the player on the screen surface
void Sprite::draw(SDL_Surface* screen, int x, int y)
{
	apply_surface( x, y, sprite, screen, &off );
}
// frees the surface used by the player
Sprite::~Sprite()
{	
	SDL_FreeSurface( sprite );
}
// handles changing the sprite for animation 
void Sprite::animate()
{
    sprite_index = (sprite_index + 1) % image_number;
    off.x = off.w*sprite_index;
}
int Sprite::getWidth()
{
    return off.w;
}
int Sprite::getHeight()
{
    return off.h;
}
