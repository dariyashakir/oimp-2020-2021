#include "c.h"

#include <chrono>
#include <iostream>
#include <vector>

class Timer {
    using Clock = std::chrono::high_resolution_clock;
public:
    explicit Timer(std::string message)
        : message_(std::move(message))
        , start_(Clock::now()) {
    }

    ~Timer() {
        auto end = Clock::now();
        std::cout << message_ << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start_).count() << "ms\n";
    }

private:
    std::string message_;
    std::chrono::time_point<Clock> start_;
};

class Vector2D {
public:
    Vector2D() = default;

    Vector2D(int x, int y)
        : x_(x)
        , y_(y)
    {}

    Vector2D(std::pair<int, int> pair)
        : x_(pair.first)
        , y_(pair.second)
    {}

    Vector2D& operator+=(const Vector2D& rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    Vector2D operator+() const {
        return *this;
    }

    int X() const {
        return x_;
    }

    int& X() {
        return x_;
    }

private:
    int x_ = 0;
    int y_ = 0;
};

Vector2D operator+(Vector2D lhs, const Vector2D& rhs) {
    lhs += rhs;
    return lhs;
}

Vector2D operator+(int lhs, const Vector2D& rhs) {
}

Vector2D operator+(const Vector2D& rhs, int lhs) {
}

int main() {
    Vector2D x;
    const Vector2D y;
    std::cout << y.X() << '\n';

    x += y;

    auto z = x + y;
    auto u = y + x;

    auto v = std::make_pair(1, 3) + y;
}





















//template <typename T>
//void g(T t) {
//    auto b = t;
//}
//
//void G() {
//    {
//        g(C());
//    }
//    std::cout << "------------------------\n";
//
//    {
//        C c2;
//        g(c2);
//    }
//    std::cout << "------------------------\n";
//
//    {
//        C c4;
//        g(std::move(c4));
//    }
//    std::cout << "------------------------\n";
//
//    {
////        g(10);
//    }
//    std::cout << "------------------------\n";
//}
//
