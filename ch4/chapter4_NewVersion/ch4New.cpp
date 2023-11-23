// Chapter 4 tekrardan iþlenecek. Düzgünce virgül atlamadan not alýp devam edecez Diðer not hoþuma gitmedi.
#include <iostream>

int main()
{
    return 0;
}
/*
                                                     TEMEL VERÝ TÝPLERÝ 
Bitler Byteler ve Adresleme
Deðiþkenler, bilgi depolamak için kullanýlan belleðin belirli bir parçasýna isimlerdir, bu parça rastgele eriþim belleði (RAM) içerisindedir.

Belleðin en küçük birimi, 0 veya 1 deðerini alabilen bir ikili sayý olan "bit"tir. Bit, geleneksel bir ýþýk anahtarý gibi düþünülebilir.

Bellek, ardýþýk birimlere sahip "bellek adresleri" veya "adresler" tarafýndan organize edilmiþtir. Adresler, bellekte belirli bir konumdaki 
içeriklere eriþmemizi saðlar.

Modern bilgisayar mimarilerinde her bitin kendi benzersiz bellek adresine sahip olmasý gerekmez. Bunun yerine, her bellek adresi 1 bayt veri
içerir. Bayt, iþlem birimi olarak 8 ardýþýk bit içerir.

Bilgisayar belleði genellikle bitlerin yaný sýra baytlarla çalýþýr. Baytlar, genellikle bir bilgi grubunu temsil eder ve birim olarak iþlenir.

Bellek adreslerinin sayýsý sýnýrlýdýr ve genellikle veriye bitler halinde eriþme ihtiyacý nadirdir. Bu nedenle, modern bilgisayar mimarilerinde
her bitin kendi adresi olmaz.

Bellek, bilgisayar programlarý tarafýndan kullanýlan bir kaynaktýr ve deðiþkenlerin deðerlerini depolar. Program çalýþtýkça bellek kullanýlýr 4
ve deðiþkenler bellekteki belirli adreslere yerleþtirilir.

Bayt, 8 bit içeren bir veri birimidir ve genellikle bir karakterin temsil edildiði temel bellek birimidir.
*C++'da genellikle "bayt boyutunda" veri yýðýnlarýyla çalýþýrýz. Bazý old bilgisayar mimarilerinde deðiþebilir fakat endiþelenmeye gerek yok.
*/
/*
Veri tipleri 

Yani buradaki bilgiye göre veri tiplerinden kastýmýz belleðin belirli bitlerini isimlendirmek. Örneðin bu 4 bit e integer diyecez diyerek tanýmladýk
Bundan sonra onu integer olarak yorumlayacaðýz. Örnek veriyorum tekrar 65 deðerini saklicaz bu bellekte 0100 0001 olarak tutulur. Kullanacaðýmýz 
zaman tekrar 65 olarak fönüþtürülür. Burada bizim düþünmemiz gereken tek þey nesnemize en çok uyan veri tipini seçmemiz.

The _t Soneki

Daha yeni C++ sürümlerinde tanýmlanan birçok tür (örneðin std::nullptr_t) _t soneki kullanýr. Bu sonek, "tür" anlamýna gelir ve modern türlere 
uygulanan yaygýn bir adlandýrmadýr.Eðer bir þey _t soneki içeriyorsa, muhtemelen bir türdür. Ancak birçok türde _t soneki bulunmaz,
bu nedenle bu tutarlý bir þekilde uygulanmaz.
*/
/*
Void 

Void, eksik bir türün ilk örneðidir. Bir eksik tür, bildirilmiþ ancak henüz tanýmlanmamýþ bir türdür. Derleyici, bu türlerin varlýðýný bilir,
ancak bu türün nesneleri için kaç bellek ayrýlacaðýný belirlemek için yeterli bilgiye sahip deðildir. void, bilerek eksiktir çünkü bir türün 
eksikliðini temsil eder ve bu nedenle tanýmlanamaz.

* - * void value; // çalýþmaz, deðiþkenler eksik türle tanýmlanamaz

Bunun dýþýnda deðer döndürmeyen fonksiyonlarý tanýmlamak için kullanýlýr. C de de bir fonksiyonun parametresinin olmadýðýný bildirmek için void 
kelimesi kullanýlýrdý fakat c++ da bu durum geri yönlü uyumluluk nedeni ile desteklense de parametresi olmayan fonksiyona int main(void) gibi yazmak 
yerine boþ býrakmak her zaman daha iyidir. 
*/
/*
                                                    4.3 — Nesne boyutlarý ve sizeof operatörü
                                                    -----------------------------------------

Genellikle deðiþken adlarý aracýlýðýyla belleðe eriþtiðimizden, yüksek seviyeli programlama dillerinde derleyici, bir deðiþkenin kaç byte bellek 
kullandýðýný bizden saklar. Yani, bir deðiþkeni kullanýrken doðrudan bellek adreslerini düþünmemize gerek yoktur.

Ancak, bir nesnenin bellekte ne kadar yer kapladýðýný bilmek yine de önemlidir. Çünkü bir nesnenin kullanacaðý bellek miktarý, içinde
taþýyabileceði bilgi miktarýný belirler. Mesela, tek bir bit sadece 0 veya 1 deðerini alabilir.

Genelleþtirmek gerekirse, n bit içeren bir veri türü 2^n benzersiz bilgi tutar ileride diðer veri tipleri ile beraber daha detaylý öðreneceðiz.

Yeni programcýlar genellikle kodlarýný mümkün olan en az belleði kullanacak þekilde optimize etmeye fazla odaklanýrlar. Çoðu durumda, 
bu ihmal edilebilir bir fark yaratýr. Bakýmý kolay olan bir kod yazmaya odaklanýn ve yararý önemli olacak yerlerde ve zamanlarda optimize edin.


Temel veri tiplerinin boyutlarýyla ilgili bir sonraki soru þu olabilir: "Farklý veri tiplerine sahip deðiþkenler ne kadar bellek kullanýr?"

Belki þaþýrtýcý olabilir ancak C++ standardý, temel tiplerin tam boyutunu tanýmlamaz. Bunun yerine, sadece integral ve char tipleri için 
minimum boyutu (bit cinsinden) tanýmlar ve tüm tiplerin gerçek boyutunu uygulama tanýmlý býrakýr! C++ standardý ayrýca bir bytenin 8 bit
olduðunu varsaymaz.Bu öðretici serisinde, genellikle modern mimariler için genel olarak doðru olan bazý makul varsayýmlar yaparak basitleþtirilmiþ 
bir görünüm alacaðýz:

-* Bir byte 8 bittir.
-* Bellek, byte adreslenebilir, bu nedenle en küçük nesne 1 bytedir.
-* Ondalýk sayý desteði IEEE-754 uyumludur.
-* 32-bit veya 64-bit mimari üzerindeyiz.


Belirli bir makinedeki veri tiplerinin boyutunu belirlemek için, C++ sizeof adlý bir operatör saðlar. sizeof operatörü, ya bir türü ya da
bir deðiþkeni alan ve onun boyutunu byte cinsinden döndüren bir tek operandlý operatördür. Aþaðýdaki programý derleyip çalýþtýrarak veri 
tiplerinin boyutlarýný öðrenebilirsiniz: Tabi ki mimariden mimariye veya sistem ayarlarýna göre deðiþebilir. 
sizeof operatörü, void gibi tamamlanmamýþ (incomplete) tipler üzerinde kullanýlmaya çalýþýldýðýnda derleme hatasý ile sonuçlanýr. void tipi, 
boyutu belirsiz olan bir tip olarak kabul edilir, çünkü bellekte kaç byte yer kapladýðý belirli deðildir.

genellikle modern makinelerde, temel veri tiplerine ait nesneler hýzlýdýr. Bu nedenle, bu tipleri kullanýrken veya kopyalarken performans 
endiþesi genellikle bir sorun olmamalýdýrbellek kullanýmý ile performans arasýndaki iliþki, genel sistem mimarisi, derleyici optimizasyonlarý
ve kullanýlan algoritmalar gibi birçok faktöre baðlýdýr. Optimize edilmiþ ve okunabilir kod yazmak için genellikle tipik kullaným senaryolarýný
deðerlendirmek ve ölçüm yapmak önemlidir
*/
/*
                                                        SIGNED INTEGER

* Bir tamsayý, pozitif ve negatif tam sayýlarý, 0'ý da içeren bir integral türdür (örneðin, -2, -1, 0, 1, 2). C++, kullaným için kullanýlabilir 
olan 4 temel tamsayý türüne sahiptir: 
* Temel tamsayý türleri arasýndaki temel fark, deðiþen boyutlara sahip olmalarýdýr - daha büyük tamsayýlar daha büyük sayýlarý temsil edebilir.
C++, tamsayýlarýn belirli bir minimum boyuta sahip olacaðýný, ancak belirli bir boyuta sahip olacaðýný garanti etmez.

Ek bilgi olarak…
Teknik olarak, bool ve char türleri integral türler olarak kabul edilir (çünkü bu türler deðerlerini tamsayý olarak saklarlar). Birkaç sonraki 
ders için, bu türleri tartýþmamýzdan dýþlayacaðýz.

Ýkili temsil içinde, sayýnýn iþaretini saklamak için tek bir bit kullanýlýr (iþaret biti olarak adlandýrýlýr). Ýþaret olmayan bitler (büyüklük
bitleri olarak adlandýrýlýr) sayýnýn büyüklüðünü belirler. C++ dilinde, tamsayýlar varsayýlan olarak iþaretlidir, yani sayýnýn iþareti sayýnýn
bir parçasý olarak saklanýr. Bu nedenle, bir iþaretli tamsayý hem pozitif hem de negatif sayýlarý (ve 0'ý) tutabilir.

Signed türlerin tanýmlanmasý örnekler ile: 
    short s;      // "short int" yerine "short" tercih edilir
    int i;
    long l;       // "long int" yerine "long" tercih edilir
    long long ll; // "long long int" yerine "long long" tercih edilir
Yani signed short int veya short int gibi tanýmlamalar da geçerlidir. Fakat signed gereksizdir çünkü integerler varsayýlan olarak zaten 
signed olarak tanýmlanýr. int yazmak da kafa karýþýklýðý yapabilir ya da dikkatsizlik ile short unutulabilir. 

Menzilleri yani rangeleride yine 2^n formülü ile bulunur örneðin 8 bitlik iþaretli 2^8 = 256 => -128 ve 127 aralýðýný tutar. Diðer türlerde bu 
þekilde hesap edilir. Burada 7 bit büyüklüðe 1 bit ise iþarete gittiði için bu þekilde. 

yani -(2n-1) ile 2n-1-1 aralýktýr. Her hangi verinin tutabileceði veri büyüklüðü.

*** ÝÞARETLÝ SAYILARDA TAÞMA
----------------------------
C++20 standardý þu genel ifadeyi kullanýr: "Bir ifadenin deðerlendirilmesi sýrasýnda sonuç matematiksel olarak tanýmlanmamýþsa veya türünün 
temsil edilebilir deðerler aralýðýnda bulunmuyorsa, davranýþ tanýmsýzdýr." Günlük dilde buna taþma (overflow) denir.Bu nedenle, 140 deðerini
bir 8-bit iþaretli tamsayýya atamak tanýmsýz davranýþa neden olacaktýr.

*** Tam sayý bölmesi 
--------------------
Ek olarak tam sayýlarda bölme iþlemi yapacak olursa örneðin 20/5= 4 olur fakat 8/ 5 yaparsak burada cevap 1 olur geriye kalan kýsým ise direktmen 
düþürülür yani yuvarlanmaz. Eðer virgüllü bir sonuca ihtiyacýmýz yoksa sorun olmaz fakat ihtiyaç varsa bilgi kaybý olur dikkat et.
*/
/*
                                                      ÝÞARETSÝZ TAM SAYILAR 

Ýþaretsiz tam sayýlar negatif olmayan sayýlarý tutar. tanýmlamak için "unsigned" kelimesini deðiþkenin baþýna koymak yeterlidir:
    unsigned int a;
    unsigned short s;
    unsigned long long;
Ýþaretsiz sayýlarýn rangeleri hesap edilirken iþaret bitine ihtiyaç olmadýðý için hesaplama da düþüþ olmaz yani 0 ile 2^n-1 arasýnda olur.
Hiçbir negatif sayý gerekmediðinde, iþaretsiz tamsayýlar að oluþturma ve az belleðe sahip sistemler için çok uygundur, çünkü iþaretsiz
tamsayýlar fazladan bellek kullanmadan daha fazla pozitif sayý saklayabilir.
 

*** ÝÞARETSÝZ SAYILARDA TAÞMA
-----------------------------
Ýlginç bir þekilde, C++ standardý açýkça "unsigned operatörler içeren bir hesaplama asla taþmaz (overflow) " der. Bu, genel
programlama uzlaþmasýna aykýrýdýr çünkü genellikle tamsayý taþmasý, iþaretli ve iþaretsiz kullaným durumlarýný içerir (kaynak).
ÖRNEÐÝN
Sayý 280, 0 ile 255 arasýndaki 1 byte'lýk aralýðýmýza sýðacak kadar küçük deðildir. Türün en büyük sayýsýndan bir fazlasý 256'dýr.
Bu nedenle, 280'i 256'ya böleriz ve 1 kalan 24 elde ederiz. 24 kalaný saklanan deðerdir. Buna wrapping around veya modulo wrapping denir. 

-1 -2 gibi sayýlarda da baþa dönme var yani python daki tersten indeksleme gibi. -1 65535 olarak baþa döner ve burdan deðerlendirilerek devam eder.

Birçok geliþtirici (ve bazý büyük yazýlým geliþtirme þirketleri, örneðin Google gibi), genellikle geliþtiricilerin genellikle iþaretsiz tamsayýlardan kaçýnmasý gerektiðine inanmaktadýr.

Bu, genellikle iki problem yaratan iki davranýþtan kaynaklanmaktadýr.

Ýlk olarak, iþaretli deðerlerle, aralýðýn üstünü veya altýný kazara aþmak biraz çaba gerektirir çünkü bu deðerler 0'dan uzaktýr. 
Ýmzasýz sayýlarda, aralýðýn altýný kazara aþmak çok daha kolaydýr, çünkü aralýðýn altý 0'dýr ve bu deðer, deðerlerimizin çoðunun
bulunduðu yerden yakýndýr.

örneðin 2 - 3 gibi bir durum olduðu gibi taþma olur çok riskli hoceeeem.


Ýkinci olarak, daha da tehlikeli olaný, iþaretli ve iþaretsiz tamsayýlarý karýþtýrdýðýnýzda beklenmeyen davranýþlarýn ortaya çýkabilmesidir.
C++ dilinde, matematiksel bir iþlem (örneðin, aritmetik veya karþýlaþtýrma) bir iþaretli tamsayý ve bir iþaretsiz tamsayý içeriyorsa, 
genellikle iþaretli tamsayý iþaretsiz bir tamsayýya dönüþtürülür. Ve sonuç bu nedenle iþaretsiz olur. Örneðin:
Yani örnekte gör: 
    unsigned int u{ 2 };
    signed int s{ 3 };

    std::cout << u - s << '\n'; // 2 - 3 = 4294967295 -> u iþaretli bir sayý olsaydý doðru cevap çýkardý fakat olmadýðý için s iþaretsiz sayýya 
    çevrildi ve cevap farklý bir þekilde geldi. 

*** BEST
* Miktarlarý (hatta non-negatif olmasý gereken miktarlarý bile) ve matematiksel iþlemleri tutmak için iþaretli sayýlarý tercih edin. 
iþaretli ve iþaretsiz sayýlarý karýþtýrmaktan kaçýnýn.


O zaman ne zaman iþaretsiz sayýlarý kullanmalýsýnýz?

C++ dilinde hala iþaretsiz sayýlarý kullanmanýn uygun/necessary (gerekli) olduðu birkaç durum vardýr.

Ýlk olarak, bit manipülasyonu ile uðraþýldýðýnda (O bölümünde ele alýnan), iþaretsiz sayýlar tercih edilir. Ayrýca, iyi tanýmlanmýþ döngüselliðin
gerektiði durumlarda (þifreleme ve rastgele sayý üretimi gibi bazý algoritmalar için kullanýþlýdýr).

Ýkinci olarak, iþaretsiz sayýlarýn kullanýmý bazý durumlarda hala kaçýnýlmazdýr, özellikle dizi indeksleme ile ilgili durumlar. Diziler ve dizi
indeksleme derslerinde daha fazla bilgi vereceðiz.

Ayrýca, bir gömülü sistem için (örneðin bir Arduino) veya bazý diðer iþlemci/bellek sýnýrlý baðlamda, iþaretsiz sayýlarýn kullanýmý performans
nedenleriyle daha yaygýn ve kabul edilebilir (ve bazý durumlarda kaçýnýlmaz) olabilir.
*/
/*

                                            Sabit Geniþlikli Tam sayýlar ve size_t
hatýrlama: Bir önceki derste c++ ýn tam sayýlar için belirli bir bellek alaný vermek yerine minimum bellek alaný ile tanýmladýðýný ve bu bellek 
alanýnýn hedef sisteme göre deðiþebileceðini söylemiþtik. 

Neden tamsayý deðiþkenlerinin boyutu sabit deðil?
-------------------------------------------------
Kýsa cevap, bu durumun C'ye dayanmasýndan kaynaklanýr. Bilgisayarlar yavaþ olduðunda ve performans en önemli konu olduðunda, C, derleyici 
uygulayýcýlarýnýn int için hedef bilgisayar mimarisinde en iyi performansý sergileyen bir boyut seçmesine izin vermek amacýyla tamsayýlarýn
boyutunu bilinçli bir þekilde açýk býrakmýþtýr.

Bu durum kötü mü ?
------------------

Bu durum çaðdaþ standartlara göre evet, biraz tuhaf. Bir programcý olarak, belirsiz aralýklara sahip türlerle uðraþmak biraz absürt.

int türünü düþünün. int için minimum boyut 2 byte'dýr, ancak modern mimarilerde genellikle 4 byte'dýr. Bir int'in muhtemelen 4 byte 
olduðunu varsayarsanýz, programýnýz muhtemelen int'in aslýnda 2 byte olduðu mimarilerde yanlýþ davranacaktýr (çünkü muhtemelen 4 byte 
gerektiren deðerleri 2 byte bir deðiþkende saklýyorsunuz, bu da taþma veya tanýmsýz davranýþa neden olacaktýr). Maksimum uyumluluðu 
saðlamak için int'in yalnýzca 2 byte olduðunu varsayarsanýz, int'in 4 byte olduðu sistemlerde her bir tamsayý için 2 byte boþa harcamýþ
olursunuz ve bellek kullanýmýnýzý iki katýna çýkarmýþ olursunuz!

Yukarýdaki sorunlarý ele almak için, C99, herhangi bir mimaride ayný boyutta olmalarý garanti edilen bir dizi sabit geniþlikte tamsayýyý 
(stdint.h baþlýðý içinde) tanýmlamýþtýr.
Tablo da görebilirsin:
Name	            Type	          Range         	                                Notes
std::int8_t	    1 byte signed	    -128 to 127	                    Çoðu sistemde signed char gibi davranýyor tehlike. 
std::uint8_t	1 byte unsigned 	0 to 255	                    Çoðu sistemde unsigned char gibi davranýyor tehlike. 
std::int16_t	2 byte signed   	-32,768 to 32,767
std::uint16_t	2 byte unsigned 	0 to 65,535
std::int32_t	4 byte signed	    -2,147,483,648 to 2,147,483,647
std::uint32_t	4 byte unsigned	    0 to 4,294,967,295
std::int64_t	8 byte signed   	-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
std::uint64_t	8 byte unsigned	    0 to 18,446,744,073,709,551,615


C++, resmi olarak bu sabit geniþlikteki tamsayýlarý C++11'in bir parçasý olarak benimsemiþtir. Bunlara, <cstdint> baþlýðýný içe aktararak
eriþilebilir, burada std ad alaný içinde tanýmlanmýþlardýr. Ýþte bir örnek:

        #include <cstdint> // for fixed-width integers
        #include <iostream>

        int main()
        {
            std::int16_t i{5};
            std::cout << i << '\n';
            return 0;
        }


Sabit geniþlikteki tamsayýlarýn genellikle dile getirilen iki dezavantajý bulunmaktadýr.

Ýlk olarak, sabit geniþlikteki tamsayýlarýn tüm mimarilerde tanýmlý olmasý garanti edilmez. Yalnýzca geniþliklerine uyan temel türlerin ve 
belirli bir ikili temsilin bulunduðu sistemlerde var olurlar. Programýnýz, kullandýðýnýz sabit geniþlikteki bir tamsayýyý desteklemeyen herhangi
bir mimaride derlenemez. Ancak, çoðu modern mimarinin 8/16/32/64-bit deðiþkenlere standartlaþtýðý göz önüne alýndýðýnda, bu, programýnýzýn 
taþýnabilir olmasý gerekiyorsa nadiren bir sorun olacaktýr, ancak belirli bir egzotik ana bilgisayara veya gömülü mimarilere taþýnmasý gerekiyorsa
bu durum deðiþebilir.

Ýkinci olarak, sabit geniþlikteki bir tamsayý kullanýrsanýz, bazý mimarilerde daha geniþ bir türden daha yavaþ olabilir. Örneðin, 32 bit garanti
edilen bir tamsayýya ihtiyacýnýz varsa, std::int32_t'yi kullanmaya karar verebilirsiniz, ancak CPU'nuz aslýnda 64 bit tamsayýlarý iþlemekte daha
hýzlý olabilir. Ancak, CPU'nuzun belirli bir türü daha hýzlý iþleyebilmesi, programýnýzýn genel olarak daha hýzlý olacaðý anlamýna gelmez - 
modern programlar genellikle bellek kullanýmýyla sýnýrlýdýr ve daha büyük bellek ayak izi, daha hýzlý CPU iþleme hýzlandýrdýðýndan daha fazla
yavaþlayabilir. Bu, gerçekten ölçmeden zor bilinir.

Fast ve Least Tam sayýlarý
--------------------------
Yukarýdaki dezavantajlarý ele almak için, C++ ayrýca tanýmlanmýþ olan iki alternatif tamsayý kümesini de saðlar.

Hýzlý türler (std::int_fast#_t ve std::uint_fast#_t), en az # bit geniþliðinde en hýzlý imzalý/imzasýz tamsayý türünü saðlar 
(burada # = 8, 16, 32 veya 64). Örneðin, std::int_fast32_t size en az 32 bit olan en hýzlý imzalý tamsayý türünü saðlar. En hýzlý ifadesiyle,
CPU tarafýndan en hýzlý þekilde iþlenebilen tamsayý türünü anlýyoruz.

En küçük türler (std::int_least#_t ve std::uint_least#_t), en az # bit geniþliðinde en küçük imzalý/imzasýz tamsayý türünü saðlar
(burada # = 8, 16, 32 veya 64). Örneðin, std::uint_least32_t size en az 32 bit olan en küçük imzasýz tamsayý türünü saðlar.

Burada bazý tam sayý tipleri belirtildiði geniþliðe sahip olmayabilir yani mesela int_fast16_t makineden makineye 32 olabilir bu o makinenin 32 biti
16 bitten hýzlý iþlemesinden kaynaklanýyordur. 
Ancak, bu hýzlý ve en küçük tamsayýlara ait kendi dezavantajlarý vardýr: Ýlk olarak, pek çok programcý bunlarý gerçekten kullanmaz ve bu da bilgi
eksikliðinden dolayý hatalara neden olabilir. Ýkinci olarak, hýzlý türler, gerçek boyutlarý adlarýnda belirtilenden daha büyük olabileceðinden,
bellek israfýna neden olabilir. En ciddi dezavantajý ise fast/least türlerinin geniþlikleri deðiþebilir bu durum da programýmýzýn mimariden mimariye
farklý çözümlenmesinden dolayý farklý davranmasýna ve hatalara neden olabilir. 

    #include <cstdint> // for fixed-width integers
    #include <iostream>

    int main()
    {
        std::uint_fast16_t sometype { 0 };
        --sometype; // intentionally overflow to invoke wraparound behavior

        std::cout << sometype << '\n';

        return 0;
    }

Burada iþaretsiz sayýnýn taþmasýný saðlamaya çalýþýlmýþ denediðimizde farklý sonuçlar alýyoruz. Bu da gösteriyorki fast/least türlerini kullanýrken
mimarilerde dikkatli olmalý ve nasýl davrandýðýný bilmemiz gerekiyor. 

std::int8_t ve std::uint8_t'nin (ve buna karþýlýk gelen fast ve least türlerin) çoðu derleyici tarafýndan signed char ve 
unsigned char türleriyle ayný þekilde tanýmlandýðý ve iþlendiði için, bu 8-bit türlerin diðer sabit geniþlikli türlerden farklý 
davranýþ sergileyebileceði anlamýna gelir. Bu durum hatalara yol açabilir. Bu davranýþ, sistem baðýmlýdýr, bu nedenle bir mimaride doðru
davranan bir program, baþka bir mimaride doðru derlenmeyebilir veya doðru davranmayabilir.

Bu konuda bir örnek, 4.12 dersinde, tür dönüþümüne ve static_cast'a giriþte gösterilmektedir.

Tamsayý deðerleri saklarken, genellikle std::int8_t ve std::uint8_t (ve ilgili hýzlý ve en küçük türlerden) kaçýnýlmalý ve bunun yerine 
std::int16_t veya std::uint16_t kullanýlmalýdýr.

Temel tamsayý türlerinin, sabit geniþlikli tamsayý türlerinin, fast/leasr türlerinin ve signed/unsigned zorluklarýn çeþitli 
avantajlarý ve dezavantajlarý göz önüne alýndýðýnda, integral en iyi uygulamalar konusunda pek az bir uzlaþma vardýr.

Bizim duruþumuz, hýzlý olmaktan ziyade doðru olmanýn ve çalýþma zamanýnda baþarýsýz olmaktansa derleme zamanýnda baþarýsýz olmanýn daha
iyi olduðudur. Bu nedenle, sabit bir boyutta bir integral türüne ihtiyacýnýz varsa, fast/en küçük türlerden ziyade sabit geniþlikli 
türleri tercih etmenizi öneririz. Daha sonra belirli bir sabit geniþlikli türün belirli bir platformda derlenmeyeceðini keþfederse, o
noktada programýnýzý nasýl geçireceðinize (ve bunu dikkatlice yeniden test etmeye) karar verebilirsiniz.
*/
/*
                                                                size_t nedir 
            #include <iostream>

            int main()
            {
                std::cout << sizeof(int) << '\n';

                return 0;
            }
            Bu programa bakalým yazarýn programýnda 4 çýktýsýný veriyor. 

Oldukça basit, deðil mi? sizeof operatörünün bir tamsayý deðeri döndürdüðünü çýkarabiliriz - ancak bu dönüþ deðeri hangi tamsayý türüdür? 
Bir int mi? Bir short mu? Cevap, sizeof (ve bir boyut veya uzunluk deðeri döndüren birçok iþlev) deðerinin std::size_t türünde olduðudur. 
std::size_t, imzalý bir tamsayý türü olarak tanýmlanmýþtýr ve genellikle nesnelerin boyutunu veya uzunluðunu temsil etmek için kullanýlýr.

Ýlginç bir þekilde, sizeof operatörünü (std::size_t türünde bir deðer döndüren) std::size_t'in kendi boyutunu sormak için kullanabiliriz:

std::size_t, birkaç farklý baþlýkta tanýmlanmýþtýr. <cstddef>, diðer tanýmlanmýþ kimlik sayýsýný en az içerdiði için dahil etmek için en iyi 
seçenektir. Bir tamsayý sisteme baðlý olarak boyut deðiþtirebileceði gibi, std::size_t de boyut deðiþtirebilir. std::size_t, garantili olarak
iþaretsiz ve en az 16 bit olacak þekilde tanýmlanmýþtýr, ancak çoðu sistemde genellikle uygulamanýn adres geniþliðine eþdeðer olacaktýr.
Yani, 32-bit uygulamalar için std::size_t genellikle 32 bit iþaretsiz bir tamsayý olacaktýr ve 64-bit uygulama için std::size_t genellikle
64 bit iþaretsiz bir tamsayý olacaktýr.

sizeof, bir nesnenin boyutunu (bayt cinsinden) std::size_t türünde bir deðer kullanarak döndürebilmelidir. Bu nedenle, bir sistemde
oluþturulabilir olan en büyük nesnenin boyutu (bayt cinsinden), std::size_t'nin tutabileceði en büyük deðere eþittir. Eðer daha büyük bir 
nesne oluþturmak mümkün olsaydý, sizeof, std::size_t'nin aralýðýný aþacaðý için boyutunu döndüremezdi.

Bu nedenle, std::size_t türündeki bir nesnenin boyutu (bayt cinsinden), std::size_t türündeki bir nesnenin tutabileceði en büyük deðerden
daha büyükse, bu durum hatalý kabul edilir ve bir derleme hatasýna neden olur.

Örneðin, 4 baytlýk iþaretsiz bir tamsayýnýn aralýðý 0 ile 4.294.967.295 arasýndadýr. Varsayalým ki std::size_t'nin boyutu 4 bayt ise, 
o zaman std::size_t türündeki bir nesne, 0 ile 4.294.967.295 arasýnda bir tamsayý deðerini tutabilir. Bu, bu tür bir sistemde oluþturulabilen
en büyük nesnenin 4.294.967.295 bayt olduðu anlamýna gelir (ve bu nesnenin üzerinde sizeof çaðrýldýðýnda tam olarak 4.294.967.295 dönecektir).

Bir not olarak...

std::size_t'nin boyutu, bir nesnenin boyutuna sýký bir matematiksel üst sýnýr getirir. Uygulamada, oluþturulabilen en büyük nesne bu miktarýn
altýnda olabilir (belki de önemli ölçüde).

Bazý derleyiciler, en büyük oluþturulabilir nesneyi std::size_t'nin maksimum deðerinin yarýsýyla sýnýrlayabilir (bu konuda bir açýklama burada
bulunabilir). Diðer faktörler de rol oynayabilir, örneðin bilgisayarýnýzýn hangi miktarda ardýþýk belleðe sahip olduðu gibi            
*/

