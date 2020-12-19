#include <math.h>
#include "Vector2D.h"

template <class T>
T Vector2D<T>::dot(Vector2D ot) { return this->x * ot.x + this->y * ot.y; }

template <class T>
T Vector2D<T>::cross(Vector2D ot) { return this->x * ot.y - this->y * ot.x; }

template <class T>
T Vector2D<T>::mag() { return sqrt(this->x * this->x + this->y * this->y); }

template <class T>
T Vector2D<T>::dir() { return atan2(this->y, this->x); }

template <class T>
Vector2D<T> Vector2D<T>::norm()
{
    T t = dir();
    return {cos(t), sin(t)};
}

template <class T>
T Vector2D<T>::proj(Vector2D ot) { return this->dot(ot) / ot.mag(); }

template <class T>
Vector2D<T> Vector2D<T>::perp() { return {-y, x}; }
