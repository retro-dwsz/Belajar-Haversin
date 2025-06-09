from enum import Enum
import math as m
from os import get_terminal_size as gts

class Unit(Enum):
    Degree = "\u00B0"
    Radian = "RAD"

class Symbols(Enum):
    Degree = Unit.Degree.value
    Radian = Unit.Radian.value
    
    PHI    = "\u03D5"
    LAMBDA = "\u03BB"
    DELTA  = "\u0394"
    THETA  = "\u03B8"

    C_DELTA  = "\x1b[38;2;115;192;105m\u0394\x1b[0m"    # Color: 73c069
    C_THETA  = "\x1b[38;2;255;138;70m\u03b8\x1b[0m"     # Color: ff8a46
    C_PHI    = "\x1b[38;2;16;150;150m\u03d5\x1b[0m"     # Color: 109696
    C_LAMBDA = "\x1b[38;2;223;196;125m\u03bb\x1b[0m"    # Color: dfc47d

    # Math symbols
    DEGREE  = "\u00b0"    # °
    RAD     = " RAD"      # RAD
    SQRT    = "\u221a"    # √
    APRX    = "\u2248"    # ≈

    # Subscripts
    SB1 = "\u2081"    # ₁
    SB2 = "\u2082"    # ₂

class Misc:
    TerminalSize = gts().columns
    
    @staticmethod
    def PrintMid(Text:str = "Hello!", Char:str = "=", offset:int = 2, Printing:bool = False) -> str|None:
        Width:int = Misc.TerminalSize + offset
        Border:int = (Width - len(Text) - 4) // 2
        
        Left = f"{Char}" * Border
        Right = f"{Char}" * (Border + (len(Text) % 2))
        content = f"{Left}[{Text}]{Right}"
        if Printing:
            return content
        else:
            print(content)
            return None

class Location:
    Name:str = ""
    Lat:float|int = 0
    Lon:float|int = 0
    Coords:list[float|int] = []
    
    Unit:Unit
    Symbol:Symbols = ""
    
    def __init__(self, Name:str = "MyLocation", Lat:float|int = 0, Lon:float|int = 0, IsRadian:bool = False ) -> None:
        self.Name = Name
        self.Lat = Lat
        self.Lon = Lon
        
        if IsRadian:
            self.Unit = Unit.Radian
            self.Symbol = Symbols.Radian.value
        else:
            self.Unit = Unit.Degree
            self.Symbol = Symbols.Degree.value
            
        self.Coords.extend([Lat, Lon])
        
    def Printer(self) -> None:
        print(f"{self.Name} Coords in {self.Unit}")
        print(f"{Symbols.PHI.value} = {self.Lat}{self.Symbol}")
        print(f"{Symbols.THETA.value} = {self.Lon}{self.Symbol}")
    
    def toRadian(self, SupressWarning:bool = False, Force:bool = False) -> None:
        if self.Unit == Unit.Radian:
            if not SupressWarning and Force:
                print(f"Warning: Already in Radians, but forced conversion is enabled")
            elif not SupressWarning:
                print(f"Warning: Already in Radians")
                # return self.Coords
        
        self.Lat = self.Lat * m.pi / 180
        self.Lon = self.Lon * m.pi / 180
        
        self.Unit = Unit.Radian
        self.Symbol = Symbols.Radian.value
        
        self.Coords.clear()
        self.Coords.extend([self.Lat, self.Lon])
    
    def toRadian(self, SupressWarning:bool = False, Force:bool = False) -> None:
        if self.Unit == Unit.Radian:
            if not SupressWarning and Force:
                print(f"Warning: Already in Degree, but forced conversion is enabled")
            elif not SupressWarning:
                print(f"Warning: Already in Degree")
                # return self.Coords
        
        self.Lat = self.Lat * m.pi / 180
        self.Lon = self.Lon * m.pi / 180
        
        self.Unit = Unit.Degree
        self.Symbol = Symbols.Degree.value
        
        self.Coords.clear()
        self.Coords.extend([self.Lat, self.Lon])

    def GetCoords(self):
        return self.Coords

    def GetUnit(self) -> Unit:
        return self.Unit
    
class Haversine:
    @staticmethod
    def deg2rad(Deg:float, Printing:bool = False) -> float:
        var = m.pi / 180 * Deg
        if Printing:
            print(f"Deg = {Deg}")
            print(f"Rad = {var}")
        return var
    
    @staticmethod
    def Hav_rad(x:float, Printing:bool = False) -> float:
        Cos:float = 1 - m.cos(x)
        Hav:float = Cos/2
        if Printing:
            print(f"~! x = {x}{Symbols.Radian.value}")
            print(f"~! cos(x) = {m.cos(x)}")
            print(f"~! 1-cos(x) = {Cos}")
            print(f"~! Hav(x) = {Hav}")
        return Hav

    # radian-ize the Angle
    # because Python expect angle in radian
    @staticmethod
    def Hav_deg(x:float, Printing:bool = False) -> float:
        x = Haversine.deg2rad(x)

        Cos:float = 1 - m.cos(x)
        Hav:float = Cos / 2
    
        if Printing:
            print(f"~! x = {x}{Symbols.Radian.value}")
            print(f"~! cos(x) = {m.cos(x)}")
            print(f"~! 1-cos(x) = {Cos}")
            print(f"~! Hav(x) = {Hav}")
        
        return Hav
    
    @staticmethod
    def Hav(x:float, IsRadian:bool = False, Printing:bool = False) -> None:
        if IsRadian:
            pass
        else:
            x = Haversine.deg2rad(x)
        
        Cos:float = 1 - m.cos(x)
        Hav:float = Cos/2
        
        if Printing:
            print(f"~! x = {x}{Symbols.Radian.value}")
            print(f"~! cos(x) = {m.cos(x)}")
            print(f"~! 1-cos(x) = {Cos}")
            print(f"~! Hav(x) = {Hav}")

