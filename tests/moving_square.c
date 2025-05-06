#include <shade2d/shade2dlib.h>

int main(int argc, char *argv[]) {
    Window2D window = shade2d_init_window("Moving Square", 800, 600);
    shade2d_set_window_fps(window, 60);
    
    shade2d_set_background(window, 0, 0, 0);

    shade2d_set_color(window, 255, 0, 0);

    Rectangle2D rectangle = shade2d_rectangle(window, 100, 100, 50, 50);

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        shade2d_setup_projection(window);
        shade2d_draw_rectangle(window, rectangle);

        if (shade2d_is_key_pressed(window, SHAD2D_KEY_RIGHT) || shade2d_is_key_pressed(window, SHAD2D_KEY_D)) {
            rectangle.x += 5;
        }

        if (shade2d_is_key_pressed(window, SHAD2D_KEY_LEFT) || shade2d_is_key_pressed(window, SHAD2D_KEY_A)) {
            rectangle.x -= 5;
        }

        if (shade2d_is_key_pressed(window, SHAD2D_KEY_UP) || shade2d_is_key_pressed(window, SHAD2D_KEY_W)) {
            rectangle.y -= 5;
        }

        if (shade2d_is_key_pressed(window, SHAD2D_KEY_DOWN) || shade2d_is_key_pressed(window, SHAD2D_KEY_S)) {
            rectangle.y += 5;
        }

        shade2d_update_window(window);
    }

    shade2d_destroy_window(window);

    return 0;
}
