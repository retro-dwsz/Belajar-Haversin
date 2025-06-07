using Csharp;
using Location;

namespace Driving;

using Location;
using System.Runtime.CompilerServices;

// UNDER CONSTRUCTION
class GroundNav
{
    /*
     Default latitudes       0
     Default longitudes      0
     Default name           MyLocation
     Default coords unit    Degrees
    */
    private List<Location> Chords;
    private int ChordsSize;
    private Location Start;
    private Location End;

    public string Name;
    public Unit Unit;

    public GroundNav(string Name, Location Start, Location End, List<Location> Chords, Unit Unit = Unit.Degree) {
        this.Name = Name;
        this.Start = Start;
        this.End = End;
        this.Chords = Chords;
        this.Unit = Unit;
        ChordsSize = this.Chords.Capacity;
    }

    public int GetSize() {
        return ChordsSize;
    }

    public void Printer() {
        Console.WriteLine();
        for (int i = 0; i < GetSize(); i++) {
            Console.WriteLine($"> {Chords[i].Name}: ");
            Console.WriteLine($"{Symbols.Symbols.PHI} {Chords[i].Lat}");
            Console.WriteLine($"{Symbols.Symbols.LAMBDA} {Chords[i].Lon}");
        }
    }

    
}

//class Driving{
//    public static void main() {
//        Location Start = new Location("Start", -6.597833622666178, 106.794373367117);
//        Location End = new Location("End", -6.62225014590596, 106.8175039391197);
//        List<Location> Coords = new List<Location>{
//            new Location("Point 01", -6.597052825849262, 106.7937717227824),
//            new Location("Point 02", -6.594705841518939, 106.7942047962342),
//            new Location("Point 03", -6.593604212378643, 106.7961204047717),
//            new Location("Point 04", -6.593158753811323, 106.7965106718923),
//            new Location("Point 05", -6.59358588035416, 106.7977024324252),
//            new Location("Point 06", -6.592574319321151, 106.7996765661645),
//            new Location("Point 07", -6.592563005485911, 106.8017069133976),
//            new Location("Point 08", -6.594667559352246, 106.8025736217902),
//            new Location("Point 09", -6.595509737648851, 106.8040512684551),
//            new Location("Point 10", -6.600999297161692, 106.8050744834284),
//            new Location("Point 11", -6.603626052516093, 106.8060427964824),
//            new Location("Point 12", -6.604047858096131, 106.806516050656),
//            new Location("Point 13", -6.601627793206586, 106.8105263916231),
//            new Location("Point 14", -6.601627793206586, 106.8105263916231),
//            new Location("Point 15", -6.604752634429251, 106.8069558676157),
//            new Location("Point 16", -6.605464978116315, 106.8073990601912),
//            new Location("Point 17", -6.606909664145737, 106.8079136645895),
//            new Location("Point 18", -6.615939116766738, 106.8142013219661),
//            new Location("Point 19", -6.620564055949383, 106.8158072006643),
//            new Location("Point 20", -6.622434959044009, 106.8173220950337)
//        };
        
//        GroundNav Journey = new GroundNav("Journey", Start, End, Coords, Unit.Degree);
        
//    }
//}