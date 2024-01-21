#include <iostream>

int main()
{
    return 0;
}
/*
13.9 — Struct Karışıklığı
-------------------------
Program Tanımlı Üyeleri Olan Structlar
--------------------------------------
C++'da, structlar (ve sınıflar) diğer program tanımlı türlerin üyeleri olabilir. Bunu yapmanın iki yolu vardır.
İlk olarak, bir program tanımlı türü (global kapsamda) tanımlayabilir ve sonra bunu başka bir program tanımlı türünün üyesi olarak
kullanabiliriz:
 
                #include <iostream>

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                struct Company
                {
                    int numberOfEmployees {};
                    Employee CEO {}; // Employee, Company struct'ının içinde bir struct
                };

                int main()
                {
                    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Employee'yi başlatmak için iç içe geçmiş başlatma listesi
                    std::cout << myCompany.CEO.wage << '\n'; // CEO'nun maaşını yazdır

                    return 0;
                }
                
Yukarıdaki durumda, bir Employee struct'ı tanımladık ve sonra bunu bir Company struct'ının üyesi olarak kullandık. Company'mizi 
başlatırken, iç içe geçmiş bir başlatma listesi kullanarak Employee'mizi de başlatabiliriz. Ve CEO'nun maaşını bilmek istiyorsak,
yalnızca üye seçim operatörünü iki kez kullanırız:-> myCompany.CEO.wage;

İkinci olarak, türler diğer türlerin içine de yerleştirilebilir, yani bir Employee yalnızca bir Company'nin parçası olarak varsa, 
Employee türü Company struct'ının içine yerleştirilebilir:
 
                #include <iostream>

                struct Company
                {
                    struct Employee // Company::Employee üzerinden erişilir
                    {
                        int id{};
                        int age{};
                        double wage{};
                    };

                    int numberOfEmployees{};
                    Employee CEO{}; // Employee, Company struct'ının içinde bir struct
                };

                int main()
                {
                    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Employee'yi başlatmak için iç içe geçmiş başlatma listesi
                    std::cout << myCompany.CEO.wage << '\n'; // CEO'nun maaşını yazdır

                    return 0;
                }
 
Bu, daha sıklıkla sınıflarla yapılır, bu yüzden bunu gelecekteki bir dersde daha fazla konuşacağız

Struct Boyutu ve Veri Yapısı Hizalaması
---------------------------------------
Genellikle, bir struct'ın boyutu tüm üyelerinin boyutlarının toplamıdır, ama her zaman değil!
Aşağıdaki programı düşünün:
 
                #include <iostream>

                struct Foo
                {
                    short a {};
                    int b {};
                    double c {};
                };

                int main()
                {
                    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
                    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
                    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

                    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

                    return 0;
                }
 
                Yazarın makinesinde bu yazdırıldı:

                The size of short is 2 bytes
                The size of int is 4 bytes
                The size of double is 8 bytes
                The size of Foo is 16 bytes
                short + int + double'ın boyutunun 14 byte olduğuna, ancak Foo'nun boyutunun 16 byte olduğuna dikkat edin!

Meğerse, bir struct'ın boyutunun, içerdiği tüm değişkenlerin boyutundan en az bu kadar büyük olacağını söyleyebiliriz.
Ama daha büyük olabilir! Performans nedenleriyle, derleyici bazen yapılarına boşluklar ekler (buna dolgu denir). Yukarıdaki Foo
struct'ında, derleyici görünmez bir şekilde a üyesinden sonra 2 byte dolgu ekliyor, bu da struct boyutunu 14 yerine 16 byte yapıyor.
Bu, struct'ın boyutu üzerinde oldukça önemli bir etkiye sahip olabilir, aşağıdaki program bunu gösterir:
 
                #include <iostream>

                struct Foo1
                {
                    short a{}; // a'dan sonra 2 byte dolgu olacak
                    int b{};
                    short c{}; // c'den sonra 2 byte dolgu olacak
                };

                struct Foo2
                {
                    int b{};
                    short a{};
                    short c{};
                };

                int main()
                {
                    std::cout << sizeof(Foo1) << '\n'; // 12 yazdırır
                    std::cout << sizeof(Foo2) << '\n'; // 8 yazdırır

                    return 0;
                }
 
                Bu program şunu yazdırır:

                12
                8
Foo1 ve Foo2'nin aynı üyeleri olduğuna dikkat edin, tek fark bildirim sırasıdır. Ancak Foo1, eklenen dolgu nedeniyle %50 daha
büyüktür.
Kaynak:
(1) github.com. https://github.com/StephenMeansMe/textbook_cpp-for-mathematicians/tree/2f10a987e2116aaa5d49b4581ae0875b9db1e139/ch02%2Fexamples%2Fprogram2_3.cc.

13.10 — İşaretçiler ve Referanslarla Üye Seçimi
-----------------------------------------------
structlar ve struct referansları için üye seçimi

13.5 -- structlara, üyelere ve üye seçimine giriş dersinde, bir struct nesnesinden bir üyeyi seçmek için üye seçim operatörünü (.)
kullanabileceğinizi gösterdik:

                #include <iostream>

                struct Calisan
                {
                    int id {};
                    int yas {};
                    double maas {};
                };

                int main()
                {
                    Calisan joe { 1, 34, 65000.0 };

                    // struct nesnesinden bir üyeyi seçmek için üye seçim operatörünü (.) kullanın
                    ++joe.yas; // Joe'nun doğum günü oldu
                    joe.maas = 68000.0; // Joe terfi etti

                    return 0;
                }
 
Bir nesneye olan referanslar, nesnenin kendisi gibi davrandığından, bir struct referansından bir üyeyi seçmek için üye seçim
operatörünü (.) kullanabiliriz:

                #include <iostream>

                struct Calisan
                {
                    int id{};
                    int yas{};
                    double maas{};
                };

                void calisaniYazdir(const Calisan& e)
                {
                    // Yapıya referans olan bir üyeyi seçmek için üye seçim operatörünü (.) kullanın
                    std::cout << "Id: " << e.id << '\n';
                    std::cout << "Yaş: " << e.yas << '\n';
                    std::cout << "Maaş: " << e.maas << '\n';
                }

                int main()
                {
                    Calisan joe{ 1, 34, 65000.0 };

                    ++joe.yas;
                    joe.maas = 68000.0;

                    calisaniYazdir(joe);

                    return 0;
                }
 
structlara işaretçilerle üye seçimi
-----------------------------------
Ancak, bir yapıya işaretçiniz varsa, üye seçim operatörünün (.) kullanımı işe yaramaz:

                #include <iostream>

                struct Calisan
                {
                    int id{};
                    int yas{};
                    double maas{};
                };

                int main()
                {
                    Calisan joe{ 1, 34, 65000.0 };

                    ++joe.yas;
                    joe.maas = 68000.0;

                    Calisan* ptr{ &joe };
                    std::cout << ptr.id << '\n'; // Derleme hatası: işaretçilerle operator. kullanılamaz

                    return 0;
                }
Normal değişkenler veya referanslarla, nesnelere doğrudan erişebiliriz. Ancak, işaretçiler adresleri tuttuğu için, onunla bir şey
yapmadan önce işaretçiyi önce dereferans etmemiz gerekiyor. Bu yüzden bir yapıya işaretçiden bir üyeye erişmenin bir yolu şu
şekildedir:

                #include <iostream>

                struct Calisan
                {
                    int id{};
                    int yas{};
                    double maas{};
                };

                int main()
                {
                    Calisan joe{ 1, 34, 65000.0 };

                    ++joe.yas;
                    joe.maas = 68000.0;

                    Calisan* ptr{ &joe };
                    std::cout << (*ptr).id << '\n'; // Çok iyi değil ama işe yarıyor: İlk önce ptr'yi dereferans edin, sonra üye
                                                    // seçimi yapın

                    return 0;
                }
 
Ancak, bu biraz çirkin, özellikle dereferans işlemini parantez içine almak zorunda olduğumuz için, bu da üye seçim işleminden önce
öncelik kazanır. Daha temiz bir sözdizimi için, C++ bir işaretçiden üye seçim operatörü (->) sunar (bazen ok operatörü olarak da 
adlandırılır) ve bir nesneye işaretçiden üyeleri seçmek için kullanılabilir:

                #include <iostream>

                struct Calisan
                {
                    int id{};
                    int yas{};
                    double maas{};
                };

                int main()
                {
                    Calisan joe{ 1, 34, 65000.0 };

                    ++joe.yas;
                    joe.maas = 68000.0;

                    Calisan* ptr{ &joe };
                    std::cout << ptr->id << '\n'; // Daha iyi: -> kullanarak işaretçiden üye seçin

                    return 0;
                }
 
Bu işaretçiden üye seçim operatörü (->), üye seçim operatörü (.) ile aynı şekilde çalışır, ancak üyeyi seçmeden önce işaretçi
nesnesini implisit olarak dereferans eder. Bu nedenle ptr->id, (*ptr).id ile eşdeğerdir. Bu ok operatörü sadece yazması daha kolay
değil, ayrıca indireksiyon sizin için implisit olarak yapıldığı için hata yapmaya çok daha az eğilimlidir, bu yüzden endişelenmeniz
gereken öncelik sorunları yoktur. Bu nedenle, bir işaretçi aracılığıyla üye erişimi yaparken, her zaman . operatörü yerine ->
operatörünü kullanın.

*** BEST -> Bir işaretçiyi kullanarak bir üyenin değerine erişirken, üye seçim operatörü (.) yerine işaretçiden üye seçim 
            operatörünü (->) kullanın.

İşaretçiler ve işaretçi olmayan üyeleri karıştırma
--------------------------------------------------
Üye seçim operatörü her zaman şu anda seçili olan değişkene uygulanır. İşaretçiler ve normal üye değişkenler karışık olduğunda,
. ve ->'nun sırayla kullanıldığı üye seçimlerini görebilirsiniz: 

                #include <iostream>
                #include <string>

                struct Paw
                {
                    int claws{};
                };

                struct Animal
                {
                    std::string name{};
                    Paw paw{};
                };

                int main()
                {
                    Animal puma{ "Puma", { 5 } };

                    Animal* ptr{ &puma };

                    // ptr is a pointer, use ->
                    // paw is not a pointer, use .

                    std::cout << ptr->paw.claws << '\n'; // Parantezlere gerek yok

                    return 0;
                }
Burada parantez gerekli değildir. Çünkü hem . operatörü hem de -> operatörü soldan sağa doğru okunur o yüzden bir yanlışlık 
olmayacaktır fakat parantezlerin kullanılması okunabilirliği arttıracaktır.
11.6 -- Fonksiyon Şablonları dersinde, her farklı tür setiyle çalışmak istediğimizde ayrı bir (aşırı yüklenmiş) fonksiyon
oluşturma zorluğunu tanıttık:

                #include <iostream>

                // iki int değerinden daha büyüğünü hesaplamak için fonksiyon
                int max(int x, int y)
                {
                    return (x < y) ? y : x;
                }

                // iki double değerinden daha büyüğünü hesaplamak için neredeyse aynı fonksiyon
                // tek fark tip bilgisi
                double max(double x, double y)
                {
                    return (x < y) ? y : x;
                }

                int main()
                {
                    std::cout << max(5, 6);     // max(int, int)'i çağırır
                    std::cout << '\n';
                    std::cout << max(1.2, 3.4); // max(double, double)'ı çağırır

                    return 0;
                }
 
Buna çözüm, derleyicinin ihtiyaç duyduğumuz her tür seti için normal fonksiyonları örnekleştirmek üzere kullanabileceği bir
fonksiyon şablonu oluşturmaktı:

                #include <iostream>

                // max için tek bir fonksiyon şablonu
                template <typename T>
                T max(T x, T y)
                {
                    return (x < y) ? y : x;
                }

                int main()
                {
                    std::cout << max(5, 6);     // max<int>(int, int)'i örnekleştirir ve çağırır
                    std::cout << '\n';
                    std::cout << max(1.2, 3.4); // max<double>(double, double)'ı örnekleştirir ve çağırır

                    return 0;
                }
Toplu Türler Benzer Zorluklarla Karşılaşır

Toplu türlerle (hem structlar/sınıflar/unionlarhem de diziler) benzer zorluklarla karşılaşıyoruz. Örneğin, int değerlerinin
çiftleriyle çalışmamız gereken bir program yazıyoruz ve iki sayıdan hangisinin daha büyük olduğunu belirlememiz gerekiyor. Böyle
bir program yazabiliriz:

                #include <iostream>

                struct Pair
                {
                    int first{};
                    int second{};
                };

                constexpr int max(Pair p) // Pair küçük olduğu için değer olarak geçer
                {
                    return (p.first < p.second ? p.second : p.first);
                }

                int main()
                {
                    Pair p1{ 5, 6 };
                    std::cout << max(p1) << " is larger\n";

                    return 0;
                }
 
Daha sonra, double değerlerinin çiftlerine de ihtiyacımız olduğunu keşfediyoruz. Bu yüzden programımızı aşağıdaki gibi 
güncelliyoruz:

                #include <iostream>

                struct Pair
                {
                    int first{};
                    int second{};
                };

                struct Pair // derleme hatası: Pair'ın yanlış yeniden tanımı
                {
                    double first{};
                    double second{};
                };

                constexpr int max(Pair p)
                {
                    return (p.first < p.second ? p.second : p.first);
                }

                constexpr double max(Pair p) // derleme hatası: aşırı yüklenmiş fonksiyon yalnızca dönüş tipinden farklılık
                                             // gösterir
                {
                    return (p.first < p.second ? p.second : p.first);
                }

                int main()
                {
                    Pair p1{ 5, 6 };
                    std::cout << max(p1) << " is larger\n";

                    Pair p2{ 1.2, 3.4 };
                    std::cout << max(p2) << " is larger\n";

                    return 0;
                }
 
Ne yazık ki, bu program derlenmeyecek ve ele alınması gereken bir dizi sorun var.

İlk olarak, fonksiyonların aksine, tür tanımları aşırı yüklenemez. Derleyici, Pair'ın ikinci tanımını, Pair'ın ilk tanımının
yanlış bir yeniden tanımı olarak kabul eder. İkinci olarak, fonksiyonlar aşırı yüklenebilirken, max(Pair) fonksiyonlarımız
yalnızca dönüş tipinden farklılık gösterir ve aşırı yüklenmiş fonksiyonlar yalnızca dönüş tipine göre ayrıştırılamaz.
Üçüncü olarak, burada çok fazla fazlalık var. Her Pair struct'ı aynıdır (veri tipi dışında) ve max(Pair) fonksiyonlarımız da
aynıdır (dönüş tipi dışında).

Pair struct'larımıza farklı isimler vererek (ör. PairInt ve PairDouble) ilk iki sorunu çözebilirdik. Ama sonra hem isimlendirme
şemamızı hatırlamamız gerekiyor, hem de istediğimiz her ek çift türü için bir sürü kodu klonlamamız gerekiyor, bu da fazlalık 
sorununu çözmüyor.

Neyse ki, daha iyisini yapabiliriz.

Yazarın Notu

Devam etmeden önce, fonksiyon şablonları, şablon türleri veya fonksiyon şablonu örnekleştirmenin nasıl çalıştığı konusunda
belirsizseniz, lütfen 11.6 -- Fonksiyon Şablonları ve 11.7 -- Fonksiyon Şablonu Örnekleştirme derslerini gözden geçirin.

Sınıf Şablonları
----------------
Bir fonksiyon şablonunun fonksiyonları örnekleştirmek için bir şablon tanımı olduğu gibi, bir sınıf şablonu da sınıf türlerini
örnekleştirmek için bir şablon tanımıdır.
Hatırlatma
Bir "sınıf türü", bir struct, sınıf veya union türüdür. Her ne kadar "sınıf şablonları"nı basitlik için structlar üzerinde
gösteriyor olsak da, burada anlatılan her şey sınıflar için de aynı şekilde geçerlidir.

Hatırlatma olarak, int çifti struct tanımımızı burada veriyorum:
 
                struct Pair
                {
                    int first{};
                    int second{};
                };
 
Çift sınıfımızı bir sınıf şablonu olarak yeniden yazalım:
 
                #include <iostream>

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                int main()
                {
                    Pair<int> p1{ 5, 6 };        // Pair<int>'i örnekleştirir ve p1 nesnesini oluşturur
                    std::cout << p1.first << ' ' << p1.second << '\n';

                    Pair<double> p2{ 1.2, 3.4 }; // Pair<double>'ı örnekleştirir ve p2 nesnesini oluşturur
                    std::cout << p2.first << ' ' << p2.second << '\n';

                    Pair<double> p3{ 7.8, 9.0 }; // Pair<double>'ın önceki tanımını kullanarak p3 nesnesini oluşturur
                    std::cout << p3.first << ' ' << p3.second << '\n';

                    return 0;
                }
 
Fonksiyon şablonları gibi, bir sınıf şablonu tanımını da bir şablon parametre bildirimiyle başlatırız. Önce template anahtar
kelimesiyle başlarız. Sonra, sınıf şablonumuzun içinde kullanacağı tüm şablon türlerini açılış ve kapanış parantezleri (<>) içinde
belirtiriz. Her bir şablon türü için, typename (tercih edilen) veya class (tercih edilmeyen) anahtar kelimesini kullanırız, 
ardından şablon türünün adını (ör. T) yazarız. Bu durumda, her iki üyemiz de aynı tür olacağı için, yalnızca bir şablon türüne
ihtiyacımız var.

Sonra, struct'ımızı her zamanki gibi tanımlarız, tek fark, şablon türümüzü (T) daha sonra gerçek bir türle değiştirilecek bir 
şablonlu tür istediğimiz her yerde kullanabiliriz. İşte bu kadar! Sınıf şablonu tanımıyla işimiz bitti.

Main içinde, Pair nesnelerini istediğimiz her türle örnekleştirebiliriz. Önce, Pair<int> türünde bir nesne örnekleştiririz. 
Pair<int> için bir tür tanımı henüz mevcut olmadığından, derleyici sınıf şablonunu kullanarak Pair<int> adında bir struct türü 
tanımı örnekleştirir, burada şablon türü T'nin tüm örnekleri int türüyle değiştirilir.

Sonra, Pair<double> türünde bir nesne örnekleştiririz, bu da T'nin double ile değiştirildiği Pair<double> adında bir struct türü
tanımı örnekleştirir. p3 için, Pair<double> zaten örnekleştirilmiş olduğundan, derleyici önceki tür tanımını kullanır.

İşte yukarıdaki örneğin aynısı, tüm şablon örnekleştirmeleri yapıldıktan sonra derleyicinin aslında neyi derlediğini gösteriyor:
 
                #include <iostream>

                // Pair sınıf şablonumuz için bir bildirim
                // (artık tanıma ihtiyacımız yok çünkü kullanılmıyor)
                template <typename T>
                struct Pair;

                // Pair<int>'in neye benzediğini açıkça tanımlayın
                template <> // derleyiciye bunun hiç şablon parametresi olmayan bir şablon türü olduğunu söyler
                struct Pair<int>
                {
                    int first{};
                    int second{};
                };

                // Pair<double>'ın neye benzediğini açıkça tanımlayın
                template <> // derleyiciye bunun hiç şablon parametresi olmayan bir şablon türü olduğunu söyler
                struct Pair<double>
                {
                    double first{};
                    double second{};
                };

                int main()
                {
                    Pair<int> p1{ 5, 6 };        // Pair<int>'i örnekleştirir ve p1 nesnesini oluşturur
                    std::cout << p1.first << ' ' << p1.second << '\n';

                    Pair<double> p2{ 1.2, 3.4 }; // Pair<double>'ı örnekleştirir ve p2 nesnesini oluşturur
                    std::cout << p2.first << ' ' << p2.second << '\n';

                    Pair<double> p3{ 7.8, 9.0 }; // Pair<double>'ın önceki tanımını kullanarak p3 nesnesini oluşturur
                    std::cout << p3.first << ' ' << p3.second << '\n';

                    return 0;
                }
 
Bu örneği doğrudan derleyebilir ve beklenildiği gibi çalıştığını görebilirsiniz!
Sınıf Şablonumuzu Bir Fonksiyonda Kullanma
------------------------------------------
Şimdi, max() fonksiyonumuzun farklı türlerle çalışmasını sağlama zorluğuna geri dönelim. Derleyici, Pair<int> ve Pair<double>'ı
ayrı türler olarak kabul ettiği için, parametre türüne göre ayrıştırılan aşırı yüklenmiş fonksiyonları kullanabiliriz:
Hatırlatma
Pair<int> p ile max() fonksiyonu çağrıldığında, derleyici fonksiyon şablonundan int max<int>(Pair<int>) fonksiyonunu örnekleştirir,
burada şablon türü T, int ile değiştirilir. Aşağıdaki kod parçacığı, bu durumda derleyicinin aslında neyi örnekleştirdiğini
gösterir:

                template <>
                constexpr int max(Pair<int> p)
                {
                    return (p.first < p.second ? p.second : p.first);
                }
 
Tüm fonksiyon şablonu çağrılarında olduğu gibi, şablon türü argümanı konusunda açık olabiliriz (ör. max<int>(p1)) veya gizli 
olabiliriz (ör. max(p2)) ve derleyicinin şablon türü argümanının ne olması gerektiğini belirlemek için şablon argümanı çıkarımını
kullanmasına izin verebiliriz.

Şablon Türü ve Şablon Olmayan Tür Üyeleri Olan Sınıf Şablonları
---------------------------------------------------------------
Sınıf şablonları, bazı üyelerin bir şablon türünü ve diğer üyelerin normal (şablon olmayan) bir türü kullanabilir. Örneğin:
 
                template <typename T>
                struct Foo
                {
                    T first{};    // first, T'nin yerine neyin geçtiğine sahip olacak
                    int second{}; // second, T'nin ne tür olduğuna bakılmaksızın her zaman int olacak
                };
 
Bu, beklediğiniz gibi tam olarak çalışır: first, şablon türü T'nin ne olduğu olacak ve second her zaman bir int olacaktır.

Birden Fazla Şablon Türüne Sahip Sınıf Şablonları
-------------------------------------------------
Sınıf şablonları da birden fazla şablon türüne sahip olabilir. Örneğin, Pair sınıfımızın iki üyesinin farklı türlerde olabilmesini
istiyorsak, Pair sınıf şablonumuzu iki şablon türü ile tanımlayabiliriz:

                #include <iostream>

                template <typename T, typename U>
                struct Pair
                {
                    T first{};
                    U second{};
                };

                template <typename T, typename U>
                void print(Pair<T, U> p)
                {
                    std::cout << '[' << p.first << ", " << p.second << ']';
                }

                int main()
                {
                    Pair<int, double> p1{ 1, 2.3 }; // bir int ve bir double tutan bir çift
                    Pair<double, int> p2{ 4.5, 6 }; // bir double ve bir int tutan bir çift
                    Pair<int, int> p3{ 7, 8 };      // iki int tutan bir çift

                    print(p2);

                    return 0;
                }
 
Birden fazla şablon türünü tanımlamak için, şablon parametre bildirimimizde, her bir istenen şablon türünü bir virgülle ayırırız.
Yukarıdaki örnekte, biri T ve diğeri U adında iki farklı şablon türü tanımlarız. T ve U için gerçek şablon türü argümanları farklı
(p1 ve p2'nin durumu gibi) veya aynı (p3'ün durumu gibi) olabilir.

Bir Fonksiyon Şablonunu Birden Fazla Sınıf Türüyle Çalışacak Şekilde Yapma
--------------------------------------------------------------------------
Yukarıdaki örnekteki print() fonksiyon şablonunu düşünün:
 
                template <typename T, typename U>
                void print(Pair<T, U> p)
                {
                    std::cout << '[' << p.first << ", " << p.second << ']';
                }
 
Fonksiyon parametresini açıkça Pair<T, U> olarak tanımladığımız için, yalnızca Pair<T, U> türündeki argümanlar (veya Pair<T, U>'ya
dönüştürülebilenler) eşleşir. Bu, fonksiyonumuzu yalnızca Pair<T, U> argümanıyla çağırabilmek istediğimiz durumlar için idealdir.

Bazı durumlarda, başarılı bir şekilde derlenecek herhangi bir türle kullanmak istediğimiz fonksiyon şablonları yazabiliriz.
Bunu yapmak için, fonksiyon parametresi olarak bir tür şablon parametresi kullanırız.Örneğin:

                #include <iostream>

                template <typename T, typename U>
                struct Pair
                {
                    T first{};
                    U second{};
                };

                struct Point
                {
                    int first{};
                    int second{};
                };

                template <typename T>
                void print(T p) // tür şablon parametresi her şeyle eşleşir
                {
                    std::cout << '[' << p.first << ", " << p.second << ']'; // yalnızca türün first ve second üyeleri varsa
                                                                            // derlenecektir
                }

                int main()
                {
                    Pair<double, int> p1{ 4.5, 6 };
                    print(p1); // print(Pair<double, int>)'i eşleştirir

                    std::cout << '\n';

                    Point p2 { 7, 8 };
                    print(p2); // print(Point)'i eşleştirir

                    std::cout << '\n';

                    return 0;
                }
 
Yukarıdaki örnekte, print()'i yalnızca tek bir tür şablon parametresi (T) olan bir şekilde yeniden yazdık, bu da her türle eşleşir.
Fonksiyonun gövdesi, bir first ve second üyesi olan her sınıf türü için başarılı bir şekilde derlenecektir. Bunu, print()'i
Pair<double, int> türünde bir nesneyle çağırarak ve ardından Point türünde bir nesneyle tekrar çağırarak gösteriyoruz.

Yanıltıcı olabilecek bir durum var. Aşağıdaki print() versiyonunu düşünün:

                template <typename T, typename U>
                struct Pair // Pair adında bir sınıf türü tanımlar
                {
                    T first{};
                    U second{};
                };

                template <typename Pair> // Pair adında bir tür şablon parametresi tanımlar (Pair sınıf türünü gölgede bırakır)
                void print(Pair p)       // bu, şablon parametresi Pair'e atıfta bulunur, sınıf türü Pair'e değil
                {
                    std::cout << '[' << p.first << ", " << p.second << ']';
                }
 
Bu fonksiyonun yalnızca Pair sınıf türü argümanıyla çağrıldığında eşleşeceğini düşünebilirsiniz. Ancak bu print() versiyonu,
şablon parametresinin T olarak adlandırıldığı önceki versiyonla işlevsel olarak aynıdır ve her türle eşleşir. Buradaki sorun,
Pair'i bir tür şablon parametresi olarak tanımladığımızda, Pair'in global kapsamdaki diğer kullanımlarını gölgede bırakmamızdır.
Bu yüzden fonksiyon şablonu içinde, Pair, şablon parametresi Pair'e atıfta bulunur, sınıf türü Pair'e değil. Ve bir tür şablon
parametresi her türle eşleşeceğinden, bu Pair, herhangi bir argüman türüyle eşleşir, yalnızca sınıf türü Pair olanlarla değil!

Basit şablon parametre isimlerine (T, U, N gibi) bağlı kalmak iyi bir fikirdir, çünkü bu şekilde bir sınıf türü adını gölgeleme 
olasılığı daha düşüktür.

std::pair
---------
Veri çiftleriyle çalışmak yaygın olduğu için, C++ standart kütüphanesi, önceki bölümdeki Pair sınıf şablonuyla aynı şekilde
tanımlanan std::pair adında bir sınıf şablonu içerir (<utility> başlığındadır). Aslında, geliştirdiğimiz çift struct'ını 
std::pair ile değiştirebiliriz:

                #include <iostream>
                #include <utility>

                template <typename T, typename U>
                void print(std::pair<T, U> p)
                {
                    std::cout << '[' << p.first << ", " << p.second << ']';
                }

                int main()
                {
                    std::pair<int, double> p1{ 1, 2.3 }; // bir int ve bir double tutan bir çift
                    std::pair<double, int> p2{ 4.5, 6 }; // bir double ve bir int tutan bir çift
                    std::pair<int, int> p3{ 7, 8 };      // iki int tutan bir çift

                    print(p2);

                    return 0;
                }
 
Bu dersde kendi Pair sınıfımızı geliştirdik, ancak gerçek kodda, kendi Pair sınıfınızı yazmak yerine std::pair'ı tercih 
etmelisiniz.

Sınıf Şablonlarını Birden Fazla Dosyada Kullanma
------------------------------------------------
Fonksiyon şablonları gibi, sınıf şablonları da genellikle başlık dosyalarında tanımlanır, böylece onları ihtiyaç duyan her kod 
dosyasına dahil edebiliriz. Hem şablon tanımları hem de tür tanımları, bir tanımlama kuralından( ODR ) muaf olduğu için bu sorun
oluşturmaz:

pair.h:
 
                #ifndef PAIR_H
                #define PAIR_H

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                template <typename T>
                constexpr T max(Pair<T> p)2
                {
                    return (p.first < p.second ? p.second : p.first);
                }

                #endif
 
foo.cpp:

                #include "pair.h"
                #include <iostream>

                void foo()
                {
                    Pair<int> p1{ 1, 2 };
                    std::cout << max(p1) << " is larger\n";
                }
 
main.cpp:

                #include "pair.h"
                #include <iostream>

                void foo(); // foo() fonksiyonu için ileri bildirim

                int main()
                {
                    Pair<double> p2 { 3.4, 5.6 };
                    std::cout << max(p2) << " is larger\n";

                    foo();

                    return 0;
                }

Sınıf şablonu argüman çıkarımı (CTAD)
-------------------------------------
C++17'de başlayarak, bir sınıf şablonundan bir nesne örnekleştirirken, derleyici nesnenin başlatıcısının türlerinden şablon
türlerini çıkarabilir (buna sınıf şablonu argüman çıkarımı veya kısaca CTAD denir). Örneğin:

                #include <utility> // std::pair için

                int main()
                {
                    std::pair<int, int> p1{ 1, 2 }; // açıkça sınıf şablonunu belirt std::pair<int, int> (C++11 ve sonrası)
                    std::pair p2{ 1, 2 };           // CTAD, başlatıcılardan std::pair<int, int>'i çıkarmak için kullanılır (C++17)

                    return 0;
                }
CTAD yalnızca şablon argüman listesi bulunmadığında gerçekleştirilir. Bu nedenle, aşağıdakilerin her ikisi de hatalardır:

#include <utility> // std::pair için

                int main()
                {
                    std::pair<> p1 { 1, 2 };    // hata: çok az şablon argümanı, her iki argüman çıkarılmadı
                    std::pair<int> p2 { 3, 4 }; // hata: çok az şablon argümanı, ikinci argüman çıkarılmadı

                    return 0;
                }

CTAD bir tür çıkarımı olduğundan, çıkarılan türü değiştirmek için sözcük son eklerini kullanabiliriz:

#include <utility> // std::pair için

                int main()
                {
                    std::pair p1 { 3.4f, 5.6f }; // pair<float, float> olarak çıkarıldı
                    std::pair p2 { 1u, 2u };     // pair<unsigned int, unsigned int> olarak çıkarıldı

                    return 0;
                }
Şablon argüman çıkarım rehberleri
---------------------------------
Çoğu durumda, CTAD kutudan çıkar çıkmaz çalışır. Ancak, belirli durumlarda, derleyici şablon argümanlarını düzgün bir şekilde
nasıl çıkaracağını anlamak için biraz daha yardıma ihtiyaç duyabilir.

Aşağıdaki programın (std::pair'ı kullanan örneğe neredeyse aynı olan) C++17'de derlenmediğini (yalnızca) görmek sizi şaşırtabilir:

                // kendi Pair tipimizi tanımlayın
                template <typename T, typename U>
                struct Pair
                {
                    T first{};
                    U second{};
                };

                int main()
                {
                    Pair<int, int> p1{ 1, 2 }; // tamam: şablon argümanlarını açıkça belirtiyoruz
                    Pair p2{ 1, 2 };           // C++17'de derleme hatası (C++20'de tamam)

                    return 0;
                }
Bunu C++17'de derlerseniz, muhtemelen “sınıf şablonu argüman çıkarımı başarısız oldu” veya “şablon argümanları çıkarılamıyor” veya
“Geçerli bir yapılandırıcı veya çıkarım rehberi yok” hakkında bir hata alırsınız. Bu, C++17'de, CTAD'nin toplu sınıf şablonları 
için şablon argümanlarını nasıl çıkaracağını bilmediği içindir. Bunu çözmek için, derleyiciye bir çıkarım rehberi sağlayabiliriz,
bu da derleyiciye belirli bir sınıf şablonu için şablon argümanlarını nasıl çıkaracağını söyler.
İşte bir çıkarım rehberi ile aynı program:
                template <typename T, typename U>
                struct Pair
                {
                    T first{};
                    U second{};
                };

                // İşte Pair için bir çıkarım rehberi (yalnızca C++17'de gereklidir)
                // T ve U türündeki argümanlarla başlatılan Pair nesneleri Pair<T, U> olarak çıkarılmalıdır
                template <typename T, typename U>
                Pair(T, U) -> Pair<T, U>;

                int main()
                {
                    Pair<int, int> p1{ 1, 2 }; // açıkça sınıf şablonunu belirt Pair<int, int> (C++11 ve sonrası)
                    Pair p2{ 1, 2 };           // CTAD, başlatıcılardan Pair<int, int>'i çıkarmak için kullanılır (C++17)

                    return 0;
                }
Bu örnek C++17 altında derlenmelidir.
Pair sınıfımız için çıkarım rehberi oldukça basittir, ancak nasıl çalıştığına daha yakından bakalım.
                // İşte Pair için bir çıkarım rehberi (yalnızca C++17'de gereklidir)
                // T ve U türündeki argümanlarla başlatılan Pair nesneleri Pair<T, U> olarak çıkarılmalıdır
                template <typename T, typename U>
                Pair(T, U) -> Pair<T, U>;

Öncelikle, Pair sınıfımızdaki gibi aynı şablon tip tanımını kullanıyoruz. Bu mantıklıdır, çünkü çıkarım kılavuzumuz derleyiciye 
bir Pair<T, U> için tipleri nasıl çıkaracağını söyleyecekse, T ve U'nun ne olduğunu (şablon tipleri) tanımlamamız gerekiyor.
İkinci olarak, okun sağ tarafında, derleyicinin çıkarmasına yardımcı olduğumuz tipi belirtiyoruz. Bu durumda, derleyicinin
Pair<T, U> tipindeki nesneler için şablon argümanlarını çıkarabilmesini istiyoruz, bu yüzden tam olarak buraya bunu koyuyoruz.
Son olarak, okun sol tarafında, derleyicinin hangi tür bir bildirim araması gerektiğini söylüyoruz. Bu durumda, iki argümanı olan
(biri T tipinde, diğeri U tipinde) bir Pair nesnesinin bildirimini aramasını söylüyoruz. Bunu Pair(T t, U u) olarak da 
yazabilirdik (burada t ve u, parametrelerin adlarıdır, ancak t ve u'yu kullanmadığımız için onlara isim vermemiz gerekmez).

Hepsini bir araya getirerek, derleyicinin bir Pair ile iki argümanın (sırasıyla T ve U tiplerinde) bir bildirimini gördüğünde,
tipin Pair<T, U> olması gerektiğini söylüyoruz.

Bu yüzden derleyici programımızda Pair p2{ 1, 2 }; tanımını gördüğünde, "oh, bu bir Pair'ın bildirimi ve iki argüman var, int ve
int tipinde, bu yüzden çıkarım kılavuzunu kullanarak bunun Pair<int, int> olması gerektiğini çıkarabilirim" diyecek.
Tek bir şablon tipi alan bir Pair için benzer bir örnek aşağıdadır:

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                // Pair'ımız için bir çıkarım kılavuzu (sadece C++17'de gereklidir)
                // T ve T tipindeki argümanlarla başlatılan Pair nesneleri Pair<T> olarak çıkarılmalıdır
                template <typename T>
                Pair(T, T) -> Pair<T>;

                int main()
                {
                    Pair<int> p1{ 1, 2 }; // sınıf şablonunu açıkça belirt Pair<int> (C++11 ve sonrası)
                    Pair p2{ 1, 2 };      // CTAD, başlatıcılarından Pair<int> çıkarmak için kullanılır (C++17)

                    return 0;
                }
Bu durumda, çıkarım kılavuzumuz bir Pair(T, T) (T tipinde iki argümanı olan bir Pair) ile Pair<T> eşleştirir.

İpucu

C++20, derleyicinin topluluklar için otomatik olarak çıkarım kılavuzları oluşturma yeteneğini ekledi, bu yüzden çıkarım
kılavuzları sadece C++17 uyumluluğu için sağlanmalıdır.
Bu nedenle, çıkarım kılavuzları olmayan Pair versiyonu C++20'de derlenebilir.

std::pair (ve diğer standart kütüphane şablon tipleri) önceden tanımlanmış çıkarım kılavuzlarıyla birlikte gelir, bu yüzden 
yukarıdaki std::pair'ı kullanan örneğimiz, çıkarım kılavuzları sağlamamıza gerek kalmadan C++17'de düzgün bir şekilde derlenir.

Varsayılan değerlere sahip tip şablon parametreleri
---------------------------------------------------
Fonksiyon parametrelerinin varsayılan argümanlara sahip olabileceği gibi, şablon parametrelerine de varsayılan değerler 
verilebilir. Bunlar, şablon parametresi açıkça belirtilmediğinde ve çıkarılamadığında kullanılır.

İşte yukarıdaki Pair<T, U> sınıf şablon programımızın bir modifikasyonu, tip şablon parametreleri T ve U, int tipine varsayılan 
olarak ayarlanmış:
                template <typename T=int, typename U=int> // T ve U'yu int tipine varsayılan olarak ayarla
                struct Pair
                {
                    T first{};
                    U second{};
                };

                template <typename T, typename U>
                Pair(T, U) -> Pair<T, U>;

                int main()
                {
                    Pair<int, int> p1{ 1, 2 }; // sınıf şablonunu açıkça belirt Pair<int, int> (C++11 ve sonrası)
                    Pair p2{ 1, 2 };           // CTAD, başlatıcılarından Pair<int, int> çıkarmak için kullanılır (C++17)

                    Pair p3;                   // varsayılan Pair<int, int> kullanır

                    return 0;
                }

p3 için tanımımız, tip şablon parametreleri için tipleri açıkça belirtmez, ne de bu tiplerin çıkarılacağı bir başlatıcı vardır.
Bu nedenle, derleyici varsayılanlarda belirtilen tipleri kullanacak, bu da p3'ün Pair<int, int> tipinde olacağı anlamına gelir.

CTAD statik olmayan üye başlatma ile çalışmaz
---------------------------------------------
Bir sınıf türünün üyesini statik olmayan üye başlatma kullanarak başlatırken, CTAD bu bağlamda çalışmaz. Tüm şablon argümanları 
açıkça belirtilmelidir:

                #include <utility> // std::pair için

                struct Foo
                {
                    std::pair<int, int> p1{ 1, 2 }; // tamam, şablon argümanları açıkça belirtildi
                    std::pair p2{ 1, 2 };           // derleme hatası, CTAD bu bağlamda kullanılamaz
                };

                int main()
                {
                    std::pair p3{ 1, 2 };           // tamam, CTAD burada kullanılabilir
                    return 0;
                }
CTAD işlev parametreleri ile çalışmaz
-------------------------------------
CTAD, sınıf şablonu argüman çıkarımı anlamına gelir, sınıf şablonu parametre çıkarımı değil, bu yüzden yalnızca şablon
argümanlarının türünü çıkarır, şablon parametrelerini değil.

Bu nedenle, CTAD işlev parametrelerinde kullanılamaz.

                #include <iostream>
                #include <utility>

                void print(std::pair p) // derleme hatası, CTAD burada kullanılamaz
                {
                    std::cout << p.first << ' ' << p.second << '\n';
                }

                int main()
                {
                    std::pair p { 1, 2 }; // p, std::pair<int, int> olarak çıkarıldı
                    print(p);

                    return 0;
                }
Bu tür durumlarda, bir şablon kullanmalısınız:

                #include <iostream>
                #include <utility>

                template <typename T, typename U>
                void print(std::pair<T, U> p)
                {
                    std::cout << p.first << ' ' << p.second << '\n';
                }

                int main()
                {
                    std::pair p { 1, 2 }; // p, std::pair<int, int> olarak çıkarıldı
                    print(p);

                    return 0;
                }

10.7 -- Typedefs ve tip takma adları dersinde, tip takma adlarının mevcut bir tip için bir takma ad tanımlamamıza nasıl izin 
verdiğini tartıştık. Tüm şablon argümanları açıkça belirtildiğinde bir sınıf şablonu için bir tip takma adı oluşturmak, normal bir
tip takma adı gibi çalışır:

                #include <iostream>

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                template <typename T>
                void print(const Pair<T>& p)
                {
                    std::cout << p.first << ' ' << p.second << '\n';
                }

                int main()
                {
                    using Point = Pair<int>; // normal tip takma adı oluştur
                    Point p { 1, 2 };        // derleyici bunu Pair<int> ile değiştirir

                    print(p);

                    return 0;
                }
Bu tür takma adlar yerel olarak (örneğin, bir fonksiyon içinde) veya global olarak tanımlanabilir.

Takma Ad Şablonları
-------------------
Diğer durumlarda, bir şablon sınıfı için bir tip takma adı isteyebiliriz, burada takma adın bir parçası olarak tanımlanan tüm 
şablon argümanları yoktur (ve bunun yerine tip takma adının kullanıcısı tarafından sağlanacaktır). Bunu yapmak için, tip takma
adlarını örnekleştirmek için kullanılabilecek bir takma ad şablonu tanımlayabiliriz. Aynı Tip takma adları ayrı tipler
tanımlamazkenki gibi, takma ad şablonları da ayrı tipler tanımlamaz.
İşte bunun nasıl çalıştığına dair bir örnek:

                #include <iostream>

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                // İşte bizim takma ad şablonumuz
                // Takma ad şablonları global kapsamda tanımlanmalıdır
                template <typename T>
                using Coord = Pair<T>; // Coord, Pair<T> için bir takma addır

                // Print fonksiyon şablonumuzun, Coord'un şablon parametresi T'nin bir tip şablon parametresi olduğunu bilmeye
                ihtiyacı var
                template <typename T>
                void print(const Coord<T>& c)
                {
                    std::cout << c.first << ' ' << c.second << '\n';
                }

                int main()
                {
                    Coord<int> p1 { 1, 2 }; // C++-20 öncesi: Tüm tip şablon argümanlarını açıkça belirtmeliyiz
                    Coord p2 { 1, 2 };      // C++20'de, CTAD ile çalışacak takma adlı tipin bir başlatıcıdan şablon
                                            // argümanlarının tipini çıkarmak için takma ad şablon çıkarımını kullanabiliriz

                    std::cout << p1.first << ' ' << p1.second << '\n';
                    print(p2);

                    return 0;
                }

Bu örnekte, tip şablon parametresi T'nin Coord takma adının kullanıcısı tarafından tanımlanacağı bir yer olan Coord adlı bir takma
ad şablonu tanımlıyoruz. Coord, takma ad şablonudur ve Coord<T>, Pair<T> için örnekleştirilmiş tip takma adıdır. Bir kez 
tanımlandıktan sonra, Pair'ı kullanacağımız yerde Coord'u ve Pair<T>'yi kullanacağımız yerde Coord<T>'yi kullanabiliriz.

Bu örnekle ilgili birkaç şeyi not etmeye değer.

Birincisi, normal tip takma adlarının aksine (bir blok içinde tanımlanabilir), takma ad şablonları global kapsamda tanımlanmalıdır
(tüm şablonların olması gerektiği gibi).

İkincisi, C++20'den önce, bir takma ad şablonunu kullanarak bir nesneyi örnekleştirirken şablon argümanlarını açıkça belirtmeliyiz.
C++20'den itibaren, takma ad şablon çıkarımını kullanabiliriz, bu da bir başlatıcıdan takma adlı tipin bir CTAD ile çalışacak
şekilde şablon argümanlarının tipini çıkarır.

Üçüncüsü, CTAD'ın fonksiyon parametrelerinde çalışmaması nedeniyle, bir takma ad şablonunu bir fonksiyon parametresi olarak 
kullanırken, takma ad şablonu tarafından kullanılan şablon argümanlarını açıkça tanımlamalıyız. Diğer bir deyişle, bunu yaparız:

                template <typename T>
                void print(const Coord<T>& c)
                {
                    std::cout << c.first << ' ' << c.second << '\n';
                }
Bunu yapmayız:

                void print(const Coord& c) // çalışmaz, eksik şablon argümanları
                {
                    std::cout << c.first << ' ' << c.second << '\n';
                }
Bu, Coord veya Coord<T> yerine Pair veya Pair<T> kullanmış olsaydık hiçbir fark yaratmaz.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    ÖZET
Tebrikler! Bir başka konuyu daha başarıyla tamamladınız. Structlar hakkında edindiğiniz bilgiler, C++'ın en önemli konusu olan 
sınıflara (classes) geçtiğimizde işinize yarayacak!

Hızlı bir gözden geçirme yapalım:

Bir program tanımlı tipi (veya kullanıcı tanımlı tipi), kendi programlarımızda kullanmak üzere oluşturabileceğimiz özel bir tiptir.
Enumerasyon tipleri ve sınıf tipleri (structlar, sınıflar ve unionlardahil) program tanımlı tiplerin oluşturulmasına izin verir.
Program tanımlı tipler, kullanılmadan önce tanımlanmalıdır. Bir program tanımlı tipinin tanımına tip tanımı denir. Tip tanımları,
bir tanım kuralından( ODR ) muaf tutulur.

Bir enumerasyon (ayrıca bir sayılan tip veya bir enum olarak da adlandırılır), her olası değerin sembolik bir sabit (bir 
numaralandırıcı denir) olarak tanımlandığı bileşik bir veri tipidir. Enumerasyonlar, ayrı tiplerdir, yani derleyici onları diğer
tiplerden ayırt edebilir (tip takma adlarının aksine).

Kapsam dışı enumerasyonlar, numaralandırıcı isimlerini enumerasyon tanımının kendisiyle aynı kapsama alanına koydukları için bu 
şekilde adlandırılır (bir ad alanının yaptığı gibi yeni bir kapsam bölgesi oluşturmak yerine). Kapsam dışı enumerasyonlar ayrıca
numaralandırıcıları için adlandırılmış bir kapsam bölgesi sağlar. Kapsam dışı enumerasyonlar, açıkça integral değerlere 
dönüştürülür.

Kapsamlı enumerasyonlar, kapsam dışı enumerasyonlara benzer şekilde çalışır, ancak tam sayılara açıkça dönüştürülmezler ve
numaralandırıcılar yalnızca enumerasyonun kapsam bölgesine yerleştirilir (enumerasyonun tanımlandığı kapsam bölgesine değil).

Bir struct (yapı ( structure ) için kısaltma), birden çok değişkeni tek bir tipe toplamamıza izin veren bir program tanımlı veri 
tipidir. Struct'ın (veya sınıfın) bir parçası olan değişkenlere veri üyeleri (veya üye değişkenler) denir.
Belirli bir üye değişkenine erişmek için, struct değişken adı ve üye adı arasında üye seçim operatörünü (operatör.) kullanırız 
(normal structlar ve struct referansları için), veya pointer operatöründen üye seçim operatörünü (operatör->) kullanırız 
(struct pointerları için).

Genel programlamada, bir toplu veri tipi (veya bir topluluk), birden çok veri üyesi içerebilecek herhangi bir tipi ifade eder. 
C++'da, yalnızca veri üyeleri olan diziler ve structlar topluluktur.

Topluluklar, topluluk üyelerini doğrudan başlatmamıza izin veren bir başlatma formu olan toplu başlatmayı kullanır. Bunu yapmak 
için, bir başlatıcı listesi sağlarız, bu sadece virgülle ayrılmış değerler listesidir. Toplu başlatma, üyeye özgü bir başlatma
yapar, yani struct'taki her üye, bildirimin sırasına göre başlatılır.

C++20'de, Belirlenmiş başlatıcılar, hangi başlatma değerlerinin hangi üyelere eşleştiğini açıkça tanımlamanıza izin verir.
Üyeler, struct'ta bildirildikleri sırayla başlatılmalıdır, aksi takdirde bir hata oluşur.

Bir struct (veya sınıf) tipi tanımladığımızda, her üye için tip tanımının bir parçası olarak varsayılan bir başlatma değeri
sağlayabiliriz. Bu işleme statik olmayan üye başlatma denir ve başlatma değeri varsayılan üye başlatıcı olarak adlandırılır.

Performans nedenleriyle, derleyici bazen yapılarına boşluklar ekler (bu dolgu olarak adlandırılır), bu yüzden bir yapının boyutu,
üyelerinin boyutlarının toplamından daha büyük olabilir.

Bir sınıf şablonu, sınıf tiplerini (structlar, sınıflar veya unionlar) örnekleştirmek için bir şablon tanımıdır. Sınıf Şablonu
Argüman Çıkarımı (CTAD), derleyicinin bir başlatıcıdan şablon tipi argümanlarını çıkarabilmesine izin veren bir C++17 özelliğidir.
*/