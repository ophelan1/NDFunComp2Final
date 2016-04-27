/*tank.h
 * Defines the Tank class, which acts as the game character.
 */
#ifndef TANK_H
#define TANK_H

#include "sprite.h"
#include "object.h"
#include "bullet.h"
#include "oursdllib.h"
#include <SDL/SDL.h>
#include <SDL/SDL_keyboard.h>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <math.h>

using namespace std;

class Tank : public object{
	public:
        // Constructor, takes keys for left and right, the bounds on position, the up and down turret keys, the fire key, and a list of objects to add bullets to
	    Tank(int left, int right, int minX, int maxX, int up, int down, int fire, list<object*>*bullets);
        // called when drawing sprites
		void drawSprite(SDL_Surface* screen);
        // called on every frame
		void onUpdate(const unsigned char* state, set<int>* taps);
        void onUpdate();
        // called to check if the tank is dead, our condition is if the hp <= 0
        bool is_dead();
        // called when the tank dies, we add a bigboom object to the objectlist
        void onDeath(list<object*>* a);
        // called to check collisions, we look for explosions
        void checkCollision(object &b);
	private:
		int dxMax; // maximum horizontal velocity
		int xMax; // maximum x position
		int xMin; // minimum x position
        int key_left; // key to move left
	    int key_right; // key to move right
		int key_up; // key to raise turret
		int key_down; // key to lower turret
        int key_fire; // key to fire
        int hp; // player health
        static const int MAX_HP = 100; // maximum player health
		static const int SHOT_POWER = 16; // initial velocity of bullets
		static const int ACCEL_X = 0.25*SCALE; // movement acceleration
		static const int FRICTION_X = 0.1*SCALE; // movement friction
        static const int DAMAGE_PER_BULLET = 10; // how much hp to remove when hit
	    Sprite sprite; // the tank base sprite
		Sprite turret; // the tank turretsprite
        list<object*>*bulList; // the list of objects we add bullets to
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
    // cpnstructor
    Tank::Tank(int left, int right, int minX, int maxX, int up, int down, int fire, list<object*>* bullets) : sprite(), turret("line360.png",0,0,32,32,360) {
        type = TANK; // set our collision type to tank
        xPos = ((maxX-minX)/2+minX)*SCALE; // center us in our half of the screen
        yPos = 675*SCALE; // set us on the ground
        dxVal = 0; // start at rest
        dyVal = 0;
        hp = MAX_HP; // start at full health
        dxMax = 4*SCALE; // define our maximum speed
        xMax = maxX*SCALE; // set our position limits
        xMin = minX*SCALE;
        // set the keys we use for movement
        key_left = left;
        key_right = right;
        key_up = up;
        key_down = down;
        key_fire = fire;
        // set our turret pointing upwards
        turret.setFrame(90);
        // define our bullet list
        bulList = bullets;
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(const unsigned char* state, set<int>* taps){
        static int ODD_FRAME = 0; // a variable used to limit the turret movement speed
        // Handle movements
        if (state[ key_left ] && (dxVal > -dxMax) && (xPos > xMin))
            dxVal -= ACCEL_X;
        else if (state[ key_right ] && (dxVal < dxMax) && (xPos < xMax))
            dxVal += ACCEL_X;
    	else if (dxVal != 0)
		    dxVal += dxVal > 0? -FRICTION_X:FRICTION_X;

    	if ((dxVal>0?dxVal:-dxVal) < FRICTION_X)
	    	dxVal = 0;

	    xPos += dxVal;	

        // prevent going too far
        if (xPos < xMin){
            dxVal = 0;
            xPos = xMin;
        }
        if (xPos > xMax){
            dxVal = 0;
            xPos = xMax;
        }
        // Handle turret motion
        if (state[ key_up ])
            if ((ODD_FRAME=(ODD_FRAME+1)%2) == 0)
                turret.incFrame(1);

        if (state[ key_down ])
            if ((ODD_FRAME=(ODD_FRAME+1)%2) == 0)
                turret.incFrame(-1);
    
        if (taps->find(key_fire)!=taps->end())
            bulList->push_back(new Bullet(xPos/SCALE,yPos/SCALE,turret.getFrame(),SHOT_POWER));
    }

    void Tank::onUpdate() { }

    bool Tank::is_dead()
    {
        if (hp <= 0) {
            return true;
        }
        else {
            return false;
        }
    }

 
    void Tank::drawSprite(SDL_Surface* screen)
    {
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE,   16, (xMin+(xMax-xMin)*3/4)/SCALE,                 24, color::BLACK, screen );
        double fill = ((double)(xMax-xMin)/2*(double)hp/(double)MAX_HP);
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE, 17, (xMin+(xMax-xMin)/4+fill)/SCALE, 23, color::GREEN, screen );
        const int sprite_height = sprite.getHeight()*SCALE;
        int angle = turret.getFrame();
        int x = xPos;
        int y = yPos;
        int xprev = x;
        int yprev = y;
        int dx =  SHOT_POWER * SCALE * cos( angle * M_PI / 180.0 );
        int dy = -SHOT_POWER * SCALE * sin( angle * M_PI / 180.0 );
        while ( y<yPos+sprite_height && x>=0 && x<=screen->w*SCALE )
        {
            draw_line( xprev/SCALE, yprev/SCALE, x/SCALE, y/SCALE, color::RED, screen );
            xprev = x;
            yprev = y;
            x += dx;
            y += dy;
            dy += Bullet::ACCEL_Y;
        }
        sprite.draw( screen, xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
    	turret.draw( screen, xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
    }
void Tank::onDeath(list<object*>* a)
{
    a->push_back( new Boom( xPos/SCALE, yPos/SCALE, "bigboom.png", 7, 128, 128 ) );
    Scene::switchScenes( "menu" );
}
void Tank::checkCollision(object& a)
{
        const int sprite_width = sprite.getWidth()*SCALE;
        const int sprite_height = sprite.getHeight()*SCALE;
        const int ox = a.get_x() * SCALE;
        const int oy = a.get_y() * SCALE;
        if ( ox >= xPos -sprite_width/2 && oy >= yPos -sprite_height/2 && ox <= xPos + sprite_width/2 && oy <= yPos + sprite_height/2 && a.getType() == EXPLOSION )
        {
            hp -= DAMAGE_PER_BULLET;
            a.kill();
        }
}
#endif
