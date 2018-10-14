#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 848;
	ground.h = 64;

	// Background
	background.x = 120;
	background.y = 128;
	background.w = 671;
	background.h = 200;

	// Cieling
	cieling.x = 91;
	cieling.y = 8;
	cieling.w = 765;
	cieling.h = 48;
	
	// Bath
	bath.x = 164;
	bath.y = 66;
	bath.w = 336;
	bath.h = 51;

	// Bucket
	bucket.x = 540;
	bucket.y = 84;
	bucket.w = 36;
	bucket.h = 28;

	// water animation
	water.frames.push_back({ 0, 0, 0, 0});
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 296, 448, 284, 20 });
	water.frames.push_back({ 8, 448, 284, 18 });
	water.frames.push_back({ 296, 448, 284, 20 });
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 0, 0, 0, 0 });
	water.speed = 0.09f;

}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading Honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	//Enable the player module
	App->player->Enable();

	//Trigger background music
	App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading Honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{

	// RENDER
	App->renderer->Blit(graphics, -85, 155, &ground);
	App->renderer->Blit(graphics, -8, -20, &background, 0.84f);
	App->renderer->Blit(graphics, -58, 0, &cieling, 0.87f);
	App->renderer->Blit(graphics, 215, 120, &bath, 0.92f);
	App->renderer->Blit(graphics, 188, 150, &bucket, 0.92f);
	App->renderer->Blit(graphics, 243, 132, &(water.GetCurrentFrame()), 0.92f);

	// Change Scene
	if (can_transition && App->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_ken, this, 3.0f);
		can_transition = false;
	}
	return UPDATE_CONTINUE;
}