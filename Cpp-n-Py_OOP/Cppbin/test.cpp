#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <fmt/core.h>

enum Unit {
    Degree,
    Radian
};

// Repeater Overloads
std::string Repeater(char ch, int repetitions = 1) {
    return std::string(repetitions, ch);
}

std::string Repeater(const std::string& str, int repetitions = 1) {
    std::ostringstream oss;
    for (int i = 0; i < repetitions; ++i) {
        oss << str;
    }
    return oss.str();
}

std::string Repeater(const char* cstr, int repetitions = 1) {
    return Repeater(std::string(cstr), repetitions);
}

// Centered Print Function
std::string PrintMid(const std::string& text = "Hello!", char filler = '-', int offset = 2) {
    int width = 80; // Replace with TerminalSize() in real use
    int padding = (width - static_cast<int>(text.length()) - 4) / 2;

    std::string left = Repeater(filler, padding);
    std::string right = Repeater(filler, padding + (text.length() % 2));

    return fmt::format("{}[{}]{}", left, text, right);
}

// Demo
int main() {
    std::cout << PrintMid("Welcome!") << '\n';
    std::cout << PrintMid("C++ String Magic", '=') << '\n';
    std::cout << PrintMid("Formatted", '*') << '\n';


    std::cout << Unit::Degree;
    std::cout << Unit::Radian;
    // fmt::println();
}