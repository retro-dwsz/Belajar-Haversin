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
