#ifndef _BAT_H_
#define _BAT_H_

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#include "p2Vec2.h"
#include "p2DynArray.h"
#include "brofiler/Brofiler/Brofiler.h"
#include "Entity.h"

struct SDL_Texture;
struct Collider;

struct Bat_Input {
	
};

enum Bat_States {
	IDLE_BAT,
	FLY_RIGHT_BAT,
	FLY_LEFT_BAT,
	DEATH_BAT,
};

class Bat : public Entity 
{
public:
	Bat();

	virtual ~Bat();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void PathControl();

	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

	bool LoadAnimations();

	bool waitTime(float s);

private:
	
public:
	SDL_Texture* bat_tex;
	p2SString folder;
	Bat_Input Bat_input;
	int initial_x_position = 0;
	int initial_y_position = 0;
	int death_reset = 0;
	int death_timer = 0;
	float waitTimer = 0;
	iPoint position;
	iPoint lastPosition;
	fVec2 velocity;
	bool debugPath;
	bool deathSound = false;
	bool chasing = false;

	//animations
	Animation idle;
	Animation run;
	Animation death;
	Animation* current_animation;

	p2SString  deathFX;

	p2List<Animation*> animations;

	pugi::xml_document animation_doc;
	Bat_States state;
	Bat_States last_state;

	SDL_RendererFlip flip;
	Collider* collider = nullptr;
	Collider* collider_copy;
	SDL_Texture* debug_tex;
	const p2DynArray<iPoint>* path;
};

#endif //