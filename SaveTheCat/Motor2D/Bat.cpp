/*#include "Bat.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Audio.h"
#include "j1Pathfinding.h"
#include "j1Player.h"

Bat::Bat() :j1Module() {
	name.create("bat");
	debugPath = false;
	LoadAnimations();
}

Bat::~Bat() { }

bool Bat::Start()
{
	debug_tex = App->tex->Load("maps/path.png");

	return ret;
}

void Bat::PathControl()
{
	static iPoint origin = position;
	static bool origin_selected = false;

	int x, y;
	x = App->player->position.x;
	y = App->player->position.y;
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(position.DistanceTo(App->player->position)<100) App->pathfinding->CreatePath(origin, p);
}

bool Bat::PreUpdate()
{
	PathControl();

	
	return true;
}

bool Bat::Update(float dt)
{


	// Debug pathfinding ------------------------------
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) debugPath = !debugPath;

	if (debugPath)
	{		
		const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)///Text for path
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(debug_tex, pos.x, pos.y);
		}
	}
}

bool Bat::CleanUp() 
{
	collider = nullptr;
	debug_tex = nullptr;
	bat_tex = nullptr;
	return true;
}*/