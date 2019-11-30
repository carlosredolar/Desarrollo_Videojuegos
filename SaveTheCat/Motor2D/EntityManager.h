#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "SDL_image/include/SDL_image.h"

class Entity;
struct SDL_Texture;


enum class EntityType
{
	PLAYER,
	WALKING_ENEMY,
	FLYING_ENEMY,
	TRAP,
	PARTICLES,
	UNKNOWN
};


class EntityManager : public j1Module
{
public:

	EntityManager();
	~EntityManager();

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();

	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();

	virtual bool CleanUp();

	virtual bool Load(pugi::xml_node& data);
	virtual bool Save(pugi::xml_node& data);

	Entity* CreateEntity(EntityType type, int position_x, int position_y);
	virtual void DestroyEntity(Entity* delete_entity);
	void DestroyAllEntities();

public:

	p2List<Entity*> entities;
	pugi::xml_node config_data;

	j1Player* player;

public:
	int gravity = 0;

	j1Zombie* reference_walking_enemy = nullptr;
	Bat* reference_flying_enemy = nullptr;

	//health
	int trap_health = 0;

	//damage
	int trap_damage = 0;

	//textures
	SDL_Texture* trap_texture = nullptr;

	//sfx
	uint walking_enemy_attack_fx;
	uint flying_enemy_attack_fx;

	uint walking_enemy_die_fx;
	uint flying_enemy_die_fx;


};

#endif // _ENTITY_MANAGER_H_