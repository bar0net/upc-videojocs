#include "Application.h"

#include <vector>

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "SceneObject.h"

#include "GL/glew.h"
#include "SDL.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

#define PI 3.14169258f
#define ASPECT 1.7777778f

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{

	// Create Objects
	triangle = new SceneObject();
	triangle->position = { 10.0f, 0.0f, 10.0f };
	triangle->scale = { 0.5f, 1.0f, 0.5f };
	triangle->rotation = { 0.0f, 0.0f, 10.0f };
	
	// Base (Red)
	triangle->AddVertex(-0.5f, -0.5f, -0.33f );
	triangle->AddVertex( 0.0f, -0.5f,  0.66f );
	triangle->AddVertex( 0.5f, -0.5f, -0.33f );

	// Wall (Blue)
	triangle->AddVertex(0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, -0.5f, 0.66f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);

	// Wall (Green)
	triangle->AddVertex(0.0f, -0.5f, 0.66f);
	triangle->AddVertex(-0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);

	// Wall (White)
	triangle->AddVertex(-0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.5f, -0.5f, -0.33f);
	triangle->AddVertex(0.0f, 0.5f, 0.0f);

	// Camera
	camera = new SceneObject();
	camera->position = { 0.0f, 5.0f, 0.0f };
	camera->scale = { 1.0f, 1.0f, 1.0f };
	camera->rotation = { 0.0f, 0.0f, 0.0f };

	// Load GL Program
	LoadShaderProgram();
	glUseProgram(program);

	// Fill Buffer
	std::vector<float>* vertex_buffer_data = triangle->GetVertices();
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (*vertex_buffer_data).size() * sizeof(float), (*vertex_buffer_data).data(), GL_STATIC_DRAW);

	// Set Projection, View & Model
	math::float4x4 model = triangle->ModelMatrix();
	math::float4x4 view = LookAt(*triangle, *camera);
	math::float4x4 projection = ProjectionMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete vertex_buffer_data;
    return vbo;
}

update_status ModuleRenderExercise::Update()
{

	++(triangle->rotation.y);
	math::float4x4 model = triangle->ModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);

	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0 );

	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

	glUniform3f(glGetUniformLocation(program, "albedo"),0.0f,1.0f,0.0f);
	glDrawArrays(GL_TRIANGLES, 3, 3);

	glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 6, 3);

	glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 9, 3);

    glDisableVertexAttribArray(0);
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    if(vbo != 0)		glDeleteBuffers(1, &vbo);
	if (program != 0)	glDeleteProgram(program);

	delete triangle;
	delete camera;

	return true;
}

void ModuleRenderExercise::LoadShaderProgram() 
{
	GLint success = 0;
	unsigned vShader = 0;
	unsigned fShader = 0;

	// ==== COMPILE VERTEX SHADER ====
	char* vShaderData = LoadShaderData("Default.vs");
	assert(vShaderData != nullptr);
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderData, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)	LOG("[GL] Vertex Shader failed to compile.")
	else LOG("[GL] Vertex Shader successfully compiled")

	// ==== COMPILE FRAGMENT SHADER ====
	char* fShaderData = LoadShaderData("default.fs");
	assert(fShaderData != nullptr);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderData, NULL);
	glCompileShader(fShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) LOG("[GL] Fragment Shader failed to compile.")
	else LOG("[GL] Fragment Shader successfully compiled")

	// ==== LINK PROGRAM ====
	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		program = 0;

		LOG("[GL] Program failed to link.")
	}
	else
	{
		LOG("[GL] Program successfully linked")
	}

	glDetachShader(program, vShader);
	glDetachShader(program, fShader);

	if (vShader != 0)	glDeleteShader(vShader);
	if (fShader != 0)	glDeleteShader(fShader);
}

char* ModuleRenderExercise::LoadShaderData(const char* filename)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = (char*)malloc(size + 1);

		fread(data, 1, size, file);
		data[size] = 0;

		fclose(file);
	}
	return data;
}


math::float4x4 ModuleRenderExercise::LookAt(const SceneObject &target, const SceneObject &eye)
{
	math::float3 up(
		cos(eye.rotation.x) * sin(eye.rotation.z) + sin(eye.rotation.x) * sin(eye.rotation.y) * cos(eye.rotation.z),
		cos(eye.rotation.x) * cos(eye.rotation.z) - sin(eye.rotation.x) * sin(eye.rotation.y) * sin(eye.rotation.z),
		-sin(eye.rotation.x) * cos(eye.rotation.y)
	);

	math::float3 f(target.position - eye.position); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));

	math::float4x4 matrix = {
		 s.x,	 s.y,	 s.z,	-s.Dot(eye.position),
		 u.x,	 u.y,	 u.z,	-u.Dot(eye.position),
		-f.x,	-f.y,	-f.z,	 f.Dot(eye.position),
		0.0f,	0.0f,	0.0f,	 1.0f
	};

	return matrix;
}

math::float4x4 ModuleRenderExercise::ProjectionMatrix()
{
	math::Frustum frustrum;
	frustrum.type = FrustumType::PerspectiveFrustum;

	frustrum.pos = float3::zero;
	frustrum.front = -float3::unitZ;
	frustrum.up = float3::unitY;

	frustrum.nearPlaneDistance = 0.1f;
	frustrum.farPlaneDistance = 100.0f;
	frustrum.verticalFov = PI / 4.0f;
	frustrum.horizontalFov = 1.0f * atanf(tanf(frustrum.verticalFov * 0.5f) * ASPECT);
	
	return frustrum.ProjectionMatrix();
}