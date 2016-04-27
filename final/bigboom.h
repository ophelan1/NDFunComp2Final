/*bigboom.h
 * Defines the big boom class, which is like the boom class,
 * only it ends the game upon animation completion.
 */
#ifndef BIGBOOM_H
#define BIGBOOM_H

#include "sprite.h"
#include "boom.h"
#include "object.h"
#include "scene.h"
#include <string>

class BigBoom : public Boom
{
    public:
        // constructor with default values
        BigBoom(int x, int y, std::string file="bigboom.png", int num=7, int w=128, int h=128); 
        void onCollision(object& a){ } // no collisions for us
        void onDeath(list<object*>* a); // on death action - return to main menu
    private:
	    Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################

BigBoom::BigBoom(int x, int y, std::string file, int num, int w, int h) : Boom(x, y, file, num, w, h)
{
    type = EXPLOSION; // we are an explosion
}
// Callled on death (animation end from parent class) - return to main menu
void BigBoom::onDeath(list<object*>* a)
{
    Scene::switchScenes( "menu" );
}
#endif
