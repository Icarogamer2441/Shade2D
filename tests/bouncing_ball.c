#include <shade2d/shade2dlib.h>

#define GRAVITY 9.81
#define FRICTION 0.99

int main(int argc, char *argv[]) {
    Window2D window = shade2d_init_window("Bouncing Ball", 800, 600);
    shade2d_set_window_fps(window, 60);

    shade2d_set_background(window, 0, 0, 0);

    shade2d_set_color(window, 255, 255, 255);

    Circle2D circle = shade2d_circle(window, 100, 100, 10); // Draw a circle at (100, 100) with a radius of 10

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        shade2d_setup_projection(window);
        shade2d_draw_circle(window, circle);

        circle.vely += GRAVITY; // Apply gravity to the circle updating its y velocity

        circle.y += circle.vely; // Update the circle's y position

        if (circle.y + circle.radius > shade2d_get_height(window)) {
            circle.vely = -circle.vely * FRICTION; // Apply friction to the y velocity
            circle.y = shade2d_get_height(window) - circle.radius;
        }

        shade2d_update_window(window);
    }

    shade2d_destroy_window(window);

    return 0;
}