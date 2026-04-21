# Laporan Praktikum Modul 3: Protokol Komunikasi

**Nama** : Muhammad Aziz Ihza Fahriza Salam  
**NIM** : H1H024050  
**Mata Kuliah**: TK244005-Praktikum Sistem Mikrokontroller  

---

### Jawaban Pertanyaan Praktikum Percobaan 3B

**1) Cara Kerja Komunikasi I2C antara Arduino dan LCD**


Komunikasi I2C bekerja dengan konsep Master-Slave, di mana Arduino bertindak sebagai Master pengontrol dan LCD I2C bertindak sebagai Slave penerima instruksi. Komunikasi ini hanya membutuhkan dua kabel utama: SDA (terhubung ke pin A4) untuk jalur data dua arah, dan SCL (terhubung ke pin A5) untuk sinyal detak (*clock*) sinkronisasi. 

Arduino mengirimkan alamat heksadesimal spesifik (dalam modul ini umumnya `0x27` atau `0x3F`) ke jalur komunikasi. Hanya perangkat (LCD) dengan alamat I2C yang cocok yang akan merespons dan menerima paket data selanjutnya, seperti instruksi `lcd.print()` atau `lcd.setCursor()`.

**2) Pertukaran Pin Potensiometer**


Posisi pin kiri (GND) dan pin kanan (5V) pada potensiometer tidak mutlak harus seperti itu. Kedua pin tersebut berfungsi sebagai pembagi tegangan di ujung-ujung elemen resistif. 

Jika posisi pin kiri (GND) dan pin kanan (5V) ditukar, arah pembacaan nilai akan terbalik. Misalnya, jika sebelumnya memutar knob ke kanan membuat nilai ADC naik (hingga 1023), maka setelah ditukar, memutar knob ke kanan akan membuat nilai ADC menurun (menuju 0). Tidak akan terjadi korsleting atau kerusakan komponen selama pin tengah (Wiper) tetap masuk ke pin analog A0.

**3) Modifikasi Program Gabungan UART dan I2C**


```cpp
#include <Wire.h>                    // Library I2C
#include <Adafruit_LiquidCrystal.h>  // Library LCD

Adafruit_LiquidCrystal lcd_1(0);     // Inisialisasi LCD pada alamat 0

const int pinPot = A0;               // Pin analog potensiometer

void setup() {
  Serial.begin(9600);                // Mulai komunikasi serial

  lcd_1.begin(16, 2);                // Set ukuran LCD 16x2
  lcd_1.setBacklight(1);             // Nyalakan lampu latar LCD
}

void loop() {
  int nilai = analogRead(pinPot);    // Baca nilai ADC (0-1023)

  float volt = nilai * (5.0 / 1023.0);      // Konversi ADC ke tegangan (0-5V)
  int persen = map(nilai, 0, 1023, 0, 100); // Konversi ADC ke persentase (0-100%)
  int bar = map(nilai, 0, 1023, 0, 16);     // Pemetaan untuk panjang bar (0-16 karakter)

  // Cetak hasil pembacaan ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" | Volt: ");
  Serial.print(volt, 2);
  Serial.print(" V | Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // Tampilkan teks data (ADC, Volt, Persen) di baris pertama LCD
  lcd_1.setCursor(0, 0);
  lcd_1.print(nilai);
  lcd_1.print(" ");
  lcd_1.print(volt, 1);
  lcd_1.print(" ");
  lcd_1.print(persen);
  lcd_1.print("% ");

  // Tampilkan progress bar di baris kedua LCD
  lcd_1.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd_1.print((char)255);        // Cetak karakter blok (bar terisi)
    } else {
      lcd_1.print(" ");              // Cetak spasi (kosongkan sisa bar)
    }
  }

  delay(200);                        // Jeda 200 milidetik
}
```
**4) Tabel Pengamatan Nilai Konversi**


| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 4%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |