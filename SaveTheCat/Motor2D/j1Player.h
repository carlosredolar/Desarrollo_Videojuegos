#ifndef _j1PLAYER_H_
#define _j1PLAYER_H_

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#include "p2Vec2.h"

struct SDL_Texture;
struct Collider;

#define COLLIDER_MARGIN speed*1.5f
#define JUMP_AFTER_SLIDE 5.1f

struct Player_Input {
	bool pressing_W;
	bool pressing_A;
	bool pressing_S;
	bool pressing_D;
	bool pressing_space;
	bool S_keyUp;
};

enum Player_States {
	IDLE, 
	RUN_FORWARD,
	RUN_BACKWARD,
	JUMP,
	FALL,
	SLIDE_FORWARD,
	SLIDE_BACKWARD,

};

class j1Player : public j1Module {
public:
	j1Player();

	virtual ~j1Player();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void MovementControl();

	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

	bool LoadAnimations();

private:


public:

	SDL_Texture* player_tex;
	p2SString folder;
	Player_Input player_input;
	int initial_x_position;
	int initial_y_position;
	iPoint position;
	iPoint lastPosition;
	fVec2 velocity;

	//animations
	Animation idle;
	Animation jump;
	Animation run;
	Animation slide;
	Animation fall;
	Animation death;
	Animation* current_animation;

	p2SString jumpFX,deathFX,slideFX,winFX,music;

	p2List<Animation*> animations;

	pugi::xml_document animation_doc;

	Player_States state;
	Player_States last_state;

	SDL_RendererFlip flip;
	Collider* collider = nullptr;
	Collider* collider_copy;

	float speed;
	float jumpImpulse;
	float gravity;

	bool can_double_jump = true;
	bool can_go_right = true;
	bool can_go_left = true;
	bool god = false;
};

#endif // !_j1PLAYER_H_

