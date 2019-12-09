#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include <Godot.hpp>
#include <TileMap.hpp>
#include <String.hpp>
#include <KinematicBody2D.hpp>
#include <Area2D.hpp>
#include <AStar.hpp>
#include <Array.hpp>
#include <ResourceLoader.hpp>
#include <Ref.hpp>
#include <PackedScene.hpp>
#include <math.h> // floor
#include <vector>
#include <stdlib.h> //srand, rand
#include <time.h>
#include <algorithm>
#include "base_ai.h"

//class BaseAI;

namespace godot {

	class Room {

	public:
		int x;
		int y;
		int width;
		int height;
		Vector2 center;

		Room(int x, int y, int width, int height);

		bool check_intersect(Room other);
	};

	class MapHandler : public TileMap {
		GODOT_CLASS(MapHandler, TileMap)

	private:
		std::vector<Room> rooms;

		std::vector<BaseAI*> enemies;

	public:
		Vector2 tile_size = get_cell_size();

		Vector2 map_size = Vector2(40, 40);

		int floor_level = 0;

		AStar* astar;

		bool enemy_has_died = false;

		static void _register_methods();

		MapHandler();
		~MapHandler();

		void _init();
		void _ready();
		void _process(float delta);
		void _stairs_entered(Area2D* area);
		void generate_rooms();
		void generate_paths();
		void draw_rooms();
		void make_map();
		void clear_map();
		void add_navigation();
		int id_from_cell(Vector2 cell);
		void place_enemies();
		PoolVector3Array get_cell_path(Vector2 start, Vector2 end);
		PoolVector3Array get_path_to_player(Vector2 start);
		PoolVector3Array get_path_random(Vector2 start);

		Vector2 get_player_cell();
		std::vector<BaseAI*> get_enemies();
		Vector3 get_enemy_index_at_location(Vector2 mouse_location);
		void enemy_death(Vector2 position);
	};
}

#endif