#include "EditorCameraMove.h"

#include "Application.h"
#include "ModuleInput.h"
#include "SceneObject.h"

#include "SDL.h"

void EditorCameraMove::Update()
{
	//LOG("EDITOR CAMERA MOVE UPDATE")
	if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT) 
	{
		sceneObject->position.y += 0.1f;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
	{
		sceneObject->position.y -= 0.1f;
	}


	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
	{
		sceneObject->position.z -= 0.1f;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
	{
		sceneObject->position.z += 0.1f;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
	{
		sceneObject->position.x -= 0.1f;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
	{
		sceneObject->position.x += 0.1f;
	}



	if (App->input->GetKey(SDL_SCANCODE_J) == KeyState::KEY_REPEAT)
	{
		sceneObject->rotation.y += 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KeyState::KEY_REPEAT)
	{
		sceneObject->rotation.y -= 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_I) == KeyState::KEY_REPEAT)
	{
		sceneObject->rotation.x += 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KeyState::KEY_REPEAT)
	{
		sceneObject->rotation.x -= 0.5f;
	}
}