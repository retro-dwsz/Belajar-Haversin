# Belajar-Haversin
Belajar mencari jarak & navigasi sederhana dari 2 kordinat bumi (latitude "φ" dan longitude "λ") menggunakan Python dan C++
---
## Achtung:
> Répositori ini adalah yang dibuat karena seseorang yang sedang _gap-year_ mencari-cari kesibukan saat sedang rebahan disore hari
---
## 🌍 Belajar-Haversin

Proyek ini dibuat untuk mempelajari bagaimana menghitung jarak antar dua titik di permukaan bumi menggunakan rumus **Haversine**, serta memahami perbedaan hasil antara implementasi dalam **Python** dan **C++**.

Dalam repo ini, kita akan:
- Menghitung jarak 2D (permukaan bumi)
- Menambahkan ketinggian (elevasi) untuk menghitung jarak 3D
- Membandingkan akurasi antara pendekatan derajat dan radian
- Membangun modul modular untuk penggunaan lanjutan seperti flight plan, drone path, atau simulator GNSS

---

## 🧠 Kenapa Haversine?

Rumus haversine digunakan untuk menghitung jarak terpendek antara dua titik di permukaan bumi (diasumsikan berbentuk bola). Ini sangat berguna dalam navigasi, aplikasi geospatial, dan sistem GPS.

## Rumus Utama

$$
\text{hav}{\left( x \right)} = \frac{1 - \cos{\left( x \right)}}{2} = \sin^2{\left( \frac{x}{2} \right)}
$$

### Rumus Dasar (Derajat):
$$
\begin{aligned}
\text{hav}(\theta) &= \text{hav}(\Delta\phi) + \cos(\phi_1)\cos(\phi_2)\cdot\text{hav}(\Delta\lambda)
\\
\theta &= 2 \cdot \arcsin\left( \sqrt{\text{hav}(\theta)} \right)\\
d &= R \cdot \theta
\end{aligned}
$$


### Rumus Dasar (Radian):
$$
\text{hav}(\theta) = \text{hav}(\Delta\phi) + \cos(\phi_1)\cos(\phi_2)\cdot\text{hav}(\Delta\lambda)
$$
$$
\theta = 2 \cdot \arctan2\left(\sqrt{\text{hav}(\theta)},  \sqrt{1-\text{hav}(\theta)} \right)\\
d = R \cdot \theta
$$

- Dengan $ R $ adalah radius bumi (~6378 km)

