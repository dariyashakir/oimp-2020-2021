#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <class T>
T Min(T a, T b) {
    if (a > b) {
        return b;
    }
    return a;
}

// Windows + shift + s
// ctrl + shift + prtScn

template <class Iterator, class T>
Iterator Find(Iterator first, Iterator last, T value) {
    for (; first != last; ++first) {
        if (*first == value) {
            break;
        }
    }
    return first;
}

class Timer {
    using Clock = std::chrono::high_resolution_clock;
public:
    Timer(std::string message)
        : message_(std::move(message))
        , start_(Clock::now())
    {
    }

    ~Timer() {
        auto end = Clock::now();
        std::cout << message_ << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count() << "ms\n";
    }

private:
    std::string message_;
    std::chrono::time_point<Clock> start_;
};

// {1, 1, 2, 2, 3} ---> {1, 2, 3, ...}
template <class Iterator>
Iterator Unique(Iterator first, Iterator last) {
    if (first == last) {
        return first;
    }

    auto unique = first;

    while (++first != last) {
        if (!(*first == *unique)) {
            *(++unique) = std::move(*first);
        }
    }

    return ++unique;
}

int main() {
    {
        std::vector<int> v = {1, 1, 2, 2, 3};
        auto cpy = v;

        auto end = Unique(v.begin(), v.end());
        auto first = v.begin();

        auto end_cpy = std::unique(cpy.begin(), cpy.end());
        auto first_cpy = cpy.begin();

        while (first < end && first_cpy < end_cpy) {
            assert(*first == *first_cpy);
            ++first;
            ++first_cpy;
        }
        assert(first == end);
        assert(first_cpy == end_cpy);
    }
    {
        std::vector<int> v = {1, 2, 2, 2, 3};
        auto cpy = v;
        auto end = Unique(v.begin(), v.end());
        auto end_cpy = std::unique(cpy.begin(), cpy.end());
        auto first = v.begin();
        auto first_cpy = cpy.begin();

        while (first < end && first_cpy < end_cpy) {
            assert(*first == *first_cpy);
            ++first;
            ++first_cpy;
        }
        assert(first == end);
        assert(first_cpy == end_cpy);
    }
    {
        std::vector<int> v = {};
        auto cpy = v;
        auto end = Unique(v.begin(), v.end());
        auto end_cpy = std::unique(cpy.begin(), cpy.end());
        auto first = v.begin();
        auto first_cpy = cpy.begin();

        while (first < end && first_cpy < end_cpy) {
            assert(*first == *first_cpy);
            ++first;
            ++first_cpy;
        }
        assert(first == end);
        assert(first_cpy == end_cpy);
    }
    {
        std::vector<int> v = {1, 1, 1};
        auto cpy = v;
        auto end = Unique(v.begin(), v.end());
        auto end_cpy = std::unique(cpy.begin(), cpy.end());
        auto first = v.begin();
        auto first_cpy = cpy.begin();

        while (first < end && first_cpy < end_cpy) {
            assert(*first == *first_cpy);
            ++first;
            ++first_cpy;
        }
        assert(first == end);
        assert(first_cpy == end_cpy);
    }
    {
        std::vector<int> v = {1};
        auto cpy = v;
        auto end = Unique(v.begin(), v.end());
        auto end_cpy = std::unique(cpy.begin(), cpy.end());
        auto first = v.begin();
        auto first_cpy = cpy.begin();

        while (first < end && first_cpy < end_cpy) {
            assert(*first == *first_cpy);
            ++first;
            ++first_cpy;
        }
        assert(first == end);
        assert(first_cpy == end_cpy);
    }











    Min(static_cast<double>(2000), 2000.0);

    std::vector<int> vector;
    auto it = std::back_inserter(vector);
    *it = 10;
    std::cout << vector.back() << '\n';

    std::cout << "Find has found? " << (Find(vector.begin(), vector.end(), 10) != vector.end()) << '\n';

    std::cout << "std::find has found? " << (std::find(vector.begin(), vector.end(), 10) != vector.end()) << '\n';

    std::map<int, int> map{
        {1, 2},
        {1000000, 3},
    };

    std::cout << "Find has found? " << (Find(map.begin(), map.end(), std::pair<const int, int>{1, 2}) != map.end()) << '\n';

    std::cout << "std::find has found? " << (std::find(map.begin(), map.end(), std::pair<const int, int>{1, 2}) != map.end()) << '\n';

    const size_t SIZE = 1'000;
    std::vector<int> to_find(SIZE);
    std::iota(to_find.begin(), to_find.end(), 0);
    for (size_t i = 0; i < SIZE; i += 2) {
        map.try_emplace(i, 0);
    }
    {
        Timer timer("std::find");
        for (auto el : to_find) {
            auto a = std::find(map.begin(), map.end(), std::pair<const int, int>{el, 0});
            (void) a;
        }
    }
    // std::cout: std::find 123ms\n
    {
        Timer timer("map::find");
        for (auto el : to_find) {
            auto a = map.find(el);
            (void) a;
        }
    }





    *it = 100;
    *it = 100;
    *it = 100;
    *it = 150;
    *it = 200;
    *it = 300;

    // {10, 100, 100, 100, 150, 200, 300}
    std::cout << *std::lower_bound(vector.begin(), vector.end(), 100) << '\n';
    std::cout << *std::lower_bound(vector.begin(), vector.end(), 101) << '\n';

    std::cout << *std::upper_bound(vector.begin(), vector.end(), 100) << '\n';
    std::cout << *std::upper_bound(vector.begin(), vector.end(), 101) << '\n';






    std::vector<int> stack;

    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(5);
    std::cout << stack.front() << '\n';


    std::priority_queue<int, std::deque<int>, std::greater<>> priority_queue;
    priority_queue.push(10);
    priority_queue.push(20);
    priority_queue.push(5);
    std::cout << priority_queue.top() << " heap\n";

    std::cout << "Erased " << std::erase(vector, 100) << " hundreds\n";
    for (int el : vector) {
        std::cout << el << ' ';
    }
    std::cout << '\n';
}
