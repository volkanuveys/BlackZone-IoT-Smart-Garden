<?php
// --- AYARLAR ---
$guvenlik_sifresi = "12345"; 

// Türkiye Saati
date_default_timezone_set('Europe/Istanbul');

// --- VERİYİ YAKALAMA KISMI ---
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    
    // 1. Şifre Kontrolü
    $gelen_sifre = isset($_POST['sifre']) ? $_POST['sifre'] : '';
    
    if ($gelen_sifre == $guvenlik_sifresi) {
        
        // 2. Verileri Al
        $nem_degeri = isset($_POST['nem']) ? $_POST['nem'] : '0';
        $durum_mesaji = isset($_POST['durum']) ? $_POST['durum'] : 'Veri Yok';
        
        // 3. Veriyi Paketle (Burada 'nem' yerine 'yuzde' yazıyoruz ki site görsün)
        $veri_paketi = array(
            "yuzde" => $nem_degeri,  // DÜZELTME: index.html bunu 'yuzde' olarak bekliyor
            "durum" => $durum_mesaji,
            "zaman" => date("H:i:s") 
        );
        
        // 4. Dosyaya Yaz (data.json)
        $json_verisi = json_encode($veri_paketi, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);
        file_put_contents("data.json", $json_verisi);
        
        // --- MOTOR KONTROL KISMI ---
        // Kaydettikten sonra emir.txt dosyasını oku ve ESP32'ye söyle
        if (file_exists("emir.txt")) {
            echo file_get_contents("emir.txt"); // Ekrana "AC" veya "KAPAT" yazar
        } else {
            echo "OTO"; 
        }
        
    } else {
        echo "Hata: Yanlis Sifre!";
    }
} else {
    echo "Bekleniyor... (Sadece POST)";
}
?>