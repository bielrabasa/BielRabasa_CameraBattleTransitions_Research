#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{

	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	

	return UPDATE_CONTINUE;
}
