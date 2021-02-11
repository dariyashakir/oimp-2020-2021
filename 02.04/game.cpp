#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>

char GetKeyPressed() {
    char ch = 0;
    struct termios oldSettings, newSettings;

    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);

    fd_set set;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 1000;

    FD_ZERO(&set);
    FD_SET(fileno(stdin), &set);

    int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);

    if (res > 0) {
        read(fileno(stdin), &ch, 1);
    }

    tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
    return ch;
}

constexpr size_t GRID_SIZE = 20;
constexpr char EMPTY = ' ';

void Print(const std::vector<char>& array) {
    for (auto element : array) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

struct Point {
    Point() = default;

    Point(int x, int y) : x(x), y(y) {
    }

    int x;
    int y;
};

struct Missile {
    Point position;
    Point direction;
};

bool Inside(const Point& point) {
    return point.x >= 0 && point.x < static_cast<int>(GRID_SIZE)
        && point.y >= 0 && point.y < static_cast<int>(GRID_SIZE);
}

using Grid = std::vector<std::vector<char>>;

struct Box {
    Point top_left;
    int width;
    int height;

    void Draw(Grid& grid) const {
        const int x = top_left.x;
        const int y = top_left.y;
        grid[x][y] = '+';
        grid[x + height][y] = '+';
        grid[x][y + width] = '+';
        grid[x + height][y + width] = '+';

        for (int i = x + 1; i < x + height; ++i) {
            grid[i][y] = '|';
            grid[i][y + width] = '|';
        }
        for (int i = y + 1; i < y + width; ++i) {
            grid[x][i] = '-';
            grid[x + height][i] = '-';
        }
    }
};

void Render(
    std::vector<std::vector<char>>& grid,
    const Point& player_position,
    const std::vector<Point>& enemies,
    const std::vector<Missile>& missiles) {
    grid[player_position.x][player_position.y] = 'p';
    for (const auto& [x, y] : enemies) {
        grid[x][y] = 'e';
    }
    for (const auto& [pos, _] : missiles) {
        if (Inside(pos)) {
            grid[pos.x][pos.y] = 'o';
        }
    }

    Box box{{5, 5}, 3, 5};
    box.Draw(grid);

    for (const auto& row : grid) {
        Print(row);
    }

    std::cout << "\033[" + std::to_string(GRID_SIZE) + "A\r";
    std::cout.flush();
}

void Clear(
        std::vector<std::vector<char>>& grid,
        const Point& player_position,
        const std::vector<Point>& enemies,
        std::vector<Missile>& missiles) {
    grid[player_position.x][player_position.y] = EMPTY;
    for (const auto& [x, y] : enemies) {
        grid[x][y] = EMPTY;
    }

    std::vector<Missile> alive_missiles;
    alive_missiles.reserve(missiles.size());
    for (const auto& [pos, dir] : missiles) {
        if (Inside(pos) && grid[pos.x][pos.y] ) {
            grid[pos.x][pos.y] = EMPTY;
            alive_missiles.push_back(Missile{pos, dir});
        }
    }
    missiles = std::move(alive_missiles);
}

int Distance(const Point& lhs, const Point& rhs) {
    return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y);
}

Point operator+(Point lhs, const Point& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

int main() {
    std::cout << "04-02-game\n";
    std::vector<std::vector<char>> grid(GRID_SIZE, std::vector<char>(GRID_SIZE, EMPTY));
    Point player_position{0, 0};
    std::vector<Point> enemies;
    enemies.emplace_back(4, 4);
    enemies.emplace_back(4, 5);
    enemies.emplace_back(5, 4);
    enemies.emplace_back(6, 7);
    enemies.emplace_back(6, 6);

    size_t turn = 0;

    const Point BOT = {1, 0};
    const Point TOP = {-1, 0};
    const Point LEFT = {0, -1};
    const Point RIGHT = {0, 1};
    Point player_direction = BOT;

    std::vector<Missile> missiles;
    missiles.reserve(1000);

    std::unordered_map<char, std::function<void()>> handlers;
    handlers.emplace('w', [&]() {
        --player_position.x;
        player_direction = TOP;
    });
    handlers.emplace('s', [&]() {
        ++player_position.x;
        player_direction = BOT;
    });
    handlers.emplace('a', [&]() {
        --player_position.y;
        player_direction = LEFT;
    });
    handlers.emplace('d', [&]() {
        ++player_position.y;
        player_direction = RIGHT;
    });
    handlers.emplace('f', [&]() {
        auto& missile = missiles.emplace_back();
        missile.position = player_position;
        missile.direction = player_direction;
    });

    Render(grid, player_position, enemies, missiles);

    while (true) {
        Clear(grid, player_position, enemies, missiles);

        char ch = 0;
        if ((ch = GetKeyPressed())) {
            if (ch == 'o') {
                break;
            }
            if (handlers.contains(ch)) {
                handlers[ch]();
            }
        }

        if (turn % 500 == 0 && !enemies.empty()) {
            auto& closest_enemy = *std::min_element(
                enemies.begin(),
                enemies.end(),
                [&player_position](const Point& lhs, const Point& rhs) {
                    return Distance(lhs, player_position) < Distance(rhs, player_position);
                }
            );

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
        }

        if (turn % 100 == 0) {
            for (auto& [pos, dir] : missiles) {
                pos = pos + dir;
            }
        }

        Render(grid, player_position, enemies, missiles);

        std::vector<Point> alive_enemies;
        alive_enemies.reserve(enemies.size());
        for (const auto [x, y] : enemies) {
            if (grid[x][y] == 'e') {
                alive_enemies.emplace_back(x, y);
            }
        }
        enemies = std::move(alive_enemies);

        ++turn;
    }
}
