#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#ifndef _j1BAT_H_
#define _j1BAT_H_

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "j1Audio.h"
#include "SDL/include/SDL.h"
#include "p2Vec2.h"
#include "brofiler/Brofiler/Brofiler.h"

struct SDL_Texture;
struct Collider;

#define COLLIDER_PREDICTION speed

/*struct Bat_Input {
	bool pressing_W;
	bool pressing_A;
	bool pressing_S;
	bool pressing_D;
	bool pressing_space;
	bool S_keyUp;
};*/

enum Bat_States {
	FLY,
	FLY_RIGHT,
	FLY_LEFT,
	FLY_UP,
	FLY_DOWN,
	DEATH_BAT,

};

class j1Bat : public j1Module {
public:
	j1Bat();

	virtual ~j1Bat();

	bool Awake(pugi::xml_node&);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void MovementControl(float dt);

	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

	bool LoadAnimations();

	bool waitTime(float s);

	void j1Bat::calculate_path();
	void j1Bat::blit_path();
	void j1Bat::check_path_toMove();


public:

	SDL_Texture* bat_tex;
	SDL_Texture* debug_tex = nullptr;
	p2SString folder;
	//Bat_Input bat_input;
	int initial_x_position = 0;
	int initial_y_position = 0;
	int death_reset = 0;
	int death_timer = 0;
	float waitTimer = 0;
	iPoint position;
	iPoint lastPosition;
	fVec2 velocity;

	bool deathSound = false;


	//animations
	Animation fly;
	Animation death_bat;
	Animation* current_animation;

	p2SString deathFX;

	p2List<Animation*> animations;

	pugi::xml_document animation_doc;

	Bat_States state;
	Bat_States last_state;

	SDL_RendererFlip flip;
	Collider* collider = nullptr;
	Collider* collider_copy;

	float speed;
	float gravity;

	bool can_go_right = true;
	bool can_go_left = true;
	bool can_go_up = true;
	bool can_go_down = true;
	bool god = false;
	bool set_path = true;

private:
	float dt = 0.0f;
};

#endif // !_j1BAT_H_

