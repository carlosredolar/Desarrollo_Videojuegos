#include "EntityManager.h"
#include "j1App.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Collision.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Audio.h"
//#include "j1UI.h"
#include "j1Particles.h"
#include "j1Zombie.h"
#include "Bat.h"
#include "Entity.h"
#include "brofiler/Brofiler/Brofiler.h"


EntityManager::EntityManager() {
	name.create("entities");
}


EntityManager::~EntityManager() {
}

Entity* EntityManager::CreateEntity(EntityType type, int position_x, int position_y)
{
	//static_assert(EntityType::UNKNOWN == 4, "code needs update");
	Entity* entity = nullptr;
	switch (type)
	{
	case EntityType::PLAYER:
		entity = new j1Player();
		break;
	case EntityType::WALKING_ENEMY:
		entity = new j1Zombie();
		entity->position.x = position_x;
		entity->position.y = position_y;
		break;
	case EntityType::FLYING_ENEMY:
		entity = new Bat();
		entity->position.x = position_x;
		entity->position.y = position_y;
		break;
	/*case EntityType::TRAP:
		entity = new j1Trap();
		entity->position.x = position_x;
		entity->position.y = position_y;
		break;*/
	case EntityType::PARTICLES:
		break;
	case EntityType::UNKNOWN:
		break;
	default:
		break;
	}

	if (entity != nullptr) entities.add(entity);

	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	p2List_item<Entity*>* item;

	if (entity != nullptr) {
		item = entities.At(entities.find(entity));
		if (entity->collider != nullptr)
		{
			entity->collider->to_delete = true;
			entity->collider = nullptr;
		}
		if (entity->raycast != nullptr) {
			entity->raycast->to_delete = true;
			entity->raycast = nullptr;
		}
		entities.del(item);;
	}
}


bool EntityManager::Awake(pugi::xml_node& config) {
	bool ret = true;

	config_data = config;

	gravity = config.child("gravity").attribute("value").as_int();

	//player creation
	player = new j1Player();
	player->Awake(config.child("player"));
	entities.add(player);
	
	//reference walking enemy
	reference_walking_enemy = new j1Zombie();
	reference_walking_enemy->Awake(config.child("walking_enemy"));

	//reference flying enemy
	reference_flying_enemy = new Bat();
	reference_flying_enemy->Awake(config.child("flying_enemy"));

	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;

	player->Start();
	reference_walking_enemy->texture = App->tex->Load("sprites/characters/spritesheet_zombie.png");
	reference_flying_enemy->texture = App->tex->Load("sprites/characters/spritesheet_bat.png");

	for (p2List_item<Entity*>* entity = entities.start; entity != nullptr; entity = entity->next)
	{
		if (entity->data->type == EntityType::WALKING_ENEMY) {
			entity->data->texture = reference_walking_enemy->texture;
		}
		if (entity->data->type == EntityType::FLYING_ENEMY) {
			entity->data->texture = reference_flying_enemy->texture;
		}
	}

	return ret;
}

bool EntityManager::CleanUp()
{
	bool ret = true;
	/*
	App->tex->UnLoad(walking_enemy_texture);
	walking_enemy_texture = nullptr;
	App->tex->UnLoad(flying_enemy_texture);
	flying_enemy_texture = nullptr;
	*/

	App->tex->UnLoad(trap_texture);
	trap_texture = nullptr;


	App->tex->UnLoad(reference_walking_enemy->texture);
	reference_walking_enemy->texture = nullptr;

	App->tex->UnLoad(reference_flying_enemy->texture);
	reference_flying_enemy->texture = nullptr;

	for (p2List_item<Entity*>* entity = entities.start; entity != nullptr; entity = entity->next)
	{
		entity->data->DestroyEntity(entity->data);
	}

	return ret;
}

bool EntityManager::PreUpdate()
{
	bool ret = true;
	player->PreUpdate();
	return ret;
}

bool EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("EntitiesUpdate", Profiler::Color::MediumPurple)
		bool ret = true;

	for (p2List_item<Entity*>* entity = entities.start; entity != nullptr; entity = entity->next)
	{
		if (entity != nullptr)
		{
			entity->data->Update(dt);
		}
	}

	return ret;
}

bool EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("EntitiesPostUpdate", Profiler::Color::Khaki)
		bool ret = true;
	for (p2List_item<Entity*>* entity = entities.start; entity != nullptr; entity = entity->next)
	{
		entity->data->PostUpdate();
	}
	return ret;
}


bool EntityManager::Load(pugi::xml_node& data)
{
	CleanUp();
	bool ret = true;
	p2List_item<Entity*>* item;

	for (pugi::xml_node WALKING_ENEMY = data.child("walking_enemy"); WALKING_ENEMY; WALKING_ENEMY = WALKING_ENEMY.next_sibling("walking_enemy"))
	{
		CreateEntity(EntityType::WALKING_ENEMY, WALKING_ENEMY.attribute("position_x").as_int(), WALKING_ENEMY.attribute("position_y").as_int());
	}

	for (pugi::xml_node FLYING_ENEMY = data.child("flying_enemy"); FLYING_ENEMY; FLYING_ENEMY = FLYING_ENEMY.next_sibling("flying_enemy"))
	{
		CreateEntity(EntityType::FLYING_ENEMY, FLYING_ENEMY.attribute("position_x").as_int(), FLYING_ENEMY.attribute("position_y").as_int());
	}


	return ret;
}

bool EntityManager::Save(pugi::xml_node& data)
{
	bool ret = true;
	p2List_item<Entity*>* item;

	for (item = entities.start; item != nullptr; item = item->next)
	{
		pugi::xml_node child = data.append_child(item->data->name.GetString());
		child.append_attribute("position_x") = item->data->position.x;
		child.append_attribute("position_y") = item->data->position.y;
	}

	return ret;
}

void EntityManager::DestroyAllEntities() {
	p2List_item<Entity*>* item;

	for (item = entities.start; item != nullptr; item = item->next)
	{
		DestroyEntity(item->data);
	}
}