#include <iostream>

int main() {
    return 0;
}
/*
                                                            KODLARI TEST ETMEYE GÝRÝÞ

Programýnýzý yazdýnýz, derlediniz ve hatta çalýþtý gibi görünüyor! Peki, þimdi ne yapmalýsýnýz?

Cevap, duruma baðlýdýr. Eðer programýnýzý bir defa çalýþtýrýp ardýndan atýlmak üzere yazdýysanýz, o zaman iþiniz bitmiþ demektir. Bu durumda, programýnýzýn her
durum için çalýþmamasýnýn bir önemi olmayabilir. Eðer sadece ihtiyacýnýz olan bir durumda çalýþýyorsa ve programý sadece bir kez çalýþtýracaksanýz, iþiniz tamamlanmýþ
demektir. Eðer programýnýz tamamen lineerse (if veya switch ifadeleri gibi koþullu ifadeler içermiyorsa), girdi almýyorsa ve doðru cevabý üretiyorsa, o zaman büyük 
ihtimalle iþiniz bitmiþ demektir. Bu durumda, programý çalýþtýrarak ve çýktýyý doðrulayarak zaten tüm programý test etmiþsiniz demektir. Programý farklý sistemlerde
derleyip çalýþtýrarak davranýþýnýn tutarlý olup olmadýðýný kontrol etmek isteyebilirsiniz (eðer tutarsýzlýk varsa, baþlangýç sistemizde tesadüfen çalýþan tanýmsýz 
davranýþ üreten bir þey yapmýþ olabiliriz).
Ancak büyük olasýlýkla programýnýzý birçok kez çalýþtýrmayý, döngüler ve koþullu mantýk kullanan ve bir tür kullanýcý girdisi kabul eden bir program yazdýnýz. 
Muhtemelen gelecekteki diðer programlarda yeniden kullanýlabilir olmasý için iþlevler yazdýnýz. Belki de kapsam artýþý(scope creep) yaþadýnýz ve baþlangýçta planlanmayan bazý
yeni yetenekler eklediniz. Belki de bu programý diðer kiþilere daðýtmayý düþünüyorsunuz (ki muhtemelen sizin düþünmediðiniz durumlarý deneyeceklerdir). Bu durumda,
programýnýzýn geniþ bir dizi koþul altýnda düþündüðünüz gibi çalýþtýðýný doðrulamak için proaktif bir test yapmanýz gerekmektedir.

Programýnýzýn bir set girdi için çalýþmasý, programýn tüm durumlarda doðru çalýþacaðý anlamýna gelmez.

Yazýlým testi (ayný zamanda yazýlým doðrulama olarak da adlandýrýlýr), yazýlýmýn beklenildiði gibi çalýþýp çalýþmadýðýný belirleme sürecidir.


Test etme Problemi
------------------
Kapsamlý bir test neden zordur ? Þu örnek üzerinden düþünelim:

                                                #include <iostream>

                                                void compare(int x, int y)
                                                {
                                                    if (x > y)
                                                        std::cout << x << " is greater than " << y << '\n'; // case 1
                                                    else if (x < y)
                                                        std::cout << x << " is less than " << y << '\n'; // case 2
                                                    else
                                                        std::cout << x << " is equal to " << y << '\n'; // case 3
                                                }

                                                int main()
                                                {
                                                    std::cout << "Enter a number: ";
                                                    int x{};
                                                    std::cin >> x;

                                                    std::cout << "Enter another number: ";
                                                    int y{};
                                                    std::cin >> y;

                                                    compare(x, y);

                                                    return 0;
                                                }

Bir 4 baytlýk bir tamsayý varsayýldýðýnda, bu programý her olasý giriþ kombinasyonuyla açýkça test etmek, programý 18,446,744,073,709,551,616 (yaklaþýk 18 kentilyon)
kez çalýþtýrmanýzý gerektirir. Bu açýkça makul bir görev deðil!

Her kullanýcý girdisi istediðimizde veya kodumuzda bir koþullu ifade olduðunda, programýmýzýn çalýþma þeklinin olasý yollarýný çoðaltan bir çarpanla karþýlaþýrýz. 
En basit programlar için bile, her giriþ kombinasyonunu açýkça test etmek neredeyse hemen imkansýz hale gelir.

Þimdi, yukarýdaki programý 18 kentilyon kez çalýþtýrmanýzýn gerçekten gerekmediðini sezginiz size söylemelidir. Mantýklý bir þekilde, durum 1'in x ve y deðerleri 
için x > y olduðunda çalýþýyorsa, x > y olan herhangi bir x ve y çifti için çalýþmasý gerektiðini sonuçlandýrabilirsiniz. Bu durumda, programý gerçekten sadece üç 
kez çalýþtýrmamýz yeterli olur (compare() fonksiyonundaki üç durumu birer kez çalýþtýrmak için), böylece istenildiði gibi çalýþtýðýna dair yüksek bir güven düzeyine
sahip olabiliriz. Test etmemiz gereken þeyin sayýsýný dramatik bir þekilde azaltmak için kullanabileceðimiz baþka benzer hileler de vardýr, bu da test etmeyi
yönetilebilir hale getirir.

Test yöntemleri hakkýnda yazýlacak çok þey var - aslýnda, bunun üzerine bir bölüm bile yazabiliriz. Ancak bu konu C++ ile sýnýrlý olmadýðýndan, kýsa ve gayri resmi
bir tanýtým ile yetineceðiz. Bir sonraki birkaç alt bölümde, kodunuzu test ederken düþünmeniz gereken bazý pratik konular hakkýnda konuþacaðýz.


Programlarýnýzý küçük parçalar halinde test edin
------------------------------------------------
Özel bir konsept arabasý üreten bir otomobil üreticisini düþünün. Aþaðýdakilerden hangisini düþündüðünüzü düþünün?
a) Her araba parçasýný bireysel olarak inþa et (veya satýn al) ve kurulumdan önce her parçayý ayrý ayrý test et. Parçanýn çalýþtýðý kanýtlandýktan sonra, onu 
arabaya entegre et ve entegrasyonun çalýþtýðýndan emin olmak için tekrar test et. Son olarak, her þeyin iyi göründüðünü son doðrulama olarak tüm arabayý test et.
b) Tüm bileþenlerden hemen bir araba oluþtur, ardýndan tüm þeyi ilk kez tamamen test et.

Olasý a) seçeneðinin daha iyi bir seçenek olduðu açýktýr. Ve yine de, birçok yeni programcý kodlarýný b) seçeneði gibi yazar!

Durum b)'de, araba parçalarýndan herhangi biri beklenildiði gibi çalýþmazsa, mekanikçi neyin yanlýþ olduðunu belirlemek için tüm arabayý teþhis etmek zorunda
kalacaktýr - sorun her yerde olabilir. Bir semptomun birçok nedeni olabilir - örneðin, araba baþlamýyorsa, kusurlu bir buji, pil, yakýt pompasý veya baþka bir þey mi?
Bu, problemlerin tam olarak nerede olduðunu ve bunlarla ne yapýlmasý gerektiðini belirlemeye yönelik çok zaman kaybýna neden olur. Ve eðer bir sorun bulunursa, 
sonuçlarý felaket olabilir - bir alandaki bir deðiþiklik, çok sayýda baþka yerde "dalga etkileri" (deðiþiklikler) yaratabilir. Örneðin, çok küçük bir yakýt pompasý,
bir motor tasarýmýna, ardýndan bir araba þasisinin tasarýmýna yol açabilir. En kötü durumda, baþlangýçta küçük bir sorunu karþýlamak için arabayý geniþ bir þekilde 
yeniden tasarlamýþ olabilirsiniz!

Durum a)'da þirket, sürekli olarak test eder. Eðer herhangi bir bileþen kutusundan çýktýðýnda kötüyse, hemen bilgi sahibi olabilir ve düzeltebilir/deðiþtirebilir. 
Bir parça yalnýzca kendi içinde çalýþtýðý kanýtlandýktan sonra arabaya entegre edilir ve ardýndan bu parça hemen entegre olduktan sonra tekrar test edilir. Bu þekilde,
beklenmedik sorunlar mümkün olduðunca erken keþfedilir, henüz küçük ve kolayca düzeltilebilecek sorunlardýr.

Tüm arabayý monte etme aþamasýna geldiklerinde, arabayý çalýþtýrmanýn makul bir güvene sahip olmalarý gerekir - sonuçta, tüm parçalar izole edilmiþ ve baþlangýçta 
entegre edildiði zaman test edilmiþtir. Bu noktada beklenmeyen sorunlar bulunabilir, ancak bu risk, önceki tüm testlerle azaltýlmýþtýr.

Yukarýdaki benzetme, programlar için de geçerlidir, ancak bir nedenden dolayý, yeni programcýlar bunun farkýna genellikle varmazlar. Küçük iþlevleri (veya sýnýflarý)
yazmak ve ardýndan hemen derleyip test etmek, daha iyidir. Bu þekilde, bir hata yaparsanýz, son derlediðiniz/test ettiðinizden bu yana deðiþtirdiðiniz küçük kod
miktarýnda olmasý gerektiðini bileceksiniz. Bu, daha az yer aramak ve çok daha az zaman harcamak anlamýna gelir.

Bir "ünite" kodun doðru olduðundan emin olmak için kodunuzun küçük bir parçasýný izole etmek ve test etmek, ünite testi ( unit testing ) olarak adlandýrýlýr.
Her ünite testi ( unit test ), birimin belirli bir davranýþýnýn doðru olduðunu saðlamak için tasarlanmýþtýr.

*** BEST -> Programýnýzý küçük, iyi tanýmlanmýþ birimlere (fonksiyonlar veya sýnýflar) yazýn, sýk sýk derleyin ve kodunuzu geliþtirirken test edin.



Eðer program kýsa ise ve kullanýcý giriþi kabul ediyorsa, çeþitli kullanýcý giriþlerini denemek yeterli olabilir. Ancak programlar giderek daha uzun hale geldikçe, 
bu yeterlilik azalýr ve parçalarý programýn geri kalanýna entegre etmeden önce bireysel fonksiyonlarý veya sýnýflarý test etmek daha deðerli hale gelir.

Peki, kodumuzu birimler halinde nasýl test edebiliriz?


Informal testing
----------------
Kodu yazarken programýnýzý test etmenin bir yoludur. Bir kod birimini (bir fonksiyon, bir sýnýf veya diðer ayrýk kod "paketleri") yazdýktan sonra, eklenen bu birimi 
test etmek için bazý kodlarý yazabilir ve test baþarýlý olduðunda testi silebilirsiniz. Aþaðýdaki isLowerVowel() fonksiyonu için örnek olarak þu kodlarý
yazabilirsiniz:

                                        #include <iostream>

                                        // Test edilecek fonksiyon aþaðýdaki gibidir
                                        bool isLowerVowel(char c)
                                        {
                                            switch (c)
                                            {
                                            case 'a':
                                            case 'e':
                                            case 'i':
                                            case 'o':
                                            case 'u':
                                                return true;
                                            default:
                                                return false;
                                            }
                                        }

                                        int main()
                                        {
                                            // Ýþte geçici testlerimiz, doðru çalýþtýðýný doðrulamak için
                                            std::cout << isLowerVowel('a') << '\n'; // geçici test kodu, 1 üretmeli
                                            std::cout << isLowerVowel('q') << '\n'; // geçici test kodu, 0 üretmeli

                                            return 0;
                                        }
Eðer sonuçlar 1 ve 0 olarak dönerse, iþte tamam! Fonksiyonunuzun temel durumlar için çalýþtýðýný biliyorsunuz ve kodu inceleyerek test etmediðiniz durumlar
('e', 'i', 'o' ve 'u') için de çalýþacaðýný makul bir þekilde çýkarabilirsiniz. Bu nedenle, geçici test kodunu silebilir ve programlamaya devam edebilirsiniz.


Testlerinizi korumak
--------------------
Geçici testler yazmak, bazý kodlarý hýzlý ve kolay bir þekilde test etmenin bir yolu olsa da, ayný kodu daha sonra tekrar test etmek isteyebileceðiniz gerçeðini
hesaba katmaz. Belki bir fonksiyonu yeni bir yetenek eklemek için deðiþtirdiniz ve zaten çalýþan bir þeyi bozmadýðýnýzdan emin olmak istiyorsunuz. Bu nedenle,
testlerinizi gelecekte tekrar çalýþtýrýlabilir olacak þekilde korumak daha mantýklý olabilir. Örneðin, geçici test kodunuzu silmek yerine, testleri bir testVowel()
fonksiyonuna taþýyabilirsiniz:

                    #include <iostream>

                    bool isLowerVowel(char c)
                    {
                        switch (c)
                        {
                        case 'a':
                        case 'e':
                        case 'i':
                        case 'o':
                        case 'u':
                            return true;
                        default:
                            return false;
                        }
                    }

                    // Þu an hiçbir yerden çaðrýlmýyor
                    // Ancak daha sonra þeyleri tekrar test etmek istiyorsanýz burada
                    void testVowel()
                    {
                        std::cout << isLowerVowel('a') << '\n'; // geçici test kodu, 1 üretmeli
                        std::cout << isLowerVowel('q') << '\n'; // geçici test kodu, 0 üretmeli
                    }

                    int main()
                    {
                        return 0;
                    }

Daha fazla test oluþturdukça bunlarý testVowel() iþlevine ekleyebilirsiniz.

Test fonksiyonlarýný otomatize etme
-----------------------------------
Test iþleviyle ilgili yukarýdaki sorun, onu çalýþtýrdýðýnýzda sonuçlarý manuel olarak doðrulamanýza dayanmasýdýr. Bu, en kötü durumda beklenen cevabýn ne olduðunu
hatýrlamanýzý gerektirir (belgelenmediyse), ve gerçek sonuçlarý beklenen sonuçlarla manuel olarak karþýlaþtýrmanýzý gerektirir.

Daha iyisini yapabiliriz, testleri ve beklenen cevaplarý içeren ve bunlarý karþýlaþtýrmamýza gerek olmayan bir test iþlevi yazarak.


                        #include <iostream>

                        bool isLowerVowel(char c)
                        {
                            switch (c)
                            {
                            case 'a':
                            case 'e':
                            case 'i':
                            case 'o':
                            case 'u':
                                return true;
                            default:
                                return false;
                            }
                        }

                        // Baþarýsýz olan testin numarasýný veya tüm testlerin geçtiðini belirtmek için 0'ý döndürür
                        int testVowel()
                        {
                            if (!isLowerVowel('a')) return 1;
                            if (isLowerVowel('q')) return 2;

                            return 0;
                        }

                        int main()
                        {
                            int result { testVowel() };
                            if (result != 0)
                                std::cout << "testVowel() test " << result << " baþarýsýz.\n";
                            else
                                std::cout << "testVowel() testleri geçti.\n";

                            return 0;
                        }

Artýk herhangi bir zamanda testVowel()'ý çaðýrarak hiçbir þeyi bozmadýðýnýzý yeniden kanýtlayabilirsiniz ve test rutini sizin için tüm iþi yapacaktýr, ya 
bir "her þey yolunda" sinyali (dönüþ deðeri 0) ya da geçmeyen test numarasý döndürerek, neden bozulduðunu inceleyebilirsiniz. Bu özellikle eski kodlarý
deðiþtirirken, kazara bir þeyleri bozmadýðýnýzdan emin olmak için çok kullanýþlýdýr!

Unit Testing Frameworklarý
--------------------------

Diðer fonksiyonlarý çalýþtýrmak için fonksiyonlar yazmak o kadar yaygýn ve kullanýþlýdýr ki, bu iþlemi yazma, sürdürme ve yürütme sürecini basitleþtirmeye yardýmcý 
olacak þekilde tasarlanmýþ bütün çerçeveler (birim test çerçeveleri ( unit testing frameworks ) olarak adlandýrýlýr) vardýr. Bunlar üçüncü taraf yazýlýmlarý
içerdiðinden, burada bunlarý ele almayacaðýz, ancak var olduklarýný bilmelisiniz.

Entegrasyon Testleri
--------------------

Her bir biriminiz izolasyon halinde test edildikten sonra, bunlar programýnýza entegre edilebilir ve doðru bir þekilde entegre edildiklerinden emin olmak için tekrar
test edilebilir. Bu, bir entegrasyon testi olarak adlandýrýlýr. Entegrasyon testi genellikle daha karmaþýktýr - þu anda, programýnýzý birkaç kez çalýþtýrma ve 
entegre birimin davranýþýný gözden geçirme yeterli olacaktýr.
*/

