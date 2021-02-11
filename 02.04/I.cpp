#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

struct Date {
    bool operator<(const Date& rhs) const {
        return std::tie(day, month, year) < std::tie(rhs.day, rhs.month, rhs.year);
    }

    int day = 0;
    int month = 0;
    int year = 0;
};

struct Student {
    bool operator<(const Student& rhs) const {
        // Сделайте по аналогии с кодом выше.
    }

    std::string name;
    std::string surname;
    Date birthday;
};

struct Applicant {
    bool operator<(const Applicant& rhs) const {
        if (score == rhs.score) {
            // Сделайте по аналогии с кодом выше.
        }
        return score > rhs.score;
    }

    int score = 0;
    Student student;
    std::vector<std::string> universities;
};

struct University {
    std::set<Student> students;
    int capacity = 0;
};

auto ReadUniversities() {
    std::unordered_map<std::string, University> universities;
    int num_universities = 0;
    std::cin >> num_universities;
    for (int i = 0; i < num_universities; ++i) {
        // Вспоминаем, что можно лаконично записать в unordered_map, использовав operator[].
    }
    return universities;
}

auto ReadApplicants() {
    int num_applicants = 0;
    std::cin >> num_applicants;
    std::vector<Applicant> applicants(num_applicants);
    for (auto& applicant : applicants) {
        // Читаем поступающего в переменную applicant.
    }
    return applicants;
}

int main() {
    auto universities = ReadUniversities();
    auto applicants = ReadApplicants();

    // Основная логика программы.
    // Гарантируется ли существование универа из списка универов студента?
    // Можем не думать и воспользоваться методом find у unordered_map.

    for (const auto& name : university_names) {
        std::cout << name;
        for (const auto& student : universities[name].students) {
            std::cout << '\t' << student.name << ' ' << student.surname;
        }
        std::cout << '\n';
    }
}
