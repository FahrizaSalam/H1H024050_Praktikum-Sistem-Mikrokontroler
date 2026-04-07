<h1>Jawaban Pertanyaan Praktikum: Modul I Percabangan dan Perulangan</h1>

Nama: Muhammad Aziz Ihza Fahriza Salam<br>
NIM: H1H024050<br>
Mata Kuliah: TK244005-Praktikum Sistem Mikrokontroller<br>

Jawaban Pertanyaan Praktikum
1.	Kondisi Blok if :
Program akan mengeksekusi blok di dalam if hanya jika ekspresi logika atau kondisi yang didefinisikan di dalam kurung bernilai benar (true). Contohnya, jika kita mengecek status tombol: if (buttonState == HIGH).
2.	Kondisi Blok else :
Program akan masuk ke blok else apabila kondisi pada if (dan semua else if sebelumnya) bernilai salah (false). else berfungsi sebagai jalur alternatif terakhir jika tidak ada kondisi lain yang terpenuhi.
3.	Fungsi delay(timeDelay) :
Perintah ini berfungsi untuk menghentikan eksekusi program sementara selama durasi yang ditentukan dalam satuan milidetik ($1 \text{ detik} = 1000 \text{ ms}$). Selama masa jeda ini, mikrokontroler tidak akan menjalankan baris kode berikutnya, sehingga status pin (misal: LED menyala) akan tertahan.
4. Berikut adalah modifikasi kodenya beserta penjelasan baris per baris:
```cpp
const int ledPin = 6;          // LED terhubung ke pin 6
int timeDelay = 1000;          // Waktu jeda awal (Fase Lambat = 1 detik)
bool isSpeedingUp = true;      // Penanda arah: true = makin cepat, false = makin lambat

void setup() {
  pinMode(ledPin, OUTPUT);     // Atur pin 6 sebagai output
}

void loop() {
  // --- Proses Kedip ---
  digitalWrite(ledPin, HIGH);  // Nyalakan LED
  delay(timeDelay);            // Tahan nyala sesuai timeDelay
  digitalWrite(ledPin, LOW);   // Matikan LED
  delay(timeDelay);            // Tahan mati sesuai timeDelay

  // --- Logika Perubahan Kecepatan ---
  if (isSpeedingUp == true) {  // Jika sedang dalam fase DIPERCEPAT
    timeDelay -= 100;          // Kurangi waktu jeda (kedipan makin cepat)
    
    if (timeDelay <= 100) {    // Jika batas CEPAT maksimal (100ms) tercapai
      isSpeedingUp = false;    // Ganti ke fase DIPERLAMBAT
    }
    
  } else {                     // Jika sedang dalam fase DIPERLAMBAT
    timeDelay += 100;          // Tambah waktu jeda (kedipan makin lambat)
    
    if (timeDelay >= 600) {    // Jika batas SEDANG (600ms) tercapai
      delay(3000);             // Jeda 3 detik (LED posisi MATI TOTAL)
      timeDelay = 1000;        // Reset kecepatan kembali ke LAMBAT
      isSpeedingUp = true;     // Reset alur kembali ke DIPERCEPAT
    }
  }
}
```
