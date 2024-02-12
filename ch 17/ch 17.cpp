#include <iostream>

int main()
{
    return 0;
}
/*
17.1 — std::array'a Giriþ
-------------------------
16.1 -- Konteynerlere ve dizilere giriþ dersinde, konteynerleri ve dizileri tanýttýk. Özetlemek gerekirse:

Konteynerler, isimsiz nesnelerin (elementler olarak adlandýrýlýr) bir koleksiyonu için depolama saðlar.
Diziler, elementlerini hafýzada ardýþýk olarak tahsis eder ve herhangi bir elemente alt dizinleme yoluyla hýzlý, doðrudan eriþim saðlar.
C++'da yaygýn olarak kullanýlan üç farklý dizi tipi vardýr: std::vector, std::array ve C tarzý diziler.
16.10 -- std::vector yeniden boyutlandýrma ve kapasite dersinde, dizilerin iki kategoriye ayrýldýðýný belirttik:

*- Sabit boyutlu diziler (ayný zamanda sabit uzunluklu diziler olarak da adlandýrýlýr), dizinin uzunluðunun örnekleme noktasýnda bilinmesini
   gerektirir ve bu uzunluk daha sonra deðiþtirilemez. C tarzý diziler ve std::array her ikisi de sabit boyutlu dizilerdir.
*- Dinamik diziler, çalýþma zamanýnda yeniden boyutlandýrýlabilir. std::vector bir dinamik dizidir.

Önceki bölümde, std::vector'a odaklandýk, çünkü hýzlý, nispeten kolay kullanýlýr ve çok yönlüdür. Bu, bir dizi konteynerine ihtiyaç duyduðumuzda 
baþvuracaðýmýz tipi yapar.

Peki neden her þey için dinamik dizileri kullanmýyoruz?
-------------------------------------------------------
Dinamik diziler güçlü ve kullanýþlýdýr, ancak hayattaki her þey gibi, sunduklarý faydalar için bazý ödünler verirler.

*- std::vector, sabit boyutlu dizilere göre biraz daha az performanslýdýr. Çoðu durumda farký muhtemelen fark etmeyeceksiniz 
   (aþýrý yeniden tahsislara neden olan düzensiz kod yazmadýðýnýz sürece).
*- std::vector, sadece çok sýnýrlý baðlamlarda constexpr'i destekler.
Modern C++'da, aslýnda bu son nokta önemlidir. Constexpr dizileri, daha saðlam kod yazma yeteneði sunar ve ayrýca derleyici tarafýndan daha yüksek
optimize edilebilir. Her zaman bir constexpr dizisi kullanabileceðimiz zaman, kullanmalýyýz -- ve eðer bir constexpr dizisine ihtiyacýmýz varsa,
kullanmamýz gereken konteyner sýnýfý std::array'dir.

*** BEST -> Constexpr diziler için std::array, non-constexpr diziler için std::vector kullanýn.

Bir std::array Tanýmlama
------------------------
std::array, <array> baþlýðýnda tanýmlanmýþtýr. std::vector'a benzer þekilde çalýþacak þekilde tasarlanmýþtýr ve göreceksiniz ki, ikisi arasýnda 
daha çok benzerlik vardýr.

Ýkisi arasýndaki farklardan biri, bir std::array nasýl bildirdiðimizdir:

                #include <array>  // for std::array
                #include <vector> // for std::vector

                int main()
                {
                    std::array<int, 5> a {};  // 5 int'lik bir std::array

                    std::vector<int> b(5);    // 5 int'lik bir std::vector (karþýlaþtýrma için)

                    return 0;
                }
std::array bildirimimizde iki þablon argümaný vardýr. Ýlki (int), dizi elemanýnýn tipini tanýmlayan bir tip þablon argümanýdýr. Ýkincisi (5),
dizi uzunluðunu tanýmlayan integral bir non-tip þablon argümanýdýr.

Bir std::array'ýn uzunluðu bir sabit ifade olmalýdýr
----------------------------------------------------
Bir std::vector'ün aksine, çalýþma zamanýnda yeniden boyutlandýrýlabilen, bir std::array'ýn uzunluðu bir sabit ifade olmalýdýr. Çoðunlukla,
uzunluk için saðlanan deðer bir tam sayý literali, constexpr deðiþkeni veya kapsamsýz bir numaralandýrýcý olacaktýr.

                #include <array>

                int main()
                {
                    std::array<int, 7> a {}; // Bir literel sabiti kullanarak

                    constexpr int len { 8 };
                    std::array<int, len> b {}; // Bir constexpr deðiþkeni kullanarak

                    enum Colors
                    {
                         red,
                         green,
                         blue,
                         max_colors
                    };

                    std::array<int, max_colors> c {}; // Bir numaralandýrýcý kullanarak

                #define DAYS_PER_WEEK 7
                    std::array<int, DAYS_PER_WEEK> d {}; // Bir makro kullanarak (bunu yapmayýn, yerine bir constexpr deðiþkeni kullanýn)

                    return 0;
                }
Not: Non-const deðiþkenler ve çalýþma zamaný sabitleri uzunluk için kullanýlamaz:
---------------------------------------------------------------------------------

                #include <array>
                #include <iostream>

                void foo(const int length) // length bir çalýþma zamaný sabitidir
                {
                    std::array<int, length> e {}; // hata: length bir sabit ifade deðil
                }

                int main()
                {
                    // non-const bir deðiþken kullanarak
                    int numStudents{};
                    std::cin >> numStudents; // numStudents non-constant

                    std::array<int, numStudents> {}; // hata: numStudents bir sabit ifade deðil

                    foo(7);

                    return 0;
                }

Bir std::array'ýn Toplu Baþlatýlmasý
------------------------------------
Belki de þaþýrtýcý bir þekilde, std::array bir topluluktur. Bu, hiçbir yapýcýya sahip olmadýðý ve bunun yerine toplu baþlatma kullanýlarak
baþlatýldýðý anlamýna gelir. Hýzlý bir özet olarak, toplu baþlatma, topluluklarýn üyelerini doðrudan baþlatmamýza izin verir. Bunu yapmak için,
bir baþlatýcý listesi saðlarýz, bu da virgülle ayrýlmýþ baþlatma deðerlerinin süslü parantezlerle çevrili listesidir.

                #include <array>

                int main()
                {
                    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // süslü liste kullanarak kopya-liste baþlatma
                    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // süslü liste kullanarak liste baþlatma (tercih edilen)

                    return 0;
                }
Bu baþlatma formlarýnýn her biri, dizi üyelerini sýrayla baþlatýr, 0. elemandan baþlar.

Bir std::array, bir baþlatýcý olmadan tanýmlanýrsa, elemanlar varsayýlan olarak baþlatýlýr. Çoðu durumda, bu, elemanlarýn baþlatýlmamýþ
býrakýlmasý sonucunu doðurur. Genellikle elemanlarýmýzýn baþlatýlmasýný istediðimiz için, std::array, baþlatýcý olmadan tanýmlandýðýnda deðer
baþlatýlmalýdýr (boþ süslü parantezler kullanarak).

                #include <array>
                #include <vector>

                int main()
                {
                    std::array<int, 5> a;   // Üyeler varsayýlan olarak baþlatýlýr (int elemanlar baþlatýlmamýþ býrakýlýr)
                    std::array<int, 5> b{}; // Üyeler deðer baþlatýlýr (int elemanlar sýfýr baþlatýlýr) (tercih edilen)

                    std::vector<int> v(5);  // Üyeler deðer baþlatýlýr (int elemanlar sýfýr baþlatýlýr) (karþýlaþtýrma için)

                    return 0;
                }

Bir baþlatýcý listesinde tanýmlanan dizi uzunluðundan daha fazla baþlatýcý saðlanýrsa, derleyici hata verecektir. Bir baþlatýcý listesinde 
tanýmlanan dizi uzunluðundan daha az baþlatýcý saðlanýrsa, baþlatýcý olmayan kalan elemanlar deðer baþlatýlýr:

                #include <array>

                int main()
                {
                    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // derleme hatasý: çok fazla baþlatýcý
                    std::array<int, 4> b { 1, 2 };          // arr[2] ve arr[3] deðer baþlatýlýr

                    return 0;
                }

Const ve constexpr std::array
-----------------------------
Bir std::array const olabilir:

                #include <array>

                int main()
                {
                    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

                    return 0;
                }

Bir const std::array'ýn elemanlarý açýkça const olarak iþaretlenmemiþ olsa bile, hala const olarak ele alýnýrlar (çünkü tüm dizi const).
std::array ayrýca constexpr için tam desteðe sahiptir:

                #include <array>

                int main()
                {
                    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

                    return 0;
                }
Bu constexpr desteði, std::array'ý kullanma ana nedenidir.
*** BEST -> std::array'ýnýzý mümkün olduðunda constexpr olarak tanýmlayýn. Eðer std::array'ýnýz constexpr deðilse, bunun yerine bir std::vector 
            kullanmayý düþünün.

C++17'de std::array için Sýnýf Þablon Argüman Çýkarýmý (CTAD)
-------------------------------------------------------------
C++17'deki CTAD (class template argument deduction) kullanarak, derleyicinin bir std::array'ýn hem eleman tipini hem de dizi uzunluðunu bir
baþlatýcý listesinden çýkarmasýný saðlayabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // Tip, std::array<int, 5> olarak çýkarýlýr
                    constexpr std::array a2 { 9.7, 7.31 };     // Tip, std::array<double, 2> olarak çýkarýlýr

                    return 0;
                }
Bu sözdizimini, pratik olduðunda tercih ederiz. Derleyiciniz C++17 uyumlu deðilse, tip ve uzunluk þablon argümanlarýný açýkça saðlamanýz
gerekecektir.

*** BEST -> Derleyicinin bir std::array'ýn tipini ve uzunluðunu baþlatýcýlarýndan çýkarmasýný saðlamak için sýnýf þablon argüman çýkarýmýný (CTAD)
            kullanýn.

C++, þablon parametrelerinin kýsmi atlanmasýný desteklemez (C++20 itibariyle), bu yüzden bir std::array'ýn sadece uzunluðunu veya sadece tipini
atlamak için çekirdek dil özelliði kullanmanýn bir yolu yoktur:

                #include <iostream>

                int main()
                {
                    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // hata: çok az þablon argümaný (uzunluk eksik)
                    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // hata: çok az þablon argümaný (tip eksik)

                    return 0;
                }

Sadece Dizi Uzunluðunu Atlayarak std::to_array Kullanma C++20
-------------------------------------------------------------
C++20'den itibaren, std::to_array yardýmcý fonksiyonunu kullanarak bir std::array'ýn dizi uzunluðunu atlamak mümkün olmuþtur:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Tipi ve boyutu belirt
                    constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };    // Sadece tipi belirt, boyutu çýkar
                    constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };         // Tipi ve boyutu çýkar

                    return 0;
                }
Ne yazýk ki, std::to_array kullanmak, bir std::array'ý doðrudan oluþturmaktan daha pahalýdýr, çünkü istenen std::array'ý kopya baþlatmak için
kullanýlan geçici bir std::array oluþturmayý içerir. Bu nedenle, std::to_array, tipin baþlatýcýlardan etkili bir þekilde belirlenemediði 
durumlarda kullanýlmalý ve bir dizi birçok kez oluþturulduðunda (ör. bir döngü içinde) kaçýnýlmalýdýr.

Operator[] Kullanarak Dizi Elemanlarýna Eriþim
----------------------------------------------
Bir std::vector gibi, bir std::array'ýn elemanlarýna eriþmenin en yaygýn yolu, alt dizin operatörünü (operator[]) kullanmaktýr:

                #include <array> // for std::array
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

                    std::cout << prime[3]; // indeksi 3 olan elemanýn deðerini yazdýr (7)
                    std::cout << prime[9]; // geçersiz indeks (tanýmsýz davranýþ)

                    return 0;
                }
Bir hatýrlatma olarak, operator[] sýnýrlarýn kontrolünü yapmaz. Geçersiz bir indeks saðlanýrsa, tanýmsýz davranýþ sonucu oluþur.
Bir std::array'a birkaç baþka þekilde indeksleme hakkýnda bir sonraki derste tartýþacaðýz.

17.2 — std::array uzunluðu ve indeksleme
----------------------------------------
16.3 dersinde -- std::vector ve unsigned uzunluk ve subscript problemi, standart kütüphane konteyner sýnýflarýnýn uzunluklar ve indeksler için
unsigned deðerler kullanma kararýný tartýþtýk. Çünkü std::array bir standart kütüphane konteyner sýnýfýdýr, ayný sorunlara tabidir.

Bu derste, bir std::array'ýn indeksini almanýn ve uzunluðunu almanýn yollarýný özetleyeceðiz. Çünkü std::vector ve std::array benzer arayüzlere
sahip olduðu için, bu, std::vector için ele aldýðýmýz þeyi paralel hale getirecektir. Ancak sadece std::array'ýn constexpr için tam desteði
olduðundan, biraz daha ona odaklanacaðýz.

Devam etmeden önce, “constexpr olmadýkça, iþaret dönüþümleri daraltýcý dönüþümlerdir” üzerinde hafýzanýzý tazelemek iyi bir zaman olabilir 

Bir std::array'ýn uzunluðu std::size_t tipindedir
-------------------------------------------------
std::array, þu þekilde görünen bir þablon struct olarak uygulanmýþtýr:

                template<typename T, std::size_t N> // N is a non-type template parameter
                struct array;

Gördüðünüz gibi, dizi uzunluðunu temsil eden non-type þablon parametresi (N) std::size_t tipindedir. Ve muhtemelen þimdiye kadar farkýndasýnýzdýr,
std::size_t büyük bir unsigned integral tipidir. Dolayýsýyla, bir std::array tanýmladýðýmýzda, uzunluk non-type þablon argümaný ya std::size_t
tipinde olmalýdýr, ya da std::size_t tipinde bir deðere dönüþtürülebilir olmalýdýr. Bu deðer constexpr olmalýdýr, bu yüzden bir signed integral 
deðer kullandýðýmýzda iþaret dönüþümü sorunlarýyla karþýlaþmayýz, çünkü derleyici, bir signed integral deðeri derleme zamanýnda std::size_t'ye
dönüþtürmeyi seve seve kabul eder ve bu daraltýcý bir dönüþüm olarak kabul edilmez.

Bir kenara NOT…
---------------
C++23'ten önce, C++'ýn bile std::size_t için bir literal soneki yoktu, çünkü genellikle constexpr bir std::size_t'ye ihtiyaç duyduðumuz durumlar 
için int'ten std::size_t'ye implicit derleme zamaný dönüþümü yeterli olur.

Sonek, esas olarak tip çýkarýmý amaçlarý için eklendi, çünkü constexpr auto x { 0 } size bir int yerine bir std::size_t verecektir.
Bu tür durumlarda, açýk bir static_cast kullanmak zorunda kalmadan 0 (int) ile 0UZ (std::size_t) arasýnda ayrým yapabilme yeteneði yararlýdýr.

std::array'ýn uzunluðu ve indeksleri size_type tipindedir, bu her zaman std::size_t'dir
---------------------------------------------------------------------------------------
Bir std::vector gibi, std::array de size_type adýnda bir iç içe geçmiþ typedef üyesi tanýmlar, bu da konteynerin uzunluðu 
(ve destekleniyorsa indeksler) için kullanýlan tip için bir takma addýr. std::array durumunda, size_type her zaman std::size_t için bir takma addýr

std::array'ýn uzunluðunu tanýmlayan non-type þablon parametresinin, size_type yerine açýkça std::size_t olarak tanýmlandýðýna dikkat edin. 
Bu, size_type'ýn std::array'ýn bir üyesi olduðu ve o noktada tanýmlanmadýðý içindir. Bu, std::size_t'yi açýkça kullanan tek yerdir -- 
her yerde baþka size_type kullanýlýr.

Bir std::array'ýn uzunluðunu almak
----------------------------------
Bir std::array nesnesinin uzunluðunu almanýn üç yaygýn yolu vardýr.

Ýlk olarak, size() üye fonksiyonunu kullanarak bir std::array nesnesinden uzunluðunu sorabiliriz (bu, uzunluðu unsigned size_type olarak döndürür):

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
                    std::cout << "uzunluk: " << arr.size() << '\n'; // uzunluðu `size_type` tipinde döndürür (alias for `std::size_t`)
                    return 0;
                }

                Bu, þunu yazdýrýr:

                uzunluk: 5
std::string ve std::string_view'in aksine, hem length() hem de size() üye fonksiyonuna sahipken (ayný iþi yapan), std::array (ve C++'daki diðer 
çoðu konteyner tipi) sadece size()'a sahiptir.

Ýkinci olarak, C++17'de, std::size() non-member fonksiyonunu kullanabiliriz (bu, std::array için sadece size() üye fonksiyonunu çaðýrýr,
böylece uzunluðu unsigned size_type olarak döndürür).

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr{ 9, 7, 5, 3, 1 };
                    std::cout << "uzunluk: " << std::size(arr); // C++17, uzunluðu `size_type` tipinde döndürür (alias for `std::size_t`)

                    return 0;
                }

Son olarak, C++20'de, uzunluðu büyük bir signed integral tip olarak döndüren std::ssize() non-member fonksiyonunu kullanabiliriz
(genellikle std::ptrdiff_t):

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array arr { 9, 7, 5, 3, 1 };
                    std::cout << "uzunluk: " << std::ssize(arr); // C++20, uzunluðu büyük bir signed integral tip olarak döndürür

                    return 0;
                }

Bu, uzunluðu signed tip olarak döndüren üç fonksiyondan sadece biridir.

Bir std::array'ýn uzunluðunu constexpr bir deðer olarak almak
-------------------------------------------------------------
Bir std::array'ýn uzunluðu constexpr olduðu için, yukarýdaki fonksiyonlarýn her biri bir std::array'ýn uzunluðunu constexpr bir deðer olarak 
döndürecektir (non-constexpr bir std::array nesnesi üzerinde çaðrýlsa bile)! Bu, bu fonksiyonlarýn herhangi birini sabit ifadelerde 
kullanabileceðimiz ve döndürülen uzunluðun daraltýcý bir dönüþüm olmadan bir int'e dönüþtürülebileceði anlamýna gelir:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array arr { 9, 7, 5, 3, 1 }; // not: bu örnekte constexpr deðil
                    constexpr int uzunluk{ std::size(arr) }; // tamam: dönüþ deðeri constexpr std::size_t ve int'e dönüþtürülebilir,
                                                             // daraltýcý bir dönüþüm deðil

                    std::cout << "uzunluk: " << uzunluk << '\n';

                    return 0;
                }

Visual Studio kullanýcýlarý için
--------------------------------
Visual Studio, yukarýdaki örnekte hatalý bir þekilde C4365 uyarýsýný tetikler. Sorun Microsoft'a bildirildi.

Uyarý

Bir dil hatasý nedeniyle, yukarýdaki fonksiyonlar, (const) referansla geçirilen bir std::array fonksiyon parametresi üzerinde çaðrýldýðýnda
non-constexpr bir deðer döndürecektir:

                #include <array>
                #include <iostream>

                void foo(const std::array<int, 5> &arr)
                {
                    constexpr int uzunluk{ std::size(arr) }; // derleme hatasý!
                    std::cout << "uzunluk: " << uzunluk << '\n';
                }

                int main()
                {
                    std::array arr { 9, 7, 5, 3, 1 };
                    constexpr int uzunluk{ std::size(arr) }; // tamam
                    std::cout << "uzunluk: " << uzunluk << '\n';

                    foo(arr);

                    return 0;
                }

Bu hata, P2280 ile C++23'te ele alýnmýþtýr. Yazma zamanýnda, az sayýda derleyici bu özelliði desteklemektedir.

Bir çözüm yolu, foo()'yu, dizi uzunluðunun bir non-type þablon parametresi olduðu bir fonksiyon þablonu yapmaktýr. Bu non-type þablon parametresi
daha sonra fonksiyonun içinde kullanýlabilir. Bunu, 17.3 dersinde -- std::array'ý geçmek ve döndürmek konusunda daha fazla tartýþýyoruz.

std::array'ý operator[] veya at() üye fonksiyonunu kullanarak subscripting
--------------------------------------------------------------------------
Önceki derste 17.1 -- std::array'a Giriþ, bir std::array'ý indekslemenin en yaygýn yolunun subscript operatörünü (operator[]) kullanmak olduðunu 
belirttik. Bu durumda hiçbir sýnýrlama kontrolü yapýlmaz ve geçersiz bir indeks geçirilirse tanýmsýz davranýþa neden olur.

std::vector gibi, std::array'ýn da çalýþma zamanýnda sýnýrlama kontrolü yapan bir at() üye fonksiyonu vardýr. Genellikle indeksleme öncesi 
sýnýrlama kontrolü yapmak veya derleme zamanýnda sýnýrlama kontrolü yapmak istediðimiz için bu fonksiyonun kullanýlmasýný önermiyoruz.
Bu iki fonksiyon da indeksin size_type (std::size_t) tipinde olmasýný bekler.

Bu fonksiyonlardan herhangi biri constexpr bir deðerle çaðrýlýrsa, derleyici bir constexpr dönüþümünü std::size_t'ye yapar. Bu, daraltýcý bir
dönüþüm olarak kabul edilmez, bu yüzden burada iþaret problemleriyle karþýlaþmazsýnýz. Ancak, bu fonksiyonlardan herhangi biri non-constexpr bir
signed integral deðerle çaðrýlýrsa, std::size_t'ye dönüþüm daraltýcý olarak kabul edilir ve derleyiciniz bir uyarý yayýnlayabilir. 

std::get() constexpr indeksler için derleme zamanýnda sýnýrlama kontrolü yapar
------------------------------------------------------------------------------
Bir std::array'ýn uzunluðu constexpr olduðu için, indeksimiz de bir constexpr deðeri ise, derleyicinin derleme zamanýnda constexpr indeksimizin 
dizinin sýnýrlarý içinde olduðunu doðrulayabileceðini ve constexpr indeksin sýnýrlarýn dýþýnda olduðu durumda derlemeyi durdurabileceðini
söyleyebiliriz. Ancak, operator[] taným gereði hiçbir sýnýrlama kontrolü yapmaz ve at() üye fonksiyonu sadece çalýþma zamanýnda sýnýrlama kontrolü 
yapar. Ve fonksiyon parametreleri constexpr olamaz (constexpr veya consteval fonksiyonlar bile), bu yüzden nasýl constexpr bir indeks geçeriz?

constexpr bir indeksimiz olduðunda derleme zamanýnda sýnýrlama kontrolü almak için, indeksi bir non-type þablon argümaný olarak alan std::get()
fonksiyon þablonunu kullanabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array prime{ 2, 3, 5, 7, 11 };

                    std::cout << std::get<3>(prime); // indeks 3 olan elemanýn deðerini yazdýr
                    std::cout << std::get<9>(prime); // geçersiz indeks (derleme hatasý)

                    return 0;
                }

std::get()'in uygulamasýnýn içinde, non-type þablon argümanýnýn dizi uzunluðundan daha küçük olduðunu kontrol eden bir static_assert vardýr. 
Þablon argümanlarý constexpr olmalýdýr, bu yüzden std::get() yalnýzca constexpr indekslerle çaðrýlabilir. Eðer deðilse, static_assert derleme 
sürecini derleme hatasýyla durdurur.


17.3 — std::array'ý geçmek ve döndürmek
---------------------------------------
std::array tipinde bir nesne, diðer herhangi bir nesne gibi bir fonksiyona geçirilebilir. Bu, bir std::array'ý deðer olarak geçirirsek,
pahalý bir kopya yapýlacaðý anlamýna gelir. Bu nedenle, genellikle bu tür kopyalarý önlemek için std::array'ý (const) referans olarak geçiririz.

Bir std::array ile hem eleman tipi hem de dizi uzunluðu nesnenin tip bilgilerinin bir parçasýdýr. Bu nedenle, bir std::array'ý bir fonksiyon 
parametresi olarak kullandýðýmýzda, hem eleman tipini hem de dizi uzunluðunu açýkça belirtmemiz gerekir:

                #include <array>
                #include <iostream>

                void passByRef(const std::array<int, 5>& arr) // burada <int, 5> belirtmeliyiz
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD tipi std::array<int, 5> olarak çýkarýr
                    passByRef(arr);

                    return 0;
                }

CTAD (þu anda) fonksiyon parametreleriyle çalýþmaz, bu yüzden burada sadece std::array belirtebiliriz ve derleyicinin þablon argümanlarýný 
çýkarmasýný bekleyemeziz. 

Farklý eleman tipleri veya uzunluklara sahip std::array'ý geçmek için fonksiyon þablonlarýný kullanma
-----------------------------------------------------------------------------------------------------
Her türlü eleman tipi veya herhangi bir uzunlukta std::array kabul edebilen bir fonksiyon yazmak için, std::array'ýmýzýn hem eleman tipini
hem de uzunluðunu parametrize eden bir fonksiyon þablonu oluþturabiliriz ve sonra C++ bu fonksiyon þablonunu kullanarak gerçek tipler ve
uzunluklarla gerçek fonksiyonlarý örneklendirecektir.

std::array þu þekilde tanýmlanmýþtýr:

                template<typename T, std::size_t N> // N is a non-type template parameter
                struct array;

Ayný þablon parametre bildirimini kullanan bir fonksiyon þablonu oluþturabiliriz:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N> // not: bu þablon parametre bildirimi std::array için olanla ayný
                void passByRef(const std::array<T, N>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'ý std::array<int, 5> çýkarmak için kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) örneðini oluþturacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'ý std::array<int, 6> çýkarmak için kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) örneðini oluþturacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'ý std::array<double, 5> çýkarmak için kullan
                    passByRef(arr3); // tamam: derleyici passByRef(const std::array<double, 5>& arr) örneðini oluþturacak

                    return 0;
                }

Yukarýdaki örnekte, std::array<T, N> tipinde bir parametreye sahip olan passByRef() adýnda tek bir fonksiyon þablonu oluþturduk. 
T ve N, önceki satýrdaki þablon parametre bildiriminde tanýmlanmýþtýr: template <typename T, std::size_t N>. T, çaðýranýn eleman tipini,
belirtmesine izin veren standart bir tip þablon parametresidir. N, çaðýranýn dizi uzunluðunu belirtmesine izin veren std::size_t 
tipinde bir non-type þablon parametresidir.

Uyarý

std::array için non-type þablon parametresinin tipinin std::size_t olmasý gerektiðine dikkat edin, int deðil! Bu, 
std::array'ýn template<class T, std::size_t N> struct array; olarak tanýmlanmýþ olmasýndandýr. Eðer non-type þablon parametresinin tipi olarak
int kullanýrsanýz, derleyici std::array<T, std::size_t> tipindeki argümaný std::array<T, int> tipindeki parametreyle eþleþtiremez (ve þablonlar
dönüþüm yapmaz).

Bu nedenle, main() içerisinden passByRef(arr) çaðrýsý yaptýðýmýzda (arr, std::array<int, 5> olarak tanýmlanmýþtýr), derleyici 
void passByRef(const std::array<int, 5>& arr) çaðrýsýný yapacak ve örneklendirecektir. Benzer bir süreç arr2 ve arr3 için de gerçekleþir.

Böylece, her türlü eleman tipi ve uzunluða sahip std::array argümanlarýný iþleyebilecek fonksiyonlarý örneklendirebilen tek bir fonksiyon þablonu
oluþturduk! Ýstenirse, iki þablon parametresinden sadece birini þablonlaþtýrmak da mümkündür. Aþaðýdaki örnekte, yalnýzca std::array'ýn uzunluðunu
parametrize ediyoruz, ancak eleman tipi açýkça int olarak tanýmlanmýþtýr:

                #include <array>
                #include <iostream>

                template <std::size_t N> // not: burada sadece uzunluk þablonlaþtýrýldý
                void passByRef(const std::array<int, N>& arr) // eleman tipini int olarak tanýmladýk
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'ý std::array<int, 5> çýkarmak için kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) örneðini oluþturacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'ý std::array<int, 6> çýkarmak için kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) örneðini oluþturacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'ý std::array<double, 5> çýkarmak için kullan
                    passByRef(arr3); // hata: derleyici eþleþen fonksiyonu bulamýyor

                    return 0;
                }

Auto non-type þablon parametreleri C++20
----------------------------------------
Kendi fonksiyon þablonlarýnýz için bir þablon parametre bildiriminde kullanabileceðiniz bir non-type þablon parametresinin tipini hatýrlamak 
(veya araþtýrmak) can sýkýcýdýr.

C++20'de, bir non-type þablon parametresinin argümandan tipini çýkarmasýný saðlamak için bir þablon parametre bildiriminde auto kullanabiliriz:

                #include <array>
                #include <iostream>

                template <typename T, auto N> // þimdi auto'yu N'nin tipini çýkarmak için kullanýyoruz
                void passByRef(const std::array<T, N>& arr)
                {
                    std::cout << arr[0] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD'ý std::array<int, 5> çýkarmak için kullan
                    passByRef(arr);  // tamam: derleyici passByRef(const std::array<int, 5>& arr) örneðini oluþturacak

                    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // CTAD'ý std::array<int, 6> çýkarmak için kullan
                    passByRef(arr2); // tamam: derleyici passByRef(const std::array<int, 6>& arr) örneðini oluþturacak

                    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // CTAD'ý std::array<double, 5> çýkarmak için kullan
                    passByRef(arr3); // tamam: derleyici passByRef(const std::array<double, 5>& arr) örneðini oluþturacak

                    return 0;
                }
Eðer derleyiciniz C++20 yetenekliyse, bunu kullanmakta bir sakýnca yoktur.

Dizi Uzunluðunda Static Assert Kullanma
---------------------------------------
Yukarýda sunulanlara benzer bir þablon fonksiyonu düþünün:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr);

                    return 0;
                }

printElement3() bu durumda iyi çalýþýrken, bu programda dikkatsiz bir programcýyý bekleyen potansiyel bir hata var. Gördünüz mü?

Yukarýdaki program, dizinin indeksi 3 olan elemanýnýn deðerini yazdýrýr. Bu, dizinin indeksi 3 olan geçerli bir elemaný olduðu sürece iyidir.
Ancak, derleyici, indeksi 3'ün sýnýrlarýn dýþýnda olduðu dizileri geçirmenize seve seve izin verecektir. Örneðin:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << arr[3] << '\n'; // geçersiz indeks
                }

                int main()
                {
                    std::array arr{ 9, 7 }; // 2 elemanlý bir dizi (geçerli indeksler 0 ve 1)
                    printElement3(arr);

                    return 0;
                }

Bu, tanýmsýz davranýþa yol açar. Ýdeal olarak, böyle bir þey yapmaya çalýþtýðýmýzda derleyicinin bizi uyarmasýný isteriz!

Þablon parametrelerinin fonksiyon parametrelerine göre bir avantajý, þablon parametrelerinin derleme zamaný sabitleri olmasýdýr. 
Bu, sabit ifadeler gerektiren yeteneklerden yararlanabileceðimiz anlamýna gelir.

Bu yüzden bir çözüm, std::get()'i kullanmaktýr (derleme zamanýnda sýnýrlama kontrolü yapar) operator[] yerine (sýnýrlama kontrolü yapmaz):

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    std::cout << std::get<3>(arr) << '\n'; // derleme zamanýnda indeks 3'ün geçerli olduðunu kontrol eder
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr); // tamam

                    std::array arr2{ 9, 7 };
                    printElement3(arr2); // derleme hatasý

                    return 0;
                }

Derleyici, printElement3(arr2) çaðrýsýna ulaþtýðýnda, printElement3(const std::array<int, 2>&) fonksiyonunu örneklendirir ve çaðýrýr.Bu fonksiyonun
gövdesindeki satýr std::get<3>(arr)'dir. Dizi parametresinin uzunluðu 2 olduðundan, bu geçersiz bir eriþimdir ve derleyici bir hata yayýnlar.

Alternatif bir çözüm, bir önkoþulu kendimiz doðrulamak için static_assert kullanmaktýr:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void printElement3(const std::array<T, N>& arr)
                {
                    // önkoþul: dizi uzunluðu 3'ten büyük olmalýdýr, böylece eleman 3 var olur
                    static_assert (N > 3);

                    // bu noktadan itibaren dizi uzunluðunun 3'ten büyük olduðunu varsayabiliriz

                    std::cout << arr[3] << '\n';
                }

                int main()
                {
                    std::array arr{ 9, 7, 5, 3, 1 };
                    printElement3(arr); // tamam

                    std::array arr2{ 9, 7 };
                    printElement3(arr2); // derleme hatasý

                    return 0;
                }

Derleyici, printElement3(arr2) çaðrýsýna ulaþtýðýnda, printElement3(const std::array<int, 2>&) fonksiyonunu örneklendirir ve çaðýrýr. Bu fonksiyonun
gövdesindeki satýr static_assert (N > 3)'tir. N þablon non-type parametresinin deðeri 2'dir ve 2 > 3 yanlýþtýr, bu yüzden derleyici bir hata
yayýnlar.

Ana Fikir

Yukarýdaki örnekte, neden static_assert (N > 3); yerine static_assert (std::size(arr) > 3) kullandýðýmýzý merak ediyor olabilirsiniz. Ýkincisi, 
önceki derste (17.2 -- std::array uzunluðu ve indeksleme) bahsedilen dil hatasý nedeniyle C++23'ten önce derlenmez.

Bir std::array'ý Döndürme
-------------------------
Sözdizimi bir yana, bir std::array'ý bir fonksiyona geçirmek kavramsal olarak basittir - (const) referans olarak geçirin. Ancak, bir std::array
döndürmesi gereken bir fonksiyonumuz varsa? Ýþler biraz daha karmaþýklaþýyor. std::vector'ün aksine, std::array taþýnabilir deðildir,
bu yüzden bir std::array'ý deðer olarak döndürmek, dizinin bir kopyasýný yapar. Dizinin içindeki elemanlar, taþýnabilirlerse taþýnýr,
aksi takdirde kopyalanýr.

Burada iki geleneksel seçenek vardýr ve hangisini seçeceðiniz duruma baðlýdýr.

Bir std::array'ý Deðer Olarak Döndürme
--------------------------------------
Aþaðýdakilerin tümü doðru olduðunda bir std:array'ý deðer olarak döndürmek tamam:

*- Dizi çok büyük deðil.
*- Eleman tipi kopyalamak ucuz (veya taþýnabilir).
*- Kod, performans açýsýndan hassas bir baðlamda kullanýlmýyor.
Bu tür durumlarda, std::array'ýn bir kopyasý yapýlýr, ancak yukarýdaki tüm durumlar doðruysa, performans kaybý küçük olacaktýr ve çaðýran kiþiye
veri döndürmenin en geleneksel yolunu sürdürmek en iyi seçenek olabilir.

                #include <array>
                #include <iostream>

                // deðer olarak döndür
                template <typename T, std::size_t N>
                std::array<T, N> inputArray() // deðer olarak döndür
                {
                    std::array<T, N> arr{};
                    std::size_t index { 0 };
                    while (index < N)
                    {
                        std::cout << "Enter value #" << index << ": ";
                        std::cin >> arr[index];

                        if (!std::cin) // hatalý giriþi iþle
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        ++index;
                    }

                    return arr;
                }

                int main()
                {
                    std::array<int, 5> arr { inputArray<int, 5>() };

                    std::cout << "Element 2'nin deðeri " << arr[2] << '\n';

                    return 0;
                }

Bu yöntem hakkýnda birkaç güzel þey var:

*- Çaðýran kiþiye veri döndürmenin en geleneksel yolunu kullanýr.
*- Fonksiyonun bir deðer döndürdüðü açýktýr.
*- Bir dizi tanýmlayabilir ve onu tek bir ifadeyle baþlatabiliriz.
Ayrýca birkaç dezavantajý da var:

*- Fonksiyon, dizinin ve tüm elemanlarýnýn bir kopyasýný döndürür, bu ucuz deðildir.
*- Fonksiyonu çaðýrdýðýmýzda, parametrelerden çýkarýlamayan þablon argümanlarýný açýkça belirtmemiz gerekir.

Bir std::array'ý Bir Out Parametresi Aracýlýðýyla Döndürme
----------------------------------------------------------
Deðer olarak döndürme çok pahalýysa, bunun yerine bir out-parametresi kullanabiliriz. Bu durumda, çaðýran kiþi, std::array'ý non-const referans
olarak (veya adres olarak) geçirmekten sorumludur ve fonksiyon daha sonra bu diziyi deðiþtirebilir.

                #include <array>
                #include <iostream>

                template <typename T, std::size_t N>
                void inputArray(std::array<T, N>& arr) // non-const referans olarak geçir
                {
                    std::size_t index { 0 };
                    while (index < N)
                    {
                        std::cout << "Enter value #" << index << ": ";
                        std::cin >> arr[index];

                        if (!std::cin) // hatalý giriþi iþle
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            continue;
                        }
                        ++index;
                    }

                }

                int main()
                {
                    std::array<int, 5> arr {};
                    inputArray(arr);

                    std::cout << "Element 2'nin deðeri " << arr[2] << '\n';

                    return 0;
                }

Bu yöntemin birincil avantajý, dizinin hiçbir zaman kopyalanmamasýdýr, bu yüzden bu verimlidir.

Ayrýca birkaç dezavantajý da var:

*- Bu veri döndürme yöntemi geleneksel deðildir ve fonksiyonun argümaný deðiþtirdiði kolayca anlaþýlamaz.
*- Bu yöntemi yalnýzca dizinin deðerlerini atamak için kullanabiliriz, onu baþlatamayýz.
*- Böyle bir fonksiyon, geçici nesneler üretmek için kullanýlamaz.

Bir std::vector Döndürme
------------------------
std::vector taþýnabilir ve pahalý kopyalar yapmadan deðer olarak döndürülebilir. Bir std::array'ý deðer olarak döndürüyorsanýz, std::array'ýnýz ,
muhtemelen constexpr deðildir ve std::vector kullanmayý (ve döndürmeyi) düþünmelisiniz. Bir std::array, yalnýzca temel türlerin elemanlarýyla
sýnýrlý deðildir. Daha ziyade, bir std::array'ýn elemanlarý, bileþik türler de dahil olmak üzere herhangi bir nesne türü olabilir. Bu,
bir std::array'ý iþaretçilerle veya bir std::array'ý structlarla (veya sýnýflarla) oluþturabileceðiniz anlamýna gelir.

Ancak, bir std::array'ý structlar veya sýnýflarla baþlatmak genellikle yeni programcýlarý zorlar, bu yüzden bu konuyu açýkça ele alacaðýz.

Yazarýn notu -> Bu derste noktalarýmýzý örneklendirmek için yapýlarý kullanacaðýz. Materyal sýnýflar için de eþit derecede geçerlidir.

Bir std::array'ý structlarla tanýmlama ve atama
-----------------------------------------------
Basit bir yapýyla baþlayalým:

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };
Bir std::array'ý House tanýmlamak ve elemanlarý atamak beklediðiniz gibi çalýþýr:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    std::array<House, 3> houses{};

                    houses[0] = { 13, 1, 7 };
                    houses[1] = { 14, 2, 5 };
                    houses[2] = { 15, 2, 4 };

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                                  << " has " << (house.stories * house.roomsPerStory)
                                  << " rooms.\n";
                    }

                    return 0;
                }

                Yukarýdaki, aþaðýdakileri çýktýlar:

                House number 13 has 7 rooms.
                House number 14 has 10 rooms.
                House number 15 has 8 rooms.
Bir std::array'ý structlarla baþlatma
-------------------------------------
Bir dizi yapýlarý baþlatmak da, eleman türünü açýkça belirttiðiniz sürece beklediðiniz gibi çalýþýr:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    constexpr std::array houses { // CTAD'ý þablon argümanlarý <House, 3> çýkarmak için kullan
                            House{ 13, 1, 7 },
                            House{ 14, 2, 5 },
                            House{ 15, 2, 4 }
                        };

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                            << " has " << (house.stories * house.roomsPerStory)
                            << " rooms.\n";
                    }

                    return 0;
                }

Yukarýdaki örnekte, std::array'ýn tipini std::array<House, 3> olarak çýkarmak için CTAD'ý kullanýyoruz. Daha sonra, 3 House nesnesini baþlatýcýlar
olarak saðlýyoruz, bu da gayet iyi çalýþýyor.

Her baþlatýcý için eleman türünü açýkça belirtmeden baþlatma
------------------------------------------------------------
Yukarýdaki örnekte, her baþlatýcýnýn eleman türünü listelememiz gerektiðini not edeceksiniz:

                constexpr std::array houses {
                        House{ 13, 1, 7 }, // burada House belirtiyoruz
                        House{ 14, 2, 5 }, // ve burada
                        House{ 15, 2, 4 }  // ve burada
                    };
Ama atama durumunda aynýsýný yapmak zorunda kalmadýk:

                // Derleyici, houses'ýn her elemanýnýn bir House olduðunu biliyor
                // bu yüzden her atamanýn sað tarafýný bir House'a otomatik olarak dönüþtürür
                houses[0] = { 13, 1, 7 };
                houses[1] = { 14, 2, 5 };
                houses[2] = { 15, 2, 4 };

Bu yüzden þunu denemeyi düþünebilirsiniz:


                // çalýþmaz
                constexpr std::array<House, 3> houses { // derleyiciye her elemanýn bir House olduðunu söylüyoruz
                        { 13, 1, 7 }, // ama burada belirtmiyoruz
                        { 14, 2, 5 },
                        { 15, 2, 4 }
                    };
Belki de þaþýrtýcý bir þekilde, bu çalýþmaz. Nedenini inceleyelim.
Bir std::array, uygulama tarafýndan tanýmlanan adý olan tek bir C tarzý dizi üyesi içeren bir yapý olarak tanýmlanýr:

                template<typename T, std::size_t N>
                struct array
                {
                    T implementation_defined_name[N]; // N elemanlý tip T olan bir C tarzý dizi
                }

Yazarýn notu

Henüz C tarzý dizileri ele almadýk, ancak bu dersin amacý için, T implementation_defined_name[N];'in T tipinde N elemanlý sabit boyutlu bir dizi
olduðunu (týpký std::array<T, N> implementation_defined_name; gibi) bilmelisiniz.

C tarzý dizileri yaklaþan 17.7 dersinde -- C tarzý dizilere giriþ konusunda ele alýyoruz.

Yukarýdaki gibi evleri baþlatmaya çalýþtýðýmýzda, derleyici baþlatmayý þu þekilde yorumlar:

                // Çalýþmaz
                constexpr std::array<House, 3> houses { // evler için baþlatýcý
                    { 13, 1, 7 }, // C tarzý dizi üyesi için baþlatýcý implementation_defined_name
                    { 14, 2, 5 }, // ?
                    { 15, 2, 4 }  // ?
                };

Derleyici, { 13, 1, 7 }'yi evlerin ilk üyesi için baþlatýcý olarak yorumlar, bu da uygulama tarafýndan tanýmlanan adý olan C tarzý dizidir. 
Bu, C tarzý dizi elemaný 0'ý { 13, 1, 7 } ile baþlatýr ve geri kalan üyeler sýfýr baþlatýlýr. Sonra derleyici, iki baþlatma deðeri daha 
saðladýðýmýzý ({ 14, 2, 7 } ve { 15, 2, 5 }) keþfeder ve çok fazla baþlatma deðeri saðladýðýmýzý belirten bir derleme hatasý oluþturur.

Yukarýdakini doðru bir þekilde baþlatmanýn yolu, ek bir set süslü parantez eklemektir:

                // Bu beklenildiði gibi çalýþýr
                constexpr std::array<House, 3> houses { // evler için baþlatýcý
                    { // C tarzý dizi üyesini baþlatmak için ekstra bir set süslü parantez
                        { 13, 4, 30 }, // dizi elemaný 0 için baþlatýcý
                        { 14, 3, 10 }, // dizi elemaný 1 için baþlatýcý
                        { 15, 3, 40 }, // dizi elemaný 2 için baþlatýcý
                     }
                };

Gerekli olan ek süslü parantez setine dikkat edin (std::array yapý içindeki C tarzý dizi üyesinin baþlatýlmasýný baþlatmak için). 
Bu süslü parantezlerin içinde, daha sonra her bir elemaný kendi süslü parantezlerinin içinde baþlatabiliriz.

Bu, eleman türü bir deðer listesi gerektirdiðinde ve baþlatýcýlarýn bir parçasý olarak eleman türünü açýkça saðlamadýðýmýzda std::array 
baþlatýcýlarýna ek bir süslü parantez seti göreceðiniz neden budur.

Ana Fikir

Bir std::array'ý bir yapý, sýnýf veya dizi ile baþlatýrken ve her baþlatýcýyla eleman türünü saðlamýyorsanýz, derleyicinin neyi baþlatacaðýný
doðru bir þekilde yorumlamasý için ek bir süslü parantez çiftine ihtiyacýnýz olacaktýr.

Bu, toplu baþlatmanýn bir özelliðidir ve diðer standart kütüphane konteyner türleri (liste yapýlandýrýcýlarý kullananlar) bu durumlarda çift süslü 
parantez gerektirmez.

Ýþte tam bir örnek:

                #include <array>
                #include <iostream>

                struct House
                {
                    int number{};
                    int stories{};
                    int roomsPerStory{};
                };

                int main()
                {
                    constexpr std::array<House, 3> houses {{ // çift süslü parantezlere dikkat edin
                        { 13, 1, 7 },
                        { 14, 2, 5 },
                        { 15, 2, 4 }
                    }};

                    for (const auto& house : houses)
                    {
                        std::cout << "House number " << house.number
                                  << " has " << (house.stories * house.roomsPerStory)
                                  << " rooms.\n";
                    }

                    return 0;
                }

Topluluklar için Süslü Parantez Elizyonu
----------------------------------------
Yukarýdaki açýklamayý göz önünde bulundurarak, yukarýdaki durumun neden çift süslü parantez gerektirdiðini, ancak gördüðümüz tüm diðer durumlarýn 
yalnýzca tek süslü parantez gerektirdiðini merak ediyor olabilirsiniz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // tek süslü parantezler

                    for (const auto n : arr)
                        std::cout << n << '\n';

                    return 0;
                }
Ortaya çýktýðýna göre, bu tür diziler için çift süslü parantez saðlayabilirsiniz:

                #include <array>
                #include <iostream>

                int main()
                {
                    constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // çift süslü parantezler

                    for (const auto n : arr)
                        std::cout << n << '\n';

                    return 0;
                }

Ancak, C++'daki topluluklar, birden çok süslü parantezin ne zaman atlanabileceðine dair bazý kurallar koyan bir kavram olan süslü parantez
elizyonunu destekler. Genellikle, bir std::array'ý skalar (tek) deðerlerle baþlatýrken veya türün her elemanla açýkça adlandýrýldýðý sýnýf türleri
veya dizilerle baþlatýrken süslü parantezleri atlayabilirsiniz.

Bir std::array'ý her zaman çift süslü parantezlerle baþlatmada bir sakýnca yoktur, çünkü bu, süslü parantez elizyonunun belirli bir durumda
uygulanabilir olup olmadýðýný düþünmek zorunda kalmamýzý önler. Alternatif olarak, tek süslü parantezle baþlatmayý deneyebilir ve derleyici
genellikle bunu çözemediyse þikayet eder. Bu durumda, hýzlýca ek bir süslü parantez seti ekleyebilirsiniz.

Ýþte bir örnek daha, burada bir std::array'ý Student structlarý ile baþlatýyoruz.

                #include <array>
                #include <iostream>
                #include <string_view>

                // Her öðrencinin bir kimliði ve bir adý vardýr
                struct Student
                {
                    int id{};
                    std::string_view name{};
                };

                // 3 öðrencimizin dizisi (her baþlatýcýda Student'ý belirttiðimiz için tekli süslü)
                constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

                const Student* findStudentById(int id)
                {
                    // Tüm öðrencilere bak
                    for (auto& s : students)
                    {
                        // Eþleþen kimliði olan öðrenciyi döndür
                        if (s.id == id) return &s;
                    }

                    // Eþleþen kimlik bulunamadý
                    return nullptr;
                }

                int main()
                {
                    constexpr std::string_view nobody { "nobody" };

                    const Student* s1 { findStudentById(1) };
                    std::cout << "Bulduðunuz: " << (s1 ? s1->name : nobody) << '\n';

                    const Student* s2 { findStudentById(3) };
                    std::cout << "Bulduðunuz: " << (s2 ? s2->name : nobody) << '\n';

                    return 0;
                }

                Bu, aþaðýdakileri yazdýrýr:

                Bulduðunuz: Joe
                Bulduðunuz: nobody
Not: std::array students constexpr olduðu için, findStudentById() fonksiyonumuz bir const pointer döndürmelidir, bu da main() içindeki Student 
pointerlarýnýn da const olmasý gerektiði anlamýna gelir.

17.5 — std::reference_wrapper aracýlýðýyla referans dizileri
------------------------------------------------------------
Önceki derste, dizilerin herhangi bir nesne türünün öðelerine sahip olabileceðini belirttik. Bu, temel türlerdeki (ör. int) nesneleri ve bileþik
türlerdeki (ör. int'e iþaretçi) nesneleri içerir.

                #include <array>
                #include <iostream>
                #include <vector>

                int main()
                {
                    int x { 1 };
                    int y { 2 };

                    [[maybe_unused]] std::array valarr { x, y };   // int deðerlerinin bir dizisi
                    [[maybe_unused]] std::vector ptrarr { &x, &y }; // int iþaretçilerinin bir vektörü

                    return 0;
                }
Ancak, referanslar nesne olmadýðý için, bir referans dizisi oluþturamazsýnýz. Bir dizinin öðeleri de atanabilir olmalýdýr ve referanslar yeniden
oturtulamaz.

                #include <array>
                #include <iostream>

                int main()
                {
                    int x { 1 };
                    int y { 2 };

                    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // derleme hatasý: referanslarýn bir dizisini tanýmlayamaz

                    int& ref1 { x };
                    int& ref2 { y };
                    [[maybe_unused]] std::array valarr { ref1, ref2 }; // tamam: bu aslýnda bir std::array<int, 2>, bir referans dizisi deðil

                    return 0;
                }

Bu derste, örneklerde std::array kullanacaðýz, ancak bu tüm dizi türlerine eþit derecede uygulanabilir.
Ancak, bir referans dizisi istiyorsanýz, bir çözüm yolu vardýr.

std::reference_wrapper
----------------------
std::reference_wrapper, <functional> baþlýðýnda yaþayan bir standart kütüphane sýnýf þablonudur. Bir T tür þablon argümaný alýr ve sonra T'ye 
modifiye edilebilir bir lvalue referansý gibi davranýr.

std::reference_wrapper hakkýnda birkaç þeyi not etmekte fayda var:

*- Operator= bir std::reference_wrapper'ý yeniden oturtur (referans verilen nesneyi deðiþtirir).
*- std::reference_wrapper<T> T&'a doðrudan dönüþtürülür.
*- get() üye fonksiyonu bir T& almak için kullanýlabilir. Bu, referans verilen nesnenin deðerini güncellemek istediðimizde yararlýdýr.
Ýþte basit bir örnek:

                #include <array>
                #include <functional> // std::reference_wrapper için
                #include <iostream>

                int main()
                {
                    int x { 1 };
                    int y { 2 };
                    int z { 3 };

                    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };

                    arr[1].get() = 5; // dizinin 1. öðesindeki nesneyi deðiþtir

                    std::cout << arr[1] << y << '\n'; // arr[1] ve y'nin deðiþtirildiðini gösterir, 55 yazdýrýr

                    return 0;
                }

                Bu örnek aþaðýdakileri yazdýrýr:

                55
arr[1].get() = 5 kullanmamýz ve arr[1] = 5 kullanmamamýz gerektiðini unutmayýn. Ýkincisi belirsizdir, çünkü derleyici,
std::reference_wrapper<int>'i deðer 5'e yeniden oturtmayý mý (zaten yasadýþý olan bir þey) yoksa referans verilen deðeri deðiþtirmeyi mi 
amaçladýðýmýzý anlayamaz. get() kullanmak bunu belirsizleþtirir.

arr[1]'i yazdýrýrken, derleyici bir std::reference_wrapper<int>'i yazdýramayacaðýný anlar, bu yüzden onu bir int&'ye dönüþtürür, 
ki bu yazdýrýlabilir. Yani burada get() kullanmamýza gerek yok.

std::ref ve std::cref
---------------------
C++17'den önce, CTAD (sýnýf þablonu argüman çýkarýmý) mevcut deðildi, bu yüzden bir sýnýf türü için tüm þablon argümanlarý açýkça listelenmeliydi.
Bu nedenle, bir std::reference_wrapper<int> oluþturmak için bunlardan birini yapabilirdiniz:

                int x { 5 };

                std::reference_wrapper<int> ref1 { x };        // C++11
                auto ref2 { std::reference_wrapper<int>{ x }}; // C++11

Uzun isim ve þablon argümanlarýný açýkça listeleme zorunluluðu nedeniyle, birçok referans wrapper oluþturmak zor olabilirdi.
Ýþleri kolaylaþtýrmak için, std::ref() ve std::cref() fonksiyonlarý, std::reference_wrapper ve const std::reference_wrapper nesnelerini oluþturmak
için kýsayollar olarak saðlandý. Bu fonksiyonlarýn þablon argümanýný açýkça belirtmek zorunda kalmadan auto ile kullanýlabileceðini unutmayýn.

                int x { 5 };
                auto ref { std::ref(x) };   // C++11, std::reference_wrapper<int> olarak çýkarýr
                auto cref { std::cref(x) }; // C++11, std::reference_wrapper<const int> olarak çýkarýr

Tabii ki, þimdi C++17'de CTAD'ye sahip olduðumuza göre, bunu da yapabiliriz:

                std::reference_wrapper ref1 { x };        // C++17
                auto ref2 { std::reference_wrapper{ x }}; // C++17

Ama std::ref() ve std::cref() yazmasý daha kýsa olduðu için, std::reference_wrapper nesneleri oluþturmak için hala yaygýn olarak kullanýlýyorlar.

17.6 — std::array ve enümeratorlar
----------------------------------
16.9 dersinde -- Dizinin indekslenmesi ve uzunluðu enümeratorlar kullanýlarak, diziler ve enümeratorlar hakkýnda konuþtuk. Artýk araç setimizde
constexpr std::array olduðuna göre, bu tartýþmayý sürdüreceðiz ve birkaç ek hile göstereceðiz.

Dizi baþlatýcýlarýnýn uygun sayýsýný saðlamak için statik assert kullanma
-------------------------------------------------------------------------
Bir constexpr std::array'ý CTAD kullanarak baþlatýrken, derleyici dizi baþlatýcýlarýnýn sayýsýndan dizinin ne kadar uzun olmasý gerektiðini çýkarýr
Beklenenden daha az baþlatýcý saðlanýrsa, dizi beklenenden daha kýsa olacak ve onu indekslemek tanýmsýz davranýþa yol açabilir Örneðin:

                #include <array>
                #include <iostream>

                enum StudentNames
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_students // 5
                };

                int main()
                {
                    constexpr std::array testScores { 78, 94, 66, 77 }; // hata, sadece 4 deðer

                    std::cout << "Cartman'ýn notu " << testScores[StudentNames::cartman] << '\n'; // geçersiz indeks nedeniyle tanýmsýz davranýþ

                    return 0;
                }
Bir constexpr std::array'deki baþlatýcýlarýn sayýsý makul bir þekilde kontrol edilebiliyorsa, bunu bir statik assert kullanarak yapabilirsiniz:

                #include <array>
                #include <iostream>

                enum StudentNames
                {
                    kenny, // 0
                    kyle, // 1
                    stan, // 2
                    butters, // 3
                    cartman, // 4
                    max_students // 5
                };

                int main()
                {
                    constexpr std::array testScores { 78, 94, 66, 77 };

                    // Test notlarýnýn sayýsýnýn öðrenci sayýsýyla ayný olduðunu doðrula
                    static_assert(std::size(testScores) == max_students); // derleme hatasý: static_assert koþulu baþarýsýz oldu

                    std::cout << "Cartman'ýn notu " << testScores[StudentNames::cartman] << '\n';

                    return 0;
                }
Bu þekilde, daha sonra yeni bir enümerator ekler ama testScores'a karþýlýk gelen bir baþlatýcý eklemeyi unutursanýz, program derlenmeyecektir.
Ayrýca, iki farklý constexpr std::array'ýn ayný uzunluða sahip olduðunu saðlamak için bir statik assert kullanabilirsiniz.

Daha iyi bir numaralandýrma giriþi ve çýkýþý için constexpr dizilerini kullanma
-------------------------------------------------------------------------------
13.3 dersinde -- Kapsam dýþý numaralandýrma giriþi ve çýkýþý, numaralandýrýcýlarýn adlarýný çýktý olarak vermenin birkaç yolunu ve bir
numaralandýrýlmýþ deðeri bir tamsayý olarak giriþ yapmanýn bir yolunu ele aldýk. Bu iþlevleri biraz geliþtirelim. Aþaðýdaki örnekte, her 
numaralandýrýcýnýn adýný bir std::string_view olarak tutmak için bir dizi kullanýyoruz. Ardýndan bu diziyi iki amaç için kullanýyoruz:

*- Numaralandýrýcýlarýn adýný bir dize olarak kolayca çýktý almak.
*- Numaralandýrýcýlarýn adýný bir dize olarak aramak.
Sonuncusu, bize operator>>'nin bir numaralandýrýcýyý isimle (tamsayý yerine) nasýl giriþ yapacaðýný öðretmemizi saðlar!

                #include <array>
                #include <iostream>
                #include <string>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullanýn, böylece std::array tipi std::string_view olarak çýkarýr
                    using namespace std::string_view_literals; // sv soneki için
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // Tüm renklerimiz için dize tanýmladýðýmýzdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nasýl yazdýrýlacaðýný öðretin
                // Þimdilik bunu sihir olarak düþünün çünkü henüz kullandýðý hiçbir kavramý açýklamadýk
                // std::ostream, std::cout'un tipidir
                // Dönüþ tipi ve parametre tipi referanslardýr (kopyalarýn yapýlmasýný önlemek için)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                // operator>>'e bir Color'ý isimle nasýl giriþ yapacaðýný öðretin
                // Þimdilik bunu sihir olarak düþünün
                // Color'ý sabit olmayan bir referansla geçiriyoruz, böylece iþlevin deðerini deðiþtirmesine izin verebiliriz
                std::istream& operator>> (std::istream& in, Color::Type& color)
                {
                    std::string input {};
                    std::getline(in >> std::ws, input);

                    // Bir eþleþme bulup bulamayacaðýmýzý görelim
                    for (std::size_t index=0; index < Color::colorName.size(); ++index)
                    {
                        if (input == Color::colorName[index])
                        {
                            color = static_cast<Color::Type>(index);
                            return in;
                        }
                    }

                    // Bir eþleþme bulamadýk, bu yüzden giriþ geçersiz olmalýydý
                    // bu yüzden giriþ akýþýný hata durumuna getireceðiz
                    in.setstate(std::ios_base::failbit);
                    return in;
                }

                int main()
                {
                    auto shirt{ Color::blue };
                    std::cout << "Your shirt is " << shirt << '\n';

                    std::cout << "Enter a new color: ";
                    std::cin >> shirt;
                    if (!std::cin)
                        std::cout << "Invalid\n";
                    else
                        std::cout << "Your shirt is now " << shirt << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Your shirt is blue
                Enter a new color: red
                Your shirt is now red

Aralýk tabanlý for-döngüleri ve numaralandýrmalar
-------------------------------------------------
Bazen, bir numaralandýrmanýn numaralandýrýcýlarý üzerinde yinelemek için kullanýþlý olabilecek durumlarla karþýlaþýrýz. Bunu bir for-döngüsü
kullanarak bir tam sayý indeksi ile yapabiliriz, ancak bu muhtemelen tam sayý indeksimizi numaralandýrma türümüze statik olarak dökme
gerektirecektir.

                #include <array>
                #include <iostream>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullanýn, böylece std::array tipi std::string_view olarak çýkarýr
                    using namespace std::string_view_literals; // sv soneki için
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // Tüm renklerimiz için stringler tanýmladýðýmýzdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nasýl yazdýrýlacaðýný öðretin
                // Þimdilik bu sihir olarak düþünün çünkü henüz kullandýðý kavramlarý açýklamadýk
                // std::ostream, std::cout'un tipidir
                // Dönüþ tipi ve parametre tipi referanslardýr (kopyalarýn yapýlmasýný önlemek için)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                int main()
                {
                    // Tüm renklerimiz üzerinde yinelemek için bir for döngüsü kullanýn
                    for (int i=0; i < Color::max_colors; ++i )
                        std::cout << getColorName(static_cast<Color::Type>(i)) << '\n'; // burada çirkin static_cast

                    return 0;
                }
Ne yazýk ki, aralýk tabanlý for-döngüleri, bir numaralandýrmanýn numaralandýrýcýlarý üzerinde yinelemenize izin vermez:

                #include <array>
                #include <iostream>
                #include <string_view>

                namespace Color
                {
                    enum Type
                    {
                        black,
                        red,
                        blue,
                        max_colors
                    };

                    // sv sonekini kullanýn, böylece std::array tipi std::string_view olarak çýkarýr
                    using namespace std::string_view_literals; // sv soneki için
                    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

                    // Tüm renklerimiz için stringler tanýmladýðýmýzdan emin olun
                    static_assert(std::size(colorName) == max_colors);
                };

                constexpr std::string_view getColorName(Color::Type color)
                {
                    return Color::colorName[color];
                }

                // operator<<'e bir Color nasýl yazdýrýlacaðýný öðretin
                // Þimdilik bu sihir olarak düþünün çünkü henüz kullandýðý kavramlarý açýklamadýk
                // std::ostream, std::cout'un tipidir
                // Dönüþ tipi ve parametre tipi referanslardýr (kopyalarýn yapýlmasýný önlemek için)!
                std::ostream& operator<<(std::ostream& out, Color::Type color)
                {
                    return out << getColorName(color);
                }

                int main()
                {
                    for (auto c: Color::Type) // derleme hatasý: numaralandýrmayý geçemez
                        std::cout << c < '\n';

                    return 0;
                }
Bunun için birçok yaratýcý çözüm var. Bir dizi üzerinde bir aralýk tabanlý for-döngüsü kullanabildiðimizden, en basit çözümlerden biri, 
numaralandýrýcýlarýmýzýn her birini içeren bir constexpr std::array oluþturmak ve ardýndan bunun üzerinde yinelemektir. Bu yöntem,
numaralandýrýcýlarýn 0'dan baþlayarak sýralý deðerlere sahip olmasý durumunda çalýþýr (ancak çoðu numaralandýrma bunu yapar).

Bir std::array'ýn elemanlarý, Color::types'ýn eleman türü Color::Type olduðundan, c deðiþkeni bir Color::Type olarak çýkarýlacaktýr, ki bu tam
olarak istediðimiz þeydir!

Bu, aþaðýdakileri yazdýrýr:

                black
                red
                blue

17.7 — C Tarzý Dizilere Giriþ
-----------------------------
Artýk std::vector ve std::array'ý ele aldýðýmýza göre, dizilerin kapsamýný son dizi türü olan C tarzý dizileri ele alarak tamamlayacaðýz.
16.1 dersinde -- Konteynerlere ve dizilere giriþ konusunda belirtildiði gibi, C tarzý diziler C dilinden miras alýnmýþtýr ve C++'ýn çekirdek
diline yerleþiktir (diðer tüm dizi türlerinin aksine, bunlar standart kütüphane konteyner sýnýflarýdýr). Bu, onlarý kullanmak için bir baþlýk 
dosyasýný #include etmemiz gerektiði anlamýna gelir.

Bir parantez içinde...
----------------------
Dil tarafýndan yerel olarak desteklenen tek dizi türü olduklarý için, standart kütüphane dizi konteyner türleri (ör. std::array ve std::vector)
genellikle bir C tarzý dizi kullanýlarak uygulanýr.

Bir C Tarzý Dizi Bildirme
-------------------------
Çekirdek dilin bir parçasý olduklarý için, C tarzý dizilerin kendi özel bildirim sözdizimleri vardýr. Bir C tarzý dizi bildiriminde,
bir nesnenin bir C tarzý dizi olduðunu derleyiciye söylemek için köþeli parantezler ([]) kullanýrýz. Köþeli parantezlerin içinde, isteðe baðlý 
olarak dizinin uzunluðunu saðlayabiliriz, bu, derleyiciye dizide kaç eleman olduðunu söyleyen std::size_t türünde bir integral deðerdir.
Aþaðýdaki taným, 30 adet int elemaný içeren testScore adýnda bir C tarzý dizi deðiþkeni oluþturur:

                int main()
                {
                    // testScore adýnda 30 deðer baþlatýlmýþ int elemaný içeren bir C tarzý dizi tanýmlar (include gerekmez)
                    int testScore[30] {};      

                    // Karþýlaþtýrma için, iþte 30 deðer baþlatýlmýþ int elemaný içeren bir std::array (requires #including <array>)
                    std::array<int, 30> arr{}; 

                    return 0;
                }

Bir C tarzý dizinin uzunluðu en az 1 olmalýdýr. Dizi uzunluðu sýfýr, negatif veya integral olmayan bir deðerse derleyici hata verecektir.

Bir c-style dizinin uzunluðu sabit bir ifade olmalýdýr
------------------------------------------------------
std::array gibi, bir C-style dizi tanýmlarken, dizinin uzunluðu bir sabit ifade olmalýdýr (tipi std::size_t olsa da, bu genellikle önemli deðildir)

Ýpucu -> Bazý derleyiciler, C99 özelliði olan deðiþken uzunluklu diziler (VLAs) ile uyumluluk için constexpr olmayan uzunluklarda diziler 
         oluþturmayý kabul edebilir.

Deðiþken uzunluklu diziler  C++ da geçerli deðildir ve C++ programlarýnda kullanýlmamalýdýr. Eðer derleyiciniz bu dizilere izin veriyorsa, 
muhtemelen derleyici uzantýlarýný devre dýþý býrakmayý unuttunuz (bkz. 0.10 -- Derleyicinizi yapýlandýrma: Derleyici uzantýlarý).

Bir C-style diziyi alt dizinleme
--------------------------------
std::array ile olduðu gibi, C-style diziler de alt dizin operatörü (operator[]) kullanýlarak indekslenebilir:

                #include <iostream>

                int main()
                {
                    int arr[5]; // 5 int deðerinin bir dizisini tanýmla

                    arr[1] = 7; // alt dizin operatörünü kullanarak dizi öðesi 1'i indeksle
                    std::cout << arr[1]; // 7 yazdýrýr

                    return 0;
                }
Standart kütüphane konteyner sýnýflarýnýn aksine (sadece unsigned indeksleri kullanýr), bir C-style dizinin indeksi ya bir signed ya da
bir unsigned tam sayý veya kapsamsýz bir numaralandýrma olabilir. Bu, C-style dizilerin standart kütüphane konteyner sýnýflarýnýn tüm iþaret
dönüþüm indeksleme sorunlarýna tabi olmadýðý anlamýna gelir!

                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };

                    int s { 2 };
                    std::cout << arr[s] << '\n'; // signed indeks kullanmak tamam

                    unsigned int u { 2 };
                    std::cout << arr[u] << '\n'; // unsigned indeks kullanmak tamam

                    return 0;
                }

Ýpucu -> C-style diziler signed veya unsigned indeksleri (veya kapsamsýz numaralandýrmalarý) kabul eder.
operator[] herhangi bir sýnýr kontrolü yapmaz ve sýnýrlarýn dýþýnda bir indeks geçmek tanýmsýz davranýþa yol açar.

Bir parantez açmak gerekirse, Bir dizi tanýmlarken (ör. int arr[5]), [] kullanýmý bildirim sözdiziminin bir parçasýdýr, alt dizin operatörü
operator[]'nin bir çaðrýsý deðildir.

C-style dizilerin toplu baþlatýlmasý
------------------------------------
std::array gibi, C-style diziler de topluluktur, bu da onlarýn toplu baþlatma ile baþlatýlabileceði anlamýna gelir. Hýzlý bir hatýrlatma olarak, 
toplu baþlatma, topluluklarýn üyelerini doðrudan baþlatmamýzý saðlar. Bunu yapmak için, bir baþlatýcý listesi saðlarýz, bu bir virgülle ayrýlmýþ 
baþlatma deðerlerinin süslü parantezlerle çevrili listesidir.

                int main()
                {
                    int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // süslü liste kullanarak kopya-liste baþlatma
                    int prime[5] { 2, 3, 5, 7, 11 };         // süslü liste kullanarak liste baþlatma (tercih edilir)

                    return 0;
                }
Bu baþlatma formlarýnýn her biri, dizi üyelerini sýrayla baþlatýr,Varsayýlan olarak 0 öðesiyle baþlar. Eðer bir C-style dizi için bir baþlatýcý 
saðlamazsanýz, öðeler varsayýlan olarak baþlatýlýr. Çoðu durumda, bu öðelerin baþlatýlmamýþ býrakýlmasý sonucunu doðurur. Genellikle öðelerimizin 
baþlatýlmasýný istediðimiz için, baþlatýcýlarý olmayan C-style diziler tanýmlandýðýnda deðer baþlatmalýdýr (boþ süslü parantezler kullanarak).

                int main()
                {
                    int arr1[5];    // Üyeler varsayýlan olarak baþlatýlýr int öðeleri baþlatýlmamýþ býrakýlýr)
                    int arr2[5] {}; // Üyeler deðer baþlatýlýr (int öðeleri sýfýr baþlatýlýr) (tercih edilir)

                    return 0;
                }
Eðer bir baþlatýcý listesinde tanýmlanan dizi uzunluðundan daha fazla baþlatýcý saðlanýrsa, derleyici hata verecektir. Eðer bir baþlatýcý
listesinde tanýmlanan dizi uzunluðundan daha az baþlatýcý saðlanýrsa, baþlatýcýsý olmayan kalan öðeler deðer baþlatýlýr:

                int main()
                {
                    int a[4] { 1, 2, 3, 4, 5 }; // derleme hatasý: çok fazla baþlatýcý
                    int b[4] { 1, 2 };          // arr[2] ve arr[3] deðer baþlatýlýr

                    return 0;
                }
Bir C-style dizi kullanmanýn bir dezavantajý, öðenin türünün açýkça belirtilmesi gerektiðidir. CTAD çalýþmaz çünkü C-style diziler sýnýf þablonlarý
deðildir. Ve bir dizinin öðe türünü baþlatýcýlar listesinden çýkarmaya çalýþmak için auto kullanmak da iþe yaramaz:

                int main()
                {
                    auto squares[5] { 1, 4, 9, 16, 25 }; // derleme hatasý: C tarzý dizilerde tür çýkarýmý kullanýlamaz

                    return 0;
                }

Uzunluk Atlanmýþ
----------------
Aþaðýdaki dizi tanýmýnda ince bir fazlalýk var. Gördünüz mü?

                int main()
                {
                    const int prime[5] { 2, 3, 5, 7, 11 }; // prime'ýn uzunluðu 5

                    return 0;
                }

Derleyiciye dizinin uzunluðunun 5 olduðunu açýkça söylüyoruz ve ardýndan onu 5 elemanla baþlatýyoruz. Bir C tarzý diziyi bir baþlatýcý listesiyle
baþlattýðýmýzda, uzunluðu (dizi tanýmýnda) atlayabilir ve derleyicinin dizinin uzunluðunu baþlatýcýlarýn sayýsýndan çýkarmasýna izin verebiliriz.

Aþaðýdaki dizi tanýmlarý ayný þekilde davranýr:

                int main()
                {
                    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 açýkça uzunluðu 5 olarak tanýmlandý
                    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 derleyici tarafýndan uzunluðu 5 olarak çýkarýldý

                    return 0;
                }
Bu, yalnýzca tüm dizi üyeleri için baþlatýcýlar açýkça saðlandýðýnda çalýþýr.

                int main()
                {
                    int bad[] {}; // hata: derleyici bunu izin verilmeyen bir sýfýr uzunluklu dizi olarak çýkaracak!

                    return 0;
                }
Bir C tarzý dizinin tüm elemanlarýný bir baþlatýcý listesiyle baþlatýrken, uzunluðu atlamak ve derleyicinin dizinin uzunluðunu hesaplamasýna 
izin vermek tercih edilir. Bu þekilde, baþlatýcýlar eklenir veya kaldýrýlýrsa, dizinin uzunluðu otomatik olarak ayarlanýr ve tanýmlanan dizi 
uzunluðu ve saðlanan baþlatýcýlarýn sayýsý arasýnda bir uyumsuzluk riski yoktur.

*** BEST -> Her dizi elemanýný bir deðerle açýkça baþlatýrken, bir C tarzý dizinin uzunluðunu atlamayý tercih edin.

Const ve constexpr C tarzý diziler
----------------------------------
std::array gibi, C tarzý diziler de const veya constexpr olabilir. Diðer const deðiþkenler gibi, const diziler baþlatýlmalýdýr ve elemanlarýn 
deðeri sonradan deðiþtirilemez.

                #include <iostream>

                namespace ProgramData
                {
                    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // constexpr int dizisi
                }

                int main()
                {
                    const int prime[5] { 2, 3, 5, 7, 11 }; // const int dizisi
                    prime[0] = 17; // derleme hatasý: const int deðiþtirilemez

                    return 0;
                }

C tarzý bir dizinin sizeof'u
----------------------------
Önceki derslerde, sizeof() operatörünü bir nesnenin veya tipin boyutunu bayt cinsinden almak için kullandýk. Bir C tarzý diziye uygulandýðýnda, 
sizeof() tüm dizinin kullandýðý bayt sayýsýný döndürür:

                #include <iostream>

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 }; // derleyici prime'ýn uzunluðunu 5 olarak çýkaracak

                    std::cout << sizeof(prime); // 20 yazdýrýr (4 baytlýk int varsayýlýrsa)

                    return 0;
                }
4 baytlýk int varsayýlýrsa, yukarýdaki program 20 yazdýrýr. Prime dizisi, her biri 4 bayt olan 5 int elemaný içerir, bu yüzden 5 * 4 = 20 bayt.
Burada hiçbir fazlalýk yok. Bir dizi nesnesi, elemanlarýný ve baþka hiçbir þey içermez.

C-stil bir dizinin uzunluðunu alma
----------------------------------
C++17'de, <iterator> baþlýðýnda tanýmlanan std::size() kullanabiliriz, bu da dizinin uzunluðunu std::size_t türünde bir unsigned integral deðer 
olarak döndürür. C++20'de, std::ssize() kullanabiliriz, bu da dizinin uzunluðunu büyük bir signed integral türünde bir deðer olarak döndürür 
(muhtemelen std::ptrdiff_t).

                #include <iostream>
                #include <iterator> // std::size ve std::ssize için

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };   // derleyici prime'ýn uzunluðunu 5 olarak çýkarýr

                    std::cout << std::size(prime) << '\n';  // C++17, unsigned integral deðer 5 döndürür
                    std::cout << std::ssize(prime) << '\n'; // C++20, signed integral deðer 5 döndürür

                    return 0;
                }

C-stil bir dizinin uzunluðunu alma (C++14 veya daha eski)
---------------------------------------------------------
C++17'den önce, C-stil bir dizinin uzunluðunu almak için standart bir kütüphane fonksiyonu yoktu.
Eðer C++11 veya C++14 kullanýyorsanýz, bunun yerine bu fonksiyonu kullanabilirsiniz:

                #include <iostream>

                template <typename T, std::size_t N>
                constexpr std::size_t length(const T(&)[N]) noexcept
                {
                    return N;
                }

                int main() {

                    int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
                    std::cout << "Dizinin: " << length(array) << " elemaný var\n";

                    return 0;
                }
Bu, bir C-stil dizisini referans olarak alan ve ardýndan dizinin uzunluðunu temsil eden non-type template parametresini döndüren bir fonksiyon
þablonu kullanýr. Çok daha eski kod tabanlarýnda, bir C-stil dizisinin uzunluðunun, tüm dizinin boyutunu bir dizi elemanýnýn boyutuna bölerken
belirlendiðini görebilirsiniz:

                #include <iostream>

                int main()
                {
                    int array[8] {};
                    std::cout << "Dizinin: " << sizeof(array) / sizeof(array[0]) << " elemaný var\n";

                    return 0;
                }
                Bu, þunu yazdýrýr:

                Dizinin: 8 elemaný var
Bu nasýl çalýþýr? Ýlk olarak, tüm dizinin boyutunun, dizinin uzunluðu ile bir elemanýn boyutunun çarpýmýna eþit olduðunu not edin.
Daha kompakt bir þekilde ifade edersek: dizi boyutu = uzunluk * eleman boyutu.

Cebir kullanarak, bu denklemi yeniden düzenleyebiliriz: uzunluk = dizi boyutu / eleman boyutu. Eleman boyutu için genellikle sizeof(array[0])
kullanýrýz. Bu nedenle, uzunluk = sizeof(array) / sizeof(array[0]). Bunu bazen sizeof(array) / sizeof(*array) olarak yazýldýðýný da görebilirsiniz, 
bu ayný þeyi yapar. Ancak, size bir sonraki derste göstereceðimiz gibi, bu formül (bir decayed array geçirildiðinde) oldukça kolay bir þekilde 
baþarýsýz olabilir, programý beklenmedik bir þekilde bozabilir. C++17'nin std::size() ve yukarýda gösterilen length() fonksiyon þablonu her iki
durumda da derleme hatalarýna neden olur, bu yüzden güvenli bir þekilde kullanýlabilirler.

17.8 — C-stil array decay
-------------------------
C-stil dizisi geçirme zorluðu
-----------------------------
C dilinin tasarýmcýlarý bir sorunla karþýlaþtý. Aþaðýdaki basit programý düþünün:

                #include <iostream>

                void print(int val)
                {
                    std::cout << val;
                }

                int main()
                {
                    int x { 5 };
                    print(x);

                    return 0;
                }

print(x) çaðrýldýðýnda, x argümanýnýn deðeri (5) val parametresine kopyalanýr. Fonksiyonun gövdesi içinde, val'in deðeri (5) konsola yazdýrýlýr.
X'in kopyalanmasý ucuz olduðu için burada bir sorun yok.

Þimdi, tek bir int yerine 1000 elemanlý bir C-stil int dizisi kullanan benzer bir programý düþünün:

                #include <iostream>

                void printElementZero(int arr[1000])
                {
                    std::cout << arr[0]; // ilk elemanýn deðerini yazdýr
                }

                int main()
                {
                    int x[1000] { 5 };   // 1000 elemanlý bir dizi tanýmla, x[0] 5'e baþlatýlýr
                    printElementZero(x);

                    return 0;
                }
Bu program da derlenir ve beklenen deðeri (5) konsola yazdýrýr. Bu örnekteki kod, önceki örnekteki koda benzerken, mekanik olarak beklediðinizden 
biraz farklý çalýþýr (bunu aþaðýda açýklayacaðýz). Ve bu, C tasarýmcýlarýnýn iki büyük zorluðu çözmek için bulduðu çözümden kaynaklanmaktadýr.

Ýlk olarak, her fonksiyon çaðrýldýðýnda 1000 elemanlý bir diziyi kopyalamak pahalýdýr (özellikle elemanlar pahalý bir kopya türüyse), 
bu yüzden bunu önlemek istiyoruz. Ama nasýl? C'nin referanslarý yok, bu yüzden fonksiyon argümanlarýnýn bir kopyasýný yapmaktan kaçýnmak için
referans ile geçme seçeneði yok.

Ýkinci olarak, farklý uzunluklarda dizi argümanlarýný kabul edebilecek tek bir fonksiyon yazabilmek istiyoruz. Ýdeal olarak, yukarýdaki örnekteki 
printElementZero() fonksiyonumuz, herhangi bir uzunluktaki dizi argümanlarýyla çaðrýlabilir olmalýdýr (çünkü eleman 0'ýn var olduðu garantilidir).
Her olasý dizi uzunluðu için farklý bir fonksiyon yazmak zorunda kalmak istemiyoruz. Ama nasýl? C'nin "herhangi bir uzunlukta" dizileri belirtmek 
için bir sözdizimi yok, þablonlarý desteklemiyor, ne de bir uzunluktaki diziler baþka bir uzunluða dönüþtürülebiliyor (muhtemelen bunun pahalý bir
kopya yapmayý gerektireceði için).

C dilinin tasarýmcýlarý, her iki sorunu da çözen zekice bir çözüm buldular (uyumluluk nedenleriyle C++ tarafýndan miras alýndý):

                #include <iostream>

                void printElementZero(int arr[1000]) // bir kopya yapmaz
                {
                    std::cout << arr[0]; // ilk elemanýn deðerini yazdýr
                }

                int main()
                {
                    int x[7] { 5 };      // 7 elemanlý bir dizi tanýmla
                    printElementZero(x); // bir þekilde çalýþýyor!

                    return 0;
                }
Bir þekilde, yukarýdaki örnek, herhangi bir kopya yapýlmadan, 1000 elemanlý bir dizi bekleyen bir fonksiyona 7 elemanlý bir dizi geçirir. 
Bu dersimizde, bunun nasýl çalýþtýðýný inceleyeceðiz. Ayrýca, C tasarýmcýlarýnýn seçtiði çözümün neden tehlikeli olduðuna ve modern 
C++ için uygun olmadýðýna bakacaðýz.

Ama önce, iki alt konuyu kapsamamýz gerekiyor.

Diziden Ýþaretçiye Dönüþümler (Dizi Çürümesi)
---------------------------------------------
Çoðu durumda, bir C tarzý dizi bir ifadede kullanýldýðýnda, dizi, ilk elemanýn (indeks 0 olan) adresiyle baþlatýlan eleman türüne bir iþaretçiye
otomatik olarak dönüþtürülür. Bu, halk arasýnda dizi bozunmasý (veya kýsaca bozunma ( decay )) olarak adlandýrýlýr.

Bunu aþaðýdaki programda görebilirsiniz:

                #include <iomanip> // std::boolalpha için
                #include <iostream>

                int main()
                {
                    int arr[5]{ 9, 7, 5, 3, 1 }; // dizimizin elemanlarý int türünde

                    // Öncelikle, arr'ýn bir int* iþaretçisine çürüdüðünü kanýtlayalým

                    auto ptr{ arr }; // deðerlendirme arr'ýn çürümesine neden olur, tür çýkarýmý türün int* olduðunu çýkarmalý
                    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // ptr'nin türü int* ise true yazdýrýr

                    // Þimdi iþaretçinin dizinin ilk elemanýnýn adresini tuttuðunu kanýtlayalým

                    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu yazdý:

                true
                true

Bir dizi bozunduðunda iþaretçi hakkýnda özel bir þey yoktur. Bu, ilk elemanýn adresini tutan normal bir iþaretçidir.
Benzer þekilde, bir const dizisi (ör. const int arr[5]) bir const'a iþaret eden iþaretçiye (const int*) bozunur.

Ýpucu -> C++'da, bir C tarzý dizinin bozunmadýðý birkaç yaygýn durum vardýr:

*- sizeof() veya typeid() argümaný olarak kullanýldýðýnda.
*- Dizinin adresini operator& kullanarak alýrken.
*- Bir sýnýf türünün üyesi olarak geçirildiðinde.
*- Referans olarak geçirildiðinde.

C tarzý dizilerin çoðu durumda bir iþaretçiye bozunmasý nedeniyle, dizilerin iþaretçiler olduðuna inanmak yaygýn bir yanýlgýdýr. Bu doðru deðil.
Bir dizi nesnesi bir eleman dizisidir, oysa bir iþaretçi nesnesi sadece bir adresi tutar.

Bir dizi ve bozunmuþ bir dizi arasýndaki tür bilgisi farklýdýr. Yukarýdaki örnekte, arr dizisinin türü int[5]'tir, bozunmuþ dizinin türü ise
int*'dir. Özellikle, dizi türü int[5] uzunluk bilgisi içerirken, bozunmuþ dizi iþaretçi türü int* bunu içermez.

Ana Fikir

Bir bozunmuþ dizi iþaretçisi, iþaret ettiði dizinin ne kadar uzun olduðunu bilmez. "Bozunma" terimi, bu uzunluk türü bilgisinin kaybýný gösterir.
Bir C Tarzý Diziyi Alt dizinlemek Aslýnda bozunmuþ Ýþaretçiye operator[] Uygular

Bir C tarzý dizi deðerlendirildiðinde bir iþaretçiye bozunur, bu yüzden bir C tarzý dizi altdizinlendiðinde, altdizin aslýnda bozunmuþ dizi iþaretçisi üzerinde iþlem yapar:

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    std::cout << arr[2]; // bozunmuþ diziyi altdizinleme ile eleman 2'yi alýr, 5 yazdýrýr

    return 0;
}
```
Ayrýca operator[]'yi doðrudan bir iþaretçi üzerinde de kullanabiliriz. Eðer bu iþaretçi ilk elemanýn adresini tutuyorsa, sonuç ayný olacaktýr:

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr };  // arr bir iþaretçiye bozunur
    std::cout << ptr[2];    // ptr'yi altdizinleme ile eleman 2'yi alýr, 5 yazdýrýr

    return 0;
}
```
Birazdan bunun nerede kullanýþlý olduðunu göreceðiz ve aslýnda bunun nasýl çalýþtýðýna (ve iþaretçinin ilk elemanýn adresinden baþka bir þeyi tuttuðunda ne olduðuna) bir sonraki derste 17.9 -- Ýþaretçi aritmetiði ve altdizinleme konusunda daha derinlemesine bakacaðýz.

Dizi çürümesi, C-style dizi geçirme sorunumuzu çözer

Dizi çürümesi, dersin baþýnda karþýlaþtýðýmýz her iki zorluðu da çözer.

Bir C-style diziyi bir argüman olarak geçirirken, dizi bir iþaretçiye bozunur veya bozulur ve dizinin ilk öðesinin adresini tutan iþaretçi,
fonksiyona geçirilen þeydir. Yani, C-style diziyi deðer olarak geçirdiðimiz gibi görünse de, aslýnda onu adres olarak geçiriyoruz! Bu, C-style dizi
argümanýnýn bir kopyasýnýn yapýlmasýnýn nasýl önlendiðidir.

Anahtar nokta þudur ki; C-style diziler, deðer olarak geçirildikleri gibi görünseler bile, adres olarak geçirilirler.

Þimdi, ayný öðe türüne ama farklý uzunluklara sahip iki farklý dizi düþünün (ör. int[5] ve int[7]). Bunlar, birbirleriyle uyumsuz olan ayrý
türlerdir. Ancak, her ikisi de ayný iþaretçi türüne (ör. int*) bozunur. Onlarýn bozunmuþ sürümleri birbirinin yerine geçebilir! Türden uzunluk 
bilgisini atmak, tür uyumsuzluðu olmadan farklý uzunluklarda dizileri geçirmemize olanak saðlar.

Anahtar nokta, Ayný öðe türüne ama farklý uzunluklara sahip iki C-style dizi, ayný iþaretçi türüne bozunur.

Aþaðýdaki örnekte, iki þeyi göstereceðiz:

*- Farklý uzunluklarda dizileri tek bir fonksiyona geçirebiliriz (çünkü her ikisi de ayný iþaretçi türüne bozunur).
*- Diziyi alan fonksiyon parametremizin, dizinin öðe türünün bir (const) iþaretçisi olabilir.

                #include <iostream>

                void printElementZero(const int* arr) // const adresi ile geçir
                {
                    std::cout << arr[0];
                }

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };
                    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

                    printElementZero(prime);   // prime bir const int* iþaretçisine bozunur
                    printElementZero(squares); // squares bir const int* iþaretçisine bozunur

                    return 0;
                }

                Bu örnek gayet iyi çalýþýr ve þunu yazdýrýr:

                2
                1
main() içinde, printElementZero(prime) çaðrýsýný yaptýðýmýzda, prime dizisi const int[5] türünden bir diziden, prime'ýn ilk öðesinin adresini tutan
const int* türünde bir iþaretçiye bozunur. Benzer þekilde, printElementZero(squares) çaðrýsýný yaptýðýmýzda, squares dizisi const int[8] türünde
bir diziden, squares'ýn ilk öðesinin adresini tutan const int* türünde bir iþaretçiye bozunur. Bu const int* türündeki iþaretçiler, aslýnda 
fonksiyona bir argüman olarak geçirilen þeylerdir.

Ýþaretçileri const int* türünde geçirdiðimizden, printElementZero() fonksiyonumuzun ayný iþaretçi türünde bir parametreye sahip olmasý gerekiyor.
Bu fonksiyon içinde, seçili dizi öðesine eriþmek için iþaretçiyi alt dizinliyoruz.Bir C-style dizi adres olarak geçirildiðinden, fonksiyon doðrudan
geçirilen diziye (bir kopya deðil) eriþir ve öðelerini deðiþtirebilir. Bu nedenle, fonksiyonunuzun dizi öðelerini deðiþtirmeyi amaçlamamasý
durumunda, fonksiyon parametrenizin const olmasýný saðlamak iyi bir fikirdir.

C-style dizi fonksiyon parametre sözdizimi
------------------------------------------
Fonksiyon parametresini int* arr olarak bildirmenin bir sorunu, arr'ýn tek bir tam sayýya deðil, deðerlerin bir dizisine iþaret eden bir iþaretçi 
olmasý gerektiðinin açýk olmamasýdýr. Bu nedenle, bir C-style dizi geçirirken, int arr[] alternatif bildirim formunu kullanmak tercih edilir:

                #include <iostream>

                void printElementZero(const int arr[]) // const int* ile ayný þekilde ele alýnýr
                {
                    std::cout << arr[0];
                }

                int main()
                {
                    const int prime[] { 2, 3, 5, 7, 11 };
                    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

                    printElementZero(prime);  // prime bir iþaretçiye bozunur
                    printElementZero(squares); // squares bir iþaretçiye bozunur

                    return 0;
                }

Bu program, öncekiyle ayný þekilde davranýr, çünkü derleyici, fonksiyon parametresi const int arr[]'yi const int* ile ayný þekilde yorumlar.
Ancak, bu, arr'ýn tek bir deðere deðil, bozunmuþ bir C-style dizi olmasý beklenen bir iþaretçi olduðunu çaðýrýcýya iletmek gibi bir avantaja
sahiptir. Köþeli parantezler arasýnda uzunluk bilgisine gerek yoktur (zaten kullanýlmadýðý için). Eðer bir uzunluk saðlanýrsa, bu göz ardý edilir.

*** BEST -> Bir C tarzý dizi türü bekleyen bir fonksiyon parametresi, dizi sözdizimini (ör. int arr[]) kullanmalýdýr, pointer sözdizimi yerine 
            (ör. int *arr).

Bu sözdizimini kullanmanýn dezavantajý, arr'ýn bozunduðunun daha az belirgin olmasýdýr (pointer sözdizimiyle oldukça açýktýr), bu yüzden bozunmuþ
bir diziyle beklenildiði gibi çalýþmayan herhangi bir þey yapmamaya ekstra özen göstermeniz gerekecektir bunlardan bazýlarýný birazdan ele alacaðýz

Dizi Bozunmasýnýn Sorunlarý
---------------------------
Dizi çürümesi, farklý uzunluklarda C tarzý dizilerin pahalý kopyalar yapmadan bir fonksiyona geçirilebilmesini saðlamak için akýllýca bir çözümdü,
ancak dizi uzunluðu bilgisinin kaybolmasý, birkaç tür hatanýn yapýlmasýný kolaylaþtýrýr.

Öncelikle, sizeof() diziler ve bozunmuþ diziler için farklý deðerler döndürecektir:

                #include <iostream>

                void printArraySize(int arr[])
                {
                    std::cout << sizeof(arr) << '\n'; // 4 yazdýrýr (32 bit adresler varsayýlýrsa)
                }

                int main()
                {
                    int arr[]{ 3, 2, 1 };

                    std::cout << sizeof(arr) << '\n'; // 12 yazdýrýr (4 baytlýk int varsayýlýrsa)

                    printSize(arr);

                    return 0;
                }

Bu, bir C tarzý dizide sizeof() kullanmanýn potansiyel olarak tehlikeli olduðu anlamýna gelir, çünkü bunu yalnýzca gerçek dizi nesnesine 
eriþebildiðinizde, bozunmuþ dizi veya pointer olmadan kullanmanýz gerektiðinden emin olmalýsýnýz.

Önceki derste (17.7 -- C tarzý dizilere giriþ), sizeof(arr)/sizeof(*arr)'ýn tarihsel olarak bir C tarzý dizinin boyutunu almak için bir hile olarak
kullanýldýðýný belirttik. Bu hile tehlikelidir çünkü eðer arr bozunmuþsa, sizeof(arr) bir pointer'ýn boyutunu döndürecektir, bu da sonuçta yanlýþ 
dizi uzunluðunu üretir, muhtemelen programýn yanlýþ çalýþmasýna neden olur.

Neyse ki, C++17'nin daha iyi yerine geçeni std::size() (ve C++20'nin std::ssize()) bir pointer deðeri geçirildiðinde derlemeyi baþarýsýz olacaktýr:

                #include <iostream>

                int printArrayLength(int arr[])
                {
                    std::cout << std::size(arr) << '\n'; // derleme hatasý: std::size() bir pointer üzerinde çalýþmaz
                }

                int main()
                {
                    int arr[]{ 3, 2, 1 };

                    std::cout << std::size(arr) << '\n'; // 3 yazdýrýr

                    printArrayLength(arr);

                    return 0;
                }

Ýkinci olarak, ve belki de en önemlisi, dizi bozunmasý, yeniden düzenlemeyi (uzun fonksiyonlarý daha kýsa, daha modüler fonksiyonlara ayýrmayý)
zorlaþtýrabilir. Bozunmayan bir diziyle beklenildiði gibi çalýþan kod, ayný kod bozunmuþ bir dizi kullanýldýðýnda derlenmeyebilir 
(veya daha kötüsü, sessizce yanlýþ çalýþabilir).

Üçüncüsü, uzunluk bilgisine sahip olmamak birkaç programlama zorluðu yaratýr. Uzunluk bilgisi olmadan, dizinin uzunluðunu mantýklý bir þekilde 
kontrol etmek farklýdýr. Kullanýcýlar kolayca beklenenden daha kýsa dizileri (veya hatta tek bir deðere pointerlarý) geçirebilir, bu da onlar 
geçersiz bir indeksle abone olduðunda tanýmsýz davranýþa neden olur.

                #include <iostream>

                void printElement2(int arr[])
                {
                    // arr'ýn en az üç elemana sahip olduðunu nasýl saðlarýz?
                    std::cout << arr[2] << '\n';
                }

                int main()
                {
                    int a[]{ 3, 2, 1 };
                    printElement2(a);  // tamam

                    int b[]{ 7, 6 };
                    printElement2(b);  // derlenir ama tanýmsýz davranýþ üretir

                    int c{ 9 };
                    printElement2(&c); // derlenir ama tanýmsýz davranýþ üretir

                    return 0;
                }

Dizi uzunluðuna sahip olmamak ayrýca diziyi dolaþýrken zorluklar yaratýr - sona ne zaman ulaþtýðýmýzý nasýl bilebiliriz? Bu sorunlara çözümler var,
ancak bu çözümler bir programa hem karmaþýklýk hem de kýrýlganlýk ekler.

Dizi uzunluk sorunlarýný çözme
------------------------------
Tarihsel olarak, programcýlar dizi uzunluðu bilgisinin eksikliðini iki yöntemden biriyle çözmüþtür.

Ýlk olarak, hem diziyi hem de dizi uzunluðunu ayrý argümanlar olarak iletebiliriz:

                #include <cassert>
                #include <iostream>

                void printElement2(const int arr[], int length)
                {
                    assert(length > 2 && "printElement2: Dizi çok kýsa"); // length üzerinde static_assert kullanamayýz

                    std::cout << arr[2] << '\n';
                }

                int main()
                {
                    constexpr int a[]{ 3, 2, 1 };
                    printElement2(a, static_cast<int>(std::size(a)));  // tamam

                    constexpr int b[]{ 7, 6 };
                    printElement2(b, static_cast<int>(std::size(b)));  // assert tetikleyecek

                    return 0;
                }

Ancak, bu hala bir dizi sorunlarý içerir:

*- Çaðýranýn dizinin ve dizi uzunluðunun eþleþtiðinden emin olmasý gerekiyor -- eðer length için yanlýþ bir deðer geçirilirse, fonksiyon hala hatalý
   çalýþacaktýr.
*- Eðer std::size() kullanýyorsanýz veya uzunluðu std::size_t olarak döndüren bir fonksiyon kullanýyorsanýz, potansiyel iþaret dönüþüm sorunlarý
   vardýr.
*- Runtime assertler yalnýzca runtime'da karþýlaþýldýðýnda tetiklenir. Eðer test yolumuz fonksiyona yapýlan tüm çaðrýlarý kapsamýyorsa, müþteriye
   bir þeyi test etmediðimizde assert çýkaracak bir program gönderme riskimiz vardýr. Modern C++'da, constexpr dizilerin dizi uzunluðunu derleme
   zamanýnda doðrulamak için static_assert kullanmak isteriz, ancak bunu yapmanýn kolay bir yolu yoktur (çünkü fonksiyon parametreleri constexpr 
   olamaz, hatta constexpr veya consteval fonksiyonlarda bile!).

*- Bu yöntem yalnýzca açýk bir fonksiyon çaðrýsý yapýyorsak çalýþýr. Eðer fonksiyon çaðrýsý implicit ise (örneðin, diziyi bir operand olarak
   kullanarak bir operatörü çaðýrýyorsak), uzunluðu geçirme fýrsatý yoktur.

Ýkinci olarak, eðer semantik olarak geçerli olmayan bir eleman deðeri varsa (örneðin, -1 olan bir test skoru), bunun yerine bu deðere sahip bir 
elemaný kullanarak dizinin sonunu iþaretleyebiliriz. Bu þekilde, dizinin uzunluðu, dizinin baþlangýcý ve bu sonlandýrýcý eleman arasýnda kaç eleman
olduðunu sayarak hesaplanabilir. Dizi ayrýca, baþlangýçtan baþlayýp sonlandýrýcý elemana ulaþana kadar yineleyerek de geçilebilir.
Bu yöntemin güzel yaný, implicit fonksiyon çaðrýlarýyla bile çalýþmasýdýr.

Anahtar nokta þudur ki; C-stil dizeleri (ki bunlar C-stil dizilerdir) dizenin sonunu iþaretlemek için bir null-sonlandýrýcý kullanýr, 
böylece onlar decay olmuþ olsalar bile geçilebilirler.

Ama bu yöntemin de bir dizi sorunu vardýr:

*- Eðer sonlandýrýcý eleman mevcut deðilse, geçiþ dizinin sonundan doðruca yürüyecek, tanýmsýz davranýþa neden olacaktýr.
*- Diziyi geçen fonksiyonlarýn sonlandýrýcý eleman için özel bir iþlem yapmasý gereklidir (örneðin, bir C-stil dize yazdýrma fonksiyonunun
   sonlandýrýcý elemaný yazdýrmamasý gerektiðini bilmelidir).
*- Gerçek dizi uzunluðu ve semantik olarak geçerli elemanlarýn sayýsý arasýnda bir uyumsuzluk vardýr. Eðer yanlýþ uzunluk kullanýlýrsa, semantik
   olarak geçersiz sonlandýrýcý eleman "iþlenmiþ" olabilir.

Bu yaklaþým yalnýzca semantik olarak geçersiz bir deðer varsa çalýþýr, ki bu genellikle durum deðildir. Çoðu durumda C tarzý dizilerden
kaçýnýlmalýdýr

Standart dýþý geçiþ semantiði (adrese göre geçiþ, deðere göre geçiþ yerine kullanýlýr) ve bozulmuþ dizilerin uzunluk bilgilerini kaybetme riskleri
nedeniyle, C tarzý diziler genellikle tercih edilmez hale gelmiþtir. Mümkün olduðunca bunlardan kaçýnmanýzý öneririz.

*** BEST -> Pratik olduðunda C tarzý dizilerden kaçýnýn.
--------------------------------------------------------
*- Salt okunur dizeler için (string literal sembolik sabitleri ve string parametreleri) std::string_view'ý tercih edin.
*- Deðiþtirilebilir dizeler için std::string'i tercih edin.
*- Global olmayan constexpr diziler için std::array'i tercih edin.
*- constexpr olmayan diziler için std::vector'ü tercih edin.
*- Global constexpr diziler için C tarzý dizileri kullanmak tamam. Bunu birazdan tartýþacaðýz.

Bir parantez açalým...
----------------------
C++'da, diziler referans olarak geçirilebilir, bu durumda dizi argümaný bir fonksiyona geçirildiðinde bozulmaz (ancak diziye olan referans
deðerlendirildiðinde hala bozulur). Ancak, bunu tutarlý bir þekilde uygulamayý unutmak kolaydýr ve kaçýrýlan bir referans, bozulmuþ argümanlara yol
açar. Ayrýca, dizi referans parametrelerinin sabit bir uzunluðu olmalýdýr, yani fonksiyon yalnýzca belirli bir uzunluktaki dizileri iþleyebilir. 
Farklý uzunluktaki dizileri iþleyebilen bir fonksiyon istiyorsak, o zaman fonksiyon þablonlarýný da kullanmalýyýz. Ancak, C tarzý dizileri
"düzeltmek" için bu iki þeyi yapacaksanýz, o zaman zaten std::array'i kullanabilirsiniz!

Peki modern C++'da C tarzý diziler ne zaman kullanýlýr?
-------------------------------------------------------
Modern C++'da, C tarzý diziler genellikle iki durumda kullanýlýr:

1- constexpr global (veya constexpr statik local) program verisini saklamak için. Bu tür dizilere programýn her yerinden doðrudan eriþilebildiði için,
diziyi geçirmemize gerek yoktur, bu da bozulma ile ilgili sorunlarý önler. C tarzý dizileri tanýmlamak için sözdizimi, std::array'den biraz daha az
garip olabilir. Daha da önemlisi, bu tür dizilerin indekslenmesi, standart kütüphane konteyner sýnýflarýnýn yaptýðý gibi iþaret dönüþüm sorunlarýna
sahip deðildir.

2- constexpr olmayan C tarzý string argümanlarýný doðrudan iþlemek isteyen fonksiyonlara veya sýnýflara parametre olarak. Bunun için iki olasý 
neden vardýr: Ýlk olarak, constexpr olmayan bir C tarzý string'i bir std::string_view'a dönüþtürmek, C tarzý string'in uzunluðunu belirlemek için 
string'i geçmek gerektirir. Eðer fonksiyon, performansý kritik bir kod bölümünde ve uzunluk gerekmiyorsa (örneðin, çünkü fonksiyon zaten string'i 
geçecekse) o zaman dönüþümden kaçýnmak yararlý olabilir. Ýkincisi, eðer fonksiyon (veya sýnýf) C tarzý string'leri bekleyen diðer fonksiyonlarý 
çaðýrýyorsa, bir std::string_view'a dönüþtürmek için sadece geri dönüþtürmek suboptimal olabilir (std::string_view istemek için baþka nedenleriniz
olmadýkça).

17.9 — Pointer aritmetiði ve subscripting ( Alt dizinleme )
-----------------------------------------------------------
Ders 16.1 -- Konteynerlara ve dizilere giriþte, dizilerin ardýþýk olarak bellekte saklandýðýný belirtmiþtik. Bu derste, dizilerin indeksleme
matematiðinin nasýl çalýþtýðýna daha derinlemesine bakacaðýz.

Gelecekteki derslerde indeksleme matematiðini kullanmayacaðýz, ancak bu dersin konularý, aralýk tabanlý for döngülerinin aslýnda nasýl çalýþtýðýna
dair size içgörü saðlayacak ve daha sonra yineleyicileri ele aldýðýmýzda iþe yarayacak.

Ýþaretçi Aritmetiði Nedir?
--------------------------
Ýþaretçi aritmetiði, belirli tam sayý aritmetik operatörlerini (toplama, çýkarma, artýrma veya azaltma) bir iþaretçiye uygulayarak yeni 
bir bellek adresi üretmemize olanak saðlayan bir özelliktir.

Bazý ptr iþaretçisi verildiðinde, ptr + 1, bellekteki bir sonraki nesnenin adresini döndürür (iþaret edilen tipe dayanýr). Yani ptr bir int* ise 
ve bir int 4 byte ise, ptr + 1, ptr'den 4 byte sonraki bellek adresini döndürecek ve ptr + 2, ptr'den 8 byte sonraki bellek adresini döndürecektir.

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'lýk int'leri varsayalým

                    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu yazdý:

                00AFFD80 00AFFD84 00AFFD88

Her bellek adresinin bir öncekinden 4 byte daha büyük olduðuna dikkat edin.
Daha az yaygýn olmasýna raðmen, iþaretçi aritmetiði çýkarma ile de çalýþýr. Bazý ptr iþaretçisi verildiðinde, ptr - 1, bellekteki bir önceki 
nesnenin adresini döndürür (iþaret edilen tipe dayanýr).

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'lýk int'leri varsayalým

                    std::cout << ptr << ' ' << (ptr - 1) << ' ' << (ptr - 2) << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu yazdý:

                00AFFD80 00AFFD7C 00AFFD78

Bu durumda, her bellek adresi bir öncekinden 4 byte daha azdýr.

Ana Fikir, Ýþaretçi aritmetiði, bir sonraki/önceki adresi deðil, bir sonraki/önceki nesnenin adresini (iþaret edilen tipe dayanarak) döndürür.
Artýrma (++) ve azaltma (--) operatörlerini bir iþaretçiye uygulamak, sýrasýyla iþaretçi toplama ve iþaretçi çýkarmayla ayný þeyi yapar,
ancak iþaretçinin tuttuðu adresi gerçekten deðiþtirir.

Bazý int deðeri x verildiðinde, ++x, x = x + 1'in kýsa yoludur. Benzer þekilde, bazý ptr iþaretçisi verildiðinde, ++ptr, ptr = ptr + 1'in kýsa 
yoludur, bu iþaretçi aritmetiði yapar ve sonucu ptr'ye atar.

                #include <iostream>

                int main()
                {
                    int x {};
                    const int* ptr{ &x }; // 4 byte'lýk int'leri varsayalým

                    std::cout << ptr << '\n';

                    ++ptr; // ptr = ptr + 1
                    std::cout << ptr << '\n';

                    --ptr; // ptr = ptr - 1
                    std::cout << ptr << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu yazdý:

                00AFFD80 00AFFD84 00AFFD80

Altdizinleme Ýþaretçi Aritmetiði Aracýlýðýyla Uygulanýr
-------------------------------------------------------
Önceki derste (17.8 -- C tarzý dizi çürümesi), operator[]'nin bir iþaretçiye uygulanabileceðini belirttik:

                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 7, 5, 3, 1 };

                    const int* ptr{ arr }; // eleman 0'ýn adresini tutan normal bir iþaretçi
                    std::cout << ptr[2];   // ptr'yi altdizinleme ile eleman 2'yi alýr, 5 yazdýrýr

                    return 0;
                }

Burada neler olduðuna daha derinlemesine bakalým. Ortaya çýktýðý gibi, ptr[n] altdizin iþlemi, *((ptr) + (n)) ifadesine eþdeðer olan daha açýk bir
sözdizimine eþittir. Bu, sadece iþaretçi aritmetiðidir, doðru sýrayla deðerlendirmeyi saðlamak için bazý ek parantezler ve adresindeki nesneyi
almak için bir implicit dereference vardýr.

Öncelikle, ptr'yi arr ile baþlatýrýz. arr bir baþlatýcý olarak kullanýldýðýnda, eleman 0'ýn adresini tutan bir iþaretçiye bozunur.
Yani ptr þimdi eleman 0'ýn adresini tutar. Sonraki adýmda, ptr[2]'yi yazdýrýrýz. ptr[2], *((ptr) + (2))'ye eþdeðerdir, bu da *(ptr + 2)'ye 
eþdeðerdir. ptr + 2, ptr'den iki nesne sonrasýndaki nesnenin adresini döndürür, bu da indeks 2 olan elemandýr. O adresin nesnesi daha sonra çaðýran
kiþiye döndürülür.

Bir baþka örneðe bakalým:

                #include <iostream>

                int main()
                {
                    const int arr[] { 3, 2, 1 };

                    // Öncelikle, dizi öðelerimizin adreslerini ve deðerlerini almak için alt dizinlemeyi kullanalým
                    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
                    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

                    // Þimdi aynýsýný iþaretçi aritmetiði kullanarak yapalým
                    std::cout << arr<< ' ' << (arr+ 1) << ' ' << (arr+ 2) << '\n';
                    std::cout << *arr<< ' ' << *(arr+ 1) << ' ' << *(arr+ 2) << '\n';

                    return 0;
                }

                Yazarýn makinesinde, bu yazdýrýldý:

                00AFFD80 00AFFD84 00AFFD88
                3 2 1
                00AFFD80 00AFFD84 00AFFD88
                3 2 1
ptr'nin 00AFFD80 adresini tuttuðunu, (ptr + 1)'in 4 byte sonraki bir adresi döndürdüðünü ve (ptr + 2)'nin 8 byte sonraki bir adresi döndürdüðünü
not edeceksiniz. Bu adresleri dereferans ederek bu adreslerdeki öðeleri alabiliriz.

Dizi öðeleri her zaman bellekte ardýþýk olduðu için, eðer ptr bir dizinin 0. öðesine iþaret eden bir iþaretçiyse, *(ptr + n) dizinin n. öðesini
döndürecektir. Bu, dizilerin 0 tabanlý yerine 1 tabanlý olmasýnýn temel nedenidir. Matematiði daha verimli hale getirir (çünkü derleyicinin her alt
dizinleme iþlemi sýrasýnda 1 çýkarmasýna gerek yoktur)!

Bir parantez açma...
--------------------
Bir iþaretçiyi alt dizinleme sýrasýnda derleyicinin ptr[n]'i *((ptr) + (n))'a dönüþtürdüðü için, bu, bir iþaretçiyi n[ptr] olarak da alt
dizinleyebileceðimiz anlamýna gelir! Derleyici bunu *((n) + (ptr))'a dönüþtürür, bu da *((ptr) + (n)) ile davranýþsal olarak aynýdýr.
Ancak bunu gerçekten yapmayýn, çünkü bu kafa karýþtýrýcýdýr.

Ýþaretçi aritmetiði ve alt dizinleme göreceli adreslerdir
---------------------------------------------------------
Dizi alt dizinlemesi hakkýnda ilk öðrendiðinizde, indeksin dizideki sabit bir öðeyi temsil ettiðini varsaymak doðaldýr: Ýndeks 0 her zaman ilk
öðedir, indeks 1 her zaman ikinci öðedir, vb... Bu bir yanýlsamadýr. Dizi indeksleri aslýnda göreceli pozisyonlardýr. Ýndeksler sadece sabit
görünür çünkü neredeyse her zaman dizinin baþýndan (0. öðe) indeksleriz!

Bir iþaretçi ptr verildiðinde, hem *(ptr + 1) hem de ptr[1] bellekteki sonraki nesneyi döndürür (iþaret edilen tipe dayalý). Sonraki,
mutlak bir terim deðildir, göreceli bir terimdir. Bu nedenle, eðer ptr 0. öðeye iþaret ediyorsa, o zaman hem *(ptr + 1) hem de ptr[1] 1. öðeyi
döndürecektir. Ama eðer ptr 3. öðeye iþaret ediyorsa, o zaman hem *(ptr + 1) hem de ptr[1] 4. öðeyi döndürecektir!

Aþaðýdaki örnek bunu gösterir:

                #include <array>
                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };
                    const int *ptr { arr }; // arr 0. öðeye iþaret eden bir iþaretçiye bozunur

                    // 0. öðeye iþaret ettiðimizi kanýtlayalým
                    std::cout << *ptr << ptr[0] << '\n'; // 99 yazdýrýr
                    // ptr[1]'in 1. öðe olduðunu kanýtlayalým
                    std::cout << *(ptr+1) << ptr[1] << '\n'; // 88 yazdýrýr

                    // Þimdi ptr'yi 3. öðeye iþaret etmek üzere ayarlayalým
                    ptr = &arr[3];

                    // 3. öðeye iþaret ettiðimizi kanýtlayalým
                    std::cout << *ptr << ptr[0] << '\n'; // 66 yazdýrýr
                    // ptr[1]'in 4. öðe olduðunu kanýtlayalým!
                    std::cout << *(ptr+1) << ptr[1] << '\n'; // 55 yazdýrýr

                    return 0;
                }
Ancak, ptr[1]'in her zaman 1. öðe olduðunu varsayamazsak programýmýzýn çok daha karýþýk olduðunu da not edeceksiniz. Bu nedenle, sadece dizinin 
baþýndan (0. öðe) indeksleme yaparken alt dizinlemeyi kullanmanýzý öneririz. Sadece göreceli konumlandýrma yaparken iþaretçi aritmetiðini kullanýn.

*** BEST -> Dizinin baþýndan (0. öðe) indeksleme yaparken alt dizinlemeyi tercih edin, böylece dizi indeksleri öðe ile ayný hizada olur.
            Belirli bir öðeden göreceli konumlandýrma yaparken iþaretçi aritmetiðini tercih edin.

Negatif Ýndisler
----------------
Son derste, (standart kütüphane konteyner sýnýflarýnýn aksine) bir C tarzý dizinin indeksinin ya bir unsigned integer ya da bir signed integer
olabileceðini belirttik. Bu, sadece kolaylýk için yapýlmadý - aslýnda bir C tarzý diziyi negatif bir alt dizinle indekslemek mümkün. Komik geliyor,
ama mantýklý.

*(ptr+1)'in bellekteki sonraki nesneyi döndürdüðünü yeni öðrendik. Ve ptr[1] bunu yapmak için sadece uygun bir sözdizimi.

Bu dersin baþýnda, *(ptr-1)'in bellekteki önceki nesneyi döndürdüðünü belirttik. Alt dizinin eþdeðerini tahmin etmek ister misiniz? Evet, ptr[-1].

                #include <array>
                #include <iostream>

                int main()
                {
                    const int arr[] { 9, 8, 7, 6, 5 };

                    // ptr'yi eleman 3'e iþaret edecek þekilde ayarla
                    const int* ptr { &arr[3] };

                    // ptr'nin eleman 3'e iþaret ettiðini kanýtla
                    std::cout << *ptr << ptr[0] << '\n'; // 66 yazdýrýr
                    // ptr[-1]'in eleman 2 olduðunu kanýtla!
                    std::cout << *(ptr-1) << ptr[-1] << '\n'; // 77 yazdýrýr

                    return 0;
                }

Pointer Aritmetiði Bir Diziyi Gezmek Ýçin Kullanýlabilir
--------------------------------------------------------
Pointer aritmetiðinin en yaygýn kullanýmlarýndan biri, açýkça indeksleme yapmadan bir C tarzý diziyi yinelemektir. Aþaðýdaki örnek, bunun nasýl
yapýldýðýný gösterir:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    const int* begin{ arr };                // begin baþlangýç elemanýna iþaret eder
                    const int* end{ arr + std::size(arr) }; // end bir-sonraki-son elemana iþaret eder

                    for (; begin != end; ++begin)           // begin'den baþlayarak (ama hariç) end'e kadar yinele
                    {
                        std::cout << *begin << ' ';     // döngü deðiþkenimizi dereferans yaparak mevcut elemaný al
                    }

                    return 0;
                }

Yukarýdaki örnekte, gezinmeye begin tarafýndan iþaret edilen elemanda (bu durumda dizi'nin 0. elemaný) baþlýyoruz. Henüz begin != end olduðundan,
döngü gövdesi çalýþýr. Döngü içinde, mevcut elemaný *begin ile eriþiriz, bu sadece bir pointer dereferansýdýr. Döngü gövdesinden sonra, ++begin 
yaparýz, bu pointer aritmetiði kullanarak begin'i sonraki elemana iþaret etmek üzere artýrýr. Begin != end olduðundan, döngü gövdesi tekrar çalýþýr.
Bu, begin != end yanlýþ olduðunda, yani begin == end olduðunda devam eder.

Dolayýsýyla, yukarýdaki þunu yazdýrýr:

9 7 5 3 1
End'in dizinin sonundan bir sonraki elemana ayarlandýðýný unutmayýn. End'in bu adresi tutmasý iyidir (end'i dereferans etmediðimiz sürece, çünkü o
adreste geçerli bir eleman yok). Bunu, matematiðimizi ve karþýlaþtýrmalarýmýzý olabildiðince basit hale getirmek için yapýyoruz (hiçbir yerde 1 
eklemeye veya çýkarmaya gerek yok).

Önceki derste 17.8 -- C tarzý dizi bozunmasý, dizi bozunmasýnýn fonksiyonlarý yeniden düzenlemeyi zorlaþtýrdýðýný belirttik çünkü belirli þeyler
bozunmayan dizilerle çalýþýr ancak bozunmuþ dizilerle çalýþmaz (std::size gibi). Bu þekilde bir dizi gezinmesi hakkýnda güzel bir þey,
yukarýdaki örneðin döngü kýsmýný olduðu gibi ayrý bir fonksiyona yeniden düzenleyebiliriz ve hala çalýþýr:

                #include <iostream>

                void printArray(const int* begin, const int* end)
                {
                    for (; begin != end; ++begin)   // begin'den baþlayarak (ama hariç) end'e kadar yinele
                    {
                        std::cout << *begin << ' '; // döngü deðiþkenimizi dereferans yaparak mevcut elemaný al
                    }

                    std::cout << '\n';
                }

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    const int* begin{ arr };                // begin baþlangýç elemanýna iþaret eder
                    const int* end{ arr + std::size(arr) }; // end bir-sonraki-son elemana iþaret eder

                    printArray(begin, end);

                    return 0;
                }
Bu program, diziyi açýkça fonksiyona geçirmediðimiz halde derlenir ve doðru sonucu üretir! Ve arr'ý geçirmediðimiz için printArray()'da bozunmuþ
bir arr ile uðraþmak zorunda deðiliz. Bunun yerine, begin ve end diziyi gezinmek için ihtiyaç duyduðumuz tüm bilgileri içerir.

Gelecekteki derslerde (iteratörleri ve algoritmalarý ele aldýðýmýzda), standart kütüphanenin, fonksiyonun hangi konteyner elemanlarý üzerinde
iþlem yapmasý gerektiðini tanýmlamak için bir baþlangýç ve bitiþ çifti kullanan birçok fonksiyon olduðunu göreceðiz.

C-stil diziler üzerinde range-based for döngülerinin pointer aritmetiði kullanýlarak uygulandýðý Aþaðýdaki range-based for döngüsünü düþünün:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    for (auto e : arr)         // `begin`den (`end` dahil olmamak üzere) yukarýya doðru yinele
                    {
                        std::cout << e << ' '; // döngü deðiþkenimizi dereference ederek mevcut elemaný alýn
                    }

                    return 0;
                }
Eðer range-based for döngülerinin belgelerine bakarsanýz, genellikle bunlarýn aþaðýdaki gibi uygulandýðýný göreceksiniz:

                {
                    auto __begin = begin-expr;
                    auto __end = end-expr;

                    for ( ; __begin != __end; ++__begin)
                    {
                        range-declaration = *__begin;
                        loop-statement;
                    }
                }

Önceki örnekteki range-based for döngüsünü bu uygulama ile deðiþtirelim:

                #include <iostream>

                int main()
                {
                    constexpr int arr[]{ 9, 7, 5, 3, 1 };

                    auto __begin = arr;                // arr bizim begin-expr'imizdir
                    auto __end = arr + std::size(arr); // arr + std::size(arr) bizim end-expr'imizdir

                    for ( ; __begin != __end; ++__begin)
                    {
                        auto e = *__begin;         // e bizim range-declaration'ýmýzdýr
                        std::cout << e << ' ';     // burasý bizim loop-statement'ýmýzdýr
                    }

                    return 0;
                }

Önceki bölümde yazdýðýmýz örneðe ne kadar benzediðine dikkat edin! Tek fark, *__begin'i e'ye atayýp e'yi kullanmamýz ve sadece *__begin'i doðrudan
kullanmamýzdýr!

17.10 — C-stil dizeleri ( stringler )
-------------------------------------
17.7 dersinde -- C-stil dizilere giriþ, C-stil dizileri tanýttýk, bu da bize ardýþýk bir eleman koleksiyonu tanýmlama imkaný verir:

                int testScore[30] {}; // 30 int'in bir dizisi, indeksler 0'dan 29'a

5.2 dersinde -- Literaller, bir dizeyi ardýþýk karakterlerin bir koleksiyonu olarak (örneðin “Merhaba, dünya!”) tanýmladýk ve C-stil dize 
literallerini tanýttýk. Ayrýca, C-stil dize literalinin “Merhaba, dünya!”'nýn const char[14] tipinde olduðunu (13 açýk karakter artý 1 gizli
null-terminator karakter) belirttik.

Eðer daha önce noktalarý birleþtirmemiþseniz, þimdi C-stil dizelerin sadece eleman tipi char veya const char olan C-stil diziler olduðu açýk olmalý!
C-stil dize literallerinin kodumuzda kullanýlmasý sorun olmasa da, C-stil dize nesneleri modern C++'da kullanýlmaz hale geldi çünkü onlarý 
kullanmak zor ve tehlikelidir (std::string ve std::string_view modern yerine geçenlerdir). Bununla birlikte, eski kodlarda hala C-stil dize 
nesnelerinin kullanýldýðýný görebilirsiniz ve onlarý hiç ele almamýþ olmamýz eksiklik olurdu.

Bu yüzden, bu derste, modern C++'daki C-stil dize nesneleri hakkýndaki en önemli noktalara bakacaðýz.

C-stil dizeleri tanýmlama
-------------------------
Bir C-stil dize deðiþkeni tanýmlamak için, sadece char (veya const char / constexpr char) türünde bir C-stil dizi deðiþkeni bildirin:

                char str1[8]{};                    // 8 char'ýn bir dizisi, indeksler 0'dan 7'ye

                const char str2[]{ "string" };     // 7 char'ýn bir dizisi, indeksler 0'dan 6'ya
                constexpr char str3[] { "hello" }; // 5 const char'ýn bir dizisi, indeksler 0'dan 4'e

Hatýrlayýn ki, implicit null-terminator için ekstra bir karaktere ihtiyacýmýz var. Bir baþlatýcý ile C-stil dizeleri tanýmlarken, 
dizinin uzunluðunu atlayýp derleyicinin uzunluðu hesaplamasýna izin vermenizi þiddetle öneririz. Bu þekilde, eðer baþlatýcý gelecekte deðiþirse,
uzunluðu güncellemeyi hatýrlamanýz gerekmez ve null-terminator tutmak için ekstra bir eleman eklemeyi unutma riski yoktur.

C tarzý dizeler bozulur
-----------------------
17.8 -- C tarzý dizi bozulmasý dersinde, C tarzý dizilerin çoðu durumda bir iþaretçiye bozulacaðýný tartýþtýk. C tarzý dizeler C tarzý diziler 
olduðu için onlar da bozulur. Ve bir C tarzý dize bir iþaretçiye bozulduðunda, dizenin uzunluðu (tip bilgisinde kodlanmýþ) kaybolur.

Bu uzunluk bilgisi kaybý, C tarzý dizelerin null-terminator olmasýnýn nedenidir. Dizenin uzunluðu, dizenin baþlangýcý ile null-terminator 
arasýndaki eleman sayýsýný sayarak (verimsiz bir þekilde) yeniden oluþturulabilir. Alternatif olarak, dize, baþlangýçtan itibaren yineleyerek ve
null-terminatora ulaþýncaya kadar geçilebilir.

Bir C tarzý dizeyi çýktý olarak verme
-------------------------------------
Bir C tarzý dizeyi çýktý olarak verirken, std::cout, null-terminatorla karþýlaþana kadar karakterleri çýktýlar. Bu null-terminator, dizenin sonunu
iþaretler, böylece bozulmuþ dizeler (uzunluk bilgilerini kaybetmiþ olanlar) hala yazdýrýlabilir.

                #include <iostream>

                void print(char ptr[])
                {
                    std::cout << ptr << '\n'; // dizeyi çýktý olarak ver
                }

                int main()
                {
                    char str[]{ "string" };
                    std::cout << str << '\n'; // stringi çýktý olarak ver

                    print(str);

                    return 0;
                }
Eðer null-terminatoru olmayan bir dizeyi yazdýrmayý denerseniz (örneðin, null-terminator bir þekilde üzerine yazýldýysa), sonuç tanýmsýz davranýþ
olacaktýr. Bu durumda en olasý sonuç, dizinin tüm karakterlerinin yazdýrýlmasý ve ardýndan bitiþik bellek slotlarýndaki her þeyi (bir karakter 
olarak yorumlanýr) yazdýrmaya devam etmesi olacaktýr, ta ki 0 içeren bir bellek baytýna rastlayana kadar (bu, bir null-terminator olarak yorumlanýr)

C tarzý dizeleri giriþ olarak alma
----------------------------------
Kullanýcýdan istediði kadar zar atmasýný ve atýlan sayýlarý boþluk býrakmadan girmesini istediðimiz bir durumu düþünün (örneðin, 524412616).
Kullanýcý kaç karakter girecek? Hiçbir fikrimiz yok.

Çünkü C tarzý dizeler sabit boyutlu dizilerdir, çözüm, muhtemelen hiç ihtiyaç duymayacaðýmýzdan daha büyük bir dizi tanýmlamaktýr:

                #include <iostream>

                int main()
                {
                    char rolls[255] {}; // 254 karakter + null-terminator tutacak kadar büyük bir dizi tanýmla
                    std::cout << "Enter your rolls: ";
                    std::cin >> rolls;
                    std::cout << "You entered: " << rolls << '\n';

                    return 0;
                }
C++20'den önce, std::cin >> rolls, mümkün olduðunca çok karakteri rolls'a çýkarýrdý (ilk öncü olmayan boþluða kadar dururdu).
Kullanýcýnýn 254'ten fazla karakter girmesini engelleyen hiçbir þey yok (ister istemeden, ister kötü niyetle). Ve eðer bu olursa,
kullanýcýnýn giriþi rolls dizisini taþýracak ve tanýmsýz davranýþ sonucu olacaktýr.

Anahtar nokta þudur ki; Dizi taþmasý veya tampon taþmasý, daha fazla verinin depolama alanýna kopyalandýðý durumlarda ortaya çýkan bir bilgisayar 
güvenlik sorunudur. Bu tür durumlarda, depolama alanýnýn hemen ötesindeki bellek üzerine yazýlýr, bu da tanýmsýz davranýþa yol açar. Kötü niyetli
aktörler, potansiyel olarak bu tür kusurlarý, programýn davranýþýný bazý avantajlý bir þekilde deðiþtirmeyi umarak, belleðin içeriðini üzerine 
yazmak için kullanabilirler.

C++20'de, operator>> deðiþtirildi ve yalnýzca bozulmamýþ C tarzý dizeleri giriþ olarak almak için çalýþýr. Bu, operator>>'nýn,
C tarzý dizenin uzunluðunun izin vereceði kadar çok karakteri çýkarmasýna olanak saðlar, taþmayý önler. Ancak bu ayný zamanda artýk operator>>'yi
bozulmuþ C tarzý dizelere giriþ olarak kullanamayacaðýnýz anlamýna gelir.

C tarzý dizeleri std::cin kullanarak okumanýn önerilen yolu aþaðýdaki gibidir:

                #include <iostream>
                #include <iterator> // std::size için

                int main()
                {
                    char rolls[255] {}; // 254 karakter + null-terminator tutacak kadar büyük bir dizi tanýmla
                    std::cout << "Enter your rolls: ";
                    std::cin.getline(rolls, std::size(rolls));
                    std::cout << "You entered: " << rolls << '\n';

                    return 0;
                }
`cin.getline()` çaðrýsý, 254 karaktere kadar (boþluklar dahil) `rolls` içine okur. Fazla karakterler atýlýr. `getline()` bir uzunluk alýr,
bu yüzden kabul edilecek maksimum karakter sayýsýný saðlayabiliriz. Bozunmayan bir diziyle, bu kolaydýr - dizinin uzunluðunu almak için 
`std::size()` kullanabiliriz. bozunmuþ bir diziyle, uzunluðu baþka bir þekilde belirlememiz gerekir. Ve yanlýþ bir uzunluk saðlarsak,
programýmýz hatalý çalýþabilir veya güvenlik sorunlarý olabilir.

Modern C++'da, kullanýcýdan gelen metni saklarken, `std::string` kullanmak daha güvenlidir, çünkü `std::string` gerektiði kadar çok karakteri
tutacak þekilde otomatik olarak ayarlanýr.

C Tarzý Dizeleri Deðiþtirme
---------------------------
Not etmek için önemli bir nokta, C tarzý dizelerin C tarzý dizilerle ayný kurallarý izlemesidir. Bu, diziyi oluþtururken baþlatabileceðiniz,
ancak sonrasýnda atama operatörünü kullanarak deðer atayamayacaðýnýz anlamýna gelir!

                char str[]{ "string" }; // tamam
                str = "rope";           // tamam deðil!

Bu, C tarzý dizeleri kullanmayý biraz zorlaþtýrýr. 
C tarzý dizeler diziler olduðundan, dizedeki tek tek karakterleri deðiþtirmek için `[]` operatörünü kullanabilirsiniz:

                #include <iostream>

                int main()
                {
                    char str[]{ "string" };
                    std::cout << str << '\n';
                    str[1] = 'p';
                    std::cout << str << '\n';

                    return 0;
                }

                Bu program þunu yazdýrýr:

                string
                spring

Bir C Tarzý Dizenin Uzunluðunu Alma
-----------------------------------
C tarzý dizeler C tarzý diziler olduðundan, dizinin uzunluðunu almak için `std::size()` (veya C++20'de `std::ssize()`) kullanabilirsiniz.
Burada iki uyarý var:

1 - Bu, bozunmuþ dizilerde çalýþmaz.
2 - Dizenin deðil, C tarzý dizinin gerçek uzunluðunu döndürür.

                #include <iostream>

                int main()
                {
                    char str[255]{ "string" }; // 6 karakter + null sonlandýrýcý
                    std::cout << "length = " << std::size(str) << '\n'; // length = 255 yazdýrýr

                    char *ptr { str };
                    std::cout << "length = " << std::size(ptr) << '\n'; // derleme hatasý

                    return 0;
                }
Alternatif bir çözüm, `<cstring>` baþlýk dosyasýnda bulunan `strlen()` fonksiyonunu kullanmaktýr. `strlen()` bozunmuþ dizilerde çalýþýr ve tutulan
dizenin uzunluðunu döndürür, null-terminator'u hariç tutar:

                #include <cstring> // std::strlen için
                #include <iostream>

                int main()
                {
                    char str[255]{ "string" }; // 6 karakter + null sonlandýrýcý
                    std::cout << "length = " << std::strlen(str) << '\n'; // length = 6 yazdýrýr

                    char *ptr { str };
                    std::cout << "length = " << std::strlen(ptr) << '\n';   // length = 6 yazdýrýr

                    return 0;
                }
Ancak, `std::strlen()` yavaþtýr, çünkü tüm diziyi geçer, null-terminatora ulaþana kadar karakterleri sayar.

Diðer C Tarzý Dizi Manipülasyon Fonksiyonlarý
---------------------------------------------
C tarzý dizeler C dilindeki birincil dizi türü olduðundan, C dili C tarzý dizeleri manipüle etmek için birçok fonksiyon saðlar. Bu fonksiyonlar,
`<cstring>` baþlýk dosyasýnýn bir parçasý olarak C++ tarafýndan miras alýnmýþtýr.

Ýþte eski kodda görebileceðiniz en yararlý birkaçý:

`strlen()` -- bir C tarzý dizenin uzunluðunu döndürür
`strcpy(), strncpy(), strcpy_s()` -- bir C tarzý dizeyi baþka biriyle üzerine yazar
`strcat(), strncat()` -- Bir C tarzý diziyi baþka birinin sonuna ekler
`strcmp(), strncmp()` -- Ýki C tarzý dizeyi karþýlaþtýrýr (eþitse 0 döndürür)
`strlen()` dýþýnda, bu türleri genellikle kaçýnmanýzý öneririz.

Non-const C Tarzý Dize Nesnelerinden Kaçýnýn
--------------------------------------------
Belirli, zorlayýcý bir nedeniniz olmadýkça, non-const C tarzý dizelerden kaçýnmak en iyisidir, çünkü bunlarla çalýþmak zordur ve
taþmaya eðilimlidirler, bu da tanýmsýz davranýþa neden olur (ve potansiyel güvenlik sorunlarýdýr).

Nadir durumlarda, C tarzý dizelerle veya sabit tampon boyutlarýyla (ör. bellek sýnýrlý cihazlar için) çalýþmanýz gerekiyorsa, bu amaç için
tasarlanmýþ iyi test edilmiþ 3. taraf sabit uzunluklu dize kütüphanesini kullanmanýzý öneririz.

*** BEST -> Non-const C tarzý dizE nesnelerinden kaçýnýn ve `std::string`'i tercih edin.

17.11 — C tarzý dize sembolik sabitleri
---------------------------------------
Önceki derste (17.10 -- C tarzý dizeler), C tarzý dize nesnelerini nasýl oluþturacaðýmýzý ve baþlatacaðýmýzý tartýþtýk:

                #include <iostream>

                int main()
                {
                    char name[]{ "Alex" }; // C tarzý dize
                    std::cout << name << '\n';

                    return 0;
                }
C++, C tarzý dize sembolik sabitlerini oluþturmak için iki farklý yol destekler:

                #include <iostream>

                int main()
                {
                    const char name[] { "Alex" };        // durum 1: C tarzý dize sabiti, C tarzý dize sabiti ile baþlatýlýr
                    const char* const color{ "Orange" }; // durum 2: C tarzý dize sabitine const iþaretçi

                    std::cout << name << ' ' << color << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                Alex Orange

Yukarýdaki iki yöntem ayný sonuçlarý üretirken, C++ bu konuda bellek tahsisini biraz farklý þekilde ele alýr.

Durum 1'de, "Alex" muhtemelen salt okunur bir bellekte bir yere konulur. Daha sonra program, bir C tarzý dizE için bellek ayýrýr ve uzunluðu 5'tir
(dört açýk karakter artý null-terminator) ve bu belleði "Alex" dizesi ile baþlatýr. Bu yüzden "Alex"in 2 kopyasýyla sonuçlanýrýz - biri global
bellekte bir yerde, diðeri ise `name` tarafýndan sahip olunan. `name` const olduðundan (ve asla deðiþtirilmeyecektir), bir kopya yapmak verimsizdir

Durum 2'de, derleyicinin bunu nasýl ele aldýðý uygulamaya baðlýdýr. Genellikle olan þey, derleyicinin "Orange" dizesini salt okunur bir bellekte
bir yere yerleþtirmesi ve daha sonra iþaretçiyi dizenin adresiyle baþlatmasýdýr.

Optimizasyon amaçlarý için, birden çok dize sabiti tek bir deðere birleþtirilebilir. Örneðin:

                const char* name1{ "Alex" };
                const char* name2{ "Alex" };

Bunlar, ayný deðere sahip iki farklý dize sabitidir. Bu sabitler sabit olduðundan, derleyici bu sabitleri tek bir paylaþýlan dize sabitine 
birleþtirerek bellekten tasarruf etmeyi seçebilir ve hem `name1` hem de `name2` ayný adrese iþaret eder.

Const C Tarzý Dizelerle Tür Çýkarýmý
------------------------------------
C tarzý bir dize sabiti kullanarak tür çýkarýmý oldukça basittir:

                auto s1{ "Alex" };  // tür, const char* olarak çýkarýlýr
                auto* s2{ "Alex" }; // tür, const char* olarak çýkarýlýr
                auto& s3{ "Alex" }; // tür, const char(&)[5] olarak çýkarýlýr

Farklý türlerdeki iþaretçileri `std::cout`'un nasýl ele aldýðý hakkýnda ilginç bir þey fark etmiþ olabilirsiniz.

Aþaðýdaki örneði düþünün:

                #include <iostream>

                int main()
                {
                    int narr[]{ 9, 7, 5, 3, 1 };
                    char carr[]{ "Merhaba!" };
                    const char* ptr{ "Alex" };

                    std::cout << narr << '\n'; // narr int* türüne bozunur
                    std::cout << carr << '\n'; // carr char* türüne bozunur
                    std::cout << ptr << '\n'; // ptr zaten char* türünde

                    return 0;
                }

                Yazarýn makinesinde, bu yazdý:

                003AF738
                Merhaba!
                Alex

Neden int dizisi bir adresi yazdýrdý, ancak karakter dizileri dize olarak yazdýrýldý?

Cevap, çýktý akýþlarýnýn (ör. `std::cout`) niyetiniz hakkýnda bazý varsayýmlar yapmasýdýr. Eðer ona bir char olmayan bir iþaretçi geçirirseniz,
sadece o iþaretçinin içeriðini (iþaretçinin tuttuðu adresi) yazdýrýr. Ancak, eðer ona `char*` veya `const char*` türünde bir nesne geçirirseniz,
bir dizeyi yazdýrmayý amaçladýðýnýzý varsayar. Sonuç olarak, iþaretçinin deðerini (bir adresi) yazdýrmak yerine, iþaret edilen dizeyi yazdýrýr!

Bu çoðu zaman istenen durumdur, ancak beklenmeyen sonuçlara yol açabilir. Aþaðýdaki durumu düþünün:

                #include <iostream>

                int main()
                {
                    char c{ 'Q' };
                    std::cout << &c;

                    return 0;
                }
Bu durumda, programcý `c` deðiþkeninin adresini yazdýrmayý amaçlýyor. Ancak, `&c`'nin türü `char*` olduðu için `std::cout` bunu bir dize olarak
yazdýrmayý dener! Ve `c` null ile sonlandýrýlmadýðý için, tanýmsýz bir davranýþ elde ederiz.

                Yazarýn makinesinde, bu yazdý:

                Q??????4;¿?A

Bunu neden yaptý? Ýlk olarak, `&c`'nin (türü `char*` olan) bir C tarzý dize olduðunu varsaydý. Yani 'Q'yu yazdýrdý ve devam etti. Bellekte bir
sonraki yerde bir sürü çöp vardý. Sonunda, 0 deðerini tutan bir belleðe rastladý, bunu bir null-terminator olarak yorumladý, bu yüzden durdu.
`c` deðiþkeninden sonraki bellekte ne olduðuna baðlý olarak gördüðünüz þey farklý olabilir.

Bu durum, gerçek hayatta biraz olasýdýr (çünkü gerçekten bellek adreslerini yazdýrmak istemeyeceksinizdir), ancak kaputun altýnda iþlerin nasýl
çalýþtýðýný ve programlarýn nasýl istemeden raydan çýkabileceðini gösterir.

Eðer gerçekten bir char iþaretçisinin adresini yazdýrmak istiyorsanýz, onu `const void*` türüne `static_cast` yapýn:

                #include <iostream>

                int main()
                {
                    const char* ptr{ "Alex" };

                    std::cout << ptr << '\n';                           // ptr'yi C tarzý dize olarak yazdýr
                    std::cout << static_cast<const void*>(ptr) << '\n'; // ptr tarafýndan tutulan adresi yazdýr

                    return 0;
                }
void*`'ý ders 19.5 -- Void iþaretçileri'nde ele alýyoruz. Burada kullanmak için nasýl çalýþtýðýný bilmeniz gerekmez.

C Tarzý Dize Sembolik Sabitleri Ýçin `std::string_view`'i Tercih Edin
---------------------------------------------------------------------
Modern C++'da C tarzý dize sembolik sabitlerini kullanmak için pek bir neden yoktur. Bunun yerine, genellikle ayný hýzda (hatta daha hýzlý) ve daha
tutarlý davranan `constexpr std::string_view` nesnelerini tercih edin.

*** BEST -> `constexpr std::string_view`'i tercih ederek C tarzý dize sembolik sabitlerinden kaçýnýn.

Çok Boyutlu C Tarzý Diziler
---------------------------
Örneðin, Tic-tac-toe gibi bir oyunu düþünün. Bu oyunun standart tahtasý 3x3'lük bir ýzgaradýr, oyuncular sýrayla 'X' ve 'O' sembollerini yerleþtirir
Üst üste üç sembol alan ilk oyuncu kazanýr.

Tahta verilerini 9 ayrý deðiþken olarak saklayabilirdiniz, ancak birden çok öðe örneðiniz olduðunda, bir dizi kullanmanýn daha iyi olduðunu
biliyoruz:

                int ttt[9]; // int'lerden oluþan bir C tarzý dizi (deðer 0 = boþ, 1 = oyuncu 1, 2 = oyuncu 2)

Bu, bellekte sýralý olarak düzenlenmiþ 9 elemanlý bir C tarzý dizi tanýmlar. Bu elemanlarý tek bir satýr deðerleri olarak düzenlenmiþ olarak hayal
edebiliriz:

// ttt[0] ttt[1] ttt[2] ttt[3] ttt[4] ttt[5] ttt[6] ttt[7] ttt[8]
Bir dizinin boyutu, bir öðeyi seçmek için gereken indeks sayýsýdýr. Yalnýzca tek bir boyutu içeren bir dizi, tek boyutlu dizi veya bir boyutlu dizi
olarak adlandýrýlýr (bazen 1d dizi olarak kýsaltýlýr). Yukarýdaki `ttt`, tek boyutlu bir dizi örneðidir, çünkü öðeler tek bir indeksle seçilebilir
(ör. `ttt[2]`).

Ancak, tek boyutlu dizimizin tic-tac-toe tahtasýna çok benzemediðini unutmayýn, çünkü tahta iki boyutta bulunur. Daha iyisini yapabiliriz.

Ýki Boyutlu Diziler
-------------------
Önceki derslerde, bir dizinin öðelerinin herhangi bir nesne türünde olabileceðini belirttik. Bu, bir dizinin öðe türünün baþka bir dizi olabileceði
anlamýna gelir! Böyle bir dizi tanýmlamak basittir:

                int a[3][5]; // int'lerden oluþan 5 öðeli dizinin 3 öðeli bir dizisi

Dizilerden oluþan bir dizi, iki boyutlu dizi olarak adlandýrýlýr (bazen 2d dizi olarak kýsaltýlýr) çünkü iki alt dizine sahiptir.

Ýki boyutlu bir diziyle, ilk (sol) alt dizinin satýrý seçtiðini ve ikinci (sað) alt dizinin sütunu seçtiðini düþünmek uygundur. Kavramsal olarak,
bu iki boyutlu diziyi þu þekilde düzenlenmiþ olarak hayal edebiliriz:

                // col 0    col 1    col 2    col 3    col 4
                // a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
                // a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
                // a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2
Bir iki boyutlu dizinin öðelerine eriþmek için, sadece iki alt dizi kullanýrýz:

                a[2][3] = 7; // a[row][col], where row = 2 and col = 3

Bu nedenle, bir Tic-tac-toe tahtasý için, bir 2d dizi þu þekilde tanýmlayabiliriz:

                int ttt[3][3];

Ve þimdi, satýr ve sütun indekslerini kullanarak kolayca manipüle edebileceðimiz 3x3'lük bir öðe ýzgarasýna sahibiz!

Çok Boyutlu Diziler
-------------------
Bir boyuttan fazla olan dizilere çok boyutlu diziler denir. C++ hatta 2'den fazla boyutlu çok boyutlu dizileri bile destekler:

                int threedee[4][4][4]; // 4x4x4'lük bir dizi (4 int'lerden oluþan 4 dizinin bir dizisi)

Örneðin, Minecraft'taki arazi 16x16x16 bloklara (chunk sections olarak adlandýrýlýr) bölünmüþtür. 3'ten daha yüksek boyutlara sahip diziler
desteklenir, ancak nadirdir.

2d Dizilerin Bellekte Nasýl Düzenlendiði
----------------------------------------
Bellek doðrusal (1 boyutlu) olduðu için, çok boyutlu diziler aslýnda bir dizi öðeler olarak saklanýr. 
Aþaðýdaki dizinin bellekte nasýl saklandýðýna dair iki olasý yol vardýr:

                // col 0   col 1   col 2   col 3   col 4
                // [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
                // [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
                // [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
C++ satýr büyük sýrasýný kullanýr ( row-major order ), burada öðeler bellekte satýr satýr sýralý olarak yerleþtirilir, 
soldan saða, yukarýdan aþaðýya sýralanýr:

                [0][0] [0][1] [0][2] [0][3] [0][4] [1][0] [1][1] [1][2] [1][3] [1][4] [2][0] [2][1] [2][2] [2][3] [2][4]
Bazý diðer diller (örneðin Fortran) sütun büyük sýrasýný kullanýr, öðeler bellekte sütun sütun sýralý olarak yerleþtirilir, yukarýdan aþaðýya,
soldan saða:

                [0][0] [1][0] [2][0] [0][1] [1][1] [2][1] [0][2] [1][2] [2][2] [0][3] [1][3] [2][3] [0][4] [1][4] [2][4]
C++'da, bir dizi baþlatýlýrken, öðeler satýr büyük sýrasýnda baþlatýlýr. Ve bir diziyi geçerken, öðeleri bellekte düzenlendikleri sýrayla eriþmek
en verimli olanýdýr.

Ýki Boyutlu Dizileri Baþlatma
-----------------------------
Bir iki boyutlu diziyi baþlatmak için, her bir sayý setinin bir satýrý temsil ettiði iç içe geçmiþ parantezler kullanmak en kolay olanýdýr:

                int array[3][5]
                {
                  { 1, 2, 3, 4, 5 },     // satýr 0
                  { 6, 7, 8, 9, 10 },    // satýr 1
                  { 11, 12, 13, 14, 15 } // satýr 2
                };

Bazý derleyiciler iç parantezleri atmanýza izin verebilir, ancak okunabilirlik amaçlarý için yine de onlarý eklemenizi þiddetle öneririz.
Ýç parantezler kullanýlýrken, eksik baþlatýcýlar deðer baþlatýlýr:

                int array[3][5]
                {
                  { 1, 2 },          // satýr 0 = 1, 2, 0, 0, 0
                  { 6, 7, 8 },       // satýr 1 = 6, 7, 8, 0, 0
                  { 11, 12, 13, 14 } // satýr 2 = 11, 12, 13, 14, 0
                };

Baþlatýlmýþ bir çok boyutlu dizi, sol taraftaki uzunluk belirtimini (yalnýzca) atlayabilir:

                int array[][5]
                {
                  { 1, 2, 3, 4, 5 },
                  { 6, 7, 8, 9, 10 },
                  { 11, 12, 13, 14, 15 }
                };

Bu tür durumlarda, derleyici baþlangýçtaki sayýlarýn sayýsýndan sol taraftaki uzunluðun ne olduðunu hesaplamak için matematiði yapabilir.
Sol taraftaki olmayan boyutlarý atlamak izin verilmez:

                int array[][]
                {
                  { 1, 2, 3, 4 },
                  { 5, 6, 7, 8 }
                };

Normal diziler gibi, çok boyutlu diziler de aþaðýdaki gibi 0'a baþlatýlabilir:

                int array[3][5] {};

Ýki Boyutlu Diziler ve Döngüler
-------------------------------
Tek boyutlu bir diziyle, dizideki tüm öðeleri yinelemek için tek bir döngü kullanabiliriz:

                #include <iostream>

                int main()
                {
                    int arr[] { 1, 2, 3, 4, 5 };

                    // indeksli for döngüsü
                    for (std::size_t i{0}; i < std::size(arr); ++i)
                        std::cout << arr[i] << ' ';

                    std::cout << '\n';

                    // aralýk tabanlý for döngüsü
                    for (auto e: arr)
                        std::cout << e << ' ';

                    std::cout << '\n';

                    return 0;
                }
Ýki boyutlu bir diziyle, birini satýrý seçmek ve diðerini sütunu seçmek için iki döngüye ihtiyacýmýz vardýr. Ve iki döngüyle, hangi döngünün
dýþ döngü ve hangisinin iç döngü olacaðýný belirlememiz gerekiyor. Öðelere, bellekte düzenlendikleri sýrayla eriþmek en verimli olanýdýr.
C++ satýr büyük sýrasýný kullandýðýndan, satýr seçici dýþ döngü olmalý ve sütun seçici iç döngü olmalýdýr.

                #include <iostream>

                int main()
                {
                    int arr[3][4] {
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }};

                    // indeksli çift for döngüsü
                    for (std::size_t row{0}; row < std::size(arr); ++row) // std::size(arr) satýr sayýsýný döndürür
                    {
                        for (std::size_t col{0}; col < std::size(arr[0]); ++col) // std::size(arr[0]) sütun sayýsýný döndürür
                            std::cout << arr[row][col] << ' ';

                        std::cout << '\n';
                    }

                    // aralýk tabanlý çift for döngüsü
                    for (const auto& arow: arr)   // her dizi satýrýný al
                    {
                        for (const auto& e: arow) // satýrdaki her öðeyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }

                    return 0;
                }


Ýki Boyutlu Dizi Örneði
-----------------------
Bir iki boyutlu dizinin pratik bir örneðine bakalým:

                #include <iostream>

                int main()
                {
                    constexpr int numRows{ 10 };
                    constexpr int numCols{ 10 };

                    // 10x10'luk bir dizi tanýmla
                    int product[numRows][numCols]{};

                    // Bir çarpým tablosu hesapla
                    // 0 ile çarpma her zaman 0 olduðu için satýr ve sütun 0'ý hesaplamamýza gerek yok
                    for (std::size_t row{ 1 }; row < numRows; ++row)
                    {
                        for (std::size_t col{ 1 }; col < numCols; ++col)
                        {
                            product[row][col] = static_cast<int>(row * col);
                        }
                     }

                    for (std::size_t row{ 1 }; row < numRows; ++row)
                    {
                        for (std::size_t col{ 1 }; col < numCols; ++col)
                        {
                            std::cout << product[row][col] << '\t';
                        }

                        std::cout << '\n';
                     }


                    return 0;
                }

Bu program, 1 ve 9 (dahil) arasýndaki tüm deðerler için bir çarpým tablosunu hesaplar ve yazdýrýr. Tabloyu yazdýrýrken, for döngülerinin 0 
yerine 1'den baþladýðýný unutmayýn. Bu, sadece bir dizi 0 olan 0 sütunu ve 0 satýrýný yazdýrmamak içindir! Ýþte çýktý:

                1    2    3    4    5    6    7    8    9
                2    4    6    8    10   12   14   16   18
                3    6    9    12   15   18   21   24   27
                4    8    12   16   20   24   28   32   36
                5    10   15   20   25   30   35   40   45
                6    12   18   24   30   36   42   48   54
                7    14   21   28   35   42   49   56   63
                8    16   24   32   40   48   56   64   72
                9    18   27   36   45   54   63   72   81

Kartezyen Koordinatlar vs Dizi Ýndeksleri
-----------------------------------------
Geometride, bir nesnenin konumunu tanýmlamak için genellikle Kartezyen koordinat sistemi kullanýlýr. Ýki boyutta, "x" ve "y" olarak adlandýrýlan
iki koordinat ekseni vardýr. "x" yatay eksendir ve "y" dikey eksendir.

Kartezyen Koordinat Sistemi Diyagramý
-------------------------------------
Ýki boyutta, bir nesnenin Kartezyen konumu, bir { x, y } çifti olarak tanýmlanabilir, burada x-koordinat ve y-koordinat, bir nesnenin 
x-ekseninin saðýna ve y-ekseninin üzerine ne kadar uzakta olduðunu belirten deðerlerdir. Bazen y-ekseni ters çevrilir (yani y-koordinat,
y-ekseninin ne kadar altýnda olduðunu tanýmlar).

Þimdi C++'daki 2d dizi düzenimize bir göz atalým:

                // col 0   col 1   col 2   col 3   col 4
                // [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
                // [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
                // [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2

Bu da bir öðenin konumunun [row][col] olarak tanýmlanabileceði iki boyutlu bir koordinat sistemidir (burada col-ekseni ters çevrilmiþtir).
Her bir koordinat sistemi baðýmsýz olarak anlamak oldukça kolayken, Kartezyen { x, y }'dan Dizi indekslerine [row][col] dönüþtürmek biraz karþý 
sezgiseldir. Ana fikir, bir Kartezyen sistemindeki x-koordinatýn, dizi indeksleme sisteminde hangi sütunun seçildiðini tanýmlamasýdýr. 
Tersine, y-koordinat hangi satýrýn seçildiðini tanýmlar. Bu nedenle, bir { x, y } Kartezyen koordinatý, bir [y][x] dizi koordinatýna dönüþür, 
bu da beklentimizin tersidir!

Bu, þu þekilde görünen 2d döngülere yol açar:

                for (std::size_t y{0}; y < std::size(arr); ++y) // dýþ döngü satýrlar / y
                {
                    for (std::size_t x{0}; x < std::size(arr[0]); ++x) // iç döngü sütunlar / x
                        std::cout << arr[y][x] << ' '; // önce y (satýr) ile indeksle, sonra x (sütun)
                }

Bu durumda, diziyi a[y][x] olarak indeksleriz, bu da muhtemelen beklediðiniz alfabetik sýralamanýn tersidir.

17.13 — Çok boyutlu std::array
------------------------------
Önceki derste (17.12 -- Çok Boyutlu C Tarzý Diziler), C tarzý çok boyutlu dizileri tartýþtýk:

                // C tarzý 2d dizi
                int arr[3][4] {
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 }};

Ama bildiðiniz gibi, genellikle C tarzý dizilerden kaçýnmak istiyoruz (eðer global verileri saklamak için kullanýlmýyorsa).
Bu derste, çok boyutlu dizilerin `std::array` ile nasýl çalýþtýðýna bakacaðýz.

Standart Kütüphanede Çok Boyutlu Dizi Sýnýfý Yok
------------------------------------------------
`std::array`'in tek boyutlu bir dizi olarak uygulandýðýný unutmayýn. Yani ilk sorduðunuz soru, "çok boyutlu diziler için bir standart kütüphane
sýnýfý var mý?" olmalý. Ve cevap... hayýr. Çok kötü. Womp womp. 

Ýki Boyutlu `std::array`
------------------------
`std::array`'in iki boyutlu bir dizi oluþturmanýn kanonik yolu, þablon tür argümanýnýn baþka bir `std::array` olduðu bir `std::array` oluþturmaktýr.
Bu, þuna benzer bir þeye yol açar:

                std::array<std::array<int, 4>, 3> arr {{  // çift paranteze dikkat edin
                    { 1, 2, 3, 4 },
                    { 5, 6, 7, 8 },
                    { 9, 10, 11, 12 }}};

Bu hakkýnda birkaç "ilginç" þey not etmek var:

*- Çok boyutlu bir `std::array` baþlatýrken, çift parantez kullanmamýz gerekiyor (nedenini ders 17.4 -- sýnýf türlerinin `std::array`'i ve brace 
   elision'da tartýþýyoruz).
*- Sözdizimi aðýr ve okumasý zor.
*- Þablonlarýn iç içe geçme þekli nedeniyle, dizi boyutlarý deðiþtirilir. 4 öðeli 3 satýrlý bir dizi istiyoruz, bu yüzden `arr[3][4]` doðaldýr. 
   `std::array<std::array<int, 4>, 3>` tersine çevrilmiþtir.

Bir iki boyutlu `std::array` öðesini indekslemek, bir iki boyutlu C tarzý dizi indekslemesi gibi çalýþýr:

                std::cout << arr[1][2]; // satýr 1, sütun 2'deki öðeyi yazdýr

Ayrýca bir iki boyutlu `std::array`'i, bir boyutlu bir `std::array` gibi bir fonksiyona da geçirebiliriz:

                #include <array>
                #include <iostream>

                template <typename T, std::size_t Row, std::size_t Col>
                void printArray(std::array<std::array<T, Col>, Row> &arr)
                {
                    for (const auto& arow: arr)   // her dizi satýrýný al
                    {
                        for (const auto& e: arow) // satýrdaki her öðeyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }
                }

                int main()
                {
                    std::array<std::array<int, 4>, 3>  arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    printArray(arr);

                    return 0;
                }
Iðrenç. Ve bu, bir iki boyutlu `std::array` için. Üç boyutlu veya daha yüksek bir `std::array` daha da aðýrdýr!

Çok Boyutlu `std::array`'i Kullanmayý Kolaylaþtýrmak için Takma Ad Þablonlarý
-----------------------------------------------------------------------------
Ders 10.7 -- Typedefs ve type aliases'de, takma adlarý tanýttýk ve takma adlarýn bir kullanýmýnýn karmaþýk türleri daha basit hale getirmek
olduðunu belirttik. Ancak, normal bir tür takma adýyla, tüm þablon argümanlarýný açýkça belirtmemiz gerekir. örneðin:

                using Array2dint34 = std::array<std::array<int, 4>, 3>;

Bu, bir 3×4 iki boyutlu `std::array` of int istediðimiz her yerde `Array2dint34` kullanmamýza olanak saðlar. Ancak, kullanmak istediðimiz her 
öðe türü ve boyut kombinasyonu için böyle bir takma ada ihtiyacýmýz olacaðýný unutmayýn!

Bu, bir tür takma adý için öðe türünü, satýr uzunluðunu ve sütun uzunluðunu þablon argümanlarý olarak belirtmemize izin veren bir takma ad þablonu
kullanmanýn mükemmel bir yeridir!

                // Ýki boyutlu bir std::array için bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

Daha sonra, bir 3×4 iki boyutlu `std::array` of int istediðimiz her yerde `Array2d<int, 3, 4>` kullanabiliriz. Bu çok daha iyi!

Ýþte tam bir örnek:

                #include <array>
                #include <iostream>

                // Ýki boyutlu bir std::array için bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

                // Array2d'yi bir fonksiyon parametresi olarak kullanýrken, þablon parametrelerini yeniden belirtmemiz gerekiyor
                template <typename T, std::size_t Row, std::size_t Col>
                void printArray(Array2d<T, Row, Col> &arr)
                {
                    for (const auto& arow: arr)   // her dizi satýrýný al
                    {
                        for (const auto& e: arow) // satýrdaki her öðeyi al
                            std::cout << e << ' ';

                        std::cout << '\n';
                    }
                }

                int main()
                {
                    // 3 satýr ve 4 sütunlu bir int'in iki boyutlu dizisini tanýmla
                    Array2d<int, 3, 4> arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    printArray(arr);

                    return 0;
                }

Ne kadar daha özlü ve kullanýmý kolay olduðuna dikkat edin! Takma ad þablonumuz hakkýnda güzel bir þey, þablon parametrelerimizi istediðimiz
sýrayla tanýmlayabileceðimizdir. `std::array` önce öðe türünü ve ardýndan boyutu belirttiðinden, bu düzene baðlý kalýrýz. Ancak `Row` veya `Col`'u
ilk tanýmlama esnekliðine sahibiz. C tarzý dizi tanýmlarý satýr öncelikli tanýmlandýðýndan, takma ad þablonumuzu `Row`'dan önce `Col` ile tanýmlarýz

Bu yöntem, daha yüksek boyutlu `std::array`'a da güzel bir þekilde ölçeklenir:

                // Üç boyutlu bir std::array için bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
                using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;

Ýki Boyutlu Bir Dizinin Boyutsal Uzunluklarýný Alma
---------------------------------------------------
Bir iki boyutlu dizinin uzunluðunu almak biraz sezgisel deðildir.

                #include <array>
                #include <iostream>

                // Ýki boyutlu bir std::array için bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using Array2d = std::array<std::array<T, Col>, Row>;

                int main()
                {
                    // 3 satýr ve 4 sütunlu bir int'in iki boyutlu dizisini tanýmla
                    Array2d<int, 3, 4> arr {{
                        { 1, 2, 3, 4 },
                        { 5, 6, 7, 8 },
                        { 9, 10, 11, 12 }}};

                    std::cout << "Rows: " << arr.size() << '\n';    // ilk boyutun (satýrlar) uzunluðunu al
                    std::cout << "Cols: " << arr[0].size() << '\n'; // ikinci boyutun (sütunlar) uzunluðunu al

                    return 0;
                }
Birinci boyutun uzunluðunu almak için, dizimizde `size()`'ý çaðýrmamýz yeterlidir. Peki ya ikinci boyut? Ýkinci boyutun uzunluðunu almak için, 
o boyuttan bir öðeye ihtiyacýmýz var. Bu nedenle, alt diziyi almak için önce `arr[0]`'ý çaðýrýrýz (öðe 0'ýn var olduðu garantilidir),
ardýndan onun üzerinde `size()`'ý çaðýrýrýz.

3 boyutlu bir dizinin üçüncü boyutunun uzunluðunu almak için, `arr[0][0].size()`'ý çaðýrabiliriz.

Ýki Boyutlu Bir Diziyi Düzleþtirme
----------------------------------
Ýki veya daha fazla boyutlu diziler bazý zorluklarla karþýlaþýr:

- Tanýmlamalarý ve çalýþmalarý daha ayrýntýlýdýr.
- Ýlk boyuttan daha büyük boyutlarýn uzunluðunu almak garip.
- Üzerlerinde yinelemek giderek daha zor hale gelir (her boyut için bir döngü daha gerektirir).

Çok boyutlu dizilerle çalýþmayý kolaylaþtýrmanýn bir yaklaþýmý, onlarý düzleþtirmektir. Bir diziyi düzleþtirmek, bir dizinin boyutsallýðýný azaltma
sürecidir (genellikle tek bir boyuta indirgenir).

Örneðin, `Row` satýr ve `Col` sütunlu olan iki boyutlu bir dizi oluþturmak yerine, `Row * Col` öðesi olan tek boyutlu bir dizi oluþturabiliriz.
Bu, tek bir boyut kullanarak bize ayný miktarda depolama alaný saðlar.

Ancak, tek boyutlu dizimizin yalnýzca tek bir boyutu olduðu için, onunla çok boyutlu bir dizi olarak çalýþamayýz. Bunu çözmek için, çok boyutlu bir
diziyi taklit eden bir arayüz saðlayabiliriz. Bu arayüz, iki boyutlu koordinatlarý kabul eder ve ardýndan bunlarý tek boyutlu dizide benzersiz bir 
konuma eþler.

C++11 veya daha yeni sürümlerde çalýþan bu yaklaþýmýn bir örneði aþaðýdadýr:

                #include <array>
                #include <iostream>
                #include <functional>

                // Ýki boyut kullanarak tek boyutlu bir std::array tanýmlamamýza izin veren bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using ArrayFlat2d = std::array<T, Row * Col>;

                // ArrayFlat2d ile iki boyutta çalýþmamýza izin veren bir deðiþtirilebilir görünüm
                // Bu bir görünüm olduðu için, görüntülenen ArrayFlat2d'nin kapsamda kalmasý gerekir
                template <typename T, std::size_t Row, std::size_t Col>
                class ArrayView2d
                {
                private:
                    // m_arr'yi bir ArrayFlat2d referansý yapma eðiliminde olabilirsiniz,
                    // ancak bu, görünümün kopyalanabilir olmamasýný saðlar çünkü referanslar yeniden oturtulamaz.
                    // std::reference_wrapper kullanmak bize referans semantiði ve kopyalanabilirliði saðlar.
                    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

                public:
                    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr)
                        : m_arr { arr }
                    {}

                    // Tek alt dizin aracýlýðýyla öðeyi al (operator[] kullanarak)
                    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
                    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

                    // 2d alt dizin aracýlýðýyla öðeyi al (operator() kullanarak, çünkü operator[] C++23'ten önce birden çok boyutu desteklemiyor)
                    T& operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
                    const T& operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

                    // C++23'te, bunlarý yorumdan çýkarabilirsiniz çünkü çok boyutlu operator[] desteklenir
                //    T& operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
                //    const T& operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

                    int rows() const { return static_cast<int>(Row); }
                    int cols() const { return static_cast<int>(Col); }
                    int length() const { return static_cast<int>(Row * Col); }
                };

                int main()
                {
                    // Bir int'in tek boyutlu std::array'ini tanýmla (3 satýr ve 4 sütun ile)
                    ArrayFlat2d<int, 3, 4> arr {
                        1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12 };

                    // Tek boyutlu dizimize iki boyutlu bir görünüm tanýmla
                    ArrayView2d<int, 3, 4> arrView { arr };

                    // dizi boyutlarýný yazdýr
                    std::cout << "Rows: " << arrView.rows() << '\n';
                    std::cout << "Cols: " << arrView.cols() << '\n';

                    // tek boyut kullanarak diziyi yazdýr
                    for (int i=0; i < arrView.length(); ++i)
                        std::cout << arrView[i] << ' ';

                    std::cout << '\n';

                    // iki boyut kullanarak diziyi yazdýr
                    for (int row=0; row < arrView.rows(); ++row)
                    {
                        for (int col=0; col < arrView.cols(); ++col)
                            std::cout << arrView(row, col) << ' ';
                        std::cout << '\n';
                    }

                    std::cout << '\n';

                    return 0;
                }

                Bu, aþaðýdakileri yazdýrýr:

                Rows: 3
                Cols: 4
                1 2 3 4 5 6 7 8 9 10 11 12
                1 2 3 4
                5 6 7 8
                9 10 11 12

C++23'ten önce `operator[]` yalnýzca tek bir alt dizin kabul edebilir, bu yüzden iki alternatif yaklaþým vardýr:

- Bunun yerine `operator()` kullanýn, bu birden çok alt dizin kabul eder. Bu, tek indeks indekslemesi için `[]` ve çok boyutlu indeksleme için `()`
  kullanmanýza olanak saðlar. Yukarýda bu yaklaþýmý seçtik.

- `operator[]`'nin bir alt görünüm döndürmesine izin verin, böylece `operator[]`'yi zincirleyebilirsiniz. Bu daha karmaþýk ve daha yüksek boyutlara
   iyi ölçeklenmez.

C++23'te, `operator[]` birden çok alt dizin kabul etmek üzere geniþletildi, bu yüzden hem tek hem de çoklu alt dizinleri iþlemek için onu aþýrý 
yükleyebilirsiniz (birden çok alt dizin için `operator()` kullanmak yerine).

`std::mdspan` C++23
-------------------
C++23'te tanýtýlan `std::mdspan`, sürekli bir öðe dizisi için çok boyutlu bir dizi arayüzü saðlayan bir deðiþtirilebilir görünümdür.
Deðiþtirilebilir görünüm derken, bir `std::mdspan`'in sadece salt okunur bir görünüm (`std::string_view` gibi) olmadýðýný kastediyoruz 
temel öðe dizisi sabit deðilse, bu öðeler deðiþtirilebilir.

Aþaðýdaki örnek, önceki örnekle ayný çýktýyý yazdýrýr, ancak kendi özel görünümümüz yerine `std::mdspan` kullanýr:

                #include <array>
                #include <iostream>
                #include <mdspan>

                // Ýki boyut kullanarak tek boyutlu bir std::array tanýmlamamýza izin veren bir takma ad þablonu
                template <typename T, std::size_t Row, std::size_t Col>
                using ArrayFlat2d = std::array<T, Row * Col>;

                int main()
                {
                    // Bir int'in tek boyutlu std::array'ini tanýmla (3 satýr ve 4 sütun ile)
                    ArrayFlat2d<int, 3, 4> arr {
                        1, 2, 3, 4,
                        5, 6, 7, 8,
                        9, 10, 11, 12 };

                    // Tek boyutlu dizimize iki boyutlu bir span tanýmla
                    // std::mdspan'a bir öðe dizisine iþaretçi geçirmemiz gerekiyor
                    // bunu, bir C tarzý dizinin bozunmasý veya std::array veya std::vector'ün data() üye fonksiyonunu kullanarak yapabiliriz
                    std::mdspan mdView { arr.data(), 3, 4 };

                    // dizi boyutlarýný yazdýr
                    // std::mdspan bunlara extents der
                    std::size_t rows { mdView.extents().extent(0) };
                    std::size_t cols { mdView.extents().extent(1) };
                    std::cout << "Rows: " << rows << '\n';
                    std::cout << "Cols: " << cols << '\n';

                    // tek boyutlu olarak diziyi yazdýr
                    // data_handle() üye, bize bir öðe dizisine iþaretçi verir
                    // daha sonra bunu indeksleyebiliriz
                    for (std::size_t i=0; i < mdView.size(); ++i)
                        std::cout << mdView.data_handle()[i] << ' ';
                    std::cout << '\n';

                    // iki boyutlu olarak diziyi yazdýr
                    // Öðelere eriþmek için çok boyutlu [] kullanýrýz
                    for (std::size_t row=0; row < rows; ++row)
                    {
                        for (std::size_t col=0; col < cols; ++col)
                            std::cout << mdView[row, col] << ' ';
                        std::cout << '\n';
                    }
                    std::cout << '\n';

                    return 0;
                }

Bu oldukça basit olmalý, ancak not etmeye deðer birkaç þey var:

- `std::mdspan` bize istediðimiz kadar boyutla bir görünüm tanýmlama imkaný verir.
- `std::mdspan`'ýn yapýcýsýna ilk parametre olarak bir dizi verisi iþaretçisi olmalýdýr. Bu, bir C tarzý dizinin bozunmasý olabilir veya 
  `std::array` veya `std::vector`'ün `data()` üye fonksiyonunu kullanarak bu veriyi alabiliriz.
- Bir `std::mdspan`'i tek boyutlu olarak indekslemek için, dizinin verisine iþaretçiyi almalýyýz, bunu `data_handle()` üye fonksiyonunu kullanarak
  yapabiliriz. Daha sonra bunu alt dizinleyebiliriz.
- C++23'te, `operator[]` birden çok indeks kabul eder, bu yüzden indeksimiz olarak `[row][col]` yerine `[row, col]` kullanýrýz.
- C++26, `std::array` ve `std::mdspan`'i sahip olan çok boyutlu bir diziye dönüþtüren `std::mdarray`'i içerecek!

**Bölüm Ýncelemesi**
--------------------
Sabit boyutlu diziler (veya sabit uzunluklu diziler), dizinin uzunluðunun örnekleme noktasýnda bilinmesini ve bu uzunluðun daha sonra
deðiþtirilememesini gerektirir. C tarzý diziler ve `std::array` her ikisi de sabit boyutlu dizilerdir. Dinamik diziler çalýþma zamanýnda
yeniden boyutlandýrýlabilir. `std::vector` bir dinamik dizidir.

Bir `std::array`'in uzunluðu bir sabit ifade olmalýdýr. Çoðu zaman, uzunluk için saðlanan deðer bir tam sayý literali, `constexpr` deðiþkeni 
veya kapsamsýz bir numaratör olacaktýr.

`std::array` bir topluluktur. Bu, hiçbir yapýcýya sahip olmadýðý ve bunun yerine toplu baþlatma kullanýlarak baþlatýldýðý anlamýna gelir.

`std::array`'inizi mümkün olduðunda `constexpr` olarak tanýmlayýn. `std::array`'iniz `constexpr` deðilse, bunun yerine bir `std::vector` 
kullanmayý düþünün.

Derleyicinin bir `std::array`'in türünü ve uzunluðunu baþlatýcýlarýndan çýkarmasýný saðlamak için sýnýf þablon argüman çýkarýmýný (CTAD) kullanýn.

`std::array`, aþaðýdaki gibi bir þablon yapý olarak uygulanmýþtýr:

                template<typename T, std::size_t N> // N, bir tür olmayan þablon parametresidir
                struct array;

Dizi uzunluðunu temsil eden tür olmayan þablon parametresi (`N`) `std::size_t` türündedir.

Bir `std::array`'in uzunluðunu almak için:

- Bir `std::array` nesnesinden uzunluðunu `size()` üye fonksiyonunu kullanarak sorabiliriz (bu, uzunluðu `unsigned size_type` olarak döndürür).
- C++17'de, `std::size()` adlý üye olmayan fonksiyonu kullanabiliriz (bu, `std::array` için sadece `size()` üye fonksiyonunu çaðýrýr, 
  böylece uzunluðu `unsigned size_type` olarak döndürür).
- C++20'de, uzunluðu büyük bir imzalý integral tür olarak döndüren `std::ssize()` adlý üye olmayan fonksiyonu kullanabiliriz
  (genellikle `std::ptrdiff_t`).
- Bu üç fonksiyonun tümü, uzunluðu bir `constexpr` deðeri olarak döndürecektir, ancak bir `std::array` referans olarak geçirildiðinde çaðrýldýðýnda
  bu geçerli olmayacaktýr. Bu kusur, P2280 tarafýndan C++23'te ele alýnmýþtýr.

Bir `std::array`'i indekslemek için:

- Alt dizin operatörünü (`operator[]`) kullanýn. Bu durumda hiçbir sýnýrlama kontrolü yapýlmaz ve geçersiz bir indeks geçirilirse tanýmsýz
  davranýþa neden olur.
- Çalýþma zamanýnda sýnýrlama kontrolü yapan `at()` üye fonksiyonunu kullanýn. Genellikle indekslemeden önce sýnýrlama kontrolü yapmak istediðimiz
  veya derleme zamaný sýnýrlama kontrolü yapmak istediðimiz için bu fonksiyonu kullanmamanýzý öneririz.
- Derleme zamaný sýnýrlama kontrolü yapan ve indeksi tür olmayan bir þablon argümaný olarak alan `std::get()` fonksiyon þablonunu kullanýn.
- Farklý öðe türleri ve uzunluklara sahip bir `std::array`'i, þablon parametre bildirimi `template <typename T, std::size_t N>` olan bir fonksiyon
  þablonuna geçirebilirsiniz. Veya C++20'de, `template <typename T, auto N>` kullanýn.

Bir `std::array`'i deðer olarak döndürmek, diziyi ve tüm öðeleri kopyalar, ancak bu, dizi küçük ve öðelerin kopyalanmasý pahalý deðilse kabul
edilebilir olabilir. Bazý baðlamlarda, bunun yerine bir çýkýþ parametresi kullanmak daha iyi bir seçenek olabilir.

Bir `std::array`'i bir struct, sýnýf veya dizi ile baþlatýrken ve her baþlatýcýyla öðe türünü saðlamazsanýz, derleyicinin neyi baþlatacaðýný doðru
bir þekilde yorumlamasý için ekstra bir çift paranteze ihtiyacýnýz olacaktýr. Bu, toplu baþlatmanýn bir kalýntýsýdýr ve diðer standart kütüphane 
konteyner türleri (liste yapýlandýrýcýlarý kullananlar) bu durumlarda çift parantez gerektirmez.

C++'daki topluluklar, birden çok parantezin atlanabileceði durumlarý belirleyen brace elision adlý bir kavramý destekler. Genellikle, bir 
`std::array`'i skalar (tek) deðerlerle veya türün her öðe ile açýkça adlandýrýldýðý sýnýf türleri veya dizilerle baþlatýrken parantezleri
atlayabilirsiniz.

Referanslarýn bir dizisi olamaz, ancak `std::reference_wrapper`'ýn bir dizisi olabilir, bu da deðiþtirilebilir bir lvalue referansý gibi davranýr.

`std::reference_wrapper` hakkýnda not edilmesi gereken birkaç þey var:

- `Operator=` bir `std::reference_wrapper`'ý yeniden oturtur (referans verilen nesneyi deðiþtirir).
- `std::reference_wrapper<T>` otomatik olarak `T&`'ye dönüþtürülür.
- `get()` üye fonksiyonu, bir `T&` almak için kullanýlabilir. Bu, referans verilen nesnenin deðerini güncellemek istediðimizde yararlýdýr.
- `std::ref()` ve `std::cref()` fonksiyonlarý, `std::reference_wrapper` ve `const std::reference_wrapper` sarýlý nesneleri oluþturmak için
   kýsayollar olarak saðlandý.

Mümkün olduðunda, CTAD kullanarak bir `constexpr std::array`'in doðru sayýda baþlatýcýya sahip olduðunu garantilemek için `static_assert` kullanýn.

C tarzý diziler, C dilinden miras alýndý ve C++'ýn çekirdek dilinin bir parçasýdýr. Çekirdek dilin bir parçasý olduklarý için, C tarzý dizilerin
kendi özel bildirim sözdizimleri vardýr. Bir C tarzý dizi bildiriminde, bir nesnenin bir C tarzý dizi olduðunu derleyiciye bildirmek için köþeli
parantezler (`[]`) kullanýrýz. Köþeli parantezlerin içinde, dizinin uzunluðunu isteðe baðlý olarak saðlayabiliriz, bu `std::size_t` türünde bir 
integral deðerdir ve derleyiciye dizide kaç öðenin olduðunu söyler. Bir C tarzý dizinin uzunluðu bir sabit ifade olmalýdýr.

C tarzý diziler topluluktur, bu da onlarýn toplu baþlatma kullanýlarak baþlatýlabileceði anlamýna gelir. Bir C tarzý dizinin tüm öðelerini bir 
baþlatýcý listesi kullanarak baþlatýrken, uzunluðu atlamak ve derleyicinin dizinin uzunluðunu hesaplamasýna izin vermek tercih edilir.

C tarzý diziler `operator[]` aracýlýðýyla indekslenebilir. Bir C tarzý dizinin indeksi, bir imzalý veya imzasýz tam sayý veya kapsamsýz bir
numarasyon olabilir. Bu, C tarzý dizilerin, standart kütüphane konteyner sýnýflarýnýn sahip olduðu tüm iþaret dönüþümü indeksleme sorunlarýna 
tabi olmadýðý anlamýna gelir!

C tarzý diziler `const` veya `constexpr` olabilir.

Bir C tarzý dizinin uzunluðunu almak için:

- C++17'de, uzunluðu `unsigned std::size_t` olarak döndüren `std::size()` adlý üye olmayan fonksiyonu kullanabiliriz.
- C++20'de, uzunluðu genellikle `std::ptrdiff_t` olan büyük bir imzalý integral tür olarak döndüren `std::ssize()` adlý üye olmayan fonksiyonu 
  kullanabiliriz.
- Çoðu durumda, bir C tarzý dizi bir ifadede kullanýldýðýnda, dizi otomatik olarak öðe türüne bir iþaretçiye dönüþtürülür ve ilk öðenin (indeks 0)
  adresiyle baþlatýlýr. Bu, halk arasýnda dizi bozunmasý (veya kýsaca bozunma) olarak adlandýrýlýr.

Ýþaretçi aritmetiði, belirli tam sayý aritmetik operatörlerini (toplama, çýkarma, artýrma veya azaltma) bir iþaretçiye uygulama özelliðidir ve yeni
bir bellek adresi üretir. Belirli bir iþaretçi `ptr` verildiðinde, `ptr + 1` bellekteki sonraki nesnenin adresini döndürür
(iþaret edilen türe dayanýr).

- Dizinin baþýndan (öðe 0) indeksleme yaparken alt dizinlemeyi kullanýn, böylece dizi indeksleri öðe ile ayný hizada olur.
- Belirli bir öðeden göreceli konumlandýrma yaparken iþaretçi aritmetiði kullanýn.

C tarzý dizeler, öðe türü `char` veya `const char` olan C tarzý dizilerdir. Bu nedenle, C tarzý dizeler bozunur.

Bir dizinin boyutu, bir öðeyi seçmek için gereken indeks sayýsýdýr.

Yalnýzca tek bir boyut içeren bir diziye tek boyutlu dizi veya bir boyutlu dizi (bazen 1d dizi olarak kýsaltýlýr) denir.
Dizilerin bir dizisi, iki alt dizine sahip olduðu için iki boyutlu dizi (bazen 2d dizi olarak kýsaltýlýr) olarak adlandýrýlýr. 
Birden fazla boyuta sahip dizilere çok boyutlu diziler denir. Bir diziyi düzleþtirmek, bir dizinin boyutsallýðýný azaltma sürecidir
(genellikle tek bir boyuta indirgenir).

C++23'te, `std::mdspan` sürekli bir öðe dizisi için çok boyutlu bir dizi arayüzü saðlayan bir görünümdür.
*/