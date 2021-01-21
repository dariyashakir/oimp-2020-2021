#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void FastErase(std::vector<int>& vec, size_t index) {
    vec[index] = vec.back();
    vec.pop_back();
}

void Print(const std::vector<int>& array) {
    for (auto elem : array) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void Print(std::string_view str) {
    std::cout << str << '\n';
}

int main() {
    std::string str{'1', '2', '3', '4'};
    std::string_view str_view = str;

    std::cout << str.substr(2, 2) << '\n';  // Slow...
    std::cout << str_view.substr(2, 2) << '\n';  // Fast!

    Print(str_view);
}

void LookAddressChange() {
    std::vector<int> array{1, 2, 3, 4};
    const auto& ref = array[3];
    std::cout << ref << '\n';
    std::cout << &array[3] << " before address\n";

    array.push_back(5);

    std::cout << array[3] << '\n';
    std::cout << &array[3] << " after address\n";
    std::cout << ref << '\n';  // Trash
}
