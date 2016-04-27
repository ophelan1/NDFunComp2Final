/*tank.h
 * Defines the Tank class, which acts as the game character.
 */
#ifndef TANK_H
#define TANK_H

#include "sprite.h"
#include "object.h"
#include "bullet.h"
#include "bigboom.h"
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
        static const int SHOT_DELAY = 30; // minimum delay between shots
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
        static int SHOT_TIMER = 0; // a variable used to limit the number of shots per second
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
        // decrement shot timer
        if (SHOT_TIMER > 0)
        {
            SHOT_TIMER -= 1;
        }
        // fire our weapons, if it was a recent keytap and we're allowed to shoot
        if (taps->find(key_fire)!=taps->end() && SHOT_TIMER == 0)
        {
            bulList->push_back(new Bullet(xPos/SCALE,yPos/SCALE,turret.getFrame(),SHOT_POWER));
            SHOT_TIMER = SHOT_DELAY;
        }
    }
    // no default onUpdate action
    void Tank::onUpdate() { }

    // Check if we are dead
    bool Tank::is_dead()
    {
        return (hp <= 0);
    }
 
    // draw ourselves, our hp bar, and our bullet path
    void Tank::drawSprite(SDL_Surface* screen)
    {
        //draw hp bar outline
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE,   16, (xMin+(xMax-xMin)*3/4)/SCALE,  24, color::BLACK, screen );
        // calculate fill for hp bar
        double fill = ((double)(xMax-xMin)/2*(double)hp/(double)MAX_HP);
        // draw filling of hp bar
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE, 17, (xMin+(xMax-xMin)/4+fill)/SCALE, 23, color::GREEN, screen );
        // Handle drawing the arc
        // first set up some initial values
        const int sprite_height = sprite.getHeight()*SCALE;
        int angle = turret.getFrame();
        int x = xPos;
        int y = yPos;
        int xprev = x;
        int yprev = y;
        // calculate dx,dy from power and angle
        int dx =  SHOT_POWER * SCALE * cos( angle * M_PI / 180.0 );
        int dy = -SHOT_POWER * SCALE * sin( angle * M_PI / 180.0 );
        // go until we are out of the screen or on the ground
        while ( y<yPos+sprite_height && x>=0 && x<=screen->w*SCALE )
        {
            // draw a line between the last two points
            draw_line( xprev/SCALE, yprev/SCALE, x/SCALE, y/SCALE, color::RED, screen );
            xprev = x;
            yprev = y;
            // make a new point
            x += dx;
            y += dy;
            dy += Bullet::ACCEL_Y;
        }
        // lastly, draw our tank and turret sprites
        sprite.draw( screen, xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
    	turret.draw( screen, xPos/SCALE-sprite.getWidth()/2, yPos/SCALE-sprite.getHeight()/2);
    }

    // our on-death action - add a bigboom
    void Tank::onDeath(list<object*>* a)
    {
        a->push_back( new BigBoom( xPos/SCALE, yPos/SCALE, "bigboom.png", 21, 128, 128 ) );
    }
    // check for collisions against explosions
    void Tank::checkCollision(object& a)
    {
            const int sprite_width = sprite.getWidth()*SCALE;
            const int sprite_height = sprite.getHeight()*SCALE;
            const int ox = a.get_x() * SCALE;
            const int oy = a.get_y() * SCALE;
            // if one hit us, take away some hp and make sure the explosion doesn't hit us again
            if ( ox >= xPos -sprite_width/2 && oy >= yPos -sprite_height/2 && ox <= xPos + sprite_width/2 && oy <= yPos + sprite_height/2 && a.getType() == EXPLOSION )
            {
                hp -= DAMAGE_PER_BULLET;
                a.kill();
            }
    }
#endif
