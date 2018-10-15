#ifndef _MODULESCENE_TRIANGLE_
#define _MODULESCENE_TRIANGLE_

#include "Module.h"
#include "glew-2.1.0/include/GL/glew.h"


class ModuleScene_Triangle : public Module {
public:
	bool Start();
	update_status Update();
	bool CleanUp();

private:
	GLuint vbo;
};

#endif // !_MODULESCENE_TRIANGLE_
