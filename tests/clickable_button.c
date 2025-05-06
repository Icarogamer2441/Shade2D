#include <shade2d/shade2dlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    Window2D window = shade2d_init_window("Clickable Button", 800, 600);
    shade2d_set_window_fps(window, 60);

    shade2d_set_background(window, 0, 0, 0);

    shade2d_set_color(window, 255, 255, 255);

    Rectangle2D button = shade2d_rectangle(window, 100, 100, 250, 100);

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        shade2d_setup_projection(window);
        shade2d_draw_rectangle(window, button);

        if (shade2d_is_mouse_pressed_button(window, SHAD2D_MOUSE_BUTTON_LEFT, button)) {
            printf("Button pressed\n");
            shade2d_buffer_init(window); // Create a new buffer (needed to make the delay function don't stop other processes)
            button.x += 10;
            button.y += 10;
            button.width -= 20;
            button.height -= 20;
            shade2d_window_delay(window, 0.5); // 500 ms delay
            button.x -= 10;
            button.y -= 10;
            button.width += 20;
            button.height += 20;
            shade2d_buffer_destroy(window); // Destroy the buffer to don't use too much memory
        }

        shade2d_update_window(window);
    }

    shade2d_destroy_window(window);

    return 0;
}