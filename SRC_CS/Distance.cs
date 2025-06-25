/* Distance.cs */

namespace Distance;

using Haversine;
using Symbols;
using Location;

using System.Runtime.CompilerServices;  // Super Optimization

class Distance
{
    public static int R = 6371;

    public class Distance_2D
    {
        /*
        based on Wikipedia article (With Printing)
        https://en.wikipedia.org/wiki/Haversine_formula

        formula:
        hav(θ°) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ° = 2 * archav(θ)
        d = R * θ°

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        archav(θ) = 2 * arcsin(√(θ)) = 2 * arctan2(√(θ), √(1-θ))
        */
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        public static double Distance_Deg(Location A, Location B)
        {
            // Print Degree coordinates 
            Console.WriteLine($"Coords in Degrees");

            // Latitudes
            double lat1 = A.Lat;
            double lon1 = A.Lon;
            Console.WriteLine($"{Symbols.PHI}{Symbols.SB1} = {lat1}{Symbols.DEGREE}");
            Console.WriteLine($"{Symbols.LAMBDA}{Symbols.SB1} = {lon1}{Symbols.DEGREE}\n");

            // Longitudes
            double lat2 = B.Lat;
            double lon2 = B.Lon;
            Console.WriteLine($"{Symbols.PHI}{Symbols.SB2} = {lat2}{Symbols.DEGREE}");
            Console.WriteLine($"{Symbols.LAMBDA}{Symbols.SB2} = {lon2}{Symbols.DEGREE}\n~~~");

            // Calculate Deltas
            // Delta phi
            double Dlat = Haversine.Normalize(lat2 - lat1);
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {Symbols.PHI}{Symbols.SB2} - {Symbols.PHI}{Symbols.SB1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {lat2} - {lat1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {Dlat}\n");

            // Delta lambda
            double Dlon = Haversine.Normalize(lon2 - lon1);
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {Symbols.LAMBDA}{Symbols.SB2} - {Symbols.LAMBDA}{Symbols.SB1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {lon2} - {lon1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {Dlon}\n~~~");

            /*
            Convert to Radians and Build hav(θ) formula
            */
            Console.WriteLine($"~ Hav({Symbols.DELTA}{Symbols.PHI})");
            Console.WriteLine($"~ Hav({Dlat}{Symbols.DEGREE})");
            double hav1 = Haversine.Hav_deg(Dlat, Printing: true);

            Console.WriteLine($"\n~ Hav({Symbols.DELTA}{Symbols.LAMBDA})");
            Console.WriteLine($"~ Hav({Dlon}{Symbols.DEGREE})");
            double hav2 = Haversine.Hav_deg(Dlon, Printing: true);

            double cos1 = Math.Cos(Haversine.deg2rad(lat1));
            double cos2 = Math.Cos(Haversine.deg2rad(lat2));

            // Plug everything
            double Hav = hav1 + cos1 * cos2 * hav2;
            Console.WriteLine($"\nhav({Symbols.THETA}) = hav({Symbols.DELTA}{Symbols.PHI}) + cos({Symbols.PHI}{Symbols.SB1}) * cos({Symbols.PHI}{Symbols.SB2}) * hav({Symbols.DELTA}{Symbols.LAMBDA})");
            Console.WriteLine($"hav({Symbols.THETA}) = hav({Dlat}) + cos({lat1}) * cos({lat2}) * hav({Dlon})");
            Console.WriteLine($"hav({Symbols.THETA}) = {hav1} + {cos1} * {cos2} * {hav2}");
            Console.WriteLine($"hav({Symbols.THETA}) = {Hav}");

            // Find theta
            double T = 2 * Math.Asin(Math.Sqrt(Hav));
            Console.WriteLine($"{Symbols.THETA} = 2 * archav({Symbols.SQRT}(1 - hav)))");
            Console.WriteLine($"{Symbols.THETA} = 2 * arcsin({Symbols.SQRT}({Hav})");
            Console.WriteLine($"{Symbols.THETA} = {T}");

            // Find d with theta
            double d = R * T;
            Console.WriteLine($"d = R * θ{Symbols.RAD}");
            Console.WriteLine($"d = {R} * {T}");
            Console.WriteLine($"d {Symbols.APRX} {d} KM");
            Console.WriteLine($"d {Symbols.APRX} {Math.Round(d, 2)} KM");

            return d;
        }

        /*
        based on Radian formula (With Printing)

        hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ = 2 * arctan2(√(θ), √(1-θ))
        d = R * θ
        hav(x) = sin²(x/2) = (1 - cos(x))/2
        */
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        public static double Distance_Rad(Location A, Location B)
        {
            // Print Radian coordinates 
            Console.WriteLine("Coords in Radians");
            // Latitudes
            double lat1 = A.Lat;
            double lon1 = A.Lon;
            Console.WriteLine($"{Symbols.PHI}{Symbols.SB1} = {lat1}{Symbols.RAD}");
            Console.WriteLine($"{Symbols.LAMBDA}{Symbols.SB1} = {lon1}{Symbols.RAD}\n");

            // Longitudes
            double lat2 = B.Lat;
            double lon2 = B.Lon;
            Console.WriteLine($"{Symbols.PHI}{Symbols.SB2} = {lat2}{Symbols.RAD}");
            Console.WriteLine($"{Symbols.LAMBDA}{Symbols.SB2} = {lon2}{Symbols.RAD}\n~~~");

            // Calculate Deltas
            // Delta phi
            double Dlat = Haversine.Normalize(lat2 - lat1);
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {Symbols.PHI}{Symbols.SB2} - {Symbols.PHI}{Symbols.SB1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {lat2} - {lat1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.PHI} = {Dlat}\n");

            // Delta lambda
            double Dlon = Haversine.Normalize(lon2 - lon1);
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {Symbols.LAMBDA}{Symbols.SB2} - {Symbols.LAMBDA}{Symbols.SB1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {lon2} - {lon1}");
            Console.WriteLine($"{Symbols.DELTA}{Symbols.LAMBDA} = {Dlon}\n~~~");

            // Build hav(θ) formula
            Console.WriteLine($"~  Hav({Symbols.DELTA}{Symbols.PHI})");
            Console.WriteLine($"~  Hav({Dlat})");
            double hav1 = Haversine.Hav_rad(Dlat, Printing: true);

            Console.WriteLine($"\n~  Hav({Symbols.DELTA}{Symbols.LAMBDA})");
            Console.WriteLine($"~  Hav({Dlon})");
            double hav2 = Haversine.Hav_rad(Dlon, Printing: true);
            double cos1 = Math.Cos(lat1);
            double cos2 = Math.Cos(lat2);

            // Plug everything
            double Hav = hav1 + cos1 * cos2 * hav2;
            Console.WriteLine($"\nhav({Symbols.THETA}) = hav({Symbols.DELTA}{Symbols.PHI}) + cos({Symbols.PHI}{Symbols.SB1}) * cos({Symbols.PHI}{Symbols.SB2}) * hav({Symbols.DELTA}{Symbols.LAMBDA})");
            Console.WriteLine($"hav({Symbols.THETA}) = hav({Dlat}) + cos({lat1}) * cos({lat2}) * hav({Dlon})");
            Console.WriteLine($"hav({Symbols.THETA}) = {hav1} + {cos1} * {cos2} * {hav2}");
            Console.WriteLine($"hav({Symbols.THETA}) = {Hav}\n");

            // Find theta
            double T = 2 * Math.Atan2(Math.Sqrt(Hav), Math.Sqrt(1 - Hav));
            Console.WriteLine($"{Symbols.THETA} = 2 * archav({Symbols.THETA})");
            Console.WriteLine($"{Symbols.THETA} = 2 * arctan2({Symbols.SQRT}({Symbols.THETA}), {Symbols.SQRT}(1 - {Symbols.THETA}))");
            Console.WriteLine($"{Symbols.THETA} = 2 * arctan2({Symbols.SQRT}({Hav}), {Symbols.SQRT}({1 - Hav}))");
            Console.WriteLine($"{Symbols.THETA} = {T}\n");

            // Find d with theta
            double d = R * T;
            Console.WriteLine($"d = R * θ{Symbols.RAD}");
            Console.WriteLine($"d = {R} * {T}");
            Console.WriteLine($"d {Symbols.APRX} {d} KM");
            Console.WriteLine($"d {Symbols.APRX} {Math.Round(d, 2)} KM");

            return d;
        }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        public static double Distance(Location A, Location B, bool IsRadian = false)
        {
            double lat1, lon1;
            double lat2, lon2;

            double Dlat;
            double Dlon;

            double hav1;
            double hav2;
            double cos1;
            double cos2;

            double Hav, T, d;

            if (!IsRadian)
            {
                lat1 = A.Lat;
                lon1 = A.Lon;
                lat2 = B.Lat;
                lon2 = B.Lon;

                Dlat = Haversine.Normalize(lat2 - lat1);
                Dlon = Haversine.Normalize(lon2 - lon1);

                hav1 = Haversine.Hav_deg(Dlat);
                hav2 = Haversine.Hav_deg(Dlon);
                cos1 = Math.Cos(Haversine.deg2rad(lat1));
                cos2 = Math.Cos(Haversine.deg2rad(lat2));
                Hav = hav1 + cos1 * cos2 * hav2;
                T = 2 * Math.Asin(Math.Sqrt(Hav));
                d = R * T;
                return d;
            }
            else
            {
                lat1 = A.Lat;
                lon1 = A.Lon;
                lat2 = B.Lat;
                lon2 = B.Lon;

                Dlat = Haversine.Normalize(lat2 - lat1);
                Dlon = Haversine.Normalize(lon2 - lon1);

                hav1 = Haversine.Hav_rad(Dlat);
                hav2 = Haversine.Hav_rad(Dlon);
                cos1 = Math.Cos(lat1);
                cos2 = Math.Cos(lat2);
                Hav = hav1 + cos1 * cos2 * hav2;
                T = 2 * Math.Atan2(Math.Sqrt(Hav), Math.Sqrt(1 - Hav));
                d = R * T;
                return d;
            }
        }
    }
}
/* end Distance.cs */
