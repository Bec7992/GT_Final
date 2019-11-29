#include "main_menu.h"

using namespace godot;

void MainMenu::_register_methods() {
	register_method("_init", &MainMenu::_init);
    register_method("_ready", &MainMenu::_ready);
    register_method("_process", &MainMenu::_process);
    register_method("_on_PlayMain_pressed", &MainMenu::_on_PlayMain_pressed);
    register_method("_on_QuitButton_pressed", &MainMenu::_on_QuitButton_pressed);
}

MainMenu::MainMenu() {
	Godot::print("main menu construcor");
}
MainMenu::~MainMenu() {

}

void MainMenu::_init() {

}

void MainMenu::_ready() {
	Godot::print("ready: start");
	Control* main_menu = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu) {
    	main_menu->show();
		get_tree()->set_pause(true);
    }
    //Godot::print("ready: ");

	Node* play_main = get_parent()->get_node("MainMenu/PlayMain");
	if (play_main) {
		play_main->connect("pressed", this, "_on_PlayMain_pressed");
	}

	Node* quit_main = get_parent()->get_node("MainMenu/QuitMain");
	if (quit_main) {
		quit_main->connect("pressed", this, "_on_QuitButton_pressed");
	}
}

void MainMenu::_process() {
	
}

void MainMenu::_on_PlayMain_pressed() {
	//ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
	//Ref<PackedScene> mapScene = resourceLoader->load("res://map.tscn");
	//Node* map_scene = Object::cast_to<Node>(mapScene->instance());
	//map_scene->set_name("mapScene");
	//get_parent()->add_child(map_scene);

	Control* main_menu = Object::cast_to<Control>(get_parent()->get_node("MainMenu"));
    if (main_menu) {
    	main_menu->hide();
    	get_tree()->set_pause(false);
    }
}

void MainMenu::_on_QuitButton_pressed() {
	get_tree()->quit();
}