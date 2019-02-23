/*
 *  vec2.h
 */
#pragma once

typedef float vec_t;

class vec2
{
public:
    
    vec_t x, y;
    
    vec2() { }
    vec2(vec_t x, vec_t y) { this->x = x; this->y = y; }
    
    vec_t length();
    vec_t delta(const vec2& vec);
    vec2  delta_vec(const vec2& vec);
    
    // operators
    vec2& operator=(const vec2& right);
    bool operator==(const vec2& right) const;
    
    friend const vec2 operator+(const vec2& left, const vec2& right);
    friend const vec2 operator-(const vec2& left, const vec2& right);
    friend const vec2 operator*(const vec2& left, const vec2& right);
    friend const vec2 operator*(const vec2& left, const float& scale);
    
    vec2& operator+=(const vec2& right);
    vec2& operator-=(const vec2& right);
    vec2& operator*=(const vec2& right);
    
    template<class T>
    inline vec2& operator*=(const T& scale)
    {
        this->x *= scale;
        this->y *= scale;
        return *this;
    }
    
    operator bool();    
};

inline vec_t vec2::length()
{
    return (x * x + y * y);
}

inline vec_t vec2::delta(const vec2& vec)
{
    vec2 delta;
    
    delta.x = this->x - vec.x;
    delta.y = this->y - vec.y;
    
    return delta.length();
}

inline vec2 vec2::delta_vec(const vec2& vec)
{
    vec2 delta;
    
    delta.x = this->x - vec.x;
    delta.y = this->y - vec.y;
    
    return delta;
}

inline vec2::operator bool()
{
    return x != 0 || y != 0;
}

inline vec2& vec2::operator=(const vec2& right)
{
    if (this != &right)
    {
        this->x = right.x;
        this->y = right.y;
    }
    
    return *this;
}

inline bool vec2::operator==(const vec2& right) const
{
    return (this->x == right.x) && (this->y == right.y);
}

inline const vec2 operator+(const vec2& left, const vec2& right)
{
    return vec2(left.x + right.x, left.y + right.y);
}

inline const vec2 operator-(const vec2& left, const vec2& right)
{
    return vec2(left.x - right.x, left.y - right.y);
}

inline const vec2 operator*(const vec2& left, const vec2& right)
{
    return vec2(left.x * right.x, left.y * right.y);
}

inline const vec2 operator*(const vec2& left, const float& scale)
{
    return vec2(left.x * scale, left.y * scale);
}

inline vec2& vec2::operator+=(const vec2& right)
{
    this->x += right.x;
    this->y += right.y;
    return *this;
}

inline vec2& vec2::operator-=(const vec2& right)
{
    this->x -= right.x;
    this->y -= right.y;
    return *this;
}

/*
inline vec2& vec2::operator*=(const vec2& right)
{
    this->x *= right.x;
    this->y *= right.y;
    return *this;
}
*/
