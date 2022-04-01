#include "Application.h"
#include "ModuleTransitions.h"
#include "SDL_image/include/SDL_image.h"

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

	//Sets blendmode to default + unload texture
	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_NONE);
	App->textures->Unload(sprite);
	sprite = nullptr;

	//Erase screenshot if exists
	remove("Assets/screenshot.bmp");

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

	for (int j = 0; j < percentage; ++j) {
		for (int i = 0; i < percentage; ++i) {
			App->renderer->DrawQuad(SDL_Rect{ w * i, h * (10 - j + i), w, h }, 0, 0, 0, 255);
		}
	}
}

void ModuleTransitions::Circle()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/circle.png");

	float percentage = ((float)step / (float)transitionTime) * 2.0f;

	if (step * 2 >= transitionTime)
		percentage = 2.0f - percentage;

	float scale = 5.0f * percentage;

	App->renderer->DrawTexture(sprite, SCREEN_WIDTH / 2.0f - 150.0f * scale, SCREEN_HEIGHT / 2.0f - 150.0f * scale, scale);
}

void ModuleTransitions::Slash()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/slash.png");

	float percentage = ((float)step / (float)transitionTime) * 200.0f;

	if (step * 2 >= transitionTime)
		percentage = 200 - percentage;

	int scale = 3;

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH / 2) * ((100.0f - percentage) / 100.0f)) + ((SCREEN_WIDTH - (600 * scale)) / 2),
		(SCREEN_HEIGHT - (300 * scale)) / 2, scale);

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH - (600 * scale)) / 2) - ((SCREEN_WIDTH / 2) * ((100.0f - percentage) / 100.0f)),
		(SCREEN_HEIGHT - (300 * scale)) / 2, scale, true);
}

void ModuleTransitions::Theatre()
{
	if (sprite == nullptr)
		sprite = App->textures->Load("Assets/semicircle.png");

	float percentage = ((float)step / (float)transitionTime) * 360.0f;

	int scale = 7;

	App->renderer->DrawTexture(sprite, ((SCREEN_WIDTH - (300 * scale)) / 2), SCREEN_HEIGHT, scale, false, NULL, 1.0f, percentage, 150 * scale, 0);
}

void ModuleTransitions::Dissolve()
{
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 255.0f;

	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sprite, 255.0f - percentage);

	App->renderer->DrawTexture(sprite, 0, 0);
}

void ModuleTransitions::Zoom()
{
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * 5.0f;

	App->renderer->DrawTexture(sprite, 0, 0, 1.0f + percentage);

}

//TODO 6: Defineix la funció de transició
void ModuleTransitions::Cut() {
	//If screenshot is made, load it
	if (App->renderer->screenshot) {
		sprite = App->textures->Load("Assets/screenshot.bmp");
	}

	//Call for screenshot
	if (sprite == nullptr) {
		App->renderer->pendingToScreenshot = true;
		return;
	}

	float percentage = ((float)step / (float)transitionTime) * ((float)SCREEN_HEIGHT / 2.0f);
	
	SDL_Rect top = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_Rect bot = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	App->renderer->DrawTexture(sprite, 0, -percentage, 1.0f, false, &top);
	App->renderer->DrawTexture(sprite, 0, SCREEN_HEIGHT / 2 + percentage, 1.0f, false, &bot);
}
//

update_status ModuleTransitions::Update()
{
	step++;

	return UPDATE_CONTINUE;
}

update_status ModuleTransitions::PostUpdate()
{
	//FUNCTION EXECUTION SWITCH
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

	case TRANSITION_TYPE::SLASH:
		Slash();
		break;

	case TRANSITION_TYPE::THEATRE:
		Theatre();
		break;

	case TRANSITION_TYPE::DISSOLVE:
		Dissolve();
		break;

	case TRANSITION_TYPE::ZOOM:
		Zoom();
		break;

	//TODO 4: Executa la funció de la transisió
	case TRANSITION_TYPE::CUT:
		Cut();
		break;
	//

	}

	//CHANGING SCENE SWITCH
	switch (transitionType) {

	//TODO 5: Assigna el tipus de transisió perquè faci el canvi de mòdul al principi.
	case TRANSITION_TYPE::CUT:
	//
	
	case TRANSITION_TYPE::ZOOM:
	case TRANSITION_TYPE::DISSOLVE:
		if (step >= 1)
			SceneChange();
		break;

	default:
		if (2 * step >= transitionTime)
			SceneChange();
		break;
	}

	if (step >= transitionTime)
		Disable();

	return UPDATE_CONTINUE;
}
