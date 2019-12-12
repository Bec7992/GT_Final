#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <InputEventMouseButton.hpp>
#include <TileMap.hpp>
#include <Input.hpp>
#include <chrono>
#include "ability.h"
#include "map_handler.h"
#include "health_bar.h"

namespace godot {

	class PlayerHandler : public KinematicBody2D {
		GODOT_CLASS(PlayerHandler, KinematicBody2D)

	private:
		Vector2 position = Vector2(0, 0);
		Vector2 target_pos = Vector2(0, 0);
		double time_elapsed = 0.0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		bool just_moved = false;

		Ability abil1;
		Ability abil2;
		Ability abil3;
		int ability_index = 0;
		bool ability_targeting = false;

	public:
		int tile_size = 16;
		int speed = 256;
		int health = 100;

		std::vector<BaseAI*> enemies;

		static void _register_methods();

		PlayerHandler();
		~PlayerHandler();

		void _init();
		void _ready();
		void _process(float delta);
		void _physics_process(float delta);
		void _movement_process();
		void enemy_turns();
		void _stairs_entered(Area2D* area);
		void change_health(int change);
		void recieve_ability(Ability enemy_ability);
		void death();
		void enemy_death(int index);
		void _particle_timeout();
		void _fire_pressed();
		void _ice_pressed();
		void _earth_pressed();
	};
}

#endif