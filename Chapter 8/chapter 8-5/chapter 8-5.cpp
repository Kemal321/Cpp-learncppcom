#include <iostream>
#include <random>


int main()
{
    std::mt19937 mt{}; // Mersenne Twister algoritması kullanarak bir random sayı üreteci oluştur

    // 1 ile 6 arasında uniform sayılar üreten tekrar kullanılabilir bir random sayı üreteci oluştur
    std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

    // Bir dizi rastgele sayıyı ekrana yazdır
    for (int count{ 1 }; count <= 40; ++count)
    {
        std::cout << die6(mt) << '\t'; // burada bir zar atışı yap

        // Eğer 10 sayı yazdıysak, yeni bir satıra geç
        if (count % 10 == 0)
            std::cout << '\n';
    }
    return 0;
}
/*
                                                8.19 — Rastgele sayı üretimine giriş


Rastgele sayılar üretme yeteneği, belirli türdeki programlarda özellikle oyunlarda, istatistik modelleme programlarında ve şifreleme ve şifre 
çözme gerektiren kriptografik uygulamalarda kullanışlı olabilir. Oyunlara örnek olarak -- rastgele olaylar olmadan canavarlar her zaman aynı 
şekilde sizi saldırırdı, her zaman aynı hazineleri bulurdunuz, zindan düzeni asla değişmezdi, vb... ve bu iyi bir oyun yapmazdı.

Gerçek hayatta, genellikle madeni para atma, zar atma veya bir desteyi karıştırma gibi şeyler yaparak rastgelelik üretiriz. Bu olaylar aslında 
rastgele değildir, ancak o kadar çok fiziksel değişkeni içerir (örneğin, yerçekimi, sürtünme, hava direnci, momentum, vb.) ki tahmin etmek veya
kontrol etmek neredeyse imkansız hale gelir ve (sihirbaz değilseniz) her amaçlı olarak rastgele sonuçlar üretir.

Ancak bilgisayarlar fiziksel değişkenlerden yararlanacak şekilde tasarlanmamışlardır -- bilgisayarınız madeni para atamaz, zar atamaz veya gerçek 
kartları karıştıramaz. Modern bilgisayarlar, her şeyin ikili (0 veya 1) olduğu kontrol edilebilir bir elektrik dünyasında yaşar. Doğaları gereği 
bilgisayarlar, mümkün olduğunca tahmin edilebilir sonuçlar üretmek üzere tasarlanmışlardır. Bilgisayara 2 + 2'yi hesaplamasını söylediğinizde,
her zaman cevabın 4 olmasını istersiniz. Ara sıra 3 veya 5 olmasını istemezsiniz.

Bu nedenle, bilgisayarlar genellikle (en azından yazılım aracılığıyla) gerçekten rastgele sayılar üretebilme yeteneğine sahip değildir. 
Bunun yerine, modern programlar genellikle bir algoritma kullanarak rastgeleliği taklit eder.

Bu ders kapsamında, programlarda nasıl rastgele sayılar üretildiğine dair teorinin birçok yönünü kapsayacak ve gelecekteki derslerde
kullanacağımız bazı terimleri tanıtacağız.

                                                        Algoritmalar ve Durum

Öncelikle, algoritmalar ve durum kavramlarına bir göz atalım.

Bir algoritma, bir problemi çözmek veya bazı faydalı sonuçlar elde etmek için takip edilebilen sonlu bir talimat dizisidir.

Örneğin, diyelim ki patronunuz size sıralanmamış bir dizi ismi içeren küçük bir metin dosyası verir (her biri bir satırda), ve size listeyi 
sıralamanızı ister. Liste küçük olduğu ve bunu sık sık yapmayı beklemediğiniz için, bunu el ile sıralamaya karar verirsiniz. Bir listenin 
sıralanması için birden fazla yol vardır, ancak şöyle bir şey yapabilirsiniz:

* - Yeni, sıralanmış sonuçları içerecek boş bir liste oluşturun
* - Sıralanmamış isimler listesini tarayın ve alfabetik olarak ilk gelen ismi bulun.
* - Bu ismi sıralanmamış listesinden kesip, sıralı liste en altına yapıştırın.
* - Önceki iki adımı, sıralanmamış liste üzerinde daha fazla isim kalmayana kadar tekrarlayın.


Yukarıdaki adım kümesi, bir sıralama algoritmasını (doğal dil kullanarak) tanımlar. Algoritmalar doğası gereği yeniden kullanılabilirler - eğer
patronunuz size yarın başka bir liste sıralamanızı isterse, sadece aynı algoritmayı yeni liste üzerinde uygulayabilirsiniz.

Çünkü bilgisayarlar talimatları hızlı bir şekilde yürütebilir ve verilerle oynayabilir, algoritmalar genellikle programlama dilleri kullanılarak
yazılır, böylece görevleri otomatikleştirebiliriz. C++ dilinde, algoritmalar genellikle yeniden kullanılabilir fonksiyonlar olarak uygulanır.

İşte her bir sonraki sayının 1 artırıldığı bir sayı dizisi oluşturmak için basit bir algoritma:

                    #include <iostream>

                    int artiBir()
                    {
                        static int s_durum { 3 }; // Bu fonksiyon ilk çağrıldığında yalnızca ilk kez başlatılır

                        // Sonraki sayıyı oluştur

                        ++s_durum;        // İlk olarak durumu değiştiririz
                        return s_durum;   // Ardından yeni durumu kullanarak dizideki bir sonraki sayıyı oluştururuz
                    }

                    int main()
                    {
                        std::cout << artiBir() << '\n';
                        std::cout << artiBir() << '\n';
                        std::cout << artiBir() << '\n';

                        return 0;
                    }
Bu programın çıktısı:
                    4
                    5
                    6




Bu algoritma oldukça basittir. İlk defa plusOne() çağrıldığında, s_state değeri 3 olarak başlatılır. Ardından sıradaki sayı oluşturulur ve 
geri döndürülür. Bir algoritma, çağrılar arasında bazı bilgileri saklarsa durumlu( stateful ) olarak kabul edilir. Aksine, durumsuz ( stateless )
bir algoritma herhangi bir bilgi saklamaz (ve çağrıldığında çalışması için ihtiyaç duyduğu tüm bilgileri alır). ArtıBir() fonksiyonumuz durumlu 
bir fonksiyondur, çünkü son üretilen sayıyı saklamak için static bir değişken olan s_state'i kullanır. Algoritmalar üzerinde uygulandığında,
"durum" ( state ) terimi, durumlu değişkenlerde (çağrılar arasında saklananlar) tutulan geçerli değerlere atıfta bulunur.

Dizideki bir sonraki sayıyı oluşturmak için algoritmamız iki adımlı bir süreç kullanır:

1 - İlk olarak, mevcut durum (başlangıç ​​değerinden başlatılan veya önceki çağrıdan korunan) yeni bir durumu üretmek üzere değiştirilir.
2 - Ardından, yeni durumdan dizideki bir sonraki sayı oluşturulur.

Algoritmamız belirli bir giriş için (başlangıç değeri için sağlanan değer) her zaman aynı çıkış dizisini üretecek şekilde belirlenmiştir.
Bu nedenle, algoritmamız belirli ( deterministic ), yani aynı giriş için her zaman aynı çıkışı üretecektir.

Sözde rastgele sayı üreteçleri (PRNG'ler)
-----------------------------------------


Rastgeleliği taklit etmek için, programlar genellikle bir yarı rastgele sayı üreteci (PRNG) kullanır. Bir yarı rastgele sayı üreteci (PRNG),
özellikleri rastgele sayı dizisini taklit eden bir dizi sayı üreten bir algoritmadır.

Temel bir PRNG algoritması yazmak oldukça kolaydır. İşte 100 adet 16-bit yarı rastgele sayı üreten kısa bir PRNG örneği:
                        #include <iostream>

                        // Sadece açıklama amaçlı, bunu kullanmayın
                        unsigned int LCG16() // bizim PRNG
                        {
                            static unsigned int s_durum { 5323 };

                            // Sonraki sayıyı oluştur

                            // Bir sonraki sayının ne olacağını belirlemeyi zorlaştırmak için büyük sabitler ve kasıtlı taşmalar kullanarak
                            // durumu değiştiririz.

                            s_durum = 8253729 * s_durum + 2396403; // ilk olarak durumu değiştiririz
                            return s_durum % 32768; // ardından yeni durumu kullanarak dizideki bir sonraki sayıyı oluştururuz
                        }

                        int main()
                        {
                            // 100 rastgele sayıyı yazdır
                            for (int sayac { 1 }; sayac <= 100; ++sayac)
                            {
                                std::cout << LCG16() << '\t';

                                // 10 sayıyı yazdıysak, yeni bir satıra başla
                                if (sayac % 10 == 0)
                                    std::cout << '\n';
                            }

                            return 0;
                        }

Çıktı:

                        23070   27857   22756   10839   27946   11613   30448   21987   22070   1001
                        27388   5999    5442    28789   13576   28411   10830   29441   21780   23687
                        5466    2957    19232   24595   22118   14873   5932    31135   28018   32421
                        14648   10539   23166   22833   12612   28343   7562    18877   32592   19011
                        13974   20553   9052    15311   9634    27861   7528    17243   27310   8033
                        28020   24807   1466    26605   4992    5235    30406   18041   3980    24063
                        15826   15109   24984   15755   23262   17809   2468    13079   19946   26141
                        1968    16035   5878    7337    23484   24623   13826   26933   1480    6075
                        11022   19393   1492    25927   30234   17485   23520   18643   5926    21209
                        2028    16991   3634    30565   2552    20971   23358   12785   25092   30583

Her sayı, öncekine göre oldukça rastgele görünüyor.

LCG16(), yukarıdaki plusOne() örneğimize oldukça benzer! LCG16() fonksiyonuna başlangıç değeri olarak kullanılmak üzere bir başlangıç değeri
geçirebiliriz. Ardından, çıktı dizisindeki bir sonraki sayıyı üretmek için mevcut durum değiştirilir (bazı matematiksel işlemler uygulanarak)
ve yeni durumdan dizideki bir sonraki sayı oluşturulur.

Bu özel algoritmanın rastgele sayı üreteci olarak çok iyi olmadığını fark ettiğimiz bir durum var (her sonuç çift ve tek arasında sıralanmış gibi
görünüyor -- bu pek rastgele değil!). Ancak çoğu PRNG, LCG16() ile benzer şekilde çalışır -- genellikle daha fazla durum değişkeni ve daha
karmaşık matematiksel işlemler kullanarak daha kaliteli sonuçlar üretirler.

PRNG'i seedleme( tohumlama ) 
----------------------------
Bir PRNG tarafından üretilen "rastgele sayılar" dizisi hiç de rastgele değildir. ArtıBir() fonksiyonumuz gibi, LCG16() fonksiyonu da belirli bir
girişe bağlı olarak belirlenen bir algoritmadır. Bir kere durum başlatıldıktan sonra, LCG16() (ve diğer tüm PRNG'ler) aynı çıkış dizisini
üretecektir. Bir PRNG örneği oluşturulduğunda, PRNG'nin durumunu başlatmak için bir başlangıç değeri (veya bir dizi değer) sağlanabilir.
Bu başlangıç değerine random seed (veya kısaca seed) denir. Bir PRNG bir seed ile başlatıldığında, bu durumda tohumlandığı söylenir.

Kilit nokta *** Bir PRNG'nin üreteceği tüm değerler, tohum değerinden belirlenmiş bir şekilde hesaplanır.

Kaliteli sonuçlar üreten çoğu PRNG, en az 16 baytlık bir durum kullanır, hatta daha fazlasını kullanabilir. Ancak, tohum değerinin boyutu PRNG'nin durumunun boyutundan daha küçük olabilir. Bu durumda, PRNG'nin yetersiz bir şekilde tohumlandığından bahsederiz.

İdeal olarak, durumdaki her bit, eşit boyuttaki bir tohumdan başlatılır ve tohumdaki her bit bir şekilde bağımsız olarak belirlenmiştir. Ancak 
bir PRNG yetersiz bir şekilde tohumlandıysa, durumdaki bazı bitler tohumdaki aynı bitlerden başlatılacaktır. Eğer bir PRNG önemli ölçüde yetersiz
bir şekilde tohumlandırılmışsa (yani tohumun boyutu durumun boyutundan çok daha küçükse), PRNG'nin ürettiği rastgele sonuçların kalitesi
etkilenebilir.

İyi bir PRNG olmak için, PRNG'nin bir dizi özelliği sergilemesi gerekmektedir:
------------------------------------------------------------------------------
PRNG, her sayıyı yaklaşık olarak aynı olasılıkla üretmelidir.
Bu, dağılımın düzenliliği olarak adlandırılır. Eğer bazı sayılar diğerlerinden daha sık üretiliyorsa, PRNG'yi kullanan programın sonucu önyargılı 
olacaktır! Dağılım düzenliliğini kontrol etmek için bir histogram kullanabiliriz. Bir histogram, her sayının kaç kez üretildiğini takip eden bir
grafiktir. Bizim histogramlarımız metin tabanlı olduğu için, bir verilen sayının kaç kez üretildiğini temsil etmek için bir * sembolü 
kullanacağız.

1 ile 6 arasında sayılar üreten bir PRNG düşünelim. Eğer 36 sayı üretiyorsak, dağılım düzenliliğine sahip bir PRNG, şuna benzeyen bir histogram
üretmelidir:

                    1|******
                    2|******
                    3|******
                    4|******
                    5|******
                    6|******

Belirli bir şekilde önyargılı olan bir PRNG, şu şekilde düzensiz bir histogram üretecektir:

                    1|***
                    2|******
                    3|******
                    4|******
                    5|******
                    6|*********

Ya da şu şekilde: 

                    1|****
                    2|********
                    3|******
                    4|********
                    5|******
                    6|****

Burada sonucun önyargılı olmasından kasıt bir tarafa daha fazla yatkın olmasıdır yani mesela olasılık dağılımı gibi düşün 3 grup var diyelim 
örneklemlerin çoğunun 1.grupta olması sonucumuzunda çoğunluk olarak 1.gruba evrilmesine neden olur. 
Veya zar atma durumu olarak düşünecek olursan 1 2 3 4 5 6 eşit olasılıklara sahip olması durumunda sonucunda bu şekilde olması beklenir. 
Fakat 1 değeri ön yargılı ise 1 in daha fazla görülmesi beklenir. 

Diyelim ki bir oyun için rastgele bir öğe üreteci yazmaya çalışıyorsunuz. Bir canavar öldürüldüğünde, kodunuz 1 ile 6 arasında rastgele bir sayı
üretir ve sonuç 6 ise canavar yaygın bir öğe yerine nadir bir öğe bırakır. Bu durumun gerçekleşme olasılığını 1'e 6 olarak beklersiniz. Ancak
altta yatan PRNG düzensiz ise ve beklenenden daha fazla 6 üretiyorsa (yukarıdaki ikinci histogram gibi), oyuncularınız istediğinizden daha fazla
nadir öğe elde edebilir, bu da oyununuzun zorluğunu küçümsemelerine veya oyun içi ekonominizi bozmalarına neden olabilir.

Düzgün sonuçlar üreten PRNG algoritmalarını bulmak zordur.

*** Dizideki bir sonraki sayının nasıl üretildiği tahmin edilemez olmalıdır.

Örneğin, şu PRNG algoritmasını düşünün: `return ++num`. Bu PRNG tamamen düzenli olabilir, ancak aynı zamanda tamamen tahmin edilebilir -- ve
rastgele sayıların bir dizisi olarak pek kullanışlı değildir!

Gözle rastgele görünen sayı dizileri (yukarıdaki LCG16() fonksiyonunun çıktısı gibi) bile motive olan bir kişi tarafından basitçe tahmin 
edilebilir. Yukarıdaki LCG16() fonksiyonu tarafından üretilen birkaç sayıyı inceleyerek, kullanılan sabitlerin (8253729 ve 2396403) hangileri
olduğunu belirlemek mümkündür. Bu bilindiğinde, bu PRNG'den gelecekte üretilecek tüm sayıları hesaplamak basitleşir.

Şimdi, kullanıcıların 100 dolar bahis yapabileceği bir bahis web sitesini çalıştığınızı düşünün. Web siteniz ardından 0 ile 32767 arasında
rastgele bir sayı üretir. Eğer sayı 20000'den büyükse, müşteri kazanır ve siz onlara iki katını ödersiniz. Aksi takdirde kaybederler. Müşteri
sadece zamanın 12767/32767'sinde (yüzde 39) kazanıyorsa, web siteniz çok para kazanmalı, değil mi? Ancak müşterilerin bir sonraki hangi sayıların
üretileceğini belirleyebilmesi durumunda, her zaman (veya genellikle) kazanmak için stratejik bahisler yerleştirebilirler. Tebrikler, şimdi iflas
başvurusu yapma vaktiniz geldi!

* PRNG'nin sayıların iyi bir boyutlu dağılımına sahip olması gerekmektedir.

Bu, PRNG'nin rasgele olarak mümkün olan sonuçlar aralığında sayılar döndürmesi gerektiği anlamına gelir. Örneğin, PRNG düşük sayılar, orta 
sayılar, yüksek sayılar, hatta sayılar ve tek sayılar gibi görünüşte rasgele sayılar üretmelidir.

Tüm düşük sayıları ardından tüm yüksek sayıları döndüren bir PRNG, düzenli ve tahmin edilemez olabilir, ancak özellikle kullanılan rastgele sayı
miktarı az ise önyargılı sonuçlara yol açacaktır.

PRNG'nin her tohum için yüksek bir periyoda sahip olması gerekir
Tüm PRNG'ler periyodiktir, yani üretilen sayı dizisinin belirli bir noktada kendini tekrar etmeye başlayacağı anlamına gelir. PRNG'nin kendini
tekrar etmeye başlamadan önceki dizi uzunluğuna periyot denir.

Örneğin, düşük periyotlu bir PRNG'den üretilen ilk 100 sayı şu şekildedir:

                    112	9	130	97	64	31	152	119	86	53
                    20	141	108	75	42	9	130	97	64	31
                    152	119	86	53	20	141	108	75	42	9
                    130	97	64	31	152	119	86	53	20	141
                    108	75	42	9	130	97	64	31	152	119
                    86	53	20	141	108	75	42	9	130	97
                    64	31	152	119	86	53	20	141	108	75
                    42	9	130	97	64	31	152	119	86	53
                    20	141	108	75	42	9	130	97	64	31
                    152	119	86	53	20	141	108	75	42	9

Dikkatinizi çekecektir ki 9'u 2. sayı olarak, tekrar 16. sayı olarak ve sonrasında her 14 sayıda bir üretmiştir. Bu PRNG, sürekli olarak şu diziyi
üretmeye takılmış durumda: 9-130-97-64-31-152-119-86-53-20-141-108-75-42-(tekrar).

Bu durum, PRNG'lerin belirleyici (deterministik) olmalarından kaynaklanır. Bir PRNG'nin durumu önceki bir durumla aynı olduğunda, PRNG daha önce
ürettiği aynı çıkış dizisini üretmeye başlar ve bir döngü oluşturur.

İyi bir PRNG, tüm tohum numaraları için uzun bir periyoda sahip olmalıdır. Bu özelliği karşılayan bir algoritma tasarlamak son derece zor 
olabilir - birçok PRNG, uzun bir periyoda sadece bazı tohumlar için sahiptir ve diğerleri için değildir. Kullanıcı, kısa bir periyoda sahip bir
duruma yol açan bir tohum seçerse, o zaman PRNG, birçok rastgele sayıya ihtiyaç duyuluyorsa iyi bir iş çıkarmayabilir.

* PRNG'nin verimli olması gerekmektedir

Çoğu PRNG'nin durum boyutu genellikle 4096 byte'tan azdır, bu nedenle genellikle toplam bellek kullanımı endişe kaynağı olmaz. Ancak, iç durum ne
kadar büyükse, PRNG'nin yetersiz bir şekilde tohumlandığı olasılığı o kadar artar ve başlangıç tohumlaması daha yavaş olur (çünkü başlatılacak
daha fazla durum vardır).

İkinci olarak, bir PRNG'nin dizideki bir sonraki sayıyı üretebilmesi için iç durumunu çeşitli matematiksel operasyonlar uygulayarak karıştırması
gerekmektedir. Bu ne kadar zaman alırsa, bu süre PRNG'ye ve mimariye bağlı olarak önemli ölçüde değişebilir (bazı PRNG'ler belirli mimarilerde
diğerlerinden daha iyi performans gösterir). Bu, yalnızca periyodik olarak rastgele sayılar üretiyorsanız önemli değilse de, çok sayıda rastgele
sayıya ihtiyacınız varsa büyük bir etkisi olabilir.

Birçok farklı türde PRNG algoritması bulunmaktadır
--------------------------------------------------

Yıllar içinde birçok farklı türde PRNG algoritması geliştirilmiştir (Wikipedia'da iyi bir liste bulunmaktadır). Her PRNG algoritması, belirli 
uygulamalar için daha uygun veya daha az uygun olabilecek güçlü ve zayıf yönleri içerir, bu nedenle uygulamanız için doğru algoritmayı seçmek
önemlidir.

Birçok PRNG, modern standartlara göre nispeten zayıf olarak kabul edilmektedir ve performansı düşük bir PRNG kullanmanın, performansı yüksek bir 
PRNG kullanmak kadar kolay olmadığı bir durum genellikle söz konusu değildir.

Randomization in C++
--------------------

C++'daki rastgeleleştirme yetenekleri, standart kütüphanenin `<random>` başlık dosyası aracılığıyla erişilebilir. Rastgele kütüphanesinde, 
kullanılabilir durumda olan 6 Pseudo-Random Number Generator (PRNG) ailesi bulunmaktadır (C++20 sürümüne kadar):

| Tür Adı               | Aile                              | Dönem     | Durum Boyutu* | Performans | Kalite  | Kullanmalı mıyım?     |
|-----------------------|------------------------------------|-----------|---------------|-------------|---------|---------------------|
| minstd_rand           | Doğrusal kongrüans üreteci         | 2^31      | 4 bayt        | Kötü        | Kötü    | Hayır               |
| minstd_rand0          | Doğrusal kongrüans üreteci         | 2^31      | 4 bayt        | Kötü        | Kötü    | Hayır               |
| mt19937               | Mersenne twister                   | 2^19937   | 2500 bayt     | Orta        | Orta    | Muhtemelen          |
| mt19937_64            | Mersenne twister                   | 2^19937   | 2500 bayt     | Orta        | Orta    | Muhtemelen          |
| ranlux24              | Çıkart ve taşı                     | 10^171    | 96 bayt       | Kötü        | İyi     | Hayır               |
| ranlux48              | Çıkart ve taşı                     | 10^171    | 96 bayt       | Kötü        | İyi     | Hayır               |
| knuth_b               | Karıştırılmış doğrusal kongrüans üreteci | 2^31   | 1028 bayt     | Kötü     | Kötü    | Hayır               |
| default_random_engine | Yukarıdaki herhangi biri (uygulamaya bağlı) | Değişiklik gösterir | Değişiklik gösterir| ?           | ?    | Hayır               |
| rand()                | Doğrusal kongrüans üreteci         | 2^31      | 4 bayt        | Kötü        | Kötü    | Hayır               |

`knuth_b`, `default_random_engine` ve `rand()` kullanmanın hiçbir mantıklı nedeni yoktur (bu, C ile uyumluluk için sağlanan bir rasgele sayı 
üretecidir). C++20'den itibaren, Mersenne Twister algoritması, hem makul performansa sahip hem de kaliteli olan C++ ile birlikte gelen
tek PRNG'dir.

İleri düzey okuyucular için
---------------------------

PRNG'lerin performansını ve kalitesini değerlendirmek için genellikle PracRand adlı bir test kullanılır (farklı türde önyargılara sahip olup 
olmadıklarını belirlemek için). Ayrıca SmallCrush, Crush veya BigCrush gibi testlere de rastlayabilirsiniz - bunlar aynı amaca hizmet eden 
diğer testlerdir.
https://pracrand.sourceforge.net/

Pracrand'ın çıktısını görmek istiyorsanız, bu https://arvid.io/2018/06/30/on-cxx-random-number-generator-quality/ web sitesinde C++'ın C++20'de 
desteklediği tüm PRNG'lerin çıktısını bulabilirsiniz.

Öyleyse Mersenne Twister kullanmalıyız, değil mi?
-------------------------------------------------

Büyük olasılıkla. Çoğu uygulama için Mersenne Twister, hem performans hem de kalite açısından uygun bir seçenektir.

Ancak, modern PRNG standartlarına göre Mersenne Twister biraz eski sayılabilir. Mersenne Twister'ın en büyük sorunu, 624 üretilen sayı
görüldükten sonra sonuçlarının tahmin edilebilir olmasıdır, bu da onu tahmin edilemezlik gerektiren herhangi bir uygulama için uygun olmaz.

Eğer en yüksek kalitede rastgele sonuçlara (örneğin, istatistiksel bir simülasyon) veya en hızlı sonuçlara veya tahmin edilemezlik önemli 
olan bir uygulama geliştiriyorsanız (örneğin, şifreleme), üçüncü taraf bir kütüphane kullanmanız gerekecektir.

Bu yazının yazıldığı tarih itibariyle popüler seçenekler:

- Kriptografik olmayan PRNG'ler için Xoshiro ailesi ve Wyrand. 
-- https://prng.di.unimi.it/   - https://github.com/wangyi-fudan/wyhash
- Kriptografik (tahmin edilemez) PRNG'ler için Chacha ailesi.
-- https://cr.yp.to/chacha.html

Tamam, şimdi gözleriniz muhtemelen kanıyor, yeterince teori konuştuk. Şimdi gerçekten C++ ile Mersenne Twister kullanarak nasıl rastgele sayı 
üreteceğimizi tartışalım.

8.20 — Mersenne Twister Kullanarak Rastgele Sayı Üretme
-------------------------------------------------------

Önceki derste 8.19 — Rastgele Sayı Üretme Girişi, rastgele sayı üretme kavramını tanıttık ve programlarda rastgeleliği simüle etmek için
genellikle PRNG algoritmalarının nasıl kullanıldığını tartıştık.

Bu derste, programlarınızda nasıl rastgele sayılar üreteceğinizi inceleyeceğiz. C++'da herhangi bir rastgele özelliklere erişmek için standart
kütüphanenin <random> başlığını dahil ederiz.


C++'da Mersenne Twister Kullanarak Rastgele Sayı Üretme

Mersenne Twister PRNG, harika bir isme sahip olmasının yanı sıra, muhtemelen tüm programlama dillerinde en popüler PRNG'dir. Günümüz 
standartlarına göre biraz eski olmasına rağmen genellikle kaliteli sonuçlar üretir ve iyi bir performansa sahiptir. Rastgele kütüphanesi,
iki Mersenne Twister türünü destekler:

* - mt19937, 32 bitlik işaretsiz tam sayılar üreten bir Mersenne Twister'dir.
* - mt19937_64, 64 bitlik işaretsiz tam sayılar üreten bir Mersenne Twister'dir.
Mersenne Twister kullanmak oldukça basittir:
kullanımı :
                        #include <iostream>
                        #include <random> // std::mt19937 için

                        int main()
                        {
                            std::mt19937 mt{}; // 32 bitlik bir Mersenne Twister'ı başlat

                            // Birçok rastgele sayıyı yazdır
                            for (int sayac{ 1 }; sayac <= 40; ++sayac)
                            {
                                std::cout << mt() << '\t'; // rastgele bir sayı üret

                                // 5 sayı yazdıysak, yeni bir satıra geç
                                if (sayac % 5 == 0)
                                    std::cout << '\n';
                            }

                            return 0;
                        }

 Üretilen çıktı:
                        3499211612      581869302       3890346734      3586334585      545404204
                        4161255391      3922919429      949333985       2715962298      1323567403
                        418932835       2350294565      1196140740      809094426       2348838239
                        4264392720      4112460519      4279768804      4144164697      4156218106
                        676943009       3117454609      4168664243      4213834039      4111000746
                        471852626       2084672536      3427838553      3437178460      1275731771
                        609397212       20544909        1811450929      483031418       3933054126
                        2747762695      3402504553      3772830893      4120988587      2163214728

İlk olarak, <random> başlığını ekliyoruz, çünkü rastgele sayı yeteneklerinin tamamı burada bulunuyor. Ardından, std::mt19937 mt ifadesi ile 32
bitlik bir Mersenne Twister motorunu örnekliyoruz. Daha sonra, her seferinde rastgele bir 32 bitlik işaretsiz tamsayı üretmek istediğimizde mt()
çağırıyoruz.

İpucu

mt bir değişken olduğundan mt() ifadesinin ne anlama geldiğini merak ediyor olabilirsiniz.

5.9 dersinde, std::string değişkeni adında length() fonksiyonunu çağırdığımız bir örnek gösterdik, bu, std::string değişkeni adında length()
fonksiyonunu çağırdı.

mt(), bu PRNG türleri için sıradaki rastgele sonucu döndürmek üzere tanımlanmış olan mt.operator() fonksiyonunu çağırmak için özgün bir 
sözdizimidir. operator() yerine adlandırılmış bir fonksiyon kullanmanın avantajı, fonksiyonun adını hatırlamamıza gerek olmaması ve özgün
sözdiziminin daha az yazı içermesidir.

Mersenne Twister kullanarak bir zar atma

32-bit Pseudo-Random Number Generator (PRNG), 0 ile 4,294,967,295 arasında rastgele sayılar üretecek şekilde tasarlanmıştır, ancak her zaman bu
aralıktaki sayıları istemeyebiliriz. Eğer programımız bir masa oyununu veya bir zar oyununu simüle ediyorsa, muhtemelen 6 yüzlü bir zarın
atılmasını simüle etmek için 1 ile 6 arasında rastgele sayılar üretmek isteyeceğizdir. Eğer programımız bir macera oyunuysa ve oyuncunun 
canavarlara 7 ile 11 arasında hasar veren bir kılıcı varsa, o zaman oyuncu bir canavara vurduğunda 7 ile 11 arasında rastgele sayılar üretmek 
isteyeceğiz.

Maalesef PRNG'ler bunu yapamazlar. Sadece tam aralığı kullanan sayıları üretebilirler. İhtiyacımız olan şey, PRNG'den çıkan bir sayıyı 
istediğimiz daha küçük bir aralıktaki bir değere dönüştürmek için bir yol. Kendi başımıza bunu yapmak mümkün olsa da, bunu yaparken tarafsız
sonuçlar üretmek non-trivial (karmaşık) bir görevdir.

Neyse ki, burada random kütüphanesi bize yardımcı olabilir, random sayı dağılımları şeklinde. Bir random sayı dağılımı, bir PRNG değerini girdi 
olarak alan bir olasılık dağılımıdır.

stats uzmanları için: bir random sayı dağılımı, PRNG değerlerini giriş olarak alacak şekilde tasarlanmış bir olasılık dağılımıdır.

Random kütüphanesi birçok random sayı dağılımına sahiptir, çoğunu muhtemelen istatistik analiz yapmıyorsanız asla kullanmayacaksınız.
Ancak oldukça kullanışlı bir random sayı dağılımı var: uniform dağılım, X ile Y arasında (dahil) eşit olasılıkla sayılar üreten bir random
sayı dağılımıdır.

İşte 6 yüzlü bir zarın atılmasını simüle etmek için uniform dağılımı kullanan benzer bir program:

                    #include <iostream>
                    #include <random> // std::mt19937 ve std::uniform_int_distribution için

                    int main()
                    {
                        std::mt19937 mt{}; // Mersenne Twister algoritması kullanarak bir random sayı üreteci oluştur

                        // 1 ile 6 arasında uniform sayılar üreten tekrar kullanılabilir bir random sayı üreteci oluştur
                        std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

                        // Bir dizi rastgele sayıyı ekrana yazdır
                        for (int count{ 1 }; count <= 40; ++count)
                        {
                            std::cout << die6(mt) << '\t'; // burada bir zar atışı yap

                            // Eğer 10 sayı yazdıysak, yeni bir satıra geç
                            if (count % 10 == 0)
                                std::cout << '\n';
                        }

                        return 0;
                    }
Çıktı olarak Bu üretilir:

                    3       1       3       6       5       2       6       6       1       2
                    2       6       1       1       6       1       4       5       2       5
                    6       2       6       2       1       3       5       4       5       6
                    1       4       2       3       1       2       2       6       2       1

Bu örnekle ilgili öncekiyle karşılaştırıldığında sadece iki dikkate değer fark vardır. İlk olarak, 1 ile 6 arasında sayılar üretmek için bir 
uniform dağılım değişkeni oluşturduk (die6 adında). İkinci olarak, 32-bitlik işaretsiz tam sayı rastgele sayılar üretmek için mt() fonksiyonunu
çağırmak yerine şimdi die6(mt) fonksiyonunu çağırıyoruz, böylece 1 ile 6 arasında bir değer üretilmiş oluyor.



Yukarıdaki program göründüğü kadar rastgele değil
-------------------------------------------------

Yukarıdaki zar atma örneğinin sonuçları oldukça rastgele gibi görünse de, programda önemli bir kusur bulunmaktadır. Programı 3 kez çalıştırın
ve bu kusuru anlamaya çalışın. Buyurun, bekliyoruz.

Programı birden fazla kez çalıştırırsanız, her seferinde aynı sayıları yazdığını fark edeceksiniz! Her bir sayı öncekine göre rastgele olabilir,
ancak tüm dizi hiç rastgele değil! Programımızın her çalıştırması tam olarak aynı sonucu üretir.

Haydi, bu nedenin ne olduğuna ve bunu nasıl düzeltebileceğimize daha yakından bakalım.

Önceki dersimizde (8.19 - Rastgele Sayı Üretmeye Giriş) her sayının bir PRNG dizisinde belirli bir şekilde olduğunu ve PRNG'nin durumunun 
başlangıç değerinden başlatıldığını öğrendik. Dolayısıyla, herhangi bir başlangıç ​​tohum numarası verildiğinde, PRNG'ler her zaman o tohumdan
aynı sayı dizisini üretecektir.

Mersenne Twister'ımızı değer olarak başlatıyoruz çünkü, program her çalıştırıldığında aynı tohumla başlatılır. Ve çünkü tohum aynı, üretilen
rastgele sayılar da aynıdır.

Programımızın her çalıştırıldığında tüm diziyi farklı hale getirmek için, sabit bir sayı olmayan bir tohum seçmemiz gerekiyor. Muhtemelen
aklınıza gelen ilk cevap tohumumuzun rastgele bir sayı olması gerektiğidir! Bu iyi bir düşünce, ancak rastgele sayılar üretmek için rastgele
bir sayıya ihtiyacımız varsa, bir çıkmaz durumdayız demektir. Aslında, tohumumuzun gerçekten rastgele bir sayı olmasına gerek yok - sadece
program her çalıştırıldığında değişen bir şey seçmemiz gerekiyor. Sonra PRNG'mizi bu tohumdan benzersiz bir pseudo-rastgele sayı dizisi üretmek
için kullanabiliriz.

Bunu yapmak için genellikle iki yöntem kullanılır:

* - Sistem saatinin kullanımı
* - Sistem'in rastgele cihazının kullanımı

Şimdiz bazılarını öğrenebiliriz: 

1 - Sistem saati ile tohumlama
------------------------------
Sistem saati ile tohumlama

Programınızı her çalıştırdığınızda farklı olan şey nedir? Programınızı tam olarak aynı anda iki kez çalıştırmayı başaramazsanız, cevap genellikle
geçerli zamanın farklı olmasıdır. Bu nedenle, eğer geçerli zamanı tohum değerimiz olarak kullanırsak, programımız her çalıştırıldığında farklı
bir rastgele sayı seti üretecektir. C ve C++, PRNG'lerin genellikle std::time() fonksiyonunu kullanarak geçerli zamanla tohumlanma geçmişine
sahiptir, bu nedenle birçok mevcut kodda bunu görebilirsiniz.

Neyse ki, C++'ta chrono adlı bir kütüphane bulunmaktadır ve bu kütüphanede kullanabileceğimiz çeşitli saatler bulunmaktadır. Program hızlı bir
şekilde ardışık çalıştırıldığında iki zaman değerinin aynı olma olasılığını en aza indirmek istiyoruz. Bunun için saate, ölçebileceği en erken
zamanından bu yana geçen süreyi sormak isteyeceğiz. Bu süre genellikle "ticks" adı verilen çok küçük bir zaman birimidir (genellikle nanosaniye 
olmakla birlikte milisaniye de olabilir).

                    #include <iostream>
                    #include <random> // std::mt19937
                    #include <chrono> // std::chrono

                    int main()
                    {
                        // Mersenne Twister'ı steady_clock kullanarak tohumla
                        std::mt19937 mt{ static_cast<std::mt19937::result_type>(
                            std::chrono::steady_clock::now().time_since_epoch().count()
                            ) };

                        // 1 ile 6 arasında uniform sayılar üreten tekrar kullanılabilir bir random sayı üreteci oluştur
                        std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

                        // Bir dizi rastgele sayıyı ekrana yazdır
                        for (int count{ 1 }; count <= 40; ++count)
                        {
                            std::cout << die6(mt) << '\t'; // burada bir zar atışı yap

                            // Eğer 10 sayı yazdıysak, yeni bir satıra geç
                            if (count % 10 == 0)
                                std::cout << '\n';
                        }

                        return 0;
                    }

Yukarıdaki programda sadece iki değişiklik bulunmaktadır. İlk olarak, <chrono> kütüphanesini dahil ediyoruz, bu da bize saate erişim sağlar. 
İkinci olarak, saatteki geçerli zamanı Mersenne Twister'ımızın tohum değeri olarak kullanıyoruz.

Bu program tarafından üretilen sonuçlar artık her çalıştırıldığında farklı olmalıdır, bunu birkaç kez çalıştırarak deneysel olarak 
doğrulayabilirsiniz.

Bu yaklaşımın dezavantajı, programın hızlı bir şekilde ardışık olarak birkaç kez çalıştırılması durumunda, her çalıştırma için üretilen
tohumların çok farklı olmamasıdır, bu da istatistiksel olarak rastgele sonuçlar kalitesini etkileyebilir. Normal programlar için bu önemli değil,
ancak yüksek kaliteli, bağımsız sonuçlar gerektiren programlar için bu tohumlama yöntemi yetersiz olabilir.

Not:
std::chrono::high_resolution_clock, std::chrono::steady_clock yerine popüler bir tercihtir. std::chrono::high_resolution_clock, en ince zaman
birimini kullanan saat türüdür, ancak mevcut zaman için sistem saatinin kullanılabilir, bu da kullanıcılar tarafından değiştirilebilecek veya 
geri alınabilecek anlamına gelebilir. std::chrono::steady_clock daha az ince bir tik süresine sahip olabilir, ancak kullanıcıların bunu 
ayarlayamayacağı bir güvenceye sahip tek saat türüdür.
Yani, std::chrono::high_resolution_clock, en ince zaman birimini kullanan bir saat türüdür. Yani, zamanı çok hassas bir şekilde ölçer. Ancak, 
bu saat türü, mevcut zamanı belirlemede sistem saatinin kullanılabileceği bir özelliğe sahiptir. Kullanıcılar bu sistem saatini değiştirebilecek
veya geri alabileceği için, zamanın hassasiyeti sağlanmış olsa bile bu saatin güvenilirliği sınırlı olabilir.

Öte yandan, std::chrono::steady_clock daha az hassas bir tik süresine sahip olabilir, ancak bu saat türü kullanıcılar tarafından ayarlanamaz. 
Bu, zamanın daha güvenilir bir şekilde ölçülmesini sağlar, çünkü kullanıcılar tarafından saat ayarlanamaz ve bu nedenle sistemdeki 
değişikliklerden etkilenmez.

Bu nedenle, hassasiyet önemliyse ve sistem saatini kullanmaktan endişe edilmiyorsa, std::chrono::high_resolution_clock tercih edilebilir. 
Ancak zamanın güvenilirliği daha önemliyse ve kullanıcı müdahalesinden etkilenmemesi gerekiyorsa, std::chrono::steady_clock kullanılabilir.

2 - Sistem'in rastgele cihazının kullanımı
------------------------------------------

Rastgele cihaz kullanarak tohumlama

random kütüphanesi, std::random_device adında, uygulama tarafından tanımlanan bir PRNG tipini içerir. Genellikle uygulama tarafından tanımlanan
yeteneklerden kaçınırız çünkü kalite veya taşınabilirlik konusunda herhangi bir güvence sağlamazlar, ancak bu istisna durumlardan biridir. 
Tipik olarak std::random_device, işletim sisteminden bir rastgele sayı isteyecektir (bunu nasıl yaptığı işletim sistemine bağlıdır).

                    #include <iostream>
                    #include <random> // std::mt19937 ve std::random_device için

                    int main()
                    {
                        std::mt19937 mt{ std::random_device{}() };

                        // 1 ile 6 arasında uniform sayılar üreten tekrar kullanılabilir bir random sayı üreteci oluştur
                        std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

                        // Bir dizi rastgele sayıyı ekrana yazdır
                        for (int count{ 1 }; count <= 40; ++count)
                        {
                            std::cout << die6(mt) << '\t'; // burada bir zar atışı yap

                            // Eğer 10 sayı yazdıysak, yeni bir satıra geç
                            if (count % 10 == 0)
                                std::cout << '\n';
                        }

                        return 0;
                    }


Yukarıdaki programda, Mersenne Twister'ımızı std::random_device'ın geçici bir örneğinden üretilen bir rastgele sayı ile tohumluyoruz. Bu programı
birden çok kez çalıştırırsanız, her seferinde farklı sonuçlar üretmesi gerekmelidir.

std::random_device ile potansiyel bir sorun şudur: belirli olmaması gerekir, yani, bazı sistemlerde program her çalıştırıldığında aynı diziyi 
üretebilir, bu da tam olarak kaçınmaya çalıştığımız durumdur. MinGW'de (GCC 9.2 ile düzeltilmiş) böyle bir durumu tetikleyen bir hata vardı,
bu da std::random_device'ı işe yaramaz hale getiriyordu. https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85494

Ancak, en popüler derleyicilerin (GCC/MinGW, Clang, Visual Studio) en son sürümleri, std::random_device'ın uygun uygulamalarını destekler.

*** BEST -> PRNG'lerinizi tohumlamak için std::random_device kullanın (ancak hedef derleyici/mimari için düzgün bir şekilde uygulanmamışsa).
(ancak hedef derleyici/mimari için düzgün bir şekilde uygulanmamışsa) -> KASIT -> Bazı durumlarda, özellikle farklı derleyiciler ve sistemler 
arasında, std::random_device'ın sağladığı rastgele sayıların beklenen düzeyde olmaması veya belirli durumlarda aynı diziyi üretmesi gibi 
sorunlar ortaya çıkabilir. Bu durumda, std::random_device kullanmak yerine farklı bir yöntem düşünülmelidir.

Soru: std::random_device{}() ın anlamı nedir ?
----------------------------------------------

std::random_device{}() ifadesi, std::random_device türünde bir değeri değerlemeyle başlatılmış geçici bir nesne oluşturur. Ardından ()
operatörünü bu geçici nesne üzerinde çağırır, bu da rastgele bir değeri döndürür (ki bu değeri Mersenne Twister'ımızı başlatmak için kullanırız).
Bu, aşağıdaki fonksiyonu çağırmakla eşdeğerdir ve daha alışık olduğunuz bir sözdizimi kullanır:

                    unsigned int getRandomDeviceValue()
                    {
                       std::random_device rd{}; // değerleme ile başlatılmış bir std::random_device nesnesi oluştur
                       return rd(); // operator()'ın sonucunu çağırana geri dön
                    }
std::random_device{}() kullanmak, adlandırılmış bir işlev veya değişken oluşturmadan aynı sonucu elde etmemize olanak tanır, bu nedenle çok
daha özlüdür.

Eğer std::random_device kendi başına rastgele ise, neden onu Mersenne Twister yerine kullanmıyoruz?
---------------------------------------------------------------------------------------------------

Çünkü std::random_device uygulama tanımlıdır, bu nedenle onun hakkında pek çok şeyi varsayamayız. Bu, erişiminin maliyetli olabileceği veya daha
fazla rastgele sayı beklenirken programımızın duraklamasına neden olabileceği anlamına gelir. Ayrıca, bu sayılardan çeken havuz hızla tükenmiş
olabilir, bu da aynı yöntemi kullanarak rastgele sayılar isteyen diğer uygulamalar için rastgele sonuçları etkiler. Bu nedenle,
std::random_device'ın daha çok başka PRNG'leri tohumlamak için kullanılması, kendi başına bir PRNG olarak kullanılmasından daha iyidir.

Bir PRNG'yi sadece bir kez tohumla (seed)
-----------------------------------------

Birçok PRNG, ilk tohumlamadan sonra tekrar tohumlanabilir. Bu, temelde rastgele sayı üretecinin durumunu yeniden başlatarak yeni bir tohum
durumundan başlayarak sonuçlar üretmesine neden olur. Ancak genellikle belirli bir neden olmadıkça tekrar tohumlama yapılmamalıdır, çünkü bu,
sonuçların daha az rastgele veya hiç rastgele olmasına yol açabilir.

*** BEST -> Belirli bir yarı-rastgele sayı üreteciyi sadece bir kez tohumla ve tekrar tohumlama işlemi yapma.

İşte yeni programcıların yaptığı yaygın hataya bir örnek:

                    #include <iostream>
                    #include <random>

                    int getCard()
                    {
                        std::mt19937 mt{ std::random_device{}() }; // bu her fonksiyon çağrıldığında oluşturulur ve tohumlanır
                        std::uniform_int_distribution card{ 1, 52 };
                        return card(mt);
                    }

                    int main()
                    {
                        std::cout << getCard() << '\n';

                        return 0;
                    }

getCard() fonksiyonunda, her çağrıldığında rastgele sayı üreteci oluşturuluyor ve tohumlanıyor. Bu en iyi ihtimalle verimsiz bir durumdur ve
muhtemelen düşük kaliteli rastgele sonuçlara neden olacaktır.

Mersenne Twister ve düşük tohumlama sorunları
---------------------------------------------

Bir Mersenne Twister'ın iç durumu 624 bayt büyüklüğündedir. Yukarıdaki örneklerde, saat veya std::random_device'tan tohumlandığımızda,
tohumumuz yalnızca tek bir 32-bit tamsayıdır. Bu, esasen 4 bayt değeri olan bir nesneyi 624 bayt olarak başlatmamız anlamına gelir, ki bu 
Mersenne Twister PRNG'yi önemli ölçüde düşük bir şekilde tohumlamaktır. random kütüphanesi, geriye kalan 620 bayiti "rastgele" veri ile doldurmak
için elinden gelenin en iyisini yapar... ama sihir yapamaz. Düşük tohumlanmış bir PRNG, en yüksek kalitede sonuçlara ihtiyaç duyan uygulamalar
için optimize edilmemiş sonuçlar üretebilir. Örneğin, std::mt19937'yi yalnızca tek bir 32-bit değeri ile tohumlamak, asla ilk çıktı olarak sayı
42 üretmeyecektir.

Peki bunu nasıl düzeltebiliriz? C++20'den itibaren, bunun kolay bir yolu yok. Ancak bazı önerilerimiz var.

İlk olarak, std::seed_seq ("tohum dizisi" anlamına gelir) hakkında konuşalım. Daha önceki derslerde, tohum verilerimizin ideal olarak PRNG'nin
durumu kadar çok bit olmasını istediğimizi söyledik, aksi takdirde PRNG düşük bir şekilde tohumlanacaktır. Ancak birçok durumda (özellikle 
PRNG'nin büyük bir durumu olduğunda), bu kadar çok bit rastgele tohum verisine sahip olmayabiliriz.

std::seed_seq, bu konuda yardımcı olmak için tasarlanmış bir türdür. Ne kadar rastgele değer geçirirsek, o kadar fazla önyargısız tohum değeri
oluşturacaktır. Bu nedenle std::random_device'dan alınan tek bir 32-bit tamsayı ile std::seed_seq'yi başlatır ve ardından bir Mersenne Twister'ı
std::seed_seq nesnesiyle başlatırsak, std::seed_seq 620 bayt ek tohum verisi oluşturacaktır. Sonuçlar inanılmaz yüksek kalitede olmasa da, hiç
yoktan iyidir.

Şimdi fikirlere geçelim.

İlk olarak, std::seed_seq'e daha fazla rastgele veri verirsek, o kadar iyi olur. Bu nedenle en kolay fikir, std::seed_seq'e daha fazla veri 
sağlamak için basitçe std::random_device kullanmaktır. Eğer std::seed_seq'i std::random_device'tan 8 sayı ile başlatırsak, std::seed_seq 
tarafından üretilen geriye kalan sayılar o kadar daha iyi olmalıdır:

                        #include <iostream>
                        #include <random>

                        int main()
                        {
                            std::random_device rd{};
                            std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // std::random_device'tan 8 adet rastgele 
                                                                                                // tamsayı alarak tohumumuzu oluştur
                            std::mt19937 mt{ ss }; // Mersenne Twister'ımızı std::seed_seq ile başlat

                            // 1 ile 6 arasında uniform sayılar üreten tekrar kullanılabilir bir rastgele sayı üreteci oluştur
                            std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

                            // Birçok rastgele sayıyı yazdır
                            for (int count{ 1 }; count <= 40; ++count)
                            {
                                std::cout << die6(mt) << '\t'; // burada bir zar atışı üret

                                // Eğer 10 sayı yazdıysak, yeni bir satıra geç
                                if (count % 10 == 0)
                                    std::cout << '\n';
                            }

                            return 0;
                        }

Bu oldukça açıktır, bu nedenle bunu en azından yapmamak için pek bir neden yoktur.

Soru: -> Neden std::random_device'den std::seed_seq'e 156 tam sayı (624 bayt) vermiyorsunuz?

Evet, yapabilirsiniz! Ancak bu işlem yavaş olabilir ve std::random_device'ın kullandığı rastgele sayı havuzunu tükenme riski taşır.

İkinci olarak, std::seed_seq'a başka "rastgele" girdileri kullanabilirsiniz. Zaten size saatten bir değer almayı nasıl yapacağınızı gösterdik,
bu yüzden bunu kolayca ekleyebilirsiniz. Bazı durumlarda kullanılan diğer şeyler arasında mevcut iş parçacığı kimliği, belirli fonksiyonların
adresi, kullanıcının kimliği, işlem kimliği vb. bulunmaktadır. Bunları yapmak, bu makalenin kapsamının ötesindedir, ancak bu makale, bu bağlamda
bazı bilgiler ve bunu uygulayan randutils.hpp adlı bir bağlantı içerir.

Alternatif bir yol, daha küçük bir duruma sahip farklı bir PRNG kullanmaktır. Birçok iyi PRNG, 64 veya 128 bit durum kullanır, bu da kolayca 8
std::random_device çağrısı ile doldurulmuş bir std::seed_seq ile başlatılabilir.


Bir Pseudo-Random Number Generator (PRNG), düşük kaliteli bir tohum aldığında (veya düşük tohumlama durumunda), PRNG'nin ilk sonuçları yüksek
kalitede olmayabilir. Bu nedenle, bazı PRNG'lerin "ısıtılması" yani "warming up" işleminden faydalanılır. Bu, PRNG tarafından üretilen ilk N
sonucun atılması anlamına gelir. Bu, PRNG'nin iç durumunu karıştırarak, sonraki sonuçların daha yüksek kalitede olması beklenir. Genellikle
birkaç yüz ila birkaç bin başlangıç sonucu atılır. PRNG'nin periyodu ne kadar uzunsa, o kadar çok başlangıç sonucu atılmalıdır.

Bir ayrıntı olarak...

Visual Studio'nun rand() fonksiyonunun uygulamasında (hala var mı yoksa bilinmiyor mu?) ilk üretilen sonucun yeterince rastgele olmadığı bir hata
bulunuyordu. Bu nedenle, rand() kullanan eski programlarda bu sorunu önlemek için tek bir sonucun atıldığını görebilirsiniz.

std::mt19937 tarafından kullanılan seed_seq başlatma işlemi bir "ısıtma" gerçekleştirir, bu nedenle std::mt19937 nesnelerini açıkça ısıtmamıza 
gerek yoktur.

Çoklu Fonksiyon veya Dosya Üzerinde Rastgele Sayılar (Random.h)
---------------------------------------------------------------

Eğer bir rastgele sayı üreteciyi birden çok fonksiyon veya dosyada kullanmak istiyorsak ne olur? Bunun bir yolu, PRNG'mizi main() fonksiyonumuzda
oluşturmak (ve tohumlamak) ve sonra ihtiyaç duyduğumuz her yere onu iletmektir. Ancak bu, yalnızca ara sıra kullanabileceğimiz ve farklı yerlerde
kullanabileceğimiz bir şey için çok fazla iletim demektir. Bu, böyle bir nesneyi etrafa iletmek için kodumuza çok fazla karma ekleyebilir.

Rastgele Sayılar Çeşitli Fonksiyonlarda veya Dosyalarda (Random.h)

Eğer bir rastgele sayı üreteciyi birden çok fonksiyon veya dosyada kullanmak istiyorsak ne olur? Bir yol, PRNG'mizi main() fonksiyonumuzda
oluşturmak (ve tohumlamak) ve sonra ihtiyaç duyduğumuz her yere onu iletmektir. Ancak bu, yalnızca ara sıra kullanabileceğimiz ve farklı
yerlerde kullanabileceğimiz bir şey için çok fazla iletim demektir. Bu, böyle bir nesneyi etrafa iletmek için kodumuza çok fazla karma ekleyebilir.

Alternatif olarak, ihtiyaç duyan her fonksiyonda (sadece bir kez tohumlanacağı için static olarak) bir static yerel std::mt19937 değişkeni
oluşturabilirsiniz. Ancak her bir fonksiyonun kendi yerel Random sayı üreteci tanımlamasını ve tohumlamasını yapması gerekir, bu da her
Random sayı üreteci için düşük çağrı hacmi, daha düşük kalitede sonuçlara yol açabilir.

Gerçekten istediğimiz şey, her yerden erişebileceğimiz ve paylaşabileceğimiz tek bir PRNG nesnesidir, tüm fonksiyonlarımız ve dosyalarımız 
boyunca. Burada en iyi seçenek, küresel bir rastgele sayı üreteci nesnesi oluşturmaktır (bir namespace içinde!). Hafızada sabit olmayan global
değişkenlerden kaçınmanızı söylemiştik, ancak bu bir istisnadır.

İşte, herhangi bir kod dosyasına #include edebileceğiniz basit, yalnızca başlık dosyası içeren bir çözüm: (Random.h)

                        #ifndef RANDOM_MT_H
                        #define RANDOM_MT_H

                        #include <chrono>
                        #include <random>

                        // Bu başlık dosyası yalnızca bildirimleri içerir ve çoklu dosya kullanımına uygun hale getirilmiştir.
                        // Inline anahtar kelimesi, ODR (One Definition Rule) ihlallerini önlemek için kullanılmıştır.

                        namespace Random
                        {
                            // Kendini başlatan bir Mersenne Twister üreten bir fonksiyon.
                            // Not: std::seed_seq'nin değerini döndürmek istiyoruz, ancak std::seed kopyalanamaz,
                            // bu nedenle değer olarak döndürülemez. Bunun yerine, std::mt19937 oluşturacak, seed edecek
                            // ve ardından std::mt19937'yi (kopyalanabilir) döndüreceğiz.
                            inline std::mt19937 generate()
                            {
                                std::random_device rd{};

                                // Saat ve std::random_device'tan alınan 7 rastgele sayı ile seed_seq oluşturun.
                                std::seed_seq ss{
                                    static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
                                        rd(), rd(), rd(), rd(), rd(), rd(), rd() };

                                return std::mt19937{ ss };
                            }

                            // Global std::mt19937 nesnemiz burada tanımlanır.
                            // Inline anahtar kelimesi, programımızın tamamı için yalnızca bir global örneğe sahip olduğumuz anlamına gelir.
                            inline std::mt19937 mt{ generate() }; // başlatılmış bir std::mt19937 üretir ve global nesneye kopyalar

                            // [min, max] aralığında rastgele bir tamsayı üreten fonksiyon.
                            inline int get(int min, int max)
                            {
                                return std::uniform_int_distribution{min, max}(mt);
                            }

                            // Aşağıdaki fonksiyon şablonları, min ve/veya max türü int olmadığında rastgele sayılar üretmek için kullanılabilir.
                            // https://www.learncpp.com/cpp-tutorial/function-template-instantiation/ adresinden daha fazla bilgi alabilirsiniz.
                            // Eğer anlamıyorsanız, bunları göz ardı edebilirsiniz.

                            // [min, max] aralığında bir rastgele değer üreten fonksiyon şablonu.
                            // * min ve max aynı türdedir
                            // * Döndürülen değer min ve max ile aynı türdedir
                            // * Desteklenen türler:
                            // *    short, int, long, long long
                            // *    unsigned short, unsigned int, unsigned long, veya unsigned long long
                            // Örnek kullanım: Random::get(1L, 6L);             // long türünde değer döndürür
                            // Örnek kullanım: Random::get(1u, 6u);             // unsigned int türünde değer döndürür
                            template <typename T>
                            T get(T min, T max)
                            {
                                return std::uniform_int_distribution<T>{min, max}(mt);
                            }

                            // [min, max] aralığında bir rastgele değer üreten fonksiyon şablonu.
                            // * min ve max farklı türlerde olabilir
                            // * Dönüş türünü şablon türü argümanı olarak açıkça belirtmek zorundasınız
                            // * min ve max dönüş türüne dönüştürülecektir
                            // Örnek kullanım: Random::get<std::size_t>(0, 6);  // std::size_t tür

İşte bu başlık dosyasını nasıl kullanabileceğinizi gösteren örnek bir program:

main.cpp: 

                        #include "Random.h" // Random::mt, Random::get() ve Random::generate()'i tanımlar
                        #include <iostream>

                        int main()
                        {
                            // Random::get() kullanarak rastgele sayılar üretebiliriz

                            std::cout << Random::get(1, 6) << '\n';   // 1 ile 6 arasında bir int döndürür
                            std::cout << Random::get(1u, 6u) << '\n'; // 1 ile 6 arasında bir unsigned int döndürür

                            // Aşağıdaki örnek bir şablon türü argümanı kullanır
                            // Ayrıntılar için: https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
                            std::cout << Random::get<std::size_t>(1, 6u) << '\n'; // 1 ile 6 arasında bir std::size_t döndürür

                            // Eğer kendi dağılımımız varsa Random::mt'yi doğrudan kullanabiliriz

                            // 1 ile 6 arasında uniform sayılar üreten yeniden kullanılabilir bir rastgele sayı üreteci oluştur
                            std::uniform_int_distribution die6{ 1, 6 }; // C++14 için std::uniform_int_distribution<> die6{ 1, 6 };

                            // Birçok rastgele sayıyı yazdır
                            for (int count{ 1 }; count <= 10; ++count)
                            {
                                // Random::mt'yi doğrudan erişebiliriz
                                std::cout << die6(Random::mt) << '\t'; // zar atışını burada üret
                            }

                            std::cout << '\n';

                            return 0;
                        }

Normalde bir başlık dosyasında değişkenler ve fonksiyonlar tanımlamak, o başlık dosyasının birden fazla kaynak dosyasına dahil edilmesi durumunda
bir tanımlama kuralı ihlali (ODR) oluşturabilir. Ancak, mt değişkenimizi ve destekleyici fonksiyonlarımızı inline olarak tanımladık, bu da bize 
bu tanımlamaların hepsinin aynı olduğu sürece ODR'yi ihlal etmeden birden çok tanımlamaya sahip olma imkanı tanır. Bu tanımlamaların hepsinin
aynı olduğunu, bunları manuel olarak yazmak veya kopyala/yapıştır yapmak yerine bir başlık dosyasından #include ettiğimizden emin olarak 
sağlayabiliriz. İnline fonksiyonlar ve değişkenler, genellikle bu tür başlık-tabanlı işlevselliği mümkün kılmak amacıyla dile eklenmiştir.

Üstesinden gelmemiz gereken diğer zorluk, global Random::mt nesnemizi nasıl başlatacağımızdır. Bu nesnenin kendi kendini başlatan olmasını
istiyoruz, böylece doğru şekilde çalışabilmesi için açıkça bir başlatma işlevini çağırmamıza gerek kalmaz. Başlatıcımız bir ifade olmalıdır.
Ancak std::mt19937'yi başlatmak için birkaç yardımcı nesneye (std::random_device ve std::seed_seq) ihtiyacımız var, bu nesneler ifadeler olarak 
tanımlanmalıdır. İşte burada bir yardımcı fonksiyon işe yarar. Bir fonksiyon çağrısı bir ifade olduğundan, bir fonksiyonun return değerini bir 
başlatıcı olarak kullanabiliriz. Ve fonksiyonun kendisi içinde ihtiyacımız olan herhangi bir kombinasyona sahip ifadeleri kullanabiliriz. Bu 
nedenle, generate() fonksiyonumuz, sistem saati ve std::random_device kullanılarak tamamen başlatılmış bir std::mt19937 nesnesi oluşturur ve 
döndürür, bu nesneyi global Random::mt nesnemizin başlatıcısı olarak kullanırız.

Bir kez "Random.h" dahil edildikten sonra, şu iki şekilde kullanabiliriz:

1 - Random::get() fonksiyonunu çağırarak iki değer arasında (dahil) rastgele bir sayı üretebiliriz.
2 - Random::mt üzerinden std::mt19937 nesnesine doğrudan erişebilir ve istediğimiz herhangi bir işlemi yapabiliriz.

Random sayılar kullanırken Debug yapma 
--------------------------------------

Rastgele sayıları kullanan programları hata ayıklamak zor olabilir çünkü program, her çalıştırıldığında farklı davranışlar sergileyebilir.
Bazı durumlarda çalışabilirken, bazı durumlarda çalışmayabilir. Hata ayıklama yaparken, programınızın her seferinde aynı (yanlış) şekilde 
çalıştığından emin olmak faydalıdır. Bu şekilde, hatanın nerede olduğunu izole etmek için programı gerektiği kadar çok kez çalıştırabilirsiniz.

Bu nedenle, hata ayıklarken, PRNG'nizi belirli bir değerle (örneğin 5) başlatmak, hatalı davranışın ortaya çıkmasına neden olacak ve bu sayede
programınızın her seferinde aynı sonuçları üretmesini sağlayacaktır. Bu da hata ayıklamayı kolaylaştırır. Hata bulduktan sonra normal başlatma 
yönteminizi kullanarak tekrar rastgele sonuçlar üretmeye başlayabilirsiniz.

Sık sorulan sorular:
-> Rastgele sayı üreteci aynı rastgele sayı dizisini üretiyor.

Eğer rastgele sayı üreteciniz her program çalıştırıldığında aynı rastgele sayı dizisini üretiyorsa, muhtemelen onu doğru bir şekilde 
başlatmadınız (veya hiç başlatmadınız). Programın her çalıştırıldığında değişen bir değerle başlattığınızdan emin olun.

-> Rastgele sayı üreteci sürekli aynı sayıyı üretiyor.

Eğer rastgele sayı üreteciniz her seferinde aynı sayıyı üretiyorsa, muhtemelen her rastgele sayı üretmeden önce rastgele sayı üreticisini tekrar 
başlatıyorsunuz ya da her rastgele sayı için yeni bir üreteç oluşturuyorsunuz demektir.
*/

