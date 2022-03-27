#include "Globals.h"
#include "Application.h"
#include "ModuleScene1.h"

ModuleScene1::ModuleScene1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	backgroundTex = nullptr;
}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
{
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	backgroundTex = App->textures->Load("Assets/Background1.png");

	return ret;
}

// Load assets
bool ModuleScene1::CleanUp()
{
	App->textures->Unload(backgroundTex);

	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	App->renderer->DrawTexture(backgroundTex, 0, 0, 1.0f/1.5f);


	return UPDATE_CONTINUE;
}

update_status ModuleScene1::PostUpdate()
{
	return update_status();
}
