#ifndef TESTING_H
#define TESTING_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <SceneTree.hpp>
#include <InputEventMouseMotion.hpp>
#include <TileMap.hpp>
#include <Input.hpp>
#include <chrono>
#include "ability.h"

namespace godot {

	class Testing : public KinematicBody2D {
		GODOT_CLASS(Testing, KinematicBody2D)

	private:
		Vector2 position = Vector2(0, 0);
		Vector2 target_pos = Vector2(0, 0);
		double time_elapsed = 0.0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		bool just_moved = false;

		Ability abil1;

	public:
		int tile_size = 16;
		int speed = 256;

		static void _register_methods();

		Testing();
		~Testing();

		void _init();
		void _ready();
		void _process(float delta);
		void _physics_process(float delta);
		void _movement_process();
	};
}

#endif