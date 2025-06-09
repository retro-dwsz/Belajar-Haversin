// Distance.h
#pragma once

#include "Includes.h"
#include "Location.h"

#include "Haversine.h"

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

// end Distance.h