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

def Distance_Generic(A: list[int|float], B: list[int|float]):
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
    print(f"d = {d}")

def main() -> None:
    SV_IPB    = [-6.588457, 106.806200]
    Danau_IPB = [-6.559582, 106.726720]

    C = [SV_IPB, Danau_IPB]
    print(f"Chords = {C}\n")
    Distance_Generic(C[0], C[1])

main()