class Distance:
    R:int = 6378
    
    @staticmethod
    def Distance_Deg(A:Location, B:Location) -> float:
        print(f"Coords in Degrees")
        
        lat1:float = A.Lat
        lon1:float = A.Lon
        print(f"{Symbols.PHI.value}{Symbols.SB1.value} = {lat1}{Symbols.DEGREE.value}")
        print(f"{Symbols.LAMBDA.value}{Symbols.SB1.value} = {lon1}{Symbols.DEGREE.value}\n")
        
        lat2:float = B.Lat
        lon2:float = B.Lon
        print(f"{Symbols.PHI.value}{Symbols.SB2.value} = {lat2}{Symbols.DEGREE.value}")
        print(f"{Symbols.LAMBDA.value}{Symbols.SB2.value} = {lon2}{Symbols.DEGREE.value}\n~~~")
        
        Dlat:float = lat2 - lat1
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {Symbols.PHI.value}{Symbols.SB2.value} - {Symbols.PHI.value}{Symbols.SB1.value}")
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {lat2} - {lat1}")
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {Dlat}\n")
        
        Dlon:float = lon2 - lon1
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {Symbols.LAMBDA.value}{Symbols.SB2.value} - {Symbols.LAMBDA.value}{Symbols.SB1.value}")
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {lon2} - {lon1}")
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {Dlon}\n~~~")

        print(f"~ Hav({Symbols.DELTA.value}{Symbols.PHI.value})")
        print(f"~ Hav({Dlat}{Symbols.DEGREE.value})")
        hav1:float = Haversine.Hav_deg(Dlat, Printing = True)

        print(f"\n~ Hav({Symbols.DELTA.value}{Symbols.LAMBDA.value})")
        print(f"~ Hav({Dlon}{Symbols.DEGREE.value})")
        hav2:float = Haversine.Hav_deg(Dlon, Printing = True)

        cos1:float = m.cos(Haversine.deg2rad(lat1))
        cos2:float = m.cos(Haversine.deg2rad(lat2))

        Hav:float = hav1 + cos1 * cos2 * hav2
        print(f"\nhav({Symbols.THETA.value}) = hav({Symbols.DELTA.value}{Symbols.PHI.value}) + cos({Symbols.PHI.value}{Symbols.SB1.value}) * cos({Symbols.PHI.value}{Symbols.SB2.value}) * hav({Symbols.DELTA.value}{Symbols.LAMBDA.value})")
        print(f"hav({Symbols.THETA.value}) = hav({Dlat}) + cos({lat1}) * cos({lat2}) * hav({Dlon})")
        print(f"hav({Symbols.THETA.value}) = {hav1} + {cos1} * {cos2} * {hav2}")
        print(f"hav({Symbols.THETA.value}) = {Hav}")

        T:float = 2 * m.asin(m.sqrt(Hav))
        print(f"{Symbols.THETA.value} = 2 * archav({Symbols.SQRT.value}(1 - hav)))")
        print(f"{Symbols.THETA.value} = 2 * arcsin({Symbols.SQRT.value}({Hav})")
        print(f"{Symbols.THETA.value} = {T}")

        d:float = Distance.R * T
        print(f"d = R * θ{Symbols.RAD.value}")
        print(f"d = {Distance.R} * {T}")
        print(f"d {Symbols.APRX.value} {d} KM")
        print(f"d {Symbols.APRX.value} {round(d, 2)} KM")

        return d
    
    @staticmethod
    def Distance_Rad(A:Location, B:Location) -> float:
        print(f"Coords in Radians")

        lat1:float = A.Lat
        lon1:float = A.Lon
        print(f"{Symbols.PHI.value}{Symbols.SB1.value} = {lat1}{Symbols.DEGREE.value}")
        print(f"{Symbols.LAMBDA.value}{Symbols.SB1.value} = {lon1}{Symbols.DEGREE.value}\n")

        lat2:float = B.Lat
        lon2:float = B.Lon
        print(f"{Symbols.PHI.value}{Symbols.SB2.value} = {lat2}{Symbols.DEGREE.value}")
        print(f"{Symbols.LAMBDA.value}{Symbols.SB2.value} = {lon2}{Symbols.DEGREE.value}\n~~~")

        Dlat:float = lat2 - lat1
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {Symbols.PHI.value}{Symbols.SB2.value} - {Symbols.PHI.value}{Symbols.SB1.value}")
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {lat2} - {lat1}")
        print(f"{Symbols.DELTA.value}{Symbols.PHI.value} = {Dlat}\n")

        Dlon:float = lon2 - lon1
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {Symbols.LAMBDA.value}{Symbols.SB2.value} - {Symbols.LAMBDA.value}{Symbols.SB1.value}")
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {lon2} - {lon1}")
        print(f"{Symbols.DELTA.value}{Symbols.LAMBDA.value} = {Dlon}\n~~~")

        print(f"~ Hav({Symbols.DELTA.value}{Symbols.PHI.value})")
        print(f"~ Hav({Dlat}{Symbols.DEGREE.value})")
        hav1:float = Haversine.Hav_rad(Dlat, Printing = True)

        print(f"\n~ Hav({Symbols.DELTA.value}{Symbols.LAMBDA.value})")
        print(f"~ Hav({Dlon}{Symbols.DEGREE.value})")
        hav2:float = Haversine.Hav_rad(Dlon, Printing = True)

        cos1:float = m.cos(lat1)
        cos2:float = m.cos(lat2)

        Hav:float = hav1 + cos1 * cos2 * hav2
        print(f"\nhav({Symbols.THETA.value}) = hav({Symbols.DELTA.value}{Symbols.PHI.value}) + cos({Symbols.PHI.value}{Symbols.SB1.value}) * cos({Symbols.PHI.value}{Symbols.SB2.value}) * hav({Symbols.DELTA.value}{Symbols.LAMBDA.value})")
        print(f"hav({Symbols.THETA.value}) = hav({Dlat}) + cos({lat1}) * cos({lat2}) * hav({Dlon})")
        print(f"hav({Symbols.THETA.value}) = {hav1} + {cos1} * {cos2} * {hav2}")
        print(f"hav({Symbols.THETA.value}) = {Hav}")

        T:float = 2 * m.asin(m.sqrt(Hav))
        print(f"{Symbols.THETA.value} = 2 * archav({Symbols.SQRT.value}(1 - hav)))")
        print(f"{Symbols.THETA.value} = 2 * arcsin({Symbols.SQRT.value}({Hav})")
        print(f"{Symbols.THETA.value} = {T}")

        d:float = Distance.R * T
        print(f"d = R * θ{Symbols.RAD.value}")
        print(f"d = {Distance.R} * {T}")
        print(f"d {Symbols.APRX.value} {d} KM")
        print(f"d {Symbols.APRX.value} {round(d, 2)} KM")

        return d
    
    @staticmethod
    def Distance(A:Location, B:Location, IsRadian:bool = False) -> float:
        lat1:float = 0
        lon1:float = 0
        lat2:float = 0
        lon2:float = 0

        Dlat:float = 0
        Dlon:float = 0

        hav1:float = 0
        hav2:float = 0
        cos1:float = 0
        cos2:float = 0

        Hav:float = 0
        T:float = 0
        d:float = 0

        if not IsRadian:
            
            lat1 = A.Lat
            lon1 = A.Lon
            lat2 = B.Lat
            lon2 = B.Lon
    
            Dlat = lat2 - lat1
            Dlon = lon2 - lon1
    
            hav1 = Haversine.Hav_deg(Dlat)
            hav2 = Haversine.Hav_deg(Dlon)
            cos1 = m.cos(Haversine.deg2rad(lat1))
            cos2 = m.cos(Haversine.deg2rad(lat2))
            Hav = hav1 + cos1 * cos2 * hav2
            T = 2 * m.asin(m.sqrt(Hav))
            d = Distance.R * T
            return d
        else:
            lat1 = A.Lat
            lon1 = A.Lon
            lat2 = B.Lat
            lon2 = B.Lon
    
            Dlat = lat2 - lat1
            Dlon = lon2 - lon1
    
            hav1 = Haversine.Hav_rad(Dlat)
            hav2 = Haversine.Hav_rad(Dlon)
            cos1 = m.cos(lat1)
            cos2 = m.cos(lat2)
            Hav = hav1 + cos1 * cos2 * hav2
            T = 2 * m.atan2(m.sqrt(Hav), m.sqrt(1 - Hav))
            d = Distance.R * T
            return d

        
class Main:
    @staticmethod
    def IPB():
        SV_IPB:Location = Location("SV IPB", -6.588457, 106.806200, IsRadian = False)
        Danau:Location = Location("Danau IPB", -6.559582, 106.726720, IsRadian = False)
        
        SV_IPB.Printer()
        Danau.Printer()
        
        Misc.PrintMid("Degree", "-")
        D:float = Distance.Distance_Deg(SV_IPB, Danau)

        Misc.PrintMid("Radian", "-")
                
        SV_IPB.toRadian()
        Danau.toRadian()
                
        R:float = Distance.Distance_Rad(SV_IPB, Danau)

        print(f"Degrees = {D} KM")
        print(f"Radians = {R} KM")
        
        if D == R:
            print("APPROVED!")
        else:
            print("meh")
            
if __name__ == "__main__":
    Main.IPB()