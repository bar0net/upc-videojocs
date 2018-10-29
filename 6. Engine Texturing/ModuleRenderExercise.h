#ifndef __ModuleRenderExercise_h__
#define __ModuleRenderExercise_h__

#include "Module.h"

#include "MathGeoLib.h"
#include "Math/float4x4.h"
#include "Math/float3.h"

class ModuleRenderExercise : public Module
{
public:
    ModuleRenderExercise();
    ~ModuleRenderExercise();

	bool            Init    ();
	update_status   Update  ();
	bool            CleanUp ();

private:

    void LookAt (math::float4x4&  matrix, const math::float3& eye, const math::float3& target, const math::float3& up);

private:
    unsigned vbo        = 0;
	unsigned texture0   = 0;

	math::float4x4 tri_model = math::float4x4::identity;
	math::float4x4 proj      = math::float4x4::identity;
    math::float4x4 view      = math::float4x4::identity;
};

#endif /* __ModuleRenderExercise_h__ */
