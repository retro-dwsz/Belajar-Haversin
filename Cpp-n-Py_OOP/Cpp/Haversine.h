// Haversine.h

#pragma once

#include "Includes.h"

#include "Symbols.h"

namespace Haversine{
    double deg2rad(double Deg, bool Printing = false){
        double var = PI / 180 * Deg;

        if (Printing){
            fmt::println("Deg = {}", Deg);
            fmt::println("Rad = {}", var);
        }

        return var;
    }

    double Hav_rad(double x, bool Printing = false){
        double Cos = 1 - cos(x);
        double Hav = Cos/2;

        if (Printing){
            fmt::println("~! x = {}{}", x, Symbols::Radian);
            fmt::println("~! cos(x) = {}", cos(x));
            fmt::println("~! 1-cos(x) = {}", Cos);
            fmt::println("~! Hav(x) = {}", Hav);
        }

        return Hav;
    }

    double Hav_deg(double x, bool Printing = false){
        x = deg2rad(x);

        double Cos = 1 - cos(x);
        double Hav = Cos/2;

        if (Printing){
            fmt::println("~! x = {}{}", x, Symbols::Degree);
            fmt::println("~! cos(x) = {}", cos(x));
            fmt::println("~! 1-cos(x) = {}", Cos);
            fmt::println("~! Hav(x) = {}", Hav);
        }

        return Hav;
    }

    double Hav(double x, Unit unit = Unit::Degree, bool Printing = false){
        if(unit == Unit::Degree){
            x = deg2rad(x);
        } else { }
        
        double Cos = 1 - cos(x);
        double Hav = Cos/2;

        if (Printing){
            fmt::println("~! x = {}{}", x, Symbols::Degree);
            fmt::println("~! cos(x) = {}", cos(x));
            fmt::println("~! 1-cos(x) = {}", Cos);
            fmt::println("~! Hav(x) = {}", Hav);
        }

        return Hav;
    }
}

// end Haversine.h