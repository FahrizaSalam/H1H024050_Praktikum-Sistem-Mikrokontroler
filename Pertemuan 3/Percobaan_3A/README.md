# Laporan Praktikum Modul 3: Protokol Komunikasi

**Nama** : Muhammad Aziz Ihza Fahriza Salam  
**NIM** : H1H024050  
**Mata Kuliah**: TK244005-Praktikum Sistem Mikrokontroller  

---

### Jawaban Pertanyaan Praktikum Percobaan 3A

**1) Jelaskan proses dari input keyboard hingga LED menyala/mati!**


Proses dimulai ketika pengguna mengetikkan karakter pada keyboard di Serial Monitor, komputer mengirimkan data tersebut dalam bentuk ASCII ke Arduino melalui port USB (menggunakan komunikasi serial asinkron/UART). Arduino menerima data tersebut dan menyimpannya di dalam buffer penerima.Fungsi `Serial.read()` kemudian membaca karakter dari buffer.Menggunakan struktur kontrol `if-else`, Arduino mengevaluasi apakah data berupa '1' atau '0', yang kemudian memicu fungsi `digitalWrite()` untuk mengubah status tegangan pada pin LED menjadi `HIGH` (menyala) atau `LOW` (mati).

**2) Mengapa digunakan `Serial.available()` sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?**


Fungsi `Serial.available()` digunakan untuk mengecek apakah ada data serial yang masuk dan mengantri di buffer sebelum dieksekusi. Jika baris ini dihilangkan, Arduino akan terus-menerus mengeksekusi `Serial.read()` dalam siklus *looping* meskipun tidak ada input yang masuk, yang akan mengembalikan nilai sampah (biasanya -1) dan membuat program mengeksekusi percabangan secara tidak terkendali (seperti terus menampilkan "Perintah tidak dikenal").

**3) Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dan berikan penjelasan.**


```cpp
int led = 12;            // Pin LED
char data;               // Simpan input serial
bool blinkMode = false;  // Status mode kedip

void setup() {
  pinMode(led, OUTPUT);  // Set LED sebagai output
  Serial.begin(9600);    // Mulai komunikasi serial
}

void loop() {

  if (Serial.available() > 0) { // Jika ada data masuk
    data = Serial.read();       // Baca data

    if (data == '1') {          // Jika input '1'
      digitalWrite(led, HIGH);  // LED nyala
      blinkMode = false;        // Matikan mode kedip
    }
    else if (data == '0') {     // Jika input '0'
      digitalWrite(led, LOW);   // LED mati
      blinkMode = false;        // Matikan mode kedip
    }
    else if (data == '2') {     // Jika input '2'
      blinkMode = true;         // Aktifkan mode kedip
    }
    else {                      // Jika input salah
      Serial.println("Input tidak valid!"); 
    }
  }

  if (blinkMode == true) {      // Jika mode kedip aktif
    digitalWrite(led, HIGH);    // LED nyala
    delay(500);                 // Jeda 0.5 detik
    digitalWrite(led, LOW);     // LED mati
    delay(500);                 // Jeda 0.5 detik
  }
}
```

**4) Tentukan apakah menggunakan `delay()` atau `millis()`! Jelaskan pengaruhnya terhadap sistem.**


Wajib menggunakan `millis()`. Jika menggunakan `delay()` saat mode blink, mikrokontroler akan "berhenti" atau blocking selama jeda waktu tersebut, sehingga sistem tidak akan bisa segera membaca instruksi baru dari `Serial.available()`. Dengan `millis()`, kita menggunakan pendekatan non-blocking sehingga Arduino dapat terus mengecek input serial sembari menghitung waktu jeda secara asinkron di latar belakang.