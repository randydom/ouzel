// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_MATH_RECT_HPP
#define OUZEL_MATH_RECT_HPP

#include <algorithm>
#include "math/Vector2.hpp"
#include "math/Size2.hpp"

namespace ouzel
{
    template<class T> class Rect final
    {
    public:
        Vector2<T> position;
        Size2<T> size;

        Rect()
        {
        }

        Rect(T width, T height):
            size(width, height)
        {
        }

        Rect(T x, T y, T width, T height):
            position(x, y), size(width, height)
        {
        }

        Rect(const Vector2<T>& initPosition, T width, T height):
            position(initPosition), size(width, height)
        {
        }

        Rect(const Vector2<T>& initPosition, const Size2<T>& initSize):
            position(initPosition), size(initSize)
        {
        }

        Rect(const Rect& copy):
            position(copy.position), size(copy.size)
        {
        }

        Rect& operator=(const Rect& other)
        {
            position.v[0] = other.position.v[0];
            position.v[1] = other.position.v[1];
            size.v[0] = other.size.v[0];
            size.v[1] = other.size.v[1];
            return *this;
        }

        inline bool isEmpty() const
        {
            return size.isZero();
        }

        void setPosition(T x, T y)
        {
            position.v[0] = x;
            position.v[1] = y;
        }

        void setPosition(const Vector2<T>& newPosition)
        {
            position = newPosition;
        }

        T left() const
        {
            return position.v[0];
        }

        T bottom() const
        {
            return position.v[1];
        }

        T right() const
        {
            return position.v[0] + size.v[0];
        }

        T top() const
        {
            return position.v[1] + size.v[1];
        }

        Vector2<T> bottomLeft() const
        {
            return position;
        }

        Vector2<T> topRight() const
        {
            return Vector2<T>(position.v[0] + size.v[0], position.v[1] + size.v[1]);
        }

        bool containsPoint(T x, T y) const
        {
            return x >= position.v[0] && x <= (position.v[0] + size.v[0]) &&
                y >= position.v[1] && y <= (position.v[1] + size.v[1]);
        }

        bool containsPoint(const Vector2<T>& point) const
        {
            return point.v[0] >= position.v[0] && point.v[0] <= (position.v[0] + size.v[0]) &&
                point.v[1] >= position.v[1] && point.v[1] <= (position.v[1] + size.v[1]);
        }

        bool contains(T x, T y, T width, T height) const
        {
            return containsPoint(x, y) && containsPoint(x + width, y + height);
        }

        bool contains(const Rect& r) const
        {
            return contains(r.position.v[0], r.position.v[1], r.size.v[0], r.size.v[1]);
        }

        bool intersects(T x, T y, T width, T height) const
        {
            T t;
            if ((t = x - position.v[0]) > size.v[0] || -t > width)
                return false;
            if ((t = y - position.v[1]) > size.v[1] || -t > height)
                return false;
            return true;
        }

        bool intersects(const Rect& r) const
        {
            return intersects(r.position.v[0], r.position.v[1], r.size.v[0], r.size.v[1]);
        }

        static bool intersect(const Rect& r1, const Rect& r2, Rect& dst)
        {
            T xmin = std::max(r1.position.v[0], r2.position.v[0]);
            T xmax = std::min(r1.right(), r2.right());
            if (xmax > xmin)
            {
                T ymin = std::max(r1.position.v[1], r2.position.v[1]);
                T ymax = std::min(r1.bottom(), r2.bottom());
                if (ymax > ymin)
                {
                    dst.position.v[0] = xmin;
                    dst.position.v[1] = ymin;
                    dst.size.v[0] = xmax - xmin;
                    dst.size.v[1] = ymax - ymin;
                    return true;
                }
            }

            dst.position.v[0] = dst.position.v[1] = dst.size.v[0] = dst.size.v[1] = 0;
            return false;
        }

        static void combine(const Rect& r1, const Rect& r2, Rect& dst)
        {
            dst.position.v[0] = std::min(r1.position.v[0], r2.position.v[0]);
            dst.position.v[1] = std::min(r1.position.v[1], r2.position.v[1]);
            dst.size.v[0] = std::max(r1.position.v[0] + r1.size.v[0], r2.position.v[0] + r2.size.v[0]) - dst.position.v[0];
            dst.size.v[1] = std::max(r1.position.v[1] + r1.size.v[1], r2.position.v[1] + r2.size.v[1]) - dst.position.v[1];
        }

        void inflate(T horizontalAmount, T verticalAmount)
        {
            position.v[0] -= horizontalAmount;
            position.v[1] -= verticalAmount;
            size.v[0] += horizontalAmount * 2;
            size.v[1] += verticalAmount * 2;
        }

        bool operator==(const Rect& other) const
        {
            return position.v[0] == other.position.v[0] && size.v[0] == other.size.v[0] &&
                position.v[1] == other.position.v[1] && size.v[1] == other.size.v[1];
        }

        bool operator!=(const Rect& other) const
        {
            return position.v[0] != other.position.v[0] || size.v[0] != other.size.v[0] ||
                position.v[1] != other.position.v[1] || size.v[1] != other.size.v[1];
        }

        inline const Rect operator*(T scalar) const
        {
            return Rect(position.v[0] * scalar, position.v[1] * scalar,
                        size.v[0] * scalar, size.v[1] * scalar);
        }

        inline Rect& operator*=(T scalar)
        {
            position.v[0] *= scalar;
            position.v[1] *= scalar;
            size.v[0] *= scalar;
            size.v[1] *= scalar;
            return *this;
        }

        inline const Rect operator/(T scalar) const
        {
            return Rect(position.v[0] / scalar, position.v[1] / scalar,
                        size.v[0] / scalar, size.v[1] / scalar);
        }

        inline Rect& operator/=(T scalar)
        {
            position.v[0] /= scalar;
            position.v[1] /= scalar;
            size.v[0] /= scalar;
            size.v[1] /= scalar;
            return *this;
        }
    };
}

#endif // OUZEL_MATH_RECT_HPP
