#ifndef _MODULE_SCENE_HONDA_
#define _MODULE_SCENE_HONDA_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool can_transition = true;
	
public:
	SDL_Texture * graphics = nullptr;
	
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect cieling;
	SDL_Rect bath;
	SDL_Rect bucket;

	Animation water;
};

#endif // !_MODULE_SCENE_HONDA_

