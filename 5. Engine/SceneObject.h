#pragma once

#include <list>
#include <vector>

#include "Math/float3.h"
#include "Math/float4x4.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	virtual void Start() {}
	virtual void Update() {}
	virtual void CleanUp() {}

	virtual void AddVertex(float x, float y, float z);
	virtual std::vector<float>* GetVertices();
	virtual math::float4x4 ModelMatrix();

	std::list<math::float3> vertices;
	math::float3 position = math::float3::zero;
	math::float3 rotation = math::float3::zero;
	math::float3 scale = math::float3::one;
};

