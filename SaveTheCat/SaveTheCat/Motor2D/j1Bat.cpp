#include "j1Bat.h"
#include "j1Player.h"
#include "j1Pathfinding.h"
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

j1Bat::j1Bat() :j1Module() {
	name.create("bat");

	LoadAnimations();

}

j1Bat::~j1Bat() { }

bool j1Bat::Awake(pugi::xml_node& config) {

	LOG("Loading Player Data");
	bool ret = true;

	current_animation = &fly;

	folder.create(config.child("folder").child_value());

	
	speed = 50;
	gravity = 20;
	deathFX = "sounds/death.wav";

	

	return ret;
}

bool j1Bat::Start() {
	//load character sprites
	bat_tex = App->tex->Load("sprites/characters/spritesheet_bat.png");
	debug_tex = App->tex->Load("maps/path.png");

	bat_x_position = 1100;
	bat_y_position = 500;

	position.x = bat_x_position;
	position.y = bat_y_position;

	collider = App->collision->AddCollider(current_animation->GetCurrentFrame(), COLLIDER_ENEMY, (j1Module*)App->bat);

	App->audio->LoadFx(deathFX.GetString());

	waitTimer = 0;
	deathSound = false;

	return true;
}

bool j1Bat::CleanUp() {
	collider->to_delete = true;
	SDL_DestroyTexture(bat_tex);
	//bat_tex = nullptr;
	return true;
}


bool j1Bat::PreUpdate() {
	BROFILER_CATEGORY("PreUpdate_Player", Profiler::Color::Tan)

	lastPosition = position;
	last_state = state;

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		god = !god;
		if (god)
		{
			state = FLY;
			velocity.y = 0;
		}
	}

	
	if (!App->pause)
	{
		velocity.x = 0;
		if (state == FLY)
		{
			collider->SetSize(80, 66);

			if (can_go_right == true)
			{
				state = FLY_RIGHT;
			}

			if (can_go_left == true)
			{
				state = FLY_LEFT;
			}


			if (can_go_down == true)
			{
				state = FLY_DOWN;
			}

			if (can_go_up == true)
			{
				state = FLY_UP;
			}

		}

		if (state == FLY_RIGHT)
		{
			collider->SetSize(80, 66);
			if (can_go_right == false)
			{
				state = FLY;
				velocity.x = 0;
			}

			if (can_go_up == true)
			{
				state = FLY_UP;
				
			}

			if (can_go_down == true)
			{
				state = FLY_DOWN;
				flip == SDL_FLIP_NONE;
				
			}

			velocity.x = speed;
		}

		if (state == FLY_LEFT)
		{
			collider->SetSize(80, 66);
			if (can_go_left == false)
			{
				state = FLY;
				velocity.x = 0;
			}

			if (can_go_up == true)
			{
				state = FLY_UP;
				
			}

			if (can_go_down == true)
			{
				state = FLY_DOWN;
				flip == SDL_FLIP_HORIZONTAL;
				
			}

			velocity.x = -speed;
		}


		if (state == FLY_DOWN)
		{
			collider->SetSize(80, 55);
			if (can_go_down == false)
			{
				state = FLY;
				velocity.y = 0;
			}
			velocity.y = -speed;
		}


		if (state == FLY_UP)
		{
			collider->SetSize(80, 55);
			if (can_go_up == false)
			{
				state = FLY;
				velocity.y = 0;
			}
			velocity.y = speed;
		}


		if (state == DEATH_BAT)
		{
			collider->SetSize(80, 60);

			velocity.y -= gravity;
		}


		

		collider->SetPos(position.x, position.y);
	}

	


	return true;
}

bool j1Bat::Update(float dt)
{
	BROFILER_CATEGORY("Update_Player", Profiler::Color::Teal)

		
	
		switch (state)
		{
		case FLY:
			current_animation = &fly;
			break;

		case FLY_RIGHT:
			current_animation = &fly;
			flip = SDL_FLIP_NONE;
			
			break;

		case FLY_LEFT:
			current_animation = &fly;
			flip = SDL_FLIP_HORIZONTAL;
		
			break;


		case FLY_DOWN:
			current_animation = &fly;
			
			break;

		case FLY_UP:
			current_animation = &fly;
			
			break;

		case DEATH_BAT:
			current_animation = &death_bat;
			velocity.y -= gravity;
			position.y -= velocity.y * dt;
			collider->type = COLLIDER_HIT;
			timer = SDL_GetTicks();
			deathSound = false;
			break;
		default:
			LOG("No state found");
			break;
		}

	

	if (timer - SDL_GetTicks() >= DELAY)
	{
		collider->type = COLLIDER_ENEMY;
		velocity.x = 0;
		velocity.y = 0;
		
	}

	MovementControl(dt);

	death_reset = SDL_GetTicks();

	


	return true;
}

