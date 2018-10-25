#include "SceneObject.h"

#include "MathGeoLib.h"
#include "Behaviour.h"

#define DEG2RAD 0.0174532925f

SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
	for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		delete(*it);
	behaviours.clear();
}

void SceneObject::Start()
{
	for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->Start();
}

void SceneObject::Update()
{
	for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->Update();

}

void SceneObject::CleanUp()
{
	for (std::list<Behaviour*>::iterator it = behaviours.begin(); it != behaviours.end(); ++it)
		(*it)->CleanUp();
}

void SceneObject::AddVertex(float x, float y, float z) 
{
	math::float3 v = { x,y,z };
	vertices.push_back(v);
}

std::vector<float>* SceneObject::GetVertices() 
{
	std::vector<float>* output = new std::vector<float>;

	for (std::list<math::float3>::iterator it = vertices.begin(); it != vertices.end(); ++it) 
	{		
		(*output).push_back((*it).x);
		(*output).push_back((*it).y);
		(*output).push_back((*it).z);
	}

	return output;
}

math::float4x4 SceneObject::RotationMatrix()
{

	math::float4x4 rot = math::float4x4::identity; // RotX * RotY * RotZ

	float CX = cos(DEG2RAD * rotation.x); float SX = sin(DEG2RAD * rotation.x);
	float CY = cos(DEG2RAD * rotation.y); float SY = sin(DEG2RAD * rotation.y);
	float CZ = cos(DEG2RAD * rotation.z); float SZ = sin(DEG2RAD * rotation.z);

	rot[0][0] = CY * CZ;				rot[0][1] = -CY * SZ;				rot[0][2] = SY;
	rot[1][0] = CX * SZ + SX * SY*CZ;	rot[1][1] = CX * CZ - SX * SY*SZ;	rot[1][2] = -SX * CY;
	rot[2][0] = SX * SZ - CX * SY*CZ;	rot[2][1] = -CX * SY*SZ + SX * CZ;	rot[2][2] = CX * CY;

	return rot;
}

math::float4x4 SceneObject::ModelMatrix()
{	
	math::float4x4 rot = RotationMatrix();
	math::float4x4 scaleM = math::float4x4::identity; 
	math::float4x4 translate = math::float4x4::identity;

	scaleM[0][0] = scale.x;				scaleM[1][1] = scale.y;				scaleM[2][2] = scale.z;
	translate[0][3] = position.x;		translate[1][3] = position.y;		translate[2][3] = position.z;

	return  translate * scaleM * rot;
}
