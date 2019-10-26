#include "j1Player.h"
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

j1Player::j1Player():j1Module () {
	name.create("player");

	LoadAnimations();

}

j1Player::~j1Player(){ }

bool j1Player::Awake(pugi::xml_node& config) {

	LOG("Loading Player Data");
	bool ret = true;

	current_animation = &idle;

	folder.create(config.child("folder").child_value());

	//set initial attributes of the player
	speed = config.child("speed").attribute("value").as_int();
	jumpImpulse = config.child("jumpImpulse").attribute("value").as_float();
	gravity = config.child("gravity").attribute("value").as_float();
	jumpFX = "sounds/jump.wav";
	deathFX = "sounds/death.wav";
	winFX = "sounds/win.wav";
	slideFX = "sounds/slide.wav";
	music = "sounds/SuperSong.wav";

	collider = App->collision->AddCollider(current_animation->GetCurrentFrame(), COLLIDER_PLAYER, (j1Module*)App->player); //a collider to start

	return ret;
}

bool j1Player::Start(){
	//load character sprites
	player_tex = App->tex->Load("sprites/characters/spritesheet_cat.png");
	position.x = initial_x_position = App->scene->player_x_position;
	position.y = initial_x_position = App->scene->player_y_position;

	App->audio->LoadFx(jumpFX.GetString());
	App->audio->LoadFx(deathFX.GetString());
	App->audio->LoadFx(winFX.GetString());
	App->audio->LoadFx(slideFX.GetString());
	App->audio->PlayMusic(music.GetString(),0);

	return true;
}

bool j1Player::CleanUp() {
	collider = nullptr;
	player_tex = nullptr;
	return true;
}


bool j1Player::PreUpdate(){
	//get player input
	player_input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	player_input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	player_input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	player_input.S_keyUp = App->input->GetKey(SDL_SCANCODE_S) == KEY_UP;
	player_input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	player_input.pressing_space = App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN;

	lastPosition = position;
	last_state = state;

	/*if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		god = !god;
		if (god)
		{
			state = IDLE;
			velocity.y = 0;
		}
	}*/

	if (!App->pause)
	{
		velocity.x = 0;
		if (state == IDLE)
		{
			collider->SetSize(42, 66);
			can_double_jump = true;

			if ((player_input.pressing_D)/*&&(velocity.y == 0)*/)
			{
				state = RUN_FORWARD;
			}

			if (player_input.pressing_A)
			{
				state = RUN_BACKWARD;
			}


			if (player_input.pressing_S)
			{
				if (flip == SDL_FLIP_NONE)
				{
					state = SLIDE_FORWARD;
					App->audio->PlayFx(4, 0);
				}
				else
				{
					state = SLIDE_BACKWARD;
					App->audio->PlayFx(4, 0);
				}
			}
			
			if (player_input.pressing_space)
			{
				state = JUMP;
				velocity.y = jumpImpulse;	
				App->audio->PlayFx(1, 0);
			}
			
		}
		
		if (state == RUN_FORWARD)
		{
			collider->SetSize(42, 66);
			if (!player_input.pressing_D)
			{
				state = IDLE;
				velocity.x = 0;
			}
			
			if (player_input.pressing_space)
			{
				state = JUMP;
				velocity.y = jumpImpulse;
				App->audio->PlayFx(1, 0);
			}
			
			if (player_input.pressing_S)
			{
				state = SLIDE_FORWARD;
				App->audio->PlayFx(4, 0);
			}

			velocity.x = speed;
		}

		if (state == RUN_BACKWARD)
		{
			collider->SetSize(42, 66);
			if (!player_input.pressing_A)
			{
				state = IDLE;
				velocity.x = 0;
			}
			
			if (player_input.pressing_space)
			{
				state = JUMP;
				velocity.y = jumpImpulse;
				App->audio->PlayFx(1, 0);
			}
			
			if (player_input.pressing_S)
			{
				state = SLIDE_BACKWARD;
				App->audio->PlayFx(4, 0);
			}

			velocity.x = -speed;
		}


		if (state == SLIDE_FORWARD)
		{
			collider->SetSize(45, 55);
			if (!player_input.pressing_S)
			{
				state = RUN_FORWARD;
				velocity.y = JUMP_AFTER_SLIDE;
			}
			//position.x += speed;
			
			velocity.x = speed;
		}

		if (state == SLIDE_BACKWARD)
		{
			collider->SetSize(45, 55);
			if (!player_input.pressing_S)
			{
				state = RUN_BACKWARD;
				velocity.y = JUMP_AFTER_SLIDE;
			}
			//position.x -= speed;
			velocity.x = -speed;
		}

		if (state == JUMP)
		{
			collider->SetSize(42, 66);
			if (player_input.pressing_D) position.x += speed/2;
			if (player_input.pressing_A) position.x -= speed/2;

			if ((player_input.pressing_space)&&(can_double_jump == true)&&(velocity.y <= jumpImpulse/2))
			{ 
				jump.Reset();
				velocity.y = jumpImpulse;
				can_double_jump = false;
			}

			if (current_animation->Finished())
			{
				state = FALL;
				jump.Reset();
			}
			
		}
		if (state == FALL)
		{
			collider->SetSize(42, 66);
			//let the player move while faling
			if ((player_input.pressing_D)&&(can_go_right == true)) position.x += speed /2;
			if ((player_input.pressing_A)&&(can_go_left == true)) position.x -= speed / 2;

			if ((player_input.pressing_space)&&(can_double_jump == true) & (velocity.y <= jumpImpulse / 2))
			{
				jump.Reset();
				state = JUMP;
				velocity.y = jumpImpulse; 
				can_double_jump = false;
				App->audio->PlayFx(1, 0);
			}

			if (current_animation->Finished())
			{
				fall.Reset();
			}
		}

		if ((velocity.y < -10)&&(state == IDLE))
		{
			state = FALL;
		}

		MovementControl(); //calculate new position
		
		collider->SetPos(position.x, position.y);
	}

	if (god)
	{
		if (player_input.pressing_W) position.y -= speed;
		if (player_input.pressing_S) position.y += speed;
	}
	return true;
}

