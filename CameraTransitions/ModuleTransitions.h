#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"


enum class TRANSITION_TYPE {
	NONE,
	FADE_TO_BLACK,
	SQUARED,
	CIRCLE,
	SLASH,
	THEATRE
};

class ModuleTransitions : public Module
{
public:
	ModuleTransitions(Application* app, bool start_enabled = false);
	~ModuleTransitions();

	//Current scene, Next scene, transition time in frames, transition type
	void Transition(Module* preScene, Module* postScene, int transitionTime, TRANSITION_TYPE transitionType)
	{
		//The module is already transitioning
		if (transitionTime < 0) {
			LOG("ERROR: INVALID TRANSITION TIME");
			return;
		}

		//The module is already transitioning
		if (IsEnabled()) {
			LOG("ERROR: ALREADY TRANSITIONING");
			return;
		}

		Enable();
		this->preScene = preScene;
		this->postScene = postScene;
		this->transitionTime = transitionTime;
		this->transitionType = transitionType;
	}

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


private:
	
	//PreScene disable, PostScene enable
	void SceneChange();

	//TransitionModules
	void FadeToBlack();
	void Squared();
	void Circle();
	void Slash();
	void Theatre();

	//Transition Sprites
	SDL_Texture* sprite = nullptr;

	//Variables
	int step;
	int transitionTime;
	TRANSITION_TYPE transitionType;
	Module* preScene;
	Module* postScene;
};
