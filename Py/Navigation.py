import random
import math as m
# import sympy as s
from os import get_terminal_size as tz
from typing import Any

'''
Symbols for the road
'''
# x, y = s.symbols("x y")
# havf = s.Function("hav")(x)     # type: ignore

# Math symbols
DEGREE = "\u00b0"
RAD = " RAD"
SQRT = "\u221a"
APRX = "\u2248"

# Earth radius
R = 6378

# Sum-script 1
SUB_1 = "\u2081"
SUB_2 = "\u2082"

class Misc:
    def printmid(self, text: str ="Hello", char:str ="=", offset: int = 0, printing: bool = False)-> str | None:
        """
        Print text centered with borders.

        Parameters:
            text (str): Text to print.
            offset (int): Extra width to add to terminal size.
            p (bool): Whether to print the text or return it.

        Returns:
            str: The centered text (if p=False).
        """
        terminal_width = tz().columns + offset
        border_length = (terminal_width - len(text) - 4) // 2
        top_border = f"{char}" * border_length
        bottom_border = f"{char}" * (border_length + (len(text) % 2))
        content = f"{top_border}[{text}]{bottom_border}"
        if printing:
            return content
        else:
            print(content)

    def colortx(self, tx: str, hex: str = "75fb7e") -> str:
        """
        Apply ANSI color formatting to text.

        Parameters:
            tx (str): Text to colorize.
            hex (str): Hex color code (e.g., 'ff0000' for red).

        Returns:
            str: ANSI color-formatted string.
        """
        
        if hex.lower() == "random":
            # Generate random colors for each character in the string
            colored_chars = []
            for char in tx:
                rgb = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
                colored_char = f"\033[38;2;{rgb[0]};{rgb[1]};{rgb[2]}m{char}\033[0m"
                colored_chars.append(colored_char)
            return ''.join(colored_chars)
        else:
            # Single color for the whole text
            hex = hex.lstrip('#')
            rgb = tuple(int(hex[i:i+2], 16) for i in (0, 2, 4))
            return f"\033[38;2;{rgb[0]};{rgb[1]};{rgb[2]}m{tx}\033[0m"
    
    def Printer(self, Coords: list = [], Symbol:str = DEGREE) -> None:
        Len = len(Coords)
        if Len == 0:
            print(f"{self.colortx("Error!", "e28177")} Coords list is empty!")
        elif Len == 2:
            lat = Coords[0]
            lon = Coords[1]
            print(f"φ = {lat}{DEGREE}\nλ = {lon}{DEGREE}")

# Greek Symbols
DELTA = "\u0394"

THETA = "\u03b8"
PHI = "\u03d5"
LAMBDA = "\u03bb"

C_DELTA = Misc().colortx("\u0394", "73c069")
C_THETA = Misc().colortx("\u03b8", "ff8a46")
C_PHI = Misc().colortx("\u03d5", "109696")
C_LAMBDA = Misc().colortx("\u03bb", "dfc47d")

C_SS = [C_THETA, C_PHI, C_LAMBDA, C_DELTA]

print(C_SS)
for i in C_SS: print(i)

class Haversin:
    def hav(self,x, isRadian = True) -> int|float:
        if isRadian:
            x = x
        else:
            x = m.radians(x)
        
        cos = m.cos(x)
        Hav = (1 - cos)/2
        
        print(f">>> x = {x}")
        print(f">>> cos(x) = {cos}")
        print(f">>> 1-cos(x) = {1 - cos}")
        print(f">>> hav(x) = {Hav}\n")
        return Hav

    def hav_degree(self,x) -> int|float:
        # radian-ize the Angle
        # because python expect angle in radian
        x = m.radians(x)
        
        cos = m.cos(x)
        Hav = (1 - cos)/2
        
        print(f">>> x = {x}")
        print(f">>> cos(x) = {cos}")
        print(f">>> 1-cos(x) = {1 - cos}")
        print(f">>> hav(x) = {Hav}\n")
        return Hav

