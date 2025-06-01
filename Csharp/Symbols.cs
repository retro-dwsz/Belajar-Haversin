/* Symbols.cs */

namespace nSymbols;

public static class Symbols
{
    // Greek Alphabets
    public const string DELTA  = "\u0394";    // Δ
    public const string THETA  = "\u03b8";    // θ
    public const string PHI    = "\u03d5";    // π   
    public const string LAMBDA = "\u03bb";    // λ

    // Greek Alphabets Colored
    public const string C_DELTA  = "\x1b[38;2;115;192;105m\u0394\x1b[0m";    // Color: 73c069
    public const string C_THETA  = "\x1b[38;2;255;138;70m\u03b8\x1b[0m";     // Color: ff8a46
    public const string C_PHI    = "\x1b[38;2;16;150;150m\u03d5\x1b[0m";     // Color: 109696
    public const string C_LAMBDA = "\x1b[38;2;223;196;125m\u03bb\x1b[0m";    // Color: dfc47d

    // Math symbols
    public const string DEGREE  = "\u00b0"; // °
    public const string RAD     = " RAD";      // RAD
    public const string SQRT    = "\u221a";   // √
    public const string APRX    = "\u2248";   // ≈

    // Subscripts
    public const string SB1 = "\u2081";    // ₁
    public const string SB2 = "\u2082";    // ₂
};


/* End Symbols.cs */