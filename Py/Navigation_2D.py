import random
import math as m
from os import get_terminal_size as tz
from typing import List

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

'''
Symbols for the road
'''
# x, y = s.symbols("x y")
# havf = s.Function("hav")(x)     # type: ignore

# Greek Symbols
DELTA = "\u0394"
THETA = Misc().colortx("\u03b8", "ff8a46")
PHI = Misc().colortx("\u03d5", "109696")
LAMBDA = Misc().colortx("\u03bb", "dfc47d")

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


def hav(x, isRadian = True) -> int|float:
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

def hav_degree(x) -> int|float:
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
    def Distance_Radians(self, A: list[int|float], B: list[int|float]):
        r'''
        based on Generic formula using Radian:
        hav(θ) = hav(Δφ) + cos(φ₁) * cos(φ₂) * hav(Δλ)
        θ = 2 * arctan2(√(θ), √(1-θ))
        d = R * θ

        hav(x) = sin²(x/2) = (1 - cos(x))/2
        '''

        # ''' Choords in Degrees '''
        # print(f"Coords {DEGREE}:")

        # lat1 = A[0]
        # print(f"{PHI}{SUB_1} = {lat1}{DEGREE}")
        # lon1 = A[1]
        # print(f"{LAMBDA}{SUB_1} = {lon1}{DEGREE}\n")

        # lat2 = B[0]
        # print(f"{PHI}{SUB_2} = {lat2}{DEGREE}")
        # lon2 = B[1]
        # print(f"{LAMBDA}{SUB_2} = {lon2}{DEGREE}\n~~~")

        # dLat = lat2 - lat1
        # print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        # print(f"{DELTA}{PHI} = {lat2} - {lat1}")
        # print(f"{DELTA}{PHI} = {dLat}\n")

        # dLon = lon2 - lon1
        # print(f"{DELTA}{PHI} = {PHI}{SUB_2} - {PHI}{SUB_1}")
        # print(f"{DELTA}{PHI} = {lon2} - {lon1}")
        # print(f"{DELTA}{PHI} = {dLon}\n~~~")

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
        print(f"{DELTA}{LAMBDA} = {LAMBDA}{SUB_2} - {LAMBDA}{SUB_1}")
        print(f"{DELTA}{LAMBDA} = {lon2} - {lon1}")
        print(f"{DELTA}{LAMBDA} = {dLon}\n~~~")

        cos1 = m.cos(lat1)
        cos2 = m.cos(lat2)

        print(f">>  hav({DELTA}{PHI})")
        print(f">>  hav({dLat})")
        hav1 = hav(dLat)
        
        print(f">>  hav({DELTA}{LAMBDA})")
        print(f">>  hav({dLon})")
        hav2 = hav(dLon)

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
        print(f"{DELTA}{LAMBDA} = {LAMBDA}{SUB_2} - {LAMBDA}{SUB_1}")
        print(f"{DELTA}{LAMBDA} = {lon2} - {lon1}")
        print(f"{DELTA}{LAMBDA} = {dLon}\n~~~")

        cos1 = m.cos(m.radians(lat1))
        cos2 = m.cos(m.radians(lat2))

        print(f">>  hav({DELTA}{PHI})")
        print(f">>  hav({dLat})")
        hav1 = hav_degree(dLat)
        
        print(f">>  hav({DELTA}{LAMBDA})")
        print(f">>  hav({dLon})")
        hav2 = hav_degree(dLon)
        
        HAV = hav1 + cos1 * cos2 * hav2
        print(f"hav({THETA}{DEGREE}) = hav({DELTA}{PHI}{DEGREE}) + cos({PHI}{SUB_1}{DEGREE}) * cos({PHI}{SUB_2}{DEGREE}) * hav({DELTA}{LAMBDA}{DEGREE})")
        print(f"hav({THETA}{DEGREE}) = hav({dLat}{DEGREE}) + cos({lat1}{DEGREE}) * cos({lat2}{DEGREE}) * hav({dLon}{DEGREE})")
        print(f"hav({THETA}{DEGREE}) = {hav1} + {cos1} * {cos2} * {hav2}")
        print(f"hav({THETA}{DEGREE}) = {HAV}")

        T = 2 * m.asin(m.sqrt(HAV))
        print(f"{THETA}{DEGREE} = 2 * archav(hav({THETA}))")
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
    
