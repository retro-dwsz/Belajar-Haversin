/**
 * File: Misc.hpp
 * 
 * Decorative file for terminal size and print middle
 */


#include <fmt/format.h>
#include <fmt/ranges.h>

#include <windows.h>
#include <processenv.h>

#include "Symbols.hpp"

#pragma once

namespace Misc{
    int TerminalSize(const char *SIDE = "X", int offset = 0) {
        CONSOLE_SCREEN_BUFFER_INFO CSBI;

        // Get console screen buffer info
        
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CSBI)) {
            fprintf(stderr, "Failed to retrieve console screen buffer info.\n");
            return -1; // Indicate failure
        }

        // Calculate columns and rows
        int columns = CSBI.srWindow.Right - CSBI.srWindow.Left + 1;
        int rows = CSBI.srWindow.Bottom - CSBI.srWindow.Top + 1;

        // Handle input based on SIDE
        if (strcmp(SIDE, "D") == 0) {
            fmt::print("Columns:{}d\n", columns);
            fmt::print("Rows: {}\n", rows);
            return 0; // Indicate success
        } else if (strcmp(SIDE, "X") == 0) {
            return columns + offset;
        } else if (strcmp(SIDE, "Y") == 0) {
            return rows + offset;
        } else {
            return 0; // Default return value for invalid input
        }
    }

    void printmid(std::string Text = "Title", std::string border = "-"){
        // auto TX = fmt::format("{:^{}}");
        // const auto = fmt::format("{:~^{}}", Text, TS);
        
        Text = fmt::format(" {} ", Text);

        const auto TS = Misc::TerminalSize();
        fmt::println("{:-^{}}", Text, TS);
    }
}

/* ~ end Misc.hpp ~*/
