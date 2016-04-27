/*scene.h
 * Base class for in-game scenes,
 * which act as menus or levels, discrete
 * areas of the game with separable logic, 
 * also containsstatic functions for scene manager.
 */
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
        // Variables to handle the map of all scenes as well as the current scene pointer
        static map<string, Scene*> scenes;
        static Scene* curScene;
	public:
        // Static functions to handle scenes at a high level
        static bool switchScenes(string newcene);
        static void addScene(string name, Scene* scene);
		static void update(unsigned char keyStates[400], set<int> keytaps);
		static void draw(SDL_Surface* screen);
        static void free();
        // virtual functions for scenes to implement custom behavior
		virtual void onDraw(SDL_Surface* screen) = 0;
		virtual void onUpdate(unsigned char keyStates[400], set<int> keytaps)  = 0;
        virtual void onStart(){ }
        virtual void onEnd(){ }
        virtual ~Scene(){ }
};
// the map between scene names and scene pointers, allows for easy switching with string names
map<string, Scene*> Scene::scenes;
// the current scene pointer
Scene* Scene::curScene = NULL;

// Change the scene we are on - returns whether or not we were successfull
bool Scene::switchScenes(string newscene)
{
    // if the current scene exists, tell it we are leaving
    if (curScene != NULL)
        curScene->onEnd();

    // get the new scene
    bool suc = true;
    try
    {
        curScene = scenes.at(newscene);
    }
    catch (const std::out_of_range& oor)
    {
        suc = false;
    }
    // next, if we successfully changed scenes, then tell the new scene we are coming
    if (curScene != NULL)
        curScene->onStart();
    // return success status
    return suc;
}
// adds a scene to the map
// also sets that scene to the current scene if there are no other scenes
void Scene::addScene(string name, Scene* scene)
{
    if ( scenes.size()==0 )
    {
        curScene = scene;
    }

    scenes.insert(make_pair(name, scene));
}
// call the current scene's update function
void Scene::update(unsigned char keyStates[400], set<int> keytaps)
{
    if (curScene != NULL)
        curScene->onUpdate(keyStates, keytaps);
}
// call the current scene's draw function
void Scene::draw(SDL_Surface* screen)
{
    if (curScene != NULL)
        curScene->onDraw(screen);
}
// free all scenes
void Scene::free()
{
    // delete their memory
    for (auto i = scenes.begin(); i != scenes.end(); i++)
    {
        delete (*i).second;
    }
    // then clear the references to them
    scenes.clear();
}
#endif
