#ifndef _MODULE_TEXTURES_
#define _MODULE_TEXTURES_

#include<list>

#include "Module.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);

private:
	std::list<SDL_Texture*> textures;
};

#endif //!_MODULE_TEXTURES_