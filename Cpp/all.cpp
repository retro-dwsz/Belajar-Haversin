/* File: _Main.cpp */

#include "includes.hpp"
#include "Navigation_2D.hpp"
#include "Navigation_2D_P.hpp"

int main(){
    // Test::PrintGreek();
    // Test::PrintMiddle();
    // Test::TerminalSize();
    // Test::Macros();

    ListD SV_IPB = {-6.588457, 106.806200};
    ListD DanauIPB = {-6.559582, 106.726720};
    double_t Jarak_DEG =  Distances_2D::Distance_Deg_Plain(SV_IPB, DanauIPB);

    fmt::println(
        "~Deg\nSV IPB = {}\nDanau IPB = {}\n\n",
        SV_IPB, DanauIPB
    );

    SV_IPB = {Haversine::DegreesToRadians(-6.588457), Haversine::DegreesToRadians(106.806200)};
    DanauIPB = {Haversine::DegreesToRadians(-6.559582), Haversine::DegreesToRadians(106.726720)};
    double_t Jarak_RAD =  Distances_2D::Distance_Rad_Plain(SV_IPB, DanauIPB);

    fmt::println(
        "~Rad\nSV IPB = {}\nDanau IPB = {}\n",
        SV_IPB, DanauIPB
    );

    fmt::println(
        "Degrees = {}\nRadians = {}",
        Jarak_DEG, Jarak_RAD
    );

    fmt::println("{:~^{}}", "", Misc::TerminalSize());
    bool same;
    if (Jarak_DEG == Jarak_RAD){
        fmt::println("APPROVED!");
    } else {
        fmt::println("meh");
    }

}

/* ~ end _Main.cpp ~*/
/* File: Haversine.hpp */

#pragma once

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cmath>

#include "Symbols.hpp"

namespace Haversine{
    float DegreesToRadians(float degrees) {
        return degrees * (PI / 180);
    }

    double_t Archav(double_t x){
        return 2 * asinl(sqrtl(x));
    }

    double_t Archav_rad(double_t x){
        return 2 * atan2l(sqrtl(x), sqrtl(1 - x));
    }

    double_t Hav_Radian(double_t x){
        auto Cos = cos(x);
        auto Hav = (1 - Cos)/2;

        return Hav;
    }

    double_t Hav_Degree(double_t x){
        x = DegreesToRadians(x);
        auto Cos = cos(x);
        auto Hav = (1 - Cos)/2;

        return Hav;
    }

    double_t Hav(double_t x, bool isRadian = false, bool DEBUG = true){
        if(isRadian){
            if(DEBUG){ fmt::println("{} x = {}{}", COM3, x, RAD); };
            auto Cos = cos(x);
            auto Hav = (1 - Cos)/2;

            if(DEBUG){
                fmt::println(
                    "{} cos(x) = {}\n{}hav(x) = (1 - {})/2",
                    COM3, Cos,
                    COM3, Cos
                );
                fmt::println("{} hav(x) = {}", COM3, Hav);
            }
            return Hav;

        } else {
            if(DEBUG){ fmt::println("{} x = {}{}", COM3, x, DEGREE); };
            x = DegreesToRadians(x);
            if(DEBUG){ fmt::println("{} x = {}{}", COM3, x, RAD); };
            auto Cos = cos(x);
            auto Hav = (1 - Cos)/2;

            if(DEBUG){
                fmt::println(
                    "{} cos(x) = {}\n{} hav(x) = (1 - {})/2",
                    COM3, Cos,
                    COM3, Cos
                );
                fmt::println("{} hav(x) = {}\n", COM3, Hav);
            }
            return Hav;
        }
    }
}

/* ~ end Haversine.hpp ~*/
/**
 * File: includes.hpp
 *
 * Include bundle
 */

#pragma once

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <string>
#include <vector>
#include <cmath>

#include <windows.h>
#include <processenv.h>

// #include "Haversine.hpp"
// #include "Symbols.hpp"
// #include "Misc.hpp"

/* ~ end includes.hpp ~*/
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
/**
 * File: Navigation_2D_P.hpp
 *
 * Just like Navigation_2D.hpp, but with
 * printing for every steps
 */

#pragma once

#include "Haversine.hpp"
#include "Misc.hpp"
#include "Symbols.hpp"

