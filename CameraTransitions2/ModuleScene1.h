#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleScene1 : public Module
{
public:
	ModuleScene1(Application* app, bool start_enabled = true);
	~ModuleScene1();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	
	SDL_Texture* backgroundTex;
};
