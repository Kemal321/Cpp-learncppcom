#include <iostream>
class Deneme {
private: 
    int m_x{};
    int m_y{};
public:
    
    Deneme(int x = 0, int y = 0)  
        :m_x{ x }, m_y{ y }
    {
        std::cout << "baslatici(" << x << ", " << y << ") constructed\n";
    }
    void kontrol() {
            std::cout << "baslatici(" << m_x << "," << m_y << ")\n";
    }
};
int main()
{
    Deneme denem{};
    denem.kontrol();
    return 0;
}
/*
Bir sýnýf tipi bir topluluk olduðunda, sýnýf tipini doðrudan toplu baþlatma ile baþlatabiliriz:

                struct Foo // Foo bir topluluktur
                {
                    int x {};
                    int y {};
                };

                int main()
                {
                    Foo foo { 6, 7 }; // toplu baþlatmayý kullanýr

                    return 0;
                }

Toplu baþlatma, üyeleri baþlatmayý üye bazýnda yapar (üyeler tanýmlandýklarý sýrayla baþlatýlýr). Bu yüzden yukarýdaki örnekte foo
örneklendiðinde, foo.x 6'ya ve foo.y 7'ye baþlatýlýr. Ancak, herhangi bir üye deðiþkenini private yapar yapmaz (verilerimizi 
gizlemek için), sýnýf tipimiz artýk bir topluluk deðildir (çünkü topluluklar private üyelere sahip olamaz). Ve bu, artýk toplu 
baþlatmayý kullanamayacaðýmýz anlamýna gelir:

                class Foo // Foo bir topluluk deðildir (private üyelere sahip)
                {
                    int m_x {};
                    int m_y {};
                };

                int main()
                {
                    Foo foo { 6, 7 }; // derleme hatasý: toplu baþlatma kullanýlamaz

                    return 0;
                }
Private üyelere sahip sýnýf tiplerinin toplu baþlatma ile baþlatýlmasýna izin verilmemesi, bir dizi nedenle mantýklýdýr:

Toplu baþlatma, sýnýfýn uygulamasý hakkýnda bilgi gerektirir (çünkü üyelerin ne olduðunu ve hangi sýrayla tanýmlandýðýný
bilmelisiniz), ki bu, veri üyelerimizi gizlediðimizde kasýtlý olarak kaçýnmaya çalýþtýðýmýz bir þeydir. Eðer sýnýfýmýzýn bazý
türden deðiþmezleri olsaydý, kullanýcýnýn sýnýfý, deðiþmezi koruyacak bir þekilde baþlatmasýna güveniyor olurduk. Peki private üye
deðiþkenlere sahip bir sýnýfý nasýl baþlatýrýz? Önceki örnekte derleyici tarafýndan verilen hata mesajý bir ipucu saðlar:
“hata: ‘Foo’ baþlatmasý için eþleþen bir yapýlandýrýcý yok”

Eþleþen bir yapýlandýrýcýya ihtiyacýmýz olmalý. Ama bu ne demek?

Yapýlandýrýcýlar ( Constructor )
--------------------------------
Bir yapýlandýrýcý, bir topluluk olmayan bir sýnýf tipi nesnesi oluþturulduktan sonra otomatik olarak çaðrýlan özel bir üye
fonksiyonudur. Bir topluluk olmayan bir sýnýf tipi nesnesi tanýmlandýðýnda, derleyici, çaðýranýn saðladýðý baþlatma deðerleri 
(varsa) için eriþilebilir bir eþleþen yapýlandýrýcý bulup bulamayacaðýný görmek için bakar.

Eðer eriþilebilir bir eþleþen yapýlandýrýcý bulunursa, nesne için bellek ayrýlýr ve sonra yapýlandýrýcý fonksiyonu çaðrýlýr.
Eðer eriþilebilir bir eþleþen yapýlandýrýcý bulunamazsa, bir derleme hatasý oluþturulur.

Ana Fikir þudur ki, Birçok yeni programcý, yapýlandýrýcýlarýn nesneleri oluþturup oluþturmadýðý konusunda karýþýklýða düþer. 
Onlar oluþturmaz -- derleyici, yapýlandýrýcý çaðrýsýndan önce nesne için bellek ayýrýmýný ayarlar. Yapýlandýrýcý daha sonra 
baþlatýlmamýþ nesne üzerinde çaðrýlýr.

Ancak, bir dizi baþlatýcý için eþleþen bir yapýlandýrýcý bulunamazsa, derleyici hata verir. Yani yapýlandýrýcýlar nesneleri 
oluþturmaz, ancak eþleþen bir yapýlandýrýcýnýn eksikliði bir nesnenin oluþturulmasýný engeller.

Bir nesnenin nasýl oluþturulabileceðini belirlemenin ötesinde, yapýlandýrýcýlar genellikle iki iþlevi yerine getirir:

*- Genellikle üye deðiþkenlerinin baþlatýlmasýný gerçekleþtirirler (bir üye baþlatma listesi aracýlýðýyla)
*- Diðer kurulum iþlevlerini gerçekleþtirebilirler (yapýlandýrýcýnýn gövdesindeki ifadeler aracýlýðýyla). Bu, baþlatma 
   deðerlerinin hata kontrolünü, bir dosyanýn veya veritabanýnýn açýlmasýný vb. içerebilir...
   Yapýlandýrýcý yürütmeyi bitirdikten sonra, nesnenin "oluþturulduðunu" söyleriz ve nesne artýk tutarlý, kullanýlabilir bir durumda
   olmalýdýr.

Not edin ki topluluklarýn yapýlandýrýcýlara sahip olmasýna izin verilmez -- yani bir topluluða bir yapýlandýrýcý eklerseniz,
artýk bir topluluk olmaz.

Yapýlandýrýcýlarýn Adlandýrýlmasý
---------------------------------
Normal üye fonksiyonlarýn aksine, yapýlandýrýcýlar adlandýrýlmalýdýr:

Yapýlandýrýcýlar, sýnýf ile ayný ada (ayný büyük/küçük harf kullanýmýyla) sahip olmalýdýr. Þablon sýnýflar için bu ad, þablon 
parametrelerini içermez.

Yapýlandýrýcýlarýn dönüþ tipi yoktur (hatta void bile deðil).
Yapýlandýrýcýlar genellikle sýnýfýnýzýn arayüzünün bir parçasýdýr, bu yüzden genellikle public olurlar.

Temel Bir Yapýlandýrýcý Örneði
------------------------------
Yukarýdaki örneðimize temel bir yapýlandýrýcý ekleyelim:
                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo(int x, int y) // iki baþlatýcý alan yapýlandýrýcý fonksiyonumuz burada
                    {
                        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 }; // Foo(int, int) yapýlandýrýcýsýný çaðýrýr
                    foo.print();

                    return 0;
                }

Bu program artýk derlenecek ve sonucu üretecek:

                Foo(6, 7) constructed
                Foo(0, 0)
Derleyici Foo foo{ 6, 7 } tanýmýný gördüðünde, iki int argümaný kabul edecek bir Foo yapýlandýrýcýsý arar. Foo(int, int) bir 
eþleþmedir, bu yüzden derleyici tanýma izin verir.

Çalýþma zamanýnda, foo örneklendiðinde, foo için bellek ayrýlýr ve ardýndan Foo(int, int) yapýlandýrýcýsý, x parametresi 6'ya ve
y parametresi 7'ye baþlatýlarak çaðrýlýr. Yapýlandýrýcý fonksiyonunun gövdesi daha sonra yürütülür ve Foo(6, 7) constructed yazar.

Print() üye fonksiyonunu çaðýrdýðýmýzda, m_x ve m_y üyelerinin deðeri 0 olduðunu not edeceksiniz. Bu, Foo(int, int) yapýlandýrýcý
fonksiyonumuz çaðrýldý, ancak aslýnda üyeleri baþlatmadý. Bunu nasýl yapacaðýmýzý bir sonraki derste göstereceðiz.

Yapýlandýrýcý Argümanlarýnýn Implicit Dönüþümü
----------------------------------------------
Ders 10.1 -- Implicit Tür Dönüþümü'nde, derleyicinin bir fonksiyon çaðrýsýndaki argümanlarýn implicit dönüþümünü 
gerçekleþtireceðini belirttik (gerekirse), parametrelerin farklý bir tür olduðu bir fonksiyon tanýmýna uyacak þekilde:

                void foo(int, int)
                {
                }

                int main()
                {
                    foo('a', true); // foo(int, int) ile eþleþir

                    return 0;
                }
Bu, yapýlandýrýcýlar için de farklý deðildir: Foo(int, int) yapýlandýrýcýsý, argümanlarýnýn int'e implicit dönüþtürülebilir olduðu
herhangi bir çaðrýyla eþleþir:

                class Foo
                {
                public:
                    Foo(int x, int y)
                    {
                    }
                };

                int main()
                {
                    Foo foo{ 'a', true }; // Foo(int, int) yapýlandýrýcýsý ile eþleþir

                    return 0;
                }

Yapýlandýrýcýlar const Olmamalýdýr
----------------------------------
Bir yapýlandýrýcýnýn, oluþturulan nesneyi baþlatabilmesi gereklidir -- bu nedenle, bir yapýlandýrýcý const olmamalýdýr.

                #include <iostream>

                class Something
                {
                private:
                    int m_x{};

                public:
                    Something() // yapýlandýrýcýlar const olmamalýdýr
                    {
                        m_x = 5; // const olmayan yapýlandýrýcýda üyeleri deðiþtirmek tamam
                    }

                    int getX() const { return m_x; } // const
                };

                int main()
                {
                    const Something s{}; // const nesne, implicit olarak (const olmayan) yapýlandýrýcýyý çaðýrýr

                    std::cout << s.getX(); // 5 yazar

                    return 0;
                }
Normalde bir const olmayan üye fonksiyonu, bir const nesne üzerinde çaðrýlamaz. Ancak, yapýlandýrýcý implicit olarak çaðrýldýðý
için, bir const nesne üzerinde const olmayan bir yapýlandýrýcý çaðrýlabilir.

Yapýlandýrýcýlar vs Ayarlayýcýlar ( setter lar )
------------------------------------------------
Yapýlandýrýcýlar, bir nesnenin tümünü oluþturma anýnda baþlatmak üzere tasarlanmýþtýr. Ayarlayýcýlar, mevcut bir nesnenin tek bir 
üyesine bir deðer atamak üzere tasarlanmýþtýr.

14.10 — Üye Baþlatma Listeleri ile Yapýlandýrýcýlar
---------------------------------------------------
Üye Baþlatma, bir Üye Baþlatma Listesi ile
------------------------------------------
Bir yapýlandýrýcýnýn üyeleri baþlatmasýný saðlamak için, bir üye baþlatma listesi (genellikle "üye baþlatma listesi" olarak
adlandýrýlýr) kullanýrýz. Bu terimi, bir deðerler listesi ile topluluklarý baþlatmak için kullanýlan "baþlatýcý listesi" ile
karýþtýrmayýn.

Üye baþlatma listeleri, en iyi þekilde örnek üzerinden öðrenilir. Aþaðýdaki örnekte, Foo(int, int) yapýlandýrýcýmýz, m_x ve m_y'yi
baþlatmak için bir üye baþlatma listesi kullanacak þekilde güncellenmiþtir:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo(int x, int y)
                        : m_x { x }, m_y { y } // iþte üye baþlatma listemiz
                    {
                        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
Üye baþlatma listesi, yapýlandýrýcý parametrelerinden sonra tanýmlanýr. Bir iki nokta üst üste (:) ile baþlar ve ardýndan baþlatma
deðeri ile birlikte baþlatýlacak her üyeyi listeler, virgülle ayrýlýr. Burada doðrudan bir baþlatma formu kullanmalýsýnýz 
(tercihen süslü parantezler kullanarak, ancak parantezler de iþe yarar) -- eþittir ile kopya baþlatma burada iþe yaramaz. Ayrýca 
üye baþlatma listesinin bir noktalý virgülle sona ermediðini unutmayýn.

Bu program aþaðýdaki çýktýyý üretir:

                Foo(6, 7) constructed
                Foo(6, 7)
Foo örneklendiðinde, baþlatma listesindeki üyeler belirtilen baþlatma deðerleri ile baþlatýlýr. Bu durumda, üye baþlatma listesi
m_x'i x'in deðeri olan 6'ya ve m_y'yi y'nin deðeri olan 7'ye baþlatýr. Ardýndan yapýlandýrýcýnýn gövdesi çalýþýr.

Print() üye fonksiyonunu çaðýrdýðýnýzda, m_x'in hala 6 deðerine ve m_y'nin hala 7 deðerine sahip olduðunu görebilirsiniz.

Üye Baþlatma Listesi Biçimlendirme
----------------------------------
C++, üye baþlatma listelerinizi tercih ettiðiniz gibi biçimlendirmeniz için size çok fazla özgürlük saðlar, çünkü iki nokta üst
üste, virgül veya boþluklarýnýzý nereye koyduðunuz konusunda umursamaz.
Aþaðýdaki stiller tümü geçerlidir (ve uygulamada hepsini görmek olasýdýr):

                Foo(int x, int y) : m_x { x }, m_y { y }
                {
                }
                Foo(int x, int y) :
                    m_x { x },
                    m_y { y }
                {
                }
                Foo(int x, int y)
                    : m_x { x }
                    , m_y { y }
                {
                }
Önerimiz, yukarýdaki üçüncü stili kullanmaktýr:

Ýki nokta üst üsteyi, yapýlandýrýcý adýndan sonraki satýra koyun, çünkü bu, üye baþlatma listesini fonksiyon prototipinden temiz 
bir þekilde ayýrýr. Üye baþlatma listenizi girintili yapýn, fonksiyon adlarýný görmeyi kolaylaþtýrýr. Eðer üye baþlatma listesi
kýsa/trivial ise, tüm baþlatýcýlar tek bir satýrda olabilir:

                Foo(int x, int y)
                    : m_x { x }, m_y { y }
                {
                }
Aksi takdirde (veya tercih ederseniz), her üye ve baþlatýcý çifti ayrý bir satýra konabilir (hizalamayý korumak için virgülle 
baþlayarak):

                Foo(int x, int y)
                    : m_x { x }
                    , m_y { y }
                {
                }

Üye Baþlatma Sýrasý
-------------------
C++ standardýna göre, bir üye baþlatma listesindeki üyeler her zaman sýnýf içinde tanýmlandýklarý sýraya göre baþlatýlýr (üye
baþlatma listesinde tanýmlandýklarý sýraya deðil).

Yukarýdaki örnekte, m_x sýnýf tanýmýnda m_y'den önce tanýmlandýðý için, m_x ilk olarak baþlatýlýr (üye baþlatma listesinde
ilk sýrada listelenmemiþ olsa bile).

Deðiþkenlerin intuitif olarak soldan saða baþlatýlmasýný beklediðimiz için, bu, ince hatalarýn oluþmasýna neden olabilir.
Aþaðýdaki örneði düþünün:

                #include <algorithm> // std::max için
                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    Foo(int x, int y)
                        : m_y{ std::max(x, y) }, m_x{ m_y } // bu satýrda sorun var
                    {
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
Yukarýdaki örnekte, amacýmýz, geçirilen baþlatma deðerlerinin daha büyüðünü hesaplamak (std::max(x, y) aracýlýðýyla) ve bu deðeri 
hem m_x hem de m_y'yi baþlatmak için kullanmaktýr. Ancak, yazarýn makinesinde, aþaðýdaki sonuç yazdýrýlýr:

                Foo(-858993460, 7)
Ne oldu? M_y, üye baþlatma listesinde ilk sýrada listelenmiþ olsa bile, m_x sýnýfta ilk tanýmlandýðý için, m_x ilk olarak 
baþlatýlýr. Ve m_x, henüz baþlatýlmamýþ olan m_y'nin deðerine baþlatýlýr. Son olarak, m_y, baþlatma deðerlerinin daha büyüðüne 
baþlatýlýr.

Bu tür hatalarý önlemek için, üye baþlatma listesindeki üyeler, sýnýfta tanýmlandýklarý sýraya göre listelenmelidir. Üyelerin 
sýrasý dýþýnda baþlatýlmasý durumunda, bazý derleyiciler bir uyarý verecektir.

*** BEST -> Bir üye baþlatma listesindeki üye deðiþkenler, sýnýfta tanýmlandýklarý sýraya göre listelenmelidir.

Ayrýca, üyeleri diðer üyelerin deðerini kullanarak baþlatmaktan kaçýnmak da iyi bir fikirdir (mümkünse). Bu þekilde, baþlatma
sýrasýnda bir hata yaparsanýz, baþlatma deðerleri arasýnda hiçbir baðýmlýlýk olmadýðý için önemli olmamalýdýr.

Üye Baþlatma Listesi vs Varsayýlan Üye Baþlatýcýlarý
----------------------------------------------------
Üyeler, birkaç farklý þekilde baþlatýlabilir:

Bir üye, üye baþlatma listesinde listelenmiþse, o baþlatma deðeri kullanýlýr
Aksi takdirde, üyenin bir varsayýlan üye baþlatýcýsý varsa, o baþlatma deðeri kullanýlýr
Aksi takdirde, üye varsayýlan olarak baþlatýlýr.
Bu, bir üyenin hem bir varsayýlan üye baþlatýcýsý hem de yapýlandýrýcý için üye baþlatma listesinde listelenmiþse, üye baþlatma
listesi deðeri önceliði alýr demektir.

Ýþte tüm üç baþlatma yöntemini gösteren bir örnek:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};    // varsayýlan üye baþlatýcý (göz ardý edilecek)
                    int m_y{ 2 }; // varsayýlan üye baþlatýcý (kullanýlacak)
                    int m_z;      // baþlatýcý yok

                public:
                    Foo(int x)
                        : m_x{ x } // üye baþlatma listesi
                    {
                        std::cout << "Foo constructed\n";
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6 };
                    foo.print();

                    return 0;
                }

Yazarýn makinesinde, bu çýktýyý verir:

                Foo constructed
                Foo(6, 2, -858993460)
Ýþte burada olanlar. Foo oluþturulduðunda, yalnýzca m_x üye baþlatma listesinde görünür, bu yüzden m_x ilk olarak 6'ya baþlatýlýr.
M_y, üye baþlatma listesinde deðildir, ancak bir varsayýlan üye baþlatýcýsý vardýr, bu yüzden 2'ye baþlatýlýr. M_z ne üye baþlatma
listesinde ne de varsayýlan bir üye baþlatýcýsý vardýr, bu yüzden varsayýlan olarak baþlatýlýr (ki bu, temel tipler için,
baþlatýlmamýþ olduðu anlamýna gelir). Bu yüzden, m_z'nin deðerini yazdýrdýðýmýzda, tanýmlanmamýþ davranýþ elde ederiz.

Yapýlandýrýcý Fonksiyon Gövdeleri
---------------------------------
Yapýlandýrýcý fonksiyonlarýn gövdeleri genellikle boþ býrakýlýr. Bunun nedeni, yapýlandýrýcýyý çoðunlukla baþlatma için
kullanmamýzdýr, bu da üye baþlatma listesi aracýlýðýyla yapýlýr. Eðer yapmamýz gereken tek þey bu ise, yapýlandýrýcýnýn gövdesinde
herhangi bir ifadeye ihtiyacýmýz yoktur.

Ancak, yapýlandýrýcýnýn gövdesindeki ifadeler, üye baþlatma listesi yürütüldükten sonra yürütülür, bu yüzden baþka herhangi bir 
kurulum görevi gerektiren ifadeler ekleyebiliriz. Yukarýdaki örneklerde, yapýlandýrýcýnýn yürütüldüðünü göstermek için konsola
bir þeyler yazdýrýyoruz, ancak baþka þeyler de yapabilirdik, örneðin bir dosya veya veritabaný açabilir, bellek ayýrabiliriz,vb...

Yeni programcýlar bazen yapýlandýrýcýnýn gövdesini üyelere deðer atamak için kullanýr:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    Foo(int x, int y)
                    {
                        m_x = x; // yanlýþ: bu bir atama, baþlatma deðil
                        m_y = y; // yanlýþ: bu bir atama, baþlatma deðil
                    }

                    void print() const
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
                    }
                };

                int main()
                {
                    Foo foo{ 6, 7 };
                    foo.print();

                    return 0;
                }
Bu basit durumda bu, beklenen sonucu verecektir, ancak üyelerin baþlatýlmasý gerektiði durumlarda (örneðin, const veya referans
olan veri üyeleri için) atama iþlemi çalýþmayacaktýr.
*** BEST -> Üyelerinizi baþlatmak için üye baþlatma listesini kullanmayý, yapýlandýrýcýnýn gövdesinde deðer atamayý tercih edin.

14.11 — Varsayýlan Yapýlandýrýcýlar ve Varsayýlan Argümanlar
------------------------------------------------------------
Bir varsayýlan yapýlandýrýcý, hiçbir argüman kabul etmeyen bir yapýlandýrýcýdýr. Genellikle, bu, hiçbir parametre ile tanýmlanmýþ
bir yapýlandýrýcýdýr.

Ýþte varsayýlan bir yapýlandýrýcýya sahip bir sýnýfýn örneði:

                #include <iostream>

                class Foo
                {
                public:
                    Foo() // varsayýlan yapýlandýrýcý
                    {
                        std::cout << "Foo default constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // Hiçbir baþlatma deðeri yok, Foo'nun varsayýlan yapýlandýrýcýsýný çaðýrýr

                    return 0;
                }
Yukarýdaki program çalýþtýrýldýðýnda, Foo tipinde bir nesne oluþturulur. Hiçbir baþlatma deðeri saðlanmadýðýndan, varsayýlan 
yapýlandýrýcý Foo() çaðrýlýr, bu da þunu yazdýrýr:

                Foo default constructed
Sýnýf Tipleri için Deðer Baþlatma vs Varsayýlan Baþlatma
--------------------------------------------------------
Bir sýnýf tipi bir varsayýlan yapýlandýrýcýya sahipse, hem deðer baþlatma hem de varsayýlan baþlatma varsayýlan yapýlandýrýcýyý
çaðýrýr. Bu nedenle, yukarýdaki örnekteki Foo sýnýfý gibi bir sýnýf için, aþaðýdakiler esasen eþdeðerdir:

                Foo foo{}; // deðer baþlatma, Foo() varsayýlan yapýlandýrýcýsýný çaðýrýr
                Foo foo2;  // varsayýlan baþlatma, Foo() varsayýlan yapýlandýrýcýsýný çaðýrýr

Ancak, zaten 13.7 -- Varsayýlan Üye Baþlatma dersinde ele aldýðýmýz gibi, deðer baþlatma topluluklar için daha güvenlidir.
Bir sýnýf tipinin bir topluluk olup olmadýðýný anlamak zor olduðundan, her þey için sadece deðer baþlatmayý kullanmak ve bunun 
hakkýnda endiþelenmemek daha güvenlidir.
*** BEST -> Tüm sýnýf tipleri için varsayýlan baþlatmayý deðer baþlatmaya tercih edin.

Varsayýlan Argümanlara Sahip Yapýlandýrýcýlar
---------------------------------------------
Tüm fonksiyonlarda olduðu gibi, yapýlandýrýcýlarýn en saðdaki parametreleri varsayýlan argümanlara sahip olabilir. Örneðin:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x { };
                    int m_y { };

                public:
                    Foo(int x=0, int y=0) // varsayýlan argümanlara sahip
                        : m_x { x }
                        , m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo1{};     // Foo(int, int) yapýlandýrýcýsýný varsayýlan argümanlarý kullanarak çaðýrýr
                    Foo foo2{6, 7}; // Foo(int, int) yapýlandýrýcýsýný çaðýrýr

                    return 0;
                }
                Bu, þunu yazdýrýr:

                Foo(0, 0) constructed
                Foo(6, 7) constructed
Bir yapýlandýrýcýnýn tüm parametreleri varsayýlan argümanlara sahipse, yapýlandýrýcý bir varsayýlan yapýlandýrýcýdýr
(çünkü hiçbir argüman olmadan çaðrýlabilir).

Aþýrý Yüklenmiþ Yapýlandýrýcýlar
--------------------------------
Yapýlandýrýcýlar fonksiyonlar olduðu için, aþýrý yüklenebilirler. Yani, farklý þekillerde nesneler oluþturabilmek için birden
fazla yapýlandýrýcýmýz olabilir:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() // varsayýlan yapýlandýrýcý
                    {
                        std::cout << "Foo constructed\n";
                    }

                    Foo(int x, int y) // varsayýlan olmayan yapýlandýrýcý
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo1{};     // Foo() yapýlandýrýcýsýný çaðýrýr
                    Foo foo2{6, 7}; // Foo(int, int) yapýlandýrýcýsýný çaðýrýr

                    return 0;
                }
Yukarýdakinden çýkan bir sonuç, bir sýnýfýn yalnýzca bir varsayýlan yapýlandýrýcýsý olmasý gerektiðidir. Birden fazla varsayýlan 
yapýlandýrýcý saðlanýrsa, derleyici hangisinin kullanýlacaðýný belirleyemez:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() // varsayýlan yapýlandýrýcý
                    {
                        std::cout << "Foo constructed\n";
                    }

                    Foo(int x=1, int y=2) // varsayýlan yapýlandýrýcý
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // derleme hatasý: belirsiz yapýlandýrýcý fonksiyon çaðrýsý

                    return 0;
                }
Yukarýdaki örnekte, foo'yu hiçbir argüman olmadan örneklendiriyoruz, bu yüzden derleyici bir varsayýlan yapýlandýrýcý arar. 
Ýkisini bulur ve hangi yapýlandýrýcýnýn kullanýlacaðýný belirleyemez. Bu, bir derleme hatasýna neden olur.

Implicit Varsayýlan Yapýlandýrýcý
---------------------------------
Bir topluluk olmayan bir sýnýf tipi nesnesinin kullanýcý tarafýndan bildirilen bir yapýlandýrýcýsý yoksa, derleyici bir public
varsayýlan yapýlandýrýcý oluþturur (böylece sýnýf, deðer veya varsayýlan olarak baþlatýlabilir). Bu yapýlandýrýcýya implicit 
varsayýlan yapýlandýrýcý denir.

Aþaðýdaki örneði düþünün:

                #include <iostream>

                class Foo
                {
                private:
                    int m_x{};
                    int m_y{};

                    // Not: hiçbir yapýlandýrýcý bildirilmedi
                };

                int main()
                {
                    Foo foo{};

                    return 0;
                }
Bu sýnýfýn kullanýcý tarafýndan bildirilen bir yapýlandýrýcýsý yok, bu yüzden derleyici bizim için bir implicit varsayýlan
yapýlandýrýcý oluþturur. Bu yapýlandýrýcý, foo{}'yu örneklendirmek için kullanýlýr.

Implicit varsayýlan yapýlandýrýcý, hiçbir parametresi olmayan, üye baþlatma listesi olmayan ve yapýlandýrýcýnýn gövdesinde hiçbir
ifadesi olmayan bir yapýlandýrýcýya eþdeðerdir. Diðer bir deyiþle, yukarýdaki Foo sýnýfý için, derleyici bunu oluþturur:
                public:
                    Foo() // implicit olarak oluþturulan varsayýlan yapýlandýrýcý
                    {
                    }
Implicit varsayýlan yapýlandýrýcý, çoðunlukla veri üyeleri olmayan sýnýflar için yararlýdýr. Eðer bir sýnýfýn veri üyeleri varsa,
muhtemelen onlarý kullanýcýnýn saðladýðý deðerlerle baþlatýlabilir yapmak isteyeceðiz ve implicit varsayýlan yapýlandýrýcý bunun 
için yeterli deðildir.

Varsayýlan bir Yapýlandýrýcý Oluþturmak için = default Kullanma
---------------------------------------------------------------
Varsayýlan bir yapýlandýrýcý yazacaðýmýz durumlarda, bu yapýlandýrýcý implicit olarak oluþturulan varsayýlan yapýlandýrýcýya 
eþdeðerse, derleyicinin bizim için bir implicit varsayýlan yapýlandýrýcý oluþturmasýný söyleyebiliriz. Aþaðýdaki sözdizimini 
kullanarak:
                #include <iostream>

                class Foo
                {
                private:
                    int m_x {};
                    int m_y {};

                public:
                    Foo() = default; // bir implicit varsayýlan yapýlandýrýcý oluþtur

                    Foo(int x, int y)
                        : m_x { x }, m_y { y }
                    {
                        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
                    }
                };

                int main()
                {
                    Foo foo{}; // Foo() varsayýlan yapýlandýrýcýsýný çaðýrýr

                    return 0;
                }
Yukarýdaki örnekte, kullanýcý tarafýndan bildirilen bir yapýlandýrýcýmýz var (Foo(int, int)), bu yüzden normalde bir implicit 
varsayýlan yapýlandýrýcý oluþturulmaz. Ancak, derleyiciye böyle bir yapýlandýrýcý oluþturmasýný söylediðimiz için, oluþturur. 
Bu yapýlandýrýcý, daha sonra foo{}'nun örneklendirilmesi için kullanýlýr.

Implicit Varsayýlan Yapýlandýrýcý vs Boþ Kullanýcý Yapýlandýrýcýsý
------------------------------------------------------------------
Implicit varsayýlan yapýlandýrýcýnýn boþ bir kullanýcýnýn saðladýðý yapýlandýrýcýdan farklý davrandýðý en az bir durum vardýr. 
Bir sýnýfý deðer baþlatýrken, sýnýfýn kullanýcý tarafýndan saðlanan bir varsayýlan yapýlandýrýcýsý varsa, nesne varsayýlan olarak 
baþlatýlýr. Ancak, sýnýfýn kullanýcý tarafýndan saðlanmayan bir varsayýlan yapýlandýrýcýsý varsa (yani, ya implicit tanýmlý bir 
yapýlandýrýcý veya =default kullanýlarak oluþturulan bir varsayýlan yapýlandýrýcý), nesne varsayýlan baþlatma öncesinde sýfýra
baþlatýlýr.
                #include <iostream>

                class User
                {
                private:
                    int m_a; // not: varsayýlan baþlatma deðeri yok
                    int m_b {};

                public:
                    User() {} // kullanýcý tarafýndan saðlanan boþ yapýlandýrýcý

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                class Default
                {
                private:
                    int m_a; // not: varsayýlan baþlatma deðeri yok
                    int m_b {};

                public:
                    Default() = default; // açýkça varsayýlan varsayýlan yapýlandýrýcý

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                class Implicit
                {
                private:
                    int m_a; // not: varsayýlan baþlatma deðeri yok
                    int m_b {};

                public:
                    // implicit varsayýlan yapýlandýrýcý

                    int a() const { return m_a; }
                    int b() const { return m_b; }
                };

                int main()
                {
                    User user{}; // varsayýlan baþlatýlýr
                    std::cout << user.a() << ' ' << user.b() << '\n';

                    Default def{}; // sýfýra baþlatýlýr, sonra varsayýlan baþlatýlýr
                    std::cout << def.a() << ' ' << def.b() << '\n';

                    Implicit imp{}; // sýfýra baþlatýlýr, sonra varsayýlan baþlatýlýr
                    std::cout << imp.a() << ' ' << imp.b() << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu çýktýyý verir:

                782510864 0
                0 0
                0 0
Not edin ki, user.a varsayýlan baþlatma öncesinde sýfýra baþlatýlmadý ve bu nedenle baþlatýlmamýþ oldu. Pratikte, tüm veri üyeleri
için varsayýlan üye baþlatýcýlarý saðlamanýz gerektiði için bu önemli olmamalýdýr!

*** BEST -> Boþ bir gövdeye sahip varsayýlan bir yapýlandýrýcý yerine açýkça varsayýlan bir varsayýlan yapýlandýrýcý (=default)
            tercih edin.
Yalnýzca Mantýklý Olduðunda Bir Varsayýlan Yapýlandýrýcý Oluþturun
------------------------------------------------------------------
Bir varsayýlan yapýlandýrýcý, kullanýcý tarafýndan saðlanan baþlatma deðerleri olmadan bir topluluk olmayan sýnýf tipi nesneleri 
oluþturmamýza izin verir. Bu nedenle, bir sýnýf yalnýzca bir sýnýf tipi nesnelerinin tüm varsayýlan deðerler kullanýlarak
oluþturulmasýnýn mantýklý olduðu durumlarda bir varsayýlan yapýlandýrýcý saðlamalýdýr.
Örneðin:
                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    Fraction() {}
                    Fraction(int numerator, int denominator)
                        : m_numerator{ numerator }
                        , m_denominator{ denominator }
                    {
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f1 {3, 5};
                    f1.print();

                    Fraction f2 {}; // will get Fraction 0/1
                    f2.print();

                    return 0;
                }
Bir kesiri temsil eden bir sýnýf için, kullanýcýnýn baþlatýcý olmadan Kesir nesneleri oluþturmasýna izin vermek mantýklýdýr 
(bu durumda, kullanýcý kesir 0/1'i alýr). Þimdi bu sýnýfý düþünün:
                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{ };
                    int m_id{ };

                public:
                    Employee(std::string_view name, int id)
                        : m_name{ name }
                        , m_id{ id }
                    {
                    }

                    void print() const
                    {
                        std::cout << "Employee(" << m_name << ", " << m_id << ")\n";
                    }
                };

                int main()
                {
                    Employee e1 { "Joe", 1 };
                    e1.print();

                    Employee e2 {}; // compile error: no matching constructor
                    e2.print();

                    return 0;
                }
Bir çalýþaný temsil eden bir sýnýf için, ismi olmayan çalýþanlarýn oluþturulmasýna izin vermek mantýklý deðildir. Bu nedenle,
böyle bir sýnýfýn bir varsayýlan yapýlandýrýcýsý olmamalýdýr, böylece sýnýfýn kullanýcýsý bunu yapmaya çalýþýrsa bir derleme
hatasý oluþur.

14.12 — Yapýlandýrýcýlarý Delege Etme
-------------------------------------
Mümkün olduðunda, gereksiz kodu azaltmak istiyoruz (DRY prensibini takip ederek -- Kendinizi Tekrarlamayýn). 
Aþaðýdaki fonksiyonlarý düþünün:

                void A()
                {
                    // Görev A'yý yapan ifadeler
                }

                void B()
                {
                    // Görev A'yý yapan ifadeler
                    // Görev B'yi yapan ifadeler
                }

Her iki fonksiyonda da tamamen ayný þeyi yapan bir ifade kümesi var (görev A). Bu durumda, þu þekilde yeniden düzenleyebiliriz:

                void A()
                {
                    // Görev A'yý yapan ifadeler
                }

                void B()
                {
                    A();
                    // Görev B'yi yapan ifadeler
                }

Bu þekilde, A() ve B() fonksiyonlarýnda bulunan gereksiz kodu kaldýrmýþ oluruz. Bu, kodumuzu daha kolay bakým yapýlabilir hale
getirir, çünkü deðiþiklikler yalnýzca bir yerde yapýlmalýdýr.

Bir sýnýfýn birden çok yapýlandýrýcýsý olduðunda, her yapýlandýrýcýnýn kodunun benzer hatta ayný olmasý son derece yaygýndýr,
çok fazla tekrar vardýr. Mümkün olduðunda yapýlandýrýcý tekrarýný da kaldýrmak isteriz. Aþaðýdaki örneði düþünün:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Her yapýlandýrýcýnýn gövdesi ayný þeyi yazdýrýr.

Yapýlandýrýcýlar, diðer fonksiyonlarý çaðýrabilir, sýnýfýn diðer üye fonksiyonlarýný da içerir. Bu yüzden þu þekilde yeniden
düzenleyebiliriz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                    void printCreated() const
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        printCreated();
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        printCreated();
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Bu, önceki versiyondan daha iyidir, ancak yeni bir fonksiyonun tanýtýlmasýný gerektirir, bu da ideal deðildir.

Daha iyisini yapabilir miyiz?

Açýk çözüm iþe yaramýyor

Yukarýdaki örnekte olduðu gibi, fonksiyon B()'nin fonksiyon A()'yý çaðýrmasýna benzer þekilde, açýk çözüm, Employee 
yapýlandýrýcýlarýndan birinin diðer yapýlandýrýcýyý çaðýrmasý olacaktýr. Ancak bu, beklenildiði gibi çalýþmayacaktýr,
çünkü yapýlandýrýcýlar, baþka bir fonksiyonun gövdesinden (diðer yapýlandýrýcýlar da dahil olmak üzere) doðrudan çaðrýlmak
üzere tasarlanmamýþtýr! Örneðin, bunu denemeyi düþünebilirsiniz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : m_name{ name }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id }
                    {
                        Employee(name); // derleme hatasý
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
Bu iþe yaramaz ve bir derleme hatasýna neden olur. Daha tehlikeli bir durum, herhangi bir argüman olmadan bir yapýlandýrýcýyý
açýkça çaðýrmayý denediðimizde ortaya çýkar. Bu, varsayýlan yapýlandýrýcýya bir fonksiyon çaðrýsý yapmaz -- aksine, geçici 
(isimsiz) bir nesne oluþturur ve onu deðer baþlatýr! Ýþte bunu gösteren saçma bir örnek:
                #include <iostream>
                struct Foo
                {
                    int x{};
                    int y{};

                public:
                    Foo()
                    {
                        x = 5;
                    }

                    Foo(int value): y { value }
                    {
                        // niyet: Foo() fonksiyonunu çaðýrmak
                        // gerçek: value, isimsiz geçici Foo'yu baþlatýr (daha sonra atýlýr)
                        Foo(); // not: bu, Foo{} yazmanýn eþdeðeridir
                    }
                };

                int main()
                {
                    Foo f{ 9 };
                    std::cout << f.x << ' ' << f.y; // 0 9 yazdýrýr
                }
Bu örnekte, Foo(int) yapýcýsý Foo() ifadesine sahip ve Foo() yapýcýsýný çaðýrýp x üyesine 5 deðerini atamayý bekliyor.
Ancak bu sözdizimi, aslýnda isimsiz geçici bir Foo oluþturur ve ardýndan onu deðer baþlatýr (Foo{} yazmýþýz gibi). x = 5 ifadesi
çalýþtýðýnda, deðeri atanacak olan x, geçici Foo'nun x üyesidir. Geçici nesne kullanýlmadýðý için, yapýmý tamamlandýktan sonra
atýlýr.

Foo(int) yapýcýsýnýn içsel nesnesinin x üyesine hiçbir deðer atanmaz. Bu yüzden daha sonra main() içinde deðerini yazdýrdýðýmýzda,
beklenen 5 yerine 0 alýrýz.

Bu durumun bir derleme hatasý oluþturmadýðýný unutmayýn - sadece beklenen sonuçlarý sessizce üretmeyi baþaramaz!

*** Uyarý -> Yapýcýlar, baþka bir fonksiyonun gövdesinden doðrudan çaðrýlmamalýdýr. Bunu yapmak ya bir derleme hatasýna yol açar
             ya da bir geçici nesneyi deðer baþlatýr ve ardýndan onu atar (ki bu muhtemelen istediðiniz þey deðildir).

Yapýcýlarýn Delege Edilmesi
---------------------------
Yapýcýlar, baþlatmayý ayný sýnýf türünden baþka bir yapýcýya devretmeye (sorumluluk aktarmaya) izin verir. Bu sürece bazen yapýcý
zincirleme denir ve bu tür yapýcýlara delege eden yapýcýlar denir.

Bir yapýcýnýn baþlatmayý baþka bir yapýcýya devretmesini saðlamak için, sadece üye baþlatýcý listesinde yapýcýyý çaðýrýn.
Yukarýdaki örneðimize uygulandýðýnda:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 };

                public:
                    Employee(std::string_view name)
                        : Employee{ name, 0 } // baþlatmayý Employee(std::string_view, int) yapýcýsýna devreder
                    {
                    }

                    Employee(std::string_view name, int id)
                        : m_name{ name }, m_id{ id } // üyeleri gerçekten baþlatýr
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }

                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }
e1 { "James" } baþlatýldýðýnda, parametre adý "James" olarak ayarlanmýþ olan Employee(std::string_view) yapýcýsý çaðrýlýr. 
Bu yapýcýnýn üye baþlatýcý listesi, baþlatmayý baþka bir yapýcýya devreder, bu yüzden Employee(std::string_view, int) daha sonra 
çaðrýlýr. Adýn deðeri ("James") ilk argüman olarak geçirilir ve 0 deðeri ikinci argüman olarak geçirilir. Delege edilen yapýcýnýn
üye baþlatýcý listesi daha sonra üyeleri baþlatýr. Delege edilen yapýcýnýn gövdesi daha sonra çalýþýr. Daha sonra kontrol,
baþlangýçtaki yapýcýya döner, onun (boþ) gövdesi çalýþýr. Son olarak, kontrol çaðýrýcýya döner.

Bu yöntemin dezavantajý, bazen baþlatma deðerlerinin çoðaltýlmasýný gerektirmesidir. Employee(std::string_view, int) yapýcýsýna 
yapýlan delegasyonda, int parametresi için bir baþlatma deðerine ihtiyacýmýz var. Varsayýlan üye baþlatýcýsýna baþvurmanýn bir 
yolu olmadýðý için, 0 deðerini elle girmek zorunda kaldýk.

Delege eden yapýcýlar hakkýnda birkaç ek not. Ýlk olarak, baþka bir yapýcýya delegasyon yapan bir yapýcý, kendi baþýna herhangi
bir üye baþlatmasý yapamaz. Yani yapýcýlarýnýz ya delegasyon yapabilir ya da baþlatabilir, ama her ikisini birden yapamaz.
Yan Not…

Daha az parametreye sahip olan Employee(std::string_view) yapýlandýrýcýsýnýn, daha fazla parametreye sahip olan
Employee(std::string_view name, int id) yapýlandýrýcýsýna delege ettiðini unutmayýn. Daha az parametreye sahip olan
yapýlandýrýcýnýn, daha fazla parametreye sahip olan yapýlandýrýcýya delege etmesi yaygýndýr.

Eðer Employee(std::string_view name, int id) yapýlandýrýcýsýnýn Employee(std::string_view)'a delege etmesini seçmiþ olsaydýk,
bu durumda m_id'yi id kullanarak baþlatamazdýk, çünkü bir yapýlandýrýcý yalnýzca delege edebilir veya baþlatabilir, her ikisini
birden yapamaz.

Ýkincisi, bir yapýlandýrýcýnýn baþka bir yapýlandýrýcýya delege etmesi mümkündür, bu yapýlandýrýcý da ilk yapýlandýrýcýya delege 
eder. Bu, sonsuz bir döngü oluþturur ve programýnýzýn yýðýn alanýnýn tükenmesine ve çökmesine neden olur. Bunu, tüm 
yapýlandýrýcýlarýnýzýn bir delege etmeyen yapýlandýrýcýya çözülmesini saðlayarak önleyebilirsiniz.

*** BEST -> Birden çok yapýlandýrýcýnýz varsa, gereksiz kodu azaltmak için delege eden yapýlandýrýcýlarý kullanýp
            kullanamayacaðýnýzý düþünün.

Varsayýlan Argümanlarý Kullanarak Yapýlandýrýcýlarý Azaltma
-----------------------------------------------------------
Varsayýlan deðerler, bazen birden çok yapýlandýrýcýyý daha az yapýlandýrýcýya indirgemek için kullanýlabilir. Örneðin, id
parametremize bir varsayýlan deðer koyarak, bir isim argümaný gerektiren ancak isteðe baðlý olarak bir id argümaný kabul edecek 
tek bir Employee yapýlandýrýcýsý oluþturabiliriz:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                private:
                    std::string m_name{};
                    int m_id{ 0 }; // varsayýlan üye baþlatýcý

                public:

                    Employee(std::string_view name, int id = 0) // id için varsayýlan argüman
                        : m_name{ name }, m_id{ id }
                    {
                        std::cout << "Employee " << m_name << " created\n";
                    }
                };

                int main()
                {
                    Employee e1{ "James" };
                    Employee e2{ "Dave", 42 };
                }

Varsayýlan deðerler, bir fonksiyon çaðrýsýndaki en saðdaki parametrelere eklenmelidir, bu yüzden sýnýflarý tanýmlarken iyi bir
uygulama, kullanýcýnýn baþlatma deðerleri saðlamasý gereken üyeleri ilk olarak tanýmlamaktýr (ve bunlarý yapýlandýrýcýnýn en 
solundaki parametreler yapar). Kullanýcýnýn isteðe baðlý olarak saðlayabileceði üyeler (çünkü varsayýlan deðerler kabul edilebilir)
ikinci olarak tanýmlanmalýdýr (ve bunlarý yapýlandýrýcýnýn en saðdaki parametreleri yapar).

Bu yöntem ayrýca m_id için varsayýlan baþlatma deðerinin ('0') çoðaltýlmasýný gerektirir: bir kez varsayýlan üye baþlatýcý olarak
ve bir kez varsayýlan argüman olarak.

Bir Ýkilem: Gereksiz Yapýlandýrýcýlar vs Gereksiz Varsayýlan Deðerler

Yukarýdaki örneklerde, yapýlandýrýcý tekrarýný azaltmak için delege eden yapýlandýrýcýlarý ve ardýndan varsayýlan argümanlarý
kullandýk. Ancak her iki yöntem de üyelerimiz için baþlatma deðerlerini çeþitli yerlerde çoðaltmamýzý gerektirdi. Maalesef,
þu anda bir delege eden yapýlandýrýcýnýn veya varsayýlan argümanýn varsayýlan üye baþlatýcý deðerini kullanmasý gerektiðini
belirtmenin bir yolu yok.

Daha az yapýlandýrýcýya sahip olmanýn (baþlatma deðerlerinin çoðaltýlmasýyla) mý yoksa daha fazla yapýlandýrýcýya sahip olmanýn
(baþlatma deðerlerinin çoðaltýlmamasýyla) mý daha iyi olduðu konusunda çeþitli görüþler var. Görüþümüz, genellikle daha az 
yapýlandýrýcýnýn olmasýnýn, baþlatma deðerlerinin çoðaltýlmasýna yol açsa bile, daha basit olduðudur.

14.13 — Geçici sýnýf nesneleri
------------------------------
Aþaðýdaki örneði düþünün:

                #include <iostream>

                int add(int x, int y)
                {
                    int sum{ x + y }; // x + y'yi bir deðiþkende saklar
                    return sum;       // bu deðiþkenin deðerini döndürür
                }

                int main()
                {
                    std::cout << add(5, 3) << '\n';

                    return 0;
                }
add() fonksiyonunda, sum deðiþkeni x + y ifadesinin sonucunu saklamak için kullanýlýr. Bu deðiþken daha sonra return ifadesinde
deðerlendirilir ve döndürülecek deðeri üretir. Bu, ara sýra hata ayýklama için yararlý olabilir (böylece sum deðerini 
istediðimizde inceleyebiliriz), ancak aslýnda fonksiyonu gerektiðinden daha karmaþýk hale getirir çünkü yalnýzca bir kez
kullanýlan bir nesne tanýmlar.

Bir deðiþkenin yalnýzca bir kez kullanýldýðý çoðu durumda, aslýnda bir deðiþkene ihtiyacýmýz yoktur. Bunun yerine,
deðiþkenin kullanýldýðý yerde deðiþkeni baþlatmak için kullanýlan ifadeyi yerleþtirebiliriz. Ýþte bu þekilde yeniden yazýlmýþ
add() fonksiyonu:

                #include <iostream>

                int add(int x, int y)
                {
                    return x + y; // sadece x + y'yi doðrudan döndür
                }

                int main()
                {
                    std::cout << add(5, 3) << '\n';

                    return 0;
                }
Bu, yalnýzca return deðerleriyle deðil, ayný zamanda çoðu fonksiyon argümanýyla da çalýþýr. Örneðin, bunun yerine:

                #include <iostream>

                void printValue(int value)
                {
                    std::cout << value;
                }

                int main()
                {
                    int sum{ 5 + 3 };
                    printValue(sum);

                    return 0;
                }
Bunu yazabiliriz:

                #include <iostream>

                void printValue(int value)
                {
                    std::cout << value;
                }

                int main()
                {
                    printValue(5 + 3);

                    return 0;
                }

Kodumuzu ne kadar temiz tuttuðuna dikkat edin. Bir deðiþkeni tanýmlamak ve bir isim vermek zorunda deðiliz. Ve bu deðiþkenin baþka
bir yerde gerçekten kullanýlýp kullanýlmadýðýný belirlemek için tüm fonksiyonu tarayamayýz. Çünkü 5 + 3 bir ifade olduðu için,
yalnýzca o bir satýrda kullanýldýðýný biliyoruz.

Bunun yalnýzca bir rvalue ifadesinin kabul edildiði durumlarda çalýþtýðýný unutmayýn. Bir lvalue ifadesi gerektiðinde, bir 
nesnemiz olmalýdýr:

                #include <iostream>

                void addOne(int& value) // non-const referanslarý geçmek lvalue gerektirir
                {
                    ++value;
                }

                int main()
                {
                    int sum { 5 + 3 };
                    addOne(sum);   // tamam, sum bir lvalue

                    addOne(5 + 3); // derleme hatasý: bir lvalue deðil

                    return 0;
                }
Geçici sýnýf nesneleri
----------------------
Ayný sorun, sýnýf türleri baðlamýnda da geçerlidir.

Yazarýn notu

Burada bir sýnýf kullanacaðýz, ancak bu dersin her þeyi, toplu baþlatma kullanýlarak baþlatýlan yapýlar için de geçerlidir.
Aþaðýdaki örnek, yukarýdakilere benzer, ancak int yerine program tarafýndan tanýmlanan sýnýf türü IntPair kullanýr:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const { return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                int main()
                {
                    // Durum 1: Deðiþkeni geç
                    IntPair p { 3, 4 };
                    print(p); // (3, 4) yazar

                    return 0;
                }

Durum 1'de, IntPair p deðiþkenini örnekliyoruz ve ardýndan p'yi print() fonksiyonuna geçiriyoruz. Ancak, p yalnýzca bir kez 
kullanýlýyor ve print() fonksiyonu rvalue'leri kabul edeceði için, burada bir deðiþken tanýmlamak için gerçekten bir neden yok.
O zaman p'den kurtulalým.

Bunu, adlandýrýlmýþ bir deðiþken yerine geçici bir nesne geçirerek yapabiliriz. Geçici bir nesne (bazen anonim nesne veya isimsiz
nesne olarak adlandýrýlýr), adý olmayan ve yalnýzca tek bir ifade süresince var olan bir nesnedir.

Geçici sýnýf tipi nesneler oluþturmanýn iki yaygýn yolu vardýr:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const{ return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                int main()
                {
                    // Durum 1: Deðiþkeni geç
                    IntPair p { 3, 4 };
                    print(p);

                    // Durum 2: Geçici IntPair oluþtur ve fonksiyona geç
                    print(IntPair { 5, 6 } );

                    // Durum 3: { 7, 8 }'i geçici bir Intpair'a dönüþtür ve fonksiyona geç
                    print( { 7, 8 } );

                    return 0;
                }

Durum 2'de, derleyiciye bir IntPair nesnesi oluþturmasýný ve bunu { 5, 6 } ile baþlatmasýný söylüyoruz. Bu nesnenin bir adý
olmadýðý için bu bir geçicidir. Geçici nesne daha sonra print() fonksiyonunun p parametresine geçirilir. Fonksiyon çaðrýsý
döndüðünde, geçici nesne yok edilir.

Durum 3'te, print() fonksiyonuna geçmek üzere bir geçici IntPair nesnesi oluþturuyoruz. Ancak, hangi türü oluþturacaðýmýzý açýkça
belirtmediðimiz için, derleyici gerekli türü (IntPair) fonksiyon parametresinden çýkarýr ve ardýndan { 7, 8 }'i bir IntPair,
nesnesine dönüþtürür.

Özetlemek gerekirse:

                IntPair p { 1, 2 }; // p adýnda bir nesne oluþtur ve { 1, 2 } deðeriyle baþlat
                IntPair { 1, 2 };   // { 1, 2 } deðeriyle baþlatýlan geçici bir nesne oluþtur
                { 1, 2 };           // derleyici { 1, 2 } deðerini geçici bir nesneye dönüþtürmeye çalýþacak

Bu son durumu, 14.16 -- Dönüþtürme yapýcýlarý ve explicit anahtar kelimesi dersinde daha ayrýntýlý olarak tartýþacaðýz.

Geçici nesnelerin return deðerleriyle kullanýlmasý muhtemelen daha yaygýndýr:

                #include <iostream>

                class IntPair
                {
                private:
                    int m_x{};
                    int m_y{};

                public:
                    IntPair(int x, int y)
                        : m_x { x }, m_y { y }
                    {}

                    int x() const { return m_x; }
                    int y() const { return m_y; }
                };

                void print(IntPair p)
                {
                    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
                }

                // Durum 1: Adlandýrýlmýþ deðiþken oluþtur ve return et
                IntPair ret1()
                {
                    IntPair p { 3, 4 };
                    return p;
                }

                // Durum 2: Geçici IntPair oluþtur ve return et
                IntPair ret2()
                {
                    return IntPair { 5, 6 };
                }

                // Durum 3: { 7, 8 }'i IntPair'a dönüþtür ve return et
                IntPair ret3()
                {
                    return { 7, 8 };
                }

                int main()
                {
                    print(ret1());
                    print(ret2());
                    print(ret3());

                    return 0;
                }

Bu örnekteki durumlar, önceki örnekteki durumlara benzer.

Birkaç not

Birincisi, bir int'in durumunda olduðu gibi, bir ifade içinde kullanýldýðýnda, geçici bir sýnýf nesnesi bir rvalue'dir.
Bu nedenle, bu tür nesneler yalnýzca rvalue ifadelerinin kabul edildiði yerlerde kullanýlabilir.

Ýkincisi, geçici nesneler tanýmlandýðý noktada oluþturulur ve tanýmlandýklarý tam ifadenin sonunda yok edilir. Tam bir ifade, 
bir alt ifade olmayan bir ifadedir.

14.14 — Kopya yapýcýya giriþ
----------------------------
Aþaðýdaki programý düþünün:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    void print()
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };  // Fraction(int, int) yapýcýsýný çaðýrýr
                    Fraction fCopy { f }; // Burada hangi yapýcý kullanýlýyor?

                    f.print();
                    fCopy.print();

                    return 0;
                }
Bu programýn sorunsuz bir þekilde derlendiðini ve þu sonucu ürettiðini görmek sizi þaþýrtabilir:

                Fraction(5, 3)
                Fraction(5, 3)
                
Bu programýn nasýl çalýþtýðýný daha yakýndan inceleyelim. f deðiþkeninin baþlatýlmasý, Fraction(int, int) yapýcýsýný çaðýran 
standart bir süslü parantez baþlatmasýdýr. Peki ya sonraki satýr? fCopy deðiþkeninin baþlatýlmasý da açýkça bir baþlatmadýr ve 
sýnýflarý baþlatmak için yapýcý fonksiyonlarýn kullanýldýðýný biliyorsunuz. 

*- Peki bu satýr hangi yapýcýyý çaðýrýyor?
*- Cevap: kopya yapýcý.

Kopya Yapýcý
------------
Bir kopya yapýcý, bir nesneyi ayný türdeki mevcut bir nesne ile baþlatmak için kullanýlan bir yapýcýdýr. Kopya yapýcý çalýþtýktan
sonra, yeni oluþturulan nesne, baþlatýcý olarak geçirilen nesnenin bir kopyasý olmalýdýr.

Açýk Kopya Yapýcý
-----------------
Sýnýflarýnýz için bir kopya yapýcý saðlamazsanýz, C++ sizin için genel bir açýk kopya yapýcý oluþturur. Yukarýdaki örnekte,
Fraction fCopy { f }; ifadesi, fCopy'yi f ile baþlatmak için açýk kopya yapýcýyý çaðýrýyor.

Varsayýlan olarak, açýk kopya yapýcý üyeleri baþlatma yapar. Bu, her üyenin baþlatýcý olarak geçirilen sýnýfýn karþýlýk gelen
üyesi kullanýlarak baþlatýlacaðý anlamýna gelir. Yukarýdaki örnekte, fCopy.m_numerator, f.m_numerator (deðer 5 olan) kullanýlarak
baþlatýlýr ve fCopy.m_denominator, f.m_denominator (deðer 3 olan) kullanýlarak baþlatýlýr.

Kopya yapýcý çalýþtýktan sonra, f ve fCopy'nin üyeleri ayný deðerlere sahiptir, bu yüzden fCopy, f'nin bir kopyasýdýr.
Bu nedenle, her ikisinde de print() çaðrýsý ayný sonucu verir.

Kendi Kopya Yapýcýnýzý Tanýmlama
--------------------------------
Kendi kopya yapýcýmýzý da açýkça tanýmlayabiliriz. Bu derste, kopya yapýcýmýzýn kopyalar oluþturulduðunda gerçekten çalýþtýðýný
gösterebilmek için kopya yapýcýmýza bir mesaj yazdýracaðýz.

Kopya yapýcý, beklediðiniz gibi görünür:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Copy constructor
                    Fraction(const Fraction& fraction)
                        // Initialize our members using the corresponding member of the parameter
                        : m_numerator{ fraction.m_numerator }
                        , m_denominator{ fraction.m_denominator }
                    {
                        std::cout << "Copy constructor called\n"; // just to prove it works
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
                    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

                    f.print();
                    fCopy.print();

                    return 0;
                }

                Bu program çalýþtýrýldýðýnda, þunu alýrsýnýz:


                Copy constructor called
                Fraction(5, 3)
                Fraction(5, 3)
Yukarýda tanýmladýðýmýz kopya yapýcý, varsayýlan olarak alacaðýmýzla iþlevsel olarak eþdeðerdir, tek fark, kopya yapýcýnýn
gerçekten çaðrýldýðýný kanýtlamak için bir çýktý ifadesi eklemiþ olmamýzdýr. Bu kopya yapýcý, fCopy'nin f ile baþlatýldýðý
zaman çaðrýlýr.

Bir hatýrlatma

Eriþim kontrolleri sýnýf bazýnda çalýþýr (nesne bazýnda deðil). Bu, bir sýnýfýn üye fonksiyonlarýnýn ayný türdeki herhangi bir
sýnýf nesnesinin özel üyelerine eriþebileceði anlamýna gelir (sadece açýk nesne deðil).

Yukarýdaki Fraction kopya yapýcýsýnda bunu avantajýmýza kullanýyoruz, böylece fraction parametresinin özel üyelerine doðrudan 
eriþebiliyoruz. Aksi takdirde, bu üyelere doðrudan eriþimimiz olmazdý (eriþim fonksiyonlarý eklemek dýþýnda, bunu yapmak 
istemeyebiliriz).

Bir kopya yapýcýnýn bir nesneyi kopyalamaktan baþka bir þey yapmamasý gerekir. Bu, derleyicinin belirli durumlarda kopya yapýcýyý
optimize edebileceði içindir. Kopya yapýcýya, sadece kopyalamadan baþka bir davranýþ için güveniyorsanýz, bu davranýþ olabilir 
veya olmayabilir. Bunu, 14.15 -- Sýnýf baþlatma ve kopya elision dersinde daha ayrýntýlý olarak tartýþacaðýz.

*** BEST -> Kopya yapýcýlar, kopyalamanýn ötesinde hiçbir yan etkiye sahip olmamalýdýr.

Açýk Kopya Yapýcýyý Tercih Edin
-------------------------------
Hiçbir þey yapmayan (ve bu yüzden nadiren istediðimiz þey olan) açýk varsayýlan yapýcýdan farklý olarak, açýk kopya yapýcýnýn 
gerçekleþtirdiði üye baþlatma genellikle tam olarak istediðimiz þeydir. Bu nedenle, çoðu durumda, açýk kopya yapýcýyý kullanmak 
mükemmel bir seçenektir.

*** BEST -> Kendi oluþturmanýz için belirli bir nedeniniz olmadýkça, açýk kopya yapýcýyý tercih edin.

Kopya Yapýcýnýn Parametresi Bir Referans Olmalýdýr
--------------------------------------------------
Bir kopya yapýcýnýn parametresinin bir lvalue referansý veya const lvalue referansý olmasý gerekliliðidir. Çünkü kopya yapýcýnýn
parametreyi deðiþtirmemesi gerektiði için, const lvalue referansý kullanmak tercih edilir.

*** BEST -> Kendi kopya yapýcýnýzý yazarsanýz, parametre const lvalue referansý olmalýdýr.

Deðerden Geçme (ve Deðerden Dönme) ve Kopya Yapýcý
--------------------------------------------------
Bir nesne deðerden geçtiðinde, argüman parametreye kopyalanýr. Argüman ve parametre ayný sýnýf türü olduðunda, kopya,
kopya yapýcýsýný açýkça çaðýrarak yapýlýr. Benzer þekilde, bir nesne deðerden döndürüldüðünde, kopya yapýcýsý kopyayý yapmak
için açýkça çaðrýlýr.

Aþaðýdaki örnekte her ikisini de görüyoruz:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator = 0, int denominator = 1)
                        : m_numerator{ numerator }, m_denominator{ denominator }
                    {
                    }

                    // Copy constructor
                    Fraction(const Fraction& fraction)
                        : m_numerator{ fraction.m_numerator }
                        , m_denominator{ fraction.m_denominator }
                    {
                        std::cout << "Copy constructor called\n";
                    }

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                void printFraction(Fraction f) // f is pass by value
                {
                    f.print();
                }

                Fraction generateFraction(int n, int d)
                {
                    Fraction f{ n, d };
                    return f;
                }

                int main()
                {
                    Fraction f{ 5, 3 };

                    printFraction(f); // f, kopya yapýcýsý kullanýlarak fonksiyon parametresine kopyalanýr

                    Fraction f2{ generateFraction(1, 2) }; // Fraction, kopya yapýcýsý kullanýlarak döndürülür

                    printFraction(f2); // f, kopya yapýcýsý kullanýlarak fonksiyon parametresine kopyalanýr

                    return 0;
                }

Yukarýdaki örnekte, printFraction(f) çaðrýsý, f'yi deðerden geçiriyor. Kopya yapýcý, f'yi main'den printFraction fonksiyonunun
f parametresine kopyalamak için çaðrýlýr.

generateFraction, main'e bir Fraction döndürdüðünde, kopya yapýcýsý tekrar açýkça çaðrýlýr. Ve f2, printFraction'a geçirildiðinde,
kopya yapýcýsý üçüncü kez çaðrýlýr.

                Yazarýn makinesinde, bu örnek þunu yazdýrýr:


                Copy constructor called
                Fraction(5, 3)
                Copy constructor called
                Copy constructor called
                Fraction(1, 2)

Yukarýdaki örneði derleyip çalýþtýrýrsanýz, kopya yapýcýnýn yalnýzca iki kez çaðrýldýðýný görebilirsiniz. Bu, kopya elision olarak
bilinen bir derleyici optimizasyonudur. Kopya elision'ý, 14.15 -- Sýnýf baþlatma ve kopya elision dersinde daha ayrýntýlý olarak 
tartýþacaðýz.

Bir sýnýfýn kopya yapýcýsý yoksa, derleyici bizim için açýkça bir tane oluþturur. Tercih edersek, = default sözdizimini kullanarak
derleyiciden bizim için varsayýlan bir kopya yapýcý oluþturmasýný açýkça isteyebiliriz:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Explicitly request default copy constructor
                    Fraction(const Fraction& fraction) = default;

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };
                    Fraction fCopy { f };

                    f.print();
                    fCopy.print();

                    return 0;
                }

= delete kullanarak kopyalarý önleme
------------------------------------
Bazen, belirli bir sýnýfýn nesnelerinin kopyalanabilir olmasýný istemeyiz. Kopya yapýcý fonksiyonu silinmiþ olarak iþaretleyerek 
bunu önleyebiliriz, = delete sözdizimini kullanýrýz:

                #include <iostream>

                class Fraction
                {
                private:
                    int m_numerator{ 0 };
                    int m_denominator{ 1 };

                public:
                    // Default constructor
                    Fraction(int numerator=0, int denominator=1)
                        : m_numerator{numerator}, m_denominator{denominator}
                    {
                    }

                    // Delete the copy constructor so no copies can be made
                    Fraction(const Fraction& fraction) = delete;

                    void print() const
                    {
                        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
                    }
                };

                int main()
                {
                    Fraction f { 5, 3 };
                    Fraction fCopy { f }; // compile error: copy constructor has been deleted

                    return 0;
                }
Örnekte, derleyici fCopy'yi f ile baþlatmak için bir yapýcý bulmaya gittiðinde, kopya yapýcýnýn silindiðini görecektir.
Bu, derleyicinin bir derleme hatasý yayýnlamasýna neden olacaktýr.

Bir not…

Kopya yapýcýsýný özel yaparak da public sýnýf nesnesinin kopyalarýný yapmasýný önleyebilirsiniz (çünkü özel fonksiyonlar public 
tarafýndan çaðrýlamaz). Ancak, bir özel kopya yapýcý, sýnýfýn diðer üyelerinden çaðrýlabilir, bu yüzden bu çözüm, istenilen
durum dýþýnda tavsiye edilmez.
*/