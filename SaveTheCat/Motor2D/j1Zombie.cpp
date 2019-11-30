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
#include "j1Zombie.h"
#include "j1Player.h"
#include "j1Pathfinding.h"
#include "j1Entity.h"
#include "j1EntityManager.h"


j1Zombie::j1Zombie() :j1Entity(EntityType::WALKING_ENEMY)
{
	name.create("walking_enemy");
	//variable declaration from EntityManager
	player = App->entities->player;
	gravity = App->entities->gravity;
	type = EntityType::WALKING_ENEMY;
	debugPath = false;

	if (App->entities->reference_walking_enemy != nullptr)
	{
		speed = App->entities->reference_walking_enemy->speed;
		health = App->entities->reference_walking_enemy->health;
		damage = App->entities->reference_walking_enemy->damage;

		animations = App->entities->reference_walking_enemy->animations;
		idle = *animations.start->data;
		attack = *animations.start->next->data;
		run = *animations.end->data;
		//run = animations
		/*
		p2List_item<Animation*>* animation = animations.start;
		for (p2List_item<Animation*>* item = App->entities->reference_walking_enemy->animations.start; item != nullptr; item = item->next)
		{
			animations.add(item->data);
		}
		*/
	}

	lastPosition = position;

	/*
	animations = App->entities->walking_enemy_animations;
	//idle.PushBack({ 16,34,27,30 });
	if (App->entities->walking_enemy_animations.start != nullptr)
	{
		idle = *App->entities->walking_enemy_animations.start->data;
	}
	//animations = App->entities->walking_enemy_animations;
	*/

	flip = SDL_FLIP_HORIZONTAL;

	//colliders
	collider = App->collision->AddCollider({ 16,34,27,30 }, COLLIDER_ENEMY, (j1Module*)this);

}


j1Zombie::~j1Zombie() {
	/*
	App->tex->UnLoad(texture);
	texture = nullptr;
	collider->to_delete = true;
	collider = nullptr;
	raycast->to_delete = true;
	raycast = nullptr;*/	
}

bool j1Zombie::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

bool j1Zombie::Start()
{
	bool ret = true;
	debug_tex = App->tex->Load("maps/path.png");

	return ret;
}

void j1Zombie::PathControl()
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

bool j1Zombie::PreUpdate()
{
	PathControl();

	return true;	

}

bool j1Zombie::Update(float dt) 
{
	bool ret = true;
	lastPosition = position;
	gravity = 925;


	//what to do when getting to a gap
	/*if (last_collider != nullptr)
	{
		if (!raycast->CheckCollision(last_collider->rect))
		{
			grounded = false;
			//current_speed.x = -current_speed.x;
		}
	}*/

	//guard path
	//if ((position.x < path_minimum)||(position.x > path_maximum)) current_speed.x -= current_speed.x;


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

	/*//state machine
	switch (state)
	{
		run = idle;
	case IDLE:
		current_animation = &idle;
		break;
	case JUMP:
		current_animation = &jump;
		break;
	case RUN_FORWARD:
		//current_animation = &run;
		current_speed.x = speed.x;
		flip = SDL_FLIP_NONE;
		break;
	case RUN_BACKWARD:
		//current_animation = &run;
		current_speed.x = -speed.x;
		flip = SDL_FLIP_HORIZONTAL;
		break;
	case FALL:
		current_animation = &fall;
		break;
	case ATTACK:
		current_animation = &attack;
		break;
	case DIE:
		current_animation = &die;
		break;
	default:
		break;
	}

	//Movement Control
	if (!grounded) {
		//if (current_speed.y > max_falling_speed) 
		current_speed.y -= gravity * dt;
		position.y -= current_speed.y * dt;
	}

	position.x += current_speed.x * dt;

	//collider control

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if ((raycast != nullptr) && (collider != nullptr))
		raycast->SetPos(collider->rect.x + collider->rect.w * 0.5f - raycast->rect.w * 0.5f, position.y + current_animation->GetCurrentFrame().h);
		*/
	return ret;
}

bool j1Zombie::PostUpdate() {
	bool ret = true;
	//App->render->Blit(texture, position.x, position.y, &current_animation->GetCurrentFrame(), flip);
	return ret;
}


void j1Zombie::OnCollision(Collider* c1, Collider* c2) {

	/*if (c1 == raycast)
	{
		last_collider = c2;
	}

	switch (c2->type)
	{
	case COLLIDER_WALL:
		if (position.y + current_animation->GetCurrentFrame().h < c2->rect.y + COLLIDER_MARGIN)
		{
			grounded = true;
			position.y = c2->rect.y - current_animation->GetCurrentFrame().h;
			current_speed.y = 0;
			state = IDLE;
		}

		if (position.y + current_animation->GetCurrentFrame().h > c2->rect.y) {
			position.x = lastPosition.x;
		}
		if (position.y > c2->rect.y + c2->rect.h - COLLIDER_MARGIN)
		{
			position.y = c2->rect.y + c2->rect.h;
			current_speed.y = 0;
		}
		if ((position.y > c2->rect.y) && (position.x > c2->rect.x) && (position.x + current_animation->GetCurrentFrame().w < c2->rect.x + c2->rect.w) && (position.x < c2->rect.x + c2->rect.w))
		{
			position.y = lastPosition.y;
			if (lastPosition.y + current_animation->GetCurrentFrame().h > c2->rect.y) {
				//position.y = c2->rect.y - current_animation->GetCurrentFrame().h;
			}
		}
		break;
	case COLLIDER_PLAYER:
		App->entities->DestroyEntity(this);
		//state = DIE;
		break;
	default:
		break;
	}*/
}

bool j1Zombie::CleanUp()
{
	collider = nullptr;
	debug_tex = nullptr;
	zombie_tex = nullptr;
	return true;
}

bool j1Zombie::LoadAnimations()
{
	bool ret = true;
	pugi::xml_parse_result result = animation_doc.load_file("sprites/characters/animationsZombie.xml");
	//bool ret = true;
	uint i = 0u;
	uint j = 0;

	if (result == NULL)
	{
		LOG("Could not load animations xml file %s. pugi error: %s", "animations.xml", result.description());
		ret = false;
	}

	LOG("%u animations loaded", i);

	return ret;
}

bool j1Zombie::Save(pugi::xml_node& data) const {

	pugi::xml_node p_position = data.append_child("position");

	p_position.append_attribute("x") = position.x;
	p_position.append_attribute("y") = position.y;
	return true;
}

bool j1Zombie::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}