class Distance_2D:
    def Distance_Radians(self, A: list[int|float], B: list[int|float]) -> float:
        r'''
        based on Generic formula using Radian:
        hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ = 2 * arctan2(√(θ), √(1-θ))
        d = R * θ

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        '''

        ''' Choords in Degrees '''
        print(f"Coords {DEGREE}:")

        lat1 = A[0]
        print(f"{PHI}{SUB_1} = {lat1}{DEGREE}")
        lon1 = A[1]
        print(f"{LAMBDA}{SUB_1} = {lon1}{DEGREE}\n")

        lat2 = B[0]
        print(f"{PHI}{SUB_2} = {lat2}{DEGREE}")
        lon2 = B[1]
        print(f"{LAMBDA}{SUB_2} = {lon2}{DEGREE}\n~~~")

        dLat = lat2 - lat1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lat2} - {lat1}")
        print(f"{DELTA}{PHI} = {dLat}\n")

        dLon = lon2 - lon1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lon2} - {lon1}")
        print(f"{DELTA}{PHI} = {dLon}\n~~~")

        ''' Choords in Radians '''
        print(f"Coords {RAD}:")

        lat1 = m.radians(A[0])
        print(f"{PHI}{SUB_1} = {lat1}{RAD}")
        lon1 = m.radians(A[1])
        print(f"{LAMBDA}{SUB_1} = {lon1}{RAD}\n")

        lat2 = m.radians(B[0])
        print(f"{PHI}{SUB_2} = {lat2}{RAD}")
        lon2 = m.radians(B[1])
        print(f"{LAMBDA}{SUB_2} = {lon2}{RAD}\n~~~")

        ''' Deltas '''
        dLat = lat2 - lat1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lat2} - {lat1}")
        print(f"{DELTA}{PHI} = {dLat}\n")

        dLon = lon2 - lon1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lon2} - {lon1}")
        print(f"{DELTA}{PHI} = {dLon}\n~~~")

        cos1 = m.cos(lat1)
        cos2 = m.cos(lat2)

        print(f">>  hav({DELTA}{PHI})")
        print(f">>  hav({dLat})")
        hav1 = Haversin().hav(dLat)
        
        print(f">>  hav({DELTA}{LAMBDA})")
        print(f">>  hav({dLon})")
        hav2 = Haversin().hav(dLon)

        HAV = hav1 + cos1 * cos2 * hav2
        print(f"hav({THETA}) = hav({DELTA}{PHI}) + cos({PHI}{SUB_1}) * cos({PHI}{SUB_2}) * hav({DELTA}{LAMBDA})")
        print(f"hav({THETA}) = hav({dLat}) + cos({lat1}) * cos({lat2}) * hav({dLon})")
        print(f"hav({THETA}) = {hav1} + {cos1} * {cos2} * {hav2}")
        print(f"hav({THETA}) = {HAV}")

        T = 2 * m.atan2(m.sqrt(HAV), m.sqrt(1 - HAV))
        print(f"{THETA} = 2 * archav({THETA})")
        print(f"{THETA} = 2 * arctan2({SQRT}({THETA}), {SQRT}(1 - {THETA}))")
        print(f"{THETA} = 2 * arctan2({SQRT}({HAV}), {SQRT}({1 - HAV}))")
        print(f"{THETA} = {T}")

        d = R * T
        print(f"d = R * θ")
        print(f"d = {R} * {T}")
        print(f"d {APRX} {d} KM")
        print(f"d {APRX} {d:.2f} KM")

        return d
    
    def Distance_Degrees(self, A: list[int|float], B: list[int|float]):
        r'''
        based on Wikipedia article:
        https://en.wikipedia.org/wiki/Haversine_formula

        formula:
        hav(θ°) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ° = 2 * archav(θ)
        d = R * θ°

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        archav(θ) = 2 * arcsin(√(θ)) = 2 * arctan2(√(θ), √(1-θ))
        '''

        ''' Choords in Degrees '''
        print("Coords:")

        lat1 = A[0]
        print(f"{PHI}{SUB_1} = {lat1}{DEGREE}")
        lon1 = A[1]
        print(f"{LAMBDA}{SUB_1} = {lon1}{DEGREE}\n")

        lat2 = B[0]
        print(f"{PHI}{SUB_2} = {lat2}{DEGREE}")
        lon2 = B[1]
        print(f"{LAMBDA}{SUB_2} = {lon2}{DEGREE}\n~~~")

        ''' Deltas '''
        ''' Δφ '''
        dLat = lat2 - lat1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lat2} - {lat1}")
        print(f"{DELTA}{PHI} = {dLat}\n")

        ''' Δλ '''
        dLon = lon2 - lon1
        print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        print(f"{DELTA}{PHI} = {lon2} - {lon1}")
        print(f"{DELTA}{PHI} = {dLon}\n~~~")

        cos1 = m.cos(m.radians(lat1))
        cos2 = m.cos(m.radians(lat2))

        print(f">>  hav({DELTA}{PHI})")
        print(f">>  hav({dLat})")
        hav1 = Haversin().hav_degree(dLat)
        
        print(f">>  hav({DELTA}{LAMBDA})")
        print(f">>  hav({dLon})")
        hav2 = Haversin().hav_degree(dLon)
        
        HAV = hav1 + cos1 * cos2 * hav2
        print(f"hav({THETA}{DEGREE}) = hav({DELTA}{PHI}{DEGREE}) + cos({PHI}{SUB_1}{DEGREE}) * cos({PHI}{SUB_2}{DEGREE}) * hav({DELTA}{LAMBDA}{DEGREE})")
        print(f"hav({THETA}{DEGREE}) = hav({dLat}{DEGREE}) + cos({lat1}{DEGREE}) * cos({lat2}{DEGREE}) * hav({dLon}{DEGREE})")
        print(f"hav({THETA}{DEGREE}) = {hav1} + {cos1} * {cos2} * {hav2}")
        print(f"hav({THETA}{DEGREE}) = {HAV}")

        T = 2 * m.asin(m.sqrt(HAV))
        print(f"{THETA}{DEGREE} = 2 * archav({THETA}{DEGREE})")
        print(f"{THETA}{DEGREE} = 2 * arcsin({SQRT}{THETA}{DEGREE})")
        print(f"{THETA}{DEGREE} = 2 * arcsin({SQRT}{HAV})")
        print(f"{THETA}{DEGREE} = {T}{DEGREE}")

        d = R * T
        print(f"d = R * θ{DEGREE}")
        print(f"d = {R} * {T}")
        print(f"d {APRX} {d} KM")
        print(f"d {APRX} {d:.2f} KM")

        return d
    
    def Distance(self, A: list[int|float], B: list[int|float], useRadian:bool = False) -> int|float:
        '''
        The wikipedia and generic way, but without any printing

        if Radian: 
        hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ = 2 * arctan2(√(θ), √(1-θ))
        d = R * θ

        if Degree:
        hav(θ°) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ° = 2 * archav(θ)
        d = R * θ°

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        archav(θ) = 2 * arcsin(√(θ)) = 2 * arctan2(√(θ), √(1-θ))
        '''

        if useRadian:
            lat1 = m.radians(A[0])
            lon1 = m.radians(A[1])
            lat2 = m.radians(B[0])
            lon2 = m.radians(B[1])

            dLat = lat2 - lat1
            dLon = lon2 - lon1

            hav1 = (1 - m.cos(dLat))/2
            cos1 = m.cos(lat1)
            cos2 = m.cos(lat2)
            hav2 = (1 - m.cos(dLon))/2

            HAV = hav1 + cos1 * cos2 * hav2
            T = 2 * m.atan2(m.sqrt(HAV), m.sqrt(1 - HAV))
            d = R * T

            return d

        else:
            lat1 = A[0]
            lon1 = A[1]
            lat2 = B[0]
            lon2 = B[1]

            dLat = lat2 - lat1
            dLon = lon2 - lon1

            hav1 = (1 - m.cos(m.radians(dLat)))/2
            cos1 = m.cos(m.radians(lat1))
            cos2 = m.cos(m.radians(lat2))
            hav2 = (1 - m.cos(m.radians(dLon)))/2

            HAV = hav1 + cos1 * cos2 * hav2
            T = 2 * m.atan2(m.sqrt(HAV), m.sqrt(1 - HAV))
            d = R * T

            return d