Lihat di [sini](https://en.wikipedia.org/wiki/Haversine_formula)

---

## 🛠️ Fitur Utama

| Bahasa | Jarak 2D | Jarak 3D | ECEF Conversion | Unit Testing | Pencetakan Langkah |
|--------|-----------|------------|------------------|---------------|---------------------|
| Python | ✅         | ✅          | ✅                | ❌             | ✅                  |
| C++    | ✅         | ❌ (WIP)   | ✅                | ❌             | ✅                  |

Repo ini dirancang agar mudah dipelajari dan dikembangkan. Kamu bisa mengeksplorasi perbedaan kecil pada hasil antara Python dan C++ karena presisi floating point.

---

## 📁 Struktur Repo

```
├── Python/
│   ├── Navigation.py         # Navigasi Gabungan
│   ├── Navigation_2D.py      # Navigasi 2D (lat, lon) yg di Improve
│   ├── Navigation_3D.py      # Navigasi 3D (lat, lon, alt)
│   ├── Navigation_Generic.py   # Navigasi 2D (lat, lon) cakaran dalam radian
│   └── Navigation_Wikipedia.py # Navigasi 2D (lat, lon) cakaran dalam derajat
│
├── Cpp/
│   ├── includes.hpp          # Inlcude pack
│   ├── Haversine.hpp         # Bumbu utama
│   ├── Misc.hpp              # Bumbu sampingan
│   ├── Symbols.hpp           # Macro pack
│   ├── Navigation_2D.hpp     # Implementasi Bumbu utama
│   └── _Main.cpp             # File utama
├── Cppbin/
│   └── _Main.exe             # Build dari File utama _Main.cpp
├── README.md
└── .gitignore
```

---

## 🔢 Contoh Output

### Python
```python
# SV IPB ke Danau IPB 
Chords = [[-6.588457, 106.8062], [-6.559582, 106.72672]]
...
Distance ≈ 9.35 km
```

### C++
```
Degrees = 9.358608358705892
Radians = 9.357494150382932
meh
```

Kecil perbedaan output? Itu normal 👇

---

## ⚖️ Perbedaan Kecil Antara Python dan C++

Output sedikit berbeda karena:

| Faktor | Python | C++ |
|-------|--------|------|
| Tipe float | `float` = `double` (64-bit) | Bisa `float`, `double`, atau `long double` |
| Konstanta PI | Presisi tinggi secara otomatis | Harus definisi manual (`#define PI 3.141592653589793`) |
| Trigonometri | `math.sin/cos/atan2` | `std::sin/cos/atan2` — bisa lebih sensitif |
| Casting & Parsing | Dinamis | Statis → rentan terhadap loss of precision |

✅ Solusi:
- Gunakan `long double` di C++
- Gunakan Boost.Multiprecision untuk presisi arbitrer

---

## 🚀 Tujuan Proyek

- [x] Implementasi formula haversine dalam 2D di Python (lat, lon)
- [ ] Implementasi formula haversine dalam 2D di C++ (lat, lon)
- [x] Tambahkan fungsi 3D lengkap dengan elevasi di Pyhton (alt)
- [ ] Tambahkan fungsi 3D lengkap dengan elevasi di C++ (alt)
- [x] Visualisasi langkah-langkah perhitungan
- [x] Modularisasi kode

---

## 💻 Requirements

### OS
- Windows 11 atau 10 dengan x86_64

### Python
- Python 3.x
- Library:
  - `math`
  - `sys`
  - Optional: `matplotlib`, `folium`, `boost/multiprecision`

### C++
- Compiler yang mendukung C++20/C++23
- Library:
  - `fmt` (untuk printing)
  - `cmath`
  - Boost (opsional, untuk presisi tinggi, belum digunakan)

- Compiler Windows [punya saya](https://github.com/mstorsjo/llvm-mingw/releases/tag/20250305) (LLVM-MinGW dari [Martin Storsjö](https://github.com/mstorsjo))
---

## 📦 Cara Jalankan

### Python
```bash
py Py/Navigation_2D.py
py Py/Navigation_3D.py
```

### C++
```bash
clang++ ./Cpp/_Main.cpp -o ./Cppbin/_Main.exe -std=c++23 -O0 && ./Cppbin/_Main.exe
```

Pastikan semua header tersedia dan library seperti `fmt` sudah diinstal.

---

## 🧪 Ingin Ikut Berkembang?

Repo ini cocok untuk:
- Mahasiswa teknik, geodesi, atau pemrograman
- Penggemar matematika, trigonometri, dan navigasi
- Developer yang ingin tahu bagaimana komputer menghitung jarak di bumi melengkung

---

## 🤝 Contributing

Kamu bisa ikut berkontribusi dengan:
- Membantu memperbaiki bug pada C++
- Membuat lib baru
- ...

---

## 📬 Lisensi

MIT License — bebas dimodifikasi dan digunakan ulang

---

## 📬 Author

👤 [Rétro Dvořák]   
🎯 Bogor, Indonesia

---

## 🙏 Terima Kasih

Terima kasih telah tertarik dengan proyek ini.  
Semoga kamu semudah saya saat belajar haversine, dan seberani saya ketika bertanya "kenapa hasilnya beda?"

---

## 📣 Kata Penutup

Jika kamu suka:
- Geodesi
- Matematika
- Navigasi
- Floating point
- Debugging presisi
- Atau sekadar penasaran kenapa pesawat tidak terbang lurus di peta

Ingat, repositori ini adalah yang dibuat karena seseorang yang sedang gap-year mencari-cari kesibukan saat sedang rebahan disore hari

Mulai dari 2D, naik ke 3D, lalu mungkin... naik lagi ke simulasi udara!

---

## 📸 Screenshot 

Python Degrees
<img width="598" alt="Python" src="https://github.com/user-attachments/assets/614c1aae-988a-4cf4-a0b1-61a2ce36f55d" />

Python Radians
<img width="587" alt="Python2" src="https://github.com/user-attachments/assets/dd424f2f-ab0e-477e-b8af-b2c544a3b1e0" />

C++ Degrees
<img width="590" alt="C++" src="https://github.com/user-attachments/assets/0341bf07-cb35-453c-a30f-1f22550818ab" />

---
## 📦 Badge 

Kamu bisa tambahkan badge seperti ini (sesuaikan dengan status repo kamu):

[![Build Status](https://img.shields.io/badge/build-passed-green)]()
[![Language](https://img.shields.io/badge/language-Python%20&%20C++-blue)]()

---

## 🎯 Roadmap 

Kalau kamu ingin menambahkan hal-hal baru, tambahkan roadmap:

- ✅ Python 2D Done (APPROVED!)
- ✅ Python 3D with Pythagoras (APPROVED!)
- 🟡 Python 3D with ECEF (Meh?)
- 🟡 C++ 2D Done (Meh)
- 🟡 C++ 3D with Pythagoras (Meh²)
- 🟡 C++ 3D with ECEF (Meh³)

---

## 📣 Kata Akhir

> "Kenapa harus lurus kalau bisa diagonal? Kenapa harus melengkung kalau bisa chord?"  
> – Kamu, setelah satu malam debugging
