#ifndef SHADE2D_H
#define SHADE2D_H

#include <stdbool.h>
#include <stddef.h>  // For size_t

// Window management
typedef struct {
    void* handle;
    int width;
    int height;
    const char* title;
} Window2D;

Window2D shade2d_init_window(const char* title, int width, int height);
void shade2d_destroy_window(Window2D window);
bool shade2d_is_running(Window2D window);
void shade2d_update_window(Window2D window);
int shade2d_get_width(Window2D window);
int shade2d_get_height(Window2D window);
void shade2d_set_window_fps(Window2D window, int fps);
void shade2d_clear_window(Window2D window);
void shade2d_setup_projection(Window2D window);

// Drawing
void shade2d_set_background(Window2D window, unsigned char r, unsigned char g, unsigned char b);
void shade2d_set_color(Window2D window, unsigned char r, unsigned char g, unsigned char b);

// Shapes
typedef struct {
    float x, y;
    float velx, vely;
    float mass;
    float radius;
} Circle2D;

typedef struct {
    float x, y;
    float velx, vely;
    float mass;
    float width, height;
} Rectangle2D;

Circle2D shade2d_circle(Window2D window, float x, float y, float radius);
void shade2d_draw_circle(Window2D window, Circle2D circle);
Rectangle2D shade2d_rectangle(Window2D window, float x, float y, float width, float height);
void shade2d_draw_rectangle(Window2D window, Rectangle2D rectangle);

// Input Handling
#define SHAD2D_KEY_UNKNOWN -1
#define SHAD2D_KEY_SPACE 32
#define SHAD2D_KEY_APOSTROPHE 39 /* '' */
#define SHAD2D_KEY_COMMA 44  /* , */
#define SHAD2D_KEY_MINUS 45  /* - */
#define SHAD2D_KEY_PERIOD 46 /* . */
#define SHAD2D_KEY_SLASH 47  /* / */
#define SHAD2D_KEY_0 48
#define SHAD2D_KEY_1 49
#define SHAD2D_KEY_2 50
#define SHAD2D_KEY_3 51
#define SHAD2D_KEY_4 52
#define SHAD2D_KEY_5 53
#define SHAD2D_KEY_6 54
#define SHAD2D_KEY_7 55
#define SHAD2D_KEY_8 56
#define SHAD2D_KEY_9 57
#define SHAD2D_KEY_SEMICOLON 59 /* ; */
#define SHAD2D_KEY_EQUAL 61 /* = */
#define SHAD2D_KEY_A 65
#define SHAD2D_KEY_B 66
#define SHAD2D_KEY_C 67
#define SHAD2D_KEY_D 68
#define SHAD2D_KEY_E 69
#define SHAD2D_KEY_F 70
#define SHAD2D_KEY_G 71
#define SHAD2D_KEY_H 72
#define SHAD2D_KEY_I 73
#define SHAD2D_KEY_J 74
#define SHAD2D_KEY_K 75
#define SHAD2D_KEY_L 76
#define SHAD2D_KEY_M 77
#define SHAD2D_KEY_N 78
#define SHAD2D_KEY_O 79
#define SHAD2D_KEY_P 80
#define SHAD2D_KEY_Q 81
#define SHAD2D_KEY_R 82
#define SHAD2D_KEY_S 83
#define SHAD2D_KEY_T 84
#define SHAD2D_KEY_U 85
#define SHAD2D_KEY_V 86
#define SHAD2D_KEY_W 87
#define SHAD2D_KEY_X 88
#define SHAD2D_KEY_Y 89
#define SHAD2D_KEY_Z 90
#define SHAD2D_KEY_LEFT_BRACKET 91  /* [ */
#define SHAD2D_KEY_BACKSLASH 92 /* \ */
#define SHAD2D_KEY_RIGHT_BRACKET 93 /* ] */
#define SHAD2D_KEY_GRAVE_ACCENT 96  /* ` */
#define SHAD2D_KEY_WORLD_1 161 /* non-US #1 */
#define SHAD2D_KEY_WORLD_2 162 /* non-US #2 */

