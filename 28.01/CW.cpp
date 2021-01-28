#include <cassert>

#include <string>
#include <vector>

bool CheckAntiDiagonalSymmetry(const std::vector<std::vector<int>>& matrix) {
    const auto size = matrix.size();
    for (size_t row = 0; row < size; ++row) {
        for (size_t col = 0; col < size - row; ++col) {
            if (matrix[row][col] != matrix[size - col - 1][size - row - 1]) {
                return false;
            }
        }
    }
    return true;
}

#include <string>
#include <vector>

std::string Join(const std::vector<std::string>& tokens, char delimiter) {
    std::string result;
    for (const auto& token : tokens) {
        result += token;
        result += delimiter;
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

#include <string>
#include <vector>

std::string CommonPrefix(const std::vector<std::string>& words) {
    if (words.empty()) {
        return "";
    }

    auto find_lcp = [](std::string_view first, std::string_view second) {
        size_t prefix_len = 0;
        while (prefix_len < first.size() &&
                prefix_len < second.size() &&
                first[prefix_len] == second[prefix_len]) {
            ++prefix_len;
        }
        return first.substr(0, prefix_len);
    };

    std::string_view prefix = words[0];
    for (size_t i = 1; i < words.size(); ++i) {
        prefix = find_lcp(words[i], prefix);
    }
    return std::string(prefix);
}















void UnitTest() {
    {
        std::vector<std::string> words{
            "apple",
            "apricot",
            "application",
        };
        std::string answer = "ap";
        assert(CommonPrefix(words) == answer);
    }
    {
        std::vector<std::string> words{
            "aple",
            "appricot",
            "application",
        };
        std::string answer = "ap";
        assert(CommonPrefix(words) == answer);
    }
    {
        std::vector<std::string> words{
            "",
            "apricot",
            "application",
        };
        std::string answer = "";
        assert(CommonPrefix(words) == answer);
    }
    {
        std::vector<std::string> words{
            "apple",
            "apricot",
            "",
        };
        std::string answer = "";
        assert(CommonPrefix(words) == answer);
    }
    {
        std::vector<std::string> words{
            "apple",
            "a",
            "application",
        };
        std::string answer = "a";
        assert(CommonPrefix(words) == answer);
    }





    {
        std::vector<std::string> tokens{
            "What",
            "Is",
            "my",
            "name?",
        };
        char delimiter = ' ';
        std::string result = "What Is my name?";
        assert(Join(tokens, delimiter) == result);
    }
    {
        std::vector<std::string> tokens{
        };
        char delimiter = ' ';
        std::string result = "";
        assert(Join(tokens, delimiter) == result);
    }
    {
        std::vector<std::string> tokens{
            "What",
        };
        char delimiter = ' ';
        std::string result = "What";
        assert(Join(tokens, delimiter) == result);
    }









    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {5, 3, 2},
            {4, 5, 1},
        };
        assert(CheckAntiDiagonalSymmetry(matrix));
    }
    {
        std::vector<std::vector<int>> matrix{
        };
        assert(CheckAntiDiagonalSymmetry(matrix));
    }
    {
        std::vector<std::vector<int>> matrix{
            {1, 2, 3},
            {1, 3, 2},
            {4, 5, 1},
        };
        assert(!CheckAntiDiagonalSymmetry(matrix));
    }
    {
        std::vector<std::vector<int>> matrix{
            {1},
        };
        assert(CheckAntiDiagonalSymmetry(matrix));
    }
    {
        std::vector<std::vector<int>> matrix{
            {1, 2},
            {4, 5},
        };
        assert(!CheckAntiDiagonalSymmetry(matrix));
    }
    {
        std::vector<std::vector<int>> matrix{
            {1, 2},
            {4, 1},
        };
        assert(CheckAntiDiagonalSymmetry(matrix));
    }
}

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int Caesar() {
    std::string str;
    std::cin >> str;
    int shift;
    std::cin >> shift;

    const int LETTERS = 26;
    shift %= LETTERS;

    auto decode = [shift](char letter) {
        int case_shift;
        if (std::isupper(letter)) {
            case_shift = 'A';
        } else {
            case_shift = 'a';
        }
        return (letter - case_shift + LETTERS - shift) % LETTERS + case_shift;
    };

    std::transform(str.begin(), str.end(), str.begin(), decode);

    std::cout << str << '\n';
    return 0;
}

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int Files() {
    int num_files = 0;
    std::cin >> num_files;
    std::vector<std::vector<std::string>> files(num_files);
    size_t max_lines = 0;
    for (int file_index = 0; file_index < num_files; ++file_index) {
        size_t num_lines = 0;
        std::cin >> num_lines;
        if (num_lines > max_lines) {
            max_lines = num_lines;
        }
        files[file_index].reserve(num_lines);
        for (size_t line_index = 0; line_index < num_lines; ++line_index) {
            std::string line;
            std::cin >> line;
            files[file_index].push_back(std::move(line));
        }
    }

    for (size_t line_index = 0; line_index < max_lines; ++line_index) {
        for (int file_index = 0; file_index < num_files; ++file_index) {
            if (line_index < files[file_index].size()) {
                std::cout << files[file_index][line_index];
            }
            if (file_index + 1 < num_files) {
                std::cout << '\t';
            }
        }
        std::cout << '\n';
    }
    return 0;
}

int main() {
    UnitTest();
}