/*
BEST en iyi uygulama
En iyi uygulama

- Ýnteger'ýn boyutu önemli deðilse (örneðin, sayý her zaman 2 byte'lýk bir iþaretli integer'a sýðacaksa), `int` tercih edin. Örneðin, kullanýcýdan yaþlarýný girmesini istiyorsanýz veya 1'den 10'a kadar sayýyorsanýz, `int`'in 16 veya 32 bit olup olmadýðý önemli deðildir (sayýlar her iki durumda da sýðacaktýr). Bu, karþýlaþma ihtimalinizin çok yüksek olduðu durumlarýn çoðunu kapsayacaktýr.
- Bir miktarý depolamak için garantili bir aralýða ihtiyaç duyuluyorsa, `std::int#_t` tercih edin.
- Bit manipülasyonu yapýlýyorsa veya tanýmlý bir wrap-around davranýþý gerekiyorsa, `std::uint#_t` tercih edin.
- Mümkünse aþaðýdakilerden kaçýnýn:
  - `short` ve `long` integer'lar - bunun yerine sabit geniþlikli bir tip kullanýn.
  - Unsigned tipleri miktarlarý tutmak için kullanmayýn.
  - 8-bit sabit geniþlikli integer tipleri.
  - Fast ve least sabit geniþlikli tipler.
  - Herhangi bir derleyici özel sabit geniþlikli integer'ý - örneðin, Visual Studio `__int8`, `__int16`, vb. tanýmlar.
*/
// Scientific gösterimi geçtim. 
/* 
                                            4.8 Floating Point Number - Kayan noktalý sayýlar 


float fValue;          |                                                             4       
double dValue;         |-> Þeklinde tanýmlanan 3 türden oluþur minimum geniþlikleri  8       -> byte olabilir. 
long double ldValue;   |                                                             8 12 16    

Kayan noktalý sayýlarý kullanýrken virgülden sonra 0 bile olsa " . , " hangisi ise kullanmak lazým. Çünkü derleyici bunu bir tamsayý olarak görebilir. 
Varsayýlan olarak derleyicide kayan noktalý sayýlar double olarak tanýmlanýr o yüzden float bir sayý tanýmlanýrken sonuna "f" suffix i getirilir. 

Her zaman literallerinizin türünün, atanacaklarý veya baþlatýlacaklarý deðiþkenin türüyle eþleþtiðinden emin olun. Aksi takdirde gereksiz bir 
dönüþüm meydana gelebilir ve bu da olasý bir hassasiyet kaybýna neden olabilir.


Floating point range
--------------------
4 bytes                         	    ±1.18 x 10-38 to ±3.4 x 1038 and 0.0	    6-9 significant digits, typically 7
8 bytes	                                ±2.23 x 10-308 to ±1.80 x 10308 and 0.0	    15-18 significant digits, typically 16
80-bits (typically uses 12 or 16 bytes)	±3.36 x 10-4932 to ±1.18 x 104932 and 0.0	18-21 significant digits
16 bytes	                            ±3.36 x 10-4932 to ±1.18 x 104932 and 0.0	33-36 significant digits


80-bit kayan nokta tipi bir tür olarak tarihsel bir aykýrýlýktýr. Modern iþlemcilerde genellikle 12 veya 16 byte kullanýlarak uygulanýr 
(bu, iþlemcilerin iþlemesi için daha doðal bir boyuttur).

80-bit kayan nokta tipinin, 16-byte kayan nokta tipi ile ayný aralýða sahip olmasý biraz garip görünebilir. Bu, üs için ayrýlan bit 
sayýsýnýn ayný olmasýndan kaynaklanýr - ancak 16-byte sayý daha fazla anlamlý basamaklarý depolayabilir.

Float sayýlarýn hassasiyeti
---------------------------
Düþünün ki kesir 1/3. Bu sayýnýn ondalýk gösterimi 0.33333333333333... þeklinde, sonsuza kadar devam eden 3'lerle. Eðer bu sayýyý
bir kaðýda yazýyorsanýz, bir noktada kolunuz yorulacak ve yazmayý býrakacaksýnýz. Ve geriye kalan sayý, 0.3333333333...
(3'ler sonsuza kadar devam ediyor) ile yaklaþýk olarak olacaktýr, ancak tam olarak deðil.

Bir bilgisayarda sonsuz uzunluktaki bir sayýyý depolamak için sonsuz belleðe ihtiyaç duyulur, ancak genellikle sadece 4 veya 8 byte'a sahibiz.
Bu sýnýrlý bellek, kayan nokta sayýlarýnýn yalnýzca belli bir sayýda anlamlý basamak depolayabilmesi anlamýna gelir - ve herhangi ek anlamlý 
basamak kaybolur. Gerçekte depolanan sayý, istenen sayýya yakýn olacaktýr, ancak tam olarak deðil.

Bir kayan nokta sayýsýnýn hassasiyeti, bilgi kaybý olmadan temsil edebileceði anlamlý basamak sayýsýný belirler.

Kayan nokta sayýlarýný çýktý olarak verirken, std::cout'un varsayýlan hassasiyeti 6'dýr - yani, tüm kayan nokta deðiþkenlerini yalnýzca
6 basamaða kadar anlamlý kabul eder (float'ýn minimum hassasiyeti), bu nedenle sonrasýndaki her þeyi kesecektir.

Aþaðýdaki program, std::cout'un 6 basamaða kadar kestiðini göstermektedir:
    #include <iostream>
    int main()
    {
        std::cout << 9.87654321f << '\n';
        std::cout << 987.654321f << '\n';
        std::cout << 987654.321f << '\n';
        std::cout << 9876543.21f << '\n';
        std::cout << 0.0000987654321f << '\n';

        return 0;
    }
    Çýktý:
    9.87654
    987.654
    987654
    9.87654e+006
    9.87654e-005

Her birinin sadece 6 anlamlý basamaðý olduðuna dikkat edin.

Ayrýca, std::cout'un bazý durumlarda sayýlarý bilimsel nota çevirmeye geçeceðini unutmayýn. Derleyiciye baðlý olarak, üs genellikle bir 
minimum basamak sayýsýna kadar doldurulur. Endiþelenmeyin, 9.87654e+006, 9.87654e6 ile aynýdýr, sadece bazý dolgu 0'larý vardýr. Üsün en 
az kaç basamaklý gösterileceði derleyiciye özgüdür (Visual Studio 3 kullanýr, diðerleri C99 standardýna göre 2 kullanýr).

Bir kayan nokta deðiþkeninin sahip olduðu kesinlik sayýsý, boyuta (float'lar double'lardan daha az kesinliðe sahiptir) ve depolanan belirli
deðere baðlýdýr (bazý deðerler diðerlerinden daha fazla kesinliðe sahiptir). Float deðerlerinin 6 ila 9 arasýnda kesin basamaðý vardýr, 
çoðu float deðeri en az 7 anlamlý basamaða sahiptir. Double deðerlerinin 15 ila 18 arasýnda kesin basamaðý vardýr, çoðu double deðeri en az
16 anlamlý basamaða sahiptir. Long double'ýn 15, 18 veya 33 anlamlý basamaða sahip olma minimum kesinliði, kaç byte yer kapladýðýna baðlýdýr.

std::setprecision() adlý bir çýkýþ düzenleyici iþlevini kullanarak std::cout'un gösterdiði varsayýlan kesinliði geçersiz kýlabiliriz.
Çýkýþ düzenleyicileri, verilerin nasýl çýktýlandýðýný deðiþtirir ve iomanip baþlýk dosyasýnda tanýmlanýr.

Çýkýþ manipülatörleri (ve giriþ manipülatörleri) yapýþkandýr; yani onlarý ayarlarsanýz ayarlý kalýrlar.
Burada dikkat etmen gereken diðer bir durum floatlar 7 basamaða kadar hassastýrlar sonrasýnda 8.bir basamak daha saklamak istediðimizde bunu 
düzgünce saklayamaz ve bu durum bize hatalý sonuçlar verebilir. Buna rounding error deriz yani yuvarlama hatasý. 

*** Yani best : Yer önemli deðilse, genellikle float'taki kesinlik eksikliði nedeniyle doðruluk kayýplarýna yol açabileceðinden dolayý 
double'ý tercih edin.

Yuvarlama hatalarý Float sayýlarýn karþýlaþtýrmasýný biraz zorlaþtýrýr
----------------------------------------------------------------------
Kayan noktalý sayýlarla çalýþmak, verilerin nasýl depolandýðý (ikili sistem) ile onlarýn nasýl düþündüðümüz (onlu sistem) arasýndaki açýk 
olmayan farklar nedeniyle zordur. Örneðin, kesir 1/10'u ele alalým. Onlu sistemde bunu kolayca 0.1 olarak temsil edebiliriz ve 0.1'i 1 
anlamlý hane içeren kolayca temsil edilebilen bir sayý olarak düþünmeye alýþýðýz. Ancak ikili sistemde ondalýk deðer 0.1, sonsuz diziyi
temsil eden þu þekildedir: 0.00011001100110011... Bu nedenle, bir kayan noktalý sayýya 0.1'i atadýðýmýzda, hassasiyet sorunlarýyla karþýlaþýrýz.

Yani mesela 1/10 aslýnda 0.1 olarak düþünürüz ama sonsuza dek gidiyor binary yazýmda burada float sayý olarak kaydedildiðinde ise yuvarlama hatasý
ile 0.1 0.1000001 olarak kaydediliyor olabilir. 
slýnda tam olarak 0.1 olmadýðýný görüyoruz! Bu, double'ýn sýnýrlý belleði nedeniyle yaklaþýmý budanmak zorunda kaldýðý anlamýna gelir. 
Sonuç, 16 anlamlý haneye kadar kesin bir sayýdýr (ki bu double türü tarafýndan garanti edilir), ancak sayý tam olarak 0.1 deðildir. 
Yuvarlama hatalarý, budamanýn nerede gerçekleþtiðine baðlý olarak bir sayýyý biraz daha küçük veya biraz daha büyük yapabilir.

Mevzu
-----
Yuvarlama hatalarý, bir sayýnýn tam olarak depolanamadýðý durumlarda ortaya çýkar. Bu, basit sayýlarla bile, örneðin 0.1 ile gerçekleþebilir.
Bu nedenle, yuvarlama hatalarý gerçekleþebilir ve genellikle gerçekleþir. Yuvarlama hatalarý istisna deðildir, kuraldýr. Asla kayan nokta
sayýlarýnýzýn tam olduðunu varsaymayýn.

Bu kuralýn bir sonucu olarak: finansal veya para birimi verileri için kayan nokta sayýlarýný kullanýrken dikkatli olun.

Kayar nokta sayýlarýnýn iki özel kategorisi vardýr. Ýlk olarak, "Inf" (sonsuz) sonsuzluðu temsil eder. Inf hem pozitif hem de negatif olabilir. 
Ýkincisi, "NaN", "Not a Number" (Sayý Deðil) anlamýna gelir. NaN'ýn birkaç farklý türü vardýr (ki burada tartýþmayacaðýz). NaN ve Inf, derleyici
kayan nokta sayýlarý için belirli bir biçimi (IEEE 754) kullanýyorsa yalnýzca mevcuttur. Baþka bir biçem kullanýlýyorsa, aþaðýdaki kod tanýmsýz
davranýþ üretir.
******Derleyici desteklese bile 0 a bölünmeden kaçýnmak en iyi davranýþtýr. ****
*/

