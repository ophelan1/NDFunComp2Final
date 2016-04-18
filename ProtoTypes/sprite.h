/* sprite.h
 * Author:	John Westhoff
 * Date:	03/20/2016
 * Course:	CSE20212
 *
 * Interface file for the Sprite class. 
 *
 */
#include <SDL/SDL.h>
#include <string>
#ifndef PLAYER_H
#define PLAYER_H
class Sprite
{
	private:
		// Sprite values
		SDL_Surface* sprite;
        // Rectangle for clipping the sprite sheet
		SDL_Rect off;
        // The current frame in the animation
       	int sprite_index;
        // The number of frames
	    int image_number;
	public:
		~Sprite();
		Sprite(std::string sprite_file = "player.png", int sp_x=0, int sp_y=0, int sp_w=32, int sp_h=32, int im_num = 7);
        // modifies the off rect
		void animate();
        // gets the current frame number
		int getFrame();
        // increments the current frame number by inc
		void incFrame(int inc = 1);
        // sets the frame number to frame
		void setFrame(int frame = 0);
        // draws the sprite on the screen at (x,y)
		void draw(SDL_Surface* screen, int x = 0, int y = 0);
        // gets the sprite width
		int getWidth();
        // gets the sprite height
		int getHeight();
};
#endif
