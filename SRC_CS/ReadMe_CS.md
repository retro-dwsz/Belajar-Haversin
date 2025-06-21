---

## 📘 **Dokumentasi Proyek: Implementasi Formula Haversine dalam C#**

> **Nama Proyek**: `CS_Navigation`  
> **Tujuan**: Mengimplementasikan formula **Haversine** untuk menghitung jarak antara dua titik geografis (latitude/longitude) dalam lingkungan .NET.  
> **Bahasa**: C#  
> **Target Framework**: .NET 6+  
> **Fitur Tambahan**: Visualisasi proses perhitungan, output berwarna, manipulasi string konsol

---

## 🧠 Latar Belakang

Proyek ini dirancang untuk mempelajari:
- Penggunaan konsep **OOP (Object-Oriented Programming)** di C#
- Penerapan rumus matematika (terutama **Haversine**) secara program
- Visualisasi data numerik di konsol
- Manipulasi unit sudut (derajat vs radian)
- Interaksi pengguna di CLI dengan output yang informatif dan estetik

Formula Haversine digunakan untuk menghitung jarak antara dua koordinat pada permukaan bola (dalam hal ini, bumi). Rumusnya adalah:

$$
a = \sin^2\left(\frac{\Delta\phi}{2}\right) + \cos(\phi_1)\cdot\cos(\phi_2)\cdot\sin^2\left(\frac{\Delta\lambda}{2}\right)
$$
$$
c = 2\cdot\arctan2\left(\sqrt{a}, \sqrt{1-a}\right) \ \text{atau} \
c = 2\cdot\arcsin\left(\sqrt{a}\right)
$$ 
$$
d = R \cdot c
$$

---

## 📁 Struktur Proyek

```
CS_Navigation/
│
├── Program.cs                  // Titik masuk aplikasi
├── Symbols.cs                  // Simbol matematika dan Unicode
├── Location.cs                 // Kelas lokasi geografis
├── Haversine.cs                // Fungsi haversine dan konversi sudut
├── Distance.cs                 // Perhitungan jarak antar lokasi
├── Misc.cs                     // Utilitas konsol dan manipulasi string
└── CS_Navigation.csproj        // File proyek .NET
```

---

## 📦 Namespace & Komponen Utama

### 1. **Namespace `Symbols`**
Menyimpan simbol Unicode dan karakter khusus untuk visualisasi matematis.

#### Isi:
```csharp
public static class Symbols
{
    public const string PHI = "\u03d5";     // φ
    public const string LAMBDA = "\u03bb";  // λ
    public const string DELTA = "\u0394";   // Δ
    public const string DEGREE = "\u00b0";   // °
    public const string RAD = " RAD";
    public const string SQRT = "\u221a";    // √
    public const string APRX = "\u2248";     // ≈
    public const string SB1 = "\u2081";      // Subscript ₁
    public const string SB2 = "\u2082";      // Subscript ₂
}
```

---

### 2. **Namespace `Location`**
Merepresentasikan lokasi geografis dengan properti latitude dan longitude.

#### Kelas Utama:
```csharp
class Location
{
    public double Lat { get; set; }
    public double Lon { get; set; }
    public string Name { get; set; }
    public Unit LUnit { get; private set; } // Degree / Radian

    public void toRadian(bool SupressWarning, bool force);
    public void toDegree(bool SupressWarning, bool Force);
    public List<double> GetCoords();
}
```

#### Fitur:
- Konversi otomatis derajat ke radian
- Output terformat ke console
- Penanganan warning jika konversi tidak diperlukan

---

### 3. **Namespace `Haversine`**
Berisi fungsi matematika untuk menghitung nilai **haversine** dari sudut.

#### Kelas Utama:
```csharp
public class Haversine
{
    public static double deg2rad(double deg, bool Printing);
    public static double Hav_rad(double x, bool Printing);
    public static double Hav_deg(double x, bool Printing);
    public static double Hav(double x, bool isRadian, bool Printing);
}
```

#### Deskripsi:
- `deg2rad`: Mengubah derajat menjadi radian
- `Hav_rad`, `Hav_deg`: Menghitung nilai haversine
- `Hav`: Fungsi generik untuk semua jenis input (radian/derajat)

---

### 4. **Namespace `Distance`**
Melakukan perhitungan jarak antara dua lokasi menggunakan formula Haversine.

#### Kelas Utama:
```csharp
class Distance
{
    public class Distance_2D
    {
        public static double Distance_Deg(Location A, Location B); // versi derajat
        public static double Distance_Rad(Location A, Location B); // versi radian
        public static double Distance(Location A, Location B, bool IsRadian); // wrapper
    }
}
```

#### Output:
- Langkah-langkah perhitungan ditampilkan ke konsol
- Jarak akhir dalam kilometer
- Verifikasi kesamaan hasil antara versi derajat dan radian

---

### 5. **Namespace `Misc`**
Utilitas tambahan untuk manipulasi konsol dan string.

#### Kelas Utama:
```csharp
public static class Misc
{
    public static string Repeater(object str, int repetitions);
    public static string PrintMid(...); // Center text with borders
}

public class ColorTx
{
    public static string ColorStr(string text, uint hex, Position pos);
    public static void Print(uint hex, Position pos, string text);
}
```

#### Kegunaan:
- Membuat garis pemisah (`Repeater`)
- Menengahkan teks (`PrintMid`)
- Memberi warna teks (`ColorStr`)

---

### 6. **Namespace `CS_Navigation`**
Program utama yang menjalankan contoh implementasi.

