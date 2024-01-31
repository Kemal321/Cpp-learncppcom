#include <iostream>
class Something {
    int m_x{};
public:
    Something(int x)
        : m_x{ x }
    {
        std::cout << "Constructor Cagirildi. \n";
    }
    Something(const Something& s)
        :m_x{ s.m_x }
    {
        std::cout << "Copy Constructor Cagirildi.\n";
    }
    void print() const {
        std::cout << "Something(" << m_x << ")\n";
    }
};
int main()
{
    Something s{ Something{5} };
    s.print();
    return 0;
}
/*
14.15 — Sýnýf baþlatma ve kopya elision
---------------------------------------
1.4 -- Deðiþken atama ve baþlatma dersinde, temel türlerle nesneler için 6 temel baþlatma türünü tartýþýyoruz:

                int a;         // baþlatýcý yok (varsayýlan baþlatma)
                int b = 5;     // eþittir iþaretinden sonra baþlatýcý (kopya baþlatma)
                int c( 6 );    // parantez içinde baþlatýcý (doðrudan baþlatma)

                // Liste baþlatma yöntemleri (C++11)
                int d { 7 };   // süslü parantezler içinde baþlatýcý (doðrudan liste baþlatma)
                int e = { 8 }; // eþittir iþaretinden sonra süslü parantezler içinde baþlatýcý (kopya liste baþlatma)
                int f {};      // baþlatýcý boþ süslü parantezler (deðer baþlatma)

Bu baþlatma türlerinin tümü, sýnýf türleriyle nesneler için geçerlidir:

                #include <iostream>

                class Foo
                {
                public:

                    // Varsayýlan yapýcý
                    Foo()
                    {
                        std::cout << "Foo()\n";
                    }

                    // Normal yapýcý
                    Foo(int x)
                    {
                        std::cout << "Foo(int) " << x << '\n';
                    }

                    // Kopya yapýcý
                    Foo(const Foo&)
                    {
                        std::cout << "Foo(const Foo&)\n";
                    }
                };

                int main()
                {
                    // Foo() varsayýlan yapýcýyý çaðýrýr
                    Foo f1;           // varsayýlan baþlatma
                    Foo f2{};         // deðer baþlatma (tercih edilen)

                    // foo(int) normal yapýcýyý çaðýrýr
                    Foo f3 = 3;       // kopya baþlatma (yalnýzca non-explicit yapýcýlar)
                    Foo f4(4);        // doðrudan baþlatma
                    Foo f5{ 5 };      // doðrudan liste baþlatma (tercih edilen)
                    Foo f6 = { 6 };   // kopya liste baþlatma (yalnýzca non-explicit yapýcýlar)

                    // foo(const Foo&) kopya yapýcýyý çaðýrýr
                    Foo f7 = f3;      // kopya baþlatma
                    Foo f8(f3);       // doðrudan baþlatma
                    Foo f9{ f3 };     // doðrudan liste baþlatma (tercih edilen)
                    Foo f10 = { f3 }; // kopya liste baþlatma

                    return 0;
                }

Modern C++'ta, kopya baþlatma, doðrudan baþlatma ve liste baþlatma esasen ayný þeyi yapar - bir nesneyi baþlatýrlar.

Baþlatma türlerinin tümü için:

Bir sýnýf türünü baþlatýrken, bu sýnýfýn yapýcýlarý kümesi incelenir ve en iyi eþleþen yapýcýyý belirlemek için aþýrý yük 
çözümlemesi kullanýlýr. Bu, argümanlarýn açýk dönüþümünü içerebilir.
Bir sýnýf olmayan türü baþlatýrken, açýk dönüþüm kurallarý, bir açýk dönüþümün var olup olmadýðýný belirlemek için kullanýlýr.
Anahtar Bilgi

Baþlatma biçimleri arasýnda üç anahtar fark vardýr:

Liste baþlatma, daraltýcý dönüþümleri reddeder.
Kopya baþlatma, yalnýzca non-explicit yapýcýlarý/dönüþüm fonksiyonlarýný dikkate alýr. Bunu, 14.16 -- Dönüþtürme yapýcýlarý ve
explicit anahtar kelimesi dersinde ele alacaðýz.
Liste baþlatma, diðer eþleþen yapýcýlardan ziyade eþleþen liste yapýcýlarýna öncelik verir. Bunu, 16.2 -- std::vector'a Giriþ
ve liste yapýcýlarý dersinde ele alacaðýz.
Ayrýca belirli durumlarda, belirli baþlatma biçimlerinin kullanýlmasýnýn yasaklandýðýný belirtmekte fayda var (örneðin, bir yapýcý
üye baþlatýcý listesinde, yalnýzca doðrudan baþlatma biçimlerini kullanabiliriz, kopya baþlatma deðil).

Gereksiz Kopyalar
-----------------
Bu basit programý düþünün:

                #include <iostream>

                class Something
                {
                    int m_x{};

                public:
                    Something(int x)
                        : m_x{ x }
                    {
                        std::cout << "Normal constructor\n";
                    }

                    Something(const Something& s)
                        : m_x { s.m_x }
                    {
                        std::cout << "Copy constructor\n";
                    }

                    void print() const { std::cout << "Something(" << m_x << ")\n"; }
                };

                int main()
                {
                    Something s { Something { 5 } }; // bu satýra odaklanýn
                    s.print();

                    return 0;
                }

Yukarýdaki s deðiþkeninin baþlatýlmasýnda, önce deðeri 5 olan bir geçici Something oluþturuyoruz (bu, Something(int) yapýcýsýný
kullanýr). Bu geçici daha sonra s'yi baþlatmak için kullanýlýr. Geçici ve s'nin ayný türde olmasý (her ikisi de Something
nesneleri olduðu için), Something(const Something&) kopya yapýcýsýnýn normalde burada, geçici içindeki deðerleri s'ye kopyalamak 
için çaðrýlmasý gerekirdi. Sonuç olarak, s deðeri 5 ile baþlatýlýr.

Optimizasyonlar olmadan, yukarýdaki program þunu yazdýrýr:

                Normal constructor
                Copy constructor
                Something(5)

Ancak, bu program gereksiz yere verimsizdir, çünkü iki yapýcý çaðrýsý yapmamýz gerekiyor: biri Something(int) için, diðeri
Something(const Something&) için. Yukarýdaki sonucun, aþaðýdakini yazmýþ olsaydýk ayný olacaðýný unutmayýn:

                Something s { 5 }; // yalnýzca Something(int)'i çaðýrýr, kopya yapýcý yok

Bu versiyon ayný sonucu üretir, ancak daha verimlidir, çünkü yalnýzca Something(int)'e bir çaðrý yapar (kopya yapýcýya gerek
yoktur).

Kopya Elision
-------------
Derleyicinin ifadeleri optimize etmek için yeniden yazma özgürlüðü olduðundan, derleyicinin gereksiz kopyayý optimize edip 
Something s { Something{5} };'yi baþlangýçta Something s { 5 } yazmýþ gibi ele alýp alamayacaðýný merak edebilirsiniz.

Cevap evet, ve bunu yapma sürecine kopya elision denir. Kopya elision, derleyicinin gereksiz nesne kopyalamalarýný kaldýrmasýna 
izin veren bir derleyici optimizasyon tekniðidir. Diðer bir deyiþle, derleyicinin normalde bir kopya yapýcýyý çaðýracaðý 
durumlarda, derleyici kodu yeniden yazarak kopya yapýcýya yapýlan çaðrýyý tamamen önlemekte özgürdür. Derleyici, kopya yapýcýya
yapýlan çaðrýyý optimize ederse, yapýcýnýn elided olduðunu söyleriz.

Diðer optimizasyon türlerinin aksine, kopya elision "as-if" kuralýndan muaf tutulmuþtur. Yani, kopya elision, kopya yapýcýnýn
yan etkileri olsa bile (örneðin, konsola metin yazdýrma) kopya yapýcýyý elide etmeye izin verir! Bu, kopya yapýcýlarýn
kopyalamadan baþka yan etkileri olmamasý gerektiði nedenidir - eðer derleyici kopya yapýcýya yapýlan çaðrýyý eliderse, 
yan etkiler gerçekleþmez ve programýn gözlemlenebilir davranýþý deðiþir!

Bunu yukarýdaki örnekte görebiliriz. Programý bir C++17 derleyicisinde çalýþtýrýrsanýz, aþaðýdaki sonucu üretir:

                Normal constructor
                Something(5)

Derleyici, gereksiz bir kopyayý önlemek için kopya yapýcýyý elided etmiþtir ve sonuç olarak, "Kopya yapýcý" yazdýran ifade
çalýþtýrýlmamýþtýr! Programýmýzýn gözlemlenebilir davranýþý, kopya elision nedeniyle deðiþti!

Deðerden Geçme ve Deðerden Dönme'de Kopya Elision
-------------------------------------------------
Kopya yapýcý, parametrenin ayný türdeki bir argümanýn deðerden geçtiði veya deðerden dönme kullanýldýðýnda normalde çaðrýlýr.
Ancak, belirli durumlarda, bu kopyalar elided olabilir. Aþaðýdaki program, bu durumlarýn bazýlarýný gösterir:

                #include <iostream>
                class Something
                {
                public:
                    Something() = default;
                    Something(const Something&)
                    {
                        std::cout << "Copy constructor called\n";
                    }
                };

                Something rvo()
                {
                    return Something{}; // Something() ve kopya yapýcýyý çaðýrýr
                }

                Something nrvo()
                {
                    Something s{}; // Something() çaðýrýr
                    return s;      // kopya yapýcýyý çaðýrýr
                }

                int main()
                {
                    std::cout << "Initializing s1\n";
                    Something s1 { rvo() }; // kopya yapýcýyý çaðýrýr

                    std::cout << "Initializing s2\n";
                    Something s2 { nrvo() }; // kopya yapýcýyý çaðýrýr

                        return 0;
                }

Optimizasyon olmadan, yukarýdaki program kopya yapýcýyý 4 kez çaðýrýr:

*- rvo, Something'i main'e döndürdüðünde bir kez.
*- rvo()'nun dönüþ deðeri s1'i baþlatmak için kullanýldýðýnda bir kez.
*- nrvo, s'yi main'e döndürdüðünde bir kez.
*- nrvo()'nun dönüþ deðeri s2'yi baþlatmak için kullanýldýðýnda bir kez.
Ancak, kopya elision nedeniyle, derleyicinizin bu kopya yapýcý çaðrýlarýnýn çoðunu veya tümünü elide etmesi muhtemeldir.
Visual Studio 2022, 3 durumu elider (nrvo()'nun deðerden döndüðü durumu elide etmez) ve GCC hepsini elider.

Derleyicinin ne zaman kopya elision yapacaðýný / yapmayacaðýný ezberlemeniz önemli deðildir. Sadece, derleyicinizin bunu
yapabileceði bir optimizasyon olduðunu bilin ve kopya yapýcýnýzýn çaðrýlmasýný bekliyorsanýz ve çaðrýlmazsa, muhtemelen nedeni
kopya elision'dýr.

Kopya elision hatalarý
----------------------
C++17'den önce, kopya elision kesinlikle derleyicilerin yapabileceði isteðe baðlý bir optimizasyondu. C++17'de, kopya elision bazý
durumlarda zorunlu hale geldi.

Ýsteðe baðlý elision durumlarýnda, eriþilebilir bir kopya yapýcý mevcut olmalýdýr (ör. silinmemiþ), gerçek kopya yapýcý çaðrýsý
elided olsa bile.

Zorunlu elision durumlarýnda, eriþilebilir bir kopya yapýcý mevcut olmak zorunda deðildir (diðer bir deyiþle, zorunlu elision,
kopya yapýcý silinmiþ olsa bile gerçekleþebilir).

14.16 — Dönüþtürme Yapýcýsý ve explicit anahtar kelimesi
--------------------------------------------------------
10.1 dersinde -- Ýmplicit tür dönüþümü, tür dönüþümünü ve derleyicinin gerektiði gibi bir türün deðerini baþka bir türün deðerine
implicit olarak dönüþtüreceði implicit tür dönüþümü kavramýný tanýttýk.

Bu, bize þunlarý yapma imkaný verir:

                #include <iostream>

                void printDouble(double d) // bir double parametresi var
                {
                    std::cout << d;
                }

                int main()
                {
                    printDouble(5); // bir int argümaný saðlýyoruz

                    return 0;
                }

Yukarýdaki örnekte, printDouble fonksiyonumuzun bir double parametresi var, ancak biz bir int argümaný geçiriyoruz. Parametrenin 
türü ile argümanýn türü eþleþmediðinde, derleyici argümanýn türünü parametrenin türüne dönüþtürüp dönüþtüremeyeceðini görecektir.
Bu durumda, sayýsal dönüþüm kurallarýný kullanarak, int deðeri 5, double deðeri 5.0'a dönüþtürülür ve deðeri geçtiðimiz için,
parametre d bu deðerle kopya baþlatýlýr.

Kullanýcý tanýmlý dönüþümler
----------------------------
Þimdi aþaðýdaki benzer örneði düþünün:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                public:
                    Foo(int x)
                        : m_x{ x }
                    {
                    }

                    int getX() const { return m_x; }
                };

                void printFoo(Foo f) // bir Foo parametresi var
                {
                    std::cout << f.getX();
                }

                int main()
                {
                    printFoo(5); // bir int argümaný saðlýyoruz

                    return 0;
                }

Bu versiyonda, printFoo'nun bir Foo parametresi var ama biz bir int argümaný geçiriyoruz. Bu türler eþleþmediði için, 
derleyici int deðeri 5'i bir Foo nesnesine dönüþtürmeye çalýþacak, böylece fonksiyon çaðrýlabilir.

Ýlk örnekte olduðu gibi, parametre ve argüman türlerimiz her ikisi de temel türlerdi (ve bu nedenle yerleþik sayýsal 
tanýtým/dönüþüm kurallarýný kullanarak dönüþtürülebilir), bu durumda türlerimizden biri bir program tanýmlý türdür.
C++ standardý, derleyicinin deðerleri bir program tanýmlý türe (veya ondan) nasýl dönüþtüreceðini söyleyen belirli kurallara sahip
deðildir.

Bunun yerine, derleyici, böyle bir dönüþümü gerçekleþtirmek için kullanabileceði bazý fonksiyonlarý tanýmlayýp tanýmlamadýðýmýzý 
görmek için bakar. Böyle bir fonksiyon, kullanýcý tanýmlý bir dönüþüm olarak adlandýrýlýr.

Dönüþtürme Yapýcýsý
-------------------
Yukarýdaki örnekte, derleyici int deðeri 5'i bir Foo nesnesine dönüþtürmeyi saðlayan bir fonksiyon bulacak. Bu fonksiyon,
Foo(int) yapýcýsýdýr.

Bu noktaya kadar, genellikle yapýcýlarý nesneleri açýkça oluþturmak için kullanýyoruz:

                Foo x { 5 }; // Açýkça int deðeri 5'i bir Foo'ya dönüþtür

Bunu ne yaptýðýný düþünün: bir int deðeri (5) saðlýyoruz ve karþýlýðýnda bir Foo nesnesi alýyoruz.

Bir fonksiyon çaðrýsý baðlamýnda, ayný problemi çözmeye çalýþýyoruz:

                printFoo(5); // Implicit olarak int deðeri 5'i bir Foo'ya dönüþtür

Bir int deðeri (5) saðlýyoruz ve karþýlýðýnda bir Foo nesnesi istiyoruz. Foo(int) yapýcýsý tam olarak bunun için tasarlandý!
Bu yüzden bu durumda, printFoo(5) çaðrýldýðýnda, parametre f, 5 argümanýyla Foo(int) yapýcýsý kullanýlarak kopya baþlatýlýr!
Bir implicit dönüþüm gerçekleþtirmek için kullanýlabilecek bir yapýcýya dönüþtürme yapýcýsý denir. Varsayýlan olarak, 
tüm yapýcýlar dönüþtürme yapýcýsýdýr.

Sadece bir kullanýcý tanýmlý dönüþüm uygulanabilir. Ne demek istediðimizi bir örnekle anlatalým.

Aþaðýdaki örneði düþünün:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                    }

                    const std::string& getName() const { return m_name; }
                };

                void printEmployee(Employee e) // bir Employee parametresi var
                {
                    std::cout << e.getName();
                }

                int main()
                {
                    printEmployee("Joe"); // bir string literal argümaný saðlýyoruz

                    return 0;
                }

Bu versiyonda, Foo sýnýfýmýzý bir Employee sýnýfý ile deðiþtirdik. printEmployee'ýn bir Employee parametresi var ve biz bir
C-style string literal geçiriyoruz. Ve bir dönüþtürücü yapýcýya sahibiz: Employee(std::string_view).

Bu versiyonun derlenmediðini görmek sizi þaþýrtabilir. Sebep basit: bir implicit dönüþümü gerçekleþtirmek için sadece bir 
kullanýcý tanýmlý dönüþüm uygulanabilir ve bu örnekte iki tanesi gereklidir. Öncelikle, C-style string literalimizin bir
std::string_view'a dönüþtürülmesi gerekiyor (bir std::string_view dönüþtürücü yapýcý kullanarak), ve sonra std::string_view'imizin
bir Employee'ye dönüþtürülmesi gerekiyor (Employee(std::string_view) dönüþtürücü yapýcý kullanarak).

Bu örneði çalýþtýrmanýn iki yolu vardýr:

Bir std::string_view literal kullanýn:

                int main()
                {
                    using namespace std::literals;
                    printEmployee( "Joe"sv); // þimdi bir std::string_view literal

                    return 0;
                }

Bu çalýþýr çünkü artýk sadece bir kullanýcý tanýmlý dönüþüm gereklidir (std::string_view'dan Employee'ye).

Bir Employee'yi implicit olarak oluþturmak yerine explicit olarak oluþturun:

                int main()
                {
                    printEmployee(Employee{ "Joe" });

                    return 0;
                }

Bu da çalýþýr çünkü artýk sadece bir kullanýcý tanýmlý dönüþüm gereklidir (string literal'den Employee nesnesini baþlatmak için
kullanýlan std::string_view'a). Fonksiyona explicit olarak oluþturulmuþ Employee nesnemizi geçmek, ikinci bir dönüþümün
gerçekleþmesini gerektirmez.

Bu son örnek, kullanýþlý bir tekniði ortaya çýkarýr: bir implicit dönüþümü explicit bir tanýma dönüþtürmek basittir. 
Bu dersin ilerleyen bölümlerinde bunun daha fazla örneðini göreceðiz.

Anahtar nokta þudur, Bir implicit dönüþüm, direkt liste baþlatma (veya direkt baþlatma) kullanýlarak basitçe explicit bir tanýma 
dönüþtürülebilir.

Dönüþtürücü yapýcýlar yanlýþ gittiðinde

Aþaðýdaki programý düþünün:


                #include <iostream>

                class Dollars
                {
                private:
                    int m_dollars{};

                public:
                    Dollars(int d)
                        : m_dollars{ d }
                    {
                    }

                    int getDollars() const { return m_dollars; }
                };

                void print(Dollars d)
                {
                    std::cout << "$" << d.getDollars();
                }

                int main()
                {
                    print(5);

                    return 0;
                }

print(5) çaðrýldýðýnda, Dollars(int) dönüþtürücü yapýcý, 5'i bir Dollars nesnesine dönüþtürmek için kullanýlacaktýr. Bu yüzden,
bu program þunu yazdýrýr:
                $5

Bu, çaðýrýcýnýn niyeti olabilir, ancak çaðýrýcýnýn bunu gerçekten istediðine dair herhangi bir belirti saðlamamasý nedeniyle bunu
anlamak zordur. Çaðýrýcýnýn bunun 5'i yazdýracaðýný varsaydýðý ve derleyicinin bizim int deðerimizi sessizce ve implicit olarak
bir Dollars nesnesine dönüþtürmesini, bu fonksiyon çaðrýsýný karþýlayabilecek þekilde beklemediði tamamen mümkündür.

Bu örnek basitken, daha büyük ve daha karmaþýk bir programda, derleyicinin beklenmedik bir implicit dönüþüm gerçekleþtirdiði ve
çalýþma zamanýnda beklenmedik bir davranýþa yol açtýðý oldukça kolaydýr.

print(Dollars) fonksiyonumuzun yalnýzca bir Dollars nesnesi ile çaðrýlabilmesi, herhangi bir deðerin implicit olarak Dollars'a 
dönüþtürülebileceði (özellikle int gibi temel bir tür) daha iyi olurdu. Bu, istemeden hatalarýn oluþma olasýlýðýný azaltýr.

"explicit" anahtar kelimesi
---------------------------
Bu tür sorunlarý çözmek için, bir yapýcýyý dönüþtürme yapýcýsý olarak kullanýlmamasý gerektiðini derleyiciye söylemek için
explicit anahtar kelimesini kullanabiliriz.

Bir yapýcýyý explicit yapmak iki önemli sonuç doðurur:

1- Açýk bir yapýcý, kopya baþlatma veya kopya listesi baþlatma yapmak için kullanýlamaz.
2- Açýk bir yapýcý, dolaylý dönüþümler yapmak için kullanýlamaz (çünkü bu, kopya baþlatma veya kopya listesi baþlatmayý kullanýr).

Önceki örnekteki Dollars(int) yapýcýsýný bir açýk yapýcý olacak þekilde güncelleyelim:

                #include <iostream>

                class Dollars
                {
                private:
                    int m_dollars{};

                public:
                    explicit Dollars(int d) // þimdi açýk
                        : m_dollars{ d }
                    {
                    }

                    int getDollars() const { return m_dollars; }
                };

                void print(Dollars d)
                {
                    std::cout << "$" << d.getDollars();
                }

                int main()
                {
                    print(5); // derleme hatasý çünkü Dollars(int) açýk

                    return 0;
                }

Derleyici artýk Dollars(int)'i bir dönüþtürme yapýcýsý olarak kullanamadýðý için, 5'i bir Dollars'a dönüþtürmenin bir yolunu
bulamaz. Sonuç olarak, bir derleme hatasý oluþturacaktýr.

Açýk yapýcýlar doðrudan ve liste baþlatma için kullanýlabilir

Bir açýk yapýcý hala doðrudan ve doðrudan liste baþlatma için kullanýlabilir:

                // Dollars(int)'in açýk olduðunu varsayalým
                int main()
                {
                    Dollars d1(5); // tamam
                    Dollars d2{5}; // tamam
                }
Þimdi, önceki örneðimize dönelim, burada Dollars(int) yapýcýmýzý açýk yaptýk ve bu nedenle aþaðýdaki bir derleme hatasý oluþturdu:

                print(5); // derleme hatasý çünkü Dollars(int) açýk

Peki ya aslýnda print() fonksiyonunu int deðeri 5 ile çaðýrmak istiyoruz ama yapýcý açýksa ne yapmalýyýz ? 
Çözüm basit: derleyicinin 5'i print()'e geçirilebilecek bir Dollars'a dolaylý olarak dönüþtürmesi yerine, Dollars nesnesini 
kendimiz açýkça tanýmlayabiliriz:

                print(Dollars{5}); // tamam: Dollars oluþtur ve print()'e geçir (dönüþüm gerekli deðil)

Bu, hala açýk yapýcýlarý liste baþlatma nesneleri için kullanabildiðimiz için mümkündür. Ve artýk açýkça bir Dollars 
oluþturduðumuzdan, argüman türü parametre türüyle eþleþir, bu yüzden dönüþüm gerekmez!

Bu sadece derlenir ve çalýþýr, ayrýca niyetimizi daha iyi belgeler, çünkü bu fonksiyonu bir Dollars nesnesi ile çaðýrmayý 
düþündüðümüz konusunda açýktýr.

Deðer döndürme ve açýk yapýcýlar
--------------------------------
Bir fonksiyondan bir deðer döndürdüðümüzde, bu deðer fonksiyonun dönüþ türüyle eþleþmiyorsa, dolaylý bir dönüþüm gerçekleþir.
Deðer geçirme ile ayný þekilde, bu tür dönüþümler açýk yapýcýlarý kullanamaz.

Aþaðýdaki programlar, dönüþ deðerlerinde birkaç varyasyonu ve sonuçlarýný gösterir:

                #include <iostream>

                class Foo
                {
                public:
                    explicit Foo() // not: açýk (sadece örnek olmasý için)
                    {
                    }

                    explicit Foo(int x) // not: açýk
                    {
                    }
                };

                Foo getFoo()
                {
                    // explicit Foo() durumlarý
                    return Foo{ };   // tamam
                    return { };      // hata: baþlatýcý listeyi Foo'ya dolaylý olarak dönüþtüremez

                    // explicit Foo(int) durumlarý
                    return 5;        // hata: int'i Foo'ya dolaylý olarak dönüþtüremez
                    return Foo{ 5 }; // tamam
                    return { 5 };    // hata: baþlatýcý listeyi Foo'ya dolaylý olarak dönüþtüremez
                }

                int main()
                {
                    return 0;
                }

Belki de þaþýrtýcý bir þekilde, return { 5 } bir dönüþüm olarak kabul edilir.

"explicit" kullanýmý için en iyi uygulamalar
--------------------------------------------
Modern en iyi uygulama, tek bir argüman kabul edecek herhangi bir yapýlandýrýcýyý varsayýlan olarak açýk yapmaktýr. 
Bu, çoðu veya tümü varsayýlan deðerlere sahip olan birden fazla parametreli yapýlandýrýcýlarý içerir.

Bu, derleyicinin bu yapýlandýrýcýyý implicit dönüþümler için kullanmasýný engeller. Bir dönüþüm gerekiyorsa, yalnýzca açýk olmayan
yapýlandýrýcýlar dikkate alýnýr. Dönüþümü gerçekleþtirmek için hiçbir açýk olmayan yapýlandýrýcý bulunamazsa, derleyici hata verir

Böyle bir dönüþümün belirli bir durumda gerçekten istenmesi durumunda, implicit dönüþümü liste baþlatma kullanarak açýk bir tanýma
dönüþtürmek basittir.

Aþaðýdakiler açýk yapýlmamalýdýr:

*- Kopya (ve taþýma) yapýlandýrýcýlarý (çünkü bunlar dönüþüm gerçekleþtirmez).
*- Parametresi olmayan varsayýlan yapýlandýrýcýlar (çünkü bunlar yalnýzca {}'yi varsayýlan bir nesneye dönüþtürmek için kullanýlýr,
   kýsýtlamamýz gereken bir þey deðil).
*- Yalnýzca birden çok argüman kabul eden yapýlandýrýcýlar (çünkü bunlar genellikle dönüþümler için aday deðildir).
*- Tek argümanlý bir yapýlandýrýcýyý açýk olmayan yapmak anlamlý olduðu bazý durumlar vardýr. Aþaðýdakilerin tümü doðru olduðunda
   bu yararlý olabilir:

*- Dönüþtürülen deðer, argüman deðeri ile semantik olarak eþdeðerdir.
*- Dönüþüm performanslýdýr.
*- Örneðin, bir C-stil dize argümanýný kabul eden std::string_view yapýlandýrýcýsý açýk deðildir, çünkü bir C-stil dizenin bir
   std::string_view olarak kabul edilmesi durumunda sorun olmayacaðý olasý bir durum olmasý pek olasý deðildir.

Buna karþýlýk, bir std::string_view alýrken std::string yapýlandýrýcýsý açýk olarak iþaretlenmiþtir, çünkü bir std::string deðeri bir std::string_view deðeri ile semantik olarak eþdeðer olsa da, bir std::string oluþturmak performanslý deðildir.
*** BEST -> Tek bir argüman kabul eden herhangi bir yapýlandýrýcýyý varsayýlan olarak açýk yapýn. Eðer türler arasýnda 
            hem semantik olarak eþdeðer hem de performanslý bir implicit dönüþüm varsa, yapýlandýrýcýyý açýk olmayan yapmayý 
            düþünebilirsiniz. Kopya veya taþýma yapýlandýrýcýlarýný açýk yapmayýn, çünkü bunlar dönüþüm gerçekleþtirmez.

14.x - Bölüm 14 özeti
---------------------
Bu bölümde, C++'ýn etini keþfettik - sýnýflar! Bu, öðretici serideki en önemli bölümdür, çünkü geriye kalan çok þey için sahneyi 
hazýrlar.

Bölüm Ýncelemesi

Ýþlemsel programlamada, odak noktamýz, program mantýðýmýzý uygulayan "prosedürler" oluþturmaktýr (C++'da bunlara fonksiyonlar 
denir). Veri nesnelerini bu fonksiyonlara geçeriz, bu fonksiyonlar veriler üzerinde iþlemler gerçekleþtirir ve ardýndan potansiyel
olarak bir sonuç döndürürler.

Nesne yönelimli programlama (genellikle OOP olarak kýsaltýlýr) ile odak noktamýz, hem özellikler hem de iyi tanýmlanmýþ 
davranýþlar içeren program tanýmlý veri türleri oluþturmaktýr.

Bir sýnýf deðiþmezi, bir nesnenin geçerli bir durumda kalmasý için nesnenin ömrü boyunca doðru olmasý gereken bir durumdur.
Sýnýf deðiþmezliði ihlal edilmiþ bir nesne, geçersiz bir durumda olduðu söylenir ve bu nesnenin daha fazla kullanýlmasýndan 
beklenmedik veya tanýmsýz davranýþlar ortaya çýkabilir.

Bir sýnýf, hem veri hem de bu veri üzerinde çalýþan fonksiyonlarý paketleyen bir program tanýmlý bileþik türdür.

Bir sýnýf türüne ait olan fonksiyonlara üye fonksiyonlar denir. Üye fonksiyonun çaðrýldýðý nesne genellikle implicit nesne olarak
adlandýrýlýr. Üye fonksiyon olmayan fonksiyonlara, üye fonksiyonlardan ayýrt etmek için üye olmayan fonksiyonlar denir. 
Eðer sýnýf türünüzün veri üyeleri yoksa, bir ad alaný kullanmayý tercih edin.

Bir const üye fonksiyonu, nesneyi deðiþtirmeyeceðini veya herhangi bir const olmayan üye fonksiyonu çaðýrmayacaðýný 
(çünkü bunlar nesneyi deðiþtirebilir) garanti eden bir üye fonksiyondur. Bir üye fonksiyon, nesnenin durumunu deðiþtirmiyor 
(ve asla deðiþtirmeyecek) ise, const yapýlmalýdýr, böylece hem const olmayan hem de const nesneler üzerinde çaðrýlabilir.

Bir sýnýf türünün her bir üyesinin, o üyeye kimlerin eriþebileceðini belirleyen bir eriþim düzeyi adý verilen bir özelliði vardýr.
Eriþim düzeyi sistemi bazen gayri resmi olarak eriþim kontrolleri olarak adlandýrýlýr. Eriþim düzeyleri, sýnýf bazýnda tanýmlanýr,
nesne bazýnda deðil.

Public üyeler, eriþimleri üzerinde herhangi bir kýsýtlama olmayan bir sýnýf türünün üyeleridir. Public üyelere herkes tarafýndan
eriþilebilir (kapsamlarý sürece). Bu, ayný sýnýfýn diðer üyelerini de içerir. Public üyelere ayrýca public tarafýndan da
eriþilebilir, bu da belirli bir sýnýf türünün üyeleri dýþýnda var olan kodu ifade eder. Public'in örnekleri arasýnda üye olmayan 
fonksiyonlar ve diðer sýnýf türlerinin üyeleri bulunur.

Varsayýlan olarak, bir struct'ýn tüm üyeleri public üyelerdir.

Private üyeler, yalnýzca ayný sýnýfýn diðer üyeleri tarafýndan eriþilebilen bir sýnýf türünün üyeleridir.

Varsayýlan olarak, bir sýnýfýn üyeleri private'dir. Private üyelere sahip bir sýnýf artýk bir topluluk deðildir ve bu nedenle 
topluluk baþlatmasýný kullanamaz. Private üyelerinizi, onlarý yerel deðiþkenlerin, fonksiyon parametrelerinin ve üye
fonksiyonlarýnýn adlarýndan ayýrt etmeye yardýmcý olmak için "m_" önekiyle baþlayacak þekilde adlandýrmayý düþünün.

Üyelerimizin eriþim düzeyini, bir eriþim belirleyici kullanarak açýkça belirleyebiliriz. Struct'lar genellikle eriþim 
belirleyicilerini kullanmaktan kaçýnmalýdýr, böylece tüm üyeler varsayýlan olarak public olur.

Bir eriþim fonksiyonu, private bir üye deðiþkenin deðerini almak veya deðiþtirmek olan basit bir public üye fonksiyonudur.
Eriþim fonksiyonlarý iki çeþittir: getter'lar ve setter'lar. Getter'lar (bazen eriþim saðlayýcýlar olarak da adlandýrýlýr)
private bir üye deðiþkenin deðerini döndüren public üye fonksiyonlarýdýr. Setter'lar (bazen deðiþtiriciler olarak da adlandýrýlýr)
private bir üye deðiþkenin deðerini ayarlayan public üye fonksiyonlarýdýr.

Bir sýnýf türünün arayüzü, bir sýnýf türünün kullanýcýsýnýn sýnýf türünün nesneleriyle nasýl etkileþime gireceðini tanýmlar.
Yalnýzca public üyelere sýnýf türünün dýþýndan eriþilebildiðinden, bir sýnýf türünün public üyeleri arayüzünü oluþturur. 
Bu nedenle, public üyelerden oluþan bir arayüz bazen public arayüz olarak adlandýrýlýr.

Bir sýnýf türünün uygulamasý, sýnýfýn amaçlandýðý gibi davranmasýný saðlayan kodu içerir. Bu, hem veri depolayan üye deðiþkenleri 
hem de program mantýðýný içeren ve üye deðiþkenleri manipüle eden üye fonksiyonlarýnýn gövdelerini içerir.

Programlamada, veri gizleme (ayný zamanda bilgi gizleme veya veri soyutlama olarak da adlandýrýlýr) bir tekniktir ve
kullanýcýlarýn bir program tanýmlý veri türünün uygulamasýný gizleyerek arayüz ve uygulamanýn ayrýmýný saðlar.

Encapsulation terimi bazen veri gizlemeyi ifade etmek için de kullanýlýr. Ancak, bu terim ayný zamanda verilerin ve fonksiyonlarýn
bir araya getirilmesini (eriþim kontrollerine bakýlmaksýzýn) ifade etmek için de kullanýlýr, bu yüzden kullanýmý belirsiz olabilir

Bir sýnýf tanýmlarken, public üyelerinizi ilk olarak ve private üyelerinizi son olarak bildirmeyi tercih edin. Bu, public arayüzü
öne çýkarýr ve uygulama ayrýntýlarýný önemsizleþtirir.

Bir constructor, sýnýf türü nesnelerini baþlatmak için kullanýlan özel bir üye fonksiyondur. Bir non-aggregate sýnýf türü nesnesi
oluþturmak için eþleþen bir constructor bulunmalýdýr.

Üye baþlatýcý listesi, bir constructor içinde üye deðiþkenlerinizi baþlatmanýza olanak saðlar. Üye baþlatýcý listesindeki üye 
deðiþkenler, sýnýfta tanýmlandýklarý sýraya göre listelenmelidir. Üyelerinizi baþlatmak için üye baþlatýcý listesini kullanmayý,
constructor'ýn gövdesinde deðerler atamaya tercih edin.

Parametre almayan bir yapýcý (veya tüm varsayýlan parametrelere sahip olan) varsayýlan yapýcý olarak adlandýrýlýr.
Varsayýlan yapýcý, kullanýcý tarafýndan baþlatma deðerleri saðlanmadýðýnda kullanýlýr. Bir topluluk olmayan sýnýf türü nesnesinin
kullanýcý tarafýndan bildirilen yapýcýlarý yoksa, derleyici bir varsayýlan yapýcý oluþturur (böylece sýnýf deðer veya varsayýlan
baþlatma yapýlabilir). Bu yapýcýya dolaylý varsayýlan yapýcý denir.

Yapýcýlar, baþlatmayý ayný sýnýf türünden baþka bir yapýcýya devretmeye izin verir. Bu sürece bazen yapýcý zincirleme denir ve bu
tür yapýcýlara devreden yapýcýlar denir. Yapýcýlar devredebilir veya baþlatabilir, ancak her ikisini birden yapamazlar.

Geçici bir nesne (bazen anonim nesne veya isimsiz nesne olarak adlandýrýlýr) ismi olmayan ve yalnýzca tek bir ifade süresince var
olan bir nesnedir.

Bir kopya yapýcýsý, bir nesneyi ayný türden mevcut bir nesne ile baþlatmak için kullanýlan bir yapýcýdýr. Sýnýflarýnýz için bir 
kopya yapýcýsý saðlamazsanýz, C++ sizin için üye baþlatma yapan genel bir dolaylý kopya yapýcýsý oluþturur.

As-if kuralý, derleyicinin bir programý daha optimize bir kod üretmek için istediði gibi deðiþtirebileceðini söyler, yeter ki bu
deðiþiklikler bir programýn "gözlemlenebilir davranýþýný" etkilemesin. As-if kuralýnýn bir istisnasý kopya elizyondur. Kopya 
elizyon, derleyicinin gereksiz nesne kopyalamalarýný kaldýrmasýna izin veren bir derleyici optimizasyon tekniðidir. Derleyici,
kopya yapýcýya bir çaðrýyý optimize ederse, yapýcýnýn elizyon olduðunu söyleriz.

Bir deðeri bir program tanýmlý türüne dönüþtürmek için yazdýðýmýz bir fonksiyon, kullanýcý tanýmlý dönüþüm olarak adlandýrýlýr.
Dolaylý bir dönüþüm gerçekleþtirmek için kullanýlabilecek bir yapýcýya dönüþtürme yapýcýsý denir. Varsayýlan olarak, tüm yapýcýlar
dönüþtürme yapýcýsýdýr.

Derleyiciye bir yapýcýnýn dönüþtürme yapýcýsý olarak kullanýlmamasý gerektiðini söylemek için "explicit" anahtar kelimesini 
kullanabiliriz. Böyle bir yapýcý, kopya baþlatma veya kopya listesi baþlatma yapmak için kullanýlamaz, ayrýca dolaylý dönüþümler 
yapmak için de kullanýlamaz.

Tek bir argüman kabul eden herhangi bir yapýcýyý varsayýlan olarak explicit yapýn. Eðer türler arasýnda hem semantik olarak
eþdeðer hem de performanslý bir dolaylý dönüþüm varsa (std::string'den std::string_view'a dönüþüm gibi), yapýcýyý açýk olmayan
yapmayý düþünebilirsiniz. Kopya veya taþýma yapýcýlarý açýk yapmayýn, çünkü bunlar dönüþüm yapmaz.
*/