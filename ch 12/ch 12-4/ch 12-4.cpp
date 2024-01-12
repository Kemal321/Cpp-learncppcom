#include <iostream>

int main()
{
	return 0;
}
/*

Rvalue olarak geçirilen bir const referansý const referans ile geri döndürmek uygun bir davranýþtýr
---------------------------------------------------------------------------------------------------
Bir const referans parametresi için bir argüman bir rvalue olduðunda, bu parametreyi yine const referans ile döndürmek uygun bir 
davranýþtýr. Bu, rvaluelarýn oluþturulduklarý tam ifadenin sonuna kadar yok edilmediði için geçerlidir. Ýlk olarak, aþaðýdaki
örneðe bir göz atalým:

                    #include <iostream>
                    #include <string>

                    std::string getHello()
                    {
                        return std::string{"Hello"};
                    }

                    int main()
                    {
                        const std::string s{ getHello() };

                        std::cout << s;

                        return 0;
                    }
Bu durumda, getHello() fonksiyonu bir std::string'i deðer olarak döndürüyor, ki bu bir rvalue'dir. Bu rvalue daha sonra s'yi
baþlatmak için kullanýlýr. s'nin baþlatýlmasýndan sonra, rvalue'ýn oluþturulduðu ifade deðerlendirmeyi tamamlar ve rvalue yok 
edilir.

Þimdi benzer bir örneðe bakalým:
                    #include <iostream>
                    #include <string>

                    const std::string& foo(const std::string &s)
                    {
                        return s;
                    }

                    std::string getHello()
                    {
                        return std::string{"Hello"};
                    }

                    int main()
                    {
                        const std::string s{ foo(getHello()) };

                        std::cout << s;

                        return 0;
                    }

Bu durumda tek fark, rvalue'ýn const referans ile foo() fonksiyonuna iletilmesi ve ardýndan s'yi baþlatmak için kullanýlmadan
önce çaðrýyý geri döndürmesidir. Diðer her þey ayný þekilde çalýþýr.


Çaðýran fonksiyon referans üzerinden deðerleri deðiþtirebilir

Bir argüman, bir fonksiyona const olmayan referans ile iletildiðinde, fonksiyon referansý kullanarak argümanýn deðerini 
deðiþtirebilir.

Benzer þekilde, bir fonksiyondan const olmayan bir referans döndürüldüðünde, çaðýran fonksiyon geri döndürülen deðeri deðiþtirmek
için referansý kullanabilir.

Ýþte bunu gösteren açýklayýcý bir örnek:

                    #include <iostream>

                    // non-const ile 2 parametre alýyor, ve büyük olan parametreyi referans ile döndürüyor
                    int& max(int& x, int& y)
                    {
                        return (x > y) ? x : y;
                    }

                    int main()
                    {
                        int a{ 5 };
                        int b{ 6 };

                        max(a, b) = 7; // a yada b den büyük olanýný 7 olarak ayarlar

                        std::cout << a << b << '\n';

                        return 0;
                    }

Yukarýdaki programda, max(a, b) ifadesi a ve b argümanlarý ile max() fonksiyonunu çaðýrýr. Referans parametre x, argüman a'ya 
baðlanýr ve referans parametre y, argüman b'ye baðlanýr. Fonksiyon daha sonra x (5) ve y (6) arasýnda hangisinin daha büyük
olduðunu belirler. Bu durumda, bu y'dir, bu nedenle fonksiyon y'yi (hala b'ye baðlý olan) çaðýran fonksiyona geri döndürür. 
Çaðýran fonksiyon daha sonra bu döndürülen referansa deðeri 7 olarak atar.

Bu nedenle, max(a, b) = 7 ifadesi etkili bir þekilde b = 7'ye çözülür.

Bu þu þekilde yazdýrýlýr:
                    57
Adrese göre dönüþ
-----------------
Adrese göre dönüþ, neredeyse referansa göre dönüþle ayný þekilde çalýþýr, ancak bir nesnenin referansý yerine bir nesnenin
iþaretçisi döndürülür. Adrese göre dönüþün referansa göre dönüþle ayný temel sakýncasý vardýr -- adrese göre döndürülen nesnenin, 
adresi döndüren fonksiyonun kapsamýndan önce yaþamýþ olmasý gerekir, aksi takdirde çaðrýlan taraf bir sarkýk iþaretçi alacaktýr.

Adrese göre dönüþün referansa göre dönüþe karþý büyük avantajý, fonksiyonun döndürülecek geçerli bir nesne olmadýðýnda nullptr 
döndürebilmemizdir. Örneðin, aramak istediðimiz bir öðrenci listemiz olduðunu varsayalým. Öðrenciyi listede bulursak, eþleþen
öðrenciyi temsil eden nesnenin bir iþaretçisini döndürebiliriz. Eðer eþleþen öðrenci nesnesi bulunamazsa, nullptr döndürerek
eþleþen öðrenci nesnesinin bulunmadýðýný belirtebiliriz.

Adrese göre dönüþün büyük dezavantajý, çaðýran tarafýn, deðeri dereference etmeden önce nullptr kontrolü yapmayý hatýrlamasý
gerekmektedir; aksi takdirde bir null iþaretçi dereferansý meydana gelebilir ve tanýmsýz davranýþ ortaya çýkabilir.Bu tehlikeden 
dolayý, "nesne yok" özelliði gerekmediði sürece, adrese göre dönüþ yerine referansla dönüþ tercih edilmelidir.
 
****BEST -> Nesne yok" (nullptr kullanarak) döndürme yeteneði önemli olmadýðý sürece, adrese göre dönüþ yerine referansa göre 
            dönüþü tercih edin.

IN ve OUT Parametreleri
-----------------------

Bir fonksiyon ve çaðýraný, iki mekanizma aracýlýðýyla iletiþim kurar: parametreler ve geri dönüþ deðerleri. Bir fonksiyon
çaðrýldýðýnda, çaðýran taraf, fonksiyon tarafýndan parametreleri aracýlýðýyla alýnan argümanlarý saðlar. Bu argümanlar deðer, 
referans veya adrese göre iletilmiþ olabilir.

Genellikle, argümanlarý deðer veya const referans ile ileteceðiz. Ancak bazen baþka þekilde yapmamýz gereken durumlar olabilir.

In parametreleri -> Çoðu durumda, bir fonksiyon parametresi, çaðýran tarafýndan gelen bir giriþi almak için kullanýlýr. 
Sadece çaðýran tarafýndan gelen giriþi almak için kullanýlan parametreler bazen "in parameters" olarak adlandýrýlýr.

                    #include <iostream>

                    void print(int x) // x bir in parametresi
                    {
                        std::cout << x << '\n';
                    }

                    void print(const std::string& s) // s bir in parametresi
                    {
                        std::cout << s << '\n';
                    }

                    int main()
                    {
                        print(5);
                        std::string s { "Hello, world!" };
                        print(s);

                        return 0;
                    }

In-Parametreler genellikle deðere veya const referansýna göre iletilir.

Out parametreler -> Fonksiyona (const olmayan) referans (veya adrese) iletilen bir fonksiyon argümaný, fonksiyonun argüman olarak
iletilen bir nesnenin deðerini deðiþtirmesine izin verir. Bu, bir fonksiyonun, bir return deðeri kullanmanýn herhangi bir nedenle
yeterli olmadýðý durumlarda veriyi çaðýran tarafýna geri döndürmesi için bir yol saðlar.

Sadece bilgiyi çaðýran tarafa geri döndürmek amacýyla kullanýlan bir fonksiyon parametresine "out parameter" denir.

Örneðin:

                    #include <cmath>    // std::sin() ve std::cos() için
                    #include <iostream>

                    // sinOut ve cosOut out parametreleridir
                    void getSinCos(double degrees, double& sinOut, double& cosOut)
                    {
                        // sin() ve cos() derece deðil radyan alýyoruz, bu yüzden dönüþtürmemiz gerekiyor
                        constexpr double pi { 3.14159265358979323846 }; // pi deðeri
                        double radians = degrees * pi / 180.0;
                        sinOut = std::sin(radians);
                        cosOut = std::cos(radians);
                    }

                    int main()
                    {
                        double sin { 0.0 };
                        double cos { 0.0 };

                        double degrees{};
                        std::cout << "Enter the number of degrees: ";
                        std::cin >> degrees;

                        // getSinCos sin ve cos deðiþkenlerinde sin ve cos deðerlerini döndürür
                        getSinCos(degrees, sin, cos);

                        std::cout << "The sin is " << sin << '\n';
                        std::cout << "The cos is " << cos << '\n';

                        return 0;
                    }
Bu fonksiyonun bir parametresi degrees (ki argümaný deðer ile iletilir) olarak giriþ, ve iki parametreyi (referans ile) çýkýþ
olarak "geri döndürüyor". Bu çýkýþ parametrelerini, "out" ekini kullanarak out parametre olduklarýný belirttik. Bu, çaðýran 
tarafa, bu parametrelere iletilen baþlangýç deðerinin önemli olmadýðýný, ve bunlarýn üzerine yazýlmasýný beklememiz gerektiðini
hatýrlatmaya yardýmcý olur. Geleneksel olarak, çýkýþ parametreleri genellikle en saðdaki parametrelerdir.

Bu nasýl çalýþtýðýný daha ayrýntýlý olarak inceleyelim. Ýlk olarak, ana fonksiyon sin ve cos adýnda yerel deðiþkenler oluþturur.
Bunlar, getSinCos() fonksiyonuna deðer yerine referans ile iletilir. Bu, getSinCos() fonksiyonunun main() içindeki sin ve cos
deðiþkenlerine gerçek eriþimi olduðu anlamýna gelir, sadece kopyalar deðil. getSinCos() bu þekilde sin ve cos'a yeni deðerler
atar (sýrasýyla referanslar sinOut ve cosOut aracýlýðýyla), bu da sin ve cos içindeki eski deðerleri üzerine yazar. main()
fonksiyonu daha sonra bu güncellenmiþ deðerleri yazdýrýr.

Eðer sin ve cos, deðer yerine referans iletilmemiþ olsaydý, getSinCos() kopyalarýný deðiþtirecekti ve herhangi bir deðiþikliðin
fonksiyonun sonunda atýlmasýna neden olacaktý. Ancak sin ve cos referans ile iletilmiþ olduklarý için, sin veya cos'a yapýlan
herhangi bir deðiþiklik (referanslar aracýlýðýyla) fonksiyondan öteye taþýnýr. Bu nedenle, bu mekanizmayý çaðýran tarafa deðerleri
geri döndürmek için kullanabiliriz.

Out parametreler, iþlevsel olmalarýna raðmen birkaç dezavantaja sahiptir
------------------------------------------------------------------------
Ýlk olarak, çaðýran taraf nesneleri oluþturmalý (ve baþlatmalý) ve bunlarý argüman olarak iletmelidir, hatta kullanmayý niyet 
etmeseler bile. Bu nesneler atanabilir olmalýdýr, bu da onlarýn const olamayacaðý anlamýna gelir.

Ýkinci olarak, çaðýran taraf nesneleri iletmek zorunda olduðu için, bu deðerler geçici olarak kullanýlamaz veya kolayca tek bir
ifadede kullanýlamaz.

Aþaðýdaki örnek, bu iki dezavantajý göstermektedir:

                    #include <iostream>

                    int getByValue()
                    {
                        return 5;
                    }

                    void getByReference(int& x)
                    {
                        x = 5;
                    }

                    int main()
                    {
                        // deðer döndürme
                        [[maybe_unused]] int x{ getByValue() }; // objeyi baþlatmak için kullanýlabilir
                        std::cout << getByValue() << '\n';      // geçici return deðerini ifadede kullanabiliriz

                        // out parametresi döndürme
                        int y{};                // önce atanabilir bir nesne ayýrmalýyýz
                        getByReference(y);      // ardýndan iþlevi kullanarak istenen deðeri atamak için geçirilir
                        std::cout << y << '\n'; // ve ancak o zaman bu deðeri kullanabiliriz

                        return 0;
                    }
                    Gördüðünüz gibi, dýþ parametreleri kullanmanýn sözdizimi biraz doðal deðil.

Referansa göre Out parametreler, argümanlarýn deðiþtirileceðini açýkça ortaya koymaz
------------------------------------------------------------------------------------
Bir fonksiyonun dönüþ deðerini bir nesneye atadýðýmýzda, nesnenin deðerinin deðiþtirildiði açýktýr:

                    x = getByValue(); // x'in deðiþtirildiði açýk

Bu iyidir, çünkü x'in deðerinin deðiþmesini beklememiz gerektiðini açýkça ortaya koymaktadýr. Ancak yukarýdaki örnekte 
getSinCos() iþlevine yapýlan iþlev çaðrýsýna tekrar bakalým:

                    getSinCos(degrees, sin, cos);
Bu iþlev çaðrýsýndan derecelerin bir iç parametre olduðu, ancak sin ve cos'un dýþ parametreler olduðu açýk deðildir. Arayan kiþi
sin ve cos'un deðiþtirileceðini fark etmezse, muhtemelen anlamsal bir hata ortaya çýkacaktýr.

Referansa göre geçiþ yerine adrese göre geçiþ kullanmak, bazý durumlarda arayanýn nesnelerin adresini argüman olarak iletmesini
gerektirerek dýþ parametrelerin daha belirgin olmasýna yardýmcý olabilir. Aþaðýdaki örneði düþünün:

                    void foo1(int x); // deðere göre aktar
                    void foo2(int& x); // referansa göre ilet
                    void foo3(int* x); // adrese göre geç

                    int ana()
                    {
                         int i{};

                         foo1(i); // deðiþtiremiyorum
                         foo2(i); // i'yi deðiþtirebilirim
                         foo3(&i); // i'yi deðiþtirebilirim

                         int *ptr { &i };
                         foo3(ptr); // i'yi deðiþtirebilirim

                         0 deðerini döndür;
                    }
foo3(&i) çaðrýsýnda i yerine &i'yi aktarmamýz gerektiðine dikkat edin; bu, i'nin deðiþtirilmesini beklememiz gerektiðini daha 
açýk hale getirmeye yardýmcý olur.

Ancak foo(ptr), foo()'nun i'yi deðiþtirmesine izin verdiði ve arayanýn ptr adresini almasýný gerektirmediði için bu kusursuz 
deðildir.

Arayan kiþi ayný zamanda buna izin verilmediðinde geçerli bir argüman olarak nullptr veya bir boþ göstericiyi iletebileceðini
düþünebilir. Ve fonksiyonun artýk boþ iþaretçi kontrolü ve iþlemesi gerekiyor, bu da daha fazla karmaþýklýk katýyor. Eklenen boþ
iþaretçi kullanýmýna olan bu ihtiyaç, genellikle yalnýzca referansa göre geçiþe baðlý kalmaktan daha fazla soruna neden olur.

Tüm bu nedenlerden dolayý, baþka iyi bir seçenek olmadýðý sürece, dýþ parametrelerden kaçýnýlmalýdýr.

*** BEST -> Out parametrelerden kaçýnýn (daha iyi seçeneklerin bulunmadýðý nadir durumlar hariç). Ýsteðe baðlý olmayan
            Out parametreleri için referansa göre geçiþi tercih edin.

In/out parametreler

Nadiren, bir fonksiyon gerçekten bir out-parametrenin deðerini üzerine yazmadan önce bu deðeri kullanacaktýr. Böyle bir
parametreye in-out parametre denir. In-out parametreleri, out-parametreleriyle tamamen ayný þekilde çalýþýr ve ayný zorluklara 
sahiptir.
Non-const referans ile iletim ne zaman kullanýlmalýdýr?
-------------------------------------------------------
Eðer bir argümanýn bir kopyasýný oluþturmaktan kaçýnmak için referans ile iletecekseniz, neredeyse her zaman const referans ile
iletmelisiniz.

Ancak, pass by non-const reference'ýn daha iyi bir seçenek olabileceði iki temel durum vardýr.

Ýlk olarak, bir parametre bir in-out parametresi olduðunda non-const referans ile iletimi kullanýn. Zaten geri almak istediðimiz 
nesneyi iletiyorsak, genellikle bu nesneyi doðrudan deðiþtirmek daha basit ve performanslý olabilir.

                    void someFcn(Foo& inout)
                    {
                        // modify inout
                    }

                    int main()
                    {
                        Foo foo{};
                        someFcn(foo); // foo bu çaðrýdan sonra deðiþtirildi, açýk olmayabilir

                        return 0;
                    }
Fonksiyona iyi bir ad vermek yardýmcý olabilir:

                    void modifyFoo(Foo& inout)
                    {
                        // modify inout
                    }

                    int main()
                    {
                        Foo foo{};
                        modifyFoo(foo); // foo bu çaðrýdan sonra deðiþtirildi, nispeten daha belirgin

                        return 0;
                    }

Alternatif olarak, nesneyi deðer veya const referans ile iletmek (genellikle alýþýlageldiði gibi) ve 
ardýndan çaðýrana geri atayabileceði yeni bir nesneyi deðer olarak döndürmek mümkündür:

                    Foo someFcn(const Foo& in)
                    {
                        Foo foo{in}; // burada bir kopya oluþturuluyor
                        // foo'yu deðiþtir
                        return foo;
                    }

                    int main()
                    {
                        Foo foo{};
                        foo = someFcn(foo); // foo'nun deðiþtirildiði açýk hale getirir, ancak burada baþka bir kopya oluþturulur

                        return 0;
                    }

Bu, daha geleneksel bir dönüþ sözdizimi kullanmanýn avantajýna sahiptir, ancak 2 ekstra kopya yapýlmasýný gerektirir
(bazen derleyici bu kopyalardan birini optimize edebilir).

Ýkinci olarak, bir fonksiyonun aksi takdirde bir nesneyi çaðýran tarafýna deðer olarak döndüreceði, ancak bu nesnenin bir
kopyasýný yapmanýn son derece maliyetli olduðu durumlarda pass by non-const reference kullanýn. Özellikle fonksiyon, kodun 
performans açýsýndan kritik bir bölümünde çok kez çaðrýlacaksa.

                    void generateExpensiveFoo(Foo& out)
                    {
                        // out'u deðiþtir
                    }

                    int main()
                    {
                        Foo foo{};
                        generateExpensiveFoo(foo); // bu çaðrýdan sonra foo deðiþtirildi

                        return 0;
                    }

Bununla birlikte, Bu ifade, genellikle bir nesnenin kopyalanmasýnýn o kadar maliyetli olmadýðý için, bu nesneleri geri
döndürmek için alýþýlmadýk yöntemlere baþvurmak genellikle gereksizdir.

Type deduction with pointers, references, and const ( Pointerler, referanslar ve constlar ile Tür çýkarýmý )
------------------------------------------------------------------------------------------------------------
                    int getVal(); // int deðerini deðere göre döndüren bir fonksiyon

                    int ana()
                    {
                         otomatik deðer { getVal() }; // val int türünden çýkarýldý

                         0 deðerini döndür;
                    }
Bundan önceki tür çýkarýmý dersinde, tür çýkarýmýnýn nasýl yapýlacaðýný. Ayrýca, varsayýlan olarak tür kesintisinin 
const (ve constexpr) niteleyicilerini düþüreceðini de belirttik:

                    const double foo()
                    {
                        return 5.6;
                    }

                    int main()
                    {
                        const double cd{ 7.8 };

                        auto x{ cd };    // double (const düþürüldü)
                        auto y{ foo() }; // double (const düþürüldü)

                        return 0;
                    }

Const (veya constexpr), const (veya constexpr) niteleyicisinin tanýma eklenmesiyle (yeniden) uygulanabilir:

                    const double foo()
                    {
                        return 5.6;
                    }

                    int main()
                    {
                        constexpr double cd{ 7.8 };

                        const auto x{ foo() };  // const double (const düþürüldü, const tekrar uygulandý)
                        constexpr auto y{ cd }; // constexpr double (constexpr düþürüldü, constexpr tekrar uygulandý)
                        const auto z { cd };    // const double (constexpr düþürüldü, const uygulandý)

                        return 0;
                    }

Tür çýkarýmý referanslarý düþür
-------------------------------
const belirleyicileri düþürmenin yaný sýra, tür çýkarýmý ayrýca referanslarý da düþürür:

                    #include <string>

                    std::string& getRef(); // referans döndüren bir fonksiyon

                    int main()
                    {
                        auto ref { getRef() }; // tür std::string olarak çýkarýlmýþtýr (std::string& deðil)

                        return 0;
                    }

Yukarýdaki örnekte, ref deðiþkeni tür çýkarýmýný kullanýyor. getRef() fonksiyonu bir std::string& döndürmesine raðmen,
referans belirleyici atýlýr, bu yüzden ref’in türü std::string olarak çýkarýlýr.

Atýlan const belirleyicisi gibi, çýkarýlan türün bir referans olmasýný istiyorsanýz, tanýmlama noktasýnda referansý yeniden 
uygulayabilirsiniz:

                    #include <string>

                    std::string& getRef(); // referans döndüren bir fonksiyon

                    int main()
                    {
                        auto ref1 { getRef() };  // std::string (referans düþürüldü)
                        auto& ref2 { getRef() }; // std::string& (reference tekrar uygulandý)

                        return 0;
                    }

Üst seviye const ve alt seviye const
------------------------------------
Bir üst seviye const, bir nesnenin kendisine uygulanan bir const belirleyicidir. Örneðin:

                    const int x;    // bu const x'e uygulanýr, bu yüzden üst seviyedir
                    int* const ptr; // bu const ptr'ye uygulanýr, bu yüzden üst seviyedir

Buna karþýlýk, bir alt seviye const, referansý alýnan veya iþaret edilen nesneye uygulanan bir const belirleyicidir:

                    const int& ref; // bu const referansý alýnan nesneye uygulanýr, bu yüzden alt seviyedir
                    const int* ptr; // bu const iþaret edilen nesneye uygulanýr, bu yüzden alt seviyedir

Bir const deðere referans her zaman bir alt seviye const’tir. Bir pointer, üst seviye, alt seviye veya her iki tür const’a sahip 
olabilir:

                    const int* const ptr; // sol taraftaki const alt seviye, sað taraftaki const üst seviyedir

Tür çýkarýmýnýn const belirleyicilerini attýðýný söylediðimizde, sadece üst seviye const’larý atar. Alt seviye const’lar atýlmaz.
Bunun örneklerini birazdan göreceðiz.

Tür çýkarýmý ve const referanslarý
----------------------------------
Baþlatýcý bir const referansý (veya constexpr) ise, önce referans atýlýr (ve uygunsa yeniden uygulanýr), ardýndan sonuçtan 
herhangi bir üst seviye const atýlýr.

                    #include <string>

                    const std::string& getConstRef(); // const bir referans döndüren bir fonksiyon

                    int main()
                    {
                        auto ref1{ getConstRef() }; // std::string (referans atýldý, ardýndan üst seviye const sonuçtan atýldý)

                        return 0;
                    }

Yukarýdaki örnekte, getConstRef() bir const std::string& döndürdüðünden, önce referans atýlýr, bizi bir const std::string ile
býrakýr. Bu const þimdi bir üst seviye const, bu yüzden ayrýca atýlýr, çýkarýlan tür std::string olarak kalýr.

Anahtar nokta

Bir referansý atmak, bir alt seviye const’u bir üst seviye const’a dönüþtürebilir: const std::string& bir alt seviye const’týr,
ancak referansý atmak const std::string verir, bu da bir üst seviye const’týr.

Bunlardan birini veya her ikisini de yeniden uygulayabiliriz:

                    #include <string>

                    const std::string& getConstRef(); // const bir referans döndüren bir fonksiyon

                    int main()
                    {
                        auto ref1{ getConstRef() };        // std::string (referans ve üst seviye const atýldý)
                        const auto ref2{ getConstRef() };  // const std::string (referans atýldý, const yeniden uygulandý)

                        auto& ref3{ getConstRef() };       // const std::string& (referans yeniden uygulandý, alt seviye const
                                                              atýlmadý)
                        const auto& ref4{ getConstRef() }; // const std::string& (referans ve const yeniden uygulandý)

                        return 0;
                    }

ref1 için durumu önceki örnekte ele aldýk. ref2 için, bu ref1 durumuna benzer, tek fark const belirleyicisini yeniden uyguluyoruz,
bu yüzden çýkarýlan tür const std::string’dir.

ref3 ile iþler daha ilginç hale geliyor. Normalde önce referans atýlýrdý, ancak referansý yeniden uyguladýðýmýzdan, atýlmaz.
Bu, türün hala const std::string& olduðu anlamýna gelir. Ve bu const bir alt seviye const olduðundan, atýlmaz. Bu nedenle 
çýkarýlan tür const std::string&'dir.

ref4 durumu, ref3’e benzer þekilde çalýþýr, tek fark const belirleyicisini de yeniden uygulamýþ olmamýzdýr. Tür zaten const bir
referans olarak çýkarýldýðýndan, burada const’u yeniden uygulamamýz gereksizdir. Ancak, burada const kullanmak, sonucumuzun const 
olacaðýný açýkça belirtir (oysa ref3 durumunda, sonucun const olmasý dolaylý ve açýk deðildir).

**** BEST -> Eðer const bir referans istiyorsanýz, kesinlikle gerekli olmasa bile const belirleyicisini yeniden uygulayýn, 
             çünkü niyetinizi açýkça belirtir ve hatalarý önler.

constexpr referanslarý hakkýnda ne düþünüyorsunuz?
--------------------------------------------------
Bunlar const referanslarý gibi çalýþýr:

                    #include <string_view>

                    constexpr std::string_view hello { "Hello" };

                    constexpr const std::string_view& getConstRef()
                    {
                        return hello;
                    }

                    int main()
                    {
                        auto ref1{ getConstRef() };            // std::string_view (üst seviye const ve referans atýldý)
                        constexpr auto ref2{ getConstRef() };  // constexpr std::string_view (constexpr yeniden uygulandý,
                                                                  referans atýldý)

                        auto& ref3{ getConstRef() };           // const std::string_view& (referans yeniden uygulandý, 
                                                                  alt seviye const atýlmadý)
                        constexpr auto& ref4{ getConstRef() }; // constexpr const std::string_view& (referans yeniden uygulandý,
                                                                  alt seviye const atýlmadý, constexpr uygulandý)

                        return 0;
                    }

Tür çýkarýmý ve pointerlar
--------------------------
Referanslarýn aksine, tür çýkarýmý pointerlarý atlamaz:

                    #include <string>

                    std::string* getPtr(); // bir pointer döndüren bir fonksiyon

                    int main()
                    {
                        auto ptr1{ getPtr() }; // std::string*

                        return 0;
                    }

Ayrýca bir yýldýzý pointer tür çýkarýmý ile birlikte de kullanabiliriz:

                    #include <string>

                    std::string* getPtr(); // bir pointer döndüren bir fonksiyon

                    int main()
                    {
                        auto ptr1{ getPtr() };  // std::string*
                        auto* ptr2{ getPtr() }; // std::string*

                        return 0;
                    }

auto ve auto* arasýndaki fark
-----------------------------
auto’yu bir pointer tür baþlatýcýsý ile kullandýðýmýzda, auto için çýkarýlan tür pointerý içerir. Yani yukarýdaki ptr1 için,
auto yerine geçen tür std::string*'dir. auto* ile bir pointer tür baþlatýcýsý kullandýðýmýzda, auto için çýkarýlan tür pointerý
içermez - tür çýkarýldýktan sonra pointer yeniden uygulanýr. Yani yukarýdaki ptr2 için, auto yerine geçen tür std::string’dir ve
sonra pointer yeniden uygulanýr.

Çoðu durumda, pratik etki aynýdýr (yukarýdaki örnekte ptr1 ve ptr2 her ikisi de std::string* olarak çýkarýlýr).
Ancak, auto ve auto* arasýnda pratikte birkaç fark vardýr. Ýlk olarak, auto* bir pointer baþlatýcýsýna çözülmelidir,
aksi takdirde bir derleme hatasý oluþur:

                    #include <string>

                    std::string* getPtr(); // bir pointer döndüren bir fonksiyon

                    int main()
                    {
                        auto ptr3{ *getPtr() };      // std::string (çünkü getPtr()'yi dereferans ettik)
                        auto* ptr4{ *getPtr() };     // derlenmiyor (baþlatýcý bir pointer deðil)

                        return 0;
                    }

Bu mantýklýdýr: ptr4 durumunda, auto std::string’e çýkarýlýr, sonra pointer yeniden uygulanýr. Bu nedenle ptr4’ün türü
std::string*'dir ve bir pointer olmayan bir baþlatýcý ile std::string*'i baþlatamayýz.

Ýkinci olarak, const’u denkleme dahil ettiðimizde auto ve auto* nasýl davrandýðý arasýnda farklar vardýr. Bunu aþaðýda ele
alacaðýz.

Tür çýkarýmý ve const pointerlar
--------------------------------
Pointerlar atýlmadýðýndan, bunun hakkýnda endiþelenmemize gerek yok. Ancak pointerlarla, hem const pointer hem de const’a pointer
durumlarýný düþünmemiz gerekiyor ve ayrýca auto ve auto* var. Referanslarla olduðu gibi, pointer tür çýkarýmý sýrasýnda sadece 
üst seviye const atýlýr.

Basit bir durumla baþlayalým:

                    #include <string>

                    std::string* getPtr(); // bir pointer döndüren bir fonksiyon

                    int main()
                    {
                        const auto ptr1{ getPtr() };  // std::string* const
                        auto const ptr2 { getPtr() }; // std::string* const

                        const auto* ptr3{ getPtr() }; // const std::string*
                        auto* const ptr4{ getPtr() }; // std::string* const

                        return 0;
                    }

auto const veya const auto kullandýðýmýzda, “çýkarýlan türün ne olursa olsun const yap” diyoruz. Yani ptr1 ve ptr2 durumunda,
çýkarýlan tür std::string*'dir ve sonra const uygulanýr, son tür std::string* const olur. Bu, const int ve int const’ýn ayný 
anlama geldiði gibidir.

Ancak, auto* kullandýðýmýzda, const belirleyicinin sýrasý önemlidir. Soldaki bir const, “çýkarýlan pointer türünü const’a bir
pointer yap” anlamýna gelirken, saðdaki bir const, “çýkarýlan pointer türünü bir const pointer yap” anlamýna gelir. 
Bu nedenle ptr3 const’a bir pointer olarak sonuçlanýr ve ptr4 bir const pointer olarak sonuçlanýr.

Þimdi baþlatýcýnýn const bir pointer’a const olduðu bir örneðe bakalým.

                    #include <string>

                    int main()
                    {
                        std::string s{};
                        const std::string* const ptr { &s };

                        auto ptr1{ ptr };  // const std::string*
                        auto* ptr2{ ptr }; // const std::string*

                        auto const ptr3{ ptr };  // const std::string* const
                        const auto ptr4{ ptr };  // const std::string* const

                        auto* const ptr5{ ptr }; // const std::string* const
                        const auto* ptr6{ ptr }; // const std::string*

                        const auto const ptr7{ ptr };  // hata: const belirleyici iki kez uygulanamaz
                        const auto* const ptr8{ ptr }; // const std::string* const

                        return 0;
                    }

ptr1 ve ptr2 durumlarý basittir. Üst seviye const (pointerýn kendisindeki const) atýlýr. Ýþaret edilen nesnedeki alt seviye 
const atýlmaz. Bu yüzden her iki durumda da son tür const std::string*'dir.

ptr3 ve ptr4 durumlarý da basittir. Üst seviye const atýlýr, ancak yeniden uyguluyoruz. Ýþaret edilen nesnedeki alt seviye const
atýlmaz. Bu yüzden her iki durumda da son tür const std::string* const’dir.

ptr5 ve ptr6 durumlarý, önceki örnekte gösterdiðimiz durumlara benzer. Her iki durumda da üst seviye const atýlýr.
ptr5 için, auto* const üst seviye const’u yeniden uygular, bu yüzden son tür const std::string* const’dir. ptr6 için,
const auto* const’u iþaret edilen türe uygular (bu durumda zaten const idi), bu yüzden son tür const std::string*'dir.

ptr7 durumunda, const belirleyiciyi iki kez uyguluyoruz, bu izin verilmez ve bir derleme hatasýna neden olur.

Ve son olarak, ptr8 durumunda, pointerýn her iki tarafýna da const uyguluyoruz (auto* bir pointer türü olmalýdýr, bu yüzden izin 
verilir), bu yüzden sonuç türleri const std::string* const’dir.

**** BEST -> Eðer const bir pointer istiyorsanýz, kesinlikle gerekli olmasa bile const belirleyicisini yeniden uygulayýn,
             çünkü niyetinizi açýkça belirtir ve hatalarý önler.

                                        Bölüm 12 özeti Hýzlý inceleme

Bileþik veri türleri (veya bileþik veri türü olarak da adlandýrýlýr), temel veri türlerinden (veya diðer bileþik veri türlerinden)
oluþturulabilen veri türleridir.

Bir ifadenin deðer kategorisi, bir ifadenin bir deðere, bir iþleve veya bir tür nesneye çözülüp çözülmediðini belirtir.

Bir lvalue, bir iþlevi veya bir kimliði olan bir nesneyi deðerlendiren bir ifadedir. Bir kimliði olan bir nesne veya iþlevin bir 
tanýmlayýcýsý veya tanýmlanabilir bir bellek adresi vardýr. Lvalue’lar iki alt tipe ayrýlýr: deðiþtirilebilir lvalue’lar
deðiþtirilebilen lvalue’lardýr ve deðiþtirilemeyen lvalue’lar deðerleri deðiþtirilemeyen lvalue’lardýr (genellikle const veya
constexpr olduklarý için).

Bir rvalue, bir l-deðeri olmayan bir ifadedir. Bu, literalleri (dize literalleri hariç) ve iþlevlerin veya operatörlerin dönüþ 
deðerlerini (deðer olarak döndürüldüðünde) içerir.

Bir referans, mevcut bir nesnenin takma adýdýr. Bir referans tanýmlandýktan sonra, referansa uygulanan herhangi bir iþlem, 
referansý alýnan nesneye uygulanýr. C++'da iki tür referans bulunur: lvalue referanslarý ve rvalue referanslarý. Bir lvalue 
referansý (genellikle sadece referans olarak adlandýrýlýr) mevcut bir lvalue’nin (genellikle baþka bir deðiþkenin) takma adý
olarak hareket eder. Bir lvalue referans deðiþkeni, bir lvalue’ye (genellikle baþka bir deðiþken) referans olarak hareket eden
bir deðiþkendir.

Bir referans bir nesneyle (veya iþlevle) baþlatýldýðýnda, bu nesneye (veya iþleve) baðlandýðýný söyleriz. Referansý alýnan nesne 
(veya iþlev) bazen referans olarak adlandýrýlýr.

Lvalue referanslarý, deðiþtirilemeyen lvalue’lara veya rvalue’lara baðlanamaz (aksi takdirde bu deðerleri referans aracýlýðýyla
deðiþtirebilirsiniz, bu da const-ness’larýnýn ihlali olurdu). Bu nedenle, lvalue referanslarý bazen const olmayan lvalue
referanslarý olarak adlandýrýlýr (bazen kýsaltýlmýþ olarak non-const referans).

Bir kez baþlatýldýktan sonra, C++'daki bir referans yeniden oturtulamaz, yani baþka bir nesneye referans olacak þekilde 
deðiþtirilemez.

Bir nesne, ona bir referans verilmeden önce yok edilirse, referans artýk var olmayan bir nesneyi referans olarak býrakýr.
Böyle bir referansa asýlý referans denir. Asýlý bir referansa eriþmek tanýmsýz davranýþa yol açar.

Bir lvalue referansýný bildirirken const anahtar kelimesini kullanarak, bir lvalue referansýna referansý alýnan nesneyi const 
olarak ele almasýný söyleriz. Böyle bir referansa const deðere bir lvalue referansý denir (bazen const’a referans veya const
referans olarak adlandýrýlýr). Const referanslar, deðiþtirilebilir lvalue’lara, deðiþtirilemeyen lvalue’lara ve rvalue’lara
baðlanabilir.

Bir geçici nesne (ayný zamanda isimsiz nesne veya anonim nesne olarak da adlandýrýlýr), tek bir ifade içinde geçici kullaným için
oluþturulan (ve sonra yok edilen) bir nesnedir.

Referans ile geçiþ kullanýrken, bir iþlev parametresini normal bir deðiþken yerine bir referans (veya const referans) olarak
bildiririz. Ýþlev çaðrýldýðýnda, her referans parametresi uygun argümana baðlanýr. Referans, argümanýn takma adý olarak hareket
ettiði için, argümanýn bir kopyasý yapýlmaz.

Adres operatörü (&), iþlecinin bellek adresini döndürür. Dereferans operatörü (*), belirli bir bellek adresindeki deðeri bir
lvalue olarak döndürür.

Bir pointer, deðeri olarak bir bellek adresi (genellikle baþka bir deðiþkenin) tutan bir nesnedir. Bu, daha sonra kullanmak
üzere baþka bir nesnenin adresini saklamamýzý saðlar. Normal deðiþkenler gibi, pointerlar da varsayýlan olarak baþlatýlmaz.
Baþlatýlmamýþ bir pointer bazen wild pointer olarak adlandýrýlýr. Asýlý bir pointer, artýk geçerli olmayan bir nesnenin adresini
tutan bir pointerdýr (örneðin, çünkü yok edilmiþtir).

Bir pointer, bir bellek adresinin yaný sýra, tutabileceði bir ek deðere daha sahiptir: null deðeri. Null deðeri (genellikle kýsaca
null), bir þeyin deðeri olmadýðý anlamýna gelen özel bir deðerdir. Bir pointer null deðeri tutuyorsa, bu pointerýn hiçbir þeye
iþaret etmediði anlamýna gelir. Böyle bir pointera null pointer denir. nullptr anahtar kelimesi, bir null pointer literalini
temsil eder. Bir pointerý açýkça baþlatmak veya null deðere atamak için nullptr kullanabiliriz.

Bir pointer, ya geçerli bir nesnenin adresini tutmalýdýr, ya da nullptr’a ayarlanmalýdýr. Bu þekilde, sadece pointerlarý null için
test etmemiz gerekir ve herhangi bir null olmayan pointerýn geçerli olduðunu varsayabiliriz.

Bir const deðere pointer (kýsaca const’a pointer olarak da adlandýrýlýr), sabit bir deðere iþaret eden bir (non-const) pointerdýr.

Bir const pointer, baþlatýldýktan sonra adresi deðiþtirilemeyen bir pointerdýr.

Bir const deðere const pointer, ne adresi deðiþtirilemez, ne de pointer aracýlýðýyla iþaret ettiði deðer deðiþtirilebilir.

Adres ile geçiþ kullanýrken, bir nesneyi argüman olarak saðlamak yerine, çaðýran kiþi bir nesnenin adresini (bir pointer 
aracýlýðýyla) saðlar. Bu pointer (nesnenin adresini tutan) çaðrýlan iþlevin bir pointer parametresine kopyalanýr (þimdi de 
nesnenin adresini tutar). Ýþlev daha sonra bu pointerý dereferans ederek geçirilen adresin nesnesine eriþebilir.

Referans ile döndürme, döndürülen nesneye baðlý bir referans döndürür, bu da dönüþ deðerinin bir kopyasýný yapmayý önler. 
Referans ile döndürme kullanmanýn bir ana sakýncasý vardýr: programcýnýn, referansý döndüren iþlevi aþan nesnenin referans 
alýndýðýndan emin olmasý gerekir. Aksi takdirde, döndürülen referans asýlý kalýr (yok edilmiþ bir nesneyi referans alýr) ve
bu referansýn kullanýlmasý tanýmsýz davranýþa yol açar. Bir parametre bir iþleve referans olarak geçirilirse, bu parametreyi
referans olarak döndürmek güvenlidir.

Bir iþlev bir referans döndürürse ve bu referans, bir referans olmayan bir deðiþkeni baþlatmak veya atamak için kullanýlýrsa,
dönüþ deðeri kopyalanýr (sanki deðer olarak döndürülmüþ gibi).

Deðiþkenler için tür çýkarýmý (auto anahtar kelimesi aracýlýðýyla) çýkarýlan türden herhangi bir referansý veya üst seviye
const belirleyicilerini atar. Bu, deðiþken bildiriminin bir parçasý olarak yeniden uygulanabilir.

Evet, adres ile döndürme, referans ile döndürme ile neredeyse ayný þekilde çalýþýr. Tek fark, bir nesnenin referansý yerine 
bir nesnenin pointerýnýn döndürülmesidir.
*/