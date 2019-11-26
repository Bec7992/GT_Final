#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <Godot.hpp>
#include <Control.hpp>
#include <SceneTree.hpp>
//#include <ResourceLoader.hpp>
//#include <Ref.hpp>
//#include <PackedScene.hpp>
//#include <stdlib.h>
//#include "map_handler.h"

namespace godot {

	class MainMenu : public Control {
	    GODOT_CLASS(MainMenu, Control)

	private:

	public:
	    static void _register_methods();

	    MainMenu();
	    ~MainMenu();

	    //void _ready();

	    //void _process();

	    //void _on_PlayMain_pressed();

	    //void _on_QuitButton_pressed();
	};
}

#endif