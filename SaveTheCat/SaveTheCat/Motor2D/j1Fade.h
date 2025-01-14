#ifndef __J1FADE_H__
#define __J1FADE_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"
#include "Brofiler/Brofiler.h"

class j1Fade : public j1Module
{
public:
	j1Fade();
	~j1Fade();
	j1Module* ModuleOn = nullptr;
	j1Module* ModuleOff = nullptr;

	bool Start();
	bool Update(float dt);
	bool FadeToBlack(j1Module* module_off, j1Module* module_on, float time = 2.0f);

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
};

#endif 