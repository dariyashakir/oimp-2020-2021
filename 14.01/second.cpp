#include <cmath>
#include <iostream>
#include <vector>

void FastErase(std::vector<int>& array, size_t index) {
    array[index] = array.back();
    array.pop_back();
}

void Print(const std::vector<int>& array) {
    for (auto elem : array) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

// Задача: сумма 1 и 3 степеней первых n натуральных чисел

uint64_t CalculateSum(int n, int degree) {
    uint64_t sum = 0;
    for (int number = 1; number <= n; ++number) {
        sum += std::pow(number, degree);
    }
    return sum;
}

int main() {
    for (int n = 1; n < 1000; ++n) {
        std::cout << CalculateSum(n, 1) << ' ' << CalculateSum(n, 3) << '\n';
    }

    // Отступление про чтение слов и строк.
    std::string word;
    while (std::cin >> word) {
        std::cout << word << '\n';
    }

    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << '\n';
    }
}
