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
        SDL_Surface *background;
	public:
        MenuScene();
		void onDraw(SDL_Surface* screen);
		void onUpdate(unsigned char keyStates[400], set<int> keytaps);
};

MenuScene::MenuScene()
{
    background = load_image( "menu.png" );
}
void MenuScene::onUpdate(unsigned char keyStates[400], set<int> keyTaps)
{
    if (keyStates[SDLK_SPACE])
    {
        Scene::switchScenes("game");
    }
}
void MenuScene::onDraw(SDL_Surface *screen)
{
    apply_surface(0, 0, background, screen);
}
#endif
