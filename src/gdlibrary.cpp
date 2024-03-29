#include "player_handler.h"
#include "map_handler.h"
#include "main_menu.h"
#include "base_ai.h"
#include "health_bar.h"
#include "testing.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    
    godot::register_class<godot::PlayerHandler>();
    godot::register_class<godot::MapHandler>();
    godot::register_class<godot::MainMenu>();
    godot::register_class<godot::BaseAI>();
    godot::register_class<godot::HealthBar>();
    //godot::register_class<godot::Testing>();
}