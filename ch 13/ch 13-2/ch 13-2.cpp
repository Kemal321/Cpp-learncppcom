#include <iostream>
int main()
{
    return 0;
}
/*
13.3 — Kapsamsýz numaralandýrma giriþi ve çýktýsý
-----------------------------------------------------
Önceki derste (13.2 – Kapsamsýz numaralandýrmalar), numaralandýrýcýlarýn sembolik sabitler olduðunu belirtmiþtik. Ancak, size
o zaman söylemediðimiz þey, numaralandýrýcýlarýn tamsayý sembolik sabitler olduðudur. Sonuç olarak, numaralandýrýlmýþ türler 
aslýnda bir tamsayý deðeri tutar.

Bu, charlarla yani karakterlerle olan duruma benzer. Dikkate alýn:
                    char ch { 'A' };

Bir karakter aslýnda sadece 1 baytlýk bir tamsayý deðeridir ve karakter ‘A’ bir tamsayý deðerine (bu durumda, 65) dönüþtürülür ve
saklanýr.

Bir numaralandýrýcý tanýmladýðýmýzda, her numaralandýrýcý otomatik olarak numaralandýrýcý listesindeki konumuna dayalý bir tamsayý
deðeri atanýr. Varsayýlan olarak, ilk numaralandýrýcý tamsayý deðeri 0 atanýr ve her bir sonraki numaralandýrýcý, önceki
numaralandýrýcýdan bir fazla deðere sahiptir:
                    enum Color
                    {
                        black, // assigned 0
                        red, // assigned 1
                        blue, // assigned 2
                        green, // assigned 3
                        white, // assigned 4
                        cyan, // assigned 5
                        yellow, // assigned 6
                        magenta, // assigned 7
                    };

                    int main()
                    {
                        Color shirt{ blue }; // Bu aslýnda tamsayý deðeri 2'yi saklar

                        return 0;
                    }

Numaralandýrýcýlarýn deðerini açýkça tanýmlamak mümkündür. Bu tamsayý deðerleri pozitif veya negatif olabilir ve diðer
numaralandýrýcýlarla ayný deðeri paylaþabilir. Herhangi bir Kapsamsýz numaralandýrýcý, önceki numaralandýrýcýdan bir fazla
deðer verilir.

                    enum Animal
                    {
                        cat = -3,
                        dog,         // assigned -2
                        pig,         // assigned -1
                        horse = 5,
                        giraffe = 5, // shares same value as horse
                        chicken,      // assigned 6
                    };

Bu durumda, at ve zürafa ayný deðer verilmiþtir. Bu olduðunda, numaralandýrýcýlar ayýrt edilemez hale gelir - temelde, at ve zürafa birbirinin yerine geçebilir. C++ bunu saðlasa da, ayný numaralandýrmada iki numaralandýrýcýya ayný deðeri atamaktan genellikle kaçýnýlmalýdýr.

*** BEST -> Numaralandýrýcýlarýnýza açýkça deðer atamaktan kaçýnýn, bunu yapmak için geçerli bir nedeniniz olmadýkça.

Kapsamsýz numaralandýrmalar, tamsayý deðerlerine dolaylý olarak dönüþtürülür

Aþaðýdaki programý düþünün:

                    #include <iostream>

                    enum Color
                    {
                        black, // assigned 0
                        red, // assigned 1
                        blue, // assigned 2
                        green, // assigned 3
                        white, // assigned 4
                        cyan, // assigned 5
                        yellow, // assigned 6
                        magenta, // assigned 7
                    };

                    int main()
                    {
                        Color shirt{ blue };

                        std::cout << "Your shirt is " << shirt << '\n'; // bu ne yapar?

                        return 0;
                    }

Numaralandýrýlmýþ türler tamsayý deðerlerini tuttuðu için, beklediðiniz gibi, bu þu çýktýyý verir:

                    Your shirt is 2 
Bir numaralandýrýlmýþ tür, bir iþlev çaðrýsýnda veya bir operatörle kullanýldýðýnda, derleyici ilk olarak
numaralandýrýlmýþ türle eþleþen bir iþlev veya operatör bulmaya çalýþýr. Örneðin, derleyici 
                    std::cout << shirt 
derlemeye çalýþtýðýnda, derleyici ilk olarak operator<<'in Color türünden bir nesneyi (çünkü shirt Color türündedir) std::cout’a 
nasýl yazdýracaðýný bilip bilmediðini görmek için bakar. Bilmez.

Derleyici bir eþleþme bulamazsa, derleyici daha sonra Kapsamsýz bir numaralandýrmayý veya numaralandýrýcýyý karþýlýk gelen
tamsayý deðerine dolaylý olarak dönüþtürür. Çünkü std::cout bir tamsayý deðerini yazdýrmayý bilir, shirt’teki deðer bir tamsayýya 
dönüþtürülür ve tamsayý deðeri 2 olarak yazdýrýlýr.

Numaralandýrýcý isimlerini yazdýrma
-----------------------------------
Çoðu zaman, bir numaralandýrmayý bir tamsayý deðeri olarak yazdýrmak (örneðin 2) istediðimiz þey deðildir. Bunun yerine,
genellikle numaralandýrýcýnýn temsil ettiði ne olursa olsun ismini yazdýrmak isteriz (blue). Ancak bunu yapmak için, 
numaralandýrmanýn tamsayý deðerini (2) numaralandýrýcý adýna eþleþen bir dizeye (“blue”) dönüþtürmenin bir yoluna ihtiyacýmýz var.

C++20 itibariyle, C++ bunu yapmanýn kolay bir yolunu sunmuyor, bu yüzden kendi çözümümüzü bulmamýz gerekiyor. Neyse ki, bu çok zor
deðil. Bunu yapmanýn tipik yolu, bir numaralandýrýlmýþ türü parametre olarak alan ve ardýndan karþýlýk gelen dizeyi çýktý olarak
veren (veya dizeyi çaðýrýcýya döndüren) bir iþlev yazmaktýr.

Bunu yapmanýn tipik yolu, numaralandýrmamýzý her olasý numaralandýrýcýya karþý test etmektir.

                    // Bunun için if-else kullanmak verimsizdir
                    void renkYaz(Color renk)
                    {
                        if (renk == black) std::cout << "siyah";
                        else if (renk == red) std::cout << "red";
                        else if (renk == blue) std::cout << "blue";
                        else std::cout << "???";
                    }
Ancak, bunun için bir dizi if-else ifadesi kullanmak verimsizdir, çünkü bir eþleþme bulunmadan önce birden çok karþýlaþtýrma 
yapýlmasý gerekir. Ayný þeyi yapmanýn daha verimli bir yolu, bir switch ifadesi kullanmaktýr. Aþaðýdaki örnekte, Color'umuzu da
bir std::string olarak döndüreceðiz, böylece çaðýran kiþiye adýyla (yazdýrmak dahil) istediklerini yapma esnekliði vereceðiz:

                    #include <iostream>
                    #include <string>

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };


                    // Bunu C++17 için daha iyi bir versiyonunu aþaðýda göstereceðiz
                    std::string getRenk(Color renk)
                    {
                        switch (renk)
                        {
                        case black: return "siyah";
                        case red:   return "red";
                        case blue:  return "blue";
                        default:    return "???";
                        }
                    }

                    int main()
                    {
                        Color gomlek { blue };

                        std::cout << "Gömleðiniz " << getRenk(gomlek) << '\n';

                        return 0;
                    }
                    Þu çýktýyý verir:

                    Gömleðiniz blue
Bu, if-else zincirinden muhtemelen daha iyi performans gösterir (switch ifadeleri genellikle if-else zincirlerinden daha verimlidir)
ve okumasý da daha kolaydýr. Ancak, bu versiyon hala verimsizdir, çünkü her fonksiyon çaðrýldýðýnda bir std::string oluþturup
döndürmemiz gerekiyor.

C++17'de, daha verimli bir seçenek, std::string'i std::string_view ile deðiþtirmektir. std::string_view, string literallerini 
kopyalamasý çok daha az maliyetli bir þekilde döndürmemize olanak saðlar.

                    #include <iostream>
                    #include <string_view> // C++17

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    constexpr std::string_view getRenk(Color renk) // C++17
                    {
                        switch (renk)
                        {
                        case black: return "siyah";
                        case red:   return "red";
                        case blue:  return "blue";
                        default:    return "???";
                        }
                    }

                    int main()
                    {
                        constexpr Color gomlek{ blue };

                        std::cout << "Gömleðiniz " << getRenk(gomlek) << '\n';

                        return 0;
                    }

Bir numaralandýrýcýyý nasýl yazdýracaðýný öðretme
-------------------------------------------------
Yukarýdaki örnek iyi iþlev görse de, numaralandýrýcý adýný almak için oluþturduðumuz fonksiyonun adýný hala hatýrlamamýz gerekiyor.
Bu genellikle çok zor olmasa da, birçok numaralandýrmanýz varsa daha sorunlu hale gelebilir. Operatör aþýrý yüklemeyi kullanarak
(fonksiyon aþýrý yüklemeye benzer bir yetenek), aslýnda program tarafýndan tanýmlanan bir numaralandýrmanýn deðerini nasýl 
yazdýracaðýný öðretebiliriz! Bunun nasýl çalýþtýðýný henüz açýklamadýk, bu yüzden þimdilik biraz sihir olarak düþünün:

                    #include <iostream>

                    enum Color
                    {
                        black,
                        red,
                        blue,
                    };

                    // Operator<<'e bir Color nasýl yazdýrýlacaðýný öðret
                    // Bunun nasýl çalýþtýðýný henüz açýklamadýðýmýz için þimdilik bunu sihir olarak düþünün
                    // std::ostream, std::cout'un türüdür
                    // Dönüþ türü ve parametre türü referanslardýr (kopyalarýn yapýlmasýný önlemek için)!
                    std::ostream& operator<<(std::ostream& out, Color renk)
                    {
                        switch (renk)
                        {
                        case black: return out << "siyah";
                        case red:   return out << "red";
                        case blue:  return out << "blue";
                        default:    return out << "???";
                        }
                    }

                    int main()
                    {
                        Color gomlek{ blue };
                        std::cout << "Gömleðiniz " << gomlek << '\n'; // iþe yarýyor!

                        return 0;
                    }
                    Þu çýktýyý verir:

                    Gömleðiniz blue
Ders 21.4’te I/O operatörlerinin aþýrý yüklenmesini ele alýyoruz – I/O operatörlerinin aþýrý yüklenmesi. Þimdilik bu kodu 
kopyalayabilir ve Color’u kendi numaralandýrýlmýþ tipinizle deðiþtirebilirsiniz.

Numaralandýrma boyutu ve altta yatan tip (taban) ( ( underlying type or base )  )
---------------------------------------------------------------------------------
Bir numaralandýrmanýn numaralandýrýcýlarý integral sabitlerdir. Numaralandýrýcýlarý temsil etmek için kullanýlan belirli integral
tipine altta yatan tip (veya taban ( underlying type or base ) ) denir.

Kapsamsýz numaralandýrýcýlar için, C++ standardý altta yatan tip olarak hangi belirli integral tipinin kullanýlmasý gerektiðini 
belirtmez. Çoðu derleyici, numaralandýrýcý deðerlerini saklamak için daha büyük bir tip gerektirmedikçe, altta yatan tip olarak
int tipini kullanýr (bu, kapsamsýz bir enum’un bir int ile ayný boyutta olacaðý anlamýna gelir).

Farklý bir altta yatan tip belirtmek mümkündür. Örneðin, bazý bant geniþliði hassas baðlamlarda (ör. bir að üzerinden veri
gönderme) daha küçük bir tip belirtmek isteyebilirsiniz:

                    #include <cstdint>  // for std::int8_t
                    #include <iostream>

                    // Use an 8-bit integer as the enum underlying type
                    enum Color : std::int8_t
                    {
                        black,
                        red,
                        blue,
                    };

                    int main()
                    {
                        Color c{ black };
                        std::cout << sizeof(c) << '\n'; // prints 1 (byte)

                        return 0;
                    }

*** BEST -> Bir numaralandýrmanýn taban tipini sadece gerekli olduðunda belirtin.

*** Uyarý -> std::int8_t ve std::uint8_t genellikle char tipleri için tip takma adlarýdýr, bu nedenle bu tiplerden herhangi birini
             enum tabaný olarak kullanmak, numaralandýrýcýlarýn büyük olasýlýkla int deðerleri yerine char deðerleri olarak 
             yazdýrýlmasýna neden olacaktýr.

Tamsayýdan kapsamsýz numaralandýrýcýya dönüþüm
----------------------------------------------
Derleyici, kapsamsýz numaralandýrýcýlarý bir tamsayýya açýkça dönüþtürürken, bir tamsayýyý kapsamsýz bir numaralandýrýcýya açýkça
dönüþtürmez. Aþaðýdakiler bir derleyici hatasý üretecektir:

                    enum Pet // no specified base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
                        pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

                        return 0;
                    }

Bunu aþmanýn iki yolu vardýr.

Ýlk olarak, derleyiciyi bir tamsayýyý kapsamsýz bir numaralandýrýcýya dönüþtürmeye zorlayabilirsiniz static_cast kullanarak:

                    enum Pet // no specified base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
                        pet = static_cast<Pet>(3);       // our pig evolved into a whale!

                        return 0;
                    }

Birazdan bunun nerede kullanýþlý olabileceðine dair bir örnek göreceðiz.

Ýkincisi, C++17’de, kapsamsýz bir numaralandýrmanýn belirtilmiþ bir tabaný varsa, derleyici bir tamsayýyý kullanarak kapsamsýz bir
numaralandýrmayý liste baþlatmanýza izin verecektir:

                    enum Pet: int // we've specified a base
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet1 { 2 }; // ok: integer ile liste baþlatma yapabilir
                        Pet pet2 (2);   // compile error: Direkt olarak integer ile baþlatýlamaz
                        Pet pet3 = 2;   // compile error: Direkt olarak integer ile baþlatýlamaz

                        pet1 = 3;       // compile error: Ýnteger ile atama yapýlamaz

                        return 0;
                    }

Kapsamsýz numaralandýrýcý giriþi
--------------------------------
Pet, bir program tarafýndan tanýmlanan bir tip olduðu için, dil std::cin kullanarak bir Pet girmeyi bilmez:

                    #include <iostream>

                    enum Pet
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };

                    int main()
                    {
                        Pet pet { pig };
                        std::cin >> pet; // compile error, std::cin Pet e nasýl girdi yapacaðýný bilmez

                        return 0;
                    }

Bunu aþmak için, bir tamsayýyý okuyabiliriz ve uygun numaralandýrýlmýþ tipin bir numaralandýrýcýsýna dönüþtürmek için static_cast
kullanabiliriz:

                    #include <iostream>

                    enum Pet
                    {
                        cat, // assigned 0
                        dog, // assigned 1
                        pig, // assigned 2
                        whale, // assigned 3
                    };
                    int main()
                    {
                        Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
                        pet = static_cast<Pet>(3);       // our pig evolved into a whale!

                        return 0;
                    }

13.4 — Kapsamlý numaralandýrmalar ( enum class )
------------------------------------------------
C++'da kapsamsýz numaralandýrmalar ayrýk türler olmasýna raðmen, tür güvenli deðillerdir ve bazý durumlarda mantýklý olmayan 
þeyler yapmanýza izin verebilirler. Aþaðýdaki durumu düþünün:

                    #include <iostream>

                    int main()
                    {
                        enum Renk
                        {
                            red, // red
                            blue, // blue
                        };

                        enum Meyve
                        {
                            muz, // banana
                            elma, // apple
                        };

                        Renk renk { red }; // red
                        Meyve meyve { muz }; // banana

                        if (renk == meyve) // Derleyici renk ve meyveyi tam sayýlar olarak karþýlaþtýracak
                            std::cout << "renk ve meyve eþittir\n"; // ve bunlarýn eþit olduðunu bulacak!
                        else
                            std::cout << "renk ve meyve eþit deðildir\n";

                        return 0;
                    }
                    ```
                    Bu, þunu yazdýrýr:

                    renk ve meyve eþittir
Renk ve meyve karþýlaþtýrýldýðýnda, derleyici bir Renk ve Meyve'yi nasýl karþýlaþtýracaðýný bilmek için bakar. Bilmiyor. Sonra,
Renk ve/veya Meyve'yi tam sayýlara dönüþtürmeyi dener ve bir eþleþme bulup bulamayacaðýný görür. Sonunda derleyici, her ikisini de
tam sayýlara dönüþtürürse, karþýlaþtýrmayý yapabileceðini belirler. Renk ve meyve, tam sayý deðeri 0'a dönüþtüren 
numaralandýrýcýlara ayarlandýðýndan, renk meyveye eþit olacaktýr.

Bu, semantik olarak mantýklý deðildir çünkü renk ve meyve farklý numaralandýrmalardan gelir ve karþýlaþtýrýlabilir olmalarý
amaçlanmamýþtýr. Standart numaralandýrýcýlarla, bunu önlemenin kolay bir yolu yoktur.

Bu tür zorluklar nedeniyle, ayrýca ad alaný kirliliði sorunu (kapsamsýz numaralandýrmalar, numaralandýrýcýlarýný küresel ad 
alanýna koyarak küresel kapsamda tanýmlanýr), C++ tasarýmcýlarý, numaralandýrmalar için daha temiz bir çözümün faydalý olacaðýný 
belirledi.

Kapsamlý numaralandýrmalar
--------------------------
Bu çözüm, kapsamlý numaralandýrma (C++'da genellikle enum class olarak adlandýrýlýr, nedenleri kýsa süre sonra açýk olacaktýr).
Kapsamlý numaralandýrmalar, kapsamsýz numaralandýrmalara benzer þekilde çalýþýr, ancak iki ana farký vardýr: Açýkça tam sayýlara
dönüþtürmezler ve numaralandýrýcýlar sadece numaralandýrmanýn kapsam bölgesine yerleþtirilir (numaralandýrmanýn tanýmlandýðý
kapsam bölgesine deðil).

Kapsamlý bir numaralandýrma yapmak için, enum class anahtar kelimelerini kullanýrýz. Kapsamlý numaralandýrma tanýmýnýn geri kalaný,
kapsamsýz bir numaralandýrma tanýmýyla aynýdýr. Ýþte bir örnek:

                    #include <iostream>
                    int main()
                    {
                        enum class Renk // "enum class" bunu kapsamsýz bir numaralandýrma yerine kapsamlý bir numaralandýrma 
                                        // olarak tanýmlar
                        {
                            red, // red, Renk'in kapsam bölgesinin bir parçasý olarak kabul edilir
                            blue, // blue
                        };

                        enum class Meyve
                        {
                            muz, // muz, Meyve'nin kapsam bölgesinin bir parçasý olarak kabul edilir
                            elma, // apple
                        };

                        Renk renk { Renk::red }; // not: red doðrudan eriþilebilir deðil, 
                                                     // Renk::red kullanmamýz gerekiyor
                        Meyve meyve { Meyve::muz }; // not: muz doðrudan eriþilebilir deðil, Meyve::muz kullanmamýz gerekiyor

                        if (renk == meyve) // derleme hatasý: derleyici, farklý türler Renk ve Meyve'yi nasýl karþýlaþtýracaðýný
                                           // bilmiyor
                            std::cout << "renk ve meyve eþittir\n";
                        else
                            std::cout << "renk ve meyve eþit deðildir\n";

                        return 0;
                    }

Bu program, kapsamlý numaralandýrmanýn baþka bir türle karþýlaþtýrýlacak herhangi bir türe dönüþtürmeyeceði için 19. satýrda bir 
derleme hatasý oluþturur.

Bir kenara not:
Sýnýf anahtar kelimesi (statik anahtar kelimesiyle birlikte), C++ dilinde en çok aþýrý yüklenmiþ anahtar kelimelerden biridir ve
baðlama baðlý olarak farklý anlamlara gelebilir. Kapsamlý numaralandýrmalar sýnýf anahtar kelimesini kullanmasýna raðmen, bir 
"sýnýf türü" olarak kabul edilmezler (bu, yapýlar, sýnýflar ve birlikler ( struct, classes and unions ) için ayrýlmýþtýr).

Bu baðlamda "enum struct" da çalýþýr ve enum class ile ayný þekilde davranýr. Ancak, enum struct'ýn kullanýmý gayriidiomatiktir,
bu yüzden kullanýmýndan kaçýnýn.

Kapsamlý numaralandýrmalar kendi kapsam bölgelerini tanýmlar
------------------------------------------------------------
Kapsamsýz numaralandýrmalar, numaralandýrýcýlarýný numaralandýrmanýn kendisiyle ayný kapsama yerleþtirirken, kapsamlý
numaralandýrmalar numaralandýrýcýlarýný yalnýzca numaralandýrmanýn kapsam bölgesine yerleþtirir. Baþka bir deyiþle, kapsamlý 
numaralandýrmalar numaralandýrýcýlarý için bir ad alaný gibi davranýr. Bu yerleþik ad alaný, kapsamlý numaralandýrmalarýn küresel 
kapsamda kullanýldýðýnda küresel ad alaný kirliliðini azaltýr ve ad çakýþmalarýnýn potansiyelini azaltýr.

Bir kapsamlý numaralandýrýcýya eriþmek için, ona sanki kapsamlý numaralandýrmanýn ayný adýný taþýyan bir ad alanýnda gibi
davranýrýz:
                        #include <iostream>

                        int main()
                        {
                            enum class Renk // "enum class" bunu kapsamsýz bir enum yerine kapsamlý bir enum olarak tanýmlar
                            {
                                red, // red Color ýn kapsam bölgesinin bir parçasý olarak düþünülür
                                blue,
                            };

                            std::cout << red << '\n';        // derleme hatasý: red bu kapsam bölgesinde tanýmlanmamýþ
                            std::cout << Renk::red << '\n'; // derleme hatasý: std::cout bunu nasýl yazdýracaðýný bilmiyor 
                                                                // (açýkça int'e dönüþtürmez)

                            Renk renk { Renk::blue }; // tamam

                            return 0;
                        }

Kapsamlý numaralandýrmalar, numaralandýrýcýlarý için kendi içsel ad alanlarýný sunduðundan, kapsamlý numaralandýrmalarý baþka bir
kapsam bölgesine (örneðin bir ad alanýna) koymanýn bir gerekliliði yoktur, aksi takdirde gereksiz olurdu.

Kapsamlý numaralandýrmalar açýkça tam sayýlara dönüþtürmez

Kapsamsýz numaralandýrýcýlarýn aksine, kapsamlý numaralandýrýcýlar açýkça tam sayýlara dönüþtürmez. Çoðu durumda, bu iyi bir þeydir
çünkü nadiren mantýklýdýr ve farklý numaralandýrmalardan numaralandýrýcýlarý karþýlaþtýrmak veya red + 5 gibi semantik hatalarý
önlemeye yardýmcý olur.

Ayný kapsamlý numaralandýrma içindeki numaralandýrýcýlarý hala karþýlaþtýrabileceðinizi unutmayýn (çünkü ayný türdendirler):

                    #include <iostream>
                    int main()
                    {
                        enum class Renk
                        {
                            red, 
                            blue, 
                        };

                        Renk shirt { Renk::red }; 

                        if (shirt == Renk::red) // bu Renk ile Renk::red karþýlaþtýrmasý tamam
                            std::cout << "shirt red!\n";
                        else if (shirt == Renk::blue)
                            std::cout << "shirt blue!\n";

                        return 0;
                    }

Bazen, bir kapsamlý numaralandýrýcýyý bir tamsayý deðeri olarak ele almanýn yararlý olduðu durumlar vardýr. Bu durumlarda, bir
kapsamlý numaralandýrýcýyý bir tamsayýya açýkça dönüþtürebilirsiniz, bunun için static_cast kullanabilirsiniz. C++23'te daha iyi
bir seçenek, std::to_underlying()'i (<utility> baþlýðýnda tanýmlanmýþtýr) kullanmaktýr, bu da bir numaralandýrýcýyý
numaralandýrmanýn altýnda yatan türün bir deðerine dönüþtürür.

                    #include <iostream>
                    #include <utility> // for std::to_underlying() (C++23)

                    int main()
                    {
                        enum class Renk
                        {
                            red, // red
                            blue, // blue
                        };

                        Renk renk { Renk::blue }; // blue

                        std::cout << renk << '\n'; // çalýþmaz, çünkü açýk bir dönüþüm int'e yok
                        std::cout << static_cast<int>(renk) << '\n';   // açýk dönüþüm int'e, 1 yazdýrýr
                        std::cout << std::to_underlying(renk) << '\n'; // altýnda yatan türe dönüþtür, 1 yazdýrýr (C++23)

                        return 0;
                    }

Tersine, bir tamsayýyý bir kapsamlý numaralandýrýcýya da static_cast yapabilirsiniz, bu kullanýcýdan giriþ yaparken yararlý
olabilir:

                #include <iostream>

                int main()
                {
                    enum class EvcilHayvan
                    {
                        kedi, // assigned 0
                        köpek, // assigned 1
                        domuz, // assigned 2
                        balina, // assigned 3
                    };

                    std::cout << "Bir evcil hayvan girin (0=kedi, 1=köpek, 2=domuz, 3=balina): ";

                    int giriþ{};
                    std::cin >> giriþ; // bir tamsayý girin

                    EvcilHayvan evcilHayvan{ static_cast<EvcilHayvan>(giriþ) }; // tamsayýmýzý bir EvcilHayvan'a static_cast yapýn

                    return 0;
                }

C++17 itibariyle, bir tamsayý deðeri kullanarak bir kapsamlý numaralandýrmayý liste baþlatma iþlemi yapabilirsiniz ve static_cast 
gerektirmez (ve kapsamsýz bir numaralandýrmanýn aksine, bir taban( base ) belirtmeniz gerekmez).

*** BEST -> Kapsamsýz numaralandýrmalar yerine kapsamlý numaralandýrmalarý tercih edin, aksi takdirde bunu yapmak için geçerli bir
            neden varsa.

Kapsamlý numaralandýrmalarýn sunduðu avantajlara raðmen, kapsamsýz numaralandýrmalar hala C++'da yaygýn olarak kullanýlýyor çünkü
bazen açýkça int'e dönüþümü istiyoruz (çok fazla static_cast yapmak can sýkýcý olabilir) ve ek ad alanýna ihtiyacýmýz yok.

using enum kullanma C++20
-------------------------
C++20'de tanýtýlan bir using enum ifadesi, bir enum'daki tüm numaralandýrýcýlarý mevcut kapsama aktarýr. Bir enum class türüyle
kullanýldýðýnda, bu bize enum class numaralandýrýcýlarýna her birini enum class adý ile öne koymadan eriþmemizi saðlar.

Bu, switch ifadesi içindeki gibi birçok ayný, tekrarlanan önekler olacaðý durumlarda yararlý olabilir:

                #include <iostream>
                #include <string_view>

                enum class Renk
                {
                    siyah,
                    kýrmýzý,
                    mavi,
                };

                constexpr std::string_view getRenk(Renk renk)
                {
                    using enum Renk; // tüm Renk numaralandýrýcýlarýný mevcut kapsama getirin (C++20)
                    // Artýk Renk numaralandýrýcýlarýna Renk:: öneki kullanmadan eriþebiliriz

                    switch (renk)
                    {
                    case siyah: return "siyah"; // not: siyah yerine Renk::siyah
                    case kýrmýzý:   return "kýrmýzý";
                    case mavi:  return "mavi";
                    default:    return "???";
                    }
                }

                int main()
                {
                    Renk gömlek{ Renk::mavi };

                    std::cout << "Gömleðiniz " << getRenk(gömlek) << '\n';

                    return 0;
                }

Yukarýdaki örnekte, Renk bir enum class, bu yüzden normalde numaralandýrýcýlarý tam nitelikli bir adý kullanarak eriþiriz
(ör. Renk::mavi). Ancak, getColor() fonksiyonu içinde, using enum Renk; ifadesini ekledik, bu da bize bu numaralandýrýcýlarý
Renk:: öneki olmadan eriþmemizi saðlar.

Bu, switch ifadesi içinde birden çok, gereksiz, açýk önekler olmasýný önler.
*/
