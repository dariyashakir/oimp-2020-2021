#include <iostream>
#include <string>
#include <vector>

void Print(const std::vector<char>& array) {
    for (auto element : array) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

void Render(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        Print(row);
    }
}

struct Point {
    Point(int x, int y) : x(x), y(y) {
    }

    int x;
    int y;
};

int main() {
    std::cout << "21-01-game\n";
    std::vector<std::vector<char>> grid(10, std::vector<char>(10, '.'));
    Point player_position{0, 0};
    std::vector<Point> enemies;
    enemies.emplace_back(4, 4);
    enemies.emplace_back(4, 5);
    enemies.emplace_back(5, 4);
    enemies.emplace_back(6, 7);
    enemies.emplace_back(6, 6);

    grid[player_position.x][player_position.y] = 'p';
    for (const auto& [y, x] : enemies) {
        grid[y][x] = 'e';
    }
    Render(grid);

    while (true) {
        grid[player_position.x][player_position.y] = '.';
        for (const auto& [y, x] : enemies) {
            grid[y][x] = '.';
        }

        std::string line;
        std::getline(std::cin, line);

        if (line == "quit") {
            return 0;
        }

        if (line == "up") {
            --player_position.x;
        } else if (line == "down") {
            ++player_position.x;
        } else if (line == "left") {
            --player_position.y;
        } else if (line == "right") {
            ++player_position.y;
        }

        std::sort(enemies.begin(), enemies.end(), [&player_position](const Point& lhs, const Point& rhs) {
            const auto lhs_dist = std::abs(lhs.x - player_position.x) + std::abs(lhs.y - player_position.y);
            const auto rhs_dist = std::abs(rhs.x - player_position.x) + std::abs(rhs.y - player_position.y);
            return lhs_dist < rhs_dist;
        });

        auto& closest_enemy = enemies[0];
        const auto prev_pos = closest_enemy.x;
        if (closest_enemy.x < player_position.x) {
            ++closest_enemy.x;
        } else if (closest_enemy.x > player_position.x) {
            --closest_enemy.x;
        }
        if (prev_pos == closest_enemy.x) {
            if (closest_enemy.y < player_position.y) {
                ++closest_enemy.y;
            } else if (closest_enemy.y > player_position.y) {
                --closest_enemy.y;
            }
        }

        grid[player_position.x][player_position.y] = 'p';
        for (const auto& [y, x] : enemies) {
            grid[y][x] = 'e';
        }

        Render(grid);
    }
}
