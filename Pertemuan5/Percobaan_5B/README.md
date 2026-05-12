# Jawaban Pertanyaan Praktikum Modul 5: Percobaan 5B (Komunikasi Task)

**Nama:** Muhammad Aziz Ihza Fahriza Salam
**NIM:** H1H024050 
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Sama seperti percobaan sebelumnya, task read_data dan display berjalan secara bergantian di bawah kendali scheduler. Namun, pada percobaan ini terdapat mekanisme sinkronisasi menggunakan Queue (my_queue). Task display akan berada dalam kondisi blocked (menunggu) sampai task read_data mengirimkan data ke dalam queue menggunakan xQueueSend().

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini memiliki potensi rendah atau terhindar dari race condition karena menggunakan Queue untuk berbagi data. Dalam FreeRTOS, Queue adalah mekanisme komunikasi antar task yang aman (thread-safe). Artinya, sistem memastikan bahwa hanya satu task yang dapat mengakses atau memodifikasi data dalam queue pada satu waktu, sehingga mencegah konflik data jika kedua task mencoba mengakses variabel yang sama secara bersamaan.

---

## 3. Program Modifikasi (Menggunakan Sensor DHT Sesungguhnya)

```cpp
#include <Arduino_FreeRTOS.h>// Memasukkan library sistem operasi waktu nyata (FreeRTOS) untuk Arduino
#include <queue.h>// Memasukkan library untuk fitur Queue (Antrean pesan) pada FreeRTOS
#include "DHT.h"// Memasukkan library untuk membaca sensor suhu dan kelembaban DHT

#define DHTPIN 2 // Menentukan bahwa pin data sensor DHT dihubungkan ke pin digital 2 Arduino
#define DHTTYPE DHT11// Mendefinisikan tipe sensor DHT yang digunakan, yaitu DHT11

DHT dht(DHTPIN, DHTTYPE);// Membuat objek 'dht' dengan pengaturan pin dan tipe yang sudah didefinisikan

struct readings {// Mendeklarasikan tipe data buatan (struct) bernama 'readings'
  float temp;// Variabel di dalam struct untuk menyimpan nilai suhu (desimal)
  float h;// Variabel di dalam struct untuk menyimpan nilai kelembaban (desimal)
};

QueueHandle_t my_queue;// Membuat variabel penunjuk (handle) untuk Queue dengan nama 'my_queue'

void read_data(void *pvParameters);// Deklarasi awal (prototipe) fungsi task untuk membaca sensor
void display(void *pvParameters);// Deklarasi awal (prototipe) fungsi task untuk menampilkan data

void setup() { 
  Serial.begin(9600);// Memulai komunikasi serial dengan komputer pada kecepatan 9600 bps
  dht.begin();// Mengaktifkan dan menginisialisasi sensor DHT

  my_queue = xQueueCreate(1, sizeof(struct readings));// Membuat Queue dengan kapasitas 1 item sebesar ukuran 'struct readings'
  
  if (my_queue != NULL) {// Mengecek apakah antrean (Queue) berhasil dibuat di memori
    xTaskCreate(read_data, "ReadSensors", 128, NULL, 1, NULL);// Membuat Task untuk membaca sensor (memori 128 bytes, prioritas 1)
    xTaskCreate(display, "Display", 128, NULL, 1, NULL);// Membuat Task untuk menampilkan data (memori 128 bytes, prioritas 1)
  }                          
}                             

void loop() {
}                            

void read_data(void *pvParameters) {// Implementasi dari task/fungsi 'read_data'
  struct readings x;// Membuat variabel lokal 'x' bertipe 'struct readings'
  for(;;) {// Memulai perulangan tak terbatas (khas untuk task pada sistem RTOS)
    x.temp = dht.readTemperature();// Membaca suhu dari sensor DHT dan menyimpannya ke variabel x.temp
    x.h = dht.readHumidity();// Membaca kelembaban dari sensor DHT dan menyimpannya ke variabel x.h

    if (isnan(x.temp) || isnan(x.h)) {// Mengecek apakah hasil bacaan adalah NaN (Not a Number/Gagal terbaca)
      x.temp = 0.0;// Jika gagal baca, atur nilai suhu menjadi 0.0
      x.h = 0.0;// Jika gagal baca, atur nilai kelembaban menjadi 0.0
    }

    xQueueSend(my_queue, &x, portMAX_DELAY);// Mengirim paket data 'x' ke dalam antrean 'my_queue', menunggu terus jika antrean penuh
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);// Menjeda task ini selama 2000 milidetik (2 detik) sebelum membaca ulang
  }
}

void display(void *pvParameters) {// Implementasi dari task/fungsi 'display'
  struct readings x; // Membuat variabel lokal 'x' bertipe 'struct readings' untuk menampung data
  for(;;) {// Memulai perulangan tak terbatas
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) { // Mengambil data dari 'my_queue' dan memasukkannya ke 'x', menunggu terus jika antrean kosong
      Serial.print("Suhu = ");// Menampilkan teks "Suhu = " ke Serial Monitor
      Serial.print(x.temp);// Menampilkan nilai suhu yang diambil dari queue
      Serial.print(" *C | Kelembaban = ");// Menampilkan satuan suhu dan teks awalan kelembaban
      Serial.print(x.h);// Menampilkan nilai kelembaban yang diambil dari queue
      Serial.println(" %");// Menampilkan satuan "%" dan membuat baris baru (enter)
    }
  }
}