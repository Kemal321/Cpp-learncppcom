#include <iostream>

int main()
{
    return 0;
}
/*

13.1 — Program Tanýmlý (Kullanýcý Tanýmlý) Türlerin Giriþi 
----------------------------------------------------------
Temel türler, C++ dilinin çekirdek parçasý olarak tanýmlandýðýndan, hemen kullanýlabilirler. Örneðin, bir deðiþkeni int veya
double türünde tanýmlamak istiyorsak, bunu hemen yapabiliriz:

                    int x; // 'int' temel türünde deðiþken tanýmla
                    double d; // 'double' temel türünde deðiþken tanýmla

Bu, temel türlerin basit geniþlemeleri olan bileþik türler (fonksiyonlar, iþaretçiler, referanslar ve diziler dahil) için de 
geçerlidir:

                    void fcn(int) {}; // 'void()(int)' türünde bir fonksiyon tanýmla
                    int* ptr; // 'int'e iþaret eden' bileþik türünde deðiþken tanýmla
                    int& ref { x }; // 'int'e referans' bileþik türünde deðiþken tanýmla (x ile baþlatýldý)
                    int arr[5]; // 5 tam sayýdan oluþan bir dizi tanýmla, türü 'int[5]' (bunu gelecekteki bir bölümde ele alacaðýz)

Bu, C++ dilinin bu türler için tür adlarýný (ve sembollerini) ne anlama geldiðini zaten bildiði için çalýþýr - herhangi bir taným
saðlamamýz veya içe aktarmamýz gerekmez.

Ancak, mevcut bir tür için yeni bir ad tanýmlamamýza izin veren bir tür takma adýnýn (10.7 dersinde tanýtýlan Typedefs ve tür
takma adlarý) durumunu düþünün. Bir tür takma adý, programa yeni bir tanýmlayýcý eklediði için, bir tür takma adý kullanýlmadan
önce tanýmlanmalýdýr:

                    #include <iostream>

                    using length = int; // 'length' tanýmlayýcýsý olan bir tür takma adý tanýmla

                    int main()
                    {
                        length x { 5 }; // 'length'i burada kullanabiliriz çünkü onu yukarýda tanýmladýk
                        std::cout << x << '\n';

                        return 0;
                    }

Eðer length tanýmýný atlatýrsak, derleyici bir length’in ne olduðunu bilmez ve bu türü kullanarak bir deðiþken tanýmlamayý
denediðimizde þikayet eder. Length için taným bir nesne oluþturmaz – sadece derleyiciye bir length’in ne olduðunu söyler, böylece
daha sonra kullanýlabilir.

Kullanýcý Tanýmlý / Program Tanýmlý Türler Nedir?
-------------------------------------------------
Önceki bölümün giriþinde (12.1 — Bileþik Veri Türlerine Giriþ), bir kesiri, kavramsal olarak birbirine baðlý olan bir pay ve payda
ile saklama isteðini tanýttýk. Bu derste, bir kesirin pay ve paydasýný baðýmsýz olarak saklamak için iki ayrý tam sayý kullanmanýn
zorluklarýný tartýþtýk.

Eðer C++'ta yerleþik bir kesir türü olsaydý, bu mükemmel olurdu – ama yok. Ve C++'ta, birinin ihtiyaç duyabileceði her þeyi 
önceden tahmin etmek (hele bunlarý uygulamak ve test etmek) mümkün olmadýðý için, potansiyel olarak yararlý yüzlerce diðer tür
de dahil deðil.

Bunun yerine, C++ bu tür sorunlarý farklý bir þekilde çözer: programlarýmýzda kullanmak üzere tamamen yeni, özel türler
oluþturmamýza izin vererek! Bu tür türler genellikle kullanýcý tanýmlý türler olarak adlandýrýlýr (ancak program tanýmlý türler
teriminin daha iyi olduðunu düþünüyoruz – bu dersin ilerleyen kýsmýnda farký tartýþacaðýz). C++'ta bunu saðlayan iki kategori
bileþik tür vardýr: numaralandýrýlmýþ türler (kapsamsýz ve kapsamlý numaralandýrmalar dahil (unscoped and scoped enumerations) ve
sýnýf türleri (yapýlar(structs),sýnýflar (classes) ve birlikler (unions) dahil).

                    // Derleyicinin bir Fraction'ýn ne olduðunu anlamasý için Fraction adýnda bir program tanýmlý tür tanýmlayýn
                    // (Bir struct'ýn ne olduðunu ve nasýl kullanýlacaðýný bu bölümün ilerleyen kýsmýnda açýklayacaðýz)
                    // Bu sadece bir Fraction türünün neye benzediðini tanýmlar, bir tane oluþturmaz
                    struct Fraction
                    {
	                    int pay {};
	                    int payda {};
                    };

                    // Þimdi Fraction türümüzü kullanabiliriz
                    int main()
                    {
	                    Fraction f{ 3, 4 }; // Bu aslýnda f adýnda bir Fraction nesnesi oluþturur

	                    return 0;
                    }

Bu örnekte, yeni bir program tanýmlý tür olan Fraction’ý tanýmlamak için struct anahtar kelimesini kullanýyoruz (global kapsamda,
böylece dosyanýn geri kalanýnda her yerde kullanýlabilir). Bu herhangi bir bellek ayýrmaz – sadece derleyiciye bir Fraction’ýn
neye benzediðini söyler, böylece daha sonra Fraction türünde nesneler ayýrabiliriz. Daha sonra, main() içinde, f adýnda bir
Fraction türünde deðiþken oluþturuyoruz (ve baþlatýyoruz).

Program tanýmlý tür tanýmlarý her zaman noktalý virgülle biter. Tür tanýmýnýn sonunda noktalý virgülü eklememek yaygýn bir
programcý hatasýdýr ve hata ayýklamasý zor olabilir çünkü derleyici genellikle tür tanýmýndan sonraki satýrda hata verir. Örneðin,
yukarýdaki örnekte Fraction tanýmýnýn sonundaki noktalý virgülü çýkarýrsanýz (8. satýr), derleyici muhtemelen main() tanýmý
hakkýnda (11. satýr) þikayet eder.

*** Uyarý -> Tür tanýmlarýnýzý bir noktalý virgülle bitirmeyi unutmayýn, aksi takdirde derleyici genellikle bir sonraki kod
             satýrýnda hata verir.

Program Tanýmlý Türlerin Adlandýrýlmasý
---------------------------------------
Geleneksel olarak, program tanýmlý türler büyük harfle baþlar ve bir sonek kullanmazlar (ör. Fraction, fraction, fraction_t veya 
Fraction_t deðil).

*** BEST -> Program tanýmlý türlerinizi büyük harfle baþlatýn ve bir sonek kullanmayýn.

Yeni programcýlar bazen aþaðýdaki gibi deðiþken tanýmlarýný tür adý ve deðiþken adý arasýndaki benzerlik nedeniyle kafa
karýþtýrýcý bulabilirler:

                    Fraction fraction {}; // Fraction türünde fraction adýnda bir deðiþken oluþturur

Bu, diðer herhangi bir deðiþken tanýmýndan farklý deðildir: önce tür (Fraction) gelir (ve Fraction büyük harfle baþladýðý için, 
bunun bir program tanýmlý tür olduðunu biliyoruz), ardýndan deðiþken adý (fraction) ve ardýndan isteðe baðlý bir baþlatýcý. 
C++ büyük/küçük harfe duyarlý olduðu için burada bir adlandýrma çakýþmasý yok!

Çok Dosyalý Bir Program Boyunca Program Tanýmlý Türlerin Kullanýlmasý
---------------------------------------------------------------------
Bir program tanýmlý türü kullanan her kod dosyasý, türün kullanýldýðý yerden önce tam tür tanýmýný görmelidir. Ýleri bildirim
yeterli deðildir. Bu, derleyicinin o türden nesneler için ne kadar bellek ayýrmasý gerektiðini bilmesi gereklidir.

Tür tanýmlarýný ihtiyaç duyan kod dosyalarýna yaymak için, program tanýmlý türler genellikle baþlýk dosyalarýnda tanýmlanýr ve 
ardýndan o tür tanýmýný gerektiren her kod dosyasýna #include edilir. Bu baþlýk dosyalarý genellikle program tanýmlý türle ayný
adý alýr (ör. Fraction adýnda bir program tanýmlý tür, Fraction.h’de tanýmlanýr)

En Ýyi Uygulama

Yalnýzca bir kod dosyasýnda kullanýlan bir program tanýmlý tür, mümkün olduðunca ilk kullaným noktasýna yakýn bir yerde o kod 
dosyasýnda tanýmlanmalýdýr.

Birden çok kod dosyasýnda kullanýlan bir program tanýmlý tür, program tanýmlý türle ayný adý taþýyan bir baþlýk dosyasýnda 
tanýmlanmalý ve ardýndan her kod dosyasýna gerektiði gibi #include edilmelidir.

Ýþte Fraction türümüzü bir baþlýk dosyasýna (Fraction.h adýnda) taþýyýp birden çok kod dosyasýna dahil edilebilecek þekilde neye 
benzeyeceði hakkýnda bir örnek:

Fraction.h:
                    #ifndef FRACTION_H
                    #define FRACTION_H

                    // Fraction adýnda yeni bir tür tanýmlayýn
                    // Bu sadece bir Fraction'ýn neye benzediðini tanýmlar, bir tane oluþturmaz
                    // Bu bir tam tanýmdýr, ileri bildirim deðil
                    struct Fraction
                    {
                        int pay {};
                        int payda {};
                    };

                    #endif

Fraction.cpp:
                    #include "Fraction.h" // Bu kod dosyasýna Fraction tanýmýmýzý dahil edin

                    // Þimdi Fraction türümüzü kullanabiliriz
                    int main()
                    {
                        Fraction f{ 3, 4 }; // Bu aslýnda f adýnda bir Fraction nesnesi oluþturur

                        return 0;
                    }

Tür tanýmlarý, bir tanýmlama kuralý olan (ODR) kýsmen muaf tutulmuþtur

2.7 dersinde -- Ýleri Bildirimler ve Tanýmlar, bir tanýmlama kuralýnýn her fonksiyon ve global deðiþkenin program baþýna yalnýzca
bir tanýmýna sahip olmasýný gerektirdiðini tartýþtýk. Tanýmý içermeyen bir dosyada belirli bir fonksiyonu veya global deðiþkeni 
kullanmak için, bir ileri bildirime (genellikle bir baþlýk dosyasý aracýlýðýyla yaydýðýmýz) ihtiyacýmýz var. Bu, fonksiyonlar ve
non-constexpr deðiþkenler söz konusu olduðunda derleyiciyi tatmin etmek için bildirimlerin yeterli olduðu için çalýþýr ve 
baðlayýcý daha sonra her þeyi baðlar.

Ancak, türler için ileri bildirimleri benzer bir þekilde kullanmak iþe yaramaz, çünkü derleyici genellikle belirli bir türü
kullanmak için tam tanýmý görmeye ihtiyaç duyar. Her kod dosyasýna tam tür tanýmýný yayabilmeliyiz.

Bunu saðlamak için, türler bir tanýmlama kuralýndan ( ODR ) kýsmen muaf tutulur: belirli bir tür, birden çok kod dosyasýnda 
tanýmlanabilir. Bu yeteneði zaten kullanmýþ olabilirsiniz (muhtemelen farkýnda olmadan): programýnýzda <iostream> 'u içeren iki
kod dosyasý varsa, tüm giriþ/çýkýþ tür tanýmlarýný her iki dosyaya da içe aktarýyorsunuz.

Bilmeye deðer iki uyarý var.
* - Ýlk olarak, hala her kod dosyasý baþýna yalnýzca bir tür tanýmýna sahip olabilirsiniz (bu genellikle bir sorun olmaz çünkü 
    baþlýk korumalarý bunu önler). 
* - Ýkincisi, belirli bir tür için tüm tür tanýmlarý ayný olmalýdýr, aksi takdirde tanýmsýz davranýþ sonucu olur.( inline gibi )

Terimler: kullanýcý tanýmlý türler vs program tanýmlý türler
------------------------------------------------------------
"Kullanýcý tanýmlý tür" terimi bazen gündelik konuþmalarda ortaya çýkar ve C++ dil standardýnda da belirtilir (ancak tanýmlanmaz).
Gündelik konuþmalarda, terim genellikle "kendi programlarýnýzda tanýmlanan bir tür" anlamýna gelir (yukarýdaki Fraction tür örneði
gibi).

C++ dil standardý, "kullanýcý tanýmlý tür" terimini geleneksel olmayan bir þekilde kullanýr. Dil standardýnda, bir "kullanýcý 
tanýmlý tür", sizin, standart kütüphanenin veya uygulamanýn (ör. dil geniþlemelerini desteklemek için derleyici tarafýndan 
tanýmlanan türler) tanýmladýðý herhangi bir sýnýf türü veya numaralandýrýlmýþ türdür. Belki de karþý sezgisel olarak, bu,
std::string'in (standart kütüphanede tanýmlanan bir sýnýf türü) bir kullanýcý tanýmlý tür olarak kabul edildiði anlamýna gelir!

Ek ayrým saðlamak için, C++20 dil standardý, standart kütüphane, uygulama veya çekirdek dilin bir parçasý olarak tanýmlanmayan
sýnýf türlerini ve numaralandýrýlmýþ türleri ifade etmek için "program tanýmlý tür" terimini tanýmlar. Diðer bir deyiþle,
"program tanýmlý türler" yalnýzca bizim (veya bir üçüncü taraf kütüphanesi) tarafýndan tanýmlanan sýnýf türlerini ve enum 
türlerini içerir.

Sonuç olarak, yalnýzca kendi programlarýmýzda tanýmladýðýmýz sýnýf türleri ve enum türleri hakkýnda konuþurken, "program tanýmlý"
terimini tercih ederiz, çünkü daha kesin bir tanýmý vardýr.

Tür                Anlam                                                                             Örnekler
----------------------------------------------------------------------------------------------------------------------------------
Temel              Çekirdek C++ diline yerleþik bir tür                                          int, std::nullptr_t
Bileþik            Temel türlerden oluþturulan bir tür                                   int&, double*, std::string, Fraction
Kullanýcý Tanýmlý  Bir sýnýf türü veya numaralandýrýlmýþ tür                                    std::string, Fraction
                   (Standart kütüphanede veya uygulamada tanýmlananlarý içerir)
                   (Gündelik kullanýmda, genellikle program tanýmlý türler anlamýna gelir)    
Program Tanýmlý    Bir sýnýf türü veya numaralandýrýlmýþ tür
                   (Standart kütüphane veya uygulamada tanýmlananlarý hariç tutar)                    Fraction
----------------------------------------------------------------------------------------------------------------------------------

13.2 Kapsamsýz Numaralandýrýlmýþ türler ( Unscoped enumerations )
-----------------------------------------------------------------
C++ birçok kullanýþlý temel ve bileþik veri türü içerir. Ancak bu türler, yapmak istediðimiz þeyler için her zaman yeterli
olmayabilir. Örneðin, bir elmanýn kýrmýzý, sarý veya yeþil olup olmadýðýný veya bir gömleðin rengini (önceden belirlenmiþ bir
renk listesinden) takip etmesi gereken bir program yazýyorsunuz diyelim. Eðer sadece temel türler mevcut olsaydý, bunu nasýl
yapardýnýz?

Rengi bir tam sayý deðeri olarak saklayabilir, bazý türden bir içsel eþlemeyi kullanabilirsiniz (0 = kýrmýzý, 1 = yeþil, 2 = mavi):
                    int main()
                    {
                        int elmaRengi{ 0 }; // elma kýrmýzý
                        int gomlekRengi{ 1 }; // gömlek yeþil

                        return 0;
                    }

Ama bu hiç de sezgisel deðil ve sihirli sayýlarýn neden kötü olduðunu zaten tartýþtýk. Sembolik sabitleri kullanarak sihirli 
sayýlardan kurtulabiliriz:

                    constexpr int kirmizi{ 0 };
                    constexpr int yesil{ 1 };
                    constexpr int mavi{ 2 };

                    int main()
                    {
                        int elmaRengi{ kirmizi };
                        int gomlekRengi{ yesil };

                        return 0;
                    }

Bu, okuma için biraz daha iyidir, ancak programcý hala elmaRengi ve gomlekRengi’nin (int türünde olan) renk sembolik sabitlerinden
birini tutmasý gerektiðini çýkarmak zorundadýr (bu sabitler muhtemelen baþka bir yerde, muhtemelen ayrý bir dosyada tanýmlanmýþtýr)
Bu programý biraz daha açýk hale getirmek için bir tür takma adý kullanabiliriz:

using Renk = int; // Renk adýnda bir tür takma adý tanýmla

// Aþaðýdaki renk deðerleri bir Renk için kullanýlmalýdýr
constexpr Renk kirmizi{ 0 };
constexpr Renk yesil{ 1 };
constexpr Renk mavi{ 2 };

int main()
{
    Renk elmaRengi{ kirmizi };
    Renk gomlekRengi{ yesil };

    return 0;
}

Daha yaklaþýyoruz. Bu kodu okuyan biri hala bu renk sembolik sabitlerinin Renk türündeki deðiþkenlerle kullanýlmasý gerektiðini
anlamalý, ancak en azýndan türün artýk benzersiz bir adý var, böylece Renk arayan biri iliþkili sembolik sabitler kümesini,
bulabilir.

Ancak, Renk sadece bir int için bir takma ad olduðu için, bu renk sembolik sabitlerinin uygun kullanýmýný zorlayan hiçbir þey yok.
Hala þöyle bir þey yapabiliriz:

Renk gozRengi{ 8 }; // sözdizimsel olarak geçerli, anlamsal olarak anlamsýz

Ayrýca, bu deðiþkenlerin herhangi birini hata ayýklayýcýmýzda hata ayýklarsak, yalnýzca rengin tam sayý deðerini (ör. 0) görürüz,
sembolik anlamýný (kýrmýzý) deðil, bu da programýmýzýn doðru olup olmadýðýný anlamayý zorlaþtýrabilir.

Neyse ki, daha iyisini yapabiliriz.

Ýlham kaynaðý olarak, bool türünü düþünün. Bool’u özellikle ilginç kýlan þey, yalnýzca iki tanýmlý deðeri olmasýdýr: true ve false.
True veya false’u doðrudan (literaller olarak) kullanabiliriz, ya da bir bool nesnesi oluþturabilir ve onun bu deðerlerden birini
tutmasýný saðlayabiliriz. Ayrýca, derleyici bool’u diðer türlerden ayýrt edebilir. Bu, fonksiyonlarý aþýrý yükleyebileceðimiz ve
bu fonksiyonlarýn bir bool deðeri geçirildiðinde nasýl davranacaðýný özelleþtirebileceðimiz anlamýna gelir.

Kendi özel türlerimizi tanýmlama yeteneðimiz olsaydý, bu türle iliþkilendirilmiþ adlandýrýlmýþ deðerler kümesini tanýmlayabilirdik,
o zaman yukarýdaki zorluðu zarif bir þekilde çözmek için mükemmel bir aracýmýz olurdu…

Numaralandýrmalar ( Enumerations )
----------------------------------
Bir numaralandýrma (ayný zamanda bir numaralandýrýlmýþ tür veya bir enum olarak da adlandýrýlýr), deðerleri adlandýrýlmýþ sembolik
sabitler kümesiyle (numaralandýrýcýlar olarak adlandýrýlýr) sýnýrlý bir bileþik veri türüdür.

C++ iki tür numaralandýrmayý destekler: kapsamsýz numaralandýrmalar ve kapsamlý numaralandýrmalar.

Numaralandýrmalar, program tanýmlý türler olduðu için 13.1 – Program Tanýmlý (Kullanýcý Tanýmlý) Türlerin Giriþi,
her numaralandýrmanýn tam olarak tanýmlanmasý gerekiyor, kullanmadan önce (bir ileri bildirim yeterli deðil).

Kapsamsýz Numaralandýrmalar ( Unscoped Enumerations )
-----------------------------------------------------
Kapsamsýz numaralandýrmalar, enum anahtar kelimesi aracýlýðýyla tanýmlanýr.

Numaralandýrýlmýþ türler en iyi örneklerle öðretilir, bu yüzden bazý renk deðerlerini tutabilecek bir kapsamsýz numaralandýrma
tanýmlayalým. Nasýl çalýþtýðýný aþaðýda açýklayacaðýz.
                    // Color adýnda yeni bir enum tanýmla
                    enum Color
                    {
                        // Ýþte enum deðerleri
                        // Bu sembolik sabitler, bu tipin alabileceði tüm deðerleri tanýmlar
                        // Her enum deðeri virgülle ayrýlýr, noktalý virgülle deðil
                        red,
                        green,
                        blue, // son enum deðerinden sonra virgül opsiyonel ama tavsiye edilir
                    }; // enum tanýmý noktalý virgülle bitmeli

                    int main()
                    {
                        // Color tipinde birkaç deðiþken tanýmla
                        Color apple { red };   // elma kýrmýzý
                        Color shirt { green }; // gömlek yeþil
                        Color cup { blue };    // bardak mavi

                        Color socks { white }; // hata: white, Color'ýn bir enum deðeri deðil
                        Color hat { 2 };       // hata: 2, Color'ýn bir enum deðeri deðil

                        return 0;
                    }

Örneðimize, enum anahtar kelimesini kullanarak derleyiciye Color adýnda bir enum tanýmladýðýmýzý söyleyerek baþlýyoruz.

Bir çift süslü parantez içinde, Color tipi için enum deðerlerini tanýmlýyoruz: red, green ve blue. Bu enum deðerleri, 
Color tipinin sýnýrlý olduðu belirli deðerleri tanýmlar. Her enum deðeri virgülle ayrýlmalýdýr (noktalý virgülle deðil) -
son enum deðerinden sonra virgül opsiyonel ama tutarlýlýk için tavsiye edilir.

Color için tip tanýmý bir noktalý virgülle biter. Artýk Color adlý enum tipini tamamen tanýmladýk!

main() içinde, Color tipinde üç deðiþken oluþturuyoruz: apple, red rengiyle baþlatýlýyor; shirt, green rengiyle baþlatýlýyor;
ve cup, blue rengiyle baþlatýlýyor. Bu nesneler için bellek ayrýlýr. Bir enum tipinin baþlatýcýsý, o tip için tanýmlanan enum
deðerlerinden biri olmalýdýr. Socks ve hat deðiþkenleri derleme hatalarýna neden olur çünkü baþlatýcýlar white ve 2, 
Color'ýn enum deðerleri deðildir.

Enum deðerleri implisit ( bilinçsiz - otomatik ) olarak constexpr'dir.

Hatýrlatma

Terimler üzerinde hýzlýca bir özet yapalým:

Bir enum veya enum tipi, program tarafýndan tanýmlanan tipin kendisidir (ör. Color).
Bir enum deðeri, enum'a ait belirli bir adlandýrýlmýþ deðerdir (ör. red).
Enum ve enum deðerlerinin adlandýrýlmasý

Geleneksel olarak, enum tiplerinin adlarý büyük harfle baþlar (tüm program tarafýndan tanýmlanan tipler gibi).

*** Uyarý -> Enum'larýn adlandýrýlmasý zorunlu deðildir, ancak modern C++'da isimsiz enum'larýn kullanýlmasý kaçýnýlmalýdýr.

Enum deðerlerine isim verilmelidir. Ne yazýk ki, enum deðerlerinin isimleri için ortak bir adlandýrma kuralý yoktur. Yaygýn
seçenekler arasýnda küçük harfle baþlama (ör. red), büyük harfle baþlama (Red), tüm büyük harfler (RED), bir önek ile tüm büyük 
harfler (COLOR_RED) veya "k" ile öne çýkan ve büyük harfle baþlayan (kColorRed) bulunur.

Modern C++ kurallarý genellikle tüm büyük harfli adlandýrma kurallarýndan kaçýnmayý önerir, çünkü tüm büyük harfler genellikle
öniþlemci makrolarý için kullanýlýr ve çakýþabilir. Büyük harfle baþlayan kurallardan kaçýnmayý da öneririz, çünkü büyük harfle
baþlayan isimler genellikle program tarafýndan tanýmlanan tipler için ayrýlmýþtýr.

*** BEST -> Enum tiplerinizi büyük harfle baþlayarak adlandýrýn. Enum deðerlerinizi küçük harfle baþlayarak adlandýrýn.

Enum tipleri ayrý tiplerdir

Oluþturduðunuz her enum tipi, derleyicinin diðer tiplerden ayýrt edebileceði ayrý bir tip olarak kabul edilir 
(typedef'ler veya tip takma adlarý aksine, bunlar takma ad olduklarý tiplerle ayný kabul edilir).

Çünkü enum tipleri ayrýdýr, bir enum tipinin parçasý olarak tanýmlanan enum deðerleri, baþka bir enum tipinin nesneleriyle
kullanýlamaz:

                    enum Pet
                    {
                        cat,
                        dog,
                        pig,
                        whale,
                    };

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    int main()
                    {
                        Pet myPet { black }; // derleme hatasý: black, Pet'in bir enum deðeri deðil
                        Color shirt { pig }; // derleme hatasý: pig, Color'ýn bir enum deðeri deðil

                        return 0;
                    }

Muhtemelen zaten domuzlu bir gömlek istemezdiniz.

Numaralandýrmalarý Kullanma ( Putting Enumerations to use )
-----------------------------------------------------------
Numaralandýrmalar açýklayýcý olduðu için, kod belgelerini ve okunabilirliðini artýrmak için yararlýdýrlar. Numaralandýrýlmýþ 
türler, küçük bir ilgili sabitler kümesine sahip olduðunuzda ve nesnelerin ayný anda yalnýzca bu deðerlerden birini tutmasý 
gerektiðinde en iyi þekilde kullanýlýr.

Genellikle tanýmlanan numaralandýrýlmalar arasýnda haftanýn günleri, ana yönler ve bir kart destesindeki takýmlar bulunur:

                    enum HaftaninGünleri
                    {
                        pazar,
                        pazartesi,
                        sali,
                        carsamba,
                        persembe,
                        cuma,
                        cumartesi,
                    };

                    enum AnaYönler
                    {
                        kuzey,
                        dogu,
                        güney,
                        bati,
                    };

                    enum KartTakimlari
                    {
                        kulüpler,
                        elmaslar,
                        kalpler,
                        maçalar,
                    };

Bazen fonksiyonlar, fonksiyonun baþarýyla yürütülüp yürütülmediðini veya bir hata ile karþýlaþýp karþýlaþmadýðýný belirtmek için
bir durum kodunu çaðýrýcýya döndürür. Geleneksel olarak, farklý olasý hata kodlarýný temsil etmek için küçük negatif sayýlar 
kullanýlýrdý. Örneðin:

                    int dosyaIceriginiOku()
                    {
                        if (!dosyayiAc())
                            return -1;
                        if (!dosyayiOku())
                            return -2;
                        if (!dosyayiAyristir())
                            return -3;

                        return 0; // baþarý
                    }

Ancak, bu tür sihirli sayýlarý kullanmak çok açýklayýcý deðildir. Daha iyi bir yöntem, bir numaralandýrýlmýþ tür kullanmaktýr:

                    enum DosyaOkumaSonucu
                    {
                        okumaSonucuBasari,
                        okumaSonucuHataDosyaAcma,
                        okumaSonucuHataDosyaOkuma,
                        okumaSonucuHataDosyaAyristirma,
                    };

                    DosyaOkumaSonucu dosyaIceriginiOku()
                    {
                        if (!dosyayiAc())
                            return okumaSonucuHataDosyaAcma;
                        if (!dosyayiOku())
                            return okumaSonucuHataDosyaOkuma;
                        if (!dosyayiAyristir())
                            return okumaSonucuHataDosyaAyristirma;

                        return okumaSonucuBasari;
                    }

Daha sonra çaðýrýcý, fonksiyonun dönüþ deðerini uygun numaralandýrýcýya karþý test edebilir, bu da dönüþ sonucunu belirli bir tam
sayý deðeri için test etmekten daha kolay anlaþýlýr.

                    if (dosyaIceriginiOku() == okumaSonucuBasari)
                    {
                        // bir þey yap
                    }
                    else
                    {
                        // hata mesajý yazdýr
                    }

numaralandýrýlmýþ türler, oyunlarda da iyi bir þekilde kullanýlabilir, farklý türdeki öðeleri, canavarlarý veya arazileri
tanýmlamak için. Temel olarak, küçük bir ilgili nesneler kümesi olan her þey.

Örneðin:

                    enum ÖðeTürü
                    {
                        kýlýç,
                        meþale,
                        iksir,
                    };

                    int main()
                    {
                        ÖðeTürü tutulan{ meþale };

                        return 0;
                    }

numaralandýrýlmýþ türler, kullanýcýnýn iki veya daha fazla seçenek arasýnda bir seçim yapmasý gerektiðinde yararlý iþlev 
parametreleri yapabilir:

                    enum SýralamaDüzeni
                    {
                        alfabetik,
                        alfabetikTers,
                        sayýsal,
                    };

                    void veriyiSýrala(SýralamaDüzeni düzen)
                    {
                        switch (düzen)
                        {
                            case alfabetik:
                                // veriyi ileri alfabetik sýrayla sýrala
                                break;
                            case alfabetikTers:
                                // veriyi geri alfabetik sýrayla sýrala
                                break;
                            case sayýsal:
                                // veriyi sayýsal olarak sýrala
                                break;
                        }
                    }

Birçok dil, Boole'larý tanýmlamak için numaralandýrýlmalarý kullanýr - sonuçta, bir Boole, temelde yalnýzca 2 numaralandýrýcýya
sahip bir sayýlandýrmadýr: false ve true! Ancak, C++'da, true ve false, numaralandýrmalar yerine anahtar kelimeler olarak 
tanýmlanmýþtýr.

numaralandýrýlmalar küçük ve kopyalamasý ucuz olduðu için, onlarý deðer olarak geçmek (ve döndürmek) iyidir.

Ders O.1 -- Bit bayraklarý ve bit manipülasyonu via std::bitset, konusunda bit bayraklarýný tartýþtýk. numaralandýrýlmalar,
std::bitset ile kullanýlmak üzere ilgili bit bayrak pozisyonlarýnýn bir koleksiyonunu tanýmlamak için de kullanýlabilir:

                    #include <bitset>
                    #include <iostream>

                    namespace Bayraklar
                    {
                        enum Durum
                        {
                            ac,
                            uzgun,
                            kizgin,
                            mutlu,
                            guluyor,
                            uyuyor,
                            olu,
                            agliyor,
                        };
                    }

                    int main()
                    {
                        std::bitset<8> ben{};
                        ben.set(Bayraklar::mutlu);
                        ben.set(Bayraklar::gulu);

                        std::cout << std::boolalpha; // bool'u true/false olarak yazdýr

                        // Birkaç durumu sorgula (herhangi bir bitin ayarlý olup olmadýðýný görmek için any() fonksiyonunu
                           kullanýrýz)
                        std::cout << "Mutlu muyum? " << ben.test(Bayraklar::mutlu) << '\n';
                        std::cout << "Gülüyor muyum? " << ben.test(Bayraklar::gulu) << '\n';

                        return 0;
                    }
Bir tam sayý deðerinin beklendiði yerde bir numaralandýrýcýyý nasýl kullanabileceðimizi merak ediyorsanýz, kapsamsýz
numaralandýrýcýlar otomatik olarak tam sayý deðerlerine dönüþtürülür. Bunu bir sonraki derste (13.3 – Kapsamsýz numaralandýrma 
giriþi ve çýkýþý) daha ayrýntýlý olarak inceleyeceðiz.

Kapsamsýz Numaralandýrmalarýn Kapsamý

Kapsamsýz numaralandýrmalar, numaralandýrýcý adlarýný numaralandýrma tanýmýnýn kendisiyle ayný kapsama koyarlar 
(bir ad alanýnýn yaptýðý gibi yeni bir kapsam bölgesi oluþturmak yerine).

Örneðin, bu programý verelim:

                    enum Renk // bu enum global ad alanýnda tanýmlanmýþtýr
                    {
                        kirmizi, // bu yüzden kirmizi global ad alanýna konulur
                        yesil,
                        mavi,
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma kýrmýzý

                        return 0;
                    }
Renk numaralandýrmasý global kapsamda tanýmlanmýþtýr. Bu nedenle, tüm numaralandýrma adlarý (kýrmýzý, yeþil ve mavi) de global
kapsama girer. Bu, global kapsamý kirletir ve ad çakýþma olasýlýðýný önemli ölçüde artýrýr.

Bunun bir sonucu olarak, bir numaralandýrýcý adý ayný kapsamdaki birden çok numaralandýrmada kullanýlamaz:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alanýna konulur
                    };

                    enum Duygu
                    {
                        mutlu,
                        yorgun,
                        mavi, // hata: yukarýdaki mavi ile ad çakýþmasý
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma kýrmýzý
                        Duygu ben { mutlu }; // þu anda mutluyum (programým derlenmiyor olsa bile)

                        return 0;
                    }

Yukarýdaki örnekte, her iki kapsamsýz numaralandýrma (Renk ve Duygu) ayný adý taþýyan numaralandýrýcýlarý global kapsama koyar.
Bu, bir ad çakýþmasýna ve ardýndan derleme hatasýna yol açar.

Kapsamsýz numaralandýrmalar ayrýca numaralandýrýcýlarý için adlandýrýlmýþ bir kapsam bölgesi saðlar (bir ad alanýnýn içindeki
adlarý içeren bir adlandýrýlmýþ kapsam bölgesi gibi). Bu, bir kapsamsýz numaralandýrmanýn numaralandýrýcýlarýna þu þekilde
eriþebileceðimiz anlamýna gelir:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alanýna konulur
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // tamam, numaralandýrýcýyý global ad alanýndan eriþiyor
                        Renk ahududu { Renk::kirmizi }; // ayrýca tamam, numaralandýrýcýyý Renk kapsamýndan eriþiyor

                        return 0;
                    }

Çoðu zaman, kapsamsýz numaralandýrýcýlar kapsam çözümleme operatörünü kullanmadan eriþilir.

Numaralandýrýcý Ad Çakýþmalarýný Önlemek
----------------------------------------
Kapsamsýz numaralandýrýcý ad çakýþmalarýný önlemenin oldukça yaygýn birkaç yolu vardýr. Bir seçenek, her numaralandýrýcýyý
numaralandýrmanýn adýyla öne koymaktýr:

                    enum Renk
                    {
                        renk_kirmizi,
                        renk_mavi,
                        renk_yesil,
                    };

                    enum Duygu
                    {
                        duygu_mutlu,
                        duygu_yorgun,
                        duygu_mavi, // artýk renk_mavi ile ad çakýþmasý yok
                    };

                    int main()
                    {
                        Renk boya { renk_mavi };
                        Duygu ben { duygu_mavi };

                        return 0;
                    }

Bu hala ad alanýný kirletir ama adlarý daha uzun ve daha benzersiz yaparak ad çakýþma olasýlýðýný azaltýr. Daha iyi bir seçenek,
numaralandýrýlmýþ türü, ayrý bir kapsam bölgesi saðlayan bir þeyin içine koymaktýr, örneðin bir ad alaný:

                    namespace Renk
                    {
                        // Renk, kýrmýzý, mavi ve yeþil adlarý, Renk ad alaný içinde tanýmlanýr
                        enum Renk
                        {
                            kirmizi,
                            yesil,
                            mavi,
                        };
                    }

                    namespace Duygu
                    {
                        enum Duygu
                        {
                            mutlu,
                            yorgun,
                            mavi, // Duygu::mavi, Renk::mavi ile çakýþmaz
                        };
                    }

                    int main()
                    {
                        Renk::Renk boya{ Renk::mavi };
                        Duygu::Duygu ben{ Duygu::mavi };

                        return 0;
                    }

Bu, artýk numaralandýrma ve numaralandýrýcý adlarýmýzý kapsam bölgesinin adýyla öne koymamýz gerektiði anlamýna gelir.
Ýlgili bir seçenek, kendi kapsam bölgesini tanýmlayan bir kapsamlý numaralandýrma kullanmaktýr göreceðiz.
*** BEST -> Numaralandýrmalarýnýzý, numaralandýrýcýlarýn global ad alanýný kirletmemesi için adlandýrýlmýþ bir kapsam bölgesi 
            içine koymayý tercih edin (örneðin bir ad alaný veya sýnýf).

Alternatif olarak, bir numaralandýrma yalnýzca tek bir fonksiyonun gövdesinde kullanýlýyorsa, numaralandýrma fonksiyonun içinde 
tanýmlanmalýdýr. Bu, numaralandýrmanýn ve numaralandýrýcýlarýnýn kapsamýný yalnýzca o fonksiyona sýnýrlar. Bu tür bir 
numaralandýrmanýn numaralandýrýcýlarý, global kapsamda tanýmlanan ayný adlý numaralandýrýcýlarý gölgede býrakýr.

Numaralandýrýcýlarla Karþýlaþtýrma
----------------------------------
Bir numaralandýrmanýn belirli bir numaralandýrýcýnýn deðerine sahip olup olmadýðýný test etmek için eþitlik operatörlerini
(operator== ve operator!=) kullanabiliriz.

                    #include <iostream>

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi,
                    };

                    int main()
                    {
                        Renk gomlek{ mavi };

                        if (gomlek == mavi) // eðer gömlek maviyse
                            std::cout << "Gömleðiniz mavi!";
                        else
                            std::cout << "Gömleðiniz mavi deðil!";

                        return 0;
                    }
Yukarýdaki örnekte, bir if-deyimi kullanarak gomleðin numaralandýrýcý maviye eþit olup olmadýðýný test ediyoruz. Bu, programýmýzýn
davranýþýný, numaralandýrmamýzýn hangi numaralandýrýcýyý tuttuðuna dayalý olarak koþullandýrmamýz için bir yol saðlar.

Bunu bir sonraki derste daha fazla kullanacaðýz.
*/