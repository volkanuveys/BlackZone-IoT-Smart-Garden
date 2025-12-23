void setup() {
  // put your#include <DHT.h>

// --- PIN AYARLARI ---
#define DHTPIN 2     // DHT11 Sensörünün Sinyal ucu D2'ye
#define DHTTYPE DHT11
#define RELAY_PIN 3  // Röle Modülünün IN ucu D3'e

DHT dht(DHTPIN, DHTTYPE);

unsigned long sonZaman = 0;
// 5 Saniyede bir veri gönderelim (Çok sık gönderip sistemi yorma)
unsigned long beklemeSuresi = 5000; 

void setup() {
  Serial.begin(9600); // ESP32 ile konuşma hızı
  dht.begin();
  
  pinMode(RELAY_PIN, OUTPUT);
  // Rölenin tipine göre burası HIGH veya LOW ile başlar.
  // Genelde HIGH yapınca röle kapanır (Low Trigger).
  digitalWrite(RELAY_PIN, HIGH); 
}

void loop() {
  // --- 1. SENSÖR VERİSİNİ OKU VE ESP32'YE AT ---
  if ((millis() - sonZaman) > beklemeSuresi) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Sensörde hata yoksa gönder
    if (!isnan(h) && !isnan(t)) {
      // Veriyi şu formatta gönderiyoruz: "sicaklik,nem" (Örn: 25.50,60.00)
      Serial.print(t);
      Serial.print(",");
      Serial.println(h);
    }
    sonZaman = millis();
  }

  // --- 2. ESP32'DEN GELEN EMİR VAR MI? (KONTROL) ---
  if (Serial.available() > 0) {
    char gelenKomut = Serial.read();
    
    // Web sitesinden '1' geldiyse AÇ
    if (gelenKomut == '1') {
      digitalWrite(RELAY_PIN, LOW); // Röle çeker
    }
    // Web sitesinden '0' geldiyse KAPAT
    else if (gelenKomut == '0') {
      digitalWrite(RELAY_PIN, HIGH); // Röle bırakır
    }
  }
} setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
