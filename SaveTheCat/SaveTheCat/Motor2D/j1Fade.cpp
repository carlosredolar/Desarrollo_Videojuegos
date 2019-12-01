#include <math.h>
#include "j1App.h"
#include "j1Fade.h"
#include "j1Render.h"
#include "p2Log.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

//Load Scenes
/*#include "ModulePlayerSelection.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFFIntro.h"
#include "ModuleFFIntro2.h"*/

j1Fade::j1Fade()
{
	
}

j1Fade::~j1Fade()
{}

// Load assets
bool j1Fade::Start()
{
	LOG("Preparing Fade Screen");
	screen = { 0, 0, App->render->camera.w,  App->render->camera.h };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);	
	return true;
}

// Update: draw background
bool j1Fade::Update(float dt)
{
	BROFILER_CATEGORY("Update_Fade", Profiler::Color::Chocolate)

	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			ModuleOff->active=false;
			ModuleOn->active=true;

			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1Fade::FadeToBlack(j1Module* module_off, j1Module* module_on, float time)
{
	bool ret = false;
	ModuleOff = module_off;
	ModuleOn = module_on;
	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;
	}

	return ret;
}