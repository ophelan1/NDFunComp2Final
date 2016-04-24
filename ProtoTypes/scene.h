#ifndef SCENE_H
#define SCENE_H

#include <SDL/SDL.h>
#include <set>
#include <string>
#include <map>

using namespace std;

class Scene
{
    private:
        static map<string, Scene*> scenes;
        static Scene* curScene;
	public:
        static bool switchScenes(string newcene);
        static void addScene(string name, Scene* scene);
		static void update(unsigned char keyStates[400], set<int> keytaps);
		static void draw(SDL_Surface* screen);
        static void free();
		virtual void onDraw(SDL_Surface* screen) = 0;
		virtual void onUpdate(unsigned char keyStates[400], set<int> keytaps)  = 0;
        virtual ~Scene(){ }
};
map<string, Scene*> Scene::scenes;
Scene* Scene::curScene = NULL;
bool Scene::switchScenes(string newscene)
{
    try
    {
        curScene = scenes.at(newscene);
    }
    catch (const std::out_of_range& oor)
    {
        return false;
    }
    return true;
}
void Scene::addScene(string name, Scene* scene)
{
    if (scenes.size()==0)
        curScene = scene;

    scenes.insert({name, scene});
}
void Scene::update(unsigned char keyStates[400], set<int> keytaps)
{
    if (curScene != NULL)
        curScene->onUpdate(keyStates, keytaps);
}
void Scene::draw(SDL_Surface* screen)
{
    if (curScene != NULL)
        curScene->onDraw(screen);
}
void Scene::free()
{
    for (auto i = scenes.begin(); i != scenes.end(); i++)
    {
        delete (*i).second;
    }
}
#endif
