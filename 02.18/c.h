#include <iostream>

class C {
public:
    C(): id(++counter) {
        std::cout << "constructor C() " << id << "\n";
    }

    explicit C(int number): id(++counter) {
        std::cout << "constructor C(int number) " << id << '\n';
    }

    C(const C& other): id(++counter) {
        std::cout << "constructor C(const C&) " << id << " " << other.id << "\n";
    }

    C(C&& other): id(++counter) {
        std::cout << "constructor C(const C&&) " << id << " " << other.id << "\n";
    }

    C& operator = (const C& other) {
        std::cout << "operator = (const C&) " << id << " " << other.id << "\n";
        return *this;
    }

    C& operator = (C&& other) {
        std::cout << "operator = (const C&&) " << id << " " << other.id << "\n";
        return *this;
    }

    ~C() {
        std::cout << "destructor C() " << id << "\n";
    }

    C& Add(int x) {
        return *this;
    }

private:
    static int counter;
    const int id;
};

int C::counter = 0;
