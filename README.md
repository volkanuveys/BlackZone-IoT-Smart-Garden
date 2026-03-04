# BlackZone-IoT-Smart-Garden
ESP32 and PHP based remote smart irrigation system with custom web interface.
# 🌱 BLACKZONE IOT - Akıllı Sera ve Otonom Sulama Sistemi

![Sürüm](https://img.shields.io/badge/Sürüm-2.0.0_Secure-00ff00?style=flat-square)
![Yazılım](https://img.shields.io/badge/Yazılım-C%2B%2B_%7C_PHP_%7C_JS-00ff00?style=flat-square)
![Donanım](https://img.shields.io/badge/Donanım-ESP32_%2B_Arduino-00ff00?style=flat-square)
![Bağlantı](https://img.shields.io/badge/Ağ-Wi--Fi_%7C_HTTPS-00ff00?style=flat-square)
![Güvenlik](https://img.shields.io/badge/Güvenlik-SSL_%7C_API_Key-00ff00?style=flat-square)

## 🚀 Proje Hakkında
Blackzone IoT Akıllı Sera Sistemi, tarımsal verimliliği artırmak ve su israfını önlemek amacıyla geliştirilmiş, **Çift İşlemcili (Dual-MCU)** bir tarım otomasyonudur. 

Sistem, toprağın nem durumunu korozyona dayanıklı endüstriyel sensörlerle analiz ederek bitkilerin ihtiyacı olduğu anda otonom olarak su pompalarını devreye sokar. Uçtan uca şifrelenmiş (End-to-End Encrypted) HTTPS protokolü sayesinde, dünyanın herhangi bir yerinden sisteme güvenle manuel müdahale (Aç/Kapat) olanağı tanır.

## 🛠️ Temel Özellikler
* **Kriptografik Veri İletimi (YENİ):** Sistem, bulut sunucusuyla standart HTTP yerine **HTTPS (SSL/TLS)** üzerinden haberleşir. Gönderilen veri paketleri API şifrelemesi (Payload Authentication) ile korunur; yetkisiz erişimler ve bot saldırıları engellenir.
* **Otonom Sulama (OTO Mod):** Toprak nemi belirlenen kritik eşiğin (%30) altına düştüğünde röle/pompa otomatik açılır, doygunluğa (%60) ulaştığında kapanır.
* **Uzaktan Yönetim (MANUEL Mod):** Blackzone Web Paneli üzerinden sisteme HTTPS üzerinden güvenli "AC" veya "KAPAT" komutları gönderilerek anlık müdahale edilebilir.
* **Lokal Arayüz (HMI):** Sera içerisindeki operatörler için 16x2 I2C LCD ekran üzerinden anlık nem yüzdesi ve aktif mod (OTO/MANUEL) takibi.
* **Hata Toleranslı Haberleşme:** ESP32 ve Arduino arasında Logic Level Converter (LLC) ve `trim()` filtreleme algoritmalarıyla desteklenen, veri kaybı sıfıra indirilmiş izole Serial köprü.

## 💻 Kullanılan Teknolojiler (Yazılım ve Donanım)

**Yazılım ve Bulut Katmanı:**
* **C / C++:** Arduino ve ESP32 mikrodenetleyicilerinin donanım haberleşmesi ve gömülü (embedded) yazılımları.
* **PHP:** ESP32'den gelen şifreli `POST` verilerini işleyen, sunucu tarafı (Backend) API altyapısı (`veri.php`).
* **HTML5 / CSS3 / JavaScript:** Kullanıcının sistemi uzaktan kontrol ettiği ve değerleri okuduğu Blackzone Web Paneli (Frontend).

**Uç Birim ve Sensör Katmanı (Arduino):**
* Arduino Uno/Nano (Ana Sensör Yönetimi ve HMI)
* **Kapasitif Toprak Nem Sensörü v1.2** *(Elektroliz yapmayan, korozyon korumalı uzun ömürlü ölçüm)*
* 5V Röle Modülü (Kuru Kontak / Su Pompası Tetikleme)
* 16x2 I2C LCD Ekran (0x27 Adresi)

**Ağ Geçidi (Gateway) Katmanı (ESP32):**
* ESP32 Wi-Fi Modülü (Secure Gateway olarak kullanıldı)
* Çift Yönlü Logic Level Converter (5V <-> 3.3V TX/RX İzolasyonu)
* C++ tabanlı `HTTPClient` ve SSL destekli `WiFiClientSecure` kütüphaneleri

## 🔌 Sistem Mimarisi (Nasıl Çalışır?)
1. **Sensör Okuma:** Arduino, topraktaki nem oranını kapasitif olarak okur, 0-100% aralığına map eder ve I2C üzerinden LCD ekrana yazar.
2. **Köprü (Bridge):** Arduino, bu veriyi donanımsal Serial (TX/RX) hattı üzerinden 3.3V seviyesine düşürerek ESP32'ye iletir.
3. **Güvenli Bulut (Cloud):** ESP32, aldığı veriyi şifreli bir paket haline getirir (`sifre=****&nem=...`) ve Blackzone IoT web sunucusuna **HTTPS POST** metodu ile fırlatır.
4. **Emir/Komut (Feedback):** Sunucudan dönen kriptolanmış cevapta kullanıcının bir web komutu (AÇ/KAPAT) varsa, ESP32 bunu Arduino'ya iletir. Arduino gelen string veriyi temizler ve saniyesinde röleyi tetikler.

## 💡 Geliştirici Notu
Bu projenin en büyük mühendislik başarılarından biri; farklı çalışma voltajlarına sahip (5V ve 3.3V) iki ayrı mikrodenetleyicinin yakılmadan hatasız konuşturulması ve IoT cihazlarının en büyük zafiyeti olan siber güvenliğin (SSL Sertifikası ve Payload Şifreleme) donanım seviyesinde çözülmesidir. Ayrıca uçtan uca Full-Stack (C++, PHP, JS) bir mimari kurgulanmıştır.

---
**Geliştirici:** Volkan Günçavdi
*"Sadece toprağa can vermiyoruz, veriyi de zırhlıyoruz."*
