**Nama** : Muhammad Aziz Ihza Fahriza Salam  
**NIM** : H1H024050  
**Mata Kuliah** : TK244005-Praktikum Sistem Mikrokontroller  

---

## Jawaban Pertanyaan Praktikum 2.6.4 (Percobaan 1B: Kontrol Counter Dengan Push Button)

**Gambarkan rangkaian schematic yang digunakan pada percobaan!**
![Skema Rangkaian](../Dokumentasi/Skema2B.png)

**2. Mengapa pada push button digunakan mode `INPUT_PULLUP` pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?**

Penggunaan mode `INPUT_PULLUP` pada saat inisialisasi `pinMode()` bertujuan untuk mengaktifkan resistor pull-up internal (sekitar 20k Ohm) yang sudah tertanam di dalam mikrokontroler ATmega pada papan Arduino Uno. 

**Keuntungannya:** * **Efisien secara Rangkaian (Hardware):** Kita tidak perlu lagi memasang resistor pull-up atau pull-down eksternal secara fisik di breadboard, sehingga rangkaian menjadi jauh lebih ringkas dan hemat kabel.
* **Mencegah Status Mengambang (Floating):** Menjamin bahwa saat push button tidak ditekan, pin Arduino akan membaca sinyal secara stabil di logika `HIGH` (karena ditarik ke 5V oleh resistor internal). Tanpa pull-up, pin akan berada dalam kondisi mengambang dan bisa secara acak membaca logika HIGH atau LOW akibat gangguan elektromagnetik di sekitarnya. 

**3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?**

**Dari Sisi Hardware:**
* Kabel jumper yang menghubungkan pin Arduino ke kaki segmen tersebut putus, longgar, atau tertancap di lubang breadboard yang salah.
* Resistor 220 Ohm yang terhubung sebagai pembatas arus ke segmen tersebut rusak atau kakinya tidak menempel dengan baik (kontak kurang bagus).
* Lampu LED mikro untuk segmen spesifik tersebut di dalam komponen Seven Segment memang sudah putus/rusak (bisa karena cacat komponen atau terbakar akibat arus berlebih sebelumnya).

**Dari Sisi Software:**
* Terdapat kesalahan deklarasi pola (typo) pada array biner di dalam variabel `digitPattern` misalnya, segmen yang seharusnya bernilai `1` untuk menyala malah diketik `0`.
* Terjadi kesalahan pemetaan urutan nomor pin Arduino di dalam array `segmentPins` misal pin tertukar posisinya atau salah memasukkan angka pin.
* Logika looping pada saat inisialisasi `pinMode()` di dalam fungsi `setup()` tidak mencakup seluruh rentang array (misal kondisinya hanya `i<7` padahal ada 8 pin), sehingga ada pin segmen yang tidak dideklarasikan sebagai `OUTPUT` dan gagal mengirimkan tegangan.

**4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement):**

**Modifikasi Rangkaian Fisik:**
Selain tombol "UP" yang sudah terhubung ke **Pin 2**, tambahkan satu buah push button lagi untuk fungsi "DOWN". Hubungkan salah satu kaki tombol baru tersebut ke **Pin 3** Arduino, dan hubungkan kaki di seberangnya langsung ke jalur **GND** (sama persis dengan prinsip tombol pertama karena kita tetap menggunakan fitur `INPUT_PULLUP` bawaan Arduino).

**Kode Program Lengkap (dengan penjelasan per baris):**

```cpp
#include <Arduino.h>

// Pemetaan urutan pin untuk dihubungkan ke kaki-kaki Seven Segment
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4}; 

const int btnUp = 2;   // Mendefinisikan Pin 2 sebagai input untuk tombol increment (tambah angka)
const int btnDown = 3; // MODIFIKASI: Mendefinisikan Pin 3 sebagai input untuk tombol decrement (kurangi angka)

// Pola nyala biner LED angka 0-F untuk Seven Segment berjenis Common Cathode (1=Nyala, 0=Mati)
byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, {0,1,1,0,0,0,0,0}, {1,1,0,1,1,0,1,0}, {1,1,1,1,0,0,1,0}, 
  {0,1,1,0,0,1,1,0}, {1,0,1,1,0,1,1,0}, {1,0,1,1,1,1,1,0}, {1,1,1,0,0,0,0,0}, 
  {1,1,1,1,1,1,1,0}, {1,1,1,1,0,1,1,0}, {1,1,1,0,1,1,1,0}, {0,0,1,1,1,1,1,0}, 
  {1,0,0,1,1,1,0,0}, {0,1,1,1,1,0,1,0}, {1,0,0,1,1,1,1,0}, {1,0,0,0,1,1,1,0}  
};

int currentDigit = 0;           // Variabel global untuk menyimpan posisi angka yang sedang aktif di layar (dimulai dari 0)
bool lastUpState = HIGH;        // Menyimpan status memori tombol UP di siklus sebelumnya (HIGH karena pull-up default)
bool lastDownState = HIGH;      // Menyimpan status memori tombol DOWN di siklus sebelumnya (HIGH karena pull-up default)

// Fungsi khusus untuk menyalakan LED segmen sesuai dengan angka/huruf yang diminta di parameter
void displayDigit(int num) {
  for(int i=0; i<8; i++) {
    digitalWrite(segmentPins[i], digitPattern[num][i]); // Menuliskan sinyal HIGH/LOW ke masing-masing pin
  }
}

void setup() {
  for(int i=0; i<8; i++) {
    pinMode(segmentPins[i], OUTPUT); // Melakukan perulangan untuk mengatur semua 8 pin Seven Segment sebagai OUTPUT
  }
  
  pinMode(btnUp, INPUT_PULLUP);      // Menginisialisasi pin tombol UP dengan resistor internal Pull-Up agar sinyal stabil
  pinMode(btnDown, INPUT_PULLUP);    // Menginisialisasi pin tombol DOWN dengan resistor internal Pull-Up agar sinyal stabil
  
  displayDigit(currentDigit);        // Mengeksekusi fungsi untuk menampilkan angka inisial (0) saat Arduino baru dinyalakan
}

void loop() {
  // Membaca status kelistrikan dari kedua tombol saat ini (Pin akan terbaca LOW jika tombol sedang ditekan secara fisik)
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown);

  if(lastUpState == HIGH && upState == LOW) { 
    currentDigit++;                         // Menambah nilai variabel hitungan sebanyak 1
    if(currentDigit > 15) currentDigit = 0; // Logika Rollover: Jika hitungan telah melewati batas atas (F/15), maka reset kembali ke angka 0
    displayDigit(currentDigit);             // Segarkan tampilan di layar Seven Segment dengan angka terbaru
  }

  if(lastDownState == HIGH && downState == LOW) {
    currentDigit--;                         // Mengurangi nilai variabel hitungan sebanyak 1
    if(currentDigit < 0) currentDigit = 15; // Logika Rollover mundur: Jika hitungan kurang dari 0, putar balik batas menjadi ke 15 (F)
    displayDigit(currentDigit);             // Segarkan tampilan di layar Seven Segment dengan angka terbaru
  }

  // Memperbarui riwayat status memori tombol saat ini untuk dijadikan perbandingan pada siklus loop per detik berikutnya
  lastUpState = upState;     
  lastDownState = downState; 
  
  // Memberikan jeda waktu eksekusi singkat 50 milidetik sebagai mekanisme perlindungan
  delay(50); 
}