#include <iostream>

int main()
{
    return 0;
}
/*
13.5 — Structlara, memberlara ve member seçimine giriþ
------------------------------------------------------
Programlama sýrasýnda birçok durumda, ilgi alanýný temsil etmek için birden fazla deðiþkene ihtiyaç duyarýz.
Önceki bölümün giriþinde (12.1 -- Bileþik veri türlerine giriþ) tartýþtýðýmýz gibi, bir kesirin payý ve paydasý tek bir 
matematiksel nesneye baðlýdýr.

Alternatif olarak, bir þirketteki çalýþanlar hakkýnda bilgi saklamamýz gereken bir program yazmak isteyelim. Çalýþanýn adý,unvaný,
yaþý, çalýþan kimliði, yönetici kimliði, ücreti, doðum günü, iþe baþlama tarihi vb. özellikleri takip etmekle ilgilenebiliriz...

Eðer bu tüm bilgileri takip etmek için baðýmsýz deðiþkenler kullanýrsak, bu þuna benzer bir þey olabilir:

 
                    std::string name;
                    std::string title;
                    int age;
                    int id;
                    int managerId;
                    double wage;
                    int birthdayYear;
                    int birthdayMonth;
                    int birthdayDay;
                    int hireYear;
                    int hireMonth;
                    int hireDay;
 
Ancak, bu yaklaþýmla bir dizi sorun var. Ýlk olarak, bu deðiþkenlerin gerçekten iliþkili olup olmadýðý hemen belli olmaz 
(yorumlarý okumanýz veya onlarýn baðlamda nasýl kullanýldýðýný gözlemlemeniz gerekir). Ýkinci olarak, þimdi yönetilmesi gereken
12 deðiþken var. Eðer bu çalýþaný bir fonksiyona geçmek istersek, 12 argümaný (ve doðru sýrayla) geçmemiz gerekir, bu da fonksiyon
prototiplerimizi ve fonksiyon çaðrýlarýmýzý karýþtýrýr. Ve bir fonksiyon sadece tek bir deðer döndürebilir, o zaman bir fonksiyon 
nasýl bir çalýþaný döndürür?

Ve birden fazla çalýþana ihtiyacýmýz olursa, her ek çalýþan için 12 daha fazla deðiþken tanýmlamamýz gerekir (her biri benzersiz
bir isim gerektirir)! Bu açýkça hiç ölçeklenmiyor. Gerçekten ihtiyacýmýz olan þey, tüm bu ilgili veri parçalarýný bir araya
getirmenin bir yoludur, böylece onlarý daha kolay yönetebiliriz.

Neyse ki, C++ bu tür zorluklarý çözmek için tasarlanmýþ iki bileþik türle birlikte gelir: Structlar (þimdi tanýtacaðýmýz) ve
sýnýflar (yakýnda keþfedeceðimiz). Bir Struct (structure kýsaltmasý) bir program tanýmlý veri türüdür (13.1 -- Program tanýmlý
(kullanýcý tanýmlý) türlerine giriþ) ve bize birden çok deðiþkeni tek bir türde bir araya getirme olanaðý saðlar. Yakýnda
göreceðiniz gibi, bu, ilgili deðiþken setlerinin yönetimini çok daha basit hale getirir!

Structlarý Tanýmlama
--------------------
Structlar bir program tanýmlý tür olduðu için, onu kullanmaya baþlamadan önce derleyiciye Struct türümüzün nasýl göründüðünü
öncelikle söylememiz gerekir. Ýþte basitleþtirilmiþ bir çalýþan için bir Struct tanýmýnýn bir örneði:

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };
 
Struct anahtar kelimesi, bir Struct tanýmladýðýmýzý derleyiciye bildirmek için kullanýlýr, bunu Employee olarak adlandýrdýk 
(çünkü program tanýmlý türler genellikle büyük harfle baþlayan isimlerle adlandýrýlýr).

Sonra, bir çift süslü parantez içinde, her Employee nesnesinin içereceði deðiþkenleri tanýmlarýz. Bu örnekte, oluþturduðumuz her 
Employee 3 deðiþkene sahip olacak: bir int id, bir int age ve bir double wage. Struct'ýn bir parçasý olan deðiþkenlere veri
memberlarý (veya member deðiþkenler) denir.

Ýpucu

Günlük dilde, bir member (üye) bir gruba ait bir bireydir. Örneðin, basketbol takýmýnýn bir member'i olabilirsiniz ve kýz 
kardeþiniz koro member'i olabilir.

C++'da, bir member bir Struct'a (veya sýnýfa) ait bir deðiþken, fonksiyon veya türdür. Tüm memberlar, Struct (veya sýnýf) tanýmý 
içinde bildirilmelidir.

Gelecekteki derslerde member terimini çok kullanacaðýz, bu yüzden ne anlama geldiðini unutmayýn.

Normal deðiþkenleri deðer baþlatmak için boþ bir set süslü parantez kullanýrýz, her member deðiþkenin ardýndaki boþ süslü 
parantezler, bir Employee oluþturulduðunda Employee içindeki member deðiþkenlerin deðer baþlatýldýðýndan emin olur.
Son olarak, tip tanýmýný bir noktalý virgülle bitiriyoruz.

Bir hatýrlatma olarak, Employee sadece bir tip tanýmýdýr - bu noktada aslýnda hiçbir nesne oluþturulmaz.

Struct nesneleri tanýmlama
--------------------------
Employee tipini kullanmak için, sadece Employee tipinde bir deðiþken tanýmlarýz:
 
                Employee joe {}; // Employee tipidir, joe deðiþken adýdýr
 
Bu, joe adýnda bir Employee tipinde deðiþken tanýmlar. Kod çalýþtýrýldýðýnda, 3 veri member'ini içeren bir Employee nesnesi 
örneklendirilir. Boþ süslü parantezler, nesnemizin deðerle baþlatýlmasýný saðlar.
Diðer her tipte olduðu gibi, ayný struct tipinde birden çok deðiþken tanýmlamak mümkündür:

                Employee joe {}; // Joe için bir Employee struct oluþtur
                Employee frank {}; // Frank için bir Employee struct oluþtur
 
memberlare eriþim
-----------------
Aþaðýdaki örneði düþünün:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};

                    return 0;
                }
 
Yukarýdaki örnekte, joe adý tüm struct nesnesine (member deðiþkenleri içerir) atýfta bulunur. Belirli bir member deðiþkenine
eriþmek için, struct deðiþken adý ve member adý arasýnda member seçim operatörünü (operator.) kullanýrýz. Örneðin, 
Joe'nun yaþ member'ine eriþmek için joe.age kullanýrýz.

Struct member deðiþkenleri normal deðiþkenler gibi çalýþýr, bu yüzden atama, aritmetik, karþýlaþtýrma vb. normal iþlemleri yapmak
mümkündür...

                #include <iostream>

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};

                    joe.age = 32;  // member seçim operatörünü (.) kullanarak joe deðiþkeninin age member'ini seç

                    std::cout << joe.age << '\n'; // joe'nun yaþýný yazdýr

                    return 0;
                }
                Bu, þunu yazdýrýr:
                32

Structlarýn en büyük avantajlarýndan biri, her struct deðiþkeni için yalnýzca bir yeni ad oluþturmamýz gerektiðidir
(member adlarý struct tipi tanýmýnýn bir parçasý olarak sabittir). Aþaðýdaki örnekte, iki Employee nesnesi örneklendiriyoruz: 
joe ve frank.
 
                #include <iostream>

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe {};
                    joe.id = 14;
                    joe.age = 32;
                    joe.wage = 60000.0;

                    Employee frank {};
                    frank.id = 15;
                    frank.age = 28;
                    frank.wage = 45000.0;

                    int totalAge { joe.age + frank.age };

                    if (joe.wage > frank.wage)
                        std::cout << "Joe, Frank'ten daha fazla kazanýyor\n";
                    else if (joe.wage < frank.wage)
                        std::cout << "Joe, Frank'ten daha az kazanýyor\n";
                    else
                        std::cout << "Joe ve Frank ayný miktarda kazanýyor\n";

                    // Frank terfi etti
                    frank.wage += 5000.0;

                    // Bugün Joe'nun doðum günü
                    ++joe.age; // Joe'nun yaþýný 1 artýrmak için ön artýrýmý kullan

                    return 0;
                }
 
Yukarýdaki örnekte, hangi member deðiþkenlerin Joe'ya ait olduðunu ve hangilerinin Frank'e ait olduðunu anlamak çok kolaydýr. Bu,
bireysel deðiþkenlerden çok daha yüksek bir organizasyon seviyesi saðlar. Ayrýca, Joe'nun ve Frank'in memberlarýnin ayný adlara 
sahip olmasý, ayný struct tipinde birden çok deðiþkeniniz olduðunda tutarlýlýk saðlar.

13.6 — Struct Toplu Baþlatma
----------------------------
Önceki derste (13.5 -- Struct'lara, üyelere ve üye seçimine giriþ), struct'larý nasýl tanýmlayacaðýmýzý, struct nesnelerini nasýl 
oluþturacaðýmýzý ve üyelerine nasýl eriþeceðimizi konuþtuk. Bu derste, struct'larýn nasýl baþlatýldýðýný tartýþacaðýz.

Veri üyeleri varsayýlan olarak baþlatýlmaz
------------------------------------------
Normal deðiþkenler gibi, veri üyeleri de varsayýlan olarak baþlatýlmaz. Aþaðýdaki struct'ý düþünün:

                #include <iostream>

                struct Employee
                {
                    int id; // not: burada bir baþlatýcý yok
                    int age;
                    double wage;
                };

                int main()
                {
                    Employee joe; // not: burada da bir baþlatýcý yok
                    std::cout << joe.id << '\n';

                    return 0;
                }
 
Herhangi bir baþlatýcý saðlamadýðýmýz için, joe oluþturulduðunda, joe.id, joe.age ve joe.wage tümü baþlatýlmamýþ olacak. 
Daha sonra joe.id'nin deðerini yazdýrmaya çalýþtýðýmýzda tanýmsýz bir davranýþ elde ederiz.

Ancak, bir struct'ý nasýl baþlatacaðýnýzý göstermeden önce, kýsa bir sapma yapalým.

Bir topluluk (aggregate) nedir?
--------------------------------
Genel programlamada, bir topluluk veri türü (ayný zamanda bir topluluk olarak da adlandýrýlýr), birden çok veri üyesi içerebilen
herhangi bir türdür. Topluluklarýn bazý türleri, üyelerin farklý türlerde olmasýna izin verir (ör. struct'lar), diðerleri ise tüm
üyelerin tek bir türde olmasýný gerektirir (ör. diziler).

C++'da, bir topluluðun tanýmý daha dar ve oldukça daha karmaþýktýr.

Not: Bu eðitim serisinde, "toplu" (veya "toplu olmayan") terimini kullandýðýmýzda, C++ tanýmý olan toplu anlamýna gelecektir.
Kesin tanýmý bir kenara býrakarak, bu noktada anlamanýz gereken önemli þey, yalnýzca veri üyelerine sahip struct'larýn topluluklar
olduðudur.

Bir struct'ýn toplu baþlatýlmasý
--------------------------------
Normal bir deðiþken yalnýzca tek bir deðer tutabilir, bu yüzden yalnýzca tek bir baþlatýcý saðlamamýz gerekir:

                int x { 5 };
 
Ancak, bir struct birden çok üyeye sahip olabilir:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };
 
Bir nesneyi bir struct türüyle tanýmladýðýmýzda, baþlatma zamanýnda birden çok üyeyi baþlatmanýn bir yoluna ihtiyacýmýz vardýr:

                Employee joe; // joe.id, joe.age ve joe.wage'yi nasýl baþlatýrýz?
 
Topluluklar, üyeleri doðrudan baþlatmamýza izin veren toplu baþlatma adý verilen bir baþlatma formunu kullanýr. Bunu yapmak için,
bir baþlatýcý listesi saðlarýz, bu sadece virgülle ayrýlmýþ deðerlerin süslü parantezlerle listesidir.

Toplu baþlatmanýn 2 ana formu vardýr:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee frank = { 1, 32, 60000.0 }; // süslü liste kullanarak kopya-liste baþlatma
                    Employee joe { 2, 28, 45000.0 };     // süslü liste kullanarak liste baþlatma (tercih edilir)

                    return 0;
                }
 
Bu baþlatma formlarýnýn her biri, bir üye baþýna baþlatma yapar, bu da struct'daki her üyenin bildirildiði sýrayla baþlatýldýðý
anlamýna gelir. Bu nedenle, Employee joe { 2, 28, 45000.0 }; önce joe.id'yi 2 deðeriyle baþlatýr, sonra joe.age'i 28 deðeriyle
ve son olarak joe.wage'i 45000.0 deðeriyle baþlatýr.

*** BEST -> Topluluklarý baþlatýrken (kopya olmayan) süslü liste formunu tercih edin.

C++20'de, parantezli bir deðer listesi kullanarak (bazý) topluluklarý da baþlatabiliriz:
 
                Employee robert ( 3, 45, 62500.0 );  // parantezli liste kullanarak doðrudan baþlatma (C++20)
 
Bu son formu mümkün olduðunca kaçýnmanýzý öneririz, çünkü þu anda brace elision kullanan topluluklarla (özellikle std::array) 
çalýþmamaktadýr.

Bir baþlatýcý listesinde eksik baþlatýcýlar
-------------------------------------------
Bir topluluk baþlatýldýðýnda, ancak baþlatma deðerlerinin sayýsý üye sayýsýndan az olduðunda, tüm kalan üyeler deðerle baþlatýlýr.
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 2, 28 }; // joe.wage 0.0 olarak deðerle baþlatýlýr

                    return 0;
                }
 
Yukarýdaki örnekte, joe.id deðeri 2 ile baþlatýlýr, joe.age deðeri 28 ile baþlatýlýr ve joe.wage için açýk bir baþlatýcý 
verilmediði için 0.0 olarak deðerle baþlatýlýr.
Bu, bir struct'ýn tüm üyelerini deðerle baþlatmak için boþ bir baþlatma listesi kullanabileceðimiz anlamýna gelir:
 
                Employee joe {}; // tüm üyeleri deðerle baþlat
 
Const struct'lar
----------------
Bir struct tipindeki deðiþkenler const (veya constexpr) olabilir ve tüm const deðiþkenler gibi, bunlarýn baþlatýlmasý gerekir.
 
                struct Rectangle
                {
                    double length {};
                    double width {};
                };

                int main()
                {
                    const Rectangle unit { 1.0, 1.0 };
                    const Rectangle zero { }; // tüm üyeleri deðerle baþlat

                    return 0;
                }
 
Belirlenmiþ baþlatýcýlar C++20
------------------------------
Bir struct'ý bir deðer listesinden baþlatýrken, baþlatýcýlar bildirme sýrasýna göre üyelere uygulanýr.

                struct Foo
                {
                    int a {};
                    int c {};
                };

                int main()
                {
                    Foo f { 1, 3 }; // f.a = 1, f.c = 3

                    return 0;
                }
 
Þimdi, bu struct tanýmýný güncelleyip son üye olmayan yeni bir üye eklerseniz ne olacaðýný düþünün:
 
                struct Foo
                {
                    int a {};
                    int b {}; // yeni eklendi
                    int c {};
                };

                int main()
                {
                    Foo f { 1, 3 }; // þimdi, f.a = 1, f.b = 3, f.c = 0

                    return 0;
                }
 
Þimdi tüm baþlatma deðerleriniz kaydý ve daha kötüsü, derleyici bunu bir hata olarak algýlamayabilir (sonuçta, sözdizimi hala 
geçerlidir). Bunu önlemeye yardýmcý olmak için, C++20, struct üyelerini baþlatmanýn yeni bir yolunu ekler: belirlenmiþ
baþlatýcýlar. Belirlenmiþ baþlatýcýlar, hangi baþlatma deðerlerinin hangi üyelere eþleþtiðini açýkça tanýmlamanýza olanak saðlar.
Üyeler, liste veya kopya baþlatma kullanýlarak baþlatýlabilir ve struct'ta bildirildikleri ayný sýrayla baþlatýlmalýdýr, 
aksi takdirde bir uyarý veya hata oluþur. Bir baþlatýcý belirlenmeyen üyeler deðerle baþlatýlýr.
 
                struct Foo
                {
                    int a{ };
                    int b{ };
                    int c{ };
                };

                int main()
                {
                    Foo f1{ .a{ 1 }, .c{ 3 } }; // tamam: f1.a = 1, f1.b = 0 (deðerle baþlatýldý), f1.c = 3
                    Foo f2{ .a = 1, .c = 3 };   // tamam: f2.a = 1, f2.b = 0 (deðerle baþlatýldý), f2.c = 3
                    Foo f3{ .b{ 2 }, .a{ 1 } }; // hata: baþlatma sýrasý, struct'taki bildirim sýrasýna uymuyor

                    return 0;
                }
 
Clang kullanýcýlarý için

Tek deðerlerin belirlenmiþ baþlatýcýlarýný süslü parantezler kullanarak yaparken, Clang hatalý bir þekilde "skaler baþlatýcý
etrafýnda süslü parantezler" uyarýsý verir. Umarým bu yakýnda düzeltilecektir. Belirlenmiþ baþlatýcýlar güzeldir çünkü belirli bir
düzeyde kendi belgelerini saðlarlar ve baþlatma deðerlerinizin sýrasýný yanlýþlýkla karýþtýrmanýzý önlerler. Ancak, belirlenmiþ
baþlatýcýlar ayný zamanda baþlatýcý listesini önemli ölçüde karmaþýklaþtýrýr, bu yüzden þu anda bunlarýn kullanýlmasýný en iyi 
uygulama olarak önermiyoruz.

Ayrýca, belirlenmiþ baþlatýcýlarýn bir topluluðun her yerinde baþlatýldýðýnda tutarlý bir þekilde kullanýldýðýna dair bir zorlama
olmadýðý için, baþlatýcýlarýn kaymasýný önlemek için mevcut bir topluluk tanýmýnýn ortasýna yeni üyeler eklemekten kaçýnmak iyi
bir fikirdir.

*** BEST -> Bir topluluða yeni bir üye eklerken, diðer üyelerin baþlatýcýlarý kaymazsa, onu taným listesinin altýna eklemek
            en güvenlisidir.

Bir baþlatýcý listesiyle atama
------------------------------
Önceki derste gösterildiði gibi, struct'larýn üyelerine tek tek deðer atayabiliriz:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };

                    joe.age  = 33;      // Joe'nun doðum günü oldu
                    joe.wage = 66000.0; // ve bir zam aldý

                    return 0;
                }
 
Tek üyeler için bu iyi, ancak birçok üyeyi güncellemek istediðimizde harika deðil. Bir structý bir baþlatýcý listesiyle baþlatmaya
benzer þekilde, bir baþlatýcý listesi kullanarak Structlarýna da deðer atayabilirsiniz (bu, üye bazýnda atamayý gerçekleþtirir):

                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };
                    joe = { joe.id, 33, 66000.0 }; // Joe'nun bir doðum günü oldu ve zam aldý

                    return 0;
                }
 
joe.id'yi deðiþtirmek istemediðimiz için, üye bazýnda atamanýn joe.id'yi joe.id'ye atayabilmesi için listemizde bir yer tutucu 
olarak joe.id için mevcut deðeri saðlamamýz gerektiðini unutmayýn. Bu biraz çirkin.

C++20 ile belirlenmiþ baþlatýcýlarla atama
------------------------------------------
Belirlenmiþ baþlatýcýlar da bir liste atamasýnda kullanýlabilir:
 
                struct Employee
                {
                    int id {};
                    int age {};
                    double wage {};
                };

                int main()
                {
                    Employee joe { 1, 32, 60000.0 };
                    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe'nun bir doðum günü oldu ve zam aldý

                    return 0;
                }
 
Bu tür bir atamada belirlenmemiþ herhangi bir üye, deðer baþlatma için kullanýlacak deðeri alýr. Eðer joe.id için belirlenmiþ bir
baþlatýcý belirtmemiþ olsaydýk, joe.id deðeri 0 olarak atanýrdý.

Ayný türden baþka bir structyla bir structý baþlatma
-------------------------------------------------
Bir struct, ayný türden baþka bir struct kullanýlarak da baþlatýlabilir:
 
                #include <iostream>

                struct Foo
                {
                    int a{};
                    int b{};
                    int c{};
                };

                int main()
                {
                    Foo foo { 1, 2, 3 };

                    Foo x = foo; // kopya baþlatma
                    Foo y(foo);  // doðrudan baþlatma
                    Foo z {foo}; // liste baþlatma

                    std::cout << x.a << ' ' << y.b << ' ' << z.c << '\n';

                    return 0;
                }
                Çýktýsý:
                1 2 3
Bunun, tanýdýk olduðumuz standart baþlatma formlarýný (kopya, doðrudan veya liste baþlatma) kullanýrken toplu baþlatma yerine 
kullandýðýný unutmayýn. Bu, bir structý, ayný türden bir struct döndüren bir fonksiyonun dönüþ deðeriyle baþlatýrken en sýk görülür.

13.7 — Üye Ýlk Deðer Atama
--------------------------
Bir struct (veya sýnýf) tipi tanýmladýðýmýzda, tip tanýmýnýn bir parçasý olarak her üye için varsayýlan bir ilk deðer saðlayabiliriz.
Bu iþleme statik olmayan üye ilk deðer atama denir ve ilk deðer, varsayýlan üye ilk deðeri olarak adlandýrýlýr.Örneðin:
                struct BirSey
                {
                    int x;       // ilk deðer yok (kötü)
                    int y {};    // varsayýlan olarak deðer-atamasý structlýyor
                    int z { 2 }; // açýkça belirtilen varsayýlan deðer
                };

                int main()
                {
                    BirSey s1; // s1.x atanmamýþ, s1.y 0, ve s1.z 2

                    return 0;
                }
 
Yukarýdaki BirSey tanýmýnda, x'in varsayýlan bir deðeri yok, y varsayýlan olarak deðer-atamasý structlýyor ve z'nin varsayýlan 
deðeri 2. Bu varsayýlan üye ilk deðerler, kullanýcý BirSey tipinde bir nesne oluþtururken açýk bir ilk deðer saðlamazsa
kullanýlacaktýr.

s1 nesnemizin bir ilk deðeri yok, bu yüzden s1'in üyeleri varsayýlan deðerlerine atanýr. s1.x'in varsayýlan bir ilk deðeri yok,
bu yüzden atanmamýþ kalýr. s1.y varsayýlan olarak deðer-atamasý structlýyor, bu yüzden deðeri 0 alýr. Ve s1.z deðeri 2 ile atanýr.
s1.z için açýk bir ilk deðer saðlamamýþ olmamýza raðmen, saðlanan varsayýlan üye ilk deðeri nedeniyle sýfýr olmayan bir deðere 
atanýr.

Anahtar Bilgi
-------------
Varsayýlan üye ilk deðerlerini (veya daha sonra ele alacaðýmýz diðer mekanizmalarý) kullanarak, Structlar ve sýnýflar hiçbir açýk
ilk deðer saðlanmadýðýnda bile kendilerini baþlatabilir!

Ýleri Seviye Okuyucular Ýçin

Açýk ilk deðerler, varsayýlan deðerlere üstün gelir

Bir liste ilk deðer atamasýndaki açýk deðerler, her zaman varsayýlan üye ilk deðerlerine üstün gelir.

                struct BirSey
                {
                    int x;       // varsayýlan ilk deðer yok (kötü)
                    int y {};    // varsayýlan olarak deðer-atamasý structlýyor
                    int z { 2 }; // açýkça belirtilen varsayýlan deðer
                };

                int main()
                {
                    BirSey s2 { 5, 6, 7 }; // s2.x, s2.y, ve s2.z için açýk ilk deðerler kullanýlýr (varsayýlan deðerler
                                           // kullanýlmaz)

                    return 0;
                }
 
Yukarýdaki durumda, s2'nin her üyesi için açýk ilk deðerler var, bu yüzden varsayýlan üye ilk deðerleri hiç kullanýlmaz. Bu, 
s2.x, s2.y ve s2.z'nin sýrasýyla 5, 6 ve 7 deðerlerine atanacaðý anlamýna gelir.

Varsayýlan deðerlerin olduðu durumda, ilk deðer atama listesinde eksik ilk deðerler
-----------------------------------------------------------------------------------
Önceki derste (13.6 -- Struct ýn toplu ilk deðer atamasý) bir topluluðun baþlatýldýðýný ancak ilk deðer atama sayýsýnýn üye
sayýsýndan az olduðunu belirtmiþtik, o zaman tüm kalan üyeler deðer-atamasý structlýr. Ancak, belirli bir üye için varsayýlan bir 
üye ilk deðeri saðlanýrsa, bu varsayýlan üye ilk deðeri yerine kullanýlýr.

                struct BirSey
                {
                    int x;       // varsayýlan ilk deðer yok (kötü)
                    int y {};    // varsayýlan olarak deðer-atamasý structlýyor
                    int z { 2 }; // açýkça belirtilen varsayýlan deðer
                };

                int main()
                {
                    BirSey s3 {}; // s3.x'i deðer-atamasý yap, s3.y ve s3.z için varsayýlan deðerleri kullan

                    return 0;
                }
 
Yukarýdaki durumda, s3 boþ bir liste ile liste-atamasý structlýyor, bu yüzden tüm ilk deðerler eksik. Bu, varsayýlan bir üye ilk 
deðeri varsa kullanýlacaðý ve aksi takdirde deðer-atamasý structlacaðý anlamýna gelir. Bu nedenle, s3.x (varsayýlan bir üye ilk 
deðeri olmayan) 0'a deðer-atamasý structlýr, s3.y varsayýlan olarak 0'a deðer-atamasý structlýr ve s3.z varsayýlan olarak 2 deðerine
atanýr.

Baþlangýç deðerlerinin özetlenmesi
----------------------------------
Bir topluluk bir baþlangýç listesi ile tanýmlanmýþsa:

* - Eðer açýk bir baþlangýç deðeri varsa, bu açýk deðer kullanýlýr.
* - Eðer bir baþlatýcý eksik ve varsayýlan bir üye baþlatýcýsý varsa, varsayýlan deðer kullanýlýr.
* - Eðer bir baþlatýcý eksik ve varsayýlan bir üye baþlatýcýsý yoksa, deðer baþlatma gerçekleþir.

Bir topluluk baþlangýç listesi olmadan tanýmlanmýþsa:

* - Eðer varsayýlan bir üye baþlatýcýsý varsa, varsayýlan deðer kullanýlýr.
* - Eðer varsayýlan bir üye baþlatýcýsý yoksa, üye baþlatýlmadan kalýr.
* - Üyeler her zaman bildirim sýrasýna göre baþlatýlýr.

Aþaðýdaki örnek tüm olasýlýklarý özetler:

                struct BirSey
                {
                    int x;       // varsayýlan baþlangýç deðeri yok (kötü)
                    int y {};    // varsayýlan olarak deðer-baþlatýldý
                    int z { 2 }; // açýk varsayýlan deðer
                };

                int main()
                {
                    BirSey s1;             // Baþlatýcý listesi yok: s1.x baþlatýlmamýþ, s1.y ve s1.z varsayýlanlarý kullanýr
                    BirSey s2 { 5, 6, 7 }; // Açýk baþlatýcýlar: s2.x, s2.y ve s2.z açýk deðerleri kullanýr (varsayýlan deðerler 
                                           // kullanýlmaz)
                    BirSey s3 {};          // Eksik baþlatýcýlar: s3.x deðer baþlatýlýr, s3.y ve s3.z varsayýlanlarý kullanýr

                    return 0;
                }
 
Dikkat etmemiz gereken durum s1.x'tir. Çünkü s1'in bir baþlatýcý listesi yok ve x'in varsayýlan bir üye baþlatýcýsý yok, bu yüzden
s1.x baþlatýlmadan kalýr (bu kötüdür, çünkü deðiþkenlerimizi her zaman baþlatmalýyýz).

Üyeleriniz için her zaman varsayýlan deðerler saðlayýn
------------------------------------------------------
Baþlatýlmamýþ üyelerin olasýlýðýný önlemek için, basitçe her üyenin bir varsayýlan deðeri olduðundan emin olun (ya açýk bir 
varsayýlan deðer veya boþ bir süslü parantez çifti). Bu þekilde, üyelerimiz bir baþlatýcý listesi saðlayýp saðlamadýðýmýza 
bakýlmaksýzýn bir deðerle baþlatýlacaktýr. Aþaðýdaki structý düþünün, tüm üyeleri varsayýlan deðerlere sahiptir:
 
                struct Kesir
                {
                    int pay { }; // burada { 0 } kullanmalýyýz, ama örneðin uðruna deðer baþlatmayý kullanacaðýz
                    int payda { 1 };
                };

                int main()
                {
                    Kesir f1;          // f1.pay deðer baþlatýldý ve 0 oldu, f1.payda 1'e varsayýlandý
                    Kesir f2 {};       // f2.pay deðer baþlatýldý ve 0 oldu, f2.payda 1'e varsayýlandý
                    Kesir f3 { 6 };    // f3.pay 6'ya baþlatýldý, f3.payda 1'e varsayýlandý
                    Kesir f4 { 5, 8 }; // f4.pay 5'e baþlatýldý, f4.payda 8'e baþlatýldý

                    return 0;
                }
 
Tüm durumlarda, üyelerimiz deðerlerle baþlatýlýr.
*** BEST -> Tüm üyeler için bir varsayýlan deðer saðlayýn. Bu, deðiþken tanýmýnýz bir baþlatýcý listesi içermese bile üyelerinizin
            baþlatýlacaðýný garanti eder.

Topluluklar için varsayýlan baþlatma vs deðer baþlatma
------------------------------------------------------
Yukarýdaki örnekteki iki satýrý tekrar gözden geçirelim:
 
                Kesir f1;          // f1.pay deðer baþlatýldý ve 0 oldu, f1.payda 1'e varsayýlandý
                Kesir f2 {};       // f2.pay deðer baþlatýldý ve 0 oldu, f2.payda 1'e varsayýlandý
 
F1'in varsayýlan baþlatýldýðýný ve f2'nin deðer baþlatýldýðýný not edeceksiniz, ancak sonuçlar aynýdýr (pay 0'a baþlatýlýr ve
payda 1'e baþlatýlýr). Peki hangisini tercih etmeliyiz?
Deðer baþlatma durumu (f2) daha güvenlidir, çünkü varsayýlan deðerleri olmayan herhangi bir üyenin deðer baþlatýlmasýný saðlar 
(ve her zaman üyeler için varsayýlan deðerler saðlamalýyýz, ancak bu, bir tanesinin kaçýrýldýðý durumu korur).Deðer baþlatmayý 
tercih etmenin bir avantajý daha var - diðer türlerin nesnelerini nasýl baþlattýðýmýzla tutarlýdýr. Tutarlýlýk hatalarý önlemeye
yardýmcý olur.

*** BEST -> Topluluklar için, varsayýlan baþlatmaya (süslü parantez olmadan) karþý deðer baþlatmayý (boþ süslü parantez baþlatýcý
            ile) tercih edin.

Bununla birlikte, programcýlarýn sýnýf türleri için deðer baþlatma yerine varsayýlan baþlatmayý kullanmalarý alýþýlmadýk bir durum 
deðildir. Bu kýsmen tarihsel nedenlerden dolayýdýr (çünkü deðer baþlatma C++11 ile tanýtýldý) ve kýsmen de varsayýlan baþlatmanýn
daha verimli olabileceði benzer bir durum (bu durumu 14.9 - structcýlarýna Giriþ bölümünde ele alýyoruz) vardýr.

Bu nedenle, bu eðitimlerde Structlar ve sýnýflar için deðer baþlatmanýn kullanýlmasýný zorlaþtýrmayacaðýz, ancak bunu þiddetle
öneriyoruz.

13.8 — Structlarý Geçmek ve Döndürmek ( Pass and Return )
---------------------------------------------------------
3 serbest deðiþkenle temsil edilen bir çalýþaný düþünün:

                int main()
                {
                    int id { 1 };
                    int yas { 24 };
                    double maas { 52400.0 };

                    return 0;
                }
 
Bu çalýþaný bir fonksiyona geçirmek istiyorsak, üç deðiþkeni geçirmemiz gerekiyor:

                #include <iostream>

                void printEmployee(int id, int yas, double maas)
                {
                    std::cout << "ID:   " << id << '\n';
                    std::cout << "Yaþ:  " << yas << '\n';
                    std::cout << "Maaþ: " << maas << '\n';
                }

                int main()
                {
                    int id { 1 };
                    int yas { 24 };
                    double maas { 52400.0 };

                    printEmployee(id, yas, maas);

                    return 0;
                }
 
3 ayrý çalýþan deðiþkenini geçmek o kadar kötü deðil, ancak 10 veya 12 çalýþan deðiþkenini geçmemiz gereken bir fonksiyon düþünün.
Her deðiþkeni baðýmsýz olarak geçmek zaman alýcý ve hata yapmaya eðilimlidir. Ayrýca, eðer çalýþanýmýza yeni bir özellik eklersek
(ör. isim), artýk tüm fonksiyon bildirimlerini, tanýmlamalarýný ve fonksiyon çaðrýlarýný yeni parametre ve argümaný kabul etmek 
üzere deðiþtirmemiz gerekiyor!

Structlarý (Referans Olarak) Geçmek
-----------------------------------
Structlarý bireysel deðiþkenler üzerinde kullanmanýn büyük bir avantajý, üyelerle çalýþmasý gereken bir fonksiyona tüm structý 
geçirebilmemizdir. Structlar genellikle kopyalarý önlemek için (const) referans olarak geçirilir.
 
                #include <iostream>

                struct Calisan
                {
                    int id {};
                    int yas {};
                    double maas {};
                };

                void printEmployee(const Calisan& calisan) // burada referansla geçiþi not edin
                {
                    std::cout << "ID:   " << calisan.id << '\n';
                    std::cout << "Yaþ:  " << calisan.yas << '\n';
                    std::cout << "Maaþ: " << calisan.maas << '\n';
                }

                int main()
                {
                    Calisan joe { 14, 32, 24.15 };
                    Calisan frank { 15, 28, 18.27 };

                    // Joe'nun bilgilerini yazdýr
                    printEmployee(joe);

                    std::cout << '\n';

                    // Frank'in bilgilerini yazdýr
                    printEmployee(frank);

                    return 0;
                }
 
Yukarýdaki örnekte, tüm bir Calisan'ý printEmployee()'a geçiriyoruz (iki kez, bir kez joe ve bir kez frank için).

                Yukarýdaki program þunu çýktýlar:

                ID:   14
                Yaþ:  32
                Maaþ: 24.15

                ID:   15
                Yaþ:  28
                Maaþ: 18.27
Tüm struct nesnesini (bireysel üyeler yerine) geçirdiðimiz için, struct nesnesinin kaç üyesi olursa olsun yalnýzca bir parametreye
ihtiyacýmýz var. Ve gelecekte, eðer Calisan structmýza yeni üyeler eklemeye karar verirsek, fonksiyon bildirimini veya fonksiyon 
çaðrýsýný deðiþtirmemiz gerekmeyecek! Yeni üye otomatik olarak dahil edilecektir.

Structlarý Döndürmek
--------------------
3 boyutlu Kartezyen uzayda bir noktayý döndürmesi gereken bir fonksiyon olduðunu düþünün. Böyle bir noktanýn 3 özelliði vardýr:
bir x-koordinatý, bir y-koordinatý ve bir z-koordinatý. Ancak fonksiyonlar yalnýzca bir deðer döndürebilir. Peki kullanýcýya tüm
3 koordinatý nasýl geri döndürürüz?

Yaygýn bir yol, bir struct döndürmektir:

                #include <iostream>

                struct Nokta3d
                {
                    double x { 0.0 };
                    double y { 0.0 };
                    double z { 0.0 };
                };

                Nokta3d sifirNoktayiAl()
                {
                    // Bir deðiþken oluþturabilir ve deðiþkeni döndürebiliriz (bunu aþaðýda geliþtireceðiz)
                    Nokta3d gecici { 0.0, 0.0, 0.0 };
                    return gecici;
                }

                int main()
                {
                    Nokta3d sifir{ sifirNoktayiAl() };

                    if (sifir.x == 0.0 && sifir.y == 0.0 && sifir.z == 0.0)
                        std::cout << "Nokta sýfýr\n";
                    else
                        std::cout << "Nokta sýfýr deðil\n";

                    return 0;
                }
 
                Bu çýktýyý verir:

                Nokta sýfýr
Structlar genellikle deðer olarak döndürülür, böylece asýlý bir referans döndürülmez.

Yukarýdaki getZeroPoint() fonksiyonunda, yalnýzca onu döndürebilmek için yeni bir adlandýrýlmýþ nesne (temp) oluþturuyoruz:

                Nokta3d sifirNoktayiAl()
                {
                    // Bir deðiþken oluþturabilir ve deðiþkeni döndürebiliriz (bunu aþaðýda geliþtireceðiz)
                    Nokta3d gecici { 0.0, 0.0, 0.0 };
                    return gecici;
                }
 Nesnenin adý (temp) burada herhangi bir belgelendirme deðeri saðlamýyor. Fonksiyonumuzu, geçici (isimsiz/anonim) bir nesne 
 döndürerek biraz daha iyi hale getirebiliriz:

                Point3d getZeroPoint()
                {
                    return Point3d { 0.0, 0.0, 0.0 }; // isimsiz bir Point3d döndür
                }
 
Bu durumda, geçici bir Point3d oluþturulur, çaðýran kiþiye geri kopyalanýr ve ifadenin sonunda yok edilir. Bu durumun ne kadar 
daha temiz olduðuna dikkat edin (iki satýr yerine bir satýr ve temp'in birden fazla kullanýlýp kullanýlmadýðýný anlamanýza gerek 
yok).

Dönüþ Tipini Çýkarým Yapma
--------------------------
Fonksiyonun açýk bir dönüþ tipi olduðu durumda (ör. Point3d), dönüþ ifadesinde tipi bile atlayabiliriz:

Point3d getZeroPoint()
{
    // Tipi zaten fonksiyon bildiriminde belirttik
    // bu yüzden burada tekrar yapmamýza gerek yok
    return { 0.0, 0.0, 0.0 }; // isimsiz bir Point3d döndür
}
Ayrýca, bu durumda tüm sýfýr deðerlerini döndürdüðümüzden, deðer baþlatýlmýþ bir Point3d döndürmek için boþ süslü parantezler
kullanabiliriz:

                Point3d getZeroPoint()
                {
                    // Tüm üyeleri deðer baþlatmak için boþ süslü parantezleri kullanabiliriz
                    return {};
                }
 
Structlar önemli bir yapý taþýdýr

Structlar kendi baþlarýna yararlý olsa da, sýnýflar (C++ ve nesne yönelimli programlamanýn kalbi olan) burada tanýttýðýmýz
kavramlarýn doðrudan üzerine inþa eder. Structlarýn (özellikle veri üyeleri, üye seçimi ve varsayýlan üye baþlatma)
iyi bir anlayýþýna sahip olmak, sýnýflara geçiþinizi çok daha kolay hale getirecektir.
*/
