#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleScene2 : public Module
{
public:
	ModuleScene2(Application* app, bool start_enabled = false);
	~ModuleScene2();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	
	SDL_Texture* backgroundTex;
};
