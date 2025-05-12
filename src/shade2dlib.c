#include "shade2dlib.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define ObjectID if not already defined (assuming it's an unsigned int for IDs)
typedef unsigned int ObjectID;  // This should ideally be in the header, but adding here for completeness if missing

Window2D shade2d_init_window(const char* title, int width, int height) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    
    Window2D window;
    window.width = width;
    window.height = height;
    window.title = title;
    
    window.handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window.handle) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window.handle);
    
    // Initialize OpenGL settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    return window;
}

void shade2d_destroy_window(Window2D window) {
    glfwDestroyWindow(window.handle);
    glfwTerminate();
}

bool shade2d_is_running(Window2D window) {
    return !glfwWindowShouldClose(window.handle);
}

void shade2d_update_window(Window2D window) {
    glfwSwapBuffers(window.handle);
    glfwPollEvents();
}

int shade2d_get_width(Window2D window) {
    return window.width;
}

int shade2d_get_height(Window2D window) {
    return window.height;
}

void shade2d_set_window_fps(Window2D window, int fps) {
    (void)window; // Mark as unused
    if (fps <= 0) {
        glfwSwapInterval(0); // Unlimited frame rate
    } else {
        // The swap interval is the number of vertical blanks to wait
        // 1 for vsync (capped at monitor refresh rate)
        // 0 for no vsync
        // > 1 for slower than monitor refresh rate (not commonly used)
        // Here we assume fps is the desired frame rate, so we use 1 for vsync
        glfwSwapInterval(1);
    }
}

void shade2d_set_background(Window2D window, unsigned char r, unsigned char g, unsigned char b) {
    (void)window; // Mark as unused
    glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void shade2d_set_color(Window2D window, unsigned char r, unsigned char g, unsigned char b) {
    (void)window; // Mark as unused
    glColor3f(r/255.0f, g/255.0f, b/255.0f);
}

Circle2D shade2d_circle(Window2D window, float x, float y, float radius) {
    (void)window; // Mark as unused
    Circle2D circle;
    circle.x = x;
    circle.y = y;
    circle.velx = 0;
    circle.vely = 0;
    circle.mass = 1.0f; // Default mass
    circle.radius = radius;
    return circle;
}

void shade2d_draw_circle(Window2D window, Circle2D circle) {
    (void)window; // Mark as unused
    
    // Set up orthographic projection
    int width = shade2d_get_width(window);
    int height = shade2d_get_height(window);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Draw the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(circle.x, circle.y); // Center
    
    int segments = 32;
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * M_PI / segments;
        glVertex2f(
            circle.x + (cosf(angle) * circle.radius),
            circle.y + (sinf(angle) * circle.radius)
        );
    }
    
    glEnd();
    
    // Reset color to white after drawing
    glColor3f(1.0f, 1.0f, 1.0f);
}

void shade2d_clear_window(Window2D window) {
    (void)window; // Mark as unused
    glClear(GL_COLOR_BUFFER_BIT);
}

