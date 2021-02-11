#include <algorithm>
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
    explicit Timer(std::string message)
        : message_(std::move(message))
        , start_(Clock::now()) {
    }


    ~Timer() {
        auto end = Clock::now();
        std::cout << message_ << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start_).count() << "ms\n";
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
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

        assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

                assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {1};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

                assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {1, 1};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

                assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {1, 2, 3};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

        assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {1, 2, 3, 3};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

        assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }
    {
        std::vector<int> v = {1, 1, 2, 2, 3, 40};
        std::set<int> s(v.begin(), v.end());

        auto end = Unique(v.begin(), v.end());

                assert(std::distance(v.begin(), end) == s.size());
        for (auto it = v.begin(); it < end; ++it) {
            s.erase(*it);
        }
        assert(s.empty());
    }




//    std::cout << Min(1'000'000'001, 1'000'000'002) << '\n';
//    std::cout << Min(10.5f, 20.5f) << '\n';
//    std::cout << Min(10.5f, 20) << '\n';
//    std::cout << Min(10.5, 20.5) << '\n';





    std::vector<int> vector;
    auto it = std::back_inserter(vector);
    std::set<int> s;
    auto i = std::inserter(s, s.end());
    for (int el : s) {
        std::cout << el << ' ';
    }
    std::cout << " set\n";
    ++it = 10;
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




    std::multimap<int, int> m;
    m.emplace(1, 2);
    m.emplace(1, 3);
    for (auto [begin, end] = m.equal_range(1); begin != end; ++begin) {
        std::cout << begin->second << '\n';
    }


    std::vector<int> stack;

    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(5);
    std::cout << stack.front() << '\n';


    std::priority_queue<int, std::vector<int>, std::greater<>> priority_queue;
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
