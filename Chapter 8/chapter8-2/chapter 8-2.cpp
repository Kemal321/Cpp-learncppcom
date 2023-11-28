#include <iostream>

int main()
{
    return 0;
}
/*
Break ve Continue
-----------------
Break

Switch ifadeleri baðlamýnda break ifadesini zaten gördünüz (8.5 -- Switch ifadesi temelleri), ancak bu ifade diðer kontrol akýþ ifadeleriyle de kullanýlabilir,
bu nedenle daha detaylý bir açýklamayý hak ediyor. break ifadesi, bir while döngüsü, do-while döngüsü, for döngüsü veya switch ifadesini sonlandýrýr ve kýrýlan
döngü veya switch ifadesinden sonra gelen bir sonraki ifadeyle devam eder

Brak ile switch kullanýmý
-------------------------
Switch ifadesi baðlamýnda, bir break genellikle her durumun sonunda kullanýlýr ve bu durumun bittiðini belirtmek için kullanýlýr
(bu, ardýþýk durumlara geçiþin önlenmesini saðlar):
                #include <iostream>

                void printMath(int x, int y, char ch)
                {
                    switch (ch)
                    {
                    case '+':
                        std::cout << x << " + " << y << " = " << x + y << '\n';
                        break; // ardýþýk durumlara geçme
                    case '-':
                        std::cout << x << " - " << y << " = " << x - y << '\n';
                        break; // ardýþýk durumlara geçme
                    case '*':
                        std::cout << x << " * " << y << " = " << x * y << '\n';
                        break; // ardýþýk durumlara geçme
                    case '/':
                        std::cout << x << " / " << y << " = " << x / y << '\n';
                        break;
                    }
                }

                int main()
                {
                    printMath(2, 3, '+');

                    return 0;
                }

Bir loop ile break in kullanýmý
--------------------------------
Döngü baðlamýnda, bir `break` ifadesi döngüyü erken sonlandýrmak için kullanýlabilir. Ýþlem, döngünün sonundan sonraki ifadeyle devam eder.
                #include <iostream>

                int main()
                {
                    int sum{ 0 };

                    // Kullanýcýya 10'a kadar sayý girmesine izin ver
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        std::cout << "Eklemek için bir sayý girin veya çýkmak için 0 girin: ";
                        int num{};
                        std::cin >> num;

                        // Kullanýcý 0 girdiyse döngüden çýk
                        if (num == 0)
                            break; // döngüden þimdi çýk

                        // Aksi takdirde sayýyý toplamýmýza ekleyin
                        sum += num;
                    }

                    // break'ten sonra iþlem buradan devam edecek
                    std::cout << "Girdiðiniz tüm sayýlarýn toplamý: " << sum << '\n';

                    return 0;
                }

Bu program, kullanýcýnýn 10'a kadar sayý girmesine izin verir ve giriþ yapýlan tüm sayýlarýn toplamýný
sonunda görüntüler. Kullanýcý 0 girdiðinde, break, döngünün erken sona ermesine (10 sayý girilmeden önce) neden olur.
Çýktý : 
                Bir sayý eklemek için girin veya çýkmak için 0 girin: 5
                Bir sayý eklemek için girin veya çýkmak için 0 girin: 3
                Bir sayý eklemek için girin veya çýkmak için 0 girin: 8
                Bir sayý eklemek için girin veya çýkmak için 0 girin: 0
                Girdiðiniz tüm sayýlarýn toplamý: 16

`break`, isteðe baðlý olarak sonsuz bir döngüden çýkmak için yaygýn olarak kullanýlan bir yöntemdir yukarýdaki iþlemin aynýsý bir if bloðu ile yapýlabilir. 

Break vs return 
---------------
`Break` ve `return` ifadeleri arasýndaki farký anlamak yeni programcýlar için bazen zor olabilir. Bir `break` ifadesi, switch veya döngüyü sonlandýrýr ve iþlem,
switch veya döngünün ötesindeki ilk ifadeyle devam eder. Bir `return` ifadesi ise içinde bulunduðu fonksiyonu tamamen sonlandýrýr ve iþlem, fonksiyonun çaðrýldýðý 
noktada devam eder.

                        #include <iostream>

                        int breakOrReturn()
                        {
                            while (true) // sonsuz döngü
                            {
                                std::cout << "'b' girmek için veya 'r' girmek için: ";
                                char ch{};
                                std::cin >> ch;

                                if (ch == 'b')
                                    break; // iþlem, döngünün ötesindeki ilk ifadeyle devam edecektir

                                if (ch == 'r')
                                    return 1; // return, fonksiyonun hemen çaðrýldýðý yere (bu durumda main()) geri dönecektir
                            }

                            // döngüyü kýrmak, iþlemin buradan devam etmesine neden olur

                            std::cout << "Döngüden çýktýk\n";

                            return 0;
                        }

                        int main()
                        {
                            int returnValue{ breakOrReturn() };
                            std::cout << "breakOrReturn fonksiyonu þunu döndürdü: " << returnValue << '\n';

                            return 0;
                        }

Bu programýn iki çalýþtýrmasý:

                        'b' girmek için veya 'r' girmek için: r
                        breakOrReturn fonksiyonu 1 döndürdü

                        'b' girmek için veya 'r' girmek için: b
                        Döngüden çýktýk
                        breakOrReturn fonksiyonu 0 döndürdü

`Continue` ifadesi
------------------
`continue` ifadesi, mevcut döngü iterasyonunu sonlandýrmadan tüm döngüyü sonlandýrmak için uygun bir yol saðlar.

Ýþte `continue` kullanýmýnýn bir örneði:

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // eðer sayý 4'e bölünebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue; // bir sonraki iterasyona git

                        // Eðer sayý 4'e bölünebiliyorsa, devam et
                        std::cout << count << '\n';

                        // continue ifadesi buraya atlar
                    }

                    return 0;
                }

Yani bu program 4 e bölünemeyen sayýlarý yazdýrýr
                    1
                    2
                    3
                    5
                    6
                    7
                    9
`continue` ifadesi, mevcut yürütme noktasýný mevcut döngünün altýna atarak çalýþýr.

Bir for-döngüsü durumunda, for-döngüsünün end ifadesi (yukarýdaki örnekte `++count`), continue'dan sonra hala çalýþýr (çünkü bu, döngü gövdesinin sonundan sonra 
gerçekleþir).

Dikkatli olun, bir continue ifadesini while veya do-while döngüleri ile kullanýrken. Bu döngüler genellikle döngü gövdesi içinde kullanýlan deðiþkenlerin deðerini 
deðiþtirir. Eðer continue ifadesi, bu satýrlarýn atlanmasýna neden oluyorsa, döngü sonsuz olabilir!

break ve continue kullanýmý üzerine yapýlan tartýþma
----------------------------------------------------
Birçok kaynak, break ve continue ifadelerinin döngülerde kullanýlmasýndan kaçýnýlmasý gerektiði konusunda okuyucularý uyarýr, çünkü bu ifadeler, yürütme akýþýnýn
atlamasýna neden olabilir ve mantýk akýþýný takip etmeyi zorlaþtýrabilir. Örneðin, karmaþýk bir mantýk parçasýnda ortasýnda bir break, ya atlanabilir ya da ne 
koþullar altýnda tetiklenmesi gerektiði açýk olmayabilir.

Ancak, dikkatli bir þekilde kullanýldýðýnda, break ve continue, döngüleri daha okunabilir hale getirmeye yardýmcý olabilir. Bu ifadeler, iç içe geçmiþ bloklarýn 
sayýsýný azaltarak ve karmaþýk döngü mantýðýna duyulan ihtiyacý azaltarak, döngüleri daha anlaþýlýr hale getirebilir.
Örneðin: 
            #include <iostream>

            int main()
            {
                int count{ 0 }; // döngünün kaç kez tekrarlandýðýný say
                bool keepLooping { true }; // döngünün bitip bitmediðini kontrol eder
                while (keepLooping)
                {
                    std::cout << "Bu döngüden çýkmak için 'e' girin veya devam etmek için herhangi bir karakter girin: ";
                    char ch{};
                    std::cin >> ch;

                    if (ch == 'e')
                        keepLooping = false;
                    else
                    {
                        ++count;
                        std::cout << "Biz " << count << " kez tekrarladýk\n";
                    }
                }

                return 0;
            }

Bu program, döngünün devam edip etmeyeceðini kontrol etmek için bir Boolean deðiþkeni ve kullanýcý çýkýþ yapmazsa yalnýzca çalýþan iç içe geçmiþ bir blok kullanýr.
Break kullanýlarak oluþturulmuþ haline bakalým bir de:
                    #include <iostream>

                    int main()
                    {
                        int count{ 0 }; // döngünün kaç kez tekrarlandýðýný say
                        while (true) // kullanýcý sonlandýrana kadar döngüyü sürdür
                        {
                            std::cout << "Bu döngüden çýkmak için 'e' girin veya devam etmek için herhangi bir karakter girin: ";
                            char ch{};
                            std::cin >> ch;

                            if (ch == 'e')
                                break;

                            ++count;
                            std::cout << "Biz " << count << " kez tekrarladýk\n";
                        }

                        return 0;
                    }

Bu versiyonda, tek bir break ifadesi kullanarak bir Boolean deðiþkenin kullanýmýný (ve amaçlanan kullanýmýnýn ne olduðunu ve nerede deðerinin deðiþtiðini anlamanýn
gerekliliðini), bir else ifadesini ve iç içe geçmiþ bir bloku önledik.

continue ifadesi, bir koþul karþýlandýðýnda döngü iterasyonlarýný atlamak için en etkili þekilde bir for-döngüsünün baþýnda kullanýlýr. Bu, iç içe geçmiþ bir bloku
önlememize olanak tanýyabilir.

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // eðer sayý 4'e bölünmüyorsa...
                        if ((count % 4) != 0) // iç içe geçmiþ blok
                        {
                                // Sayýyý yazdýr
                                std::cout << count << '\n';
                        }
                    }

                    return 0;
                }


Bunun yerine bunu yazabiliriz:

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // eðer sayý 4'e bölünebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue;

                        // iç içe geçmiþ bir blok gerekli deðil

                        std::cout << count << '\n';
                    }

                    return 0;
                }

Deðiþkenlerin sayýsýný en aza indirme ve iç içe geçmiþ bloklarýn sayýsýný azaltma, kodun anlaþýlýrlýðýný artýrýrken, bir break veya continue kullanmanýn 
bu anlaþýlýrlýðý bozmasýndan daha etkilidir. Bu nedenle, break veya continue'nin ölçülü bir þekilde kullanýlmasýný kabul edilebilir buluyoruz.

*** BEST -> Loop mantýðýnýzý basitleþtirmek için break ve continue kullanýn.

Early return ( break ve continue ye benzer bir durum du hatýrlamak iyidir )
----------------------------------------------------------------------------
Erken dönüþlerin kullanýmýna dair benzer bir argüman da return ifadeleri için yapýlabilir. Bir fonksiyon içindeki son ifade olmayan bir return ifadesine erken 
dönüþ denir. Birçok programcý, erken dönüþlerden kaçýnýlmasý gerektiðine inanýr. Fonksiyonu sadece bir return ifadesi olan ve bu ifadenin fonksiyonun altýnda
bulunduðu bir yapý, basitlik taþýr - fonksiyonun argümanlarý alacaðýný, uyguladýðý mantýðý gerçekleþtireceðini ve sapma olmadan bir sonuç döndüreceðinizi 
varsayabilirsiniz. Ekstra dönüþ ifadeleri, mantýðý karmaþýklaþtýrýr.

Karþý argüman ise erken dönüþlerin fonksiyonunuzu hemen bitirmesine olanak tanýdýðýný, bu sayede gereksiz mantýk okuma ve koþullu iç içe geçmiþ bloklarý en aza 
indirdiðini ve kodunuzu daha okunabilir hale getirdiðini savunur.

Bazý geliþtiriciler orta bir yol izler ve erken dönüþleri yalnýzca fonksiyonun baþýnda parametre doðrulama (geçersiz argümanlarýn yakalanmasý) için kullanýr, 
ardýndan tek bir dönüþ ifadesi kullanýr.

Bizim duruþumuz erken dönüþlerin daha çok yardýmcý olduðu yönündedir, ancak bunun pratiðinde bir miktar sanat olduðunu kabul ediyoruz.

*** BEST -> Erken dönüþler, fonksiyonunuzun mantýðýný basitleþtiriyorsa kullanýn.

                                                        8.12 Halts (Programýnýzý Erken Sonlandýrma)
                                                        -------------------------------------------


Bu bölümde ele alacaðýmýz akýþ kontrol ifadesi kategorisi, "halt"tir. Bir "halt", programý sonlandýran bir akýþ kontrol ifadesidir. C++'da, "halt"lar fonksiyonlar 
olarak uygulanýr (anahtar kelimeler olarak deðil), bu nedenle "halt" ifadelerimiz fonksiyon çaðrýlarý olacaktýr.

Kýsaca, bir program normal olarak sona erdiðinde neler olduðunu özetleyelim. main() fonksiyonu döndüðünde (fonksiyonun sonuna ulaþarak veya bir return ifadesi 
aracýlýðýyla), bir dizi farklý þey gerçekleþir.

Ýlk olarak, fonksiyondan çýkýldýðý için tüm yerel deðiþkenler ve fonksiyon parametreleri (normalde olduðu gibi) yok edilir.

Sonrasýnda, main() fonksiyonundan dönen deðer (durum kodu) ile std::exit() adlý özel bir fonksiyon çaðrýlýr. Peki std::exit() nedir?
std::exit() nedir 
-----------------

std::exit() iþlevi, programýn normal bir þekilde sona ermesine neden olan bir fonksiyondur. Normal sonlanma, programýn beklenen bir þekilde sonlandýðý anlamýna
gelir. Normal sonlanma terimi, programýn baþarýlý olup olmadýðý konusunda bir þey ifade etmez (bu, durum kodu içindir). Örneðin, kullanýcýnýn iþlem yapmak için
bir dosya adý yazmasýný beklediðiniz bir program yazýyorsanýz, eðer kullanýcý geçerli olmayan bir dosya adý yazarsa, programýnýz muhtemelen baþarýsýzlýk durumunu
göstermek için bir sýfýr olmayan durum kodu döndürecektir, ancak hala normal bir sona erme olacaktýr.

std::exit(), bir dizi temizlik iþlevini gerçekleþtirir. Ýlk olarak, statik depolama süresine sahip nesneler yok edilir. Ardýndan, eðer dosyalar kullanýldýysa,,
baþka bazý dosya temizliði yapýlýr. Son olarak, kontrol, std::exit() 'e iletilen argüman olarak kullanýlan durum koduyla birlikte iþletim sistemine geri döner.


std::exit i açýkça kullanma
---------------------------
std::exit() fonksiyonu, main() fonksiyonu sona erdiðinde dolaylý olarak çaðrýlsa da, std::exit() ayrýca programýn normal olarak sona ermeden önce programý
durdurmak için açýkça çaðrýlabilir. Bu þekilde std::exit() çaðrýldýðýnda, cstdlib baþlýk dosyasýný içermelisiniz.

Ýþte std::exit() 'i açýkça kullanmanýn bir örneði:
                                                #include <cstdlib> // std::exit() için
                                                #include <iostream>

                                                void cleanup()
                                                {
                                                    // Gerekli her türlü temizlik için burada kod bulunabilir
                                                    std::cout << "cleanup!\n";
                                                }

                                                int main()
                                                {
                                                    std::cout << 1 << '\n';
                                                    cleanup();

                                                    std::exit(0); // programý sonlandýr ve iþletim sistemine durum kodu 0 döndür

                                                    // Aþaðýdaki ifadeler hiçbir zaman çalýþtýrýlmaz
                                                    std::cout << 2 << '\n';

                                                    return 0;
                                                }




bu program þu çýktýyý verir :
                                                        1
                                                        cleanup!

Unutmayýn ki, std::exit() çaðrýsýndan sonra gelen ifadeler çalýþtýrýlmaz çünkü program zaten sona ermiþtir.

Yukarýdaki programda std::exit()'i main() fonksiyonundan çaðýrýyor olsak da, std::exit() herhangi bir fonksiyondan çaðrýlabilir ve programý o noktada sonlandýrabilir.
std::exit()'i açýkça çaðýrma konusunda önemli bir not: std::exit(), herhangi bir yerel deðiþkeni (hem mevcut fonksiyonda hem de çaðrý yýðýnýndaki diðer fonksiyonlarda)
temizlemez. Bu nedenle, genellikle std::exit() çaðrýsýndan kaçýnýlmasý daha iyidir.

*** UYARI -> std::exit() fonksiyonu, mevcut fonksiyondaki veya çaðrý yýðýnýndaki diðer fonksiyonlardaki yerel deðiþkenleri temizlemez.

std::atexit()
-------------
Çünkü std::exit(), programý hemen sonlandýrýr, sonlandýrmadan önce manuel olarak bazý temizleme iþlemleri yapmak isteyebilirsiniz. Bu baðlamda, temizleme,
veritabaný veya að baðlantýlarýný kapatma, ayrýlmýþ belleði serbest býrakma, bir günlüðe bilgi yazma vb. gibi iþleri içerir...

Yukarýdaki örnekte, temizleme görevlerimizi ele almak için cleanup() fonksiyonunu çaðýrdýk. Ancak, her exit() çaðrýsýndan önce manuel olarak bir temizleme 
fonksiyonunu çaðýrmayý hatýrlamak, programcýya ek bir yük getirir.

Bu konuda yardýmcý olmasý için, C++, std::exit() aracýlýðýyla program sonlandýrýldýðýnda otomatik olarak çaðrýlacak bir iþlevi belirtmenizi saðlayan std::atexit() 
iþlevini sunar.

Bir örnek:
                        #include <cstdlib> // std::exit() için
                        #include <iostream>

                        void cleanup()
                        {
                            // burada herhangi bir temizleme iþlemi kodu
                            std::cout << "temizleme!\n";
                        }

                        int main()
                        {
                            // std::exit() çaðrýldýðýnda otomatik olarak cleanup() fonksiyonunu kaydet
                            std::atexit(cleanup); // not: þu an cleanup() fonksiyonunu çaðýrmýyoruz, bu nedenle cleanup yerine cleanup() kullanmýyoruz

                            std::cout << 1 << '\n';

                            std::exit(0); // programý sonlandýr ve iþletim sistemine durum kodu 0 döndür

                            // Aþaðýdaki ifadeler asla çalýþmaz
                            std::cout << 2 << '\n';

                            return 0;
                        }
bir önceki programla ayný çýktýyý verir: 
                                      1
                                      temizleme!

Neden bunu yapmak istersiniz? Bu size bir temizleme iþlevini belirleme þansý tanýr (muhtemelen main fonksiyonunda) ve ardýndan std::exit() fonksiyonunu açýkça 
çaðýrmadan önce bu iþlevi çaðýrmayý hatýrlamak zorunda kalmazsýnýz.

Ýþte std::atexit() ve cleanup fonksiyonu hakkýnda birkaç not: Ýlk olarak, main() sona erdiðinde std::exit() çaðrýldýðýndan, bu durumda programýn çýkýþ yapmasý 
std::atexit() tarafýndan kaydedilen iþlevleri çaðýrýr. Ýkinci olarak, kaydedilen iþlevin parametre almadýðýný ve geri dönüþ deðeri olmadýðýný belirtmelisiniz. 
Son olarak, std::atexit() kullanarak birden çok temizleme iþlevini kaydedebilirsiniz ve bunlar, kayýt sýrasýnýn tersine (en son kaydedilen ilk çaðrýlan) çaðrýlýr.


geliþmiþ okuyucular için :
    Çoklu iþ parçacýklý programlarda, `std::exit()` çaðýrmak programýnýzýn çökmesine neden olabilir (çünkü `std::exit()`'i çaðýran iþ parçacýðý, diðer iþ 
    parçacýklarý tarafýndan hâlâ eriþilebilecek olan statik nesneleri temizler). Bu nedenle, C++, `std::exit()` ve `std::atexit()` gibi benzer iþlevlere
    benzer þekilde çalýþan `std::quick_exit()` ve `std::at_quick_exit()` adlý baþka bir ikili fonksiyon çiftini tanýtmýþtýr. `std::quick_exit()`, programý
    normal bir þekilde sonlandýrýr, ancak statik nesneleri temizlemez ve baþka türden temizlik iþlemlerini yapabilir veya yapmayabilir. `std::at_quick_exit()`,
    `std::quick_exit()` ile sonlandýrýlan programlar için `std::atexit()`'in ayný rolünü yerine getirir.

std::abort ve std::terminate
----------------------------
C++ iki baþka durdurma ile ilgili fonksiyon içerir.

std::abort() fonksiyonu programýnýzýn anormal bir þekilde sonlanmasýna neden olur. Anormal sonlanma, programýn olaðandýþý bir çalýþma zamaný hatasý ile 
karþýlaþmasý ve programýn çalýþmaya devam edememesi anlamýna gelir. Örneðin, 0'a bölmeye çalýþmak bir anormal sonlanmaya neden olacaktýr. std::abort() 
herhangi bir temizlik iþlemi yapmaz.

                    #include <cstdlib> // for std::abort()
                    #include <iostream>

                    int main()
                    {
                        std::cout << 1 << '\n';
                        std::abort();

                        // Sonraki ifadeler asla çalýþtýrýlmaz.
                        std::cout << 2 << '\n';

                        return 0;
                    }

Bu bölümde (8.18 -- Assert ve static_assert) ilerleyen kýsýmlarda std::abort'un dolaylý olarak çaðrýldýðý durumlarý göreceðiz.

std::terminate() fonksiyonu genellikle exceptions ile birlikte kullanýlýr (exceptions daha sonraki bir bölümde ele alacaðýz). Her ne kadar std::terminate() 
açýkça çaðrýlabilecek olsa da, genellikle bir istisna iþlenmediðinde (ve birkaç baþka exceptions-related durumda) dolaylý olarak çaðrýlýr. 
Varsayýlan olarak, std::terminate() fonksiyonu std::abort() fonksiyonunu çaðýrýr.

Ne zaman halt kullanmalýyýz ? 
-----------------------------
Kýsa cevap  "neredeyse hiçbir zaman" olacaktýr. Yerel nesneleri imha etmek, C++'ýn önemli bir bölümünü oluþturur (özellikle sýnýflara geçtiðimizde), 
yukarýda bahsedilen fonksiyonlardan hiçbiri yerel deðiþkenleri temizlemez. Hata durumlarýyla baþa çýkmak için exceptions, daha iyi ve güvenli bir mekanizmadýr.

*** BEST -> Yalnýzca main fonksiyonundan normal bir þekilde dönmenin güvenli bir yolu yoksa halt kullanýn. Eðer exceptions larý devre dýþý býrakmadýysanýz,
            hatalarý güvenli bir þekilde iþlemek için exceptions tercih edin.






*/
