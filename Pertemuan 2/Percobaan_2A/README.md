**Nama** : Muhammad Aziz Ihza Fahriza Salam  
**NIM** : H1H024050  
**Mata Kuliah** : TK244005-Praktikum Sistem Mikrokontroller  

---

## Jawaban Pertanyaan Praktikum 2.5.4 (Percobaan 2A: Seven Segment)

**1.Gambarkan rangkaian schematic yang digunakan pada percobaan!**
![Skema Rangkaian](../Dokumentasi/Skema2A.png)

**2. Apa yang terjadi jika nilai num lebih dari 15?**
Jika nilai variabel `num` yang dilemparkan ke dalam fungsi `displayDigit(int num)` bernilai lebih dari 15, program akan mengalami out-of-bounds memory access (mengakses indeks di luar batas array). Hal ini dikarenakan array `digitPattern` dideklarasikan dengan ukuran `[16][8]` yang berarti indeks maksimalnya hanya sampai 15. Pada mikrokontroler, mengakses indeks di luar batas array akan menyebabkan program membaca data acak di memori, sehingga pola LED yang menyala pada *seven segment* menjadi tidak beraturan, atau bahkan dapat menyebabkan mikrokontroler mengalami crash.

**3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!**
Program ini menggunakan rangkaian Common Cathode. 
**Alasannya:** Pada kode program, nilai `1` yang berarti `HIGH` digunakan untuk menyalakan segmen LED. Secara prinsip elektronika, agar LED dapat menyala ketika diberikan logika `HIGH` dari pin output Arduino, maka ujung pin lain dari LED tersebut (yaitu kaki katodanya) harus terhubung secara bersama-sama ke Ground(GND). Konfigurasi menyatukan semua kaki katoda ke GND inilah yang disebut sebagai Common Cathode.

**4. Modifikasi program agar tampilan berjalan dari F ke 0 beserta penjelasannya:**

```cpp
#include <Arduino.h>

// Mendefinisikan daftar pin Arduino yang terhubung ke segmen (A, B, C, D, E, F, G, DP)
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Array 2 dimensi berisi pola logika (nyala/mati) untuk membentuk angka 0-9 dan huruf A-F
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // Pola untuk menampilkan angka 0
  {0,1,1,0,0,0,0,0}, // Pola untuk menampilkan angka 1
  {1,1,0,1,1,0,1,0}, // Pola untuk menampilkan angka 2
  {1,1,1,1,0,0,1,0}, // Pola untuk menampilkan angka 3
  {0,1,1,0,0,1,1,0}, // Pola untuk menampilkan angka 4
  {1,0,1,1,0,1,1,0}, // Pola untuk menampilkan angka 5
  {1,0,1,1,1,1,1,0}, // Pola untuk menampilkan angka 6
  {1,1,1,0,0,0,0,0}, // Pola untuk menampilkan angka 7
  {1,1,1,1,1,1,1,0}, // Pola untuk menampilkan angka 8
  {1,1,1,1,0,1,1,0}, // Pola untuk menampilkan angka 9
  {1,1,1,0,1,1,1,0}, // Pola untuk menampilkan huruf A
  {0,0,1,1,1,1,1,0}, // Pola untuk menampilkan huruf b
  {1,0,0,1,1,1,0,0}, // Pola untuk menampilkan huruf C
  {0,1,1,1,1,0,1,0}, // Pola untuk menampilkan huruf d
  {1,0,0,1,1,1,1,0}, // Pola untuk menampilkan huruf E
  {1,0,0,0,1,1,1,0}  // Pola untuk menampilkan huruf F
};

// Fungsi untuk menyalakan segmen sesuai dengan pola karakter yang diminta
void displayDigit(int num) {
  for(int i = 0; i < 8; i++) { // Mengulang 8 kali untuk mengatur tiap-tiap pin segmen
    // Memberi sinyal ke pin. Tanda '!' membalik nilai (1 jadi LOW, 0 jadi HIGH), khusus untuk 7-segment Common Anode
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup() {
  for(int i = 0; i < 8; i++) { // Mengulang 8 kali untuk mendaftarkan semua pin
    pinMode(segmentPins[i], OUTPUT); // Mengatur setiap pin segmen agar berfungsi sebagai OUTPUT
  }
}

void loop() {
  for(int i = 15; i >= 0; i--) { // Perulangan untuk menghitung mundur dari 15 (F) sampai 0
    displayDigit(i); // Memanggil fungsi displayDigit untuk menampilkan nilai 'i' saat ini ke 7-segment
    delay(1000); // Menghentikan program sementara selama 1000 milidetik (1 detik) sebelum lanjut ke angka berikutnya
  }
}