#include <stdio.h>
#define MAXISIM 100
#define MAXKISI 50


// Personel yapısını tanımlıyoruz
struct personel {
   int sicilNo;      // Sicil numarası
   char isim[100];   // İsim ve soyisim
   int satis;        // Satış miktarı
};


// Personel array'ini tanımlıyoruz
struct personel personeller[MAXKISI];
int makssatis = 0;        // Maksimum satış miktarını tutacak değişken
int arrayLenght = 0;      // Array'deki kişi sayısını tutacak değişken


// Verileri dosyadan okuyarak personel array'ine yazan fonksiyon
int arrayeYaz(const char *veri_dosyasi) {
   // Dosyayı okuma modunda açıyoruz
   FILE *verifile = fopen(veri_dosyasi ,"r");
   if (verifile == NULL) {
       printf("Arrayde acilamadi\n");
       return 1;
   }// Dosya açılamazsa hata mesajı
   for (int i = 0; i < 50; i++) {
       arrayLenght++;  // Array uzunluğunu arttırıyoruz
       if (fscanf(verifile ,"%d" ,&personeller[i].sicilNo) == EOF) break;  // Sicil numarasını okuyoruz
       getc(verifile);  // Boşluğu atlıyoruz
       char c;
       for (int j = 0; ; j++) {
           c = getc(verifile);  // Bir karakter okuyoruz
           if (c >= '0' && c <= '9') break;  // Karakter sayıysa, isim okuma biter
           personeller[i].isim[j] = c;  // İsim karakterini array'e yazıyoruz
       }
       ungetc(c ,verifile);  // Okunan karakteri geri alıyoruz (sayı kısmı için)
       if (fscanf(verifile, "%d", &personeller[i].satis) == EOF) break;  // Satış miktarını okuyoruz
       if (personeller[i].satis > makssatis) makssatis = personeller[i].satis;  // Maksimum satış miktarını güncelliyoruz
   }
   return 0;
}


// Array'deki her kişinin maksimum satışa ulaşmak için gereken satış miktarını hesaplayan fonksiyon
void arrayDuzelt() {
   for (int i = 0; i < arrayLenght; i++) {
       personeller[i].satis = makssatis - personeller[i].satis;  // Eksik satış miktarını hesaplıyoruz
   }
}


// Sonuçları dosyaya yazan fonksiyon
int dosyayaYaz(const char *sonuc_dosyasi) {
   // Dosyayı yazma modunda açıyoruz
   FILE *sonuc = fopen(sonuc_dosyasi,"w");
   if (sonuc == NULL) {
       printf("Dosya acıladi\n");
       return 1;
   }  // Dosya açılamazsa hata mesajı
   // Personel array'indeki her veriyi dosyaya yazıyoruz
   for (int i = 0; i < arrayLenght; i++) {
       fprintf(sonuc ,"Sicil no: %d ,İsim %s; Gereken satis %d\n" ,personeller[i].sicilNo ,personeller[i].isim ,personeller[i].satis);
   }
   return 0;
}


int main() {
   char sonuc_dosyasi[256], veri_dosyasi[256];
   printf("Veri dosyasinin yolunu giriniz\n>");  // Veri dosyasının yolunu soruyoruz
   scanf("%s", veri_dosyasi);  // Kullanıcıdan veri dosyasının yolunu alıyoruz
   arrayeYaz(veri_dosyasi);  // Veri dosyasını okuyup array'e yazıyoruz


   printf("Cikti dosyasinin yolunu giriniz\n>");  // Çıktı dosyasının yolunu soruyoruz
   scanf("%s", sonuc_dosyasi);  // Kullanıcıdan çıktı dosyasının yolunu alıyoruz


   if (printf("Sonuclar %s dosyasina yazildi", sonuc_dosyasi) == 1) return 1;  // İşlem bittiğinde kullanıcıya bilgi veriyoruz
   arrayDuzelt();  // Maksimum satışa kalan miktarı yazıyoruz
   if(dosyayaYaz(sonuc_dosyasi) == 1) return 1;  // Sonuçları dosyaya yazıyoruz
   return 0;
}
