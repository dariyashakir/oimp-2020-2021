#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Student {
    Student(std::string name, std::string surname)
        : name(std::move(name))
        , surname(std::move(surname)) {
    }

    bool operator==(const Student& rhs) const {
        return name == rhs.name && surname == rhs.surname;
    }

    std::string name;
    std::string surname;
};

namespace std {
    template <>
    struct hash<Student> {
        std::size_t operator()(const Student& s) const {
            std::hash<std::string> hash_fn;
            return hash_fn(s.name + ' ' + s.surname);
        }
    };
}

int main() {
    std::unordered_map<Student, std::vector<int>> scores;
    int num_students = 0;
    std::cin >> num_students;

    for (int i = 0; i < num_students; ++i) {
        std::string name, surname;
        int score;
        std::cin >> name >> surname >> score;
        Student student(name, surname);

        scores.try_emplace(student).first->second.push_back(score);
    }

    for (const auto& [student, score_arr] : scores) {
        std::cout << student.name << ' ' << student.surname << ' ';
        for (auto score : score_arr) {
            std::cout << score << ' ';
        }
        std::cout << '\n';
    }
}

int B() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::unordered_set<int> numbers;
    int number;
    while (std::cin >> number) {
        if (numbers.find(number) == numbers.end()) {
            std::cout << "NO\n";
            numbers.insert(number);  // или emplace
        } else {
            std::cout << "YES\n";
        }
    }

    return 0;
}
