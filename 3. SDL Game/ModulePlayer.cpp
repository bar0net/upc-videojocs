#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100.0;
	position.y = 128.0; //216;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({4, 128, 70, 94});
	forward.frames.push_back({73, 128, 70, 94});
	forward.frames.push_back({162, 128, 70, 94});
	forward.frames.push_back({259, 128, 70, 94});
	forward.frames.push_back({352, 128, 70, 94});
	forward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	curr_animation = &idle;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	HandleInput();

	App->renderer->Blit(graphics, (int)position.x, (int)position.y, &((*curr_animation).GetCurrentFrame()), 1.0f);

	return UPDATE_CONTINUE;
}

void ModulePlayer::HandleInput() 
{
	switch (state)
	{
	case (PlayerState::PLAYER_IDLE):
		if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_BACKWARD);
		if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_FORWARD);
		break;

	case (PlayerState::PLAYER_FORWARD):
		if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP) ChangeState(PlayerState::PLAYER_IDLE);
		else 
		{
			if (position.x < 820) position.x += (_PLAYER_SPEED_ * App->delta_time);
		}
		break;

	case (PlayerState::PLAYER_BACKWARD):
		if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_UP) ChangeState(PlayerState::PLAYER_IDLE);
		else 
		{
			if (position.x > 10) position.x -= (_PLAYER_SPEED_ * App->delta_time);
		}
		break;
	default:
		break;
	}

}

void ModulePlayer::ChangeState(PlayerState new_state) 
{
	switch (new_state)
	{
	case PlayerState::PLAYER_IDLE:
		curr_animation = &idle;
		break;
	case PlayerState::PLAYER_FORWARD:
		curr_animation = &forward;
		break;
	case PlayerState::PLAYER_BACKWARD:
		curr_animation = &backward;
		break;
	default:
		break;
	}

	state = new_state;
}