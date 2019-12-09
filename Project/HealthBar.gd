extends Control

onready var health_bar = $HealthBar

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _on_health_updated(health):
	health_bar.value = health