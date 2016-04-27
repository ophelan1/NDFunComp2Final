/*menuscene.h
 *
 * handles the main menu
 *
 */
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SDL/SDL.h>
#include "scene.h"
#include <set>
#include "oursdllib.h"

using namespace std;

class MenuScene : public Scene
{
    private:
        SDL_Surface *background; // our menu image
	public:
        MenuScene();
        ~MenuScene();
		void onDraw(SDL_Surface* screen);
		void onUpdate(unsigned char keyStates[400], set<int> keytaps);
};
// constructor, just load the image
MenuScene::MenuScene()
{
    background = load_image( "menu.png" );
}
// destructor, just free the image
MenuScene::~MenuScene()
{
    SDL_FreeSurface( background );
}
// called every frame - just check if we should go to the main game
void MenuScene::onUpdate(unsigned char keyStates[400], set<int> keyTaps)
{
    if (keyStates[SDLK_SPACE])
    {
        Scene::switchScenes("game");
    }
}
// called every draw - just draw our image
void MenuScene::onDraw(SDL_Surface *screen)
{
    apply_surface(0, 0, background, screen);
}
#endif
