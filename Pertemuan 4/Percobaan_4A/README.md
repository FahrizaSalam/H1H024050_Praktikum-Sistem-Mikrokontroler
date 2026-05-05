# Jawaban Pertanyaan Praktikum Modul 4: Percobaan 1 (ADC)

**Nama : Muhammad Aziz Ihza Fariza Salam** 
**NIM : H1H024050**  
**Mata Kuliah : TK244005-Praktikum Sistem Mikrokontroller**

---

## 1. Fungsi Perintah analogRead() 

Fungsi `analogRead()` pada rangkaian ini digunakan untuk membaca nilai tegangan analog (0-5V) yang dihasilkan oleh putaran potensiometer. Mikrokontroler Arduino menggunakan Analog to Digital Converter (ADC) 10-bit bawaannya untuk mengubah tegangan analog tersebut menjadi nilai diskrit digital dengan rentang 0 hingga 1023.

---

## 2. Mengapa Diperlukan Fungsi map() dalam Program?

Fungsi `map()` diperlukan untuk melakukan proses scaling atau konversi rentang nilai. Nilai yang dihasilkan oleh pembacaan ADC (potensiometer) memiliki rentang 0 hingga 1023, sedangkan motor servo standar dikendalikan menggunakan nilai sudut dari 0 hingga 180 derajat. Fungsi `map()` menerjemahkan skala 0–1023 menjadi skala 0–180 agar pergerakan servo dapat sejalan dengan putaran potensiometer.

---

## 3. Program Modifikasi (Servo bergerak pada rentang 30° hingga 150°)

Berikut adalah source code program yang dimodifikasi beserta penjelasannya:

```cpp
#include <Servo.h>
Servo myservo; // Membuat objek bernama 'myservo' untuk mengendalikan servo

const int potensioPin = A0; // Menentukan pin analog A0 untuk potensiometer
const int servoPin = 9; // Menentukan pin digital 9 untuk mengontrol servo

int pos = 0; // Variabel untuk menyimpan nilai sudut posisi servo
int val = 0; // Variabel untuk menyimpan nilai pembacaan dari potensiometer

void setup() {
  myservo.attach(servoPin); // Menghubungkan servo dengan pin 9
  Serial.begin(9600); // Memulai komunikasi serial dengan kecepatan 9600 bps
}

void loop() { 
  val = analogRead(potensioPin); // Membaca nilai analog (0-1023) dari potensiometer
  pos = map(val, 0, 1023, 30, 150); // Mengonversi skala nilai ADC (0-1023) menjadi sudut servo (30-150 derajat)
  myservo.write(pos); // Memerintahkan servo bergerak sesuai sudut 'pos'

  Serial.print("ADC Potensio: "); // Menampilkan teks "ADC Potensio: " di Serial Monitor
  Serial.print(val); // Menampilkan angka hasil bacaan potensiometer

  Serial.print(" | Sudut Servo: "); // Menampilkan teks pembatas " | Sudut Servo: "
  Serial.println(pos); // Menampilkan angka sudut servo, lalu berpindah ke baris baru (enter)

  delay(15); // Memberi jeda waktu 15 milidetik agar servo stabil mencapai posisinya
}