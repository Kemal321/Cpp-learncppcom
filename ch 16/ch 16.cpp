#include <iostream>
#include <vector>

int main()
{/*
    std::vector primes{ 2, 3, 5, 7, 11 };
    std::cout << primes[11]<< '\n';*/
    std::vector primes{ 2 , 3, 5, 7, 11 };
    std::cout << primes.at(19) << '\n'; // -> Ýstisna fýrlatcek 

    return 0;
}
/*

16.1 — Konteynerlara ve dizilere giriþ
--------------------------------------
Deðiþken ölçeklenebilirlik sorunu
---------------------------------
30 öðrencinin sýnav sonuçlarýný kaydetmek ve sýnýfýn ortalama puanýný hesaplamak istediðimiz bir senaryoyu düþünün. Bunu yapmak için 30 deðiþkene
ihtiyacýmýz olacak. Bu deðiþkenleri þu þekilde tanýmlayabiliriz:

                // 30 tam sayý deðiþkeni tahsis edin (her birinin farklý bir adý var)
                int testScore1 {};
                int testScore2 {};
                int testScore3 {};
                // ...
                int testScore30 {};
Tanýmlanacak çok fazla deðiþken var! Ve sýnýfýn ortalama puanýný hesaplamak için þöyle bir þey yapmamýz gerekecek:

int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
Bu sadece çok fazla yazý, ayný zamanda çok tekrarlayýcýdýr (ve numaralardan birini yanlýþ yazmak ve fark etmemek o kadar da zor olmazdý). 
Ve bu deðerlerin her biriyle (örneðin, onlarý ekrana yazdýrmak gibi) bir þeyler yapmak istiyorsak, bu deðiþken isimlerini tekrar tekrar girmemiz 
gerekecek.

Þimdi, sýnýfa yeni eklenen bir öðrenciyi barýndýracak þekilde programýmýzý deðiþtirmemiz gerektiðini söyleyelim. Tüm kod tabanýný tarayýp ilgili
yerlere manuel olarak testScore31 eklememiz gerekecek. Mevcut kodu her deðiþtirdiðimizde, yeni hatalar oluþturma riskimiz vardýr. Örneðin,
ortalamanýn hesaplanmasýndaki böleni 30'dan 31'e güncellemeyi unutmak o kadar da zor olmazdý!

Ve bu sadece 30 deðiþkenle. Yüzlerce veya binlerce nesnemiz olduðu durumu düþünün. Ayný türden birkaç nesneye ihtiyaç duyduðumuzda, bireysel
deðiþkenlerin tanýmlanmasý basitçe ölçeklenmez.

Verilerimizi bir structýn içine koyabiliriz:

                struct testScores
                {
                // 30 tam sayý deðiþkeni tahsis edin (her birinin farklý bir adý var)
                int score1 {};
                int score2 {};
                int score3 {};
                // ...
                int score30 {};
                }
Bu, puanlarýmýz için ek bir organizasyon saðlar (ve onlarý daha kolay bir þekilde fonksiyonlara geçmemizi saðlar), ancak temel sorunu çözmez:
hala her test puaný nesnesini bireysel olarak tanýmlamamýz ve eriþmemiz gerekiyor.

Tahmin etmiþ olabilirsiniz, C++'ýn yukarýdaki zorluklara çözümleri var. Bu bölümde, bu çözümlerden birini tanýtacaðýz. Ve takip eden bölümlerde,
bu çözümün bazý diðer varyantlarýný inceleyeceðiz.

Konteynerlar
------------
Bir düzine yumurta almak için markete gittiðinizde, muhtemelen 12 yumurtayý bireysel olarak seçmiyor ve sepetinize koymuyorsunuz (deðil mi?).
Bunun yerine, muhtemelen tek bir yumurta kartonu seçiyorsunuz. Karton, belirli bir sayýda yumurta içeren bir tür konteynerdir (muhtemelen 6, 12 
veya 24). Þimdi kahvaltýlýk gevrekleri düþünün, birçok küçük gevrek parçasý içerir. Tüm bu parçalarý mutfak dolabýnýzda bireysel olarak saklamak
istemezsiniz! Gevrek genellikle bir kutuda gelir, bu da baþka bir konteynerdir. Gerçek hayatta sürekli olarak konteynerlarý kullanýyoruz çünkü bir 
koleksiyonu yönetmeyi kolaylaþtýrýrlar.

Programlamada da konteynerlar var, (potansiyel olarak büyük) nesne koleksiyonlarýný oluþturmayý ve yönetmeyi kolaylaþtýrýr. Genel programlamada, 
bir konteyner, isimsiz nesnelerin (elementler olarak adlandýrýlýr) bir koleksiyonu için depolama saðlayan bir veri tipidir.

Anahtar içgörü; Genellikle, ilgili deðerlerle çalýþmamýz gerektiðinde konteynerlarý kullanýrýz.

Anlaþýlan o ki, zaten bir konteyner türünü kullanýyorsunuz: dizeler! Bir dize konteyneri, bir karakter koleksiyonu için depolama saðlar,
bu da metin olarak çýktý alabilir:

                #include <iostream>
                #include <string>

                int main()
                {
                    std::string name{ "Alex" }; // dizeler, karakterler için bir konteynerdýr
                    std::cout << name; // dizemizi bir karakter dizisi olarak çýktý al

                    return 0;
                }

Bir konteynýrýn elemanlarý isimsizdir
-------------------------------------
Konteynýr nesnesinin kendisi genellikle bir isme sahip olur (aksi takdirde nasýl kullanýrýz?), ancak bir konteynýrýn elemanlarý isimsizdir. 
Bu, istediðimiz kadar çok elemaný konteynýrýmýza koyabilmemiz için böyledir, her bir elemana benzersiz bir isim vermek zorunda kalmadan!
Ýsimlendirilmemiþ elemanlarýn olmamasý önemlidir ve konteynýrlarý diðer veri yapýlarýndan ayýran þey budur. Bu yüzden düz yapýlar (yukarýdaki
testScores yapýmýz gibi sadece bir veri üyesi koleksiyonu olanlar) genellikle konteynýr olarak kabul edilmez -- veri üyeleri benzersiz isimler
gerektirir.

Yukarýdaki örnekte, string konteynýrýmýzýn bir ismi var (name), ancak konteynýrýn içindeki karakterlerin ('A', 'l', 'e', 'x') ismi yok.

Peki, elemanlar kendileri isimsizse, onlara nasýl eriþiriz? Her konteynýr, elemanlarýna eriþmek için bir veya daha fazla yöntem saðlar -- 
ancak tam olarak nasýl, konteynýrýn türüne baðlýdýr. Bu konudaki ilk örneðimizi bir sonraki dersimizde göreceðiz.

Anahtar Ýçgörü; Bir konteynýrýn elemanlarý kendi isimlerine sahip deðildir, böylece konteynýrýn istediðimiz kadar çok elemana sahip olmasýný
saðlarýz, her bir elemana benzersiz bir isim vermek zorunda kalmadan. Her konteynýr, bu elemanlara eriþmek için bir yöntem saðlar,
ancak nasýl olduðu, konteynýrýn belirli türüne baðlýdýr.

Bir konteynýrýn uzunluðu
------------------------
Programlamada, bir konteynýrýn eleman sayýsý genellikle uzunluðu (veya bazen sayýsý) olarak adlandýrýlýr.Stringler için aþaðýdaki örnek:

                #include <iostream>
                #include <string>

                int main()
                {
                    std::string name{ "Alex" };
                    std::cout << name << " has " << name.length() << " characters\n";

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Alex has 4 characters
C++'da, bir konteynýrýn eleman sayýsý için genellikle boyut ( size ) terimi de kullanýlýr. Bu, nomenklatürde talihsiz bir seçimdir, çünkü “boyut” 
terimi ayný zamanda bir nesnenin kullandýðý bellek bayt sayýsýna (sizeof operatörü tarafýndan döndürülür) da iþaret edebilir.

Konteynýrýn eleman sayýsýna atýfta bulunurken “uzunluk” terimini tercih ederiz ve bir nesnenin gerektirdiði depolama miktarýna atýfta bulunmak için
“boyut” terimini kullanýrýz.

Konteynýr Ýþlemleri
-------------------
Bir an için yumurta kartonumuza geri dönelim. Böyle bir kartonla ne yapabilirsiniz? Ýlk olarak, bir yumurta kartonu edinebilirsiniz.
Yumurta kartonunu açabilir ve bir yumurta seçebilir, ardýndan o yumurtayla istediðinizi yapabilirsiniz. Kartondan mevcut bir yumurtayý çýkarabilir
veya boþ bir alana yeni bir yumurta ekleyebilirsiniz. Ayrýca kartondaki yumurta sayýsýný da sayabilirsiniz.

Benzer þekilde, konteynýrlar genellikle aþaðýdaki iþlemlerin önemli bir alt kümesini uygular:

*- Bir konteynýr oluþturun (ör. boþ, bazý baþlangýç elemanlarý için depolama alanýyla, bir deðer listesinden).
*- Elemanlara eriþim (ör. ilk elemaný al, son elemaný al, herhangi bir elemaný al).
*- Elemanlarý ekle ve çýkar.
*- Konteynýrdaki eleman sayýsýný al.

Konteynýrlar ayrýca, eleman koleksiyonunu yönetmeye yardýmcý olan diðer iþlemleri (veya yukarýdakilerin varyasyonlarýný) saðlayabilir.

Modern programlama dilleri genellikle çeþitli farklý konteynýr türleri saðlar. Bu konteynýr türleri, hangi iþlemleri gerçekten destekledikleri ve
bu iþlemlerin ne kadar performanslý olduðu açýsýndan farklýlýk gösterir. Örneðin, bir konteynýr türü, konteynýrdaki herhangi bir elemana hýzlý
eriþim saðlayabilir, ancak elemanlarýn eklenmesini veya çýkarýlmasýný desteklemeyebilir. Baþka bir konteynýr türü, elemanlarýn hýzlý bir þekilde 
eklenmesini ve çýkarýlmasýný saðlar, ancak yalnýzca elemanlara sýralý bir þekilde eriþime izin verir.

Her konteynýrýn bir dizi güçlü ve zayýf yönü vardýr. Çözmeye çalýþtýðýnýz görev için doðru konteynýr türünü seçmek, hem kodun bakýmýný hem de genel
performansý üzerinde büyük bir etkisi olabilir. Bu konuyu ileride bir dersimizde daha ayrýntýlý olarak tartýþacaðýz.

Element türleri
---------------
Çoðu programlama dilinde (C++ dahil), konteynerlar homojendir, yani bir konteynerin elemanlarýnýn ayný türde olmasý gerekir.

Bazý konteynerlar önceden belirlenmiþ bir eleman türü kullanýr (örneðin, bir string genellikle char elemanlarýna sahiptir), ancak daha sýk olarak
eleman türü, konteynerýn kullanýcýsý tarafýndan belirlenebilir. C++'da, konteynerlar genellikle sýnýf þablonlarý olarak uygulanýr, böylece 
kullanýcý istenen eleman türünü bir þablon türü argümaný olarak saðlayabilir. Bu konuda bir örneði bir sonraki derste göreceðiz.

Bu, konteynerlarý esnek hale getirir, çünkü tutmak istediðimiz her eleman türü için yeni bir konteyner sýnýfý oluþturmamýz gerekmez. Bunun yerine,
sadece istenen eleman türü ile sýnýf þablonunu örneklendiririz ve hazýrýz.

Bir not olarak Homojen bir konteynerýn zýttý, heterojen bir konteynerdir, bu da elemanlarýn farklý türlerde olmasýna izin verir.
Heterojen konteynerlar genellikle betik dilleri (Python gibi) tarafýndan desteklenir.

C++'da Konteynerlar
-------------------
Konteynerlar kütüphanesi, C++ standart kütüphanesinin bir parçasýdýr ve bazý ortak konteyner türlerini uygulayan çeþitli sýnýf türlerini içerir.
Bir konteynerý uygulayan bir sýnýf türü bazen bir konteyner sýnýfý olarak adlandýrýlýr. Konteynerlar kütüphanesindeki konteynerlarýn tam listesi 
https://en.cppreference.com/w/cpp/container da belgelenmiþtir.

C++'da "konteyner" tanýmý, genel programlama tanýmýndan daha dar bir anlama gelir. Sadece Konteynerlar kütüphanesindeki sýnýf türleri C++'da
konteyner olarak kabul edilir. Genel olarak konteynerlardan bahsederken "konteyner" terimini kullanacaðýz ve Konteynerlar kütüphanesinin bir 
parçasý olan konteyner sýnýf türlerinden özellikle bahsederken "konteyner sýnýfý" terimini kullanacaðýz.

Saðlanan konteyner sýnýflarý arasýnda, std::vector ve std::array en çok kullanýlanlardýr ve dikkatimizin büyük çoðunluðunu bu konulara 
odaklayacaðýz. Diðer konteyner sýnýflarý genellikle daha özel durumlarda kullanýlýr.

Dizilere Giriþ
--------------
Bir dizi, bir dizi deðeri ardýþýk olarak (yani her elemanýn bitiþik bir bellek konumuna yerleþtirildiði, arada boþluk olmadan) depolayan bir 
konteyner veri türüdür. Diziler, herhangi bir elemana hýzlý, doðrudan eriþim saðlar. Kavramsal olarak basit ve kullanýmý kolaydýrlar, bu da onlarý
bir dizi ilgili deðer oluþturup çalýþmamýz gerektiðinde ilk seçenek yapar.

C++'da üç ana dizi türü vardýr: (C tarzý) diziler, std::vector konteyner sýnýfý ve std::array konteyner sýnýfý.

(C tarzý) diziler C dilinden miras alýnmýþtýr. Geriye dönük uyumluluk için, bu diziler temel veri türleri gibi çekirdek C++ dilinin bir parçasý 
olarak tanýmlanýr. C++ standardý bunlara "diziler" der, ancak modern C++'da bunlar genellikle std::array'den ayýrt etmek için C dizileri veya C 
tarzý diziler olarak adlandýrýlýr. C tarzý dizilere bazen "çýplak diziler ( naked arrays )", "sabit boyutlu diziler ( fixed-sized arrays )", 
"sabit diziler ( fixed arrays )" veya "yerleþik diziler ( built-in arrays )" denir.
Biz "C tarzý dizi" terimini tercih edeceðiz ve genel olarak dizi türlerinden bahsederken "dizi" terimini kullanacaðýz. Modern standartlara göre, 
C tarzý diziler tuhaf davranýr ve tehlikelidirler. Nedenini bir sonraki bölümde inceleyeceðiz.

C++'da dizileri daha güvenli ve kullanýmý kolay hale getirmek için, std::vector konteyner sýnýfý C++03'te tanýtýldý. std::vector, 
üç dizi türü arasýnda en esnek olanýdýr ve diðer dizi türlerinin sahip olmadýðý bir dizi kullanýþlý özelliðe sahiptir.

Son olarak, std::array konteyner sýnýfý, C tarzý dizilerin doðrudan yerine geçmek üzere C++11'de tanýtýldý. std::vector'dan daha sýnýrlýdýr,
ancak özellikle daha küçük diziler için daha verimli olabilir.

Bu dizi türlerinin tümü, modern C++'da farklý kapasitelerde hala kullanýlmaktadýr, bu yüzden üçünü de çeþitli derecelerde ele alacaðýz.

Ýlerleyiþ
---------
Bir sonraki derste, ilk konteyner sýnýfýmýz olan std::vector'ü tanýtacaðýz ve bu dersin baþýnda sunduðumuz meydan okumayý nasýl verimli bir þekilde
çözebileceðini göstermeye baþlayacaðýz. std::vector ile çok zaman geçireceðiz, çünkü oldukça fazla yeni kavramý tanýtmamýz ve yolda bazý 
ek zorluklarý ele almamýz gerekecek.

Güzel olan bir þey, tüm konteyner sýnýflarýnýn benzer arayüzlere sahip olmasýdýr. Bu nedenle, bir konteyneri (örneðin std::vector) nasýl 
kullanacaðýnýzý öðrendikten sonra, diðerlerini (örneðin std::array) öðrenmek çok daha basittir. Gelecekteki konteynerler için (örneðin std::array),
belirgin farklýlýklarý (ve en önemli noktalarý tekrarlayacaðýz).

Yazarýn Notu
------------
Terminoloji üzerine hýzlý bir not:

Çoðu veya tüm standart kütüphane konteyner sýnýflarýna uygulanan bir þey hakkýnda konuþurken konteyner sýnýflarýný kullanacaðýz.
Tüm dizi türlerine genellikle uygulanan bir þey hakkýnda konuþurken dizi kullanacaðýz, diðer programlama dillerinde uygulananlar bile.
std::vector, bu iki kategoriye de girer, bu yüzden farklý terimler kullanýyor olabiliriz, ancak std::vector'a hala uygulanýr.

Tamam, hazýr mýsýnýz?

Hadi baþlayalým.

16.2 — std::vector'a Giriþ ve list constructors
-----------------------------------------------
Önceki derste 16.1 -- Konteynerlere ve dizilere giriþ, hem konteynerleri hem de dizileri tanýttýk. Bu derste, bölümün geri kalanýnda 
odaklanacaðýmýz dizi türünü tanýtacaðýz: std::vector. Ayrýca geçen derste tanýttýðýmýz ölçeklenebilirlik meydan okumasýnýn bir kýsmýný çözeceðiz.

std::vector'a Giriþ
-------------------
std::vector, bir dizi uygulayan C++ standart konteynerler kütüphanesindeki konteyner sýnýflarýndan biridir. std::vector, <vector> baþlýðýnda bir 
sýnýf þablonu olarak tanýmlanýr, bir þablon tür parametresi ile, bu da öðelerin türünü tanýmlar. Bu nedenle, std::vector<int> bir std::vector'ü
tanýmlar, öðeleri int türündedir.

Bir std::vector nesnesini örnekleme basittir:

                #include <vector>

                int main()
                {
                    // Deðer baþlatma (varsayýlan yapýlandýrýcýyý kullanýr)
                    std::vector<int> empty{}; // 0 int öðesi içeren vector

                    return 0;
                }

Boþ deðiþkeni, öðeleri int türünde olan bir std::vector olarak tanýmlanmýþtýr. Burada deðer baþlatmayý kullandýðýmýz için, vector'ümüz boþ 
(yani, hiçbir öðe olmadan) baþlar.

Þimdilik hiç öðesi olmayan bir vector kullanýþlý görünmeyebilir, ancak bu durumu gelecekteki derslerde (özellikle 16.11 -- std::vector ve stack 
davranýþý) tekrar karþýlaþacaðýz.

Bir std::vector'ü bir deðer listesiyle baþlatma
-----------------------------------------------
Bir konteynerin amacý, bir dizi ilgili deðeri yönetmek olduðundan, çoðu zaman konteynerimizi bu deðerlerle baþlatmak isteyeceðiz. Bunu, istediðimiz
belirli baþlatma deðerleriyle liste baþlatmayý kullanarak yapabiliriz. Örneðin:

                #include <vector>

                int main()
                {
                    // Liste yapýsý (liste yapýlandýrýcýsýný kullanýr)
                    std::vector<int> primes{ 2, 3, 5, 7 };          // 2, 3, 5 ve 7 deðerlerine sahip 4 int öðesi içeren vector
                    std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // 'a', 'e', 'i', 'o' ve 'u' deðerlerine sahip 5 char öðesi içeren vector.  
                                                                    // CTAD (C++17) kullanýr ve char öðe türünü çýkarýr ( deduce ) (tercih edilir).
                    return 0;
                }

Primes ile, öðelerinin int türünde olduðu bir std::vector istediðimizi açýkça belirtiyoruz. 4 baþlatma deðeri saðladýðýmýz için,
primes 2, 3, 5 ve 7 deðerlerine sahip 4 öðe içerecektir.

Sesli harflerle, açýkça bir öðe türü belirtmedik. Bunun yerine, derleyicinin baþlatýcýlarýndan öðe türünü çýkarmasý için C++17'nin CTAD
(sýnýf þablonu argüman çýkarýmý) özelliðini kullanýyoruz. 5 baþlatma deðeri saðladýðýmýz için, sesli harfler 'a', 'e', 'i', 'o' ve 'u' deðerlerine 
sahip 5 öðe içerecek.

Liste yapýcýlarý ve baþlatýcý listeler
--------------------------------------
Yukarýdaki iþleyiþin biraz daha detayýna girelim.

13.6 dersinde -- Struct'ý toplu baþlatma, bir baþlatýcý listeyi virgülle ayrýlmýþ deðerlerin süslü parantez içindeki listesi olarak tanýmladýk
(ör. { 1, 2, 3 }).

Konteynerler genellikle, bir baþlatýcý listeyi kullanarak konteynerin bir örneðini oluþturmamýza izin veren özel bir kurucuya sahiptir. 
Liste yapýcýsý üç þey yapar:

*- Tüm baþlatma deðerlerini saklamak için konteynerin yeterli depolama alanýna sahip olmasýný saðlar (gerekirse).
*- onteynerin uzunluðunu, baþlatýcý listedeki öðe sayýsýna ayarlar (gerekirse).
*- Öðeleri, baþlatýcý listedeki deðerlere (sýralý olarak) baþlatýr.
* 
Dolayýsýyla, bir konteynera bir baþlatýcý deðer listesi saðladýðýmýzda, liste yapýcý çaðrýlýr ve konteyner, bu deðer listesini kullanarak 
oluþturulur!

*** BEST -> Bir konteyneri, bu öðe deðerleriyle oluþturmak için bir baþlatýcý deðer listesi ile liste baþlatmasýný kullanýn.

Subscript operatörü (operator[]) kullanarak dizi öðelerine eriþim
-----------------------------------------------------------------
Peki, bir dizi öðe oluþturduk... onlara nasýl eriþiriz?

Bir an için bir benzetme kullanalým. Yan yana olan ayný posta kutularýný düþünün. Posta kutularýný daha kolay tanýmlamak için, her posta kutusunun
önünde bir numara boyanmýþ. Ýlk posta kutusu numarasý 0, ikincisi numarasý 1, vb... Yani size posta kutusu numarasý 0'a bir þey koymanýz 
söylendiðinde, bu ilk posta kutusu anlamýna geldiðini bilirsiniz.

C++'da, dizi öðelerine eriþmenin en yaygýn yolu, dizinin adýný ve subscript operatörünü (operator[]) kullanmaktýr. Belirli bir öðeyi seçmek için, 
subscript operatörünün köþeli parantezlerinin içine, hangi öðeyi seçmek istediðimizi belirleyen bir tam sayý deðeri saðlarýz. Bu tam sayý deðeri,
bir subscript (veya gayri resmi olarak, bir index) olarak adlandýrýlýr. Posta kutularýmýz gibi, ilk öðeye index 0 kullanýlarak, ikinciye index 1 
kullanýlarak eriþilir, vb...

Örneðin, primes[0] asal dizi içindeki index 0'a sahip öðeyi (ilk öðeyi) döndürecektir. Subscript operatörü, gerçek öðeye bir referans döndürür, 
bir kopya deðil. Bir dizi öðesine eriþtikten sonra, onu normal bir nesne gibi kullanabiliriz (ör. bir deðer atayabiliriz, 
onu çýktý olarak verebiliriz, vb...)

Dizileme 0'dan baþladýðý için, C++'daki dizilerin sýfýr tabanlý olduðunu söyleriz. Bu, nesneleri 1'den baþlayarak saymaya alýþkýn olduðumuz için
kafa karýþtýrýcý olabilir. Bu ayrýca bir belirsizliðe de neden olabilir çünkü dizi öðesi 1 hakkýnda konuþtuðumuzda, ilk dizi öðesi (index 0 ile)
mi yoksa ikinci dizi öðesi (index 1 ile) mi olduðu açýk olmayabilir.

Ýþte bir örnek:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

                    std::cout << "The first prime number is: " << primes[0] << '\n';
                    std::cout << "The second prime number is: " << primes[1] << '\n';
                    std::cout << "The sum of the first 5 primes is: " << primes[0] + primes[1] + primes[2] + primes[3] + primes[4] << '\n';

                    return 0;
                }
                Bu, þunu yazdýrýr:

                The first prime number is: 2
                The second prime number is: 3
                The sum of the first 5 primes is: 28

Dizileri kullanarak, 5 asal deðerimizi tutmak için 5 farklý adlý deðiþken tanýmlamamýz gerekmiyor. Bunun yerine, 5 öðeli tek bir dizi (primes) 
tanýmlayabilir ve farklý öðelere eriþmek için index deðerini deðiþtirebiliriz!

Bir sonraki ders olan 16.3 -- std::vector ve iþaretsiz uzunluk ve subscript sorunu dersinde operator[] ve diðer bazý array elemanlarýna eriþim
yöntemleri hakkýnda daha fazla konuþacaðýz.

Subscript sýnýrlarýn dýþýnda
----------------------------
Bir dizini indexlerken, saðlanan indexin dizinin geçerli bir elemanýný seçmesi gerekir. Yani, N uzunluðunda bir dizi için, subscript 0 ve N-1
(dahil) arasýnda bir deðer olmalýdýr.

operator[] herhangi bir sýnýrlama kontrolü yapmaz, yani indexin 0 ile N-1 (dahil) sýnýrlarý içinde olup olmadýðýný kontrol etmez. operator[]'ye 
geçersiz bir index geçmek tanýmsýz bir davranýþa neden olur.

Negatif subscriptleri kullanmamayý hatýrlamak oldukça kolaydýr. Index N olan bir eleman olmadýðýný hatýrlamak daha az kolaydýr! Dizinin son 
elemanýnýn indexi N-1'dir, bu yüzden N indexini kullanmak, derleyicinin dizinin sonundan bir sonraki elemana eriþmeye çalýþmasýna neden olur.

Ýpucu

N elemanlý bir dizide, ilk elemanýn indexi 0, ikincinin indexi 1 ve son elemanýn indexi N-1'dir. N indexli bir eleman yoktur!

N'yi subscript olarak kullanmak tanýmsýz bir davranýþa neden olur (çünkü bu aslýnda dizinin parçasý olmayan N+1. elemana eriþmeye çalýþýyor).

Ýpucu

Bazý derleyiciler (Visual Studio gibi) indexin geçerli olduðunu kontrol eden bir runtime assert saðlar. Bu tür durumlarda, debug modunda geçersiz
bir index saðlanýrsa, program assert çýkarýr. Release modunda, assert derlenir, bu yüzden hiçbir performans penalty'si yoktur.

Diziler bellekte bitiþiktir
---------------------------
Dizilerin belirleyici özelliklerinden biri, elemanlarýn her zaman bellekte bitiþik olarak ayrýlmasýdýr, yani elemanlar bellekte birbirine 
bitiþiktir (aralarýnda boþluk yoktur).

Bunu göstermek için:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

                    std::cout << "An int is " << sizeof(int) << " bytes\n";
                    std::cout << &(primes[0]) << '\n';
                    std::cout << &(primes[1]) << '\n';
                    std::cout << &(primes[2]) << '\n';

                    return 0;
                }
                Yazarýn makinesinde, yukarýdaki programýn bir çalýþtýrýlmasý aþaðýdaki sonucu verdi:

                An int is 4 bytes
                00DBF720
                00DBF724
                00DBF728

Bu int elemanlarýnýn bellek adreslerinin, yazarýn makinesindeki bir int'in boyutu olan 4 byte kadar ayrý olduðunu not edeceksiniz.

Bu, dizilerin herhangi bir eleman baþýna ekstra maliyeti olmadýðý anlamýna gelir. Ayrýca derleyicinin dizinin herhangi bir elemanýnýn adresini
hýzlýca hesaplamasýný saðlar.

Diziler, her bir elemana doðrudan ve eþit hýzda eriþim saðlayan birkaç konteynýr türünden biridir, konteynýrýn eleman sayýsýna bakýlmaksýzýn.
Herhangi bir elemana hýzlýca doðrudan eriþim yeteneði, dizilerin konteynýr seçimi için birincil nedenidir.

Belirli bir uzunlukta bir std::vector oluþturma
-----------------------------------------------
Kullanýcýnýn 10 deðer girmesini ve bunlarý bir std::vector'da saklamasýný istediðimiz bir durumu düþünün. Bu durumda, std::vector'a herhangi bir 
deðer koymadan önce 10 uzunluðunda bir std::vector'a ihtiyacýmýz var. Bunu nasýl çözeriz?

Bir std::vector oluþturabilir ve onu 10 adet yer tutucu deðeri olan bir baþlatýcý listesi ile baþlatabiliriz:

                std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
Ama bu, birçok nedenle kötüdür. Çok fazla yazým gerektirir. Kaç tane baþlatýcý olduðunu görmek kolay deðildir. Ve daha sonra farklý bir deðer
sayýsý istemeye karar verirsek güncellemesi kolay olmaz.

Neyse ki, std::vector'ýn, oluþturulacak std::vector'ýn uzunluðunu tanýmlayan tek bir int deðeri alan bir explicit constructor'ý
(explicit std::vector<T>(int)) vardýr:

                std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
Oluþturulan her bir eleman deðer-initialize edilir, bu int için sýfýr-initialization yapar (ve sýnýf türleri için default constructor'ý çaðýrýr).

Ancak, bu constructor'ý kullanýrken gözden kaçan bir þey var: doðrudan baþlatma kullanýlarak çaðrýlmalýdýr.

Liste constructorlarý diðer constructorlardan önceliklidir

Önceki constructor'ýn neden doðrudan baþlatma kullanýlarak çaðrýlmasý gerektiðini anlamak için bu tanýmlamayý düþünün:

                std::vector<int> data{ 10 }; // bu ne yapar?
Bu baþlatmayý eþleþtiren iki farklý constructor vardýr:

*- { 10 } bir baþlatýcý listesi olarak yorumlanabilir ve liste constructor'ý ile eþleþtirilerek deðeri 10 olan uzunluðu 1 olan bir 
   vektör oluþturabilir

*- { 10 } tek bir süslü baþlatma deðeri olarak yorumlanabilir ve std::vector<T>(int) constructor'ý ile eþleþtirilerek elemanlarý 0'a deðer
   baþlatýlmýþ uzunluðu 10 olan bir vektör oluþturabilir.

Normalde bir sýnýf türü tanýmý birden fazla constructor'ý eþleþtirirse, eþleþme belirsiz kabul edilir ve bir derleme hatasý oluþur. Ancak,
C++'ýn bu durum için özel bir kuralý vardýr: Eþleþen bir liste constructor'ý, diðer eþleþen constructor'lardan seçilir. Bu kural olmasaydý, 
bir liste constructor'ý, tek tip argüman alan herhangi bir constructor ile belirsiz bir eþleþme oluþtururdu.

{ 10 } bir baþlatýcý listesi olarak yorumlanabilir ve std::vector'ýn bir liste constructor'ý olduðundan, bu durumda liste constructor'ý 
önceliklidir.

Anahtar içgörü

Bir sýnýf türü nesnesi oluþtururken, eþleþen bir liste constructor'ý, diðer eþleþen constructor'lardan seçilir.

Çeþitli baþlatma durumlarýnda ne olduðunu daha da açýklýða kavuþturmak için, kopya, doðrudan ve liste baþlatma kullanýlarak benzer durumlara
bakalým:

                // Kopya baþlatma
                std::vector<int> v1 = 10;     // 10 bir baþlatýcý liste deðil, kopya baþlatma explicit constructor'ý eþleþtirmez: derleme hatasý

                // Doðrudan baþlatma
                std::vector<int> v2(10);      // 10 bir baþlatýcý liste deðil, explicit tek argümanlý constructor'ý eþleþtirir

                // Liste baþlatma
                std::vector<int> v3{ 10 };    // { 10 } baþlatýcý liste olarak yorumlanýr, liste constructor'ý ile eþleþir

                // Kopya liste baþlatma
                std::vector<int> v4 = { 10 }; // { 10 } baþlatýcý liste olarak yorumlanýr, liste constructor'ý ile eþleþir
                std::vector<int> v5({ 10 });  // { 10 } baþlatýcý liste olarak yorumlanýr, liste constructor'ý ile eþleþir

v1 durumunda, 10 baþlatma deðeri bir baþlatýcý liste deðil, bu yüzden liste constructor'ý bir eþleþme deðil. Tek argümanlý constructor
explicit std::vector<T>(int) de kopya baþlatma ile explicit constructor'larý eþleþtirmeyeceði için bir eþleþme deðil. 
Hiçbir constructor eþleþmediði için bu bir derleme hatasýdýr.

v2 durumunda, 10 baþlatma deðeri bir baþlatýcý liste deðil, bu yüzden liste constructor'ý bir eþleþme deðil. Tek argümanlý constructor
explicit std::vector<T>(int) bir eþleþmedir, bu yüzden tek argümanlý constructor seçilir.

v3 durumunda (liste baþlatma), { 10 } liste constructor'ý veya explicit std::vector<T>(int) ile eþleþtirilebilir. Liste constructor'ý,
diðer eþleþen constructor'lardan öncelikli olur ve seçilir.

v4 durumunda (kopya liste baþlatma), { 10 } bir baþlatýcý liste ile eþleþtirilebilir (bu, explicit olmayan bir constructor'dur, bu yüzden kopya
baþlatma ile kullanýlabilir). Liste constructor'ý seçilir.

v5 durumu þaþýrtýcý bir þekilde kopya liste baþlatma için alternatif bir sözdizimi (doðrudan baþlatma deðil) ve v4 ile aynýdýr.

Bu, C++ baþlatmasýnýn bir kusurudur: { 10 } varsa bir liste constructor'ý ile eþleþir, veya bir liste constructor'ý yoksa tek argümanlý bir 
constructor ile eþleþir. Bu, hangi davranýþý elde ettiðinizin bir liste constructor'ýnýn var olup olmadýðýna baðlý olduðu anlamýna gelir! 
Genellikle konteynerlarýn liste constructor'larý olduðunu varsayabilirsiniz.

Özetlemek gerekirse, liste baþlatýcýlar genellikle bir konteynerý bir eleman deðerleri listesi ile baþlatmamýza izin vermek için tasarlanmýþtýr
ve bu amaç için kullanýlmalýdýr. Zaten çoðunlukla istediðimiz þey budur. Bu nedenle, { 10 } 10'un bir eleman deðeri olduðu durumlarda uygundur. 
Eðer 10, bir konteynerýn liste olmayan bir constructor'ýna bir argüman olarak anlamýna geliyorsa, doðrudan baþlatmayý kullanýn.

*** BEST -> Bir konteyneri (veya bir liste yapýcýya sahip herhangi bir türü) öðe deðerleri olmayan baþlatýcýlarla oluþtururken, doðrudan baþlatmayý
            kullanýn.

Ýpucu

Bir std::vector, bir sýnýf türünün üyesi olduðunda, bir std::vector'ün uzunluðunu belirli bir baþlangýç deðerine ayarlayan bir varsayýlan 
baþlatýcýyý nasýl saðlayacaðý açýk deðildir:

                #include <vector>

                struct Foo
                {
                    std::vector<int> v1(8); // derleme hatasý: üye varsayýlan baþlatýcýlarý için doðrudan baþlatmaya izin verilmez
                };

Bir sýnýf türünün bir üyesi için varsayýlan bir baþlatýcý saðlarken:

*- Ya kopya baþlatmayý ya da liste baþlatmayý kullanmalýyýz.
*- CTAD'a izin verilmez (bu yüzden öðe türünü açýkça belirtmeliyiz).

Cevap þu þekildedir:

                struct Foo
                {
                    std::vector<int> v{ std::vector<int>(8) }; // tamam
                };

Bu, kapasitesi 8 olan bir std::vector oluþturur ve ardýndan bunu v'nin baþlatýcýsý olarak kullanýr.

Const ve constexpr std::vector
------------------------------
std::vector türündeki nesneler const yapýlabilir:

                #include <vector>

                int main()
                {
                    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime ve öðeleri deðiþtirilemez

                    return 0;
                }

Bir const std::vector baþlatýlmalý ve ardýndan deðiþtirilemez. Bu tür bir vector'ün öðeleri, constmuþ gibi ele alýnýr.

Bir non-const std::vector'ün öðeleri non-const olmalýdýr. Bu nedenle, aþaðýdakine izin verilmez:

                #include <vector>

                int main()
                {
                    std::vector<const int> prime { 2, 3, 5, 7, 11 };
                }

std::vector'ün en büyük dezavantajlarýndan biri, constexpr yapýlamamasýdýr. Eðer constexpr bir diziye ihtiyacýnýz varsa, std::array kullanýn.

Neden vector olarak adlandýrýldý?
---------------------------------
Ýnsanlar konuþma sýrasýnda "vector" terimini kullandýklarýnda, genellikle bir büyüklüðü ve yönü olan bir nesne olan bir geometrik vector'ü
kastediyorlar. Peki std::vector, bir geometrik vector olmadýðýnda adýný nasýl aldý?

"Matematikten Genel Programlamaya" adlý kitapta Alexander Stepanov, "STL'deki vector adý, daha önceki programlama dilleri Scheme ve Common Lisp'ten
alýndý. Ne yazýk ki, bu, matematikteki çok daha eski terimin anlamýyla tutarsýzdý... bu veri yapýsýna dizi denmeliydi. Üzgünüm, eðer bir hata
yaparsanýz ve bu ilkeleri ihlal ederseniz, sonuç uzun süre boyunca kalabilir." diye yazdý.

Yani, temelde, std::vector yanlýþ adlandýrýlmýþtýr, ancak þimdi onu deðiþtirmek için çok geçtir.

16.3 — std::vector ve iþaretsiz uzunluk ve subscript sorunu
----------------------------------------------------------
Önceki ders olan 16.2 -- std::vector ve liste kurucularýna giriþte, bir diziyi subscript etmek ve bir öðeye eriþmek için kullanýlabilecek
operator[]'i tanýttýk. Bu derste, dizi öðelerine eriþmenin diðer yollarýna ve bir konteyner sýnýfýnýn uzunluðunu (konteyner sýnýfýnda þu anda 
bulunan öðe sayýsý) almanýn birkaç farklý yoluna bakacaðýz.

Ama bunu yapmadan önce, C++'ýn tasarýmcýlarýnýn yaptýðý büyük bir hatayý ve bu hatanýn C++ standart kütüphanesindeki tüm konteyner sýnýflarýný 
nasýl etkilediðini tartýþmamýz gerekiyor.

Konteyner uzunluk iþaret sorunu
-------------------------------
Bir iddiayla baþlayalým: bir diziyi subscript etmek için kullanýlan veri tipi, dizinin uzunluðunu saklamak için kullanýlan veri tipiyle
eþleþmelidir. Bu, en uzun olasý dizideki tüm öðelerin indexlenebilmesi ve daha fazlasýnýn olmamasý için gereklidir.

Bjarne Stroustrup'un hatýrladýðýna göre, C++ standart kütüphanesindeki konteyner sýnýflarý tasarlanýrken (yaklaþýk 1997), tasarýmcýlarýn uzunluðu
(ve dizi subcriptlerini) iþaretli mi yoksa iþaretsiz mi yapacaklarýna karar vermesi gerekiyordu. Onlar bunlarý iþaretsiz ( iþaretsiz )
yapmayý seçtiler.

Bunun için verilen nedenler: standart kütüphane dizi tiplerinin subcriptleri negatif olamaz, bir iþaretsiz tip kullanmak ekstra bit nedeniyle
daha uzun dizilere izin verir (bu, 16-bit günlerinde önemliydi) ve subscriptin aralýk kontrolü iki yerine bir koþullu kontrol gerektirir
(çünkü indexin 0'dan küçük olduðunu saðlamak için kontrol yapmaya gerek yoktu).

Geriye dönüp baktýðýmýzda, bu genellikle yanlýþ bir seçim olarak kabul edilir. Artýk iþaretsiz deðerlerin negatif olmayanlarý zorlamaya çalýþmanýn,
implicit dönüþüm kurallarý nedeniyle iþe yaramadýðýný anlýyoruz (çünkü negatif bir iþaretli tam sayý, sadece büyük bir iþaretsiz tam sayýya 
implicit olarak dönüþür ve çöp bir sonuç üretir), ekstra bit aralýðý genellikle 32-bit veya 64-bit sistemlerde gerekli deðildir
(çünkü muhtemelen 2 milyondan fazla öðe içeren diziler oluþturmuyorsunuzdur) ve yaygýn olarak kullanýlan operator[] zaten aralýk kontrolü yapmaz.

4.5 dersinde -- Ýþaretsiz tam sayýlar ve onlardan kaçýnma nedenleri, nicelikleri tutmak için iþaretli deðerleri kullanmayý tercih ettiðimiz
nedenleri tartýþtýk. Ayrýca, iþaretli ve iþaretsiz deðerlerin karýþtýrýlmasýnýn beklenmedik davranýþlara yol açabileceðini de belirttik. 
Dolayýsýyla, standart kütüphane konteyner sýnýflarýnýn uzunluk (ve indeksler) için iþaretsiz deðerler kullanmasý sorunludur, çünkü bu türleri
kullanýrken iþaretsiz deðerlerden kaçýnmayý imkansýz kýlar.

Þimdilik, bu seçimle ve neden olduðu gereksiz karmaþýklýkla baþa çýkmak zorundayýz.

Bir inceleme iþaret dönüþümleri daraltýcý dönüþümlerdir, constexpr olduðunda hariç
----------------------------------------------------------------------------------
Daha ileri gitmeden önce, bu bölümde çok konuþacaðýmýz iþaret dönüþümleri (iþaretli'den iþaretsiz'e veya tam tersi integral dönüþümler) 
hakkýnda 10.4 dersi -- Daraltýcý dönüþümler, liste baþlatma ve constexpr baþlatýcýlarýndan bazý materyalleri hýzlýca gözden geçirelim.

Ýþaret dönüþümleri, bir iþaretli veya iþaretsiz tipin, karþýt tipin aralýðýndaki tüm deðerleri tutamamasý nedeniyle daraltýcý dönüþümler olarak 
kabul edilir. Böyle bir dönüþüm, çalýþma zamanýnda denenirse, derleyici daraltýcý dönüþümlerin izin verilmediði baðlamlarda (örneðin liste
baþlatmasýnda) bir hata verecek ve bu tür bir dönüþüm gerektiren diðer baðlamlarda uyarý verebilir veya vermeyebilir.

Örneðin:

                #include <iostream>

                void foo(unsigned int)
                {
                }

                int main()
                {
                    int s { 5 };

                    [[maybe_unused]] iþaretsiz int u { s }; // compile error: list initialization disallows narrowing conversion
                    foo(s);                                // possible warning: copy initialization allows narrowing conversion

                    return 0;
                }

Yukarýdaki örnekte, u deðiþkeninin baþlatýlmasý bir derleme hatasý oluþturur çünkü daraltýcý dönüþümler list initialization yapýlýrken kabul
edilmez. foo() çaðrýsý copy initialization gerçekleþtirir, bu daraltýcý dönüþümlere izin verir ve derleyicinin sign conversion uyarýlarýný 
ne kadar agresif ürettiðine baðlý olarak bir uyarý oluþturabilir veya oluþturmayabilir. Örneðin, hem GCC hem de Clang, -Wsign-conversion derleyici 
bayraðý kullanýldýðýnda bu durumda uyarýlar oluþturacaktýr.

Ancak, iþaret dönüþtürülmesi gereken deðer constexpr ise ve karþý türde eþdeðer bir deðere dönüþtürülebilirse, iþaret dönüþümü daraltýcý olarak
kabul edilmez. Bu, derleyicinin dönüþümün güvenli olduðunu garanti edebileceði veya derleme sürecini durdurabileceði içindir.

                #include <iostream>

                void foo(unsigned int)
                {
                }

                int main()
                {
                    constexpr int s { 5 };                 // now constexpr
                    [[maybe_unused]] iþaretsiz int u { s }; // ok: x is constexpr and can be converted safely, not a narrowing conversion
                    foo(s);                                // ok: x is constexpr and can be converted safely, not a narrowing conversion

                    return 0;
                }

Bu durumda, s constexpr olduðu ve dönüþtürülmesi gereken deðerin (5) iþaretsiz bir deðer olarak temsil edilebildiði için, dönüþüm daraltýcý olarak 
kabul edilmez ve sorunsuz bir þekilde implicit olarak gerçekleþtirilebilir.

Bu daraltmayan dönüþüm, constexpr int'ten constexpr std::size_t'ye, çok fazla kullanacaðýmýz bir þeydir.

std::vector'ýn uzunluðu ve indeksleri size_type tipindedir

10.7 Dersinde -- Typedefs and type aliases, typedef'lerin ve type alias'larýn genellikle bir türün deðiþebileceði durumlarda
(ör. çünkü implementation-defined) bir tür için bir isme ihtiyaç duyduðumuzda sýklýkla kullanýldýðýný belirttik. Örneðin std::size_t,
genellikle iþaretsiz long veya iþaretsiz long long olan bazý büyük iþaretsiz integral tipi için bir typedef'tir.

Standart kütüphane konteynýr sýnýflarýnýn her biri, konteynýrýn uzunluðu (ve destekleniyorsa indeksleri) için kullanýlan tip için bir alias olan 
size_type (bazen T::size_type olarak yazýlýr) adýnda bir nested typedef üye tanýmlar.

size_type'ý genellikle belgelerde ve derleyici uyarýlarý/hata mesajlarýnda görürsünüz. Örneðin, std::vector'ýn size() üye fonksiyonu için bu belge,
size()'ýn size_type deðeri döndürdüðünü belirtir.

Ýlgili Ýçerik

Nested typedef'leri 15.3 -- Nested types (member types) dersinde ele alýyoruz.

size_type neredeyse her zaman std::size_t için bir alias'týr, ancak nadir durumlarda farklý bir tipi kullanmak üzere geçersiz kýlýnabilir.

Anahtar Ýçgörü

size_type, standart kütüphane konteynýr sýnýflarýnda tanýmlanan bir nested typedef'tir, konteynýr sýnýfýnýn uzunluðu (ve destekleniyorsa indeksleri)
için kullanýlan tipe karþýlýk gelir.

size_type varsayýlan olarak std::size_t'ye ayarlanýr ve bu neredeyse hiç deðiþtirilmediði için, size_type'ýn std::size_t için bir alias olduðunu
makul bir þekilde varsayabiliriz.
Bir konteynýr sýnýfýnýn size_type üyesine eriþirken, onu konteynýr sýnýfýnýn tamamen þablonlanmýþ adý ile scope qualify etmeliyiz.
Örneðin, std::vector<int>::size_type.

size() üye fonksiyonunu kullanarak bir std::vector'ýn uzunluðunu almak veya std::size() kullanmak

Bir konteynýr sýnýfý nesnesinden uzunluðunu size() üye fonksiyonunu kullanarak sorabiliriz (bu, uzunluðu iþaretsiz size_type olarak döndürür):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
                    return 0;
                }

                Bu, þunu yazdýrýr:

                length: 5
hem length() hem de size() üye fonksiyonuna sahip olan std::string ve std::string_view'in aksine, std::vector (ve C++'daki diðer çoðu konteynýr
türü) yalnýzca size()'a sahiptir. Ve þimdi bir konteynýrýn uzunluðunun bazen belirsiz bir þekilde boyutu olarak adlandýrýlmasýnýn nedenini
anladýnýz.

C++17'de, ayrýca std::size() non-member fonksiyonunu da kullanabiliriz (bu, konteynýr sýnýflarý için yalnýzca size() üye fonksiyonunu çaðýrýr).

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    std::cout << "uzunluk: " << std::size(prime); // C++17, `size_type` türünde ( `std::size_t` için takma ad) uzunluk döndürür

                    return 0;
                }

Eðer yukarýdaki yöntemlerden herhangi birini uzunluðu iþaretli bir türdeki bir deðiþkende saklamak için kullanmak istiyorsak, bu muhtemelen 
iþaretli/iþaretsiz dönüþüm uyarýsý veya hatasý sonucunu doðuracaktýr. Burada yapýlacak en basit þey, sonucu istenen türe static_cast etmektir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime { 2, 3, 5, 7, 11 };
                    int uzunluk { static_cast<int>(prime.size()) }; // dönüþ deðerini int'e static_cast
                    std::cout << "uzunluk: " << uzunluk ;

                    return 0;
                }

std::ssize() kullanarak std::vector'ýn uzunluðunu almak C++20
--------------------------------------------------------------
C++20, uzunluðu büyük bir iþaretli integral tür olarak döndüren std::ssize() adlý üye olmayan bir fonksiyonu tanýtýr (genellikle std::ptrdiff_t, 
ki bu genellikle std::size_t'nin iþaretli karþýlýðý olarak kullanýlan türdür):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    std::cout << "uzunluk: " << std::ssize(prime); // C++20, uzunluðu büyük bir iþaretli integral tür olarak döndürür

                    return 0;
                }

Bu, üç fonksiyon arasýnda uzunluðu iþaretli bir tür olarak döndüren tek fonksiyondur. Eðer bu yöntemi uzunluðu iþaretli bir türdeki bir deðiþkende
saklamak istiyorsanýz, birkaç seçeneðiniz var.

Öncelikle, int türü std::ssize() tarafýndan döndürülen iþaretli türden daha küçük olabilir, eðer uzunluðu bir int deðiþkenine atayacaksanýz, 
sonucu int'e static_cast etmelisiniz ki herhangi bir dönüþüm açýkça belirtilmiþ olsun (aksi takdirde daraltýcý dönüþüm uyarýsý veya hatasý
alabilirsiniz):

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    int uzunluk { static_cast<int>(std::ssize(prime)) }; // dönüþ deðerini int'e static_cast
                    std::cout << "uzunluk: " << uzunluk;

                    return 0;
                }

Alternatif olarak, derleyicinin deðiþken için kullanýlacak doðru iþaretli türü çýkarmasýný saðlamak için auto'yu kullanabilirsiniz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };
                    auto uzunluk { std::ssize(prime) }; // std::ssize() tarafýndan döndürülen iþaretli türü çýkarmak için auto kullanýn
                    std::cout << "uzunluk: " << uzunluk;

                    return 0;
                }

operator[] kullanarak dizi elemanlarýna eriþim sýnýrlama kontrolü yapmaz
------------------------------------------------------------------------
Önceki derste, subscript operatörünü (operator[]) tanýttýk:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3];  // indeksi 3 olan elemanýn deðerini yazdýr (7)
                    std::cout << prime[9]; // geçersiz indeks (tanýmsýz davranýþ)

                    return 0;
                }

operator[] sýnýrlama kontrolü yapmaz. operator[] için indeks non-const olabilir. Bunu daha sonra bir bölümde tartýþacaðýz.

at() üye fonksiyonunu kullanarak dizi elemanlarýna eriþim, çalýþma zamanýnda sýnýrlama kontrolü yapar
-----------------------------------------------------------------------------------------------------
Dizi konteyner sýnýflarý, bir diziyi eriþmek için baþka bir yöntem destekler. at() üye fonksiyonu, çalýþma zamanýnda sýnýrlama kontrolü ile dizi
eriþimi yapmak için kullanýlabilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime.at(3); // indeksi 3 olan elemanýn deðerini yazdýr
                    std::cout << prime.at(9); // geçersiz indeks (istisna fýrlatýr)

                    return 0;
                }

Yukarýdaki örnekte, prime.at(3) çaðrýsý, indeksin 3'ün geçerli olduðunu kontrol eder ve çünkü öyledir, dizi elemaný 3'e bir referans döndürür.
Bu deðeri daha sonra yazdýrabiliriz. Ancak, prime.at(9) çaðrýsý, 9'un bu dizi için geçerli bir indeks olmadýðý için (çalýþma zamanýnda) baþarýsýz
olur. Bir referans döndürmek yerine, at() fonksiyonu programý sonlandýran bir hata oluþturur.

Operator[] gibi, at() fonksiyonuna geçirilen indeks de non-const olabilir.

Her çaðrýda çalýþma zamaný sýnýrlarýný kontrol ettiði için, at() fonksiyonu operator[]'den daha yavaþ (ama daha güvenli) olabilir.
Daha az güvenli olmasýna raðmen, operator[] genellikle at() üzerinde tercih edilir, çünkü at() fonksiyonunu çaðýrmadan önce sýnýrlarýn
kontrol edilmesi daha iyidir, böylece baþtan beri geçersiz bir indeksle çaðýrmayýz.

constexpr iþaretliint ile std::vector Ýndeksleme
-----------------------------------------------
Bir std::vector'ü bir constexpr (signed) int ile indekslerken, derleyicinin bunu bir daraltma dönüþümü olmadan std::size_t'ye dönüþtürmesine 
izin verebiliriz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3] << '\n';     // tamam: 3 int'ten std::size_t'ye dönüþtürülür, daraltma dönüþümü deðil

                    constexpr int index { 3 };         // constexpr
                    std::cout << prime[index] << '\n'; // tamam: constexpr indeks std::size_t'ye dönüþtürülür, daraltma dönüþümü deðil

                    return 0;
                }

Non-constexpr Deðer ile std::vector Ýndeksleme
----------------------------------------------
Bir diziyi indekslemek için kullanýlan alt dizinler non-const olabilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    std::size_t index { 3 };           // non-constexpr
                    std::cout << prime[index] << '\n'; // operator[] bir std::size_t türünde indeks bekler, dönüþüm gerekmez

                    return 0;
                }

Ancak, en iyi uygulamalarýmýza göre , genellikle miktarlarý tutmak için iþaretsiz türlerini kullanmaktan kaçýnmak istiyoruz.
Alt dizinimiz non-constexpr bir iþaretlideðer olduðunda, sorunlarla karþýlaþýyoruz:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector prime{ 2, 3, 5, 7, 11 };

                    int index { 3 };                   // non-constexpr
                    std::cout << prime[index] << '\n'; // olasý uyarý: indeks std::size_t'ye dönüþtürülür, daraltma dönüþümü

                    return 0;
                }

Bu örnekte, indeks bir non-constexpr iþaretliint'tir. std::vector'ün bir parçasý olarak tanýmlanan operator[]'nin alt dizi türü size_type'dýr
(std::size_t için bir takma ad). Bu nedenle, print[index] dediðimizde, iþaretliint'imiz std::size_t'ye dönüþtürülmelidir.

Böyle bir dönüþüm tehlikeli olmamalýdýr (çünkü bir std::vector'ün indeksinin negatif olmamasý beklenir ve negatif olmayan bir iþaretlideðer güvenli 
bir þekilde iþaretsiz bir deðere dönüþtürülür). Ancak çalýþma zamanýnda gerçekleþtirildiðinde, bu bir daraltma dönüþümü olarak kabul edilir ve
derleyicinizin bu dönüþümün güvensiz olduðuna dair bir uyarý üretmesi gerekir (eðer üretmezse, uyarýlarýnýzý deðiþtirerek bunu yapmasý gerektiðini
düþünmelisiniz).

Dizi alt dizinleme yaygýn olduðu ve her bir dönüþümün bir uyarý oluþturacaðý için, bu durum kolayca derleme günlüðünüzü gereksiz uyarýlarla 
doldurabilir. Veya, "uyarýlarý hatalar olarak iþle" seçeneðini etkinleþtirdiyseniz, derlemeniz durur.

Bu sorunu önlemek için birçok olasý yol vardýr (örneðin, her bir dizi indeksleme iþleminde int'inizi std::size_t'ye static_cast yapýn),
ancak hiçbiri uygun deðildir - hepsi kaçýnýlmaz olarak kodunuzu bir þekilde karmaþýklaþtýrýr veya karýþtýrýr.

Bu durumda yapýlacak en basit þey, indeksiniz olarak std::size_t türünde bir deðiþken kullanmaktýr ve bu deðiþkeni yalnýzca indeksleme 
için kullanýn.

16.4 — std::vector'ün Geçirilmesi
---------------------------------
std::vector tipindeki bir nesne, diðer herhangi bir nesne gibi bir fonksiyona geçirilebilir. Bu, bir std::vector'ü deðer olarak geçirdiðimizde, 
pahalý bir kopya yapýlacaðý anlamýna gelir. Bu nedenle, genellikle bu tür kopyalarý önlemek için std::vector'ü (const) referans olarak geçiririz.

Bir std::vector ile, öðe tipi nesnenin tip bilgilerinin bir parçasýdýr. Bu nedenle, bir std::vector'ü bir fonksiyon parametresi olarak
kullandýðýmýzda, öðe tipini açýkça belirtmemiz gerekir:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector<int>& arr) // burada <int> belirtmeliyiz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes);

                    return 0;
                }

Farklý öðe tiplerine sahip std::vector'larýn geçirilmesi
--------------------------------------------------------
passByRef() fonksiyonumuz bir std::vector<int> beklediði için, farklý öðe tiplerine sahip vektörleri geçiremiyoruz:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector<int>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes);  // tamam: bu bir std::vector<int>

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl); // derleme hatasý: std::vector<double> std::vector<int>'e dönüþtürülemez

                    return 0;
                }

C++17 veya daha yenisiyle, bu sorunu çözmek için CTAD'yi kullanmayý deneyebilirsiniz:

                #include <iostream>
                #include <vector>

                void passByRef(const std::vector& arr) // derleme hatasý: CTAD, fonksiyon parametrelerini çýkarmak için kullanýlamaz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 }; // tamam: CTAD'yi kullanarak std::vector<int>'i çýkar
                    passByRef(primes);

                    return 0;
                }

CTAD, bir vektörün öðe tipini tanýmlandýðýnda baþlatýcýlardan çýkarmak için çalýþacak olsa da, CTAD (þu anda) fonksiyon parametreleriyle çalýþmaz.
Parametre tipinden sadece farklý olan aþýrý yüklenmiþ fonksiyonlar olduðunda bu tür bir sorunla daha önce karþýlaþtýk. Bu, fonksiyon þablonlarýný
kullanmanýn harika bir yeri! Öðe tipini parametrize eden bir fonksiyon þablonu oluþturabiliriz ve sonra C++ bu fonksiyon þablonunu gerçek tiplerle
fonksiyonlarý örnekleþtirmek için kullanacaktýr.

Ayný þablon parametre bildirimini kullanan bir fonksiyon þablonu oluþturabiliriz:

                #include <iostream>
                #include <vector>

                template <typename T>
                void passByRef(const std::vector<T>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i örnekleþtirecek

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i örnekleþtirecek

                    return 0;
                }

Yukarýdaki örnekte, const std::vector<T>& tipinde bir parametreye sahip olan passByRef() adýnda tek bir fonksiyon þablonu oluþturduk. 
T, önceki satýrdaki þablon parametre bildiriminde tanýmlanmýþtýr: template <typename T. T, çaðýranýn öðe tipini belirtmesine izin veren standart 
bir tip þablon parametresidir.

Bu nedenle, main() içinden passByRef(primes) çaðrýsýný yaptýðýmýzda (primes, std::vector<int> olarak tanýmlanmýþtýr), derleyici
void passByRef(const std::vector<int>& arr)'yi örnekleþtirecek ve çaðýracaktýr.

Main() içinden passByRef(dbl) çaðrýsýný yaptýðýmýzda (dbl, std::vector<double> olarak tanýmlanmýþtýr), derleyici 
void passByRef(const std::vector<double>& arr)'yi örnekleþtirecek ve çaðýracaktýr.

Böylece, herhangi bir öðe tipi ve uzunluða sahip std::vector argümanlarýný iþlemek için fonksiyonlarý örnekleþtirebilen tek bir fonksiyon þablonu 
oluþturduk!

Herhangi bir türdeki nesneyi kabul edecek bir fonksiyon þablonu da oluþturabiliriz:

                #include <iostream>
                #include <vector>

                template <typename T>
                void passByRef(const T& arr) // overloaded operator[] olan her türdeki nesneyi kabul eder
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i örnekleþtirir

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i örnekleþtirir

                    return 0;
                }

C++20'de ayný þeyi yapmak için kýsaltýlmýþ bir fonksiyon þablonu (bir auto parametresi aracýlýðýyla) kullanabiliriz:

                #include <iostream>
                #include <vector>

                void passByRef(const auto& arr) // abbreviated function template
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::vector primes{ 2, 3, 5, 7, 11 };
                    passByRef(primes); // tamam: derleyici passByRef(const std::vector<int>&)'i örnekleþtirir

                    std::vector dbl{ 1.1, 2.2, 3.3 };
                    passByRef(dbl);    // tamam: derleyici passByRef(const std::vector<double>&)'i örnekleþtirir

                    return 0;
                }

Her iki durumda da, derlenebilecek her türden bir argüman kabul edilir. Bu, belki de yalnýzca bir std::vector üzerinde çalýþmak istemeyeceðimiz 
fonksiyonlar yazarken arzu edilebilir. Örneðin, yukarýdaki fonksiyonlar ayrýca bir std::array, bir std::string veya belki de hiç düþünmediðimiz
baþka bir tür üzerinde de çalýþacaktýr. Bu yöntemin potansiyel dezavantajý, fonksiyonun, derlenebilir ancak semantik olarak mantýklý olmayan bir
türün nesnesini geçtiðinde hatalara yol açabileceðidir.

Dizi Uzunluðunda assert yapmak 
------------------------------
Yukarýda sunulanlara benzer bir fonksiyon þablonu düþünün:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printElement3(const std::vector<T>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr);

                    return 0;
                }

printElement3(arr) bu durumda iyi çalýþýrken, bu programda dikkatsiz bir programcýyý bekleyen potansiyel bir hata var. Gördün mü?

Yukarýdaki program, dizinin 3 indeksli elemanýnýn deðerini yazdýrýr. Bu, dizinin 3 indeksli geçerli bir elemaný olduðu sürece iyidir.
Ancak, derleyici, 3 indeksinin sýnýrlarýn dýþýnda olduðu dizileri geçmenize seve seve izin verir. Örneðin:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printElement3(const std::vector<T>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::vector arr{ 9, 7 }; // 2 elemanlý bir dizi (geçerli indeksler 0 ve 1)
                    printElement3(arr);

                    return 0;
                }

Bu, tanýmsýz bir davranýþa yol açar. Burada bir seçenek, arr.size() üzerinde assert yapmaktýr, bu da debug build konfigürasyonunda 
çalýþtýrýldýðýnda bu tür hatalarý yakalar. Çünkü std::vector::size() bir non-constexpr iþlev olduðu için, burada yalnýzca bir runtime assert
yapabiliriz.

Ýpucu

Daha iyi bir seçenek, dizi uzunluðunda iddia etmeniz gereken durumlarda std::vector kullanmaktan kaçýnmaktýr. Constexpr dizileri destekleyen
bir tür kullanmak (ör. std::array), muhtemelen daha iyi bir seçenektir, çünkü bir constexpr dizinin uzunluðunda static_assert yapabilirsiniz.
Bu konuyu gelecekteki 17.3 -- Passing and returning std::array dersinde ele alacaðýz.

*** BEST -> Baþtan beri kullanýcýnýn minimum uzunlukta bir vektör geçmesine dayanan fonksiyonlar yazmaktan kaçýnmaktýr.

16.5 — Std::vector'un döndürülmesi ve hareket semantiðine giriþ
---------------------------------------------------------------
Bir std::vector'ü bir fonksiyona geçirmemiz gerektiðinde, dizinin verisini pahalý bir kopya oluþturmadan geçirmek için (const) referans olarak 
geçiririz. Bu yüzden, bir std::vector'ü deðer olarak döndürmenin tamam olduðunu öðrenmek sizi þaþýrtabilir.

Nasýl yani?

Kopya semantiði
---------------
Aþaðýdaki programý düþünün:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr1 { 1, 2, 3, 4, 5 }; // { 1, 2, 3, 4, 5 }'i arr1'e kopyalar
                    std::vector arr2 { arr1 };          // arr1'i arr2'ye kopyalar

                    arr1[0] = 6; // arr1'i kullanmaya devam edebiliriz
                    arr2[0] = 7; // ve arr2'yi kullanmaya devam edebiliriz

                    std::cout << arr1[0] << arr2[0] << '\n';

                    return 0;
                }

arr2, arr1 ile baþlatýldýðýnda, std::vector'ün kopya constructor'ý çaðrýlýr, bu da arr1'i arr2'ye kopyalar. Bu durumda bir kopya yapmak tek 
mantýklý þeydir, çünkü hem arr1'in hem de arr2'nin baðýmsýz olarak yaþamasý gerekmektedir. Bu örnek, her baþlatma için iki kopya oluþturur.

Kopya semantiði terimi, nesnelerin kopyalarýnýn nasýl yapýldýðýný belirleyen kurallara atýfta bulunur. Bir türün kopya semantiðini desteklediðini 
söylediðimizde, bu türün nesnelerinin kopyalanabilir olduðunu, çünkü bu tür kopyalarý yapma kurallarýnýn tanýmlandýðýný ifade ederiz. 
Kopya semantiðinin çaðrýldýðýný söylediðimizde, bir nesnenin bir kopyasýný yapacak bir þey yaptýðýmýzý ifade ederiz.

Sýnýf türleri için, kopya semantiði genellikle kopya constructor'ý (ve kopya atama operatörü) aracýlýðýyla uygulanýr, bu da o türün nesnelerinin
nasýl kopyalandýðýný tanýmlar. Genellikle bu, sýnýf türünün her veri üyesinin kopyalanmasý sonucunu verir. Önceki örnekte,
std::vector arr2 { arr1 }; ifadesi kopya semantiðini çaðýrýr, bu da std::vector'ün kopya constructor'ýnýn çaðrýlmasýna ve ardýndan arr1'in her veri
üyesinin arr2'ye kopyalanmasýna yol açar. Sonuç olarak, arr1 arr2'ye eþittir (ancak arr2'den baðýmsýzdýr).

Kopya semantiðinin optimal olmadýðý durumlar
--------------------------------------------
Þimdi bu ilgili örneði düþünün:

                #include <iostream>
                #include <vector>

                std::vector<int> generate() // deðer olarak döndür
                {
                    // Zorunlu kopya elisyonunun uygulanmamasý için burada kasýtlý olarak adlandýrýlmýþ bir nesne kullanýyoruz
                    std::vector arr1 { 1, 2, 3, 4, 5 }; // { 1, 2, 3, 4, 5 }'i arr1'e kopyalar
                    return arr1;
                }

                int main()
                {
                    std::vector arr2 { generate() }; // generate()'un dönüþ deðeri ifadenin sonunda ölür

                    // generate()'un dönüþ deðerini burada kullanmanýn bir yolu yok
                    arr2[0] = 7; // sadece arr2'ye eriþimimiz var

                    std::cout << arr2[0] << '\n';

                    return 0;
                }

Bu sefer arr2 baþlatýldýðýnda, generate() fonksiyonundan dönen geçici bir nesne kullanýlarak baþlatýlýr. Önceki durumda, baþlatýcý gelecekteki
ifadelerde kullanýlabilecek bir lvalue idi, bu durumda, geçici nesne bir rvalue olacak ve baþlatma ifadesinin sonunda yok edilecektir.
Geçici nesne o noktadan sonra kullanýlamaz. Geçici (ve verisi) ifadenin sonunda yok edileceði için, veriyi geçiciden çýkarýp arr2'ye koymak için
bir yol bulmamýz gerekiyor.

Burada yapýlacak alýþýlmýþ þey, önceki örnekte olduðu gibi: kopya semantiðini kullanýn ve potansiyel olarak pahalý bir kopya yapýn. 
Bu þekilde arr2, geçici (ve verisi) yok edildikten sonra bile kullanýlabilecek kendi veri kopyasýna sahip olur.

Ancak, bu durumu önceki örnektekinden farklý kýlan þey, geçicinin zaten yok edilecek olmasýdýr. Baþlatma tamamlandýktan sonra, geçici verisine
daha fazla ihtiyaç duymaz (bu yüzden onu yok edebiliriz). Ýki veri kümesinin ayný anda var olmasýna ihtiyacýmýz yok. Bu tür durumlarda, 
potansiyel olarak pahalý bir kopya yapmak ve ardýndan orijinal veriyi yok etmek optimal deðildir.

Taþýma Semantiðine Giriþ
------------------------
Peki, arr2'nin geçici veriyi kopyalamak yerine "çalmasýna" izin veren bir yol olsaydý ne olurdu? arr2, verinin yeni sahibi olurdu ve verinin hiçbir
kopyasýnýn yapýlmasýna gerek kalmazdý. Verinin sahipliði bir nesneden diðerine aktarýldýðýnda, verinin taþýndýðýný söyleriz. Böyle bir taþýmanýn 
maliyeti genellikle önemsizdir (genellikle sadece iki veya üç pointer atamasý, bir dizi veriyi kopyalamaktan çok daha hýzlýdýr!).

Ek bir fayda olarak, ifadenin sonunda geçici nesne yok edildiðinde, artýk yok edilecek hiçbir verisi olmaz, bu yüzden bu maliyeti de ödememiz
gerekmez.

Bu, taþýma semantiðinin özüdür, bu da bir nesnenin verisinin baþka bir nesneye nasýl taþýndýðýný belirleyen kurallara atýfta bulunur. 
Taþýma semantiði çaðrýldýðýnda, taþýnabilen herhangi bir veri üyesi taþýnýr ve taþýnamayan herhangi bir veri üyesi kopyalanýr. 
Veriyi kopyalamak yerine taþýma yeteneði, taþýma semantiðini, özellikle pahalý bir kopyayý ucuz bir taþýma ile deðiþtirebildiðimizde,
kopya semantiðinden daha verimli hale getirebilir.

Anahtar nokta þudur ki; Taþýma semantiði, belirli durumlar altýnda, bazý veri üyelerinin sahipliðini bir nesneden diðerine ucuz bir þekilde
aktarmamýza izin veren bir optimizasyondur (daha pahalý bir kopya yapmak yerine). Taþýnamayan veri üyeleri kopyalanýr.

Taþýma Semantiði Nasýl Çaðrýlýr
-------------------------------
Normalde, bir nesne ayný türden bir nesne ile baþlatýlýyor veya atanýyorsa, kopya semantiði kullanýlacaktýr (kopya elided deðilse).
Ancak, aþaðýdakilerin tümü doðru olduðunda, kopya semantiði yerine taþýma semantiði çaðrýlýr:

*- Nesnenin türü taþýma semantiðini destekler.
*- Baþlatýcý veya atanmýþ nesne bir rvalue (geçici) nesnedir.
*- Taþýma elided deðildir.
* 
Ýþte üzücü haber: çok fazla tür taþýma semantiðini desteklemiyor. Ancak, std::vector ve std::string her ikisi de yapar!

Taþýma semantiðinin nasýl çalýþtýðýný 22. bölümde daha ayrýntýlý olarak inceleyeceðiz. Þimdilik, taþýma semantiðinin ne olduðunu ve hangi türlerin
taþýma yeteneðine sahip olduðunu bilmek yeterlidir.

std::vector gibi taþýma yeteneðine sahip türleri deðer olarak döndürebiliriz
----------------------------------------------------------------------------
Deðer olarak döndürme bir rvalue döndürdüðü için, döndürülen tür taþýma semantiðini destekliyorsa, döndürülen deðer hedef nesneye kopyalanmak
yerine taþýnabilir! Bu, bu türler için deðer olarak döndürmeyi son derece ucuz hale getirir!

Anahtar nokta þudur ki; Taþýma yeteneðine sahip türleri (std::vector ve std::string gibi) deðer olarak döndürebiliriz. Bu türler, pahalý bir kopya
yapmak yerine deðerlerini ucuz bir þekilde taþýyacaklardýr.

16.6 — Diziler ve Döngüler
--------------------------
Bu bölümün giriþ dersinde (16.1 -- Konteynerlara ve dizilere giriþ), birçok ilgili bireysel deðiþkenimiz olduðunda karþýlaþtýðýmýz
ölçeklenebilirlik sorunlarýný tanýttýk. Bu derste, sorunu tekrar ele alacaðýz ve ardýndan dizilerin bu tür sorunlarý nasýl zarif bir þekilde 
çözebileceðini tartýþacaðýz. 

Deðiþken ölçeklenebilirlik sorunu, tekrar ziyaret edildi
--------------------------------------------------------
Bir sýnýfýn öðrencilerinin ortalama test puanýný bulmak istediðimiz bir durumu düþünün. Bu örnekleri özlü tutmak için, sýnýfýn sadece 5 öðrencisi 
olduðunu varsayacaðýz.

Bunu bireysel deðiþkenler kullanarak nasýl çözebileceðimizi gösterelim:

                #include <iostream>

                int main()
                {
                    // 5 tam sayý deðiþkeni tahsis edin (her birinin farklý bir adý var)
                    int testScore1{ 84 };
                    int testScore2{ 92 };
                    int testScore3{ 76 };
                    int testScore4{ 81 };
                    int testScore5{ 56 };

                    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

                    std::cout << "Sýnýf ortalamasý: " << average << '\n';

                    return 0;
                }

Bu, tanýmlanacak çok fazla deðiþken ve çok fazla yazýdýr. 30 öðrenci veya 600 için ne kadar çok iþ yapmamýz gerektiðini hayal edin. Ayrýca,
yeni bir test puaný eklenirse, yeni bir deðiþkenin tanýmlanmasý, baþlatýlmasý ve ortalama hesaplamasýna eklenmesi gerekecektir. 
Ve böleni güncellemeyi hatýrladýnýz mý? Unuttuysanýz, artýk semantik bir hatanýz var. Mevcut kodu her deðiþtirdiðinizde, hatalar oluþturma riskiniz
vardýr.

Þimdiye kadar, bir sürü ilgili deðiþkenimiz olduðunda bir dizi kullanmamýz gerektiðini biliyorsunuz. O zaman bireysel deðiþkenlerimizi 
bir std::vector ile deðiþtirelim:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector testScore { 84, 92, 76, 81, 56 };
                    std::size_t length { testScore.size() };

                    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
                        / static_cast<int>(length) };

                    std::cout << "Sýnýf ortalamasý: " << average << '\n';

                    return 0;
                }

Bu daha iyi -- tanýmlanan deðiþken sayýsýný önemli ölçüde azalttýk ve ortalama hesaplamanýn böleni artýk doðrudan dizinin uzunluðundan belirleniyor.
Ancak ortalama hesaplama hala bir sorun, çünkü her öðeyi tek tek manuel olarak listelemek zorundayýz. Ve her öðeyi açýkça listelemek zorunda 
olduðumuz için, ortalama hesaplamamýz yalnýzca listelenen kadar çok öðesi olan diziler için çalýþýr. Eðer ayrýca diðer uzunluklardaki dizilerin
ortalamasýný da alabilmek istiyorsak, her farklý dizi uzunluðu için yeni bir ortalama hesaplama yazmamýz gerekecek.

Gerçekten ihtiyacýmýz olan þey, her dizi öðesine eriþebilmek için her birini açýkça listelememize gerek kalmadan bir yol.

Diziler ve döngüler
-------------------
Önceki derslerde, dizi subcriptlerinin sabit ifadeler olmasý gerekmediðini -- bunlarýn çalýþma zamaný ifadeleri olabileceðini belirttik. 
Bu, bir deðiþkenin deðerini bir index olarak kullanabileceðimiz anlamýna gelir.

Ayrýca, önceki örnekteki ortalama hesaplamada kullanýlan dizi indekslerinin artan bir dizi olduðunu da not edin: 0, 1, 2, 3, 4. Bu nedenle, 
bir deðiþkeni sýrayla 0, 1, 2, 3 ve 4 deðerlerine ayarlayabilecek bir yolumuz olsaydý, o zaman bu deðiþkeni dizi indeksi olarak kullanabiliriz 
yerine literaller. Ve bunu nasýl yapacaðýmýzý zaten biliyoruz -- bir for-döngüsü ile.

Yukarýdaki örneði, döngü deðiþkeninin dizi indeksi olarak kullanýldýðý bir for-döngüsü kullanarak yeniden yazalým:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector testScore { 84, 92, 76, 81, 56 };
                    std::size_t length { testScore.size() };

                    int average { 0 };
                    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
                        average += testScore[index];                      // add the value of element with index `index`
                    average /= static_cast<int>(length);                  // calculate the average

                    std::cout << "Average of Class: " << average << '\n';

                    return 0;
                }

Bu oldukça basit olmalý. index 0'da baþlar, testScore[0] ortalama'ya eklenir ve index 1 artýrýlýr. testScore[1] ortalama'ya eklenir ve index 2
artýrýlýr. Sonunda, index 5 artýrýldýðýnda, index < length yanlýþ olur ve döngü sona erer. Bu noktada, döngü testScore[0], testScore[1],
testScore[2], testScore[3] ve testScore[4]'ün deðerlerini ortalama'ya eklemiþtir. Son olarak, biriken deðerleri dizi uzunluðuna böleriz ve 
ortalamamýzý hesaplarýz.

Bu çözüm, bakým açýsýndan idealdir. Döngünün kaç kez yinelediði, dizinin uzunluðundan belirlenir ve döngü deðiþkeni, tüm dizi indekslemesini yapmak
için kullanýlýr. Artýk her bir dizi elemanýný manuel olarak listelememiz gerekmiyor.

Bir test skoru eklemek veya çýkarmak istiyorsak, yalnýzca dizi baþlatýcýlarýnýn sayýsýný deðiþtirebiliriz ve kodun geri kalaný daha fazla
deðiþiklik yapmadan hala çalýþýr!

Bir konteynýrýn her bir elemanýna belirli bir sýrayla eriþmek, konteynýrý dolaþma ( traversal ) veya konteynýrý gezinme olarak adlandýrýlýr.
Dolaþma ayrýca bazen konteynýr üzerinde yineleme veya konteynýr içinden yineleme olarak adlandýrýlýr.

Yazarýn Notu
------------
Konteynýr sýnýflarý, uzunluk ve indeksler için size_t tipini kullandýðýndan, bu derste aynýsýný yapacaðýz. iþaretli uzunluklarý ve indeksleri
kullanmayý gelecek ders olan 16.7 -- Arrays, loops, and sign challenge solutions dersinde tartýþacaðýz.

Þablonlar, diziler ve döngüler ölçeklenebilirliði açar
------------------------------------------------------
*-Diziler, her bir elemana isim vermeden birden çok nesneyi saklama olanaðý saðlar.
*-Döngüler, her bir elemaný açýkça listelemeden bir diziyi dolaþma olanaðý saðlar.
*-Þablonlar, eleman tipini parametrize etme olanaðý saðlar.

Birlikte, þablonlar, diziler ve döngüler, eleman tipine veya konteynýrda bulunan elemanlarýn sayýsýna bakýlmaksýzýn, bir konteynýrýn elemanlarý 
üzerinde iþlem yapabilecek kodlarý yazmamýza olanak saðlar!

Bunu daha da açýklamak için, yukarýdaki örneði yeniden yazalým, ortalama hesaplamasýný bir fonksiyon þablonuna çevirelim:

                #include <iostream>
                #include <vector>

                // std::vector'deki deðerlerin ortalamasýný hesaplamak için fonksiyon þablonu
                template <typename T>
                T calculateAverage(const std::vector<T>& arr)
                {
                    std::size_t length { arr.size() };

                    T average { 0 };                                  // eðer dizimiz T tipinde elemanlara sahipse, ortalamamýz da T tipinde olmalý
                    for (std::size_t index{ 0 }; index < length; ++index) // tüm elemanlarý döngüye al
                        average += arr[index];                            // tüm elemanlarý topla
                    average /= static_cast<int>(length);

                    return average;
                }

                int main()
                {
                    std::vector class1 { 84, 92, 76, 81, 56 };
                    std::cout << "Sýnýf 1'in ortalamasý: " << calculateAverage(class1) << '\n'; // 5 int'in ortalamasýný hesapla

                    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
                    std::cout << "Sýnýf 2'nin ortalamasý: " << calculateAverage(class2) << '\n'; // 4 double'ýn ortalamasýný hesapla

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Sýnýf 1'in ortalamasý: 77
                Sýnýf 2'nin ortalamasý: 81.75
Yukarýdaki örnekte, herhangi bir eleman tipine ve herhangi bir uzunluða sahip bir std::vector alýp, ortalamayý döndüren calculateAverage() 
adýnda bir fonksiyon þablonu oluþturduk. main() içinde, bu fonksiyonun 5 int elemaný olan bir diziyle veya 4 double elemaný olan bir diziyle
çaðrýldýðýnda eþit derecede iyi çalýþtýðýný gösteriyoruz!

calculateAverage() fonksiyonu, fonksiyon içinde kullanýlan operatörleri destekleyen herhangi bir T tipi için çalýþacaktýr (operator+=(T),
operator/=(int)). Bu operatörleri desteklemeyen bir T kullanmayý denerseniz, derleyici, örnekleþtirilmiþ fonksiyon þablonunu derlemeye çalýþýrken
hata verecektir.

Diziler ve döngülerle neler yapabileceðiz
-----------------------------------------
Bir eleman konteynerini bir döngü kullanarak nasýl gezineceðimizi bildiðimize göre, konteyner gezinmesini ne için kullanabileceðimize bakalým.
Genellikle bir konteyneri dört þey yapmak için geziniriz:

*- Mevcut elemanlarýn deðerine dayalý yeni bir deðer hesapla (ör. ortalama deðer, deðerlerin toplamý).
*- Mevcut bir elemaný ara (ör. tam eþleþme var mý, eþleþme sayýsýný say, en yüksek deðeri bul).
*- Her bir eleman üzerinde iþlem yap (ör. her bir elemaný çýktý olarak ver, tüm elemanlarý 2 ile çarp).
*- Elemanlarý yeniden sýrala (ör. elemanlarý artan sýrayla sýrala).
* 
Bu iþlemlerin ilk üçü oldukça basittir. Her bir elemaný uygun þekilde incelemek veya deðiþtirmek için tek bir döngü kullanabiliriz. Bir konteynerin
elemanlarýný yeniden sýralamak biraz daha zordur, çünkü bunu yapmak genellikle baþka bir döngünün içinde bir döngü kullanmayý gerektirir.
Bunu manuel olarak yapabiliriz, ancak genellikle bunu yapmak için standart kütüphaneden mevcut bir algoritmayý kullanmak daha iyidir. Algoritmalarý
tartýþacaðýmýz bir gelecek bölümde bunu daha ayrýntýlý olarak ele alacaðýz.

Diziler ve bir fazla hatalar -> For döngüsünde anlatýldý aynýsý olduðu için geçtim. 

16.7 — Diziler, döngüler ve iþaret sorunlarý çözümleri
------------------------------------------------------
4.5 -- iþaretsiz tam sayýlar ve neden onlardan kaçýnmalýyýz dersinde, genellikle miktarlarý tutmak için iþaretli deðerleri kullanmayý tercih 
ettiðimizi belirttik, çünkü iþaretsiz deðerler þaþýrtýcý þekillerde davranabilir. Ancak, 16.3 -- std::vector ve iþaretsiz uzunluk ve subscript 
problemi dersinde, std::vector'ün (ve diðer konteyner sýnýflarýnýn) uzunluk ve indeksler için iþaretsiz integral türü std::size_t'yi kullandýðýný
tartýþtýk. Bu, aþaðýdaki gibi sorunlara yol açabilir:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printReverse(const std::vector<T>& arr)
                {
                    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index iþaretsizdir
                    {
                        std::cout << arr[index] << ' ';
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

                    printReverse(arr);

                    return 0;
                }

                Bu kod, diziyi tersine çevirerek yazdýrmaya baþlar:

                9 1 2 8 3 7 6 4
Ve sonra tanýmsýz bir davranýþ sergiler. Çöp deðerler yazdýrabilir veya uygulamanýn çökmesine neden olabilir. Burada iki sorun var. Ýlk olarak, 
döngümüz index >= 0 olduðu sürece (diðer bir deyiþle, index pozitif olduðu sürece) çalýþýr, bu da index'in iþaretsiz olduðunda her zaman doðru 
olduðu anlamýna gelir. Bu yüzden döngü asla sona ermez.

Ýkincisi, indeksi 0 deðerinde azalttýðýmýzda, büyük bir pozitif deðere sarar, bu deðeri daha sonra bir sonraki yinelemede diziyi indekslemek 
için kullanýrýz. Bu, sýnýrlarýn dýþýnda bir indekstir ve tanýmsýz davranýþa neden olur. Dizimiz boþsa ayný sorunla karþýlaþýrýz.

Ve bu tür özel sorunlarý çözmenin birçok yolu olsa da, bu tür sorunlar hata mýknatýlarýdýr.

Bir döngü deðiþkeni için iþaretli bir tür kullanmak bu tür sorunlardan daha kolay kaçýnýr, ancak kendi zorluklarý vardýr. Ýþte iþaretli bir indeks
kullanan yukarýdaki sorunun bir versiyonu:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printReverse(const std::vector<T>& arr)
                {
                    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index iþaretlidir
                    {
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

                    printReverse(arr);

                    return 0;
                }

Bu versiyon, amaçlandýðý gibi iþlev görür, ancak eklenen iki static_cast nedeniyle kod da karmaþýktýr. arr[static_cast<std::size_t>(index)]
özellikle okumasý zordur. Bu durumda, güvenliði okunabilirlik pahasýna önemli ölçüde artýrdýk.

Ýþte iþaretli indeks kullanmanýn baþka bir örneði:

                #include <iostream>
                #include <vector>

                // Bir std::vector'deki ortalama deðeri hesaplamak için fonksiyon þablonu
                template <typename T>
                T calculateAverage(const std::vector<T>& arr)
                {
                    int length{ static_cast<int>(arr.size()) };

                    T average{ 0 };
                    for (int index{ 0 }; index < length; ++index)
                        average += arr[static_cast<std::size_t>(index)];
                    average /= length;

                    return average;
                }

                int main()
                {
                    std::vector testScore1 { 84, 92, 76, 81, 56 };
                    std::cout << "Sýnýf 1 ortalamasý: " << calculateAverage(testScore1) << '\n';

                    return 0;
                }
Kodumuzun static_cast'lerle dolmasý oldukça kötü. Peki ne yapmalýyýz? Bu, ideal bir çözümün olmadýðý bir alandýr.

Burada birçok geçerli seçenek var, bunlarý en kötüden en iyisine doðru sýralayacaðýz. Diðerleri tarafýndan yazýlan kodda bunlarýn hepsini
muhtemelen karþýlaþacaksýnýz.

Yazarýn Notu
------------
Bu konuyu std::vector baðlamýnda tartýþacak olsak da, tüm standart kütüphane konteynerleri (örneðin std::array) benzer þekilde çalýþýr ve ayný
zorluklara sahiptir. Aþaðýdaki tartýþma, bunlarýn herhangi birine uygulanabilir.

Signed/unsigned dönüþüm uyarýlarýný kapatýn
-------------------------------------------     
Eðer signed/unsigned dönüþüm uyarýlarýnýn genellikle varsayýlan olarak devre dýþý býrakýldýðýný merak ediyorsanýz, bu konu ana nedenlerden biridir.
Her seferinde bir standart kütüphane konteynerini bir iþaretli indeks kullanarak alt dizinlediðimizde, bir iþaret dönüþüm uyarýsý oluþturulur. 
Bu, derleme günlüðünüzü gereksiz uyarýlarla hýzla doldurur, gerçekten meþru olan uyarýlarý boðar.

Bu yüzden, bir sürü signed/unsigned dönüþüm uyarýsýyla uðraþmak zorunda kalmamak için bir yol, bu uyarýlarý basitçe kapalý býrakmaktýr.

Bu en basit çözüm, ancak bunu önermiyoruz, çünkü bu ayný zamanda hatalara neden olabilecek meþru iþaret dönüþüm uyarýlarýnýn oluþturulmasýný da
engeller.

Unsigned döngü deðiþkeni kullanma
---------------------------------
Birçok geliþtirici, standart kütüphane dizi türlerinin iþaretsiz indeksler kullanmak üzere tasarlandýðýna inanýr, bu yüzden iþaretsiz indeksler 
kullanmalýyýz! Bu tamamen makul bir pozisyon. Sadece signed/unsigned uyumsuzluklarýna karþý ekstra dikkatli olmamýz gerekiyor. Mümkünse, indeks 
döngü deðiþkenini yalnýzca indeksleme için kullanýn.

Bu yaklaþýmý kullanmaya karar verirsek, hangi iþaretsiz türünü gerçekten kullanmalýyýz?

16.3 -- std::vector ve iþaretsiz uzunluk ve alt dizi problemi dersinde, standart kütüphane konteyner sýnýflarýnýn iç içe geçmiþ typedef size_type'ý
tanýmladýðýný belirttik, bu bir iþaretsiz integral türdür ve dizi uzunluklarý ve indeksler için kullanýlýr. size() üye fonksiyonu size_type
döndürür ve operator[] bir indeks olarak size_type kullanýr, bu yüzden indeksinizin türü olarak size_type kullanmak teknik olarak en tutarlý ve 
güvenli iþaretsiz türünü kullanmaktýr (bu, tüm durumlarda çalýþýr, hatta size_type'ýn size_t'den baþka bir þey olmadýðý son derece nadir durumda 
bile). Örneðin:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr { 1, 2, 3, 4, 5 };

                    for (std::vector<int>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';

                    return 0;
                }

Ancak, size_type kullanmanýn büyük bir dezavantajý vardýr: iç içe geçmiþ bir tür olduðu için, onu kullanmak için adýn tamamen þablonlu adýyla
açýkça öne çýkmamýz gerekiyor (yani std::vector<int>::size_type yazmak yerine sadece std::size_type yazmamýz gerekiyor). Bu, çok fazla yazmayý 
gerektirir, okumasý zordur ve konteyner ve öðe türüne baðlý olarak deðiþir.

Bir fonksiyon þablonu içinde kullanýldýðýnda, þablon argümanlarý için T'yi kullanabiliriz. Ancak türü typename anahtar kelimesiyle öne çýkarmamýz
da gerekiyor:

                #include <iostream>
                #include <vector>

                template <typename T>
                void printArray(const std::vector<T>& arr)
                {
                    // baðýmlý tip için typename anahtar kelime öneki gereklidir
                    for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';
                }

                int main()
                {
                    std::vector arr { 9, 7, 5, 3, 1 };

                    printArray(arr);

                    return 0;
                }
Eðer typename anahtar kelimesini unutursanýz, derleyiciniz muhtemelen size onu eklemenizi hatýrlatacaktýr.

Bazen dizi tipinin, döngüyü daha kolay okunabilir hale getirmek için takma adlaþtýrýldýðýný görebilirsiniz:

                using arrayi = std::vector<int>;
                for (arrayi::size_type index { 0 }; index < arr.size(); ++index)
                
Daha genel bir çözüm, derleyicinin bizim için dizi tipi nesnesinin tipini getirmesidir, böylece konteyner tipini veya þablon argümanlarýný açýkça
belirtmek zorunda kalmayýz. Bunu yapmak için, parametresinin tipini döndüren decltype anahtar kelimesini kullanabiliriz.

                // arr bazý referans olmayan bir tip
                for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index) // decltype(arr) std::vector<int>'i çözer

Ancak, arr bir referans tipi ise (ör. referansla geçirilen bir dizi), yukarýdaki iþe yaramaz. Ýlk önce arr'dan referansý kaldýrmamýz gerekiyor:

                template <typename T>
                void printArray(const std::vector<T>& arr)
                {
                    // arr bir referans veya referans olmayan tip olabilir
                    for (typename std::remove_reference_t<decltype(arr)>::size_type index { 0 }; index < arr.size(); ++index)
                        std::cout << arr[index] << ' ';
                }

Ne yazýk ki, bu artýk çok özlü veya kolay hatýrlanabilir deðil.

Çünkü size_type neredeyse her zaman size_t için bir typedef olduðu için, birçok programcý size_type'ý tamamen atlar ve daha kolay hatýrlanabilir
ve yazýlabilir std::size_t'yi doðrudan kullanýr:

                for (std::size_t index { 0 }; index < arr.size(); ++index)

Özel bellek ayýrýcýlarý kullanmýyorsanýz (ve muhtemelen kullanmýyorsunuzdur), bunun makul bir yaklaþým olduðuna inanýyoruz.

Ýþaretli döngü deðiþkeni kullanma
---------------------------------
Standart kütüphane konteyner tipleriyle çalýþmayý biraz daha zorlaþtýrsa da, iþaretli bir döngü deðiþkeni kullanmak, kodumuzun geri kalanýnda
uygulanan en iyi uygulamalarla tutarlýdýr (miktarlar için iþaretli deðerleri tercih etmek). Ve en iyi uygulamalarýmýzý ne kadar tutarlý bir þekilde
uygularsak, genel olarak o kadar az hatamýz olur.

Eðer iþaretli döngü deðiþkenleri kullanmayý düþünüyorsak, ele alýnmasý gereken üç konu var:

*- Hangi iþaretli tipi kullanmalýyýz?
*- Dizinin uzunluðunu iþaretli bir deðer olarak alma
*- Ýþaretli döngü deðiþkenini iþaretsiz bir indekse dönüþtürme

Hangi iþaretli tipi kullanmalýyýz?
----------------------------------
Burada üç (bazen dört) iyi seçenek var.

1 - Çok büyük bir diziyle çalýþmýyorsanýz, int kullanmak iyidir (özellikle int'in 4 byte olduðu mimarilerde). int, tipin aksi halde önemli olmadýðý
    her þey için kullandýðýmýz varsayýlan iþaretli integral tipidir ve burada aksi yönde bir sebep yoktur.

2 - Çok büyük dizilerle uðraþýyorsanýz veya biraz daha savunmacý olmak istiyorsanýz, garip adlý std::ptrdiff_t'yi kullanabilirsiniz. Bu typedef,
    genellikle std::size_t'nin iþaretli karþýlýðý olarak kullanýlýr.

3 - Çünkü std::ptrdiff_t'nin garip bir adý var, baþka iyi bir yaklaþým, indeksler için kendi tip takma adýnýzý tanýmlamaktýr:

                using Index = std::ptrdiff_t;

                // Örnek döngü index kullanarak
                for (Index index{ 0 }; index < static_cast<Index>(arr.size()); ++index)
Bunu bir sonraki bölümde tam bir örnekle göstereceðiz.

Kendi tip takma adýnýzý tanýmlamak da potansiyel bir gelecek faydasý vardýr: eðer C++ standart kütüphanesi bir gün iþaretli bir index olarak 
kullanýlmak üzere tasarlanmýþ bir tip yayýnlarsa, Index'i o tipi taklit etmek için deðiþtirmek veya Index'i ne olursa olsun o tipin adýyla bulup 
deðiþtirmek kolay olacaktýr.

4 - Döngü deðiþkeninizin tipini baþlatýcýdan türetebileceðiniz durumlarda, derleyicinin tipi çýkarmasýný saðlamak için auto kullanabilirsiniz:

                for (auto index{ static_cast<std::ptrdiff_t>(arr.size())-1 }; index >= 0; --index)

C++23'te, Z soneki std::size_t'nin iþaretli karþýlýðý olan bir tipin (muhtemelen std::ptrdiff_t) örneðini tanýmlamak için kullanýlabilir:

                for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)

Bir dizinin uzunluðunu iþaretli bir deðer olarak alma
---------------------------------------------------
1 - C++20'den önce, en iyi seçenek size() üye fonksiyonunun veya std::size()'ýn dönüþ deðerini iþaretli bir tipe static_cast yapmaktýr:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    for (auto index{ static_cast<Index>(arr.size())-1 }; index >= 0; --index)
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
Bu þekilde, arr.size() tarafýndan döndürülen unsigned deðer, karþýlaþtýrma operatörümüzün iki iþaretli iþlemciye sahip olmasý için bir iþaretli 
tipe dönüþtürülür. Ve iþaretli indeksler negatif olduðunda taþmayacaðý için, unsigned indeksler kullanýrken karþýlaþtýðýmýz wrap-around sorunu
olmayacak.

Bu yaklaþýmýn dezavantajý, döngümüzü karýþtýrmasý ve okumasýný zorlaþtýrmasýdýr. Bunu, uzunluðu döngüden çýkararak bu sorunu çözebiliriz:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    auto length{ static_cast<Index>(arr.size()) };
                    for (auto index{ length-1 }; index >= 0; --index)
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
2 - C++20'de, std::ssize() kullanýn:
C++'nýn tasarýmcýlarýnýn artýk iþaretli indekslerin yolunun bu olduðuna inandýðýný daha fazla kanýt istiyorsanýz, C++20'de std::ssize()'ýn
tanýtýlmasýný düþünün. Bu fonksiyon, bir dizi tipinin boyutunu iþaretli bir tip olarak (muhtemelen ptrdiff_t) döndürür.

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    for (auto index{ std::ssize(arr)-1 }; index >= 0; --index) // std::ssize C++20'de tanýtýldý
                        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

                    return 0;
                }
iþaretli döngü deðiþkenini unsigned bir indekse dönüþtürme

Bir kez iþaretli bir döngü deðiþkenine sahip olduðumuzda, bu iþaretli döngü deðiþkenini bir indeks olarak kullanmaya çalýþtýðýmýzda her zaman
implicit iþaret dönüþüm uyarýlarý alacaðýz. Bu yüzden iþaretli döngü deðiþkenimizi bir indeks olarak kullanmayý düþündüðümüz her yerde unsigned bir
deðere dönüþtürmenin bir yoluna ihtiyacýmýz var.

1 - Açýk seçenek, iþaretli döngü deðiþkenimizi unsigned bir indekse static_cast yapmaktýr. Bunu önceki örnekte gösteriyoruz. Ne yazýk ki, bunu 
    dizinin her alt dizininde yapmamýz gerekiyor ve bu, dizinin indekslerini okumasýný zorlaþtýrýyor.

2 - Kýsa bir adý olan bir dönüþüm fonksiyonu kullanýn:

                #include <iostream>
                #include <vector>

                using Index = std::ptrdiff_t;

                constexpr std::size_t toUZ(Index value)
                {
                    return static_cast<std::size_t>(value);
                }

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };

                    auto length { static_cast<Index>(arr.size()) };  // C++20'de, std::ssize() tercih edilir
                    for (auto index{ length-1 }; index >= 0; --index)
                        std::cout << arr[toUZ(index)] << ' '; // iþaret dönüþüm uyarýsýný önlemek için toUZ() kullanýn

                    return 0;
                }
Yukarýdaki örnekte, Index tipindeki deðerleri std::size_t tipindeki deðerlere dönüþtürmek üzere tasarlanmýþ toUZ() adýnda bir fonksiyon oluþturduk.
Bu, dizimizi arr[toUZ(index)] olarak indekslememize izin verir, bu da oldukça okunabilir.

3 - Özel bir görünüm kullanma

Önceki derslerde, std::string'in bir stringe sahip olduðunu, std::string_view'in ise baþka bir yerde var olan bir stringe bir görünüm sunduðunu
tartýþtýk. std::string_view'in güzel yanlarýndan biri, farklý türdeki stringlere (C tarzý string literalleri, std::string ve diðer std::string_view)
bakabilmesi ancak bizim için tutarlý bir arayüz saðlamasýdýr.

Standart kütüphane konteynerlerini iþaretli integral bir indeks kabul edecek þekilde deðiþtiremesek de, standart kütüphane konteyner sýnýfýný 
"görmek" için kendi özel görünüm sýnýfýmýzý oluþturabiliriz. Bunu yaparak, kendi arayüzümüzü istediðimiz gibi tanýmlayabiliriz.

Aþaðýdaki örnekte, indekslemeyi destekleyen herhangi bir standart kütüphane konteynerini görebilen bir özel görünüm sýnýfý tanýmlýyoruz.
Arayüzümüz iki þey yapacak:

*- Bize, iþaretli integral bir türle operator[] kullanarak elemanlara eriþme imkaný saðlar.
*- Konteynerin uzunluðunu iþaretli integral bir tür olarak alýr (çünkü std::ssize() yalnýzca C++20'de mevcuttur).

Bu, operator[]'i uygulamak için henüz ele almadýðýmýz bir konu olan operatör aþýrý yüklemeyi kullanýr. SignedArrayView'in nasýl uygulandýðýný 
bilmeye gerek yoktur, onu kullanabilirsiniz.

                SignedArrayView.h:


                #ifndef SIGNED_ARRAY_VIEW_H
                #define SIGNED_ARRAY_VIEW_H

                #include <cstddef> // for std::size_t and std::ptrdiff_t

                // SignedArrayView provides a view into a container that supports indexing
                // allowing us to work with these types using signed indices
                template <typename T>
                class SignedArrayView // C++17
                {
                private:
                    T& m_array;

                public:
                    using Index = std::ptrdiff_t;

                    SignedArrayView(T& array)
                        : m_array{ array } {}

                    // Overload operator[] to take a signed index
                    constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
                    constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
                    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
                };

                #endif

                main.cpp:


                #include <iostream>
                #include <vector>
                #include "SignedArrayView.h"

                int main()
                {
                    std::vector arr{ 9, 7, 5, 3, 1 };
                    SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

                    for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
                        std::cout << sarr[index] << ' '; // index using a iþaretlitype

                    return 0;
                }

Tek mantýklý seçenek: indekslemeyi tamamen býrakýn!

Yukarýda sunulan tüm seçeneklerin kendi dezavantajlarý vardýr, bu yüzden bir yaklaþýmý diðerine tercih etmek zordur. Ancak, diðerlerinden çok daha
mantýklý olan bir seçenek var: integral deðerlerle indekslemeyi tamamen býrakýn.

C++, indeks kullanmadan dizilerden geçmek için birkaç baþka yöntem saðlar. Ve indekslerimiz olmadýðýnda, bu signed/unsigned dönüþüm sorunlarýna 
girmez.

Ýndeksler olmadan dizi gezinmesi için iki yaygýn yöntem aralýklý döngüler ( range-based for loops ) ve yineleyicilerdir ( iterators ).
Eðer diziyi gezinmek için yalnýzca indeks deðiþkenini kullanýyorsanýz, indeks kullanmayan bir yöntemi tercih edin.

*** BEST -> Mümkün olduðunda integral deðerlerle dizi indekslemekten kaçýnýn.

16.8 — Range-based for loops (for-each) ( kapsam bazlý döngüler )
-----------------------------------------------------------------
16.6 -- Diziler ve döngüler dersinde, bir dizi deðiþkeni olarak bir döngü deðiþkeni kullanarak bir dizi üzerinde her bir öðeyi yinelemek için bir
for döngüsü kullandýðýmýz örnekleri gösterdik. Ýþte böyle bir örneðin daha:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    std::size_t length { fibonacci.size() };
                    for (std::size_t index { 0 }; index < length; ++index)
                       std::cout << fibonacci[index] << ' ';

                    std::cout << '\n';

                    return 0;
                }

For döngüleri, bir dizinin üzerinden geçmek için uygun ve esnek bir yol saðlasa da, kolayca hata yapýlabilir, bir fazla/bir eksik hatalarýna
eðilimlidir ve dizi indeksleme iþaret problemlarýna tabidir.

Bir dizinin (ileri doðru) üzerinden geçmek bu kadar yaygýn bir iþlem olduðu için, C++ baþka bir tür for döngüsünü destekler, buna range-based for 
döngüsü (bazen for-each döngüsü olarak da adlandýrýlýr) denir ve açýkça indeksleme yapmadan bir konteynerin üzerinden geçmeyi saðlar. Range-based 
for döngüleri daha basit, daha güvenli ve C++'daki tüm yaygýn dizi türleriyle (std::vector, std::array ve C tarzý diziler dahil) çalýþýr.

Range-based for döngüleri
-------------------------
Range-based for ifadesinin þu þekilde bir sözdizimi vardýr:

                for (element_declaration : array_object)
                   statement;

Bir range-based for döngüsü karþýlaþýldýðýnda, döngü array_object'teki her bir öðeyi yineleyecektir. Her yineleme için, geçerli dizi öðesinin
deðeri element_declaration'da bildirilen deðiþkene atanýr ve ardýndan statement ifadesi çalýþtýrýlýr.

En iyi sonuçlar için, element_declaration dizi öðeleriyle ayný türde olmalýdýr, aksi takdirde tür dönüþümü gerçekleþir.
Ýþte, fibonacci adlý bir dizideki tüm öðeleri yazdýrmak için bir range-based for döngüsü kullanan basit bir örnek:

#include <iostream>
#include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    for (int num : fibonacci) // fibonacci dizisi üzerinde yinele ve her deðeri `num`a kopyala
                       std::cout << num << ' '; // `num`un geçerli deðerini yazdýr

                    std::cout << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:
                0 1 1 2 3 5 8 13 21 34 55 89
Bu örnekte, dizinin uzunluðunu kullanmamýz veya diziyi indekslememiz gerekmiyor! Bu nasýl çalýþtýðýna daha yakýndan bakalým.
Bu range-based for döngüsü, fibonacci'nin tüm öðeleri üzerinde çalýþacaktýr. Ýlk yineleme için, num deðiþkenine ilk öðenin (0) deðeri atanýr. 
Ardýndan program, num'un (0) deðerini konsola yazdýran iliþkili ifadeyi çalýþtýrýr. Ýkinci yineleme için, num ikinci öðenin (1) deðerine atanýr. 
Ýliþkili ifade tekrar çalýþtýrýlýr, bu 1'i yazdýrýr. Range-based for döngüsü, her biri için iliþkili ifadeyi çalýþtýrarak dizinin her bir öðesi
üzerinde sýrayla yinelemeye devam eder, ta ki dizide yinelenecek baþka öðe kalmayana kadar. Bu noktada, döngü sona erer ve program yürütmesine
devam eder (bir satýr sonu yazdýrýr ve ardýndan iþletim sistemine 0 döndürür).

Anahtar nokta þudur ki; Bildirilen öðe (önceki örnekte num) bir dizi indeksi deðildir. Bunun yerine, üzerinde yinelendiði dizi öðesinin deðeri 
atanýr. Num, dizi öðesinin deðerine atanýr çünkü bu, dizi öðesinin kopyalandýðý anlamýna gelir (bu, bazý türler için pahalý olabilir).

*** BEST -> Konteynerleri dolaþýrken range-based for döngülerini düzenli for döngülerine tercih edin.

Aralýk-tabanlý for döngüleri ve auto anahtar kelimesi kullanarak tip çýkarýmý
-----------------------------------------------------------------------------
element_declaration'ýn, dizi öðeleriyle ayný tip olmasý gerektiði için (tip dönüþümünün oluþmasýný önlemek için), bu, auto anahtar kelimesini
kullanmanýn ve derleyicinin bizim için dizi öðelerinin tipini çýkarmasýnýn ideal bir durumdur. Bu þekilde, tipi gereksiz yere belirtmek zorunda
kalmayýz ve yanlýþ yazma riski yoktur.

Ýþte yukarýdaki ayný örnek, ancak num'ýn tipi auto olarak:
    
                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

                    for (auto num : fibonacci) // derleyici num'un tipini `int` olarak çýkaracak
                       std::cout << num << ' ';

                    std::cout << '\n';

                    return 0;
                }
Çünkü std::vector fibonacci'nin öðeleri int tipindedir, num bir int olarak çýkarýlacaktýr.

*** BEST -> Dizi öðesinin tipini derleyicinin çýkarmasý için aralýk-tabanlý for döngülerinde tip çýkarýmýný (auto) kullanýn.

Auto'yu kullanmanýn bir baþka avantajý da, dizi öðesinin tipi her güncellendiðinde (ör. int'ten long'a), auto otomatik olarak güncellenmiþ öðe
tipini çýkarýr, bunlarýn senkron kalmasýný saðlar (ve tip dönüþümünün oluþmasýný önler).

Öðe kopyalarýndan kaçýnýn, referanslarý kullanýn
------------------------------------------------
Bir dizi std::string üzerinde yineleyen aþaðýdaki aralýk-tabanlý for döngüsünü düþünün:

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // std::string literalleri için s soneki
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // std::vector<std::string>

                    for (auto word : words)
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Bu döngünün her yinelemesi için, words dizisinden sonraki std::string öðesi, word deðiþkenine atanýr (kopyalanýr). Bir std::string'i kopyalamak 
pahalýdýr, bu yüzden genellikle std::string'i fonksiyonlara const referans olarak geçiririz. Gerçekten bir kopyaya ihtiyacýmýz olmadýkça,
kopyalamasý pahalý olan þeylerin kopyalarýný yapmaktan kaçýnmak isteriz. Bu durumda, sadece kopyanýn deðerini yazdýrýyoruz ve sonra kopya yok
ediliyor. Bir kopya yapmaktan kaçýnmak ve sadece gerçek dizi öðesine referans vermek daha iyi olurdu.

Neyse ki, element_declaration'ýmýzý bir (const) referans yaparak tam olarak bunu yapabiliriz:

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // std::string literalleri için s soneki
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // std::vector<std::string>

                    for (const auto& word : words) // word artýk bir const referans
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Yukarýdaki örnekte, word artýk bir const referanstýr. Bu döngünün her yinelemesiyle, word sonraki dizi öðesine baðlanýr. Bu, pahalý bir kopya
yapmak zorunda kalmadan dizi öðesinin deðerine eriþmemizi saðlar. Referans const olmayan ise, ayrýca dizideki deðerleri deðiþtirmek için
kullanýlabilir (element_declaration'ýmýz deðerin bir kopyasý ise bu mümkün deðildir).

*** BEST -> Aralýk-tabanlý for döngülerinde, öðe bildirimi, normalde o öðe tipini (const) referans olarak geçirdiðinizde bir (const) referans
            kullanmalýdýr.

Normalde ucuz kopyalanabilir türler için `auto` kullanýrýz ve pahalý kopyalanabilir türler için `const auto&` kullanýrýz. Ancak range-based for
döngüleriyle birçok geliþtirici, daha geleceðe dayanýklý olduðu için her zaman `const auto&` kullanmanýn daha uygun olduðuna inanýr.

Örneðin, aþaðýdaki örneði düþünün:

                #include <iostream>
                #include <string_view>
                #include <vector>

                int main()
                {
                    using namespace std::literals;
                    std::vector words{ "peter"sv, "likes"sv, "frozen"sv, "yogurt"sv }; // std::vector<std::string_view>

                    for (auto word : words) // Normalde string_view deðeri geçeriz, bu yüzden burada auto kullanacaðýz
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Bu örnekte, `std::string_view` nesneleri içeren bir `std::vector`'ümüz var. `std::string_view` normalde deðer olarak geçtiði için, `auto` kullanmak
uygun görünüyor. Ancak, `words`'ün daha sonra bir `std::string` dizisine güncellendiðini düþünün.

                #include <iostream>
                #include <string>
                #include <vector>

                int main()
                {
                    using namespace std::literals;
                    std::vector words{ "peter"s, "likes"s, "frozen"s, "yogurt"s }; // burayý güncellemeliyiz

                    for (auto word : words) // Burayý da güncellememiz gerektiði muhtemelen açýk deðil
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }
Range-based for döngüsü sorunsuz bir þekilde derlenecek ve çalýþacaktýr, ancak `word` artýk bir `std::string` olacaktýr ve `auto` kullanýldýðý için
döngümüz sessizce `std::string` elemanlarýnýn pahalý kopyalarýný yapacaktýr. Büyük bir performans kaybý yaþadýk!

Bu durumun olmamasýný saðlamak için birkaç makul yol vardýr:

- Range-based for döngünüzde tür çýkarýmýný kullanmayýn. Eðer eleman türünü `std::string_view` olarak açýkça belirtmiþ olsaydýk, daha sonra dizi 
  `std::string`'e güncellendiðinde, `std::string` elemanlarý sorunsuz bir þekilde `std::string_view`'e dönüþtürülürdü. Eðer dizi daha sonra 
  dönüþtürülemez bir baþka türe güncellenirse, derleyici hata verecektir ve o noktada ne yapýlmasý gerektiðini anlayabiliriz.

- `auto` yerine range-based for döngünüzde tür çýkarýmý kullanýrken her zaman `const auto&` kullanýn. Bir referans üzerinden elemanlara eriþmenin 
  deðer üzerinden eriþmeye göre performans cezasý muhtemelen küçük olacaktýr ve bu, eleman türü daha sonra kopyalamasý pahalý olan bir þeye
  deðiþtirilirse bizi potansiyel olarak önemli performans cezalarýndan korur.

Ýpucu

Bir range-based for döngüsünde tür çýkarýmý kullanýyorsanýz, kopyalarla çalýþmak istemediðiniz sürece her zaman `const auto&` kullanmayý düþünün.
Bu, eleman türü daha sonra deðiþtirilse bile kopyalarýn yapýlmayacaðýný garanti eder.

Range-based for döngüleri ve diðer standart konteynýr türleri
-------------------------------------------------------------
Range-based for döngüleri, (decay olmamýþ) C-stil dizileri, `std::array`, `std::vector`, linked list, trees, ve maps dahil olmak üzere çeþitli dizi
türleriyle çalýþýr. Bunlarýn hiçbirini henüz ele almadýk, bu yüzden bunlarýn ne olduðunu bilmiyorsanýz endiþelenmeyin. Sadece range-based for
döngülerinin, yalnýzca `std::vector` üzerinde deðil, daha geniþ bir yelpazede yineleme yapmanýn esnek ve genel bir yolunu saðladýðýný unutmayýn:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; // burada std::array kullanýlýyor

                    for (auto number : fibonacci)
                    {
                        std::cout << number << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }

Mevcut elemanýn indeksini alma
------------------------------
Aralýklý döngüler, mevcut elemanýn dizi indeksini doðrudan almanýn bir yolunu saðlamaz. Bu, bir aralýklý döngünün yineleyebileceði birçok yapý
(örneðin std::list) indeksleri desteklemediði içindir.

Ancak, aralýklý döngüler her zaman ileri yönde yinelendiði ve elemanlarý atlamadýðý için, her zaman kendi sayaçýnýzý bildirebilir 
(ve artýrabilirsiniz). Ancak bunu yapacaksanýz, bir aralýklý döngü yerine normal bir döngü kullanmanýn daha iyi olup olmadýðýný düþünmelisiniz.

Ters aralýklý döngüler C++20
----------------------------
Aralýklý döngüler yalnýzca ileri sýradadýr. Ancak, bir diziyi ters sýrayla gezinmek istediðimiz durumlar vardýr. C++20'den önce, aralýklý döngüler
bu amaç için kolayca kullanýlamazdý ve baþka çözümler kullanýlmalýydý (genellikle normal döngüler).

Ancak, C++20 itibariyle, Ranges kütüphanesinin std::views::reverse özelliðini kullanarak elemanlarýn tersine bir görünümünü oluþturabilir ve 
yineleyebilirsiniz:

                #include <iostream>
                #include <ranges> // C++20
                #include <string_view>
                #include <vector>

                int main()
                {
                    using namespace std::literals; // for sv suffix for std::string_view literals
                    std::vector words{ "Alex"sv, "Bobby"sv, "Chad"sv, "Dave"sv }; // sorted in alphabetical order

                    for (const auto& word : std::views::reverse(words)) // create a reverse view
                        std::cout << word << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Dave
                Chad
                Bobby
                Alex
Ranges kütüphanesini henüz ele almadýk, bu yüzden bunu þimdilik yararlý bir sihir olarak düþünün.

16.9 — Enumeratörler kullanarak dizi indekslemesi ve uzunluðu
-------------------------------------------------------------
Dizilerle ilgili daha büyük belgelendirme sorunlarýndan biri, tamsayý indekslerinin programcýya indeksin anlamý hakkýnda bilgi saðlamamasýdýr.
5 test puanýný tutan bir dizi düþünün:

                #include <vector>

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    testScores[2] = 76; // bu kimin puanýný temsil ediyor?
                }
testScores[2] tarafýndan temsil edilen öðrenci kimdir? Bu açýk deðil.

Ýndekslemek için kapsamsýz enumeratörler kullanma
-------------------------------------------------
16.3 -- std::vector ve iþaretsiz uzunluk ve subscript problemi dersinde, std::vector<T>::operator[]'nin (ve subscript olabilen diðer 
C++ konteyner sýnýflarýnýn) indeksinin size_type türünde olduðunu, bu türün genellikle std::size_t için bir takma ad olduðunu tartýþtýk.
Bu nedenle, indekslerimiz ya std::size_t türünde olmalý, ya da std::size_t'ye dönüþen bir türde olmalýdýr.

Kapsamsýz enumerasyonlar, std::size_t'ye doðrudan dönüþtürüleceðinden, bu, kapsamsýz enumerasyonlarý indeksin anlamýný belgelemek için dizi 
indeksleri olarak kullanabileceðimiz anlamýna gelir:

                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    testScores[Students::stan] = 76; // þimdi stan'ýn test puanýný güncelliyoruz

                    return 0;
                }
Bu þekilde, dizinin her bir elemanýnýn neyi temsil ettiði çok daha açýk hale gelir. Enumeratörlerin doðrudan constexpr olduðu için, 
bir enumeratörün iþaretsiz integral bir türe dönüþtürülmesi daraltýcý bir dönüþüm olarak kabul edilmez, böylece signed/unsigned indeksleme 
sorunlarýndan kaçýnýlýr.

Non-constexpr Kapsamsýz Enumerasyon ile Ýndeksleme
--------------------------------------------------
Bir kapsamsýz enumerasyonun alt türü uygulamaya baðlýdýr (ve bu nedenle, ya bir iþaretli ya da iþaretsiz integral türü olabilir).
Enumeratörlerin doðal olarak constexpr olduðu için, kapsamsýz enumeratörlerle indekslemeye devam ettiðimiz sürece, iþaret dönüþümü 
sorunlarýyla karþýlaþmayýz.

Ancak, enumerasyon türünün non-constexpr bir deðiþkenini tanýmlar ve ardýndan std::vector'ümüzü bununla indekslersek, kapsamsýz enumerasyonlarý
bir iþaretli türüne varsayýlan herhangi bir platformda iþaret dönüþümü uyarýlarý alabiliriz:

                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };
                    Students::Names name { Students::stan }; // non-constexpr

                    testScores[name] = 76; // Student::Names'in iþaretlibir alt türüne varsayýlan bir durumda iþaret dönüþümü uyarýsý tetikleyebilir

                    return 0;
                }
name'i constexpr yapabilirdik (böylece bir constexpr iþaretli integral türünden std::size_t'ye yapýlan dönüþüm daraltýcý olmaz), 
ancak daha iyi bir yol var. Bunun yerine, enumerasyonun alt türünü açýkça bir iþaretsiz int olarak belirtebiliriz:

                #include <vector>

                namespace Students
                {
                    enum Names : unsigned int // alt türün açýkça iþaretsiz int olduðunu belirtir
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };
                    Students::Names name { Students::stan }; // non-constexpr

                    testScores[name] = 76; // ad iþaretsiz olduðu için bir iþaret dönüþümü deðil

                    return 0;
                }
Yukarýdaki örnekte, name'in artýk bir iþaretsiz int olduðu garantilendiðinden, iþaret dönüþümü sorunlarý olmadan bir std::size_t'ye dönüþtürülebilir

Sayým Enumeratörü Kullanma
--------------------------
Not edin ki, enumeratör listesinin sonunda max_students adýnda ekstra bir enumeratör tanýmladýk. Önceki tüm enumeratörler varsayýlan deðerleri
kullanýyorsa (ki bu önerilir), bu enumeratör önceki enumeratörlerin sayýsýný eþleþtiren bir varsayýlan deðere sahip olacaktýr.
Yukarýdaki örnekte, max_students deðeri 5'tir, çünkü önce 5 enumeratör tanýmlanmýþtýr. Resmi olmayan bir þekilde, bunu bir sayým enumeratörü olarak 
adlandýracaðýz, çünkü deðeri önceden tanýmlanmýþ enumeratörlerin sayýsýný temsil eder.

Bu sayým enumeratörü, önceki enumeratörlerin bir sayýsýna ihtiyaç duyduðumuz her yerde kullanýlabilir. Örneðin:

                #include <iostream>
                #include <vector>

                namespace Students
                {
                    enum Names
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        // gelecekteki enumeratörleri buraya ekleyin
                        max_students // 5
                    };
                }

                int main()
                {
                    std::vector<int> testScores(Students::max_students); // 5 öðeli bir vector oluþtur

                    testScores[Students::stan] = 76; // þimdi stan'a ait test skorunu güncelliyoruz

                    std::cout << "Sýnýfta " << Students::max_students << " öðrenci var\n";

                    return 0;
                }
max_students'ý iki yerde kullanýyoruz: öncelikle, max_students uzunluðunda bir std::vector oluþturuyoruz, böylece vector her öðrenci için bir öðeye
sahip olacak. Ayrýca max_students'ý öðrenci sayýsýný yazdýrmak için de kullanýyoruz.

Bu teknik ayrýca güzeldir çünkü eðer baþka bir enumeratör daha sonra eklenirse (max_students'ten hemen önce), o zaman max_students otomatik olarak
bir daha büyük olacak ve max_students'i kullanan tüm dizilerimiz yeni uzunluðu kullanmak üzere güncellenecektir.

                #include <vector>
                #include <iostream>

                namespace Ogrenciler
                {
                    enum Isimler
                    {
                        kenny, // 0
                        kyle, // 1
                        stan, // 2
                        butters, // 3
                        cartman, // 4
                        wendy, // 5 (eklendi)
                        // gelecekteki numaralandýrýcýlarý buraya ekleyin
                        max_ogrenciler // þimdi 6
                    };
                }

                int main()
                {
                    std::vector<int> testScores(Ogrenciler::max_ogrenciler); // þimdi 6 öðe ayýrýr

                    testScores[Ogrenciler::stan] = 76; // hala çalýþýr

                    std::cout << "Sýnýfta " << Ogrenciler::max_ogrenciler << " öðrenci var\n";

                    return 0;
                }

Bir sayým Enumeratörü ile dizi uzunluðunu doðrulama
---------------------------------------------------
Daha sýk olarak, bir dizi oluþtururken bir baþlatma listesi deðerlerini kullanýyoruz, bu diziyi numaralandýrýcýlarla indeksleme niyetiyle.
Bu tür durumlarda, konteynerin boyutunun sayým numaralandýrýcýmýza eþit olduðunu doðrulamak yararlý olabilir. Bu doðrulama tetiklenirse, 
ya numaralandýrýcý listemiz bir þekilde yanlýþtýr, ya da yanlýþ sayýda baþlatýcý saðlamýþýzdýr. Bu, bir numaralandýrýcýnýn numaralandýrmaya 
yeni eklenmesi, ancak dizisine yeni bir baþlatma deðeri eklenmemesi durumunda kolayca olabilir Örneðin:

                #include <cassert>
                #include <iostream>
                #include <vector>

                enum OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 5
                };

                int main()
                {
                    std::vector testScores { 78, 94, 66, 77, 14 };

                    // Test puanlarýnýn sayýsýnýn öðrenci sayýsýyla ayný olduðundan emin olun
                    assert(std::size(testScores) == max_ogrenciler);

                    return 0;
                }
Ýpucu

Eðer diziniz constexpr ise, o zaman static_assert kullanmalýsýnýz. std::vector constexpr'i desteklemez, ancak std::array (ve C tarzý diziler) yapar.

*** BEST -> constexpr dizinizin uzunluðunun sayým numaralandýrýcýnýza uyduðundan emin olmak için bir static_assert kullanýn.
            non-constexpr dizinizin uzunluðunun sayým numaralandýrýcýnýza uyduðundan emin olmak için bir assert kullanýn.

Diziler ve enum sýnýflarý
-------------------------
Kapsamsýz numaralandýrmalar, numaralandýrýcýlarýyla birlikte tanýmlandýklarý ad alanýný kirlettiði için, numaralandýrma zaten baþka bir kapsam 
bölgesinde (ör. bir ad alaný veya sýnýf) bulunmadýðý durumlarda enum sýnýflarýný kullanmak tercih edilir.

Ancak, enum sýnýflarýnýn integral tiplere doðrudan bir dönüþümü olmadýðý için, numaralandýrýcýlarýný dizi indeksleri olarak kullanmaya
çalýþtýðýmýzda bir sorunla karþýlaþýyoruz:

                #include <iostream>
                #include <vector>

                enum class OgrenciIsimleri // þimdi bir enum sýnýfý
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 5
                };

                int main()
                {
                    // derleme hatasý: OgrenciIsimleri'nden std::size_t'ye dönüþüm yok
                    std::vector<int> testScores(OgrenciIsimleri::max_ogrenciler);

                    // derleme hatasý: OgrenciIsimleri'nden std::size_t'ye dönüþüm yok
                    testScores[OgrenciIsimleri::stan] = 76;

                    // derleme hatasý: operator<<'nin çýktý yapabileceði herhangi bir tipe OgrenciIsimleri'nden dönüþüm yok
                    std::cout << "Sýnýfta " << OgrenciIsimleri::max_ogrenciler << " öðrenci var\n";

                    return 0;
                }
Bunu ele almanýn birkaç yolu var. En açýk olaný, numaralandýrýcýyý bir tam sayýya static_cast yapabiliriz:

                #include <iostream>
                #include <vector>

                enum class OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_ogrenciler // 6
                };

                int main()
                {
                    std::vector<int> testScores(static_cast<int>(OgrenciIsimleri::max_ogrenciler));

                    testScores[static_cast<int>(OgrenciIsimleri::stan)] = 76;

                    std::cout << "Sýnýfta " << static_cast<int>(OgrenciIsimleri::max_ogrenciler) << " öðrenci var\n";

                    return 0;
                
Ancak, bunu yazmak sadece can sýkýcý deðil, ayný zamanda kodumuzu önemli ölçüde karmaþýklaþtýrýyor. Daha iyi bir seçenek, 
13.4 dersinde tanýttýðýmýz yardýmcý fonksiyonu kullanmaktýr - Kapsamlý numaralandýrmalar (enum sýnýflarý), bu sayede enum sýnýflarýnýn
numaralandýrýcýlarýný tekli operatör+ kullanarak integral deðerlere dönüþtürmemizi saðlar.

                #include <iostream>
                #include <type_traits> // std::underlying_type_t için
                #include <vector>

                enum class OgrenciIsimleri
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    wendy, // 5
                    max_ogrenciler // 6
                };

                // Unary + operatörünü aþýrý yükleyin ve OgrenciIsimleri'ni altta yatan tipe dönüþtürün
                constexpr auto operator+(OgrenciIsimleri a) noexcept
                {
                    return static_cast<std::underlying_type_t<OgrenciIsimleri>>(a);
                }

                int main()
                {
                    std::vector<int> testScores(+OgrenciIsimleri::max_ogrenciler);

                    testScores[+OgrenciIsimleri::stan] = 76;

                    std::cout << "Sýnýfta " << +OgrenciIsimleri::max_ogrenciler << " öðrenci var\n";

                    return 0;
                }
Ancak, çok fazla numaralandýrýcýyý integral dönüþümlere yapmayý düþünüyorsanýz, muhtemelen bir ad alaný (veya sýnýf) içinde standart bir enum 
kullanmak daha iyidir.

16.10 — std::vector yeniden boyutlandýrma ve kapasite
-----------------------------------------------------
Bu bölümdeki önceki derslerde, konteynerleri, dizileri ve std::vector'ü tanýttýk. Ayrýca dizi öðelerine nasýl eriþileceði, bir dizinin uzunluðunu 
nasýl alacaðýmýz ve bir diziyi nasýl gezeceðimiz gibi konularý da tartýþtýk. Örneklerimizde std::vector'ü kullandýk, ancak tartýþtýðýmýz kavramlar
genellikle tüm dizi tiplerine uygulanabilir.

Bu bölümdeki kalan derslerde, std::vector'ü diðer dizi tiplerinin çoðundan önemli ölçüde farklý kýlan bir þeye odaklanacaðýz: oluþturulduktan sonra
kendini yeniden boyutlandýrma yeteneði.

Sabit boyutlu diziler vs dinamik diziler
----------------------------------------
Çoðu dizi tipinin önemli bir kýsýtlamasý vardýr: dizinin uzunluðu oluþturma noktasýnda bilinmelidir ve daha sonra deðiþtirilemez.
Bu tür dizilere sabit boyutlu diziler veya sabit uzunluklu diziler denir. Hem std::array hem de C tarzý diziler sabit boyutlu dizi tipleridir. 
Bunlarý bir sonraki bölümde daha fazla tartýþacaðýz.

Diðer yandan, std::vector bir dinamik dizidir. Bir dinamik dizi (veya yeniden boyutlandýrýlabilir dizi), boyutu oluþturulduktan sonra 
deðiþtirilebilen bir dizidir. Bu yeniden boyutlandýrýlabilir olma yeteneði, std::vector'ü özel kýlar.

Bir std::vector'ü çalýþma zamanýnda yeniden boyutlandýrma
---------------------------------------------------------
Bir std::vector, yeni istenen uzunlukla resize() üye fonksiyonunu çaðýrarak oluþturulduktan sonra yeniden boyutlandýrýlabilir:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector v{ 0, 1, 2 }; // 3 öðeli bir vektör oluþtur
                    std::cout << "Uzunluk: " << v.size() << '\n';

                    v.resize(5);              // 5 öðeye yeniden boyutlandýr
                    std::cout << "Uzunluk: " << v.size() << '\n';

                    for (auto i : v)
                        std::cout << i << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Uzunluk: 3
                Uzunluk: 5
                0 1 2 0 0
Burada iki þeyi not etmek önemlidir. Ýlk olarak, vektörü yeniden boyutlandýrdýðýmýzda, mevcut öðe deðerleri korundu! Ýkincisi, yeni öðeler deðer 
baþlatýlýr (sýnýf tipleri için varsayýlan baþlatmayý, diðer tipler için sýfýr baþlatmayý gerçekleþtirir). Bu nedenle, int tipindeki iki yeni öðe 
deðeri 0'a zero-initialize edildi.

Vektörler ayrýca daha küçük olacak þekilde yeniden boyutlandýrýlabilir:
-----------------------------------------------------------------------
                #include <iostream>
                #include <vector>

                void printLength(const std::vector<int>& v)
                {
                    std::cout << "Uzunluk: "	<< v.size() << '\n';
                }

                int main()
                {
                    std::vector v{ 0, 1, 2, 3, 4 }; // uzunluk baþlangýçta 5
                    printLength(v);

                    v.resize(3);                    // 3 öðeye yeniden boyutlandýr
                    printLength(v);

                    for (int i : v)
                        std::cout << i << ' ';

                    std::cout << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Uzunluk: 5
                Uzunluk: 3
                0 1 2

Bir `std::vector`'ün uzunluðu vs. kapasitesi 
--------------------------------------------
12 evlik bir sýra düþünün. Evlerin sayýsýnýn (veya evlerin sýrasýnýn uzunluðunun) 12 olduðunu söyleriz. Hangi evlerin þu anda iþgal edildiðini 
bilmek istesek... bunu baþka bir þekilde belirlememiz gerekir (örneðin, kapý zilini çalar ve birinin cevap verip vermediðini görürüz).
Sadece bir uzunluðumuz olduðunda, kaç tane þeyin var olduðunu biliriz.

Þimdi içinde þu anda 5 yumurta olan bir yumurta kartonunu düþünün. Yumurtalarýn sayýsýnýn 5 olduðunu söyleriz. Ancak bu baðlamda, baþka bir boyutla
ilgileniriz: kartonun dolu olduðunda kaç yumurta alabileceði. Yumurta kartonunun kapasitesinin 12 olduðunu söyleriz. Kartonda 12 yumurta için yer 
var ve yalnýzca 5 tanesi kullanýlýyor - bu nedenle, kartonu taþýrmadan 7 yumurta daha ekleyebiliriz. Hem bir uzunluðumuz hem de bir kapasitemiz 
olduðunda, kaç tane þeyin þu anda var olduðunu kaç tane þey için yer olduðundan ayýrt edebiliriz.

Bu noktaya kadar, yalnýzca bir `std::vector`'ün uzunluðundan bahsettik. Ancak `std::vector`'ün ayný zamanda bir kapasitesi de vardýr. 
Bir `std::vector` baðlamýnda, kapasite `std::vector`'ün ne kadar çok eleman için depolama alaný ayýrdýðýdýr ve uzunluk þu anda kaç elemanýn 
kullanýldýðýdýr.

Kapasitesi 5 olan bir `std::vector` 5 eleman için depolama alaný ayýrýr. Eðer vektör aktif olarak kullanýlan 2 eleman içeriyorsa, vektörün uzunluðu
(boyutu) 2'dir. Geri kalan 3 eleman için bellek ayrýlmýþtýr, ancak bunlar aktif olarak kullanýlmadýðý kabul edilir. Bunlar daha sonra vektörü
taþýrmadan kullanýlabilir.

Anahtar Bilgi

*- Bir vektörün uzunluðu, kaç elemanýn "kullanýmda" olduðudur.
*- Bir vektörün kapasitesi, kaç elemanýn bellekte ayrýldýðýdýr.

Bir `std::vector`'ün kapasitesini alma
--------------------------------------
Bir `std::vector`'den kapasitesini `capacity()` üye fonksiyonu aracýlýðýyla isteyebiliriz Örneðin:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
                }

                int main()
                {
                    std::vector v{ 0, 1, 2 }; // uzunluk baþlangýçta 3

                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    v.resize(5); // 5 elemana yeniden boyutlandýr

                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu aþaðýdakileri yazdýrýr:

                Capacity: 3  Length: 3
                0 1 2
                Capacity: 5  Length: 5
                0 1 2 0 0
Öncelikle, vektörü 3 elemanla baþlattýk. Bu, vektörün 3 eleman için depolama alaný ayýrmasýna (kapasite 3) neden olur ve tüm 3 eleman aktif olarak
kullanýlýr (uzunluk = 3). Daha sonra `resize(5)` çaðýrýrýz, yani artýk uzunluðu 5 olan bir vektör istiyoruz. Vektörün yalnýzca 3 eleman için 
depolama alaný var, ancak 5'e ihtiyacý var, bu yüzden vektör, ek elemanlarý tutmak için daha fazla depolama alaný almalýdýr. `resize()` çaðrýsý 
tamamlandýktan sonra, vektörün artýk 5 eleman için yer olduðunu (kapasite 5) ve tüm 5 elemanýn artýk kullanýmda olduðunu (uzunluk 5) görebiliriz.

Çoðu zaman `capacity()` fonksiyonunu kullanmanýz gerekmez, ancak vektörün depolamasýnýn ne olduðunu görebilmek için aþaðýdaki örneklerde çok
kullanacaðýz.

Depolamanýn yeniden tahsis edilmesi ve bu neden pahalýdýr
---------------------------------------------------------
Bir `std::vector` yönettiði depolama miktarýný deðiþtirdiðinde, bu sürece yeniden tahsis ( reallocation ) denir. Resmi olmayan bir þekilde,
yeniden tahsis süreci þöyle gider:

*- `std::vector` istenen sayýda eleman için kapasiteye sahip yeni bir bellek alýr. Bu elemanlar deðerle baþlatýlýr.
*- Eski bellekteki elemanlar yeni belleðe kopyalanýr (veya mümkünse taþýnýr). Eski bellek daha sonra sisteme geri verilir.
*- `std::vector`'ün kapasitesi ve uzunluðu yeni deðerlere ayarlanýr.

Dýþarýdan bakýldýðýnda, `std::vector`'ün yeniden boyutlandýrýldýðý görünür. Ancak içeride, bellek (ve tüm elemanlar) aslýnda deðiþtirilmiþtir!
Çalýþma zamanýnda yeni bellek almanýn sürecine dinamik bellek tahsisi denir. Bunu ileride ele alacaðýz. Yeniden tahsis genellikle dizinin her
elemanýnýn kopyalanmasýný gerektirdiðinden, yeniden tahsis pahalý bir iþlemdir. Sonuç olarak, yeniden tahsisi mümkün olduðunca kaçýnmak istiyoruz.

Anahtar nokta þudur ki; Yeniden tahsis genellikle pahalýdýr. Gereksiz yeniden tahsislerden kaçýnýn.

Uzunluk ve kapasiteyi neden ayýrt ediyoruz?
-------------------------------------------
Bir std::vector, gerektiðinde depolamasýný yeniden tahsis eder, ancak Melville’in Bartleby’si gibi, tercih etmez, çünkü depolamanýn reallocatesi
hesaplama açýsýndan pahalýdýr. Bir std::vector yalnýzca uzunluðunu takip ederse, her resize() isteði yeni uzunluða pahalý bir yeniden tahsis 
sonucunu doðurur. Uzunluðu ve kapasiteyi ayýrmak, std::vector'ün yeniden tahsislerin ne zaman gerektiði konusunda daha akýllý olabilmesini saðlar.
Aþaðýdaki örnek bunu gösterir:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Kapasite: " << v.capacity() << " Uzunluk:"	<< v.size() << '\n';
                }

                int main()
                {
                    // Uzunluðu 5 olan bir vektör oluþturun
                    std::vector v{ 0, 1, 2, 3, 4 };
                    v = { 0, 1, 2, 3, 4 }; // tamam, dizi uzunluðu = 5
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Vektörü 3 elemana yeniden boyutlandýr
                    v.resize(3); // burada 3 elemanlý bir liste de atayabilirdik
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Vektörü 5 elemana geri yeniden boyutlandýr
                    v.resize(5);
                    printCapLen(v);

                    for (auto i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Bu, aþaðýdakileri üretir:

                Kapasite: 5  Uzunluk: 5
                0 1 2 3 4
                Kapasite: 5  Uzunluk: 3
                0 1 2
                Kapasite: 5  Uzunluk: 5
                0 1 2 0 0
5 elemanla vektörümüzü baþlattýðýmýzda, kapasite 5 olarak ayarlandý, bu da vektörümüzün baþlangýçta 5 eleman için yer ayýrdýðýný gösterir. 
Uzunluk da 5 olarak ayarlandý, bu da tüm bu elemanlarýn kullanýmda olduðunu gösterir. v.resize(3) dedikten sonra, uzunluk daha küçük bir dizi 
için isteðimizi yerine getirmek üzere 3'e deðiþtirildi. Ancak, kapasitenin hala 5 olduðunu unutmayýn, bu da vektörün bir yeniden tahsis yapmadýðýný
anlamýna gelir!

Son olarak, v.resize(5) dedik. Çünkü vektör zaten 5 kapasiteye sahipti, yeniden tahsis yapmaya ihtiyaç duymadý. Sadece uzunluðu 5'e geri deðiþtirdi
ve son iki elemaný deðer baþlatmalý olarak ayarladý.

Uzunluðu ve kapasiteyi ayýrarak, bu örnekte aksi halde meydana gelecek 2 yeniden tahsisi önledik. Bir sonraki derste, bir vektöre birer birer 
eleman eklediðimiz örnekleri göreceðiz. Bu tür durumlarda, uzunluk her deðiþtiðinde yeniden tahsis etmeme yeteneði daha da önemlidir.

Anahtar nokta, Kapasiteyi uzunluktan ayrý olarak takip etmek, std::vector'ün uzunluk deðiþtiðinde bazý yeniden tahsislerden kaçýnmasýný saðlar.

Vektör indekslemesi uzunluða dayalýdýr, kapasiteye deðil
--------------------------------------------------------
subscript operatörünün (operator[]) ve at() üye fonksiyonunun geçerli indeksleri Vektörün uzunluðuna baðlýdýr, kapasitesine deðil.
Yukarýdaki örnekte, v'nin kapasitesi 5 ve uzunluðu 3 olduðunda, yalnýzca 0 ve 2 indeksleri geçerlidir. Uzunluðun 3 (dahil) ve kapasitenin 5 (hariç)
arasýndaki indekslerle elemanlar var olsa bile, indeksleri sýnýrlarýn dýþýnda kabul edilir.

*** Uyarý -> Bir subscript, yalnýzca 0 ile vektörün uzunluðu (kapasitesi deðil) arasýnda ise geçerlidir!

Bir std::vector'ü Küçültme ( shrinking )
----------------------------------------
Bir vektörü daha büyük hale getirmek için yeniden boyutlandýrmak, vektörün uzunluðunu artýrýr ve gerektiðinde kapasitesini artýrýr. Ancak,
bir vektörü daha küçük hale getirmek için yeniden boyutlandýrmak, yalnýzca uzunluðunu azaltýr ve kapasitesini deðil.

Artýk ihtiyaç duyulmayan birkaç öðenin belleðini geri almak için bir vektörü yeniden tahsis etmek kötü bir seçimdir. Ancak, artýk ihtiyaç 
duymadýðýmýz büyük sayýda öðeye sahip olduðumuz bir vektör durumunda, bellek israfý önemli olabilir.

Bu durumu ele almak için, std::vector'ün kapasitesini uzunluðuna uyacak þekilde küçültmesini isteyen shrink_to_fit() adýnda bir üye fonksiyonu
vardýr. Bu istek baðlayýcý deðildir, yani uygulamanýn bunu görmezden gelme hakký vardýr. Uygulamanýn en iyisi neyse ona baðlý olarak, uygulama 
isteði yerine getirebilir, kýsmen yerine getirebilir (örneðin, kapasiteyi azaltabilir ama tamamen deðil) veya isteði tamamen görmezden gelebilir.

Ýþte bir örnek:

                #include <iostream>
                #include <vector>

                void printCapLen(const std::vector<int>& v)
                {
                    std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
                }

                int main()
                {

                    std::vector<int> v(1000); // 1000 öðe için yer ayýr
                    printCapLen(v);

                    v.resize(0); // 0 öðeye yeniden boyutlandýr
                    printCapLen(v);

                    v.shrink_to_fit();
                    printCapLen(v);

                    return 0;
                }

                Yazarýn makinesinde, bu aþaðýdaki sonucu verir:

                Capacity: 1000  Length: 1000
                Capacity: 1000  Length: 0
                Capacity: 0  Length: 0
Gördüðünüz gibi, v.shrink_to_fit() çaðrýldýðýnda, vektör kapasitesini 0'a yeniden tahsis etti, 1000 öðe için belleði serbest býraktý.

16.11 — std::vector ve Yýðýn Davranýþý ( stack behavior )
---------------------------------------------------------
Bir kullanýcýnýn bir dizi deðer gireceði (örneðin bir dizi test skoru) bir program yazdýðýnýzý düþünün. Bu durumda, girecekleri deðerlerin sayýsý
derleme zamanýnda bilinmez ve programý her çalýþtýrdýklarýnda deðiþebilir. Bu deðerleri bir std::vector'de saklayacak ve/veya iþleyeceksiniz.

Þimdiye kadar tartýþtýðýmýz þeylere dayanarak, bunu nasýl ele alabileceðiniz konusunda birkaç yol olabilir:

Öncelikle, kullanýcýdan kaç giriþi olduðunu sormak, bu uzunlukta bir vektör oluþturmak ve ardýndan kullanýcýdan bu sayýda deðer girmesini 
isteyebilirsiniz. Bu kötü bir yaklaþým deðil, ancak kullanýcýnýn tam olarak kaç giriþi olduðunu önceden bilmesini ve sayarken hata yapmamýþ
olmasýný gerektirir. On veya yirmiden fazla öðeyi manuel olarak saymak sýkýcý olabilir - ve bizim onlar için bunu yapmamýz gerekirken neden
kullanýcýdan girilen deðerlerin sayýsýný saymasýný isteyelim ki?

Alternatif olarak, kullanýcýnýn belirli bir sayýdan fazla deðer girmek istemeyeceðini (örneðin 30) varsayabilir ve bu kadar çok öðeye sahip bir 
vektör oluþturabilir (veya yeniden boyutlandýrabiliriz). Sonra kullanýcýya bitene kadar (veya 30 giriþ deðerine ulaþana kadar) veri girmesini
isteyebiliriz. Bir vektörün uzunluðu, kullanýlan öðe sayýsýný ifade etmek üzere olduðundan, vektörü kullanýcýnýn gerçekte girdiði deðer sayýsýna
yeniden boyutlandýrabiliriz.

Bu yaklaþýmýn dezavantajý, kullanýcýnýn 30 deðer girmekle sýnýrlý olmasý ve bu sayýnýn çok fazla mý yoksa çok az mý olduðunu bilmiyor olmamýzdýr.
Kullanýcý daha fazla deðer girmek isterse, çok kötü.

Bu sorunu, kullanýcýnýn maksimum deðer sayýsýna ulaþtýðýnda vektörü daha büyük hale getirmek için biraz mantýk ekleyerek çözebiliriz. 
Ancak bu, artýk dizi boyutu yönetimini program mantýðýmýzla karýþtýrmamýz gerektiði anlamýna gelir ve bu, programýmýzýn karmaþýklýðýný önemli
ölçüde artýracaktýr (bu kaçýnýlmaz olarak hatalara yol açacaktýr).

Gerçek sorun burada, kullanýcýnýn kaç öðe girebileceðini tahmin etmeye çalýþmamýz, böylece vektörün boyutunu uygun þekilde yönetebilmemizdir.
Girilecek öðe sayýsýnýn gerçekten önceden bilinmediði durumlar için, daha iyi bir yaklaþým vardýr.

Ama oraya varmadan önce, kýsa bir süreliðine yan konuya geçmemiz gerekiyor.

Bir yýðýn ( stach ) nedir ? 
---------------------------
Benzeþim zamaný! Bir kafeteryadaki tabak yýðýnýný düþünün. Bilinmeyen bir nedenle, bu tabaklar ekstra aðýrdýr ve sadece bir seferde bir tanesi 
kaldýrýlabilir. Tabaklar yýðýldýðý ve aðýr olduðu için, tabak yýðýnýný yalnýzca iki þekilde deðiþtirebilirsiniz:

1- Yýðýnýn üstüne yeni bir tabak koyun (altýndaki tabaðý gizler, eðer varsa)
2- Yýðýnýn en üstündeki tabaðý çýkarýn (altýndaki tabaðý açýða çýkarýr, eðer varsa)

Yýðýnýn ortasýndan veya altýndan bir tabak eklemek veya çýkarmak izin verilmez, çünkü bu bir seferde birden fazla tabaðý kaldýrmayý gerektirir.
Bir yýðýna eklenen ve çýkarýlan öðelerin sýrasý, son giren ilk çýkar (LIFO) olarak tanýmlanabilir. Yýðýna eklenen son tabak, çýkarýlacak ilk tabak 
olacaktýr.

Programlamada Yýðýnlar
----------------------
Programlamada, bir yýðýn, öðelerin ekleme ve çýkarma iþlemlerinin LIFO þeklinde gerçekleþtiði bir konteyner veri tipidir. Bu genellikle push ve pop
adlý iki iþlem aracýlýðýyla uygulanýr:

---------------------------------------------------------------------------------------------------------
| Ýþlem Adý | Davranýþ                         | Gerekli mi? | Notlar                                   |
|-----------|----------------------------------|-------------|------------------------------------------|
| Push      | Yýðýnýn üstüne yeni bir öðe koy  | Evet        |                                          |
| Pop       | Yýðýnýn en üstündeki öðeyi çýkar | Evet        | Çýkarýlan öðeyi veya boþluk döndürebilir |
---------------------------------------------------------------------------------------------------------
Birçok yýðýn uygulamasý, isteðe baðlý olarak diðer kullanýþlý iþlemleri de destekler:

---------------------------------------------------------------------------------------------
| Ýþlem Adý     | Davranýþ                                  | Gerekli mi?  | Notlar         |
|---------------|-------------------------------------------|--------------|----------------|
| Top veya Peek | Yýðýnýn en üstündeki öðeyi al             | Ýsteðe Baðlý | Öðeyi çýkarmaz |
| Empty         | Yýðýnýn hiç öðesi olup olmadýðýný belirle | Ýsteðe Baðlý |                |
| Size          | Yýðýnda kaç tane öðe olduðunu say         | Ýsteðe Baðlý |                |
---------------------------------------------------------------------------------------------

Yýðýnlar programlamada yaygýndýr. 3.9 dersinde -- Entegre bir hata ayýklayýcý kullanma: Çaðrý yýðýný, hangi fonksiyonlarýn çaðrýldýðýný takip eden
çaðrý yýðýnýndan bahsettik. Çaðrý yýðýný... bir yýðýndýr! (Biliyorum, bu açýklama hayal kýrýklýðýna uðrattý). Bir fonksiyon çaðrýldýðýnda, 
o fonksiyon hakkýnda bilgi içeren bir giriþ, çaðrý yýðýnýnýn üstüne eklenir. Fonksiyon döndüðünde, o fonksiyon hakkýnda bilgi içeren giriþ,
çaðrý yýðýnýnýn üstünden çýkarýlýr. Bu þekilde, çaðrý yýðýnýnýn en üstü her zaman þu anda yürütülen fonksiyonu temsil eder ve her bir sonraki giriþ
önceki yürütülen fonksiyonu temsil eder.

Örneðin, bir yýðýnda nasýl push ve pop iþlemlerinin çalýþtýðýný gösteren kýsa bir dizi:

       (Yýðýn: boþ)
Push 1 (Yýðýn: 1)
Push 2 (Yýðýn: 1 2)
Push 3 (Yýðýn: 1 2 3)
Pop    (Yýðýn: 1 2)
Push 4 (Yýðýn: 1 2 4)
Pop    (Yýðýn: 1 2)
Pop    (Yýðýn: 1)
Pop    (Yýðýn: boþ)

C++'da Yýðýnlar
---------------
Bazý dillerde, bir yýðýn, kendi ayrý konteyner tipi olarak uygulanýr (diðer konteynerlerden ayrý). Ancak, bu oldukça sýnýrlayýcý olabilir.
Bir yýðýndaki tüm deðerleri yazdýrmak istediðimiz durumu düþünün, yýðýný deðiþtirmeden. Saf bir yýðýn arayüzü bunu yapmak için doðrudan bir 
yöntem saðlamaz.

C++'da, yýðýn gibi iþlemler yerine (üye fonksiyonlar olarak) bir uçta öðelerin etkin bir þekilde ekleme ve çýkarma iþlemlerini destekleyen mevcut
standart kütüphane konteyner sýnýflarýna eklendi (std::vector, std::deque ve std::list). Bu, bu konteynerlerin yýðýnlar olarak kullanýlmasýna
olanak saðlar ve yerel yeteneklerine ek olarak bunu yapar.

Bir parantez içinde…
---------------------
Tabak yýðýný benzetmesi iyi bir örnektir, ancak bir yýðýnýn bir dizi kullanýlarak nasýl uygulanabileceðini anlamamýza yardýmcý olacak daha iyi bir
benzetme yapabiliriz. Þu anda kaç tabak tuttuðu deðiþebilen bir tabak yýðýný yerine, birbiri üzerine yýðýlmýþ bir sütun posta kutusu düþünün.
Her posta kutusu sadece bir öðe tutabilir ve tüm posta kutularý boþ baþlar. Her posta kutusu, altýndaki posta kutusuna çivilenmiþtir ve sütunun
üstü zehirli dikenlerle kaplýdýr, bu yüzden yeni posta kutularý hiçbir yere eklenemez.

Posta kutusu sayýsýný deðiþtiremiyorsak, yýðýn benzeri bir davranýþ nasýl elde ederiz?
--------------------------------------------------------------------------------------
Öncelikle, yýðýnýn üst kýsmýnýn nerede olduðunu takip etmek için bir iþaretçi (post-it notu gibi) kullanýrýz - bu her zaman en düþük boþ posta 
kutusu olacaktýr. Baþlangýçta, yýðýn boþtur, bu yüzden iþaretçi alt posta kutusuna gider.

Bir öðeyi posta kutusu yýðýnýmýza ittiðimizde, onu iþaretli olan posta kutusuna (bu en düþük boþ posta kutusu) koyarýz ve iþaretçiyi bir posta
kutusu yukarý taþýrýz. Bir öðeyi yýðýndan çýkardýðýmýzda, iþaretçiyi bir posta kutusu aþaðý taþýrýz (bu yüzden en üstteki dolu posta kutusunu
gösterir) ve o posta kutusundaki öðeyi çýkarýrýz, böylece artýk boþtur.

Ýþaretçinin altýndaki öðeler “yýðýn üzerinde” olarak kabul edilir. Ýþaretçinin üzerinde veya üzerindeki öðeler yýðýn üzerinde deðildir.
Þimdi, iþaretçiyi uzunluk olarak adlandýrýn ve posta kutularýnýn sayýsýný kapasite olarak adlandýrýn…

Bu dersin geri kalanýnda, std::vector'ün yýðýn arayüzünün nasýl çalýþtýðýný inceleyeceðiz ve sonra, dersin baþýnda tanýtýlan meydan okumayý nasýl
çözdüðünü göstererek sona ereceðiz.

std::vector ile Yýðýn Davranýþý
-------------------------------
std::vector'deki yýðýn davranýþý, aþaðýdaki üye fonksiyonlar aracýlýðýyla uygulanýr:
-----------------------------------------------------------------------------------------------------------------------------------------------
| Fonksiyon Adý | Yýðýn Ýþlemi    | Davranýþ                                                | Notlar                                          |
|---------------|-----------------|---------------------------------------------------------|-------------------------------------------------|
| push_back()   | Itme            | Yýðýnýn üstüne yeni bir öðe koyar                       | Vectorün sonuna öðeyi ekler                     |
| pop_back()    | Çýkarma         | Yýðýnýn üstündeki öðeyi çýkarýr                         | Void döndürür, vectorün sonundaki öðeyi çýkarýr |
| back()        | Üst veya Göz At | Yýðýnýn üstündeki öðeyi alýr                            | Öðeyi çýkarmaz                                  |
| emplace_back()| Itme            | push_back()'ýn daha verimli olabilecek alternatif formu | Vectorün sonuna öðeyi ekler                     |
-----------------------------------------------------------------------------------------------------------------------------------------------
Bu fonksiyonlarýn bazýlarýný kullanan bir örneðe bir göz atalým:

                #include <iostream>
                #include <vector>

                void printStack(const std::vector<int>& stack)
                {
                    if (stack.empty()) // eðer stack.size == 0 ise
                        std::cout << "Boþ";

                    for (auto element : stack)
                        std::cout << element << ' ';

                    // \t bir tab karakteridir, metni hizalamaya yardýmcý olur
                    std::cout << "\tKapasite: " << stack.capacity() << "  Uzunluk " << stack.size() << "\n";
                }

                int main()
                {
                    std::vector<int> stack{}; // boþ yýðýn

                    printStack(stack);

                    stack.push_back(1); // push_back() bir öðeyi yýðýna iter
                    printStack(stack);

                    stack.push_back(2);
                    printStack(stack);

                    stack.push_back(3);
                    printStack(stack);

                    std::cout << "Üst: " << stack.back() << '\n'; // back() son öðeyi döndürür

                    stack.pop_back(); // pop_back() bir öðeyi yýðýndan çýkarýr
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    return 0;
                }

                GCC veya Clang'da, bu þunlarý yazdýrýr:

                Boþ     Kapasite: 0  Uzunluk: 0
                1       Kapasite: 1  Uzunluk: 1
                1 2     Kapasite: 2  Uzunluk: 2
                1 2 3   Kapasite: 4  Uzunluk: 3
                Üst:3
                1 2     Kapasite: 4  Uzunluk: 2
                1       Kapasite: 4  Uzunluk: 1
                Boþ     Kapasite: 4  Uzunluk: 0
Unutmayýn, uzunluk vectordeki öðe sayýsýdýr, bu durumda, yýðýnýmýzdaki öðe sayýsýdýr.
Alt dizin operatörü operator[] veya at() üye fonksiyonunun aksine, push_back() (ve emplace_back()) vectorün uzunluðunu artýrýr ve kapasite,
deðeri eklemek için yeterli olmadýðýnda yeniden tahsisat yapýlmasýna neden olur.
Yukarýdaki örnekte, vector 3 kez yeniden tahsis edilir (kapasite 0'dan 1'e, 1'den 2'ye ve 2'den 4'e).

Anahtar nokta,push_back() ve emplace_back(), bir std::vector'ün uzunluðunu artýrýr ve kapasite, deðeri eklemek için yeterli olmadýðýnda yeniden
tahsisat yapýlmasýna neden olur.

Bir öðeyi eklerken (`push_back`), `std::vector` genellikle bir sonraki öðe eklenirken baþka bir yeniden tahsis tetiklenmesini önlemek için biraz
ekstra kapasite ayýrýr. Bu ekstra kapasitenin ne kadar olduðu, `std::vector`'ün derleyicinin uygulamasýna baðlýdýr ve farklý derleyiciler
genellikle farklý þeyler yapar:

- GCC ve Clang, mevcut kapasiteyi ikiye katlar. Son yeniden boyutlandýrma tetiklendiðinde, kapasite 2'den 4'e çýkar.
- Visual Studio 2022, mevcut kapasiteyi 1.5 ile çarpar. Son yeniden boyutlandýrma tetiklendiðinde, kapasite 2'den 3'e deðiþtirilir.

Sonuç olarak, önceki programýn çýktýsý kullanýlan derleyiciye baðlý olarak biraz farklý olabilir.

Bir vektörü yeniden boyutlandýrmak, yýðýn davranýþýyla çalýþmaz
---------------------------------------------------------------
Bir vektörü yeniden tahsis etmek hesaplama açýsýndan pahalýdýr (vektörün uzunluðuna orantýlý), bu yüzden makul olduðunda yeniden tahsislerden 
kaçýnmak istiyoruz. Yukarýdaki örnekte, programýn baþýnda vektörü kapasitesi 3 olan bir vektöre yeniden boyutlandýrýrsak, vektörün 3 kez yeniden
tahsis edilmesini önleyebiliriz.
Aþaðýdaki gibi 18. satýrý deðiþtirirsek, programý tekrar çalýþtýrdýðýmýzda aþaðýdaki çýktýyý alýrýz:

                std::vector<int> stack(3); // parantez init vektörün kapasitesini 3'e ayarlar

                Çýktý:


                0 0 0   Kapasite: 3  Uzunluk: 3
                0 0 0 1         Kapasite: 4  Uzunluk: 4
                0 0 0 1 2       Kapasite: 6  Uzunluk: 5
                0 0 0 1 2 3     Kapasite: 6  Uzunluk: 6
                Üst: 3
                0 0 0 1 2       Kapasite: 6  Uzunluk: 5
                0 0 0 1         Kapasite: 6  Uzunluk: 4
                0 0 0   Kapasite: 6  Uzunluk: 3
Bu doðru deðil - bir þekilde yýðýnýmýzýn baþýnda bir sürü 0 deðeri var! Buradaki sorun, parantez baþlatmanýn (vektörün baþlangýç boyutunu ayarlamak
için) ve `resize()` fonksiyonunun hem kapasiteyi hem de uzunluðu ayarlamasýdýr. Vektörümüz kapasite 3 ile baþlýyor (bu bizim istediðimiz þey), 
ancak uzunluk da 3 olarak ayarlanýyor. Bu yüzden vektörümüz 0 deðerine sahip 3 elemanla baþlýyor. Daha sonra üzerine eklediðimiz elemanlar,
bu baþlangýç elemanlarýnýn üzerine eklenir.

`resize()` üye fonksiyonunun vektörün uzunluðunu deðiþtirmesi, elemanlara subscript olmak için indeksleri kullanmayý düþündüðümüzde iyidir (çünkü 
indekslerimizin geçerli olmasý için uzunluktan daha küçük olmasý gerekir), ancak vektörü bir yýðýn olarak kullandýðýmýzda sorunlara neden olur.

Aslýnda istediðimiz þey, kapasiteyi deðiþtirebilecek (gelecekteki yeniden tahsisleri önlemek için) ancak uzunluðu deðiþtirmeyecek (yýðýna yeni 
elemanlar eklemenin yan etkisi) bir yol.

`reserve()` üye fonksiyonu kapasiteyi deðiþtirir (ama uzunluðu deðil)
---------------------------------------------------------------------
`reserve()` üye fonksiyonu, mevcut uzunluðu deðiþtirmeden bir `std::vector`'ü yeniden tahsis etmek için kullanýlabilir. Ýþte ayný örnek,
ancak kapasiteyi ayarlamak için eklenmiþ bir `reserve()` çaðrýsý ile:

                #include <iostream>
                #include <vector>

                void printStack(const std::vector<int>& stack)
                {
                    if (stack.empty()) // if stack.size == 0
                        std::cout << "Boþ";

                    for (auto element : stack)
                        std::cout << element << ' ';

                    // \t bir sekme karakteridir, metni hizalamaya yardýmcý olur
                    std::cout << "\tKapasite: " << stack.capacity() << "  Uzunluk " << stack.size() << "\n";
                }

                int main()
                {
                    std::vector<int> stack{};

                    printStack(stack);

                    stack.reserve(6); // 6 eleman için yer ayýr (ama uzunluðu deðiþtirme)
                    printStack(stack);

                    stack.push_back(1);
                    printStack(stack);

                    stack.push_back(2);
                    printStack(stack);

                    stack.push_back(3);
                    printStack(stack);

                    std::cout << "Üst: " << stack.back() << '\n';

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    stack.pop_back();
                    printStack(stack);

                    return 0;
                }


                Yazarýn makinesinde, bu þunu yazdýrýr:

                Boþ   Kapasite: 0  Uzunluk: 0
                Boþ   Kapasite: 6  Uzunluk: 0
                1       Kapasite: 6  Uzunluk: 1
                1 2     Kapasite: 6  Uzunluk: 2
                1 2 3   Kapasite: 6  Uzunluk: 3
                En Üst: 3
                1 2     Kapasite: 6  Uzunluk: 2
                1       Kapasite: 6  Uzunluk: 1
                Boþ   Kapasite: 6  Uzunluk: 0
Gördüðünüz gibi, reserve(6) çaðrýldýðýnda kapasite 6'ya deðiþtirildi, ancak uzunluk etkilenmedi. std::vector tüm eklenen öðeleri barýndýrmak için 
yeterince büyük olduðu için daha fazla yeniden tahsisat yapýlmaz.

Anahtar nokta

*- resize() üye fonksiyonu vektörün uzunluðunu ve gerekirse kapasitesini deðiþtirir.
*- reserve() üye fonksiyonu sadece kapasiteyi (gerekirse) deðiþtirir.

Ýpucu

Bir std::vector'deki öðe sayýsýný artýrmak için:
*- Vektöre indeksleme yoluyla eriþirken resize() kullanýn. Bu, vektörün uzunluðunu deðiþtirir, böylece indeksleriniz geçerli olur.
*- Vektöre yýðýn iþlemleri kullanarak eriþirken reserve() kullanýn. Bu, vektörün uzunluðunu deðiþtirmeden kapasite ekler.

push_back() vs emplace_back()
-----------------------------
Hem push_back() hem de emplace_back() bir öðeyi yýðýna iter. Ýtelenen nesne zaten varsa, push_back() ve emplace_back() eþdeðerdir ve push_back()
tercih edilir.
Ancak, vektöre itmek için bir geçici nesne oluþturduðumuz durumlarda, emplace_back() daha verimli olabilir:

                #include <iostream>
                #include <string>
                #include <string_view>
                #include <vector>

                class Foo
                {
                private:
                    std::string m_a{};
                    int m_b{};

                public:
                    Foo(std::string_view a, int b)
                        : m_a { a }, m_b { b }
                        {}
                };

                int main()
                {
                    std::vector<Foo> stack{};

                    // Zaten bir nesnemiz varsa, push_back benzer verimliliktedir
                    Foo f{ "a", 2 };
                    stack.push_back(f);    // bunu tercih edin
                    stack.emplace_back(f);

                    // Bir geçici nesne oluþturup itmeye ihtiyacýmýz olduðunda, emplace_back daha verimlidir
                    stack.push_back({ "a", 2 });  // bir geçici nesne oluþturur ve sonra onu vektöre kopyalar
                    stack.emplace_back("a", 2);   // argümanlarý iletir, böylece nesne doðrudan vektörde oluþturulabilir (kopya yapýlmaz)

                    return 0;
                }

Yukarýdaki örnekte, Foo nesnelerinin bir vektörüne sahibiz. push_back({ "a", 2 }) ile, bir Foo geçici nesnesi oluþturuyor ve baþlatýyoruz,
bu daha sonra vektöre kopyalanýr. Kopyalamasý pahalý türler (std::string gibi) için bu kopya, performans kaybýna neden olabilir.

emplace_back() ile, geçmek için bir geçici nesne oluþturmamýza gerek yok. Bunun yerine, geçici nesneyi oluþturmak için kullanýlacak argümanlarý
geçeriz ve emplace_back() bunlarý vektöre iletir (mükemmel iletim adý verilen bir özellik kullanarak), burada vektör içindeki nesneyi oluþturmak
ve baþlatmak için kullanýlýrlar. Bu, aksi takdirde yapýlmýþ olacak bir kopyayý önler.

C++20'den önce, emplace_back() toplu baþlatmayla çalýþmaz.

*** BEST -> Konteynere eklemek için yeni bir geçici nesne oluþtururken emplace_back() tercih edin. Aksi takdirde push_back() tercih edin.

Yýðýn Ýþlemleri Kullanarak Sorunumuzu Çözme
-------------------------------------------
Dersin baþýnda tanýttýðýmýz sorunu nasýl ele alacaðýmýz artýk açýk olmalý. Önceden kaç öðenin std::vector'ümüze ekleneceðini bilmiyorsak,
bu öðeleri eklemek için yýðýn fonksiyonlarýný kullanmak yol olacaktýr.
Ýþte bir örnek:

                #include <iostream>
                #include <limits>
                #include <vector>

                int main()
                {
                    std::vector<int> scoreList{};

                    while (true)
                    {
                        std::cout << "Bir skor girin (veya bitirmek için -1): ";
                        int x{};
                        std::cin >> x;

                        if (!std::cin) // hatalý giriþi ele al
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }

                        // Eðer bittiysek, döngüden çýk
                        if (x == -1)
                            break;

                        // Kullanýcý geçerli bir öðe girdi, bu yüzden onu vektöre itelim
                        scoreList.push_back(x);
                    }

                    std::cout << "Skorlarýnýzýn listesi: \n";

                    for (const auto& score : scoreList)
                        std::cout << score << ' ';

                    return 0;
                }
Bu program, kullanýcýnýn test puanlarýný girmesine izin verir, her puaný bir vektöre ekler. Kullanýcý puan eklemeyi bitirdikten sonra, 
vektördeki tüm deðerler yazdýrýlýr.

Bu programda, hiçbir sayma, indeksleme veya dizi uzunluklarýyla uðraþmamýz gerekmiyor! Sadece programýn ne yapmasýný istediðimiz mantýðýna
odaklanabiliriz ve vektörün tüm depolama sorunlarýný halletmesine izin verebiliriz.

16.12 — std::vector<bool>
-------------------------
O.1 dersinde -- Bit bayraklarý ve bit manipülasyonu via std::bitset, std::bitset'in 8 Boolean deðerini bir byte'a sýkýþtýrma yeteneðine sahip 
olduðunu tartýþtýk. Bu bitler, std::bitset'in üye fonksiyonlarý aracýlýðýyla deðiþtirilebilir.

std::vector'ýn kollarýnda ilginç bir hile var. Boolean deðerler için daha fazla alan verimli olabilecek bir std::vector<bool> için özel bir 
uygulama var, benzer þekilde 8 Boolean deðerini bir byte'a sýkýþtýrýyor.

Bit manipülasyonu için tasarlanmýþ olan std::bitset'in aksine, std::vector<bool> bit manipülasyon üye fonksiyonlarýndan yoksundur.

std::vector<bool> Kullanýmý
---------------------------
Çoðunlukla, std::vector<bool> normal bir std::vector gibi çalýþýr:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector<bool> v { true, false, false, true, true };

                    for (int i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    // Change the Boolean value with index 4 to false
                    v[4] = false;

                    for (int i : v)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    return 0;
                }

                Yazarýn 64-bit makinesinde bu, þunu yazdýrýr:

                1 0 0 1 1
                1 0 0 1 0
std::vector<bool> ödünleþimler ( tradeoffs )
--------------------------------------------
Ancak, std::vector<bool>'un kullanýcýlarýn farkýnda olmasý gereken bazý tavizleri vardýr. Ýlk olarak, std::vector<bool> oldukça yüksek miktarda bir 
overhead'e sahiptir (yazarýn makinesinde sizeof(std::vector<bool>) 40 byte'dir), bu yüzden mimarinizin overhead'inden daha fazla Boolean deðeri 
ayýrmadýkça bellek tasarrufu saðlamazsýnýz.

Ýkinci olarak, std::vector<bool>'un performansý uygulamaya oldukça baðýmlýdýr (uygulamalarýn optimizasyon yapmak zorunda olmamasý, hatta iyi yapmak
zorunda olmamasý). Bu makaleye göre, oldukça optimize edilmiþ bir uygulama, alternatiflerden önemli ölçüde daha hýzlý olabilir. Ancak, kötü 
optimize edilmiþ bir uygulama daha yavaþ olacaktýr.

Üçüncü ve en önemlisi, std::vector<bool> bir vektör deðildir (bellekte ardýþýk olmasý gerekmez), ne de bool deðerlerini tutar 
(bir bit koleksiyonunu tutar), ne de C++'ýn bir konteynerin tanýmýný karþýlar.

std::vector<bool> çoðu durumda bir vektör gibi davranýrken, standart kütüphanenin geri kalanýyla tamamen uyumlu deðildir. Diðer öðe türleriyle 
çalýþan kod, std::vector<bool> ile çalýþmayabilir.

Örneðin, aþaðýdaki kod, T herhangi bir tür olduðunda çalýþýr, ancak bool deðil:

                template<typename T>
                void foo( std::vector<T>& v )
                {
                    T& first = v[0]; // get a reference to the first element
                    // Do something with first
                }

std::vector<bool> Kaçýnýn
-------------------------
Modern fikir birliði, genellikle std::vector<bool>'un kaçýnýlmasý gerektiði yönündedir, çünkü performans kazanýmlarýnýn, uygun bir konteyner
olmamasý nedeniyle uyumluluk sorunlarýna deðmeyeceði düþünülmektedir.

Ne yazýk ki, bu optimize edilmiþ sürüm std::vector<bool> varsayýlan olarak etkindir ve gerçekten bir konteyner olan optimize edilmemiþ bir sürüm
lehine devre dýþý býrakmanýn bir yolu yoktur. std::vector<bool>'un kullanýmdan kaldýrýlmasý çaðrýlarý olmuþtur ve bool'un sýkýþtýrýlmýþ bir
vektörünün neye benzeyeceðini belirlemek için çalýþmalar devam etmektedir (belki gelecekteki bir std::dynamic_bitset olarak).

Önerimiz þu þekildedir:

*- Derleme zamanýnda ihtiyaç duyduðunuz bit sayýsý bilindiðinde, saklamak için fazla sayýda Boolean deðeriniz olmadýðýnda (ör. 64k altýnda) ve sýnýrlý
   operatör ve üye fonksiyon seti (ör. yineleyici desteði eksikliði) gereksinimlerinizi karþýladýðýnda (constexpr) std::bitset kullanýn.

*- Boolean deðerlerin yeniden boyutlandýrýlabilir bir konteynerine ihtiyaç duyduðunuzda ve alan tasarrufu bir zorunluluk deðilse std::vector<char>'ý
   tercih edin. Bu tür, normal bir konteyner gibi davranýr.
*- Bit iþlemleri yapmanýz gereken bir dinamik bitset'e ihtiyaç duyduðunuzda, bir 3. tarafýn dinamik bitset uygulamasýný
   (örneðin boost::dynamic_bitset) tercih edin. Bu türler, standart kütüphane konteynerleri olmadýklarýnda bunlarýn standart kütüphane
   konteynerleri olduðunu iddia etmez.

*** BEST -> std::vector<bool>'dan ziyade constexpr std::bitset, std::vector<char> veya 3. taraf dinamik bitsetleri tercih edin.

16.x — Bölüm 16 özeti
---------------------
Teþvik Edici Sözler
-------------------
Bu bölüm kolay bir bölüm deðil. Çok fazla materyal üzerinden geçtik ve C++'ýn bazý kusurlarýný ortaya çýkardýk. Bunu baþardýðýnýz için tebrikler!
Diziler, C++ programlarýnýzdaki büyük miktarda gücün kilidini açan anahtarlardan biridir.

Bölüm Ýncelemesi
----------------
Bir konteyner, bir dizi isimsiz nesneyi (elementler olarak adlandýrýlýr) saklamak için bir veri tipidir. Genellikle, bir dizi ilgili deðerle 
çalýþmamýz gerektiðinde konteynerleri kullanýrýz.

Bir konteynerdeki elementlerin sayýsý genellikle uzunluk olarak adlandýrýlýr (bazen sayý). C++'da, bir konteynerdeki elementlerin sayýsý için boyut 
terimi de yaygýn olarak kullanýlýr. Çoðu programlama dilinde (C++ dahil), konteynerler homojendir, yani bir konteynerin elementlerinin ayný türde 
olmasý gerekir.

Konteynerler kütüphanesi, bazý yaygýn konteyner türlerini uygulayan çeþitli sýnýf türlerini içeren C++ standart kütüphanesinin bir parçasýdýr.
Bir konteyneri uygulayan bir sýnýf türü bazen bir konteyner sýnýfý olarak adlandýrýlýr.

Bir dizi, bir dizi deðeri ardýþýk olarak (yani her element, boþluk olmadan bitiþik bir bellek konumuna yerleþtirilir) saklayan bir konteyner veri
tipidir. Diziler, herhangi bir elemente hýzlý, doðrudan eriþim saðlar.

C++'da üç ana dizi tipi vardýr: (C tarzý) diziler, std::vector konteyner sýnýfý ve std::array konteyner sýnýfý.

std::vector, bir diziyi uygulayan C++ standart konteynerler kütüphanesindeki konteyner sýnýflarýndan biridir. std::vector, <vector> baþlýðýnda bir
sýnýf þablonu olarak tanýmlanmýþtýr, bir þablon tür parametresi ile elementlerin türünü tanýmlar. Bu nedenle, std::vector<int> bir std::vector'ü 
tanýmlar ve elementlerin türü int'tir.

Konteynerler genellikle, bir baþlatýcý listesi kullanarak konteynerin bir örneðini oluþturmamýza izin veren özel bir yapýlandýrýcýya sahiptir.
Bir konteyneri, bu element deðerleriyle oluþturmak için bir baþlatýcý deðerler listesi ile liste baþlatmayý kullanýn.

C++'da, dizi elementlerine eriþmenin en yaygýn yolu, dizi adýný ve alt dizin operatörünü (operator[]) kullanmaktýr. Belirli bir elementi seçmek 
için, alt dizin operatörünün köþeli parantezlerinin içine, hangi elementi seçmek istediðimizi belirleyen bir tamsayý deðeri saðlarýz. Bu tamsayý
deðeri bir alt dizin olarak adlandýrýlýr (veya gayri resmi olarak, bir indeks). Ýlk element, indeks 0 kullanýlarak eriþilir, ikinci element,
indeks 1 kullanýlarak eriþilir, vb... Dizinleme 1 yerine 0 ile baþladýðý için, C++'daki dizilerin sýfýr tabanlý olduðunu söyleriz.

operator[] herhangi bir sýnýrlama kontrolü yapmaz, yani indeksin 0 ile N-1 (dahil) arasýnda olup olmadýðýný kontrol etmez. operator[]'a geçersiz 
bir indeks geçirilirse, tanýmsýz bir davranýþa neden olur.

Diziler, doðrudan ve eþit hýzda her öðeye eriþime izin veren birkaç konteyner türünden biridir, yani konteynerdaki öðe sayýsýna bakýlmaksýzýn.

Bir sýnýf tipi nesnesi oluþtururken, eþleþen bir liste yapýcý, diðer eþleþen yapýcýlardan seçilir. Element deðerleri olmayan baþlatýcýlarla bir
konteyner (veya bir liste yapýcýsý olan herhangi bir tip) oluþtururken, doðrudan baþlatmayý kullanýn.

                std::vector v1 { 5 }; // `5` deðerini içeren 1 öðeli bir vektör tanýmlar.
                std::vector v2 ( 5 ); // öðelerin deðer baþlatýldýðý 5 öðeli bir vektör tanýmlar.
std::vector const yapýlabilir ancak constexpr yapýlamaz.

Standart kütüphane konteyner sýnýflarýnýn her biri, konteynerin uzunluðu (ve destekleniyorsa indeksler) için kullanýlan tip için bir takma ad olan
size_type adlý bir iç içe geçmiþ typedef üyesi tanýmlar (bazen T::size_type olarak yazýlýr). size_type neredeyse her zaman std::size_t için bir 
takma addýr, ancak nadir durumlarda farklý bir tip kullanmak üzere geçersiz kýlýnabilir. size_type'ýn std::size_t için bir takma ad olduðunu makul
bir þekilde varsayabiliriz.

Bir konteyner sýnýfýnýn size_type üyesine eriþirken, onu konteyner sýnýfýnýn tam þablonlu adýyla kapsam belirtmeliyiz. Örneðin, 
std::vector<int>::size_type.

Bir konteyner sýnýfý nesnesinden uzunluðunu size() üye fonksiyonu kullanarak sorabiliriz, bu da uzunluðu iþaretsiz size_type olarak döndürür. 
C++17'de, std::size() üye olmayan fonksiyonunu da kullanabiliriz.

C++20'de, std::ssize() üye olmayan fonksiyonu, uzunluðu büyük bir iþaretli integral tip olarak döndürür (genellikle std::ptrdiff_t, ki bu 
genellikle std::size_t'nin iþaretli karþýlýðý olarak kullanýlan tip).

Dizi öðelerine at() üye fonksiyonu kullanarak eriþim, çalýþma zamaný sýnýrlama kontrolü yapar (ve sýnýrlar dýþýnda kalýrsa std::out_of_range 
tipinde bir istisna atar). Ýstisna yakalanmazsa, uygulama sonlandýrýlýr.

Hem operator[] hem de at() üye fonksiyonu, const olmayan indekslerle indekslemeyi destekler. Ancak, her ikisi de indeksin size_type tipinde 
olmasýný bekler, bu da bir iþaretsiz integral tipidir. Bu, indeksler constexpr olmadýðýnda iþaret dönüþümü sorunlarýna neden olur.

std::vector tipinde bir nesne, diðer herhangi bir nesne gibi bir fonksiyona geçirilebilir. Yani, bir std::vector'ü deðer olarak geçirirsek,
pahalý bir kopya yapýlýr. Bu nedenle, genellikle bu tür kopyalarý önlemek için std::vector'ü (const) referans olarak geçiririz.
Herhangi bir öðe tipiyle bir std::vector'ü bir fonksiyona geçirebilmek için bir fonksiyon þablonu kullanabiliriz. Vektörün doðru uzunlukta olduðunu
garanti etmek için bir assert() kullanabilirsiniz.

Kopya semantiði terimi, nesnelerin kopyalarýnýn nasýl yapýldýðýný belirleyen kurallara atýfta bulunur. Kopya semantiðinin çaðrýldýðýný 
söylediðimizde, bir nesnenin bir kopyasýný yapacak bir þey yaptýk demektir.

Verinin sahipliði bir nesneden diðerine aktarýldýðýnda, verinin taþýndýðýný söyleriz.
Taþýma semantiði, bir nesnenin verisinin baþka bir nesneye nasýl taþýndýðýný belirleyen kurallara atýfta bulunur. Taþýma semantiði çaðrýldýðýnda,
taþýnabilecek herhangi bir veri üyesi taþýnýr ve taþýnamayan herhangi bir veri üyesi kopyalanýr. Veriyi kopyalamak yerine taþýma yeteneði, 
pahalý bir kopyayý ucuz bir taþýma ile deðiþtirebildiðimizde, taþýma semantiðini kopya semantiðinden daha verimli hale getirebilir.

Normalde, bir nesne ayný tip bir nesne ile baþlatýlýyor veya atanýyorsa, kopya semantiði kullanýlýr (kopyanýn elided olmadýðý varsayýlýr).
Taþýma semantiði, nesnenin tipinin taþýma semantiðini desteklediði ve baþlatýcý veya atanmýþ nesnenin bir rvalue olduðunda otomatik olarak 
kullanýlýr.

Taþýnabilir türler (örneðin `std::vector` ve `std::string` gibi) deðer olarak döndürülebilir. Bu türler, deðerlerini pahalý bir kopya yapmak yerine
ucuz bir þekilde taþýyacaktýr.

Bir konteynerin her bir elemanýna belirli bir sýrayla eriþmek, konteyneri dolaþma veya konteynerden geçme olarak adlandýrýlýr. Dolaþma ayrýca bazen
konteyner üzerinde yineleme veya konteynerden geçme olarak adlandýrýlýr.

Diziden geçmek için genellikle döngüler kullanýlýr, bir döngü deðiþkeni indeks olarak kullanýlýr. Bir fazla hatalarýna dikkat edin, burada döngü
gövdesi bir fazla veya bir eksik kez çalýþýr.

Aralýklý bir döngü (bazen de her biri için döngü olarak adlandýrýlýr), açýk indekslemeyi yapmadan bir konteynerin dolaþýlmasýna izin verir.
Konteynerleri dolaþýrken aralýklý döngüleri düzenli döngüler üzerinde tercih edin.

Dizi elemanýnýn türünü derleyicinin çýkarabilmesi için aralýklý döngülerle tür çýkarýmýný (auto) kullanýn. Eleman bildirimi, normalde o eleman
türünü (const) referans olarak geçireceðiniz zaman bir (const) referans kullanmalýdýr. Kopyalarla çalýþmanýz gerekmeyen sürece her zaman 
const auto& kullanmayý düþünün. Bu, eleman türü daha sonra deðiþtirilse bile kopyalarýn yapýlmadýðýndan emin olacaktýr.

Kapsamsýz enumerasyonlar indeks olarak kullanýlabilir ve indeksin anlamý hakkýnda bilgi saðlamaya yardýmcý olabilir. Dizi uzunluðunu temsil eden
bir enumeratör gerektiðinde ek bir "sayým" enumeratörü eklemek yararlýdýr. Bir dizinin uzunluðunun sayým enumeratörüne eþit olduðunu belirtmek veya
statik belirtmek için bir dizi, beklenen sayýda baþlatýcýyla baþlatýldýðýndan emin olabilirsiniz.

Dizinin uzunluðunun örnekleme noktasýnda tanýmlanmasý ve daha sonra deðiþtirilememesi gereken dizilere sabit boyutlu diziler veya sabit uzunluklu
diziler denir. Bir dinamik dizi (veya yeniden boyutlandýrýlabilir dizi olarak da adlandýrýlýr), boyutu örneklemeden sonra deðiþtirilebilen bir 
dizidir. Yeniden boyutlandýrýlabilir olma yeteneði, `std::vector`'ü özel kýlar.

Bir `std::vector`, yeni istenen uzunlukla `resize()` üye fonksiyonunu çaðýrarak örneklemeden sonra yeniden boyutlandýrýlabilir.

Bir `std::vector` baðlamýnda, kapasite `std::vector`'ün kaç eleman için depolama ayýrdýðýdýr ve uzunluk þu anda kullanýlan elemanlarýn sayýsýdýr.
Bir `std::vector`'ün kapasitesini `capacity()` üye fonksiyonu aracýlýðýyla sorgulayabiliriz.

Bir `std::vector` yönettiði depolama miktarýný deðiþtirdiðinde, bu sürece yeniden tahsis denir. Yeniden tahsis genellikle dizinin her elemanýnýn 
kopyalanmasýný gerektirdiðinden, yeniden tahsis pahalý bir iþlemdir. Sonuç olarak, yeniden tahsislerden makul olduðunca kaçýnmak istiyoruz.

subscript operatörünün (operator[]) ve `at()` üye fonksiyonunun geçerli indeksleri, vektörün uzunluðuna dayalýdýr, kapasitesine deðil.

`std::vector`'ün, vektörün kapasitesini uzunluðuna uyacak þekilde küçültme talebinde bulunan `shrink_to_fit()` adýnda bir üye fonksiyonu vardýr.
Bu talep baðlayýcý deðildir.

Bir yýðýnda eklenen ve çýkarýlan öðelerin sýrasý, son giren ilk çýkar (LIFO) olarak tanýmlanabilir. Yýðýna eklenen son tabak, çýkarýlan ilk tabak 
olacaktýr. Programlamada, bir yýðýn, elemanlarýn ekleme ve çýkarma iþlemlerinin LIFO þeklinde gerçekleþtiði bir konteyner veri türüdür. 
Bu genellikle `push` ve `pop` adlý iki iþlemle uygulanýr.

`std::vector` üye fonksiyonlarý `push_back()` ve `emplace_back()`, bir `std::vector`'ün uzunluðunu artýrýr ve kapasite, deðeri eklemek için yeterli
deðilse bir yeniden tahsisin gerçekleþmesine neden olur. Bir öðe eklerken yeniden tahsis tetiklendiðinde, `std::vector` genellikle bir sonraki öðe
eklenirken baþka bir yeniden tahsisin tetiklenmesini önlemek için biraz ekstra kapasite ayýrýr.

                `resize()` üye fonksiyonu, vektörün uzunluðunu ve gerekirse kapasiteyi deðiþtirir.
                `reserve()` üye fonksiyonu yalnýzca kapasiteyi deðiþtirir (gerekirse)

Bir std::vector'deki öðe sayýsýný artýrmak için:

- Indeksleme yoluyla bir vektöre eriþirken resize() kullanýn. Bu, vektörün uzunluðunu deðiþtirir, böylece indeksleriniz geçerli olur.
- Vektöre yýðýn iþlemleri kullanarak eriþirken reserve() kullanýn. Bu, vektörün uzunluðunu deðiþtirmeden kapasite ekler.
- Hem push_back() hem de emplace_back() bir öðeyi yýðýna iter. Ýtelenen nesne zaten varsa, push_back() ve emplace_back() eþdeðerdir.
  Ancak, bir geçici nesne oluþturup onu vektöre itmeye ihtiyaç duyduðumuz durumlarda, emplace_back() daha verimli olabilir. C++20 itibarýyla,
  push_back() yerine emplace_back() tercih etmek için pek bir neden yoktur.

Boolean deðerler için benzer þekilde 8 Boolean deðerini bir byte'a sýkýþtýran std::vector<bool> için daha fazla alan verimli bir uygulama vardýr.

std::vector<bool> bir vektör deðildir (bellekte ardýþýk olmasý gerekmez), ne de bool deðerleri tutar (bir bit koleksiyonu tutar), ne de C++'ýn bir
konteynerin tanýmýný karþýlar. std::vector<bool>, çoðu durumda bir vektör gibi davranýr, ancak standart kütüphanenin geri kalanýyla tamamen uyumlu
deðildir. Diðer öðe türleriyle çalýþan kod, std::vector<bool> ile çalýþmayabilir. Sonuç olarak, genellikle std::vector<bool> kaçýnýlmalýdýr.
*/