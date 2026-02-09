#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/Ref.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot{
    class Player : public CharacterBody2D{
        GDCLASS(Player, CharacterBody2D)

    private:
        double speed;
        double gravity;
        Vector2 direction;
        Ref<Texture2D> texture_ref;
        Sprite2D* sprite;

    protected:
	    static void _bind_methods();

    public:
	    Player() : speed(1000.0), direction(1,0), sprite(nullptr) {};
	    ~Player() = default;

        void _process(double delta) override;

        double get_speed() const { return speed; }
        void set_speed(const double p_speed) { speed = p_speed * 10; }
        
        double get_gravity() const { return gravity; }
        void set_gravity(const float p_gravity) { gravity = p_gravity; }

        const Vector2& get_direction() const { return direction; }
        void set_direction(const Vector2& p_direction) { direction = p_direction; }

        void set_texture(const Ref<Texture2D>& _texture_ref)
        {
            texture_ref = _texture_ref;
            if (sprite)
            {
                sprite->set_texture(texture_ref);
            }
        };
        Ref<Texture2D> get_texture() const { return texture_ref; };
    };
}