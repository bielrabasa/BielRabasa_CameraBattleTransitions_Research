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
	backgroundTex = nullptr;

	return true;
}

update_status ModuleScene1::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 30, TRANSITION_TYPE::FADE_TO_BLACK);

	else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 120, TRANSITION_TYPE::SQUARED);

	else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 60, TRANSITION_TYPE::CIRCLE);

	else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 30, TRANSITION_TYPE::SLASH);

	else if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 60, TRANSITION_TYPE::THEATRE);

	else if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 60, TRANSITION_TYPE::DISSOLVE);

	else if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 100, TRANSITION_TYPE::ZOOM);

	//TODO 2A: Executa la funció "Transition" de l'escena 1 a la 2, dona-li un temps de transisió i el tipus que has creat previament.
	else if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->transitions->Transition(App->scene1, App->scene2, 40, TRANSITION_TYPE::CUT);
	//

	return UPDATE_CONTINUE;
}

update_status ModuleScene1::PostUpdate()
{
	App->renderer->DrawTexture(backgroundTex, 0, 0, 1.0f / 1.5f);
	return UPDATE_CONTINUE;
}
