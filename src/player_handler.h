#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <InputEventMouseMotion.hpp>
#include <TileMap.hpp>
#include <Input.hpp>
#include "ability.h"

namespace godot {

	class PlayerHandler : public KinematicBody2D {
		GODOT_CLASS(PlayerHandler, KinematicBody2D)

	private:
		Vector2 position = Vector2(0, 0);
		Vector2 target_pos = Vector2(0, 0);

		Ability abil1;

	public:
		int tile_size = 16;
		int speed = 256;

		static void _register_methods();

		PlayerHandler();
		~PlayerHandler();

		void _init();
		void _ready();
		void _process(float delta);
		void _physics_process(float delta);
	};
}

#endif