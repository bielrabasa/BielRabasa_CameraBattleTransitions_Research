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
	
	step = 0;

	return ret;
}

bool ModuleTransitions::CleanUp()
{
	preScene = nullptr;
	postScene = nullptr;

	SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_NONE);

	return true;
}

void ModuleTransitions::SceneChange()
{
	preScene->Disable();
	postScene->Enable();
}

void ModuleTransitions::FadeToBlack()
{
	App->renderer->DrawQuad(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 255, 0, 0, 255);
}

update_status ModuleTransitions::Update()
{
	step++;

	//SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_BLEND);

	switch (transitionType) {
	case TRANSITION_TYPE::FADE_TO_BLACK:
		FadeToBlack();
		break;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleTransitions::PostUpdate()
{
	
	
	if (2 * step >= transitionTime)
		SceneChange();

	if (step >= transitionTime)
		Disable();

	return update_status();
}
