#include "Globals.h"
#include "Application.h"
#include "ModuleTransitions.h"

ModuleTransitions::ModuleTransitions(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleTransitions::~ModuleTransitions()
{}

// Load assets
bool ModuleTransitions::Start()
{
	bool ret = true;
	
	frames = 0;

	return ret;
}

// Load assets
bool ModuleTransitions::CleanUp()
{
	preScene = nullptr;
	postScene = nullptr;

	return true;
}

void ModuleTransitions::SceneChange()
{
	preScene->Disable();
	postScene->Enable();
}

// Update: draw background
update_status ModuleTransitions::Update()
{


	return UPDATE_CONTINUE;
}

update_status ModuleTransitions::PostUpdate()
{
	if (2 * frames >= transitionTime)
		SceneChange();

	frames++;

	if (frames > transitionTime)
		Disable();

	return update_status();
}