/*
Bölüm incelemesi
----------------
CPU'nun bir programda yürüttüğü belirli bir ifade dizisine programın yürütme yolu ( execution path ) denir. Doğrusal bir program çalıştırıldığında
her zaman aynı yolu izler.

Kontrol akışı ifadeleri (ayrıca Akış kontrol ifadeleri olarak da adlandırılır), programcının yürütme yolunu değiştirmesine izin verir. Bir 
kontrol akışı ifadesi, programın normal sıra dışı bir talimat dizisini çalıştırmaya başlamasına neden olduğunda, bu bir dal olarak adlandırılır.
Aynı zamanda buna branch denir. 

Bir koşullu ifade, ilişkilendirilmiş bazı ifadelerin yürütülüp yürütülmeyeceğini belirleyen bir ifadedir.

If ifadeleri, bir koşulun doğru olup olmadığına bağlı olarak ilişkilendirilmiş bir ifadeyi çalıştırmamıza olanak tanır. Else ifadeleri,
ilişkilendirilmiş koşul yanlışsa çalıştırılır. Birden fazla if ve else ifadesini birleştirebilirsiniz.

Dangling else, bir else ifadesinin hangi if ifadesine bağlı olduğu belirsiz olduğunda ortaya çıkar. Dangling else ifadeleri, aynı bloktaki son
eşleşmemiş if ifadesi ile eşleştirilir. Bu nedenle, if ifadesinin gövdesinin bir blok içine yerleştirildiğinden emin olarak, danging else 
ifadelerini trivial bir şekilde önleyebiliriz.

Null ifadesi ( null statement ) dediğimiz şey aslında bir ifadedir ve sadece bir noktalı virgül içerir. Hiçbir şey yapmaz ve dil, bir ifadenin 
var olmasını isterken programcının bu ifadenin herhangi bir şey yapmasını istememesi durumunda kullanılır.

Switch ifadeleri, bir dizi eşleşen öğe arasında seçim yapmak için daha temiz ve daha hızlı bir yöntem sağlar. Switch ifadeleri sadece integral
tiplerle çalışır. Case etiketleri, değerleri belirtmek için kullanılır ve değerlendirilen koşulların eşleşmesi için kullanılır. Eşleşen bir case
etiketi bulunamazsa, bir default etiketinin altındaki ifadeler yürütülür.

Bir etiketin altındaki bir ifadenin altındaki ifadelerin ardından bir sonraki etiketin altındaki ifadelere geçiş yaptığında, buna fallthrough
denir. Fallthrough'u önlemek için bir break ifadesi (veya return ifadesi) kullanılabilir. [[fallthrough]] özniteliği, kasıtlı fallthrough'u 
belgelemek için kullanılabilir.

Goto ifadeleri programın kod içinde başka bir yere, ya ileriye ya da geriye atlamasına olanak tanır. Genellikle kaçınılması gereken bir yapıdır,
çünkü programın yürütme yolunu spagetti kodu andıran bir yapı oluşturabilir. Spagetti kod, bir programın yürütme yolunun spagetti tabağını andıran
bir karmaşıklığa sahip olduğu durumu ifade eder.

While döngüleri, belirli bir koşul doğru olduğu sürece programın döngü içinde kalmasına izin verir. Koşul, döngü çalışmadan önce değerlendirilir.

Sonsuz döngü, her zaman doğru olan bir koşula sahip döngüdür. Bu döngüler, başka bir kontrol akış ifadesi kullanılmadığı sürece sürekli olarak 
dönecektir.

Döngü değişkeni (aynı zamanda sayaç olarak da adlandırılır), bir döngünün kaç kez çalıştığını saymak için kullanılan bir tamsayı değişkenidir. 
Her döngü çalıştırılması bir iterasyon olarak adlandırılır.

Do while döngüleri, while döngülerine benzerdir, ancak koşul döngü çalıştıktan sonra değerlendirilir, öncesinde değil.

For döngüleri en çok kullanılan döngülerdir ve belirli bir sayıda kez döngü yapmanız gerektiğinde idealdir. Off-by-one hatası, döngünün bir kez 
fazla veya bir kez az döngü yapması durumunda ortaya çıkar.

Break ifadeleri, switch, while, do while veya for döngüsünden çıkmamıza izin verir (ayrıca henüz ele almadığımız range-based for döngüleri de 
dahil). Continue ifadeleri, hemen bir sonraki döngü iterasyonuna geçmemize izin verir.

Halt ifadeleri, programımızı sonlandırmamıza izin verir. Normal sonlandırma, programın beklenen bir şekilde çıkmasını (ve durum kodunun başarılı 
olup olmadığını belirtecek) ifade eder. std::exit() main'in sonunda otomatik olarak çağrılır veya programı sonlandırmak için açıkça çağrılabilir.
Temizlik yapar ancak yerel değişkenleri temizlemez veya çağrı yığını (call stack) sarmaz.

Anormal sonlandırma, programın beklenmeyen bir hatayla karşılaşması ve kapatılması durumunda ortaya çıkar. std::abort, anormal sonlandırma için
çağrılabilir.

Kapsam sızması, bir projenin yeteneklerinin projenin veya proje aşamasının başlangıcında öngörülenin ötesine geçtiği durumu ifade eder.

Yazılım doğrulama, yazılımın tüm durumlarda beklenildiği gibi çalışıp çalışmadığını test etme sürecidir. Bir birim testi, belirli bir davranışın
beklenildiği gibi gerçekleşip gerçekleşmediğini kontrol etmek üzere tasarlanmış bir testtir (genellikle bir fonksiyon veya çağrıdır). Birim test
çerçeveleri, birim testlerinizi düzenlemenize yardımcı olabilir. Entegrasyon testi, birimleri bir araya getirip düzgün çalışıp çalışmadığını
kontrol eder.

Kod kapsamı, test sırasında yürütülen kaynak kodunun ne kadarının kapsandığına referans verir. İfade kapsamı, bir programdaki ifadelerin test
rutinleri tarafından ne kadarının gerçekleştirildiğini ifade eder. Şube kapsamı, test rutinleri tarafından gerçekleştirilen şubelerin yüzdesini 
ifade eder. Döngü kapsamı (aynı zamanda 0, 1, 2 testi olarak adlandırılır), bir döngüye sahipseniz, bu döngünün 0 kez, 1 kez ve 2 kez iterken 
düzgün çalıştığından emin olmanızı ifade eder.

Mutlu yol, hata olmadan gerçekleşen yürütme yoludur. Üzgün yol, bir hata veya başarısızlık durumu meydana geldiğinde ortaya çıkar.
Kurtarılamaz bir hata (aynı zamanda fatal hata olarak da adlandırılır), programın devam edemeyecek kadar ciddi bir hatadır. Hata durumlarıyla 
iyi başa çıkan bir program, sağlamdır.

Arabellek ( buffer ), veriyi bir yerden başka bir yere taşınırken geçici olarak depolamak için ayrılmış bellek parçasıdır.

Kullanıcının girişinin programın beklediği formata uygun olup olmadığını kontrol etme sürecine giriş doğrulama ( input validation ) denir.

std::cerr, hata mesajları için kullanılan bir çıkış akışıdır (std::cout gibi).

Bir öncel koşul ( precondition ), belirli bir kod segmentinin yürütülmeden önce her zaman doğru olması gereken bir koşuldur. 
Bir değişmez ( invarient ), bir bileşen çalışırken her zaman doğru olması gereken bir koşuldur. Bir son koşul ( postcondition ), belirli bir 
kodun yürütülmesinden sonra her zaman doğru olması gereken bir koşuldur.

Bir iddia ( assertion ), programda bir hata olmadıkça doğru olan bir ifadedir. C++, çalışma zamanı iddiaları genellikle assert önişlemci makrosu 
kullanılarak uygulanır. İddialar genellikle hata ayıklama kodunda devre dışı bırakılır. Bir static_assert, derleme zamanında değerlendirilen bir
iddiadır.

İddialar, mantıksal olarak imkansız durumları belgelemek için kullanılmalıdır. Hata işleme ise, mümkün olan durumlarla başa çıkmak için
kullanılmalıdır.

Bir algoritma, belirli bir problemi çözmek veya bazı yararlı sonuçlar üretmek için takip edilebilecek sonlu bir talimat dizisidir. Bir algoritma,
çağrılar arasında bazı bilgileri koruyorsa, durumlu ( stateful )olarak kabul edilir. Tersine, durumsuz ( stateless ) bir algoritma hiçbir bilgi 
saklamaz (ve çağrıldığında çalışması için tüm bilgileri sağlamalıdır). Algoritmalerle ilgili olarak, durum terimi, durumsuz değişkenlerde bulunan
mevcut değerlere atıfta bulunur.

Bir algoritma, bir giriş için (başlangıç için sağlanan değer) belirli ( deterministic ) bir çıkış dizisini her zaman üretiyorsa,
bu algoritma belirlenmiş olarak kabul edilir.

Pseudo-rastgele sayı üreteci (PRNG), özellikleri rastgele sayı dizisini taklit eden bir algoritmadır. Bir PRNG örneklenmişse, bir başlangıç 
değeri (veya değer seti) olan bir rastgele tohum (veya kısaca tohum ) sağlanabilir ve PRNG'nin durumunu başlatmak için kullanılabilir.
Bir PRNG bir tohumla başlatıldığında, ona tohumlandı denir. Tohum değerinin boyutu, PRNG'nin durumu boyutundan daha küçük olabilir.
Bu durumda, PRNG'nin eksik tohumlandığı ( underseed ) söylenir. PRNG'nin kendini tekrarlamadan önceki uzunluğuna periyot denir.

Rastgele sayı dağıtımı, bir PRNG'nin çıkışını başka bir sayı dağılımına dönüştüren bir süreçtir. Düzgün dağılım, eşit olasılıkla X ve Y arasında
(dahil) çıktı üreten bir rastgele sayı dağılımıdır.
*/