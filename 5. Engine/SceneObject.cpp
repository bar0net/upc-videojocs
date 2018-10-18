#include "SceneObject.h"



SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
	
}

void SceneObject::AddVertex(float x, float y, float z) 
{
	math::float3 v = { x,y,z };
	vertices.push_back(v);
}

float* SceneObject::GetVertices() 
{
	// TODO: Improve this!
	float* output = new float[vertices.size() * 3];

	unsigned int i = 0;
	for (std::list<math::float3>::iterator it = vertices.begin(); it != vertices.end(); ++it, ++i) 
	{
		*(output + 3 * i)		= (*it).x;
		*(output + 3 * i + 1)	= (*it).y;
		*(output + 3 * i + 2)	= (*it).z;
	}

	return output;
}

math::float4x4 SceneObject::ModelMatrix()
{
	// TODO: Create Model Matrix
}
