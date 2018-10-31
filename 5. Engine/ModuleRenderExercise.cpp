#include "Application.h"

#include <vector>

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "SceneObject.h"
#include "ModuleTextures.h"

#include "GL/glew.h"
#include "SDL.h"
#include "MathGeoLib/include/Geometry/Frustum.h"
#include "EditorCameraMove.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

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
	triangle->position = { 0.0f, 2.0f, 1.0f };
	triangle->scale = { 1.0f, 1.0f, 1.0f };
	triangle->rotation = { 0.0f, 0.0f, 0.0f };
	
	// (x,y,z,uv0,uv1)
	triangle->AddVertex(-0.5f,  0.5f, 0.f, 0.0f, 1.0f );
	triangle->AddVertex( 0.5f,  0.5f, 0.f, 1.0f, 1.0f );
	triangle->AddVertex(-0.5f, -0.5f, 0.f, 0.0f, 0.0f );
	triangle->AddVertex( 0.5f, -0.5f, 0.f, 1.0f, 0.0f );

	camera = new SceneObject();
	camera->position = { 0.0f, 1.0f, 10.0f };
	camera->scale = { 1.0f, 1.0f, 1.0f };
	camera->rotation = { 0.0f, 0.0f, 0.0f };
	camera->behaviours.push_back(new EditorCameraMove(camera));

	// Load GL Program

	shader = new Shader("Default.vs", "default.fs");
	shader->Bind();

	// Fill Buffer
	std::vector<float>* vertex_buffer_data = triangle->GetVertices();
	std::vector<unsigned int> indices = { 1,0,2,1,2,3 };

	vbo = new VertexBuffer(4*5, vertex_buffer_data->data());
	vbo->Bind();

	//glBufferData(GL_ARRAY_BUFFER, (*vertex_buffer_data).size() * sizeof(float), (*vertex_buffer_data).data(), GL_STATIC_DRAW);
	vao = new VertexArray();
	vao->AddAttrib(vbo, 3, VA_Float, 5 * sizeof(float), 0);
	vao->AddAttrib(vbo, 2, VA_Float, 5 * sizeof(float), 3 * sizeof(float));

	ibo = new IndexBuffer(6, indices.data());
	ibo->Bind();

	// Load Texture
	const char* filename = "Lenna.png";
	textureID = App->textures->Load(filename);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);

	// Set Projection, View & Model
	math::float4x4 model = triangle->ModelMatrix();
	math::float4x4 view = camera->ModelMatrix().Inverted();
	math::float4x4 projection = ProjectionMatrix();
	shader->SetUniform4x4("model", &model[0][0]);
	shader->SetUniform4x4("view", &view[0][0]);
	shader->SetUniform4x4("proj", &projection[0][0]);
	
	delete vertex_buffer_data;

	triangle->Start();
	camera->Start();

    return vbo;
}

update_status ModuleRenderExercise::Update()
{
	triangle->Update();
	camera->Update();
	math::float4x4 view = camera->ModelMatrix().Inverted();
	shader->Bind();
	shader->SetUniform4x4("view", &view[0][0]);


	DrawPlane();

	//++(triangle->rotation.y);
	math::float4x4 model = triangle->ModelMatrix();
	shader->Bind();
	shader->SetUniform4x4("model", &model[0][0]);
	shader->SetUniform3("albedo", 1.0f, 0.0f, 0.0f);

	vao->Bind();
	ibo->Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);

	// bind ibo

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	vao->UnBind();
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	triangle->CleanUp();
	camera->CleanUp();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//if (ibo != 0) glDeleteBuffers(1, &ibo);
    //if(vbo != 0)		glDeleteBuffers(1, &vbo);
	//if (program != 0)	glDeleteProgram(program);

	delete triangle;
	delete camera;

	delete shader;
	delete vbo;
	delete vao;
	delete ibo;

	return true;
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
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	frustrum.horizontalFov = 2.0f * atanf(tanf(frustrum.verticalFov * 0.5f) * w / h);
	
	return frustrum.ProjectionMatrix();
}

void ModuleRenderExercise::DrawPlane()
{
	math::float4x4 identity = math::float4x4::identity;
	shader->SetUniform4x4("model", &identity[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &identity[0][0]);

	for (float i = -200; i < 200; i++)
	{
		if (i == 0) continue;
		if ((int)i % 5 == 0)
		{
			glLineWidth(2.0f);
			shader->SetUniform3("albedo", 1.0f, 1.0f, 1.0f);
			//glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
		}
		else
		{
			glLineWidth(1.0f);
			shader->SetUniform3("albedo", 0.66f, 0.66f, 0.66f);
			//glUniform3f(glGetUniformLocation(program, "albedo"), 0.66f, 0.66f, 0.66f);
		}

		glBegin(GL_LINES);
		glVertex3f(i, 0.0f, -200.f);
		glVertex3f(i, 0.0f,  200.f);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-200.f, 0.0f, i);
		glVertex3f( 200.f, 0.0f, i);
		glEnd();
	}

	glLineWidth(2.0f);
	shader->SetUniform3("albedo", 1.0f, 1.0f, 1.0f);
	//glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0f, -200.f);
	glVertex3f(0.0f, 0.0f, 0.f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0f, 1.f);
	glVertex3f(0.0f, 0.0f, 200.f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-200.f, 0.0f, 0.0f);
	glVertex3f(0.f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(1.f, 0.0f, 0.0f);
	glVertex3f(200.f, 0.0f, 0.0f);
	glEnd();

	glLineWidth(2.f);
	shader->SetUniform3("albedo", 1.0f, 0.0f, 0.0f);
	//glUniform3f(glGetUniformLocation(program, "albedo"), 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	shader->SetUniform3("albedo", 0.0f, 1.0f, 0.0f);
	//glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	shader->SetUniform3("albedo", 0.0f, 0.0f, 1.0f);
	//glUniform3f(glGetUniformLocation(program, "albedo"), 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
}