namespace Distance_2D_P{
    template <typename T>
    double_t Distance_Degree(std::vector<T> A, std::vector<T> B){
        /**Based on Generic formula using degrees
         *  based on Generic formula using degrees:
         *
         * hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
         * θ = 2 * arcsin(√hav(θ))
         * d = R * θ
         *
         * hav(x) = sin²(x/2) = (1 - cos(x))/2
         * θ = 2 * arcsin(√(hav(θ)))
         */

        fmt::println("Coords:");

        // Assigning φ and λ
        double_t lat1 = (double_t)A[0];
        double_t lon1 = (double_t)A[1];

        double_t lat2 = (double_t)B[0];
        double_t lon2 = (double_t)B[1];

        cstr Print_C1 = fmt::format(
            "{}{} = {}{}\n{}{} = {}{}\n",
            PHI, SB1, lat1, DEGREE,
            LAMBDA, SB1, lon1, DEGREE
        );

        cstr Print_C2 = fmt::format(
            "{}{} = {}{}\n{}{} = {}{}\n",
            PHI, SB2, lat2, DEGREE,
            LAMBDA, SB2, lon2, DEGREE
        );

        fmt::println(
            "{}\n{}\n~~~",
            Print_C1, Print_C2
        );

        // Calculate deltas
        double_t dlat = lat2 - lat1;
        double_t dlon = lon2 - lon1;

        cstr Print_Dlat = fmt::format(
            "{}{} = {}{} - {}{}\n{}{} = {} - {}\n{}{} = {}\n",
            DELTA, PHI, PHI, SB2, PHI, SB1,
            DELTA, PHI, lat2, lat1,
            DELTA, PHI, dlat
        );
        cstr Print_Dlon = fmt::format(
            "{}{} = {}{} - {}{}\n{}{} = {} - {}\n{}{} = {}\n",
            DELTA, LAMBDA, LAMBDA, SB2, LAMBDA, SB1,
            DELTA, LAMBDA, lon2, lon1,
            DELTA, LAMBDA, dlon
        );

        fmt::println(
            "{}\n{}\n~~~",
            Print_Dlat,
            Print_Dlon
        );

        // Calculate Hav1 and Hav2
        fmt::println(
            "{}  hav({}{})\n{}  hav({})",
            COM2, DELTA, PHI,
            COM2, dlat
        );
        auto hav1 = Haversine::Hav(dlat);

        fmt::println(
            "{}  hav({}{})\n{}  hav({})",
            COM2, DELTA, LAMBDA,
            COM2, dlon
        );
        auto hav2 = Haversine::Hav(dlon);

        // Calculate cos1 and cos2
        auto cos1 = cos(Haversine::DegreesToRadians(lat1));
        auto cos2 = cos(Haversine::DegreesToRadians(lat2));

        // Calculate Hav(θ)
        fmt::println("\n~~~");
        double_t hav = hav1 + cos1 * cos2 * hav2;
        double_t TH  = Haversine::Archav(hav);
        double_t Tas = asinhl(sqrtl(hav));
        double_t D   = TH * R;

        cstr rHav = fmt::format(
            "{}\n{}\n{}",
            fmt::format(
                "hav({}) = hav({}{}) + cos({}{}) * cos({}{}) * hav({}{})",
                THETA, DELTA, PHI, PHI, SB1, PHI, SB2, DELTA, LAMBDA
            ),
            fmt::format(
                "hav({}) = hav({}) + cos({}) * cos({}) * hav({})",
                THETA, dlat, lat1, lat2, dlon
            ),
            fmt::format(
                "hav({}) = {} + {} * {} * {}",
                THETA, hav1, cos1, cos2, hav2
            )
        );

        cstr rTheta = fmt::format(
            "{}\n{}\n{}\n{}\n{}\n",
            fmt::format(
                "{}{} = archav(hav({}))",
                THETA, DEGREE, THETA
            ),
            fmt::format(
                "{}{} = 2 * arcsin({}hav({}))",
                THETA, DEGREE, SQRT, THETA
            ),
            fmt::format(
                "{}{} = 2 * arcsin({}{})",
                THETA, DEGREE, SQRT, hav
            ),
            fmt::format(
                "{}{} = 2 * {}",
                THETA, DEGREE, Tas
            ),
            fmt::format(
                "{}{} = {}",
                THETA, DEGREE, TH
            )
        );

        cstr rDist = fmt::format(
            "{}\n{}\n{}\n{}\n",
            fmt::format(
                "d = R * {}{}",
                THETA, DEGREE
            ),
            fmt::format(
                "d = {} * {}",
                R, TH
            ),
            fmt::format(
                "d = {}",
                D
            ),
            fmt::format(
                "d = {}",
                fmt::format("{}", D).substr(0, 4)
            )
        );

        fmt::println(
            "{}\n{}\n{}",
            rHav, rTheta, rDist
        );

        return D;
    };
}

/* ~ end Navigation_2D_P.hpp ~*/
/* File: Navigation_2D.hpp */

#pragma once

#include "Haversine.hpp"
#include "Misc.hpp"
#include "Symbols.hpp"

// Types
#define str std::string
#define cstr const std::string
#define ListS std::vector<str>
#define ListI std::vector<int64_t>
#define ListD std::vector<double_t>