bool j1Player::Update(float dt){

	switch (state)
	{
	case IDLE:
		current_animation = &idle;
		fall.Reset();
		jump.Reset();
		slide.Reset();
		break;

	case RUN_FORWARD:
		current_animation = &run;
		flip = SDL_FLIP_NONE;
		break;

	case RUN_BACKWARD:
		current_animation = &run;
		flip = SDL_FLIP_HORIZONTAL;
		break;


	case SLIDE_FORWARD:
		current_animation = &slide;
		flip = SDL_FLIP_NONE;
		break;

	case SLIDE_BACKWARD:
		current_animation = &slide;
		flip = SDL_FLIP_HORIZONTAL;
		break;

	case JUMP:
		current_animation = &jump;
		if (velocity.y <= 0)
		{
			state = FALL;
			jump.Reset();
		}
		if ((last_state = RUN_FORWARD)||(last_state == RUN_BACKWARD))
		{
			velocity.x /= 2;			
		}
		break;
	case FALL:
		current_animation = &fall;
		break;
	case DEATH:
		current_animation = &death;
		fall.Reset();
		jump.Reset();
		slide.Reset();
		
		break;
	default:
		LOG("No state found");
		break;
	}

	death_reset = SDL_GetTicks();
	
	return true;
}

bool j1Player::PostUpdate() {

	App->render->Blit(player_tex, position.x, position.y, &current_animation->GetCurrentFrame(), flip);

	return true;	
}

void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (!god)
	{
		switch (c2->type)
		{
		case COLLIDER_WALL:
			position = lastPosition;
			velocity.x = velocity.y = 0;
			if ((position.x < c2->rect.x + COLLIDER_MARGIN) && (state == FALL))
			{
				can_go_right = false;
			}
			if ((position.x > c2->rect.x + c2->rect.w - COLLIDER_MARGIN) && (state == FALL))
			{
				can_go_left = false;
			}
			if ((position.y < c2->rect.y + COLLIDER_MARGIN) && (last_state == FALL))
			{
				state = IDLE;
				fall.Reset();
				can_go_right = true;
				can_go_left = true;
			}

			break;
		case COLLIDER_DEATH:
			if (!god) {
				state = IDLE;
				
				velocity.x = 0;
				velocity.y = 0;
				App->audio->PlayFx(2, 0);
				position.x = initial_x_position;//App->map->data.player_initial_x;
				position.y = initial_y_position;//App->map->data.player_initial_y;
				App->scene->Reset_Camera();
				App->scene->ResetLevel();
				
				
			}
			break;
		case COLLIDER_LEVEL:
			if (!god) {
				if (App->scene->current_level == LEVEL_1)
				{
					App->map->CleanUp();
					App->map->Load("Level2.tmx");
					App->scene->ResetLevel();
					App->scene->Reset_Camera();
					
				}
				if (App->scene->current_level == LEVEL_2)
				{
					App->map->CleanUp();
					App->map->Load("Level1.tmx");
					App->scene->ResetLevel();
					App->scene->Reset_Camera();
				}
			}
			break;
		default:
			break;
		}
	}
}

bool j1Player::LoadAnimations() {
	pugi::xml_parse_result result = animation_doc.load_file("sprites/characters/animations.xml");
	bool ret = true;
	uint i = 0u;
	uint j = 0;
	
	if (result == NULL)
	{
		LOG("Could not load animations xml file %s. pugi error: %s", "animations.xml", result.description());
		ret = false;
	}

	animations.add(&idle);
	animations.add(&run);
	animations.add(&slide);
	animations.add(&jump);
	animations.add(&fall);
	animations.add(&death);

	pugi::xml_node animation = animation_doc.child("animations").child("animation");
	pugi::xml_node frame;
	p2List_item<Animation*>* item = animations.start;
	int x, y, w, h;
	float anim_speed = 1;

	LOG("Loading animations ---------");

	for (animation ; animation; animation = animation.next_sibling("animation"))
	{
		item->data->loop = animation.attribute("loop").as_bool();

		for (frame = animation.child("data").child("frame"); frame; frame = frame.next_sibling("frame"))
		{
			x = frame.attribute("x").as_int();
			y = frame.attribute("y").as_int();
			w = frame.attribute("w").as_int();
			h = frame.attribute("h").as_int();
			anim_speed = frame.attribute("speed").as_float();

			item->data->PushBack({x,y,w,h}, anim_speed);
		}
		i++;
		item = item->next;
	}

	LOG("%u animations loaded", i);

	return ret;
}

void j1Player::MovementControl() {
	position.x += velocity.x;
	position.y -= velocity.y;
	if (!god) velocity.y -= gravity;
	
}

bool j1Player::Save(pugi::xml_node& data) const {

	pugi::xml_node p_position = data.append_child("position");

	p_position.append_attribute("x") = position.x;
	p_position.append_attribute("y") = position.y;
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	return true;
}