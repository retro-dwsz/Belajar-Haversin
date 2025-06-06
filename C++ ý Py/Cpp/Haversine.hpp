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
