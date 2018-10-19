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
	math::float4x4 rot = math::float4x4::identity; // RotX * RotY * RotZ
	math::float4x4 scaleTranslate = math::float4x4::zero; // Scale * Translation

	float CX = cos(DEG2RAD * rotation.x); float SX = sin(DEG2RAD * rotation.x);
	float CY = cos(DEG2RAD * rotation.y); float SY = sin(DEG2RAD * rotation.y);
	float CZ = cos(DEG2RAD * rotation.z); float SZ = sin(DEG2RAD * rotation.z);

	rot[0][0] =  CY * CZ;			rot[0][1] = -CY * SZ;			rot[0][2] =  SY;
	rot[1][0] = CX*SZ + SX*SY*CZ;	rot[1][1] = CX*CZ - SX*SY*SZ;	rot[1][2] = -SX*CY;
	rot[2][0] = SX*SZ - CX*SY*CZ;	rot[2][1] = -CX*SY*SZ + SX*CZ;	rot[2][2] = CX*CY;

	scaleTranslate[0][0] = scale.x;					scaleTranslate[1][1] = scale.y;					scaleTranslate[2][2] = scale.z;
	scaleTranslate[0][3] = scale.x * position.x;	scaleTranslate[1][3] = scale.y * position.y;	scaleTranslate[2][3] = scale.z * position.z;
	scaleTranslate[3][3] = 1;

	return rot * scaleTranslate;
}
