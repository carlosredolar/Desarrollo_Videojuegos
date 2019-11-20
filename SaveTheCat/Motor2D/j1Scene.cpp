#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1Collision.h"
#include "j1Pathfinding.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//invisible square delimiting the space in the camera where the player can move
	if (App->render->camera.y < 1)
	{
		top_edge = App->render->camera.y + App->render->camera.h / 4;
		bottom_edge = App->render->camera.y + App->render->camera.h * 3 / 4;
	}
	
	//left_edge = App->render->camera.x + App->render->camera.w / 3;
	//right_edge = App->render->camera.x + App->render->camera.w *1/2;

	/*backTex = App->tex->Load("sprites/parallax/background.png");
	farTex = App->tex->Load("sprites/parallax/sofar.png");
	midTex = App->tex->Load("sprites/parallax/medium.png");
	closeTex = App->tex->Load("sprites/parallax/front.png");
	backPos.x = 0; backPos.y = -App->render->camera.y;
	farPos.x = 0; farPos.y = -App->render->camera.y;
	midPos.x = 0; midPos.y = -App->render->camera.y;*/
	//closePos.x = 0; closePos.y = -App->render->camera.y;
	container = new SDL_Rect{0,0,13500,1000};
	cam_death = SDL_Rect{ 0,0,10,App->render->camera.h*2 };
	farTimer = 0;
	midTimer = 0;
	closeTimer = 0;

	App->audio->PlayMusic("music_sadpiano.ogg");
	
	//App->map->Load("hello2.tmx");
	App->map->Load("Level1.tmx");
	//App->map->Load("Level2.tmx");	
	App->render->camera.y = 0;
	speedCount = 0;

	collider = App->collision->AddCollider(cam_death, COLLIDER_DEATH, (j1Module*)App->scene);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() 
{ 
	BROFILER_CATEGORY("PreUpdate_Scene", Profiler::Color::AliceBlue)
	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}
	return true; 
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene", Profiler::Color::AntiqueWhite)
	iPoint* player_position = &App->player->position;

	cam_run_start = SDL_GetTicks();

	if (cam_run_start > cam_run_start_timer)
	{
		App->render->camera.x -= CAMERA_RUN_SPEED;
		collider->SetPos(-App->render->camera.x, 0);

		//Parallax
		farTimer++; midTimer++; closeTimer++;
		backPos.x += CAMERA_RUN_SPEED;
		if (farTimer >= CAMERA_RUN_SPEED) { farPos.x += CAMERA_RUN_SPEED; farTimer = 0; }
		if (midTimer >= CAMERA_RUN_SPEED + 1) { midPos.x += CAMERA_RUN_SPEED; midTimer = 0; }
		if (closeTimer >= CAMERA_RUN_SPEED + 2) { closePos.x += CAMERA_RUN_SPEED; closeTimer = 0; }
	}
	

	App->render->Blit(backTex, backPos.x, backPos.y,container);
	App->render->Blit(farTex, farPos.x, farPos.y, container);
	App->render->Blit(midTex, midPos.x, midPos.y, container);
	App->render->Blit(closeTex, closePos.x, closePos.y, container);

	//player inputs ---------------
	if (current_level == LEVEL_1)
	{
		want_to_load = 2;
	}
	else if (current_level == LEVEL_2)
	{
		want_to_load = 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		if (current_level == LEVEL_1)
		{
			ResetLevel();
			Reset_Camera();
		}
		else
		{
			App->map->CleanUp();
			App->scene->CleanUp();
			App->map->Load("Level1.tmx");
			ResetLevel();
			Reset_Camera();
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {

		if (current_level == LEVEL_2)
		{
			ResetLevel();
			Reset_Camera();
		}
		else
		{
			App->map->CleanUp();
			App->scene->CleanUp();
			App->map->Load("Level2.tmx");
			ResetLevel();
			Reset_Camera();
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		ResetLevel();
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();


	//camera window ------------------

	/*speedCount++;
	if (speedCount >= SPEED) { App->render->camera.x -= 1; speedCount = 0; }*/
	
	

	/*
	if (((player_position->x < left_edge)) &&(left_edge > App->render->initial_camera_x + App->render->camera.w / 3)){
			App->render->camera.x += App->player->speed;
			right_edge -= App->player->speed;
			left_edge -= App->player->speed;
	}

	if (player_position->x+App->player->current_animation->GetCurrentFrame().w > right_edge) { 
		App->render->camera.x -= App->player->speed;
		right_edge += App->player->speed;
		left_edge+= App->player->speed;
	}*/

	if (((player_position->y < top_edge))&&(top_edge > App->render->initial_camera_y - App->player->current_animation->GetCurrentFrame().h)) {
			App->render->camera.y += App->player->speed;
			top_edge -= App->player->speed;
			bottom_edge -= App->player->speed;
	}

	if (((player_position->y + App->player->current_animation->GetCurrentFrame().h > bottom_edge))&&(top_edge < App->render->initial_camera_y + 380)) {
		App->render->camera.y -= App->player->speed;
		top_edge+= App->player->speed;
		bottom_edge+= App->player->speed;
	}
	
	//camera manual control --------------

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += CAMERA_SPEED;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= CAMERA_SPEED;

	if((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)&&(App->render->camera.x < 0))
		App->render->camera.x += CAMERA_SPEED;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= CAMERA_SPEED;
	


	App->map->Draw();

	/*p2SString title("Save The Cat",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());*/

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	//App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		//App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate_Scene", Profiler::Color::Azure)
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		App->input->windowEvents[WE_QUIT] = true;
	}
	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::Reset_Camera() {
	App->render->camera.x = App->render->initial_camera_x;
	App->render->camera.y = App->render->initial_camera_y;
	top_edge = App->render->camera.y + App->render->camera.h / 4;
	bottom_edge = App->render->camera.y + App->render->camera.h * 3/4;
	collider->SetPos(-App->render->camera.x, 0);
	backPos.x = 0;
	farPos.x = 0;
	midPos.x = 0;
	closePos.x = 0;
	/*left_edge = App->render->camera.x + App->render->camera.w / 3;
	right_edge = App->render->camera.x + App->render->camera.w * 1 / 2;*/
}

void j1Scene::ResetLevel() {
	App->player->position.x = player_x_position;
	App->player->position.y = player_y_position;
	cam_run_start = SDL_GetTicks();
	cam_run_start_timer = cam_run_start + 5000;
	App->player->winSound = false;
}