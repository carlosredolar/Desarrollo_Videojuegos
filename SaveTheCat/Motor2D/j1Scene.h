#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

#define CAMERA_SPEED 10
#define CAMERA_RUN_SPEED 2
#define SPEED 3

struct SDL_Texture;
struct Collider;

enum MapLoaded
{
	NO_MAP = 0,
	LEVEL_1,
	LEVEL_2,
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void Reset_Camera();

	void ResetLevel();

public:
	
	/*int left_edge;
	int right_edge;*/
	int top_edge;
	int bottom_edge;
	MapLoaded current_level;
	int	player_x_position;
	int	player_y_position;
	int farTimer, midTimer, closeTimer;
	SDL_Texture* backTex;
	SDL_Texture* farTex; 
	SDL_Texture* midTex;
	SDL_Texture* closeTex;
	iPoint backPos;
	iPoint farPos;
	iPoint midPos;
	iPoint closePos;
	SDL_Rect* container;
	SDL_Rect cam_death;
	Collider* collider = nullptr;
	Collider* collider_copy;
private:
	int speedCount = 0;
};

#endif // __j1SCENE_H__