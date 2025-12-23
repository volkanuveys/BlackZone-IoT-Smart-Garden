<?php
// Bu dosya butonlardan gelen emri kaydeder
if(isset($_GET['mod'])) {
    $gelen_emir = $_GET['mod']; // URL'den emri al (AC, KAPAT, OTO)
    
    // Sadece izin verilen emirleri kabul et (G«ävenlik)
    if($gelen_emir == "AC" || $gelen_emir == "KAPAT" || $gelen_emir == "OTO") {
        file_put_contents("emir.txt", $gelen_emir);
        echo "Emir Kaydedildi: " . $gelen_emir;
    } else {
        echo "Gecersiz Emir!";
    }
}
?>