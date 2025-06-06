/* Program.cs */

namespace Csharp;

using System;                   // System sauces
using System.ComponentModel;
/**/
using Haversine;               // Main sauce
using Symbols;                 // Helper of main sauce
using Distance;                // The main dish along with the main sauce
using Misc;                    // Very side dish
using System.Runtime;

using Driving;
using Location;

class Program{
    private static void IPB()
    {
        /*
        [-6.588457, 106.806200]
        [-6.559582, 106.726720]
        */

        Location SV_IPB = new Location("SV IPB", -6.588457, 106.806200, isRadian: false);
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
        double R = nDistance.Distance_2D.Distance(SV_IPB, Danau_IPB, IsRadian: true);

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

    private static void SimpleGPS() {
        
    }

    public static void Main() {
        IPB();
    }
}

/* End Program.cs */