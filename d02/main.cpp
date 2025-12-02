#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#define COMMA 44

typedef struct {
    long long first;
    long long second;
} Pair;

const static std::string input = "17330-35281,9967849351-9967954114,880610-895941,942-1466,117855-209809,9427633930-9427769294,1-14,311209-533855,53851-100089,104-215,33317911-33385573,42384572-42481566,43-81,87864705-87898981,258952-303177,451399530-451565394,6464564339-6464748782,1493-2439,9941196-10054232,2994-8275,6275169-6423883,20-41,384-896,2525238272-2525279908,8884-16221,968909030-969019005,686256-831649,942986-986697,1437387916-1437426347,8897636-9031809,16048379-16225280";


Pair seperate(std::string_view sv) {
    Pair p = {0};
    std::string num1, num2;

    int pos = sv.find("-");
    num1 = sv.substr(0, pos);
    num2 = sv.substr((pos+1), sv.length());
    p.first = std::stoll(num1);
    p.second = std::stoll(num2);
    return p;
}

// For part-2
bool is_repeated(std::string s) {
    int len = s.length();

    for (int pattern_len = 1; pattern_len <= len / 2; ++pattern_len) {
        if (len % pattern_len != 0) continue;

        std::string pattern = s.substr(0, pattern_len);
        std::string reconstructed = "";

        int repeats = len / pattern_len;
        for (int i = 0; i < repeats; ++i) {
            reconstructed += pattern;
        }

        if (reconstructed == s) return true;
    }

    return false;
}

bool is_repeated_twice(std::string s) {
    if (s.length() % 2 != 0) return false;
    int half = s.length() / 2;

    for (int i = 0; i < half; ++i) {
        if (s[i] != s[i + half]) return false;  // Compare first half with second half
    }
    return true;
}

int main()
{

    long long int answer = 0;
    std::vector<std::string> range;
    std::string temp_word = "";

    for (const auto &i : input) {
        if ((i^COMMA) == 0) {
            range.push_back(temp_word);
            temp_word = "";
        } else {
            temp_word += i;
        }
    }
    if (!temp_word.empty()) range.push_back(temp_word);

    for (const auto &i : range)
    {
        Pair p = seperate(i);
            for (long long i = p.first; i <= p.second; ++i)
            {
                std::string s = std::to_string(i);
                if (is_repeated(s))
                {
                    answer += i;
                }
            }
        }
    std::cout << answer << "\n";
    }
