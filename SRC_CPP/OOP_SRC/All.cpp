#include <cmath>
#include <vector>
#include <string>
#include <string_view>

#include <sstream>

#include <variant>
// #include <fmt/base.h>
// #include <fmt/core.h>
#include <fmt/format.h>

#include <any>

const double PI =  3.141592653589793;
const int R     =  6378;

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

using str   = std::string;
using str_v = std::string_view;

namespace hLocation{
    class Location{
        private:
        str Symbol;
        std::vector<double> Coords;
    
        public:
        double Lat = 0;
        double Lon = 0;
        str Name = "";
        Unit Unit;
    
        Location(str Name, double Lat = 0, double Lon = 0, bool isRadian = false){
            if (isRadian) {
                this->Unit = Unit::Radian;
                this->Symbol = Symbols::Radian;
            } else {
                this->Unit = Unit::Degree;
                this->Symbol = Symbols::Degree;
            }
            this->Name = Name;
            this->Lat = Lat;
            this->Lon = Lon;

            Coords.push_back(Lat);
            Coords.push_back(Lon);
        }

        void Printer(){
            str_v unitStr = (this->Unit == Unit::Radian) ? Symbols::Radian : Symbols::Degree;

            fmt::println("{} Coords in {}", this->Name, unitStr);
            fmt::println("{} = {} {}", Symbols::PHI, this->Lat, this->Symbol);
            fmt::println("{} = {} {}", Symbols::THETA, this->Lon, this->Symbol);
        }

        void toRadian(bool SupressWarning = false, bool force = false){
            if (this->Unit == Unit::Radian){
                if (!SupressWarning && force){
                    fmt::println("Warning: Already in Radians, but forced conversion is enabled.");
                }
                else if (!SupressWarning){
                    fmt::println("Warning: Already in Radians.");
                    // return Coords;
                }
            }

            // Perform the actual conversion
            Lat = Lat * PI / 180;
            Lon = Lon * PI / 180;

            Unit = Unit::Radian;
            Symbol = Symbols::Radian;

            Coords.clear();
            Coords.push_back(Lat);
            Coords.push_back(Lon);
        }

        void toDegrees(bool SupressWarning = false, bool force = false){
            if (this->Unit == Unit::Degree){
                if (!SupressWarning && force){
                    fmt::println("Warning: Already in Degreess, but forced conversion is enabled.");
                }
                else if (!SupressWarning){
                    fmt::println("Warning: Already in Degreess.");
                    // return Coords;
                }
            }

            // Perform the actual conversion
            Lat = Lat * PI / 180;
            Lon = Lon * PI / 180;

            Unit = Unit::Degree;
            Symbol = Symbols::Degree;

            Coords.clear();
            Coords.push_back(Lat);
            Coords.push_back(Lon);
        }

        std::vector<double> GetCoords(){
            return this->Coords;
        }

        std::any GetUnit(){
            return this->Unit;
        }
    };
};

namespace Distance{
    template <typename T>
    T d_round(T value, int decimalPlaces) {
        T factor = std::pow(T(10), decimalPlaces);
        return std::round(value * factor) / factor;
    }

