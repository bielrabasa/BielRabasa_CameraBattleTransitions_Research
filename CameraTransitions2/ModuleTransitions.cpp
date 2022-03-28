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
	SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_BLEND);

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
	if (2 * step < transitionTime) {
		App->renderer->DrawQuad(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, (float(step * 2) / (float)transitionTime) * 255.0f);
	}
	else if (step * 2 == transitionTime) {
		App->renderer->DrawQuad(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 255.0f);
	}
	else {
		App->renderer->DrawQuad(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 255.0f - (float(step * 2) / (float)transitionTime) * 255.0f);
	}
	
}

void ModuleTransitions::Squared()
{
	int percentage = (float)step / (float)transitionTime * 100.0f;
	percentage /= 10;
	if (step * 2 < transitionTime) {
		switch (percentage) {
		case 10:
			App->renderer->DrawQuad(SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 0, 0, 255.0f);
		case 9:
			//CONTINUE
		}
	}
}

update_status ModuleTransitions::Update()
{
	step++;

	return UPDATE_CONTINUE;
}

update_status ModuleTransitions::PostUpdate()
{
	switch (transitionType) {
	case TRANSITION_TYPE::FADE_TO_BLACK:
		FadeToBlack();
		break;
	}
	
	if (2 * step >= transitionTime)
		SceneChange();

	if (step >= transitionTime)
		Disable();

	return UPDATE_CONTINUE;
}
