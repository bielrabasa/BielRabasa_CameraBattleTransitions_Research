#include "Globals.h"
#include "Application.h"
#include "ModuleScene1.h"

ModuleScene2::ModuleScene2(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	backgroundTex = nullptr;
}

ModuleScene2::~ModuleScene2()
{}

// Load assets
bool ModuleScene2::Start()
{
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	backgroundTex = App->textures->Load("Assets/Background2.png");

	return ret;
}

// Load assets
bool ModuleScene2::CleanUp()
{
	App->textures->Unload(backgroundTex);

	return true;
}

// Update: draw background
update_status ModuleScene2::Update()
{


	return UPDATE_CONTINUE;
}

update_status ModuleScene2::PostUpdate()
{
	App->renderer->DrawTexture(backgroundTex, 0, 0, 1.0f / 1.5f);

	return update_status();
}
