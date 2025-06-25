// main.cpp

#include "Includes.h"

#include "Symbols.h"
#include "Haversine.h"
#include "Distance.h"
#include "Misc.h"

using namespace hLocation;

namespace Main{
    void IPB(){
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
    }

    void WikipediaExample(){
        Location WhiteHouse = Location("White House WDC", 38.898, 77.037);
        Location EifflTower = Location("Effiel Tower à Paris", 48.858, 2.294);

        WhiteHouse.Printer();
        EifflTower.Printer();

        fmt::println("{}", Misc::PrintMid("Degree", '-'));
        double DEG = Distance::Distance_Deg(WhiteHouse, EifflTower);
        
        WhiteHouse.toRadian();
        EifflTower.toRadian();
        
        fmt::println("{}", Misc::PrintMid("Radian", '-'));
        double RAD = Distance::Distance_Rad(WhiteHouse, EifflTower);
        
        fmt::println("{}", fmt::format("{:~^{}}", "~", Misc::TerminalSize()));
        fmt::println("Degrees = {} KM", DEG);
        fmt::println("Radians = {} KM", RAD);
    
        if(DEG == RAD){
            fmt::println("APPROVED!");
        } else {
            fmt::println("meh");
        }
    }
}

int main(){
    fmt::println("{}", Misc::PrintMid("IPBs"));
    Main::IPB();
    
    fmt::println("{}", Misc::PrintMid("Wikipedia Example"));
    Main::WikipediaExample();
}