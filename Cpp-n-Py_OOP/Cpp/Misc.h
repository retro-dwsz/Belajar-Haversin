// Misc.h
#pragma once

#include "Includes.h"

// Platform Detection
#if defined(_WIN32) || defined(WIN32)
    #define OS_WINDOWS
    #if defined(__clang__)
        #define COMPILER "Clang"
        #include <windows.h>
        #include <malloc.h>
        //! ACHTUNG: Redefine DWORD will cause warning!
        // using DWORD = unsigned int;
        
    #elif defined(_MSC_VER)
        #define FMT_HEADER_ONLY // Required for fmt in header-only mode
        #define COMPILER "MSVC"
        #include <Windows.h>
        //! ACHTUNG: Redefine DWORD will cause warning!
        // using DWORD = unsigned int;

    #else
        #define COMPILER "Unknown-Win"
        #include <windows.h>
    #endif
#elif defined(__linux__) || defined(__unix__)
    #define OS_LINUX
    #define COMPILER "Clang/GCC/Linux"
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

using str   = std::string;
using str_v = std::string_view;

namespace Misc{
    /**
     * @brief Get terminal dimensions (columns/rows) cross-platform.
     * 
     * @param COR "X" = columns, "Y" = rows, "D" = debug print
     * @param offset Optional padding
     * @return int Terminal dimension or error (-1)
     */
    int TerminalSize(const char* COR = "X", int offset = 0) {
        #ifdef OS_WINDOWS
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                std::fprintf(stderr, "Failed to retrieve console screen buffer info.\n");
                return -1;
            }
    
            int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
            if (std::strcmp(COR, "D") == 0) {
                std::printf("Columns: %d\n", columns);
                std::printf("Rows: %d\n", rows);
                return 0;
            } else if (std::strcmp(COR, "X") == 0) {
                return columns + offset;
            } else if (std::strcmp(COR, "Y") == 0) {
                return rows + offset;
            }
        #elif defined(OS_LINUX)
            struct winsize ws;
            if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0) {
                std::perror("ioctl failed");
                return -1;
            }
    
            int columns = ws.ws_col;
            int rows = ws.ws_row;
    
            if (std::strcmp(COR, "D") == 0) {
                std::printf("Columns: %d\n", columns);
                std::printf("Rows: %d\n", rows);
                return 0;
            } else if (std::strcmp(COR, "X") == 0) {
                return columns + offset;
            } else if (std::strcmp(COR, "Y") == 0) {
                return rows + offset;
            }
        #endif
    
        return -1; // Invalid option
    }

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
        int width = Misc::TerminalSize(); // Replace with TerminalSize() in real use
        int padding = (width - static_cast<int>(text.length()) - 4) / 2;

        std::string left = Repeater(filler, padding);
        std::string right = Repeater(filler, padding + (text.length() % 2));

        // std::ostringstream oss;
        // oss << left << text << right;
        
        return fmt::format("{}[{}]{}", left, text, right);
    }
};


// end Misc.h