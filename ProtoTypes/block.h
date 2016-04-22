#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"
#include "oursdllib.h"

class Block : public object{
    public:
        Block(int x, int y, int w, int h); 
        void drawSprite(SDL_Surface* screen);
        bool is_dead();
        void onUpdate() { }
        void checkCollision(object& a);
    private:
	    int w;
        int h;
        bool hit;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
Block::Block(int x, int y, int wa, int ha)
{
    type = 5;
    w    = wa*SCALE;
    h    = ha*SCALE;
    xPos = x *SCALE;
    yPos = y *SCALE;
    hit = false;
}
//################ BASIC UTILITIES ############################

bool Block::is_dead(){
    return hit;
}

void Block::checkCollision(object& a)
{
        const int ox = a.get_x() * SCALE;
        const int oy = a.get_y() * SCALE;
        if ( ox >= xPos && oy >= yPos && ox <= xPos + w && oy <= yPos + h && a.getType() == 1 )
        {
            a.kill();
            hit = true;
        }
}
void Block::drawSprite(SDL_Surface* screen){
    fill_rect(xPos/SCALE, yPos/SCALE, (xPos+w)/SCALE, (yPos+h)/SCALE, color::BLACK, screen);
    fill_rect(xPos/SCALE+1, yPos/SCALE+1, (xPos+w)/SCALE-1, (yPos+h)/SCALE-1, color::GREEN, screen);
}

#endif
