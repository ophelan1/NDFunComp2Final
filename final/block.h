/*block.h
 *
 *Provides all functionality for the block class.
 *
 */
#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"
#include "oursdllib.h"

class Block : public object{
    public:
        Block(int x, int y, int w, int h); // constructor
        void drawSprite(SDL_Surface* screen); // called to draw the block image
        bool is_dead(); // called when the block is destroyed
        void onUpdate() { } // called every frame, ignored for the block class
        void checkCollision(object& a); // Called to check collisions with other objects
    private:
	    int w; // width of the block
        int h; // height of the block
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
//(x,y) the position of the block, defines the top left corner of the block
//(wa,ha) the size of the block in pixels
Block::Block(int x, int y, int wa, int ha)
{
    type = BLOCK; // set type to block for collisions
    // convert from pixel to large scale
    w    = wa*SCALE; 
    h    = ha*SCALE;
    xPos = x *SCALE;
    yPos = y *SCALE;
}
//################ BASIC UTILITIES ############################

// called to check our life status
bool Block::is_dead(){
    return type==NONE; // return whether we were hit or not
}

// called to check collisions
void Block::checkCollision(object& a)
{
        // Convert other location to big scale
        const int ox = a.get_x() * SCALE;
        const int oy = a.get_y() * SCALE;
        // If it is a bullet, kill us both
        if ( ox >= xPos && oy >= yPos && ox <= xPos + w && oy <= yPos + h && a.getType() == BULLET )
        {
            a.kill();
            type = NONE;
        }
}
// Draw ourselves
void Block::drawSprite(SDL_Surface* screen){
    // Draw our black outline
    fill_rect(xPos/SCALE, yPos/SCALE, (xPos+w)/SCALE, (yPos+h)/SCALE, color::BLACK, screen);
    // Draw our green gooey filling
    fill_rect(xPos/SCALE+1, yPos/SCALE+1, (xPos+w)/SCALE-1, (yPos+h)/SCALE-1, color::GREEN, screen);
}

#endif