void shade2d_setup_projection(Window2D window) {
    // Set up orthographic projection
    int width = shade2d_get_width(window);
    int height = shade2d_get_height(window);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Rectangle2D shade2d_rectangle(Window2D window, float x, float y, float width, float height) {
    (void)window; // Mark as unused
    Rectangle2D rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.velx = 0;
    rectangle.vely = 0;
    rectangle.mass = 1.0f; // Default mass
    rectangle.width = width;
    rectangle.height = height;
    return rectangle;
}

void shade2d_draw_rectangle(Window2D window, Rectangle2D rectangle) {
    (void)window; // Mark as unused
    
    // Draw the rectangle
    glBegin(GL_QUADS);
    glVertex2f(rectangle.x, rectangle.y);
    glVertex2f(rectangle.x + rectangle.width, rectangle.y);
    glVertex2f(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
    glVertex2f(rectangle.x, rectangle.y + rectangle.height);
    glEnd();
}

bool shade2d_is_key_pressed(Window2D window, int key) {
    if (window.handle) {
        return glfwGetKey(window.handle, key) == GLFW_PRESS;
    }
    return false;
}

bool shade2d_is_mouse_pressed_button(Window2D window, int button, Rectangle2D rectangle) {
    if (window.handle) {
        double xpos, ypos;
        glfwGetCursorPos(window.handle, &xpos, &ypos);

        bool is_inside = (xpos >= rectangle.x && xpos <= rectangle.x + rectangle.width &&
                          ypos >= rectangle.y && ypos <= rectangle.y + rectangle.height);

        return is_inside && (glfwGetMouseButton(window.handle, button) == GLFW_PRESS);
    }
    return false;
}

bool shade2d_is_mouse_pressed_button_circle(Window2D window, int button, Circle2D circle) {
    if (window.handle) {
        double mouseX, mouseY;
        glfwGetCursorPos(window.handle, &mouseX, &mouseY);
        
        // Calculate distance from mouse to circle center
        float dx = mouseX - circle.x;
        float dy = mouseY - circle.y;
        float distance = sqrtf(dx * dx + dy * dy);
        
        bool isInside = distance <= circle.radius;
        bool buttonPressed = glfwGetMouseButton(window.handle, button) == GLFW_PRESS;
        
        return isInside && buttonPressed;
    }
    return false;
}

// Utility Functions
void shade2d_buffer_init(Window2D window) {
    (void)window; // Mark as unused
    // Dummy implementation - buffer concept is unclear in this context
    // Might be related to event handling during delays or a misunderstanding
    // of how rendering buffers work in immediate mode OpenGL.
    // No action needed for basic functionality.
}

void shade2d_buffer_destroy(Window2D window) {
    (void)window; // Mark as unused
    // Dummy implementation - see shade2d_buffer_init
    // No action needed for basic functionality.
}

void shade2d_window_delay(Window2D window, double seconds) {
    if (window.handle) {
        double start_time = glfwGetTime();
        while (glfwGetTime() - start_time < seconds) {
            glfwPollEvents(); // Poll events to keep the window responsive
        }
    }
}

bool shade2d_check_collision_rect_rect(Rectangle2D r1, Rectangle2D r2) {
    // AABB collision detection
    return (r1.x < r2.x + r2.width &&
            r1.x + r1.width > r2.x &&
            r1.y < r2.y + r2.height &&
            r1.y + r1.height > r2.y);
}

bool shade2d_check_collision_rect_circle(Rectangle2D r, Circle2D c) {
    // Find the closest point to the circle within the rectangle
    float closestX = fmax(r.x, fmin(c.x, r.x + r.width));
    float closestY = fmax(r.y, fmin(c.y, r.y + r.height));

    // Calculate the distance between the circle's center and this closest point
    float distanceX = c.x - closestX;
    float distanceY = c.y - closestY;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    // If the distance is less than the square of the circle's radius, an overlap occurs
    return distanceSquared < (c.radius * c.radius);
}

bool shade2d_check_collision_circle_circle(Circle2D c1, Circle2D c2) {
    // Calculate the distance between the centers of the two circles
    float distanceX = c1.x - c2.x;
    float distanceY = c1.y - c2.y;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    // Calculate the sum of the radii
    float radiusSum = c1.radius + c2.radius;

    // If the distance is less than the sum of the radii, an overlap occurs
    return distanceSquared < (radiusSum * radiusSum);
}

void shade2d_handle_collision_rect_rect(Rectangle2D *r1, Rectangle2D *r2) {
    // Calculate new velocities based on elastic collision and mass
    float m1 = r1->mass;
    float m2 = r2->mass;
    float v1x = r1->velx;
    float v1y = r1->vely;
    float v2x = r2->velx;
    float v2y = r2->vely;

    // Calculate final velocities using 1D elastic collision formula
    float v1fx = ((m1 - m2) * v1x + (2 * m2) * v2x) / (m1 + m2);
    float v1fy = ((m1 - m2) * v1y + (2 * m2) * v2y) / (m1 + m2);
    float v2fx = ((2 * m1) * v1x + (m2 - m1) * v2x) / (m1 + m2);
    float v2fy = ((2 * m1) * v1y + (m2 - m1) * v2y) / (m1 + m2);

    // Update velocities
    r1->velx = v1fx;
    r1->vely = v1fy;
    r2->velx = v2fx;
    r2->vely = v2fy;

    // Separate overlapping rectangles
    float overlapX = fmin(r1->x + r1->width - r2->x, r2->x + r2->width - r1->x);
    float overlapY = fmin(r1->y + r1->height - r2->y, r2->y + r2->height - r1->y);

    // Calculate the direction of separation
    float sep_dir_x = 0;
    if (r1->x < r2->x) sep_dir_x = -1; else sep_dir_x = 1;
    float sep_dir_y = 0;
    if (r1->y < r2->y) sep_dir_y = -1; else sep_dir_y = 1;

    if (overlapX < overlapY) {
        // Separate along the x-axis
        r1->x += sep_dir_x * overlapX / 2.0f;
        r2->x -= sep_dir_x * overlapX / 2.0f;
    } else {
        // Separate along the y-axis
        r1->y += sep_dir_y * overlapY / 2.0f;
        r2->y -= sep_dir_y * overlapY / 2.0f;
    }
}

void shade2d_handle_collision_rect_circle(Rectangle2D *r, Circle2D *c) {
    // Simple elastic collision response (based on 1D collision for now)
    // This is a simplified approach for demonstration and can be improved.
    
    // Calculate the direction of collision from rectangle to circle
    float normalX = c->x - (r->x + r->width / 2.0f);
    float normalY = c->y - (r->y + r->height / 2.0f);
    
    // Normalize the collision normal (avoid division by zero)
    float magnitude = sqrtf(normalX * normalX + normalY * normalY);
    if (magnitude > 0) {
        normalX /= magnitude;
        normalY /= magnitude;
    }

    // Calculate relative velocity
    float relativeVelX = c->velx - r->velx;
    float relativeVelY = c->vely - r->vely;

    // Calculate velocity along the collision normal
    float velocityAlongNormal = relativeVelX * normalX + relativeVelY * normalY;

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0) return;

    // Calculate impulse scalar using elastic collision formula
    float m1 = r->mass;
    float m2 = c->mass;
    float impulseScalar = -(1.0f + 1.0f) * velocityAlongNormal / (1.0f/m1 + 1.0f/m2);

    // Apply impulse to velocities
    r->velx -= impulseScalar * normalX / m1;
    r->vely -= impulseScalar * normalY / m1;
    c->velx += impulseScalar * normalX / m2;
    c->vely += impulseScalar * normalY / m2;

    // Separation (basic - could be improved for more accurate separation)
    float overlap = sqrtf((c->x - (r->x + r->width/2.0f))*(c->x - (r->x + r->width/2.0f)) + (c->y - (r->y + r->height/2.0f))*(c->y - (r->y + r->height/2.0f))) - c->radius;
    if (overlap < 0) {
        r->x += normalX * overlap / 2.0f;
        r->y += normalY * overlap / 2.0f;
        c->x -= normalX * overlap / 2.0f;
        c->y -= normalY * overlap / 2.0f;
    }
}

void shade2d_handle_collision_circle_circle(Circle2D *c1, Circle2D *c2) {
    // Calculate the distance between the centers
    float distanceX = c2->x - c1->x;
    float distanceY = c2->y - c1->y;
    float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

    // Normalize the distance vector (collision normal)
    float normalX = distanceX / distance;
    float normalY = distanceY / distance;

    // Calculate relative velocity
    float relativeVelX = c2->velx - c1->velx;
    float relativeVelY = c2->vely - c1->vely;

    // Calculate velocity along the collision normal
    float velocityAlongNormal = relativeVelX * normalX + relativeVelY * normalY;

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0) return;

    // Calculate impulse scalar using elastic collision formula
    float m1 = c1->mass;
    float m2 = c2->mass;
    float impulseScalar = -(1.0f + 1.0f) * velocityAlongNormal / (1.0f/m1 + 1.0f/m2);

    // Apply impulse to velocities
    c1->velx -= impulseScalar * normalX / m1;
    c1->vely -= impulseScalar * normalY / m1;
    c2->velx += impulseScalar * normalX / m2;
    c2->vely += impulseScalar * normalY / m2;

    // Separation (push circles apart)
    float overlap = (c1->radius + c2->radius) - distance;
    if (overlap > 0) {
        c1->x -= normalX * overlap / 2.0f;
        c1->y -= normalY * overlap / 2.0f;
        c2->x += normalX * overlap / 2.0f;
        c2->y += normalY * overlap / 2.0f;
    }
}

