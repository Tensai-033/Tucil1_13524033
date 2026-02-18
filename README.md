# Tucil1_13524033
by: Ray Owen Martin 13524033

# Queens Solver w/ Brute Force
Permainan Queens yang dikembangkan oleh LinkedIn merupakan contoh permainan papan yang melatih kemampuan kognitif, berpikir kreatif, dan kemampuan membuat keputusan. Adapun permainan ini tersedia di platform online LinkedIn dan dapat dimainkan setiap harinya.
Permainan ini dibuat dalam suatu papan berisikan NxN kotak berwarna di mana pemain harus menempatkan sejumlah Queens berdasaran beberapa aturan ini:
Setiap baris, kolom, dan daerah (yang ditandai dengan warna yang sama) harus memiliki tepat satu ratu
Setiap ratu juga tidak boleh bersentuhan dengan ratu lain secara diagonal


# Requirements
Sistem perlu dipastikan memenuhi requirements sebagai berikut:
1. C++ Compiler (versi C++17 atau lebih baru)
   Disarankan menggunakan GCC

Cara cek versi compiler:
```
g++ --version
```
2. Operating System
   Windows 10/11 atau Linux dengan Ubuntu 20.04+


# Cara Kompilasi dengan G++
Setelah melakukan:
```
git clone https://github.com/Tensai-033/Tucil1_13524033/
```

pindahlah ke nama folder yang sesuai
```
cd Tucil1_13524033
```

Lalu compile dengan:
```
g++ queens.cpp -o queen
```

sehingga akan muncul queen.exe pada folder Tucil1_13524033


# Cara Menjalankan Program
Pada folder Tucil1_13524033 atau di folder bin, lakukan:
```
./queen.exe
```

# Tambahan Opsi
Untuk mengganti input, masukkan input baru di folder Tucil1_13524033 berekstensi .txt. Lalu pada source code yang terletak pada src/queens.cpp, ganti line 445:

ifstream file("input_7.txt");

ifstream file(<nama_file.txt>);



Hello