/* Function keys */
#define SHAD2D_KEY_ESCAPE 256
#define SHAD2D_KEY_ENTER 257
#define SHAD2D_KEY_TAB 258
#define SHAD2D_KEY_BACKSPACE 259
#define SHAD2D_KEY_INSERT 260
#define SHAD2D_KEY_DELETE 261
#define SHAD2D_KEY_RIGHT 262
#define SHAD2D_KEY_LEFT 263
#define SHAD2D_KEY_DOWN 264
#define SHAD2D_KEY_UP 265
#define SHAD2D_KEY_PAGE_UP 266
#define SHAD2D_KEY_PAGE_DOWN 267
#define SHAD2D_KEY_HOME 268
#define SHAD2D_KEY_END 269
#define SHAD2D_KEY_CAPS_LOCK 280
#define SHAD2D_KEY_SCROLL_LOCK 281
#define SHAD2D_KEY_NUM_LOCK 282
#define SHAD2D_KEY_PRINT_SCREEN 283
#define SHAD2D_KEY_PAUSE 284
#define SHAD2D_KEY_F1 290
#define SHAD2D_KEY_F2 291
#define SHAD2D_KEY_F3 292
#define SHAD2D_KEY_F4 293
#define SHAD2D_KEY_F5 294
#define SHAD2D_KEY_F6 295
#define SHAD2D_KEY_F7 296
#define SHAD2D_KEY_F8 297
#define SHAD2D_KEY_F9 298
#define SHAD2D_KEY_F10 299
#define SHAD2D_KEY_F11 300
#define SHAD2D_KEY_F12 301
#define SHAD2D_KEY_F13 302
#define SHAD2D_KEY_F14 303
#define SHAD2D_KEY_F15 304
#define SHAD2D_KEY_F16 305
#define SHAD2D_KEY_F17 306
#define SHAD2D_KEY_F18 307
#define SHAD2D_KEY_F19 308
#define SHAD2D_KEY_F20 309
#define SHAD2D_KEY_F21 310
#define SHAD2D_KEY_F22 311
#define SHAD2D_KEY_F23 312
#define SHAD2D_KEY_F24 313
#define SHAD2D_KEY_F25 314
#define SHAD2D_KEY_KP_0 320
#define SHAD2D_KEY_KP_1 321
#define SHAD2D_KEY_KP_2 322
#define SHAD2D_KEY_KP_3 323
#define SHAD2D_KEY_KP_4 324
#define SHAD2D_KEY_KP_5 325
#define SHAD2D_KEY_KP_6 326
#define SHAD2D_KEY_KP_7 327
#define SHAD2D_KEY_KP_8 328
#define SHAD2D_KEY_KP_9 329
#define SHAD2D_KEY_KP_DECIMAL 330
#define SHAD2D_KEY_KP_DIVIDE 331
#define SHAD2D_KEY_KP_MULTIPLY 332
#define SHAD2D_KEY_KP_SUBTRACT 333
#define SHAD2D_KEY_KP_ADD 334
#define SHAD2D_KEY_KP_ENTER 335
#define SHAD2D_KEY_KP_EQUAL 336
#define SHAD2D_KEY_LEFT_SHIFT 340
#define SHAD2D_KEY_LEFT_CONTROL 341
#define SHAD2D_KEY_LEFT_ALT 342
#define SHAD2D_KEY_LEFT_SUPER 343
#define SHAD2D_KEY_RIGHT_SHIFT 344
#define SHAD2D_KEY_RIGHT_CONTROL 345
#define SHAD2D_KEY_RIGHT_ALT 346
#define SHAD2D_KEY_RIGHT_SUPER 347
#define SHAD2D_KEY_MENU 348

#define SHAD2D_KEY_LAST SHAD2D_KEY_MENU

/* Mouse buttons */
#define SHAD2D_MOUSE_BUTTON_1 0
#define SHAD2D_MOUSE_BUTTON_2 1
#define SHAD2D_MOUSE_BUTTON_3 2
#define SHAD2D_MOUSE_BUTTON_4 3
#define SHAD2D_MOUSE_BUTTON_5 4
#define SHAD2D_MOUSE_BUTTON_6 5
#define SHAD2D_MOUSE_BUTTON_7 6
#define SHAD2D_MOUSE_BUTTON_8 7
#define SHAD2D_MOUSE_BUTTON_LAST SHAD2D_MOUSE_BUTTON_8
#define SHAD2D_MOUSE_BUTTON_LEFT SHAD2D_MOUSE_BUTTON_1
#define SHAD2D_MOUSE_BUTTON_RIGHT SHAD2D_MOUSE_BUTTON_2
#define SHAD2D_MOUSE_BUTTON_MIDDLE SHAD2D_MOUSE_BUTTON_3

bool shade2d_is_key_pressed(Window2D window, int key);
bool shade2d_is_mouse_pressed_button(Window2D window, int button, Rectangle2D rectangle);
bool shade2d_is_mouse_pressed_button_circle(Window2D window, int button, Circle2D circle);

// Utility
void shade2d_buffer_init(Window2D window);
void shade2d_buffer_destroy(Window2D window);
void shade2d_window_delay(Window2D window, double seconds);

// Collision Detection
typedef enum {
    SHAD2D_RECTANGLE,
    SHAD2D_CIRCLE
} ShapeType;

typedef struct {
    ShapeType type;
    union {
        Rectangle2D rect;
        Circle2D circle;
    } obj;
} Object2D;

bool shade2d_check_collision(Object2D obj1, Object2D obj2);
void shade2d_handle_collision_rect_rect(Rectangle2D *r1, Rectangle2D *r2);
bool shade2d_check_collision_rect_circle(Rectangle2D r, Circle2D c);
bool shade2d_check_collision_circle_circle(Circle2D c1, Circle2D c2);
void shade2d_handle_collision_rect_circle(Rectangle2D *r, Circle2D *c);
void shade2d_handle_collision_circle_circle(Circle2D *c1, Circle2D *c2);

typedef unsigned int ObjectID;  // Define ObjectID as an unsigned integer

typedef struct {
    Object2D* objects;  // Array of Object2D
    size_t size;
    size_t capacity;
} ObjectList2D;

ObjectList2D shade2d_create_object_list();
void shade2d_add_object_to_list(ObjectList2D *objects, Object2D obj, ObjectID id);
size_t shade2d_get_object_list_size(ObjectList2D objects);
Object2D* shade2d_get_object_by_id(ObjectList2D objects, size_t index);  // Assuming index-based access based on usage
bool shade2d_check_collisions_object_list(ObjectList2D objects);
void shade2d_handle_collisions_object_list(ObjectList2D objects);
void shade2d_destroy_object_list(ObjectList2D objects);
void shade2d_draw_object_list(Window2D window, ObjectList2D objects);
ObjectID shade2d_create_object_id();

#endif // SHADE2D_H 