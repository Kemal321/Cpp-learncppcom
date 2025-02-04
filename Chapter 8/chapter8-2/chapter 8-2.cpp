#include <iostream>

int main()
{
    return 0;
}
/*
Break ve Continue
-----------------
Break

Switch ifadeleri bağlamında break ifadesini zaten gördünüz (8.5 -- Switch ifadesi temelleri), ancak bu ifade diğer kontrol akış ifadeleriyle de kullanılabilir,
bu nedenle daha detaylı bir açıklamayı hak ediyor. break ifadesi, bir while döngüsü, do-while döngüsü, for döngüsü veya switch ifadesini sonlandırır ve kırılan
döngü veya switch ifadesinden sonra gelen bir sonraki ifadeyle devam eder

Break ile switch kullanımı
-------------------------
Switch ifadesi bağlamında, bir break genellikle her durumun sonunda kullanılır ve bu durumun bittiğini belirtmek için kullanılır
(bu, ardışık durumlara geçişin önlenmesini sağlar):
                #include <iostream>

                void printMath(int x, int y, char ch)
                {
                    switch (ch)
                    {
                    case '+':
                        std::cout << x << " + " << y << " = " << x + y << '\n';
                        break; // ardışık durumlara geçme
                    case '-':
                        std::cout << x << " - " << y << " = " << x - y << '\n';
                        break; // ardışık durumlara geçme
                    case '*':
                        std::cout << x << " * " << y << " = " << x * y << '\n';
                        break; // ardışık durumlara geçme
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

Bir loop ile break in kullanımı
--------------------------------
Döngü bağlamında, bir `break` ifadesi döngüyü erken sonlandırmak için kullanılabilir. İşlem, döngünün sonundan sonraki ifadeyle devam eder.
                #include <iostream>

                int main()
                {
                    int sum{ 0 };

                    // Kullanıcıya 10'a kadar sayı girmesine izin ver
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        std::cout << "Eklemek için bir sayı girin veya çıkmak için 0 girin: ";
                        int num{};
                        std::cin >> num;

                        // Kullanıcı 0 girdiyse döngüden çık
                        if (num == 0)
                            break; // döngüden şimdi çık

                        // Aksi takdirde sayıyı toplamımıza ekleyin
                        sum += num;
                    }

                    // break'ten sonra işlem buradan devam edecek
                    std::cout << "Girdiğiniz tüm sayıların toplamı: " << sum << '\n';

                    return 0;
                }

Bu program, kullanıcının 10'a kadar sayı girmesine izin verir ve giriş yapılan tüm sayıların toplamını
sonunda görüntüler. Kullanıcı 0 girdiğinde, break, döngünün erken sona ermesine (10 sayı girilmeden önce) neden olur.
Çıktı : 
                Bir sayı eklemek için girin veya çıkmak için 0 girin: 5
                Bir sayı eklemek için girin veya çıkmak için 0 girin: 3
                Bir sayı eklemek için girin veya çıkmak için 0 girin: 8
                Bir sayı eklemek için girin veya çıkmak için 0 girin: 0
                Girdiğiniz tüm sayıların toplamı: 16

`break`, isteğe bağlı olarak sonsuz bir döngüden çıkmak için yaygın olarak kullanılan bir yöntemdir yukarıdaki işlemin aynısı bir if bloğu ile yapılabilir. 

Break vs return 
---------------
`Break` ve `return` ifadeleri arasındaki farkı anlamak yeni programcılar için bazen zor olabilir. Bir `break` ifadesi, switch veya döngüyü sonlandırır ve işlem,
switch veya döngünün ötesindeki ilk ifadeyle devam eder. Bir `return` ifadesi ise içinde bulunduğu fonksiyonu tamamen sonlandırır ve işlem, fonksiyonun çağrıldığı 
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
                                    break; // işlem, döngünün ötesindeki ilk ifadeyle devam edecektir

                                if (ch == 'r')
                                    return 1; // return, fonksiyonun hemen çağrıldığı yere (bu durumda main()) geri dönecektir
                            }

                            // döngüyü kırmak, işlemin buradan devam etmesine neden olur

                            std::cout << "Döngüden çıktık\n";

                            return 0;
                        }

                        int main()
                        {
                            int returnValue{ breakOrReturn() };
                            std::cout << "breakOrReturn fonksiyonu şunu döndürdü: " << returnValue << '\n';

                            return 0;
                        }

Bu programın iki çalıştırması:

                        'b' girmek için veya 'r' girmek için: r
                        breakOrReturn fonksiyonu 1 döndürdü

                        'b' girmek için veya 'r' girmek için: b
                        Döngüden çıktık
                        breakOrReturn fonksiyonu 0 döndürdü

`Continue` ifadesi
------------------
`continue` ifadesi, mevcut döngü iterasyonunu sonlandırmadan tüm döngüyü sonlandırmak için uygun bir yol sağlar.

İşte `continue` kullanımının bir örneği:

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // eğer sayı 4'e bölünebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue; // bir sonraki iterasyona git

                        // Eğer sayı 4'e bölünebiliyorsa, devam et
                        std::cout << count << '\n';

                        // continue ifadesi buraya atlar
                    }

                    return 0;
                }

Yani bu program 4 e bölünemeyen sayıları yazdırır
                    1
                    2
                    3
                    5
                    6
                    7
                    9
`continue` ifadesi, mevcut yürütme noktasını mevcut döngünün altına atarak çalışır.

Bir for-döngüsü durumunda, for-döngüsünün end ifadesi (yukarıdaki örnekte `++count`), continue'dan sonra hala çalışır (çünkü bu, döngü gövdesinin sonundan sonra 
gerçekleşir).

Dikkatli olun, bir continue ifadesini while veya do-while döngüleri ile kullanırken. Bu döngüler genellikle döngü gövdesi içinde kullanılan değişkenlerin değerini 
değiştirir. Eğer continue ifadesi, bu satırların atlanmasına neden oluyorsa, döngü sonsuz olabilir!

break ve continue kullanımı üzerine yapılan tartışma
----------------------------------------------------
Birçok kaynak, break ve continue ifadelerinin döngülerde kullanılmasından kaçınılması gerektiği konusunda okuyucuları uyarır, çünkü bu ifadeler, yürütme akışının
atlamasına neden olabilir ve mantık akışını takip etmeyi zorlaştırabilir. Örneğin, karmaşık bir mantık parçasında ortasında bir break, ya atlanabilir ya da ne 
koşullar altında tetiklenmesi gerektiği açık olmayabilir.

Ancak, dikkatli bir şekilde kullanıldığında, break ve continue, döngüleri daha okunabilir hale getirmeye yardımcı olabilir. Bu ifadeler, iç içe geçmiş blokların 
sayısını azaltarak ve karmaşık döngü mantığına duyulan ihtiyacı azaltarak, döngüleri daha anlaşılır hale getirebilir.
Örneğin: 
            #include <iostream>

            int main()
            {
                int count{ 0 }; // döngünün kaç kez tekrarlandığını say
                bool keepLooping { true }; // döngünün bitip bitmediğini kontrol eder
                while (keepLooping)
                {
                    std::cout << "Bu döngüden çıkmak için 'e' girin veya devam etmek için herhangi bir karakter girin: ";
                    char ch{};
                    std::cin >> ch;

                    if (ch == 'e')
                        keepLooping = false;
                    else
                    {
                        ++count;
                        std::cout << "Biz " << count << " kez tekrarladık\n";
                    }
                }

                return 0;
            }

Bu program, döngünün devam edip etmeyeceğini kontrol etmek için bir Boolean değişkeni ve kullanıcı çıkış yapmazsa yalnızca çalışan iç içe geçmiş bir blok kullanır.
Break kullanılarak oluşturulmuş haline bakalım bir de:
                    #include <iostream>

                    int main()
                    {
                        int count{ 0 }; // döngünün kaç kez tekrarlandığını say
                        while (true) // kullanıcı sonlandırana kadar döngüyü sürdür
                        {
                            std::cout << "Bu döngüden çıkmak için 'e' girin veya devam etmek için herhangi bir karakter girin: ";
                            char ch{};
                            std::cin >> ch;

                            if (ch == 'e')
                                break;

                            ++count;
                            std::cout << "Biz " << count << " kez tekrarladık\n";
                        }

                        return 0;
                    }

Bu versiyonda, tek bir break ifadesi kullanarak bir Boolean değişkenin kullanımını (ve amaçlanan kullanımının ne olduğunu ve nerede değerinin değiştiğini anlamanın
gerekliliğini), bir else ifadesini ve iç içe geçmiş bir bloku önledik.

continue ifadesi, bir koşul karşılandığında döngü iterasyonlarını atlamak için en etkili şekilde bir for-döngüsünün başında kullanılır. Bu, iç içe geçmiş bir bloku
önlememize olanak tanıyabilir.

                #include <iostream>

                int main()
                {
                    for (int count{ 0 }; count < 10; ++count)
                    {
                        // eğer sayı 4'e bölünmüyorsa...
                        if ((count % 4) != 0) // iç içe geçmiş blok
                        {
                                // Sayıyı yazdır
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
                        // eğer sayı 4'e bölünebiliyorsa, bu iterasyonu atla
                        if ((count % 4) == 0)
                            continue;

                        // iç içe geçmiş bir blok gerekli değil

                        std::cout << count << '\n';
                    }

                    return 0;
                }

Değişkenlerin sayısını en aza indirme ve iç içe geçmiş blokların sayısını azaltma, kodun anlaşılırlığını artırırken, bir break veya continue kullanmanın 
bu anlaşılırlığı bozmasından daha etkilidir. Bu nedenle, break veya continue'nin ölçülü bir şekilde kullanılmasını kabul edilebilir buluyoruz.

*** BEST -> Loop mantığınızı basitleştirmek için break ve continue kullanın.

Early return ( break ve continue ye benzer bir durum du hatırlamak iyidir )
----------------------------------------------------------------------------
Erken dönüşlerin kullanımına dair benzer bir argüman da return ifadeleri için yapılabilir. Bir fonksiyon içindeki son ifade olmayan bir return ifadesine erken 
dönüş denir. Birçok programcı, erken dönüşlerden kaçınılması gerektiğine inanır. Fonksiyonu sadece bir return ifadesi olan ve bu ifadenin fonksiyonun altında
bulunduğu bir yapı, basitlik taşır - fonksiyonun argümanları alacağını, uyguladığı mantığı gerçekleştireceğini ve sapma olmadan bir sonuç döndüreceğinizi 
varsayabilirsiniz. Ekstra dönüş ifadeleri, mantığı karmaşıklaştırır.

Karşı argüman ise erken dönüşlerin fonksiyonunuzu hemen bitirmesine olanak tanıdığını, bu sayede gereksiz mantık okuma ve koşullu iç içe geçmiş blokları en aza 
indirdiğini ve kodunuzu daha okunabilir hale getirdiğini savunur.

Bazı geliştiriciler orta bir yol izler ve erken dönüşleri yalnızca fonksiyonun başında parametre doğrulama (geçersiz argümanların yakalanması) için kullanır, 
ardından tek bir dönüş ifadesi kullanır.

Bizim duruşumuz erken dönüşlerin daha çok yardımcı olduğu yönündedir, ancak bunun pratiğinde bir miktar sanat olduğunu kabul ediyoruz.

*** BEST -> Erken dönüşler, fonksiyonunuzun mantığını basitleştiriyorsa kullanın.

                                                        8.12 Halts (Programınızı Erken Sonlandırma)
                                                        -------------------------------------------

Bu bölümde ele alacağımız akış kontrol ifadesi kategorisi, "halt"tir. Bir "halt", programı sonlandıran bir akış kontrol ifadesidir. C++'da, "halt"lar fonksiyonlar 
olarak uygulanır (anahtar kelimeler olarak değil), bu nedenle "halt" ifadelerimiz fonksiyon çağrıları olacaktır.

Kısaca, bir program normal olarak sona erdiğinde neler olduğunu özetleyelim. main() fonksiyonu döndüğünde (fonksiyonun sonuna ulaşarak veya bir return ifadesi 
aracılığıyla), bir dizi farklı şey gerçekleşir.

İlk olarak, fonksiyondan çıkıldığı için tüm yerel değişkenler ve fonksiyon parametreleri (normalde olduğu gibi) yok edilir.

Sonrasında, main() fonksiyonundan dönen değer (durum kodu) ile std::exit() adlı özel bir fonksiyon çağrılır. 

std::exit() nedir ?
-------------------
std::exit() işlevi, programın normal bir şekilde sona ermesine neden olan bir fonksiyondur. Normal sonlanma, programın beklenen bir şekilde sonlandığı anlamına
gelir. Normal sonlanma terimi, programın başarılı olup olmadığı konusunda bir şey ifade etmez (bu, durum kodu içindir). Örneğin, kullanıcının işlem yapmak için
bir dosya adı yazmasını beklediğiniz bir program yazıyorsanız, eğer kullanıcı geçerli olmayan bir dosya adı yazarsa, programınız muhtemelen başarısızlık durumunu
göstermek için bir sıfır olmayan durum kodu döndürecektir, ancak hala normal bir sona erme olacaktır.

std::exit(), bir dizi temizlik işlevini gerçekleştirir. İlk olarak, statik depolama süresine sahip nesneler yok edilir. Ardından, eğer dosyalar kullanıldıysa,,
başka bazı dosya temizliği yapılır. Son olarak, kontrol, std::exit() 'e iletilen argüman olarak kullanılan durum koduyla birlikte işletim sistemine geri döner.


std::exit i açıkça kullanma
---------------------------
std::exit() fonksiyonu, main() fonksiyonu sona erdiğinde dolaylı olarak çağrılsa da, std::exit() ayrıca programın normal olarak sona ermeden önce programı
durdurmak için açıkça çağrılabilir. Bu şekilde std::exit() çağrıldığında, cstdlib başlık dosyasını içermelisiniz.

İşte std::exit() 'i açıkça kullanmanın bir örneği:
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

                                                    std::exit(0); // programı sonlandır ve işletim sistemine durum kodu 0 döndür

                                                    // Aşağıdaki ifadeler hiçbir zaman çalıştırılmaz
                                                    std::cout << 2 << '\n';

                                                    return 0;
                                                }


bu program şu çıktıyı verir :
                                                        1
                                                        cleanup!

Unutmayın ki, std::exit() çağrısından sonra gelen ifadeler çalıştırılmaz çünkü program zaten sona ermiştir.

Yukarıdaki programda std::exit()'i main() fonksiyonundan çağırıyor olsak da, std::exit() herhangi bir fonksiyondan çağrılabilir ve programı o noktada sonlandırabilir.
std::exit()'i açıkça çağırma konusunda önemli bir not: std::exit(), herhangi bir yerel değişkeni (hem mevcut fonksiyonda hem de çağrı yığınındaki diğer fonksiyonlarda)
temizlemez. Bu nedenle, genellikle std::exit() çağrısından kaçınılması daha iyidir.

*** UYARI -> std::exit() fonksiyonu, mevcut fonksiyondaki veya çağrı yığınındaki diğer fonksiyonlardaki yerel değişkenleri temizlemez.

std::atexit()
-------------
Çünkü std::exit(), programı hemen sonlandırır, sonlandırmadan önce manuel olarak bazı temizleme işlemleri yapmak isteyebilirsiniz. Bu bağlamda, temizleme,
veritabanı veya ağ bağlantılarını kapatma, ayrılmış belleği serbest bırakma, bir günlüğe bilgi yazma vb. gibi işleri içerir...

Yukarıdaki örnekte, temizleme görevlerimizi ele almak için cleanup() fonksiyonunu çağırdık. Ancak, her exit() çağrısından önce manuel olarak bir temizleme 
fonksiyonunu çağırmayı hatırlamak, programcıya ek bir yük getirir.

Bu konuda yardımcı olması için, C++, std::exit() aracılığıyla program sonlandırıldığında otomatik olarak çağrılacak bir işlevi belirtmenizi sağlayan std::atexit() 
işlevini sunar.

Bir örnek:
                        #include <cstdlib> // std::exit() için
                        #include <iostream>

                        void cleanup()
                        {
                            // burada herhangi bir temizleme işlemi kodu
                            std::cout << "temizleme!\n";
                        }

                        int main()
                        {
                            // std::exit() çağrıldığında otomatik olarak cleanup() fonksiyonunu kaydet
                            std::atexit(cleanup); // not: şu an cleanup() fonksiyonunu çağırmıyoruz, bu nedenle cleanup yerine cleanup() kullanmıyoruz

                            std::cout << 1 << '\n';

                            std::exit(0); // programı sonlandır ve işletim sistemine durum kodu 0 döndür

                            // Aşağıdaki ifadeler asla çalışmaz
                            std::cout << 2 << '\n';

                            return 0;
                        }
bir önceki programla aynı çıktıyı verir: 
                                      1
                                      temizleme!

Neden bunu yapmak istersiniz? Bu size bir temizleme işlevini belirleme şansı tanır (muhtemelen main fonksiyonunda) ve ardından std::exit() fonksiyonunu açıkça 
çağırmadan önce bu işlevi çağırmayı hatırlamak zorunda kalmazsınız.

İşte std::atexit() ve cleanup fonksiyonu hakkında birkaç not: İlk olarak, main() sona erdiğinde std::exit() çağrıldığından, bu durumda programın çıkış yapması 
std::atexit() tarafından kaydedilen işlevleri çağırır. İkinci olarak, kaydedilen işlevin parametre almadığını ve geri dönüş değeri olmadığını belirtmelisiniz. 
Son olarak, std::atexit() kullanarak birden çok temizleme işlevini kaydedebilirsiniz ve bunlar, kayıt sırasının tersine (en son kaydedilen ilk çağrılan) çağrılır.

gelişmiş okuyucular için :
    Çoklu iş parçacıklı programlarda, `std::exit()` çağırmak programınızın çökmesine neden olabilir (çünkü `std::exit()`'i çağıran iş parçacığı, diğer iş 
    parçacıkları tarafından hâlâ erişilebilecek olan statik nesneleri temizler). Bu nedenle, C++, `std::exit()` ve `std::atexit()` gibi benzer işlevlere
    benzer şekilde çalışan `std::quick_exit()` ve `std::at_quick_exit()` adlı başka bir ikili fonksiyon çiftini tanıtmıştır. `std::quick_exit()`, programı
    normal bir şekilde sonlandırır, ancak statik nesneleri temizlemez ve başka türden temizlik işlemlerini yapabilir veya yapmayabilir. `std::at_quick_exit()`,
    `std::quick_exit()` ile sonlandırılan programlar için `std::atexit()`'in aynı rolünü yerine getirir.

std::abort ve std::terminate
----------------------------
C++ iki başka durdurma ile ilgili fonksiyon içerir.

std::abort() fonksiyonu programınızın anormal bir şekilde sonlanmasına neden olur. Anormal sonlanma, programın olağandışı bir çalışma zamanı hatası ile 
karşılaşması ve programın çalışmaya devam edememesi anlamına gelir. Örneğin, 0'a bölmeye çalışmak bir anormal sonlanmaya neden olacaktır. std::abort() 
herhangi bir temizlik işlemi yapmaz.

                    #include <cstdlib> // for std::abort()
                    #include <iostream>

                    int main()
                    {
                        std::cout << 1 << '\n';
                        std::abort();

                        // Sonraki ifadeler asla çalıştırılmaz.
                        std::cout << 2 << '\n';

                        return 0;
                    }

Bu bölümde (8.18 -- Assert ve static_assert) ilerleyen kısımlarda std::abort'un dolaylı olarak çağrıldığı durumları göreceğiz.

std::terminate() fonksiyonu genellikle exceptions ile birlikte kullanılır (exceptions daha sonraki bir bölümde ele alacağız). Her ne kadar std::terminate() 
açıkça çağrılabilecek olsa da, genellikle bir istisna işlenmediğinde (ve birkaç başka exceptions-related durumda) dolaylı olarak çağrılır. 
Varsayılan olarak, std::terminate() fonksiyonu std::abort() fonksiyonunu çağırır.

Ne zaman halt kullanmalıyız ? 
-----------------------------
Kısa cevap  "neredeyse hiçbir zaman" olacaktır. Yerel nesneleri imha etmek, C++'ın önemli bir bölümünü oluşturur (özellikle sınıflara geçtiğimizde), 
yukarıda bahsedilen fonksiyonlardan hiçbiri yerel değişkenleri temizlemez. Hata durumlarıyla başa çıkmak için exceptions, daha iyi ve güvenli bir mekanizmadır.

*** BEST -> Yalnızca main fonksiyonundan normal bir şekilde dönmenin güvenli bir yolu yoksa halt kullanın. Eğer exceptions ları devre dışı bırakmadıysanız,
            hataları güvenli bir şekilde işlemek için exceptions tercih edin.
*/