bool shade2d_check_collision(Object2D obj1, Object2D obj2) {
    if (obj1.type == SHAD2D_RECTANGLE && obj2.type == SHAD2D_RECTANGLE) {
        return shade2d_check_collision_rect_rect(obj1.obj.rect, obj2.obj.rect);
    } else if (obj1.type == SHAD2D_RECTANGLE && obj2.type == SHAD2D_CIRCLE) {
        return shade2d_check_collision_rect_circle(obj1.obj.rect, obj2.obj.circle);
    } else if (obj1.type == SHAD2D_CIRCLE && obj2.type == SHAD2D_RECTANGLE) {
        // Check the collision in reverse order
        return shade2d_check_collision_rect_circle(obj2.obj.rect, obj1.obj.circle);
    } else if (obj1.type == SHAD2D_CIRCLE && obj2.type == SHAD2D_CIRCLE) {
        return shade2d_check_collision_circle_circle(obj1.obj.circle, obj2.obj.circle);
    }
    // TODO: Handle other combinations if needed
    return false;
}

// Implementation of ObjectList2D functions

ObjectList2D shade2d_create_object_list() {
    ObjectList2D list;
    list.objects = malloc(10 * sizeof(Object2D));  // Initial capacity of 10
    list.size = 0;
    list.capacity = 10;
    return list;
}

