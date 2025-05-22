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
    ...