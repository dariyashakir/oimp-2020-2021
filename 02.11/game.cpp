#include "getch.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>

const int GRID_SIZE = 10;

void Print(const std::vector<char>& array) {
    for (auto element : array) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

struct Point {
    constexpr Point() = default;

    constexpr Point(int x, int y) : x(x), y(y) {
    }

    Point operator+(Point other) const {
        other.x += x;
        other.y += y;
        return other;
    }

    int x;
    int y;
};

constexpr Point DOWN = {1, 0};
constexpr Point UP = {-1, 0};
constexpr Point LEFT = {1, 0};
constexpr Point RIGHT = {1, 0};

class Game {
public:
    Game()
        : grid_(GRID_SIZE, std::vector<char>(GRID_SIZE, ' '))
        , player_{{0, 0}, {1, 0}}
        , handlers_(std::numeric_limits<char>::max())
    {
        grid_[player_.position.x][player_.position.y] = 'p';

        SpawnEnemies();

        for (const auto& [pos, _] : enemies_) {
            grid_[pos.x][pos.y] = 'e';
        }
        Render();
        InitHandlers();
    }

    void Move() {
//        if (turn % 5000 == 0) {
//            auto& closest_enemy = enemies[0];
//            const auto prev_pos = closest_enemy.x;
//            if (closest_enemy.x < player_position.x) {
//                ++closest_enemy.x;
//            } else if (closest_enemy.x > player_position.x) {
//                --closest_enemy.x;
//            }
//            if (prev_pos == closest_enemy.x) {
//                if (closest_enemy.y < player_position.y) {
//                    ++closest_enemy.y;
//                } else if (closest_enemy.y > player_position.y) {
//                    --closest_enemy.y;
//                }
//            }
//        }
    }

    void Clear() {
        grid_[player_.position.x][player_.position.y] = '.';
        for (const auto& [y, x] : enemies_) {
            grid_[y][x] = '.';
        }
    }

    void InitHandlers() {
        handlers_['w'] = [this]() {
            --player_.position.x;
        };
        handlers_['a'] = [this]() {
            --player_.position.y;
        };
        handlers_['s'] = [this]() {
            ++player_.position.x;
        };
        handlers_['d'] = [this]() {
            ++player_.position.y;
        };

        handlers_['f'] = [this]() {
//            CreateMissile();
        };
    }

    void Render() {
        for (const auto& row : grid_) {
            Print(row);
        }

        std::cout << "\033[" + std::to_string(GRID_SIZE) + "A\r";
        std::cout.flush();
    }

    void SpawnEnemies() {
//        enemies_.emplace_back(4, 4);
//        enemies_.emplace_back(4, 5);
//        enemies_.emplace_back(5, 4);
//        enemies_.emplace_back(6, 7);
//        enemies_.emplace_back(6, 6);
    }

    struct Person {
        Person() = default;

        explicit Person(Point position)
            : Person(position, DOWN) {
        }

        explicit Person(Point position, Point direction)
            : position(position)
            , direction(direction) {
        }

        Point position;
        Point direction;
    };

private:
    std::vector<std::vector<char>> grid_;
    Person player_;
    std::vector<Person> enemies_;

    std::vector<std::function<void()>> handlers_;
};

int main() {
    std::cout << "21-01-game\n";
}
