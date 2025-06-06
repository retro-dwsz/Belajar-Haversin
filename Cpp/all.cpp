#include <fmt/format.h>
#include <fmt/ranges.h>
#include <string>
#include <vector>
#include <cmath>

#include <windows.h>
#include <processenv.h>

#include <cmath>

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

// Types
#define str std::string
#define cstr const std::string
#define ListS std::vector<str>
#define ListI std::vector<int64_t>
#define ListD std::vector<double_t>

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