namespace Distances_2D{
    template <typename T>
    double_t Distance_Deg_Plain(std::vector<T> A, std::vector<T> B){
        /**Based on Generic formula using degrees
         *
         * hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
         * θ = 2 * arcsin(√hav(θ))
         * d = R * θ
         *
         * hav(x) = sin²(x/2) = (1 - cos(x))/2
         * θ = 2 * arcsin(√(hav(θ)))
         */

        // Assigning φ and λ
        double_t lat1 = (double_t)A[0];
        double_t lon1 = (double_t)A[1];

        double_t lat2 = (double_t)B[0];
        double_t lon2 = (double_t)B[1];

        // Find deltas
        double_t dlat = lat2 - lat1;
        double_t dlon = lon2 - lon1;

        // Find for hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        auto hav1 = Haversine::Hav_Degree(dlat);
        auto cos1 = cos(Haversine::DegreesToRadians(lat1));
        auto cos2 = cos(Haversine::DegreesToRadians(lat2));
        auto hav2 = Haversine::Hav_Degree(dlon);

        double_t hav = hav1 + cos1 * cos2 * hav2;
        // double_t TH  = Haversine::Archav(hav);
        double_t TH  = 2 * asin(sqrt(hav));
        double_t D   = TH * R;

        return D;
    }

    template <typename T>
    double_t Distance_Rad_Plain(std::vector<T> A, std::vector<T> B){
        /**Based on Generic formula using radian
         *
         * hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
         * θ = 2 * arctan2(√(hav(θ)), √(hav(θ)))
         * d = R * θ
         *
         * hav(x) = sin²(x/2) = (1 - cos(x))/2
         */

        // Assigning φ and λ
        double_t lat1 = (double_t)A[0];
        double_t lon1 = (double_t)A[1];

        double_t lat2 = (double_t)B[0];
        double_t lon2 = (double_t)B[1];

        // Find deltas
        double_t dlat = lat2 - lat1;
        double_t dlon = lon2 - lon1;

        // Find for hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        auto hav1 = Haversine::Hav_Radian(dlat);
        auto cos1 = cos(lat1);
        auto cos2 = cos(lat2);
        auto hav2 = Haversine::Hav_Radian(dlon);

        double_t hav = hav1 + cos1 * cos2 * hav2;
        // double_t TH  = Haversine::Archav_rad(hav);
        double_t TH  = 2 * atan2(sqrt(hav), sqrt(1 - hav));
        double_t D   = TH * R;

        return D;
    }
};

/* namespace Test{
    void PrintGreek(){
        fmt::println("Delta = {}", DELTA);
        fmt::println("Theta = {}", THETA);
        fmt::println("Lambda = {}", LAMBDA);
        fmt::println("Phi = {}\n", PHI);

        fmt::println("Delta = {}", C_DELTA);
        fmt::println("Theta = {}", C_THETA);
        fmt::println("Lambda = {}", C_LAMBDA);
        fmt::println("Phi = {}", C_PHI);
    }

    void TerminalSize(){
        fmt::println("Terminal = {}", Misc::TerminalSize());
    }

    void PrintMiddle(){
        Misc::printmid();
    }

    void Macros(){
        fmt::println("Hi");
    }
} */

/*
9.358608358705892
9.358608543232885
*/

/* ~ end Navigation_2D.hpp ~*/
/**
 * File: Symbols.hpp
 *
 * Macros bundle
 */

#pragma once

// Values
#define PI 3.141592653589793
#define R 6378

// Greek Alphabets
#define DELTA "\u0394"
#define THETA "\u03b8"
#define PHI "\u03d5"
#define LAMBDA "\u03bb"

// Greek Alphabets Colored
#define C_DELTA "\x1b[38;2;115;192;105m\u0394\x1b[0m"    // Color: 73c069
#define C_THETA "\x1b[38;2;255;138;70m\u03b8\x1b[0m"     // Color: ff8a46
#define C_PHI "\x1b[38;2;16;150;150m\u03d5\x1b[0m"       // Color: 109696
#define C_LAMBDA "\x1b[38;2;223;196;125m\u03bb\x1b[0m"   // Color: dfc47d

// Math symbols
#define DEGREE "\u00b0" // °
#define RAD " RAD"      // RAD
#define SQRT "\u221a"   // √
#define APRX "\u2248"   // ≈

// Other symbols
#define COM3 ">>>"      // >>> (Python style Command)
#define COM2 ">>"       // >>  (Python style 2 Command)

// Subscripts
#define SB1 "\u2081"    // ₁
#define SB2 "\u2082"    // ₂

/** Types Shortcuts
 * Goal:
 * +---------------+-----------------------+
 * | What to type  | What it actually do   |
 * +---------------+-----------------------+
 * | int(64)       | int64_t               |
 * | vec(64)       | std::vector<int64_t>  |
 * | Sptr(int)     | std::make_unique<int> |
 * | Sptr(int(64)) | std::make_unique<int> |
 * +---------------------------------------+
 */
// #define int(bit) (int(bit)_t)
// #define Sptr(type) (std::make_unique<type>)

/* ~ end Symbols.hpp ~*/
