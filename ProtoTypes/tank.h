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
	    Tank(int left, int right, int minX, int maxX, int up, int down, int fire, list<object*>*bullets);
		void drawSprite(SDL_Surface* screen);
		void onUpdate(const unsigned char* state, set<int>* taps);
        void onUpdate();
        bool is_dead();
        virtual void checkCollision(object &b);
	private:
		int dxMax;
		int xMax;
		int xMin;
        int key_left;
	    int key_right;
		int key_up;
		int key_down;
        int key_fire;
        int hp;
        static const int MAX_HP = 100;
		static const int SHOT_POWER = 11;
		static const int ACCEL_X = 0.25*SCALE;
		static const int FRICTION_X = 0.1*SCALE;
        static const int DAMAGE_PER_BULLET = 10;
		Sprite turret;
	    Sprite sprite;
        list<object*>*bulList;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

    Tank::Tank(int left, int right, int minX, int maxX, int up, int down, int fire, list<object*>* bullets) : sprite(), turret("line360.png",0,0,32,32,360) {
        type = 2;
        xPos = ((maxX-minX)/2+minX)*SCALE;
        yPos = 675*SCALE;
        dxVal = 0;
        dyVal = 0;
        hp = MAX_HP;
        dxMax = 4*SCALE;
        xMax = maxX*SCALE;
        xMin = minX*SCALE;
        key_left = left;
        key_right = right;
        key_up = up;
        key_down = down;
        key_fire = fire;
        turret.setFrame(90);
        bulList = bullets;
    }

//################ BASIC UTILITIES ############################

    
    void Tank::onUpdate(const unsigned char* state, set<int>* taps){
        static int ODD_FRAME = 0;
        const int sprite_height = sprite.getHeight()*SCALE;
        const int sprite_width = sprite.getWidth()*SCALE;
        if (state[ key_left ] && (dxVal > -dxMax) && (xPos > xMin))
            dxVal -= ACCEL_X;
        else if (state[ key_right ] && (dxVal < dxMax) && (xPos + sprite_width < xMax))
            dxVal += ACCEL_X;
    	else if (dxVal != 0)
		dxVal += dxVal > 0? -FRICTION_X:FRICTION_X;

    	if ((dxVal>0?dxVal:-dxVal) < FRICTION_X)
	    	dxVal = 0;

	    xPos += dxVal;	

        if (xPos < xMin){
            dxVal = 0;
            xPos = xMin;
        }
        if (xPos + sprite_width> xMax){
            dxVal = 0;
            xPos = xMax- sprite_width;
        }

        if (state[ key_up ])
            if ((ODD_FRAME=(ODD_FRAME+1)%3) == 0)
                turret.incFrame(1);

        if (state[ key_down ])
            if ((ODD_FRAME=(ODD_FRAME+1)%3) == 0)
                turret.incFrame(-1);
    
        if (taps->find(key_fire)!=taps->end())
            bulList->push_back(new Bullet(xPos/SCALE,yPos/SCALE,turret.getFrame(),SHOT_POWER));
    }

    void Tank::onUpdate() { }

    bool Tank::is_dead()
    {
        return false;
    }

 
    void Tank::drawSprite(SDL_Surface* screen)
    {
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE,   16, (xMin+(xMax-xMin)*3/4)/SCALE,                 24, color::BLACK, screen );
        double fill = ((double)(xMax-xMin)*0.75*(double)hp/(double)MAX_HP);
            std::cout << fill << std::endl;
        fill_rect( (xMin+(xMax-xMin)/4)/SCALE, 17, (xMin+fill)/SCALE, 23, color::GREEN, screen );
        const int sprite_width = sprite.getWidth()*SCALE;
        const int sprite_height = sprite.getHeight()*SCALE;
        int angle = turret.getFrame();
        int x = xPos;
        int y = yPos;
        int xprev = x;
        int yprev = y;
        int dx =  SHOT_POWER * SCALE * cos( angle * M_PI / 180.0 );
        int dy = -SHOT_POWER * SCALE * sin( angle * M_PI / 180.0 );
        while ( y<yPos+sprite_height && x>=0 && x<screen->w*SCALE )
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

void Tank::checkCollision(object& a)
{
        const int sprite_width = sprite.getWidth()*SCALE;
        const int sprite_height = sprite.getHeight()*SCALE;
        const int ox = a.get_x() * SCALE;
        const int oy = a.get_y() * SCALE;
        if ( ox >= xPos -sprite_width/2 && oy >= yPos -sprite_height/2 && ox <= xPos + sprite_width/2 && oy <= yPos + sprite_height/2 && a.getType() == 3 )
        {
            hp -= DAMAGE_PER_BULLET;
            a.kill();
        }
}
#endif
