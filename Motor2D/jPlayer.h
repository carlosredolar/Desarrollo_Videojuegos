#ifndef _JPLAYER_H
#define _JPLAYER_H

#include "j1Module.h"
#include "jAnimation.h"
#include "p2Point.h"
#include "p2Sstring.h"
#include "p2Qeue.h"
#include "SDL\include\SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAXJUMPHEIGHT 200
#define MAX_FRAME_COLLIDERS 6
#define JUMP_VELOCITY 5
#define FALL_VELOCITY 10
#define SPEEDX  1
#define SPEEDY 1

struct SDL_Texture;

enum playerStates
{
	stUnknown=0,
	stIdle,
	stJump,
	stWalkRight,
	stWalkLeft,
	stFalling,
	stDie
};

enum playerInputs
{
	INleft=0,
	INright,
	INjump,
	INleftUP,
	INrightUP,
	INjumpEND,
	INfalling,
	INdie
};


class jPlayer : public j1Module
{
public:
	jPlayer();
	~jPlayer();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void internal_input(p2Qeue<playerInputs> &inputs);
	void external_input(p2Qeue<playerInputs> &inputs);
    playerStates process_fsm(p2Qeue<playerInputs> &inputs);
	void ResetPlayer();
	void colliders_and_blit(Animation*);
	void positionlimits();
	void debugcommands(p2Qeue<playerInputs> &inputs);
	void doJump();


public:

	SDL_Texture* graphicsRight = nullptr;
	SDL_Texture* graphicsLeft = nullptr;
	Animation idleRight;
	Animation idleLeft;
	Animation walkRight;
	Animation walkLeft;
	Animation jumpLeft;
	Animation jumpRight;
	Animation dieRight;
	Animation dieLeft;
	Animation fallingLeft;
	Animation fallingRight;

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
	int jumpHeight = 0;

	bool grounded = true;
	bool facingRight = true;
	bool jumping = false;


	Uint32 jump_timer = 0;	
};

#endif