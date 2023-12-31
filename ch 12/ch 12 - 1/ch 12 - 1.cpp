#include <iostream>

int main()
{

    
    return 0;
}
/*
                                                12.1 — Bileþik Veri Türlerine Giriþ
                                                -----------------------------------


4.1 dersinde -- Temel veri türlerine giriþ, C++'ýn temel dil bölümü olarak saðladýðý temel veri türlerini tanýttýk.

Bu temel türleri özellikle int veri türünü þimdiye kadar programlarýmýzda sýkça kullanmýþtýk. Ve bu temel türler basit kullanýmlar için son derece
kullanýþlý olsalar da, daha karmaþýk iþler yapmaya baþladýðýmýzda tüm ihtiyaçlarýmýzý kapsamazlar.

Örneðin, iki kesiri çarpmak için bir matematik programý yazýyormuþ gibi düþünün. Programýnýzda bir kesiri nasýl temsil edersiniz? Muhtemelen bir
çift tamsayý kullanýrdýnýz (pay için bir tane, payda için bir tane), þu þekilde:

                    #include <iostream>

                    int main()
                    {
                        // Ýlk kesirimiz
                        int sayi1 {};
                        int payda1 {};

                        // Ýkinci kesirimiz
                        int sayi2 {};
                        int payda2 {};

                        // pay ve payda arasýndaki slash'ý (eðik çizgi) kaldýrmak için kullanýlýr
                        char yoket {};

                        // Kullanýcýdan ilk kesiri girmesini isteyen bir çýkýþ
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi1 >> yoket >> payda1;

                        // Kullanýcýdan ikinci kesiri girmesini isteyen bir çýkýþ
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi2 >> yoket >> payda2;

                        // Ýki kesirin çarpýmýný hesaplayýp ekrana yazdýran bir çýkýþ
                        std::cout << "Ýki kesirin çarpýmý: "
                            << sayi1 * sayi2 << '/' << payda1 * payda2 << '\n';

                        return 0;
                    }
                    Çýktýsý:
                    Bir kesir girin: 1/2
                    Bir kesir girin: 3/4
                    Ýki kesirin çarpýmý: 3/8

Bu program çalýþsa da, üzerinde iyileþtirmeler yapmamýz gereken bazý zorluklarý ortaya çýkarýr. Ýlk olarak, her çift tamsayý arasýnda sadece 
gevþek bir baðlantý vardýr -- yorumlar ve kod içinde nasýl kullanýldýklarý baðlamý dýþýnda, her pay ve payda çiftinin iliþkili olduðuna dair
pek bir þey yoktur. Ýkinci olarak, DRY (kendini tekrar etme) ilkesini izleme konusunda, bir fonksiyon oluþturmalýyýz ki bu fonksiyon kullanýcýnýn
bir kesiri girmesini ele alsýn (ve bazý hata iþleme iþlemleri de içersin). Ancak, fonksiyonlar yalnýzca tek bir deðer döndürebilir, peki payyý ve
paydayý çaðýran yere nasýl geri döndürebiliriz?

Þimdi baþka bir durumu düþünün; çalýþan kimliklerini tutan bir program yazmanýz gerekiyor. Bunun için nasýl bir þey denersiniz? Belki de þöyle 
bir þey denersiniz:

                    int main()
                    {
                        int id1 { 42 };
                        int id2 { 57 };
                        int id3 { 162 };
                        // ave böylece devam edersiniz
                    }

Ancak, 100 çalýþanýnýz olsaydý ne olurdu? Ýlk olarak, 100 deðiþken adýný yazmanýz gerekecekti. Ve eðer hepsini yazdýrmamýz veya bir iþleme
geçirmemiz gerekiyorsa? Bu durumda çok fazla yazý yazmak zorunda kalýrdýk. Bu basitçe ölçeklenemez.

Açýkça temel veri tipleri bizi sadece belirli bir noktaya kadar götürecektir.

compound data types - Bileþik veri türleri
------------------------------------------
Neyse ki, C++, bileþik veri tipleri adý verilen ikinci bir veri tipi kümesini destekler. Bileþik veri tipleri, temel veri tiplerinden (veya diðer
bileþik veri tiplerinden) oluþturulabilen veri tipleridir. Her bileþik veri tipinin kendi benzersiz özellikleri vardýr.

Bu bölümde ve gelecekteki bölümlerde göstereceðimiz gibi, bileþik veri tiplerini yukarýda sunduðumuz tüm zorluklarý zarif bir þekilde çözmek için
kullanabiliriz.

C++ aþaðýdaki bileþik türlerini destekler:

-Functions
-Arrays
-Pointer types:
   -Pointer to object
   -Pointer to function
-Pointer to member types:
   -Pointer to data member
   -Pointer to member function
-Reference types:
   -L-value references
   -R-value references
-Enumerated types:
   -Unscoped enumerations
   -Scoped enumerations
-Class types:
   -Structs
   -Classes
   -Unions

Zaten düzenli olarak bir bileþik türü kullanýyorsunuz: Fonksiyonlar. Örneðin þu fonksiyonu göz önünde bulundurun:

                    void doSomething(int x, double y)
                    {
                    }

12.2 — Deðer Kategorileri (L-deðerleri ve R-deðerleri)
------------------------------------------------------
1.10 dersinde -- Ýfadelerin Tanýtýmý, bir ifadeyi "birleþik sayýlar, deðiþkenler, operatörler ve tek bir deðer üretebilmek 
için çalýþtýrýlabilir fonksiyon çaðrýlarýnýn bir kombinasyonu" olarak tanýmlamýþtýk.

                    #include <iostream>

                    int main()
                    {
                        std::cout << 2 + 3 << '\n'; // 2 + 3 ifadesi 5 deðerini üretir

                        return 0;
                    }

Yukarýdaki ifade de 2 + 3 ifadesi 5 deðerini üretir ve sonrasýnda konsola yazdýrýr.ayrýca ifadelerin, ifadeden daha uzun ömürlü yan etkiler 
üretebileceðini de belirttik:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        ++x; // Bu ifadenin yan etkisi x in arttýrýlmasýdýr
                        std::cout << x << '\n'; // Burada 6 yazar

                        return 0;
                    }


Yukarýdaki programda, ifade ++x ifadesi x'in deðerini artýrýr ve bu deðer, ifadenin deðerlendirmesi tamamlandýktan sonra bile deðiþmiþ olarak 
kalýr.

Deðer üretmenin ve yan etkilere neden olmanýn yaný sýra, ifadeler bir þey daha yapabilir: nesneleri veya fonksiyonlarý deðerlendirebilirler.


Ýfadelerin Özellikleri
----------------------

Ýfadelerin nasýl deðerlendirilmesi gerektiðini ve nerede kullanýlabileceklerini belirlemek için C++'taki tüm ifadelerin iki özelliði vardýr: 
bir tür (type) ve bir deðer kategorisi (value category).

Ýfadelerin Türü
---------------

Bir ifadenin türü, deðerlendirilen ifadeden elde edilen deðerin, nesnenin veya iþlevin türüne eþdeðerdir. Örneðin:
                    int main()
                    {
                        auto v1 { 12 / 4 }; // int / int => int
                        auto v2 { 12.0 / 4 }; // double / int => double

                        return 0;
                    }


v1 için derleyici (derleme zamanýnda), iki int operatörü ile yapýlan bir bölmenin bir int sonucu üreteceðini belirleyecektir, bu nedenle bu 
ifadenin türü int'tir. Tür çýkarýmý yoluyla, int daha sonra v1'in türü olarak kullanýlacaktýr.

v2 için derleyici (derleme zamanýnda), bir double operatörü ve bir int operatörü ile yapýlan bir bölmenin bir double sonuç üreteceðini 
belirleyecektir. Aritmetik operatörlerin eþleþen türlerde operandlara ihtiyacý olduðunu unutmayýn, bu nedenle bu durumda int operatörü
double'a dönüþtürülür ve bir kayan nokta bölme iþlemi gerçekleþtirilir. Bu nedenle bu ifadenin türü double'dir.

Derleyici, bir ifadenin türünü kullanarak bir ifadenin belirli bir baðlamda geçerli olup olmadýðýný belirleyebilir. Örneðin:

                    #include <iostream>

                    void print(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        print("foo"); // hata: print() bir int argüman bekliyordu, biz bir string literal i göndermeye çalýþtýk

                        return 0;
                    }


Yukarýdaki programda, print(int) fonksiyonu bir int parametresi bekliyor. Ancak, iletiþimde bulunduðumuz ifadenin türü (string literal
"foo") eþleþmiyor ve herhangi bir dönüþüm bulunamýyor. Bu nedenle bir derleme hatasý meydana gelir.

Bir ifadenin türü, derleme zamanýnda belirlenebilmelidir (aksi takdirde tür kontrolü ve tür çýkarýmý çalýþmaz) - ancak bir ifadenin deðeri, 
ifade constexpr ise derleme zamanýnda veya deðilse çalýþma zamanýnda belirlenebilir.

Bir ifadenin deðer kategorisi
------------------------------

Þimdi aþaðýdaki programý düþünün:

                    int main()
                    {
                        int x{};

                        x = 5; // geçerli: x e 5 deðerini atayabiliriz
                        5 = x; // hata: x in deðerini 5 e atayamayýz

                        return 0;
                    }


Bir atama ifadesine hangi tarafýn geçerli olduðunu (deðiþken x'e deðeri 5 atama) ve hangisinin geçerli olmadýðýný (x'in deðerini 5'in kendi 
anlamýna atamak ne anlama gelir?) belirlemek için derleyici nasýl bilir?

Cevap, ifadelerin ikinci özelliðinde yatar: deðer kategorisi. Bir ifadenin (veya alt ifadenin) deðer kategorisi, bir ifadenin bir deðere, 
bir fonksiyona veya bir nesneye çözünüp çözünmediðini gösterir.

C++11 öncesinde, yalnýzca iki olasý deðer kategorisi vardý: lvalue ve rvalue.

C++11'de, hareket semantiðini ( move semantic ) desteklemek için üç ek deðer kategorisi (glvalue, prvalue ve xvalue) eklenmiþtir.

Lvalue ve rvalue ifadeleri
--------------------------

Lvalue (okunuþu "ell-value", "sol deðer ( left value )" veya "bulucu deðeri ( locater value )" için kýsaltma, bazen "l-value" olarak yazýlýr), 
tanýmlanabilir bir nesne veya iþlevin (veya bit alanýnýn) deðerini döndüren bir ifadedir.

kimlik( identity ) terimi  C++ standardýnda kullanýlýr, ancak iyi tanýmlanmamýþtýr. Bir kimliðe sahip bir varlýk (örneðin bir nesne veya fonksiyon),
genellikle varlýðýn adreslerini karþýlaþtýrarak diðer benzer varlýklardan ayýrt edilebilir.

Kimliðe sahip varlýklar bir tanýmlayýcý, referans veya iþaretçi ( pointer ) aracýlýðýyla eriþilebilir ve genellikle bir ifade veya
deyimden daha uzun bir ömre sahiptir.

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


Yukarýdaki programda, x ifadesi bir lvalue ifadesidir çünkü deðiþken x'in deðerini deðerlendirir (ki bu bir tanýmlayýcýya sahiptir).

Dilin içine sabitlerin tanýtýlmasýndan bu yana, lvalues iki alt türe ayrýlmaktadýr: deðiþtirilebilir bir lvalue, deðeri deðiþtirilebilen
bir lvalue'dir. Deðiþtirilemez bir lvalue ise (çünkü lvalue const veya constexpr ise) deðeri deðiþtirilemeyen bir lvalue'dir.

                    int main()
                    {
                        int x{};
                        const double d{};
                        int y { x }; // x deðiþtirilebilir bir lvaluedir
                        const double e { d }; // d deðiþtirilemez bir lvaluedir

                        return 0;
                    }

Rvalue ("arr-value" olarak okunan, "right value"ýn kýsaltmasý ve bazen r-value olarak yazýlan) bir ifade, bir lvalue olmayan bir ifadedir.
Rvalue ifadeler bir deðere çözünür. Sýkça karþýlaþýlan rvalue'ler arasýnda literaller bulunur (C tarzý dizge literalleri hariç, çünkü bunlar
lvalue'dir) ve deðer ile dönen fonksiyonlarýn ve operatörlerin dönüþ deðerleri bulunur. Rvalue'lar tanýmlanabilir deðildir (yani hemen
kullanýlmalýdýr) ve yalnýzca kullanýldýklarý ifade kapsamýnda var olurlar.

                    int return5()
                    {
                        return 5;
                    }

                    int main()
                    {
                        int x{ 5 }; // 5 bir rvalue ifadesidir
                        const double d{ 1.2 }; // 1.2 bir rvalue ifadesidir

                        int y { x }; // x deðiþtirilebilir bir lvalue ifadesidir
                        const double e { d }; // d deðiþtirilemez bir lvalue ifadesidir
                        int z { return5() }; // return5(), sonuç deðeri ile döndürüldüðü için bir rvalue ifadesidir

                        int w { x + 1 }; // x + 1 bir rvalue ifadesidir
                        int q { static_cast<int>(d) }; // d'yi int'e static_cast etmenin sonucu bir rvalue ifadesidir

                        return 0;
                    }

Belki de return5(), x + 1 ve static_cast<int>(d) ifadelerinin neden rvalue olduðunu merak ediyorsunuz: cevap, bu ifadelerin tanýmlanabilir
nesneler olmayan geçici deðerler üretmesidir.

Ana Ýpucu

Lvalue ifadeler, tanýmlanabilir bir nesneye çözünür.
Rvalue ifadeler, bir deðere çözünür.

Þimdi x = 5'in neden geçerli olduðu ancak 5 = x'in neden geçerli olmadýðý sorusunu cevaplayabiliriz: atama iþlemi, atamanýn sol operandýnýn
deðiþtirilebilir bir lvalue ifadesi olmasýný ve sað operandýn bir rvalue ifadesi olmasýný gerektirir. Ýkinci atama (5 = x) baþarýsýzdýr
çünkü sol operand ifadesi 5 bir lvalue deðildir.

                    int main()
                    {
                        int x{};

                        // Atama iþlemi, sol operandýn deðiþtirilebilir bir lvalue ifadesi olmasýný ve sað operandýn bir rvalue ifadesi
                        olmasýný gerektirir
                        x = 5; // geçerli: x deðiþtirilebilir bir lvalue ifadesi ve 5 bir rvalue ifadesidir
                        5 = x; // hata: 5 bir rvalue ifadesi iken x deðiþtirilebilir bir lvalue ifadesidir

                        return 0;
                    }

Ýþte lvalue ve rvalue ifadelerinin tam bir listesi https://en.cppreference.com/w/cpp/language/value_category . C++11'de rvalue'lar iki alt türe 
ayrýlmýþtýr: prvalue'lar ve xvalue'lar, bu nedenle burada bahsettiðimiz rvalue'lar, bu iki kategori toplamýnýn birleþimidir.

Tavsiye -> Eðer bir ifadenin bir lvalue mi yoksa rvalue mi olduðundan emin deðilseniz, operator& kullanarak onun adresini almaya çalýþýn. 
           Çünkü operator&, operandýnýn bir lvalue olmasýný gerektirir. Eðer &(ifade); derlemesi baþarýlý oluyorsa, ifade bir lvalue olmalýdýr:

                    int foo()
                    {
                        return 5;
                    }

                    int main()
                    {
                        int x { 5 };
                        &x; // derlenebilir: x bir lvalue ifadesidir
                        // &5; // derlenmez: 5 bir rvalue ifadesidir
                        // &foo(); // derlenmez: foo() bir rvalue ifadesidir
                    }

Ana Ýpucu

Bir C tarzý string literali, C tarzý stringler (ki bunlar C tarzý arraylerdir) bir iþaretçiye dönüþmesinden dolayý bir lvalue'dir. Dönüþüm süreci,
arrayin bir lvalue olmasý durumunda çalýþýr (ve bu nedenle iþaretçide depolanabilecek bir adresi vardýr). C++ bunu geriye uyumluluk için miras
almýþtýr.

Lvalue'dan rvalue'ye dönüþüm
----------------------------
Bu örneðe tekrar bakalým:

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


Eðer x, deðiþken x'e deðeri olan bir lvalue ifadesiyse, y neden deðeri 5 olur?

Cevap, lvalue ifadelerinin, bir rvalue beklenirken ancak bir lvalue saðlandýðýnda otomatik olarak rvalue ifadelere dönüþtürülmesidir. 
Bir int deðiþkeninin baþlatýcýsý bir rvalue ifadesi olmasý beklenir. Bu nedenle, lvalue ifadesi x, bir lvalue'den rvalue'ye dönüþüm geçirir,
bu da deðeri 5 olan bir deðere çözünür ve ardýndan y'yi baþlatmak için kullanýlýr.

Yukarýda belirtildiði gibi atama operatörünün sað operandýnýn bir rvalue ifadesi olmasýný bekledik, peki neden bu tür kod iþe yarýyor?

                    int main()
                    {
                        int x{ 1 };
                        int y{ 2 };

                        x = y; // y deðiþtirilebilir bir lvalue dir, bir rvalue deðil, Ama bu geçerlidir

                        return 0;
                    }

Bu durumda, y bir lvalue ifadesidir, ancak bir lvalue-to-rvalue dönüþümüne uðrar, bu da y'nin deðerini (2) çözünmesine yol açar, ardýndan bu 
deðer x'e atanýr.

Þimdi bu örneði düþünelim:

                    int main()
                    {
                        int x { 2 };

                        x = x + 1;

                        return 0;
                    }

Bu ifadede, deðiþken x iki farklý baðlamda kullanýlmaktadýr. Atama operatörünün sol tarafýnda, x deðiþken x deðeri olan bir lvalue ifadesidir.
Atama operatörünün saðýndaysa, x + 1, deðeri 3 olan bir rvalue ifadesine çözünen bir ifadedir.

Þimdi lvalue'larý ele aldýðýmýza göre, ilk bileþik türümüze gelebiliriz: lvalue referansý.

Ana Ýpucu

Lvalue ve rvalue ifadelerini tanýmlamak için bir kural:

Lvalue ifadeler, ifade sona erdikten sonra varlýðýný sürdürebilen deðiþkenlere veya diðer tanýmlanabilir nesnelere çözünenlerdir.
Rvalue ifadeler, ifade sona erdikten sonra atýlacak olan literalleri veya fonksiyonlar/operatörler tarafýndan döndürülen deðerleri çözünenlerdir.

12.3 — Lvalue references
------------------------

C++ dilinde, bir referans mevcut bir nesnenin takma adýdýr. Bir referans bir kez tanýmlandýðýnda, referans üzerinde yapýlan herhangi bir iþlem,
referans yapýlan nesneye uygulanýr.

Kilit nokta; Bir referans, temelde üzerine referans yapýlan nesne ile özdeþtir.


Bu, bir referansý üzerine referans yapýlan nesneyi okumak veya deðiþtirmek için kullanabileceðimiz anlamýna gelir. Baþta referanslar saçma,
gereksiz veya gereksiz gibi görünebilir, ancak C++'ta referanslar her yerde kullanýlýr (bunu birkaç derste göreceðiz).

Ayrýca, fonksiyonlara referanslar da oluþturabilirsiniz, ancak bu daha az sýk yapýlýr.

Modern C++, iki tür referans içerir: lvalue referanslarý ve rvalue referanslarý. Bu bölümde, lvalue referanslarýný tartýþacaðýz.

Lvalue referans türleri
-----------------------
Bir lvalue referansý (genellikle C++11'den önce yalnýzca bir türde referans olduðu için sadece referans olarak adlandýrýlýr), mevcut bir lvalue
(örneðin bir deðiþken) için bir takma ad olarak hareket eder.

Bir lvalue referans türünü bildirmek için, tür bildiriminde bir ampersand (&) kullanýrýz:

                    int      // normal bir int türü
                    int&     // bir int nesnesine yapýlan bir lvalue referans
                    double&  // bir double nesnesine yapýlan bir lvalue referans


Lvalue referans deðiþkenleri
----------------------------
Lvalue referans türü ile yapabileceðimiz þeylerden biri, bir lvalue referans deðiþkeni oluþturmaktýr. Bir lvalue referans deðiþkeni, 
genellikle baþka bir deðiþkenin referansý olarak hareket eden bir deðiþkendir.

Bir lvalue referans deðiþkeni oluþturmak için, basitçe bir deðiþkeni bir lvalue referans türü ile tanýmlarýz:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };    // x, normal bir tamsayý deðiþkenidir
                        int& ref { x }; // ref, þimdi deðiþken x için bir takma ad olarak kullanýlabilen bir lvalue referans deðiþkenidir

                        std::cout << x << '\n';  // x'in deðerini yazdýr (5)
                        std::cout << ref << '\n'; // ref üzerinden x'in deðerini yazdýr (5)

                        return 0;
                    }

Yukarýdaki örnekte, int& türü ref'i bir int'e referans olan bir lvalue referans olarak tanýmlarýz, ardýndan lvalue ifadesini x ile baþlatýrýz.
Bundan sonra, ref ve x eþanlamlý olarak kullanýlabilir. Bu program þu þekilde çýktý verir:

                    5
                    5

Derleyicinin bakýþ açýsýndan, ampersand'ýn tip adýna (int& ref) mý yoksa deðiþken adýna (int &ref) "baðlý" olmasý önemli deðildir ve seçim tarza
baðlýdýr. Modern C++ programcýlarý, referansýn tip bilgisinin bir parçasý olduðunu, tanýmlanan deðiþkenin adý olmadýðýný daha açýk bir þekilde
ifade etmek için genellikle ampersand'ý tipin yanýna koymayý tercih eder.

*** BEST -> Bir referans tanýmlarken, ampersand'ý referans deðiþkeninin adýnýn yanýna deðil, tipin yanýna koymak en iyisidir.


Deðerleri bir lvalue referans üzerinden deðiþtirme
--------------------------------------------------
Yukarýdaki örnekte, bir referansý üzerine referans yapýlan nesnenin deðerini okumak için kullanabileceðimizi gösterdik. Ayný zamanda bir referansý
kullanarak üzerine referans yapýlan nesnenin deðerini deðiþtirebiliriz:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsayý deðiþkeni
                        int& ref { x }; // ref, þimdi deðiþken x için bir takma ad

                        std::cout << x << ref << '\n'; // 55 yazdýr

                        x = 6; // x'in deðeri þimdi 6

                        std::cout << x << ref << '\n'; // 66 yazdýr

                        ref = 7; // üzerine referans yapýlan nesne (x) þimdi deðeri 7

                        std::cout << x << ref << '\n'; // 77 yazdýr

                        return 0;
                    }
                    Çýktý:
                    55
                    66
                    77

Yukarýdaki örnekte, ref x için bir takma ad olduðundan dolayý x'in deðerini ya x üzerinden ya da ref üzerinden deðiþtirebiliyoruz.

Lvalue referanslarýnýn baþlatýlmasý
-----------------------------------

Sabitler gibi, tüm referanslar baþlatýlmalýdýr.

                    int main()
                    {
                        int& invalidRef;   // hata: referanslar baþlatýlmalýdýr

                        int x { 5 };
                        int& ref { x }; // tamam: int referansý, int deðiþkenine baðlanýr

                        return 0;
                    }


Bir referans, bir nesne (veya fonksiyon) ile baþlatýldýðýnda, o referansýn o nesneye (veya fonksiyona) baðlandýðýný söyleriz. Bu tür bir referansýn
baðlanma sürecine referans baðlama denir. Referans yapýlan nesne (veya fonksiyon) bazen referansta bulunan olarak adlandýrýlýr.

Lvalue referanslarý, deðiþtirilebilir bir lvalue'a baðlanmalýdýr.
                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // geçerli: deðiþtirilebilir bir lvalue'a baðlanan bir lvalue referansý

                        const int y { 5 };
                        int& invalidRef { y };  // geçersiz: deðiþtirilemez bir lvalue'a baðlanamaz
                        int& invalidRef2 { 0 }; // geçersiz: bir rvalue'a baðlanamaz

                        return 0;
                    }

Lvalue referanslarý, deðiþtirilemez lvalue'lara veya rvalue'lara baðlanamaz (aksi takdirde referans aracýlýðýyla bu deðerleri deðiþtirebilir ve 
bu da const durumlarýna aykýrý olurdu). Bu nedenle, lvalue referanslarý zaman zaman lvalue referanslarýna non-const (bazen non-const referans 
olarak kýsaltýlýr) olarak adlandýrýlýr.

Çoðu durumda, referansýn türü, referansta bulunan nesnenin türü ile eþleþmelidir (bu kuralýn bazý istisnalarý vardýr, bunlarý miras konusunu
ele aldýðýmýzda tartýþacaðýz):

                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // tamam: int referansý, int deðiþkenine baðlanýr

                        double y { 6.0 };
                        int& invalidRef { y }; // geçersiz; int referansý, double deðiþkenine baðlanamaz
                        double& invalidRef2 { x }; // geçersiz: double referansý, int deðiþkenine baðlanamaz

                        return 0;
                    }

Lvalue referanslarýndan void'a izin verilmez (bu ne anlama gelir ki?).

Referanslar yeniden yerleþtirilemez (baþka bir nesneyi iþaret etmek üzere deðiþtirilemez)
------------------------------------------------------------------------------------------
C++'ta bir referans bir kez baþlatýldýktan sonra yeniden yerleþtirilemez, yani baþka bir nesneye referans yapacak þekilde deðiþtirilemez.

Yeni C++ programcýlarý genellikle referansý baþka bir deðiþkenle yer deðiþtirmek için atama kullanarak yeniden yerleþtirmeye çalýþýrlar. 
Bu derlenir ve çalýþýr ancak beklenen þekilde iþlev göstermez. Aþaðýdaki programý düþünün:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        int y { 6 };

                        int& ref { x }; // ref, þimdi x için bir takma ad

                        ref = y; // x'in (ref tarafýndan referans yapýlan nesnenin) deðerini 6 (y'nin deðeri) olarak atar
                        // Yukarýdaki satýr, ref'i y deðiþkenine referans yapacak þekilde DEÐÝÞTÝRMEZ!

                        std::cout << x << '\n'; // kullanýcý bunun 5'i yazdýrmasýný bekliyor

                        return 0;
                    }
                    Çýktý:
                    6

Bir referans bir ifadede deðerlendirildiðinde, referans yaptýðý nesneye çözülür. Bu nedenle, ref = y, ref'i þimdi y'ye referans yapacak þekilde
deðiþtirmez. Tam tersine, çünkü ref x için bir takma ad, ifade, x = y þeklinde yazýlmýþ gibi deðerlendirilir -- ve çünkü y'nin deðeri 6 ise,
x'e deðer 6 atanýr.

Lvalue reference kapsam and süre
--------------------------------

Lvalue referans deðiþkenleri, normal deðiþkenlerin uyguladýðý kapsama ve süre kurallarýný takip eder:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsayý
                        int& ref { x }; // deðiþkenin deðerine referans

                        return 0;
                    } // x ve ref burada sona erer

Referanslar ve referans yapýlan nesneler baðýmsýz ömürlere sahiptir.
--------------------------------------------------------------------
Bir istisna dýþýnda (bunu bir sonraki derste ele alacaðýz), bir referansýn ömrü ve referans yaptýðý nesnenin ömrü baðýmsýzdýr. 
Baþka bir deyiþle, her ikisi de aþaðýdaki ifadeler doðrudur:

    1. Bir referans, ona referans yapýlan nesneden önce yok edilebilir.
    2. Referans yapýlan nesne, referanstan önce yok edilebilir.

Bir referans, referanstan önce yok edildiðinde, referans yapýlan nesneyi etkilemez. Aþaðýdaki program bunu göstermektedir:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };

                        {
                            int& ref { x };   // ref, x'e referans yapan bir referanstýr
                            std::cout << ref << '\n'; // ref'in deðerini (5) yazdýrýr
                        } // ref burada yok edildi -- x bunun farkýnda deðil

                        std::cout << x << '\n'; // x'in deðerini (5) yazdýrýr

                        return 0;
                    } // x burada yok edildi
                    Çýktý:
                    5
                    5

"ref" öldüðünde, deðiþken x normal þekilde devam eder, neþe içinde, ona yapýlan bir referansýn yok edildiðinden habersiz.

Asýlý referanslar
-----------------

Bir nesneye yapýlan bir referansýn, referansýn kendisinden önce yok edildiði durumda, referans artýk var olmayan bir nesneye iþaret eder durumda
kalýr. Böyle bir referansa "asýlý referans" denir. Bir asýlý referansa eriþmek, tanýmsýz davranýþa yol açar.

Asýlý referanslardan kaçýnmak oldukça basittir, ancak bunun pratikte nasýl gerçekleþebileceðini 12.12 dersinde göstereceðiz

Referanslar nesne deðildir
--------------------------

Belki de þaþýrtýcý bir þekilde, C++ dilinde referanslar nesneler deðildir. Bir referansýn var olmasý veya depolama alanýný kaplamasý gerekmez.
Mümkünse, derleyici, bir referansýn tüm örneklerini referans yapan nesneyle deðiþtirerek referanslarý optimize etme eðilimindedir. Ancak bu her 
zaman mümkün olmayabilir ve böyle durumlarda referanslar depolama alaný gerektirebilir.

Bu ayný zamanda "referans deðiþkeni" teriminin biraz yanýltýcý olduðu anlamýna gelir, çünkü deðiþkenler adý olan nesnelerdir ve referanslar 
nesneler deðildir.

Çünkü referanslar nesneler deðil, baþka bir nesnenin adý olan referanslar, nesne gereken herhangi bir yerde kullanýlamaz (örneðin, bir referansa 
referans olamazsýnýz, çünkü bir lvalue referansý tanýmlanabilir bir nesneye referans yapmalýdýr). Bir nesne veya tekrar yerleþtirilebilen bir 
referans gerektiðinde, std::reference_wrapper (ki bunu 23.3 dersinde ele alacaðýz - Birleþtirme) bir çözüm sunar.

Bir kenara not olarak...

Aþaðýdaki deðiþkenleri düþünün:

                    int var{};
                    int& ref1{ var };  // var'a baðlý bir lvalue referansý
                    int& ref2{ ref1 }; // var'a baðlý bir lvalue referansý

Çünkü ref2 (bir referans) ref1 (bir referans) ile baþlatýlmýþtýr, ref2'nin bir referansýn referansý olduðunu düþünebilirsiniz. Ancak öyle deðil.
ref1, var'a referans olduðundan, bir ifadede (örneðin bir baþlatýcýda) kullanýldýðýnda, ref1 var'a deðerlendirilir. Bu nedenle ref2, sadece var'a
baðlý normal bir lvalue referansýdýr (türü int& olarak belirtilmiþtir).

Bir referansýn referansýna (bir int'e) sahip olmak için int&& syntax'ý kullanýlmalýdýr - ancak C++, referanslarýn referansýný desteklemediði için
bu syntax C++11'de bir sað taraf deðeri referansýný göstermek için kullanýlmýþtýr (ki bunu 22.2 dersinde ele alýyoruz - R deðeri referanslarý).

ref2'nin ref1 ile baþlatýlmasýndan dolayý ref2'nin bir referansýn referansý gibi algýlanabileceði ancak bu durumun gerçekleþmediði .
C++ dilinde referanslarýn referanslarýný desteklemez. int&& syntax'ý orijinalde bir referansýn referansýný ifade ediyordu, ancak C++11'de
bu syntax, sað taraf deðeri referansýný (rvalue reference) ifade etmek için kullanýlmaya baþlandý.

12.4 - Lvalue referanslarýný const lar ile kullanýmý
----------------------------------------------------
                    int main()
                    {
                        const int x{5};    // x, deðiþtirilemez (const) bir lvalue'dir
                        int& ref{x};       // hata: ref, deðiþtirilemez lvalue'a baðlanamaz

                        return 0;
                    }

Bu durum, const bir deðiþkeni (x) deðiþtirmemize izin verecek bir const olmayan referans (ref) üzerinden deðiþtirmemize izin vermemek amacýyla 
engellenmiþtir.

Ancak eðer bir const deðiþkene bir referans oluþturmak istiyorsak, normal bir lvalue referansý (const olmayan bir deðere) yeterli olmayacaktýr.

Bir lvalue referansýnýn deklarasyonunda const anahtar kelimesini kullanarak, referansýn iþaret ettiði nesneyi const olarak ele almasýný saðlarýz.
Bu tür bir referans, bir const deðere sahip bir lvalue referansý olarak adlandýrýlýr (bazen bir const referansý veya sadece const olarak da 
adlandýrýlýr). Lvalue references to const, deðiþtirilemez lvalue'lara baðlanabilir:

                    int main()
                    {
                        const int x{5};        // x, deðiþtirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const deðere sahip bir lvalue referansýdýr

                        return 0;
                    }

Çünkü lvalue referanslarýna const, üzerine referans yapýlan nesneyi const olarak ele aldýklarý için, referans yapýlan deðeri deðiþtirmek yerine 
sadece eriþmek için kullanýlabilirler:

                    #include <iostream>

                    int main()
                    {
                        const int x{5};        // x, deðiþtirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const deðere sahip bir lvalue referansýdýr

                        std::cout << ref << '\n'; // uygun: const nesneye eriþebiliriz
                        ref = 6;                  // hata: const bir referans aracýlýðýyla bir nesneyi deðiþtiremeyiz

                        return 0;
                    }

Const ile baþlatýlmýþ, deðiþtirilebilir bir lvalue referansý
------------------------------------------------------------

Lvalue referanslarý const ile modifiable (deðiþtirilebilir) lvaluelara baðlanabilir. Bu durumda, referans aracýlýðýyla eriþilen nesne const
olarak iþlenir (ancak temeldeki nesne const olmasa bile):

                    #include <iostream>

                    int main()
                    {
                        int x{5};               // x, deðiþtirilebilir bir lvalue'dir
                        const int& ref{x};      // tamam: deðiþtirilebilir bir lvalue'a bir const referans baðlayabiliriz

                        std::cout << ref << '\n'; // tamam: nesneye const referans aracýlýðýyla eriþebiliriz
                        // ref = 7;               // hata: bir const referans aracýlýðýyla bir nesneyi deðiþtiremeyiz

                        x = 6;                   // tamam: x, deðiþtirilebilir bir lvalue'dir, hala orijinal tanýmlayýcý aracýlýðýyla
                                                    deðiþtirebiliriz

                        return 0;
                    }

Yukarýdaki programda, const referansý ref'i deðiþtirilebilir lvalue x'e baðladýk. Ardýndan ref'i kullanarak x'e eriþebiliriz, ancak ref const
olduðu için ref üzerinden x'in deðerini deðiþtiremeyiz. Ancak, x'in deðerini doðrudan (tanýmlayýcý x kullanarak) deðiþtirebiliriz.

*** BEST -> Deðiþtirilmek istenen nesnenin modifikasyonu gerekmediði sürece, const lvalue referanslarýný lvalue referanslarýna tercih edin.

Const bir lvalue referansýný rvalue ile baþlatma
------------------------------------------------
Belki de þaþýrtýcý bir þekilde, const lvalue referanslarý ayný zamanda rvalue'larla da baðlanabilir:

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // tamam: 5 bir rvalue'dir

                        std::cout << ref << '\n'; // 5'i yazdýrýr

                        return 0;
                    }

Bu durumda, geçici bir nesne oluþturulur ve rvalue ile baþlatýlýr, ardýndan const referans o geçici nesneye baðlanýr.

Geçici bir nesne (bazen anonim nesne olarak da adlandýrýlýr), bir ifade içinde geçici olarak oluþturulan (ve sonra yok edilen) bir nesnedir.
Geçici nesnelerin hiçbir kapsamý yoktur (bu mantýklýdýr, çünkü kapsam bir tanýmlayýcýnýn özelliðidir ve geçici nesnelerin bir tanýmlayýcýsý
yoktur). Bu, bir geçici nesnenin sadece oluþturulduðu noktada doðrudan kullanýlabileceði anlamýna gelir, çünkü bu noktadan ötesine referans
oluþturmanýn bir yolu yoktur.

Const referanslar geçici nesnelere baðlandýðýnda, geçici nesnenin ömrü uzatýlýr
-------------------------------------------------------------------------------

Genellikle, geçici nesneler oluþturulduklarý ifadenin sonunda yok edilir.

Ancak yukarýdaki örnekte, rvalue 5'i tutmak için oluþturulan geçici nesnenin ref tarafýndan baþlatýlan ifadenin sonunda yok edilmesi durumunda
ne olacaðýný düþünelim. Referans ref, sallantýda (yok edilmiþ bir nesneye referans) býrakýlýr ve ref'e eriþmeye çalýþtýðýmýzda tanýmsýz davranýþ
elde ederiz.

Bu tür durumlarda sallantý referanslarýndan kaçýnmak için C++'da özel bir kural vardýr: Bir const lvalue referansý doðrudan bir geçici nesneye
baðlandýðýnda, geçici nesnenin ömrü referansýn ömrüyle eþleþecek þekilde uzatýlýr.

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // 5 deðerini tutan geçici nesnenin ömrü, ref ile eþleþecek þekilde uzatýlýr

                        std::cout << ref << '\n'; // Bu nedenle, burada güvenli bir þekilde kullanabiliriz

                        return 0;
                    } // Hem ref hem de geçici nesne burada sona erer


Yukarýdaki örnekte, ref rvalue 5 ile baþlatýldýðýnda, bir geçici nesne oluþturulur ve ref bu geçici nesneye baðlanýr. Geçici nesnenin ömrü,
ref'in ömrüyle eþleþir. Bu nedenle, bir sonraki ifadede ref'in deðerini güvenli bir þekilde yazdýrabiliriz. Ardýndan, hem ref hem de geçici 
nesne, bloðun sonunda kapsam dýþýna çýkýp yok edilir.

Ana Ýpucu

- Lvalue referanslarý yalnýzca deðiþtirilebilir lvalue'lere baðlanabilir.
- Const lvalue referanslarý, deðiþtirilebilir lvalue'lere, deðiþtirilemeyen lvalue'lere ve rvalue'lere baðlanabilir. Bu, onlarý çok daha 
  esnek bir referans türü yapar.


Constexpr lvalue referanslar
----------------------------

Referansa uygulandýðýnda, constexpr referansýn bu referansýn bir sabit ifadesinde kullanýlmasýna izin verir. Constexpr referanslarýn belirli
bir kýsýtlamasý vardýr: yalnýzca statik süreye sahip nesnelere baðlanabilirler (ya global ya da static yerel deðiþkenler). Bu, derleyicinin
statik nesnelerin bellekte hangi konumda oluþturulacaðýný bildiði için o adresi derleme zamanýnda bir sabit olarak iþleyebilmesinden kaynaklanýr.

Constexpr referans, bir (non-static) yerel deðiþkene baðlanamaz. Bu, yerel deðiþkenlerin adresinin, tanýmlandýklarý fonksiyonun gerçekten
çaðrýldýðý zamana kadar bilinmediði için geçerlidir.

                    int g_x{5};

                    int main()
                    {
                        [[maybe_unused]] constexpr int& ref1{g_x}; // tamam, global deðiþkene baðlanabilir

                        static int s_x{6};
                        [[maybe_unused]] constexpr int& ref2{s_x}; // tamam, static yerel deðiþkene baðlanabilir

                        int x{6};
                        // [[maybe_unused]] constexpr int& ref3{x}; // derleme hatasý: non-static bir nesneye baðlanamaz

                        return 0;
                    }

Bir const deðiþkenine bir constexpr referans tanýmlarken, hem referansa (constexpr, referansa uygulanan) hem de referans yapýlan tipe
(const, referansýn hedeflediði tipe uygulanan) hem constexpr hem de const uygulamamýz gerekiyor.

                    int main()
                    {
                        static const int s_x { 6 }; // a const int
                        [[maybe_unused]] constexpr const int& ref2 { s_x }; // constexpr ve const ikiside gerekli

                        return 0;
                    }

Bu sýnýrlamalar göz önüne alýndýðýnda, constexpr referanslarý genellikle pek fazla kullanýlmaz.

12.5 — Sol deðer referansý argüman olarak kullanma
--------------------------------------------------
Neden bir deðiþkenin kendisini kullanmak yerine bir deðiþken için bir takma ad oluþturulsun ki?

Bu derste ve bundan sonraki derslerde bu konuyu açýklayacaðýz. Ýlk olarak, biraz baðlam. Daha önceki 2.4 dersinde - Fonksiyon Parametreleri
ve Argümanlarýna Giriþ'te, deðerle geçiþi tartýþtýk; bir fonksiyona iletilen bir argüman, fonksiyonun parametresine kopyalanýr:

                    #include <iostream>

                    void printDeger(int y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir

                    int main()
                    {
                        int x { 2 };

                        printDeger(x); // x, deðeri y parametresine (ucuz) aktarýlýr (kopyalanýr)

                        return 0;
                    }


Yukarýdaki programda, printDeger(x) çaðrýldýðýnda, x'in deðeri (2), parametre y içine kopyalanýr. Ardýndan, fonksiyonun sonunda y nesnesi yok 
edilir.

Bu, fonksiyonu çaðýrdýðýmýzda, argümanýn deðerinden bir kopya oluþturduðumuz ve ardýndan kýsa bir süre kullanýp yok ettiðimiz anlamýna gelir!
Neyse ki, temel tiplerin kopyalanmasý ucuz olduðundan, bu bir sorun teþkil etmez.

Bazý nesnelerin kopyalanmasý pahalý olabilir

Standart kütüphanenin saðladýðý çoðu tür (örneðin std::string) sýnýf türleridir. Sýnýf türleri genellikle kopyalamak pahalýdýr. Mümkünse,
özellikle bu kopyalarý neredeyse hemen yok edeceðimiz durumlarda, pahalý kopyalarýn gereksiz yaratýlmasýndan kaçýnmak istiyoruz.

Bu noktayý gösteren aþaðýdaki programý düþünün:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir 

                    int main()
                    {
                        std::string x { "Hello, world!" }; // x bir std::string türüdür

                        printValue(x); // x y parametresine deðer olarak geçildi ( pahalýdýr )

                        return 0;
                    }
                    Çýktý:
                    Hello, World!


Bu program beklediðimiz gibi davranýyor gibi görünse de, ayný zamanda verimsizdir. Önceki örnekle ayný þekilde, printValue() çaðrýldýðýnda,
argüman x printValue() parametresi y'e kopyalanýr. Ancak bu örnekte, argüman bir int yerine bir std::string'dir ve std::string, kopyalamasý
pahalý bir sýnýf türüdür. Ve bu pahalý kopya, her printValue() çaðrýldýðýnda yapýlýr!

Daha iyi yapabiliriz.

Referans ile argüman aktarma
----------------------------
Bir fonksiyonu çaðýrýrken argümanýn pahalý bir kopyasýný oluþturmaktan kaçýnmanýn bir yolu, deðer ile geçiþ yerine referans ile geçiþ kullanmaktýr.
Referans kullanýrken, bir fonksiyon parametresini normal bir tür olarak deðil, bir referans türü olarak (veya sabit referans türü olarak)
tanýmlarýz. Fonksiyon çaðrýldýðýnda, her referans parametresi uygun argümana baðlanýr. Referans, argüman için bir takma ad olarak hareket ettiði
için, argümanýn bir kopyasý oluþturulmaz.

Ýþte deðer ile geçiþ yerine referans ile geçiþ kullanýlarak yukarýdaki örneðin aynýsý:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string& y) // tür std::string& olarak deðiþtirildi
                    {
                        std::cout << y << '\n';
                    } // y burada yok edildi

                    int main()
                    {
                        std::string x { "Hello, world!" };

                        printValue(x); // Þimdi x deðeri y parametresine referans olarak geçildi ( aktarýldý ) ( pahalý deðil )

                        return 0;
                    }


Bu program, türü std::string olan parametre y'nin std::string& (bir sol deðer referansý) olarak deðiþtirilmiþ olan öncekine benziyor. Þimdi, 
printValue(x) çaðrýldýðýnda, sol deðer referans parametresi y, argüman x'e baðlanýr. Bir referansý baðlamak her zaman ucuzdur ve x'in bir kopyasý
yapýlmasýna gerek yoktur. Bir referans, referans edilen nesne için bir takma ad olarak hareket ettiði için, printValue() referans y'yi 
kullandýðýnda, gerçek argüman x'e eriþiyor (x'in bir kopyasý deðil).

Kilit nokta þudur ki; Referansa göre aktarma, fonksiyon her çaðrýldýðýnda bu argümanlarýn kopyalarýný oluþturmadan argümanlarý bir fonksiyona
iletmemize olanak tanýr.

Referansa göre geçiþ, bir argümanýn deðerini deðiþtirmemize olanak tanýr

Bir nesne deðere göre iletildiðinde, iþlev parametresi argümanýn bir kopyasýný alýr. Bu, parametrenin deðerinde yapýlan herhangi bir deðiþikliðin
argümanýn kendisine deðil, argümanýn kopyasýna yapýlacaðý anlamýna gelir:

                    #include <iostream>

                    void addOne(int y) // y, x'in kopyasýdýr
                    {
                        ++y; // Buradaki deðiþim x'in kopyasýna olacaktýr, gerçek x e deðil
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x deðiþtirilmedi

                        return 0;
                    }
Yukarýdaki programda y deðer parametresi x'in kopyasý olduðundan y'yi arttýrdýðýmýzda bu sadece y'yi etkiler. Bu programýn çýktýsý:

                    value = 5
                    value = 5

Bununla birlikte, bir referans, referans verilen nesneyle ayný þekilde davrandýðýndan, referansa göre geçiþ kullanýldýðýnda, referans
parametresinde yapýlan herhangi bir deðiþiklik baðýmsýz deðiþkeni etkileyecektir:

                    #include <iostream>

                    void addOne(int& y) // y gerçek x'e baðlý çünkü referans ediyor
                    {
                        ++y; // bu gerçek x'i deðiþtirecek
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x deðiþti

                        return 0;
                    }
                    Çýktýsý:
                    value = 5
                    value = 6


Yukarýdaki örnekte, x'in baþlangýçta deðeri 5'tir. addOne(x) çaðrýldýðýnda, referans parametresi y, argüman x'e baðlanýr. addOne() fonksiyonu
referans y'yi arttýrdýðýnda, aslýnda argüman x'i 5'ten 6'ya arttýrýyor (x'in bir kopyasý deðil). Bu deðiþen deðer, addOne() iþlemi tamamlandýktan
sonra bile devam eder.

Deðerleri const olmayanlara referansla iletmek, aktarýlan argümanlarýn deðerini deðiþtiren fonksiyonlar yazmamýza olanak tanýr.

Fonksiyonlarýn iletilen argümanlarýn deðerini deðiþtirebilme yeteneði oldukça faydalý olabilir. Hayal edin ki bir canavarýn oyuncuya baþarýyla
saldýrdýðýný belirleyen bir fonksiyon yazdýnýz. Öyleyse, canavar oyuncunun saðlýðýna bir miktar hasar vermelidir. Eðer oyuncu nesnesini referans
olarak iletiyorsanýz, fonksiyon, iletilen gerçek oyuncu nesnesinin saðlýðýný doðrudan deðiþtirebilir. Eðer oyuncu nesnesini deðer olarak
iletiyorsanýz, yalnýzca bir kopyanýn saðlýðýný deðiþtirebilirsiniz ki bu pek faydalý deðildir.


Referans ile geçiþ, yalnýzca deðiþtirilebilir sol deðer argümanlarý kabul edebilir

Çünkü bir referans, bir deðiþtirilebilir sol deðere (temelde bir const olmayan deðiþken) yalnýzca baðlanabilir, bu nedenle referans ile geçiþ,
yalnýzca deðiþtirilebilir sol deðerlerle çalýþýr demektir. Pratikte, bu, referans ile geçiþin const olmayanlara sýnýrlý faydasýný önemli ölçüde
sýnýrlar, çünkü const deðiþkenleri veya sabit ifadeleri iletimemiz mümkün deðildir. Örneðin:

                    #include <iostream>

                    void printValue(int& y) // y sadece deðiþtirilebilir lvalue kabul eder
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir deðiþtirilebilir lvalue deðiþkendir

                        const int z { 5 };
                        printValue(z); // error: z bir deðiþtirilebilir lvalue deðiþken deðildir

                        printValue(5); // error: 5 bir rvalue dir

                        return 0;
                    }

Neyse ki bunu aþmanýn kolay bir yolu var ve bunu bir sonraki derste tartýþacaðýz. Ayrýca ne zaman deðere göre geçileceðine ve ne zaman referansa 
göre geçileceðine de göz atacaðýz.

12.6 — Const sol deðer referansý ile geçiþ
------------------------------------------
Const olmayan bir referansýn aksine (yalnýzca deðiþtirilebilir sol deðerlere baðlanabilirken), bir const referans, deðiþtirilebilir sol deðerlere,
deðiþtirilemez sol deðerlere ve sað deðerlere baðlanabilir. Bu nedenle, bir referans parametreyi const yaparsak, her türlü argümana baðlanabilir 
hale gelecektir:

                    #include <iostream>

                    void printValue(const int& y) // Þimdi y bir const referans
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir deðiþtirilebilir lvalue

                        const int z { 5 };
                        printValue(z); // ok: z bir deðiþtirilemez lvalue

                        printValue(5); // ok: 5 bir literal rvalue

                        return 0;
                    }

Const referans ile geçiþ, referans ile geçiþin temel avantajýný (argümanýn bir kopyasýný oluþturmadan) sunarken, ayný zamanda fonksiyonun 
referans yapýlan deðeri deðiþtiremeyeceðini garanti eder.

Örneðin, aþaðýdaki durum const olduðu için izin verilmez:

                    void addOne(const int& ref)
                    {
                        ++ref; // Ýzin verilmemiþtir: Ref bir const çünkü
                    }

Çoðu durumda fonksiyonlarýmýzýn argümanlarýn deðerini deðiþtirmesini istemeyiz.

*** BEST -> Aksini yapmak için özel bir nedeniniz olmadýkça (örneðin, iþlevin bir argümanýn deðerini deðiþtirmesi gerekiyorsa), const referansý 
            ile geçiþ'i, const olmayan referans ile geçiþ yerine tercih edin.

Artýk sabit deðer referanslarýnýn deðerlere baðlanmasýna izin vermenin motivasyonunu anlayabiliriz: bu yetenek olmasaydý, referans yoluyla geçiþ
kullanan iþlevlere deðiþmez deðerleri (veya diðer deðerleri) aktarmanýn bir yolu olmazdý!


Deðer ile geçiþ ve referans ile geçiþi karýþtýrma ( Birlikte kullanmak )
------------------------------------------------------------------------
Çoklu parametreye sahip bir fonksiyon, her parametrenin ayrý ayrý deðer ile mi yoksa referans ile mi iletildiðini belirleyebilir.

Örneðin:

                    #include <string>

                    void foo(int a, int& b, const std::string& c)
                    {
                    }

                    int main()
                    {
                        int x { 5 };
                        const std::string s { "Hello, world!" };

                        foo(5, x, s);

                        return 0;
                    }
Yukarýdaki örnekte, ilk argüman deðere göre, ikincisi referansa göre ve üçüncüsü const referansýna göre iletilir.


(const) referans ile geçiþ ne zaman yapýlmalýdýr
------------------------------------------------
Çünkü sýnýf türleri kopyalamak pahalý olabilir (bazen önemli ölçüde), genellikle sýnýf türleri argümanýn pahalý bir kopyasýný oluþturmaktan
kaçýnmak için deðer yerine const referans ile iletilir. Temel tipler kopyalamak ucuz olduðundan genellikle deðer ile iletilir.
*** BEST 
--------
Ýlke olarak, temel tipleri deðer ile, sýnýf (veya yapý) tiplerini ise const referans ile iletmek genellikle uygundur.

Diðer yaygýn tipleri deðer ile iletmek: numaralandýrma tipleri ve std::string_view.
Diðer yaygýn tipleri (const) referans ile iletmek: std::string, std::array ve std::vector.

Fonksiyon parametreleri için, çoðu durumda const std::string& yerine std::string_view'i tercih edin
---------------------------------------------------------------------------------------------------

Modern C++ içinde sýkça karþýlaþýlan bir soru: Bir string parametresine sahip bir fonksiyon yazýlýrken, parametrenin türü const std::string& mý
yoksa std::string_view mý olmalýdýr?

Çoðu durumda, std::string_view daha iyi bir tercih olacaktýr, çünkü daha geniþ bir argüman türü yelpazesini verimli bir þekilde iþleyebilir.

                    void doSomething(const std::string&);
                    void doSomething(std::string_view);   // Çoðu durumda bunu tercih edin

const std::string& parametresini kullanmanýn daha uygun olabileceði birkaç durum vardýr:

1 - Eðer C++14 veya daha eski bir sürüm kullanýyorsanýz, std::string_view mevcut deðilse.

2 - Eðer fonksiyonunuz, C tarzý bir diziyi veya std::string parametresi alan baþka bir fonksiyonu çaðýrmasý gerekiyorsa, o zaman 
    const std::string& daha iyi bir seçenek olabilir, çünkü std::string_view'ýn null karakteri ile sona erdirilmiþ (C tarzý dizi 
    iþlevlerinin beklediði þey) olmasý garanti edilmemiþtir ve std::string'e verimli bir þekilde dönüþtürülmez.

std::string& yerine std::string_view (deðer olarak) kullanarak stringleri iletmeyi tercih edin, ancak fonksiyonunuzun C tarzý dizileri veya
std::string parametreleri gerektiren diðer fonksiyonlarý çaðýrdýðý durumlar hariç.

12.6 -> Geliþmiþ geliþtiriciler için bir kaç not bulunmakta bunlarý 12 tamamen bitmesi ve diðer durumlarda inceleyeceðim çünkü þuan bakarak bir 
        çoðunu anlamayacaðýz.
*/