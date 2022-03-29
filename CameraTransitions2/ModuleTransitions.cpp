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

	//SDL_SetRenderDrawBlendMode(App->renderer->renderer, SDL_BLENDMODE_NONE);

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
	int percentage = ((float)step / (float)transitionTime) * 40.0f;
	int w = SCREEN_WIDTH / 10;
	int h = SCREEN_HEIGHT / 10;

	if (step * 2 >= transitionTime)
		percentage = 40 - percentage;

	for (int j = 0; j < percentage; ++j){
		for (int i = 0; i < percentage; ++i) {
			App->renderer->DrawQuad(SDL_Rect{ w * i, h * (10 - j + i), w, h }, 0, 0, 0, 255);
		}
	}
}

void ModuleTransitions::Circle()
{

	float percentage = ((float)step / (float)transitionTime) * 2.0f;
	float r = 750.0f;

	if (step * 2 >= transitionTime)
		percentage = 2.0f - percentage;

	for (float i = 0.0f; i < (percentage * r); i += 0.1f) {
		App->renderer->DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, i, 0, 0, 0);
	}

	/*for (float i = 0; i < percentage; i += 0.1f) {
		int x = SCREEN_WIDTH / 2;
		int y = SCREEN_HEIGHT / 2;
		App->renderer->DrawLine(x, y, x + (r * cos(i)), y + (r * sin(i)), 0, 0, 0);
	}*/
	
}

void ModuleTransitions::Slash()
{
	int percentage = ((float)step / (float)transitionTime) * 200.0f;

	if (step * 2 >= transitionTime)
		percentage = 100 - percentage;

	//App->renderer->DrawQuad()
	
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

	case TRANSITION_TYPE::SQUARED:
		Squared();
		break;

	case TRANSITION_TYPE::CIRCLE:
		Circle();
		break;
	}
	
	if (2 * step >= transitionTime)
		SceneChange();

	if (step >= transitionTime)
		Disable();

	return UPDATE_CONTINUE;
}
