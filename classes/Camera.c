//
//  Camera.c
//  Source written by Justin Yu
//

#include "Camera.h"
#include <math.h>

// Constructor

Camera new_camera() {
	Camera instance = {
        // Assign method references
        .open = &camera_open,
        .close = &camera_close,
        .update = &camera_update,
        .get_width = &get_camera_width,
        .get_height = &get_camera_height,
        .get_object_count = &get_object_count,
        .get_object_area = &get_object_area,
        .get_object_center_x = &get_object_center_x,
        .get_object_center_y = &get_object_center_y
    };
    camera = instance;
    return instance;
}
