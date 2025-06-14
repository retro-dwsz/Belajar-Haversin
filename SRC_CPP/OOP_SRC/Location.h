// Location.h
#pragma once

#include "Includes.h"

#include "Symbols.h"

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

// end Location.h