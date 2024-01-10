#include <iostream>
int main()
{

    
    return 0;

}
/*
Pass by address
---------------

C++, bir fonksiyona deðer iletimi için üçüncü bir yol saðlar, bu da "adres iletimi" olarak adlandýrýlýr. Adres iletimi ile, bir nesneyi argüman
olarak saðlamak yerine, çaðrýcý bir nesnenin adresini (bir iþaretçi aracýlýðýyla) saðlar. Bu iþaretçi (nesnenin adresini tutan) çaðrýlan
fonksiyonun bir iþaretçi parametresine kopyalanýr (bu parametre þimdi ayný zamanda nesnenin adresini de tutar). Fonksiyon daha sonra o 
iþaretçiyi dereference ederek geçilen adresi üzerinden eriþebilir ve nesneye ulaþabilir.

Ýþte yukarýdaki programýn bir adres iletimi varyasyonunu ekleyen bir versiyonu:

                    #include <iostream>
                    #include <string>

                    void printByValue(std::string val) // Fonksiyon parametresi str'nin bir kopyasýdýr
                    {
                        std::cout << val << '\n'; // kopya üzerinden deðeri yazdýr
                    }

                    void printByReference(const std::string& ref) // Fonksiyon parametresi, str'ye baðlanan bir referanstýr
                    {
                        std::cout << ref << '\n'; // referans üzerinden deðeri yazdýr
                    }

                    void printByAddress(const std::string* ptr) // Fonksiyon parametresi, str'nin adresini tutan bir iþaretçidir
                    {
                        std::cout << *ptr << '\n'; // dereferans edilmiþ iþaretçi üzerinden deðeri yazdýr
                    }

                    int main()
                    {
                        std::string str{ "Hello, world!" };

                        printByValue(str); // str'yi deðerle ileterek, str'nin bir kopyasýný oluþturur
                        printByReference(str); // str'yi referansla ileterek, str'nin bir kopyasýný oluþturmaz
                        printByAddress(&str); // str'yi adresle ileterek, str'nin bir kopyasýný oluþturmaz

                        return 0;
                    }
Bu versiyonlarýn üçünün de ne kadar benzer olduðuna dikkat edin. Adrese göre geçiþ sürümünü daha ayrýntýlý olarak inceleyelim.

Ýlk olarak, printByAddress() fonksiyonumuzun adrese göre geçiþ kullanmasýný istediðimiz için fonksiyon parametremizi ptr adýnda bir iþaretçi 
yaptýk. printByAddress() yöntemi ptr'yi salt okunur bir þekilde kullanacaðýndan, ptr bir const deðerinin iþaretçisidir.

                    void printByAddress(const std::string* ptr)
                    {
                         std::cout << *ptr << '\n'; // deðeri referansý alýnmýþ iþaretçi aracýlýðýyla yazdýrýyoruz
                    }
printByAddress() fonksiyonu içinde, iþaret edilen nesnenin deðerine eriþmek için ptr parametresinin referansýný kaldýrýrýz.

Ýkincisi, fonksiyon çaðrýldýðýnda sadece str nesnesini geçemeyiz, str adresini de aktarmamýz gerekir. Bunu yapmanýn en kolay yolu,
str adresini tutan bir iþaretçi elde etmek için adres operatörünü (&) kullanmaktýr:

                    printByAddress(&str); // str'nin iþaretçiyi tutan adresini almak için (&) operatörünün adresini kullanýn

Bu çaðrý yürütüldüðünde &str, str adresini tutan bir iþaretçi yaratacaktýr. Bu adres daha sonra fonksiyon çaðrýsýnýn bir parçasý olarak ptr
fonksiyon parametresine kopyalanýr. Ptr artýk str'nin adresini tuttuðu için, fonksiyon ptr'yi dereference yaptýðýnda yani çaðýrdýðýnda,
fonksiyonun konsola yazdýrdýðý str deðerini alacaktýr.

Bu kadar.

Yukarýdaki örnekte str adresini almak için adres operatörünü kullanmamýza raðmen, eðer str adresini tutan bir iþaretçi deðiþkenimiz zaten varsa,
bunun yerine bunu kullanabiliriz:

                    int main()
                    {
                        std::string str{ "Hello, world!" };

                        printByValue(str);     // str'yi deðerle ileterek, str'nin bir kopyasýný oluþturur
                        printByReference(str); // str'yi referansla ileterek, str'nin bir kopyasýný oluþturmaz
                        printByAddress(&str); // str'yi adresle ileterek, str'nin bir kopyasýný oluþturmaz

                        std::string* ptr { &str }; // str'nin adresini tutan bir iþaretçi deðiþkeni tanýmla
                        printByAddress(ptr); // pass str by address, does not make a copy of str

                        return 0;
                    }

Adres iletimi, iþaret edilen nesnenin bir kopyasýný oluþturmaz
--------------------------------------------------------------
Aþaðýdaki ifadeleri göz önünde bulundurun:

                    std::string str{ "Merhaba dünya!" };
                    printByAddress(&str); // str'nin iþaretçiyi tutan adresini almak için (&) operatörünün adresini kullanýn


12.5 -- Lvalue reference bölümünde belirtildiði gibi, bir std::string'in kopyalanmasý pahalý bir iþlemdir, bu nedenle bunu kaçýnmak istiyoruz.
Bir std::string'i adrese dayalý ilettiðimizde, aslýnda std::string nesnesini kopyalamýyoruz - sadece çaðrýcýdan çaðrýlan fonksiyona bir 
iþaretçi (nesnenin adresini tutan) kopyalýyoruz. Bir adres genellikle yalnýzca 4 veya 8 bayt olduðundan, bir iþaretçi de yalnýzca 4 veya
8 bayt olduðundan, bir iþaretçiyi kopyalamak her zaman hýzlýdýr.

Bu nedenle, referansla iletim gibi, adresle iletim de hýzlýdýr ve argüman nesnesinin bir kopyasýný oluþturmaktan kaçýnýr.

Adres iletimi, fonksiyona argümanýn deðerini deðiþtirme izni verir
------------------------------------------------------------------
Bir nesneyi adrese dayalý ilettiðimizde, fonksiyon iletilen nesnenin adresini alýr ve bu adresi dereferans aracýlýðýyla eriþebilir. 
Çünkü bu, iletilen nesnenin asýl argüman nesnesinin adresidir (nesnenin bir kopyasý deðil), eðer fonksiyon parametresi bir iþaretçiye
ve const olmayan bir iþaretçiye ise, fonksiyon argümaný iþaretçi parametresi üzerinden deðiþtirebilir:

                    #include <iostream>

                    void changeValue(int* ptr) // Not: Bu örnekte ptr, const olmayan bir iþaretçidir.
                    {
                        *ptr = 6; // Deðeri 6'ya deðiþtir
                    }

                    int main()
                    {
                        int x{ 5 };

                        std::cout << "x = " << x << '\n';

                        changeValue(&x); // x'in adresini fonksiyona iletiyoruz

                        std::cout << "x = " << x << '\n';

                        return 0;
                    }
                    Çýktý:
                    x = 5
                    x = 6

Gördüðünüz gibi, argüman deðiþtirildi ve bu deðiþiklik, changeValue() fonksiyonu çalýþmayý tamamladýktan sonra bile devam eder.
Eðer bir fonksiyonun iletilen nesneyi deðiþtirmesi gerekmeyen durumlar varsa, fonksiyon parametresi bir const iþaretçi yapýlabilir:

                    void changeValue(const int* ptr) // Not: ptr artýk bir const iþaretçisidir.
                    {
                        *ptr = 6; // hata: const deðeri deðiþtirilemez
                    }

Null Kontrolü
-------------
Þimdi bu oldukça masum görünen programý düþünün:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };
                        print(&x);

                        int* myPtr {};
                        print(myPtr);

                        return 0;
                    }

Bu program çalýþtýrýldýðýnda, deðer 5'i yazdýracak ve ardýndan muhtemelen çökecektir.

print(myPtr) çaðrýsýnda myPtr bir null iþaretçisidir, bu nedenle fonksiyon parametresi ptr da bir null iþaretçisi olacaktýr. Bu null iþaretçisi,
fonksiyonun içinde dereferans edildiðinde tanýmsýz davranýþa neden olur.

Bir parametreyi adrese dayalý iletim yaparken, deðeri dereferans etmeden önce iþaretçinin null bir iþaretçi olmadýðýndan emin olmak önemlidir.
Bunu yapmanýn bir yolu, bir koþul ifadesi kullanmaktýr:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        if (ptr) // Eðer ptr bir null pointer deðilse çalýþtýr
                        {
                            std::cout << *ptr << '\n';
                        }
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

Yukarýdaki programda, ptr'yi dereferans etmeden önce onun null olmadýðýndan emin olmak için bir test yapýyoruz. Bu basit bir fonksiyon için
uygun olsa da, daha karmaþýk fonksiyonlarda bu, gereksiz mantýk (ptr'nin birden çok kez null olup olmadýðýný test etme) veya temel mantýðýn
iç içe geçmesine (bir blok içinde ise) neden olabilir.

Çoðu durumda, etkili olaný yapmak, fonksiyon parametresinin null olup olmadýðýný önkoþul olarak kontrol etmek (9.6 -- Assert ve static_assert)
ve negatif durumu hemen ele almak olacaktýr:

                    #include <iostream>

                    void print(int* ptr)
                    {
                        if (!ptr) // Eðer ptr bir null iþaretçisi ise, çaðrýcýya erken dön
                            return;

                        // Bu noktaya ulaþtýysak, ptr'nin geçerli olduðunu varsayabiliriz
                        // bu nedenle baþka test veya iç içe geçme gerekmez

                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

Eðer bir null iþaretçisi fonksiyona asla iletilmemesi gerekiyorsa, bunun yerine (veya ayrýca) bir assert kullanýlabilir
(ki bunu 9.6 -- Assert ve static_assert dersinde inceledik) (çünkü assert'ler, asla gerçekleþmemesi gereken durumlarý belgelemek için 
tasarlanmýþtýr):

                    #include <iostream>
                    #include <cassert>

                    void print(const int* ptr) // artýk bir const int iþaretçisi
                    {
                        assert(ptr); // bir null iþaretçisi iletilirse programý hata vererek sonlandýr (çünkü bu asla gerçekleþmemelidir)

                        // (isteðe baðlý) bunu üretim modunda bir hata durumu olarak ele al, böylece gerçekleþirse çökme olmaz
                        if (!ptr)
                            return;

                        std::cout << *ptr << '\n';
                    }

                    int main()
                    {
                        int x{ 5 };

                        print(&x);
                        print(nullptr);

                        return 0;
                    }

pass by const reference tercih edin
-----------------------------------
Yukarýdaki örnekteki print() fonksiyonunun null deðerleri çok iyi ele almadýðýný unutmayýn - etkili bir þekilde fonksiyonu iptal eder.
Bu durumda, neden kullanýcýya hiç null bir deðeri iletmeye izin verelim? Adrese dayalý iletimin ayný avantajlara sahip olmasýna raðmen,
yanlýþlýkla bir null iþaretçisini dereference etme riski olmaksýzýn geçiþi saðlar.

const referans iletimi, adres iletimine göre birkaç avantaja sahiptir.

Ýlk olarak, bir adrese dayalý iletilen bir nesnenin bir adresi olmalýdýr, bu nedenle yalnýzca lvalue'lar bir adrese dayalý iletilmiþ olabilir
(çünkü rvalue'lar adreslere sahip deðildir). const referans iletimi daha esnek olup, lvalue'larý ve rvalue'larý kabul edebilir:

                    #include <iostream>

                    void printByValue(int val) // Fonksiyon parametresi argümanýn bir kopyasýdýr
                    {
                        std::cout << val << '\n'; // kopya üzerinden deðeri yazdýr
                    }

                    void printByReference(const int& ref) // Fonksiyon parametresi, argümana baðlanan bir referanstýr
                    {
                        std::cout << ref << '\n'; // referans üzerinden deðeri yazdýr
                    }

                    void printByAddress(const int* ptr) // Fonksiyon parametresi, argümanýn adresini tutan bir iþaretçidir
                    {
                        std::cout << *ptr << '\n'; // dereferans edilmiþ iþaretçi üzerinden deðeri yazdýr
                    }

                    int main()
                    {
                        printByValue(5);     // geçerli (ancak bir kopya oluþturur)
                        printByReference(5); // geçerli (çünkü parametre bir const referanstýr)
                        printByAddress(&5);  // hata: r-value'ýn adresi alýnamaz

                        return 0;
                    }

Ýkinci olarak, referansla iletimin sözdizimi doðaldýr, çünkü sadece literalleri veya nesneleri iletebiliriz. Adrese dayalý iletimle,
kodumuz sürekli olarak ampersand'lar (&) ve asterisk'ler (*) ile dolup taþar.

Modern C++'ta, adresle iletilen birçok þey, genellikle baþka yöntemlerle daha iyi gerçekleþtirilebilir. Bu yaygýn kuralý takip edin:
"Referansla iletebildiðinizde referansla iletimi tercih edin, adresle iletebildiðinizde adresle iletimi tercih edin."

**** BEST -> Bir nedeniniz olmadýkça referansla iletimi tercih edin ve adresle iletimi yalnýzca belirli bir nedeniniz olduðunda kullanýn.


"Optional" argümanlar için adres üzerinden geçme

Adres üzerinden geçme, iþlevin "isteðe baðlý" bir argümaný kabul etmesine izin vermek için daha yaygýn kullanýlan yöntemlerden biridir. 
Bu, açýklamaktan çok örnek ile daha kolay anlatýlabilir:

                    #include <iostream>
                    #include <string>

                    void greet(std::string* name=nullptr)
                    {
                        std::cout << "Hello ";
                        std::cout << (name ? *name : "guest") << '\n';
                    }

                    int main()
                    {
                        greet(); // user in kim olduðunu bilmiyoruz

                        std::string joe{ "Joe" };
                        greet(&joe); // User in Joe olduðunu biliyoruz

                        return 0;
                    }
                    Çýktý:
                    Hello guest
                    Hello Joe

Bu programda, greet() fonksiyonu, adres üzerinden geçilen ve varsayýlan olarak nullptr olan bir parametreye sahiptir. main() içinde bu
fonksiyonu iki kez çaðýrýyoruz. Ýlk çaðrýda kullanýcý kim olduðunu bilmiyoruz, bu nedenle greet() fonksiyonunu argüman olmadan çaðýrýyoruz.
name parametresi varsayýlan olarak nullptr'a atanýr ve greet fonksiyonu adý "guest" ile deðiþtirir. Ýkinci çaðrý için artýk geçerli bir 
kullanýcýmýz var, bu nedenle greet(&joe) þeklinde çaðýrýyoruz. name parametresi joe'nun adresini alýr ve bunu kullanarak adý "Joe" olarak 
yazdýrmak için kullanabilir.

Ancak, birçok durumda, ayný sonuca ulaþmak için fonksyion aþýrý yüklemenin (function overloading) daha iyi bir alternatif olduðu unutulmamalýdýr:

                    #include <iostream>
                    #include <string>
                    #include <string_view>

                    void greet(std::string_view name)
                    {
                        std::cout << "Hello " << name << '\n';
                    }

                    void greet()
                    {
                        greet("guest");
                    }

                    int main()
                    {
                        greet(); // we don't know who the user is yet

                        std::string joe{ "Joe" };
                        greet(joe); // we know the user is joe

                        return 0;
                    }

Bunun bir takým avantajlarý var: Artýk boþ referanslar konusunda endiþelenmemize gerek yok ve eðer istersek bir dizge deðiþmezini iletebiliriz.
Bir iþaretçi parametresinin neyi iþaret ettiðini deðiþtirme
-----------------------------------------------------------
Bir iþleve bir adres geçtiðimizde, bu adres, argümandan iþlevin içindeki iþaretçi parametresine kopyalanýr (bu, bir adresi kopyalamanýn hýzlý
olmasý nedeniyle sorun deðildir). Þimdi aþaðýdaki programý düþünün:

                    #include <iostream>

                    // [[maybe_unused]] ptr2'nin ayarlanmasýna raðmen kullanýlmamasýna iliþkin derleyici uyarýlarýndan kurtulur
                    void nullify([[maybe_unused]] int* ptr2)
                    {
                        ptr2 = nullptr; // Fonksiyon parametresini boþ gösterici yap
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x }; // ptr x'i gösteriyor

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

                        nullify(ptr);

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
                        return 0;
                    }
                    Çýktý:
                    ptr is non-null
                    ptr is non-null

Gördüðünüz gibi, iþaretçi parametrenin tuttuðu adresi deðiþtirmenin, argümanýn tuttuðu adres üzerinde herhangi bir etkisi olmadý 
(ptr hala x'e iþaret ediyor). nullify() fonksiyonu çaðrýldýðýnda, ptr2, içine geçirilen adresin bir kopyasýný alýr (bu durumda, ptr tarafýndan
tutulan adres, yani x'in adresi). Fonksiyon ptr2'nin neye iþaret ettiðini deðiþtirdiðinde, bu sadece ptr2 tarafýndan tutulan kopyayý etkiler.

Peki, bir fonksiyona bir iþaretçi argümanýn neye iþaret ettiðini deðiþtirmesine izin vermek istersek ne yapmalýyýz?

Pass by address… by reference?
------------------------------

Evet, bu mümkün. Sýradan bir deðiþkeni referans ile geçebildiðimiz gibi, iþaretçileri de referans ile geçebiliriz. Ýþte yukarýdaki programýn
ptr2'nin bir adres referansý olacak þekilde deðiþtirilmiþ hali:

                    #include <iostream>

                    void nullify(int*& refptr) // refptr þimdi bir pointer referansý oldu yani pointer e referans
                    {
                        refptr = nullptr; // Fonksiyon parametresini bir null iþaretçi yap
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x }; // ptr, x'e iþaret ediyor

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

                        nullify(ptr);

                        std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
                        return 0;
                    }
                    Çýktý:
                    ptr is non-null
                    ptr is null

Refptr artýk bir iþaretçiye referans olduðundan, ptr argüman olarak iletildiðinde refptr, ptr'ye baðlanýr. Bu, refptr'de yapýlan herhangi bir
deðiþikliðin ptr'ye de yapýlacaðý anlamýna gelir.

Ek bilgi olarak, iþaretçilere referanslar genellikle nadir kullanýldýðýndan, sözdizimini karýþtýrmak kolay olabilir (int*& mý yoksa int&* mi?).
Ýyi haber þu ki, tersini yaptýðýnýzda derleyici hata verecektir, çünkü bir referansa iþaretçi oluþturamazsýnýz (çünkü iþaretçiler bir nesnenin
adresini tutmalýdýr ve referanslar nesneler deðildir). Ardýndan, düzeltebilmeniz için sözdizimini deðiþtirebilirsiniz.

Sadece deðerle geçirme var

Referans, adres ve deðerle geçirme arasýndaki temel farklarý anladýðýnýzý varsayalým, þimdi biraz basitleþtirelim. :)

Derleyici genellikle referanslarý tamamen optimize edebilir, ancak bu mümkün olmayan durumlar vardýr ve bir referans aslýnda gereklidir.
Referanslar genellikle derleyici tarafýndan iþaretçiler kullanýlarak uygulanýr. Bu, arka planda referansýn bir adresle geçildiði (referansa
eriþim yapýlýrken ima edilen bir dolaylý adresleme) anlamýna gelir.

Ve önceki dersimizde, adresle geçiþin sadece bir adresi çaðýran iþlevden çaðrýlan iþleme kopyaladýðýný söylemiþtik - ki bu sadece bir deðeri
geçirmek demektir.
Bu nedenle, C++'ýn aslýnda her þeyi deðerle geçirdiðini söyleyebiliriz! Adresle (ve referansla) geçiþin özellikleri, geçilen adresi deðiþtirmek
için geçilen adrese dolaylý bir eriþim yapabilmemizden kaynaklanýr, ki bunu normal bir deðer parametresiyle yapamayýz!

Neden 0 veya NULL kullanýmýnýn artýk tercih edilmediðini açýklayalým (isteðe baðlý)
-----------------------------------------------------------------------------------
Bu alt bölümde, 0 veya NULL kullanýmýnýn neden artýk tercih edilmediðini açýklayacaðýz.

Sayýsal 0 hem bir tam sayý literali olarak hem de bir null iþaretçi literali olarak yorumlanabilir. Bazý durumlarda, hangisini amaçladýðýmýz
belirsiz olabilir - ve bu durumlardan bazýlarýnda derleyici, birini kastettiðimizi düþünerek diðerini düþünebilir - bu da programýmýzýn
davranýþýnda istenmeyen sonuçlara neden olabilir.

Öniþlemci makrosu NULL'ýn tanýmý dil standardý tarafýndan belirlenmemiþtir. 0, 0L, ((void*)0) veya baþka bir þey olarak tanýmlanabilir.

11.1 Dersinde - Fonksiyon aþýrý yükleme konusuna giriþ, fonksiyonlarýn aþýrý yüklenebileceðini tartýþtýk (çok sayýda fonksiyon ayný ismi
taþýyabilir, yeter ki parametrelerin sayýsý veya türü ile ayýrt edilebilsin). Derleyici, fonksiyon çaðrýsýnýn bir parçasý olarak iletilen
argümanlarla hangi aþýrý yüklenmiþ fonksiyonu istediðinizi çözebilir.

0 veya NULL kullanýrken bu sorunlara neden olabilir:

                    #include <iostream>
                    #include <cstddef> // NULL için

                    void print(int x) // bu fonksiyon bir tamsayýyý kabul eder
                    {
                        std::cout << "print(int): " << x << '\n';
                    }

                    void print(int* ptr) // bu fonksiyon bir tamsayý iþaretçisini kabul eder
                    {
                        std::cout << "print(int*): " << (ptr ? "null deðil\n" : "null\n");
                    }

                    int main()
                    {
                        int x{ 5 };
                        int* ptr{ &x };

                        print(ptr);  // her zaman print(int*)'i çaðýrýr, çünkü ptr tipi int* (iyi)
                        print(0);    // her zaman print(int)'i çaðýrýr, çünkü 0 bir tamsayý literali (umarým bu beklediðimiz þeydir)

                        print(NULL); // bu ifade aþaðýdakilerden herhangi birini yapabilir:
                        // print(int)'i çaðýr (Visual Studio bunu yapar)
                        // print(int*)'i çaðýr
                        // belirsiz bir iþlev çaðrýsý derleme hatasýna neden olabilir (gcc ve Clang bunu yapar)

                        print(nullptr); // her zaman print(int*)'i çaðýrýr

                        return 0;
                    }
                    Yazarýn makinesinde (Visual Studio kullanarak), bu þu þekilde yazdýrýr:

                    print(int*): non-null
                    print(int): 0
                    print(int): 0
                    print(int*): null

0 olarak geçirilen bir tam sayý deðeri parametre olarak kullanýldýðýnda, derleyici print(int*) yerine print(int) 'i tercih eder. Bu durum, 
print(int*) 'in bir null iþaretçi argümaný ile çaðrýlmasýný amaçlamýþken beklenmeyen sonuçlara yol açabilir.

Eðer NULL deðeri 0 olarak tanýmlanmýþsa, print(NULL) ifadesi de beklediðiniz gibi print(int*) 'i deðil, print(int) 'i çaðýracaktýr. Eðer NULL 0
olarak tanýmlanmamýþsa, baþka davranýþlar ortaya çýkabilir, örneðin print(int*) 'i çaðýrma veya derleme hatasý alabilirsiniz.

nullptr kullanmak bu belirsizliði ortadan kaldýrýr (her zaman print(int*) 'i çaðýracaktýr), çünkü nullptr sadece bir iþaretçi türü ile 
eþleþecektir.


std::nullptr_t (isteðe baðlý)

Çünkü nullptr, iþlev aþýrý yüklemelerinde tam sayý deðerlerinden ayýrt edilebileceðinden, farklý bir tipe sahip olmalýdýr. Peki nullptr'ýn tipi
nedir? Cevap þudur: nullptr'ýn tipi std::nullptr_t'dir (header <cstddef>'de tanýmlanmýþtýr). std::nullptr_t yalnýzca bir deðeri tutabilir:
nullptr! Bu biraz saçma görünebilir, ancak bir durumda kullanýþlýdýr. Eðer sadece bir nullptr literal argümanýný kabul eden bir fonksiyon 
yazmak istiyorsak, parametreyi std::nullptr_t yapabiliriz.

                    #include <iostream>
                    #include <cstddef> // std::nullptr_t için

                    void print(std::nullptr_t)
                    {
                        std::cout << "in print(std::nullptr_t)\n";
                    }

                    void print(int*)
                    {
                        std::cout << "in print(int*)\n";
                    }

                    int main()
                    {
                        print(nullptr); // print(std::nullptr_t) ý çaðýrýr

                        int x { 5 };
                        int* ptr { &x };

                        print(ptr); // print(int*) ý çaðýrýr

                        ptr = nullptr;
                        print(ptr); // print(int*) ý çaðýrýr (Çünkü ptr int* türüne sahip)

                        return 0;
                    }

Yukarýdaki örnekte, print(nullptr) fonksiyon çaðrýsý, dönüþüm gerektirmediði için print(std::nullptr_t)'ye karþý print(int*) fonksiyonunu çözer.

Biraz karýþtýrýcý olabilecek tek durum, ptr deðeri nullptr olan bir durumda print(ptr) çaðýrdýðýmýzda ortaya çýkabilir. Unutmayýn ki fonksiyon
aþýrý yüklemeleri tiplere göre eþleþir, deðerlere deðil, ve ptr'nin tipi int* olduðu için print(int*) eþleþecektir. Bu durumda 
print(std::nullptr_t) bile dikkate alýnmaz, çünkü iþaretçi tipleri otomatik olarak std::nullptr_t'ye dönüþmez.

Muhtemelen bunu hiç kullanmanýz gerekmez, ancak her ihtimale karþý bilmenizde fayda var.

Return by reference ve return by address
----------------------------------------
Fonksiyonlara deðer ile geçme konusunda sýnýf tiplerinin maliyetli olduðundan bahsettik. Ayný durumu return ile de karþýlaþýyoruz:
fonksiyonun geri dönüþ deðerinin bir kopyasý çaðýran tarafa geri gönderilir. Eðer fonksiyonun geri dönüþ tipi bir sýnýf tipiyse,
bu maliyetli olabilir.

                    std::string returnByValue(); // Bir std::string'in kopyasýný döndürür (maliyetli)

Referans ile dönüþ

Çaðýrana bir sýnýf tipi döndürdüðümüz durumlarda, dönüþ yapmayý (yapmamayý) düþünebiliriz. Referans ile dönüþ, döndürülen nesneye baðlý bir 
referans döndürür ve bu, dönüþ deðerinin bir kopyasýný yapmaktan kaçýnýr. Referans ile dönmek için, fonksiyonun dönüþ deðerini referans türü
olarak tanýmlamak yeterlidir:

                    std::string& returnByReference();                 // Mevcut bir std::string'e referans döndürür (ucuz)
                    const std::string& returnByReferenceToConst();    // Mevcut bir std::string'e const referans döndürür (ucuz)

Referans yoluyla geri dönüþ mekaniðini gösteren akademik bir program:

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName() // bir const referansý döndürür
                    {
                        static const std::string s_programName { "Calculator" }; // statik süreye sahiptir, programýn sonunda yok edilir

                        return s_programName;
                    }

                    int main()
                    {
                        std::cout << "This program is named " << getProgramName();

                        return 0;
                    }

                    Bu program þunlarý yazdýrýr:
                    This program is named Calculator

getProgramName() bir const referansý döndürdüðü için, return s_programName satýrý çalýþtýrýldýðýnda getProgramName() s_programName'e bir const
referansý döndürecektir (böylece bir kopya yapmaktan kaçýnýlmýþ olur). Bu const referansý daha sonra çaðýran tarafýndan yazdýrýlan
s_programName deðerine eriþmek için kullanýlabilir.

Referans ile döndürülen nesne, fonksiyon geri döndükten sonra var olmalýdýr
---------------------------------------------------------------------------

Referans ile dönme kullanmanýn önemli bir sakýncasý vardýr: programcý, referansýn döndürülen fonksiyondan sonra referans yapýlan nesnenin
yaþadýðýndan emin olmalýdýr. Aksi takdirde, döndürülen referans uçuk (yok edilmiþ bir nesneyi iþaret eden) olarak kalacak ve bu referansýn
kullanýmý tanýmsýz davranýþa yol açacaktýr.

Yukarýdaki programda, s_programName'in statik süresi olduðundan, s_programName programýn sonuna kadar var olacaktýr. Main() döndürülen
referansa eriþtiðinde, aslýnda s_programName'e eriþiyor, ki bu sorun deðildir, çünkü s_programName daha sonra yok edilene kadar var
olmayacaktýr.

Þimdi yukarýdaki programý deðiþtirerek, fonksiyonumuzun uçuk bir referans döndürdüðü durumu gösterelim:

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName()
                    {
                        const std::string programName { "Calculator" }; // Þimdi statik olmayan bir deðiþken var, Bu yüzden fonksiyon sonunda 
                                                                           bu deðiþken yok edilecek

                        return programName;
                    }

                    int main()
                    {
                        std::cout << "This program is named " << getProgramName(); // tanýmsýz davranýþ

                        return 0;
                    }

Bu programýn sonucu tanýmsýzdýr. getProgramName() çaðrýldýðýnda, yerel bir deðiþkene baðlý bir referans döndürülür. Ardýndan,programýn sonunda
programName yok edilir çünkü programName otomatik süreli bir yerel deðiþkendir . Bu, döndürülen referansýn þu anda uçuk olduðu anlamýna gelir
ve main() fonksiyonundaki programName'in kullanýmý tanýmsýz davranýþa yol açar.

Modern derleyiciler, genellikle bir referans ile yerel bir deðiþkeni döndürmeye çalýþtýðýnýzda bir uyarý veya hata üretir (bu nedenle
yukarýdaki program bile derlenmeyebilir), ancak derleyiciler bazen daha karmaþýk durumlarý algýlamakta zorlanabilir.

Uyarý olarak kýsaca þöyle diyebiliriz ; 

Referans ile döndürülen nesneler, referansý döndüren fonksiyonun kapsamýnýn ötesinde yaþamalýdýr, aksi takdirde bir uçuk referans elde edilir.
Asla (static olmayan) bir yerel deðiþkeni veya geçici deðiþkeni referans ile döndürmeyin.

Ömür uzatma iþlemi fonksiyon sýnýrlarý aþan durumlarda çalýþmaz
---------------------------------------------------------------
Hadi bir örneðe bakalým, burada bir geçici deðeri referans olarak döndürüyoruz:

                    #include <iostream>

                    const int& returnByConstReference()
                    {
                        return 5; //Geçici bir nesneye const int referansý döner
                    }

                    int main()
                    {
                        const int& ref { returnByConstReference() };

                        std::cout << ref; // tanýmsýz davranýþ

                        return 0;
                    }

Yukarýdaki programda, returnByConstReference() fonksiyonu bir tamsayý literali döndürüyor, ancak fonksiyonun dönüþ tipi const int& olarak 
belirlenmiþ. Bu durum, deðeri 5 olan bir geçici nesneye baðlý bir geçici referansýn oluþturulmasýna yol açar. Bu geçici referans daha sonra
döndürülür. Geçici nesne daha sonra kapsam dýþýna çýkar ve referansý sallantýda býrakýr.

Dönüþ deðeri (main() fonksiyonundaki diðer bir const referansa baðlandýðýnda) baþka bir const referansa baðlandýðýnda, geçici nesnenin
ömrünü uzatmak için çok geçtir - çünkü zaten yok edilmiþtir. Bu nedenle, ref isimli referans bir sallantý referansýna baðlý olacaktýr ve ref
deðerinin kullanýlmasý tanýmsýz davranýþa neden olacaktýr.

Ýþte benzer þekilde çalýþmayan daha az açýk bir örnek:

                    #include <iostream>

                    const int& returnByConstReference(const int& ref)
                    {
                        return ref;
                    }

                    int main()
                    {
                        // Durum 1: Direkt baðlanma
                        const int& ref1 { 5 }; // Ömür uzatýmý
                        std::cout << ref1 << '\n'; // Tamam uygun

                        // Durum 2: Dolaylý baðlanma
                        const int& ref2 { returnByConstReference(5) }; // sallantýdaki referansa baðlanma
                        std::cout << ref2 << '\n'; // tanýmsýz davranýþ

                        return 0;
                    }

Durum 2'de, deðeri 5 olan bir geçici nesne oluþturulur ve fonksiyon parametresi olan ref bu nesneye baðlanýr. Fonksiyon sadece bu referansý 
çaðrýcýya geri döndürür, ardýndan çaðrýcý bu referansý ref2'yi baþlatmak için kullanýr. Bu, doðrudan geçici nesneye baðlanmýþ bir durum
olmadýðýndan (referans fonksiyon aracýlýðýyla geçirildiði için), ömür uzatma iþlemi uygulanmaz. Bu durumda, ref2 sallantýda kalýr ve sonraki 
kullanýmý tanýmsýz davranýþa neden olur.

Uyarý -> Referans ömür uzatmasý fonksiyon sýnýrlarý aþan durumlarda çalýþmaz.

Const olmayan statik yerel deðiþkenleri referans olarak döndürmeyin
-------------------------------------------------------------------
Deðiþtirilemeyen (const) statik yerel deðiþkenleri referans olarak döndürmek, referans ile dönüþ mekanizmasýný basit bir þekilde göstermek
amacýyla yapýlan örneklerde kullanýþlýdýr. Ancak, genel olarak deðiþtirilemeyen (const) olmayan statik yerel deðiþkenleri referans olarak 
döndürmek pek yaygýn olmayan bir yöntemdir ve genellikle kaçýnýlmalýdýr. Ýþte böyle bir durumda ortaya çýkabilecek bir problemi gösteren 
basitleþtirilmiþ bir örnek:

                    #include <iostream>
                    #include <string>

                    const int& getNextId()
                    {
                        static int s_x{ 0 }; // not: deðiþken deðiþtirilemeyen (const) deðildir
                        ++s_x; // bir sonraki kimliði oluþtur
                        return s_x; // ve ona bir referans döndür
                    }

                    int main()
                    {
                        const int& id1 { getNextId() }; // id1 bir referanstýr
                        const int& id2 { getNextId() }; // id2 bir referanstýr

                        std::cout << id1 << id2 << '\n';

                        return 0;
                    }
                    Çýktý:
                    22

Bu durum, id1 ve id2'nin ayný nesneye (static deðiþken s_x) referans olmasýndan kaynaklanmaktadýr, bu nedenle herhangi bir þey
(örneðin getNextId()) deðeri deðiþtirdiðinde tüm referanslar deðiþtirilmiþ deðeri kullanmaktadýr.

Bir diðer yaygýn sorun ise, non-const static yerel deðiþkenleri referans olarak döndüren programlarda s_x'i varsayýlan durumuna sýfýrlamak için
standartlaþtýrýlmýþ bir yolun olmamasýdýr. Bu tür programlar, genellikle non-idiomatik bir çözüm (örneðin bir sýfýrlama fonksiyon parametresi)
kullanmak zorunda kalýr veya programý sonlandýrýp yeniden baþlatarak sýfýrlayabilir.

Yukarýdaki örnek biraz saçma olsa da, programcýlar bazen optimizasyon amaçlarýyla denedikleri yukarýdaki benzer varyasyonlar nedeniyle 
beklenmedik sonuçlar alabilirler.

*** BEST -> Non-const yerel static deðiþkenlere referans döndürmekten kaçýnýn.

Eðer döndürülen referans ile bir const yerel static deðiþkenine referans oluþturmak gerekiyorsa, bu nadiren yapýlýr. Bu durum, döndürülen yerel
deðiþkenin her fonksiyon çaðrýsýnda oluþturulmasý maliyetli olduðunda kullanýlabilir ancak bu durum nadirdir.
Bir const yerel static deðiþkenine referans döndürmek, bazen bir global deðiþkenin eriþimini kapsüle etmek için kullanýlýr. Bu kullaným,
istenildiði takdirde dikkatlice ve amaçlý bir þekilde yapýlabilir.

Bir normal deðiþkeni bir geri dönen referans ile atamak/initialize etmek bir kopya oluþturur
--------------------------------------------------------------------------------------------

Eðer bir fonksiyon bir referans döndürüyorsa ve bu referans bir referans olmayan bir deðiþkeni initialize etmek veya atamak için kullanýlýyorsa,
dönüþ deðeri kopyalanýr (sanki deðer olarak döndürülmüþ gibi).

                    #include <iostream>
                    #include <string>

                    const int& sonrakiIdyiAl()
                    {
                        static int s_x{ 0 };
                        ++s_x;
                        return s_x;
                    }

                    int main()
                    {
                        // id1 þu anda normal bir deðiþken ve sonrakiIdyiAl fonksiyonunun referans ile döndürdüðü deðerin bir kopyasýný alýr
                        const int id1 { sonrakiIdyiAl() };
                        // id2 þu anda normal bir deðiþken ve sonrakiIdyiAl fonksiyonunun referans ile döndürdüðü deðerin bir kopyasýný alýr
                        const int id2 { sonrakiIdyiAl() }; 

                        std::cout << id1 << id2 << '\n';

                        return 0;
                    }

Yukarýdaki örnekte, getNextId() bir referans döndürüyor ancak id1 ve id2 referans olmayan deðiþkenler. Bu durumda, döndürülen referansýn
deðeri normal deðiþkenlere kopyalanýr. Bu nedenle, bu program þu þekilde yazdýrýr:
                    12
Tabii ki, bu ayný zamanda bir deðeri referans ile döndürmenin amacýný da boþa çýkarýr.

Ayrýca, eðer bir program bir geçersiz referans döndürüyorsa, kopya yapmadan önce referansýn geçersiz kalacaðýný unutmayýn. Bu durum,
tanýmsýz davranýþa yol açacaktýr.

                    #include <iostream>
                    #include <string>

                    const std::string& getProgramName() // bir const referans döndürecek
                    {
                        const std::string programName{ "Calculator" };

                        return programName;
                    }

                    int main()
                    {
                        std::string name { getProgramName() }; // bir asýlý referansýn kopyasýný oluþturur
                        std::cout << "This program is named " << name << '\n'; // tanýmsýz davranýþ

                        return 0;
                    }

Referans parametrelerini referans olarak döndürmek sorun deðildir
-----------------------------------------------------------------
Referans ile geçilen nesnelerin referans olarak döndürülmesi mantýklý olan birkaç durum vardýr ve bunlarla ilgili birçok durumla ilerleyen 
derslerde karþýlaþacaðýz. Ancak þu anda gösterebileceðimiz kullanýþlý bir örnek var.

Eðer bir parametre referans ile bir fonksiyona iletilmiþse, o parametreyi referans olarak döndürmek güvenlidir. Bu mantýklýdýr: Bir argümaný
bir fonksiyona iletmek için, argüman çaðýrýcýnýn kapsamýnda var olmalýdýr. Çaðrýlan fonksiyon geri döndüðünde, bu nesne hala çaðrýcýnýn 
kapsamýnda var olmalýdýr.

Ýþte böyle bir fonksiyonun basit bir örneði:

                    #include <iostream>
                    #include <string>

                    // Ýki std::string nesnesini alýr, alfabetik sýrayla hangisinin önce geldiðini döndürür
                    const std::string& firstAlphabetical(const std::string& a, const std::string& b)
                    {
                        // std::string üzerinde operator<'ý kullanabiliriz, hangisinin alfabetik olarak önce geldiðini belirlemek için
                        return (a < b) ? a : b;
                    }

                    int main()
                    {
                        std::string hello { "Hello" };
                        std::string world { "World" };

                        std::cout << firstAlphabetical(hello, world) << '\n';

                        return 0;
                    }
                    Çýktý:
                    Hello


Yukarýdaki fonksiyonda, çaðrýcý iki std::string nesnesini const referans olarak iletiyor ve bu nesnelerden hangisi alfabetik olarak önce
gelirse, o nesne const referans olarak geri döndürülüyor. Eðer deðer ile iletim ve deðer ile dönüþ kullanmýþ olsaydýk, std::string için
toplamda 3 kopya yapmýþ olacaktýk (her bir parametre için bir tane, dönüþ deðeri için bir tane). Referans ile iletim ve referans ile dönüþ
kullanarak, bu kopyalardan kaçýnabiliriz.
*/