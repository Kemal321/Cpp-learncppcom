#include <iostream>

int main()
{
    return 0;
}
/*

13.1 — Program Tanımlı (Kullanıcı Tanımlı) Türlerin Girişi 
----------------------------------------------------------
Temel türler, C++ dilinin çekirdek parçası olarak tanımlandığından, hemen kullanılabilirler. Örneğin, bir değişkeni int veya
double türünde tanımlamak istiyorsak, bunu hemen yapabiliriz:

                    int x; // 'int' temel türünde değişken tanımla
                    double d; // 'double' temel türünde değişken tanımla

Bu, temel türlerin basit genişlemeleri olan bileşik türler (fonksiyonlar, işaretçiler, referanslar ve diziler dahil) için de 
geçerlidir:

                    void fcn(int) {}; // 'void()(int)' türünde bir fonksiyon tanımla
                    int* ptr; // 'int'e işaret eden' bileşik türünde değişken tanımla
                    int& ref { x }; // 'int'e referans' bileşik türünde değişken tanımla (x ile başlatıldı)
                    int arr[5]; // 5 tam sayıdan oluşan bir dizi tanımla, türü 'int[5]' (bunu gelecekteki bir bölümde ele alacağız)

Bu, C++ dilinin bu türler için tür adlarını (ve sembollerini) ne anlama geldiğini zaten bildiği için çalışır - herhangi bir tanım
sağlamamız veya içe aktarmamız gerekmez.

Ancak, mevcut bir tür için yeni bir ad tanımlamamıza izin veren bir tür takma adının (10.7 dersinde tanıtılan Typedefs ve tür
takma adları) durumunu düşünün. Bir tür takma adı, programa yeni bir tanımlayıcı eklediği için, bir tür takma adı kullanılmadan
önce tanımlanmalıdır:

                    #include <iostream>

                    using length = int; // 'length' tanımlayıcısı olan bir tür takma adı tanımla

                    int main()
                    {
                        length x { 5 }; // 'length'i burada kullanabiliriz çünkü onu yukarıda tanımladık
                        std::cout << x << '\n';

                        return 0;
                    }

Eğer length tanımını atlatırsak, derleyici bir length’in ne olduğunu bilmez ve bu türü kullanarak bir değişken tanımlamayı
denediğimizde şikayet eder. Length için tanım bir nesne oluşturmaz – sadece derleyiciye bir length’in ne olduğunu söyler, böylece
daha sonra kullanılabilir.

Kullanıcı Tanımlı / Program Tanımlı Türler Nedir?
-------------------------------------------------
Önceki bölümün girişinde (12.1 — Bileşik Veri Türlerine Giriş), bir kesiri, kavramsal olarak birbirine bağlı olan bir pay ve payda
ile saklama isteğini tanıttık. Bu derste, bir kesirin pay ve paydasını bağımsız olarak saklamak için iki ayrı tam sayı kullanmanın
zorluklarını tartıştık.

Eğer C++'ta yerleşik bir kesir türü olsaydı, bu mükemmel olurdu – ama yok. Ve C++'ta, birinin ihtiyaç duyabileceği her şeyi 
önceden tahmin etmek (hele bunları uygulamak ve test etmek) mümkün olmadığı için, potansiyel olarak yararlı yüzlerce diğer tür
de dahil değil.

Bunun yerine, C++ bu tür sorunları farklı bir şekilde çözer: programlarımızda kullanmak üzere tamamen yeni, özel türler
oluşturmamıza izin vererek! Bu tür türler genellikle kullanıcı tanımlı türler olarak adlandırılır (ancak program tanımlı türler
teriminin daha iyi olduğunu düşünüyoruz – bu dersin ilerleyen kısmında farkı tartışacağız). C++'ta bunu sağlayan iki kategori
bileşik tür vardır: numaralandırılmış türler (kapsamsız ve kapsamlı numaralandırmalar dahil (unscoped and scoped enumerations) ve
sınıf türleri (yapılar(structs),sınıflar (classes) ve birlikler (unions) dahil).

                    // Derleyicinin bir Fraction'ın ne olduğunu anlaması için Fraction adında bir program tanımlı tür tanımlayın
                    // (Bir struct'ın ne olduğunu ve nasıl kullanılacağını bu bölümün ilerleyen kısmında açıklayacağız)
                    // Bu sadece bir Fraction türünün neye benzediğini tanımlar, bir tane oluşturmaz
                    struct Fraction
                    {
	                    int pay {};
	                    int payda {};
                    };

                    // Şimdi Fraction türümüzü kullanabiliriz
                    int main()
                    {
	                    Fraction f{ 3, 4 }; // Bu aslında f adında bir Fraction nesnesi oluşturur

	                    return 0;
                    }

Bu örnekte, yeni bir program tanımlı tür olan Fraction’ı tanımlamak için struct anahtar kelimesini kullanıyoruz (global kapsamda,
böylece dosyanın geri kalanında her yerde kullanılabilir). Bu herhangi bir bellek ayırmaz – sadece derleyiciye bir Fraction’ın
neye benzediğini söyler, böylece daha sonra Fraction türünde nesneler ayırabiliriz. Daha sonra, main() içinde, f adında bir
Fraction türünde değişken oluşturuyoruz (ve başlatıyoruz).

Program tanımlı tür tanımları her zaman noktalı virgülle biter. Tür tanımının sonunda noktalı virgülü eklememek yaygın bir
programcı hatasıdır ve hata ayıklaması zor olabilir çünkü derleyici genellikle tür tanımından sonraki satırda hata verir. Örneğin,
yukarıdaki örnekte Fraction tanımının sonundaki noktalı virgülü çıkarırsanız (8. satır), derleyici muhtemelen main() tanımı
hakkında (11. satır) şikayet eder.

*** Uyarı -> Tür tanımlarınızı bir noktalı virgülle bitirmeyi unutmayın, aksi takdirde derleyici genellikle bir sonraki kod
             satırında hata verir.

Program Tanımlı Türlerin Adlandırılması
---------------------------------------
Geleneksel olarak, program tanımlı türler büyük harfle başlar ve bir sonek kullanmazlar (ör. Fraction, fraction, fraction_t veya 
Fraction_t değil).

*** BEST -> Program tanımlı türlerinizi büyük harfle başlatın ve bir sonek kullanmayın.

Yeni programcılar bazen aşağıdaki gibi değişken tanımlarını tür adı ve değişken adı arasındaki benzerlik nedeniyle kafa
karıştırıcı bulabilirler:

                    Fraction fraction {}; // Fraction türünde fraction adında bir değişken oluşturur

Bu, diğer herhangi bir değişken tanımından farklı değildir: önce tür (Fraction) gelir (ve Fraction büyük harfle başladığı için, 
bunun bir program tanımlı tür olduğunu biliyoruz), ardından değişken adı (fraction) ve ardından isteğe bağlı bir başlatıcı. 
C++ büyük/küçük harfe duyarlı olduğu için burada bir adlandırma çakışması yok!

Çok Dosyalı Bir Program Boyunca Program Tanımlı Türlerin Kullanılması
---------------------------------------------------------------------
Bir program tanımlı türü kullanan her kod dosyası, türün kullanıldığı yerden önce tam tür tanımını görmelidir. İleri bildirim
yeterli değildir. Bu, derleyicinin o türden nesneler için ne kadar bellek ayırması gerektiğini bilmesi gereklidir.

Tür tanımlarını ihtiyaç duyan kod dosyalarına yaymak için, program tanımlı türler genellikle başlık dosyalarında tanımlanır ve 
ardından o tür tanımını gerektiren her kod dosyasına #include edilir. Bu başlık dosyaları genellikle program tanımlı türle aynı
adı alır (ör. Fraction adında bir program tanımlı tür, Fraction.h’de tanımlanır)

En İyi Uygulama

Yalnızca bir kod dosyasında kullanılan bir program tanımlı tür, mümkün olduğunca ilk kullanım noktasına yakın bir yerde o kod 
dosyasında tanımlanmalıdır.

Birden çok kod dosyasında kullanılan bir program tanımlı tür, program tanımlı türle aynı adı taşıyan bir başlık dosyasında 
tanımlanmalı ve ardından her kod dosyasına gerektiği gibi #include edilmelidir.

İşte Fraction türümüzü bir başlık dosyasına (Fraction.h adında) taşıyıp birden çok kod dosyasına dahil edilebilecek şekilde neye 
benzeyeceği hakkında bir örnek:

Fraction.h:
                    #ifndef FRACTION_H
                    #define FRACTION_H

                    // Fraction adında yeni bir tür tanımlayın
                    // Bu sadece bir Fraction'ın neye benzediğini tanımlar, bir tane oluşturmaz
                    // Bu bir tam tanımdır, ileri bildirim değil
                    struct Fraction
                    {
                        int pay {};
                        int payda {};
                    };

                    #endif

Fraction.cpp:
                    #include "Fraction.h" // Bu kod dosyasına Fraction tanımımızı dahil edin

                    // Şimdi Fraction türümüzü kullanabiliriz
                    int main()
                    {
                        Fraction f{ 3, 4 }; // Bu aslında f adında bir Fraction nesnesi oluşturur

                        return 0;
                    }

Tür tanımları, bir tanımlama kuralı olan (ODR) kısmen muaf tutulmuştur

2.7 dersinde -- İleri Bildirimler ve Tanımlar, bir tanımlama kuralının her fonksiyon ve global değişkenin program başına yalnızca
bir tanımına sahip olmasını gerektirdiğini tartıştık. Tanımı içermeyen bir dosyada belirli bir fonksiyonu veya global değişkeni 
kullanmak için, bir ileri bildirime (genellikle bir başlık dosyası aracılığıyla yaydığımız) ihtiyacımız var. Bu, fonksiyonlar ve
non-constexpr değişkenler söz konusu olduğunda derleyiciyi tatmin etmek için bildirimlerin yeterli olduğu için çalışır ve 
bağlayıcı daha sonra her şeyi bağlar.

Ancak, türler için ileri bildirimleri benzer bir şekilde kullanmak işe yaramaz, çünkü derleyici genellikle belirli bir türü
kullanmak için tam tanımı görmeye ihtiyaç duyar. Her kod dosyasına tam tür tanımını yayabilmeliyiz.

Bunu sağlamak için, türler bir tanımlama kuralından ( ODR ) kısmen muaf tutulur: belirli bir tür, birden çok kod dosyasında 
tanımlanabilir. Bu yeteneği zaten kullanmış olabilirsiniz (muhtemelen farkında olmadan): programınızda <iostream> 'u içeren iki
kod dosyası varsa, tüm giriş/çıkış tür tanımlarını her iki dosyaya da içe aktarıyorsunuz.

Bilmeye değer iki uyarı var.
* - İlk olarak, hala her kod dosyası başına yalnızca bir tür tanımına sahip olabilirsiniz (bu genellikle bir sorun olmaz çünkü 
    başlık korumaları bunu önler). 
* - İkincisi, belirli bir tür için tüm tür tanımları aynı olmalıdır, aksi takdirde tanımsız davranış sonucu olur.( inline gibi )

Terimler: kullanıcı tanımlı türler vs program tanımlı türler
------------------------------------------------------------
"Kullanıcı tanımlı tür" terimi bazen gündelik konuşmalarda ortaya çıkar ve C++ dil standardında da belirtilir (ancak tanımlanmaz).
Gündelik konuşmalarda, terim genellikle "kendi programlarınızda tanımlanan bir tür" anlamına gelir (yukarıdaki Fraction tür örneği
gibi).

C++ dil standardı, "kullanıcı tanımlı tür" terimini geleneksel olmayan bir şekilde kullanır. Dil standardında, bir "kullanıcı 
tanımlı tür", sizin, standart kütüphanenin veya uygulamanın (ör. dil genişlemelerini desteklemek için derleyici tarafından 
tanımlanan türler) tanımladığı herhangi bir sınıf türü veya numaralandırılmış türdür. Belki de karşı sezgisel olarak, bu,
std::string'in (standart kütüphanede tanımlanan bir sınıf türü) bir kullanıcı tanımlı tür olarak kabul edildiği anlamına gelir!

Ek ayrım sağlamak için, C++20 dil standardı, standart kütüphane, uygulama veya çekirdek dilin bir parçası olarak tanımlanmayan
sınıf türlerini ve numaralandırılmış türleri ifade etmek için "program tanımlı tür" terimini tanımlar. Diğer bir deyişle,
"program tanımlı türler" yalnızca bizim (veya bir üçüncü taraf kütüphanesi) tarafından tanımlanan sınıf türlerini ve enum 
türlerini içerir.

Sonuç olarak, yalnızca kendi programlarımızda tanımladığımız sınıf türleri ve enum türleri hakkında konuşurken, "program tanımlı"
terimini tercih ederiz, çünkü daha kesin bir tanımı vardır.

Tür                Anlam                                                                             Örnekler
----------------------------------------------------------------------------------------------------------------------------------
Temel              Çekirdek C++ diline yerleşik bir tür                                          int, std::nullptr_t
Bileşik            Temel türlerden oluşturulan bir tür                                   int&, double*, std::string, Fraction
Kullanıcı Tanımlı  Bir sınıf türü veya numaralandırılmış tür                                    std::string, Fraction
                   (Standart kütüphanede veya uygulamada tanımlananları içerir)
                   (Gündelik kullanımda, genellikle program tanımlı türler anlamına gelir)    
Program Tanımlı    Bir sınıf türü veya numaralandırılmış tür
                   (Standart kütüphane veya uygulamada tanımlananları hariç tutar)                    Fraction
----------------------------------------------------------------------------------------------------------------------------------

13.2 Kapsamsız Numaralandırılmış türler ( Unscoped enumerations )
-----------------------------------------------------------------
C++ birçok kullanışlı temel ve bileşik veri türü içerir. Ancak bu türler, yapmak istediğimiz şeyler için her zaman yeterli
olmayabilir. Örneğin, bir elmanın kırmızı, sarı veya yeşil olup olmadığını veya bir gömleğin rengini (önceden belirlenmiş bir
renk listesinden) takip etmesi gereken bir program yazıyorsunuz diyelim. Eğer sadece temel türler mevcut olsaydı, bunu nasıl
yapardınız?

Rengi bir tam sayı değeri olarak saklayabilir, bazı türden bir içsel eşlemeyi kullanabilirsiniz (0 = kırmızı, 1 = yeşil, 2 = mavi):
                    int main()
                    {
                        int elmaRengi{ 0 }; // elma kırmızı
                        int gomlekRengi{ 1 }; // gömlek yeşil

                        return 0;
                    }

Ama bu hiç de sezgisel değil ve sihirli sayıların neden kötü olduğunu zaten tartıştık. Sembolik sabitleri kullanarak sihirli 
sayılardan kurtulabiliriz:

                    constexpr int kirmizi{ 0 };
                    constexpr int yesil{ 1 };
                    constexpr int mavi{ 2 };

                    int main()
                    {
                        int elmaRengi{ kirmizi };
                        int gomlekRengi{ yesil };

                        return 0;
                    }

Bu, okuma için biraz daha iyidir, ancak programcı hala elmaRengi ve gomlekRengi’nin (int türünde olan) renk sembolik sabitlerinden
birini tutması gerektiğini çıkarmak zorundadır (bu sabitler muhtemelen başka bir yerde, muhtemelen ayrı bir dosyada tanımlanmıştır)
Bu programı biraz daha açık hale getirmek için bir tür takma adı kullanabiliriz:

using Renk = int; // Renk adında bir tür takma adı tanımla

// Aşağıdaki renk değerleri bir Renk için kullanılmalıdır
constexpr Renk kirmizi{ 0 };
constexpr Renk yesil{ 1 };
constexpr Renk mavi{ 2 };

int main()
{
    Renk elmaRengi{ kirmizi };
    Renk gomlekRengi{ yesil };

    return 0;
}

Daha yaklaşıyoruz. Bu kodu okuyan biri hala bu renk sembolik sabitlerinin Renk türündeki değişkenlerle kullanılması gerektiğini
anlamalı, ancak en azından türün artık benzersiz bir adı var, böylece Renk arayan biri ilişkili sembolik sabitler kümesini,
bulabilir.

Ancak, Renk sadece bir int için bir takma ad olduğu için, bu renk sembolik sabitlerinin uygun kullanımını zorlayan hiçbir şey yok.
Hala şöyle bir şey yapabiliriz:

Renk gozRengi{ 8 }; // sözdizimsel olarak geçerli, anlamsal olarak anlamsız

Ayrıca, bu değişkenlerin herhangi birini hata ayıklayıcımızda hata ayıklarsak, yalnızca rengin tam sayı değerini (ör. 0) görürüz,
sembolik anlamını (kırmızı) değil, bu da programımızın doğru olup olmadığını anlamayı zorlaştırabilir.

Neyse ki, daha iyisini yapabiliriz.

İlham kaynağı olarak, bool türünü düşünün. Bool’u özellikle ilginç kılan şey, yalnızca iki tanımlı değeri olmasıdır: true ve false.
True veya false’u doğrudan (literaller olarak) kullanabiliriz, ya da bir bool nesnesi oluşturabilir ve onun bu değerlerden birini
tutmasını sağlayabiliriz. Ayrıca, derleyici bool’u diğer türlerden ayırt edebilir. Bu, fonksiyonları aşırı yükleyebileceğimiz ve
bu fonksiyonların bir bool değeri geçirildiğinde nasıl davranacağını özelleştirebileceğimiz anlamına gelir.

Kendi özel türlerimizi tanımlama yeteneğimiz olsaydı, bu türle ilişkilendirilmiş adlandırılmış değerler kümesini tanımlayabilirdik,
o zaman yukarıdaki zorluğu zarif bir şekilde çözmek için mükemmel bir aracımız olurdu…

Numaralandırmalar ( Enumerations )
----------------------------------
Bir numaralandırma (veya enum), değerleri adlandırılmış sembolik
sabitler kümesiyle (numaralandırıcılar olarak adlandırılır) sınırlı bir bileşik veri türüdür.

C++ iki tür numaralandırmayı destekler: kapsamsız numaralandırmalar ve kapsamlı numaralandırmalar.

Numaralandırmalar, program tanımlı türler olduğu için,her numaralandırmanın tam olarak tanımlanması gerekiyor,
kullanmadan önce (bir ileri bildirim yeterli değil).

Kapsamsız Numaralandırmalar ( Unscoped Enumerations )
-----------------------------------------------------
Kapsamsız numaralandırmalar, enum anahtar kelimesi aracılığıyla tanımlanır.

Numaralandırılmış türler en iyi örneklerle öğretilir, bu yüzden bazı renk değerlerini tutabilecek bir kapsamsız numaralandırma
tanımlayalım. Nasıl çalıştığını aşağıda açıklayacağız.
                    // Color adında yeni bir enum tanımla
                    enum Color
                    {
                        // İşte enum değerleri
                        // Bu sembolik sabitler, bu tipin alabileceği tüm değerleri tanımlar
                        // Her enum değeri virgülle ayrılır, noktalı virgülle değil
                        red,
                        green,
                        blue, // son enum değerinden sonra virgül opsiyonel ama tavsiye edilir
                    }; // enum tanımı noktalı virgülle bitmeli

                    int main()
                    {
                        // Color tipinde birkaç değişken tanımla
                        Color apple { red };   // elma kırmızı
                        Color shirt { green }; // gömlek yeşil
                        Color cup { blue };    // bardak mavi

                        Color socks { white }; // hata: white, Color'ın bir enum değeri değil
                        Color hat { 2 };       // hata: 2, Color'ın bir enum değeri değil

                        return 0;
                    }

Örneğimize, enum anahtar kelimesini kullanarak derleyiciye Color adında bir enum tanımladığımızı söyleyerek başlıyoruz.

Bir çift süslü parantez içinde, Color tipi için enum değerlerini tanımlıyoruz: red, green ve blue. Bu enum değerleri, 
Color tipinin sınırlı olduğu belirli değerleri tanımlar. Her enum değeri virgülle ayrılmalıdır (noktalı virgülle değil) -
son enum değerinden sonra virgül opsiyonel ama tutarlılık için tavsiye edilir.

Color için tip tanımı bir noktalı virgülle biter. Artık Color adlı enum tipini tamamen tanımladık!

main() içinde, Color tipinde üç değişken oluşturuyoruz: apple, red rengiyle başlatılıyor; shirt, green rengiyle başlatılıyor;
ve cup, blue rengiyle başlatılıyor. Bu nesneler için bellek ayrılır. Bir enum tipinin başlatıcısı, o tip için tanımlanan enum
değerlerinden biri olmalıdır. Socks ve hat değişkenleri derleme hatalarına neden olur çünkü başlatıcılar white ve 2, 
Color'ın enum değerleri değildir.

Enum değerleri implisit ( bilinçsiz - otomatik ) olarak constexpr'dir.

Hatırlatma

Terimler üzerinde hızlıca bir özet yapalım:

Bir enum veya enum tipi, program tarafından tanımlanan tipin kendisidir (ör. Color).
Bir enum değeri, enum'a ait belirli bir adlandırılmış değerdir (ör. red).
Enum ve enum değerlerinin adlandırılması

Geleneksel olarak, enum tiplerinin adları büyük harfle başlar (tüm program tarafından tanımlanan tipler gibi).

*** Uyarı -> Enum'ların adlandırılması zorunlu değildir, ancak modern C++'da isimsiz enum'ların kullanılması kaçınılmalıdır.

Enum değerlerine isim verilmelidir. Ne yazık ki, enum değerlerinin isimleri için ortak bir adlandırma kuralı yoktur. Yaygın
seçenekler arasında küçük harfle başlama (ör. red), büyük harfle başlama (Red), tüm büyük harfler (RED), bir önek ile tüm büyük 
harfler (COLOR_RED) veya "k" ile öne çıkan ve büyük harfle başlayan (kColorRed) bulunur.

Modern C++ kuralları genellikle tüm büyük harfli adlandırma kurallarından kaçınmayı önerir, çünkü tüm büyük harfler genellikle
önişlemci makroları için kullanılır ve çakışabilir. Büyük harfle başlayan kurallardan kaçınmayı da öneririz, çünkü büyük harfle
başlayan isimler genellikle program tarafından tanımlanan tipler için ayrılmıştır.

*** BEST -> Enum tiplerinizi büyük harfle başlayarak adlandırın. Enum değerlerinizi küçük harfle başlayarak adlandırın.

Enum tipleri ayrı tiplerdir

Oluşturduğunuz her enum tipi, derleyicinin diğer tiplerden ayırt edebileceği ayrı bir tip olarak kabul edilir 
(typedef'ler veya tip takma adları aksine, bunlar takma ad oldukları tiplerle aynı kabul edilir).

Çünkü enum tipleri ayrıdır, bir enum tipinin parçası olarak tanımlanan enum değerleri, başka bir enum tipinin nesneleriyle
kullanılamaz:

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
                        Pet myPet { black }; // derleme hatası: black, Pet'in bir enum değeri değil
                        Color shirt { pig }; // derleme hatası: pig, Color'ın bir enum değeri değil

                        return 0;
                    }

Muhtemelen zaten domuzlu bir gömlek istemezdiniz.

Numaralandırmaları Kullanma ( Putting Enumerations to use )
-----------------------------------------------------------
Numaralandırmalar açıklayıcı olduğu için, kod belgelerini ve okunabilirliğini artırmak için yararlıdırlar. Numaralandırılmış 
türler, küçük bir ilgili sabitler kümesine sahip olduğunuzda ve nesnelerin aynı anda yalnızca bu değerlerden birini tutması 
gerektiğinde en iyi şekilde kullanılır.

Genellikle tanımlanan numaralandırılmalar arasında haftanın günleri, ana yönler ve bir kart destesindeki takımlar bulunur:

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

Bazen fonksiyonlar, fonksiyonun başarıyla yürütülüp yürütülmediğini veya bir hata ile karşılaşıp karşılaşmadığını belirtmek için
bir durum kodunu çağırıcıya döndürür. Geleneksel olarak, farklı olası hata kodlarını temsil etmek için küçük negatif sayılar 
kullanılırdı. Örneğin:

                    int dosyaIceriginiOku()
                    {
                        if (!dosyayiAc())
                            return -1;
                        if (!dosyayiOku())
                            return -2;
                        if (!dosyayiAyristir())
                            return -3;

                        return 0; // başarı
                    }

Ancak, bu tür sihirli sayıları kullanmak çok açıklayıcı değildir. Daha iyi bir yöntem, bir numaralandırılmış tür kullanmaktır:

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

Daha sonra çağırıcı, fonksiyonun dönüş değerini uygun numaralandırıcıya karşı test edebilir, bu da dönüş sonucunu belirli bir tam
sayı değeri için test etmekten daha kolay anlaşılır.

                    if (dosyaIceriginiOku() == okumaSonucuBasari)
                    {
                        // bir şey yap
                    }
                    else
                    {
                        // hata mesajı yazdır
                    }

numaralandırılmış türler, oyunlarda da iyi bir şekilde kullanılabilir, farklı türdeki öğeleri, canavarları veya arazileri
tanımlamak için. Temel olarak, küçük bir ilgili nesneler kümesi olan her şey.

Örneğin:

                    enum ÖğeTürü
                    {
                        kılıç,
                        meşale,
                        iksir,
                    };

                    int main()
                    {
                        ÖğeTürü tutulan{ meşale };

                        return 0;
                    }

numaralandırılmış türler, kullanıcının iki veya daha fazla seçenek arasında bir seçim yapması gerektiğinde yararlı işlev 
parametreleri yapabilir:

                    enum SıralamaDüzeni
                    {
                        alfabetik,
                        alfabetikTers,
                        sayısal,
                    };

                    void veriyiSırala(SıralamaDüzeni düzen)
                    {
                        switch (düzen)
                        {
                            case alfabetik:
                                // veriyi ileri alfabetik sırayla sırala
                                break;
                            case alfabetikTers:
                                // veriyi geri alfabetik sırayla sırala
                                break;
                            case sayısal:
                                // veriyi sayısal olarak sırala
                                break;
                        }
                    }

Birçok dil, Boole'ları tanımlamak için numaralandırılmaları kullanır - sonuçta, bir Boole, temelde yalnızca 2 numaralandırıcıya
sahip bir sayılandırmadır: false ve true! Ancak, C++'da, true ve false, numaralandırmalar yerine anahtar kelimeler olarak 
tanımlanmıştır.

numaralandırılmalar küçük ve kopyalaması ucuz olduğu için, onları değer olarak geçmek (ve döndürmek) iyidir.

Ders O.1 -- Bit bayrakları ve bit manipülasyonu via std::bitset, konusunda bit bayraklarını tartıştık. numaralandırılmalar,
std::bitset ile kullanılmak üzere ilgili bit bayrak pozisyonlarının bir koleksiyonunu tanımlamak için de kullanılabilir:

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

                        std::cout << std::boolalpha; // bool'u true/false olarak yazdır

                        // Birkaç durumu sorgula (herhangi bir bitin ayarlı olup olmadığını görmek için any() fonksiyonunu
                           kullanırız)
                        std::cout << "Mutlu muyum? " << ben.test(Bayraklar::mutlu) << '\n';
                        std::cout << "Gülüyor muyum? " << ben.test(Bayraklar::gulu) << '\n';

                        return 0;
                    }
Bir tam sayı değerinin beklendiği yerde bir numaralandırıcıyı nasıl kullanabileceğimizi merak ediyorsanız, kapsamsız
numaralandırıcılar otomatik olarak tam sayı değerlerine dönüştürülür. Bunu bir sonraki derste (13.3 – Kapsamsız numaralandırma 
girişi ve çıkışı) daha ayrıntılı olarak inceleyeceğiz.

Kapsamsız Numaralandırmaların Kapsamı

Kapsamsız numaralandırmalar, numaralandırıcı adlarını numaralandırma tanımının kendisiyle aynı kapsama koyarlar 
(bir ad alanının yaptığı gibi yeni bir kapsam bölgesi oluşturmak yerine).

Örneğin, bu programı verelim:

                    enum Renk // bu enum global ad alanında tanımlanmıştır
                    {
                        kirmizi, // bu yüzden kirmizi global ad alanına konulur
                        yesil,
                        mavi,
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma kırmızı

                        return 0;
                    }
Renk numaralandırması global kapsamda tanımlanmıştır. Bu nedenle, tüm numaralandırma adları (kırmızı, yeşil ve mavi) de global
kapsama girer. Bu, global kapsamı kirletir ve ad çakışma olasılığını önemli ölçüde artırır.

Bunun bir sonucu olarak, bir numaralandırıcı adı aynı kapsamdaki birden çok numaralandırmada kullanılamaz:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alanına konulur
                    };

                    enum Duygu
                    {
                        mutlu,
                        yorgun,
                        mavi, // hata: yukarıdaki mavi ile ad çakışması
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // elma kırmızı
                        Duygu ben { mutlu }; // şu anda mutluyum (programım derlenmiyor olsa bile)

                        return 0;
                    }

Yukarıdaki örnekte, her iki kapsamsız numaralandırma (Renk ve Duygu) aynı adı taşıyan numaralandırıcıları global kapsama koyar.
Bu, bir ad çakışmasına ve ardından derleme hatasına yol açar.

Kapsamsız numaralandırmalar ayrıca numaralandırıcıları için adlandırılmış bir kapsam bölgesi sağlar (bir ad alanının içindeki
adları içeren bir adlandırılmış kapsam bölgesi gibi). Bu, bir kapsamsız numaralandırmanın numaralandırıcılarına şu şekilde
erişebileceğimiz anlamına gelir:

                    enum Renk
                    {
                        kirmizi,
                        yesil,
                        mavi, // mavi global ad alanına konulur
                    };

                    int main()
                    {
                        Renk elma { kirmizi }; // tamam, numaralandırıcıyı global ad alanından erişiyor
                        Renk ahududu { Renk::kirmizi }; // ayrıca tamam, numaralandırıcıyı Renk kapsamından erişiyor

                        return 0;
                    }

Çoğu zaman, kapsamsız numaralandırıcılar kapsam çözümleme operatörünü kullanmadan erişilir.

Numaralandırıcı Ad Çakışmalarını Önlemek
----------------------------------------
Kapsamsız numaralandırıcı ad çakışmalarını önlemenin oldukça yaygın birkaç yolu vardır. Bir seçenek, her numaralandırıcıyı
numaralandırmanın adıyla öne koymaktır:

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
                        duygu_mavi, // artık renk_mavi ile ad çakışması yok
                    };

                    int main()
                    {
                        Renk boya { renk_mavi };
                        Duygu ben { duygu_mavi };

                        return 0;
                    }

Bu hala ad alanını kirletir ama adları daha uzun ve daha benzersiz yaparak ad çakışma olasılığını azaltır. Daha iyi bir seçenek,
numaralandırılmış türü, ayrı bir kapsam bölgesi sağlayan bir şeyin içine koymaktır, örneğin bir ad alanı:

                    namespace Renk
                    {
                        // Renk, kırmızı, mavi ve yeşil adları, Renk ad alanı içinde tanımlanır
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
                            mavi, // Duygu::mavi, Renk::mavi ile çakışmaz
                        };
                    }

                    int main()
                    {
                        Renk::Renk boya{ Renk::mavi };
                        Duygu::Duygu ben{ Duygu::mavi };

                        return 0;
                    }

Bu, artık numaralandırma ve numaralandırıcı adlarımızı kapsam bölgesinin adıyla öne koymamız gerektiği anlamına gelir.
İlgili bir seçenek, kendi kapsam bölgesini tanımlayan bir kapsamlı numaralandırma kullanmaktır göreceğiz.
*** BEST -> Numaralandırmalarınızı, numaralandırıcıların global ad alanını kirletmemesi için adlandırılmış bir kapsam bölgesi 
            içine koymayı tercih edin (örneğin bir ad alanı veya sınıf).

Alternatif olarak, bir numaralandırma yalnızca tek bir fonksiyonun gövdesinde kullanılıyorsa, numaralandırma fonksiyonun içinde 
tanımlanmalıdır. Bu, numaralandırmanın ve numaralandırıcılarının kapsamını yalnızca o fonksiyona sınırlar. Bu tür bir 
numaralandırmanın numaralandırıcıları, global kapsamda tanımlanan aynı adlı numaralandırıcıları gölgede bırakır.

Numaralandırıcılarla Karşılaştırma
----------------------------------
Bir numaralandırmanın belirli bir numaralandırıcının değerine sahip olup olmadığını test etmek için eşitlik operatörlerini
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

                        if (gomlek == mavi) // eğer gömlek maviyse
                            std::cout << "Gömleğiniz mavi!";
                        else
                            std::cout << "Gömleğiniz mavi değil!";

                        return 0;
                    }
Yukarıdaki örnekte, bir if-deyimi kullanarak gomleğin numaralandırıcı maviye eşit olup olmadığını test ediyoruz. Bu, programımızın
davranışını, numaralandırmamızın hangi numaralandırıcıyı tuttuğuna dayalı olarak koşullandırmamız için bir yol sağlar.

Bunu bir sonraki derste daha fazla kullanacağız.
*/
