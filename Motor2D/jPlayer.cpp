
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "jPlayer.h"
#include "j1Audio.h"
#include "jCollisions.h"
#include "p2Log.h"
//#include "ModuleUI.h"
#include "p2Qeue.h"
//#include"ModuleFadeToBlack.h"


jPlayer :: jPlayer()
{
/*	//Idle
	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* idleCallBack[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
	idle.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.speed = 0.1f;

	//Right
	const int fwdcollider = 5;//Collider num for the idle animation
	SDL_Rect fwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE fwdCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* fwdCallback[idleCollider] = { { this },{ this },{ this },{ this }};
	right.PushBack1({ 652,437, 73, 86 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	right.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	right.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	right.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, fwdcollider, fwdhitbox, fwdCollType, fwdCallback);
	right.speed = 0.15f;


	//Left
	const int bwdcollider = 5;//Collider num for the idle animation
	SDL_Rect bwdhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE bcwCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* bwdCallback[idleCollider] = { { this },{ this },{ this },{ this }};
	left.PushBack1({ 652,437, 73, 86 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	left.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	left.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	left.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, bwdcollider, bwdhitbox, bcwCollType, bwdCallback);
	left.speed = 0.2f;


	//Jump Left
	const int jumpcollider = 5;//Collider num for the idle animation
	SDL_Rect jumphitbox[jumpcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpCollType[jumpcollider] = { {COLLIDER_ENEMY},{COLLIDER_NONE},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	j1Module* jumpCallback[jumpcollider] = { {this},{this},{this},{this}};

	jumpLeft.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.speed = 0.21f;
	jumpLeft.loop = false;

	//Jump Right
	const int jumpcollider = 5;//Collider num for the idle animation
	SDL_Rect jumphitbox[jumpcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpCollType[jumpcollider] = { {COLLIDER_ENEMY},{COLLIDER_NONE},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	j1Module* jumpCallback[jumpcollider] = { {this},{this},{this},{this}};

	jumpRight.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpRight.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpRight.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpRight.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpRight.speed = 0.21f;
	jumpRight.loop = false;


	//die animation
	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this}};

	die.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	die.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	die.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	die.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	die.speed = 0.1f;
	die.loop = false;
*/	
}

jPlayer::~jPlayer()
{}

// Load assets
bool jPlayer::Start()
{
	bool ret = true;

	graphics = App->tex->Load("");
	shadow = App->tex->Load("");
	//position.x = 395;
	//position.y = 220;

	//Sound Effects	
	App->audio->LoadFx("path Assets/...");
	App->audio->LoadFx("path");

	//Start functions to reset player
	ResetPlayer();
	return ret;
}

bool jPlayer::CleanUp()
{
	LOG("Unloading Player textures");

	App->tex->UnLoad(graphics);

	for (int i = 0; i < MAX_COLLIDERS; i++)
	{
		if (colliders[i] != nullptr) {
			colliders[i]->to_delete = true;
			colliders[i] = nullptr;
		}
	}
	
//	App->audio->UnloadChunk(win_sound);
//	App->audio->UnloadChunk(death_sound);
	return true;
}

bool jPlayer::Update()
{
	if (GodMode)//deletes all the collision boxes if in god mode
	{
		for (int i = 0; i < MAX_COLLIDERS; i++)
		{
			if (colliders[i] != nullptr)
				colliders[i]->to_delete = true;
		}
	}
	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr) 
		{
			colliders[i]->to_delete = true;
			colliders[i] = nullptr;
		}
	}

	Animation* current_animation;
	p2Qeue<playerInputs> inputs;
	playerInputs last_input;

	positionlimits();
	debugcommands();

	if (death == false) 
	{
//		while (external_input(inputs))
//		{
			//internal_input(inputs);

			switch (newState)
			{
				case stIdle:
					current_animation = &idle;
					break;
				/*case stWalkRight:
					current_animation = &right;
					position.x += speedX;
					facingRight = true;
					break;
				case stWalkLeft:
					current_animation = &left;
					position.x -= speedX;
					facingRight = false;
					break;
				case stJump:
					onAir = true;
					break;
				case stJumpRight:
					onAir = true;
					current_animation = &jumpRight;
					break;
				case stJumpLeft:
					onAir = true;
					current_animation = &jumpLeft;
					break;*/
				case stMoving:
					while (external_input(inputs))
					{
						while (inputs.Pop(last_input))
						{
							switch (last_input)
							{
							case INleft:
								current_animation = &left;
								break;

							case INright:

								break;

							case INjump:

								break;

							case INleftUP:

								break;
							case INrightUP:

								break;
							}
						}
					}
					break;
				case stDie:
					current_animation = &die;
					break;				
			}
			currentState = newState;

			colliders_and_blit(current_animation);				
//		}
	}
	return true;
}

void jPlayer::positionlimits() 
{
	
}

