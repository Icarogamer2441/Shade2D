#include <shade2d/shade2dlib.h>

#define GRAVITY 1.5
#define FRICTION 0.6

int main() {
    Window2D window = shade2d_init_window("Multiple Objects", 800, 600);
    shade2d_set_background(window, 0, 0, 0);
    shade2d_set_window_fps(window, 60);

    shade2d_set_color(window, 255, 255, 255);

    ObjectList2D objects = shade2d_create_object_list();
    float px = 100;
    float py = 100;

    for (int i = 0; i < 500; i++) {
        ObjectID id = shade2d_create_object_id();
        Object2D obj = {SHAD2D_CIRCLE, .obj.circle = shade2d_circle(window, px, py, 10)};
        shade2d_add_object_to_list(&objects, obj, id);
        px += 10;
        py += 10;
        objects.objects[i].obj.circle.velx = 50;
    }

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        shade2d_setup_projection(window);
        shade2d_draw_object_list(window, objects);

        for (size_t i = 0; i < shade2d_get_object_list_size(objects); i++) {
            Object2D* obj = shade2d_get_object_by_id(objects, i);
            obj->obj.circle.vely += GRAVITY * (1 / 60.0);
            obj->obj.circle.y += obj->obj.circle.vely;
            obj->obj.circle.x += obj->obj.circle.velx;
            if (obj->obj.circle.y > 600 - obj->obj.circle.radius) {
                obj->obj.circle.vely = -obj->obj.circle.vely * FRICTION;
                obj->obj.circle.y = 600 - obj->obj.circle.radius;
            }
            if (obj->obj.circle.y < 0 + obj->obj.circle.radius) {
                obj->obj.circle.vely = -obj->obj.circle.vely * FRICTION;
                obj->obj.circle.y = 0 + obj->obj.circle.radius;
            }
            if (obj->obj.circle.x > 800 - obj->obj.circle.radius) {
                obj->obj.circle.velx = -obj->obj.circle.velx * FRICTION;
                obj->obj.circle.x = 800 - obj->obj.circle.radius;
            }
            if (obj->obj.circle.x < 0 + obj->obj.circle.radius) {
                obj->obj.circle.velx = -obj->obj.circle.velx * FRICTION;
                obj->obj.circle.x = 0 + obj->obj.circle.radius;
            }

            if (shade2d_is_mouse_pressed_button_circle(window, SHAD2D_MOUSE_BUTTON_LEFT, obj->obj.circle)) {
                obj->obj.circle.velx = 50;
                obj->obj.circle.vely = -50;
            }
        }

        if (shade2d_check_collisions_object_list(objects)) {
            shade2d_handle_collisions_object_list(objects);
        }

        if (shade2d_is_key_pressed(window, SHAD2D_KEY_ESCAPE)) {
            break;
        }

        shade2d_update_window(window);
    }

    shade2d_destroy_object_list(objects);

    shade2d_destroy_window(window);
}