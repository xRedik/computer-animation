#ifndef OPENGL_CONF_H
#define OPENGL_CONF_H

#include <vector>

// global variables
extern int WALL_LENGTH;

// fuction to clearing the buffer
void clear_buffer();

// function for configuring lighting
void set_source_attributes();

// function for setting material properties
void set_material_properties();

// function for disablening the lightening
void disable_lightening();

// function for reshaping the window
void reshape(int w, int h);

// function for setting the time
void timer(int value);

// initialization function to define the lookat positions and begin GL_Lines mode
void gl_init_wall(int eyeX = 30, int eyeY = 20, int eyeZ = 20);

// helper function to call the corresponding functions all at once
void draw_walls();

// the function to draw the ground
void draw_ground(float dt_ver = 0.1, float dt_hor = 0.1);

// the function to draw the left wall
void draw_left_wall(float dt_ver = 0.5, float dt_hor = 3);

// the function to draw the right wall
void draw_right_wall(float dt_ver = 0.5, float dt_hor = 3);

// the function to draw the front wall
void draw_front_wall(float dt_ver = 0.5, float dt_hor = 3);

// the function to draw the back wall
void draw_back_wall(float dt_ver = 0.5, float dt_hor = 3);

#endif