/*
                                                                 8.14 Code Coverage ( Kod Kapsamý )


Bu derste, kodunuzun doðru olduðunu saðlamak için hangi türde testlerin yazýlmasýnýn yararlý olduðunu tartýþacaðýz."Code Coverage" ( Kod kapsamý ) terimi, bir
programýn test edilirken kaynak kodun ne kadarýnýn yürütüldüðünü tanýmlar.  Kod kapsamý için birçok farklý metrik bulunmaktadýr. Daha kullanýþlý ve popüler
olanlardan birkaçýný aþaðýdaki bölümlerde ele alacaðýz.

Statement coverage ( Deyim Kapsam )
-----------------------------------
Deyim kapsamý terimi, test rutinleriniz tarafýndan yürütülen kodunuzdaki ifadelerin yüzdesini ifade eder.

                            int foo(int x, int y)
                            {
                                int z{ y };
                                if (x > y)
                                {
                                    z = x;
                                }
                                return z;
                            }

Bu fonksiyonu foo(1, 0) olarak çaðýrmak, bu fonksiyon için tam deyim kapsamý saðlar, çünkü fonksiyondaki her deyim yürütülür.


isLower() fonksiyonumuz için:
                            bool isLowerVowel(char c)
                            {
                                switch (c) // statement 1
                                {
                                case 'a':
                                case 'e':
                                case 'i':
                                case 'o':
                                case 'u':
                                    return true; // statement 2
                                default:
                                    return false; // statement 3
                                }
                            }
Bu fonksiyonun tüm deyimleri test etmek için iki çaðrýya ihtiyaç duyacaktýr, çünkü ayný fonksiyon çaðrýsýnda deyim 2'ye ve 3'e ulaþmanýn bir yolu yoktur.

%100 deyim kapsamýný hedeflemek iyi bir þey olsa da, doðruluðu saðlamak genellikle yeterli deðildir.

Branch Coverage ( Þube - Dal Kapsamý )
--------------------------------------

Þube kapsamý, yürütülen þube yüzdesini ifade eder, her bir olasý þube ayrý ayrý sayýlýr. Bir if ifadesinin iki þubesi vardýr - koþul doðru olduðunda yürütülen bir 
þube ve koþul yanlýþ olduðunda yürütülen bir þube (koþula karþýlýk gelen bir else ifadesi olmasa bile). Bir switch ifadesinin çok sayýda þubesi olabilir.

Bir önceki örnekte var olan Foo fonksiyonunu düþünelim. Önceki foo(1, 0) çaðrýsý bize %100 deyim kapsamýný saðladý ve x > y durumunu test etti, ancak bu sadece bize
%50 þube kapsamýný saðlar. if ifadesinin yürütülmediði durumu test etmek için foo(0, 1) için bir çaðrýya daha ihtiyacýmýz var.

isLower() örneðimizi inceleyelim. isLowerVowel() fonksiyonunda, %100 þube kapsamýný saðlamak için iki çaðrýya ihtiyaç duyulacaktýr: biri (örneðin isLowerVowel('a')) 
ilk durumlarý test etmek için ve diðeri (örneðin isLowerVowel('q')) varsayýlan durumu test etmek için. Ayný gövdeye beslenen birden çok durumu ayrý ayrý test
etmek gerekmez - biri çalýþýyorsa, hepsi çalýþmalýdýr.

Þimdi sýradaki örneðe bakalým:
                            void compare(int x, int y)
                            {
                                if (x > y)
                                    std::cout << x << " is greater than " << y << '\n'; // case 1
                                else if (x < y)
                                    std::cout << x << " is less than " << y << '\n'; // case 2
                                else
                                    std::cout << x << " is equal to " << y << '\n'; // case 3
                            }

Burada %100 þube kapsamýný elde etmek için 3 çaðrýya ihtiyaç vardýr: compare(1, 0), ilk if ifadesi için pozitif kullaným durumunu test eder. compare(0, 1), ilk if 
ifadesi için negatif kullaným durumunu ve ikinci if ifadesi için pozitif kullaným durumunu test eder. compare(0, 0), ilk ve ikinci if ifadesi için negatif kullaným
durumunu test eder ve else ifadesini yürütür. Bu nedenle, bu fonksiyonun güvenilir bir þekilde 3 çaðrý ile test edildiðini söyleyebiliriz (bu, 18 quintilliondan
biraz daha iyidir).

*** BEST -> Kodunuzun %100 þube kapsamýný hedefleyin. þubeden kasýt akýþ kontrol 
* "Branch" terimi, programdaki kontrol akýþýndaki dallanmalarý ifade eder. Bu dallanmalar genellikle þu tür ifadelerle iliþkilidir: if, else if, 
else, switch, while, for gibi kontrol yapýlarý. Her bir kontrol yapýsýnýn içindeki her bir þart (veya durum), bir "branch" olarak adlandýrýlýr.
Örneðin: 
                            if (x > y)
                            {
                                // Branch 1
                                // ...
                            }
                            else if (x < y)
                            {
                                // Branch 2
                                // ...
                            }
                            else
                            {
                                // Branch 3
                                // ...
                            }
Loop coverage ( Döngü Kapsamý )
-------------------------------
Döngü Kapsamý (bilinen adýyla 0, 1, 2 testi olarak da adlandýrýlýr), kodunuzda bir döngü varsa, döngünün sýfýr, bir ve iki kez döndüðünde düzgün
çalýþtýðýndan emin olmanýz gerektiðini belirtir. Eðer 2 kez dönme durumu doðru çalýþýyorsa, bu durum tüm 2'den büyük iterasyonlar için de doðru
çalýþacaktýr. Bu üç test, böylece tüm olasýlýklarý kapsar (çünkü bir döngü negatif sayýda kez çalýþtýrýlamaz).

Örneðin:
                            #include <iostream>

                            void spam(int timesToPrint)
                            {
                                for (int count{ 0 }; count < timesToPrint; ++count)
                                        std::cout << "Spam! ";
                            }

Bu fonksiyon içindeki döngüyü doðru bir þekilde test etmek için üç kez çaðrý yapmalýsýnýz: sýfýr iterasyon durumunu test etmek için spam(0),
bir iterasyon durumunu test etmek için spam(1), ve iki iterasyon durumunu test etmek için spam(2). Eðer spam(2) çalýþýyorsa, o zaman spam(n) 
çalýþmalýdýr, burada n > 2.

*** BEST -> Döngülerinizin farklý iterasyon sayýlarýyla doðru bir þekilde çalýþtýðýndan emin olmak için 0, 1, 2 testini kullanýn.

Farklý girdi kategorilerini test etme
-------------------------------------

Parametre alan fonksiyonlar yazarken veya kullanýcý girdisi alýrken, farklý giriþ kategorilerinin nasýl iþlendiðini düþünün. Bu baðlamda, 
"kategori" terimini, benzer karakteristiklere sahip bir giriþ kümesini ifade etmek için kullanýyoruz.

Örneðin, bir tamsayýnýn karekökünü üreten bir fonksiyon yazsam, hangi deðerlerle test etmek mantýklý olurdu? Muhtemelen normal bir deðerle 
baþlardýnýz, mesela 4. Ancak 0 ve negatif bir sayý ile de test etmek iyi bir fikir olacaktýr.

Ýþte kategori testi için temel yönergeler:

    Tamsayýlar için, fonksiyonunuzun negatif deðerleri, sýfýrý ve pozitif deðerleri nasýl iþlediðini düþünmüþ olduðunuzdan emin olun. Ayrýca, 
    bu konuyla ilgiliyse taþma durumunu kontrol etmelisiniz.

    Ondalýk sayýlar için, fonksiyonunuzun beklenenden biraz daha büyük veya küçük olan hassasiyet sorunlarýna sahip deðerleri nasýl iþlediðini
    düþünmüþ olduðunuzdan emin olun. Denemek için iyi çift tip deðerler, 0.1 ve -0.1 (beklenenden biraz daha büyük olan sayýlarý test etmek için) ve
    0.6 ve -0.6 (beklenenden biraz daha küçük olan sayýlarý test etmek için) olabilir.

    Diziler için, fonksiyonunuzun boþ bir dize, alfasayýsal bir dize, boþluk içeren dizeler (önceki, sonraki ve iç dizeler) ve sadece boþluklardan 
    oluþan dizeleri nasýl iþlediðini düþünmüþ olduðunuzdan emin olun.

    Fonksiyonunuz bir iþaretçi alýyorsa, nullptr'ý da test etmeyi unutmayýn (bu anlam ifade etmiyorsa endiþelenmeyin, henüz bu konuyu ele almadýk).

*** BEST -> Unit testimizin düzgünce üstesinden geldiðinden emin olmak için Farklý kategorilerde olan girdi deðerlerini test et.


C++ daki genel semantic hatalar 
-------------------------------

Sözdizimi ve Semantik Hatalarýnda, C++ dilinin gramerine uygun olmayan kod yazdýðýnýzda oluþan sözdizimi hatalarýný ele aldýk. Derleyici, bu tür 
hatalarý size bildirecek, bu nedenle bunlarý tespit etmek genellikle kolay ve genellikle düzeltmesi basittir.

Ayrýca, niyet ettiðiniz þeyi yapmayan kod yazdýðýnýzda oluþan semantik hatalarý da ele aldýk. Derleyici genellikle semantik hatalarý tespit etmez 
(ancak bazý durumlarda akýllý derleyiciler uyarý oluþturabilir).

Semantik hatalar, programýn yanlýþ sonuçlar üretmesine, düzensiz davranýþa neden olmasýna, program verilerini bozmasýna, programýn çökmesine neden
olmasýna veya hiçbir etkisi olmamasýna yol açabilir, çoðu durumda tanýmlanmamýþ davranýþýn ayný belirtilerini gösterebilirler.

Programlar yazarken, neredeyse kaçýnýlmaz bir þekilde semantik hatalar yapacaksýnýz. Bunlardan bazýlarýný programý kullanarak fark edebilirsiniz: 
örneðin, bir labirent oyunu yazýyorsanýz ve karakteriniz duvarlardan geçebiliyorsa. Programýnýzý test etmek (8.13 - Kodunuzu Teste Tanýtma) ayný 
zamanda semantik hatalarý ortaya çýkarmaya yardýmcý olabilir.

Ancak baþka bir þey daha yardýmcý olabilir - ve bu, en yaygýn semantik hatalarýn hangi türlerinin olduðunu bilmek, böylece bu durumlarýn doðru 
olduðundan emin olmak için biraz daha fazla zaman harcayabilirsiniz.

Bu derste, C++'da meydana gelen en yaygýn semantik hata türlerini (çoðu akýþ kontrolü ile ilgili olan) ele alacaðýz.

Koþulsal Mantýk hatalarý
------------------------

En yaygýn semantik hata türlerinden biri, bir koþullu mantýk hatasýdýr. Koþullu mantýk hatasý, programcýnýn koþullu bir ifade veya döngü
þartýnýn mantýðýný yanlýþ kodladýðýnda ortaya çýkar. Ýþte basit bir örnek:

Örneðin x>5 yerine x>= 5 yazmak gibi ve bunlarýn looplar ile kullanýmýnda oluþan hatalar örnek olarak verilebilir. 

- Sonsuz Döngü hatalarý burada en sýk yapýlan hatalardan biri döngü sayacýnýn eklenmemesi veya arttýrma, azaltma gibi iþlemlerin unutulmasý
veya unsigned int deðerler kullanarak taþmaya neden olmak en genel hatalardýr. 

- For döngüsünde bahsettiðimiz off-by-one hatalarý burada da yanlýþ operatör seçimi yani < >= bunlardan kaynaklanan hatadýr loop un 1 tane eksik 
veya fazla dönmesi gibi. 

- Operatör öncelik sýrasýnda yapýlan yanlýþlar. Mesela mantýksal AND in mantýksal OR dan üstün olmasý gibi veya mantýksal NOT ýn > operatöründen
yüksek önceliðe sahip olmasýndan bundan kaçýnmak kolay parantezler kullanarak kaçýnabiliriz.

- Float sayýlarýn hassasiyet sorunlarý, float deðiþkeni sayýnýn tamamýný depolamak için yeterli duyarlýlýða sahip deðildir. Karþýlaþtýrma 
iþlemlerinde float sayý kullanmaktan kaçýnmak gerekiyor aksi halde hassasiyetten sonra gelen sayýlarda yuvarlama hatalarýndan dolayý program 
düzgün çalýþmayabilir. 

- Tam sayý bölme hatasý, bir bölme iþleminde operandlarýn her ikisi de tam sayý olursa bu bölmeye integer division yani tam sayý bölme iþlemi denir
Bu iþlemde oluþacak olan ondalýk bir sayý varsa ondalýk kýsmý DÜÞÜRÜLÜR. Düþmesini istemiyorsak operandlarýn birini float veya double olarak 
yapmamýz gerekir. bunun içinde static_cast<float>()  i kullanabiliz.

- Yanlýþlýklar kullanýlan null ifadesi, Yaygýn if ifadesi problemlerinde, hiçbir þey yapmayan ifadeler olan boþ ifadeleri ( null statement )
ele aldýk. Hatýrlayalým if ( condition );
                             statements ->>> Burada bu ifade her türlü yürütülecektir çünkü noktalý virgül kullanarak null statement yaptýk 
                                             Bu programýn akýþýný veya hesaplarý belki de bir roketi ateþleyebilir. :))

- Gerektiðinde bileþik ifade kullanmamak, Bu hata da yine if ifadeleri ile alakalý dangling else problemini oluþturan sebep if ifadesinden 
sonra blok oluþturmazsak sadece 1 statement if e baðlý olur bunu farketmeden 2.ifadeyi koyduðumuzda 2.ifade her türlü durumda yürütülecektir.
Roket ateþlendi :D
*/
/*
                                            8.16 Hata tespiti ve Hatalarla uðraþma

Ders 8.15'te, C++'ta yaygýn semantik hatalarý inceledik. Yeni C++ programcýlarýnýn dil özelliklerini yanlýþlýkla yanlýþ kullanmasýnýn bir sonucu
olarak ortaya çýkan hatalar kolayca düzeltilebilir.

Ancak bir programdaki çoðu hata, genellikle programcý tarafýndan yapýlan hatalý varsayýmlar veya uygun hata algýlama/iþleme eksikliði nedeniyle
meydana gelmez. Örneðin, bir öðrencinin notunu aramak için tasarlanmýþ bir iþlevde þunlarý varsaymýþ olabilirsiniz:

        Aranan öðrencinin var olacaðý.
        Tüm öðrenci adlarýnýn benzersiz olacaðý.
        Sýnýfýn harf notu sistemini kullanacaðý (geçti/kaldý yerine).
Bu varsayýmlardan herhangi biri gerçek deðilse ne olur? Eðer programcý bu durumlarý önceden düþünmediyse, program bu durumlar ortaya çýktýðýnda
(genellikle iþlev yazýldýktan sonra uzun bir süre sonra) muhtemelen arýzalanacak veya çökecektir.

* Bir iþlev bittiðinde, programcý çaðrýlan iþlemin baþarýlý olduðunu varsayabilir, ancak bu doðru deðildir.
* Bir program giriþ alýrken (kullanýcýdan veya bir dosyadan), programcý giriþin doðru biçimde ve semantik olarak geçerli olduðunu varsayabilir,
  ancak bu doðru deðildir.
* Bir iþlev çaðrýldýðýnda, programcý argümanlarýn semantik olarak geçerli olacaðýný varsayabilir, ancak bu doðru deðildir.

Birçok yeni programcý, yalnýzca hata olmayan durumlarý içeren "mutlu yolu" test eder. Ancak ayrýca, iþlerin ters gidebileceði "üzgün yollarý"
da planlamalý ve test etmelisiniz. 3.10 dersinde belirtildiði gibi, savunmacý programlama ( defensive programming ), yazýlýmýn hem son
kullanýcýlar hem de geliþtiriciler (programcýlar kendileri veya diðerleri) tarafýndan yanlýþ kullanýlma olasýlýklarýnýn tümünü düþünme pratiðidir.
Bir yanlýþ kullanýmý öngördüðünüzde (veya keþfettiðinizde), bir sonraki adým bununla baþa çýkmaktýr.

Bu ders kapsamýnda, bir iþlev içinde bir þeyler ters gittiðinde (yani, hatalý durumlar) ne yapýlacaðýný tartýþacaðýz. Ardýndan, kullanýcý giriþini
doðrulama hakkýnda konuþacak ve ardýndan varsayýmlarý belgeleme ve doðrulamaya yardýmcý olan kullanýþlý bir aracý tanýtacaðýz.

Fonksiyonlarda oluþan hatalarla uðraþma
---------------------------------------
Fonksiyonlar birçok nedenle baþarýsýz olabilir; çaðýran, geçersiz bir deðerle bir argüman iletebilir veya fonksiyonun içinde bir þeyler baþarýsýz 
olabilir. Örneðin, bir dosyayý okumak için açan bir fonksiyon, dosya bulunamazsa baþarýsýz olabilir.

Bu durumda, birkaç seçeneðiniz vardýr. Bir hatayý iþlemenin en iyi yolu yoktur - gerçekten sorunun doðasýna ve sorunun düzeltilip 
düzeltilemeyeceðine baðlýdýr.

4 Genel strateji vardýr:
    1 - Hatayý fonksinun içinde çözmek
    2 - Hatayý çözmek için hatayý fonksiyonu çaðýrana iletmek
    3 - Programý durdurmak
    4 - Bir istisna fýrlatmak veya saymak .d    

1 Numaralý durum 
----------------
Mümkünse, hatanýn meydana geldiði fonksiyonda hatadan kurtulmak, hatanýn fonksiyon dýþýndaki herhangi bir kodu etkilemeden sýnýrlanýp 
düzeltilmesini saðlar. Burada iki seçenek bulunmaktadýr: baþarý elde edilene kadar tekrar denemek veya gerçekleþtirilen iþlemi iptal etmek.

Eðer hata programýn kontrolü dýþýndaki bir þeyden kaynaklanmýþsa, program baþarý elde edilene kadar tekrar deneyebilir. Örneðin, eðer programýn
bir internet baðlantýsýna ihtiyacý varsa ve kullanýcý baðlantýsýný kaybetti ise, program bir uyarý gösterebilir ve ardýndan bir döngü kullanarak
periyodik olarak internet baðlantýsýný yeniden kontrol edebilir. Alternatif olarak, eðer kullanýcý geçersiz bir giriþ yapmýþsa, program 
kullanýcýdan tekrar denemesini isteyebilir ve kullanýcý geçerli bir giriþ yapana kadar döngü içinde kalabilir. Geçersiz giriþi iþleme ve döngü 
kullanarak tekrar deneme örneklerini bir sonraki derste (8.17 -- std::cin ve geçersiz giriþ iþleme) göstereceðiz.

Alternatif bir strateji ise hatayý sadece yok saymak ve/veya iþlemi iptal etmektir. Örneðin:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                    }


Yukarýdaki örnekte, eðer kullanýcý y için geçersiz bir deðer gönderirse, bölme iþleminin sonucunu yazdýrmama talebini sadece yok sayarýz. Bunu
yapmanýn baþlýca zorluðu, çaðýrýcý veya kullanýcýnýn bir þeyin yanlýþ gittiðini belirleme yolunun olmamasýdýr. Bu durumda, bir hata mesajý 
yazdýrmak faydalý olabilir:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                        else
                            std::cout << "Error: Could not divide by zero\n";
                    }

Ancak, çaðrýlan fonksiyonun çaðýran fonksiyondan bir dönüþ deðeri üretmesi veya bazý faydalý yan etkileri olmasý bekleniyorsa, hatayý sadece yok
saymak bir seçenek olmayabilir.

2 Numaralý durum
----------------
Çoðu durumda, hatayla karþýlaþýldýðý fonksiyonda hatayý makul bir þekilde iþlemek mümkün olmayabilir. Örneðin, aþaðýdaki fonksiyonu düþünün:

                    double doDivision(int x, int y)
                    {
                        return static_cast<double>(x) / y;
                    }
Eðer y 0 ise, ne yapmalýyýz? Program mantýðýný sadece atlayamayýz, çünkü fonksiyon bir deðer döndürmelidir. Kullanýcýdan yeni bir y deðeri
girmesini istememeliyiz çünkü bu bir hesaplama fonksiyonu ve bunun içine giriþ rutinlerini eklemek, bu fonksiyonu çaðýran program için uygun 
olabilir veya olmayabilir.

Bu tür durumlarda, hatayý çaðrana iletmek ve umut etmek ki çaðýran bununla baþa çýkabilir.

Bunu nasýl yapabiliriz?

Eðer fonksiyonun void dönüþ türü varsa, baþarý veya baþarýsýzlýðý gösteren bir Boole türü döndürmek için deðiþtirilebilir. Örneðin, þu yerine:

                    void printDivision(int x, int y)
                    {
                        if (y != 0)
                            std::cout << static_cast<double>(x) / y;
                        else
                            std::cout << "Error: Could not divide by zero\n";
                    }

Bunu yapabiliriz: 
                    bool printDivision(int x, int y)
                    {
                        if (y == 0)
                        {
                            std::cout << "Error: could not divide by zero\n";
                            return false;
                        }

                        std::cout << static_cast<double>(x) / y;

                        return true;
                    }

Bu þekilde, çaðýran fonksiyon, fonksiyonun bir nedenle baþarýsýz olup olmadýðýný kontrol edebilir.

Eðer fonksiyon normal bir deðer döndürüyorsa, iþler biraz daha karmaþýk hale gelir. Bazý durumlarda, dönüþ deðerlerinin tam aralýðý kullanýlmaz. 
Bu tür durumlarda, normalde normal olarak meydana gelmeyecek bir hata durumunu göstermek için kullanýlamayacak bir dönüþ deðeri kullanabiliriz.
Örneðin, aþaðýdaki fonksiyonu düþünün:

                    // x'in tersi 1/x dir.
                    double reciprocal(double x)
                    {
                        return 1.0 / x;
                    }

Bir sayýnýn tersi, 1/x olarak tanýmlanýr ve bir sayýnýn tersi ile çarpýlmasý sonucunda 1 elde edilir.

Ancak, eðer kullanýcý bu fonksiyonu reciprocal(0.0) olarak çaðýrýrsa, sýfýra bölme hatasý ve program çökmesi alýrýz, bu nedenle açýkça bu duruma
karþý korunmalýyýz. Ancak bu fonksiyon bir double deðeri döndürmelidir, bu durumda ne tür bir deðer döndürmeliyiz? Bu fonksiyonun meþru bir sonuç
olarak 0.0 üretmeyeceði ortaya çýktýðýndan, bir hata durumunu göstermek için 0.0'ý döndürebiliriz.

                    // The reciprocal of x is 1/x, returns 0.0 if x=0
                    double reciprocal(double x)
                    {
                        if (x == 0.0)
                            return 0.0;

                        return 1.0 / x;
                    }

Ancak, tam dönüþ deðeri aralýðýna ihtiyaç duyuluyorsa ve dönüþ deðeriyle bir hata gösterimi yapmak mümkün deðilse (çünkü çaðýran, dönüþ deðerinin
geçerli bir deðer mi yoksa bir hata deðeri mi olduðunu anlayamaz), o zaman bu durumu iþaretlemek zor olacaktýr.

Bu tür bir durumda, `std::optional`'ý kullanmak iyi bir seçenek olabilir. Þu anda `std::optional`'ý ele almýyoruz ancak gelecekteki bir
güncellemede bunu yapmayý düþünüyoruz.

Ölümcül Hatalar ( Fatal Errors )
--------------------------------
Eðer hata programýn düzgün çalýþmaya devam edemeyecek kadar kötüyse, bu duruma kurtarýlamaz hata (ayrýca ölümcül hata olarak da adlandýrýlýr)
denir. Bu tür durumlarda en iyi þey, programý sonlandýrmaktýr. Eðer kodunuz `main()` içinde veya doðrudan `main()` tarafýndan çaðrýlan bir 
fonksiyon içinde ise, en iyi çözüm `main()`'in bir döndürme kodu ile sonlanmasýna izin vermektir. Ancak, eðer derinlemesine iç içe geçmiþ bir
alt fonksiyonda bulunuyorsanýz, hatayý `main()`'e kadar iletmek uygun veya mümkün olmayabilir. Bu durumda, bir durma ifadesi 
(örneðin `std::exit()`) kullanýlabilir.

Örneðin:
                    double doDivision(int x, int y)
                    {
                        if (y == 0)
                        {
                            std::cout << "Error: Could not divide by zero\n";
                            std::exit(1);
                        }
                        return static_cast<double>(x) / y;
                    }
Exceptions ( Ýstisnalar diye çevirdim ama :))
---------------------------------------------
Çünkü bir fonksiyondan çaðýrana bir hata döndürmek karmaþýktýr (ve bunu yapmanýn birçok farklý yolu tutarsýzlýkla sonuçlanabilir ve tutarsýzlýk 
hatalara yol açabilir), C++, hatalarý çaðýrana iletmek için tamamen ayrý bir yol sunar: istisnalar.

Temel fikir, bir hata meydana geldiðinde bir istisna "fýrlatýlmasý"dýr. Eðer mevcut fonksiyon hata durumunu "yakalamazsa", fonksiyonu çaðýran kiþi 
hatayý yakalama þansýna sahiptir. Eðer çaðýran kiþi hata durumunu yakalamazsa, çaðýranýn çaðýrýcýsý hata durumunu yakalama þansýna sahiptir. Hata,
çaðrý yýðýný boyunca giderek yukarý doðru hareket eder ve ya yakalanýr ve iþlenir (bu noktada yürütme normal þekilde devam eder), ya da main() 
hatayý iþleyemezse (bu noktada program bir istisna hatasý ile sonlandýrýlýr).

Bu konuyu, bu öðretici serisinin 27. bölümünde ele alýyoruz.


std::cout, std::cerr ve loglama -> Ne zaman hangisini kullanmalýyýz
-------------------------------------------------------------------

Belki de std::cerr'ý, std::cout'ý ve bir metin dosyasýna loglama yapmayý ne zaman kullanmanýz gerektiðini merak ediyorsunuzdur.

Varsayýlan olarak, hem std::cout hem de std::cerr metni konsola yazdýrýr. Ancak, modern iþletim sistemleri çýkýþ akýþlarýný dosyalara yönlendirmek
için bir yol saðlar, böylece çýktý daha sonra incelenmek veya otomatik iþleme tabi tutulmak üzere yakalanabilir.

Bu tartýþma için, iki tür uygulamayý ayýrt etmek faydalýdýr:

* Etkileþimli uygulamalar, kullanýcýnýn baþlatmadan sonra etkileþimde bulunacaðý uygulamalardýr. Standalone ( baðýmsýz ve kendi baþýna çalýþabilir )
  uygulamalarýn çoðu, oyunlar ve müzik uygulamalarý gibi, genellikle bu kategoriye girer.
* Etkileþimsiz uygulamalar ise kullanýcý etkileþimi gerektirmeyen uygulamalardýr. Bu programlarýn çýktýlarý, genellikle baþka bir uygulama için 
  giriþ olarak kullanýlabilir.

Etkileþimsiz uygulamalar içinde iki tür bulunmaktadýr:

1. **Araçlar (Tools):**
   - Araçlar, genellikle belirli bir hemen sonuç üretmek üzere baþlatýlan ve bu sonucu ürettikten sonra sona eren etkileþimsiz uygulamalardýr.
   - Bir örneði, Unix'in "grep" komutudur. Bu, metni belirli bir desene göre arayan bir yardýmcý programdýr.

2. **Servisler (Services):**
   - Servisler, genellikle arka planda sessizce çalýþarak sürekli bir iþlevi yerine getiren etkileþimsiz uygulamalardýr.
   - Bir örneði, bir virüs tarayýcýsý olabilir. Bu, sürekli olarak bilgisayar sistemini tarayarak virüsleri kontrol eder.


Etkileþimsiz uygulamalar içinde iki tür bulunmaktadýr:

Araçlar (Tools):
Araçlar, genellikle belirli bir hemen sonuç üretmek üzere baþlatýlan ve bu sonucu ürettikten sonra sona eren etkileþimsiz uygulamalardýr.
Bir örneði, Unix'in "grep" komutudur. Bu, metni belirli bir desene göre arayan bir yardýmcý programdýr.

Servisler (Services):
Servisler, genellikle arka planda sessizce çalýþarak sürekli bir iþlevi yerine getiren etkileþimsiz uygulamalardýr.
Bir örneði, bir virüs tarayýcýsý olabilir. Bu, sürekli olarak bilgisayar sistemini tarayarak virüsleri kontrol eder.

Bu iki tür etkileþimsiz uygulama, farklý kullaným senaryolarýna ve iþlevlere sahiptir. Araçlar anlýk sonuçlar üretir ve sonra sonlanýrken, 
servisler sürekli bir iþlevi yerine getirerek uzun süre çalýþabilirler.


Ýþte bazý kýyaslamalar:

* Tüm geleneksel, kullanýcýya yönelik metinler için std::cout kullanýn.

* Etkileþimli bir program için, std::cout'u normal kullanýcýya yönelik hata mesajlarý için kullanýn (örneðin, "Giriþiniz geçersizdi"). std::cerr
  veya bir log dosyasýný, teþhis sorunlarý için yardýmcý olabilecek ancak normal kullanýcýlar için muhtemelen ilginç olmayan durum ve teþhis
  bilgileri için kullanýn. Bu, teknik uyarýlar ve hatalar (örneðin, fonksiyon x'e kötü giriþ), durum güncellemeleri (örneðin, dosya x baþarýyla
  açýldý, internet servisi x'e baðlanýlamadý), uzun görevlerin yüzde tamamlanmasý (örneðin, kodlama %50 tamamlandý) gibi þeyleri içerebilir...

* Etkileþimsiz bir program (araç veya servis) için, std::cerr'i yalnýzca hata çýktýsý için kullanýn (örneðin, dosya x açýlamadý). Bu, hatalarýn 
  normal çýktýdan ayrý bir þekilde görüntülenmesine veya ayrýþtýrýlmasýna izin verir.
   
* Ýþlemeli bir doðaya sahip olan (örneðin, belirli olaylarý iþleyen bir web tarayýcýsý veya etkileþimsiz bir web sunucusu gibi) herhangi bir 
  uygulama türü için, olaylarýn incelenebilecek bir iþlem günlüðü üretmek için bir log dosyasýný kullanýn. Örneðin, þu anda hangi dosyayý 
  iþlediðini, tamamlanma yüzdesini, belirli bir hesaplama aþamasýna ne zaman baþladýðýný, uyarýlarý ve hata mesajlarýný çýktýlamak.

| Kullaným Durumu                                      | Uygun Çýkýþ Mekanizmalarý                     |
|------------------------------------------------------|-----------------------------------------------|
| Geleneksel, kullanýcýya yönelik metin çýktýlarý      | std::cout                                     |
| Etkileþimli program, hata mesajlarý                  | std::cout (normal hata mesajlarý), std::cerr  |
| Etkileþimli program, durum güncellemeleri            | std::cerr, log dosyasý                        |
| Etkileþimsiz program (araç veya servis), hata çýktýsý| std::cerr                                     |
| Ýþlemeli uygulama (web tarayýcýsý, web sunucusu vb.) | log dosyasý                                   |
*/