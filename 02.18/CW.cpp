#include <iostream>
#include <set>
#include <unordered_map>

struct Ngram {
    template <class Str>
    Ngram(Str&& str, int count) : ngram(std::forward<Str>(str)), count(count) {
    }

    bool operator<(const Ngram& rhs) const {
        return std::tie(rhs.count, ngram) < std::tie(count, rhs.ngram);
    }

    std::string_view ngram;
    int count = 0;
};

void Ngrams() {
    std::unordered_map<std::string, int> counters;

    int num_words;
    size_t N;
    std::cin >> num_words >> N;
    for (int i = 0; i < num_words; ++i) {
        std::string word;
        std::cin >> word;
        for (size_t index = 0; index + N <= word.size(); ++index) {
            ++counters[word.substr(index, N)];
        }
    }
    std::set<Ngram> set;
    for (const auto& [ngram, count] : counters) {
        set.emplace(ngram, count);
    }

    for (const auto& [ngram, count] : set) {
        std::cout << ngram << " - " << count << '\n';
    }
}

void Ngrams2() {
    std::unordered_map<std::string, int> counters;

    int num_words;
    size_t N;
    std::cin >> num_words >> N;
    for (int i = 0; i < num_words; ++i) {
        std::string word;
        std::cin >> word;
        ++counters[word];
    }

    std::unordered_map<std::string_view, int> ngrams;
    for (const auto& [word, count] : counters) {
        for (size_t index = 0; index + N <= word.size(); ++index) {
            ngrams[std::string_view(word).substr(index, N)] += count;
        }
    }

    std::set<Ngram> set;
    for (const auto& [ngram, count] : ngrams) {
        set.emplace(ngram, count);
    }

    for (const auto& [ngram, count] : set) {
        std::cout << ngram << " - " << count << '\n';
    }
}

template<typename Iterator, typename T, typename BinaryOp>
T Reduce(Iterator first, Iterator last, T init, BinaryOp op) {
    while (first != last) {
        init = op(*first, init);
        ++first;
    }
    return init;
}

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

void TestReduce() {
    {
        std::vector<int> v{1, 2, 3, 4, 5};
        auto my = Reduce(v.begin(), v.end(), 0, [](int a, int b) {
            return a + b;
        });
        assert(my == std::reduce(v.begin(), v.end(), 0));
    }
    {
        std::vector<int> v;
        auto my = Reduce(v.begin(), v.end(), 0, [](int a, int b) {
            return a + b;
        });
        assert(my == std::reduce(v.begin(), v.end(), 0));
    }
}

#include <cstddef>

template <typename ItA, typename ItB>
size_t CountSubsegments(ItA a_first, ItA a_last, ItB b_first, ItB b_last) {
    int count = 0;
    auto prev = a_first;
    while (prev != a_last) {
        auto b_cur = b_first;
        while (a_first != a_last && b_cur != b_last && *a_first == *b_cur) {
            ++a_first;
            ++b_cur;
        }
        if (b_cur != b_last) {
            break;
        }
        ++count;
        ++prev;
        a_first = prev;
    }
    return count;
}

#include <algorithm>
#include <cstddef>

template <typename Iter1, typename Iter2>
size_t CountSubsegments2(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2) {
    size_t result = 0;
    for (auto iter = first1; iter != last1;) {
        iter = std::search(iter, last1, first2, last2);
        if (iter != last1) {
            ++result;
            ++iter;
        }
    }
    return result;
}

void TestCountSubsegments() {
    {
        std::vector<int> v{1, 2, 3, 4, 1, 1, 2, 2, 1, 2};
        std::set<int> s{1, 2};
        assert(3 == CountSubsegments(v.begin(), v.end(), s.begin(), s.end()));
    }
    {
        std::vector<int> v{1, 2};
        std::set<int> s{1, 2};
        assert(1 == CountSubsegments(v.begin(), v.end(), s.begin(), s.end()));
    }
    {
        std::vector<int> v{1, 1, 1, 1, 1, 1, 1, 1, 1};
        std::set<int> s{1, 2};
        assert(0 == CountSubsegments(v.begin(), v.end(), s.begin(), s.end()));
    }
    {
        std::string a = "aaa";
        std::string b = "aa";
        assert(2 == CountSubsegments(a.begin(), a.end(), b.begin(), b.end()));
    }
    {
        std::string a = "aaa";
        std::string b = "aa";
        assert(2 == CountSubsegments2(a.begin(), a.end(), b.begin(), b.end()));
    }
}

#include <iostream>
#include <vector>

void MakeTrainBad() {
    const int MAX = 1'000'000;
    std::vector<int> train(MAX * 3);
    int left = train.size() / 2;
    int right = train.size() / 2;
    auto clear = [&]() {
        left = train.size() / 2;
        right = train.size() / 2;
    };

    std::string command;
    while (std::cin >> command) {
        int number = 0;
        std::cin >> number;

        if (command == "+left") {
            --left;
            train[left] = number;
        } else if (command == "+right") {
            train[right] = number;
            ++right;
        } else if (command == "-left") {
            if (number > right - left) {
                clear();
            } else {
                left += number;
            }
        } else {
            if (number > right - left) {
                clear();
            } else {
                right -= number;
            }
        }
    }

    for (; left < right; ++left) {
        std::cout << train[left];
        if (left + 1 < right) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

#include <deque>
#include <iostream>

void MakeTrain() {
    std::deque<int> train;
    int left = train.size() / 2;
    int right = train.size() / 2;
    auto clear = [&]() {
        left = train.size() / 2;
        right = train.size() / 2;
    };

    std::string command;
    while (std::cin >> command) {
        int number = 0;
        std::cin >> number;

        if (command.starts_with('+')) {
            if (command.ends_with("left")) {
                if (left == 0) {
                    train.push_front(number);
                    ++right;
                } else {
                    --left;
                    train[left] = number;
                }
            } else {
                if (right == static_cast<int>(train.size())) {
                    train.push_back(number);
                } else {
                    train[right] = number;
                }
                ++right;
            }
        } else {
            if (command.ends_with("left")) {
                if (number > right - left) {
                    clear();
                } else {
                    left += number;
                }
            } else {
                if (number > right - left) {
                    clear();
                } else {
                    right -= number;
                }
            }
        }
    }

    for (; left < right; ++left) {
        std::cout << train[left];
        if (left + 1 < right) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
}

int main() {
    std::vector v{1, 2, 3, 4};
    for (size_t i = 0; i < v.size(); ++i) {
        v.pop_back();
    }
    std::cout << v.size() << " --- size\n";
}
