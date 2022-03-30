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
	backgroundTex = nullptr;

	return true;
}

// Update: draw background
update_status ModuleScene2::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 60, TRANSITION_TYPE::FADE_TO_BLACK);

	else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 120, TRANSITION_TYPE::SQUARED);

	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 60, TRANSITION_TYPE::CIRCLE);
	
	else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 30, TRANSITION_TYPE::SLASH);

	else if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 60, TRANSITION_TYPE::THEATRE);

	else if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		App->transitions->Transition(App->scene2, App->scene1, 60, TRANSITION_TYPE::DISSOLVE);

	return UPDATE_CONTINUE;
}

update_status ModuleScene2::PostUpdate()
{
	App->renderer->DrawTexture(backgroundTex, 0, 0, 1.0f / 1.5f);

	return UPDATE_CONTINUE;
}
