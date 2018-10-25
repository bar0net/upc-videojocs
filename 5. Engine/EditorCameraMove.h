#ifndef _EDITOR_CAMERA_MOVE_H
#define _EDITOR_CAMERA_MOVE_H

#include "Behaviour.h"

class EditorCameraMove : public Behaviour
{
public:
	EditorCameraMove(SceneObject* sceneObject) : Behaviour(sceneObject) {}
	void Update();
};

#endif // !_EDITOR_CAMERA_MOVE_H

