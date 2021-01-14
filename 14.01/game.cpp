#include <iostream>
#include <string>
#include <utility>
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

int main() {
    std::vector<std::vector<char>> grid(10, std::vector<char>(10, '.'));
    Render(grid);

    std::pair<int, int> playerPosition(0, 0);
    std::vector<std::pair<int, int>> enemies;
    enemies.emplace_back(3, 3);
    enemies.emplace_back(6, 7);

    while (true) {
        grid[playerPosition.first][playerPosition.second] = '.';

        std::string line;
        std::getline(std::cin, line);

        if (line == "quit") {
            return 0;
        }

        if (line.starts_with("Move")) {
            if (line.ends_with("up")) {
                --playerPosition.first;
            } else if (line.ends_with("down")) {
                ++playerPosition.first;
            } else if (line.ends_with("left")) {
                --playerPosition.second;
            } else if (line.ends_with("right")) {
                ++playerPosition.second;
            }
        }

        grid[playerPosition.first][playerPosition.second] = 'p';
        for (const auto& [y, x] : enemies) {
            grid[y][x] = 'e';
        }
        Render(grid);
    }
}
