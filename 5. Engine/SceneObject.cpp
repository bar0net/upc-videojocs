#include "SceneObject.h"

#include "MathGeoLib.h"

#define DEG2RAD 0.0174532925f

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

std::vector<float>* SceneObject::GetVertices() 
{
	std::vector<float>* output = new std::vector<float>;
	math::float4x4 matrix = ModelMatrix();
	math::float4 v;

	for (std::list<math::float3>::iterator it = vertices.begin(); it != vertices.end(); ++it) 
	{
		v[0] = (*it).x; v[1] = (*it).y; v[2] = (*it).z; v[3] = 1;
		v = matrix * v;

		(*output).push_back(v.x);
		(*output).push_back(v.y);
		(*output).push_back(v.z); 

		/*
		(*output).push_back((*it).x);
		(*output).push_back((*it).y);
		(*output).push_back((*it).z);*/
	}

	return output;
}

math::float4x4 SceneObject::ModelMatrix()
{
	math::float4x4 rotX = math::float4x4::identity;
	math::float4x4 rotY = math::float4x4::identity;
	math::float4x4 rotZ = math::float4x4::identity;
	math::float4x4 scaleMatrix = math::float4x4::identity;
	math::float4x4 translation = math::float4x4::identity;

	rotX[1][1] = cos(DEG2RAD * rotation.x); rotX[1][2] = -sin(DEG2RAD * rotation.x);
	rotX[2][1] = sin(DEG2RAD * rotation.x); rotX[2][2] =  cos(DEG2RAD * rotation.x);

	rotY[0][0] =  cos(DEG2RAD * rotation.y); rotY[0][2] = sin(DEG2RAD * rotation.y);
	rotY[2][0] = -sin(DEG2RAD * rotation.y); rotY[2][2] = cos(DEG2RAD * rotation.y);

	rotZ[0][0] = cos(DEG2RAD * rotation.z); rotZ[0][1] = -sin(DEG2RAD * rotation.z);
	rotZ[1][0] = sin(DEG2RAD * rotation.z); rotZ[1][1] =  cos(DEG2RAD * rotation.z);

	scaleMatrix[0][0] = scale.x; scaleMatrix[1][1] = scale.y; scaleMatrix[2][2] = scale.z;

	translation[0][3] = position.x; translation[1][3] = position.y; translation[2][3] = position.z;

	// TODO: Create Model Matrix
	return rotX * rotY * rotZ * scaleMatrix * translation;
}
