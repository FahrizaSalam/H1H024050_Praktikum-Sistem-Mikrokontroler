<h1>Jawaban Pertanyaan Praktikum: Modul I Percabangan dan Perulangan</h1>

Nama: Muhammad Aziz Ihza Fahriza Salam<br>
NIM: H1H024050<br>
Mata Kuliah: TK244005-Praktikum Sistem Mikrokontroller<br>

2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
Efek LED berjalan dari kiri ke kanan (dengan asumsi pin 2 adalah posisi paling kiri) diciptakan oleh blok kode pertama di dalam fungsi void loop().

Program menggunakan perulangan for (int ledPin = 2; ledPin < 8; ledPin++).

Perulangan ini memerintahkan mikrokontroler untuk memulai dari pin 2, lalu secara bertahap naik ke pin 3, 4, 5, 6, hingga pin 7.

Di setiap langkahnya, program menghidupkan LED (digitalWrite(ledPin, HIGH);), menunggu sejenak sesuai variabel timer (delay(timer);), lalu langsung mematikannya kembali (digitalWrite(ledPin, LOW);).

Karena proses hidup-mati ini dilakukan berurutan secara cepat dari pin terkecil ke terbesar, mata kita menangkapnya sebagai satu titik cahaya yang "berjalan" dari kiri ke kanan.

3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
Efek LED kembali dari kanan ke kiri diciptakan oleh blok kode kedua di dalam fungsi void loop().

Program menggunakan perulangan mundur: for (int ledPin = 7; ledPin >= 2; ledPin--).

Berbeda dengan blok pertama, perulangan ini dimulai dari pin paling tinggi (pin 7) dan variabel ledPin-- akan mengurangi nilainya satu per satu hingga mencapai pin 2.

Sama seperti sebelumnya, program menghidupkan LED, memberi jeda waktu, dan mematikannya di setiap pin.

Karena urutannya kini dibalik dari pin terbesar (kanan) ke pin terkecil (kiri), cahaya terlihat "berjalan" mundur dari kanan ke kiri.
