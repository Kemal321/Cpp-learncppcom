
#include <iostream>

int main()
{
    return 0;
}
/*
                                                    Implicit Type Dönüþümü

Tip dönüþümüne giriþ
--------------------
Bir nesnenin deðeri, bir dizi bit olarak saklanýr ve nesnenin veri türü, derleyiciye bu bitlerin anlamlý deðerlere nasýl çevrileceðini belirtir. Farklý
veri tipleri, ayný sayýyý farklý þekillerde temsil edebilir. Örneðin, tam sayý deðeri 3, ikili olarak 0000 0000 0000 0000 0000 0000 0000 0011 olarak 
saklanabilirken, kayan noktalý sayý deðeri 3.0 ikili olarak 0100 0000 0100 0000 0000 0000 0000 0000 olarak saklanabilir.

* Bu þekilde bir þey yaptýðýmýzda neler olur?

                    float f{ 3 }; // tam sayý 3 ile kayan noktalý deðiþkeni baþlat

Bu durumda, derleyici sadece int deðeri 3'ü float deðiþkeni f için ayrýlan belleðe kopyalayamaz. Bunun yerine, tam sayý deðeri 3'ü karþýlýk gelen
kayan noktalý deðer 3.0'a dönüþtürmesi gerekir ki bu deðer daha sonra f için ayrýlan bellekte depolanabilir.

Bir deðeri farklý bir türden baþka bir türe dönüþtürme sürecine "dönüþüm" denir.

Dönüþümler, dönüþtürülen deðeri veya türü deðiþtirmez. Bunun yerine, dönüþümün bir sonucu olarak istenen türde yeni bir deðer oluþturulur.

Tür dönüþümleri iki þekilde çaðrýlabilir: ya dolaylý olarak (derleyici tarafýndan ihtiyaç duyulduðunda) ya da açýkça (programcý tarafýndan istendiðinde)
Bu derste dolaylý tür dönüþümünü ele alacaðýz ve önümüzdeki 10.6 dersinde açýk tür dönüþümlerini (casting) ve static_cast'ý iþleyeceðiz.

Dolaylý tür dönüþümü (ayný zamanda otomatik tür dönüþümü veya zorlamak olarak da adlandýrýlýr), bir veri türü istendiðinde ancak farklý bir veri türü 
saðlandýðýnda derleyici tarafýndan otomatik olarak gerçekleþtirilir. C++'taki tür dönüþümlerinin büyük çoðunluðu dolaylý tür dönüþümleridir. Örneðin, 
dolaylý tür dönüþümü aþaðýdaki durumlarýn hepsinde gerçekleþir:

Bir deðiþkeni farklý bir veri türündeki bir deðerle baþlatmak (veya bir deðer atamak) istendiðinde:

                    double d{ 3 }; // int deðeri 3, double türüne dolaylý olarak dönüþtürülüyor
                    d = 6; // int deðeri 6, double türüne dolaylý olarak dönüþtürülüyor

Dönüþ deðerinin türü, fonksiyonun ilan edilmiþ dönüþ türünden farklý olduðunda:

                    float doSomething()
                    {
                        return 3.0; // double deðeri 3.0, float türüne dolaylý olarak dönüþtürülüyor
                    }

Farklý türlerdeki operandlarý kullanýrken belirli ikili operatörler ile:

                    double division{ 4.0 / 3 }; // int deðeri 3, double türüne dolaylý olarak dönüþtürülüyor

                    if (5) // int deðeri 5, bool türüne dolaylý olarak dönüþtürülüyor
                    {
                    }

Farklý türlerdeki operandlarý kullanýrken belirli ikili operatörler ile:

                    void doSomething(long l)
                    {
                    }

                    doSomething(3); // int deðeri 3, long türüne dolaylý olarak dönüþtürülüyor

Tür Dönüþümü Çaðrýldýðýnda: Ne Olur ? 
-------------------------------------

Bir tür dönüþümü çaðrýldýðýnda (hem dolaylý olarak hem de açýkça), derleyici mevcut türden istenen türe deðeri dönüþtürüp dönüþtüremeyeceðini
belirleyecektir. Eðer geçerli bir dönüþüm bulunabilirse, derleyici istenen türde yeni bir deðer üretecektir. Unutulmamalýdýr ki tür dönüþümleri, 
dönüþtürülen deðerin deðerini veya türünü deðiþtirmez.

Eðer derleyici uygun bir dönüþüm bulamazsa, derleme hatasý ile baþarýsýz olacaktýr. Tür dönüþümleri birçok nedenden dolayý baþarýsýz olabilir. 
Örneðin, derleyici bir deðeri orijinal tür ile istenen tür arasýnda nasýl dönüþtüreceðini bilemeyebilir. Diðer durumlarda, ifadeler belirli
türlerdeki dönüþümleri yasaklayabilir. Örneðin:

                    int x { 3.5 }; // Ayraçla baþlatma, veri kaybýna neden olan dönüþümleri engeller

Ayrýca, derleyici bir deðeri baþka bir türe dönüþtürebileceði birkaç olasý dönüþüm arasýndan hangisinin en iyi olduðunu belirleyemeyebilir.
Bunun örneklerini 10.12 dersinde göreceðiz - Fonksiyon aþýrý yükleme ( overloading ) çözümleme ve belirsiz eþleþmeler.

Peki, derleyici bir deðeri bir türden baþka bir türe dönüþtürebilip dönüþtüremeyeceðini nasýl belirler?

Standart Dönüþümler
-------------------

C++ dil standardý, farklý temel türlerin (ve bazý durumlarda bileþik türlerin) diðer türlere nasýl dönüþtürülebileceðini tanýmlar. Bu dönüþüm
kurallarýna standart dönüþümler denir.

Standart dönüþümler genel olarak 4 kategoriye ayrýlabilir, her biri farklý türlerde dönüþümleri kapsar:

* - Sayýsal yükseltmeler (10.2 dersinde ele alýnmýþtýr - Kayan nokta ve tamsayý yükseltmeleri)
* - Sayýsal dönüþümler (10.3 dersinde ele alýnmýþtýr - Sayýsal dönüþümler)
* - Aritmetik dönüþümler (10.5 dersinde ele alýnmýþtýr - Aritmetik dönüþümler)
* - Diðer dönüþümler (bu, çeþitli iþaretçi ve referans dönüþümlerini içerir)

Bir tür dönüþümü gerektiðinde, derleyici, deðeri istenen türe dönüþtürmek için kullanabileceði standart dönüþümleri kontrol eder. Derleyici, 
dönüþüm sürecinde sýfýr, bir veya daha fazla standart dönüþümü uygulayabilir.

Ayrýca...

Sýfýr dönüþümlü bir tür dönüþümü nasýl gerçekleþir? Örneðin, int ve long türlerinin ayný boyuta ve aralýða sahip olduðu mimarilerde, her iki 
türün deðerlerini temsil etmek için ayný bit dizisi kullanýlýr. Bu nedenle, bu türler arasýnda bir deðeri dönüþtürmek için gerçek bir dönüþüm 
gerekmez - deðer basitçe kopyalanabilir.

Tür dönüþümlerinin nasýl çalýþtýðýný açýklayan tam kural seti hem uzun hem de karmaþýktýr ve çoðu zaman tür dönüþümleri "sadece çalýþýr". Bir
sonraki derste, tür dönüþümleri hakkýnda bilmeniz gereken en önemli konularý ele alacaðýz. Nadir durumlar için daha ayrýntýlý bilgi gerekiyorsa,
tam kurallar, dolaylý dönüþümler için teknik referans belgelerinde ayrýntýlý olarak açýklanmýþtýr.

Hadi baþlayalým!
*/
/*
10.2 — Standart Dönüþümler 1- Kayan nokta ve tamsayý yükseltmeleri
------------------------------------------------------------------

4.3 dersinde, C++'ýn her temel tür için minimum boyut garantileri olduðunu belirttik. Ancak, bu türlerin gerçek boyutu derleyici ve mimariye baðlý
olarak deðiþebilir.  Bu deðiþkenlik, int ve double veri türlerinin performansý maksimize edecek þekilde bir mimariye göre boyutlandýrýlabilmesine
izin verilmiþtir. Örneðin, 32-bit bir bilgisayar genellikle bir seferde 32 bit veriyi iþleyebilir. Bu durumlarda, bir int genellikle 32 bit 
geniþliðinde ayarlanýr, çünkü bu, CPU'nun iþlem yaptýðý verinin "doðal" boyutudur (ve muhtemelen en performanslý olanýdýr).

Bir hatýrlatma

Bir veri türünün kullandýðý bit sayýsýna geniþlik (width) denir. Daha geniþ bir veri türü, daha fazla bit kullanýrken, daha dar (narrower) bir veri
türü daha az bit kullanýr.

Ancak 32-bit bir CPU'nun bir char gibi 8-bit veya 16-bit bir deðeri deðiþtirmesi gerektiðinde ne olur? Bazý 32-bit iþlemciler (örneðin, 32-bit x86 
iþlemciler) 8-bit veya 16-bit deðerleri doðrudan iþleyebilir. Ancak, bunu yapmak genellikle 32-bit deðerleri iþlemekten daha yavaþtýr! Diðer 32-bit
iþlemciler (örneðin, 32-bit PowerPC iþlemcileri), yalnýzca 32-bit deðerler üzerinde çalýþabilir ve daha dar deðerleri iþlemek için ek hilelere ihtiyaç 
vardýr.


Sayýsal Yükseltme - Numeric Promotions 
--------------------------------------

C++, geniþ bir mimari yelpazesi üzerinde taþýnabilir ve performanslý olacak þekilde tasarlandýðýndan, dil tasarýmcýlarý belirli bir CPU'nun, o CPU'nun
doðal veri boyutundan daha dar deðerleri verimli bir þekilde iþleyebileceðini varsaymak istememiþtir.

Bu zorluðu ele almaya yardýmcý olmak için, C++, numeric promotions olarak adlandýrýlan bir tür dönüþüm kategorisi tanýmlar. Numeric promotion, belirli
daha dar sayýsal türlerin (örneðin char) genellikle int veya double gibi daha geniþ sayýsal türlere dönüþtürülmesidir ve bu türler daha verimli bir
þekilde iþlenebilir ve taþma olasýlýðý daha düþüktür.

Tüm numeric promotions deðeri koruyucudur, yani dönüþtürülen deðer her zaman kaynak deðerine eþit olacaktýr (sadece farklý bir türe sahip olacaktýr).
Kaynak türün tüm deðerleri hedef türde tam olarak temsil edilebildiði için, deðeri koruyucu dönüþümler "güvenli dönüþümler" olarak adlandýrýlýr.

Promotion lar ( Yükseltmeler ) güvenli olduðundan, derleyici ihtiyaç duyduðunda serbestçe
numeric promotion'ý kullanacak ve bunu yaparken bir uyarý çýkarmayacaktýr.

* Sayýsal yükseltme ( Numeric Promotion), tekrarý azaltýr.
*---------------------------------------------------------

Sayýsal promosyon ayný zamanda baþka bir sorunu da çözer. Bir int türündeki bir deðeri yazdýrmak için bir iþlev yazmak istediðinizi düþünün:

                        #include <iostream>

                        void printInt(int x)
                        {
                            std::cout << x << '\n';
                        }

Bu basit bir çözüm olabilir, ancak ayný zamanda short veya char türünde bir deðeri de yazdýrabilmek istersek ne olur? Tür dönüþümleri yoksa, short 
için farklý bir yazdýrma iþlevi ve char için baþka bir iþlev yazmak zorunda kalýrdýk. Ve unsigned char, signed char, unsigned short, wchar_t,
char8_t, char16_t ve char32_t için baþka bir versiyonu unutmayýn! Bu hýzla yönetilemez hale gelir.

Ýþte burada sayýsal yükseltme devreye giriyor: int ve/veya double parametrelere sahip fonksiyonlar yazabiliriz 
(yukarýdaki printInt() fonksiyonu gibi). Ayný kod daha sonra sayýsal olarak promosyon yapýlabilen argüman türleri ile çaðrýlabilir,
böylece fonksiyon parametrelerinin türleriyle eþleþebilir.

Sayýsal yükseltme kategorileri
------------------------------

Sayýsal yükseltme kurallarý, iki alt kategoriye ayrýlýr: tamsayý yükseltmeleri ve kayan nokta yükseltmeleri. Sadece bu kategorilerde listelenen
dönüþümler, sayýsal yükseltmeler olarak kabul edilir.

Kayan nokta yükseltmeleri
-------------------------


Daha kolay olaný ile baþlayalým.

Kayan nokta promosyon kurallarý kullanýlarak, float türündeki bir deðer double türündeki bir deðere dönüþtürülebilir.

Bu þu anlama gelir, bir double alan bir fonksiyon yazabiliriz ve ardýndan bu fonksiyonu hem bir double hem de bir float deðeri ile çaðýrabiliriz:

                        #include <iostream>

                        void printDouble(double d)
                        {
                            std::cout << d << '\n';
                        }

                        int main()
                        {
                            printDouble(5.0); // Dönüþüm gerekmez
                            printDouble(4.0f); // Floattan Doubleye sayýsal yükseltme gerekir. 

                            return 0;
                        }

printDouble() fonksiyonuna yapýlan ikinci çaðrýda, float 4.0f literalý double'a yükseltme yapýlýr, böylece argümanýn türü iþlev parametresinin
türüyle eþleþir.

Tam sayý yükseltmeleri
----------------------

Tam sayý yükseltme kurallarý daha karmaþýktýr.

Tam sayý yükseltme kurallarý kullanýlarak þu dönüþümler yapýlabilir:

*- signed char veya signed short, int'e yükseltilebilir.
*- unsigned char, char8_t ve unsigned short, int türü tüm aralýðý tutabiliyorsa int'e, aksi takdirde unsigned int'e yükseltilebilir.
*- Eðer char varsayýlan olarak signed ise, yukarýdaki signed char yükseltme kurallarýný takip eder. Varsayýlan olarak unsigned ise, yukarýdaki 
   unsigned char yükseltme kurallarýný takip eder.
*- bool, int'e yükseltilebilir, false 0 olur ve true 1 olur.

8 bitlik bir byte ve genellikle 4 bayt veya daha büyük bir int boyutu varsayýldýðýnda (bugünlerde tipik olan), yukarýdaki açýklamalar genellikle bool,
char, signed char, unsigned char, signed short ve unsigned short'un hepsinin int'e yükseltilmesi anlamýna gelir.

Daha az sýk kullanýlan birkaç baþka sayýsal yükseltme kuralý da bulunmaktadýr. Bunlar 
https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion adresinde bulunabilir.

Çoðu durumda, bu bize bir int parametre alan bir fonksiyon yazmamýza ve ardýndan çeþitli sayýsal türlerle kullanmamýza izin verir. Örneðin:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        printInt(2);

                        short s{ 3 }; // short literal suffix yok, bu yüzden bunun için bir deðiþken kullanacaðýz
                        printInt(s); // short'un int'e sayýsal yükseltilmesi

                        printInt('a'); // char'ýn int'e sayýsal yükseltilmesi
                        printInt(true); // bool'un int'e sayýsal yükseltilmesi

                        return 0;
                    }

Burada dikkate deðer iki þey bulunmaktadýr. Ýlk olarak, bazý mimarilerde (örneðin 2 bayt int'lerle) bazý unsigned tamsayý tiplerinin int yerine
unsigned int'e yükseltilmesi mümkündür.

Ýkinci olarak, bazý daha dar unsigned tipler (örneðin unsigned char), daha büyük iþaretli tiplere (örneðin int) yükseltilebilir. Bu nedenle, 
integral yükseltme deðeri korurken, türün iþaretli olup olmama durumunu (signed/unsigned) zorunlu olarak korumaz.

Tüm geniþleme dönüþümleri sayýsal yükseltmeler deðildir
-------------------------------------------------------

Bazý geniþleme tür dönüþümleri (örneðin char'dan short'a veya int'ten long'a) C++'da sayýsal yükseltmeler olarak kabul edilmez (bunlar yakýnda ele 
alacaðýmýz sayýsal dönüþümlerdýr, 10.3 dersi -- Sayýsal dönüþümler). Bu, bu tür dönüþümlerin daha küçük tipleri daha verimli bir þekilde iþleyebilen 
daha büyük tiplere dönüþtürme amacýna hizmet etmediði içindir.

Ayýrým genellikle akademiktir. Ancak, belirli durumlarda derleyici, sayýsal yükseltmeleri sayýsal dönüþümler üzerinde tercih edebilir. Fonksiyon
aþýrý yük çözünürlüðünü ele aldýðýmýzda (yakýnda ele alýnacak olan 10.12 dersinde -- Fonksiyon aþýrý yük çözünürlüðü ve belirsiz eþleþmeler),
bu durumun fark yarattýðý örnekleri göreceðiz.

10.2 — Standart Dönüþümler 1- Sayýsal Dönüþümler
------------------------------------------------

C++, baþka bir sayýsal tür dönüþümü kategorisini destekler, buna sayýsal dönüþümler denir. Bu sayýsal dönüþümler, temel tipler arasýndaki 
ek tip dönüþümlerini kapsar.


Numeric promotion kurallarý (10.2 -- Ondalýk Nokta ve Tamsayý Yükseltme) tarafýndan kapsanan herhangi bir tür dönüþümü bir sayýsal yükseltmedir, sayýsal bir dönüþüm deðildir.

Beþ temel sayýsal dönüþüm türü bulunmaktadýr.

1. Herhangi bir diðer integral türüne tamsayý türünden dönüþtürme (tamsayý yükseltmeleri hariç):
                        short s = 3;        // int'i short'a dönüþtür
                        long l = 3;         // int'i long'a dönüþtür
                        char ch = s;        // short'u char'a dönüþtür
                        unsigned int u = 3; // int'i unsigned int'e 

2. Ondalýk sayý türünü baþka bir ondalýk sayý türüne dönüþtürme (kayan noktalý sayý yükseltmeleri hariç):

                        float f = 3.0;       // double'ý float'a dönüþtür
                        long double ld = 3.0; // double'ý long double'a dönüþtür

3. Kayan noktalý sayý tiplerini her hangi bir tam sayý tipine dönüþtürme:
                        
                        int i = 3.5; // double'ý int'e dönüþtür

4. Bir tamsayý türünü herhangi bir ondalýk nokta türüne dönüþtürme:

                        double d = 3; // int'i double'a dönüþtür

5. Bir tamsayý türünü veya bir ondalýk sayý türünü bool'e dönüþtürme:

                        bool b1 = 3;    // int'i bool'e dönüþtür
                        bool b2 = 3.0;  // double'ý bool'e dönüþtür

Bir kenara not olarak...

Parantez baþlatma, bazý sayýsal dönüþümleri kesinlikle engellediði için (bunu bir sonraki derste daha ayrýntýlý olarak ele alacaðýz),
örnekleri basit tutmak için bu derste kopya baþlatmayý kullanýyoruz (bu tür kýsýtlamalarý içermeyen).

Güvenli ve Potansiyel Tehlikeli Dönüþümler
------------------------------------------

Her zaman deðeri koruyan (ve bu nedenle her zaman "güvenli" olan) bir sayýsal yükseltmenin aksine, bazý sayýsal dönüþümler belirli 
durumlarda deðeri korumaz. Bu tür dönüþümlere "güvensiz" denir (gerçekte "potansiyel olarak güvensiz" daha doðru bir terimdir, çünkü 
bu dönüþümler diðer durumlarda deðeri korur).

Sayýsal dönüþümler üç güvenlik kategorisinden birine girer:

1- Deðeri koruyan dönüþümler, hedef türün kaynak türdeki tüm deðerleri tam olarak temsil edebildiði güvenli sayýsal dönüþümlerdir.

Örneðin, int'ten long'a ve short'tan double'a olan dönüþümler güvenli dönüþümlerdir, çünkü kaynak deðer her zaman hedef türdeki eþdeðer bir deðere 
dönüþtürülebilir.

                        int main()
                        {
                            int n{ 5 };
                            long l = n;      // tamam, long deðeri 5 üretir

                            short s{ 5 };
                            double d = s;    // tamam, double deðeri 5.0 üretir

                            return 0;
                        }

Derleyiciler genellikle örtük deðeri koruyan dönüþümler için uyarý vermez.

Deðeri koruyan bir dönüþüm kullanýlarak dönüþtürülen bir deðer her zaman kaynak türüne geri dönüþtürülebilir ve bu, orijinal deðere eþdeðer bir
deðeri üretir:

                        #include <iostream>

                        int main()
                        {
                            int n = static_cast<int>(static_cast<long>(3)); // int 3'ü long'a ve geri dönüþtür
                            std::cout << n << '\n';                         // 3'ü yazdýrýr

                            char c = static_cast<char>(static_cast<double>('c')); // 'c'yi double'a çevir ve geri dönüþtür
                            std::cout << c << '\n';                               // 'c'yi yazdýrýr

                            return 0;
                        }


2- Yorumlama Dönüþümleri, sonucun kaynak türünün aralýðýnýn dýþýnda olabileceði potansiyel olarak güvensiz sayýsal dönüþümlerdýr. iþaretli/iþaretsiz
dönüþümler bu kategoriye girer.
Örneðin, bir iþaretli int'i iþaretsiz int'e dönüþtürdüðümüzde:

                        int main()
                        {
                            int n1{ 5 };
                            unsigned int u1{ n1 };  // tamam: unsigned int 5'e dönüþtürülecek (deðer korunur)

                            int n2{ -5 };
                            unsigned int u2{ n2 };  // hatalý: iþaretli int'in aralýðýnýn dýþýnda büyük bir tamsayý elde edilecek

                            return 0;
                        }

u1 durumunda, iþaretli int deðeri 5, iþaretsiz int deðeri 5'e dönüþtürülüyor. Bu durumda deðer korunur.

u2 durumunda, iþaretli int deðeri -5, iþaretsiz int'e dönüþtürülüyor. Çünkü iþaretsiz bir int negatif sayýlarý temsil edemez, sonuç
olarak büyük bir tamsayý deðeri elde edilir ve bu, iþaretli bir int'in aralýðýnýn dýþýnda kalýr. Bu durumda deðer korunmaz.

Bu tür deðer deðiþiklikleri genellikle istenmeyen sonuçlara yol açar ve genellikle programýn beklenmeyen veya uygulama tanýmlý davranýþ 
sergilemesine neden olabilir.

Uyarý

Yeniden yorumlama dönüþümleri potansiyel olarak güvensiz olmalarýna raðmen, çoðu derleyici genellikle varsayýlan olarak iþlevsiz iþaretli/iþaretsiz 
dönüþüm uyarýlarýný devre dýþý býrakýr.

Bu, modern C++'ýn bazý alanlarýnda (örneðin, standart kütüphane dizileri ile çalýþýrken) iþaretli/imsiz dönüþümlerin kaçýnýlmaz olabileceði anlamýna
gelir. Ve pratikte, bu tür dönüþümlerin çoðu aslýnda bir deðer deðiþikliðine neden olmaz. Bu nedenle, bu uyarýlarý etkinleþtirmek, aslýnda sorun 
olmayan iþaretli/imsiz dönüþümler için çok sayýda sahte uyarýya neden olabilir (geçerli uyarýlarý gölgede býrakabilir).

Eðer bu tür uyarýlarý devre dýþý býrakmayý seçerseniz, bu tür türler arasýndaki istenmeyen dönüþümlere karþý dikkatli olun (özellikle bir argümaný,
ters iþarete sahip bir parametre alan bir iþleme geçirirken).

Yeniden yorumlama dönüþümleri kullanýlarak dönüþtürülen deðerler, kaynak türüne geri dönüþtürülebilir, bu da baþlangýçta elde edilen deðeri kaynak 
türün aralýðýndaki bir deðere eþdeðer hale getirir (baþlangýçta yapýlan dönüþüm kaynak türün aralýðýnýn dýþýnda bir deðer üretse bile).

                            #include <iostream>

                            int main()
                            {
                                int u = static_cast<int>(static_cast<unsigned int>(-5)); // '-5' deðerini iþaretsiz tamsayýya dönüþtür ve geri dönüþtür
                                std::cout << u << '\n'; // -5'i yazdýrýr

                                return 0;
                            }


3 - Kayýplý dönüþümler, dönüþüm sýrasýnda bazý verilerin kaybedilebileceði potansiyel olarak güvensiz sayýsal dönüþümlerdir.

Örneðin, double tipinden int tipine yapýlan bir dönüþüm, veri kaybýna neden olabilecek bir dönüþümdür:

                            int i = 3.0; // geçerli: int deðeri 3'e dönüþtürülecek (deðer korunur)
                            int j = 3.5; // veri kaybý: int deðeri 3'e dönüþtürülecek (kesirli deðer 0.5 kaybolacak)

Double'dan floata yapýlan dönüþüm de veri kaybýna neden olabilir:

                            float f = 1.2;        // geçerli: float deðeri 1.2'ye dönüþtürülecek (deðer korunur)
                            float g = 1.23456789; // veri kaybý: float 1.23457'ye dönüþtürülecek (kesirli deðer kaybolur)

Veri kaybý yaþamýþ bir deðeri kaynak türüne geri dönüþtürmek, orijinal deðerden farklý bir deðere yol açacaktýr:

                            #include <iostream>

                            int main()
                            {
                                double d { static_cast<double>(static_cast<int>(3.5)) }; // double 3.5'i int'e dönüþtür ve geri double'a dönüþtür 
                                                                                         // (veri kaybý)
                                std::cout << d << '\n'; // 3 yazdýrýr

                                double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // double 1.23456789'u floata dönüþtür ve geri
                                                                                                   // double'a dönüþtür (hassasiyet kaybý)
                                std::cout << d2 << '\n'; // 1.23457 yazdýrýr

                                return 0;
                            }

Örneðin, double deðeri 3.5'in int deðeri 3'e dönüþtürülmesi durumunda, kesirli bileþen olan 0.5 kaybolur. 3, double'a geri dönüþtürüldüðünde sonuç 
3.0 olur, 3.5 deðil.

Derleyiciler genellikle çalýþma zamanýnda açýkça belirgin bir veri kaybý dönüþümü yapýlacaksa bir uyarý (veya bazý durumlarda hata) bildirir.

Uyarý

Bazý dönüþümler, platforma baðlý olarak farklý kategorilere girebilir.

Örneðin, int'ten double'a dönüþ genellikle güvenli bir dönüþümdür, çünkü int genellikle 4 bayt ve double genellikle 8 bayt olduðu için,
bu tür sistemlerde tüm olasý int deðerleri bir double olarak temsil edilebilir. Ancak int ve double'ýn her ikisinin de 8 bayt olduðu mimariler
vardýr. Bu tür mimarilerde int'ten double'a dönüþ, bir veri kaybý dönüþümüdür!

Bunu, bir long long deðerini (en az 64 bit olmalýdýr) double'a dönüþtürerek ve geri dönüþtürerek gösterebiliriz:

                            #include <iostream>

                            int main()
                            {
                                std::cout << static_cast<long long>(static_cast<double>(10000000000000001LL));

                                return 0;
                            }

                            Bu þu þekilde yazdýrýlýr:

                            10000000000000000
                            Son basamaðýmýzýn kaybolduðuna dikkat edin!


Sayýsal dönüþümlerle ilgili özel kurallar karmaþýk ve sayýca fazla olduðu için, iþte hatýrlamanýz gereken en önemli þeyler:

Her durumda, bir deðeri, o deðeri desteklemeyen bir türüne dönüþtürmek muhtemelen beklenmeyen sonuçlara yol açacaktýr. Örneðin:

                            int main()
                            {
                                int i{ 30000 };
                                char c = i; // chars have range -128 to 127

                                std::cout << static_cast<int>(c) << '\n';

                                return 0;
                            }

Bu örnekte, büyük bir tamsayýyý bir char türündeki bir deðiþkene atadýk (ki bu türün aralýðý -128 ile 127 arasýndadýr). Bu, char'ýn taþmasýna 
neden olur ve beklenmeyen bir sonuç üretir:

                            Çýktý -> 48

Unutmayýn ki taþma iþlemi, iþaretsiz deðerler için tanýmlýdýr ve iþaretli deðerler için tanýmsýz davranýþa neden olur.

Ayný ailedeki daha büyük bir türden daha küçük bir türe dönüþtürme genellikle deðerin daha küçük türün aralýðýna sýðdýðý sürece çalýþacaktýr. Örneðin:
        
                            int i{ 2 };
                            short s = i; // int -> short dönüþümü
                            std::cout << s << '\n';

                            double d{ 0.1234 };
                            float f = d;
                            std::cout << f << '\n';

Bu beklenen sonucu üretir:
                            2
                            0.1234   -> Görüldüðü üzere çalýþýyor. 

Ondalýk sayý deðerleri için, daha küçük bir türdeki hassasiyet kaybýndan dolayý bazý yuvarlama olaylarý meydana gelebilir. Örneðin:

                            float f = 0.123456789; 
                            // double deðeri 0.123456789 9 önemli rakam içerir, ancak float türü yalnýzca yaklaþýk olarak 7 rakamý destekleyebilir
                            std::cout << std::setprecision(9) << f << '\n'; // iomanip baþlýk dosyasýnda tanýmlý olan std::setprecision

Bu durumda, float türünün bir double kadar hassasiyeti tutamadýðýný görüyoruz:
                            0.123456791

Bir tamsayýyý bir kayan nokta sayýsýna dönüþtürmek genellikle deðerin kayan nokta türünün aralýðýna sýðmasý durumunda çalýþýr. Örneðin:

                            int i{ 10 };
                            float f = i;
                            std::cout << f << '\n';

Beklenen çýktýyý üretir: 
                            10

Bir kayan nokta sayýsýndan bir tamsayýya dönüþtürmek, deðerin tamsayý aralýðýna sýðmasý durumunda çalýþýr, ancak herhangi bir kesirli deðer kaybolur.
Örneðin:
                            int i = 3.5;
                            std::cout << i << '\n';

Bu örnekte, kesirli deðer (.5) kaybolur, þu sonucu býrakýr:
                            3

Sayýsal dönüþüm kurallarý korkutucu gibi görünebilir, ancak gerçekte derleyici genellikle tehlikeli bir þey yapmaya çalýþtýðýnýzda sizi uyaracaktýr
(bazý iþaretli/iþaretsiz dönüþümleri hariç tutarak).
*/
/*

10.4 — Daraltýcý dönüþümler, liste baþlatma ve constexpr baþlatýcýlar
---------------------------------------------------------------------


C++ dilinde, daraltýcý dönüþüm, hedef türün kaynak türün tüm deðerlerini tutamayabileceði potansiyel olarak güvenli olmayan bir sayýsal dönüþümdür.

Aþaðýdaki dönüþümler daraltýcý olarak tanýmlanmýþtýr:

*- Bir kayan nokta türünden bir tam sayý türüne.
*- Bir kayan nokta türünden daha dar veya daha düþük bir sýralamalý kayan nokta türüne, dönüþtürülen deðer constexpr ise ve hedef türün aralýðýnda ise
   (hedef tür, sayýnýn önemli basamaklarýnýn tamamýný depolamýyorsa bile).
*- Bir tam sayýdan bir kayan nokta türüne, dönüþtürülen deðer constexpr ise ve deðer hedef türde tam olarak depolanabiliyorsa.
*- Bir tam sayý türünden, orijinal türün tüm deðerlerini temsil edemeyen baþka bir tam sayý türüne, dönüþtürülen deðer constexpr ise ve deðer hedef
   türde tam olarak depolanabiliyorsa. Bu, geniþten daraya tam sayý dönüþümlerini, ayný zamanda iþaret dönüþümlerini (iþaretli türden iþaretsiz türe 
   veya tersi) kapsar.

Genellikle, bilinçsiz daraltýcý dönüþümler derleyici uyarýlarýna yol açacaktýr, istisna olarak iþaretli/iþaretsiz dönüþümler (derleyicinizin nasýl
yapýlandýrýldýðýna baðlý olarak uyarý üretebilir veya üretmeyebilir).

Bilinçsiz daraltýcý dönüþümler mümkün olduðunca kaçýnýlmasý gereken bir durumdur, çünkü potansiyel olarak güvensizdir ve bu nedenle potansiyel 
hatalarýn kaynaðýdýr.

*** BEST -> Güvenli olmadýklarý ve hatalarýn kaynaðý olduklarý için mümkünse bilinçsiz daraltýcý dönüþümlerden kaçýnýn.

Bilinçli daraltýcý dönüþümleri kasýtlý olarak ( explicit ) yapýn
---------------------------------------------------------------- 

Narrowing conversions her zaman kaçýnýlamaz; özellikle fonksiyon çaðrýlarý için bu durum geçerlidir, burada fonksiyon parametresi ve argümanýnýn 
uyumsuz türlere sahip olmasý ve daraltýcý bir dönüþüm gerektirmesi mümkündür.

Bu tür durumlarda, daraltýcý bir dönüþümü açýkça belirtmek için implicit (bilinçsiz) bir daraltýcý dönüþümü static_cast kullanarak explicit (açýk) 
bir daraltýcý dönüþüme çevirmek iyi bir fikirdir. Bu, daraltýcý dönüþümün kasýtlý olduðunu belgelemeye yardýmcý olur ve ayrýca derleyici uyarýlarýný 
veya hatalarýný bastýrýr.

Örnek olarak:

                    void someFcn(int i)
                    {
                    }

                    int main()
                    {
                    double d{ 5.0 };

                    someFcn(d); // hatalý: bilinçsiz daraltýcý dönüþüm derleyici uyarýsý üretecektir

                    // iyi: daraltýcý dönüþümün kasýtlý olduðunu derleyiciye açýkça belirtiyoruz
                    someFcn(static_cast<int>(d)); // uyarý üretilmez

                    return 0;
                    }

*** BEST -> Eðer daraltýcý bir dönüþüm yapmanýz gerekiyorsa, static_cast kullanarak onu açýk bir dönüþüme çevirin.

Parantez baþlatma (brace initialization) daraltýcý dönüþümleri engeller (bu baþlatma biçiminin tercih edilme nedenlerinden biridir) ve böyle 
bir dönüþüm yapmaya çalýþmak derleme hatasý üretecektir Örneðin:

                    int main()
                    {
                        int i { 3.5 }; // won't compile

                        return 0;
                    }

Visual studio þu hatayý üretir:
                    error C2397: conversion from 'double' to 'int' requires a narrowing conversion

Eðer gerçekten bir parantez baþlatma içinde daraltýcý bir dönüþüm yapmak istiyorsanýz, daraltýcý dönüþümü açýk bir dönüþüme çevirmek için static_cast
kullanýn:

                    int main()
                    {
                        double d { 3.5 };

                        // static_cast<int>, double'ý int'e çevirir, i'yi int sonucuyla baþlatýr
                        int i { static_cast<int>(d) };

                        return 0;
                    }

Bazý constexpr dönüþümler daraltýcý olarak kabul edilmez. Bir daraltýcý dönüþümün kaynak deðeri çalýþma zamanýna kadar bilinmiyorsa, dönüþümün
sonucu da çalýþma zamanýna kadar belirlenemez. Bu tür durumlarda, daraltýcý dönüþümün deðeri koruyup korumadýðý da çalýþma zamanýna kadar belirlenemez. Örneðin:

                    #include <iostream>

                    void print(unsigned int u) // not: unsigned
                    {
                        std::cout << u << '\n';
                    }

                    int main()
                    {
                        std::cout << "Enter an integral value: ";
                        int n{};
                        std::cin >> n; // 5 veya -5 girin
                        print(n);      // dönüþüm, deðeri koruyabilir veya korumayabilir

                        return 0;
                    }

Yukarýdaki programda, derleyici n için hangi deðerin girileceðini bilmez. print(n) çaðrýldýðýnda int'ten unsigned int'e olan dönüþüm o an 
gerçekleþir ve sonuçlar, n için girilen deðere baðlý olarak deðeri koruyabilir veya korumayabilir. Bu nedenle, iþaretsiz/iþaretli uyarýlarý
etkinleþtirilmiþ bir derleyici, bu durum için bir uyarý verecektir.

Ancak, çoðu daraltýcý dönüþüm tanýmýnýn baþýnda "unless the value being converted is constexpr and ..." ile baþlayan bir istisna maddesi 
olduðunu fark etmiþ olabilirsiniz. Örneðin, bir dönüþüm daraltýcýdýr ve "From an integral type to another integral type that cannot represent
all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type."
ifadesi ile belirtilir.

Bir daraltýcý dönüþümün kaynak deðeri constexpr olduðunda, dönüþtürülecek özel deðer derleyici tarafýndan bilinmelidir. Bu tür durumlarda, 
derleyici dönüþümü kendisi gerçekleþtirebilir ve ardýndan deðerin korunup korunmadýðýný kontrol edebilir. Eðer deðer korunmamýþsa, derleyici
hata ile derlemeyi durdurabilir. Deðer korunmuþsa, dönüþüm daraltýcý olarak kabul edilmez (ve derleyici, bunu güvenli olduðunu bilerek tamamen 
dönüþtürülmüþ sonuçla deðiþtirebilir).

Örneðin:

                    #include <iostream>

                    int main()
                    {
                        constexpr int n1{ 5 };   // not: constexpr
                        unsigned int u1 { n1 };  // tamam: dönüþüm, daraltýcý olmadýðý için sorun yok

                        constexpr int n2 { -5 }; // not: constexpr
                        unsigned int u2 { n2 };  // derleme hatasý: dönüþüm, deðerin deðiþmesi nedeniyle daraltýcýdýr

                        return 0;
                    }


"Orijinal türün tüm deðerlerini temsil edemeyen bir tamsayý türünden baþka bir tamsayý türüne dönüþüm, dönüþtürülen deðer constexpr ise ve deðeri 
hedef türde tam olarak depolanabiliyorsa daraltýcý deðildir" kuralýný yukarýdaki her iki dönüþüme de uygulayalým.

n1 ve u1 için, n1 bir int ve u1 bir unsigned int olduðundan, bu, orijinal türün tüm deðerlerini temsil edemeyen bir tamsayý türünden baþka bir 
tamsayý türüne dönüþümdür. Ancak n1 constexpr olduðu için ve deðeri 5, hedef türde (unsigned deðer 5 olarak) tam olarak depolanabildiði için, 
bu daraltýcý dönüþüm olarak kabul edilmez ve n1'i kullanarak u1'i liste baþlatma yapabiliriz.

n2 ve u2 için durumlar benzerdir. N2 constexpr olsa da, deðeri -5 hedef türde tam olarak temsil edilemez, bu nedenle bu daraltýcý bir dönüþüm
olarak kabul edilir ve liste baþlatma yaptýðýmýz için derleyici hata verecek ve derlemeyi durduracaktýr.

Ilginç bir þekilde, kayan nokta türünden tamsayý türüne yapýlan dönüþümlerde constexpr istisna maddesi bulunmamaktadýr. Bu nedenle, dönüþtürülecek 
deðer constexpr olsa ve hedef türün aralýðýna sýðsa bile, bu dönüþümler her zaman daraltýcý olarak kabul edilir:

                    int n { 5.0 }; // compile error: narrowing conversion

constexpr baþlatýcýlara sahip liste baþlatma ve bunlarýn özel durum maddeleri
-----------------------------------------------------------------------------
int veya double türünden olmayan nesneleri liste baþlatma iþlemlerinde son derece kullanýþlýdýr. Çünkü bir int veya double literali
(veya constexpr nesnesi) baþlatma deðeri kullanabiliriz.

Bu bize þunlardan kaçýnma imkaný tanýr:

*- Çoðu durumda literal eklerini kullanmak zorunda olmamak
*- Baþlatmalarýmýzý static_cast ile karmaþýk hale getirmemek
Örneðin:

                    int main()
                    {
                        // Soneklerle literalleri kullanmaktan kaçýnabiliriz
                        unsigned int u { 5 }; // uygun ( `5u` kullanmamýza gerek yok)
                        float f { 1.5 };      // uygun ( `1.5f` kullanmamýza gerek yok)

                        // static_cast kullanmaktan kaçýnabiliriz
                        constexpr int n{ 5 };
                        double d { n };       // uygun (burada static_cast'a ihtiyacýmýz yok)
                        short s { 5 };        // uygun (short için sonek yok, burada static_cast'a ihtiyacýmýz yok)
                            
                        return 0;
                    }

Bu, kopyalama ve doðrudan baþlatma ile de çalýþýr.

Dikkat edilmesi gereken bir husus: dar veya daha düþük sýralý bir kayan nokta türünü, hedef türün aralýðýnda bir constexpr deðeri ile baþlatmak, 
hedef türün deðeri kesin bir þekilde depolamayacak kadar hassasiyeti olmasa bile izin verilir!

Anahtar Ýpucu

Kayan nokta türleri þu sýrayla sýralanýr (büyükten küçüðe):

Long double
Double
Float
Bu nedenle, þuna benzer bir þey yasaldýr ve bir hata üretmeyecektir:

                        int main()
                        {
                            float f { 1.23456789 }; // Daraltýcý bir dönüþüm deðil, hatta hassasiyet kaybedilmiþ olsa bile!

                            return 0;
                        }

Ancak, bu durumda derleyiciniz hala bir uyarý verebilir (GCC ve Clang, -Wconversion derleme bayraðýný kullanýrsanýz uyarý verebilir).

10.5 — Aritmetik Dönüþümler
---------------------------

                        int x { 2 + 3 };

Bu durumda, operator+ çaðrýldýðýnda, iki operand da int türündedir. Her iki operand da ayný türde olduðundan, bu tür hesaplamayý gerçekleþtirmek ve 
sonucu döndürmek için kullanýlýr. Bu nedenle, 2 + 3 ifadesi int deðeri 5'e deðerlendirilecektir.

                        ??? y { 2 + 3.5 };

Bu durumda, operator+ bir tane int ve bir tane double türündeki operand ile çaðrýlýyor. Operatörün sonucu int, double veya belki tamamen farklý 
bir þey olarak dönmeli mi? Bir deðiþken tanýmlarken, onun hangi türde olduðunu seçebiliriz. Diðer durumlarda, örneðin std::cout << kullanýlýrken, 
hesaplamanýn deðeri çýktýnýn davranýþýný deðiþtirir.

C++'da, belirli operatörlerin operandlarýnýn ayný türde olmasýný gerektiren durumlar vardýr. Bu operatörlerden biri, farklý türlerdeki operandlarla 
çaðrýlýrsa, operandlardan biri veya her ikisi de, "usual arithmetic conversions" adlý bir kurallar kümesi kullanýlarak eþleþen tiplere örtülü olarak
dönüþtürülür.

Ayný türdeki operandlarý gerektiren operatörler
-----------------------------------------------

Ayný türdeki operandlarý gerektiren aþaðýdaki operatörler:

1- Ýkili aritmetik operatörler: +, -, *, /, %
2- Ýkili iliþkisel operatörler: <, >, <=, >=, ==, !=
3- Ýkili bitwise aritmetik operatörler: &, ^, |
4- Üçlü koþul operatörü ?: (beklenen tip bool türünde olan koþulu hariç)

Genel aritmetik dönüþüm kurallarý
---------------------------------


Genel aritmetik dönüþüm kurallarý oldukça basittir. Derleyicinin öncelikli bir tür listesi vardýr ve bu liste þuna benzer:

    ->> long double (en yüksek öncelik)
    ->> double
    ->> float
    ->> unsigned long long
    ->> long long
    ->> unsigned long
    ->> long
    ->> unsigned int
    ->> int (en düþük öncelik)
Sadece iki kural bulunmaktadýr:

1 -) En az bir operandýn türü öncelikli listede ise, daha düþük önceliðe sahip operand, daha yüksek önceliðe sahip operandýn türüne dönüþtürülür.
2 -) Aksi takdirde (her iki operandýn türü de listede deðilse), her iki operand da sayýsal olarak yükseltilir (bkz. 10.2 - Kayan nokta ve tam
     sayý yükseltme)


Bazý örnekler

operator+ iþlemi, operandlarýnýn ayný türe sahip olmasýný gerektiren operatörlerden biridir.

Aþaðýdaki örneklerde, sonuç türünü göstermek için <typeinfo> baþlýðýnda bulunan typeid operatörünü kullanacaðýz.

Ýlk olarak, bir int ve bir double ekleyelim:

                        #include <iostream>
                        #include <typeinfo> // for typeid()

                        int main()
                        {
                            int i{ 2 };
                            double d{ 3.5 };
                            std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // i + d nin type'ýný göster

                            return 0;
                        }

Bu durumda, double türündeki operand en yüksek önceliðe sahiptir, bu nedenle daha düþük öncelikli operand (int türünde) double deðeri 2.0'a 
dönüþtürülür. Daha sonra 2.0 ve 3.5 double deðerleri eklenerek double sonuç 5.5 elde edilir.

Yazarýn bilgisayarýnda, bu þu þekilde yazdýrýlýr:
                        double 5.5


Unutmayýn ki derleyiciniz, typeid.name()'in çýktýsýný belirlemekte serbest býrakýldýðýndan, bu biraz farklý bir þey gösterebilir.

Þimdi short türündeki iki deðeri ekleyelim:

                        #include <iostream>
                        #include <typeinfo> // typeid() için

                        int main()
                        {
                            short a{ 4 };
                            short b{ 5 };
                            std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // a + b nin type'ýný göster

                            return 0;
                        }

Çünkü her iki operand da öncelikli listede bulunmaz, her iki operand da int türüne integral yükseltmeye tabi tutulur. Ýki int'in toplamýnýn sonucu,
beklendiði gibi bir int'tir:
           -> çýktý:   int 9
                    
Ýmzalý ve Ýmzasýz Sorunlar
--------------------------

Bu öncelik sýrasý, iþaretli ve iþaretsiz deðerleri karýþtýrýrken bazý sorunlara neden olabilir. Örneðin, aþaðýdaki kodu inceleyin:

                        #include <iostream>
                        #include <typeinfo> // typeid() için

                        int main()
                        {
                            std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u nun anlamý 5 unsigned integer olarak davranýr. 

                            return 0;
                        }

Ýfade 5u - 10'in -5 olarak deðerlendirilmesini bekleyebilirsiniz çünkü 5 - 10 = -5. Ancak, iþte gerçekte ortaya çýkan:

                        unsigned int 4294967291

Ýmzasýz int operandýnýn daha yüksek önceliði olduðundan, int operandý bir iþaretsiz int'e dönüþtürülür. Ve çünkü -5 deðeri iþaretsiz bir int'in 
aralýðýnýn dýþýnda olduðu için, beklenmeyen bir sonuç elde ederiz.

Ýþte karþýt bir sonuç gösteren baþka bir örnek:

                        #include <iostream>

                        int main()
                        {
                            std::cout << std::boolalpha << (-3 < 5u) << '\n';

                            return 0;
                        }


5'in -3'ten daha büyük olduðu bize açýk olsa da, bu ifade deðerlendirildiðinde -3, 5'ten daha büyük olan büyük bir iþaretsiz int'e dönüþtürülür.
Bu nedenle, yukarýdaki ifade beklenen sonuç olan true yerine false yazdýrýr.

Bu, iþaretsiz tamsayýlarý kullanmaktan kaçýnmanýn temel nedenlerinden biridir - onlarý iþaretli tamsayýlarla aritmetik ifadelerde karýþtýrdýðýnýzda,
beklenmeyen sonuçlara karþý risk altýnda olursunuz. Ve derleyici muhtemelen uyarý bile vermez.

10.6 — Explicit tür dönüþümü (casting) and static_cast
------------------------------------------------------

Birçok yeni C++ programcýsý þöyle bir þey denemeye çalýþýr:

                        double d = 10 / 4; // tamsayý bölme yapar, d'yi 2.0 deðeri ile baþlatýr

Çünkü 10 ve 4 her ikisi de int türündedir, tamsayý bölme yapýlýr ve ifade int deðeri 2'ye deðerlendirilir. Bu deðer daha sonra deðiþken d'yi 
baþlatmak için kullanýlmadan önce double deðeri 2.0'ya sayýsal dönüþüme uðrar. Büyük olasýlýkla, bu istenmeyen bir durumdur.

Eðer literal operatörler kullanýyorsanýz, bir veya her iki tamsayý literalini double literal ile deðiþtirmek, ondalýk bölme iþlemine neden 
olacaktýr:

                        double d = 10.0 / 4.0; // ondalýk bölme yapar, d'yi 2.5 deðeri ile baþlatýr

Ancak literatller yerine deðiþkenler kullanýyorsanýz ne olacak? Bu durumu düþünün:

                        int x { 10 };
                        int y { 4 };
                        double d = x / y; // tamsayý bölme yapar, d'yi 2.0 deðeri ile baþlatýr

Çünkü burada tamsayý bölme kullanýlýyor, deðiþken "d" 2.0 deðeri ile baþlatýlacaktýr. Bu durumda derleyiciye, bu durumda tamsayý bölme yerine
ondalýk bölme kullanmak istediðimizi belirtmek için nasýl bir yol izleyebiliriz? Literal önekleri deðiþkenlerle kullanýlamaz. Bir deðiþken 
operandýný ondalýk bir türde bir sayýya dönüþtürmek için, derleyiciden bir tür dönüþümü gerçekleþtirmesini istemek için programcý tarafýndan
kullanýlan çeþitli tür dönüþüm operatörleri (daha yaygýn olarak "cast" olarak adlandýrýlýr) C++ ile birlikte gelmektedir. Çünkü "cast"ler programcý
tarafýndan yapýlan bilinçli talepler olduðu için, bu tür bir tür dönüþümü genellikle kasýtlý ( veya bilinçli olarak çevirdim )
tür dönüþümü olarak adlandýrýlýr (derleyicinin otomatik olarak bir tür dönüþümü gerçekleþtirdiði örtük tür dönüþümüne karþý).

Tür Dönüþümü
------------


C++ 5 farklý türde dönüþümü destekler:
1 - C tarzý dönüþümler
2 - static dönüþümler
3 - const dönüþümler
4 - dynamic dönüþümler 
5 - reinterpret dönüþümleri.

Son dört tanesi bazen adlandýrýlmýþ dönüþümler olarak anýlýr.

Bu derste C tarzý dönüþümler ve static dönüþümleri ele alacaðýz.


const dönüþümleri ve reinterpret dönüþümleri genellikle kaçýnýlmasý gereken türlerdir çünkü nadir durumlar dýþýnda kullanýþsýzdýr ve yanlýþ
kullanýldýðýnda zararlý olabilir.

Uyarý -> onlarý kullanma konusunda çok iyi bir nedeniniz yoksa, const dönüþümlerinden ve reinterpret dönüþümlerinden kaçýnýn

C tarzý dönüþümler

Standart C programlamada dönüþümler () operatörü aracýlýðýyla yapýlýr, bu operatörün içine dönüþtürülecek deðerin türünün adý yerleþtirilir. 
Bu tür dönüþümleri, C'den dönüþtürülmüþ olan kodlarda (veya programcýlar tarafýndan) hâlâ görebilirsiniz.

Örneðin:


                        #include <iostream>

                        int main()
                        {
                            int x { 10 };
                            int y { 4 };

                            double d { (double)(x) / y }; // x'i bir double'a dönüþtürerek ondalýk bölme elde etmek için
                            std::cout << d << '\n'; // 2.5 yazdýrýr

                            return 0;
                        }

Yukarýdaki programda, x'in bir double türüne dönüþtürülmesini söylemek için bir C tarzý dönüþüm kullanýyoruz. Çünkü "/" operatörünün sol operandý
artýk bir ondalýk sayý deðerine deðerlendirildiði için, sað operand da bir ondalýk sayý deðerine dönüþtürülecek ve bölme iþlemi ondalýk sayý
bölme olarak gerçekleþtirilecektir!

C++ ayrýca, C tarzý dönüþümü daha iþlev çaðrýsý benzeri bir sözdizimiyle kullanmanýza da izin verir.

                        double d { (double)(x) / y }; // x'i bir double'a dönüþtürerek ondalýk bölme elde etmek için


Bu, önceki örnekle ayný þekilde çalýþýr, ancak dönüþtürülen deðeri parantez içine alarak (neyin dönüþtürüldüðünü daha kolay anlamamýza olanak tanýyarak)
avantaj saðlar. C tarzý bir dönüþüm, tek bir dönüþmüþ gibi görünse de, baðlamýna baðlý olarak çeþitli farklý dönüþümleri gerçekleþtirebilir. Bu, bir 
static dönüþüm, bir const dönüþüm veya bir reinterpret dönüþümü içerebilir (ki bunlardan son ikisini yukarýda kaçýnýlmasý gerekenler olarak 
belirtmiþtik). Sonuç olarak, C tarzý dönüþümler, yanlýþlýkla yanlýþ kullanýlmaya ve beklenen davranýþý üretmemeye yönelik bir risk taþýr, ki bu da
C++ dönüþümlerini kullanarak kolayca önlenebilir.

Ayrýca, C tarzý dönüþümler yalnýzca bir tür adý, parantez ve deðiþken veya deðer olduðundan, bunlarý tanýmlamak zordur (kodunuzu daha zor okunur 
hale getirir) ve hatta daha da zor aranabilir hale getirir.

*** BEST -> C-Style cast lerden kaçýnmak en iyi uygulama olacaktýr. 

Static cast
-----------

C++, bir türün deðerini baþka bir türün deðerine dönüþtürmek için kullanýlan static_cast adlý bir dönüþüm operatörü tanýtmýþtýr.
Daha önce bir char'ý int'e dönüþtürmek için static_cast kullanýldýðýný görmüþtük, böylece std::cout, onu bir char yerine bir tamsayý olarak yazdýrýr:

                    #include <iostream>

                    int main()
                    {
                        char c { 'a' };
                        std::cout << c << ' ' << static_cast<int>(c) << '\n'; // 'a' karakterini ve karþýlýk gelen ASCII deðerini (97) yazdýrýr

                        return 0;
                    }

static_cast operatörü, bir ifadeyi girdi olarak alýr ve içindeki açýlmýþ parantez içinde belirtilen türe dönüþtürülmüþ deðeri döndürür. static_cast, 
bir temel türü baþka bir temel türe dönüþtürmek için en uygun olanýdýr.

                    #include <iostream>

                    int main()
                    {
                        int x { 10 };
                        int y { 4 };

                        // x'i bir double'a dönüþtürerek ondalýk sayý bölmesi elde ediyoruz
                        double d { static_cast<double>(x) / y };
                        std::cout << d << '\n'; // 2.5 yazdýrýr

                        return 0;
                    }

`static_cast`'in temel avantajý, derleme zamanýnda tür denetimi saðlamasýdýr; bu da yanlýþlýkla hata yapmayý zorlaþtýrýr

                    // C tarzý bir dizge literali bir tamsayýya dönüþtürülemez, bu nedenle aþaðýdaki dönüþüm geçersizdir ve derleme hatasý üretecektir
                    int x { static_cast<int>("Hello") }; // geçersiz: derleme hatasý 

static_cast ayrýca (bilerek) C tarzý dönüþümlerden daha güçsüz olup, const'u yanlýþlýkla kaldýramaz veya amaçlamadýðýnýz diðer iþlemleri
gerçekleþtiremezsiniz.

                    int main()
                    {
                        const int x{ 5 };
                        int& ref{ static_cast<int&>(x) }; // geçersiz: derleme hatasý üretecek
                        ref = 6;

                        return 0;
                    }

*** BEST -> `static_cast`'i, bir deðeri bir türden baþka bir türe dönüþtürmeniz gerektiðinde tercih edin.

static_cast kullanarak daraltma dönüþümlerini açýkça belirtin.
--------------------------------------------------------------

Derleyiciler, potansiyel olarak güvensiz (daraltma) kasýtsýz tür dönüþümleri gerçekleþtirildiðinde genellikle uyarý mesajlarý verirler. 
Örneðin, aþaðýdaki programý düþünün:

                    int i { 48 };
                    char ch = i; // implicit narrowing conversion

Bir tamsayýyý (2 veya 4 byte) bir char'a (1 byte) dönüþtürmek potansiyel olarak güvensizdir (çünkü derleyici, tamsayý deðerinin char'ýn aralýðýný 
aþýp aþmayacaðýný bilemez), bu nedenle derleyici genellikle bir uyarý mesajý verir. Eðer liste baþlatma kullanýrsak, derleyici bir hata üretecektir.

Bunu aþmak için, tamsayýmýzý açýkça bir char'a dönüþtürmek için bir static_cast kullanabiliriz:

                    int i { 48 };

                    // int'ten char'a açýkça dönüþüm, böylece bir char deðiþkenine atanýr
                    char ch { static_cast<char>(i) };

Bunu yaptýðýmýzda, derleyiciye bu dönüþümün amaçlandýðýný ve sonuçlarý (örneðin, bir char'ýn aralýðýný aþma durumu) kabul ettiðimizi açýkça 
belirtiyoruz. Bu static_cast'in çýkýþý char türünde olduðundan, deðiþken ch'nin baþlatýlmasý herhangi bir tür uyumsuzluðuna neden olmaz ve 
dolayýsýyla uyarý veya hata oluþmaz.

Ýþte baþka bir örnek, derleyicinin genellikle bir double'ý int'e dönüþtürmenin veri kaybýna neden olabileceðini bildireceði bir durum:

                    int i { 100 };
                    i = i / 2.5;

Derleyiciye bunu açýkça yapmayý amaçladýðýmýzý belirtmek için:
                
                    int i { 100 };
                    i = static_cast<int>(i / 2.5);

*/