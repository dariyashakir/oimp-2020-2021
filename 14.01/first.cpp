#include <iostream>
#include <limits>

int RandomNumber(bool flag) {
    int number;
    if (flag) {
        number = 1234;
    }
    return number;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

//    uint32_t number = 0b11111111111111111111111111111111;
////    [-2^(n - 1), 2^(n-1) - 1]
//    std::cout << number + 1 << '\n';
//    std::cout << "\n\n\n\n\n\n";

//    int arr[7];
//    std::cout << arr[10] << '\n';

//    std::cout << RandomNumber(false) << '\n';

//    uint32_t max = 0xffffffff;
//    std::cout << max << '\n';
//    std::cout << max + 1 << '\n';

//    const int32_t MAX = std::numeric_limits<int32_t>::max();
    std::cout << std::numeric_limits<uint32_t>::max() << '\n';  // A bug is somewhere in this file

    return 0;
}
