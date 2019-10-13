#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

struct comma_is_space : std::ctype<char> {
    comma_is_space() : std::ctype<char>(get_table()) {}

    static mask const *get_table() {
        static mask rc[table_size];
        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

template<class First>
std::tuple<First> ReadCSVLine(std::istream &input) {
    First first;
    input >> first;
    return std::make_tuple(first);
}

template<class First, class Second, class ...Other>
std::tuple<First, Second, Other...> ReadCSVLine(std::istream &input) {
    First first;
    input >> first;
    return std::tuple_cat(std::make_tuple(first), ReadCSVLine<Second, Other...>(input));
}

template<class ...All>
std::vector<std::tuple<All...>> ReadCSV(const std::string &filename) {
    std::ifstream fin(filename, std::ifstream::in);
    fin.imbue(std::locale(fin.getloc(), new comma_is_space));
    std::vector<std::tuple<All...>> result;
    while (!fin.eof()) {
        result.push_back(ReadCSVLine<All...>(fin));
    }
    return result;
}

class Price {
public:
    Price() = default;

    double value;
    std::string currency;

    friend std::istream &operator>>(std::istream &is, Price &price) {
        std::string str;
        is >> str;
        std::istringstream inputstring(str);
        std::string value_str;
        std::string currency_str;
        std::getline(inputstring, value_str, '|');
        std::getline(inputstring, currency_str);
        price.value = std::stod(value_str);
        price.currency = currency_str;
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Price &price) {
        os << price.value << "|" << price.currency;
        return os;
    }
};

int main() {
    auto result = ReadCSV<int, std::string, Price>("input.csv");
    for (auto &line : result) {
        std::cout << std::get<0>(line) << "; " << std::get<1>(line) << "; " << std::get<2>(line) << std::endl;
    }
    // 1; three; 1|USD
    // 2; six; 12.34|EUR
    // 4; twelve; 11.9|GBP
    // 8; twenty four; 0.3|RUB
    return 0;
}