#include <iostream>
class DateClass {
public:
    int m_day{};
    int m_month{};
    int m_year{};
};
void printDate(const DateClass& date) {
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year << '\n';
}
struct quizIntPair {
    int one{};
    int two{};
    void print() {
        std::cout << "First: " << one << "\nSecond: " << two << '\n';
    }
    bool isEqual(const quizIntPair p) {
        return (one == p.one && two == p.two);
    }
};
struct Date {
    int day{};
    int month{};
    int year{};

    void print() 
    {
        std::cout << day << '/' << month << '/' << year << '\n';
    }
    
};


int main()
{
    quizIntPair p1{ 1, 2 };
    quizIntPair p2{ 3, 4 };

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
    std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

    DateClass dateClass{ 4,10,21 };
    printDate(dateClass);

    // Struct member fonksiyon örneği
    Date date{ 28,04,1999 };
    date.print();
    
    return 0;
}
/*
14.1 — Nesne yönelimli programlamaya giriş

Yordamsal programlama (Procedural programming)
----------------------------------------------
Ders 1.3 -- Nesneler ve değişkenlere girişte, C++'daki bir nesneyi “değer saklamak için kullanılabilecek bir bellek parçası” 
olarak tanımladık. Bir ismi olan nesneye değişken denir. C++ programlarımız, bilgisayara veri tanımlayan (nesneler aracılığıyla) 
ve bu veriler üzerinde işlemler gerçekleştiren (ifadeler ve deyimler içeren fonksiyonlar aracılığıyla) talimatların ardışık 
listelerinden oluşmuştur.

Şimdiye kadar, yordamsal programlama adı verilen bir programlama türünü gerçekleştirdik. Yordamsal programlamada, program
mantığımızı uygulayan "yordamlar" oluşturmak üzerinde durulur (C++'da bunlara fonksiyon denir). Bu fonksiyonlara veri nesnelerini 
geçeriz, bu fonksiyonlar veriler üzerinde işlemler gerçekleştirir ve ardından potansiyel olarak çağıran tarafından kullanılacak
bir sonuç döndürür.

Yordamsal programlamada, fonksiyonlar ve bu fonksiyonların üzerinde işlem yaptığı veriler ayrı varlıklardır. Programcı, 
fonksiyonları ve verileri bir araya getirerek istenen sonucu üretmekten sorumludur. Bu, şu şekilde bir koda yol açar:

                eat(you, apple);

Şimdi etrafınıza bir bakın -- her yerde nesneler var: kitaplar, binalar, yiyecekler ve hatta siz. Bu nesnelerin iki ana 
bileşeni vardır: 
1) Bir dizi ilişkili özellik (ör. ağırlık, renk, boyut, katılık, şekil, vb...), ve
2) Sergileyebilecekleri bir dizi davranış (ör. açılma, başka bir şeyi ısıtma, vb...). Bu özellikler ve davranışlar ayrılmaz.

Programlamada, özellikler nesneler tarafından, davranışlar ise fonksiyonlar tarafından temsil edilir. Ve böylece, yordamsal 
programlama, özellikleri (nesneler) ve davranışları (fonksiyonlar) ayırarak gerçeği oldukça kötü temsil eder.

Nesne yönelimli programlama nedir?
----------------------------------
Nesne yönelimli programlamada (genellikle OOP olarak kısaltılır), odak noktası, hem özellikleri hem de iyi tanımlanmış bir 
davranış setini içeren program tanımlı veri türlerini oluşturmaktır. OOP'deki “nesne” terimi, bu türlerden örnekleyebileceğimiz
nesnelere atıfta bulunur.

Bu, kodun daha çok şu şekilde görünmesine yol açar:

                you.eat(apple);

Bu, kimin nesne olduğunu (you), hangi davranışın çağrıldığını (eat()), ve hangi nesnelerin bu davranışa aksesuar olduğunu (apple) 
daha net hale getirir.

Özellikler ve davranışlar artık ayrı olmadığı için, nesneleri modülerleştirmek daha kolaydır, bu da programlarımızı yazmayı ve
anlamayı kolaylaştırır ve ayrıca daha yüksek bir kod yeniden kullanılabilirliği sağlar. Bu nesneler, nesnelerle nasıl etkileşim
kurduğumuzu ve onların diğer nesnelerle nasıl etkileşim kurduğunu tanımlayarak verilerimizle çalışmayı daha sezgisel hale getirir.
Bu tür nesneleri nasıl oluşturacağımızı bir sonraki derste tartışacağız.
Yordamsal vs OOP benzeri bir örnek
----------------------------------
İşte bir hayvanın adını ve bacak sayısını yazdıran yordamsal programlama tarzında yazılmış kısa bir program:

                #include <iostream>
                #include <string_view>

                enum AnimalType
                {
                    cat,
                    dog,
                    chicken,
                };

                constexpr std::string_view animalName(AnimalType type)
                {
                    switch (type)
                    {
                    case cat: return "cat";
                    case dog: return "dog";
                    case chicken: return "chicken";
                    default:  return "";
                    }
                }

                constexpr int numLegs(AnimalType type)
                {
                    switch (type)
                    {
                    case cat: return 4;
                    case dog: return 4;
                    case chicken: return 2;
                    default:  return 0;
                    }
                }
                int main()
                {
                    constexpr AnimalType animal{ cat };
                    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

                    return 0;
                }
Bu programda, bir hayvanın bacak sayısını almak ve bir hayvanın adını almak gibi şeyleri yapmamıza izin veren fonksiyonlar yazdık.
Bu, oldukça iyi çalışırken, hayvanımızın artık bir yılan olduğunu güncellemek istediğimizde ne olacağını düşünün. Kodumuza bir
yılan eklemek için, AnimalType, numLegs(), animalName()'i değiştirmemiz gerekecek. Eğer bu daha büyük bir kod tabanı olsaydı,
AnimalType'ı kullanan herhangi bir diğer fonksiyonu da güncellememiz gerekecekti -- eğer AnimalType birçok yerde kullanılıyorsa,
bu, dokunulması gereken çok fazla kod olabilir (ve potansiyel olarak bozulabilir).
Şimdi, aynı programı (aynı çıktıyı üreten) daha çok bir OOP zihniyeti kullanarak yazalım:

                #include <iostream>
                #include <string_view>

                struct Cat
                {
                    std::string_view name{ "cat" };
                    int numLegs{ 4 };
                };

                struct Dog
                {
                    std::string_view name{ "dog" };
                    int numLegs{ 4 };
                };

                struct Chicken
                {
                    std::string_view name{ "chicken" };
                    int numLegs{ 2 };
                };

                int main()
                {
                    constexpr Cat animal;
                    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

                    return 0;
                }
Bu örnekte, her hayvan kendi program tanımlı tipidir ve bu tip, o hayvanla ilgili her şeyi yönetir (bu durumda, sadece adı ve 
bacak sayısını takip etmek). Şimdi, hayvanımızı bir yılana güncellemek istediğimiz durumu düşünün. Tek yapmamız gereken bir Snake
tipi oluşturmak ve onu Cat yerine kullanmaktır. Çok az mevcut kodun değiştirilmesi gerekiyor, bu da zaten çalışan bir şeyi bozma
riskinin çok daha az olması anlamına gelir.

Sunulan şekliyle, Cat, Dog ve Chicken örneğimiz yukarıda çok fazla tekrar içeriyor (her biri tamamen aynı üye setini tanımlıyor).
Bu gibi bir durumda, ortak bir Animal struct oluşturmak ve her hayvan için bir örnek oluşturmak tercih edilebilir. Ama ya diğer
hayvanlara uygulanmayan Chicken'a yeni bir üye eklemek istiyorsak (ör. wormsPerDay)? Ortak bir Animal struct ile, tüm hayvanlar
bu üyeyi alır. OOP modelimizle, bu üyeyi Chicken nesneleriyle sınırlayabiliriz.

OOP, masaya başka faydalar da getirir
-------------------------------------
Okulda, programlama ödevlerinizi teslim ettiğinizde, işiniz esasen bitmiştir. Profesörünüz veya öğretim görevliniz kodunuzu 
çalıştırır ve doğru sonucu üretip üretmediğini görür. Ya yapar ya da yapmaz ve buna göre notlandırılırsınız. Kodunuz muhtemelen 
bu noktada atılır.

Diğer taraftan, kodunuzu diğer geliştiriciler tarafından kullanılan bir depoya veya gerçek kullanıcıların kullandığı bir 
uygulamaya gönderdiğinizde, tamamen farklı bir oyun söz konusudur. Yeni bir işletim sistemi veya yazılım sürümü kodunuzu 
bozacaktır. Kullanıcılar yaptığınız bazı mantık hatalarını bulacak. Bir iş ortağı yeni bir yetenek talep edecek. Diğer
geliştiriciler kodunuzu bozmadan genişletmek zorunda kalacak. Kodunuzun, belki de önemli ölçüde, evrim geçirebilmesi ve bunu 
minimal zaman yatırımı, minimal baş ağrısı ve minimal kırılma ile yapabilmesi gerekiyor.

Bunları en iyi şekilde ele almanın yolu, kodunuzu olabildiğince modüler (ve tekrarsız) tutmaktır. Bu konuda yardımcı olmak için, 
OOP ayrıca miras, kapsülleme, soyutlama ve çok biçimlilik gibi bir dizi diğer faydalı kavramı da masaya getirir.

Yazarın notu
Dil tasarımcılarının bir felsefesi var: büyük bir kelime yapacaksa, asla küçük bir kelime kullanma.

Ayrıca neden kısaltma kelimesi bu kadar uzun?
---------------------------------------------
Tüm bunların ne olduğunu ve kodunuzu daha az tekrarlı hale getirmeye, değiştirmeyi ve genişletmeyi kolaylaştırmaya nasıl yardımcı 
olabileceğini zamanla anlatacağız. OOP ile doğru şekilde tanıştığınızda ve tıkladığında, muhtemelen saf yordamsal programlamaya
geri dönmek istemeyeceksiniz.

Bu söylenmişken, OOP yordamsal programlamayı değiştirmez -- daha ziyade, gerektiğinde karmaşıklığı yönetmek için programlama araç
çantanıza ek araçlar verir.
“Object” terimi
---------------
“Object” teriminin biraz aşırı yüklendiğini ve bu durumun bir miktar kafa karışıklığına neden olduğunu unutmayın. Geleneksel
programlamada, bir nesne değerleri saklamak için bir bellek parçasıdır. Nesne yönelimli programlamada, bir “nesne”,
hem geleneksel programlama anlamında bir nesne olduğunu, hem de hem özellikleri hem de davranışları birleştirdiğini ima eder.
Bu derslerde, nesne teriminin geleneksel anlamını tercih edeceğiz ve OOP nesnelerine özellikle atıfta bulunurken “sınıf nesnesi”
terimini tercih edeceğiz.

14.2 — Sınıflara Giriş
----------------------
Önceki bölümde, structları ele aldık ve birden çok üye değişkenini tek bir nesneye toplayabilme, başlatma ve bir birim olarak
taşıma konusunda ne kadar iyi olduklarını tartıştık. Başka bir deyişle, structlar, ilgili veri değerlerini depolamak ve taşımak
için uygun bir paket sağlar.
Aşağıdaki structı düşünün:

                #include <iostream>

                struct Date
                {
                    int day{};
                    int month{};
                    int year{};
                };

                void printDate(const Date& date)
                {
                    std::cout << date.day << '/' << date.month << '/' << date.year; // DMY formatını varsayalım
                }

                int main()
                {
                    Date date{ 4, 10, 21 }; // toplu başlatma kullanarak başlat
                    printDate(date);        // tüm structı fonksiyona geçirebilir

                    return 0;
                }
Yukarıdaki örnekte, bir Datenesnesi oluşturuyoruz ve ardından onu tarihi yazdıran bir fonksiyona geçiriyoruz. Bu program şunu 
yazdırır:
                4/10/21
Bir hatırlatma

Bu derslerde, tüm structlarımız topluluklardır. topluluklardır ders 13.6 -- struct topluluğu başlatma dersinde tartışıyoruz.

structlar ne kadar kullanışlı olursa olsun, structların büyük, karmaşık programlar oluştururken (özellikle birden çok geliştirici
tarafından çalışılanlar) zorluklar sunabilecek bir dizi eksikliği vardır.

Sınıf değişmezlik sorunu
------------------------
Belki de structların en büyük zorluğu, sınıf değişmezliklerini belgelemek ve uygulamak için etkili bir yol sağlamamalarıdır. 
Ders 9.6 -- Assert ve static_assert'te, bir değişmezi, "bir bileşenin çalışırken doğru olması gereken bir durum" olarak tanımladık.
Sınıf türleri bağlamında (structları, sınıfları ve unionları içerir), bir sınıf değişmezi, bir nesnenin geçerli bir durumda 
kalması için bir nesnenin ömrü boyunca doğru olması gereken bir durumdur. Değişmezliği ihlal edilmiş bir nesne, geçersiz bir 
durumda olduğu söylenir ve bu nesnenin daha fazla kullanılmasından beklenmeyen veya tanımlanmamış davranışlar ortaya çıkabilir.

Öncelikle, aşağıdaki structı düşünün:

                struct Cift
                {
                    int ilk {};
                    int ikinci {};
                };

İlk ve ikinci üyeler herhangi bir değere bağımsız olarak ayarlanabilir, bu yüzden Cift yapısının bir değişmezi yoktur.

Şimdi aşağıdaki neredeyse aynı structı düşünün:

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 };
                };

Matematikten biliyoruz ki, paydası 0 olan bir kesir matematiksel olarak tanımsızdır (çünkü bir kesirin değeri payının paydasına 
bölünmesidir -- ve 0'a bölme matematiksel olarak tanımsızdır). Bu nedenle, bir Kesir nesnesinin payda üyesinin asla 0'a 
ayarlanmamasını sağlamak istiyoruz. Eğer öyleyse, o Kesir nesnesi geçersiz bir durumdadır ve bu nesnenin daha fazla
kullanılmasından tanımlanmamış davranışlar ortaya çıkabilir.
Örneğin:

                #include <iostream>

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 }; // sınıf değişmezi: asla 0 olmamalı
                };

                void kesirDegeriniYazdir(const Kesir &k)
                {
                     std::cout << k.pay / k.payda << '\n';
                }

                int main()
                {
                    Kesir k { 5, 0 };   // paydası sıfır olan bir Kesir oluştur
                    kesirDegeriniYazdir(k); // sıfıra bölme hatası oluştur

                    return 0;
                }

Yukarıdaki örnekte, Kesir'in değişmezliğini belgelemek için bir yorum kullanıyoruz. Ayrıca, kullanıcı bir başlatma değeri
sağlamazsa paydanın 1'e ayarlanmasını sağlamak için varsayılan bir üye başlatıcısı sağlıyoruz. Bu, kullanıcının bir Kesir 
nesnesini değer başlatmaya karar vermesi durumunda Kesir nesnemizin geçerli olacağını garanti eder. Bu, iyi bir başlangıçtır.

Ama hiçbir şey bizi bu sınıf değişmezini açıkça ihlal etmekten alıkoymaz: Kesir f'yi oluştururken, paydanın açıkça 0'a
başlatılması için toplu başlatmayı kullanırız. Bu hemen bir soruna neden olmasa da, nesnemiz artık geçersiz bir durumdadır ve
nesnenin daha fazla kullanılması beklenmeyen veya tanımsız davranışlara neden olabilir.
Ve bu tam olarak kesirDegeriniYazdir(f)'yi çağırdığımızda gördüğümüz şey: program, sıfıra bölme hatası nedeniyle sona erer.

Bir parantez açalım…

kesirDegeriniYazdir'nin gövdesinin başında assert(f.payda != 0); eklemek küçük bir iyileştirme olurdu. Bu, kodun belgelendirme
değerini artırır ve hangi öncül koşulun ihlal edildiği daha belirgin hale gelir. Ancak, davranışsal olarak, bu gerçekten bir şeyi
değiştirmez. Bu sorunları sorunun kaynağında (üye kötü bir değerle başlatıldığında veya atanmış olduğunda) yakalamak istiyoruz, 
değil mi? Sorunun aşağı akışında (kötü değer kullanıldığında).

Kesir örneğinin göreceli basitliği göz önüne alındığında, geçersiz Kesir nesneleri oluşturmanın basitçe kaçınılması çok zor
olmamalıdır. Ancak, birçok structı kullanan daha karmaşık bir kod tabanında, birçok üyesi olan structlar veya üyeleri karmaşık 
ilişkiler olan structlar, hangi değer kombinasyonunun bazı sınıf değişmezini ihlal edebileceğini anlamak o kadar açık olmayabilir.

Daha karmaşık bir sınıf değişmezi
---------------------------------
Kesir için sınıf değişmezi basit bir tanedir -- payda üyesi 0 olamaz. Bu, kavramsal olarak anlaması kolay ve kaçınması çok zor
değil. Sınıf değişmezleri, bir yapının üyelerinin ilişkili değerlere sahip olması gerektiğinde daha fazla bir meydan okuma haline
gelir.

                #include <string>

                struct Calisan
                {
                    std::string isim { };
                    char ilkHarf { }; // her zaman `isim`in ilk karakterini tutmalı (veya `0`)
                };

Yukarıdaki (kötü tasarlanmış) struct da, ilkHarf üyesinde saklanan karakter değeri, her zaman isim'in ilk karakteriyle 
eşleşmelidir.

Bir Calisan nesnesi başlatıldığında, kullanıcı sınıf değişmezinin korunmasını sağlamaktan sorumludur. Ve eğer isme yeni 
bir değer atanırsa, kullanıcı aynı zamanda FirstInitial'in güncellenmesini sağlamaktan da sorumludur.. Bu ilişki, bir Calisan 
nesnesini kullanan bir geliştirici için açık olmayabilir ve hatta eğer öyleyse, bunu yapmayı unutabilir.

Calisan nesneleri oluşturmak ve güncellemek için bize yardımcı olacak fonksiyonlar yazsak bile (ilkHarf'in her zaman isim'in ilk 
karakterinden ayarlandığından emin olmak), hala kullanıcının bu fonksiyonların farkında olmasına ve bunları kullanmasına
güveniyoruz.
Kısacası, bir nesnenin kullanıcısına sınıf değişmezlerini koruma görevini vermek, sorunlu kod oluşturma olasılığını artırır.

Anahtar içgörü

Bir nesnenin kullanıcısına sınıf değişmezlerini koruma görevini vermek, sorunlara yol açma olasılığını yükseltir.

İdeal olarak, sınıf türlerimizi kurşun geçirmez hale getirmeyi çok isterdik, böylece bir nesne ya geçersiz bir duruma getirilemez
ya da eğer öyleyse hemen sinyal verebilir (gelecekteki bazı rastgele bir noktada tanımsız davranışın meydana gelmesine izin vermek
yerine).

structlar (topluluk ( aggregrate ) olarak) bu sorunu zarif bir şekilde çözmek için gereken mekaniklere sahip değil.

Sınıflara giriş
---------------
C++'ı geliştirirken, Bjarne Stroustrup, geliştiricilerin daha sezgisel bir şekilde kullanılabilecek program tanımlı türler 
oluşturmasına olanak sağlayacak yetenekler sunmak istedi. Ayrıca, büyük, karmaşık programları (özellikle daha önce bahsedilen 
sınıf değişmezlik sorunu gibi) sık sık rahatsız eden ve bakım zorluklarına zarif çözümler bulmakla da ilgileniyordu.

Diğer programlama dilleriyle (özellikle de ilk nesne yönelimli programlama dili olan Simula ile) deneyiminden yola çıkan Bjarne,
neredeyse her şey için kullanılabilecek genel ve güçlü bir program tanımlı tür geliştirmenin mümkün olduğuna ikna oldu. Simula'ya ,
bir gönderme olarak, bu türü bir sınıf olarak adlandırdı. structlar gibi, bir sınıf da birçok üye değişkeni farklı türlerde
olabilen bir program tanımlı bileşik türdür.

Kilit nokta
Teknik açıdan bakıldığında, structlar ve sınıflar neredeyse aynıdır -- bu nedenle, bir struct kullanılarak uygulanan herhangi bir
örnek, bir sınıf kullanılarak veya tam tersi uygulanabilir. Ancak, pratik açıdan bakıldığında, structları ve sınıfları farklı
şekillerde kullanırız.

Teknik ve pratik farklılıkları 14.5 -- Public ve private üyeler ve erişim belirleyicileri dersinde ele alıyoruz.

Bir sınıfı tanımlama
--------------------
Bir sınıf, bir program tanımlı veri türü olduğu için, kullanılmadan önce tanımlanmalıdır. Sınıflar, struct yerine class anahtar
kelimesini kullanarak structlarla benzer şekilde tanımlanır. Örneğin, basit bir çalışan sınıfı için bir tanım aşağıdadır:

                class Calisan
                {
                    int m_id {};
                    int m_yas {};
                    double m_wage {};
                };


Sınıfların ve yapıların ne kadar benzer olabileceğini göstermek için aşağıdaki program dersin başında sunduğumuz programın 
eşdeğeridir, ancak Date artık bir struct yerine bir sınıftır:

                #include <iostream>

                class Date      // struct'ı class ile değiştirdik
                {
                public:          // ve bu satırı ekledik, buna erişim belirleyici denir ( ileride görecez 14.5 )
                    int m_day{}; // ve her bir üye adına "m_" öneklerini ekledik
                    int m_month{};
                    int m_year{};
                };

                void printDate(const Date& date)
                {
                    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
                }

                int main()
                {
                    Date date{ 4, 10, 21 };
                    printDate(date);

                    return 0;
                }

                Bu, şunu yazdırır:

                4/10/21

C++ standart kütüphanesinin çoğu sınıftır
-----------------------------------------
Zaten belki de bilmeden sınıf nesnelerini kullanıyordunuz. Hem std::string hem de std::string_view birer sınıf olarak
tanımlanmıştır. Aslında, standart kütüphanedeki takma adı olmayan türlerin çoğu sınıf olarak tanımlanmıştır!

Sınıflar gerçekten C++'ın kalbi ve ruhudur -- o kadar temeldirler ki, C++ başlangıçta "sınıflarla C" olarak adlandırıldı! 
Sınıflarla tanıştıktan sonra, C++'da geçirdiğiniz çok zamanı onları yazmak, test etmek ve kullanmak için harcayacaksınız.

14.3 — Üye Fonksiyonlar
-----------------------
Ders 13.5 -- structlara, üyelere ve üye seçimine girişte, üye değişkenler içerebilen bir program tanımlı tür olan structı tanıttık.
İşte bir tarihi tutmak için kullanılan bir struct örneği:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};
                };

Şimdi, eğer tarihi ekrana yazdırmak istiyorsak (muhtemelen çok sık yapmak istediğimiz bir şey), bunu yapmak için bir fonksiyon 
yazmanın mantıklı olduğunu görüyoruz. İşte tam bir program:

                #include <iostream>

                struct Date
                {
                    // işte üye değişkenlerimiz
                    int year {};
                    int month {};
                    int day {};
                };

                void print(const Date& date)
                {
                    // üye değişkenler üye seçim operatörü (.) kullanılarak erişilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // structı toplu başlatma

                    today.day = 16; // üye değişkenler üye seçim operatörü (.) kullanılarak erişilir
                    print(today);   // üye olmayan fonksiyon normal çağrı sözdizimi kullanılarak erişilir

                    return 0;
                }

                Bu program şunu yazdırır:

                2020/10/16
Özelliklerin ve eylemlerin ( properties and actions ) ayrılması
---------------------------------------------------------------
Etrafınıza bir bakın -- her yerde nesneler var: kitaplar ve binalar ve yiyecekler ve hatta siz. Gerçek hayattaki nesnelerin iki 
ana bileşeni vardır: 
1) Bir dizi gözlemlenebilir özellik (ör. ağırlık, renk, boyut, katılık, şekil vb.), ve
2) Bu özelliklere dayalı olarak gerçekleştirebilecekleri veya üzerlerinde gerçekleştirilebilecekleri bir dizi eylem
   (ör. açılma, başka bir şeye zarar verme vb.). Bu özellikler ve eylemler ayrılmaz.

Programlamada, özellikleri değişkenlerle, eylemleri ise fonksiyonlarla temsil ederiz.

Yukarıdaki Date örneğinde, özelliklerimizi (Date'in üye değişkenleri) ve bu özellikleri kullanarak gerçekleştirdiğimiz eylemleri
(print() fonksiyonu) ayrı ayrı tanımladığımızı not edin. Date ve print() arasındaki bağlantıyı, yalnızca print()'ın
const Date& parametresine dayanarak çıkarırız.

Her ikisini de bir ad alanına koyabilirdik (ikisinin birlikte paketlenmesi gerektiğini daha belirgin hale getirmek için), ancak bu,
programımıza daha fazla isim ekler ve daha fazla ad alanı öneki ekler, kodumuzu karmaşıklaştırır.
Özelliklerimizi ve eylemlerimizi tek bir paket olarak birlikte tanımlayabileceğimiz bir yol olması güzel olurdu.

Üye Fonksiyonlar
----------------
Üye değişkenlere ek olarak, sınıf türleri (structları, sınıfları ve unionları içerir) kendi fonksiyonlarına da sahip olabilir! 
Bir sınıf türüne ait olan fonksiyonlara üye fonksiyonlar denir.

Bir parantez açalım…
Diğer nesne yönelimli dillerde (Java ve C# gibi), bunlara yöntemler( methods ) denir. C++'da "yöntem" terimi kullanılmamasına
rağmen, ilk önce bu diğer dilleri öğrenen programcılar hala bu terimi kullanabilir.

Üye fonksiyon olmayan fonksiyonlara, onları üye fonksiyonlardan ayırt etmek için üye olmayan fonksiyonlar (veya ara sıra serbest
fonksiyonlar) denir. Yukarıdaki print() fonksiyonu bir üye olmayan fonksiyondur.
Yazarın notu
Bu derste, üye fonksiyonların örneklerini göstermek için structları kullanacağız -- ancak burada gösterdiğimiz her şey sınıflar
için de eşit derecede geçerlidir. Nedenlerini oraya vardığımızda açıkça göreceğiz, gelecek derslerde 
(14.5 -- Public ve private üyeler ve erişim belirleyicileri) sınıfların üye fonksiyonlarına örnekler göstereceğiz.

Üye fonksiyonlar, sınıf türü tanımının içinde bildirilmeli ve sınıf türü tanımının içinde veya dışında tanımlanabilir. 
Hatırlatma olarak, bir tanım aynı zamanda bir bildirimdir, bu yüzden bir üye fonksiyonunu sınıfın içinde tanımlarsak,
bu bir bildirim olarak sayılır.

Şimdilik işleri basit tutmak için, üye fonksiyonlarımızı sınıf türü tanımının içinde tanımlayacağız.

Üye Fonksiyon Örneği
--------------------
Dersin başındaki Date örneğini yeniden yazalım, print()'i bir üye olmayan fonksiyondan bir üye fonksiyonuna dönüştürelim:

                // Üye fonksiyon versiyonu
                #include <iostream>

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() // yazdir adında bir üye fonksiyon tanımlar
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // structı toplu başlatma

                    today.day = 16; // üye değişkenler üye seçim operatörü (.) kullanılarak erişilir
                    today.print();  // üye fonksiyonlar da üye seçim operatörü (.) kullanılarak erişilir

                    return 0;
                }

                Bu program derlenir ve yukarıdakiyle aynı sonucu verir:

                2020/10/16
Üye olmayan ve üye örnekler arasında üç anahtar fark vardır:

*- print() fonksiyonunu nerede bildiriyoruz (ve tanımlıyoruz)
*- print() fonksiyonunu nasıl çağırıyoruz
*- print() fonksiyonunun içinde üyelere nasıl erişiyoruz
Her birini sırayla inceleyelim.

Üye Fonksiyonlar Sınıf Türü Tanımının İçinde Bildirilir
-------------------------------------------------------
Üye olmayan örnekte, print() üye olmayan fonksiyonu, Date yapısının dışında, global ad alanında tanımlanır. Varsayılan olarak, 
dış bağlantısı vardır, bu yüzden diğer kaynak dosyalardan (uygun ileri bildirimle) çağrılabilir.

Üye örnekte, print() üye fonksiyonu, Date yapısı tanımının içinde bildirilir (ve bu durumda, tanımlanır). print()'in Date'in bir
parçası olarak bildirildiği için, bu derleyiciye print()'in bir üye fonksiyon olduğunu söyler.

Sınıf türü tanımının içinde tanımlanan üye fonksiyonlar, dolaylı olarak satır içidir, bu yüzden sınıf türü tanımı birden çok kod
dosyasına dahil edilirse, bir tanım kuralını ihlal etmezler.

Üye Fonksiyonları Çağırma (ve Dolaylı Nesne (implicit object))
--------------------------------------------------------------
Üye olmayan örnekte, print(today)'i çağırıyoruz, burada today (açıkça) bir argüman olarak geçirilir. üye örnekte, today.print()'i
çağırıyoruz. Bu sözdizimi, üye değişkenlere nasıl eriştiğimizle (ör. today.day = 16;) tutarlıdır.

Tüm (statik olmayan) üye fonksiyonlar, o sınıf türünün bir nesnesi kullanılarak çağrılmalıdır. Bu durumda, today, print()'in 
üzerinde çağrıldığı nesnedir. Üye fonksiyon durumunda, today'i bir argüman olarak geçirmemize gerek yok. Bir üye fonksiyonun 
üzerinde çağrıldığı nesne, üye fonksiyona dolaylı olarak geçirilir. Bu nedenle, bir üye fonksiyonun üzerinde çağrıldığı nesne
genellikle dolaylı nesne olarak adlandırılır.
Başka bir deyişle, today.print()'i çağırdığımızda, today dolaylı nesnedir ve print() üye fonksiyonuna dolaylı olarak geçirilir.

İşte print()'in üye olmayan versiyonu tekrar:

                // üye olmayan print versiyonu
                void print(const Date& date)
                {
                    // üye değişkenler üye seçim operatörü (.) kullanılarak erişilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }
Bu print() versiyonunun const Date& date referans parametresi vardır. Fonksiyonun içinde, üyelere bu referans parametresi
üzerinden erişiriz, yani date.year, date.month ve date.day. print(today) çağrıldığında, date referans parametresi today argümanına
bağlanır ve date.year, date.month ve date.day sırasıyla today.year, today.month ve today.day olarak değerlendirilir.
Şimdi print() üye fonksiyonunun tanımına tekrar bakalım:
Üye Fonksiyon Örneği

                void print() // yazdir adında bir üye fonksiyon tanımlar
                {
                    std::cout << yil << '/' << ay << '/' << gun;
                }
Üye örneğinde, üyelere yil, ay ve gun olarak erişiriz.

Bir üye fonksiyonun içinde, üye seçim operatörü (.) ile öneki olmayan her üye tanımlayıcı, dolaylı nesne ile ilişkilendirilir.
Başka bir deyişle, today.print() çağrıldığında, today dolaylı nesnemizdir ve yil, ay ve gun (önekli olmayanlar) sırasıyla
today.yil, today.ay ve today.gun değerlerine karşılık gelir.

Anahtar nokta şudur ki, Üye olmayan fonksiyonlarla, üzerinde çalışmak için bir nesneyi fonksiyona açıkça geçirmeliyiz ve üyelere
açıkça erişiriz. Üye fonksiyonlarla, üzerinde çalışmak için bir nesneyi dolaylı olarak fonksiyona geçiririz ve üyelere dolaylı 
olarak erişiriz.

Başka Bir Üye Fonksiyon Örneği
------------------------------
İşte biraz daha karmaşık bir üye fonksiyonla bir örnek:
                #include <iostream>
                #include <string>

                struct Person
                {
                    std::string name{};
                    int age{};

                    void kisses(const Person& person)
                    {
                        std::cout << name << " kisses " << person.name << '\n';
                    }
                };

                int main()
                {
                    Person joe{ "Joe", 29 };
                    Person kate{ "Kate", 27 };

                    joe.kisses(kate);

                    return 0;
                }
                Bu, çıktıyı üretir:

                Joe kisses Kate
Bunun nasıl çalıştığını inceleyelim. Öncelikle, iki Person structı tanımlıyoruz, joe ve kate. Sonra, joe.kisses(kate)'i 
çağırıyoruz. joe burada dolaylı nesnedir ve kate açık bir argüman olarak geçirilir.

kisses() üye fonksiyonu çalıştığında, isim tanımlayıcısı üye seçim operatörünü (.) kullanmaz, bu yüzden dolaylı nesneye, yani
joe'ya başvurur. Bu, joe.isim'e çözülür. person.name, üye seçim operatörünü kullanır, bu yüzden dolaylı nesneye başvurmaz. person,,
kate için bir referans olduğundan, bu kate.name'e çözülür.

Anahtar nokta şudur ki, Bir üye fonksiyon olmadan, kisses(joe, kate)'i yazmış olurduk. Bir üye fonksiyonla, joe.kisses(kate)'i 
yazıyoruz. İkincisinin ne kadar daha iyi okunduğuna ve hangi nesnenin eylemi başlattığının ve hangisinin destek olduğunun ne kadar
açık olduğuna dikkat edin.

Üye Değişkenler ve Fonksiyonlar Herhangi Bir Sırayla Tanımlanabilir
-------------------------------------------------------------------
C++ derleyicisi normalde kodu yukarıdan aşağıya derler. Her isimle karşılaştığında, derleyici zaten o isim için bir bildirim
görmüş olup olmadığını belirler, böylece uygun tip kontrolünü yapabilir.

Bu, bir üye olmayan fonksiyonun içinde, en azından bildirilmemiş bir değişkene erişemez veya bir fonksiyonu çağıramazsınız
anlamına gelir:
                void x()
                {
                    y(); // hata: y henüz bildirilmedi, bu yüzden derleyici ne olduğunu bilmiyor
                }

                int y()
                {
                    return 5;
                }
Ancak, üye fonksiyonlar (ve üye veri başlatıcıları) ile, bu sınırlama geçerli değildir ve üyelerimizi istediğimiz herhangi bir
sırayla tanımlayabiliriz. Örneğin:

                struct Foo
                {
                    int m_x{ y() };   // burada y()'yi çağırmak tamam, çünkü y() daha sonra tanımlanır

                    void x() { y(); } // burada y()'yi çağırmak tamam, çünkü y() daha sonra tanımlanır
                    int y()  { return 5; }
                };

Üye Fonksiyonlar Aşırı Yüklenebilir
------------------------------------
Üye olmayan fonksiyonlar gibi, üye fonksiyonlar da aşırı yüklenebilir, yeter ki her üye fonksiyon ayırt edilebilsin.
İşte aşırı yüklenmiş print() üye fonksiyonlarına sahip bir Date yapısı örneği:

                #include <iostream>
                #include <string_view>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print()
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }

                    void print(std::string_view prefix)
                    {
                        std::cout << prefix << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 };

                    today.print(); // Tarih::print() çağırır
                    std::cout << '\n';

                    today.print("Date: "); // Tarih::print(std::string_view) çağırır
                    std::cout << '\n';

                    return 0;
                }
                Bu, şunu yazdırır:

                2020/10/14
                Tarih: 2020/10/14
Structlar ve Üye Fonksiyonlar
-----------------------------
C'de, structların yalnızca veri üyeleri vardır, üye fonksiyonları yoktur. C++'da, sınıflar tasarlanırken, Bjarne Stroustrup,
structların (C'den miras alınan) üye fonksiyonlara sahip olma yeteneğine sahip olup olmaması gerektiğini düşünmek için bir miktar
zaman harcadı. Düşündükten sonra, bunun gerektiğine karar verdi.

Bu karar, structların hangi yeni C++ yeteneklerine erişim hakkı olması gerektiği hakkında başka soruların ortaya çıkmasına neden
oldu. Bjarne, structların sınırlı bir yetenek alt kümesine erişim hakkı vermenin, dilin karmaşıklığını ve kenar durumlarını
artıracağından endişe ediyordu. Basitlik için, sonuçta Bjarne, structların ve sınıfların birleşik bir kural setine sahip olmasına 
karar verdi (yani structlar, sınıfların yapabildiği her şeyi yapabilir ve tam tersi), ve gelenek, structların nasıl
kullanılacağını belirleyebilir.

Modern C++'da, structların üye fonksiyonlara sahip olması uygundur. Bu, bizim gelecek ders 14.9 -- Yapıcılarına ( constructor )
Giriş'te ele alacağımız private bir üye fonksiyon türü olan yapıcıları dışlar. Bir yapıcıya sahip bir sınıf türü artık bir topluluk
değildir ve structlarımızın topluluk olarak kalmasını istiyoruz.

*** BEST -> Üye fonksiyonlar, hem structlarla hem de sınıflarla kullanılabilir. Ancak, structlar, yapıcı üye fonksiyonlarını 
            tanımlamaktan kaçınmalıdır, çünkü bunu yapmak onları bir topluluk olmaktan çıkarır.

Veri Üyesi Olmayan Sınıf Türleri
--------------------------------
Veri üyesi olmayan bir sınıf türü oluşturmak mümkündür (ör. yalnızca üye fonksiyonlara sahip sınıf türleri). Ayrıca, böyle bir 
sınıf türünün nesnelerini örnekleştirmek de mümkündür:
#include <iostream>

                struct Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo f{};
                    f.printHi(); // çağırmak için nesne gerektirir

                    return 0;
                }
Ancak, bir sınıf türünün hiç veri üyesi yoksa, bir sınıf türünü kullanmak muhtemelen gereksizdir. Bu tür durumlarda, bunun yerine
bir ad alanı kullanmayı düşünün (üye olmayan fonksiyonları içerir). Bu, okuyucuya hiçbir verinin yönetilmediğini (ve fonksiyonları
çağırmak için bir nesnenin örnekleştirilmesini gerektirmediğini) daha açık hale getirir.

                #include <iostream>

                namespace Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo::printHi(); // Hiç bir nesne gerekli değil

                    return 0;
                }
*** BEST -> Sınıf türünüzün hiç veri üyesi yoksa, bir ad alanı kullanmayı tercih edin.

14.4 — Const Sınıf Nesneleri ve Const Üye Fonksiyonlar
------------------------------------------------------
5.1 -- Sabit değişkenler (isimli sabitler) dersinde, temel bir veri türünün (int, double, char, vb.) nesnelerinin const anahtar
kelimesi ile sabit yapılabilceğini öğrendiniz. Tüm const değişkenler oluşturuldukları anda başlatılmalıdır.

                const int x;      // derleme hatası: başlatılmadı
                const int y{};    // tamam: değer başlatıldı
                const int z{ 5 }; // tamam: liste başlatıldı

Benzer şekilde, sınıf türü nesneleri (structlar, sınıflar ve unionlar) de const anahtar kelimesi kullanılarak sabit yapılabilir.
Bu tür nesneler de oluşturuldukları anda başlatılmalıdır.

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const sınıf türü nesne

                    return 0;
                }

Normal değişkenlerle olduğu gibi, sınıf türü nesnelerinizi de genellikle oluşturulduktan sonra değiştirilmediklerini garanti etmek
istediğinizde const (veya constexpr) yapmak istersiniz.

Sabit nesnelerin veri üyelerini değiştirmek yasaktır
----------------------------------------------------
Bir const sınıf türü nesnesi başlatıldıktan sonra, nesnenin veri üyelerini değiştirmeye yönelik herhangi bir girişim yasaktır,
çünkü bu, nesnenin const-özelliğini ihlal eder. Bu, hem üye değişkenleri doğrudan değiştirmeyi (eğer onlar public ise), hem de üye
değişkenlerin değerini ayarlayan üye fonksiyonları çağırmayı içerir.

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void incrementDay()
                    {
                        ++day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.day += 1;        // derleme hatası: const nesnenin üyesini değiştiremez
                    today.incrementDay();  // derleme hatası: const nesnenin üyesini değiştiren üye fonksiyonu çağıramaz

                    return 0;
                }

Sabit nesneler, sabit olmayan üye fonksiyonları çağıramaz
---------------------------------------------------------
Bu kodun da bir derleme hatası oluşturduğunu görmek sizi şaşırtabilir:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print()
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.print();  // derleme hatası: sabit olmayan üye fonksiyonu çağıramaz

                    return 0;
                }

print() bir üye değişkeni değiştirmeye çalışmasa bile, today.print() çağrımız hala bir const ihlalidir. Bu, print() üye
fonksiyonunun kendisinin const olarak bildirilmediği için olur. Derleyici, const bir nesne üzerinde sabit olmayan bir üye
fonksiyonu çağırmamıza izin vermez.

Sabit Üye Fonksiyonlar
----------------------
Yukarıdaki sorunu çözmek için, print()'i bir const üye fonksiyon yapmamız gerekiyor. Bir const üye fonksiyon, nesneyi 
değiştirmeyeceğini veya herhangi bir sabit olmayan üye fonksiyonları çağırmayacağını (çünkü onlar nesneyi değiştirebilir) garanti
eden bir üye fonksiyondur.
print()'i bir const üye fonksiyon yapmak kolaydır - sadece const anahtar kelimesini, parametre listesinden sonra, ancak fonksiyon 
gövdesinden önce fonksiyon prototipine ekleriz:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // şimdi bir const üye fonksiyon
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.print();  // tamam: const nesne const üye fonksiyonu çağırabilir

                    return 0;
                }

Yukarıdaki örnekte, print() bir const üye fonksiyon haline getirildi, bu da onu const nesnelerde (örneğin today gibi) 
çağırabileceğimiz anlamına gelir.
Bir üye fonksiyonun const olarak işaretlenmesi, bu fonksiyonun nesneyi değiştirmeyeceğini veya herhangi bir const olmayan üye
fonksiyonları çağırmayacağını (çünkü onlar nesneyi değiştirebilir) garanti eder. Örneğin:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void incrementDay() const // const olarak işaretlendi
                    {
                        ++day; // derleme hatası: const fonksiyon üyeyi değiştiremez
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.incrementDay();

                    return 0;
                }

Bu örnekte, incrementDay() const bir üye fonksiyon olarak işaretlenmiştir, ancak day'i değiştirmeye çalışır. Bu bir derleme hatası
oluşturacaktır.

Sabit Üye Fonksiyonlar Sabit Olmayan Nesneler Üzerinde Çağrılabilir
-------------------------------------------------------------------
Sabit üye fonksiyonlar, sabit olmayan nesneler üzerinde de çağrılabilir:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const

                    today.print();  // tamam: sabit olmayan nesne üzerinde const üye fonksiyonu çağırabilir

                    return 0;
                }
Çünkü const üye fonksiyonlar hem const hem de non-const nesneler üzerinde çağrılabilir, bir üye fonksiyonun nesnenin durumunu
değiştirmemesi durumunda, bu fonksiyonun const yapılması gerekir.
*** BEST -> Bir üye fonksiyonun nesnenin durumunu değiştirmemesi (ve hiçbir zaman değiştirmeyeceği) durumunda, bu fonksiyonun
const yapılması gerekir, böylece hem const hem de non-const nesneler üzerinde çağrılabilir.

Hangi üye fonksiyonlara const uygulayacağınıza dikkat edin. Bir üye fonksiyon bir kez const olarak yapıldığında, bu fonksiyon 
const nesneler üzerinde çağrılabilir. Bir üye fonksiyonun const'unun daha sonra kaldırılması, const bir nesne üzerinde bu üye 
fonksiyonu çağıran herhangi bir kodu bozacaktır.

Const Referans Yoluyla Const Nesneler
-------------------------------------
Const yerel değişkenlerin örnekleştirilmesi, const nesneler oluşturmanın bir yoludur, ancak daha yaygın bir yol, bir nesneyi const
referans yoluyla bir fonksiyona geçirmektir. 12.5 -- Lvalue referansı ile geçiş dersinde, sınıf türü argümanlarını değer yerine 
const referans olarak geçirmenin avantajlarını ele aldık. Tekrarlamak gerekirse, bir sınıf türü argümanını değer olarak geçirmek,
sınıfın bir kopyasının yapılmasına neden olur (bu yavaştır) - çoğu zaman, bir kopyaya ihtiyacımız yoktur, orijinal argümana bir 
referans işimizi görür ve bir kopya yapmayı önler. Fonksiyonun const lvalue argümanları ve rvalue argümanları (ör. literaller ve 
geçici nesneler) kabul etmesine izin vermek için referansı genellikle const yaparız.

Aşağıdaki kodda neyin yanlış olduğunu anlayabilir misiniz?

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() // non-const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                void doSomething(const Date &date)
                {
                    date.print();
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const
                    today.print();

                    doSomething(today);

                    return 0;
                }
                
Cevap, doSomething() fonksiyonunun içinde, date const bir nesne olarak ele alınır (çünkü const referans ile geçirilmiştir).
Ve bu const date ile, const olmayan üye fonksiyonu yazdir()'i çağırıyoruz. Const nesneler üzerinde const olmayan üye fonksiyonları
çağıramayacağımız için, bu bir derleme hatası oluşturacaktır.

Düzeltme basittir: print()'i const yapın:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // now const
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                void doSomething(const Date &date)
                {
                    date.print();
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // non-const
                    today.print();

                    doSomething(today);

                    return 0;
                }
Şimdi doSomething() fonksiyonunda, const date başarıyla const üye fonksiyonu print()'i çağırabilecektir.

Üye Fonksiyonun Const ve Non-Const Aşırı Yüklemesi
--------------------------------------------------
Son olarak, çok sık yapılmamasına rağmen, bir üye fonksiyonun const ve non-const versiyonunu aşırı yüklemek mümkündür. Bu, const
nitelikleyicinin fonksiyonun imzasının bir parçası olarak kabul edildiği için çalışır, bu yüzden yalnızca const'ları farklı olan
iki fonksiyon farklı kabul edilir.

                #include <iostream>

                struct Something
                {
                    void print()
                    {
                        std::cout << "non-const\n";
                    }

                    void print() const
                    {
                        std::cout << "const\n";
                    }
                };

                int main()
                {
                    Something s1{};
                    s1.print(); // calls print()

                    const Something s2{};
                    s2.print(); // calls print() const

                    return 0;
                }
                Bu, şunu yazdırır:

                non-const
                const
Bir fonksiyonun const ve non-const versiyonu ile aşırı yükleme genellikle dönüş değerinin const'lıkta farklı olması gerektiğinde
yapılır. Bu oldukça nadirdir.

14.5 — Public ve Private Üyeler ve Erişim Belirleyiciler
--------------------------------------------------------
Bir sonbahar gününde caddede yürüyorsunuz ve bir burrito yiyorsunuz. Oturacak bir yer arıyorsunuz, etrafınıza bakıyorsunuz.
Solunuzda çimleri biçilmiş, gölgelik ağaçları olan, birkaç rahatsız edici bankı ve yakındaki oyun alanında bağıran çocukları olan
bir park var. Sağınızda bir yabancının evi var. Pencereden, rahat bir koltuk ve çıtırdayan bir şömine görüyorsunuz.

Ağır bir iç çekerek, parkı seçiyorsunuz.

Seçiminizin ana belirleyicisi, parkın bir public alan olması, evin ise private olmasıdır. Siz (ve herkes) public alanlara serbestçe
erişebilirsiniz. Ancak evin üyeleri (veya açıkça izin verilen kişiler) private konuta erişebilir.

Üye Erişimi
-----------
Benzer bir kavram, bir sınıf türünün üyelerine de uygulanır. Bir sınıf türünün her üyesinin, kimin o üyeye erişebileceğini
belirleyen bir erişim düzeyi adı verilen bir özelliği vardır.

C++'da üç farklı erişim düzeyi vardır: public, private ve protected. Bu derste, en yaygın kullanılan iki erişim düzeyini ele 
alacağız: public ve private.
Bir üyeye erişildiğinde, derleyici üyenin erişim düzeyinin o üyeye erişime izin verip vermediğini kontrol eder. Erişime izin 
verilmezse, derleyici bir derleme hatası oluşturur. Bu erişim düzeyi sistemine bazen gayri resmi olarak erişim kontrolleri denir.
Bir yapının üyeleri varsayılan olarak public'tir
------------------------------------------------
Public erişim düzeyine sahip üyelere public üyeler denir. Public üyeler, nasıl erişileceği konusunda herhangi bir kısıtlama 
olmayan bir sınıf türünün üyeleridir. Açılış analojimizdeki park gibi, public üyelere herkes (kapsam dahilinde oldukları sürece)
erişebilir.

Public üyelere, aynı sınıfın diğer üyeleri tarafından erişilebilir. Özellikle, public üyelere public tarafından da erişilebilir,
bu da belirli bir sınıf türünün üyelerinin dışında bulunan kodu ifade ederiz. Public örnekleri arasında üye olmayan fonksiyonlar 
ve diğer sınıf türlerinin üyeleri bulunur.

Anahtar nokta şudur ki, Bir Struct'ın üyeleri varsayılan olarak public'tir. Public üyelere, sınıf türünün diğer üyeleri ve public 
tarafından erişilebilir.

"Public" terimi, belirli bir sınıf türünün üyelerinin dışında bulunan kodu ifade etmek için kullanılır. Bu, üye olmayan 
fonksiyonları ve diğer sınıf türlerinin üyelerini içerir. Varsayılan olarak, bir struct'ın tüm üyeleri public üyelerdir.
Aşağıdaki struct'ı düşünün:

                #include <iostream>

                struct Date
                {
                    // struct üyeleri varsayılan olarak public'tir, herkes tarafından erişilebilir
                    int year {};       // varsayılan olarak public
                    int month {};      // varsayılan olarak public
                    int day {};        // varsayılan olarak public

                    void print() const // varsayılan olarak public
                    {
                        // public üyelere sınıf tipinin üye fonksiyonlarında erişilebilir
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                // üye olmayan fonksiyon main "public" kısmının bir parçasıdır
                int main()
                {
                    Date today { 2020, 10, 14 }; // struct'ımızı topluca başlatıyoruz

                    // public üyelere public tarafından erişilebilir
                    today.day = 16; // tamam: day üyesi public
                    today.print();  // tamam: print() üye fonksiyonu public

                    return 0;
                }
Bu örnekte, üyelere üç yerde erişilir:

*- Üye fonksiyonu print() içinde, implicit nesnenin year, month ve day üyelerine erişiriz.
*- main() içinde, today.day'a doğrudan erişiriz ve değerini ayarlarız.
*- main() içinde, today.print() üye fonksiyonunu çağırırız.
Bu üç erişime de izin verilir çünkü public üyelere her yerden erişilebilir. main() Date'in bir üyesi olmadığı için, public'in bir
parçası olarak kabul edilir. Ancak, public'in public üyelere erişim hakkı olduğu için, main() Date'in üyelerine (today.print() 
çağrısını içerir) doğrudan erişebilir.

Bir sınıfın üyeleri varsayılan olarak private'dir
-------------------------------------------------
Private erişim seviyesine sahip üyelere private üyeler denir. Private üyeler, yalnızca aynı sınıfın diğer üyeleri tarafından 
erişilebilen bir sınıf tipinin üyeleridir.
Aşağıdaki örneği düşünün, bu örnek yukarıdaki örnekle neredeyse aynıdır:

                #include <iostream>

                class Date // artık bir struct yerine bir sınıf
                {
                    // sınıf üyeleri varsayılan olarak private'dir, yalnızca diğer üyeler tarafından erişilebilir
                    int m_year {};     // varsayılan olarak private
                    int m_month {};    // varsayılan olarak private
                    int m_day {};      // varsayılan olarak private

                    void print() const // varsayılan olarak private
                    {
                        // private üyelere üye fonksiyonlarda erişilebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // derleme hatası: artık toplu başlatma kullanılamaz

                    // private üyelere public tarafından erişilemez
                    today.m_day = 16; // derleme hatası: m_day üyesi private
                    today.print();    // derleme hatası: print() üye fonksiyonu private

                    return 0;
                }
Bu örnekte, üyelere aynı üç yerde erişilir:
*- Üye fonksiyonu print() içinde, implicit nesnenin m_year, m_month ve m_day üyelerine erişiriz.
*- main() içinde, today.m_day'a doğrudan erişiriz ve değerini ayarlarız.
*- main() içinde, today.print() üye fonksiyonunu çağırırız.
Ancak, bu programı derlerseniz, üç derleme hatası oluştuğunu göreceksiniz.

main() içinde, today.m_day = 16 ve today.print() ifadeleri artık derleme hataları oluşturur. Bu, main()'in public'in bir parçası 
olması ve public'in private üyelere doğrudan erişimine izin verilmemesi nedeniyledir.

print() içinde, m_year, m_month ve m_day üyelerine erişime izin verilir. Bu, print()'in sınıfın bir üyesi olması ve sınıfın
üyelerinin private üyelere erişimine izin verilmesi nedeniyledir.

Peki üçüncü derleme hatası nereden geliyor? Belki de şaşırtıcı bir şekilde, today'ın başlatılması artık bir derleme hatası 
oluşturuyor. Ders 13.6 -- Struct aggregate initialization'da, bir topluluğun "private veya protected olmayan statik olmayan veri 
üyeleri olmaması gerektiğini" belirttik. Date sınıfımızın private veri üyeleri var (çünkü sınıfların üyeleri varsayılan olarak 
private), bu yüzden Date sınıfımız bir topluluk olarak nitelendirilmiyor. Bu yüzden, artık onu başlatmak için toplu başlatma
kullanamayız.

Sınıfları (genellikle topluluk olmayanları) nasıl düzgün bir şekilde başlatacağımızı, yaklaşan ders 14.9 -- Constructorlara
Giriş'te tartışacağız.

*** Ana Fikir
Bir sınıfın üyeleri varsayılan olarak private'dir. Private üyelere sınıfın diğer üyeleri tarafından erişilebilir, ancak public
tarafından erişilemez. Private üyelere sahip bir sınıf artık bir topluluk değildir ve bu nedenle toplu başlatma kullanamaz.

Private Üye Değişkenlerinizi Adlandırma
---------------------------------------
C++'da, private veri üyelerini "m_" önekiyle başlayacak şekilde adlandırma yaygın bir uygulamadır. Bu, birkaç önemli nedenle
yapılır. Bir sınıfın aşağıdaki üye fonksiyonunu düşünün:

                // Private üye m_name'i name parametresinin değerine ayarlayan bir üye fonksiyon
                void setName(std::string_view name)
                {
                    m_name = name;
                }
Öncelikle, "m_" öneki, bir üye fonksiyonu içindeki veri üyelerini fonksiyon parametrelerinden veya yerel değişkenlerden kolayca
ayırt etmemizi sağlar. "m_name" in bir üye olduğunu ve "name" in olmadığını kolayca görebiliriz. Bu, bu fonksiyonun sınıfın
durumunu değiştirdiğini açıkça belirtir. Ve bu önemlidir çünkü bir veri üyesinin değerini değiştirdiğimizde, bu değişiklik üye 
fonksiyonun kapsamının ötesinde kalır (fonksiyon parametrelerine veya yerel değişkenlere yapılan değişiklikler genellikle bu
şekilde olmaz).

Bu, yerel statik değişkenler için "s_" öneklerini ve global değişkenler için "g_" öneklerini kullanmayı önermemizin aynı nedenidir.
İkincisi, "m_" öneki, private üye değişkenler ile yerel değişkenlerin, fonksiyon parametrelerinin ve üye fonksiyonlarının adları
arasında ad çakışmalarını önlemeye yardımcı olur.

Eğer private üyemizi m_name yerine name olarak adlandırmış olsaydık:
Name fonksiyon parametremiz, name private veri üyesini gölgede bırakırdı.
Eğer name adında bir üye fonksiyonumuz olsaydı, name tanımlayıcısının yeniden tanımlanması nedeniyle bir derleme hatası alırdık.
*** BEST -> Private üyelerinizi, onları yerel değişkenlerin, fonksiyon parametrelerinin ve üye fonksiyonların adlarından ayırt 
etmeye yardımcı olmak için "m_" önekiyle başlayacak şekilde adlandırmayı düşünün.

Erişim Seviyelerini Erişim Belirleyicileri ile Ayarlama
-------------------------------------------------------
Varsayılan olarak, struct'ların (ve unionların) üyeleri public'tir ve sınıfların üyeleri private'dir.
Ancak, üyelerimizin erişim seviyesini bir erişim belirleyicisi kullanarak açıkça ayarlayabiliriz. Bir erişim belirleyicisi,
belirleyiciyi takip eden tüm üyelerin erişim seviyesini ayarlar. C++ üç erişim belirleyicisi sağlar: public:, private: ve protected

Aşağıdaki örnekte, print() üye fonksiyonunun public tarafından kullanılabilmesini sağlamak için public: erişim belirleyicisini ve
veri üyelerimizi private yapmak için private: erişim belirleyicisini kullanıyoruz.

                class Date
                {
                // Burada tanımlanan herhangi bir üye varsayılan olarak private olurdu

                public: // işte bizim public erişim belirleyicimiz

                    void print() const // yukarıdaki public: belirleyici nedeniyle public
                    {
                        // üyeler diğer private üyelere erişebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }

                private: // işte bizim private erişim belirleyicimiz

                    int m_year { 2020 };  // yukarıdaki private: belirleyici nedeniyle private
                    int m_month { 14 }; // yukarıdaki private: belirleyici nedeniyle private
                    int m_day { 10 };   // yukarıdaki private: belirleyici nedeniyle private
                };

                int main()
                {
                    Date d{};
                    d.print();  // tamam, main() public üyelere erişebilir

                    return 0;
                }
Bu örnek derlenir. Print() public: erişim belirleyicisi nedeniyle bir public üye olduğu için, main() (public'in bir parçası olan)
ona erişebilir. Private üyelere sahip olduğumuz için, d'yi topluca başlatamayız. Bu örnekte, bunun yerine varsayılan üye 
başlatmasını kullanıyoruz (geçici bir çözüm olarak).

Sınıflar private erişime varsayılan olarak sahip olduğu için, öncü private: erişim belirleyicisini atlayabilirsiniz:

                Class Foo
                {
                // sınıflar varsayılan olarak private üyelere sahip olduğu için burada private erişim belirleyicisine gerek yok
                    int m_something {};  // varsayılan olarak private
                };
Ancak, sınıflar ve struct'lar farklı erişim seviyesi varsayılanlarına sahip olduğu için, birçok geliştirici açık olmayı tercih 
eder:

                class Foo
                {
                private: // gereksiz, ancak ardından gelenlerin private olduğunu açıkça belirtir
                    int m_something {};  // varsayılan olarak private
                };
Bu, yani explicit private: teknik olarak gereksiz olsa da,  belirleyicinin kullanılması, ardından gelen üyelerin private olduğunu 
açıkça belirtir, BÖylece Foo'nun bir sınıf mı yoksa bir struct mı olarak tanımlandığına dayanarak varsayılan erişim seviyesini çıkarmadan anlamış oluruz.

Erişim Seviyesi Özeti
---------------------
İşte farklı erişim seviyelerinin hızlı bir özeti:

Bir sınıf tipi, herhangi bir sırayla herhangi bir sayıda erişim belirleyicisini kullanabilir ve bunlar tekrar tekrar 
kullanılabilir (örneğin, bazı public üyeleriniz, ardından bazı private olanlar, ardından daha fazla public olanlar olabilir).

Çoğu sınıf, çeşitli üyeler için hem private hem de public erişim belirleyicilerini kullanır. Bu konuda bir örneği bir sonraki 
bölümde göreceğiz.
| Erişim Düzeyi | Erişim Belirleyici | Üye Erişimi | Türetilmiş Sınıf Erişimi  |
|---------------|---------------------|-------------|--------------------------|
| Public        | `public:`           | evet        | evet                     |
| Protected     | `protected:`        | evet        | evet                     |
| Private       | `private:`          | evet        | hayır                    |

Struct'lar ve Sınıflar için Erişim Seviyesi En İyi Uygulamaları
---------------------------------------------------------------
Artık erişim seviyelerinin ne olduğunu anladığımıza göre, nasıl kullanacağımızı konuşalım.
Struct'lar tamamen erişim belirleyicilerinden kaçınmalıdır, yani tüm struct üyeleri varsayılan olarak public olacaktır.
Struct'larımızın topluluklar olmasını istiyoruz ve topluluklar yalnızca public üyelere sahip olabilir. Public: erişim
belirleyicisinin kullanılması varsayılanla gereksiz olurdu ve private: veya protected: kullanmak struct'ı bir topluluk olmaktan 
çıkarırdı.

Sınıflar genellikle yalnızca private (veya protected) veri üyelerine sahip olmalıdır (varsayılan private erişim seviyesini
kullanarak veya private: (veya protected) erişim belirleyicisini kullanarak). Bunun gerekçesini bir sonraki ders olan
14.6 -- Erişim Fonksiyonları'nda tartışacağız.

Sınıflar normalde public üye fonksiyonlarına sahip olur (bu nedenle bu üye fonksiyonlar, nesne oluşturulduktan sonra public 
tarafından kullanılabilir). Ancak, nadiren üye fonksiyonlar private (veya protected) yapılır eğer public tarafından kullanılmaları
amaçlanmamışsa.

*** BEST -> Sınıflar genellikle üye değişkenlerini private (veya protected) yapmalı ve üye fonksiyonlarını public yapmalıdır.
Struct'lar genellikle erişim belirleyicilerini kullanmaktan kaçınmalıdır (tüm üyeler varsayılan olarak public olacaktır).

Erişim Seviyeleri Sınıf Bazında Çalışır
---------------------------------------
C++ erişim seviyelerinin sıklıkla kaçırılan veya yanlış anlaşılan bir inceliği, üyelere erişimin sınıf bazında tanımlandığı,
nesne bazında tanımlanmadığıdır.

Bir üye fonksiyonun doğrudan private üyelere erişebileceğini zaten biliyorsunuz. Ancak, erişim seviyeleri sınıf bazında olduğu 
için, bir üye fonksiyonu aynı sınıf tipinden olan ve kapsamda olan herhangi bir diğer nesnenin private üyelerine de doğrudan
erişebilir.Bunu bir örnekle gösterelim:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Person
                {
                private:
                    std::string m_name{};

                public:
                    void kisses(const Person& p) const
                    {
                        std::cout << m_name << " kisses " << p.m_name << '\n';
                    }

                    void setName(std::string_view name)
                    {
                        m_name = name;
                    }
                };

                int main()
                {
                    Person joe;
                    joe.setName("Joe");

                    Person kate;
                    kate.setName("Kate");

                    joe.kisses(kate);

                    return 0;
                }
                Bu, şunu yazdırır:

                Joe kisses Kate
Burada dikkat edilmesi gereken birkaç şey var.

Öncelikle, m_name private yapıldı, bu yüzden yalnızca Person sınıfının üyeleri tarafından erişilebilir (public tarafından değil).
İkincisi, sınıfımızın private üyeleri olduğu için, bir topluluk değildir ve Person nesnelerimizi başlatmak için toplu başlatma
kullanamayız. Bu soruna uygun bir çözüm bulana kadar, Person nesnelerimize bir isim atamamıza izin veren setName() adında bir
public üye fonksiyon oluşturduk.

Üçüncüsü, kisses() bir üye fonksiyon olduğu için, private üye m_name'e doğrudan erişim hakkına sahiptir. Ancak, p.m_name'e de
doğrudan erişim hakkına sahip olduğunu görmek sizi şaşırtabilir! Bu, p'nin bir Person nesnesi olduğu ve kisses()'in kapsamda olan
herhangi bir Person nesnesinin private üyelerine erişebileceği için çalışır!
Bu konuyu operatör aşırı yükleme bölümünde daha fazla örneklerle göreceğiz.

Teknik ve pratik açıdan struct'lar ve sınıflar arasındaki fark
--------------------------------------------------------------
Artık erişim seviyelerini ele aldığımıza göre, struct'lar ve sınıflar arasındaki teknik farkları nihayet tartışabiliriz.
Hazır mısınız?
Bir sınıf üyelerini varsayılan olarak private yapar, oysa bir struct üyelerini varsayılan olarak public yapar.
Evet, bu kadar. :))

Yazarın Notu

Titiz olmak gerekirse, bir tane daha küçük bir fark var -- struct'lar diğer sınıf türlerinden public olarak miras alır ve sınıflar
private olarak miras alır. Bu konunun ne anlama geldiğini, miras bölümünde ele alacağız, ancak bu belirli nokta pratik olarak 
önemsizdir çünkü zaten miras için varsayılanlara güvenmemelisiniz.
Pratikte, struct'ları ve sınıfları farklı şekillerde kullanırız.

Bir kural olarak, aşağıdakilerin tümü doğru olduğunda bir struct kullanmak mantıklıdır:

*- Kısıtlı erişimden fayda sağlamayan basit bir veri koleksiyonunuz var.
*- Toplu başlatma yeterlidir.
*- Sınıf değişmezleriniz, kurulum ihtiyaçlarınız veya temizleme ihtiyaçlarınız yok.
*- Struct'ların kullanılabileceği birkaç örnek: constexpr global program verileri, bir nokta struct'ı
   (private yapılmalarından fayda sağlamayan basit bir int üye koleksiyonu), bir fonksiyondan bir veri seti döndürmek için
   kullanılan struct'lar.

Aksi takdirde bir sınıf kullanın.

Struct'larımızın topluluklar olmasını istiyoruz. Yani, struct'ınızı bir topluluk olmaktan çıkaracak herhangi bir özellik
kullanıyorsanız, muhtemelen bir sınıf kullanmalısınız (ve sınıflar için tüm en iyi uygulamaları takip etmelisiniz).
*/
