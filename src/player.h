#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body2d.hpp>

namespace godot{
    class Player : public CharacterBody2D{
        GDCLASS(Player, CharacterBody2D)

    private:
        double speed;

    protected:
	    static void _bind_methods();

    public:
	    Player() : speed(1000.0) {};
	    ~Player() = default;

        void _process(double delta) override;

        double get_speed() const { return speed; }
        void set_speed(const double p_speed) { speed = p_speed * 10; }
    };
}