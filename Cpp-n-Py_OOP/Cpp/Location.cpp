#include <string>
#include <vector>

using str = std::string;

enum Unit {
    Degree,
    Radian
};

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

        } else {
            this->Unit = Unit::Degree;
        }
        this->Name = Name;
        this->Lat = Lat;
        this->Lon = Lon;
        
    }
};