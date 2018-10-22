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
	idle.frames.push_back({4, 14, 60, 93});
	idle.frames.push_back({91, 15, 60, 93});
	idle.frames.push_back({181, 14, 60, 93});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({365, 12, 60, 93});
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

	// Extra: Ducking
	ducking.frames.push_back({ 196, 1204, 64, 94 });
	ducking.speed = 0.1f;

	// Extra: Punch
	punch.frames.push_back({ 18, 272, 66, 94 });
	punch.frames.push_back({ 18, 272, 66, 94 });
	punch.frames.push_back({ 18, 272, 66, 94 });
	punch.frames.push_back({ 108, 272, 92, 94 });
	punch.frames.push_back({ 108, 272, 92, 94 });
	punch.frames.push_back({ 18, 272, 66, 94 });
	punch.speed = 0.2f;

	// Extra: Hadouken
	hadouken.frames.push_back({ 34, 1542, 74, 94 });
	hadouken.frames.push_back({ 34, 1542, 74, 94 });
	hadouken.frames.push_back({ 136, 1542, 90, 94 });
	hadouken.frames.push_back({ 136, 1542, 90, 94 });
	hadouken.frames.push_back({ 244, 1542, 90, 94 });
	hadouken.frames.push_back({ 244, 1542, 90, 94 });
	hadouken.frames.push_back({ 356, 1542, 116, 94 });
	hadouken.frames.push_back({ 356, 1542, 116, 94 });
	hadouken.frames.push_back({ 356, 1542, 116, 94 });
	hadouken.frames.push_back({ 244, 1542, 90, 94 });
	hadouken.speed = 0.25f;
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
		if (App->input->GetKey(SDL_SCANCODE_I) == KeyState::KEY_DOWN) ChangeState(PlayerState::PLAYER_PUNCH);
		else if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_BACKWARD);
		else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_FORWARD);
		else if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_DUCKING_IDLE);
		break;

	case (PlayerState::PLAYER_FORWARD):
		if (App->input->GetKey(SDL_SCANCODE_I) == KeyState::KEY_DOWN) ChangeState(PlayerState::PLAYER_PUNCH);
		if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP) ChangeState(PlayerState::PLAYER_IDLE);
		else 
		{
			if (position.x < 820) position.x += (_PLAYER_SPEED_ * App->delta_time);
		}
		break;

	case (PlayerState::PLAYER_BACKWARD):
		if (App->input->GetKey(SDL_SCANCODE_I) == KeyState::KEY_DOWN) ChangeState(PlayerState::PLAYER_PUNCH);
		if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_UP) ChangeState(PlayerState::PLAYER_IDLE);
		else 
		{
			if (position.x > 10) position.x -= (_PLAYER_SPEED_ * App->delta_time);
		}
		break;

	case (PlayerState::PLAYER_DUCKING_IDLE):
		if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_UP) ChangeState(PlayerState::PLAYER_IDLE);
		else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_DOWN) ChangeState(PlayerState::PLAYER_DUCKING_FWD);
		break;

	case (PlayerState::PLAYER_DUCKING_FWD):
		if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_UP && App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP)
			ChangeState(PlayerState::PLAYER_IDLE);
		else if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_UP) 
			ChangeState(PlayerState::PLAYER_FORWARD);
		else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_UP) 
			ChangeState(PlayerState::PLAYER_DUCKING_IDLE);
		break;

	case (PlayerState::PLAYER_PUNCH):
		if ((*curr_animation).end) 
		{
			if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_BACKWARD);
			else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_FORWARD);
			else ChangeState(PlayerState::PLAYER_IDLE);
		}
		break;

	case (PlayerState::PLAYER_HADOUKEN):
		if ((*curr_animation).end)
		{
			if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_BACKWARD);
			else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) ChangeState(PlayerState::PLAYER_FORWARD);
			else ChangeState(PlayerState::PLAYER_IDLE);
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
		hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;
		curr_animation = &idle;
		break;

	case PlayerState::PLAYER_FORWARD:
		if (state == PlayerState::PLAYER_DUCKING_FWD && hadouken_progress == HADOUKEN_PROGRESS::HADOUKEN_DOWN_FWD)
			hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_FWD;
		else hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;
		curr_animation = &forward;
		break;

	case PlayerState::PLAYER_BACKWARD:
		curr_animation = &backward;
		break;

	case PlayerState::PLAYER_DUCKING_IDLE:
		if (state == PlayerState::PLAYER_IDLE && hadouken_progress == HADOUKEN_PROGRESS::HADOUKEN_NONE)
			hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_DOWN;
		else hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;
		curr_animation = &ducking;
		break;

	case PlayerState::PLAYER_DUCKING_FWD:
		if (state == PlayerState::PLAYER_DUCKING_IDLE && hadouken_progress == HADOUKEN_PROGRESS::HADOUKEN_DOWN)
			hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_DOWN_FWD;
		else hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;
		curr_animation = &ducking;
		break;

	case PlayerState::PLAYER_PUNCH:
		if (state == PlayerState::PLAYER_FORWARD && hadouken_progress == HADOUKEN_PROGRESS::HADOUKEN_FWD)
		{
			hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_EXECUTE;
			curr_animation = &hadouken;
			curr_animation->end = false;
			new_state = PlayerState::PLAYER_HADOUKEN;
		}
		else
		{
			hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;
			curr_animation = &punch;
			curr_animation->end = false;
		}
		break;

	default:
		break;
	}

	state = new_state;
}
