/* Program.cs */

namespace CS_Navigation;

using System;                   // System sauces
using System.ComponentModel;
using System.Runtime;

/**/
using Location;                // Main sauce I
using Haversine;               // Main sauce II
using Symbols;                 // Helper of main sauce
using Distance;                // The main dish along with the main sauce
using Misc;                    // Very side dish

class Program{
    private static bool CheckEqual(object Var1, object Var2) {
        return object.Equals(Var1, Var2);
        // if (Var1 == Var2) {
        //     return true;
        // }
        // else {
        //     return false;
        // }
    }
    
    private static void IPB() {
        /*
        [-6.588457, 106.806200]
        [-6.559582, 106.726720]
        */

        Location SV_IPB = new Location("SV IPB", -6.588457, 106.806200, isRadian: false);
        Location Danau_IPB = new Location("Danau IPB", -6.559582, 106.726720, isRadian: false);

        SV_IPB.Printer();
        Danau_IPB.Printer();

        Console.WriteLine(Misc.PrintMid("Degree", '-'));
        // double D = nDistance.Distance_2D.Distance_Deg(SV_IPB, Danau_IPB);
        double D = Distance.Distance_2D.Distance_Deg(SV_IPB, Danau_IPB);
        
        Console.WriteLine(Misc.PrintMid("Radians", '-'));
        SV_IPB.toRadian();
        Danau_IPB.toRadian();
        
        // double R = nDistance.Distance_2D.Distance_Rad(SV_IPB, Danau_IPB);
        double R = Distance.Distance_2D.Distance_Rad(SV_IPB, Danau_IPB);

        Console.WriteLine(Misc.Repeater("~", Console.WindowWidth));

        Console.WriteLine($"Degrees = {D} KM");
        Console.WriteLine($"Radians = {R} KM");

        Console.WriteLine(CheckEqual(D, R) ? "APPROVED!" : "meh");
    }

    public static void Main() {
        IPB();
    }
}

/* End Program.cs */
