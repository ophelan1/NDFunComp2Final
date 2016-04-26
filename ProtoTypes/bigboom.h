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
        BigBoom(int x, int y, std::string file="bigboom.png", int num=7, int w=128, int h=128); 
        void onCollision(object& a){ }
        void onDeath(list<object*>* a);
    private:
	    Sprite sprite;
};

//############### CONSTRUCTOR / DESTRUCTOR ####################
BigBoom::BigBoom(int x, int y, std::string file, int num, int w, int h) : Boom(x, y, file, num, w, h)
{
    type = 3;
}
void BigBoom::onDeath(list<object*>* a)
{
    Scene::switchScenes( "menu" );
}
#endif
