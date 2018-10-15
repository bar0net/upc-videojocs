#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "glew-2.1.0/include/GL/glew.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN;

		// SDL_WINDOW_FULLSCREEN_DESKTOP (same way as with FULLSCREEN)
		if (FULLSCREEN == true) flags |= SDL_WINDOW_FULLSCREEN;
		else if (WINDOW_BORDERLESS == true) flags |= SDL_WINDOW_BORDERLESS;
		else if (WINDOW_RESIZABLE == true) flags |= SDL_WINDOW_RESIZABLE;
		else if (FULLSCREEN_DESKTOP == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		// Set OpenGL Attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Add OpenGL FLAG
		flags |= SDL_WINDOW_OPENGL;

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Create GL Context
			SDL_GL_CreateContext(window); 
			
			// Initialize Glew
			GLenum err = glewInit();

			// … check for errors
			LOG("Using Glew %s", glewGetString(GLEW_VERSION));

			// Initialize OpenGL configs
			OpenGLInit();

			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::PreUpdate() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleWindow::PostUpdate()
{
	SDL_GL_SwapWindow(window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_GL_DeleteContext(window);
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::OpenGLInit()
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
}