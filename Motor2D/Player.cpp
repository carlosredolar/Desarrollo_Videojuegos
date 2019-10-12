/*
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "Collision.h"
#include "SDL\include\SDL.h"
#include "jAnimation.h"
#include "p2Log.h"
#include "p2Qeue.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player() {
}

// Load assets
bool Player::Start()
{
	LOG("Loading player textures");
	App->particles->cont = 0;
	bool ret = true;
	colcreated = true;
	Activesm1 = true;

	graphics = App->textures->Load("Source/Sprites/Character_Sprites/Andy_Bogard/andy.png");
	Kick = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Kick.wav");
	Punch = App->audio->LoadFX("Source/Sound/FX/Voice/Attacks/Punch.wav");

	position.x = 200;
	position.y = 220;
	initialPos = position.y;

	playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
	playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playercrouchkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playercrouchpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpnkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpnpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerdash = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpfkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpbkick = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpfpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerjumpbpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	playerwindmill = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
	//winanimation.Reset();

	return ret;

}

bool Player::CleanUp()
{
	//App->input->inputs.Push(IN_WIN_FINISH);

	SDL_DestroyTexture(graphics);
	App->player2->Disable();
	App->audio->Disable();
	// DANGER NEXT LINE IF USED CREATES EXCEPTION AND BREAKS GAME
	//App->audio->CleanUp();
	LOG("Unloading Andy From Scene");

	return true;
}

// Update: draw background
bool Player::Update(float d1)
{

	Animation* current_animation = &idle;
	uint timersm1 = SDL_GetTicks();
	playerStates current_state = ST_UNKNOWN;
	playerStates state = process_fsm(App->input->inputs);

	App->render->Blit(graphics, position.x - 5, 210, &shadow, 1.0f, true);

	int speed = 2;

	//god mode
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {

		if (godmode == false)
		{

			playercol->to_delete = true;


			godmode = true;
		}
		else if (godmode == true)
		{
			playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);

			godmode = false;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {

		App->enemy2->life = 0; //Kill Enemy

	}

	if (state != current_state)
	{

		switch (state)
		{

		case ST_IDLE:
			//////////
			current_animation = &idle;

			forward.Reset();
			backward.Reset();
			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();


			kick.Reset();
			kickn.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchn.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();
			sm2.Reset();
			sm3.Reset();
			sm4.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_WALK_FORWARD:

			if (position.x > App->enemy2->position.x)
			{
				current_animation = &backward;
				forward.Reset();
			}
			else
			{
				current_animation = &forward;
				backward.Reset();
			}

			controllermover = true;
			position.x += speed;

			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();

			kick.Reset();
			kickn.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchn.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();
			sm2.Reset();
			sm3.Reset();
			sm4.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_WALK_BACKWARD:

			if (position.x > App->enemy2->position.x)
			{
				current_animation = &forward;
				backward.Reset();
			}
			else
			{
				current_animation = &backward;
				forward.Reset();
			}

			controllermovel = true;
			position.x -= speed;

			crouch.Reset();
			jump.Reset();
			jumpf.Reset();
			jumpb.Reset();


			kick.Reset();
			kickn.Reset();
			kickb.Reset();
			kickf.Reset();
			kickc.Reset();

			punch.Reset();
			punchn.Reset();
			punchb.Reset();
			punchf.Reset();
			punchc.Reset();
			sm1.Reset();
			sm2.Reset();
			sm3.Reset();
			sm4.Reset();

			hhd.Reset();
			highd.Reset();
			lowd.Reset();

			break;

		case ST_JUMP_NEUTRAL:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jump;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			break;

		case ST_JUMP_FORWARD:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jumpf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("JUMPING FORWARD ^^>>\n");

			break;

		case ST_JUMP_BACKWARD:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &jumpb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
			}

			if (SDL_GetTicks() - App->input->jump_timer > JUMP_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->jump_timer = 0;

				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("JUMPING BACKWARD ^^<<\n");

			break;

		case ST_CROUCH:

			current_animation = &crouch;
			punchc.Reset();
			kickc.Reset();
			LOG("CROUCHING ****\n");

			break;

		case ST_PUNCH_CROUCH:

			if (attack == true)
			{
				attack = false;
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playercrouchpunch = App->collision->AddCollider({ 10, 20, 35, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}
			if (SDL_GetTicks() - App->input->punchc_timer < PUNCHC_TIME)
			{
				current_animation = &punchc;
			}

			LOG("PUNCH CROUCHING **++\n");

			break;

		case ST_PUNCH_STANDING:
			if (attack == true)
			{
				App->audio->PlayFX(Punch);
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &punch;
			}
			LOG("PUNCH STANDING ++++\n");
			if (colcreated == true)
			{
				playerpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
				colcreated = false;
			}
			break;

		case ST_PUNCH_NEUTRAL_JUMP:


			if (position.y <= 220)
			{
				animdone = false;


				current_animation = &punchn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playerjumpnpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}


			if (SDL_GetTicks() - App->input->punchn_timer > PUNCHN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchn_timer = 0;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH NEUTRAL JUMP ++++\n");


			break;

		case ST_PUNCH_FORWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playerjumpfpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}

			if (SDL_GetTicks() - App->input->punchf_timer > PUNCHF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchf_timer = 0;
				playerjumpfpunch->to_delete = true;
				colcreated = true;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("PUNCH JUMP FORWARD ^>>+\n");

			break;

		case ST_PUNCH_BACKWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &punchb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playerjumpbpunch = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}

			if (SDL_GetTicks() - App->input->punchb_timer > PUNCHB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->punchb_timer = 0;
				playerjumpbpunch->to_delete = true;
				colcreated = true;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}
			LOG("PUNCH JUMP BACKWARD ^<<+\n");

			break;

		case ST_KICK_CROUCH:

			if (attack == true)
			{

				if (colcreated == true)
				{
					App->audio->PlayFX(Kick);
					playercrouchkick = App->collision->AddCollider({ 10, 20, 100, 10 }, COLLIDER_PLAYER_SHOT, this);
				}
				attack = false;
			}
			if (SDL_GetTicks() - App->input->kickc_timer < KICKC_TIME)
			{
				current_animation = &kickc;
			}

			LOG("KICK CROUCHING **--\n");

			break;

		case ST_KICK_STANDING:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kick;

				//Check where should go fx	
				if (SDL_GetTicks() - App->input->kick_timer > 400 && position.y == 180)
				{
					position.y = 220;

				}

			}

			if (SDL_GetTicks() - App->input->kick_timer > KICK_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_KICK_FINISH);
				App->input->kick_timer = 0;

				position.y = 220;
				kick_jumpspeed = 6;
				animdone = true;
			}


			LOG("KICK --\n")
				if (App->player2->colcreated == true)
				{
					App->audio->PlayFX(Kick);
					App->player2->playerkick = App->collision->AddCollider({ 30, 100, 50, 10 }, COLLIDER_PLAYER_SHOT, this);
					App->player2->playerpunch = App->collision->AddCollider({ 0, 0, 0, 0 }, COLLIDER_PLAYER_SHOT, 0);
					App->player2->colcreated = false;
				}
			break;

		case ST_KICK_NEUTRAL_JUMP:


			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kickn;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Kick);
					playerjumpnkick = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}

			}

			if (SDL_GetTicks() - App->input->kickn_timer > KICKN_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickn_timer = 0;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP NEUTRAL ^^--\n");

			break;

		case ST_KICK_FORWARD_JUMP:

			if (position.y <= 220)
			{

				animdone = false;
				current_animation = &kickf;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x += 2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Kick);
					playerjumpfkick = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}

			if (SDL_GetTicks() - App->input->kickf_timer > KICKF_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickf_timer = 0;
				playerjumpfkick->to_delete = true;
				colcreated = true;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP FORWARD ^>>-\n");

			break;

		case ST_KICK_BACKWARD_JUMP:

			if (position.y <= 220)
			{
				animdone = false;
				current_animation = &kickb;
				position.y -= jumpspeed;
				jumpspeed -= 0.2;
				position.x -= 2;
				if (colcreated == true)
				{
					App->audio->PlayFX(Kick);
					playerjumpbkick = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
			}

			if (SDL_GetTicks() - App->input->kickb_timer > KICKB_TIME && position.y == 220)
			{
				App->input->inputs.Push(IN_JUMP_FINISH);
				App->input->kickb_timer = 0;
				playerjumpfkick->to_delete = true;
				colcreated = true;
				position.y = 220;
				jumpspeed = 6;
				animdone = true;
			}

			LOG("KICK JUMP BACKWARD ^<<-\n");

			break;

		case ST_SM1:

			current_animation = &sm1;
			if ((SDL_GetTicks() - App->input->sp1_timer) > 500)
			{
				App->particles->p1 = true;

				if (Activesm1 == true)
				{
					if (position.x < App->enemy2->position.x)
					{
						App->particles->AddParticle(App->particles->andyspecial1, position.x + 50, position.y - 90, COLLIDER_PLAYER_SHOT, 0);
					}
					else
					{
						App->particles->AddParticle(App->particles->andyspecial1, position.x - 30, position.y - 90, COLLIDER_PLAYER_SHOT, 0);
					}

					Activesm1 = false;
				}
			}

			break;

		case ST_SM2:

			current_animation = &sm2;
			if ((SDL_GetTicks() - App->input->sp2_timer) < SM2_TIME && (SDL_GetTicks() - App->input->sp2_timer) > 200)
			{
				if (colcreated == true)
				{
					App->audio->PlayFX(Punch);
					playerdash = App->collision->AddCollider({ 10, 20, 35, 10 }, COLLIDER_PLAYER_SHOT, this);
					colcreated = false;
				}
				if (position.x < App->enemy2->position.x)
				{
					position.x += dash_speed;
				}
				if (position.x > App->enemy2->position.x)
				{
					position.x -= dash_speed;
				}
				dash_speed -= 0.1;
			}


			break;

		case ST_SM3:



			current_animation = &sm3;


			if (attack == true)

			{
				//App->audio->PlayFX("Audio");
				attack = false;
			}
			if (Active == 0)
			{
				current_animation = &sm3;
			}
			LOG("SM3()()()()\n");
			if (colcreated == true)
			{
				playerwindmill = App->collision->AddCollider({ 10, 20, 55, 10 }, COLLIDER_PLAYER_SHOT, this);
				colcreated = false;
			}
			break;

		case ST_SM4:

			if (position.y <= 220 && (SDL_GetTicks() - App->input->sp4_timer) < SP4_TIME)
			{
				animdone = false;
				current_animation = &sm4;


				if ((SDL_GetTicks() - App->input->sp4_timer) > 300)
				{
					position.y -= flykick_speed;
					flykick_speed -= 0.14;
				}

				if (position.x < App->enemy2->position.x)
				{
					position.x += 2;
				}
				else
				{
					position.x -= 2;
				}

			}

			LOG("SM4()()()()\n");


			break;




		case ST_LDAMAGE:

			if (App->enemy2->lowdamage1 == true)
			{
				current_animation = &lowd;
			}

			break;

		case ST_HDAMAGE:

			if (App->enemy2->highdamage1 == true)
			{
				current_animation = &highd;
			}

			break;

		case ST_HHDAMAGE:

			if (position.y <= 220 && App->enemy2->hhdamage1 == true)
			{
				animdone = false;
				current_animation = &hhd;
				position.y -= hhd_speed;
				hhd_speed -= 0.14;
				if (position.x < App->enemy2->position.x)
				{
					position.x -= 2;
				}
				else
				{
					position.x += 2;
				}
			}

			break;
		}

	}

	current_state = state;

	SDL_Rect* r = &current_animation->GetCurrentFrame();

	playercol->SetPos(position.x, position.y);

	if (App->enemy2->position.x > position.x)
	{
		App->render->Blit(graphics, position.x + (current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r);
	}

	if (App->enemy2->position.x < position.x)
	{
		App->render->BlitWithScale(graphics, position.x + 50 + (-current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r, -1, 1.0f, 1, TOP_RIGHT);
	}

	if (App->enemy2->position.x > position.x) {

		playerpunch->SetPos(position.x + 40, position.y - 90);
		playerkick->SetPos(position.x + 60, position.y - 80);
		playercrouchpunch->SetPos(position.x + 40, position.y - 55);
		playercrouchkick->SetPos(position.x + 20, position.y - 20);
		playerjumpnkick->SetPos(position.x + 30, position.y - 15);
		playerjumpnpunch->SetPos(position.x + 35, position.y - 55);
		playerdash->SetPos(position.x + 35, position.y - 55);
		playerjumpfpunch->SetPos(position.x + 35, position.y - 55);
		playerjumpbpunch->SetPos(position.x + 35, position.y - 55);
		playerjumpfkick->SetPos(position.x + 35, position.y - 55);
		playerjumpbkick->SetPos(position.x + 35, position.y - 55);
		playerwindmill->SetPos(position.x + 57, position.y - 85);
	}

	if (App->enemy2->position.x < position.x) {

		playerpunch->SetPos(position.x - 40, position.y - 90);
		playerkick->SetPos(position.x - 60, position.y - 80);
		playercrouchpunch->SetPos(position.x - 40, position.y - 55);
		playercrouchkick->SetPos(position.x - 70, position.y - 20);
		playerjumpnkick->SetPos(position.x - 30, position.y - 15);
		playerjumpnpunch->SetPos(position.x - 30, position.y - 55);
		playerdash->SetPos(position.x - 35, position.y - 55);
		playerjumpfpunch->SetPos(position.x - 35, position.y - 55);
		playerjumpbpunch->SetPos(position.x - 35, position.y - 55);
		playerjumpfkick->SetPos(position.x - 35, position.y - 55);
		playerjumpbkick->SetPos(position.x - 35, position.y - 55);
		playerwindmill->SetPos(position.x - 57, position.y - 85);

	}

	playercol->SetPos(position.x, position.y);


	return true;

}

playerStates Player::process_fsm(p2Qeue<playerInputs>& inputs)
{

	static player_states state = ST_IDLE;
	player_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{

		case ST_IDLE:
		{
			switch (last_input)
			{

			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; timer_combo = SDL_GetTicks(); break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL; App->input->jump_timer = SDL_GetTicks();  break;
			case IN_R:

				if (SDL_GetTicks() - combotime < 250) {
					if (combo1 == 2)combo1 = 3;
				}
				if (combo1 == 3)
				{
					state = ST_SM1; App->input->sp1_timer = SDL_GetTicks(); combo1 = 0; break;
				}
				if (SDL_GetTicks() - combotime < 250) {
					if (combo2 == 2)combo2 = 3;
				}
				if (combo2 == 3)
				{
					state = ST_SM2; App->input->sp2_timer = SDL_GetTicks(); combo2 = 0; break;
				}

				if (SDL_GetTicks() - combotime < 250) {
					if (combo3 == 2)combo3 = 3;
				}
				if (combo3 == 3)
				{
					state = ST_SM3; App->input->sp3_timer = SDL_GetTicks(); combo3 = 0; break;
				}

				else
				{
					state = ST_KICK_STANDING, App->input->kick_timer = SDL_GetTicks(); combo4 = 0; break;
				}

			case IN_F: state = ST_SM1, App->input->sp1_timer = SDL_GetTicks(); break;
			case IN_C: state = ST_SM2, App->input->sp2_timer = SDL_GetTicks(); break;
			case IN_X: state = ST_SM3, App->input->sp3_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			//SM1 left side
			if ((position.x) <= (App->player2->position.x))
			{
				if (SDL_GetTicks() - combotime < 200)
				{
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
				else
				{
					combo1 = 0;
				}
			}

			//SM3 left side
			if ((position.x) <= (App->player2->position.x))
			{
				if (SDL_GetTicks() - combotime < 200)
				{
					if (combo3 == 3)combo3 = 2;
					combotime = SDL_GetTicks();
				}
				else
				{
					combo3 = 0;
				}
			}



			switch (last_input)
			{

			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			}

		}
		break;

		case ST_WALK_BACKWARD:
		{
			//SM2 LEFT SIDE
			if (SDL_GetTicks() - combotime < 200) {
				if (combo2 == 1)combo2 = 2;
				combotime = SDL_GetTicks();
			}
			else
			{
				combo2 = 0;
			}

			if (SDL_GetTicks() - combotime < 200) {
				if (combo3 == 1)combo3 = 2;
				combotime = SDL_GetTicks();
			}
			else
			{
				combo3 = 0;
			}



			switch (last_input)
			{

			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_T: state = ST_PUNCH_STANDING, App->input->punch_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_STANDING, App->input->kick_timer = SDL_GetTicks(); break;
			case IN_F: state = ST_SM1, App->input->sp1_timer = SDL_GetTicks(); break;
			case IN_C: state = ST_SM2, App->input->sp2_timer = SDL_GetTicks(); break;
			case IN_X: state = ST_SM3, App->input->sp3_timer = SDL_GetTicks(); break;
			case IN_Z: state = ST_SM4, App->input->sp4_timer = SDL_GetTicks(); break;
				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_NEUTRAL_JUMP; App->input->punchn_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			case IN_R: state = ST_KICK_NEUTRAL_JUMP; App->input->kickn_timer = SDL_GetTicks(); Active = 0; attack = true; break;
				//case IN_WIN: state = ST_WIN; animstart = 0;  break;

			}
		}
		break;

		case ST_JUMP_FORWARD:
		{

			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_FORWARD_JUMP;  App->input->punchf_timer = SDL_GetTicks(); Active = 0; attack = true; break;
			case IN_R: state = ST_KICK_FORWARD_JUMP;  App->input->kickf_timer = SDL_GetTicks(); Active = 0; attack = true; break;
				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{

			switch (last_input)
			{

			case IN_JUMP_FINISH: state = ST_IDLE; Active = 0; attack = true; break;
			case IN_T: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punchb_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_BACKWARD_JUMP;  App->input->kickb_timer = SDL_GetTicks(); Active = 0; attack = true; break;
				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_CROUCH:
		{
			playercol->to_delete = true;
			playercol = App->collision->AddCollider({ 50, -250, 45, -65 }, COLLIDER_PLAYER, this);

			combo1 = 1;
			combo2 = 1;
			combotime = SDL_GetTicks();

			if (SDL_GetTicks() - combosm1 < 120) {
				if (combo1 == 1)combo1 = 2;
				combosm1 = SDL_GetTicks();
			}
			if (SDL_GetTicks() - combosm2 < 120) {
				if (combo2 == 1)combo2 = 2;
				combosm2 = SDL_GetTicks();
			}


			switch (last_input)
			{

			case IN_CROUCH_UP: state = ST_IDLE; playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this); break;
			case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
			case IN_T: state = ST_PUNCH_CROUCH; App->input->punchc_timer = SDL_GetTicks(); break;
			case IN_R: state = ST_KICK_CROUCH; App->input->kickc_timer = SDL_GetTicks(); break;
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;
			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;
				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}
		break;

		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_LDAMAGE: state = ST_LDAMAGE, App->input->ldamage_timer = SDL_GetTicks(); break;

			case IN_PUNCH_CROUCH_FINISH:

				if (IN_CROUCH_DOWN == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}
				else
				{
					state = ST_IDLE; Active = 0; attack = true;
					playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
				}

				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		break;

		case ST_KICK_STANDING:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_IDLE; playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this); attack = true; break;

			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;

				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}

		}
		break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_JUMP_NEUTRAL; Active = 0; attack = true; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{

			case IN_HDAMAGE: state = ST_HDAMAGE, App->input->hdamage_timer = SDL_GetTicks(); break;

			case IN_KICK_CROUCH_FINISH:

				if (IN_CROUCH_DOWN == true)
				{
					state = ST_CROUCH; Active = 0; attack = true;

				}

				else
				{
					state = ST_IDLE; Active = 0; attack = true;
					playercol->to_delete = true; playercol = App->collision->AddCollider({ 50, -250, 45, -103 }, COLLIDER_PLAYER, this);
				}

				//case IN_WIN: state = ST_WIN; Active = 0;  break;

			}
		}

		}
	}
	return state;

}

void Player::OnCollision(Collider* c1, Collider* c2) {

	if (playercol == c1 && c2->type == COLLIDER_ENEMY)
	{
		//App->enemy2->position.x += 3;

	}
	
	if (playerjumpbkick == c1 && c2->type == COLLIDER_ENEMY)
	{

		App->render->StartCameraShake(250, 3);
		App->render->UpdateCameraShake();
		playerjumpbkick->to_delete = true;
		highdamage2 = true;
		App->input->inputs2.Push(IN_HDAMAGE2);
		App->enemy2->life -= 10;
		App->enemy2->position.x += 3;

		//TRYING RUMBLE
		SDL_HapticRumblePlay(App->input->haptic, 0.2f, 500);
		LOG("MUST RUMBLE");
	}



	if (playercol == c1 && App->scene_billykane->wall1c == c2)   //Colisions with first wall
	{
		position.x += 2;

	}
	if (playercol == c1 && App->scene_billykane2->wall1c == c2)   //Colisions with first wall
	{
		position.x += 2;

	}
	if (playercol == c1 && App->scene_billykane3->wall1c == c2)   //Colisions with first wall
	{
		position.x += 2;

	}
	if (App->enemy2->life <= 0)
	{

	}
}
*/