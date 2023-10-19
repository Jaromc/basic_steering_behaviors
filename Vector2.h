#pragma once

#include <math.h>

template<class T>
class Vector2
{
   public:
      Vector2():x(0), y(0){}
      Vector2(T _x, T _y):x(_x), y(_y){}

      template<class T>
      float dot(const Vector2<T> &b) const
      {
         return (x * b.x) + (y * b.y);
      }

      float length() const
      {
         return sqrt((x * x) + (y * y));
      }

      float lengthSq() const
      {
         return (x * x) + (y * y);
      }

      Vector2<T> getNormalise() const
      {
         Vector2<T> n;

         float len = length();
         if (len == 0)
            return n;

         n.x = x / len;
         n.y = y / len;
         return n;
      }

      Vector2<T> operator+(const Vector2<T> &b)const
      {
         return Vector2<T>(x + b.x,y + b.y);
      }

		Vector2<T> operator-(const Vector2<T> &b)const
      {
         return Vector2<T>(x - b.x, y - b.y);
      }

		bool operator==(const Vector2<T> &b)const
      {
         return ((x == b.x) && (y == b.y));
      }

      bool operator!=(const Vector2<T> &b)const
      {
         return ((x != b.x) || (y != b.y));
      }

		Vector2<T> operator*(const Vector2<T> &b)const
      {
         return Vector2<T>(x*b.x, y*b.y);
      }

      Vector2<T>& operator+=(const Vector2<T> &b)
      {
         x += b.x;
         y += b.y;
         return *this;
      }

		Vector2<T>& operator-=(const Vector2<T> &b)
      {
         x -= b.x;
         y -= b.y;
         return *this;
      }

      Vector2<T>& operator*=(const Vector2<T> &b)
      {
         x *= b.x;
         y *= b.y;
         return *this;
      }

		Vector2<T>& operator*(float f)
      {
         x *= f;
         y *= f;
         return *this;
      }

   T x;
   T y;
};

typedef Vector2<float> Vector2f;