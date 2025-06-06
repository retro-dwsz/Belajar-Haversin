/* Haversine.cs */

namespace Haversine;

using Symbols;

/// <summary>
/// Provides methods to calculate the haversine function used in geographical distance calculations.
/// Includes support for both radians and degrees, with optional verbose output for debugging.
/// </summary>
public class Haversine
{
    /// <summary>
    /// Converts an angle from degrees to radians.
    /// </summary>
    /// <param name="deg">Angle in degrees.</param>
    /// <param name="Printing">Optional. If true, prints intermediate values to console.</param>
    /// <returns>The angle converted to radians.</returns>
    public static double deg2rad(double deg, bool Printing = false)
    {
        double var = Math.PI / 180 * deg;
        if (Printing)
        {
            Console.WriteLine($"deg = {deg}");
            Console.WriteLine($"rad = {var}");
        }
        return var;
    }

    /// <summary>
    /// Computes the haversine of an angle given in radians.
    /// </summary>
    /// <param name="x">Angle in radians.</param>
    /// <param name="Printing">Optional. If true, logs intermediate steps to console.</param>
    /// <returns>Haversine value (double).</returns>
    public static dynamic Hav_rad(double x, bool Printing = false)
    {
        double Cos = 1 - Math.Cos(x);
        double hHav = Cos / 2;
        if (Printing)
        {
            Console.WriteLine($"~! x = {x}{Symbols.RAD}");
            Console.WriteLine($"~! cos(x) = {Math.Cos(x)}");
            Console.WriteLine($"~! 1-cos(x) = {Cos}");
            Console.WriteLine($"~! Hav(x) = {hHav}");
        }

        return hHav;
    }

    /// <summary>
    /// Computes the haversine of an angle given in degrees.
    /// Internally converts degrees to radians before calculation.
    /// </summary>
    /// <param name="x">Angle in degrees.</param>
    /// <param name="Printing">Optional. If true, logs intermediate steps to console.</param>
    /// <returns>Haversine value (double).</returns>
    public static dynamic Hav_deg(double x, bool Printing = false)
    {
        // radian-ize the Angle
        // because C# expect angle in radian
        x = deg2rad(x);

        double Cos = 1 - Math.Cos(x);
        double hHav = Cos / 2;

        if (Printing)
        {
            Console.WriteLine($"~! x = {x}{Symbols.RAD}");
            Console.WriteLine($"~! cos(x) = {Math.Cos(x)}");
            Console.WriteLine($"~! 1-cos(x) = {Cos}");
            Console.WriteLine($"~! Hav(x) = {hHav}");
        }

        return hHav;
    }

    /// <summary>
    /// Generic haversine function that accepts input in either radians or degrees.
    /// </summary>
    /// <param name="x">Input angle (radians or degrees depending on flag).</param>
    /// <param name="isRadian">If true, assumes input is in radians; otherwise, treats it as degrees.</param>
    /// <param name="Printing">Optional. If true, logs intermediate steps to console.</param>
    /// <returns>Haversine value (double).</returns>
    public static double Hav(double x, bool isRadian = false, bool Printing = false)
    {
        if (isRadian) { }
        else
        {
            x = deg2rad(x);
        }

        double Cos = 1 - Math.Cos(x);
        double hHav = Cos / 2;

        if (Printing)
        {
            Console.WriteLine($"~ x = {x} {Symbols.RAD}");
            Console.WriteLine($"~ cos(x) = {Math.Cos(x)}");
            Console.WriteLine($"~ 1-cos(x) = {Cos}");
            Console.WriteLine($"~ Hav(x) = {hHav}");
        }

        return hHav;
    }
}
/* End Haversine.cs */