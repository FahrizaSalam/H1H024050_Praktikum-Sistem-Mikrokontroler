# Jawaban Pertanyaan Praktikum Modul 5: Percobaan 5A (Multitasking)

**Nama:** Muhammad Aziz Ihza Fahriza Salam
**NIM:** H1H024050  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task (TaskBlink1, TaskBlink2, dan Taskprint) terlihat berjalan bersamaan secara concurrent (multitasking), namun sebenarnya mereka berjalan secara bergantian dengan sangat cepat. Mekanisme ini dikelola oleh Kernel Scheduler. Scheduler memberikan jatah waktu (time slicing) kepada setiap task berdasarkan prioritasnya. Karena proses perpindahan antar task terjadi dalam hitungan milidetik, bagi pengguna manusia seolah-olah semua task berjalan secara simultan.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Untuk menambahkan task keempat, langkah-langkahnya adalah:

Definisikan fungsi task baru: Buat fungsi void baru, misalnya void TaskBaru(void *pvParameters), yang berisi loop while(1) dan 
logika program di dalamnya.  

Deklarasikan Prototype: Tambahkan deklarasi fungsi di bagian atas program (sebelum setup).  

Registrasi Task di setup(): Gunakan fungsi xTaskCreate() di dalam void setup() untuk mendaftarkan task tersebut ke scheduler. Masukkan parameter seperti nama fungsi, nama string task, ukuran stack (misal 128), parameter (NULL), prioritas (misal 1), dan handle task (NULL) .

---

## 3. Program Modifikasi (Kontrol Kecepatan LED dengan Potensiometer)

```cpp
#include <Arduino_FreeRTOS.h> // Memasukkan library sistem operasi FreeRTOS ke dalam sketch

void TaskBlinkLED(void *pvParameters); // Deklarasi prototipe fungsi untuk tugas (task) mengedipkan LED
void TaskReadPotensio(void *pvParameters); // Deklarasi prototipe fungsi untuk tugas membaca potensiometer

int ledDelay = 500; // Variabel global untuk menyimpan durasi jeda LED (dalam milidetik)
const int potPin = A0; // Menentukan pin analog A0 sebagai input dari potensiometer
const int ledPin = 8; // Menentukan pin digital 8 sebagai output untuk LED

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial ke komputer dengan kecepatan 9600 bps

  // Membuat task untuk mengedipkan LED dengan memori 128 byte dan prioritas 1
  xTaskCreate(TaskBlinkLED, "BlinkLED", 128, NULL, 1, NULL); 
  // Membuat task untuk membaca potensiometer dengan memori 128 byte dan prioritas 1
  xTaskCreate(TaskReadPotensio, "ReadPot", 128, NULL, 1, NULL);

  vTaskStartScheduler(); // Memulai penjadwal (scheduler) FreeRTOS untuk menjalankan task-task di atas
}

void loop() { 
}

void TaskBlinkLED(void *pvParameters) { // Implementasi task untuk mengedipkan LED
  pinMode(ledPin, OUTPUT); // Mengatur pin LED sebagai output
  while(1) { // Perulangan tak terbatas (looping task)
    digitalWrite(ledPin, HIGH); // Menyalakan LED
    vTaskDelay(ledDelay / portTICK_PERIOD_MS); // Menahan task (sleep) selama durasi ledDelay
    
    digitalWrite(ledPin, LOW); // Mematikan LED
    vTaskDelay(ledDelay / portTICK_PERIOD_MS); // Menahan task (sleep) selama durasi ledDelay
  }
}

void TaskReadPotensio(void *pvParameters) { // Implementasi task untuk membaca potensiometer
  while(1) { // Perulangan tak terbatas (looping task)
    int potValue = analogRead(potPin); // Membaca nilai analog (0-1023) dari potensiometer
    
    // Mengonversi nilai sensor (0-1023) menjadi durasi delay (50-1000 ms)
    ledDelay = map(potValue, 0, 1023, 50, 1000); 
    
    Serial.print("Nilai Potensiometer: "); // Mencetak teks label ke Serial Monitor
    Serial.print(potValue); // Mencetak nilai asli potensiometer
    Serial.print(" | Delay LED: "); // Mencetak teks pemisah
    Serial.println(ledDelay); // Mencetak hasil konversi delay dan pindah baris baru
    
    vTaskDelay(100 / portTICK_PERIOD_MS); // Menahan task selama 100 milidetik sebelum membaca ulang
  }
}