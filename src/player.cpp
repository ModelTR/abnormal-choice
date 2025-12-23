#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods() {

    // 绑定方法

    ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
    ClassDB::bind_method(D_METHOD("get_gravity"), &Player::get_gravity);
    ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &Player::set_gravity);

    // 添加编辑器属性
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity", PROPERTY_HINT_RANGE, "0,0.98,1"), "set_gravity", "get_gravity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,100,0.1"), "set_speed", "get_speed");
}

void Player::_process(double delta){

    // 如果在编辑器中运行，则不处理输入

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
    }

    if(input->is_action_pressed("ui_left")){
        velocity.x -= 1;
    }

    if(input->is_action_pressed("ui_down")){
        velocity.y += 1;
    }

    if(input->is_action_pressed("ui_up")){
        velocity.y -= 1;
    }

    // 标准化向量，并应用速度属性
    velocity = velocity.normalized() * speed;
    // 设置父类的速度
    set_velocity(velocity);
    // 调用父类的移动方法
    move_and_slide();

}
