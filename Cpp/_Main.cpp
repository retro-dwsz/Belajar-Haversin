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