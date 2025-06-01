/* Program.cs */

namespace Csharp;

using System;                   // System sauces
using System.ComponentModel;
/**/
using nHaversine;               // Main sauce
using nSymbols;                 // Helper of main sauce
using nDistance;                // The main dish along with the main sauce
using nMisc;                    // Very side dish
using System.Runtime;


/// <summary>
/// Represents a geographical location with latitude, longitude, and associated metadata.
/// </summary>
class Location
{
    /*
     Default latitude       0 
     Default longitude      0
     Default name           MyLocation 
     Default coords unit    Degrees
    */
    public double Lat = 0;
    public double Lon = 0;
    public string Name = "";
    public string Unit = "";

    private string Symbol = "";
    private List<double> Coords = new List<double>();

    /// <summary>
    /// Initializes a new instance of the Location class with default or specified values.
    /// </summary>
    /// <param name="aLat">Latitude of the location (default: 0).</param>
    /// <param name="aLon">Longitude of the location (default: 0).</param>
    /// <param name="aName">Name of the location (default: "MyLocation").</param>
    /// <param name="isRadian">Indicates whether the coordinates are in radians (default: false).</param>
    public Location(string aName = "MyLocation", double aLat = 0, double aLon = 0, bool isRadian = false)
    {
        if (isRadian)
        {
            Unit = "Radian";
            Symbol = Symbols.RAD;
        }
        else if (!isRadian)
        {
            Unit = "Degree";
            Symbol = Symbols.DEGREE;
        }
        Lat = aLat;
        Lon = aLon;
        Name = aName;

        Coords.Add(Lat);
        Coords.Add(Lon);
    }

    ~Location()
    {
        // TODO: Make de-constructor, but how and why?
        // IDisposable;
    }

    /// <summary>
    /// Prints the location's details in a human-readable format.
    /// </summary>
    public void Printer()
    {
        Console.WriteLine($"{Name} Coords in {Unit}");
        Console.WriteLine($"{Symbols.PHI} = {Lat}{Symbol}");
        Console.WriteLine($"{Symbols.LAMBDA} = {Lon}{Symbol}");
    }

    /// <summary>
    /// Converts the location's coordinates to radians.
    /// </summary>
    /// <param name="SupressWarning">Suppresses warnings if the coordinates are already in radians (default: false).</param>
    /// <param name="Force">Forces conversion even if the coordinates are already in radians (default: false).</param>
    /// <returns>A list containing the converted latitude and longitude in radians.</returns>
    public List<double> toRadian(bool suppressWarning = false, bool force = false)
    {
        if (Unit == "Radian")
        {
            if (!suppressWarning && force)
            {
                Console.WriteLine("Warning: Already in Radians, but forced conversion is enabled.");
            }
            else if (!suppressWarning)
            {
                Console.WriteLine("Warning: Already in Radians.");
                return Coords;
            }
        }

        // Perform the actual conversion
        Lat = Lat * Math.PI / 180;
        Lon = Lon * Math.PI / 180;

        Unit = "Radian";
        Symbol = Symbols.RAD;

        Coords.Clear();
        Coords.Add(Lat);
        Coords.Add(Lon);

        return Coords;
    }

    /// <summary>
    /// Converts the location's coordinates to degrees.
    /// </summary>
    /// <param name="SupressWarning">Suppresses warnings if the coordinates are already in degrees (default: false).</param>
    /// <param name="Force">Forces conversion even if the coordinates are already in degrees (default: false).</param>
    /// <returns>A list containing the converted latitude and longitude in degrees.</returns>
    public List<double> toDegree(bool suppressWarning = false, bool force = false)
    {
        if (Unit == "Degree")
        {
            if (!suppressWarning && force)
            {
                Console.WriteLine("Warning: Already in Degrees, but forced conversion is enabled.");
            }
            else if (!suppressWarning)
            {
                Console.WriteLine("Warning: Already in Degrees.");
                return Coords;
            }
        }

        // Perform the actual conversion
        Lat = Lat * Math.PI / 180;
        Lon = Lon * Math.PI / 180;

        Unit = "Degree";
        Symbol = Symbols.DEGREE;

        Coords.Clear();
        Coords.Add(Lat);
        Coords.Add(Lon);

        return Coords;
    }

    /// <summary>
    /// Retrieves the current coordinates of the location.
    /// </summary>
    /// <returns>A list containing the latitude and longitude.</returns>
    public List<double> GetCoords()
    {
        return Coords;
    }
}

class Program
{
    static void Main()
    {
        
        /*
        [-6.588457, 106.806200]
        [-6.559582, 106.726720]
        */

        Location SV_IPB = new Location( "SV IPB", -6.588457, 106.806200, isRadian: false);
        Location Danau_IPB = new Location("Danau IPB", -6.559582, 106.726720, isRadian: false);

        SV_IPB.Printer();
        Danau_IPB.Printer();

        Console.WriteLine(Mics.PrintMid("Degree", '-'));
        // double D = nDistance.Distance_2D.Distance_Deg(SV_IPB, Danau_IPB);
        double D = nDistance.Distance_2D.Distance(SV_IPB, Danau_IPB);

        Console.WriteLine(Mics.PrintMid("Radians", '-'));
        SV_IPB.toRadian();
        Danau_IPB.toRadian();

        // double R = nDistance.Distance_2D.Distance_Rad(SV_IPB, Danau_IPB);
        double R = nDistance.Distance_2D.Distance(SV_IPB, Danau_IPB, IsRadian:true);

        Console.WriteLine(Mics.Repeater("~", Console.WindowWidth));

        Console.WriteLine($"Degrees = {D} KM");
        Console.WriteLine($"Radians = {R} KM");

        if (D == R)
        {
            Console.WriteLine("APPROVED!");
        }
        else
        {
            Console.WriteLine("meh");
        }
    }
}

/* End Program.cs */