void jPlayer::colliders_and_blit(Animation* current_animation) 
{
	PivotX = current_animation->pivot[(int)current_animation->current_frame].x;
	PivotY = current_animation->pivot[(int)current_animation->current_frame].y;
	//dmg = current_animation->damage[(int)current_animation->current_frame];

	for (int i = 0; i < MAX_COLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colliders[i] != nullptr)
			colliders[i]->to_delete = true;
	}

	SDL_Rect r;
	int max_hitboxes = current_animation->maxcolliders[(int)current_animation->current_frame];

	for (int i = 0; i < max_hitboxes; i++)
	{
		r = current_animation->hitbox[i];
		if (!GodMode) 
		{
			if (position.x > App->player->position.x)
				colliders[i] = App->collisions->AddCollider({ position.x - (r.w - PivotX) - r.x , position.y - r.h + PivotY - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);

			if (position.x < App->player->position.x)
				colliders[i] = App->collisions->AddCollider({ position.x - PivotX + r.x , position.y + PivotY - r.h - r.y,r.w,r.h }, current_animation->type[i], current_animation->callback[i]);
		}
	}
	r = current_animation->GetCurrentFrame();


	SDL_Rect shadowrect = { 6,8,71,15 };
	if (position.x < App->player->position.x + App->player->PivotX && !RightLimit || (leftLimit && position.y == 220)) 
	{

		App->render->Blit(graphics, position.x - PivotX, position.y - r.h, &r);
	}
	if (position.x > App->player->position.x + App->player->PivotX && (!leftLimit || position.y != 220) || RightLimit) 
	{

		App->render->Blit(graphics, position.x - (r.w - PivotX), position.y - r.h, &r);
	}
}

void jPlayer::OnCollision(Collider* c1, Collider* c2) 
{
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY)
	{
		newState = stDie;

		if (currentState == stIdle) 
		{
			if (position.x > App->player->position.x)
				position.x += 1;
			if (position.x < App->player->position.x)
				position.x -= 1;
		}
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_GROUND)
	{
		grounded = true;
		if (currentState == stIdle)
		{
			if (position.x > App->player->position.x)
				position.x += 1;
			if (position.x < App->player->position.x)
				position.x -= 1;
		}
	}

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL)
	{
		if (currentState == stIdle)
		{
			if (position.x > App->player->position.x)
				position.x += 1;
			if (position.x < App->player->position.x)
				position.x -= 1;
		}
	}
}

bool jPlayer::external_input(p2Qeue<playerInputs>& inputs)
{
	bool ret = false;
	//Key up	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP) 
		inputs.Push(INleftUP); ret = true;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP) 
		inputs.Push(INrightUP); ret = true;

	//Key down
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) 
	{
		/*if (currentState != stIdle)
		{
			if (facingRight) newState = stJumpRight;
			else newState = stJumpRight;
		}*/
		if(grounded)
			inputs.Push(INjump); ret = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) 
	{
		//newState = stWalkLeft;
		inputs.Push(INleft); 
		ret = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) 
	{
		//newState = stWalkRight;
		inputs.Push(INright);
		ret = true;
	}
	return ret;
}

/*
void jPlayer::internal_input(p2Qeue<playerInputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(INjumpEND);
			jump_timer = 0;
			position.y = 220;
		}
	}
}*/

void jPlayer::ResetPlayer()
{
	position.x = 410;
	position.y = 220;
	newState = stIdle;
}

/*playerStates jPlayer::process_fsm(p2Qeue<playerInputs>& inputs)
{
	playerStates state = stIdle;
	playerInputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (last_input)
		{
			case INleft:

			break;

			case INright:

				break;

			case INjump:

				break;	

			case INleftUP:

				break;
			case INrightUP:

				break;
		}
	}
	return state;
}*/


void jPlayer::debugcommands() 
{
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		newState = stDie;
	}

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		if (!GodMode) 
		{
			for (int i = 0; i < MAX_COLLIDERS; i++)
			{
				if (colliders[i] != nullptr)
					colliders[i]->to_delete = true;
			}
			GodMode = true;
		}
		else GodMode = false;
	}
}

void jPlayer::jump_neutral_logic() {

	if (SDL_GetTicks() - jump_timer <= JUMP_TIME / 4.5) 
	{
		position.y -= 8;
	}

	if (SDL_GetTicks() - jump_timer > JUMP_TIME / 4.5 && SDL_GetTicks() - jump_timer < JUMP_TIME / 1.28) 
	{
		if (SDL_GetTicks() - jump_timer < JUMP_TIME / 2) 
		{
			position.y -= 4;
		}

		if (SDL_GetTicks() - jump_timer > JUMP_TIME / 2) 
		{
			position.y += 4;
		}
	}

	if (SDL_GetTicks() - jump_timer >= JUMP_TIME / 1.28) 
	{
		position.y += 10;
	}
}