bool j1Bat::PostUpdate() {
	BROFILER_CATEGORY("PostUpdate_Player", Profiler::Color::Thistle)
		App->render->Blit(bat_tex, position.x, position.y, &current_animation->GetCurrentFrame(), flip);

	return true;
}

void j1Bat::OnCollision(Collider* c1, Collider* c2) {
	if (!god)
	{
		switch (c2->type)
		{
		case COLLIDER_WALL:
			position = lastPosition;
			velocity.x = velocity.y = 0;

			if ((position.x < c2->rect.x + COLLIDER_PREDICTION) )
			{
				if (position.y + current_animation->GetCurrentFrame().h < c2->rect.y + COLLIDER_PREDICTION) {
					position.y = c2->rect.y - App->bat->collider->rect.h;
					state = FLY;
					velocity.y = speed;
					
				}
				can_go_right = false;
			}
			if ((position.x > c2->rect.x + c2->rect.w - COLLIDER_PREDICTION))
			{
				velocity.y = speed;
				can_go_left = false;
			}
			if ((position.y < c2->rect.y + COLLIDER_PREDICTION))
			{

				if (position.y + current_animation->GetCurrentFrame().h < c2->rect.y + COLLIDER_PREDICTION) {
					position.y = c2->rect.y - App->bat->collider->rect.h;
				}
				velocity.y = speed;
				state = FLY;
				
				can_go_right = true;
				can_go_left = true;
			}

			break;

		case COLLIDER_HIT:
			if (!god) {
				state = DEATH_BAT;
				velocity.x = 0;
			}
			break;

		default:
			break;
		}
	}
}

bool j1Bat::LoadAnimations() {
	pugi::xml_parse_result result = animation_doc.load_file("sprites/characters/animations_bat.xml");
	bool ret = true;
	uint i = 0u;
	uint j = 0;

	if (result == NULL)
	{
		LOG("Could not load animations xml file %s. pugi error: %s", "animations.xml", result.description());
		ret = false;
	}

	animations.add(&fly);
	animations.add(&death_bat);

	pugi::xml_node animation = animation_doc.child("animations").child("animation");
	pugi::xml_node frame;
	p2List_item<Animation*>* item = animations.start;
	int x, y, w, h;
	float anim_speed = 1;

	LOG("Loading animations ---------");

	for (animation; animation; animation = animation.next_sibling("animation"))
	{
		item->data->loop = animation.attribute("loop").as_bool();

		for (frame = animation.child("data").child("frame"); frame; frame = frame.next_sibling("frame"))
		{
			x = frame.attribute("x").as_int();
			y = frame.attribute("y").as_int();
			w = frame.attribute("w").as_int();
			h = frame.attribute("h").as_int();
			anim_speed = frame.attribute("speed").as_float();

			item->data->PushBack({ x,y,w,h }, anim_speed);
		}
		i++;
		item = item->next;
	}

	LOG("%u animations loaded", i);

	return ret;
}

void j1Bat::MovementControl(float dt) {
	if (position.x > App->player->position.x)
	{
		velocity.x = -speed;
		position.x += velocity.x * dt;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		velocity.x = speed;
		position.x += velocity.x * dt;
		flip = SDL_FLIP_NONE;
	}
	if (position.y > App->player->position.y && (state != DEATH_BAT))
	{
		velocity.y = speed;
		position.y -= velocity.y * dt;
	}
	else if(state != DEATH_BAT){
		velocity.y = speed;
		position.y += velocity.y * dt;
	}
}

bool j1Bat::Save(pugi::xml_node& data) const {

	pugi::xml_node p_position = data.append_child("position");

	p_position.append_attribute("x") = position.x;
	p_position.append_attribute("y") = position.y;
	return true;
}

bool j1Bat::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}



void j1Bat::CalculatePath()
{
	iPoint origin = App->map->WorldToMap(App->player->position.x, App->player->position.y);

	iPoint p = App->render->ScreenToWorld(position.x, position.y);
	p = App->map->WorldToMap(position.x, position.y);
	if (App->player->position.x - position.x <= 160 && position.x - App->player->position.x >= -160) {
		App->pathfinding->CreatePath(origin, p);
		if (set_path == true) {
			Path2Move();
		}
	}
}

void j1Bat::BlitPath()
{
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
}

void j1Bat::Path2Move()
{
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	iPoint pos = App->map->MapToWorld(path->At(1)->x, path->At(1)->y);

	if (pos.x < position.x) {
		can_go_left = true;
	}
	if (pos.x > position.x) {
		can_go_right = true;
	}
	if (pos.x >= position.x - 5 && pos.x <= position.x + 5) {
		can_go_down = true;
	}
	else
	{
		can_go_up = true;
	}
}