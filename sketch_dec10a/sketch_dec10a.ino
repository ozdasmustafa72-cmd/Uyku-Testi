#include <SoftwareSerial.h>


#define PIR_PIN 2
#define BT_TX 10
#define BT_RX 11


SoftwareSerial bt(BT_TX, BT_RX);


int hareketSayisi = 0;
unsigned long sonHareketZamani = 0;

const unsigned long kilitSuresi = 3000;   
const unsigned long uyariSuresi = 20000;  

bool uyariGonderildi = false;

void setup() {
pinMode(PIR_PIN, INPUT);

Serial.begin(9600);
bt.begin(9600);


delay(60000);

bt.println("=== Uyku Izleme Sistemi Basladi ===");
bt.println("20 sn hareketsizlikte uyarı aktif");
bt.println("----------------------------------");

sonHareketZamani = millis();
}

void loop() {
int pirDurum = digitalRead(PIR_PIN);


if (pirDurum == HIGH) {
if (millis() - sonHareketZamani > kilitSuresi) {
hareketSayisi++;
sonHareketZamani = millis();
uyariGonderildi = false; 

bt.print("Hareket Algilandi | Toplam: ");
bt.println(hareketSayisi);

Serial.print("Hareket: ");
Serial.println(hareketSayisi);
}
}


if ((millis() - sonHareketZamani > uyariSuresi) && !uyariGonderildi) {
bt.println("UYARI: 20 saniyedir hareket algilanmadi!");
Serial.println("UYARI: Hareketsizlik");

uyariGonderildi = true; 
}
}
