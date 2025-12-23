#include <WiFi.h>
#include <HTTPClient.h>

// --- AYARLAR ---
const char* ssid = "WIFI_ADIN";          // Wi-Fi Adını Buraya Yaz
const char* password = "WIFI_SIFREN";    // Şifreni Buraya Yaz

// Senin sitenin adresleri
String veriURL = "http://www.blackzoneiot.com/veri.php";
String kontrolURL = "http://www.blackzoneiot.com/kontrol.php";

unsigned long sonKontrolZamani = 0;

void setup() {
  Serial.begin(115200); // Bilgisayar ekranı için (Debug)
  
  // Arduino ile haberleşme (RX=16, TX=17)
  // Arduino'nun TX'i -> ESP32'nin 16'sına
  // Arduino'nun RX'i -> ESP32'nin 17'sine
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.begin(ssid, password);
  Serial.print("Wi-Fi Baglaniyor");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nBaglandi!");
}

void loop() {
  // --- A) ARDUINO'DAN VERİ GELİRSE SİTEYE GÖNDER ---
  if (Serial2.available() > 0) {
    String gelenVeri = Serial2.readStringUntil('\n'); // Satır sonuna kadar oku
    gelenVeri.trim(); // Boşlukları temizle

    // Virgülü bulup sıcaklık ve nemi ayıralım
    int virgulYeri = gelenVeri.indexOf(',');
    if (virgulYeri > 0) {
      String sicaklik = gelenVeri.substring(0, virgulYeri);
      String nem = gelenVeri.substring(virgulYeri + 1);
      
      Serial.println("Arduino'dan Geldi -> Sicaklik: " + sicaklik + " Nem: " + nem);
      veriyiSiteyeYolla(sicaklik, nem);
    }
  }

  // --- B) SİTEDEN KOMUT KONTROLÜ ---
  // Sürekli siteye sormayalım, 2-3 saniyede bir soralım
  if (millis() - sonKontrolZamani > 2000) {
    komutlariKontrolEt();
    sonKontrolZamani = millis();
  }
}

void veriyiSiteyeYolla(String t, String h) {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(veriURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // veri.php dosyası 'sicaklik' ve 'nem' post verisi bekliyor
    String postData = "sicaklik=" + t + "&nem=" + h;
    int httpCode = http.POST(postData);
    
    if (httpCode > 0) {
      Serial.println("Veri siteye gonderildi. Kod: " + String(httpCode));
    } else {
      Serial.println("Gonderim Hatasi: " + String(httpCode));
    }
    http.end();
  }
}

void komutlariKontrolEt() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(kontrolURL);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String gelenKomut = http.getString();
      gelenKomut.trim(); // Boşlukları sil
      
      // Siteden gelen 1 veya 0'ı Arduino'ya aynen iletiyoruz
      if(gelenKomut == "1" || gelenKomut == "0") {
        Serial2.print(gelenKomut);
        // Serial.println("Arduino'ya komut iletildi: " + gelenKomut);
      }
    }
    http.end();
  }
}