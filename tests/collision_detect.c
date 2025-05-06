#include <shade2d/shade2dlib.h>

#define GRAVITY 9.81
#define FRICTION 0.89

int main(int argc, char *argv[]) {
    Window2D window = shade2d_init_window("Collision Checker", 800, 600);
    shade2d_set_background(window, 0, 0, 0);
    shade2d_set_window_fps(window, 60);

    shade2d_set_color(window, 255, 255, 255);
    Rectangle2D rectangle1 = shade2d_rectangle(window, 800 - 100, 600 - 100, 100, 100); // Made rectangles smaller for better visual collision
    Rectangle2D rectangle2 = shade2d_rectangle(window, 800, 600 - 50, 50, 50); // Made rectangles smaller for better visual collision

    rectangle2.velx = 0;
    rectangle1.velx = 200;

    rectangle1.mass = 100;

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        shade2d_setup_projection(window);
        shade2d_draw_rectangle(window, rectangle1);
        shade2d_draw_rectangle(window, rectangle2);

        // Create Object2D representations for collision checking
        Object2D obj1 = {SHAD2D_RECTANGLE, {.rect = rectangle1}};
        Object2D obj2 = {SHAD2D_RECTANGLE, {.rect = rectangle2}};

        if (shade2d_check_collision(obj1, obj2)) {
            // Handle collision response
            shade2d_handle_collision_rect_rect(&rectangle1, &rectangle2);
        }

        rectangle1.vely += GRAVITY;
        rectangle2.vely += GRAVITY;

        // Update positions based on velocity
        rectangle1.x += rectangle1.velx * (1.0/60.0);
        rectangle1.y += rectangle1.vely * (1.0/60.0);
        rectangle2.x += rectangle2.velx * (1.0/60.0);
        rectangle2.y += rectangle2.vely * (1.0/60.0);

        // Bounce off window edges
        if (rectangle1.y + rectangle1.height > shade2d_get_height(window) || rectangle1.y < 0) {
            rectangle1.vely *= -1 * FRICTION;
            rectangle1.y = shade2d_get_height(window) - rectangle1.height;
        }

        if (rectangle2.y + rectangle2.height > shade2d_get_height(window) || rectangle2.y < 0) {
            rectangle2.vely *= -1 * FRICTION;
            rectangle2.y = shade2d_get_height(window) - rectangle2.height;
        }

        if (rectangle1.x + rectangle1.width > shade2d_get_width(window) || rectangle1.x < 0) {
            rectangle1.velx *= -1;
            if (rectangle1.x < 0) {
                rectangle1.x = 0;
            }
        }

        if (rectangle2.x + rectangle2.width > shade2d_get_width(window) || rectangle2.x < 0) {
            rectangle2.velx *= -1;
            if (rectangle2.x < 0) {
                rectangle2.x = 0;
            }
        }

        shade2d_update_window(window);
    }
    
    shade2d_destroy_window(window);

    return 0;
}