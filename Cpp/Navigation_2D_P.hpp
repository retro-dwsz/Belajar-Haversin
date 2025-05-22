/**
 * File: Navigation_2D_P.hpp
 * 
 * Just like Navigation_2D.hpp, but with
 * printing for every steps 
 */

#pragma once

#include "Haversine.hpp"
#include "Misc.hpp"
#include "Symbols.hpp"

namespace Distance_2D_P{
    template <typename T>
    double_t Distance_Degree(std::vector<T> A, std::vector<T> B){
        /**Based on Generic formula using degrees
         *  based on Generic formula using degrees:
         *
         * hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
         * θ = 2 * arcsin(√hav(θ))
         * d = R * θ
         * 
         * hav(x) = sin²(x/2) = (1 - cos(x))/2
         * θ = 2 * arcsin(√(hav(θ)))
         */

        fmt::println("Coords:");

        // Assigning φ and λ
        double_t lat1 = (double_t)A[0];
        double_t lon1 = (double_t)A[1];

        double_t lat2 = (double_t)B[0];
        double_t lon2 = (double_t)B[1];

        cstr Print_C1 = fmt::format(
            "{}{} = {}{}\n{}{} = {}{}\n",
            PHI, SB1, lat1, DEGREE,
            LAMBDA, SB1, lon1, DEGREE
        );

        cstr Print_C2 = fmt::format(
            "{}{} = {}{}\n{}{} = {}{}\n",
            PHI, SB2, lat2, DEGREE,
            LAMBDA, SB2, lon2, DEGREE
        );

        fmt::println(
            "{}\n{}\n~~~",
            Print_C1, Print_C2
        );

        // Calculate deltas
        double_t dlat = lat2 - lat1;
        double_t dlon = lon2 - lon1;

        cstr Print_Dlat = fmt::format(
            "{}{} = {}{} - {}{}\n{}{} = {} - {}\n{}{} = {}\n",
            DELTA, PHI, PHI, SB2, PHI, SB1,
            DELTA, PHI, lat2, lat1,
            DELTA, PHI, dlat
        );
        cstr Print_Dlon = fmt::format(
            "{}{} = {}{} - {}{}\n{}{} = {} - {}\n{}{} = {}\n",
            DELTA, LAMBDA, LAMBDA, SB2, LAMBDA, SB1,
            DELTA, LAMBDA, lon2, lon1,
            DELTA, LAMBDA, dlon
        );

        fmt::println(
            "{}\n{}\n~~~",
            Print_Dlat,
            Print_Dlon
        );

        // Calculate Hav1 and Hav2
        fmt::println(
            "{}  hav({}{})\n{}  hav({})",
            COM2, DELTA, PHI,
            COM2, dlat
        );
        auto hav1 = Haversine::Hav(dlat);
        
        fmt::println(
            "{}  hav({}{})\n{}  hav({})",
            COM2, DELTA, LAMBDA,
            COM2, dlon
        );
        auto hav2 = Haversine::Hav(dlon);

        // Calculate cos1 and cos2
        auto cos1 = cos(Haversine::DegreesToRadians(lat1));
        auto cos2 = cos(Haversine::DegreesToRadians(lat2));
        
        // Calculate Hav(θ)
        fmt::println("\n~~~");
        double_t hav = hav1 + cos1 * cos2 * hav2;
        double_t TH  = Haversine::Archav(hav);
        double_t Tas = asinhl(sqrtl(hav));
        double_t D   = TH * R;
        
        cstr rHav = fmt::format(
            "{}\n{}\n{}",
            fmt::format(
                "hav({}) = hav({}{}) + cos({}{}) * cos({}{}) * hav({}{})",
                THETA, DELTA, PHI, PHI, SB1, PHI, SB2, DELTA, LAMBDA
            ),
            fmt::format(
                "hav({}) = hav({}) + cos({}) * cos({}) * hav({})",
                THETA, dlat, lat1, lat2, dlon
            ),
            fmt::format(
                "hav({}) = {} + {} * {} * {}",
                THETA, hav1, cos1, cos2, hav2
            )
        );

        cstr rTheta = fmt::format(
            "{}\n{}\n{}\n{}\n{}\n",
            fmt::format(
                "{}{} = archav(hav({}))",
                THETA, DEGREE, THETA
            ),
            fmt::format(
                "{}{} = 2 * arcsin({}hav({}))",
                THETA, DEGREE, SQRT, THETA
            ),
            fmt::format(
                "{}{} = 2 * arcsin({}{})",
                THETA, DEGREE, SQRT, hav
            ),
            fmt::format(
                "{}{} = 2 * {}",
                THETA, DEGREE, Tas
            ),
            fmt::format(
                "{}{} = {}",
                THETA, DEGREE, TH
            )
        );

        cstr rDist = fmt::format(
            "{}\n{}\n{}\n{}\n",
            fmt::format(
                "d = R * {}{}",
                THETA, DEGREE
            ),
            fmt::format(
                "d = {} * {}",
                R, TH
            ),
            fmt::format(
                "d = {}",
                D
            ),
            fmt::format(
                "d = {}",
                fmt::format("{}", D).substr(0, 4)
            )
        );
        
        fmt::println(
            "{}\n{}\n{}",
            rHav, rTheta, rDist
        );

        return D;
    };
}

/* ~ end Navigation_2D_P.hpp ~*/