    double Distance_Deg( hLocation::Location A, hLocation::Location B ){

        // if(A.GetUnit() == Unit::Radian || B.Unit() == Unit::Radian){
        //     fmt::println("WARNING: Units are Radian");
        // }

        fmt::println("Coords in Degrees");

        double lat1 = A.Lat;
        double lon1 = A.Lon;
        fmt::println("{}{} = {}{}",
            Symbols::PHI, Symbols::SB1, lat1, Symbols::Degree
        );
        fmt::println("{}{} = {}{}\n",
            Symbols::LAMBDA, Symbols::SB1, lon1, Symbols::Degree
        );
        

        double lat2 = B.Lat;
        double lon2 = B.Lon;
        fmt::println("{}{} = {}{}",
            Symbols::PHI, Symbols::SB2, lat2, Symbols::Degree
        );
        fmt::println("{}{} = {}{}\n~~~", 
            Symbols::LAMBDA, Symbols::SB2, lon2, Symbols::Degree
        );

        double Dlat = lat2 - lat1;
        fmt::println("{}{} = {}{} - {}{}",
            Symbols::DELTA, Symbols::PHI,
            Symbols::PHI, Symbols::SB2,
            Symbols::PHI, Symbols::SB1
        );
        fmt::println("{}{} = {} - {}",
            Symbols::DELTA, Symbols::PHI,
            lat2, lat1
        );
        fmt::println("{}{} = {}\n",
            Symbols::DELTA, Symbols::PHI,
            Dlat
        );
        
        double Dlon = lon2 - lon1;
        fmt::println("{}{} = {}{} - {}{}",
            Symbols::DELTA, Symbols::LAMBDA,
            Symbols::LAMBDA, Symbols::SB2,
            Symbols::LAMBDA, Symbols::SB1
        );
        fmt::println("{}{} = {} - {}",
            Symbols::DELTA, Symbols::LAMBDA,
            lon2, lon1
        );
        fmt::println("{}{} = {}\n~~~",
            Symbols::DELTA, Symbols::LAMBDA,
            Dlon
        );

        fmt::println("~ Hav({}{})", Symbols::DELTA, Symbols::PHI);
        fmt::println("~ Hav({})", Dlat);
        double hav1 = Haversine::Hav_deg(Dlat, true);

        fmt::println("\n~ Hav({}{})", Symbols::DELTA, Symbols::LAMBDA);
        fmt::println("~ Hav({})", Dlon);
        double hav2 = Haversine::Hav_deg(Dlon, true);

        double cos1 = cos(Haversine::deg2rad(lat1));
        double cos2 = cos(Haversine::deg2rad(lat2));

        double Hav = hav1 + cos1 * cos2 * hav2;
        fmt::println(
            "\nhav({}) = hav({}{}) + cos({}{}) * cos({}{}) * hav({}{})",
            Symbols::THETA,
            Symbols::DELTA, Symbols::PHI,
            Symbols::PHI, Symbols::SB1,
            Symbols::PHI, Symbols::SB2,
            Symbols::DELTA, Symbols::LAMBDA
        );
        fmt::println(
            "hav({}) = hav({}) + cos({}) * cos({}) * hav({})",
            Symbols::THETA,
            Dlat, lat1, lat2, Dlon
        );
        fmt::println(
            "hav({}) = {}\n",
            Symbols::THETA, Hav
        );

        double T = 2 * asin(sqrt(Hav));
        fmt::println("{} = archav({})", Symbols::THETA, Hav);
        fmt::println("{} = 2 * arcsin({}{})", Symbols::THETA, Symbols::SQRT, Hav);
        fmt::println("{} = {}\n", Symbols::THETA, T);

        double D = R * T;
        fmt::println("d = R * {}{} ", Symbols::THETA, Symbols::Degree);
        fmt::println("d = {} * {}", R, T);
        fmt::println("d {} {} KM", Symbols::APRX, D);
        fmt::println("d {} {} KM", Symbols::APRX, d_round(D, 2));

        return D;
    }

    double Distance_Rad( hLocation::Location A, hLocation::Location B ){
        fmt::println("Coords in Radian");

        double lat1 = A.Lat;
        double lon1 = A.Lon;
        fmt::println("{}{} = {}{}",
            Symbols::PHI, Symbols::SB1, lat1, Symbols::Radian
        );
        fmt::println("{}{} = {}{}\n",
            Symbols::LAMBDA, Symbols::SB1, lon1, Symbols::Radian
        );
        

        double lat2 = B.Lat;
        double lon2 = B.Lon;
        fmt::println("{}{} = {}{}",
            Symbols::PHI, Symbols::SB2, lat2, Symbols::Radian
        );
        fmt::println("{}{} = {}{}", 
            Symbols::LAMBDA, Symbols::SB2, lon2, Symbols::Radian
        );

        double Dlat = lat2 - lat1;
        fmt::println("{}{} = {}{} - {}{}",
            Symbols::DELTA, Symbols::PHI,
            Symbols::PHI, Symbols::SB2,
            Symbols::PHI, Symbols::SB1
        );
        fmt::println("{}{} = {} - {}",
            Symbols::DELTA, Symbols::PHI,
            lat2, lat1
        );
        fmt::println("{}{} = {}\n",
            Symbols::DELTA, Symbols::PHI,
            Dlat
        );
        
        double Dlon = lon2 - lon1;
        fmt::println("{}{} = {}{} - {}{}",
            Symbols::DELTA, Symbols::LAMBDA,
            Symbols::LAMBDA, Symbols::SB2,
            Symbols::LAMBDA, Symbols::SB1
        );
        fmt::println("{}{} = {} - {}",
            Symbols::DELTA, Symbols::LAMBDA,
            lon2, lon1
        );
        fmt::println("{}{} = {}\n~~~",
            Symbols::DELTA, Symbols::LAMBDA,
            Dlon
        );

        fmt::println("~ Hav({}{})", Symbols::DELTA, Symbols::PHI);
        fmt::println("~ Hav({})", Dlat);
        double hav1 = Haversine::Hav_rad(Dlat, true);

        fmt::println("\n~ Hav({}{})", Symbols::DELTA, Symbols::LAMBDA);
        fmt::println("~ Hav({})", Dlon);
        double hav2 = Haversine::Hav_rad(Dlon, true);

        double cos1 = cos(lat1);
        double cos2 = cos(lat2);

        double Hav = hav1 + cos1 * cos2 * hav2;
        fmt::println(
            "\nhav({}) = hav({}{}) + cos({}{}) * cos({}{}) * hav({}{})",
            Symbols::THETA,
            Symbols::DELTA, Symbols::PHI,
            Symbols::PHI, Symbols::SB1,
            Symbols::PHI, Symbols::SB2,
            Symbols::DELTA, Symbols::LAMBDA
        );
        fmt::println(
            "hav({}) = hav({}) + cos({}) * cos({}) * hav({})",
            Symbols::THETA,
            Dlat, lat1, lat2, Dlon
        );
        fmt::println(
            "hav({}) = {}\n",
            Symbols::THETA, Hav
        );

        double T = 2 * asin(sqrt(Hav));
        fmt::println("{} = archav({})", Symbols::THETA, Hav);
        fmt::println("{} = 2 * arcsin({}{})", Symbols::THETA, Symbols::SQRT, Hav);
        fmt::println("{} = {}\n", Symbols::THETA, T);

        double D = R * T;
        fmt::println("d = R * {}{} ", Symbols::THETA, Symbols::Radian);
        fmt::println("d = {} * {}", R, T);
        fmt::println("d {} {} KM", Symbols::APRX, D);
        fmt::println("d {} {} KM", Symbols::APRX, d_round(D, 2));

        return D;
    }

