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

	backgroundTex = App->textures->Load("Assets/Background1.png");

	return ret;
}

// Load assets
bool ModuleScene1::CleanUp()
{
	App->textures->Unload(backgroundTex);

	return true;
}

update_status ModuleScene1::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 30, TRANSITION_TYPE::FADE_TO_BLACK);

	else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 120, TRANSITION_TYPE::SQUARED);

	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 120, TRANSITION_TYPE::CIRCLE);
	
	else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 120, TRANSITION_TYPE::SLASH);

	return UPDATE_CONTINUE;
}

update_status ModuleScene1::PostUpdate()
{
	App->renderer->DrawTexture(backgroundTex, 0, 0, 1.0f / 1.5f);
	return UPDATE_CONTINUE;
}
