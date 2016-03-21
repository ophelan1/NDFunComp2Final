/* sprite.h
 * Author:	John Westhoff
 * Date:	03/14/2016
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
		SDL_Rect off;
        int sprite_index;
        int image_number;
	public:
		~Sprite();
		Sprite(std::string sprite_file = "player.png", int sp_x=0, int sp_y=0, int sp_w=32, int sp_h=32, int im_num = 7);
        void animate();
		void draw(SDL_Surface* screen, int x = 0, int y = 0);
};
#endif
