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
using System.Drawing;

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

        Console.WriteLine($"Current terminal size: {Misc.TerminalSize}");

        Location SV_IPB = new Location("SV IPB", -6.588457, 106.806200, isRadian: false);
        Location Danau_IPB = new Location("Danau IPB", -6.559582, 106.726720, isRadian: false);

        SV_IPB.Printer();
        Danau_IPB.Printer();

        Console.WriteLine(Misc.PrintMid(Misc.PrintMid("Degree", '-', offset:-(Misc.TerminalSize/2), LeftBorder:' ', RightBorder:' '), Char:' ', LeftBorder:' ', RightBorder:' '));
        // double D = nDistance.Distance_2D.Distance_Deg(SV_IPB, Danau_IPB);
        double D = Distance.Distance_2D.Distance_Deg(SV_IPB, Danau_IPB);

        Console.WriteLine(Misc.PrintMid(Misc.PrintMid("Radians", '-', offset:-(Misc.TerminalSize/2), LeftBorder:' ', RightBorder:' '), Char:' ', LeftBorder:' ', RightBorder:' '));
        SV_IPB.toRadian();
        Danau_IPB.toRadian();
        
        // double R = nDistance.Distance_2D.Distance_Rad(SV_IPB, Danau_IPB);
        double R = Distance.Distance_2D.Distance_Rad(SV_IPB, Danau_IPB);

        Console.WriteLine(Misc.Repeater("~", Console.WindowWidth/2));

        Console.WriteLine($"Degrees = {D} KM");
        Console.WriteLine($"Radians = {R} KM");

        Console.WriteLine(CheckEqual(D, R) ? "APPROVED!" : "meh");
    }

    private static void WikipediaExample()
    {
        Location WhiteHouse = new Location("White House WDC", 38.898, 77.037);
        Location EffielTowr = new Location("Effiel Tower à Paris", 48.858, 2.294);

        WhiteHouse.Printer();
        EffielTowr.Printer();

        Console.WriteLine(Misc.PrintMid(Misc.PrintMid("Degree", '-', offset:-(Misc.TerminalSize/2), LeftBorder:' ', RightBorder:' '), Char:' ', LeftBorder:' ', RightBorder:' '));

        double D = Distance.Distance_2D.Distance_Deg(WhiteHouse, EffielTowr);

        WhiteHouse.toRadian();
        EffielTowr.toRadian();

        Console.WriteLine(Misc.PrintMid(Misc.PrintMid("Radians", '-', offset:-(Misc.TerminalSize/2), LeftBorder:' ', RightBorder:' '), Char:' ', LeftBorder:' ', RightBorder:' '));
        double R = Distance.Distance_2D.Distance_Rad(WhiteHouse, EffielTowr);

        Console.WriteLine(Misc.Repeater("~", Console.WindowWidth/2));

        Console.WriteLine($"Degrees = {D} KM");
        Console.WriteLine($"Radians = {R} KM");

        Console.WriteLine(CheckEqual(D, R) ? "APPROVED!" : "meh");
    }

    public static void Main()
    {
        string TITLE = ColorTx.ColorStr("Haversine Implementation!");
        Console.WriteLine(Misc.PrintMid(TITLE, ' ', LeftBorder:' ', RightBorder:' '));
        
        // Save current color
        // ConsoleColor CurrentColor = Console.BackgroundColor;
        // Set color
        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine(Misc.PrintMid("IPBs", '='));
        // Reset color
        Console.ResetColor();
        IPB();
        Console.WriteLine(Misc.Repeater("=", Misc.TerminalSize));

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine(Misc.PrintMid("WIkipedia Example", '='));
        Console.ResetColor();
        WikipediaExample();
        Console.WriteLine(Misc.Repeater("=", Misc.TerminalSize));

    }
}

/* End Program.cs */