void shade2d_add_object_to_list(ObjectList2D *objects, Object2D obj, ObjectID id) {
    (void)id;  // Acknowledge unused parameter to suppress warning
    if (objects->size >= objects->capacity) {
        objects->capacity *= 2;
        objects->objects = realloc(objects->objects, objects->capacity * sizeof(Object2D));
    }
    objects->objects[objects->size] = obj;  // Store the object
    objects->size++;
    // In a full implementation, you might associate the ID here, e.g., in a separate array
}

size_t shade2d_get_object_list_size(ObjectList2D objects) {
    return objects.size;
}

Object2D* shade2d_get_object_by_id(ObjectList2D objects, size_t index) {  // Treating index as ID for now
    if (index < objects.size) {
        return &objects.objects[index];
    }
    return NULL;  // Or handle error
}

bool shade2d_check_collisions_object_list(ObjectList2D objects) {
    for (size_t i = 0; i < objects.size; i++) {
        for (size_t j = i + 1; j < objects.size; j++) {
            if (shade2d_check_collision(objects.objects[i], objects.objects[j])) {
                return true;  // Collision found
            }
        }
    }
    return false;
}

void shade2d_handle_collisions_object_list(ObjectList2D objects) {
    for (size_t i = 0; i < objects.size; i++) {
        for (size_t j = i + 1; j < objects.size; j++) {
            if (shade2d_check_collision(objects.objects[i], objects.objects[j])) {
                // Handle based on types
                if (objects.objects[i].type == SHAD2D_RECTANGLE && objects.objects[j].type == SHAD2D_RECTANGLE) {
                    shade2d_handle_collision_rect_rect(&objects.objects[i].obj.rect, &objects.objects[j].obj.rect);
                } else if (objects.objects[i].type == SHAD2D_RECTANGLE && objects.objects[j].type == SHAD2D_CIRCLE) {
                    shade2d_handle_collision_rect_circle(&objects.objects[i].obj.rect, &objects.objects[j].obj.circle);
                } else if (objects.objects[i].type == SHAD2D_CIRCLE && objects.objects[j].type == SHAD2D_RECTANGLE) {
                    shade2d_handle_collision_rect_circle(&objects.objects[j].obj.rect, &objects.objects[i].obj.circle);
                } else if (objects.objects[i].type == SHAD2D_CIRCLE && objects.objects[j].type == SHAD2D_CIRCLE) {
                    shade2d_handle_collision_circle_circle(&objects.objects[i].obj.circle, &objects.objects[j].obj.circle);
                }
            }
        }
    }
}

void shade2d_draw_object_list(Window2D window, ObjectList2D objects) {
    for (size_t i = 0; i < objects.size; i++) {
        if (objects.objects[i].type == SHAD2D_CIRCLE) {
            shade2d_draw_circle(window, objects.objects[i].obj.circle);
        } else if (objects.objects[i].type == SHAD2D_RECTANGLE) {
            shade2d_draw_rectangle(window, objects.objects[i].obj.rect);
        }
    }
}

void shade2d_destroy_object_list(ObjectList2D objects) {
    free(objects.objects);  // Free the allocated array
}

ObjectID shade2d_create_object_id() {
    static ObjectID next_id = 0;  // Static to maintain state
    return next_id++;
} 