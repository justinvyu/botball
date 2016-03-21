//
//  Camera.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>

typedef struct Camera {
    int (*open)();
    int (*update)();
    void (*close)();

    void (*set_width)(int width);
    void (*set_height)(int height);
    int (*get_width)();
    int (*get_height)();

    // Blob tracking

    int (*get_object_count)(int channel);
    int (*get_object_area)(int channel, int object);

    int (*get_object_center_x)(int channel, int object);
    int (*get_object_center_y)(int channel, int object);
} Camera;

// constructor
extern Camera new_camera();

Camera camera; // global wallaby instance
