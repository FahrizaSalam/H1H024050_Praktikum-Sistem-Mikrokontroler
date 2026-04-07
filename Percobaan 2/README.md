<h1>Jawaban Pertanyaan Praktikum: Modul I Percabangan dan Perulangan</h1>

Nama: Muhammad Aziz Ihza Fahriza Salam<br>
NIM: H1H024050<br>
Mata Kuliah: TK244005-Praktikum Sistem Mikrokontroller<br>

1. Rangkaian ada pada file simulasi

2. Program menggunakan perulangan for (int ledPin = 2; ledPin < 8; ledPin++).

Perulangan ini memerintahkan mikrokontroler untuk memulai dari pin 2, lalu secara bertahap naik ke pin 3, 4, 5, 6, hingga pin 7.

Di setiap langkahnya, program menghidupkan LED (digitalWrite(ledPin, HIGH);), menunggu sejenak sesuai variabel timer (delay(timer);), lalu langsung mematikannya kembali (digitalWrite(ledPin, LOW);).

Karena proses hidup-mati ini dilakukan berurutan secara cepat dari pin terkecil ke terbesar, mata kita menangkapnya sebagai satu titik cahaya yang "berjalan" dari kiri ke kanan.

3. Program menggunakan perulangan mundur: for (int ledPin = 7; ledPin >= 2; ledPin--).

Berbeda dengan blok pertama, perulangan ini dimulai dari pin paling tinggi (pin 7) dan variabel ledPin-- akan mengurangi nilainya satu per satu hingga mencapai pin 2.

Sama seperti sebelumnya, program menghidupkan LED, memberi jeda waktu, dan mematikannya di setiap pin.

Karena urutannya kini dibalik dari pin terbesar (kanan) ke pin terkecil (kiri), cahaya terlihat "berjalan" mundur dari kanan ke kiri.

4. program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian
dan penjelasan disetiap baris kode nya

```cpp
// Deklarasi variabel untuk mengatur jeda waktu (delay).
// Angka 500 berarti 500 milidetik (setengah detik).
int timer = 500; 

void setup() {
  // Menggunakan perulangan 'for' untuk menginisialisasi pin 2 sampai 7
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    // Mengatur setiap pin yang sedang di-looping sebagai OUTPUT
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // Looping untuk pin 2, 3, dan 4 (Kelompok LED Kiri)
  for (int i = 2; i <= 4; i++) {
    // Memberikan sinyal HIGH agar LED kiri menyala
    digitalWrite(i, HIGH); 
  }
  
  // Looping untuk pin 5, 6, dan 7 (Kelompok LED Kanan)
  for (int i = 5; i <= 7; i++) {
    // Memberikan sinyal LOW agar LED kanan mati
    digitalWrite(i, LOW); 
  }
  
  // Tahan kondisi (Kiri Nyala, Kanan Mati) selama 500 ms
  delay(timer);

  // Looping kembali untuk pin 2, 3, dan 4 (Kelompok LED Kiri)
  for (int i = 2; i <= 4; i++) {
    // Kali ini berikan sinyal LOW agar LED kiri mati
    digitalWrite(i, LOW); 
  }
  
  // Looping kembali untuk pin 5, 6, dan 7 (Kelompok LED Kanan)
  for (int i = 5; i <= 7; i++) {
    // Berikan sinyal HIGH agar LED kanan menyala
    digitalWrite(i, HIGH); 
  }
  
  // Tahan kondisi (Kiri Mati, Kanan Nyala) selama 500 ms
  // Setelah delay ini, program akan kembali ke bagian paling atas fungsi loop()
  delay(timer);
}
