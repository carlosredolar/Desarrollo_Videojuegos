#ifndef _ModuleCollision_H_
#define _ModuleCollision_H_

#define MAX_COLLIDERS 100
#include "j1Module.h"


enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	//COLLIDER_WALL_LEFT,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_ATTACK,
	COLLIDER_ENEMY_SHOT,
	//COLLIDER_WALL_RIGHT,
	COLLIDER_WALL,
	COLLIDER_GROUND,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	
	Collider(SDL_Rect rectangle, COLLIDER_TYPE typeC, j1Module* callbackC = nullptr) 
	{
		rect = rectangle;
		type = typeC;
		callback = callbackC;
	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	bool CheckCollision(const SDL_Rect& r) const;
};

class jCollisions : public j1Module
{
public:

	jCollisions();
	~jCollisions();

	bool PreUpdate() override;
	bool Update();
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE typeC, j1Module* callbackC = nullptr);
	void DebugDraw();
	void DeleteCollider(Collider*);

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __jCollisions_H__