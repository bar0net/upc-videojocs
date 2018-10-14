#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

enum class HADOUKEN_PROGRESS 
{
	HADOUKEN_NONE = 0,
	HADOUKEN_DOWN,
	HADOUKEN_DOWN_FWD,
	HADOUKEN_FWD,
	HADOUKEN_EXECUTE
};

enum class PlayerState 
{
	PLAYER_IDLE = 0,
	PLAYER_FORWARD,
	PLAYER_BACKWARD,
	PLAYER_DUCKING_IDLE,
	PLAYER_DUCKING_FWD,
	PLAYER_PUNCH,
	PLAYER_HADOUKEN
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
	void HadoukenCheck();

	HADOUKEN_PROGRESS hadouken_progress = HADOUKEN_PROGRESS::HADOUKEN_NONE;

public:

	SDL_Texture* graphics = nullptr;
	
	Animation idle;
	Animation backward;
	Animation forward;
	Animation ducking;
	Animation punch;
	Animation hadouken;

	Point<double> position;
	PlayerState state = PlayerState::PLAYER_IDLE;
};

#endif // __MODULEPLAYER_H__