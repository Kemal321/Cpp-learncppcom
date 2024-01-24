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

    // Struct member fonksiyon örneði
    Date date{ 28,04,1999 };
    date.print();
    
    return 0;
}
/*
14.1 — Nesne yönelimli programlamaya giriþ

Yordamsal programlama (Procedural programming)
----------------------------------------------
Ders 1.3 -- Nesneler ve deðiþkenlere giriþte, C++'daki bir nesneyi “deðer saklamak için kullanýlabilecek bir bellek parçasý” 
olarak tanýmladýk. Bir ismi olan nesneye deðiþken denir. C++ programlarýmýz, bilgisayara veri tanýmlayan (nesneler aracýlýðýyla) 
ve bu veriler üzerinde iþlemler gerçekleþtiren (ifadeler ve deyimler içeren fonksiyonlar aracýlýðýyla) talimatlarýn ardýþýk 
listelerinden oluþmuþtur.

Þimdiye kadar, yordamsal programlama adý verilen bir programlama türünü gerçekleþtirdik. Yordamsal programlamada, program
mantýðýmýzý uygulayan "yordamlar" oluþturmak üzerinde durulur (C++'da bunlara fonksiyon denir). Bu fonksiyonlara veri nesnelerini 
geçeriz, bu fonksiyonlar veriler üzerinde iþlemler gerçekleþtirir ve ardýndan potansiyel olarak çaðýran tarafýndan kullanýlacak
bir sonuç döndürür.

Yordamsal programlamada, fonksiyonlar ve bu fonksiyonlarýn üzerinde iþlem yaptýðý veriler ayrý varlýklardýr. Programcý, 
fonksiyonlarý ve verileri bir araya getirerek istenen sonucu üretmekten sorumludur. Bu, þu þekilde bir koda yol açar:

                eat(you, apple);

Þimdi etrafýnýza bir bakýn -- her yerde nesneler var: kitaplar, binalar, yiyecekler ve hatta siz. Bu nesnelerin iki ana 
bileþeni vardýr: 
1) Bir dizi iliþkili özellik (ör. aðýrlýk, renk, boyut, katýlýk, þekil, vb...), ve
2) Sergileyebilecekleri bir dizi davranýþ (ör. açýlma, baþka bir þeyi ýsýtma, vb...). Bu özellikler ve davranýþlar ayrýlmaz.

Programlamada, özellikler nesneler tarafýndan, davranýþlar ise fonksiyonlar tarafýndan temsil edilir. Ve böylece, yordamsal 
programlama, özellikleri (nesneler) ve davranýþlarý (fonksiyonlar) ayýrarak gerçeði oldukça kötü temsil eder.

Nesne yönelimli programlama nedir?
----------------------------------
Nesne yönelimli programlamada (genellikle OOP olarak kýsaltýlýr), odak noktasý, hem özellikleri hem de iyi tanýmlanmýþ bir 
davranýþ setini içeren program tanýmlý veri türlerini oluþturmaktýr. OOP'deki “nesne” terimi, bu türlerden örnekleyebileceðimiz
nesnelere atýfta bulunur.

Bu, kodun daha çok þu þekilde görünmesine yol açar:

                you.eat(apple);

Bu, kimin nesne olduðunu (you), hangi davranýþýn çaðrýldýðýný (eat()), ve hangi nesnelerin bu davranýþa aksesuar olduðunu (apple) 
daha net hale getirir.

Özellikler ve davranýþlar artýk ayrý olmadýðý için, nesneleri modülerleþtirmek daha kolaydýr, bu da programlarýmýzý yazmayý ve
anlamayý kolaylaþtýrýr ve ayrýca daha yüksek bir kod yeniden kullanýlabilirliði saðlar. Bu nesneler, nesnelerle nasýl etkileþim
kurduðumuzu ve onlarýn diðer nesnelerle nasýl etkileþim kurduðunu tanýmlayarak verilerimizle çalýþmayý daha sezgisel hale getirir.
Bu tür nesneleri nasýl oluþturacaðýmýzý bir sonraki derste tartýþacaðýz.
Yordamsal vs OOP benzeri bir örnek
----------------------------------
Ýþte bir hayvanýn adýný ve bacak sayýsýný yazdýran yordamsal programlama tarzýnda yazýlmýþ kýsa bir program:

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
Bu programda, bir hayvanýn bacak sayýsýný almak ve bir hayvanýn adýný almak gibi þeyleri yapmamýza izin veren fonksiyonlar yazdýk.
Bu, oldukça iyi çalýþýrken, hayvanýmýzýn artýk bir yýlan olduðunu güncellemek istediðimizde ne olacaðýný düþünün. Kodumuza bir
yýlan eklemek için, AnimalType, numLegs(), animalName()'i deðiþtirmemiz gerekecek. Eðer bu daha büyük bir kod tabaný olsaydý,
AnimalType'ý kullanan herhangi bir diðer fonksiyonu da güncellememiz gerekecekti -- eðer AnimalType birçok yerde kullanýlýyorsa,
bu, dokunulmasý gereken çok fazla kod olabilir (ve potansiyel olarak bozulabilir).
Þimdi, ayný programý (ayný çýktýyý üreten) daha çok bir OOP zihniyeti kullanarak yazalým:

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
Bu örnekte, her hayvan kendi program tanýmlý tipidir ve bu tip, o hayvanla ilgili her þeyi yönetir (bu durumda, sadece adý ve 
bacak sayýsýný takip etmek). Þimdi, hayvanýmýzý bir yýlana güncellemek istediðimiz durumu düþünün. Tek yapmamýz gereken bir Snake
tipi oluþturmak ve onu Cat yerine kullanmaktýr. Çok az mevcut kodun deðiþtirilmesi gerekiyor, bu da zaten çalýþan bir þeyi bozma
riskinin çok daha az olmasý anlamýna gelir.

Sunulan þekliyle, Cat, Dog ve Chicken örneðimiz yukarýda çok fazla tekrar içeriyor (her biri tamamen ayný üye setini tanýmlýyor).
Bu gibi bir durumda, ortak bir Animal struct oluþturmak ve her hayvan için bir örnek oluþturmak tercih edilebilir. Ama ya diðer
hayvanlara uygulanmayan Chicken'a yeni bir üye eklemek istiyorsak (ör. wormsPerDay)? Ortak bir Animal struct ile, tüm hayvanlar
bu üyeyi alýr. OOP modelimizle, bu üyeyi Chicken nesneleriyle sýnýrlayabiliriz.

OOP, masaya baþka faydalar da getirir
-------------------------------------
Okulda, programlama ödevlerinizi teslim ettiðinizde, iþiniz esasen bitmiþtir. Profesörünüz veya öðretim görevliniz kodunuzu 
çalýþtýrýr ve doðru sonucu üretip üretmediðini görür. Ya yapar ya da yapmaz ve buna göre notlandýrýlýrsýnýz. Kodunuz muhtemelen 
bu noktada atýlýr.

Diðer taraftan, kodunuzu diðer geliþtiriciler tarafýndan kullanýlan bir depoya veya gerçek kullanýcýlarýn kullandýðý bir 
uygulamaya gönderdiðinizde, tamamen farklý bir oyun söz konusudur. Yeni bir iþletim sistemi veya yazýlým sürümü kodunuzu 
bozacaktýr. Kullanýcýlar yaptýðýnýz bazý mantýk hatalarýný bulacak. Bir iþ ortaðý yeni bir yetenek talep edecek. Diðer
geliþtiriciler kodunuzu bozmadan geniþletmek zorunda kalacak. Kodunuzun, belki de önemli ölçüde, evrim geçirebilmesi ve bunu 
minimal zaman yatýrýmý, minimal baþ aðrýsý ve minimal kýrýlma ile yapabilmesi gerekiyor.

Bunlarý en iyi þekilde ele almanýn yolu, kodunuzu olabildiðince modüler (ve tekrarsýz) tutmaktýr. Bu konuda yardýmcý olmak için, 
OOP ayrýca miras, kapsülleme, soyutlama ve çok biçimlilik gibi bir dizi diðer faydalý kavramý da masaya getirir.

Yazarýn notu
Dil tasarýmcýlarýnýn bir felsefesi var: büyük bir kelime yapacaksa, asla küçük bir kelime kullanma.

Ayrýca neden kýsaltma kelimesi bu kadar uzun?
---------------------------------------------
Tüm bunlarýn ne olduðunu ve kodunuzu daha az tekrarlý hale getirmeye, deðiþtirmeyi ve geniþletmeyi kolaylaþtýrmaya nasýl yardýmcý 
olabileceðini zamanla anlatacaðýz. OOP ile doðru þekilde tanýþtýðýnýzda ve týkladýðýnda, muhtemelen saf yordamsal programlamaya
geri dönmek istemeyeceksiniz.

Bu söylenmiþken, OOP yordamsal programlamayý deðiþtirmez -- daha ziyade, gerektiðinde karmaþýklýðý yönetmek için programlama araç
çantanýza ek araçlar verir.
“Object” terimi
---------------
“Object” teriminin biraz aþýrý yüklendiðini ve bu durumun bir miktar kafa karýþýklýðýna neden olduðunu unutmayýn. Geleneksel
programlamada, bir nesne deðerleri saklamak için bir bellek parçasýdýr. Nesne yönelimli programlamada, bir “nesne”,
hem geleneksel programlama anlamýnda bir nesne olduðunu, hem de hem özellikleri hem de davranýþlarý birleþtirdiðini ima eder.
Bu derslerde, nesne teriminin geleneksel anlamýný tercih edeceðiz ve OOP nesnelerine özellikle atýfta bulunurken “sýnýf nesnesi”
terimini tercih edeceðiz.

14.2 — Sýnýflara Giriþ
----------------------
Önceki bölümde, structlarý ele aldýk ve birden çok üye deðiþkenini tek bir nesneye toplayabilme, baþlatma ve bir birim olarak
taþýma konusunda ne kadar iyi olduklarýný tartýþtýk. Baþka bir deyiþle, structlar, ilgili veri deðerlerini depolamak ve taþýmak
için uygun bir paket saðlar.
Aþaðýdaki structý düþünün:

                #include <iostream>

                struct Date
                {
                    int day{};
                    int month{};
                    int year{};
                };

                void printDate(const Date& date)
                {
                    std::cout << date.day << '/' << date.month << '/' << date.year; // DMY formatýný varsayalým
                }

                int main()
                {
                    Date date{ 4, 10, 21 }; // toplu baþlatma kullanarak baþlat
                    printDate(date);        // tüm structý fonksiyona geçirebilir

                    return 0;
                }
Yukarýdaki örnekte, bir Datenesnesi oluþturuyoruz ve ardýndan onu tarihi yazdýran bir fonksiyona geçiriyoruz. Bu program þunu 
yazdýrýr:
                4/10/21
Bir hatýrlatma

Bu derslerde, tüm structlarýmýz topluluklardýr. topluluklardýr ders 13.6 -- struct topluluðu baþlatma dersinde tartýþýyoruz.

structlar ne kadar kullanýþlý olursa olsun, structlarýn büyük, karmaþýk programlar oluþtururken (özellikle birden çok geliþtirici
tarafýndan çalýþýlanlar) zorluklar sunabilecek bir dizi eksikliði vardýr.

Sýnýf deðiþmezlik sorunu
------------------------
Belki de structlarýn en büyük zorluðu, sýnýf deðiþmezliklerini belgelemek ve uygulamak için etkili bir yol saðlamamalarýdýr. 
Ders 9.6 -- Assert ve static_assert'te, bir deðiþmezi, "bir bileþenin çalýþýrken doðru olmasý gereken bir durum" olarak tanýmladýk.
Sýnýf türleri baðlamýnda (structlarý, sýnýflarý ve unionlarý içerir), bir sýnýf deðiþmezi, bir nesnenin geçerli bir durumda 
kalmasý için bir nesnenin ömrü boyunca doðru olmasý gereken bir durumdur. Deðiþmezliði ihlal edilmiþ bir nesne, geçersiz bir 
durumda olduðu söylenir ve bu nesnenin daha fazla kullanýlmasýndan beklenmeyen veya tanýmlanmamýþ davranýþlar ortaya çýkabilir.

Öncelikle, aþaðýdaki structý düþünün:

                struct Cift
                {
                    int ilk {};
                    int ikinci {};
                };

Ýlk ve ikinci üyeler herhangi bir deðere baðýmsýz olarak ayarlanabilir, bu yüzden Cift yapýsýnýn bir deðiþmezi yoktur.

Þimdi aþaðýdaki neredeyse ayný structý düþünün:

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 };
                };

Matematikten biliyoruz ki, paydasý 0 olan bir kesir matematiksel olarak tanýmsýzdýr (çünkü bir kesirin deðeri payýnýn paydasýna 
bölünmesidir -- ve 0'a bölme matematiksel olarak tanýmsýzdýr). Bu nedenle, bir Kesir nesnesinin payda üyesinin asla 0'a 
ayarlanmamasýný saðlamak istiyoruz. Eðer öyleyse, o Kesir nesnesi geçersiz bir durumdadýr ve bu nesnenin daha fazla
kullanýlmasýndan tanýmlanmamýþ davranýþlar ortaya çýkabilir.
Örneðin:

                #include <iostream>

                struct Kesir
                {
                    int pay { 0 };
                    int payda { 1 }; // sýnýf deðiþmezi: asla 0 olmamalý
                };

                void kesirDegeriniYazdir(const Kesir &k)
                {
                     std::cout << k.pay / k.payda << '\n';
                }

                int main()
                {
                    Kesir k { 5, 0 };   // paydasý sýfýr olan bir Kesir oluþtur
                    kesirDegeriniYazdir(k); // sýfýra bölme hatasý oluþtur

                    return 0;
                }

Yukarýdaki örnekte, Kesir'in deðiþmezliðini belgelemek için bir yorum kullanýyoruz. Ayrýca, kullanýcý bir baþlatma deðeri
saðlamazsa paydanýn 1'e ayarlanmasýný saðlamak için varsayýlan bir üye baþlatýcýsý saðlýyoruz. Bu, kullanýcýnýn bir Kesir 
nesnesini deðer baþlatmaya karar vermesi durumunda Kesir nesnemizin geçerli olacaðýný garanti eder. Bu, iyi bir baþlangýçtýr.

Ama hiçbir þey bizi bu sýnýf deðiþmezini açýkça ihlal etmekten alýkoymaz: Kesir f'yi oluþtururken, paydanýn açýkça 0'a
baþlatýlmasý için toplu baþlatmayý kullanýrýz. Bu hemen bir soruna neden olmasa da, nesnemiz artýk geçersiz bir durumdadýr ve
nesnenin daha fazla kullanýlmasý beklenmeyen veya tanýmsýz davranýþlara neden olabilir.
Ve bu tam olarak kesirDegeriniYazdir(f)'yi çaðýrdýðýmýzda gördüðümüz þey: program, sýfýra bölme hatasý nedeniyle sona erer.

Bir parantez açalým…

kesirDegeriniYazdir'nin gövdesinin baþýnda assert(f.payda != 0); eklemek küçük bir iyileþtirme olurdu. Bu, kodun belgelendirme
deðerini artýrýr ve hangi öncül koþulun ihlal edildiði daha belirgin hale gelir. Ancak, davranýþsal olarak, bu gerçekten bir þeyi
deðiþtirmez. Bu sorunlarý sorunun kaynaðýnda (üye kötü bir deðerle baþlatýldýðýnda veya atanmýþ olduðunda) yakalamak istiyoruz, 
deðil mi? Sorunun aþaðý akýþýnda (kötü deðer kullanýldýðýnda).

Kesir örneðinin göreceli basitliði göz önüne alýndýðýnda, geçersiz Kesir nesneleri oluþturmanýn basitçe kaçýnýlmasý çok zor
olmamalýdýr. Ancak, birçok structý kullanan daha karmaþýk bir kod tabanýnda, birçok üyesi olan structlar veya üyeleri karmaþýk 
iliþkiler olan structlar, hangi deðer kombinasyonunun bazý sýnýf deðiþmezini ihlal edebileceðini anlamak o kadar açýk olmayabilir.

Daha karmaþýk bir sýnýf deðiþmezi
---------------------------------
Kesir için sýnýf deðiþmezi basit bir tanedir -- payda üyesi 0 olamaz. Bu, kavramsal olarak anlamasý kolay ve kaçýnmasý çok zor
deðil. Sýnýf deðiþmezleri, bir yapýnýn üyelerinin iliþkili deðerlere sahip olmasý gerektiðinde daha fazla bir meydan okuma haline
gelir.

                #include <string>

                struct Calisan
                {
                    std::string isim { };
                    char ilkHarf { }; // her zaman `isim`in ilk karakterini tutmalý (veya `0`)
                };

Yukarýdaki (kötü tasarlanmýþ) struct da, ilkHarf üyesinde saklanan karakter deðeri, her zaman isim'in ilk karakteriyle 
eþleþmelidir.

Bir Calisan nesnesi baþlatýldýðýnda, kullanýcý sýnýf deðiþmezinin korunmasýný saðlamaktan sorumludur. Ve eðer isme yeni 
bir deðer atanýrsa, kullanýcý ayný zamanda FirstInitial'in güncellenmesini saðlamaktan da sorumludur.. Bu iliþki, bir Calisan 
nesnesini kullanan bir geliþtirici için açýk olmayabilir ve hatta eðer öyleyse, bunu yapmayý unutabilir.

Calisan nesneleri oluþturmak ve güncellemek için bize yardýmcý olacak fonksiyonlar yazsak bile (ilkHarf'in her zaman isim'in ilk 
karakterinden ayarlandýðýndan emin olmak), hala kullanýcýnýn bu fonksiyonlarýn farkýnda olmasýna ve bunlarý kullanmasýna
güveniyoruz.
Kýsacasý, bir nesnenin kullanýcýsýna sýnýf deðiþmezlerini koruma görevini vermek, sorunlu kod oluþturma olasýlýðýný artýrýr.

Anahtar içgörü

Bir nesnenin kullanýcýsýna sýnýf deðiþmezlerini koruma görevini vermek, sorunlara yol açma olasýlýðýný yükseltir.

Ýdeal olarak, sýnýf türlerimizi kurþun geçirmez hale getirmeyi çok isterdik, böylece bir nesne ya geçersiz bir duruma getirilemez
ya da eðer öyleyse hemen sinyal verebilir (gelecekteki bazý rastgele bir noktada tanýmsýz davranýþýn meydana gelmesine izin vermek
yerine).

structlar (topluluk ( aggregrate ) olarak) bu sorunu zarif bir þekilde çözmek için gereken mekaniklere sahip deðil.

Sýnýflara giriþ
---------------
C++'ý geliþtirirken, Bjarne Stroustrup, geliþtiricilerin daha sezgisel bir þekilde kullanýlabilecek program tanýmlý türler 
oluþturmasýna olanak saðlayacak yetenekler sunmak istedi. Ayrýca, büyük, karmaþýk programlarý (özellikle daha önce bahsedilen 
sýnýf deðiþmezlik sorunu gibi) sýk sýk rahatsýz eden ve bakým zorluklarýna zarif çözümler bulmakla da ilgileniyordu.

Diðer programlama dilleriyle (özellikle de ilk nesne yönelimli programlama dili olan Simula ile) deneyiminden yola çýkan Bjarne,
neredeyse her þey için kullanýlabilecek genel ve güçlü bir program tanýmlý tür geliþtirmenin mümkün olduðuna ikna oldu. Simula'ya ,
bir gönderme olarak, bu türü bir sýnýf olarak adlandýrdý. structlar gibi, bir sýnýf da birçok üye deðiþkeni farklý türlerde
olabilen bir program tanýmlý bileþik türdür.

Kilit nokta
Teknik açýdan bakýldýðýnda, structlar ve sýnýflar neredeyse aynýdýr -- bu nedenle, bir struct kullanýlarak uygulanan herhangi bir
örnek, bir sýnýf kullanýlarak veya tam tersi uygulanabilir. Ancak, pratik açýdan bakýldýðýnda, structlarý ve sýnýflarý farklý
þekillerde kullanýrýz.

Teknik ve pratik farklýlýklarý 14.5 -- Public ve private üyeler ve eriþim belirleyicileri dersinde ele alýyoruz.

Bir sýnýfý tanýmlama
--------------------
Bir sýnýf, bir program tanýmlý veri türü olduðu için, kullanýlmadan önce tanýmlanmalýdýr. Sýnýflar, struct yerine class anahtar
kelimesini kullanarak structlarla benzer þekilde tanýmlanýr. Örneðin, basit bir çalýþan sýnýfý için bir taným aþaðýdadýr:

                class Calisan
                {
                    int m_id {};
                    int m_yas {};
                    double m_wage {};
                };


Sýnýflarýn ve yapýlarýn ne kadar benzer olabileceðini göstermek için aþaðýdaki program dersin baþýnda sunduðumuz programýn 
eþdeðeridir, ancak Date artýk bir struct yerine bir sýnýftýr:

                #include <iostream>

                class Date      // struct'ý class ile deðiþtirdik
                {
                public:          // ve bu satýrý ekledik, buna eriþim belirleyici denir ( ileride görecez 14.5 )
                    int m_day{}; // ve her bir üye adýna "m_" öneklerini ekledik
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

                Bu, þunu yazdýrýr:

                4/10/21

C++ standart kütüphanesinin çoðu sýnýftýr
-----------------------------------------
Zaten belki de bilmeden sýnýf nesnelerini kullanýyordunuz. Hem std::string hem de std::string_view birer sýnýf olarak
tanýmlanmýþtýr. Aslýnda, standart kütüphanedeki takma adý olmayan türlerin çoðu sýnýf olarak tanýmlanmýþtýr!

Sýnýflar gerçekten C++'ýn kalbi ve ruhudur -- o kadar temeldirler ki, C++ baþlangýçta "sýnýflarla C" olarak adlandýrýldý! 
Sýnýflarla tanýþtýktan sonra, C++'da geçirdiðiniz çok zamaný onlarý yazmak, test etmek ve kullanmak için harcayacaksýnýz.

14.3 — Üye Fonksiyonlar
-----------------------
Ders 13.5 -- structlara, üyelere ve üye seçimine giriþte, üye deðiþkenler içerebilen bir program tanýmlý tür olan structý tanýttýk.
Ýþte bir tarihi tutmak için kullanýlan bir struct örneði:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};
                };

Þimdi, eðer tarihi ekrana yazdýrmak istiyorsak (muhtemelen çok sýk yapmak istediðimiz bir þey), bunu yapmak için bir fonksiyon 
yazmanýn mantýklý olduðunu görüyoruz. Ýþte tam bir program:

                #include <iostream>

                struct Date
                {
                    // iþte üye deðiþkenlerimiz
                    int year {};
                    int month {};
                    int day {};
                };

                void print(const Date& date)
                {
                    // üye deðiþkenler üye seçim operatörü (.) kullanýlarak eriþilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }

                int main()
                {
                    Date today { 2020, 10, 14 }; // structý toplu baþlatma

                    today.day = 16; // üye deðiþkenler üye seçim operatörü (.) kullanýlarak eriþilir
                    print(today);   // üye olmayan fonksiyon normal çaðrý sözdizimi kullanýlarak eriþilir

                    return 0;
                }

                Bu program þunu yazdýrýr:

                2020/10/16
Özelliklerin ve eylemlerin ( properties and actions ) ayrýlmasý
---------------------------------------------------------------
Etrafýnýza bir bakýn -- her yerde nesneler var: kitaplar ve binalar ve yiyecekler ve hatta siz. Gerçek hayattaki nesnelerin iki 
ana bileþeni vardýr: 
1) Bir dizi gözlemlenebilir özellik (ör. aðýrlýk, renk, boyut, katýlýk, þekil vb.), ve
2) Bu özelliklere dayalý olarak gerçekleþtirebilecekleri veya üzerlerinde gerçekleþtirilebilecekleri bir dizi eylem
   (ör. açýlma, baþka bir þeye zarar verme vb.). Bu özellikler ve eylemler ayrýlmaz.

Programlamada, özellikleri deðiþkenlerle, eylemleri ise fonksiyonlarla temsil ederiz.

Yukarýdaki Date örneðinde, özelliklerimizi (Date'in üye deðiþkenleri) ve bu özellikleri kullanarak gerçekleþtirdiðimiz eylemleri
(print() fonksiyonu) ayrý ayrý tanýmladýðýmýzý not edin. Date ve print() arasýndaki baðlantýyý, yalnýzca print()'ýn
const Date& parametresine dayanarak çýkarýrýz.

Her ikisini de bir ad alanýna koyabilirdik (ikisinin birlikte paketlenmesi gerektiðini daha belirgin hale getirmek için), ancak bu,
programýmýza daha fazla isim ekler ve daha fazla ad alaný öneki ekler, kodumuzu karmaþýklaþtýrýr.
Özelliklerimizi ve eylemlerimizi tek bir paket olarak birlikte tanýmlayabileceðimiz bir yol olmasý güzel olurdu.

Üye Fonksiyonlar
----------------
Üye deðiþkenlere ek olarak, sýnýf türleri (structlarý, sýnýflarý ve unionlarý içerir) kendi fonksiyonlarýna da sahip olabilir! 
Bir sýnýf türüne ait olan fonksiyonlara üye fonksiyonlar denir.

Bir parantez açalým…
Diðer nesne yönelimli dillerde (Java ve C# gibi), bunlara yöntemler( methods ) denir. C++'da "yöntem" terimi kullanýlmamasýna
raðmen, ilk önce bu diðer dilleri öðrenen programcýlar hala bu terimi kullanabilir.

Üye fonksiyon olmayan fonksiyonlara, onlarý üye fonksiyonlardan ayýrt etmek için üye olmayan fonksiyonlar (veya ara sýra serbest
fonksiyonlar) denir. Yukarýdaki print() fonksiyonu bir üye olmayan fonksiyondur.
Yazarýn notu
Bu derste, üye fonksiyonlarýn örneklerini göstermek için structlarý kullanacaðýz -- ancak burada gösterdiðimiz her þey sýnýflar
için de eþit derecede geçerlidir. Nedenlerini oraya vardýðýmýzda açýkça göreceðiz, gelecek derslerde 
(14.5 -- Public ve private üyeler ve eriþim belirleyicileri) sýnýflarýn üye fonksiyonlarýna örnekler göstereceðiz.

Üye fonksiyonlar, sýnýf türü tanýmýnýn içinde bildirilmeli ve sýnýf türü tanýmýnýn içinde veya dýþýnda tanýmlanabilir. 
Hatýrlatma olarak, bir taným ayný zamanda bir bildirimdir, bu yüzden bir üye fonksiyonunu sýnýfýn içinde tanýmlarsak,
bu bir bildirim olarak sayýlýr.

Þimdilik iþleri basit tutmak için, üye fonksiyonlarýmýzý sýnýf türü tanýmýnýn içinde tanýmlayacaðýz.

Üye Fonksiyon Örneði
--------------------
Dersin baþýndaki Date örneðini yeniden yazalým, print()'i bir üye olmayan fonksiyondan bir üye fonksiyonuna dönüþtürelim:

                // Üye fonksiyon versiyonu
                #include <iostream>

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() // yazdir adýnda bir üye fonksiyon tanýmlar
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // structý toplu baþlatma

                    today.day = 16; // üye deðiþkenler üye seçim operatörü (.) kullanýlarak eriþilir
                    today.print();  // üye fonksiyonlar da üye seçim operatörü (.) kullanýlarak eriþilir

                    return 0;
                }

                Bu program derlenir ve yukarýdakiyle ayný sonucu verir:

                2020/10/16
Üye olmayan ve üye örnekler arasýnda üç anahtar fark vardýr:

*- print() fonksiyonunu nerede bildiriyoruz (ve tanýmlýyoruz)
*- print() fonksiyonunu nasýl çaðýrýyoruz
*- print() fonksiyonunun içinde üyelere nasýl eriþiyoruz
Her birini sýrayla inceleyelim.

Üye Fonksiyonlar Sýnýf Türü Tanýmýnýn Ýçinde Bildirilir
-------------------------------------------------------
Üye olmayan örnekte, print() üye olmayan fonksiyonu, Date yapýsýnýn dýþýnda, global ad alanýnda tanýmlanýr. Varsayýlan olarak, 
dýþ baðlantýsý vardýr, bu yüzden diðer kaynak dosyalardan (uygun ileri bildirimle) çaðrýlabilir.

Üye örnekte, print() üye fonksiyonu, Date yapýsý tanýmýnýn içinde bildirilir (ve bu durumda, tanýmlanýr). print()'in Date'in bir
parçasý olarak bildirildiði için, bu derleyiciye print()'in bir üye fonksiyon olduðunu söyler.

Sýnýf türü tanýmýnýn içinde tanýmlanan üye fonksiyonlar, dolaylý olarak satýr içidir, bu yüzden sýnýf türü tanýmý birden çok kod
dosyasýna dahil edilirse, bir taným kuralýný ihlal etmezler.

Üye Fonksiyonlarý Çaðýrma (ve Dolaylý Nesne (implicit object))
--------------------------------------------------------------
Üye olmayan örnekte, print(today)'i çaðýrýyoruz, burada today (açýkça) bir argüman olarak geçirilir. üye örnekte, today.print()'i
çaðýrýyoruz. Bu sözdizimi, üye deðiþkenlere nasýl eriþtiðimizle (ör. today.day = 16;) tutarlýdýr.

Tüm (statik olmayan) üye fonksiyonlar, o sýnýf türünün bir nesnesi kullanýlarak çaðrýlmalýdýr. Bu durumda, today, print()'in 
üzerinde çaðrýldýðý nesnedir. Üye fonksiyon durumunda, today'i bir argüman olarak geçirmemize gerek yok. Bir üye fonksiyonun 
üzerinde çaðrýldýðý nesne, üye fonksiyona dolaylý olarak geçirilir. Bu nedenle, bir üye fonksiyonun üzerinde çaðrýldýðý nesne
genellikle dolaylý nesne olarak adlandýrýlýr.
Baþka bir deyiþle, today.print()'i çaðýrdýðýmýzda, today dolaylý nesnedir ve print() üye fonksiyonuna dolaylý olarak geçirilir.

Ýþte print()'in üye olmayan versiyonu tekrar:

                // üye olmayan print versiyonu
                void print(const Date& date)
                {
                    // üye deðiþkenler üye seçim operatörü (.) kullanýlarak eriþilir
                    std::cout << date.year << '/' << date.month << '/' << date.day;
                }
Bu print() versiyonunun const Date& date referans parametresi vardýr. Fonksiyonun içinde, üyelere bu referans parametresi
üzerinden eriþiriz, yani date.year, date.month ve date.day. print(today) çaðrýldýðýnda, date referans parametresi today argümanýna
baðlanýr ve date.year, date.month ve date.day sýrasýyla today.year, today.month ve today.day olarak deðerlendirilir.
Þimdi print() üye fonksiyonunun tanýmýna tekrar bakalým:
Üye Fonksiyon Örneði

                void print() // yazdir adýnda bir üye fonksiyon tanýmlar
                {
                    std::cout << yil << '/' << ay << '/' << gun;
                }
Üye örneðinde, üyelere yil, ay ve gun olarak eriþiriz.

Bir üye fonksiyonun içinde, üye seçim operatörü (.) ile öneki olmayan her üye tanýmlayýcý, dolaylý nesne ile iliþkilendirilir.
Baþka bir deyiþle, today.print() çaðrýldýðýnda, today dolaylý nesnemizdir ve yil, ay ve gun (önekli olmayanlar) sýrasýyla
today.yil, today.ay ve today.gun deðerlerine karþýlýk gelir.

Anahtar nokta þudur ki, Üye olmayan fonksiyonlarla, üzerinde çalýþmak için bir nesneyi fonksiyona açýkça geçirmeliyiz ve üyelere
açýkça eriþiriz. Üye fonksiyonlarla, üzerinde çalýþmak için bir nesneyi dolaylý olarak fonksiyona geçiririz ve üyelere dolaylý 
olarak eriþiriz.

Baþka Bir Üye Fonksiyon Örneði
------------------------------
Ýþte biraz daha karmaþýk bir üye fonksiyonla bir örnek:
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
                Bu, çýktýyý üretir:

                Joe kisses Kate
Bunun nasýl çalýþtýðýný inceleyelim. Öncelikle, iki Person structý tanýmlýyoruz, joe ve kate. Sonra, joe.kisses(kate)'i 
çaðýrýyoruz. joe burada dolaylý nesnedir ve kate açýk bir argüman olarak geçirilir.

kisses() üye fonksiyonu çalýþtýðýnda, isim tanýmlayýcýsý üye seçim operatörünü (.) kullanmaz, bu yüzden dolaylý nesneye, yani
joe'ya baþvurur. Bu, joe.isim'e çözülür. person.name, üye seçim operatörünü kullanýr, bu yüzden dolaylý nesneye baþvurmaz. person,,
kate için bir referans olduðundan, bu kate.name'e çözülür.

Anahtar nokta þudur ki, Bir üye fonksiyon olmadan, kisses(joe, kate)'i yazmýþ olurduk. Bir üye fonksiyonla, joe.kisses(kate)'i 
yazýyoruz. Ýkincisinin ne kadar daha iyi okunduðuna ve hangi nesnenin eylemi baþlattýðýnýn ve hangisinin destek olduðunun ne kadar
açýk olduðuna dikkat edin.

Üye Deðiþkenler ve Fonksiyonlar Herhangi Bir Sýrayla Tanýmlanabilir
-------------------------------------------------------------------
C++ derleyicisi normalde kodu yukarýdan aþaðýya derler. Her isimle karþýlaþtýðýnda, derleyici zaten o isim için bir bildirim
görmüþ olup olmadýðýný belirler, böylece uygun tip kontrolünü yapabilir.

Bu, bir üye olmayan fonksiyonun içinde, en azýndan bildirilmemiþ bir deðiþkene eriþemez veya bir fonksiyonu çaðýramazsýnýz
anlamýna gelir:
                void x()
                {
                    y(); // hata: y henüz bildirilmedi, bu yüzden derleyici ne olduðunu bilmiyor
                }

                int y()
                {
                    return 5;
                }
Ancak, üye fonksiyonlar (ve üye veri baþlatýcýlarý) ile, bu sýnýrlama geçerli deðildir ve üyelerimizi istediðimiz herhangi bir
sýrayla tanýmlayabiliriz. Örneðin:

                struct Foo
                {
                    int m_x{ y() };   // burada y()'yi çaðýrmak tamam, çünkü y() daha sonra tanýmlanýr

                    void x() { y(); } // burada y()'yi çaðýrmak tamam, çünkü y() daha sonra tanýmlanýr
                    int y()  { return 5; }
                };

Üye Fonksiyonlar Aþýrý Yüklenebilir
------------------------------------
Üye olmayan fonksiyonlar gibi, üye fonksiyonlar da aþýrý yüklenebilir, yeter ki her üye fonksiyon ayýrt edilebilsin.
Ýþte aþýrý yüklenmiþ print() üye fonksiyonlarýna sahip bir Date yapýsý örneði:

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

                    today.print(); // Tarih::print() çaðýrýr
                    std::cout << '\n';

                    today.print("Date: "); // Tarih::yazdir(std::string_view) çaðýrýr
                    std::cout << '\n';

                    return 0;
                }
                Bu, þunu yazdýrýr:

                2020/10/14
                Tarih: 2020/10/14
structlar ve Üye Fonksiyonlar
-----------------------------
C'de, structlarýn yalnýzca veri üyeleri vardýr, üye fonksiyonlarý yoktur. C++'da, sýnýflar tasarlanýrken, Bjarne Stroustrup,
structlarýn (C'den miras alýnan) üye fonksiyonlara sahip olma yeteneðine sahip olup olmamasý gerektiðini düþünmek için bir miktar
zaman harcadý. Düþündükten sonra, bunun gerektiðine karar verdi.
Bir parantez açalým…
Bu karar, structlarýn hangi yeni C++ yeteneklerine eriþim hakký olmasý gerektiði hakkýnda baþka sorularýn ortaya çýkmasýna neden
oldu. Bjarne, structlarýn sýnýrlý bir yetenek alt kümesine eriþim hakký vermenin, dilin karmaþýklýðýný ve kenar durumlarýný
artýracaðýndan endiþe ediyordu. Basitlik için, sonuçta Bjarne, structlarýn ve sýnýflarýn birleþik bir kural setine sahip olmasýna 
karar verdi (yani structlar, sýnýflarýn yapabildiði her þeyi yapabilir ve tam tersi), ve gelenek, structlarýn nasýl
kullanýlacaðýný belirleyebilir.

Modern C++'da, structlarýn üye fonksiyonlara sahip olmasý uygundur. Bu, bizim gelecek ders 14.9 -- Yapýcýlarýna ( constructor )
Giriþ'te ele alacaðýmýz private bir üye fonksiyon türü olan yapýcýlarý dýþlar. Bir yapýcýya sahip bir sýnýf türü artýk bir topluluk
deðildir ve structlarýmýzýn topluluk olarak kalmasýný istiyoruz.

*** BEST -> Üye fonksiyonlar, hem structlarla hem de sýnýflarla kullanýlabilir. Ancak, structlar, yapýcý üye fonksiyonlarýný 
            tanýmlamaktan kaçýnmalýdýr, çünkü bunu yapmak onlarý bir topluluk olmaktan çýkarýr.

Veri Üyesi Olmayan Sýnýf Türleri
--------------------------------
Veri üyesi olmayan bir sýnýf türü oluþturmak mümkündür (ör. yalnýzca üye fonksiyonlara sahip sýnýf türleri). Ayrýca, böyle bir 
sýnýf türünün nesnelerini örnekleþtirmek de mümkündür:
#include <iostream>

                struct Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo f{};
                    f.printHi(); // çaðýrmak için nesne gerektirir

                    return 0;
                }
Ancak, bir sýnýf türünün hiç veri üyesi yoksa, bir sýnýf türünü kullanmak muhtemelen gereksizdir. Bu tür durumlarda, bunun yerine
bir ad alaný kullanmayý düþünün (üye olmayan fonksiyonlarý içerir). Bu, okuyucuya hiçbir verinin yönetilmediðini (ve fonksiyonlarý
çaðýrmak için bir nesnenin örnekleþtirilmesini gerektirmediðini) daha açýk hale getirir.

                #include <iostream>

                namespace Foo
                {
                    void printHi() { std::cout << "Hi!\n"; }
                };

                int main()
                {
                    Foo::printHi(); // Hiç bir nesne gerekli deðil

                    return 0;
                }
*** BEST -> Sýnýf türünüzün hiç veri üyesi yoksa, bir ad alaný kullanmayý tercih edin.

14.4 — Const Sýnýf Nesneleri ve Const Üye Fonksiyonlar
------------------------------------------------------
5.1 -- Sabit deðiþkenler (isimli sabitler) dersinde, temel bir veri türünün (int, double, char, vb.) nesnelerinin const anahtar
kelimesi ile sabit yapýlabilceðini öðrendiniz. Tüm const deðiþkenler oluþturulduklarý anda baþlatýlmalýdýr.

                const int x;      // derleme hatasý: baþlatýlmadý
                const int y{};    // tamam: deðer baþlatýldý
                const int z{ 5 }; // tamam: liste baþlatýldý

Benzer þekilde, sýnýf türü nesneleri (structlar, sýnýflar ve unionlar) de const anahtar kelimesi kullanýlarak sabit yapýlabilir.
Bu tür nesneler de oluþturulduklarý anda baþlatýlmalýdýr.

                struct Tarih
                {
                    int year {};
                    int month {};
                    int day {};
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const sýnýf türü nesne

                    return 0;
                }

Normal deðiþkenlerle olduðu gibi, sýnýf türü nesnelerinizi de genellikle oluþturulduktan sonra deðiþtirilmediklerini garanti etmek
istediðinizde const (veya constexpr) yapmak istersiniz.

Sabit nesnelerin veri üyelerini deðiþtirmek yasaktýr
----------------------------------------------------
Bir const sýnýf türü nesnesi baþlatýldýktan sonra, nesnenin veri üyelerini deðiþtirmeye yönelik herhangi bir giriþim yasaktýr,
çünkü bu, nesnenin const-özelliðini ihlal eder. Bu, hem üye deðiþkenleri doðrudan deðiþtirmeyi (eðer onlar public ise), hem de üye
deðiþkenlerin deðerini ayarlayan üye fonksiyonlarý çaðýrmayý içerir.

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

                    today.day += 1;        // derleme hatasý: const nesnenin üyesini deðiþtiremez
                    today.incrementDay();  // derleme hatasý: const nesnenin üyesini deðiþtiren üye fonksiyonu çaðýramaz

                    return 0;
                }

Sabit nesneler, sabit olmayan üye fonksiyonlarý çaðýramaz
---------------------------------------------------------
Bu kodun da bir derleme hatasý oluþturduðunu görmek sizi þaþýrtabilir:

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

                    today.print();  // derleme hatasý: sabit olmayan üye fonksiyonu çaðýramaz

                    return 0;
                }

print() bir üye deðiþkeni deðiþtirmeye çalýþmasa bile, today.print() çaðrýmýz hala bir const ihlalidir. Bu, print() üye
fonksiyonunun kendisinin const olarak bildirilmediði için olur. Derleyici, const bir nesne üzerinde sabit olmayan bir üye
fonksiyonu çaðýrmamýza izin vermez.

Sabit Üye Fonksiyonlar
----------------------
Yukarýdaki sorunu çözmek için, print()'i bir const üye fonksiyon yapmamýz gerekiyor. Bir const üye fonksiyon, nesneyi 
deðiþtirmeyeceðini veya herhangi bir sabit olmayan üye fonksiyonlarý çaðýrmayacaðýný (çünkü onlar nesneyi deðiþtirebilir) garanti
eden bir üye fonksiyondur.
print()'i bir const üye fonksiyon yapmak kolaydýr - sadece const anahtar kelimesini, parametre listesinden sonra, ancak fonksiyon 
gövdesinden önce fonksiyon prototipine ekleriz:

                #include <iostream>

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void print() const // þimdi bir const üye fonksiyon
                    {
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.print();  // tamam: const nesne const üye fonksiyonu çaðýrabilir

                    return 0;
                }

Yukarýdaki örnekte, print() bir const üye fonksiyon haline getirildi, bu da onu const nesnelerde (örneðin today gibi) 
çaðýrabileceðimiz anlamýna gelir.
Bir üye fonksiyonun const olarak iþaretlenmesi, bu fonksiyonun nesneyi deðiþtirmeyeceðini veya herhangi bir const olmayan üye
fonksiyonlarý çaðýrmayacaðýný (çünkü onlar nesneyi deðiþtirebilir) garanti eder. Örneðin:

                struct Date
                {
                    int year {};
                    int month {};
                    int day {};

                    void incrementDay() const // const olarak iþaretlendi
                    {
                        ++day; // derleme hatasý: const fonksiyon üyeyi deðiþtiremez
                    }
                };

                int main()
                {
                    const Date today { 2020, 10, 14 }; // const

                    today.incrementDay();

                    return 0;
                }

Bu örnekte, incrementDay() const bir üye fonksiyon olarak iþaretlenmiþtir, ancak gun'u deðiþtirmeye çalýþýr. Bu bir derleme hatasý
oluþturacaktýr.

Sabit Üye Fonksiyonlar Sabit Olmayan Nesneler Üzerinde Çaðrýlabilir
-------------------------------------------------------------------
Sabit üye fonksiyonlar, sabit olmayan nesneler üzerinde de çaðrýlabilir:

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

                    today.print();  // tamam: sabit olmayan nesne üzerinde const üye fonksiyonu çaðýrabilir

                    return 0;
                }
Çünkü const üye fonksiyonlar hem const hem de non-const nesneler üzerinde çaðrýlabilir, bir üye fonksiyonun nesnenin durumunu
deðiþtirmemesi durumunda, bu fonksiyonun const yapýlmasý gerekir.
*** BEST -> Bir üye fonksiyonun nesnenin durumunu deðiþtirmemesi (ve hiçbir zaman deðiþtirmeyeceði) durumunda, bu fonksiyonun
const yapýlmasý gerekir, böylece hem const hem de non-const nesneler üzerinde çaðrýlabilir.

Hangi üye fonksiyonlara const uygulayacaðýnýza dikkat edin. Bir üye fonksiyon bir kez const olarak yapýldýðýnda, bu fonksiyon 
const nesneler üzerinde çaðrýlabilir. Bir üye fonksiyonun const'unun daha sonra kaldýrýlmasý, const bir nesne üzerinde bu üye 
fonksiyonu çaðýran herhangi bir kodu bozacaktýr.

Const Referans Yoluyla Const Nesneler
-------------------------------------
Const yerel deðiþkenlerin örnekleþtirilmesi, const nesneler oluþturmanýn bir yoludur, ancak daha yaygýn bir yol, bir nesneyi const
referans yoluyla bir fonksiyona geçirmektir. 12.5 -- Lvalue referansý ile geçiþ dersinde, sýnýf türü argümanlarýný deðer yerine 
const referans olarak geçirmenin avantajlarýný ele aldýk. Tekrarlamak gerekirse, bir sýnýf türü argümanýný deðer olarak geçirmek,
sýnýfýn bir kopyasýnýn yapýlmasýna neden olur (bu yavaþtýr) - çoðu zaman, bir kopyaya ihtiyacýmýz yoktur, orijinal argümana bir 
referans iþimizi görür ve bir kopya yapmayý önler. Fonksiyonun const lvalue argümanlarý ve rvalue argümanlarý (ör. literaller ve 
geçici nesneler) kabul etmesine izin vermek için referansý genellikle const yaparýz.

Aþaðýdaki kodda neyin yanlýþ olduðunu anlayabilir misiniz?

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
                
Cevap, doSomething() fonksiyonunun içinde, date const bir nesne olarak ele alýnýr (çünkü const referans ile geçirilmiþtir).
Ve bu const date ile, const olmayan üye fonksiyonu yazdir()'i çaðýrýyoruz. Const nesneler üzerinde const olmayan üye fonksiyonlarý
çaðýramayacaðýmýz için, bu bir derleme hatasý oluþturacaktýr.

Düzeltme basittir: print()'i const yapýn:

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
Þimdi doSomething() fonksiyonunda, const date baþarýyla const üye fonksiyonu print()'i çaðýrabilecektir.

Üye Fonksiyonun Const ve Non-Const Aþýrý Yüklemesi
--------------------------------------------------
Son olarak, çok sýk yapýlmamasýna raðmen, bir üye fonksiyonun const ve non-const versiyonunu aþýrý yüklemek mümkündür. Bu, const
nitelikleyicinin fonksiyonun imzasýnýn bir parçasý olarak kabul edildiði için çalýþýr, bu yüzden yalnýzca const'larý farklý olan
iki fonksiyon farklý kabul edilir.

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
                Bu, þunu yazdýrýr:

                non-const
                const
Bir fonksiyonun const ve non-const versiyonu ile aþýrý yükleme genellikle dönüþ deðerinin const'lýkta farklý olmasý gerektiðinde
yapýlýr. Bu oldukça nadirdir.

14.5 — Public ve Private Üyeler ve Eriþim Belirleyiciler
--------------------------------------------------------
Bir sonbahar gününde caddede yürüyorsunuz ve bir burrito yiyorsunuz. Oturacak bir yer arýyorsunuz, etrafýnýza bakýyorsunuz.
Solunuzda çimleri biçilmiþ, gölgelik aðaçlarý olan, birkaç rahatsýz edici banký ve yakýndaki oyun alanýnda baðýran çocuklarý olan
bir park var. Saðýnýzda bir yabancýnýn evi var. Pencereden, rahat bir koltuk ve çýtýrdayan bir þömine görüyorsunuz.

Aðýr bir iç çekerek, parký seçiyorsunuz.

Seçiminizin ana belirleyicisi, parkýn bir public alan olmasý, evin ise private olmasýdýr. Siz (ve herkes) public alanlara serbestçe
eriþebilirsiniz. Ancak evin üyeleri (veya açýkça izin verilen kiþiler) private konuta eriþebilir.

Üye Eriþimi
-----------
Benzer bir kavram, bir sýnýf türünün üyelerine de uygulanýr. Bir sýnýf türünün her üyesinin, kimin o üyeye eriþebileceðini
belirleyen bir eriþim düzeyi adý verilen bir özelliði vardýr.

C++'da üç farklý eriþim düzeyi vardýr: public, private ve protected. Bu derste, en yaygýn kullanýlan iki eriþim düzeyini ele 
alacaðýz: public ve private.
Bir üyeye eriþildiðinde, derleyici üyenin eriþim düzeyinin o üyeye eriþime izin verip vermediðini kontrol eder. Eriþime izin 
verilmezse, derleyici bir derleme hatasý oluþturur. Bu eriþim düzeyi sistemine bazen gayri resmi olarak eriþim kontrolleri denir.
Bir yapýnýn üyeleri varsayýlan olarak public'tir
------------------------------------------------
Public eriþim düzeyine sahip üyelere public üyeler denir. Public üyeler, nasýl eriþileceði konusunda herhangi bir kýsýtlama 
olmayan bir sýnýf türünün üyeleridir. Açýlýþ analojimizdeki park gibi, public üyelere herkes (kapsam dahilinde olduklarý sürece)
eriþebilir.

Public üyelere, ayný sýnýfýn diðer üyeleri tarafýndan eriþilebilir. Özellikle, public üyelere public tarafýndan da eriþilebilir,
bu da belirli bir sýnýf türünün üyelerinin dýþýnda bulunan kodu ifade ederiz. Public örnekleri arasýnda üye olmayan fonksiyonlar 
ve diðer sýnýf türlerinin üyeleri bulunur.

Anahtar nokta þudur ki, Bir yapýnýn üyeleri varsayýlan olarak public'tir. Public üyelere, sýnýf türünün diðer üyeleri ve public 
tarafýndan eriþilebilir.

"Public" terimi, belirli bir sýnýf türünün üyelerinin dýþýnda bulunan kodu ifade etmek için kullanýlýr. Bu, üye olmayan 
fonksiyonlarý ve diðer sýnýf türlerinin üyelerini içerir. Varsayýlan olarak, bir struct'ýn tüm üyeleri public üyelerdir.
Aþaðýdaki struct'ý düþünün:

                #include <iostream>

                struct Date
                {
                    // struct üyeleri varsayýlan olarak public'tir, herkes tarafýndan eriþilebilir
                    int year {};       // varsayýlan olarak public
                    int month {};      // varsayýlan olarak public
                    int day {};        // varsayýlan olarak public

                    void print() const // varsayýlan olarak public
                    {
                        // public üyelere sýnýf tipinin üye fonksiyonlarýnda eriþilebilir
                        std::cout << year << '/' << month << '/' << day;
                    }
                };

                // üye olmayan fonksiyon main "public" kýsmýnýn bir parçasýdýr
                int main()
                {
                    Date today { 2020, 10, 14 }; // struct'ýmýzý topluca baþlatýyoruz

                    // public üyelere public tarafýndan eriþilebilir
                    today.day = 16; // tamam: day üyesi public
                    today.print();  // tamam: print() üye fonksiyonu public

                    return 0;
                }
Bu örnekte, üyelere üç yerde eriþilir:

*- Üye fonksiyonu print() içinde, implicit nesnenin year, month ve day üyelerine eriþiriz.
*- main() içinde, today.day'a doðrudan eriþiriz ve deðerini ayarlarýz.
*- main() içinde, today.print() üye fonksiyonunu çaðýrýrýz.
Bu üç eriþime de izin verilir çünkü public üyelere her yerden eriþilebilir. main() Date'in bir üyesi olmadýðý için, public'in bir
parçasý olarak kabul edilir. Ancak, public'in public üyelere eriþim hakký olduðu için, main() Date'in üyelerine (today.print() 
çaðrýsýný içerir) doðrudan eriþebilir.

Bir sýnýfýn üyeleri varsayýlan olarak private'dir
-------------------------------------------------
Private eriþim seviyesine sahip üyelere private üyeler denir. Private üyeler, yalnýzca ayný sýnýfýn diðer üyeleri tarafýndan 
eriþilebilen bir sýnýf tipinin üyeleridir.
Aþaðýdaki örneði düþünün, bu örnek yukarýdaki örnekle neredeyse aynýdýr:

                #include <iostream>

                class Date // artýk bir struct yerine bir sýnýf
                {
                    // sýnýf üyeleri varsayýlan olarak private'dir, yalnýzca diðer üyeler tarafýndan eriþilebilir
                    int m_year {};     // varsayýlan olarak private
                    int m_month {};    // varsayýlan olarak private
                    int m_day {};      // varsayýlan olarak private

                    void print() const // varsayýlan olarak private
                    {
                        // private üyelere üye fonksiyonlarda eriþilebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }
                };

                int main()
                {
                    Date today { 2020, 10, 14 }; // derleme hatasý: artýk toplu baþlatma kullanýlamaz

                    // private üyelere public tarafýndan eriþilemez
                    today.m_day = 16; // derleme hatasý: m_day üyesi private
                    today.print();    // derleme hatasý: print() üye fonksiyonu private

                    return 0;
                }
Bu örnekte, üyelere ayný üç yerde eriþilir:
*- Üye fonksiyonu print() içinde, implicit nesnenin m_year, m_month ve m_day üyelerine eriþiriz.
*- main() içinde, today.m_day'a doðrudan eriþiriz ve deðerini ayarlarýz.
*- main() içinde, today.print() üye fonksiyonunu çaðýrýrýz.
Ancak, bu programý derlerseniz, üç derleme hatasý oluþtuðunu göreceksiniz.

main() içinde, today.m_day = 16 ve today.print() ifadeleri artýk derleme hatalarý oluþturur. Bu, main()'in public'in bir parçasý 
olmasý ve public'in private üyelere doðrudan eriþimine izin verilmemesi nedeniyledir.

print() içinde, m_year, m_month ve m_day üyelerine eriþime izin verilir. Bu, print()'in sýnýfýn bir üyesi olmasý ve sýnýfýn
üyelerinin private üyelere eriþimine izin verilmesi nedeniyledir.

Peki üçüncü derleme hatasý nereden geliyor? Belki de þaþýrtýcý bir þekilde, today'ýn baþlatýlmasý artýk bir derleme hatasý 
oluþturuyor. Ders 13.6 -- Struct aggregate initialization'da, bir topluluðun "private veya protected olmayan statik olmayan veri 
üyeleri olmamasý gerektiðini" belirttik. Date sýnýfýmýzýn private veri üyeleri var (çünkü sýnýflarýn üyeleri varsayýlan olarak 
private), bu yüzden Date sýnýfýmýz bir topluluk olarak nitelendirilmiyor. Bu yüzden, artýk onu baþlatmak için toplu baþlatma
kullanamayýz.

Sýnýflarý (genellikle topluluk olmayanlarý) nasýl düzgün bir þekilde baþlatacaðýmýzý, yaklaþan ders 14.9 -- Constructorlara
Giriþ'te tartýþacaðýz.

*** Ana Fikir
Bir sýnýfýn üyeleri varsayýlan olarak private'dir. Private üyelere sýnýfýn diðer üyeleri tarafýndan eriþilebilir, ancak public
tarafýndan eriþilemez. Private üyelere sahip bir sýnýf artýk bir topluluk deðildir ve bu nedenle toplu baþlatma kullanamaz.

Private Üye Deðiþkenlerinizi Adlandýrma
---------------------------------------
C++'da, private veri üyelerini "m_" önekiyle baþlayacak þekilde adlandýrma yaygýn bir uygulamadýr. Bu, birkaç önemli nedenle
yapýlýr. Bir sýnýfýn aþaðýdaki üye fonksiyonunu düþünün:

                // Private üye m_name'i name parametresinin deðerine ayarlayan bir üye fonksiyon
                void setName(std::string_view name)
                {
                    m_name = name;
                }
Öncelikle, "m_" öneki, bir üye fonksiyonu içindeki veri üyelerini fonksiyon parametrelerinden veya yerel deðiþkenlerden kolayca
ayýrt etmemizi saðlar. "m_name" in bir üye olduðunu ve "name" in olmadýðýný kolayca görebiliriz. Bu, bu fonksiyonun sýnýfýn
durumunu deðiþtirdiðini açýkça belirtir. Ve bu önemlidir çünkü bir veri üyesinin deðerini deðiþtirdiðimizde, bu deðiþiklik üye 
fonksiyonun kapsamýnýn ötesinde kalýr (fonksiyon parametrelerine veya yerel deðiþkenlere yapýlan deðiþiklikler genellikle bu
þekilde olmaz).

Bu, yerel statik deðiþkenler için "s_" öneklerini ve global deðiþkenler için "g_" öneklerini kullanmayý önermemizin ayný nedenidir.
Ýkincisi, "m_" öneki, private üye deðiþkenler ile yerel deðiþkenlerin, fonksiyon parametrelerinin ve üye fonksiyonlarýnýn adlarý
arasýnda ad çakýþmalarýný önlemeye yardýmcý olur.

Eðer private üyemizi m_name yerine name olarak adlandýrmýþ olsaydýk:
Name fonksiyon parametremiz, name private veri üyesini gölgede býrakýrdý.
Eðer name adýnda bir üye fonksiyonumuz olsaydý, name tanýmlayýcýsýnýn yeniden tanýmlanmasý nedeniyle bir derleme hatasý alýrdýk.
*** BEST -> Private üyelerinizi, onlarý yerel deðiþkenlerin, fonksiyon parametrelerinin ve üye fonksiyonlarýn adlarýndan ayýrt 
etmeye yardýmcý olmak için "m_" önekiyle baþlayacak þekilde adlandýrmayý düþünün.

Eriþim Seviyelerini Eriþim Belirleyicileri ile Ayarlama
-------------------------------------------------------
Varsayýlan olarak, struct'larýn (ve unionlarýn) üyeleri public'tir ve sýnýflarýn üyeleri private'dir.
Ancak, üyelerimizin eriþim seviyesini bir eriþim belirleyicisi kullanarak açýkça ayarlayabiliriz. Bir eriþim belirleyicisi,
belirleyiciyi takip eden tüm üyelerin eriþim seviyesini ayarlar. C++ üç eriþim belirleyicisi saðlar: public:, private: ve protected

Aþaðýdaki örnekte, print() üye fonksiyonunun public tarafýndan kullanýlabilmesini saðlamak için public: eriþim belirleyicisini ve
veri üyelerimizi private yapmak için private: eriþim belirleyicisini kullanýyoruz.

                class Date
                {
                // Burada tanýmlanan herhangi bir üye varsayýlan olarak private olurdu

                public: // iþte bizim public eriþim belirleyicimiz

                    void print() const // yukarýdaki public: belirleyici nedeniyle public
                    {
                        // üyeler diðer private üyelere eriþebilir
                        std::cout << m_year << '/' << m_month << '/' << m_day;
                    }

                private: // iþte bizim private eriþim belirleyicimiz

                    int m_year { 2020 };  // yukarýdaki private: belirleyici nedeniyle private
                    int m_month { 14 }; // yukarýdaki private: belirleyici nedeniyle private
                    int m_day { 10 };   // yukarýdaki private: belirleyici nedeniyle private
                };

                int main()
                {
                    Date d{};
                    d.print();  // tamam, main() public üyelere eriþebilir

                    return 0;
                }
Bu örnek derlenir. Print() public: eriþim belirleyicisi nedeniyle bir public üye olduðu için, main() (public'in bir parçasý olan)
ona eriþebilir. Private üyelere sahip olduðumuz için, d'yi topluca baþlatamayýz. Bu örnekte, bunun yerine varsayýlan üye 
baþlatmasýný kullanýyoruz (geçici bir çözüm olarak).

Sýnýflar private eriþime varsayýlan olarak sahip olduðu için, öncü private: eriþim belirleyicisini atlayabilirsiniz:

                Class Foo
                {
                // sýnýflar varsayýlan olarak private üyelere sahip olduðu için burada private eriþim belirleyicisine gerek yok
                    int m_something {};  // varsayýlan olarak private
                };
Ancak, sýnýflar ve struct'lar farklý eriþim seviyesi varsayýlanlarýna sahip olduðu için, birçok geliþtirici açýk olmayý tercih 
eder:

                class Foo
                {
                private: // gereksiz, ancak ardýndan gelenlerin private olduðunu açýkça belirtir
                    int m_something {};  // varsayýlan olarak private
                };
Bu teknik olarak gereksiz olsa da, explicit private: belirleyicisinin kullanýlmasý, ardýndan gelen üyelerin private olduðunu 
açýkça belirtir, Foo'nun bir sýnýf mý yoksa bir struct mý olarak tanýmlandýðýna dayanarak varsayýlan eriþim seviyesini çýkarmadan.

Eriþim Seviyesi Özeti
---------------------
Ýþte farklý eriþim seviyelerinin hýzlý bir özeti:

Bir sýnýf tipi, herhangi bir sýrayla herhangi bir sayýda eriþim belirleyicisini kullanabilir ve bunlar tekrar tekrar 
kullanýlabilir (örneðin, bazý public üyeleriniz, ardýndan bazý private olanlar, ardýndan daha fazla public olanlar olabilir).

Çoðu sýnýf, çeþitli üyeler için hem private hem de public eriþim belirleyicilerini kullanýr. Bu konuda bir örneði bir sonraki 
bölümde göreceðiz.
| Eriþim Düzeyi | Eriþim Belirleyici | Üye Eriþimi | Türetilmiþ Sýnýf Eriþimi  |
|---------------|---------------------|-------------|--------------------------|
| Public        | `public:`           | evet        | evet                     |
| Protected     | `protected:`        | evet        | evet                     |
| Private       | `private:`          | evet        | hayýr                    |

Struct'lar ve Sýnýflar için Eriþim Seviyesi En Ýyi Uygulamalarý
---------------------------------------------------------------
Artýk eriþim seviyelerinin ne olduðunu anladýðýmýza göre, nasýl kullanacaðýmýzý konuþalým.
Struct'lar tamamen eriþim belirleyicilerinden kaçýnmalýdýr, yani tüm struct üyeleri varsayýlan olarak public olacaktýr.
Struct'larýmýzýn topluluklar olmasýný istiyoruz ve topluluklar yalnýzca public üyelere sahip olabilir. Public: eriþim
belirleyicisinin kullanýlmasý varsayýlanla gereksiz olurdu ve private: veya protected: kullanmak struct'ý bir topluluk olmaktan 
çýkarýrdý.

Sýnýflar genellikle yalnýzca private (veya protected) veri üyelerine sahip olmalýdýr (varsayýlan private eriþim seviyesini
kullanarak veya private: (veya protected) eriþim belirleyicisini kullanarak). Bunun gerekçesini bir sonraki ders olan
14.6 -- Eriþim Fonksiyonlarý'nda tartýþacaðýz.

Sýnýflar normalde public üye fonksiyonlarýna sahip olur (bu nedenle bu üye fonksiyonlar, nesne oluþturulduktan sonra public 
tarafýndan kullanýlabilir). Ancak, nadiren üye fonksiyonlar private (veya protected) yapýlýr eðer public tarafýndan kullanýlmalarý
amaçlanmamýþsa.

*** BEST -> Sýnýflar genellikle üye deðiþkenlerini private (veya protected) yapmalý ve üye fonksiyonlarýný public yapmalýdýr.
Struct'lar genellikle eriþim belirleyicilerini kullanmaktan kaçýnmalýdýr (tüm üyeler varsayýlan olarak public olacaktýr).

Eriþim Seviyeleri Sýnýf Bazýnda Çalýþýr
---------------------------------------
C++ eriþim seviyelerinin sýklýkla kaçýrýlan veya yanlýþ anlaþýlan bir inceliði, üyelere eriþimin sýnýf bazýnda tanýmlandýðý,
nesne bazýnda tanýmlanmadýðýdýr.

Bir üye fonksiyonun doðrudan private üyelere eriþebileceðini zaten biliyorsunuz. Ancak, eriþim seviyeleri sýnýf bazýnda olduðu 
için, bir üye fonksiyonu ayný sýnýf tipinden olan ve kapsamda olan herhangi bir diðer nesnenin private üyelerine de doðrudan
eriþebilir.Bunu bir örnekle gösterelim:

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
                Bu, þunu yazdýrýr:

                Joe kisses Kate
Burada dikkat edilmesi gereken birkaç þey var.

Öncelikle, m_name private yapýldý, bu yüzden yalnýzca Person sýnýfýnýn üyeleri tarafýndan eriþilebilir (public tarafýndan deðil).
Ýkincisi, sýnýfýmýzýn private üyeleri olduðu için, bir topluluk deðildir ve Person nesnelerimizi baþlatmak için toplu baþlatma
kullanamayýz. Bu soruna uygun bir çözüm bulana kadar, Person nesnelerimize bir isim atamamýza izin veren setName() adýnda bir
public üye fonksiyon oluþturduk.

Üçüncüsü, kisses() bir üye fonksiyon olduðu için, private üye m_name'e doðrudan eriþim hakkýna sahiptir. Ancak, p.m_name'e de
doðrudan eriþim hakkýna sahip olduðunu görmek sizi þaþýrtabilir! Bu, p'nin bir Person nesnesi olduðu ve kisses()'in kapsamda olan
herhangi bir Person nesnesinin private üyelerine eriþebileceði için çalýþýr!
Bu konuyu operatör aþýrý yükleme bölümünde daha fazla örneklerle göreceðiz.

Teknik ve pratik açýdan struct'lar ve sýnýflar arasýndaki fark
--------------------------------------------------------------
Artýk eriþim seviyelerini ele aldýðýmýza göre, struct'lar ve sýnýflar arasýndaki teknik farklarý nihayet tartýþabiliriz.
Hazýr mýsýnýz?
Bir sýnýf üyelerini varsayýlan olarak private yapar, oysa bir struct üyelerini varsayýlan olarak public yapar.
Evet, bu kadar. :))

Yazarýn Notu

Titiz olmak gerekirse, bir tane daha küçük bir fark var -- struct'lar diðer sýnýf türlerinden public olarak miras alýr ve sýnýflar
private olarak miras alýr. Bu konunun ne anlama geldiðini, miras bölümünde ele alacaðýz, ancak bu belirli nokta pratik olarak 
önemsizdir çünkü zaten miras için varsayýlanlara güvenmemelisiniz.
Pratikte, struct'larý ve sýnýflarý farklý þekillerde kullanýrýz.

Bir kural olarak, aþaðýdakilerin tümü doðru olduðunda bir struct kullanýn:

*- Kýsýtlý eriþimden fayda saðlamayan basit bir veri koleksiyonunuz var.
*- Toplu baþlatma yeterlidir.
*- Sýnýf deðiþmezleriniz, kurulum ihtiyaçlarýnýz veya temizleme ihtiyaçlarýnýz yok.
*- Struct'larýn kullanýlabileceði birkaç örnek: constexpr global program verileri, bir nokta struct'ý
   (private yapýlmalarýndan fayda saðlamayan basit bir int üye koleksiyonu), bir fonksiyondan bir veri seti döndürmek için
   kullanýlan struct'lar.

Aksi takdirde bir sýnýf kullanýn.

Struct'larýmýzýn topluluklar olmasýný istiyoruz. Yani, struct'ýnýzý bir topluluk olmaktan çýkaracak herhangi bir özellik
kullanýyorsanýz, muhtemelen bir sýnýf kullanmalýsýnýz (ve sýnýflar için tüm en iyi uygulamalarý takip etmelisiniz).
*/