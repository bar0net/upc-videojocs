#include "EditorCameraMove.h"

#include "Application.h"
#include "ModuleInput.h"
#include "SceneObject.h"

#include "SDL.h"
#include "MathGeoLib.h"

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
		math::float4x4 model = sceneObject->RotationMatrix();
		sceneObject->position -= 0.1f*(model * math::float4(0.0f,0.0f,1.0f,1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
	{
		math::float4x4 model = sceneObject->RotationMatrix();
		sceneObject->position += 0.1f*(model * math::float4(0.0f, 0.0f, 1.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
	{
		math::float4x4 model = sceneObject->RotationMatrix();
		sceneObject->position -= 0.1f*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
	{
		math::float4x4 model = sceneObject->RotationMatrix();
		sceneObject->position += 0.1f*(model * math::float4(1.0f, 0.0f, 0.0f, 1.0f)).Float3Part();
	}



	if (App->input->GetKey(SDL_SCANCODE_J) == KeyState::KEY_REPEAT)
	{
		math::float4x4 model = sceneObject->RotationMatrix().Inverted();
		sceneObject->rotation.y += 0.5f;
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KeyState::KEY_REPEAT)
	{
		math::float4x4 model = sceneObject->RotationMatrix().Inverted();
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