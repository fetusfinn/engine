/*
 *  vec3.h
 */
#pragma once

typedef float vec_t;

class vec3
{
public:
    
    vec_t x, y, z;
    
    vec3() { }
    vec3(vec_t x, vec_t y, vec_t z) { this->x = x; this->y = y; this->z = z; }
    
};
