
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
	const int idleRightCollider = 5;//Collider num for the idle animation
	SDL_Rect idleRightHitbox[idleRightCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleRightCollType[idleRightCollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	j1Module* idleRightCallBack[idleRightCollider] = { { this },{ this },{ this },{ this },{ this } };
	idleRight.PushBack1({ 24, 6, 67, 101 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 153, 7, 67, 101 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 281, 8, 67, 100 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 409, 8, 67, 100 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 537, 8, 67, 99 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 665, 8, 67, 100 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 793, 9, 67, 99 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 921, 8, 67, 101 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 25, 135, 67, 101 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.PushBack1({ 153, 135, 67, 102 }, { 32,2 }, idleRightCollider, idleRightHitbox, idleRightCollType, idleRightCallBack);
	idleRight.speed = 1.0f;

	const int idleLeftCollider = 5;//Collider num for the idle animation
	SDL_Rect idleLeftHitbox[idleLeftCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 },{ 9,4,51,54 },{ 1,3,45,33 } };
	COLLIDER_TYPE idleLeftCollType[idleLeftCollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	j1Module* idleLeftCallBack[idleLeftCollider] = { { this },{ this },{ this },{ this },{ this } };
	idleLeft.PushBack1({ 290, 438, 72, 85 }, { 32,2 }, idleLeftCollider, idleLeftHitbox, idleLeftCollType, idleLeftCallBack);
	idleLeft.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleLeftCollider, idleLeftHitbox, idleLeftCollType, idleLeftCallBack);
	idleLeft.PushBack1({ 436, 436, 72, 87 }, { 32,2 }, idleLeftCollider, idleLeftHitbox, idleLeftCollType, idleLeftCallBack);
	idleLeft.PushBack1({ 363, 437, 72, 86 }, { 32,2 }, idleLeftCollider, idleLeftHitbox, idleLeftCollType, idleLeftCallBack);
	idleLeft.speed = 1.0f;

	//Run
	const int walkRightcollider = 5;//Collider num for the idle animation
	SDL_Rect walkRighthitbox[walkRightcollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE walkRightCollType[walkRightcollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	j1Module* walkRightCallback[walkRightcollider] = { { this },{ this },{ this },{ this }};
	walkRight.PushBack1({ 481,262, 66, 102 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 611, 263, 67, 99 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 740, 264, 67, 92 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 866, 263, 67, 98 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 33,390, 66, 102 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 162, 391, 67, 100 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 292, 391, 66, 95 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.PushBack1({ 148, 391, 67, 100 }, { 32,2 }, walkRightcollider, walkRighthitbox, walkRightCollType, walkRightCallback);
	walkRight.speed = 0.5f;

	const int walkLeftcollider = 5;//Collider num for the idle animation
	SDL_Rect walkLefthitbox[walkLeftcollider] = { { 0, 3, 45, 33 },{ 8, 4, 51, 54 },{ 15, 3, 37, 71 },{ 13, 71, 31, 21 },{ 2, 37, 35, 41 } };
	COLLIDER_TYPE walkLeftCollType[walkLeftcollider] = { { COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER },{ COLLIDER_PLAYER } };
	j1Module* walkLeftCallback[walkLeftcollider] = { { this },{ this },{ this },{ this } };
	walkLeft.PushBack1({ 652,437, 73, 86 }, { 32,2 }, walkLeftcollider, walkLefthitbox, walkLeftCollType, walkLeftCallback);
	walkLeft.PushBack1({ 726, 434, 63, 89 }, { 32,2 }, walkLeftcollider, walkLefthitbox, walkLeftCollType, walkLeftCallback);
	walkLeft.PushBack1({ 790, 433, 60, 90 }, { 32,2 }, walkLeftcollider, walkLefthitbox, walkLeftCollType, walkLeftCallback);
	walkLeft.PushBack1({ 851, 432, 63, 91 }, { 32,2 }, walkLeftcollider, walkLefthitbox, walkLeftCollType, walkLeftCallback);
	walkLeft.speed = 0.5f;


	//Jump
	const int jumpRightcollider = 5;//Collider num for the idle animation
	SDL_Rect jumpRighthitbox[jumpRightcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpRightCollType[jumpRightcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	j1Module* jumpRightCallback[jumpRightcollider] = { {this},{this},{this},{this}};

	jumpRight.PushBack1({ 410, 135, 66, 102 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 537, 136, 67, 101 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 665, 141, 67, 92 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 793, 141, 67, 95 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 922, 142, 67, 95 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 16, 262, 66, 94 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 144, 262, 65, 92 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.PushBack1({ 271, 262, 67, 95 }, { 32, 25 }, jumpRightcollider, jumpRighthitbox, jumpRightCollType, jumpRightCallback);
	jumpRight.speed = 0.5f;
	jumpRight.loop = false;

	const int jumpLeftcollider = 5;//Collider num for the idle animation
	SDL_Rect jumpLefthitbox[jumpLeftcollider] = { { 5, 53, 37, 19 },{ 2, 4, 51, 54 },{ 9, 55, 37, 39 },{ 20, 86, 31, 21 },{ 8, 68, 31, 27 } };
	COLLIDER_TYPE jumpLeftCollType[jumpLeftcollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	j1Module* jumpLeftCallback[jumpLeftcollider] = { {this},{this},{this},{this} };

	jumpLeft.PushBack1({ 1756, 1, 47, 110 }, { 32, 25 }, jumpLeftcollider, jumpLefthitbox, jumpLeftCollType, jumpLeftCallback);
	jumpLeft.PushBack1({ 1804, 27, 50, 84 }, { 32, 25 }, jumpLeftcollider, jumpLefthitbox, jumpLeftCollType, jumpLeftCallback);
	jumpLeft.PushBack1({ 1855, 36, 52, 75 }, { 32, 25 }, jumpLeftcollider, jumpLefthitbox, jumpLeftCollType, jumpLeftCallback);
	jumpLeft.PushBack1({ 1908, 46, 57, 65 }, { 32, 25 }, jumpLeftcollider, jumpLefthitbox, jumpLeftCollType, jumpLeftCallback);
	jumpLeft.speed = 0.5f;
	jumpLeft.loop = false;


	//die animation
	const int dieRightCollider = 5;//Collider num for the idle animation
	SDL_Rect dieRightHitbox[dieRightCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dieRightCollType[dieRightCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dieRightCallBack[dieRightCollider] = { {this},{this},{this},{this}};

	dieRight.PushBack1({ 2,784,71,87 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 142, 772, 79, 100 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 277, 774, 86, 98 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 413, 797, 86, 75 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 542,792,93,80 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 671, 797, 90, 75 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 797,800,88,72 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 922, 801, 87, 71 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 20,930,87,70 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.PushBack1({ 152, 930, 87, 70 }, { 32, 2 }, dieRightCollider, dieRightHitbox, dieRightCollType, dieRightCallBack);
	dieRight.speed = 0.5f;
	dieRight.loop = false;

	const int dieLeftCollider = 5;//Collider num for the idle animation
	SDL_Rect dieLeftHitbox[dieLeftCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE dieLeftCollType[dieLeftCollider] = { {COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE},{COLLIDER_NONE} };
	j1Module* dieLeftCallBack[dieLeftCollider] = { {this},{this},{this},{this} };

	dieLeft.PushBack1({ 1307,465,72,80 }, { 32, 2 }, dieLeftCollider, dieLeftHitbox, dieLeftCollType, dieLeftCallBack);
	dieLeft.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, dieLeftCollider, dieLeftHitbox, dieLeftCollType, dieLeftCallBack);
	dieLeft.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, dieLeftCollider, dieLeftHitbox, dieLeftCollType, dieLeftCallBack);
	dieLeft.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, dieLeftCollider, dieLeftHitbox, dieLeftCollType, dieLeftCallBack);
	dieLeft.speed = 0.5f;
	dieLeft.loop = false;

	//falling animation
	const int fallingRightCollider = 5;//Collider num for the idle animation
	SDL_Rect fallingRightHitbox[fallingRightCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE fallingRightCollType[fallingRightCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	j1Module* fallingRightCallBack[fallingRightCollider] = { {this},{this},{this},{this} };

	fallingRight.PushBack1({ 17,647,65,95 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 145, 645, 66, 103 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 274, 644, 68, 101 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 401, 645, 64, 100 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 529,646,65,98}, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 657, 645,66,100}, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 786, 644, 65, 101 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.PushBack1({ 913, 645, 66, 100 }, { 32, 2 }, fallingRightCollider, fallingRightHitbox, fallingRightCollType, fallingRightCallBack);
	fallingRight.speed = 0.5f;
	fallingRight.loop = false;

	const int fallingLeftCollider = 5;//Collider num for the idle animation
	SDL_Rect fallingLeftHitbox[fallingLeftCollider] = { { 14, 71, 31, 21 },{ 3, 37, 35, 41 },{ 16, 3, 37, 71 }, {9,4,51,54 },{1,3,45,33} };
	COLLIDER_TYPE fallingLeftCollType[fallingLeftCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	j1Module* fallingLeftCallBack[fallingLeftCollider] = { {this},{this},{this},{this} };

	fallingLeft.PushBack1({ 1307,465,72,80 }, { 32, 2 }, fallingLeftCollider, fallingLeftHitbox, fallingLeftCollType, fallingLeftCallBack);
	fallingLeft.PushBack1({ 1385, 458, 79, 87 }, { 32, 2 }, fallingLeftCollider, fallingLeftHitbox, fallingLeftCollType, fallingLeftCallBack);
	fallingLeft.PushBack1({ 1465, 458, 76, 87 }, { 32, 2 }, fallingLeftCollider, fallingLeftHitbox, fallingLeftCollType, fallingLeftCallBack);
	fallingLeft.PushBack1({ 1542, 462, 72, 83 }, { 32, 2 }, fallingLeftCollider, fallingLeftHitbox, fallingLeftCollType, fallingLeftCallBack);
	fallingLeft.speed = 0.5f;
	fallingLeft.loop = false;

}

jPlayer::~jPlayer()
{}

// Load assets
bool jPlayer::Start()
{
	LOG("Loading player...");
	bool ret = true;

	graphicsRight = App->tex->Load("textures/PlayerRight.png");
	graphicsLeft = App->tex->Load("textures/PlayerLeft.png");
	//shadow = App->tex->Load("");
	position.x = 300;
	position.y = 500;

	newState = stIdle;
	//Sound Effects	
	//App->audio->LoadFx("path Assets/...");
	//App->audio->LoadFx("path");

	//Start functions to reset player
	//ResetPlayer();
	return ret;
}

bool jPlayer::CleanUp()
{
	LOG("Unloading Player textures");

	App->tex->UnLoad(graphicsRight);
	App->tex->UnLoad(graphicsLeft);

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

bool jPlayer::Update(float dt)
{
//	LOG("Player update...");
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
						position.x += speedX;
						facingRight = false;
						if (grounded) newState = stWalk;
						break;
					case INright:
						position.x -= speedX;
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
	}
	else ResetPlayer();
	colliders_and_blit(current_animation);
	return true;
}

void jPlayer::positionlimits() 
{
	
}

void jPlayer::colliders_and_blit(Animation* current_animation) 
{
	PivotX = current_animation->pivot[(int)current_animation->current_frame].x;
	PivotY = current_animation->pivot[(int)current_animation->current_frame].y;

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


	//SDL_Rect shadowrect = { 6,8,71,15 };
	/*if (position.x < App->player->position.x + App->player->PivotX && !RightLimit || (leftLimit && position.y == 220)) 
	{

		App->render->Blit(graphics, position.x - PivotX, position.y - r.h, &r);
	}
	if (position.x > App->player->position.x + App->player->PivotX && (!leftLimit || position.y != 220) || RightLimit) 
	{

		App->render->Blit(graphics, position.x - (r.w - PivotX), position.y - r.h, &r);
	}*/
//	LOG("Render player...");
	App->render->Blit(graphicsRight, position.x - PivotX, position.y - r.h, &r);
	App->render->Blit(graphicsLeft, position.x - PivotX, position.y - r.h, &r);
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