# shade2d - A Simple 2D Game Library for C

**Note: This library is currently a work in progress and is under active development. APIs and features may change.**

`shade2d` is a lightweight 2D game library built in C, using OpenGL as its backend. It provides simple APIs for window management, drawing shapes, and handling basic game mechanics.

## Features
- Window creation and management
- Setting the window frame rate
- Clearing the window
- Drawing basic shapes (circles, rectangles)
- Drawing rectangles
- Basic input handling (keyboard)
- Basic input handling (mouse buttons)
- Utility functions (delay)
- Simple physics (e.g., collision detection)
- **Multiple Objects List:** Added support for managing a list of objects (circles and rectangles) with functions like `shade2d_create_object_list()`, `shade2d_add_object_to_list()`, `shade2d_get_object_list_size()`, `shade2d_get_object_by_id()`, `shade2d_check_collisions_object_list()`, `shade2d_handle_collisions_object_list()`, `shade2d_draw_object_list()`, and `shade2d_destroy_object_list()`. This allows for easier handling of multiple objects in simulations. Fixes include defining `ObjectID` as an unsigned integer and providing the full `ObjectList2D` struct in the header for proper compilation.
- **Input Handling:** Expanded to include mouse press detection for circles with `shade2d_is_mouse_pressed_button_circle(Window2D window, int button, Circle2D circle)`, which checks if a mouse button is pressed inside a circle.

## Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`)
- OpenGL and GLFW (for window management)
- Install dependencies on Ubuntu/Debian:
  ```bash
  sudo apt-get install libglfw3-dev libxi-dev
  ```

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Icarogamer2441/Shade2D.git
   cd shade2d
   ```
2. Compile the library:
   ```bash
   make
   ```
   This will build the `libshade2d.a` library. To build the test executables, run:
   ```bash
   make tests
   ```
   Or to build individual tests (e.g., `bouncing_ball`):
   ```bash
   make bouncing_ball
   ```
3. Install the library (optional, system-wide):
   ```bash
   sudo make install
   ```

### Compiling Programs with `shade2d`

#### Recommended Method (uses pkg-config):
```bash
gcc your_program.c -I./src -L. -lshade2d $(pkg-config --libs glfw3) -lm -o your_program
```

#### Fallback Method (manual linking):
```bash
gcc your_program.c -I./src -L. -lshade2d -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm -o your_program
```

#### With all warnings enabled:
```bash
gcc -Wall -Wextra -std=c11 your_program.c -I./src -L. -lshade2d $(pkg-config --libs glfw3) -lm -o your_program
```

**Troubleshooting:**
1. If you get `pkg-config` errors, install it:
   ```bash
   sudo apt-get install pkg-config libglfw3-dev
   ```
2. If linking fails, try the fallback method above.
3. Ensure all dependencies are installed:
   ```bash
   sudo apt-get install libglfw3-dev libxi-dev
   ```

### Window Management Functions

`Window2D shade2d_init_window(const char* title, int width, int height)`:
Initializes a new window and the graphics context.

`void shade2d_destroy_window(Window2D window)`:
Destroys the window and cleans up resources.

`bool shade2d_is_running(Window2D window)`:
Checks if the window should remain open.

`void shade2d_update_window(Window2D window)`:
Swaps the front and back buffers and processes events.

`int shade2d_get_width(Window2D window)`:
Gets the width of the window.

`int shade2d_get_height(Window2D window)`:
Gets the height of the window.

`void shade2d_set_window_fps(Window2D window, int fps)`:
Sets the target frame rate for the window (0 for unlimited, 1 for vsync).

`void shade2d_clear_window(Window2D window)`:
Clears the window using the current background color.

`void shade2d_setup_projection(Window2D window)`:
Sets up the orthographic projection for 2D rendering based on window dimensions.

### Shapes

**Circle2D**
A structure representing a circle with position, velocity, radius, and mass.

```c
typedef struct {
    float x, y;
    float velx, vely;
    float mass;
    float radius;
} Circle2D;
```

`Circle2D shade2d_circle(Window2D window, float x, float y, float radius)`:
Creates a new Circle2D instance with default mass 1.0.

`void shade2d_draw_circle(Window2D window, Circle2D circle)`:
Draws a Circle2D to the window.

**Rectangle2D**
A structure representing a rectangle with position, velocity, width, height, and mass.

```c
typedef struct {
    float x, y;
    float velx, vely;
    float mass;
    float width, height;
} Rectangle2D;
```

`Rectangle2D shade2d_rectangle(Window2D window, float x, float y, float width, float height)`:
Creates a new Rectangle2D instance with default mass 1.0.

`void shade2d_draw_rectangle(Window2D window, Rectangle2D rectangle)`:
Draws a Rectangle2D to the window.

### Input Handling

`bool shade2d_is_key_pressed(Window2D window, int key)`:
Checks if a specific keyboard key is currently pressed.

Use the `SHAD2D_KEY_` macros for key codes (e.g., `SHAD2D_KEY_RIGHT`, `SHAD2D_KEY_A`). A full list is available in `src/shade2dlib.h`.

### Collision Detection

The library provides basic collision detection capabilities using the `Object2D` struct which can represent different shapes. Currently, collision is supported between rectangles and rectangles, rectangles and circles, and circles and circles.

**Object2D**
A union type that can hold different shape structs (like `Rectangle2D` or `Circle2D`) along with an enum indicating the actual shape type.

```c
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
```

`bool shade2d_check_collision(Object2D obj1, Object2D obj2)`:
Checks if there is a collision between two `Object2D` instances. Returns `true` if a collision is detected, `false` otherwise. Supports rectangle-rectangle, rectangle-circle, and circle-circle collisions.

`bool shade2d_check_collision_rect_circle(Rectangle2D r, Circle2D c)`:
Checks for collision between a rectangle and a circle.

`bool shade2d_check_collision_circle_circle(Circle2D c1, Circle2D c2)`:
Checks for collision between two circles.

`void shade2d_handle_collision_rect_rect(Rectangle2D *r1, Rectangle2D *r2)`:
Handles the collision response between two rectangles. Implements elastic collision based on mass and includes logic to separate overlapping rectangles.

`void shade2d_handle_collision_rect_circle(Rectangle2D *r, Circle2D *c)`:
Handles the collision response between a rectangle and a circle. Implements a simplified elastic collision and separation.

`void shade2d_handle_collision_circle_circle(Circle2D *c1, Circle2D *c2)`:
Handles the collision response between two circles. Implements elastic collision based on mass and includes logic to separate overlapping circles.

### Example
```c
#include <shade2d/shade2dlib.h>

int main() {
    Window2D window = shade2d_init_window("My Game", 800, 600);
    shade2d_set_window_fps(window, 60); // Optional: Set target frame rate (0 for unlimited)

    while (shade2d_is_running(window)) {
        shade2d_clear_window(window);
        // ... game logic and drawing ...
        shade2d_update_window(window);
    }

    shade2d_destroy_window(window);
    return 0;
}
```

## Usage
See the example in `tests/multi_objs.c` for demonstrating multiple objects with gravity and collisions.

## Contributing
Pull requests are welcome! For major changes, please open an issue first.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Supported Platforms

This library is primarily developed and tested on **Linux (x86_64)**. 

While it *may* work on other operating systems and architectures that support OpenGL and GLFW, they are not officially supported or tested at this time.