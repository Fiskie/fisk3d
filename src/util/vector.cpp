#pragma once

#include <utility>

// what the fuck
#define vxs(x1, y1, x2, y2) ((x1)*(y2) - (x2)*(y1))

struct Vector3 {
    double x;
    double y;
    double z;

    Vector3 sub(Vector3 vec) {
        return { x - vec.x, y - vec.y, z - vec.z };
    }

    Vector3 add(Vector3 vec) {
        return { x + vec.x, y + vec.y, z + vec.z };
    }

    Vector3 scl(double mod) {
        return { x * mod, y * mod, z * mod };
    }

    Vector3 nor() {
        double l = len();
        return l > 0 ? Vector3{ x / l, y / l, z / l } : Vector3{0,0,0};
    }

    double len() {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    Vector3 withLen(double l) {
        return nor().scl(l);
    }

    friend Vector3 operator+(Vector3 lhs, Vector3 rhs) {
        return lhs.add(rhs);
    }

    friend Vector3 operator-(Vector3 lhs, Vector3 rhs) {
        return lhs.sub(rhs);
    }

    friend Vector3 operator*(Vector3 lhs, double val) {
        return lhs.scl(val);
    }
};

typedef std::pair<Vector3, Vector3> Edge3;

struct Vector2 {
    double x;
    double y;

    Vector2 sub(Vector2 vec) {
        return { x - vec.x, y - vec.y };
    }

    Vector2 add(Vector2 vec) {
        return { x + vec.x, y + vec.y };
    }

    Vector2 scl(double mod) {
        return { x * mod, y * mod };
    }

    Vector2 nor() {
        double l = len();
        return l > 0 ? Vector2{ x / l, y / l } : Vector2{0,0};
    }

    double len() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    Vector2 withLen(double l) {
        return nor().scl(l);
    }

    friend Vector2 operator+(Vector2 lhs, Vector2 rhs) {
        return lhs.add(rhs);
    }

    friend Vector2 operator-(Vector2 lhs, Vector2 rhs) {
        return lhs.sub(rhs);
    }

    friend Vector2 operator*(Vector2 lhs, double val) {
        return lhs.scl(val);
    }
};

typedef std::pair<Vector2, Vector2> Edge2;

// i have no idea what this does
Vector3 intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    return {
        vxs(vxs(x1,y1,x2,y2), x1-x2, vxs(x3,y3, x4,y4), x3-x4) / vxs(x1-x2, y1-y2, x3-x4, y3-y4),
        0,
        vxs(vxs(x1,y1,x2,y2), y1-y2, vxs(x3,y3, x4,y4), y3-y4) / vxs(x1-x2, y1-y2, x3-x4, y3-y4)
    };
}