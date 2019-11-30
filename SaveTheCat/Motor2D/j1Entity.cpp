#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "p2Log.h"

j1Entity::j1Entity(EntityType type) : j1EntityManager() {
}

j1Entity::~j1Entity() {

}

bool j1Entity::Awake(pugi::xml_node& config) {

	//config = config.child("")

	return true;
}

bool j1Entity::Start() {
	bool ret = true;

	return ret;
}

bool j1Entity::PreUpdate() {
	bool ret = true;
	return ret;
}

bool j1Entity::Update(float dt) {
	bool ret = true;
	return ret;
}

bool j1Entity::PostUpdate() {
	bool ret = true;

	return ret;
}

void j1Entity::PathfindtoPlayer(int range, j1Entity* player) {

	//if the player is close we create a path to him
	if ((abs(player->position.x - position.x) < range) && (player->state != DEATH))
	{
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(player->position.x, player->position.y);
		App->pathfinding->CreatePath(origin, destination);
		chasing = true;
	}
	else { chasing = false; }

	//pathfinding debug
	if (chasing)
	{
		int x, y;
		SDL_Rect Debug_rect = { 0,0,32,32 };

		pathToPlayer = App->pathfinding->GetLastPath();

		for (uint i = 0; i < pathToPlayer->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(pathToPlayer->At(i)->x, pathToPlayer->At(i)->y);
			Debug_rect.x = pos.x;
			Debug_rect.y = pos.y;
			//if (App->collision->debug)App->render->DrawQuad(Debug_rect, 90, 850, 230, 40);
		}
	}

}

bool j1Entity::LoadAnimations() {
	pugi::xml_parse_result result = animation_doc.load_file("sprites/characters/animations.xml");
	bool ret = true;
	uint i = 0u;
	uint j = 0;

	if (result == NULL)
	{
		LOG("Could not load animations xml file %s. pugi error: %s", "animations.xml", result.description());
		ret = false;
	}

	animations.add(&idle);
	animations.add(&run);
	animations.add(&slide);
	animations.add(&jump);
	animations.add(&fall);
	animations.add(&death);

	pugi::xml_node animation = animation_doc.child("animations").child("animation");
	pugi::xml_node frame;
	p2List_item<Animation*>* item = animations.start;
	int x, y, w, h;
	float anim_speed = 1;

	LOG("Loading animations ---------");

	for (animation; animation; animation = animation.next_sibling("animation"))
	{
		item->data->loop = animation.attribute("loop").as_bool();

		for (frame = animation.child("data").child("frame"); frame; frame = frame.next_sibling("frame"))
		{
			x = frame.attribute("x").as_int();
			y = frame.attribute("y").as_int();
			w = frame.attribute("w").as_int();
			h = frame.attribute("h").as_int();
			anim_speed = frame.attribute("speed").as_float();

			item->data->PushBack({ x,y,w,h }, anim_speed);
		}
		i++;
		item = item->next;
	}

	LOG("%u animations loaded", i);

	return ret;
}

/*bool j1Entity::LoadAnimations(const char* path) {
	bool ret = true;

	p2SString file("sprites/characters/%s", path);

	pugi::xml_document animation_file;
	pugi::xml_parse_result result = animation_file.load_file(file.GetString());
	p2SString image(animation_file.child("tileset").child("image").attribute("source").as_string());

	if (result == NULL)
	{
		LOG("Could not load animation tmx file %s. pugi error: %s", path, result.description());
		ret = false;
	}


	int tile_width = animation_file.child("map").child("tileset").attribute("tilewidth").as_int();
	int tile_height = animation_file.child("map").child("tileset").attribute("tileheight").as_int();
	int columns = animation_file.child("map").child("tileset").attribute("columns").as_int();
	int firstgid = animation_file.child("map").child("tileset").attribute("firstgid").as_int();
	int id, tile_id;
	float speed;

	pugi::xml_node animation = animation_file.child("map").child("tileset").child("tile");
	pugi::xml_node frame = animation.child("animation").child("frame");

	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;

	p2List_item<Animation*>* item_animation;

	while (animation != nullptr)
	{
		p2SString animation_name(animation.child("properties").child("property").attribute("name").as_string());

		if (animation_name == "idle")
			animations.add(&idle);
		if (animation_name == "walk")
			animations.add(&walk);
		if (animation_name == "slide")
			animations.add(&slide);
		if (animation_name == "run")
			animations.add(&run);
		if (animation_name == "crouch_down")
			animations.add(&crouch_down);
		if (animation_name == "crouch_up")
			animations.add(&crouch_up);
		if (animation_name == "jump")
			animations.add(&jump);
		if (animation_name == "fall")
			animations.add(&fall);
		if (animation_name == "attack")
			animations.add(&attack);

		id = animation.attribute("id").as_int();

		item_animation = animations.end;

		while (frame != nullptr) {
			tile_id = frame.attribute("tileid").as_int();
			speed = frame.attribute("duration").as_int() * 0.001f;
			rect.x = rect.w * ((tile_id) % columns);
			rect.y = rect.h * ((tile_id) / columns);
			item_animation->data->PushBack(rect, speed);
			frame = frame.next_sibling();
		}

		animation = animation.next_sibling();
		frame = animation.child("animation").child("frame");
	}

	return ret;
}*/