// Temel olarak hatýrlamamýz gereken 2 þey vardýr. 
/*
Özetle, kayan nokta sayýlarý hakkýnda hatýrlamanýz gereken iki þey:

Kayan nokta sayýlarý, çok büyük veya çok küçük sayýlarý, bunlar arasýnda kesirli bileþenler bulunanlarý saklamak için kullanýþlýdýr.
Kayan nokta sayýlarý genellikle küçük yuvarlama hatalarýna sahiptir, hatta sayý daha az önemli basamaða sahipse. Çoðu zaman bunlar 
çok küçük olduklarý ve sayýlar çýktý için kýrpýldýðý için fark edilmez. Ancak, kayan nokta sayýlarý üzerinde matematiksel iþlemler
gerçekleþtirmek, yuvarlama hatalarýný daha büyük hale getirecektir.*/
/*
                                                            CHARS
CHAR veri tipi karakter verilerini tutmak için üretilmiþtir. karakter dediðimiz þey bir harf iþaret sembol veya boþluk olabilir. char veri tipi bir 
integral veri tipi olarak kabul edilir. Yani temel deðer bir tam sayý olarak depolanýr ayný boolean deðerleri gibi ( false = 0 gibi )
charlarda saklanan deðerler ASCII karakteri olarak yorumlanýr. 
ascii nin ne olduðunu biliyoz geçtim  

Baþlatma þekli -> char ch2{'a'} // tercih edilen baþlatma þekli budur. 
               -> char ch2{97} // ayný þekilde 'a' karakterine karþýlýk gelir ama tercih edilen bir baþlatma deðildir. 
                                Burada dikkat edilmesi gereken ise normal sayý ile karakter olan sayý karýþtýrýlmamalý '5' ile 5 ayný deðildir. 
yazdýrma þeklide ayný zaten cout a ver yazdýrsýn :d 

input olarak alýrken std::cin>> i kullanabiliriz burada bilmemiz gereken tek þey 'cin' bir den çok girdi alabiliyor mesela kemalettin ismini 
cin e girdi olarak verebilirim ama char veri tipi sadece 1 karakter alýyor yaný k harfini alacak ve geriye kalacak olan 'emalettin' buffer da 
beklemeye devam edecektir yeni bir cin ile onu baþka karakter veya veriye aktararak çekebiliriz. Bu mevzunun dikkatinde ol. 

Char size range and default sign
--------------------------------
char, C++ tarafýndan her zaman 1 byte boyutunda olacak þekilde tanýmlanmýþtýr. Varsayýlan olarak bir char iþaretlenebilir veya iþaretsiz 
olabilir (ancak genellikle iþaretli olur). Eðer char'larý ASCII karakterlerini tutmak için kullanýyorsanýz bir iþaret belirtmenize gerek 
yoktur (çünkü hem iþaretli hem de iþaretsiz char'lar 0 ile 127 arasýndaki deðerleri tutabilir).

Eðer küçük tamsayýlarý tutmak için (bunu yalnýzca özellikle yer tasarrufu için optimize etmiyorsanýz yapmalýsýnýz) bir char kullanýyorsanýz,
her zaman iþaretli mi yoksa iþaretsiz mi olduðunu belirtmelisiniz. Bir iþaretli char, -128 ile 127 arasýnda bir sayýyý tutabilir. Bir 
iþaretsiz char, 0 ile 255 arasýnda bir sayýyý tutabilir.

kaçýþ dizilerini atladým. 

*** çift týrnak ve tek týrnak : Baðýmsýz karakterleri tek týrnak içine alýn (örneðin, 't' veya '\n', "t" veya "\n" deðil). Bu, derleyicinin
                                daha etkili bir þekilde optimizasyon yapmasýna yardýmcý olur.

Çoklu
Geriye dönük uyumluluk nedeniyle, birçok C++ derleyicisi çoklu karakterli sabitleri destekler. Bu, birden çok karakter içeren char sabitleridir 
(örneðin '56'). Destekleniyorsa, bunlar bir uygulama tanýmlý deðere sahiptir (bu, derleyiciye baðlý olarak deðiþir). Çünkü bunlar C++ standardýnýn
bir parçasý deðildir ve deðerleri kesin olarak tanýmlanmamýþtýr, çoklu karakterli sabitlerden kaçýnýlmalýdýr.
( Sanýrým multicharacter dediði tek týrnak içinde olanlara deniyor.)

wchar_t tipi neredeyse tüm durumlarda kaçýnýlmasý gereken bir tiptir (Windows API ile etkileþimde bulunulmasý haricinde). 
Boyutu uygulamaya özgüdür ve güvenilir deðildir. Genellikle terkedilmiþtir.

"Deprecated" terimi, "hâlâ destekleniyor ancak daha iyi bir þeyle deðiþtirildiði veya artýk güvenli kabul edilmediði için kullanýmý önerilmeyen"
anlamýna gelir.
C++11'e char16_t ve char32_t, 16 bitlik ve 32 bitlik Unicode karakterlere açýk destek saðlamak üzere eklenmiþtir. char8_t, C++20'de eklenmiþtir.
Bu char türleri sýrasýyla std::uint_least16_t, std::uint_least32_t ve std::uint_least8_t ile ayný boyuta sahiptir (ancak farklý türlerdir).
Teorik olarak, char#_t türleri # tarafýndan belirtilen bit sayýsýndan daha büyük olabilir (ancak esoterik bir mimari üzerinde çalýþmýyorsanýz
ayný olmalýdýr).

char8_t, char16_t veya char32_t'yi yalnýzca programýnýzý Unicode uyumlu hale getirmeyi planlýyorsanýz kullanmanýz gerekir. Unicode ve
yerelleþtirme genellikle bu öðreticilerin kapsamýnýn dýþýnda olduðu için daha fazla açýklama yapmayacaðýz.

Bu arada, karakterlerle (ve dizelerle) çalýþýrken yalnýzca ASCII karakterlerini kullanmalýsýnýz. Diðer karakter setlerinden karakterler kullanmak,
karakterlerinizin yanlýþ görüntülenmesine neden olabilir.
*/
/*                                                      TYPE DÖNÜÞÜMÜ ve static_cast

Çoðu durumda, C++, bir temel türden diðer bir temel türe deðerleri dönüþtürmemize izin verir. Bir deðeri bir türden baþka bir türe dönüþtürme 
sürecine "tür dönüþümü" denir.

Derleyicinin bizden açýkça istemeden tür dönüþümü gerçekleþtirdiðinde, buna "örtük tür dönüþümü" diyoruz. Örnek olarak bir fonksiyon 
argüman olarka double türü istediði zaman biz ona integer verirsek temel veri tiplerinden olduðu için compiler burada hatayý farkeder ve 
otomatik olarak tür dönüþümü yapar buna implicit conversion yani örtük, bilinçsiz tür dönüþümü deriz. 

Tür dönüþümü, adýndan da anlaþýlacaðý gibi, dönüþtürülen deðerin deðerini veya türünü gerçekten deðiþtirmez. Bunun yerine, dönüþtürülecek deðer
giriþ olarak kullanýlýr ve dönüþüm, hedef türde yeni bir deðer oluþturur (doðrudan baþlatma aracýlýðýyla).

Yukarýdaki örnekte dönüþüm, deðiþken y'nin türünü int'ten double'a deðiþtirmez. Bunun yerine, dönüþüm, y'nin deðerini (5) giriþ olarak kullanarak
yeni bir double deðeri (5.0) oluþturur. Bu double deðeri daha sonra print fonksiyonuna iletilir.
yani; 
Tür dönüþümü, farklý bir türdeki bir deðerin deðerinden hedef türde yeni bir deðer oluþturmak için doðrudan baþlatmayý kullanýr.

Bazý tür dönüþümleri her zaman güvenlidir ve deðeri deðiþtirmez (örneðin, int'ten double'a dönüþüm), ancak bazýlarý deðerin dönüþüm sýrasýnda
deðiþmesine neden olabilir (örneðin, double'dan int'e dönüþüm). Güvensiz, açýkça istenmeyen tür dönüþümleri genellikle derleyici uyarýsý üretecek
veya (parantez baþlatma durumunda) bir hata ortaya çýkaracaktýr.

Parantez baþlatma tercih edilen baþlatma biçimi olarak kabul edilir, çünkü bu baþlatma biçimi, deðerin dönüþüm sýrasýnda kaybolmasýna neden
olabilecek bir baþlatýcý ile deðiþkeni baþlatmaya çalýþmadýðýmýzý saðlar.

static_cast ile explicit type conversion
----------------------------------------
C++, explicit (açýk) tür dönüþümü olarak adlandýrýlan bir ikinci tür dönüþümü destekler. Explicit tür dönüþümü, (programcý olarak) deðeri bir
türden baþka bir türe açýkça dönüþtürmek istediðimizi ve bu dönüþümün sonucundan tam sorumluluk üstlendiðimizi (yani dönüþümün deðer kaybýna
neden olursa bu bizim hatamýzdýr) belirtmemize olanak tanýr.

Açýkça bir tür dönüþümü yapmak için çoðu durumda static_cast operatörünü kullanýrýz. Statik dönüþümün sözdizimi biraz garip görünüyor:

static_cast<new_type>(expression)

static_cast, bir ifadenin deðerini girdi olarak alýr ve bu deðeri new_type tarafýndan belirtilen türe dönüþtürülmüþ olarak geri döndürür
(örneðin int, bool, char, double).

Herhangi bir C++ sözdizimi (ön iþlemci hariç) gördüðünüzde ve bu sözdizimi açýlmýþ parantezleri (<> iþareti) içeriyorsa, açýlmýþ parantezler
arasýndaki þey muhtemelen bir tür olacaktýr. Bu genellikle C++'ýn parametreli bir tür gerektiren kodlarla baþa çýkmasýnýn bir yoludur.

char deðiþkenlerinde Eðer karakterin deðil de tamsayý deðerini yazdýrmak istiyorsak, bunu bir char'dan bir int'e dönüþtürmek için static_cast 
kullanarak yapabiliriz.
örnek: 
        #include <iostream>

        int main()
        {
            char ch{ 97 }; // 97 is ASCII code for 'a'
            std::cout << ch << " has value " << static_cast<int>(ch) << '\n'; // print value of variable ch as an int

            return 0;
        }
Deðeri dönüþtürülecek ifade static_cast'a argüman olarak verildiðinde, bu ifade deðerlendirilir. Bir deðiþkeni geçtiðimizde, bu deðiþkenin 
deðeri üretilir ve bu deðer daha sonra yeni türüne dönüþtürülür. Deðiþkenin kendisi, deðerini yeni bir türe dönüþtürmekten etkilenmez. 
Yukarýdaki örnekte, ch adlý deðiþken hala bir char'dýr ve deðeri, deðerini int'e dönüþtürdükten sonra bile ayný kalýr.


Bir iþaretsiz sayýyý iþaretli bir sayýya dönüþtürmek için de static_cast operatörünü kullanabilirsiniz:

        #include <iostream>

        int main()
        {
            unsigned int u { 5 };
            int s { static_cast<int>(u) }; // return value of variable u as an int

            std::cout << s << '\n';
            return 0;
        }

static_cast operatörü herhangi bir aralýk kontrolü yapmaz, bu nedenle bir deðeri, o deðeri içermeyen bir tür için dönüþtürürseniz tanýmsýz 
davranýþ oluþur. Bu nedenle, yukarýda yapýlan iþaretsiz int'ten iþaretli int'e dönüþümü, iþaretsiz int'in deðeri, iþaretli int'in tutabileceði
maksimum deðerden büyükse öngörülemeyen sonuçlar verecektir.

Buna dikkat et iþte **** Static_cast operatörü, dönüþtürülen deðer yeni türün aralýðýna uymuyorsa tanýmsýz davranýþ üretecektir.

std::int8_t ve std::uint8_t'nin, ayný zamanda ilgili hýzlý ve en küçük sabit geniþlikli türlerle birlikte (fast ve least fixed-width types)
genellikle signed char ve unsigned char türleriyle ayný þekilde tanýmlandýðýný ve iþlendiðini belirtildiði gibi, chars türleri gibi davrandýðýný
göstermiþtik. Þimdi bu durumun neden sorunlu olabileceðini gösterebiliriz:

        #include <cstdint>
        #include <iostream>

        int main()
        {
            std::int8_t myInt{65};      // initialize myInt with value 65
            std::cout << myInt << '\n'; // you're probably expecting this to print 65

            return 0;
        }



Çünkü std::int8_t kendisini bir int olarak tanýmlar, yukarýdaki programýn integral deðeri 65'i yazdýracaðýný düþünebilirsiniz.
Ancak, çoðu sistemde bu program, myInt'i bir signed char olarak iþleyerek A'yý yazdýracaktýr. Ancak bu garantilenmiþ deðildir 
(bazý sistemlerde aslýnda 65'i yazdýrabilir).

Bir std::int8_t veya std::uint8_t nesnesinin bir tam sayý olarak iþlenmesini saðlamak istiyorsanýz, deðeri static_cast kullanarak 
bir tam sayýya dönüþtürebilirsiniz:

diðer 8 bitlik integer tiplerinde de ayný durum olur ( fast ve least türler dahil )















*/