
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
	//Idle
	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* idleCallBack[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
	idleRight.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleRight.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleRight.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleRight.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleRight.speed = 0.1f;

	const int idleCollider = 5;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* idleCallBack[idleCollider] = { { this },{ this },{ this },{ this },{ this } };
	idleLeft.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleLeft.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleLeft.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleLeft.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idleLeft.speed = 0.1f;

	//Run
	const int runcollider = 5;//Collider num for the idle animation
	SDL_Rect runhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE runCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* runCallback[idleCollider] = { { this },{ this },{ this },{ this }};
	walkRight.PushBack1({ 652,437, 73, 86 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkRight.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkRight.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkRight.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkRight.speed = 0.15f;

	const int runcollider = 5;//Collider num for the idle animation
	SDL_Rect runhitbox[idleCollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE runCollType[idleCollider] = { { COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY },{ COLLIDER_ENEMY } };
	j1Module* runCallback[idleCollider] = { { this },{ this },{ this },{ this } };
	walkLeft.PushBack1({ 652,437, 73, 86 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkLeft.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkLeft.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkLeft.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, runcollider, runhitbox, runCollType, runCallback);
	walkLeft.speed = 0.15f;


	//Jump
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

	const int jumpcollider = 5;//Collider num for the idle animation
	SDL_Rect jumphitbox[jumpcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpCollType[jumpcollider] = { {COLLIDER_ENEMY},{COLLIDER_NONE},{COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	j1Module* jumpCallback[jumpcollider] = { {this},{this},{this},{this} };

	jumpLeft.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpcollider, jumphitbox, jumpCollType, jumpCallback);
	jumpLeft.speed = 0.21f;
	jumpLeft.loop = false;


	//die animation
	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this}};

	dieRight.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieRight.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieRight.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieRight.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieRight.speed = 0.1f;
	dieRight.loop = false;

	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this} };

	dieLeft.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieLeft.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieLeft.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieLeft.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	dieLeft.speed = 0.1f;
	dieLeft.loop = false;

	//falling animation
	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this} };

	fallingRight.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingRight.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingRight.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingRight.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingRight.speed = 0.1f;
	fallingRight.loop = false;

	const int dmgCollider = 5;//Collider num for the idle animation
	SDL_Rect dmgHitbox[dmgCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dmgCollType[dmgCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dmgCallBack[dmgCollider] = { {this},{this},{this},{this} };

	fallingLeft.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingLeft.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingLeft.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingLeft.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dmgCollider, dmgHitbox, dmgCollType, dmgCallBack);
	fallingLeft.speed = 0.1f;
	fallingLeft.loop = false;

}

jPlayer::~jPlayer()
{}

// Load assets
bool jPlayer::Start()
{
	bool ret = true;

	graphics = App->tex->Load("Game/textures/PlayerRight.png");
	graphics = App->tex->Load("Game/textures/PlayerLeft.png");
	//shadow = App->tex->Load("");
	//position.x = 395;
	//position.y = 220;

	//Sound Effects	
	//App->audio->LoadFx("path Assets/...");
	//App->audio->LoadFx("path");

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
	Animation* current_animation=&idleRight;
	playerInputs last_input;

	positionlimits();
	debugcommands();

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

	if (!death)
	{
		external_input(inputs);
		internal_input(inputs);

		while (inputs.Pop(last_input) || newState != currentState)
		{
			while (inputs.Pop(last_input))
			{
				switch (last_input)
				{
					case INleft:
						position.x -= speedX;
						facingRight = false;
						if (grounded) newState = stWalk;
						break;
					case INright:
						position.x += speedX;
						facingRight = true;
						if (grounded) newState = stWalk;
						break;
					case INjump:
						newState = stJump;
						grounded = false;
						doJump();
						break;
					case INjumpEND:
						newState = stFalling;
						break;
					case INdie:
						newState = stDie;
						break;
					case INfalling:
						newState = stFalling;
						break;
				}
			}
		}

		switch (newState)
		{
			case stIdle:
				if (facingRight) current_animation = &idleRight;
				else current_animation = &idleLeft;
				break;
			case stWalk:
				if (facingRight) current_animation = &walkRight;
				else current_animation = &walkLeft;
				break;
			case stJump:
				if (facingRight) current_animation = &jumpRight;
				else current_animation = &jumpLeft;
				break;
			case stFalling:
				if (facingRight) current_animation = &fallingRight;
				else current_animation = &fallingLeft;
				if (!grounded) position.y -= FALL_VELOCITY;
				break;
			case stDie:
				if (facingRight) current_animation = &dieRight;
				else current_animation = &dieLeft;
				death = true;
				break;
		}
		currentState = newState;
		colliders_and_blit(current_animation);
	}
	else ResetPlayer();
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
		inputs.Push(INdie);
	}
	else
	{
		if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_GROUND)
		{
			grounded = true;
		}

		if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL)
		{

		}
	}
}

bool jPlayer::external_input(p2Qeue<playerInputs>& inputs)
{
	bool ret = false;
	if (!death)
	{
		//Key up	
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			inputs.Push(INleftUP); ret = true;

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			inputs.Push(INrightUP); ret = true;

		//Key down
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			if (grounded)
			{
				inputs.Push(INjump);
				jumping = true;
				ret = true;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			inputs.Push(INleft);
			ret = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			inputs.Push(INright);
			ret = true;
		}
	}
	return ret;
}


bool jPlayer::internal_input(p2Qeue<playerInputs>& inputs)
{
	bool ret = false;
	if (jumping)
	{
		inputs.Push(INjump);
		!ret;
	}	
	if (!grounded && !jumping)
	{
		inputs.Push(INfalling);
		!ret;
	}
	return ret;
}

void jPlayer::ResetPlayer()
{
	position.x = 0;
	position.y = 0;
	newState = stIdle;
	death = false;
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

void jPlayer::doJump() 
{
	if (jumpHeight < MAXJUMPHEIGHT)
	{
		position.y += JUMP_VELOCITY;
	}
	else inputs.Push(INfalling); jumping = false;
}