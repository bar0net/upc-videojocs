#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Globals.h"

class SceneObject;

class Behaviour
{
public:
	Behaviour(SceneObject* sceneObject) : sceneObject(sceneObject) {}
	virtual ~Behaviour() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void CleanUp() {}

	SceneObject* sceneObject;
};

#endif
