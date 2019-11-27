
#include "Bat.h"
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

bool Bat::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

bool Bat::Start()
{
	bool ret = true;
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


	//if the player is close we create a path to him
	if (abs(App->player->position.x - position.x) < 100)
	{
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(App->player->position.x, App->player->position.y);
		App->pathfinding->CreatePath(origin, destination);
		chasing = true;
	}
	else { chasing = false; }
}

bool Bat::PreUpdate()
{
	PathControl();
	
	return true;
}

bool Bat::Update(float dt)
{
	bool ret = true;
	// Debug pathfinding ------------------------------
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) debugPath = !debugPath;
	
	if (chasing && debugPath)
	{
		int x, y;
		SDL_Rect Debug_rect = { 0,0,32,32 };

		path = App->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)///Text for path
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(debug_tex, pos.x, pos.y);
		}
	}

	//movement
	if ((path != nullptr) && (path->Count() != 0))
	{
		//compare position to tile to go
		int i = 0;
		iPoint current_map_position = App->map->WorldToMap(position.x, position.y);
		iPoint tile_to_go;
		tile_to_go.x = path->At(i)->x;
		tile_to_go.y = path->At(i)->y;

		if (tile_to_go.y < current_map_position.y)
		{
			i++;
		}

		if (current_map_position.x == tile_to_go.x)
		{
			i++;
			if (i > 1)
			{
				tile_to_go = App->map->WorldToMap(path->At(i)->x, path->At(i)->y);
			}
		}

		/*if (current_map_position.x > tile_to_go.x) {
			LOG("Going left");
			state = RUN_BACKWARD;
		}
		if (current_map_position.x < tile_to_go.x) {
			LOG("Going right");
			state = RUN_FORWARD;
		}
		if (current_map_position.y > tile_to_go.y) {
			LOG("Going up");
			position.y -= 3;
		}
		if (current_map_position.y < tile_to_go.y) {
			LOG("Going down");
		}*/
	}

	return ret;
}

bool Bat::CleanUp() 
{
	collider = nullptr;
	debug_tex = nullptr;
	bat_tex = nullptr;
	return true;
}

bool Bat::PostUpdate() {
	/*BROFILER_CATEGORY("PostUpdate_Player", Profiler::Color::Thistle)
		App->render->Blit(player_tex, position.x, position.y, &current_animation->GetCurrentFrame(), flip);*/

	return true;
}

void Bat::OnCollision(Collider* c1, Collider* c2) 
{
			
}

bool Bat::LoadAnimations() 
{
	bool ret = true;
	/*pugi::xml_parse_result result = animation_doc.load_file("sprites/characters/animations.xml");
	bool ret = true;
	uint i = 0u;
	uint j = 0;

	if (result == NULL)
	{
		LOG("Could not load animations xml file %s. pugi error: %s", "animations.xml", result.description());
		ret = false;
	}


	LOG("%u animations loaded", i);*/

	return ret;
}

bool Bat::Save(pugi::xml_node& data) const {

	pugi::xml_node p_position = data.append_child("position");

	p_position.append_attribute("x") = position.x;
	p_position.append_attribute("y") = position.y;
	return true;
}

bool Bat::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}
