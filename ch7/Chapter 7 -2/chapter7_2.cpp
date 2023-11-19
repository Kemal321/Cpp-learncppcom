#include <iostream>

int main()
{
    /*
    Diðeri çok uzamýþtý o yüzden ikinci bir dosyaya geçtim. 
                                                          7.12 - Using tanýmlamasý ve using direktifi
    Kýsa bir tarih dersi

    C++'ýn namespace desteði olmadan önce, þu anda std namespace içinde bulunan tüm isimler global namespace içindeydi. Bu durum, program tanýmlarý
    ile standart kütüphane tanýmlarý arasýnda çakýþmalara yol açtý. Bir C++ sürümü altýnda çalýþan programlar, daha yeni bir C++ sürümü ile isim
    çakýþmasýna neden olabilir.

    1995 yýlýnda, namespace'ler standartlaþtýrýldý ve standart kütüphanedeki tüm iþlevsellik global namespace'ten çýkartýlarak namespace std içine 
    taþýndý. Bu deðiþiklik, hala std:: olmadan isimleri kullanan eski kodlarý bozdu.

    Büyük bir kod tabanýnda çalýþan herkesin bildiði gibi, kod tabanýna yapýlan herhangi bir deðiþiklik (ne kadar küçük olursa olsun) programý bozmak 
    riskini taþýr. Artýk std namespace içine taþýnan her ismi std:: öneki ile kullanmaya güncelleme yapmak büyük bir riskti. Bir çözüm talep edildi.

    Günümüze geldiðimizde, eðer standart kütüphaneyi çok kullanýyorsanýz, standart kütüphaneden kullandýðýnýz her þeyin önüne std:: yazmak
    tekrarlayýcý hale gelebilir ve bazý durumlarda kodunuzu okumayý zorlaþtýrabilir.

    C++, bu sorunlara çözüm olarak using ifadeleri þeklinde bazý çözümler sunar.

    Ancak önce, iki terimi tanýmlayalým.

    ** Nitelenmiþ ve nitelenmemiþ isimler

    Bir isim nitelenmiþ veya nitelenmemiþ olabilir.Bir nitelenmiþ isim, bir iliþkilendirilmiþ kapsam içeren bir isimdir.
    Genellikle, isimler bir namespace ile kapsamlý olarak "::" kapsam çözüm operatörü kullanýlarak nitelenir. Örneðin:
    std::cout // tanýmlayýcý cout, namespace std ile nitelendirilmiþtir
            ::foo // tanýmlayýcý foo, global namespace ile nitelendirilmiþtir
            Ýleri düzey okuyucular için:

    Bir isim ayrýca "::" kapsam çözüm operatörü kullanýlarak bir sýnýf adý tarafýndan nitelendirilebilir veya bir sýnýf 
    nesnesi tarafýndan üye seçim operatörleri (veya . veya ->) kullanýlarak nitelendirilebilir. Örneðin:
            class C; // bir sýnýf

            C::s_member; // s_member, C sýnýfý tarafýndan nitelendirilmiþtir
            obj.x; // x, sýnýf nesnesi obj tarafýndan nitelendirilmiþtir
            ptr -> y; // y, sýnýf nesnesi iþaretçisi ptr tarafýndan nitelendirilmiþtir
    Nitelenmemiþ bir isim, bir kapsam belirleyici içermeyen bir isimdir. Örneðin, cout ve x nitelenmemiþ isimlerdir, 
    çünkü bunlar iliþkilendirilmiþ bir kapsam içermez.
    Bu terimler, bir ismin kullanýldýðý yerdeki kapsama ve baðlama baðlý olarak anlam deðiþtirebilir. Bir terimin kullaným 
    baðlamýný anlamak, nitelenmiþ veya nitelenmemiþ olarak adlandýrýlmasýna yardýmcý olacaktýr.

    * Using Declaration ý
    
    Tekrarlayan std:: ifadelerini azaltmanýn bir yolu, using-declaration ifadesini kullanmaktýr. Using-declaration, bir nitelenmiþ ismin
    (kapsamlý olmayan) bir takma adý(std::cout -> cout a takma ad diyor yani ) olarak kullanýlmasýna izin verir. Örnek olarak hello world programýnda 
    hatýrlarsýn, using std::cout; ve using std::endl; ifadeleri kullanýlarak, cout ve endl'yi doðrudan std:: ön eki olmadan kullanabiliriz. 
    Bu, kodun daha okunabilir olmasýna ve std:: ifadelerinin tekrarýnýn azalmasýna olanak tanýr.
    
-------------------------------------------------------------------------------------------------------------------------------------------------------
Örnek:
    #include <iostream>

    int main()
    {
       using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
       cout << "Hello world!\n"; // so no std:: prefix is needed here!

       return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
    Kullanýlan using-declaration using std::cout;, derleyiciye, std isim alanýndan cout nesnesini kullanacaðýmýzý bildirir. Bu nedenle,
    her seferinde cout gördüðünde, std::cout anlamýna geldiðini varsayacaktýr. Eðer std::cout ile cout'un baþka bir kullanýmý arasýnda 
    bir isim çakýþmasý varsa, std::cout tercih edilecektir.
    
    Bu basit örnekte çok fazla çaba tasarrufu saðlamaz, ancak bir iþlev içinde cout'u birçok kez kullanýyorsanýz, using-declaration kodunuzu 
    daha okunabilir hale getirebilir. Unutmayýn ki her isim için ayrý bir using-declaration'a ihtiyacýnýz olacak (örneðin, std::cout için bir
    tane, std::cin için bir tane vb.).

    Bu yöntem, std:: öneki kullanmaktan daha açýk olmamasýna raðmen, genellikle güvenli ve kabul edilebilir olarak deðerlendirilir (bir fonksiyon
    içinde kullanýldýðýnda).

    * Using Yönergesi
    
    Ýþleri basitleþtirmenin baþka bir yolu da bir using yönergesi kullanmaktýr. Biraz basitleþtirecek olursak, bir using yönergesi,
    bir ad alanýndaki tüm tanýmlayýcýlarý, using yönergesinin kapsamýna aktarýr.


    For advanced readers

    Teknik nedenlerden dolayý, using-directive'ler aslýnda isimleri( namespacedeki isimler yani ) mevcut kapsama dahil etmez - bunun yerine isimleri dýþ
    bir kapsama dahil eder (hangi dýþ kapsamýn seçildiði hakkýnda daha fazla ayrýntýya https://quuxplusone.github.io/blog/ buradan ulaþýlabilir). 
    Bununla birlikte, bu isimlere dýþ kapsamdan eriþilemez - yalnýzca using-directive'in kapsamýndan (veya iç içe bir kapsamdan) yapýlan nitelenmemiþ
    (öneklenmemiþ) aramalar yoluyla eriþilebilirler.
    Pratik etkisi, (iç içe geçmiþ ad alanlarý içinde birden çok using-directive içeren bazý tuhaf durumlar dýþýnda), using-directive'lerin 
    isimlerin mevcut kapsama dahil edilmiþ gibi davrandýðýdýr. Ýþleri basit tutmak için, isimlerin mevcut kapsama dahil edildiði basitleþtirmesi
    altýnda devam edeceðiz.
-------------------------------------------------------------------------------------------------------------------------------------------------------
Örneðin revizesi:
    #include <iostream>

    int main()
    {
       using namespace std; // this using directive tells the compiler to import all names from namespace std into the current
                            // namespace without qualification
       cout << "Hello world!\n"; // so no std:: prefix is needed here
       return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
    
    Using-directive, using namespace std; derleyiciye std ad alanýndaki tüm isimleri mevcut kapsama (bu durumda main() fonksiyonunun kapsamýna) 
    dahil etmesini söyler. Ardýndan nitelenmemiþ cout tanýmlayýcýsýný kullandýðýmýzda, bu, içe aktarýlan std::cout'a çözümlenecektir.

    Using-directive'ler, ad alaný öncesi eski kod tabanlarý için bir çözüm sunar ve standart kitaplýk iþlevselliði için nitelenmemiþ isimler 
    kullanýldýðýnda, her nitelenmemiþ ismi nitelenmiþ bir isme manuel olarak güncelleme zorunluluðunu ortadan kaldýrýr (bu riskliydi). Bunun yerine,
    her dosyanýn baþýna tek bir using-directive (using namespace std;) yerleþtirilebilir ve std ad alanýna taþýnmýþ tüm isimler hala nitelenmemiþ 
    olarak kullanýlabilir.
       
    * Using yçnergeleriyle ilgili sorunlar (diðer bir deyiþle neden "namespace std kullanmaktan kaçýnmanýz gerekir?")
    
    Modern C++'ta, using-directive'ler genellikle riskle karþýlaþtýrýldýðýnda (bazý yazma iþlemi tasarrufu dýþýnda) pek bir fayda saðlamaz.
    Çünkü using-directive'ler bir ad alanýndaki tüm isimleri içeri aktardýðýndan (potansiyel olarak asla kullanmayacaðýnýz birçok ismi içerir),
    isim çakýþmalarýnýn olma olasýlýðý önemli ölçüde artar (özellikle std ad alanýný içe aktarýrsanýz).
-------------------------------------------------------------------------------------------------------------------------------------------------------
Açýklama amaçlý olarak, using-directive'lerin belirsizliðe neden olduðu bir örneðe bakalým:
    #include <iostream>

    namespace a
    {
	    int x{ 10 };
    }

    namespace b
    {
	    int x{ 20 };
    }

    int main()
    {
	    using namespace a;
	    using namespace b;

	    std::cout << x << '\n';

	    return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------
Yukarýdaki örnekte, derleyici main içindeki x'in a::x'e mi yoksa b::x'e mi atýfta bulunduðunu belirleyemez. Bu durumda, "belirsiz sembol" hatasý ile derleme baþarýsýz olacaktýr. Bu sorunu çözmek için using deyimlerinden birini kaldýrabilir, bunun yerine using-declaration kullanabilir veya x'i açýk bir kapsam belirleyiciyle (a:: veya b::) nitelendirebiliriz.

Ýþte daha karmaþýk bir örnek:
    #include <iostream> // imports the declaration of std::cout

    int cout() // kendi "cout" umuzu tanýmladýk
    {
        return 5;
    }

    int main()
    {
        using namespace std; // makes std::cout accessible as "cout"
        cout << "Hello, world!\n"; // Hangi cout u istiyoruz ? Yukarýda tanýmladýðýmýz cout u mu yoksa ad alaný içinde var olan cout u mu ?

        return 0;
    }
-------------------------------------------------------------------------------------------------------------------------------------------------------

     
    Yukarýdaki örnekte, derleyici cout kullanýmýmýzýn std::cout'u mu yoksa tanýmladýðýmýz cout fonksiyonunu mu ifade ettiðini belirleyemez ve 
    yine "belirsiz sembol" hatasý ile derleme baþarýsýz olacaktýr. Bu örnek basit olsa da, std::cout'u þu þekilde açýkça öneklediysek:
-------------------------------------------------------------------------------------------------------------------------------------------------------
    std::cout << "Hello, world!\n"; // derleyiciye std::cout dan bahsettiðimizi söyle
-------------------------------------------------------------------------------------------------------------------------------------------------------
    veya bir kullaným yönergesi yerine bir kullaným bildirimi kullanýldý:
    
   * using std::cout; // derleyiciye cout denilince std::cout dan bahsettiðimizi söyle
   * cout << "Hello, world!\n"; // so this means std::cout


    Eðer bir using-directive (namespace kullaným yönergesi) bugün isim çakýþmasýna neden olmasa bile, kodunuzu gelecekteki çakýþmalara karþý daha 
    savunmasýz hale getirir. Örneðin, kodunuz güncellenen bir kütüphanenin using-directive'ini içeriyorsa, güncellenen kütüphanede tanýtýlan tüm 
    yeni isimler, mevcut kodunuzla çakýþma adaylarý olur.

    Bu durumda daha sinsice bir sorun da ortaya çýkabilir. Güncellenen kütüphane, sadece ayný isme sahip olmakla kalmayýp, belirli bir fonksiyon 
    çaðrýsý için daha iyi bir eþleþme oluþturan bir fonksiyon tanýtýrsa, derleyici yeni fonksiyonu tercih edebilir ve programýnýzýn davranýþý 
    beklenmedik bir þekilde deðiþebilir.

    Sýradaki örneðe bakarak mevzuyu daha iyi anlayalým:
foolib.h (part of some third-party library):
    #ifndef FOOLIB_H
    #define FOOLIB_H

    namespace Foo
    {
        // burada kullandýðýmýz bazý yararlý kodlar varmýþ gibi davranalým
    }
    #endif

main.cpp:
    #include <iostream>
    #include <foolib.h> // 3.parti kütüphane, bu yüzden köþeli parantez kullanýldý.

    int someFcn(double)
    {
        return 1;
    }

    int main()
    {
        using namespace Foo; // Çünkü tembeliz ve Foo:: nitelenmiþ adlara Foo:: önekini yazmadan eriþmek istiyoruz
        std::cout << someFcn(0) << '\n'; // 0'ýn gerçek deðeri 0.0 olmalýdýr, ancak bu yapýlmasý kolay bir hatadýr

        return 0;
    }

    Bu program çalýþýr ve 1'i yazdýrýr.

    Þimdi güncellenmiþ bir Folib.h dosyasýný içeren Folib kütüphanesini güncellediðimizi varsayalým. Programýmýz artýk þuna benziyor:

Folib.h (bazý üçüncü taraf kütüphanelerin bir parçasý):
    #ifndef FOOLIB_H
    #define FOOLIB_H

    namespace Foo
    {
        // Yeni tanýtýlan fonksiyon
        int someFcn(int)
        {
            return 2;
        }

        // burada kullandýðýmýz bazý yararlý kodlar varmýþ gibi davranalým
    }
    #endif
main.cpp:
    #include <iostream>
    #include <foolib.h>

    int someFcn(double)
    {
        return 1;
    }

    int main()
    {
        using namespace Foo; // Çünkü tembeliz ve Foo:: nitelenmiþ adlara Foo:: önekini yazmadan eriþmek istiyoruz
        std::cout << someFcn(0) << '\n'; // 0'ýn gerçek deðeri 0.0 olmalýdýr, ancak bu yapýlmasý kolay bir hatadýr

        return 0;
    }

    Ana main.cpp dosyamýz hiç deðiþmedi, ancak bu program þimdi çalýþýyor ve 2 yazdýrýyor!

    Derleyici bir iþlev çaðrýsýyla karþýlaþtýðýnda, iþlev çaðrýsýný hangi iþlev tanýmýyla eþleþtirmesi gerektiðini belirlemelidir.
    Potansiyel olarak eþleþen iþlevlerden birini seçerken, argüman dönüþümlerine ihtiyaç duymayan bir iþlevi, argüman dönüþümleri 
    gerektiren bir iþleve tercih eder. Çünkü 0 sayýsý bir tamsayý olduðundan, C++, bu durumu yeni tanýtýlan someFcn(int) 
    (hiçbir dönüþüm gerektirmez) ile eþleþtirmeyi someFcn(double) (int'ten double'a dönüþüm gerektirir) üzerine tercih eder.
    Bu, program sonuçlarýmýzda beklenmeyen bir deðiþikliðe neden olur.

    Bu sorun, using-declaration veya açýk bir kapsam belirleyici kullanmýþ olsaydýk meydana gelmezdi.
    
    Son olarak, açýk kapsam öneklerinin olmayýþý, okuyucunun hangi iþlevlerin kitaplýðýn parçasý olduðunu ve neyin programýnýzýn parçasý olduðunu söylemesini zorlaþtýrýr. 
    Örneðin, bir kullaným yönergesi kullanýrsak:
    using namespace ns;

    int main()
    {
        foo(); // bu foo kullanýcý tanýmlý bir iþlev mi, yoksa ns kütüphanesinin bir parçasý mý?
    }
    Modern IDE'ler, foo() çaðrýsýnýn gerçekten ns::foo()'yu mu yoksa kullanýcý tanýmlý bir fonksiyon olan foo()'yu mu ifade ettiðini size göstermeli;
    ancak her bir ismin kaynaðýný görmek için her bir ismin üzerine gelmek sýkýcýdýr.

    Kullaným direktifi olmadan, çok daha açýktýr:
    int main()
    {
        ns::foo(); // açýkça ns kütüphanesinin bir parçasý
        foo(); // muhtemelen kullanýcý tanýmlý bir fonksiyon
    }
    Bu versiyonda ns::foo() çaðrýsý açýkça bir kütüphane çaðrýsýdýr. Basit foo() çaðrýsý muhtemelen bir kullanýcý tanýmlý fonksiyonu çaðrýsýdýr 
    (bazý kütüphaneler, belirli standart kütüphane baþlýklarý dahil, isimleri global ad alanýna yerleþtirir, bu yüzden kesin bir garanti deðildir).

    bazý kütüphanelerin, özellikle belirli standart kütüphane baþlýklarýnýn, isimleri (fonksiyonlar, sýnýflar vb.) global ad alanýna 
    yerleþtirebileceðini belirtiyor. Yani, bir kütüphanenin bir ismi global ad alana eklemesi durumunda, belirli bir ismin global ad alanýnda
    bulunup bulunmadýðýný tam olarak tahmin etmek zor olabilir. Bu nedenle, bir ismin hangi ad alanýna ait olduðunu belirlemek için kesin bir garanti yoktur.
   
   "Bazý kütüphaneler, özellikle belirli standart kütüphane baþlýklarý, isimleri (fonksiyonlar, sýnýflar vb.) global ad alanýna yerleþtirebilirler."
    Bu ifade, bir kütüphanenin belirli isimleri global ad alanýna ekleyebileceði anlamýna gelir. Yani, bir fonksiyon veya sýnýf adý, belirli bir 
    baþlýk dosyasý içinde tanýmlanýyorsa, bu isim global ad alanýnda da kullanýlabilir.
    Ancak, "bu yüzden kesin bir garanti deðildir" ifadesi, her kütüphanenin bu þekilde davranmadýðýný veya bu durumun genel bir kural olmadýðýný
    belirtiyor. Yani, bir ismin global ad alanda bulunup bulunmadýðýný önceden kesin bir þekilde bilmenin her zaman mümkün olmadýðýný ifade ediyor.
    Bu durum, belirli kütüphanelerin veya baþlýk dosyalarýnýn özel davranýþlarýna baðlý olabilir.

    * Using-declaration ve using-direktiflerinin kapsamý
    Eðer bir using-declaration veya using-directive bir blok içinde kullanýlýyorsa, isimler sadece o blok için geçerli olacaktýr (normal blok kapsam
    kurallarýný takip eder). Bu durum, isim çakýþmalarýnýn sadece o blok içinde gerçekleþme olasýlýðýný azaltarak olumlu bir durumdur.

    Eðer bir using-declaration veya using-directive global ad alanýnda kullanýlýyorsa, isimler dosyanýn geri kalanýna uygulanýr (dosya kapsamýna 
    sahiptirler).


    * Using ifadesini iptal etme veya deðiþtirme iþlemi 
    ---------------------------------------------------
    "Using-statement bir kere tanýmlandýktan sonra, tanýmlandýðý kapsam içinde onu iptal etmek veya baþka bir using-statement ile deðiþtirmek
    mümkün deðildir."

    int main()
    {
    using namespace Foo;

    // Foo ad alanýný burada iptal edebilmek mümkün deðil
    // "using namespace Foo" i baþka bir using ifadesi ile deðiþtirmekte mümkün deðil

    return 0;
    } // using namespace Foo burada bitiyor


    Yapabileceðiniz en iyi þey, blok kapsam belirleme kurallarýný kullanarak, kullaným ifadesinin kapsamýný en baþtan kasýtlý olarak sýnýrlamaktýr.

    int main()
    {
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // ad alaný kullanýldýðýnda Foo'nun süresi dolar

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // ad alaný kullanýldýðýnda Goo'nun süresi dolar

    return 0;
    }

    Elbette, tüm bu baþ aðrýlarýndan ilk etapta kapsam çözümleme operatörünün (::) açýkça kullanýlmasýyla kaçýnýlabilir. :))
    */
    // BEST USÝNG-STATEMENT KULLANIMI
    // Özellikle using namespace std; gibi using - directive'lerden kaçýnýn, ancak belirli durumlarda (örneðin using namespace std::literals 
    // kullanarak s ve sv literal soneklerine eriþmek gibi). Using-declaration'lar genellikle bloklar içinde kullanmak güvenli kabul edilir.
    // Kullanýmlarýný bir kod dosyasýnýn global ad alanýnda sýnýrlayýn ve bunlarý bir baþlýk dosyasýnýn global ad alanýnda asla kullanmayýn.
    // **** BEST
    /*Açýkça belirtilmiþ ad alanlarýný(namespace) tercih edin : Ad alanlarýný açýkça belirterek, hangi ad alanýna ait olduðunu
    net bir þekilde ifade edin.

    Using ifadelerinden(using statements) mümkünse kaçýnýn : Using ifadeleri, belirli bir ad alanýndaki tüm elemanlarý kullanýlabilir kýlar, 
    bu da isim çakýþmalarýna yol açabilir.Bu nedenle, sadece gerekli olan ad alanlarýný belirtmek daha iyidir.

    Using - directive'leri mümkünse kaçýnýn: Using-directive'ler, bir dosyanýn genel kapsamýný etkiler ve isim çakýþmalarýna neden olabilir.
    Bu nedenle, genellikle kullanýlmaktan kaçýnýlmalýdýr.

    Using - declaration'larý bloklar içinde kullanabilirsiniz: Using-declaration'lar, belirli bir blok içinde geçerlidir,
    bu da isim çakýþmalarýný sýnýrlar ve daha güvenli kullaným saðlar.Bu nedenle, genellikle bloklar içinde kullanýlabilirler.

    The "using" kelimesi, using ifadeleri ile ilgisi olmayan tür takma adlarý tanýmlamak için de kullanýlýr. Tür takma adlarý,
    10.7 dersinde ele alýnmaktadýr - Typedef'ler ve tür takma adlarý.

    */  
/*                                                        7.13 — Adsýz ve satýr içi ad alanlarý
    * Ýsimsiz ( anonim ) ad alanlarý
    --------------------------------
    isimsiz ad alanlarý ayný zamanda anonim ad alaný olarak da adlandýrýlýr. Bir ad alanýnýn tanýmlanýrken ismi olmadan tanýmlanmasýdýr. 
    Örneðin : 
        #include <iostream>

        namespace // isimsiz ad alaný
        {
            void doSomething() // sadece bu dosyadan eriþilebilir.
            {
                std::cout << "v1\n";
            }
        }

        int main()
        {
            doSomething(); // ön ek olmadan doSomething() fonksiyonunu çaðýrabiliriz. 

            return 0;
        }

        Bu çýktý olarak : "v1" çýktýsýný verir. 
    Ýsimsiz bir ad alanýnda tanýmlanan tüm içerik, bir üst ad alanýnýn bir parçasýymýþ gibi ele alýnýr. Yani, doSomething() fonksiyonu isimsiz
    ad alanýnda tanýmlansa da, fonksiyon kendisi üst ad alandan (bu durumda genel ad alanýndan) eriþilebilir, bu nedenle main() içinden herhangi
    bir nitelendirici olmadan doSomething() fonksiyonunu çaðýrabiliyoruz.

    Bu, isimsiz ad alanlarýný kullanýþsýz gibi gösterebilir. Ancak isimsiz ad alanlarýnýn diðer bir etkisi de, isimsiz bir ad alaný içindeki tüm
    tanýmlayýcýlarýn iç baðlantýya sahipmiþ gibi ele alýnmasýdýr. Bu, isimsiz bir ad alanýnýn içeriðinin tanýmlandýðý dosyanýn dýþýnda görülemediði 
    anlamýna gelir.

    Fonksiyonlar için, bu, isimsiz ad alanýndaki tüm fonksiyonlarý static fonksiyonlar olarak tanýmlamakla ayný etkiye sahiptir. Aþaðýdaki program,
    etkili olarak yukarýdakiyle aynýdýr:
    
        #include <iostream>

        static void doSomething() // can only be accessed in this file
        {
            std::cout << "v1\n";
        }

        int main()
        {
            doSomething(); // we can call doSomething() without a namespace prefix

            return 0;
        }


    Kullanýlmasý gereken yer heen belli zaten Ýsimsiz ad alanlarý genellikle bir dosyada yerel kalmalarýný istediðiniz birçok içeriðiniz 
    olduðunda kullanýlýr, çünkü bu içerikleri tek tek static olarak iþaretlemekten daha kolaydýr. Ýsimsiz ad alanlarý, program tarafýndan
    tanýmlanan türleri (bunu daha sonraki bir dersimizde tartýþacaðýz) dosyada yerel tutacak ve bunun için alternatif eþdeðer bir mekanizma
    bulunmayacaktýr.


    * Satýr içi ad alanlarý
    -----------------------
    Þimdi sýradaki programý takip edelim:
        #include <iostream>

        void doSomething()
        {
            std::cout << "v1\n";
        }

        int main()
        {
            doSomething();

            return 0;
        }

    ayný þekilde "v1" çýktýsýný verir. 
    Çok basit bir program fakat varsayalým ki doSomething()'den memnun deðilsiniz ve onun davranýþýný deðiþtiren bir þekilde iyileþtirmek 
    istiyorsunuz. Ancak bunu yaparsanýz, eski sürümü kullanan mevcut programlarý bozma riskiyle karþýlaþýrsýnýz. Bu durumu nasýl yönetiriz ?

    Bir yol, fonksiyonun yeni bir sürümünü farklý bir adla oluþturmaktýr. Ancak birçok deðiþiklik boyunca neredeyse ayný adý taþýyan bir 
    dizi fonksiyonla sonuçlanabilirsiniz (doSomething, doSomething_v2, doSomething_v3, vb.).

    Alternatif olarak, Satýr içi bir ad alaný kullanmaktýr. Satýr içi ad alaný, içeriði sürümlemek için genellikle kullanýlan bir ad alanýdýr. 
    Ýsimsiz bir ad alaný gibi, Satýr içi bir ad alaný içinde bildirilen her þey, ana ad alanýnýn bir parçasý olarak kabul edilir. Ancak, 
    isimsiz ad alanlarýndan farklý olarak, Satýr içi ad alanlarý baðlantýyý etkilemez.
    Satýr içi ad alanýný tanýmlamak için "inline" keyword ünü kullanýrýz. 
    Örneðin : 
        #include <iostream>

        inline namespace V1 // V1 adýnda bir satýr içi ad alaný tanýmladýk
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        namespace V2 // V2 adýnda normal ad alaný tanýmladýk
        {
            void doSomething()
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething in V1 versiyonunu çaðýrdýk
            V2::doSomething(); // doSomething in V2 versiyonunu çaðýrdýk

            doSomething(); // Satýr için V1 ad alaný doSomething fonksiyonunu çaðýrdýk.

            return 0;
        }
    Bu program bize : 
    * v1
    * v2
    * v1 
    çýktýsýný verdi 

    Yukarýdaki örnekte, doSomething() çaðrýlarý V1'i (satýr içi sürümü) alacaktýr. Daha yeni bir sürümü kullanmak isteyen çaðrý yapanlar,
    açýkça V2::doSomething() çaðrabilirler. Bu, mevcut programlarýn iþlevini korurken daha yeni programlarýn daha yeni/daha iyi varyasyonlardan
    yararlanmasýna olanak tanýr.

    Alternatif olarak, daha yeni sürümü yüklemek istiyorsanýz:

        #include <iostream>

        namespace V1 // declare a normal namespace named V1
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace V2 // declare an inline namespace named V2
        {
            void doSomething()
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // calls the V1 version of doSomething()
            V2::doSomething(); // calls the V2 version of doSomething()

            doSomething(); // calls the inline version of doSomething() (which is V2)

            return 0;
        }
    Bu örnekte, doSomething() fonksiyonunu çaðýran herkes varsayýlan olarak v2 sürümünü alacaktýr (daha yeni ve daha iyi sürüm).
    Hâlâ eski doSomething() sürümünü isteyen kullanýcýlar, eski davranýþa eriþmek için V1::doSomething() þeklinde açýkça çaðrý yapabilirler. 
    Bu, mevcut programlarýn V1 sürümünü isteyenlerin genellikle doSomething yerine V1::doSomething'ý global olarak deðiþtirmeleri gerekeceði 
    anlamýna gelir, ancak fonksiyonlar iyi adlandýrýlmýþsa genellikle sorun olmayacaktýr.

    Yeni versiyonu ise inline namespace V2 içine koyarak, bu versiyonun ana ad alanýnda olduðunu ve varsayýlan olarak kullanýlmasý gerektiðini
    belirtiyoruz. Yani, mevcut programlar deðiþiklik yapmadan doðrudan doSomething() çaðrýsý yaptýklarýnda, bu çaðrý otomatik olarak V2 ad 
    alanýndaki fonksiyonu kullanacaktýr. Bu, mevcut programlarýn deðiþiklik yapmaksýzýn yeni davranýþa geçmelerini saðlar.

    Bu iki adým, eski ve yeni versiyonlarýn birbirinden net bir þekilde ayrýlmasýný ve geçiþin kontrol altýnda yapýlmasýný saðlar. 
    Eski davranýþa ihtiyaç duyan programlar, V1::doSomething() þeklinde açýkça belirterek eski versiyonu kullanabilirler.


    * Satýr içi ve adsýz ad alanlarýný karýþtýrma
    ---------------------------------------------
    Bir ad alaný hem inline hem de isimsiz olabilir. 
        #include <iostream>

        namespace V1 // V1 adýnda normal bir ad alaný tanýmlar
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace // inline adsýz bir ad alaný tanýmlar
        {
            void doSomething() // has internal linkage
            {
                std::cout << "V2\n";
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething() in V1 versiyonunu çaðýrýr
            // V2 yok o yüzden V2:: ön eki ile çaðrý yapamayýz

            doSomething(); // doSomething() in inline olanýný çaðýrýr yani anonim olanýný.

            return 0;
        }

    Ancak, bu tür durumlarda, muhtemelen bir iç içe geçmiþ bir anonim ad alanýný bir inline ad alaný içine yerleþtirmek daha iyidir.
    Bu, ayný etkiye sahiptir (anonim ad alaný içindeki tüm iþlevler varsayýlan olarak iç baðlantýya sahiptir), ancak hala kullanabileceðiniz
    açýk bir ad alaný adý saðlar:
        #include <iostream>

        namespace V1 // normal V1 ad alanýný bildir
        {
            void doSomething()
            {
                std::cout << "V1\n";
            }
        }

        inline namespace V2 // V2 ad alanýný içeren bir inline ad alanýný bildir
        {
            namespace // adý olmayan ad alan
            {
                void doSomething() // iç baðlantýya sahip
                {
                    std::cout << "V2\n";
                }
            }
        }

        int main()
        {
            V1::doSomething(); // doSomething() fonksiyonunun V1 sürümünü çaðýrýr
            V2::doSomething(); // doSomething() fonksiyonunun V2 sürümünü çaðýrýr

            ::doSomething(); // doSomething() fonksiyonunun iç içe geçmiþ sürümünü çaðýrýr (ki bu V2'dir)

            return 0;
        }

*******************************************************************************************************************************************************
        CHapter 7 bitti. GENEL ÖZET ve chapter7_3 -> Quiz ve çözümlerim için oluþturulacak.







*/




























































    return 0;
}
