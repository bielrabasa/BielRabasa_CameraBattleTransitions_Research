#include "Application.h"
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModuleTransitions.h"

class FadeToBlack : public Transitioning {
public:
	void Start() {}
	void Update() {}
	void PostUpdate() {}
	void CleanUp() {}
};