#include "map_handler.h"

using namespace godot;

Room::Room(int x, int y, int width, int height): x(x), y(y), width(width), height(height) {
	center = Vector2(floor((x + x + width) / 2), floor((y + y + height) / 2));
}

bool Room::check_intersect(Room other) {
	if (other.x <= x + width && other.x + other.width >= x) {
		if (other.y <= y + height && other.y + other.height >= y) {
			return true;
		}
	}
	return false;
}

void MapHandler::_register_methods() {
	register_method("_process", &MapHandler::_process);
	register_method("_ready", &MapHandler::_ready);
	//register_method("_stairs_entered", &MapHandler::_stairs_entered);
}

MapHandler::MapHandler() {
}

MapHandler::~MapHandler() {
}

void MapHandler::_ready() {
	//set_cell(2, 2, 0); // 0 = grass. How to use get_tileset()->find_tile_by_name("grass")?
	//rooms.push_back(Room(0, 3, 7, 3));
	generate_rooms();
	draw_rooms();
	generate_paths();

	update_bitmask_region(Vector2(0, 0), Vector2(map_size.x, map_size.y));

	Object::cast_to<KinematicBody2D>(get_node("Player"))->set_position(Vector2(rooms[0].x * 16 + 8, rooms[0].y * 16 + 8));
	//Object::cast_to<Area2D>(get_node("Stairs"))->set_position(Vector2(rooms[rooms.size() - 1].x * 16 + 8, rooms[rooms.size() - 1].y * 16 + 8));

	//Node* stairs = get_node("Stairs");
	//if (stairs) {
	//	stairs->connect("area_entered", this, "_stairs_entered");
	//}
}

void MapHandler::_init() {

}

void MapHandler::_process(float delta) {

}

/*void MapHandler::_stairs_entered(Area2D* area) {
	Godot::print("stairs entered");
}*/

void MapHandler::generate_rooms() {
	srand(time(NULL));
	int num_rooms = rand() % (10 - 5 + 1) + 5; // rand() % (max - min + 1) + min
	Godot::print(String::num_int64(num_rooms));

	for (int i = 0; rooms.size() < num_rooms && i < num_rooms * 3; ++i) {
		//Godot::print("i = " + String::num_int64(i));
		bool intersect = false;
		int new_x = rand() % ((((int) map_size.x) - 6) + 1); // min = 0
		int new_y = rand() % ((((int) map_size.y) - 6) + 1); // min = 0
		int new_width = rand() % (12 - 4 + 1) + 4;
		int new_height = rand() % (12 - 4 + 1) + 4;

		if (new_x + new_width > map_size.x - 1)
			new_width = map_size.x - new_x - 1;
		if (new_y + new_height > map_size.y - 1)
			new_height = map_size.y - new_y - 1;

		Room new_room = Room(new_x, new_y, new_width, new_height);

		for (Room old_room : rooms) {
			intersect = new_room.check_intersect(old_room);
			if (intersect)
				break;
		}

		if (!intersect)
			rooms.push_back(new_room);
	}
}

void MapHandler::generate_paths() {
	Room old_room = rooms[0];
	Godot::print("gen_paths: start");
	for (int i = 1; i < rooms.size(); ++i) {
		int path_x = 0; // the x coord the vertical path will start from 
		int path_y = 0; // the y coord the horizontal path will start from

		Godot::print("gen_paths: loop");
		if (1) {//rand() % 2) { // generate horizontal path first
			//Godot::print("gen_paths: in if(1)");
			path_y = rand() % ((old_room.y + old_room.height - 1) - (old_room.y + 1) + 1) + (old_room.y + 1);
			path_x = rand() % ((rooms[i].x + rooms[i].width - 1) - (rooms[i].x + 1) + 1) + (rooms[i].x + 1);

			// check if no need for h path
			if (!(path_x >= old_room.x - 1 && path_x <= old_room.x + old_room.width + 1)) {
				Godot::print("gen_paths: about to draw h path");
				for (int j = std::min(old_room.x, path_x); j <= std::max(old_room.x, path_x); ++j)
					set_cell(j, path_y, 0); // draw horizontal path
			}

			// check if no need for v path
			if (!(path_y >= rooms[i].y - 1 && path_y <= rooms[i].y + rooms[i].height + 1)) {
				Godot::print("gen_paths: about to draw v paths");
				for (int j = std::min(rooms[i].y, path_y); j <= std::max(rooms[i].y, path_y); ++j)
					set_cell(path_x, j, 0); // draw vertical path
			}
		}
		else { // generate vertical path first
			path_y = rand() % ((rooms[i].y + rooms[i].height - 1) - (rooms[i].y + 1) + 1) + (rooms[i].y + 1);
			path_x = rand() % ((old_room.x + old_room.width - 1) - (old_room.x + 1) + 1) + (old_room.x + 1);
		}

		old_room = rooms[i];
	}
}

void MapHandler::draw_rooms() {

	for (Room room : rooms) {
		for (int i = room.x; i < room.x + room.width; ++i) {
			for (int j = room.y; j < room.y + room.height; ++j) {
				set_cell(i, j, 0);
			}
		}
	}

}