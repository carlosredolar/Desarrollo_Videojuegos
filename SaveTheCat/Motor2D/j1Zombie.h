#ifndef _j1ZOMBIE_H_
#define _j1ZOMBIE_H_

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#include "p2Vec2.h"
#include "p2DynArray.h"
#include "brofiler/Brofiler/Brofiler.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

#define COLLIDER_MARGIN speed*1.5f
#define JUMP_AFTER_SLIDE 5.1f



enum Zombie_States {

	IDLE_Z,
	RUN_FORWARD_Z,
	RUN_BACKWARD_Z,
	FALL_Z,
	DEATH_Z,
};

class j1Zombie : public j1Entity {
public:
	j1Zombie();

	virtual ~j1Zombie();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	//void MovementControl();

	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

	bool LoadAnimations();

	void PathControl();
	//bool waitTime(float s);

public:

	SDL_Texture* zombie_tex;
	p2SString folder;
	int initial_x_position = 0;
	int initial_y_position = 0;
	int death_reset = 0;
	int death_timer = 0;
	float waitTimer = 0;
	iPoint position;
	iPoint lastPosition;
	fVec2 velocity;

	bool deathSound = false;
	bool winSound = false;
	bool chasing = false;
	bool debugPath;

	//animations
	Animation idle;
	Animation run;
	Animation fall;
	Animation death;
	Animation* current_animation;

	p2SString jumpFX, deathFX, slideFX, winFX, music;

	p2List<Animation*> animations;

	pugi::xml_document animation_doc;

	Zombie_States state;
	Zombie_States last_state;

	SDL_RendererFlip flip;
	Collider* collider = nullptr;
	Collider* collider_copy;
	SDL_Texture* debug_tex;

	float speed;
	float jumpImpulse;
	float gravity;

	bool can_double_jump = true;
	bool can_go_right = true;
	bool can_go_left = true;
	bool god = false;
	const p2DynArray<iPoint>* path;

private:
	float dt = 0.0f;
};

#endif // !_j1ZOMBIE_H_