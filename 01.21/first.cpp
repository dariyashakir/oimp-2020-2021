#include <cassert>
#include <iostream>
#include <random>

using namespace std;

//int main() {
//    uint64_t k, sum = 0;
//    cin >> k;
//    while (k > 0) {
//        sum += k % 10;
//        k /= 10;
//    }
//    cout << sum << '\n';
//}

/*
 * Настройка WSL
 * Настройка clion
 * Включение санитайзеров
 */

int64_t TrueArithm(int n) {
    int64_t sum = 0;
    for (int number = 1; number <= n; ++number) {
        sum += number;
    }
    return sum;
}

int64_t Arithm(int64_t n) {
    return n * (n + 1) / 2;
}

void UnitTest() {
    {
        int n = 3;
        assert(Arithm(n) == TrueArithm(n));
    }
    {
        int n = 10;
        assert(Arithm(n) == TrueArithm(n));
    }
    {
        int n = 20;
        assert(Arithm(n) == TrueArithm(n));
    }
}

void StressTest() {
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 100000);

    for (int test = 0; test < 1000; ++test) {
        int n = dis(gen);
        assert(Arithm(n) == TrueArithm(n));
    }
}

int main() {
    UnitTest();
    StressTest();
}
