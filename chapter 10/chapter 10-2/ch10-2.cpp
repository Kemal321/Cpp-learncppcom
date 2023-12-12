
#include <iostream>

int main()
{
    return 0;
}
/*
                                                        *10.7 — Typedefs ve Tür Takma Adlarý*
                                                        * --------------------------------- *

C++ dilinde, using kelimesi mevcut bir veri tipi için bir takma ad oluþturan bir anahtar kelimedir.

                    using Mesafe = double; // Mesafe'yi double türü için bir takma ad olarak tanýmla

Bir kez tanýmlandýktan sonra, bir tür takma adý, bir tür gerektiðinde herhangi bir yerde kullanýlabilir.

                    Mesafe milesToDestination{ 3.4 }; // double türünde bir deðiþken tanýmlar

Derleyici bir tür takma adý ismiyle karþýlaþtýðýnda, takma adýn yerine takma ad yapýlan türü yerine koyacaktýr. 

                    #include <iostream>

                    int main()
                    {
                        using Mesafe = double; // Mesafe'yi double türü için bir takma ad olarak tanýmla

                        Mesafe milesToDestination{ 3.4 }; // double türünde bir deðiþken tanýmlar

                        std::cout << milesToDestination << '\n'; // bir double deðeri yazdýrýr

                        return 0;
                    }
             çýktý: 3.4

Yukarýdaki programda, önce Distance'ý double türü için bir takma ad olarak tanýmlýyoruz.

Daha sonra, Distance türünde milesToDestination adýnda bir deðiþken tanýmlýyoruz. Derleyici Distance'ýn bir tür takma adý olduðunu bildiði için,
takma ad yapýlan türü kullanacak, yani double. Bu nedenle, milesToDestination deðiþkeni aslýnda bir double türünde derlenir ve her açýdan bir double
gibi davranacaktýr.

Son olarak, milesToDestination deðerini yazdýrýyoruz, bu da bir double deðeri olarak yazdýrýlacaktýr.

Tür takma adlarýný adlandýrma
-----------------------------
Tarih boyunca, tür takma adlarýnýn adlandýrýlmasýnda tutarlýlýk eksikliði olmuþtur. Üç yaygýn adlandýrma kuralý bulunmaktadýr (ve bunlarýn hepsine
rastlayacaksýnýz):

- Bir " _t " eki ile biten tür takma adlarý ("_t", "type" kelimesinin kýsaltmasýdýr). Bu kural genellikle standart kütüphane tarafýndan genel kapsamlý
tür adlarý için kullanýlýr (örneðin size_t ve nullptr_t gibi).
Bu kural, C'den miras alýnmýþ olup, kendi tür takma adlarýnýzý (ve bazen diðer türleri) tanýmlarken eskiden en popüler olanýydý, ancak modern C++'da 
tercih edilen bir kural deðildir. POSIX, "_t" eki için genel kapsamlý tür adlarýný ayýrdýðýndan, bu kuralýn kullanýlmasý POSIX sistemlerinde tür adý 
çakýþmalarýna neden olabilir.

- Bir " _type " eki ile biten tür takma adlarý. Bu kural, bazý standart kütüphane türleri (örneðin std::string) tarafýndan kullanýlýr ve gömülü tür 
takma adlarýný (örneðin std::string::size_type) adlandýrmak için kullanýlýr.
Ancak birçok gömülü tür takma adý hiçbir ek kullanmaz (örneðin std::string::iterator), bu nedenle bu kullaným en iyi durumda tutarsýzdýr.

- Hiçbir ek kullanýlmayan tür takma adlarý.
Modern C++'da, genellikle kendiniz tanýmladýðýnýz tür takma adlarýný (veya baþka herhangi bir türü) büyük harfle baþlatarak ve hiçbir ek kullanmadan
adlandýrma konvansiyonu benimsenmiþtir. Büyük harf, tür adlarýný deðiþken ve fonksiyon adlarýndan (ki bunlar küçük harfle baþlar) ayýrmaya yardýmcý 
olur ve aralarýndaki ad çakýþmalarýný önler.

Bu adlandýrma kuralýný kullanýrken þu kullanýmý sýkça görmek yaygýndýr:

                    void printDistance(Mesafe mesafe); // Mesafe, tanýmlanmýþ bir türdür

Bu durumda, Mesafe türdür ve mesafe parametre adýdýr. C++ case-sensitive bir dildir, bu nedenle bu kullaným uygundur.

*** BEST -> Tür takma adlarýnýzý büyük harfle baþlatýn ve bir ek kullanmaktan kaçýnýn (eðer baþka bir nedeniniz yoksa).

Tür takma adlarý, ayrý türler deðildir
--------------------------------------

Bir takma ad, aslýnda yeni ve ayrý bir tür tanýmlamaz (diðer türlerden ayrý bir þekilde düþünülen bir tür) - yalnýzca mevcut bir tür için yeni
bir tanýmlayýcý tanýtýr. Bir tür takma adý, tamamen takma ad yapýlan türle deðiþtirilebilir.

Bu, sözdizimi açýsýndan geçerli ancak anlamsýz olan þeyleri yapmamýza olanak tanýr. Örneðin:

                    int main()
                    {
                        using Miles = long; // Miles'i long türü için bir takma ad olarak tanýmla
                        using Speed = long; // Speed'ý long türü için bir takma ad olarak tanýmla

                        Miles distance { 5 }; // distance aslýnda sadece bir long
                        Speed mhz  { 3200 };  // mhz aslýnda sadece bir long

                        // Aþaðýdaki sözdizimi açýsýndan geçerli (ancak anlamsýz) bir durumdur
                        distance = mhz;

                        return 0;
                    }

Kavramsal olarak Miles ve Speed'in farklý anlamlarý olmasýný amaçlasak da, her ikisi de sadece long türü için takma adlardýr. Bu, etkili bir þekilde
Miles, Speed ve long'un tümünün birbirinin yerine kullanýlabileceði anlamýna gelir. Ve gerçekten de, bir Speed türünden bir deðeri bir Miles türündeki
bir deðiþkene atadýðýmýzda, derleyici yalnýzca bir long türünden bir deðeri bir long türündeki bir deðiþkene atadýðýmýzý görür ve herhangi bir uyarý
yapmaz.

Derleyici, tür takma adlarý için bu tür semantik hatalarý önlemez, bu nedenle takma adlarýn tür güvenli olmadýðýný söyleriz. Buna raðmen, bunlar hala 
kullanýþlýdýr.

!!! Dikkat edilmelidir ki, semantik olarak farklý olmasý amaçlanan takma ad deðerlerini karýþtýrmamaya özen gösterilmelidir.

Bir not olarak...

Bazý diller, güçlü bir tür adý (ya da güçlü tür takma adý) kavramýný destekler. Güçlü bir tür adý, aslýnda tüm orijinal özelliklere sahip olan yeni
bir tür oluþturur, ancak derleyici, takma ad türü ile orijinal türün deðerlerini karýþtýrmaya çalýþýrsanýz bir hata fýrlatýr. C++20'ye kadar, C++
doðrudan güçlü tür adlarýný desteklemez (ancak 13.4 dersinde ele alýnan türlerle benzer olan enum class'lar mevcuttur), ancak güçlü tür adý benzeri
davranýþý uygulayan birçok üçüncü taraf C++ kütüphanesi bulunmaktadýr.

Tür takma adýnýn kapsamý
------------------------

Çünkü kapsam bir tanýmlayýcýnýn özelliðidir, tür takma adý tanýmlayýcýlarý deðiþken tanýmlayýcýlarýyla ayný kapsama kurallarýný takip eder: bir blok 
içinde tanýmlanan bir tür takma adýnýn blok kapsamý vardýr ve yalnýzca o blok içinde kullanýlabilir, global ad alanýnda tanýmlanan bir tür takma adýnýn 
ise global kapsamý vardýr ve dosyanýn sonuna kadar kullanýlabilir. Yukarýdaki örnekte, Miles ve Speed sadece main() fonksiyonunda kullanýlabilir.

Eðer bir veya daha fazla tür takma adýný birden fazla dosya üzerinde kullanmanýz gerekiyorsa, bunlar bir baþlýk dosyasýnda tanýmlanabilir ve tanýmý
kullanmak isteyen tüm kod dosyalarýna #include edilebilir:

                        mytypes.h:
                        #ifndef MYTYPES_H
                        #define MYTYPES_H

                            using Miles = long;
                            using Speed = long;

                        #endif

Bu þekilde #include edilen tür takma adlarý, global ad alýnýna içe aktarýlacak ve dolayýsýyla global kapsama sahip olacaktýr.

Typedefs
--------

Typedef ("type definition" kýsaltmasý) bir tür için takma ad oluþturmanýn eski bir yoludur. Bir typedef takma adý oluþturmak
için typedef anahtar kelimesini kullanýrýz:

                        // Aþaðýdaki takma adlar özdeþtir
                        typedef long Miles;
                        using Miles = long;

Typedef'ler, geriye dönük uyumluluk nedenleriyle hâlâ C++ dilinde bulunmaktadýr, ancak modern C++'ta genellikle tür takma adlarý
tarafýndan büyük ölçüde yer deðiþtirmiþtir.

Typedef'lerin birkaç sözdizimi sorunu vardýr. Ýlk olarak, typedef'in adýnýn mý yoksa takma ad yapýlacak türün mü önce geleceðini
unutmak kolaydýr. Hangisi doðrudur?

                        typedef Distance double; // incorrect (typedef name first)
                        typedef double Distance; // correct (aliased type name first)

Bu durumu karýþtýrmak kolaydýr. Neyse ki, bu tür durumlarda derleyici uyarý verecektir.

Ýkinci olarak, typedef'lerin sözdizimi daha karmaþýk türlerle birlikte çirkinleþebilir. Örneðin, okunmasý zor bir typedef aþaðýda
verilmiþ olup, buna karþýlýk gelen ve biraz daha okunabilir olan bir tür takma adý da bulunmaktadýr:

                        typedef int (*FcnType)(double, char); // FcnType'ý bulmasý zordur 
                        using FcnType = int(*)(double, char); // FcnType' easier to find'ý bulmasý kolaydýr 

Yukarýdaki typedef tanýmýnda, yeni türün adý (FcnType) tanýmýn ortasýna gömülmüþtür, oysa tür takma adýnda yeni türün adý ve geri kalan 
taným bir eþittir iþareti ile ayrýlmýþtýr.

Üçüncü olarak, "typedef" adý, yeni bir türün tanýmlandýðýný düþündürse de, bu doðru deðildir. Bir typedef sadece bir takma ad'dýr.

*** BEST -> Type aliases ý typedef e tercih etmek en iyisidir. 

Terminoloji

C++ standardý, hem typedef'lerin hem de tür takma adlarýnýn adlarý için "typedef adlarý ( Typedef names )" terimini kullanýr.

Tür takma adlarýný ne zaman kullanmalýyýz?
------------------------------------------
---> Platform-independent kodlama için tür takma adlarý kullanmak

Tür takma adlarýnýn temel kullanýmlarýndan biri, platforma özgü ayrýntýlarý gizlemektir. Bazý platformlarda bir int 2 bayt iken, diðerlerinde 4 bayttýr.
Bu nedenle, platform baðýmsýz kod yazarken int'i 2 bayttan fazla bilgi depolamak potansiyel olarak tehlikeli olabilir.

char, short, int ve long'un boyutu hakkýnda hiçbir bilgi vermemesi nedeniyle, çapraz platformlu programlarýn, türün boyutunu bit cinsinden içeren 
takma adlarý tanýmlamak için tür takma adlarýný kullanmasý oldukça yaygýndýr. Örneðin, int8_t bir 8-bit iþaretsiz tamsayýyý, int16_t bir 16-bit
iþaretsiz tamsayýyý ve int32_t bir 32-bit iþaretsiz tamsayýyý tanýmlar. Bu þekilde tür takma adlarý kullanmak, hatalarý önlemeye yardýmcý olur ve
deðiþkenin boyutuyla ilgili hangi tür varsayýmlarýn yapýldýðýný daha net hale getirir.

Bu tür takma adlarýnýn her birinin doðru boyutta bir türle çözülmesini saðlamak için, genellikle bu tür takma adlarý öniþlemci yönergeleri ile birlikte 
kullanýlýr:

                        #ifdef INT_2_BYTES
                        using int8_t = char;
                        using int16_t = int;
                        using int32_t = long;
                        #else
                        using int8_t = char;
                        using int16_t = short;
                        using int32_t = int;
                        #endif

Makinelerde tamsayýlar yalnýzca 2 bayt olduðunda, INT_2_BYTES #define edilebilir (derleyici/ön iþlemci ayarý olarak), ve program üstteki tür takma 
adlarý seti ile derlenir. Tamsayýlarýn 4 bayt olduðu makinelerde, INT_2_BYTES'in tanýmsýz býrakýlmasý, alttaki tür takma adlarý setinin kullanýlmasýna
neden olacaktýr. Bu þekilde, INT_2_BYTES doðru bir þekilde #define edildiði sürece, int8_t 1 bayt tamsayýsýna, int16_t 2 bayt tamsayýsýna ve int32_t 4
bayt tamsayýsýna çözümlenecektir (programýn derlendiði makine için uygun olan char, short, int ve long kombinasyonunu kullanarak).

Sabit geniþlikte tamsayý türleri (std::int16_t ve std::uint32_t gibi) ve size_t türü (her ikisi de 4.6 dersinde ele alýnan Sabit Geniþlikte Tamsayýlar
ve size_t) aslýnda çeþitli temel türlere yönlendiren tür takma adlarýdýr.

Bu ayný zamanda, bir 8-bit sabit geniþlikli tamsayýyý std::cout kullanarak yazdýrdýðýnýzda neden muhtemelen bir karakter deðeri elde ettiðinizi açýklar. Örneðin:

                        #include <cstdint> // sabit geniþlikte tamsayýlar için
                        #include <iostream>

                        int main()
                        {
                            std::int8_t x{ 97 }; // int8_t genellikle signed char için bir tür takma adýdýr
                            std::cout << x << '\n';

                            return 0;
                        }
                Çýktý : a

Çünkü std::int8_t genellikle signed char için bir tür takma adýdýr, deðiþken x büyük olasýlýkla signed char olarak tanýmlanacaktýr. Ve char türleri,
deðerlerini tamsayý deðerleri olarak deðil, ASCII karakterleri olarak yazdýrýr.

---> Karmaþýk türleri daha okunabilir hale getirmek için tür takma adlarýný kullanmak

Þimdiye kadar sadece basit veri tipleriyle uðraþtýk, ancak geliþmiþ C++'ta, tipler karmaþýk ve klavyenizden manuel olarak girmesi uzun olabilir.
Örneðin, bir fonksiyonu ve deðiþkeni þu þekilde tanýmlanmýþ görebilirsiniz:

                        #include <string> // for std::string
                        #include <vector> // for std::vector
                        #include <utility> // for std::pair

                        bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
                        {
                            // some code here
                            return false;
                        }

                        int main()
                        {
                             std::vector<std::pair<std::string, int>> pairlist;

                             return 0;
                        }

std::vector<std::pair<std::string, int>> türünü her kullanmanýz gerektiðinde yazmak zahmetli ve yazým
hatasý yapma olasýlýðý yüksektir. Bir tür takma adý kullanmak çok daha kolaydýr:

                        #include <string> // std::string için
                        #include <vector> // std::vector için
                        #include <utility> // std::pair için

                        using VectPairSI = std::vector<std::pair<std::string, int>>; // VectPairSI'ý bu karmaþýk tür için bir takma ad yap

                        bool hasDuplicates(VectPairSI pairlist) // VectPairSI'ý bir fonksiyon parametresinde kullan
                        {
                            // burada bazý kodlar
                            return false;
                        }

                        int main()
                        {
                             VectPairSI pairlist; // VectPairSI türünde bir deðiþken oluþtur

                             return 0;
                        }

Çok daha iyi! Þimdi std::vector<std::pair<std::string, int>> yerine sadece VectPairSI yazmamýz gerekiyor.

Eðer henüz std::vector, std::pair veya tüm bu çýlgýn açýlý parantezleri bilmiyorsanýz endiþelenmeyin. Burada gerçekten anlamanýz gereken tek þey, 
tür takma adlarýnýn karmaþýk türleri almanýza ve onlara daha basit bir isim vermenize olanak tanýdýðýdýr, bu da kodunuzu daha okunabilir hale getirir
ve yazma iþleminden tasarruf saðlar.

Bu muhtemelen tür takma adlarýnýn en iyi kullanýmýdýr.

---> Bir deðerin anlamýný belgelemek için tür takma adlarý kullanmak
Tür takma adlarý, kod belgeleri ve anlama katký saðlamak için de yardýmcý olabilir.

Deðiþkenlerle, deðiþkenin tanýmlayýcýsý, deðiþkenin amacýný belgelemeye yardýmcý olur. Ancak bir fonksiyonun dönüþ deðeri durumunu düþünelim. char,
int, long, double ve bool gibi veri tipleri, bir fonksiyonun ne tür bir deðer döndürdüðünü belirtir, ancak daha sýk olarak bir dönüþ deðerinin anlamýný 
bilmek istiyoruz.

Örneðin, aþaðýdaki fonksiyonu düþünün:

                        int gradeTest();    

Dönüþ deðerinin bir tamsayý olduðunu görebiliriz, ancak bu tamsayý ne anlama geliyor? Bir harf notu mu? Kaç sorunun yanlýþ olduðu mu? Öðrencinin
kimlik numarasý mý? Bir hata kodu mu? Kim bilir! int türündeki dönüþ türü bize pek çok þey söylemez. Þanslýysak, fonksiyon için bir yerlerde belgeleme
bulunabilir. Þanssýzsak, kodu okumak ve amacý çýkarmak zorunda kalabiliriz.

Þimdi bir tür takma adý kullanarak eþdeðer bir versiyon yapalým:

                        using TestScore = int;
                        TestScore gradeTest();

TestScore'un dönüþ türü, fonksiyonun bir test skorunu temsil eden bir türü döndürdüðünü biraz daha açýk hale getirir.

Deneyimimize göre, yalnýzca tek bir iþlevin dönüþ türünü belgelemek için bir tür takma adý oluþturmak (onun yerine bir yorum kullanýn) deðmez. Ancak
birden fazla iþlevin böyle bir türü geçmesi veya döndürmesi durumunda, bir tür takma adý oluþturmak faydalý olabilir.

---> Tür takma adlarýný kullanarak kod bakýmýný kolaylaþtýrma

Tür takma adlarý ayrýca bir nesnenin temel türünü deðiþtirmenizi saðlar ve bunu yaparken çok sayýda sabit türü güncelleme zorunluluðundan kurtarýr.
Örneðin, bir öðrenci kimlik numarasýný tutmak için bir short kullanýyorsanýz, ancak daha sonra bunun yerine bir long'a ihtiyacýnýz olduðuna karar 
verirseniz, çok sayýda kodu gözden geçirip short'u long ile deðiþtirmeniz gerekebilir. short türündeki hangi nesnelerin kimlik numaralarýný tutmak 
için kullanýldýðýný ve hangilerinin baþka amaçlar için kullanýldýðýný belirlemek muhtemelen zor olacaktýr.

Ancak, tür takma adlarý kullanýyorsanýz, türleri güncellemek, yalnýzca tür takma adýný güncellemek kadar basit hale gelir (örneðin, StudentId = short;
kullanýyorsanýz, StudentId = long; olarak güncellemek).

Bu güzel bir avantaj gibi görünse de, bir tür deðiþtirildiðinde dikkatli olunmalýdýr, çünkü programýn davranýþý da deðiþebilir. Bu özellikle bir tür 
takma adýnýn tür ailesinde farklý bir tür (örneðin, bir tamsayýdan bir kayan nokta deðerine veya bir iþaretsizden bir iþaretli deðere) deðiþtirilirse 
geçerlidir! Yeni türün karþýlaþtýrma veya tamsayý/kayan nokta bölme sorunlarý veya eski türün olmayan diðer sorunlarý olabilir. Mevcut bir türü baþka 
bir türe deðiþtiriyorsanýz, kodunuz kapsamlý bir þekilde yeniden test edilmelidir.


Dezavantajlar ve Sonuç
**********************

Tür takma adlarý bazý avantajlar sunsa da, ayný zamanda kodunuza anlaþýlmasý gereken baþka bir tanýmlayýcý ekler. Eðer bu, okunabilirlik veya anlama
açýsýndan bir faydayla dengelemezse, tür takma adý daha çok zarar verir.

Kötü bir þekilde kullanýlan bir tür takma adý, tanýdýk bir türü (örneðin, std::string gibi) özel bir ismin arkasýna gizleyebilir ve bunun araþtýrýlmasý 
gerekebilir. Bazý durumlarda (gelecekte ele alacaðýmýz akýllý iþaretçiler gibi), tür bilgisini gizlemek, türün nasýl çalýþmasý gerektiðini anlama 
konusunda da zararlý olabilir.

Bu nedenle, tür takma adlarý, kodun okunabilirliði veya bakýmý açýsýndan açýk bir faydasý olduðu durumlarda kullanýlmalýdýr. Bu konu, bir sanattan 
çok bir bilimdir. Tür takma adlarý, kodunuzun birçok yerinde kullanýldýðýnda daha etkilidir, daha az yerde deðil.

*** BEST -> Tür takma adlarýný, kodun okunabilirliðini veya bakýmýný net bir þekilde artýrdýklarýnda ölçülü bir þekilde kullanýn.

10.8 — auto Anahtar Kelimesi Kullanarak Nesneler Ýçin Tür Çýkarýmý
------------------------------------------------------------------

Bu basit deðiþken tanýmýnda gizli bir tekrarlýlýk bulunmaktadýr:
                            double d{ 5.0 };
Çünkü C++, güçlü türleme (strongly-typed) bir dil olduðu için, tüm nesneler için açýk bir tür saðlamak zorundayýz. Bu nedenle, deðiþken d'nin double 
türünde olduðunu belirttik.

Ancak, d'yi baþlatmak için kullanýlan 5.0 rakamý da türü double olan bir literalden (anlamý biçimsel olarak belirlenen) dolaylý olarak tespit edilir.

Deðiþkenin ve baþlatýcýsýnýn ayný türe sahip olmasýný istediðimiz durumlarda, ayný tür bilgisini etkili bir þekilde iki kez saðlýyoruz.

Baþlatýlan Deðiþkenler Ýçin Tür Çýkarýmý
----------------------------------------
Tür çýkarýmý( Type deduction ) (bazen tür çýkarýmý ( type inference ) olarak da adlandýrýlýr), derleyicinin bir nesnenin türünü nesnenin baþlatýcýsýndan
çýkarmasýna izin veren bir özelliktir. Tür çýkarýmýný kullanmak için, "auto" anahtar kelimesi deðiþkenin türünün yerine kullanýlýr:

                            int main()
                            {
                                auto d{ 5.0 };   // 5.0 bir double literaldýr, bu nedenle d double türünde olacaktýr
                                auto i{ 1 + 2 }; // 1 + 2 bir int deðerini deðerlendirdiði için i int türünde olacaktýr
                                auto x{ i };     // i bir int olduðu için x de int türünde olacaktýr

                                return 0;
                            }


Ýlk durumda, çünkü 5.0 bir double literaldýr, derleyici deðiþken d'nin double türünde olmasý gerektiðini çýkaracaktýr. Ýkinci durumda, 1 + 2 ifadesi
bir int sonucu verdiði için deðiþken i int türünde olacaktýr. Üçüncü durumda, i önceden int türünde çýkarýlmýþtý, bu nedenle x'in de int türünde
çýkarýlmasý gerekecektir.

Fonksiyon çaðrýlarý geçerli ifadeler olduðu için, baþlatýcýmýz bir fonksiyon çaðrýsý olduðunda bile tür çýkarýmýný kullanabiliriz:

                            int add(int x, int y)
                            {
                                return x + y;
                            }

                            int main()
                            {
                                auto sum{ add(5, 6) }; // add() bir int döndürdüðü için sum'un türü int olarak çýkarýlacaktýr
                                return 0;
                            }

add() fonksiyonu bir int deðeri döndürdüðü için derleyici deðiþken sum'un int türünde olmasý gerektiðini çýkaracaktýr.

Tür çýkarýmý, baþlatýcýsý olmayan veya boþ baþlatýcýlara sahip nesneler için çalýþmaz. Bu nedenle, aþaðýdaki geçerli deðildir:

                            int main()
                            {
                                auto x;   // Derleyici x'in türünü çýkaramaz
                                auto y{ }; // Derleyici y'nin türünü çýkaramaz

                                return 0;
                            }

Temel veri tipleri için tür çýkarýmýný kullanmak yalnýzca birkaç (eðer hiç) tuþ vuruþu tasarrufu saðlasa da, gelecekteki derslerde türlerin 
karmaþýk ve uzun olduðu örnekleri göreceðiz (ve bazý durumlarda, anlamak zor olabilir). Bu durumlarda, auto kullanmak çok yazým (ve yazým hatalarý)
tasarrufu saðlayabilir.

Tür çýkarýmý, const / constexpr nitelendiricilerini düþürür.
------------------------------------------------------------

Çoðu durumda, tür çýkarýmý const veya constexpr nitelendiricisini çýkarýr. Örneðin:

                            int main()
                            {
                                const int x { 5 }; // x'in türü const int
                                auto y { x };      // y'nin türü int olacaktýr (const düþürüldü)

                                return 0;
                            }

Yukarýdaki örnekte, x'in türü const int'dir, ancak x'i baþlatýcý olarak kullanarak deðiþken y için bir tür çýkarýldýðýnda, tür çýkarýmý türü const 
int yerine int olarak çýkarýr.

Eðer bir çýkarýlan türün const veya constexpr olmasýný istiyorsanýz, const veya constexpr anahtar kelimesini auto anahtarýyla birlikte kullanmalýsýnýz:

                            int main()
                            {
                                const int x { 5 };         // x'in türü const int (derleme zamanýnda const)
                                auto y { x };              // y'nin türü int olacaktýr (const düþürüldü)

                                constexpr auto z { x };    // z'nin türü constexpr int olacaktýr (constexpr tekrar uygulandý)

                                return 0;
                            }

Bu örnekte x'ten türetilen tür int olacaktýr (const býrakýlmýþtýr), ancak z deðiþkeninin tanýmý sýrasýnda constexpr niteleyicisini yeniden eklediðimiz 
için z deðiþkeni bir constexpr int olacaktýr.

String literals için Type deduction
-----------------------------------

Tarihsel nedenlerden dolayý, C++ dilinde string literallerinin tuhaf bir türü vardýr. Bu nedenle, aþaðýdaki örneðin beklenildiði gibi çalýþmasý 
muhtemel deðildir:

                        auto s { "Hello, World!" }; // s'nin türü const char* olacak, std::string deðil

Eðer bir string literalinden türetilen tipin std::string veya std::string_view olmasýný istiyorsanýz, s veya sv literal öneklerini kullanmanýz gerekecek
(5.4 dersinde ele alýnmýþtýr):

                        #include <string>
                        #include <string_view>

                        int main()
                        {
                            using namespace std::literals; // s ve sv öneklerine eriþim için en kolay yol

                            auto s1 { "goo"s };  // "goo"s bir std::string literal olduðu için s1, std::string olarak çýkarýlacaktýr
                            auto s2 { "moo"sv }; // "moo"sv bir std::string_view literal olduðu için s2, std::string_view olarak çýkarýlacaktýr

                            return 0;
                        }
Tür deduction avantajlarý ve dezavantajlarý
-------------------------------------------
Tür deduction yalnýzca kullanýþlý olmakla kalmaz, ayný zamanda bir dizi baþka faydaya da sahiptir.

Ýlk olarak, sýralý satýrlarda iki veya daha fazla deðiþken tanýmlanýrsa deðiþkenlerin adlarý sýralanacak ve okunabilirliðin artmasýna yardýmcý olacaktýr:

                        // daha zor okunabilir
                        int a { 5 };
                        double b { 6.7 };

                        // daha kolay okunabilir
                        auto c { 5 };
                        auto d { 6.7 };

Ýkinci olarak, tür çýkarýmý yalnýzca baþlatýcýya sahip olan deðiþkenlerde çalýþýr; bu nedenle, tür çýkarýmýný kullanma alýþkanlýðýnýz varsa, istenmeyen 
durumlarda baþlatýlmamýþ deðiþkenleri önlemeye yardýmcý olabilir.

                        int x; // ups, x'in baþlatýlmasýný unuttuk, ancak derleyici uyarý vermeyebilir
                        auto y; // derleyici, y için bir tür çýkarýlamadýðýndan hata verecek

Üçüncü olarak, istenmeyen performans etkileyen dönüþümlerin olmayacaðýna garanti verilir.

                        std::string_view getString();   // std::string_view döndüren bir fonksiyon

                        std::string s1{ getString() };  // kötü: std::string_view'dan std::string'e pahalý dönüþüm (bu istemediðiniz varsayýlýrsa)
                        auto s2{ getString() };         // iyi: dönüþüm gerekmiyor

Tür çýkarýmýnýn birkaç dezavantajý vardýr.

Ýlk olarak, tür çýkarýmý, bir nesnenin tür bilgisini kod içinde gizler. Ýyi bir IDE'nin size çýkarýlan türü gösterebilmesi gerekse de (örneðin,
bir deðiþkenin üzerine gelindiðinde), tür çýkarýmý kullanýrken türle ilgili hatalar yapmak biraz daha kolaydýr.

Örneðin:
                        auto y { 5 }; // oops, we wanted a double here but we accidentally provided an int literal

Yukarýdaki kod örneðinde, eðer y'yi açýkça bir double türü olarak belirtmiþ olsaydýk, y bir int literali baþlatýcýsý versek bile yine double olacaktý. 
Ancak tür çýkarýmý kullanýldýðýnda, y'nin türü int olarak çýkarýlacaktýr.

Ýþte baþka bir örnek:

                        #include <iostream>

                        int main()
                        {
                                auto x { 3 };
                                auto y { 2 };

                                std::cout << x / y << '\n'; // hata, burada ondalýk sayý bölme istemiþtik

                                return 0;
                        }
Bu örnekte, bir tam sayý bölme yerine ondalýk sayý bölmesi aldýðýmýzý anlamak daha az açýktýr.

Ýkinci olarak, baþlatýcýnýn türü deðiþtiðinde, tür çýkarýmý kullanarak bir deðiþkenin türü de deðiþecektir, belki de beklenmedik bir þekilde.
Aþaðýdaki örneði düþünün:

                        auto sum { add(5, 6) + gravity };

Eðer `add` fonksiyonunun dönüþ türü int'ten double'a deðiþirse veya gravity'nin türü int'ten double'a deðiþirse, sum deðiþkeninin türü de int'ten 
double'a deðiþecektir.

Genel olarak, modern görüþ genellikle tür çýkarýmýnýn nesneler için genellikle güvenli olduðu ve bunun kullanýlmasýnýn kodunuzu daha okunabilir 
hale getirebileceði yönündedir. Tür bilgisini önemsizleþtirerek kod mantýðýný daha belirgin hale getirebilirsiniz.

*** BEST -> Deðiþkenleriniz için tür çýkarýmýný kullanýn, ancak belirli bir türe baðlý kalmaya ihtiyacýnýz varsa belirli bir türü açýkça belirtin.

!! Gelecekteki derslerde, tür bilgisini göstermek, bir kavramý veya örneði anlamak için yardýmcý olduðunda, açýk türleri kullanmaya devam edeceðiz.

10.9 — Fonksiyonlarda Tür çýkarýmý - Type deduction for functions
-----------------------------------------------------------------
Bir örneði inceleyerek baþlayalým:
 
                        int add(int x, int y)
                        {
                            return x + y;
                        }


Bu fonksiyon derlendiðinde, derleyici x + y'nin bir int deðerini deðerlendirdiðini belirler, ardýndan dönen deðerin türünün, fonksiyonun beyan edilen
dönüþ türüyle eþleþtiðinden veya dönüþ deðeri türünün beyan edilen dönüþ türüne dönüþtürülebileceðinden emin olur.

Çünkü derleyici zaten dönüþ türünü return ifadesinden çýkarmak zorunda olduðundan, C++14'te auto anahtar kelimesi, fonksiyon dönüþ türü çýkarýmý yapmak
üzere geniþletildi. Bu, auto anahtar kelimesini fonksiyonun dönüþ türü yerine kullanarak çalýþýr.

Örneðin:
                        auto add(int x, int y)
                        {
                            return x + y;
                        }


Çünkü return ifadesi bir int deðeri döndürüyor, derleyici bu fonksiyonun dönüþ türünün int olduðunu çýkaracaktýr.

Auto dönüþ türü kullanýlýrken, fonksiyon içindeki tüm return ifadelerinin ayný türde deðer döndürmesi gerekir, aksi takdirde bir hata oluþacaktýr. 
Örneðin:

                        auto someFcn(bool b)
                        {
                            if (b)
                                return 5; // return type int
                            else
                                return 6.7; // return type double
                        }

Yukarýdaki fonksiyonda, iki return ifadesi farklý türlerde deðer döndürdüðünden dolayý derleyici hata verecektir.

Eðer bu tür bir durum bir nedenle isteniyorsa, ya fonksiyonunuz için açýkça bir dönüþ türü belirtirsiniz (bu durumda derleyici, uyanmayan herhangi 
bir return ifadesini açýkça belirtilen dönüþ türüne örtük olarak dönüþtürmeye çalýþacaktýr), ya da tüm return ifadelerinizi açýkça ayný türe 
dönüþtürürsünüz. Yukarýdaki örnekte, ikinci seçenek 5'i 5.0'a deðiþtirerek gerçekleþtirilebilir, ancak static_cast, literat olmayan türler için de 
kullanýlabilir.

Auto dönüþ türü kullanan fonksiyonlarýn büyük bir dezavantajý, bu tür fonksiyonlarýn kullanýlmadan önce tamamen tanýmlanmýþ olmalarý gerekliliðidir 
(bir ileri bildirim yeterli deðildir). Örneðin:

                        #include <iostream>

                        auto foo();

                        int main()
                        {
                            std::cout << foo() << '\n'; // Bu noktada derleyici sadece bir ileri yönlü tanýmlama görmekte

                            return 0;
                        }

                        auto foo()
                        {
                            return 5;
                        }
Yazarýn bilgisayarýnda, bu þu derleme hatasýný verir:
                        error C3779: 'foo': a function that returns 'auto' cannot be used before it is defined.

Bu mantýklý: bir ileri bildirim, derleyicinin fonksiyonun dönüþ türünü çýkarmak için yeterli bilgiye sahip olmamasý anlamýna gelir. Bu, normalde 
auto döndüren fonksiyonlarýn genellikle tanýmlandýklarý dosya içindeki içeriden çaðrýlabilir olduðu anlamýna gelir.

Nesneler için tür çýkarýmý kullanýlýrken, baþlatýcý her zaman ayný ifadenin bir parçasý olarak bulunur, bu nedenle hangi türün çýkarýlacaðýný 
belirlemek genellikle aþýrý yük oluþturmaz. Fonksiyonlar için durum böyle deðildir - bir fonksiyonun prototipine bakýldýðýnda, fonksiyonun hangi
türü döndürdüðünü belirlemek için yardýmcý olacak bir baðlam yoktur. Ýyi bir programlama IDE'si, fonksiyonun çýkarýlan türünü açýkça göstermelidir,
ancak buna eriþim olmadýðýnda, bir kullanýcýnýn gerçekten fonksiyon gövdesine inmesi gerekebilir. Hatalar yapma olasýlýðý daha yüksektir. Ve bu tür
fonksiyonlarýn ileri bildirimde bulunamamasý, çoklu dosya içeren programlarda kullanýlabilirliklerini sýnýrlar.

*** BEST -> Normal fonksiyonlar için otomatik tür çýkarýmý yerine açýk dönüþ türlerini tercih edin.

Geriye dönük dönüþ türü sözdizimi
---------------------------------

auto anahtar kelimesi, geriye dönük bir sözdizimi kullanarak fonksiyonlarý bildirmek için de kullanýlabilir, burada dönüþ türü geri kalan
fonksiyon prototipi sonrasýnda belirtilir.

Aþaðýdaki fonksiyonu düþünün:

                        int add(int x, int y)
                        {
                            return (x + y);
                        }
Geriye dönük sözdizimi kullanarak, bu eþdeðer olarak þu þekilde yazýlabilir:

                        auto add(int x, int y) -> int
                        {
                          return (x + y);
                        }

Bu durumda, auto tür çýkarýmý gerçekleþtirmiyor; sadece geriye dönük bir dönüþ türü kullanma sözdiziminin bir parçasýdýr.

Bunu neden kullanmak istersiniz?

Bir güzel yaný da tüm fonksiyon adlarýnýzýn hizalanmasýný saðlamasýdýr:

                        auto add(int x, int y) -> int;
                        auto divide(double x, double y) -> double;
                        auto printSomething() -> void;
                        auto generateSubstring(const std::string &s, int start, int len) -> std::string;

Geriye dönük dönüþ türü sözdizimi, C++'ýn bazý geliþmiþ özellikleri için de gereklidir, örneðin lambda ifadeleri (bu, 20.6
dersinde kapsayacaðýmýz anonim fonksiyonlara bir giriþtir).

Þu an için, geriye dönük dönüþ türü sözdizimine ihtiyaç duyulan durumlar dýþýnda, geleneksel fonksiyon dönüþ türü sözdizimini 
kullanmaya devam etmenizi öneririz.

Tür çýkarýmý fonksiyon parametre türleri için kullanýlamaz
----------------------------------------------------------
Tür çýkarýmýný öðrenen birçok yeni programcý, þöyle bir þey denemeye çalýþýr:

                        #include <iostream>

                        void addAndPrint(auto x, auto y)
                        {
                            std::cout << x + y << '\n';
                        }

                        int main()
                        {
                            addAndPrint(2, 3); // Durum 1: addAndPrint fonksiyonunu int parametreleriyle çaðýrma
                            addAndPrint(4.5, 6.7); // Durum 2: addAndPrint fonksiyonunu double parametreleriyle çaðýrma

                            return 0;
                        }


Maalesef, tür çýkarýmý fonksiyon parametreleri için çalýþmaz ve C++20'den önce yukarýdaki program derlenmez (auto türüne sahip olamayan bir hata
alýrsýnýz).

C++20'de, auto anahtar kelimesi yukarýdaki programýn derlenmesine ve doðru çalýþmasýna izin vermek üzere geniþletildi - ancak bu durumda auto, tür 
çýkarýmýný çaðýrmýyor. Bunun yerine, aslýnda bu tür durumlarý ele almak üzere tasarlanmýþ bir özellik olan "fonksiyon þablonlarý"ný tetikliyor.
*/