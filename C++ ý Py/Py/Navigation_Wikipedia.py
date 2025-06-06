import math as m
import sympy as s
from os import get_terminal_size as tz

'''
Symbols for the road
'''
# x, y = s.symbols("x y")
# havf = s.Function("hav")(x)     # type: ignore

# Greek Symbols
DELTA = "\u0394"
THETA = "\u03b8"
PHI = "\u03d5"
LAMBDA = "\u03bb"

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

def Distance_Wikipedia(A: list[int|float], B: list[int|float]):
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
    print(f"{THETA}{DEGREE} = 2 * archav({THETA}{DEGREE})")
    print(f"{THETA}{DEGREE} = 2 * arcsin({SQRT}{THETA}{DEGREE})")
    print(f"{THETA}{DEGREE} = 2 * arcsin({SQRT}{HAV})")
    print(f"{THETA}{DEGREE} = {T}{DEGREE}")

    d = R * T
    print(f"d = R * θ{DEGREE}")
    print(f"d = {R} * {T}")
    print(f"d = {d}")
    

def main() -> None:
    SV_IPB    = [-6.588457, 106.806200]
    Danau_IPB = [-6.559582, 106.726720]

    C = [SV_IPB, Danau_IPB]
    print(f"Chords = {C}\n")
    Distance_Wikipedia(C[0], C[1])

main()