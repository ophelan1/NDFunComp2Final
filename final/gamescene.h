/*gamescene.h
 *
 * The main game logic is here, a subclass of scene named GameScene.
 *
 */
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
        // the list of objects in the scene
        list<object*> objList;
        // the background surface
        SDL_Surface *background;
        // the position of the background
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
// constructor
GameScene::GameScene() : objList()
{
    // set up background
    bgX = 0;
    bgY = 0;
    background = load_image( "background.png" );
}
// called when entering the scene
void GameScene::onStart()
{
    // just to be safe, clear the room
    onEnd();
    // make players
    Tank* p1 = new Tank( SDLK_a, SDLK_d, 0, 1280/2-32, SDLK_s, SDLK_w, SDLK_f, &objList );
    Tank* p2 = new Tank( SDLK_LEFT, SDLK_RIGHT, 1280/2+32, 1280, SDLK_UP, SDLK_DOWN, SDLK_RALT, &objList ); 
    // add blocks in a nice square in the center of the room
    for (int i = 0; i < 100; i++)
        objList.push_back( new Block( 1280/2-(10*16)+(i%10)*32, 720-100-(i/10)*32, 32, 32 ) );
    // add the players to the room
    objList.push_back(p1);
    objList.push_back(p2);
}
// called when leaving the scene
void GameScene::onEnd()
{
    // free all the objects in the room
    for (auto i = objList.begin(); i != objList.end(); i++)
    {
        delete (*i);
    }
    objList.clear();
}
// called when we are freed, so free everything
GameScene::~GameScene()
{
    SDL_FreeSurface( background );
    onEnd();
}
// called every frame
void GameScene::onUpdate(unsigned char keyStates[400], set<int> keyTaps)
{
    // Scroll background
    bgX -= 2;
    // If background has gone too far
    if ( bgX <= -background->w ) {
        // Reset the offset
        bgX = 0;
    }
    // iterate over all objects
    for (auto i = objList.begin(); i != objList.end(); i++)
    {
        // call their update function
        (**i).onUpdate( keyStates, &keyTaps );
        // check collisions
        for (auto t = objList.begin(); t != objList.end(); t++)
        {   if ( *i != *t )
                (*i)->checkCollision(**t);
        }
        // check deaths
        if ( (**i).is_dead() )
        {
            // tell the object it is going to die
            (**i).onDeath(&objList);
            // THIS NEXT PART IS IMPORTANT
            // SOME OBJECTS MAY CHANGE SCENES ONDEATH
            // DOING SO WOULD CALL OUR onEnd, WHICH WOULD CLEAR ALL OBJECTS
            // INVALIDATING i AND CAUSING US TO FREE AN INVALID ADDRESS,
            // CAUSING A SEGFAULT!!!
            if ( !objList.empty() )
            {
                delete *i; // free the allocated memory
                i = objList.erase(i); // erase the object from our list
            }
            else // IF EVERYTHING HAS ALREADY BEEN FREED, JUST EXIT THE LOOP
            {
                break;
            }
        }
    }
    // Check if we should return to the main menu
    if (keyStates[ SDLK_r ])
        Scene::switchScenes( "menu" );
}
void GameScene::onDraw(SDL_Surface *screen)
{

    // Show the background
    apply_surface( bgX, bgY, background, screen);
    apply_surface( bgX + screen->w, bgY, background, screen);
    apply_surface( bgX + background->w, bgY, background, screen);
    // Draw all of our objects
    for (auto i = objList.begin(); i != objList.end(); i++)
        (**i).drawSprite( screen );
}
#endif
