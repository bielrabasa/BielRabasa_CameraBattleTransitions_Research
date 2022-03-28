#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"


enum class TRANSITION_TYPE {
	NONE,
	FADE_TO_BLACK,
	SQUARED,
};

class ModuleTransitions : public Module
{
public:
	ModuleTransitions(Application* app, bool start_enabled = false);
	~ModuleTransitions();

	//Current scene, Next scene, transition time in frames, transition type
	void Transition(Module* preScene, Module* postScene, int transitionTime, TRANSITION_TYPE transitionType)
	{
		if (transitionTime < 0) {
			LOG("INCORRECT TRANSITION TIME");
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
	
	void SceneChange();

	void FadeToBlack();
	void Squared();

	int step;
	int transitionTime;
	TRANSITION_TYPE transitionType;
	Module* preScene;
	Module* postScene;
};
