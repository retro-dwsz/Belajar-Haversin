/* File: Navigation_2D.hpp */

#pragma once

#include "Haversine.hpp"
#include "Misc.hpp"
#include "Symbols.hpp"

// Types
#define str std::string
#define cstr const std::string
#define ListS std::vector<str>
#define ListI std::vector<int64_t>
#define ListD std::vector<double_t>

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

/* namespace Test{
    void PrintGreek(){
        fmt::println("Delta = {}", DELTA);
        fmt::println("Theta = {}", THETA);
        fmt::println("Lambda = {}", LAMBDA);
        fmt::println("Phi = {}\n", PHI);
    
        fmt::println("Delta = {}", C_DELTA);
        fmt::println("Theta = {}", C_THETA);
        fmt::println("Lambda = {}", C_LAMBDA);
        fmt::println("Phi = {}", C_PHI);
    }

    void TerminalSize(){
        fmt::println("Terminal = {}", Misc::TerminalSize());
    }

    void PrintMiddle(){
        Misc::printmid();
    }

    void Macros(){
        fmt::println("Hi");
    }
} */

/*
9.358608358705892
9.358608543232885
*/

/* ~ end Navigation_2D.hpp ~*/
