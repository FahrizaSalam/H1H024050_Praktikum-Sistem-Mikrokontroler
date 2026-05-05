# Jawaban Pertanyaan Praktikum Modul 4: Percobaan 2 (PWM)

**Nama : Muhammad Aziz Ihza Fahriza Salam**
**NIM : H1H024050**
**Mata Kuliah : TK244005-Praktikum Sistem Mikrokontroller**

---

## 1. Mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()?

Fungsi `analogWrite()` menggunakan teknik Pulse Width Modulation (PWM). Teknik ini memanipulasi pin digital pada Arduino agar hidup (HIGH) dan mati (LOW) dengan kecepatan yang sangat tinggi sehingga menciptakan ilusi tegangan analog. Pengaturan kecerahan LED terjadi akibat perubahan duty cycle, yaitu persentase waktu sinyal berada dalam keadaan HIGH. Semakin besar nilai PWM, rata-rata tegangan listrik yang diterima LED semakin besar sehingga LED menyala lebih terang, dan sebaliknya.

---

## 2. Hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)

Hubungan keduanya terletak pada perbedaan resolusi sistem digital yang digunakan oleh Arduino Uno. Nilai ADC berasal dari komponen konverter 10-bit, sehingga mampu menghasilkan 1024 kombinasi angka (0–1023). Di sisi lain, fungsi PWM dari `analogWrite()` menggunakan resolusi 8-bit, sehingga hanya menerima nilai antara 0 hingga 255. Keduanya berbanding lurus, di mana nilai maksimal ADC (1023) merepresentasikan nilai maksimal PWM (255). Hubungan ini bisa dikonversi dengan membagi nilai ADC sebesar 4 atau menggunakan fungsi `map()`.

---

## 3. Program Modifikasi (LED hanya menyala pada rentang PWM 50-200)

Berikut adalah source code program yang dimodifikasi beserta penjelasannya:

```cpp
#include <Arduino.h>

const int potPin = A0; // Menentukan pin analog A0 untuk dihubungkan ke potensiometer
const int ledPin = 9; // Menentukan pin digital 9 (yang mendukung PWM) untuk dihubungkan ke LED

int nilaiADC = 0; // Variabel untuk menyimpan hasil bacaan awal dari potensiometer
int pwm = 0; // Variabel untuk menyimpan nilai PWM hasil konversi

void setup() {
  pinMode(ledPin, OUTPUT); // Mengatur pin 9 (LED) agar berfungsi sebagai output
  Serial.begin(9600); // Memulai komunikasi serial ke komputer dengan kecepatan 9600 bps
}

void loop() {
  nilaiADC = analogRead(potPin); // Membaca tegangan analog dari potensiometer (nilai 0-1023)
  pwm = map(nilaiADC, 0, 1023, 0, 255); // Mengonversi skala pembacaan 0-1023 menjadi skala PWM 0-255

  if (pwm >= 50 && pwm <= 200) { // Mengecek apakah nilai PWM berada di antara 50 dan 200
    analogWrite(ledPin, pwm); // Jika ya, nyalakan LED dengan tingkat kecerahan sesuai nilai PWM
  } else { // Jika nilai PWM di luar rentang tersebut (kurang dari 50 atau lebih dari 200)
    analogWrite(ledPin, 0); // Matikan LED (berikan nilai tegangan 0)
  }

  Serial.print("ADC: "); // Menampilkan teks "ADC: " di Serial Monitor
  Serial.print(nilaiADC); // Menampilkan angka hasil bacaan potensiometer

  Serial.print(" | PWM Awal: "); // Menampilkan teks pembatas " | PWM Awal: "
  Serial.print(pwm); // Menampilkan angka nilai PWM yang sudah dikonversi

  Serial.print(" | Status LED: "); // Menampilkan teks pembatas " | Status LED: "
  if (pwm >= 50 && pwm <= 200) { // Mengecek ulang kondisi rentang PWM untuk menentukan status cetak
    Serial.println("MENYALA"); // Jika masuk rentang, cetak "MENYALA" dan pindah baris (enter)
  } else { // Jika di luar rentang
    Serial.println("MATI"); // Cetak "MATI" dan pindah baris (enter)
  }

  delay(50); // Memberikan jeda waktu 50 milidetik
}