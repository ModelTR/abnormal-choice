#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>


using namespace godot;

void Player::_bind_methods() {

    // 绑定方法

    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
    ClassDB::bind_method(D_METHOD("get_gravity"), &Player::get_gravity);
    ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &Player::set_gravity);
    ClassDB::bind_method(D_METHOD("get_direction"), &Player::get_direction);
    ClassDB::bind_method(D_METHOD("set_direction", "direction"), &Player::set_direction);
    ClassDB::bind_method(D_METHOD("get_texture"), &Player::get_texture);
    ClassDB::bind_method(D_METHOD("set_texture", "texture"), &Player::set_texture);

    // 添加编辑器属性
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity", PROPERTY_HINT_RANGE, "0,0.98,1"), "set_gravity", "get_gravity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,100,0.1"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "direction", PROPERTY_HINT_RANGE, "0,1,1"), "set_direction", "get_direction");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
}

// Player::Player() : speed(1000.0), direction(Direction::RIGHT) {
//     get_node<Sprite2D>("Player")->set_texture(sprite);
// }

void Player::_process(double delta){




    if(Engine::get_singleton()->is_editor_hint()){   
        return;
    }

    // 初始化速度向量

    Vector2 velocity(0, 0);
    

    velocity.y += gravity;  // 应用重力
    

    // 获取输入流

    Input* input = Input::get_singleton();

    if(input->is_action_pressed("ui_right")){
        velocity.x += 1;
        direction = Vector2{1,0};
    }

    if(input->is_action_pressed("ui_left")){
        velocity.x -= 1;
        direction = Vector2{-1,0};
    }

    if(input->is_action_pressed("ui_down")){
        velocity.y += 1;
    }

    if(input->is_action_pressed("ui_up")){
        velocity.y -= 1;
    }
    if (!sprite)
    {
        sprite = cast_to<Sprite2D>(get_node_or_null("Sprite2D"));
        if (!sprite)
        {
            sprite = memnew(Sprite2D);
            sprite->set_name("Sprite2D");
            add_child(sprite);
            sprite->set_owner(this);
            if (texture_ref.is_valid()) sprite->set_texture(texture_ref);
        }
    }
    if (sprite)
    {
        auto scale = sprite->get_scale();
        if (scale.x != direction.x)
        {
            sprite->set_scale(Vector2(direction.x, scale.y));
        }
    }
    // 标准化向量，并应用速度属性
    velocity = velocity.normalized() * speed;
    // 设置父类的速度
    set_velocity(velocity);
    // 调用父类的移动方法
    move_and_slide();

}
