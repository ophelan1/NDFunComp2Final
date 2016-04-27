#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SDL/SDL.h>
#include <iostream>
#include "scene.h"
#include "object.h"
#include <set>
#include <list>
#include "oursdllib.h"
#include "tank.h"
#include "bullet.h"
#include "block.h"

using namespace std;

class GameScene : public Scene
{
    private:
        list<object*> objList;
        SDL_Surface *background;
        int bgX;
        int bgY;
	public:
        GameScene();
        ~GameScene();
		void onDraw(SDL_Surface* screen);
		void onUpdate(unsigned char keyStates[400], set<int> keytaps);
        void onStart();
        void onEnd();
};

GameScene::GameScene() : objList()
{
    bgX = 0;
    bgY = 0;
    background = load_image( "background.png" );
}
void GameScene::onStart()
{
    onEnd();

    Tank* p1 = new Tank( SDLK_a, SDLK_d, 0, 1280/2-32, SDLK_s, SDLK_w, SDLK_f, &objList );
    Tank* p2 = new Tank( SDLK_LEFT, SDLK_RIGHT, 1280/2+32, 1280, SDLK_UP, SDLK_DOWN, SDLK_RALT, &objList ); 
    
    for (int i = 0; i < 100; i++)
        objList.push_back( new Block( 1280/2-(10*16)+(i%10)*32, 720-100-(i/10)*32, 32, 32 ) );

    objList.push_back(p1);
    objList.push_back(p2);
}
void GameScene::onEnd()
{
    for (auto i = objList.begin(); i != objList.end(); i++)
    {
        delete (*i);
    }
    objList.clear();
}
GameScene::~GameScene()
{
    SDL_FreeSurface( background );
    onEnd();
}
void GameScene::onUpdate(unsigned char keyStates[400], set<int> keyTaps)
{
    // Scroll background
    bgX -= 2;
    // If background has gone too far
    if ( bgX <= -background->w ) {
        // Reset the offset
        bgX = 0;
    }
    for (auto i = objList.begin(); i != objList.end(); i++)
    {
        (**i).onUpdate( keyStates, &keyTaps );
        for (auto t = objList.begin(); t != objList.end(); t++)
        {   if ( *i != *t )
                (*i)->checkCollision(**t);
        }
        if ( (**i).is_dead() )
        {
            (**i).onDeath(&objList);
            if ( !objList.empty() )
            {
                delete *i;
                i = objList.erase(i);
            }
            else
            {
                break;
            }
        }
    }
    if (keyStates[ SDLK_r ])
        Scene::switchScenes( "menu" );
}
void GameScene::onDraw(SDL_Surface *screen)
{

    // Show the background
    apply_surface( bgX, bgY, background, screen);
    apply_surface( bgX + screen->w, bgY, background, screen);
    apply_surface( bgX + background->w, bgY, background, screen);
    for (auto i = objList.begin(); i != objList.end(); i++)
        (**i).drawSprite( screen );
}
#endif