class Navigation:
    def Nav2D(self, Points: List[List[float]], isRadian:bool = False) -> float:
        """
        Calculate total 2D distance from a list of [lat, lon] points.
        
        Args:
            Points: List of [latitude, longitude] pairs
        
        Returns:
            Total distance in kilometers
        """
        if len(Points) < 2:
            raise ValueError("Need at least two points to compute distance")

        total_distance = 0.0
        for i in range(len(Points) - 1):
            total_distance += Distance_2D().Distance(Points[i], Points[i+1], isRadian)

        return total_distance

class Main:
    def Test2Points(self) -> None:
        SV_IPB    = [-6.588457, 106.806200]
        Danau_IPB = [-6.559582, 106.726720]

        # arr = [i for i in range(10) print(i)]

        C_D = [SV_IPB, Danau_IPB]
        print(f"Chords Degrees = {C_D}\n")
        C_R = [[round(m.radians(i), 6) for i in SV_IPB], [round(m.radians(i), 6) for i in Danau_IPB]]

        print(f"Chords Radians = {C_R}\n")
        
        Misc().printmid(" Degrees ", "-")
        W = Distance_2D().Distance_Degrees(SV_IPB, Danau_IPB)
        Misc().printmid(" Radians ", "-")
        G = Distance_2D().Distance_Radians(SV_IPB, Danau_IPB)

        print("~"*tz().columns)

        W = Distance_2D().Distance(SV_IPB, Danau_IPB)
        G = Distance_2D().Distance(SV_IPB, Danau_IPB, useRadian=True)

        print(f"Degrees = {W} KM")
        print(f"Radians = {G} KM")

        if W == G:
            print("APPROVED!")
        else:
            print("meh")
        
    def TestDriving(self) -> None:
        # From Church of Zebaoth to Lippo Plaza Ekalokasari
        Start = [-6.597833622666178, 106.794373367117]
        Finish = [-6.62225014590596, 106.8175039391197]
        Driving = [
            Start,
            [-6.597052825849262, 106.7937717227824],
            [-6.594705841518939, 106.7942047962342],
            [-6.593604212378643, 106.7961204047717],
            [-6.593158753811323, 106.7965106718923],
            [-6.59358588035416, 106.7977024324252],
            [-6.592574319321151, 106.7996765661645],
            [-6.592563005485911, 106.8017069133976],
            [-6.594667559352246, 106.8025736217902],
            [-6.595509737648851, 106.8040512684551],
            [-6.600999297161692, 106.8050744834284],
            [-6.603626052516093, 106.8060427964824],
            [-6.604047858096131, 106.806516050656],
            [-6.601627793206586, 106.8105263916231],
            [-6.601627793206586, 106.8105263916231],
            [-6.604752634429251, 106.8069558676157],
            [-6.605464978116315, 106.8073990601912],
            [-6.606909664145737, 106.8079136645895],
            [-6.615939116766738, 106.8142013219661],
            [-6.620564055949383, 106.8158072006643],
            [-6.622434959044009, 106.8173220950337],
            Finish
        ]

        Driving_Distance:float = Navigation().Nav2D(Driving)

        for n, D in enumerate(Driving, start=1):
            print(f"Driving {f"{n:^2}"} = {D}")
        print(f"Start = {Start}")
        print(f"Finish = {Finish}\n")
        
        print(f"Start -> Finish = {Distance_2D().Distance(Start, Finish, False)} KM")
        print(f"Start -> Driving -> Finish = {Driving_Distance}")

if __name__ == "__main__":
    Main().Test2Points()
    Main().TestDriving()
