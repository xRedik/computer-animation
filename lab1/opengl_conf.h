#ifndef OPENGL_CONF_H
#define OPENGL_CONF_H

#include <vector>

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

// function for applying the rotation transformation in one function call in render function instead of three
void glRotate(const std::vector<float> &orientation);

#endif