    double Distance(hLocation::Location A, hLocation::Location B, bool IsRadian = false, bool Printing = false ){
        double lat1, lon1, lat2, lon2, Dlat, Dlon, hav1, hav2, cos1, cos2, Hav, T;
        double D;

        if(Printing){
            if (!IsRadian){
                Distance_Deg(A, B);
            } else if (IsRadian){
                Distance_Rad(A, B);
            }   
        } else if (!Printing){
            if(!IsRadian){
                lat1 = A.Lat;
                lon1 = A.Lon;
                lat2 = B.Lat;
                lon2 = B.Lon;

                Dlat = lat2 - lat1;
                Dlon = lon2 - lon1;

                hav1 = Haversine::Hav_deg(Dlat, true);
                hav2 = Haversine::Hav_deg(Dlon, true);
                cos1 = cos(Haversine::deg2rad(lat1));
                cos2 = cos(Haversine::deg2rad(lat2));

                Hav  = hav1 + cos1 * cos2 * hav2;
                T    = 2 * asin(sqrt(Hav));
                D    = R * T;

            } else if (IsRadian){
                lat1 = A.Lat;
                lon1 = A.Lon;
                lat2 = B.Lat;
                lon2 = B.Lon;

                Dlat = lat2 - lat1;
                Dlon = lon2 - lon1;

                hav1 = Haversine::Hav_rad(Dlat, true);
                hav2 = Haversine::Hav_rad(Dlon, true);
                cos1 = cos(lat1);
                cos2 = cos(lat2);

                Hav = hav1 + cos1 * cos2 * hav2;
                T = 2 * asin(sqrt(Hav));
                D = R * T;
            }
        }

        return D;
    }
}

using namespace hLocation;

int main(){
    Location SV_IPB = Location("SV IPB", -6.588457, 106.806200);
    Location Danau  = Location("Danau IPB", -6.559582, 106.726720);

    SV_IPB.Printer();
    Danau.Printer();

    fmt::println("{}", Misc::PrintMid("Degree", '-'));
    double DEG = Distance::Distance_Deg(SV_IPB, Danau);
    
    SV_IPB.toRadian();
    Danau.toRadian();
    
    fmt::println("{}", Misc::PrintMid("Radian", '-'));
    double RAD = Distance::Distance_Rad(SV_IPB, Danau);
    
    fmt::println("{}", fmt::format("{:~^{}}", "~", Misc::TerminalSize()));
    fmt::println("Degrees = {} KM", DEG);
    fmt::println("Radians = {} KM", RAD);

    if(DEG == RAD){
        fmt::println("APPROVED!");
    } else {
        fmt::println("meh");
    }

    return 0;
}