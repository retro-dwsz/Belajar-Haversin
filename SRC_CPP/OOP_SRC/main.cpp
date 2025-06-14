// main.cpp

#include "Includes.h"

#include "Symbols.h"
#include "Haversine.h"
#include "Distance.h"
#include "Misc.h"

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

