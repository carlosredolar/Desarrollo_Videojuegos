#ifndef _JPLAYER_H
#define _JPLAYER_H

#include "j1Module.h"
#include "jAnimation.h"
#include "p2Point.h"
#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define JUMP_TIME 850
#define MAXJUMPHEIGHT 50
#define MAX_FRAME_COLLIDERS 6

struct SDL_Texture;

enum playerStates
{
	stIdle=0,
	stJump,
	stWalk,
	stFalling,
	stDie
};

enum playerInputs
{
	INnone = 0,
	INleft,
	INright,
	INjump,
	INleftUP,
	INrightUP,
	INjumpEND
};


class jPlayer : public j1Module
{
public:
	jPlayer();
	~jPlayer();

	bool Start();
	bool Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	bool internal_input(p2Qeue<playerInputs>& inputs);
	bool external_input(p2Qeue<playerInputs>& inputs);
    //playerStates process_fsm(p2Qeue<playerInputs>& inputs);
	void ResetPlayer();
	void colliders_and_blit(Animation*);
	void positionlimits();
	void debugcommands();
	void doJump();


public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* shadow = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation die;

	iPoint position;

	Mix_Chunk* win_sound;
	Mix_Chunk* death_sound;

	bool DeathSoundPlayed = false;
	bool WinSoundPlayed = false;

	Collider* colliders[MAX_COLLIDERS];

	bool GodMode = false;
	bool death = false;
	int sound = 0;
	int PivotX = 0;
	int PivotY = 0;

	bool leftLimit = false;
	bool RightLimit = false;

	int ActiveDeath = 0;
	int speedX = 1;
	int speedY = 1;
	int jumpHeight = 0;

	bool grounded = true;
	bool facingRight = true;
	bool jumping = false;

	playerStates currentState,newState;

	Uint32 jump_timer = 0;	
};

#endif