class Distance_3D:
    '''
    # 3D Distance calculator
    Calculate triaxis distance
        φ = x in Degrees
        λ = y in Degrees
        h = z in Meter

    *For printing: Not to be confused with \u2212 and \u002d
    '''

    def Printer(self, Coord: list[int|float], num: str|int = "" ) -> None:
        if str(num) == "":
            print(f"φ = {Coord[0]}")
            print(f"λ = {Coord[1]}")
            print(f"h = {Coord[2]}\n")
        else:
            print(f"φ{num} = {Coord[0]}")
            print(f"λ{num} = {Coord[1]}")
            print(f"h{num} = {Coord[2]}\n")

    def KM_to_NM(self, KM:int|float) -> float:
        return KM/1.852
    
    def FT_to_KM(self, FT:int|float) -> float:
        return FT/3281

    def FT_to_M(self, FT:int|float) -> float:
        return (FT/3281)*1000
    
    def Distance_2D(self, A: list[int|float], B: list[int|float]) -> int|float:
        '''
        The wikipedia (degrees) and generic (radians) way,
        but without any printing and in **degrees**

        hav(θ°) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ° = 2 * archav(θ)
        d = R * θ°

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        archav(θ) = 2 * arcsin(√(θ)) = 2 * arctan2(√(θ), √(1-θ))

        return in KM
        '''
        lat1 = A[0]
        lon1 = A[1]
        lat2 = B[0]
        lon2 = B[1]

        dLat = lat2 - lat1
        dLon = lon2 - lon1

        hav1 = (1 - m.cos(m.radians(dLat)))/2
        cos1 = m.cos(m.radians(lat1))
        cos2 = m.cos(m.radians(lat2))
        hav2 = (1 - m.cos(m.radians(dLon)))/2

        HAV = hav1 + cos1 * cos2 * hav2
        d = R * (2 * m.atan2(m.sqrt(HAV), m.sqrt(1 - HAV))) # R * Theta

        return d
        
    def Distance_Pyth(self, A: list[int|float], B: list[int|float]) -> int|float:
        '''
        ACHTUNG: ONLY FOR SHORT DISTANCES (0~1 KM)

        Using the Pythagoras method
        
        Steps
        - Find base using the Haversine formula
        - Find height using h2 - h1 in KM
        - Find slope or "Hypotenuse" using sqrt(base**2 + height**2)
        
        return in KM
        '''
        base = Distance_3D().Distance_2D(A, B)

        h1 = self.FT_to_KM(A[2])
        h2 = self.FT_to_KM(B[2])

        height = h2 - h1

        slope = m.sqrt(base**2 + height**2)

        return slope

        
    def Distance_ECEF(self, A: list[int|float], B: list[int|float]) -> float:
        '''
        Input:
        [φ, λ, h]
        φ and λ are in Degrees
        h is in FT

        #### Step 1: Find prime vertical radius
        N = a / sqrt(1 - e² * sin²(φ))

        #### Step 2: Find ECEF for each axises
        X = (N + h) * cos(φ) * cos(λ)
        Y = (N + h) * cos(φ) * sin(λ)
        Z = (N * (1 - e²) + h) * sin(φ)

        #### Step 3: Find final 3D Distance
        d = √[(x₂-x₁)² + (y₂-y₁)² + (z₂-₁)²]
        '''
        # Constants from WGS84 Ellipsoid
        a = 6_378_137           # semi-major axis in meters
        e_sq = 6.69437999014e-3  # first eccentricity squared

        print(f"3D Distance with ECEF")

        # Unpack and convert inputs
        lat1_deg, lon1_deg, h1_ft = A
        lat2_deg, lon2_deg, h2_ft = B

        lat1 = m.radians(lat1_deg)
        lon1 = m.radians(lon1_deg)
        h1 = self.FT_to_M(h1_ft)

        lat2 = m.radians(lat2_deg)
        lon2 = m.radians(lon2_deg)
        h2 = self.FT_to_M(h2_ft)

        self.Printer([lat1_deg, lon1_deg, h1_ft], "₁")
        self.Printer([lat2_deg, lon2_deg, h2_ft], "₂")

        # Step 1: Prime Vertical Radius of Curvature
        N1 = a / m.sqrt(1 - e_sq * m.sin(lat1)**2)
        N2 = a / m.sqrt(1 - e_sq * m.sin(lat2)**2)

        # Step 2: Compute ECEF Coordinates
        X1 = (N1 + h1) * m.cos(lat1) * m.cos(lon1)
        Y1 = (N1 + h1) * m.cos(lat1) * m.sin(lon1)
        Z1 = (N1 * (1 - e_sq) + h1) * m.sin(lat1)

        X2 = (N2 + h2) * m.cos(lat2) * m.cos(lon2)
        Y2 = (N2 + h2) * m.cos(lat2) * m.sin(lon2)
        Z2 = (N2 * (1 - e_sq) + h2) * m.sin(lat2)

        # Print intermediate values
        print("ECEF Coordinates:")
        print(f"X₁ = {X1:.3f}, Y₁ = {Y1:.3f}, Z₁ = {Z1:.3f}")
        print(f"X₂ = {X2:.3f}, Y₂ = {Y2:.3f}, Z₂ = {Z2:.3f}")

        # Step 3: 3D Euclidean Distance
        dX = X2 - X1
        dY = Y2 - Y1
        dZ = Z2 - Z1

        distance_m = m.sqrt(dX**2 + dY**2 + dZ**2)
        distance_km = distance_m / 1000

        print(f"\nDistance Formula:")
        print(f"d = √[(x₂−x₁)² + (y₂−y₁)² + (z₂−z₁)²]")
        print(f"d = √[({X2:.3f}−{X1:.3f})² + ({Y2:.3f}−{Y1:.3f})² + ({Z2:.3f}−{Z1:.3f})²]")
        print(f"d = √[({dX:.3f})² + ({dY:.3f})² + ({dZ:.3f})²]")
        print(f"d = {distance_m:.3f} M = {distance_km:.3f} KM")

        return distance_km
    
    def Distance(self, A: list[int|float], B: list[int|float], ForceECEF:bool = False) -> int|float:
        d = self.Distance_2D(A, B)
        d = round(d, 5)

        if d < 1.00000:
            if ForceECEF:
                return self.Distance_ECEF(A, B)
            else:
                return self.Distance_Pyth(A, B)
        else:
            return self.Distance_ECEF(A, B)
        
    def Flight(self, Runway: dict, FlightPlan: dict):
        """
        Compute 2D and 3D distances between every pair of consecutive flight points,
        including runway-to-first and last-to-runway segments.

        Args:
            Runway (dict): Contains departure and arrival points
            FlightPlan (dict): Dictionary of intermediate waypoints
        """

        print("\n")
        Misc().printmid(" FLIGHT DISTANCE CALCULATION ", "=")
        print("\n")

        # Extract departure and arrival
        departure_name, departure_coords = list(Runway.items())[0]
        arrival_name, arrival_coords = list(Runway.items())[-1]

        # Convert all keys to list of tuples: ('I', [lat, lon, h])
        plan_list = list(FlightPlan.items())
        plan_keys = [k for k, _ in plan_list]
        plan_vals = [v for _, v in plan_list]

        # Insert departure at start
        plan_keys.insert(0, departure_name)
        plan_vals.insert(0, departure_coords)

        # Append arrival at end
        plan_keys.append(arrival_name)
        plan_vals.append(arrival_coords)

        total_2d = 0
        total_3d = 0

        for i in range(len(plan_vals) - 1):
            name1 = plan_keys[i]
            point1 = plan_vals[i]
            name2 = plan_keys[i + 1]
            point2 = plan_vals[i + 1]

            print(f"{name1} → {name2}")
            d2d = self.Distance_2D(point1, point2)
            d3d = self.Distance_ECEF(point1, point2)

            total_2d += d2d
            total_3d += d3d

            print(f" 2D Distance: {d2d:.3f} km")
            print(f" 3D Distance: {d3d:.3f} km\n")

        print("-" * tz().columns)
        print(f"Total 2D Distance: {total_2d:.3f} km")
        print(f"Total 3D Distance: {total_3d:.3f} km")
        print("-" * tz().columns)

    class NoPrint:
        def Distance_2D(self, A, B):
            return Distance_3D().Distance_2D(A, B)
        
        def Distance_ECEF(self, A: list[int|float], B: list[int|float]) -> float:
            '''
            Input:
            [φ, λ, h]
            φ and λ are in Degrees
            h is in FT

            #### Step 1: Find prime vertical radius
            N = a / sqrt(1 - e² * sin²(φ))

            #### Step 2: Find ECEF for each axises
            X = (N + h) * cos(φ) * cos(λ)
            Y = (N + h) * cos(φ) * sin(λ)
            Z = (N * (1 - e²) + h) * sin(φ)

            #### Step 3: Find final 3D Distance
            d = √[(x₂-x₁)² + (y₂-y₁)² + (z₂-₁)²]
            '''
            # Constants from WGS84 Ellipsoid
            a = 6_378_137           # semi-major axis in meters
            e_sq = 6.69437999014e-3  # first eccentricity squared

            # print(f"3D Distance with ECEF")

            # Unpack and convert inputs
            lat1_deg, lon1_deg, h1_ft = A
            lat2_deg, lon2_deg, h2_ft = B

            lat1 = m.radians(lat1_deg)
            lon1 = m.radians(lon1_deg)
            h1 = Distance_3D().FT_to_M(h1_ft)

            lat2 = m.radians(lat2_deg)
            lon2 = m.radians(lon2_deg)
            h2 = Distance_3D().FT_to_M(h2_ft)

            # Step 1: Prime Vertical Radius of Curvature
            N1 = a / m.sqrt(1 - e_sq * m.sin(lat1)**2)
            N2 = a / m.sqrt(1 - e_sq * m.sin(lat2)**2)

            # Step 2: Compute ECEF Coordinates
            X1 = (N1 + h1) * m.cos(lat1) * m.cos(lon1)
            Y1 = (N1 + h1) * m.cos(lat1) * m.sin(lon1)
            Z1 = (N1 * (1 - e_sq) + h1) * m.sin(lat1)

            X2 = (N2 + h2) * m.cos(lat2) * m.cos(lon2)
            Y2 = (N2 + h2) * m.cos(lat2) * m.sin(lon2)
            Z2 = (N2 * (1 - e_sq) + h2) * m.sin(lat2)

            # Step 3: 3D Euclidean Distance
            dX = X2 - X1
            dY = Y2 - Y1
            dZ = Z2 - Z1

            distance_m = m.sqrt(dX**2 + dY**2 + dZ**2)
            distance_km = distance_m / 1000

            return distance_km

        def Flight(self, Runway: dict, FlightPlan: dict) -> float | Any:
            """
            Compute 2D and 3D distances between every pair of consecutive flight points,
            including runway-to-first and last-to-runway segments.

            Args:
                Runway (dict): Contains departure and arrival points
                FlightPlan (dict): Dictionary of intermediate waypoints
            """

            print("\n")
            # Misc().printmid(" FLIGHT DISTANCE CALCULATION ", "=")
            print("\n")

            # Extract departure and arrival
            departure_name, departure_coords = list(Runway.items())[0]
            arrival_name, arrival_coords = list(Runway.items())[-1]

            # Convert all keys to list of tuples: ('I', [lat, lon, h])
            plan_list = list(FlightPlan.items())
            plan_keys = [k for k, _ in plan_list]
            plan_vals = [v for _, v in plan_list]

            # Insert departure at start
            plan_keys.insert(0, departure_name)
            plan_vals.insert(0, departure_coords)

            # Append arrival at end
            plan_keys.append(arrival_name)
            plan_vals.append(arrival_coords)

            total_2d = 0
            total_3d = 0

            for i in range(len(plan_vals) - 1):
                name1 = plan_keys[i]
                point1 = plan_vals[i]
                name2 = plan_keys[i + 1]
                point2 = plan_vals[i + 1]

                d2d = self.Distance_2D(point1, point2)
                d3d = self.Distance_ECEF(point1, point2)

                total_2d += d2d
                total_3d += d3d

            return total_3d