#### Metode Utama:
```csharp
static void Main()
{
    IPB();              // Contoh lokal (IPB)
    WikipediaExample(); // Contoh global (White House vs Eiffel Tower)
}
```

#### Contoh Output:
```
===================[IPBs]===================
Coords in Degrees
φ₁ = -6.588457°
λ₁ = 106.8062°
φ₂ = -6.559582°
λ₂ = 106.72672°
...
≈ 9.25 KM
```

---

## 🔬 Tujuan Proyek

1. Memahami cara mengimplementasikan formula matematika kompleks (Haversine) dalam kode.
2. Melatih konsep OOP dan modularitas dalam C#.
3. Membiasakan diri dengan:
    - XML Documentation
    - Operator overloading (opsional)
    - MethodImplOptions.AggressiveInlining / AggressiveOptimization
4. Menggunakan teknik manipulasi konsol untuk membuat output informatif dan mudah dibaca.
5. Membangun fondasi untuk proyek navigasi/geospatial lebih lanjut.

---

## 🛠 Teknologi & Tools Digunakan

| Teknologi | Keterangan |
|-----------|------------|
| **.NET 6/7/8** | Platform runtime dan kompilasi |
| **Visual Studio / JetBrains Rider** | IDE untuk development |
| **P/Invoke** | Tidak digunakan sekarang, tapi bisa dikembangkan |
| **XML Documentation** | Dokumentasi langsung di kode |
| **Console.WriteLine() + StringBuilder** | Output visual |
| **Static Classes & Methods** | Untuk utilitas umum |

---

## 📝 Petunjuk Instalasi

### 1. Pastikan kamu sudah memiliki .NET SDK
```bash
dotnet --version
```

### 2. Buat proyek baru (opsional)
```bash
dotnet new console -n CS_Navigation
cd CS_Navigation
```

### 3. Ganti isi file `.cs` sesuai dokumen

File-file yang harus dibuat:
- `Symbols.cs`
- `Location.cs`
- `Haversine.cs`
- `Distance.cs`
- `Misc.cs`
- `Program.cs`

### 4. Jalankan aplikasi
```bash
dotnet run
```

---

## 📊 Contoh Output

```
                   Haversine Implementation!
Current terminal size: 120

====================[IPBs]=====================
Coords in Degrees
φ₁ = -6.588457°
λ₁ = 106.8062°
φ₂ = -6.559582°
λ₂ = 106.72672°

~! x = 0.0013970171025373 RAD
~! cos(x) = 0.999999037115911
~! 1-cos(x) = 9.62884088409E-07
~! Hav(x) = 4.814420442045E-07

d ≈ 9.25 KM

~~~~~~~~~~~~~~~~~~~~~~~~~~~
Degrees = 9.25 KM
Radians = 9.25 KM
APPROVED!
```

---

## 🧪 Potensi Pengembangan

| Fitur | Deskripsi |
|-------|-----------|
| GUI | Gunakan WinUI atau WPF untuk tampilan visual |
| Plotting Jarak | Integrasikan dengan peta statis |
| JSON Export | Simpan hasil perhitungan ke file |
| Unit Testing | Uji tiap fungsi dengan xUnit/NUnit |
| Optimisasi Performa | Gunakan `SIMD` atau NativeAOT |
| Input User | Tambahkan input interaktif melalui CLI |

---

## ✅ Kesimpulan

Proyek ini adalah contoh sempurna dari:
- Integrasi matematika tingkat lanjut dengan C#
- Modularitas kode dan pendekatan berbasis namespace
- Visualisasi proses perhitungan
- Estetika output CLI

Ini juga merupakan fondasi kuat untuk proyek penelitian berikutnya, seperti:
- Sistem navigasi sederhana
- Simulator pergerakan geografis
- Alat bantu untuk analisis GIS

---

## 📄 Lampiran: Diagram Arsitektur

```
+-------------------+
|     Program.cs    |
+-------------------+
          ↓
+-------------------+
|     Distance.cs   | ← Haversine.cs
+-------------------+
          ↓
+-------------------+
|     Location.cs   |
+-------------------+
          ↓
+-------------------+
|     Symbols.cs    |
+-------------------+
          ↓
+-------------------+
|      Misc.cs      | ← ColorTx.cs
+-------------------+
```

---

## 🎯 Bonus: Roadmap Pengembangan Lanjutan

| Tahap  | Fitur                                      |
|--------|--------------------------------------------|
| ✅ V1.0 | Haversine dasar, output CLI                |
| ✅ V1.1 | Haversine dasar + optimization, output CLI |
| 🚀 V2  | Input dinamis, parsing CSV                 |
| 💻 V3  | GUI sederhana (WinForms/WPF)               |
| 🌐 V4  | REST API untuk hitung jarak                |
| 📈 V5  | Analisis jarak batch (big data)            |

---

## 📞 Butuh Bantuan Lebih Lanjut?

Aku bisa bantu kamu:
- Membuat versi GUI (WPF/WinUI)
- Menjadikannya sebagai library `.dll`
- Menyebarkan sebagai tool CLI portable
- Membuat dokumentasi HTML/PDF otomatis (via DocFX)
- Menambahkan unit testing (xUnit/NUnit)

Kirim saja pertanyaanmu!

---

Semoga sukses dengan proyek penelitian dan pembelajaranmu!  
Jika kamu ingin, aku bisa bantu buatkan **PDF dokumen lengkap** atau **file ReadMe.md** untuk GitHub.