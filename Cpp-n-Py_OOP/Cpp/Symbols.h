// Symbols.h

#pragma once
#include "Includes.h"

using str   = std::string;
using str_v = std::string_view;

enum class Unit {
    Degree,
    Radian
};

namespace Symbols {
    // Units
    inline constexpr str_v Degree = "\u00B0";     // °
    inline constexpr str_v Radian = "RAD";

    // Greek letters
    inline constexpr str_v PHI    = "\u03D5";   // φ
    inline constexpr str_v LAMBDA = "\u03BB";   // λ
    inline constexpr str_v DELTA  = "\u0394";   // Δ
    inline constexpr str_v THETA  = "\u03B8";   // θ

    // Colored versions using ANSI escape codes
    inline constexpr str_v C_DELTA  = "\x1b[38;2;115;192;105m\u0394\x1b[0m";   // Green
    inline constexpr str_v C_THETA  = "\x1b[38;2;255;138;70m\u03b8\x1b[0m";    // Orange
    inline constexpr str_v C_PHI    = "\x1b[38;2;16;150;150m\u03d5\x1b[0m";    // Teal
    inline constexpr str_v C_LAMBDA = "\x1b[38;2;223;196;125m\u03bb\x1b[0m";  // Gold

    // Math symbols
    inline constexpr str_v SQRT    = "\u221a";    // √
    inline constexpr str_v APRX    = "\u2248";    // ≈

    // Subscripts
    inline constexpr str_v SB1 = "\u2081";         // ₁
    inline constexpr str_v SB2 = "\u2082";         // ₂
};

// end Symbols.h