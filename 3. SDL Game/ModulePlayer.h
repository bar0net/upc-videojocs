#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

enum class PlayerState 
{
	PLAYER_IDLE = 0,
	PLAYER_FORWARD,
	PLAYER_BACKWARD
};

class ModulePlayer : public Module
{
public:
	const float _PLAYER_SPEED_ = 60.0f;

	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	Animation* curr_animation = &backward;
	void HandleInput();
	void ChangeState(PlayerState new_state);

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation forward;
	Point<double> position;
	PlayerState state = PlayerState::PLAYER_IDLE;
};

#endif // __MODULEPLAYER_H__