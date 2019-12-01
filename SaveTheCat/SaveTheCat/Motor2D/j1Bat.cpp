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

	//set initial attributes of the bat
	speed = config.child("bat").child("speed").attribute("value").as_float();
	gravity = 20;//config.child("bat").child("gravity").attribute("value").as_float();
	deathFX = "sounds/death.wav";

	initial_x_position = 400;//config.child("bat").child("position").attribute("x").as_int();
	initial_y_position = 600;//config.child("bat").child("position").attribute("y").as_int();

	collider = App->collision->AddCollider(current_animation->GetCurrentFrame(), COLLIDER_ENEMY, (j1Module*)App->bat); //a collider to start

	return ret;
}

bool j1Bat::Start() {
	//load character sprites
	bat_tex = App->tex->Load("sprites/characters/spritesheet_bat.png");
	position.x = initial_x_position;
	position.y = initial_y_position;

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
				//velocity.y = speed;
			}

			if (can_go_down == true)
			{
				state = FLY_DOWN;
				flip == SDL_FLIP_NONE;
				//velocity.y = -speed;
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
				//velocity.y = speed;
			}

			if (can_go_down == true)
			{
				state = FLY_DOWN;
				flip == SDL_FLIP_HORIZONTAL;
				//velocity.y = -speed;
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

			if (current_animation->Finished())
			{
				state = FLY;
			}
			velocity.y -= gravity;
		}


		//MovementControl(); //calculate new position

		collider->SetPos(position.x, position.y);
	}

	return true;
}

bool j1Bat::Update(float dt)
{
	BROFILER_CATEGORY("Update_Player", Profiler::Color::Teal)
		//this->dt = dt;
		switch (state)
		{
		case FLY:
			current_animation = &fly;
			break;

		case FLY_RIGHT:
			current_animation = &fly;
			flip = SDL_FLIP_NONE;
			//velocity.x = speed * dt;
			break;

		case FLY_LEFT:
			current_animation = &fly;
			flip = SDL_FLIP_HORIZONTAL;
			//velocity.x = -speed * dt;
			break;


		case FLY_DOWN:
			current_animation = &fly;
			//velocity.x = speed * dt;
			break;

		case FLY_UP:
			current_animation = &fly;
			//velocity.y = jumpImpulse * dt;	
			break;

		case DEATH_BAT:
			current_animation = &death_bat;
			if (waitTime(30))
			{
				LOG("Wait done");
				deathSound = false;
				App->bat->CleanUp();
			}

			break;
		default:
			LOG("No state found");
			break;
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

			if ((position.x < c2->rect.x + COLLIDER_PREDICTION) /*&& (state == FALL)*/)
			{
				if (position.y + current_animation->GetCurrentFrame().h < c2->rect.y + COLLIDER_PREDICTION) {
					position.y = c2->rect.y - App->bat->collider->rect.h;
					state = FLY;
					//fall.Reset();
				}
				can_go_right = false;
			}
			if ((position.x > c2->rect.x + c2->rect.w - COLLIDER_PREDICTION) /*&& (state == FALL)*/)
			{
				can_go_left = false;
			}
			if ((position.y < c2->rect.y + COLLIDER_PREDICTION) /*&& (last_state == FALL)*/)
			{

				if (position.y + current_animation->GetCurrentFrame().h < c2->rect.y + COLLIDER_PREDICTION) {
					position.y = c2->rect.y - App->bat->collider->rect.h;
				}
				state = FLY;
				//fall.Reset();
				can_go_right = true;
				can_go_left = true;
			}

			break;
		case COLLIDER_DEATH:
			if (!god) {
				state = DEATH_BAT;
				velocity.x = 0;
				velocity.y = 0;
				if (!deathSound) { deathSound = true; App->audio->PlayFx(2, 0); }
			}
			break;
		case COLLIDER_LEVEL:
			if (!god)
			{

				if (App->scene->current_level == LEVEL_1 && App->scene->want_to_load == 2)
				{
					App->map->CleanUp();
					App->scene->CleanUp();
					//App->scene->current_level = LEVEL_2;
					App->map->Load("Level2.tmx");
					//App->scene->ResetLevel();
					//App->scene->Reset_Camera();
					//if (!winSound) { winSound = true; App->audio->PlayFx(3, 0); }
				}
				if (App->scene->current_level == LEVEL_2 && App->scene->want_to_load == 1)
				{
					App->map->CleanUp();
					App->scene->CleanUp();
					//App->scene->current_level = LEVEL_1;
					App->map->Load("Level1.tmx");
					//App->scene->ResetLevel();
					//App->scene->Reset_Camera();
					//if (!winSound) { winSound = true; App->audio->PlayFx(3, 0); }
				}

				App->scene->ResetLevel();
				App->scene->Reset_Camera();
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
	position.x += velocity.x * dt;
	position.y -= velocity.y * dt;
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

bool j1Bat::waitTime(float sec)
{
	bool ret = false;
	waitTimer++;
	if (waitTimer >= sec) { ret = true; waitTimer = 0; }
	return ret;
}

void j1Bat::calculate_path()
{
	iPoint origin = App->map->WorldToMap(App->player->position.x, App->player->position.y);

	iPoint p = App->render->ScreenToWorld(position.x, position.y);
	p = App->map->WorldToMap(position.x, position.y);
	if (App->player->position.x - position.x <= 160 && position.x - App->player->position.x >= -160) {
		App->pathfinding->CreatePath(origin, p);
		if (set_path == true) {
			check_path_toMove();
		}
	}
}

void j1Bat::blit_path()
{
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}
}

void j1Bat::check_path_toMove()
{
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	iPoint pos = App->map->MapToWorld(path->At(1)->x, path->At(1)->y);

	if (pos.x < position.x) {
		state = FLY_LEFT;
	}
	if (pos.x > position.x) {
		state = FLY_RIGHT;
	}
	if (pos.x >= position.x - 5 && pos.x <= position.x + 5) {
		state = FLY_DOWN;
	}
}