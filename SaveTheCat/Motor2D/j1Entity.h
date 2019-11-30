#ifndef _j1ENTITY_H
#define _j1ENTITY_H
#include "SDL/include/SDL.h"
#include "Animation.h"
#include "j1EntityManager.h"
#include "p2DynArray.h"
#include "p2Log.h"

struct SDL_Texture;
struct Collider;

#define COLLIDER_MARGIN 20

enum EntityState {
	IDLE,
	JUMP,
	RUN_FORWARD,
	RUN_BACKWARD,
	FALL,
	ATTACK,
	SLIDE_FORWARD,
	SLIDE_BACKWARD,
	CROUCH_UP,
	CROUCH_DOWN,
	DEATH,
};

class j1Entity : public j1EntityManager
{
public:

	j1Entity(EntityType type);
	virtual ~j1Entity();

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp() { return true; };
	virtual void OnCollision(Collider* c1, Collider* c2) {};
	void PathfindtoPlayer(int range, j1Entity* player);
	bool LoadAnimations();

public:
	iPoint position;
	iPoint lastPosition;
	iPoint current_speed;
	iPoint speed;
	int initial_x_position = 0;
	int initial_y_position = 0;

	int health = 0;
	int damage = 0;

	bool grounded = false;
	int gravity = 0;
	int max_falling_speed = 0;

	Collider* collider = nullptr;
	Collider* raycast = nullptr;
	Collider* last_collider = nullptr;

	uint die_fx = 0;
	p2SString die_fx_path;

	p2List<Animation*> animations;
	Animation idle;
	Animation walk;
	Animation slide;
	Animation crouch_down;
	Animation crouch_up;
	Animation jump;
	Animation run;
	Animation fall;
	Animation attack;
	Animation death;
	Animation* current_animation = nullptr;

	pugi::xml_document animation_doc;

	EntityType type = EntityType::UNKNOWN;
	EntityState state = EntityState::IDLE;
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	bool isVisible = true;

	bool chasing = false;

	const p2DynArray<iPoint>* pathToPlayer = nullptr;

};
#endif // _ENTITY_H