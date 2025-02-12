#include <iostream>

int main()
{

    
    return 0;
}
/*
                                                12.1 — Bileşik Veri Türlerine Giriş
                                                -----------------------------------


4.1 dersinde -- Temel veri türlerine giriş, C++'ın temel dil bölümü olarak sağladığı temel veri türlerini tanıttık.

Bu temel türleri özellikle int veri türünü şimdiye kadar programlarımızda sıkça kullanmıştık. Ve bu temel türler basit kullanımlar için son derece
kullanışlı olsalar da, daha karmaşık işler yapmaya başladığımızda tüm ihtiyaçlarımızı kapsamazlar.

Örneğin, iki kesiri çarpmak için bir matematik programı yazıyormuş gibi düşünün. Programınızda bir kesiri nasıl temsil edersiniz? Muhtemelen bir
çift tamsayı kullanırdınız (pay için bir tane, payda için bir tane), şu şekilde:

                    #include <iostream>

                    int main()
                    {
                        // İlk kesirimiz
                        int sayi1 {};
                        int payda1 {};

                        // İkinci kesirimiz
                        int sayi2 {};
                        int payda2 {};

                        // pay ve payda arasındaki slash'ı (eğik çizgi) kaldırmak için kullanılır
                        char yoket {};

                        // Kullanıcıdan ilk kesiri girmesini isteyen bir çıkış
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi1 >> yoket >> payda1;

                        // Kullanıcıdan ikinci kesiri girmesini isteyen bir çıkış
                        std::cout << "Bir kesir girin: ";
                        std::cin >> sayi2 >> yoket >> payda2;

                        // İki kesirin çarpımını hesaplayıp ekrana yazdıran bir çıkış
                        std::cout << "İki kesirin çarpımı: "
                            << sayi1 * sayi2 << '/' << payda1 * payda2 << '\n';

                        return 0;
                    }
                    Çıktısı:
                    Bir kesir girin: 1/2
                    Bir kesir girin: 3/4
                    İki kesirin çarpımı: 3/8

Bu program çalışsa da, üzerinde iyileştirmeler yapmamız gereken bazı zorlukları ortaya çıkarır. İlk olarak, her çift tamsayı arasında sadece 
gevşek bir bağlantı vardır -- yorumlar ve kod içinde nasıl kullanıldıkları bağlamı dışında, her pay ve payda çiftinin ilişkili olduğuna dair
pek bir şey yoktur. İkinci olarak, DRY (kendini tekrar etme) ilkesini izleme konusunda, bir fonksiyon oluşturmalıyız ki bu fonksiyon kullanıcının
bir kesiri girmesini ele alsın (ve bazı hata işleme işlemleri de içersin). Ancak, fonksiyonlar yalnızca tek bir değer döndürebilir, peki payyı ve
paydayı çağıran yere nasıl geri döndürebiliriz?

Şimdi başka bir durumu düşünün; çalışan kimliklerini tutan bir program yazmanız gerekiyor. Bunun için nasıl bir şey denersiniz? Belki de şöyle 
bir şey denersiniz:

                    int main()
                    {
                        int id1 { 42 };
                        int id2 { 57 };
                        int id3 { 162 };
                        // ave böylece devam edersiniz
                    }

Ancak, 100 çalışanınız olsaydı ne olurdu? İlk olarak, 100 değişken adını yazmanız gerekecekti. Ve eğer hepsini yazdırmamız veya bir işleme
geçirmemiz gerekiyorsa? Bu durumda çok fazla yazı yazmak zorunda kalırdık. Bu basitçe ölçeklenemez.

Açıkça temel veri tipleri bizi sadece belirli bir noktaya kadar götürecektir.

compound data types - Bileşik veri türleri
------------------------------------------
Neyse ki, C++, bileşik veri tipleri adı verilen ikinci bir veri tipi kümesini destekler. Bileşik veri tipleri, temel veri tiplerinden (veya diğer
bileşik veri tiplerinden) oluşturulabilen veri tipleridir. Her bileşik veri tipinin kendi benzersiz özellikleri vardır.

Bu bölümde ve gelecekteki bölümlerde göstereceğimiz gibi, bileşik veri tiplerini yukarıda sunduğumuz tüm zorlukları zarif bir şekilde çözmek için
kullanabiliriz.

C++ aşağıdaki bileşik türlerini destekler:

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

Zaten düzenli olarak bir bileşik türü kullanıyorsunuz: Fonksiyonlar. Örneğin şu fonksiyonu göz önünde bulundurun:

                    void doSomething(int x, double y)
                    {
                    }

12.2 — Değer Kategorileri (L-değerleri ve R-değerleri)
------------------------------------------------------
1.10 dersinde -- İfadelerin Tanıtımı, bir ifadeyi "birleşik sayılar, değişkenler, operatörler ve tek bir değer üretebilmek 
için çalıştırılabilir fonksiyon çağrılarının bir kombinasyonu" olarak tanımlamıştık.

                    #include <iostream>

                    int main()
                    {
                        std::cout << 2 + 3 << '\n'; // 2 + 3 ifadesi 5 değerini üretir

                        return 0;
                    }

Yukarıdaki ifade de 2 + 3 ifadesi 5 değerini üretir ve sonrasında konsola yazdırır.ayrıca ifadelerin, ifadeden daha uzun ömürlü yan etkiler 
üretebileceğini de belirttik:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        ++x; // Bu ifadenin yan etkisi x in arttırılmasıdır
                        std::cout << x << '\n'; // Burada 6 yazar

                        return 0;
                    }


Yukarıdaki programda, ifade ++x ifadesi x'in değerini artırır ve bu değer, ifadenin değerlendirmesi tamamlandıktan sonra bile değişmiş olarak 
kalır.

Değer üretmenin ve yan etkilere neden olmanın yanı sıra, ifadeler bir şey daha yapabilir: nesneleri veya fonksiyonları değerlendirebilirler.


İfadelerin Özellikleri
----------------------

İfadelerin nasıl değerlendirilmesi gerektiğini ve nerede kullanılabileceklerini belirlemek için C++'taki tüm ifadelerin iki özelliği vardır: 
bir tür (type) ve bir değer kategorisi (value category).

İfadelerin Türü
---------------

Bir ifadenin türü, değerlendirilen ifadeden elde edilen değerin, nesnenin veya işlevin türüne eşdeğerdir. Örneğin:
                    int main()
                    {
                        auto v1 { 12 / 4 }; // int / int => int
                        auto v2 { 12.0 / 4 }; // double / int => double

                        return 0;
                    }


v1 için derleyici (derleme zamanında), iki int operatörü ile yapılan bir bölmenin bir int sonucu üreteceğini belirleyecektir, bu nedenle bu 
ifadenin türü int'tir. Tür çıkarımı yoluyla, int daha sonra v1'in türü olarak kullanılacaktır.

v2 için derleyici (derleme zamanında), bir double operatörü ve bir int operatörü ile yapılan bir bölmenin bir double sonuç üreteceğini 
belirleyecektir. Aritmetik operatörlerin eşleşen türlerde operandlara ihtiyacı olduğunu unutmayın, bu nedenle bu durumda int operatörü
double'a dönüştürülür ve bir kayan nokta bölme işlemi gerçekleştirilir. Bu nedenle bu ifadenin türü double'dir.

Derleyici, bir ifadenin türünü kullanarak bir ifadenin belirli bir bağlamda geçerli olup olmadığını belirleyebilir. Örneğin:

                    #include <iostream>

                    void print(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        print("foo"); // hata: print() bir int argüman bekliyordu, biz bir string literal i göndermeye çalıştık

                        return 0;
                    }


Yukarıdaki programda, print(int) fonksiyonu bir int parametresi bekliyor. Ancak, iletişimde bulunduğumuz ifadenin türü (string literal
"foo") eşleşmiyor ve herhangi bir dönüşüm bulunamıyor. Bu nedenle bir derleme hatası meydana gelir.

Bir ifadenin türü, derleme zamanında belirlenebilmelidir (aksi takdirde tür kontrolü ve tür çıkarımı çalışmaz) - ancak bir ifadenin değeri, 
ifade constexpr ise derleme zamanında veya değilse çalışma zamanında belirlenebilir.

Bir ifadenin değer kategorisi
------------------------------

Şimdi aşağıdaki programı düşünün:

                    int main()
                    {
                        int x{};

                        x = 5; // geçerli: x e 5 değerini atayabiliriz
                        5 = x; // hata: x in değerini 5 e atayamayız

                        return 0;
                    }


Bir atama ifadesine hangi tarafın geçerli olduğunu (değişken x'e değeri 5 atama) ve hangisinin geçerli olmadığını (x'in değerini 5'in kendi 
anlamına atamak ne anlama gelir?) belirlemek için derleyici nasıl bilir?

Cevap, ifadelerin ikinci özelliğinde yatar: değer kategorisi. Bir ifadenin (veya alt ifadenin) değer kategorisi, bir ifadenin bir değere, 
bir fonksiyona veya bir nesneye çözünüp çözünmediğini gösterir.

C++11 öncesinde, yalnızca iki olası değer kategorisi vardı: lvalue ve rvalue.

C++11'de, hareket semantiğini ( move semantic ) desteklemek için üç ek değer kategorisi (glvalue, prvalue ve xvalue) eklenmiştir.

Lvalue ve rvalue ifadeleri
--------------------------

Lvalue (okunuşu "ell-value", "sol değer ( left value )" veya "bulucu değeri ( locater value )" için kısaltma, bazen "l-value" olarak yazılır), 
tanımlanabilir bir nesne veya işlevin (veya bit alanının) değerini döndüren bir ifadedir.

kimlik( identity ) terimi  C++ standardında kullanılır, ancak iyi tanımlanmamıştır. Bir kimliğe sahip bir varlık (örneğin bir nesne veya fonksiyon),
genellikle varlığın adreslerini karşılaştırarak diğer benzer varlıklardan ayırt edilebilir.

Kimliğe sahip varlıklar bir tanımlayıcı, referans veya işaretçi ( pointer ) aracılığıyla erişilebilir ve genellikle bir ifade veya
deyimden daha uzun bir ömre sahiptir.

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


Yukarıdaki programda, x ifadesi bir lvalue ifadesidir çünkü değişken x'in değerini değerlendirir (ki bu bir tanımlayıcıya sahiptir).

Dilin içine sabitlerin tanıtılmasından bu yana, lvalues iki alt türe ayrılmaktadır: değiştirilebilir bir lvalue, değeri değiştirilebilen
bir lvalue'dir. Değiştirilemez bir lvalue ise (çünkü lvalue const veya constexpr ise) değeri değiştirilemeyen bir lvalue'dir.

                    int main()
                    {
                        int x{};
                        const double d{};
                        int y { x }; // x değiştirilebilir bir lvaluedir
                        const double e { d }; // d değiştirilemez bir lvaluedir

                        return 0;
                    }

Rvalue ("arr-value" olarak okunan, "right value"ın kısaltması ve bazen r-value olarak yazılan) bir ifade, bir lvalue olmayan bir ifadedir.
Rvalue ifadeler bir değere çözünür. Sıkça karşılaşılan rvalue'ler arasında literaller bulunur (C tarzı dizge literalleri hariç, çünkü bunlar
lvalue'dir) ve değer ile dönen fonksiyonların ve operatörlerin dönüş değerleri bulunur. Rvalue'lar tanımlanabilir değildir (yani hemen
kullanılmalıdır) ve yalnızca kullanıldıkları ifade kapsamında var olurlar.

                    int return5()
                    {
                        return 5;
                    }

                    int main()
                    {
                        int x{ 5 }; // 5 bir rvalue ifadesidir
                        const double d{ 1.2 }; // 1.2 bir rvalue ifadesidir

                        int y { x }; // x değiştirilebilir bir lvalue ifadesidir
                        const double e { d }; // d değiştirilemez bir lvalue ifadesidir
                        int z { return5() }; // return5(), sonuç değeri ile döndürüldüğü için bir rvalue ifadesidir

                        int w { x + 1 }; // x + 1 bir rvalue ifadesidir
                        int q { static_cast<int>(d) }; // d'yi int'e static_cast etmenin sonucu bir rvalue ifadesidir

                        return 0;
                    }

Belki de return5(), x + 1 ve static_cast<int>(d) ifadelerinin neden rvalue olduğunu merak ediyorsunuz: cevap, bu ifadelerin tanımlanabilir
nesneler olmayan geçici değerler üretmesidir.

Ana İpucu

Lvalue ifadeler, tanımlanabilir bir nesneye çözünür.
Rvalue ifadeler, bir değere çözünür.

Şimdi x = 5'in neden geçerli olduğu ancak 5 = x'in neden geçerli olmadığı sorusunu cevaplayabiliriz: atama işlemi, atamanın sol operandının
değiştirilebilir bir lvalue ifadesi olmasını ve sağ operandın bir rvalue ifadesi olmasını gerektirir. İkinci atama (5 = x) başarısızdır
çünkü sol operand ifadesi 5 bir lvalue değildir.

                    int main()
                    {
                        int x{};

                        // Atama işlemi, sol operandın değiştirilebilir bir lvalue ifadesi olmasını ve sağ operandın bir rvalue ifadesi
                        olmasını gerektirir
                        x = 5; // geçerli: x değiştirilebilir bir lvalue ifadesi ve 5 bir rvalue ifadesidir
                        5 = x; // hata: 5 bir rvalue ifadesi iken x değiştirilebilir bir lvalue ifadesidir

                        return 0;
                    }

İşte lvalue ve rvalue ifadelerinin tam bir listesi https://en.cppreference.com/w/cpp/language/value_category . C++11'de rvalue'lar iki alt türe 
ayrılmıştır: prvalue'lar ve xvalue'lar, bu nedenle burada bahsettiğimiz rvalue'lar, bu iki kategori toplamının birleşimidir.

Tavsiye -> Eğer bir ifadenin bir lvalue mi yoksa rvalue mi olduğundan emin değilseniz, operator& kullanarak onun adresini almaya çalışın. 
           Çünkü operator&, operandının bir lvalue olmasını gerektirir. Eğer &(ifade); derlemesi başarılı oluyorsa, ifade bir lvalue olmalıdır:

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

Ana İpucu

Bir C tarzı string literali, C tarzı stringler (ki bunlar C tarzı arraylerdir) bir işaretçiye dönüşmesinden dolayı bir lvalue'dir. Dönüşüm süreci,
arrayin bir lvalue olması durumunda çalışır (ve bu nedenle işaretçide depolanabilecek bir adresi vardır). C++ bunu geriye uyumluluk için miras
almıştır.

Lvalue'dan rvalue'ye dönüşüm
----------------------------
Bu örneğe tekrar bakalım:

                    int main()
                    {
                        int x { 5 };
                        int y { x }; // x bir lvalue ifadesidir

                        return 0;
                    }


Eğer x, değişken x'e değeri olan bir lvalue ifadesiyse, y neden değeri 5 olur?

Cevap, lvalue ifadelerinin, bir rvalue beklenirken ancak bir lvalue sağlandığında otomatik olarak rvalue ifadelere dönüştürülmesidir. 
Bir int değişkeninin başlatıcısı bir rvalue ifadesi olması beklenir. Bu nedenle, lvalue ifadesi x, bir lvalue'den rvalue'ye dönüşüm geçirir,
bu da değeri 5 olan bir değere çözünür ve ardından y'yi başlatmak için kullanılır.

Yukarıda belirtildiği gibi atama operatörünün sağ operandının bir rvalue ifadesi olmasını bekledik, peki neden bu tür kod işe yarıyor?

                    int main()
                    {
                        int x{ 1 };
                        int y{ 2 };

                        x = y; // y değiştirilebilir bir lvalue dir, bir rvalue değil, Ama bu geçerlidir

                        return 0;
                    }

Bu durumda, y bir lvalue ifadesidir, ancak bir lvalue-to-rvalue dönüşümüne uğrar, bu da y'nin değerini (2) çözünmesine yol açar, ardından bu 
değer x'e atanır.

Şimdi bu örneği düşünelim:

                    int main()
                    {
                        int x { 2 };

                        x = x + 1;

                        return 0;
                    }

Bu ifadede, değişken x iki farklı bağlamda kullanılmaktadır. Atama operatörünün sol tarafında, x değişken x değeri olan bir lvalue ifadesidir.
Atama operatörünün sağındaysa, x + 1, değeri 3 olan bir rvalue ifadesine çözünen bir ifadedir.

Şimdi lvalue'ları ele aldığımıza göre, ilk bileşik türümüze gelebiliriz: lvalue referansı.

Ana İpucu

Lvalue ve rvalue ifadelerini tanımlamak için bir kural:

Lvalue ifadeler, ifade sona erdikten sonra varlığını sürdürebilen değişkenlere veya diğer tanımlanabilir nesnelere çözünenlerdir.
Rvalue ifadeler, ifade sona erdikten sonra atılacak olan literalleri veya fonksiyonlar/operatörler tarafından döndürülen değerleri çözünenlerdir.

12.3 — Lvalue references
------------------------

C++ dilinde, bir referans mevcut bir nesnenin takma adıdır. Bir referans bir kez tanımlandığında, referans üzerinde yapılan herhangi bir işlem,
referans yapılan nesneye uygulanır.

Kilit nokta; Bir referans, temelde üzerine referans yapılan nesne ile özdeştir.


Bu, bir referansı üzerine referans yapılan nesneyi okumak veya değiştirmek için kullanabileceğimiz anlamına gelir. Başta referanslar saçma veya gereksiz gibi görünebilir, ancak C++'ta referanslar her yerde kullanılır (bunu birkaç derste göreceğiz).

Ayrıca, fonksiyonlara referanslar da oluşturabilirsiniz, ancak bu daha az sık yapılır.

Modern C++, iki tür referans içerir: lvalue referansları ve rvalue referansları. Lvalue ile devam edelim.

Lvalue referans türleri
-----------------------
Bir lvalue referansı (genellikle C++11'den önce yalnızca bir türde referans olduğu için sadece referans olarak adlandırılır), mevcut bir lvalue
(örneğin bir değişken) için bir takma ad olarak hareket eder.

Bir lvalue referans türünü bildirmek için, tür bildiriminde bir ampersand (&) kullanırız:

                    int      // normal bir int türü
                    int&     // bir int nesnesine yapılan bir lvalue referans
                    double&  // bir double nesnesine yapılan bir lvalue referans


Lvalue referans değişkenleri
----------------------------
Lvalue referans türü ile yapabileceğimiz şeylerden biri, bir lvalue referans değişkeni oluşturmaktır. Bir lvalue referans değişkeni, 
genellikle başka bir değişkenin referansı olarak hareket eden bir değişkendir.

Bir lvalue referans değişkeni oluşturmak için, basitçe bir değişkeni bir lvalue referans türü ile tanımlarız:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };    // x, normal bir tamsayı değişkenidir
                        int& ref { x }; // ref, şimdi değişken x için bir takma ad olarak kullanılabilen bir lvalue referans değişkenidir

                        std::cout << x << '\n';  // x'in değerini yazdır (5)
                        std::cout << ref << '\n'; // ref üzerinden x'in değerini yazdır (5)

                        return 0;
                    }

Yukarıdaki örnekte, int& türü ref'i bir int'e referans olan bir lvalue referans olarak tanımlarız, ardından lvalue ifadesini x ile başlatırız.
Bundan sonra, ref ve x eşanlamlı olarak kullanılabilir. Bu program şu şekilde çıktı verir:

                    5
                    5

Derleyicinin bakış açısından, ampersand'ın tip adına (int& ref) mı yoksa değişken adına (int &ref) "bağlı" olması önemli değildir ve seçim tarza
bağlıdır. Modern C++ programcıları, referansın tip bilgisinin bir parçası olduğunu, tanımlanan değişkenin adı olmadığını daha açık bir şekilde
ifade etmek için genellikle ampersand'ı tipin yanına koymayı tercih eder.

*** BEST -> Bir referans tanımlarken, ampersand'ı referans değişkeninin adının yanına değil, tipin yanına koymak en iyisidir.


Değerleri bir lvalue referans üzerinden değiştirme
--------------------------------------------------
Yukarıdaki örnekte, bir referansı üzerine referans yapılan nesnenin değerini okumak için kullanabileceğimizi gösterdik. Aynı zamanda bir referansı
kullanarak üzerine referans yapılan nesnenin değerini değiştirebiliriz:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsayı değişkeni
                        int& ref { x }; // ref, şimdi değişken x için bir takma ad

                        std::cout << x << ref << '\n'; // 55 yazdır

                        x = 6; // x'in değeri şimdi 6

                        std::cout << x << ref << '\n'; // 66 yazdır

                        ref = 7; // üzerine referans yapılan nesne (x) şimdi değeri 7

                        std::cout << x << ref << '\n'; // 77 yazdır

                        return 0;
                    }
                    Çıktı:
                    55
                    66
                    77

Yukarıdaki örnekte, ref x için bir takma ad olduğundan dolayı x'in değerini ya x üzerinden ya da ref üzerinden değiştirebiliyoruz.

Lvalue referanslarının başlatılması
-----------------------------------

Sabitler gibi, tüm referanslar başlatılmalıdır.

                    int main()
                    {
                        int& invalidRef;   // hata: referanslar başlatılmalıdır

                        int x { 5 };
                        int& ref { x }; // tamam: int referansı, int değişkenine bağlanır

                        return 0;
                    }


Bir referans, bir nesne (veya fonksiyon) ile başlatıldığında, o referansın o nesneye (veya fonksiyona) bağlandığını söyleriz. Bu tür bir referansın
bağlanma sürecine referans bağlama denir. Referans yapılan nesne (veya fonksiyon) bazen referansta bulunan olarak adlandırılır.

Lvalue referansları, değiştirilebilir bir lvalue'a bağlanmalıdır.
                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // geçerli: değiştirilebilir bir lvalue'a bağlanan bir lvalue referansı

                        const int y { 5 };
                        int& invalidRef { y };  // geçersiz: değiştirilemez bir lvalue'a bağlanamaz
                        int& invalidRef2 { 0 }; // geçersiz: bir rvalue'a bağlanamaz

                        return 0;
                    }

Lvalue referansları, değiştirilemez lvalue'lara veya rvalue'lara bağlanamaz (aksi takdirde referans aracılığıyla bu değerleri değiştirebilir ve 
bu da const durumlarına aykırı olurdu). Bu nedenle, lvalue referansları zaman zaman lvalue referanslarına non-const (bazen non-const referans 
olarak kısaltılır) olarak adlandırılır.

Çoğu durumda, referansın türü, referansta bulunan nesnenin türü ile eşleşmelidir (bu kuralın bazı istisnaları vardır, bunları miras konusunu
ele aldığımızda tartışacağız):

                    int main()
                    {
                        int x { 5 };
                        int& ref { x }; // tamam: int referansı, int değişkenine bağlanır

                        double y { 6.0 };
                        int& invalidRef { y }; // geçersiz; int referansı, double değişkenine bağlanamaz
                        double& invalidRef2 { x }; // geçersiz: double referansı, int değişkenine bağlanamaz

                        return 0;
                    }

Lvalue referanslarından void'a izin verilmez (bu ne anlama gelir ki?).

Referanslar yeniden yerleştirilemez (başka bir nesneyi işaret etmek üzere değiştirilemez)
------------------------------------------------------------------------------------------
C++'ta bir referans bir kez başlatıldıktan sonra yeniden yerleştirilemez, yani başka bir nesneye referans yapacak şekilde değiştirilemez.

Yeni C++ programcıları genellikle referansı başka bir değişkenle yer değiştirmek için atama kullanarak yeniden yerleştirmeye çalışırlar. 
Bu derlenir ve çalışır ancak beklenen şekilde işlev göstermez. Aşağıdaki programı düşünün:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };
                        int y { 6 };

                        int& ref { x }; // ref, şimdi x için bir takma ad

                        ref = y; // x'in (ref tarafından referans yapılan nesnenin) değerini 6 (y'nin değeri) olarak atar
                        // Yukarıdaki satır, ref'i y değişkenine referans yapacak şekilde DEĞİŞTİRMEZ!

                        std::cout << x << '\n'; // kullanıcı bunun 5'i yazdırmasını bekliyor

                        return 0;
                    }
                    Çıktı:
                    6

Bir referans bir ifadede değerlendirildiğinde, referans yaptığı nesneye çözülür. Bu nedenle, ref = y, ref'i şimdi y'ye referans yapacak şekilde
değiştirmez. Tam tersine, çünkü ref x için bir takma ad, ifade, x = y şeklinde yazılmış gibi değerlendirilir -- ve çünkü y'nin değeri 6 ise,
x'e değer 6 atanır.

Lvalue reference kapsam and süre
--------------------------------

Lvalue referans değişkenleri, normal değişkenlerin uyguladığı kapsama ve süre kurallarını takip eder:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 }; // normal bir tamsayı
                        int& ref { x }; // değişkenin değerine referans

                        return 0;
                    } // x ve ref burada sona erer

Referanslar ve referans yapılan nesneler bağımsız ömürlere sahiptir.
--------------------------------------------------------------------
Bir istisna dışında (bunu bir sonraki derste ele alacağız), bir referansın ömrü ve referans yaptığı nesnenin ömrü bağımsızdır. 
Başka bir deyişle, her ikisi de aşağıdaki ifadeler doğrudur:

    1. Bir referans, ona referans yapılan nesneden önce yok edilebilir.
    2. Referans yapılan nesne, referanstan önce yok edilebilir.

Bir referans, referans yapılandan önce yok edildiğinde, referans yapılan nesneyi etkilemez. Örnek:

                    #include <iostream>

                    int main()
                    {
                        int x { 5 };

                        {
                            int& ref { x };   // ref, x'e referans yapan bir referanstır
                            std::cout << ref << '\n'; // ref'in değerini (5) yazdırır
                        } // ref burada yok edildi -- x bunun farkında değil

                        std::cout << x << '\n'; // x'in değerini (5) yazdırır

                        return 0;
                    } // x burada yok edildi
                    Çıktı:
                    5
                    5

"ref" öldüğünde, değişken x normal şekilde devam eder, neşe içinde, ona yapılan bir referansın yok edildiğinden habersiz.

Asılı referanslar
-----------------

Referans yapılan nesne, referansın kendisinden önce yok edildiği durumda, referans artık var olmayan bir nesneye işaret eder durumda
kalır. Böyle bir referansa "asılı referans" denir. Bir asılı referansa erişmek, tanımsız davranışa yol açar.

Asılı referanslardan kaçınmak oldukça basittir, ancak bunun pratikte nasıl gerçekleşebileceğini 12.12 dersinde göstereceğiz

Referanslar nesne değildir
--------------------------

Belki de şaşırtıcı bir şekilde, C++ dilinde referanslar nesneler değildir. Bir referansın var olması veya depolama alanını kaplaması gerekmez.
Mümkünse, derleyici, bir referansın tüm örneklerini referans yapan nesneyle değiştirerek referansları optimize etme eğilimindedir. Ancak bu her 
zaman mümkün olmayabilir ve böyle durumlarda referanslar depolama alanı gerektirebilir.

Bu aynı zamanda "referans değişkeni" teriminin biraz yanıltıcı olduğu anlamına gelir, çünkü değişkenler adı olan nesnelerdir ve referanslar 
nesneler değildir.

Çünkü referanslar nesneler değil, başka bir nesnenin adı olan referanslar, nesne gereken herhangi bir yerde kullanılamaz (örneğin, bir referansa 
referans olamazsınız, çünkü bir lvalue referansı tanımlanabilir bir nesneye referans yapmalıdır). Bir nesne veya tekrar yerleştirilebilen bir 
referans gerektiğinde, std::reference_wrapper (ki bunu 23.3 dersinde ele alacağız - Birleştirme) bir çözüm sunar.

Bir kenara not olarak...

Aşağıdaki değişkenleri düşünün:

                    int var{};
                    int& ref1{ var };  // var'a bağlı bir lvalue referansı
                    int& ref2{ ref1 }; // var'a bağlı bir lvalue referansı

Çünkü ref2 (bir referans) ref1 (bir referans) ile başlatılmıştır, ref2'nin bir referansın referansı olduğunu düşünebilirsiniz. Ancak öyle değil.
ref1, var'a referans olduğundan, bir ifadede (örneğin bir başlatıcıda) kullanıldığında, ref1 var'a değerlendirilir. Bu nedenle ref2, sadece var'a
bağlı normal bir lvalue referansıdır (türü int& olarak belirtilmiştir).

Bir referansın referansına (bir int'e) sahip olmak için int&& syntax'ı kullanılmalıdır - ancak C++, referansların referansını desteklemediği için
bu syntax C++11'de bir sağ taraf değeri referansını göstermek için kullanılmıştır (ki bunu 22.2 dersinde ele alıyoruz - R değeri referansları).

ref2'nin ref1 ile başlatılmasından dolayı ref2'nin bir referansın referansı gibi algılanabileceği ancak bu durumun gerçekleşmediği .
C++ dilinde referansların referanslarını desteklemez. int&& syntax'ı orijinalde bir referansın referansını ifade ediyordu, ancak C++11'de
bu syntax, sağ taraf değeri referansını (rvalue reference) ifade etmek için kullanılmaya başlandı.

12.4 - Lvalue referanslarını const lar ile kullanımı
----------------------------------------------------
                    int main()
                    {
                        const int x{5};    // x, değiştirilemez (const) bir lvalue'dir
                        int& ref{x};       // hata: ref, değiştirilemez lvalue'a bağlanamaz

                        return 0;
                    }

Bu durum, const bir değişkeni (x) değiştirmemize izin verecek bir const olmayan referans (ref) üzerinden değiştirmemize izin vermemek amacıyla 
engellenmiştir.

Ancak eğer bir const değişkene bir referans oluşturmak istiyorsak, normal bir lvalue referansı (const olmayan bir değere) yeterli olmayacaktır.

Bir lvalue referansının deklarasyonunda const anahtar kelimesini kullanarak, referansın işaret ettiği nesneyi const olarak ele almasını sağlarız.
Bu tür bir referans, bir const değere sahip bir lvalue referansı olarak adlandırılır (bazen bir const referansı veya sadece const olarak da 
adlandırılır). Const Lvalue referanslar, değiştirilemez lvalue'lara bağlanabilir:

                    int main()
                    {
                        const int x{5};        // x, değiştirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const değere sahip bir lvalue referansıdır

                        return 0;
                    }

Çünkü lvalue referanslarına const, üzerine referans yapılan nesneyi const olarak ele aldıkları için, referans yapılan değeri değiştirmek yerine 
sadece erişmek için kullanılabilirler:

                    #include <iostream>

                    int main()
                    {
                        const int x{5};        // x, değiştirilemez bir lvalue'dir
                        const int& ref{x};     // uygun: ref, bir const değere sahip bir const lvalue referansıdır

                        std::cout << ref << '\n'; // uygun: const nesneye erişebiliriz
                        ref = 6;                  // hata: const bir referans aracılığıyla bir nesneyi değiştiremeyiz

                        return 0;
                    }

Const ile başlatılmış, değiştirilebilir bir lvalue referansı
------------------------------------------------------------

Lvalue referansları const ile değiştirilebilir lvaluelara bağlanabilir. Bu durumda, referans aracılığıyla erişilen nesne const
olarak işlenir (ancak temeldeki nesne const olmasa bile):

                    #include <iostream>

                    int main()
                    {
                        int x{5};               // x, değiştirilebilir bir lvalue'dir
                        const int& ref{x};      // tamam: değiştirilebilir bir lvalue'a bir const referans bağlayabiliriz

                        std::cout << ref << '\n'; // tamam: nesneye const referans aracılığıyla erişebiliriz
                        // ref = 7;               // hata: bir const referans aracılığıyla bir nesneyi değiştiremeyiz

                        x = 6;                   // tamam: x, değiştirilebilir bir lvalue'dir, hala orijinal tanımlayıcı aracılığıyla
                                                    değiştirebiliriz

                        return 0;
                    }

Yukarıdaki programda, const referansı ref'i değiştirilebilir lvalue x'e bağladık. Ardından ref'i kullanarak x'e erişebiliriz, ancak ref const
olduğu için ref üzerinden x'in değerini değiştiremeyiz. Ancak, x'in değerini doğrudan (tanımlayıcı x kullanarak) değiştirebiliriz.

*** BEST -> Değiştirilmek istenen nesnenin modifikasyonu gerekmediği sürece, const lvalue referanslarını lvalue referanslarına tercih edin.

Const bir lvalue referansını rvalue ile başlatma
------------------------------------------------
Belki de şaşırtıcı bir şekilde, const lvalue referansları aynı zamanda rvalue'larla da bağlanabilir:

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // tamam: 5 bir rvalue'dir

                        std::cout << ref << '\n'; // 5'i yazdırır

                        return 0;
                    }

Bu durumda, geçici bir nesne oluşturulur ve rvalue ile başlatılır, ardından const referans o geçici nesneye bağlanır.

Geçici bir nesne (bazen anonim nesne olarak da adlandırılır), bir ifade içinde geçici olarak oluşturulan (ve sonra yok edilen) bir nesnedir.
Geçici nesnelerin hiçbir kapsamı yoktur (bu mantıklıdır, çünkü kapsam bir tanımlayıcının özelliğidir ve geçici nesnelerin bir tanımlayıcısı
yoktur). Bu, bir geçici nesnenin sadece oluşturulduğu noktada doğrudan kullanılabileceği anlamına gelir, çünkü bu noktadan ötesine referans
oluşturmanın bir yolu yoktur.

Const referanslar geçici nesnelere bağlandığında, geçici nesnenin ömrü uzatılır
-------------------------------------------------------------------------------

Genellikle, geçici nesneler oluşturuldukları ifadenin sonunda yok edilir.

Ancak yukarıdaki örnekte, rvalue 5'i tutmak için oluşturulan geçici nesnenin ref tarafından başlatılan ifadenin sonunda yok edilmesi durumunda
ne olacağını düşünelim. Referans ref, sallantıda (yok edilmiş bir nesneye referans) bırakılır ve ref'e erişmeye çalıştığımızda tanımsız davranış
elde ederiz.

Bu tür durumlarda sallantı referanslarından kaçınmak için C++'da özel bir kural vardır: Bir const lvalue referansı doğrudan bir geçici nesneye
bağlandığında, geçici nesnenin ömrü referansın ömrüyle eşleşecek şekilde uzatılır.

                    #include <iostream>

                    int main()
                    {
                        const int& ref{5}; // 5 değerini tutan geçici nesnenin ömrü, ref ile eşleşecek şekilde uzatılır

                        std::cout << ref << '\n'; // Bu nedenle, burada güvenli bir şekilde kullanabiliriz

                        return 0;
                    } // Hem ref hem de geçici nesne burada sona erer


Yukarıdaki örnekte, ref rvalue 5 ile başlatıldığında, bir geçici nesne oluşturulur ve ref bu geçici nesneye bağlanır. Geçici nesnenin ömrü,
ref'in ömrüyle eşleşir. Bu nedenle, bir sonraki ifadede ref'in değerini güvenli bir şekilde yazdırabiliriz. Ardından, hem ref hem de geçici 
nesne, bloğun sonunda kapsam dışına çıkıp yok edilir.

Ana İpucu

- Lvalue referansları yalnızca değiştirilebilir lvalue'lere bağlanabilir.
- Const lvalue referansları, değiştirilebilir lvalue'lere, değiştirilemeyen lvalue'lere ve rvalue'lere bağlanabilir. Bu, onları çok daha 
  esnek bir referans türü yapar.


Constexpr lvalue referanslar
----------------------------

Referansa uygulandığında, constexpr referansın bu referansın bir sabit ifadesinde kullanılmasına izin verir. Constexpr referansların belirli
bir kısıtlaması vardır: yalnızca statik süreye sahip nesnelere bağlanabilirler (ya global ya da static yerel değişkenler). Bu, derleyicinin
statik nesnelerin bellekte hangi konumda oluşturulacağını bildiği için o adresi derleme zamanında bir sabit olarak işleyebilmesinden kaynaklanır.

Constexpr referans, bir (non-static) yerel değişkene bağlanamaz. Bu, yerel değişkenlerin adresinin, tanımlandıkları fonksiyonun gerçekten
çağrıldığı zamana kadar bilinmediği için geçerlidir.

                    int g_x{5};

                    int main()
                    {
                        [[maybe_unused]] constexpr int& ref1{g_x}; // tamam, global değişkene bağlanabilir

                        static int s_x{6};
                        [[maybe_unused]] constexpr int& ref2{s_x}; // tamam, static yerel değişkene bağlanabilir

                        int x{6};
                        // [[maybe_unused]] constexpr int& ref3{x}; // derleme hatası: non-static bir nesneye bağlanamaz

                        return 0;
                    }

Bir const değişkenine bir constexpr referans tanımlarken, hem referansa (constexpr, referansa uygulanan) hem de referans yapılan tipe
(const, referansın hedeflediği tipe uygulanan) hem constexpr hem de const uygulamamız gerekiyor.

                    int main()
                    {
                        static const int s_x { 6 }; // a const int
                        [[maybe_unused]] constexpr const int& ref2 { s_x }; // constexpr ve const ikiside gerekli

                        return 0;
                    }

Bu sınırlamalar göz önüne alındığında, constexpr referansları genellikle pek fazla kullanılmaz.

12.5 — Sol değer referansı argüman olarak kullanma
--------------------------------------------------
Neden bir değişkenin kendisini kullanmak yerine bir değişken için bir takma ad oluşturulsun ki?

Bu derste ve bundan sonraki derslerde bu konuyu açıklayacağız. İlk olarak, biraz bağlam. Daha önceki 2.4 dersinde - Fonksiyon Parametreleri
ve Argümanlarına Giriş'te, değerle geçişi tartıştık; bir fonksiyona iletilen bir argüman, fonksiyonun parametresine kopyalanır:

                    #include <iostream>

                    void printDeger(int y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir

                    int main()
                    {
                        int x { 2 };

                        printDeger(x); // x, değeri y parametresine kopyalanır (ucuz)

                        return 0;
                    }


Yukarıdaki programda, printDeger(x) çağrıldığında, x'in değeri (2), parametre y içine kopyalanır. Ardından, fonksiyonun sonunda y nesnesi yok 
edilir.

Bu, fonksiyonu çağırdığımızda, argümanın değerinden bir kopya oluşturduğumuz ve ardından kısa bir süre kullanıp yok ettiğimiz anlamına gelir!
Neyse ki, temel tiplerin kopyalanması ucuz olduğundan, bu bir sorun teşkil etmez.

Bazı nesnelerin kopyalanması pahalı olabilir

Standart kütüphanenin sağladığı çoğu tür (örneğin std::string) sınıf türleridir. Sınıf türleri genellikle kopyalamak pahalıdır. Mümkünse,
özellikle bu kopyaları neredeyse hemen yok edeceğimiz durumlarda, pahalı kopyaların gereksiz yaratılmasından kaçınmak istiyoruz.

Bu noktayı gösteren aşağıdaki programı düşünün:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string y)
                    {
                        std::cout << y << '\n';
                    } // y burada yok edilir 

                    int main()
                    {
                        std::string x { "Hello, world!" }; // x bir std::string türüdür

                        printValue(x); // x y parametresine değer olarak geçildi ( pahalıdır )

                        return 0;
                    }
                    Çıktı:
                    Hello, World!


Bu program beklediğimiz gibi davranıyor gibi görünse de, aynı zamanda verimsizdir. Önceki örnekle aynı şekilde, printValue() çağrıldığında,
argüman x printValue() parametresi y'e kopyalanır. Ancak bu örnekte, argüman bir int yerine bir std::string'dir ve std::string, kopyalaması
pahalı bir sınıf türüdür. Ve bu pahalı kopya, her printValue() çağrıldığında yapılır!

Daha iyi yapabiliriz.

Referans ile argüman aktarma
----------------------------
Bir fonksiyonu çağırırken argümanın pahalı bir kopyasını oluşturmaktan kaçınmanın bir yolu, değer ile geçiş yerine referans ile geçiş kullanmaktır.
Referans kullanırken, bir fonksiyon parametresini normal bir tür olarak değil, bir referans türü olarak (veya sabit referans türü olarak)
tanımlarız. Fonksiyon çağrıldığında, her referans parametresi uygun argümana bağlanır. Referans, argüman için bir takma ad olarak hareket ettiği
için, argümanın bir kopyası oluşturulmaz.

İşte değer ile geçiş yerine referans ile geçiş kullanılarak yukarıdaki örneğin aynısı:

                    #include <iostream>
                    #include <string>

                    void printValue(std::string& y) // tür std::string& olarak değiştirildi
                    {
                        std::cout << y << '\n';
                    } // y burada yok edildi

                    int main()
                    {
                        std::string x { "Hello, world!" };

                        printValue(x); // Şimdi x değeri y parametresine referans olarak geçildi ( aktarıldı ) ( pahalı değil )

                        return 0;
                    }


Bu program, türü std::string olan parametre y'nin std::string& (bir sol değer referansı) olarak değiştirilmiş olan öncekine benziyor. Şimdi, 
printValue(x) çağrıldığında, sol değer referans parametresi y, argüman x'e bağlanır. Bir referansı bağlamak her zaman ucuzdur ve x'in bir kopyası
yapılmasına gerek yoktur. Bir referans, referans edilen nesne için bir takma ad olarak hareket ettiği için, printValue() referans y'yi 
kullandığında, gerçek argüman x'e erişiyor (x'in bir kopyası değil).

Kilit nokta şudur ki; Referansa göre aktarma, fonksiyon her çağrıldığında bu argümanların kopyalarını oluşturmadan argümanları bir fonksiyona
iletmemize olanak tanır.

Referansa göre geçiş, bir argümanın değerini değiştirmemize olanak tanır

Bir nesne değere göre iletildiğinde, işlev parametresi argümanın bir kopyasını alır. Bu, parametrenin değerinde yapılan herhangi bir değişikliğin
argümanın kendisine değil, argümanın kopyasına yapılacağı anlamına gelir:

                    #include <iostream>

                    void addOne(int y) // y, x'in kopyasıdır
                    {
                        ++y; // Buradaki değişim x'in kopyasına olacaktır, gerçek x e değil
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x değiştirilmedi

                        return 0;
                    }
Yukarıdaki programda y değer parametresi x'in kopyası olduğundan y'yi arttırdığımızda bu sadece y'yi etkiler. Bu programın çıktısı:

                    value = 5
                    value = 5

Bununla birlikte, bir referans, referans verilen nesneyle aynı şekilde davrandığından, referansa göre geçiş kullanıldığında, referans
parametresinde yapılan herhangi bir değişiklik bağımsız değişkeni etkileyecektir:

                    #include <iostream>

                    void addOne(int& y) // y gerçek x'e bağlı çünkü referans ediyor
                    {
                        ++y; // bu gerçek x'i değiştirecek
                    }

                    int main()
                    {
                        int x { 5 };

                        std::cout << "value = " << x << '\n';

                        addOne(x);

                        std::cout << "value = " << x << '\n'; // x değişti

                        return 0;
                    }
                    Çıktısı:
                    value = 5
                    value = 6


Yukarıdaki örnekte, x'in başlangıçta değeri 5'tir. addOne(x) çağrıldığında, referans parametresi y, argüman x'e bağlanır. addOne() fonksiyonu
referans y'yi arttırdığında, aslında argüman x'i 5'ten 6'ya arttırıyor (x'in bir kopyası değil). Bu değişen değer, addOne() işlemi tamamlandıktan
sonra bile devam eder.

Değerleri const olmayanlara referansla iletmek, aktarılan argümanların değerini değiştiren fonksiyonlar yazmamıza olanak tanır.

Fonksiyonların iletilen argümanların değerini değiştirebilme yeteneği oldukça faydalı olabilir. Hayal edin ki bir canavarın oyuncuya başarıyla
saldırdığını belirleyen bir fonksiyon yazdınız. Öyleyse, canavar oyuncunun sağlığına bir miktar hasar vermelidir. Eğer oyuncu nesnesini referans
olarak iletiyorsanız, fonksiyon, iletilen gerçek oyuncu nesnesinin sağlığını doğrudan değiştirebilir. Eğer oyuncu nesnesini değer olarak
iletiyorsanız, yalnızca bir kopyanın sağlığını değiştirebilirsiniz ki bu pek faydalı değildir.


Referans ile geçiş, yalnızca değiştirilebilir sol değer argümanları kabul edebilir

Çünkü bir referans, bir değiştirilebilir sol değere (temelde bir const olmayan değişken) yalnızca bağlanabilir, bu nedenle referans ile geçiş,
yalnızca değiştirilebilir sol değerlerle çalışır demektir. Pratikte, bu, referans ile geçişin const olmayanlara sınırlı faydasını önemli ölçüde
sınırlar, çünkü const değişkenleri veya sabit ifadeleri iletimemiz mümkün değildir. Örneğin:

                    #include <iostream>

                    void printValue(int& y) // y sadece değiştirilebilir lvalue kabul eder
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir değiştirilebilir lvalue değişkendir

                        const int z { 5 };
                        printValue(z); // error: z bir değiştirilebilir lvalue değişken değildir

                        printValue(5); // error: 5 bir rvalue dir

                        return 0;
                    }

Neyse ki bunu aşmanın kolay bir yolu var ve bunu bir sonraki derste tartışacağız. Ayrıca ne zaman değere göre geçileceğine ve ne zaman referansa 
göre geçileceğine de göz atacağız.

12.6 — Const sol değer referansı ile geçiş
------------------------------------------
Const olmayan bir referansın aksine (yalnızca değiştirilebilir sol değerlere bağlanabilirken), bir const referans, değiştirilebilir sol değerlere,
değiştirilemez sol değerlere ve sağ değerlere bağlanabilir. Bu nedenle, bir referans parametreyi const yaparsak, her türlü argümana bağlanabilir 
hale gelecektir:

                    #include <iostream>

                    void printValue(const int& y) // Şimdi y bir const referans
                    {
                        std::cout << y << '\n';
                    }

                    int main()
                    {
                        int x { 5 };
                        printValue(x); // ok: x bir değiştirilebilir lvalue

                        const int z { 5 };
                        printValue(z); // ok: z bir değiştirilemez lvalue

                        printValue(5); // ok: 5 bir literal rvalue

                        return 0;
                    }

Const referans ile geçiş, referans ile geçişin temel avantajını (argümanın bir kopyasını oluşturmadan) sunarken, aynı zamanda fonksiyonun 
referans yapılan değeri değiştiremeyeceğini garanti eder.

Örneğin, aşağıdaki durum const olduğu için izin verilmez:

                    void addOne(const int& ref)
                    {
                        ++ref; // İzin verilmemiştir: Ref bir const çünkü
                    }

Çoğu durumda fonksiyonlarımızın argümanların değerini değiştirmesini istemeyiz.

*** BEST -> Aksini yapmak için özel bir nedeniniz olmadıkça (örneğin, işlevin bir argümanın değerini değiştirmesi gerekiyorsa), const referansı 
            ile geçiş'i, const olmayan referans ile geçiş yerine tercih edin.

Artık sabit değer referanslarının değerlere bağlanmasına izin vermenin motivasyonunu anlayabiliriz: bu yetenek olmasaydı, referans yoluyla geçiş
kullanan işlevlere değişmez değerleri (veya diğer değerleri) aktarmanın bir yolu olmazdı!


Değer ile geçiş ve referans ile geçişi karıştırma ( Birlikte kullanmak )
------------------------------------------------------------------------
Çoklu parametreye sahip bir fonksiyon, her parametrenin ayrı ayrı değer ile mi yoksa referans ile mi iletildiğini belirleyebilir.

Örneğin:

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
Yukarıdaki örnekte, ilk argüman değere göre, ikincisi referansa göre ve üçüncüsü const referansına göre iletilir.


(const) referans ile geçiş ne zaman yapılmalıdır
------------------------------------------------
Çünkü sınıf türleri kopyalamak pahalı olabilir (bazen önemli ölçüde), genellikle sınıf türleri argümanın pahalı bir kopyasını oluşturmaktan
kaçınmak için değer yerine const referans ile iletilir. Temel tipler kopyalamak ucuz olduğundan genellikle değer ile iletilir.
*** BEST 
--------
İlke olarak, temel tipleri değer ile, sınıf (veya yapı) tiplerini ise const referans ile iletmek genellikle uygundur.

Diğer yaygın tipleri değer ile iletmek: numaralandırma tipleri ve std::string_view.
Diğer yaygın tipleri (const) referans ile iletmek: std::string, std::array ve std::vector.

Fonksiyon parametreleri için, çoğu durumda const std::string& yerine std::string_view'i tercih edin
---------------------------------------------------------------------------------------------------

Modern C++ içinde sıkça karşılaşılan bir soru: Bir string parametresine sahip bir fonksiyon yazılırken, parametrenin türü const std::string& mı
yoksa std::string_view mı olmalıdır?

Çoğu durumda, std::string_view daha iyi bir tercih olacaktır, çünkü daha geniş bir argüman türü yelpazesini verimli bir şekilde işleyebilir.

                    void doSomething(const std::string&);
                    void doSomething(std::string_view);   // Çoğu durumda bunu tercih edin

const std::string& parametresini kullanmanın daha uygun olabileceği birkaç durum vardır:

1 - Eğer C++14 veya daha eski bir sürüm kullanıyorsanız, std::string_view mevcut değilse.

2 - Eğer fonksiyonunuz, C tarzı bir diziyi veya std::string parametresi alan başka bir fonksiyonu çağırması gerekiyorsa, o zaman 
    const std::string& daha iyi bir seçenek olabilir, çünkü std::string_view'ın null karakteri ile sona erdirilmiş (C tarzı dizi 
    işlevlerinin beklediği şey) olması garanti edilmemiştir ve std::string'e verimli bir şekilde dönüştürülmez.

std::string& yerine std::string_view (değer olarak) kullanarak stringleri iletmeyi tercih edin, ancak fonksiyonunuzun C tarzı dizileri veya
std::string parametreleri gerektiren diğer fonksiyonları çağırdığı durumlar hariç.

12.6 -> Gelişmiş geliştiriciler için bir kaç not bulunmakta bunları 12 tamamen bitmesi ve diğer durumlarda inceleyeceğim çünkü şuan bakarak bir 
        çoğunu anlamayacağız.
*/
