#include <iostream>

int main()
{
    return 0;
}
/*
14.6 — Eriþim Fonksiyonlarý
---------------------------
Önceki ders 14.5 -- public ve private Üyeler ve Eriþim Belirleyiciler'de, public ve private eriþim düzeylerini tartýþtýk.
Hatýrlatmak gerekirse, sýnýflar genellikle veri üyelerini private yapar ve private üyelere public tarafýndan doðrudan eriþilemez.

Aþaðýdaki Date sýnýfýný düþünün:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{ 2020 };
                    int m_month{ 10 };
                    int m_day{ 14 };

                public:
                    void print() const
                    {
                        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
                    }
                };

                int main()
                {
                    Date d{};  // bir Date nesnesi oluþtur
                    d.print(); // tarihi yazdýr

                    return 0;
                }
Bu sýnýf, tüm tarihi yazdýrmak için bir print() member fonksiyonu saðlar, ancak bu, kullanýcýnýn yapmak istediði þey için yeterli
olmayabilir. Örneðin, bir Date nesnesinin kullanýcýsý year'ý almak isterse ne olur? Ya da year'ý farklý bir deðere deðiþtirmek 
isterse? Bunu yapamazlar, çünkü m_yil özeldir (ve bu nedenle public tarafýndan doðrudan eriþilemez).
Bazý sýnýflar için, özel bir member deðiþkenin deðerini almak veya ayarlamak uygun olabilir (sýnýfýn ne yaptýðý baðlamýnda).

Eriþim Fonksiyonlarý
--------------------
Bir eriþim fonksiyonu, özel bir member deðiþkenin deðerini almak veya deðiþtirmek için görevi olan basit bir public member fonksiyonudur.
Eriþim fonksiyonlarý iki çeþittir: getter'lar ve setter'lar. Getter'lar (bazen eriþimciler olarak da adlandýrýlýr) özel bir üye
deðiþkenin deðerini döndüren public member fonksiyonlardýr. Setter'lar (bazen deðiþtiriciler olarak da adlandýrýlýr) özel bir member 
deðiþkenin deðerini ayarlayan public member fonksiyonlardýr.

Getter'lar genellikle const yapýlýr, böylece hem const hem de non-const nesnelerde çaðrýlabilirler. Setter'lar non-const olmalýdýr,
böylece veri üyelerini deðiþtirebilirler.

Örnekleme amaçlý olarak, Date sýnýfýmýzý tam bir getter ve setter setine sahip olacak þekilde güncelleyelim:

                #include <iostream>

                class Date
                {
                private:
                    int m_year { 2020 };
                    int m_month { 10 };
                    int m_day { 14 };

                public:
                    void print()
                    {
                        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
                    }

                    int getYear() const { return m_year; }        // year için getter
                    void setYear(int year) { m_year = year; }     // year için setter

                    int getMonth() const  { return m_month; }     // month için getter
                    void setMonth(int month) { m_month = month; } // month için setter

                    int getDay() const { return m_day; }          // day için getter
                    void setDay(int day) { m_day = day; }         // day için setter
                };

                int main()
                {
                    Date d{};
                    d.setYear(2021);
                    std::cout << "The year is: " << d.getYear() << '\n';

                    return 0;
                }
                Bu, þunu yazdýrýr:

                The year is: 2021
Eriþim Fonksiyonu Adlandýrma
----------------------------
Eriþim fonksiyonlarýný adlandýrmak için ortak bir kural yoktur. Ancak, diðerlerinden daha popüler olan birkaç adlandýrma kuralý
vardýr.

"get" ve "set" ile öne çýkanlar:
                int getDay() const { return m_day; }  // getter
                void setDay(int day) { m_day = day; } // setter
"get" ve "set" öneklerini kullanmanýn avantajý, bunlarýn eriþim fonksiyonlarý olduðunu açýkça belirtir (ve çaðrýlmasý ucuz
olmalýdýr).

Önek yok:
                int day() const { return m_day; }  // getter
                void day(int day) { m_day = day; } // setter
Bu stil daha özlüdür ve hem getter hem de setter için ayný adý kullanýr (ikisini ayýrt etmek için fonksiyon aþýrý yüklemeye
güvenir). C++ standart kütüphanesi bu kuralý kullanýr.
Önek olmayan kuralýn dezavantajý, bu iþlemin gün üyesinin deðerini ayarladýðý konusunda özellikle açýk olmamasýdýr:

                d.day(5); // bu, gün üyesinin deðerini 5'e ayarladýðý gibi görünüyor mu?
Anahtar Bilgi
Özel veri üyelerini "m_" ile öne çýkarmak için en iyi nedenlerden biri, veri üyeleri ve getter'larýn ayný adý taþýmasýný 
önlemektir (C++ bunu desteklemez, ancak Java gibi diðer diller yapar).

Yalnýzca "set" öneki:

                int day() const { return m_day; }     // getter
                void setDay(int day) { m_day = day; } // setter

Yukarýdakilerden hangisini seçeceðiniz kiþisel tercihinize baðlýdýr. Ancak, setter'lar için "set" önekini kullanmanýzý þiddetle 
öneririz. Getter'lar ya "get" öneki veya hiç önek kullanabilir.

Ýpucu

Setter'larýnýza "set" öneki ekleyin, böylece nesnenin durumunu deðiþtirdikleri daha belirgin hale gelir.
Getter'lar deðeri veya const lvalue referansýný döndürmelidir.
Getter'lar verilere "salt okunur" eriþim saðlamalýdýr. Bu nedenle, en iyi uygulama, üyenin bir kopyasýný yapmanýn ucuz olup
olmadýðýna baðlý olarak ya deðeri ya da const lvalue referansýný döndürmeleridir.

Eriþim Fonksiyonlarýna Ýliþkin Endiþeler
----------------------------------------
Eriþim fonksiyonlarýnýn ne zaman kullanýlmasý veya kaçýnýlmasý gerektiði konusunda oldukça fazla tartýþma vardýr. Birçok
geliþtirici, eriþim fonksiyonlarýnýn kullanýlmasýnýn iyi sýnýf tasarýmýný ihlal ettiðini savunur (bu konu kolaylýkla tüm bir 
kitabý doldurabilir).
Þimdilik, pragmatik bir yaklaþým öneriyoruz. Sýnýflarýnýzý oluþtururken aþaðýdakileri göz önünde bulundurun:

- Sýnýfýnýzýn deðiþmezleri yoksa ve çok sayýda eriþim fonksiyonuna ihtiyaç duyuyorsa, bir yapý kullanmayý düþünün 
  (veri üyeleri geneldir) ve üyelere doðrudan eriþim saðlayýn.
- Eriþim fonksiyonlarý yerine davranýþlarý veya eylemleri uygulamayý tercih edin. Örneðin, setAlive(bool) setter'ý yerine bir 
  kill() ve revive() fonksiyonu uygulayýn.
- Yalnýzca genelin makul bir þekilde bir bireysel üyenin deðerini almasý veya ayarlamasý gereken durumlarda eriþim fonksiyonlarý
  saðlayýn.

Eðer public bir eriþim fonksiyonu saðlayacaksak verileri neden gizli tutalým ki?

14.7 — Veri üyelerine referans döndüren member iþlevler
----------------------------------------------------
12.12 dersinde -- Referansla dönme ve adresle dönme, referansla dönme konusunu ele aldýk. Özellikle, “Referansla döndürülen 
nesnenin fonksiyon döndükten sonra da var olmasý gerektiðini” belirttik. Bu, yerel deðiþkenleri referans olarak döndürmememiz 
gerektiði anlamýna gelir, çünkü yerel deðiþken yok edildikten sonra referans sallanýr durumda kalýr. Ancak, genellikle referansla
döndürülen fonksiyon parametreleri veya statik süreye sahip deðiþkenler (statik yerel deðiþkenler veya global deðiþkenler) genellikle
fonksiyon döndükten sonra yok edilmezler.

Örneðin:

                // Ýki std::string nesnesi alýr, alfabetik olarak önce geleni döndürür
                const std::string& firstAlphabetical(const std::string& a, const std::string& b)
                {
                    return (a < b) ? a : b; // std::string üzerinde operator< kullanarak hangisinin alfabetik olarak önce geldiðini
                                            // belirleyebiliriz
                }

                int main()
                {
                    std::string hello { "Hello" };
                    std::string world { "World" };

                    std::cout << firstAlphabetical(hello, world); // hello veya world referansla döndürülür

                    return 0;
                }
member fonksiyonlar de referansla döndürebilir ve referansla döndürmenin güvenli olduðu durumlar için member olmayan fonksiyonlarla ayný 
kurallarý izlerler. Ancak, member fonksiyonlarýn tartýþmamýz gereken bir ek durumu vardýr: veri üyelerini referansla döndüren member 
fonksiyonlar.
Bu, en sýk getter eriþim fonksiyonlarýyla görülür, bu yüzden bu konuyu getter member fonksiyonlarý kullanarak örneklendireceðiz. 
Ancak, bu konunun bir veri üyesine referans döndüren herhangi bir member fonksiyon için geçerli olduðunu unutmayýn.

Veri üyelerini deðerle döndürmek pahalý olabilir
------------------------------------------------
Aþaðýdaki örneði düþünün:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    std::string getName() const { return m_name; } //  getter deðerle döndürür
                };

                int main()
                {
                    Employee joe{};
                    joe.setName("Joe");
                    std::cout << joe.getName();

                    return 0;
                }

Bu örnekte, getName() eriþim fonksiyonu std::string m_name'i deðerle döndürür. Bu yapýlacak en güvenli þey olsa da, bu ayný 
zamanda getName() her çaðrýldýðýnda m_name'in pahalý bir kopyasýnýn yapýlacaðý anlamýna gelir. Eriþim fonksiyonlarýnýn genellikle
çokça çaðrýldýðý göz önüne alýndýðýnda, bu genellikle en iyi seçenek deðildir.

Veri üyelerini lvalue referansýyla döndürme
-------------------------------------------
member fonksiyonlar, veri üyelerini de (const) lvalue referansýyla döndürebilir.

Veri üyeleri, içinde bulunduklarý nesnenin ayný ömrüne sahiptir. member fonksiyonlar her zaman bir nesne üzerinde çaðrýldýðýndan ve
bu nesnenin çaðýranýn kapsamýnda var olmasý gerektiðinden, bir member fonksiyonun bir veri üyesini (const) lvalue referansýyla döndürmesi
genellikle güvenlidir (fonksiyon döndüðünde çaðýranýn kapsamýnda hala var olan member referansla döndürülür).

Yukarýdaki örneði güncelleyelim, böylece getName() m_name'i const lvalue referansýyla döndürsün:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const std::string& getName() const { return m_name; } //  getter const referansla döndürür
                };

                int main()
                {
                    Employee joe{}; // joe fonksiyonun sonuna kadar var olur
                    joe.setName("Joe");

                    std::cout << joe.getName(); // joe.m_name'i referansla döndürür

                    return 0;
                }
Þimdi joe.getName() çaðrýldýðýnda, joe.m_name çaðýrana referansla döndürülür, böylece bir kopya yapma ihtiyacýný ortadan kaldýrýr.
Çaðýran daha sonra bu referansý joe.m_name'i konsola yazdýrmak için kullanýr.
Joe, çaðýranýn kapsamýnda main() iþlevinin sonuna kadar var olduðu için, joe.m_name'e olan referans da ayný süre boyunca geçerlidir.

Ana içgörü

Bir veri üyesine (const) lvalue referansý döndürmek tamamdýr. Fonksion döndükten sonra çaðýranýn kapsamýnda hala var olan içsel 
nesne (veri üyesini içeren), herhangi bir döndürülen referansýn geçerli olmasýný saðlar.
Bir member fonksiyonun bir veri üyesine referans döndürmesi durumunda, dönüþ türü veri üyesinin türüyle eþleþmelidir

public olarak, referansla döndüren bir member fonksiyonun dönüþ türü, döndürülen veri üyesinin türüyle eþleþmelidir. Yukarýdaki 
örnekte, m_name std::string türündedir, bu yüzden getName() const std::string& döndürür.

Bir std::string_view döndürmek, her fonksiyon çaðrýldýðýnda geçici bir std::string_view oluþturulmasýný ve döndürülmesini
gerektirir. Bu gereksiz yere verimsizdir. Eðer çaðýran bir std::string_view istiyorsa, dönüþümü kendisi yapabilir.

**** BEST -> Bir referans döndüren bir member fonksiyon, gereksiz dönüþümleri önlemek için döndürülen veri üyesiyle ayný türde bir 
             referans döndürmelidir.

Getter'lar için, derleyicinin döndürülen üyeden dönüþ türünü çýkarmasýný saðlamak için auto kullanmak, dönüþüm olmadýðýndan emin 
olmanýn kullanýþlý bir yoludur:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } // `auto` kullanarak m_name'den dönüþ türünü çýkarýr
                };

                int main()
                {
                    Employee joe{}; // joe, fonksiyonun sonuna kadar var olur
                    joe.setName("Joe");

                    std::cout << joe.getName(); // joe.m_name'i referans olarak döndürür

                    return 0;
                }
Ancak, bir auto dönüþ türü kullanmak, getter'ýn dönüþ türünü belgelendirme açýsýndan belirsizleþtirir. Örneðin:

                const auto& getName() const { return m_name; } // `auto` kullanarak m_name'den dönüþ türünü çýkarýr

Bu fonksiyonun aslýnda ne türde bir dize döndürdüðü belirsizdir (std::string, std::string_view, C tarzý dize veya tamamen farklý
bir þey olabilir!). Bu nedenle, genellikle açýk dönüþ türlerini tercih ederiz.

Rvalue Geçici Nesneler ve Referansla Dönüþ
------------------------------------------
Biraz dikkatli olmamýz gereken bir durum var. Yukarýdaki örnekte, joe fonksiyonun sonuna kadar var olan bir lvalue nesnesidir. 
Bu nedenle, joe.getName() tarafýndan döndürülen referans da fonksiyonun sonuna kadar geçerli olacaktýr.

Peki ya geçici nesnemiz bir rvalue ise (örneðin, deðer döndüren bir fonksiyonun dönüþ deðeri gibi)? Rvalue nesneler,
oluþturulduklarý tam ifadenin sonunda yok edilir. Bir rvalue nesnesi yok edildiðinde, bu rvalue'un üyelerine olan herhangi bir
referans geçersiz kýlýnýr ve sallanýr kalýr ve bu tür referanslarýn kullanýlmasý tanýmsýz davranýþa yol açar.

Bu nedenle, bir rvalue nesnesinin bir üyesine olan bir referans, yalnýzca rvalue nesnesinin oluþturulduðu tam ifade içinde güvenle
kullanýlabilir.

Uyarý

Bir rvalue nesnesi, oluþturulduðu tam ifadenin sonunda yok edilir. Rvalue nesnesinin üyelerine olan herhangi bir referans o 
noktada sallanýr kalýr. Bir rvalue nesnesinin bir üyesine olan bir referans, yalnýzca rvalue nesnesinin oluþturulduðu tam ifade 
içinde güvenle kullanýlabilir.
Bu konuyla ilgili bazý durumlarý inceleyelim:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } //  getter const referans olarak döndürür
                };

                // createEmployee() bir Çalýþan'ý deðer olarak döndürür (bu, döndürülen deðerin bir rvalue olduðu anlamýna gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    // Durum 1: tamam: rvalue sýnýf nesnesinin üyesine dönen referansý ayný ifadede kullan
                    std::cout << createEmployee("Frank").getName();

                    // Durum 2: kötü: rvalue sýnýf nesnesinin üyesine dönen referansý daha sonra kullanmak üzere kaydet
                    const std::string& ref { createEmployee("Garbo").getName() }; // createEmployee()'ýn dönüþ deðeri yok 
                                                                                  // edildiðinde referans dangling olur
                    std::cout << ref; // undefined behavior

                    // Durum 3: tamam: referansla dönen deðeri daha sonra kullanmak üzere yerel deðiþkene kopyala
                    std::string val { createEmployee("Hans").getName() }; // referanslanan üyenin bir kopyasýný yapar
                    std::cout << val; // okay: val is independent of referenced member

                    return 0;
                }

createEmployee() çaðrýldýðýnda, bir Employee nesnesini deðer olarak döndürecektir. Bu döndürülen Employee nesnesi, createEmployee()
çaðrýsýný içeren tam ifadenin sonuna kadar var olacaktýr. Bu rvalue nesnesi yok edildiðinde, bu nesnenin üyelerine olan herhangi
bir referans dangling olacaktýr.

Durum 1'de, createEmployee("Frank")'i çaðýrýyoruz, bu bir rvalue Employee nesnesi döndürür. Daha sonra bu rvalue nesnesinde
getName() çaðrýsý yaparýz, bu m_name'e bir referans döndürür. Bu referans hemen ardýndan konsola ismi yazdýrmak için kullanýlýr. 
Bu noktada, createEmployee("Frank") çaðrýsýný içeren tam ifade sona erer ve rvalue nesnesi ve üyeleri yok edilir. Bu noktadan
sonra rvalue nesnesi veya üyeleri kullanýlmadýðýndan, bu durum sorunsuzdur.

Durum 2'de, sorunlarla karþýlaþýyoruz. Öncelikle, createEmployee("Garbo") bir rvalue nesnesi döndürür. Daha sonra getName() 
çaðrýsý yaparak bu rvalue'nin m_name üyesine bir referans alýrýz. Bu m_name üyesi daha sonra ref'i baþlatmak için kullanýlýr.
Bu noktada, createEmployee("Garbo") çaðrýsýný içeren tam ifade sona erer ve rvalue nesnesi ve üyeleri yok edilir. Bu, ref'in
dangling kalmasýna neden olur. Dolayýsýyla, sonraki ifadede ref'i kullandýðýmýzda, dangling bir referansa eriþiyoruz ve tanýmsýz
bir davranýþ sonucu oluþur.

Anahtar Ýçgörü

Bir tam ifadenin deðerlendirilmesi, bu tam ifadenin bir baþlatýcý olarak kullanýlmasýndan sonra sona erer. Bu, nesnelerin ayný
türden bir rvalue ile baþlatýlmasýna izin verir (çünkü rvalue, baþlatma gerçekleþtikten sonra yok edilmez).

Peki ya daha sonra kullanmak üzere bir üyeyi referansla döndüren bir fonksiyondan bir deðer kaydetmek istiyorsak ne olur?
-------------------------------------------------------------------------------------------------------------------------
Döndürülen referansý yerel bir referans deðiþkenini baþlatmak yerine, döndürülen referansý referans olmayan bir yerel deðiþkeni
baþlatmak için kullanabiliriz.
Durum 3'te, döndürülen referansý referans olmayan yerel deðiþken val'i baþlatmak için kullanýyoruz. Bu, referanslanan üyenin val
içine kopyalanmasýna neden olur. Baþlatmadan sonra, val referanstan baðýmsýz olarak var olur. Bu nedenle, rvalue nesnesi sonradan
yok edildiðinde, val bu durumdan etkilenmez. Bu nedenle, val, gelecekteki ifadelerde sorunsuz bir þekilde çýktý olarak
kullanýlabilir.

Referansla döndüren member iþlevlerini güvenli bir þekilde kullanma
----------------------------------------------------------------
Rvalue içsel nesnelerle potansiyel tehlikeye raðmen, getter'larýn deðerle deðil, const referansla döndürme konusunda pahalý olan
türleri döndürmesi gelenekseldir.
Bu durumda, bu tür iþlevlerden dönen deðerleri nasýl güvenli bir þekilde kullanabileceðimizi konuþalým. Yukarýdaki örnekteki üç 
durum, üç ana noktayý göstermektedir:

Referansla döndüren bir member fonksiyonun dönüþ deðerini hemen kullanmayý tercih edin (durum 1'de gösterildiði gibi). Bu, hem lvalue
hem de rvalue nesnelerle çalýþtýðýndan, bunu her zaman yaparsanýz, sorunlardan kaçýnmýþ olursunuz.

Döndürülen bir referansý daha sonra kullanmak için "kaydetmeyin" (durum 2'de gösterildiði gibi), içsel nesnenin bir lvalue
olduðundan emin olmadýkça. Eðer bunu bir rvalue içsel nesne ile yaparsanýz, artýk sallanan referansý kullandýðýnýzda tanýmsýz bir
davranýþ ortaya çýkar.

Eðer döndürülen bir referansý daha sonra kullanmak için saklamanýz gerekiyorsa ve içsel nesnenin bir lvalue olduðundan emin 
deðilseniz, döndürülen referansý bir referans olmayan yerel deðiþkenin baþlatýcýsý olarak kullanýn, bu da referansla döndürülen 
üyenin yerel deðiþkene bir kopyasýný yapar (durum 3'te gösterildiði gibi).

**** BEST -> Bir member fonksiyonun dönüþ deðerini hemen kullanmayý tercih edin, içsel nesne bir rvalue olduðunda sallanan 
             referanslarla ilgili sorunlarý önlemek için.

Özel veri üyelerine non-const referanslarý döndürmeyin
------------------------------------------------------
Bir referans, referansý alýnan nesnenin aynýsý gibi davrandýðýndan, non-const bir referans döndüren bir member iþlev, o üyeye
doðrudan eriþim saðlar (member özel olsa bile).

Örneðin:

                #include <iostream>

                class Foo
                {
                private:
                    int m_value{ 4 }; // özel üye

                public:
                    auto& value() { return m_value; } // non-const bir referans döndürür (bunu yapmayýn)
                };

                int main()
                {
                    Foo f{};                // f.m_value varsayýlan deðer 4'e baþlatýlýr
                    f.value() = 5;          // m_value = 5'in eþdeðeri
                    std::cout << f.value(); // 5 yazdýrýr

                    return 0;
                }

Value() fonksiyonu m_value'ya non-const bir referans döndürdüðü için, çaðýran bu referansý kullanarak m_value'ya doðrudan
eriþebilir (ve m_value'nun deðerini deðiþtirebilir). Bu, çaðýranýn eriþim kontrol sistemini atlatmasýna izin verir.

Const member fonksiyonlar, veri üyelerine non-const referanslarý döndüremez
------------------------------------------------------------------------
Bir const member iþlevin, üyelere non-const bir referans döndürmesine izin verilmez. Bu mantýklýdýr - bir const member iþlevin,
nesnenin durumunu deðiþtirmesine izin verilmez, ne de nesnenin durumunu deðiþtirecek fonksiyonlarý çaðýrmasýna izin verilir. Nesnenin
deðiþtirilmesine yol açabilecek herhangi bir þey yapmamalýdýr.

Eðer bir const member iþlevin, bir üyeye non-const bir referans döndürmesine izin verilseydi, çaðýraya o üyeyi doðrudan deðiþtirme
yolunu vermiþ olurdu. Bu, bir const member fonksiyonun amacýna aykýrýdýr.

14.8 — Veri Gizlemenin (Kapsülleme) Faydalarý
---------------------------------------------
Bir önceki dersimizde (14.5 -- Public ve private üyeler ve eriþim belirleyiciler), bir sýnýfýn member deðiþkenlerinin genellikle
private yapýldýðýný belirtmiþtik. Sýnýflar hakkýnda ilk kez öðrenen programcýlar, bunu neden yapmak isteyeceðinizi anlamakta 
genellikle zorlanýrlar. Sonuçta, deðiþkenlerinizi private yapmak, bunlarýn public eriþime açýk olmamasý anlamýna gelir.
En iyi ihtimalle, sýnýflarýnýzý yazarken daha fazla iþ yapmanýz gerekecektir. En kötü ihtimalle, bu tamamen anlamsýz görünebilir
(özellikle private member verilerine public eriþim fonksiyonlarý saðlýyorsak).

Bu sorunun yanýtý o kadar temel ki, bu konuda tüm bir dersi harcayacaðýz!

Bir benzetmeyle baþlayalým.

Modern hayatta, birçok mekanik veya elektronik cihaza eriþimimiz var. Televizyonunuzu bir uzaktan kumanda ile açýp kapatýrsýnýz.
Arabanýzý gaz pedalýna basarak ileri hareket ettirirsiniz. Iþýklarýnýzý bir anahtar çevirerek açarsýnýz. Tüm bu cihazlarýn ortak
bir özelliði var: Size, anahtar eylemleri gerçekleþtirmenizi saðlayan basit bir kullanýcý arayüzü (bir dizi düðme, bir pedal, bir
anahtar vb.) sunarlar.

Bu cihazlarýn nasýl çalýþtýðý sizden gizlenmiþtir. Uzaktan kumandanýzdaki düðmeye bastýðýnýzda, kumandanýn televizyonunuzla nasýl
iletiþim kurduðunu bilmenize gerek yoktur. Arabanýzdaki gaz pedalýna bastýðýnýzda, içten yanmalý motorun tekerlekleri nasýl 
çevirdiðini bilmenize gerek yoktur. Bir fotoðraf çektiðinizde, sensörlerin ýþýðý nasýl topladýðýný ve bu ýþýðý pikselleþtirilmiþ 
bir görüntmember nasýl dönüþtürdüðünü bilmenize gerek yoktur.

Arayüz ve uygulamanýn ayrýlmasý, nesneleri nasýl çalýþtýklarýný anlamadan kullanmamýza izin verir - bunun yerine, onlarla nasýl
etkileþim kuracaðýmýzý anlamamýz yeterlidir. Bu, bu nesneleri kullanmanýn karmaþýklýðýný büyük ölçüde azaltýr ve etkileþime 
girebileceðimiz nesne sayýsýný artýrýr.

Sýnýf türlerinde uygulama ve arayüzler
--------------------------------------
Benzer nedenlerle, arayüz ve uygulamanýn ayrýlmasý programlamada da yararlýdýr. Ancak önce, sýnýf türleriyle ilgili olarak arayüz
ve uygulama ne demek, onu tanýmlayalým.

Bir sýnýf türünün arayüzü, bir sýnýf türünün kullanýcýsýnýn sýnýf türünün nesneleriyle nasýl etkileþim kuracaðýný tanýmlar.
Yalnýzca public üyelere sýnýf türünün dýþýndan eriþilebildiði için, bir sýnýf türünün public üyeleri, onun arayüzünü oluþturur. 
Bu nedenle, public üyelerden oluþan bir arayüz bazen public arayüz olarak adlandýrýlýr.

Bir arayüz, bir sýnýfýn yazarý ile sýnýfýn kullanýcýsý arasýnda implicit bir sözleþmedir. Mevcut bir arayüz herhangi bir þekilde 
deðiþtirilirse, onu kullanan herhangi bir kod bozulabilir. Bu nedenle, sýnýf türlerimiz için arayüzlerin iyi tasarlanmýþ ve stabil
(çok fazla deðiþmeyen) olmasýný saðlamak önemlidir.

Bir sýnýf türünün uygulamasý, sýnýfýn istendiði gibi davranmasýný saðlayan kodu içerir. Bu, hem verileri depolayan üye
deðiþkenleri hem de program mantýðýný içeren ve member deðiþkenleri manipüle eden member fonksiyonlarýnýn gövdelerini içerir.

Veri Gizleme (Kapsülleme)
-------------------------
Programlamada, veri gizleme (ayný zamanda bilgi gizleme veya veri soyutlama olarak da adlandýrýlýr), bir program tanýmlý veri 
türünün uygulamasýný kullanýcýlardan gizleyerek arayüz ve uygulamanýn ayrýlmasýný saðlamak için kullanýlan bir tekniktir.

Terimler
--------
Kapsülleme terimi bazen veri gizlemeyi ifade etmek için de kullanýlýr. Ancak, bu terim ayný zamanda verilerin ve fonksiyonlarýn
bir araya getirilmesini (eriþim kontrollerine bakýlmaksýzýn) ifade etmek için de kullanýlýr, bu yüzden kullanýmý belirsiz olabilir.
Bu ders serisinde, tüm kapsüllenmiþ sýnýflarýn veri gizlemeyi uyguladýðýný varsayacaðýz.
Veri gizleme, bir C++ sýnýf türünde uygulamak basittir.

Öncelikle, sýnýf türünün veri üyelerinin özel (private) olduðundan emin oluruz (böylece kullanýcý bunlara doðrudan eriþemez).
member fonksiyonlarýnýn gövdelerindeki ifadeler zaten kullanýcýlara doðrudan eriþilemez, bu yüzden baþka bir þey yapmamýza gerek yok.

Ýkinci olarak, member fonksiyonlarýn public (public) olduðundan emin oluruz, böylece kullanýcý onlarý çaðýrabilir.

Bu kurallarý takip ederek, bir sýnýf türünün kullanýcýsýný nesneleri public arayüzü kullanarak manipüle etmeye zorlarýz ve onlarý
uygulama ayrýntýlarýna doðrudan eriþmekten alýkoyarýz.

C++'da tanýmlanan sýnýflarýn veri gizlemeyi kullanmasý gerekmektedir. Aslýnda, standart kütüphane tarafýndan saðlanan tüm sýnýflar
tam olarak bunu yapar. Diðer yandan, yapýlar (structs) veri gizlemeyi kullanmamalýdýr, çünkü public olmayan üyelere sahip olmak
onlarýn topluluklar (aggregates) olarak ele alýnmasýný engeller.

Sýnýflarý bu þekilde tanýmlamak, sýnýf yazarý için biraz ekstra iþ gerektirir. Ve sýnýfýn kullanýcýlarýnýn public arayüzü
kullanmasýný gerektirmek, member deðiþkenlere doðrudan public eriþim saðlamaktan daha zahmetli görünebilir. Ancak bunu yapmak, 
sýnýfýn yeniden kullanýlabilirliðini ve bakýmýný teþvik eden birçok yararlý fayda saðlar. Bu faydalarý tartýþmak için dersin geri
kalanýný harcayacaðýz.

Veri gizleme, sýnýflarý daha kolay kullanýlabilir hale getirir ve karmaþýklýðý azaltýr
--------------------------------------------------------------------------------------
Bir sýnýfý kullanmak için, nasýl uygulandýðýný bilmek zorunda deðilsiniz. Yalnýzca arayüzünü anlamanýz gerekir: hangi üye
fonksiyonlarýn public olarak kullanýlabilir olduðu, hangi argümanlarý aldýklarý ve hangi deðerleri döndürdükleri. Örneðin:

                #include <iostream>
                #include <string_view>

                int main()
                {
                    std::string_view sv{ "Merhaba, dünya!" };
                    std::cout << sv.length();

                    return 0;
                }
Bu kýsa programda, std::string_view'in nasýl uygulandýðýna dair ayrýntýlar bize açýklanmaz. Bir std::string_view'in kaç tane veri
üyesi olduðunu, ne olduklarýný, ne adlandýrýldýklarýný veya ne tür olduklarýný göremeyiz. length() member fonksiyonunun görüntülenen
dizenin uzunluðunu nasýl döndürdüðünü bilmiyoruz.

Ve harika olan kýsmý, bilmemiz gerekmiyor! Program sadece çalýþýr. Tek ihtiyacýmýz olan, std::string_view türünde bir nesneyi
nasýl baþlatacaðýmýzý ve length() member fonksiyonunun ne döndürdüðünü bilmektir.

Bu tür ayrýntýlar hakkýnda endiþelenmek zorunda olmamak, programlarýnýzýn karmaþýklýðýný dramatik bir þekilde azaltýr, bu da
hatalarý azaltýr. Diðer tüm nedenlerden daha fazla, bu, kapsüllemenin ana avantajýdýr.

std::string, std::vector veya std::cout'un nasýl uygulandýðýný anlamanýz gerektiðini düþünün, onlarý kullanabilmek için C++ ne
kadar daha karmaþýk olurdu!

Veri gizleme, deðiþmezleri korumamýza olanak saðlar
---------------------------------------------------
Sýnýflara giriþ dersinde (14.2 -- Sýnýflara Giriþ), sýnýf deðiþmezleri kavramýný tanýttýk. Bunlar, bir nesnenin geçerli bir durumda
kalabilmesi için nesnenin ömrü boyunca doðru olmasý gereken koþullardýr.

Aþaðýdaki programý düþünün:

                #include <iostream>
                #include <string>

                struct Employee // üyeler varsayýlan olarak public'tir
                {
                    std::string name{ "John" };
                    char firstInitial{ 'J' }; // name'in ilk harfiyle eþleþmelidir

                    void print() const
                    {
                        std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
                    }
                };

                int main()
                {
                    Employee e{}; // varsayýlan olarak "John" ve 'J'
                    e.print();

                    e.name = "Mark"; // employee'nin adýný "Mark" olarak deðiþtir
                    e.print(); // yanlýþ harfi yazdýrýr

                    return 0;
                }

                Bu program þunu yazdýrýr:

                John has first initial J
                Mark has first initial J
Employee struct'ýmýzýn bir sýnýf deðiþmezi vardýr ki bu da firstInitial'ýn her zaman name'in ilk karakterine eþit olmasý 
gerektiðidir. Eðer bu hiçbir zaman doðru olmazsa, print() fonksiyonu hatalý çalýþýr.

Name üyesi public olduðu için, main() içindeki kod e.name'i "Mark" olarak ayarlayabilir ve firstInitial üyesi güncellenmez. 
Deðiþmezimiz bozulmuþ olur ve ikinci print() çaðrýmýz beklediðimiz gibi çalýþmaz.

Kullanýcýlara bir sýnýfýn uygulamasýna doðrudan eriþim hakký verdiðimizde, tüm deðiþmezleri korumaktan onlar sorumlu olur -- ki 
bunu doðru bir þekilde veya hiç yapmayabilirler. Bu, kullanýcý üzerinde çok fazla karmaþýklýk yaratýr.

Bu programý yeniden yazalým, member deðiþkenlerimizi private yapalým ve bir Employee'nin adýný ayarlamak için bir member fonksiyonu
açýða çýkaralým:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee // üyeler varsayýlan olarak private'tir
                {
                    std::string m_name{};
                    char m_firstInitial{};

                public:
                    void setName(std::string_view name)
                    {
                        m_name = name;
                        m_firstInitial = name.front(); // `name`in ilk harfini almak için std::string::front() kullanýr
                    }

                    void print() const
                    {
                        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
                    }
                };

                int main()
                {
                    Employee e{};
                    e.setName("John");
                    e.print();

                    e.setName("Mark");
                    e.print();

                    return 0;
                }
                
                Bu program artýk beklenildiði gibi çalýþýr:
                John has first initial J
                Mark has first initial M
Kullanýcýnýn perspektifinden tek deðiþiklik, name'e doðrudan bir deðer atamak yerine, setName() member iþlevini çaðýrýyor olmalarýdýr,
bu fonksiyon hem m_name'i hem de m_firstInitial'ý ayarlar. Kullanýcýnýn bu deðiþmezi koruma yükü ortadan kalkar!

Veri gizleme, daha iyi hata tespiti (ve iþlemesi) yapmamýza olanak saðlar
-------------------------------------------------------------------------
Yukarýdaki programda, m_firstInitial'ýn m_name'in ilk karakteriyle eþleþmesi gerektiði deðiþmezi, m_firstInitial'ýn m_name'den 
baðýmsýz olarak var olmasý nedeniyle vardýr. Bu belirli deðiþmezi, m_firstInitial'ý ilk harfi döndüren bir member iþlevle 
deðiþtirerek kaldýrabiliriz:

                #include <iostream>
                #include <string>

                class Employee
                {
                    std::string m_name{ "John" };

                public:
                    void setName(std::string_view name)
                    {
                        m_name = name;
                    }

                    // `m_name`in ilk harfini almak için std::string::front() kullanýr
                    char firstInitial() const { return m_name.front(); }

                    void print() const
                    {
                        std::cout << "Employee " << m_name << " has first initial " << firstInitial() << '\n';
                    }
                };

                int main()
                {
                    Employee e{}; // varsayýlan olarak "John"
                    e.setName("Mark");
                    e.print();

                    return 0;
                }
Ancak, bu programýn baþka bir sýnýf deðiþmezi var. Bir an durun ve ne olduðunu belirlemeye çalýþýn. Burada bekleriz ve bu kuru 
boyayý izleriz...

Cevap, m_name'in boþ bir string olmamasý gerektiðidir (çünkü her Employee'nin bir adý olmalýdýr). Eðer m_name boþ bir string 
olarak ayarlanýrsa, hemen kötü bir þey olmaz. Ancak daha sonra firstInitial() çaðrýlýrsa, std::string'in front() üyesi boþ 
stringin ilk harfini almayý deneyecek ve bu tanýmsýz bir davranýþa yol açacaktýr.bÝdeal olarak, m_name'in hiçbir zaman boþ
olmamasýný isteriz.

Eðer kullanýcýnýn m_name üyesine public eriþimi olsaydý, sadece m_name = "" diyebilirlerdi ve bunun olmasýný engelleyecek hiçbir
þey yapamazdýk.

Ancak, kullanýcýyý m_name'i public arayüz fonksiyonu setName() aracýlýðýyla ayarlamaya zorladýðýmýz için, setName() kullanýcýnýn 
geçerli bir ad geçtiðini doðrulayabilir. Eðer ad boþ deðilse, o zaman onu m_name'e atayabiliriz. Eðer ad boþ bir string ise,
bir dizi þey yapabiliriz mesela:

*- Adý "" olarak ayarlamak için yapýlan isteði görmezden gelin ve çaðýraya dönün.
*- Assert çýkýþý yapýn.
*- Bir istisna fýrlatýn.
*- Hokey pokey yapýn. Bekleyin, bu deðil. :))

Buradaki nokta, kötmember kullanmayý tespit edebiliriz ve sonra onu en uygun olduðunu düþündüðümüz þekilde ele alabiliriz. Bu tür
durumlarý nasýl etkili bir þekilde ele alacaðýmýz baþka bir günün konusudur.

Veri gizleme, uygulama ayrýntýlarýný deðiþtirmeyi, mevcut programlarý bozmadan mümkün kýlar
-------------------------------------------------------------------------------------------
Bu basit örneði düþünün:

                #include <iostream>

                struct Something
                {
                    int value1 {};
                    int value2 {};
                    int value3 {};
                };

                int main()
                {
                    Something something;
                    something.value1 = 5;
                    std::cout << something.value1 << '\n';
                }
Bu program iyi çalýþýrken, sýnýfýn uygulama ayrýntýlarýný þu þekilde deðiþtirmeye karar verirsek ne olurdu?

                #include <iostream>

                struct Something
                {
                    int value[3] {}; // 3 deðerli bir dizi kullanýr
                };

                int main()
                {
                    Something something;
                    something.value1 = 5;
                    std::cout << something.value1 << '\n';
                }

Henüz dizileri ele almadýk, ama bundan endiþelenmeyin. Buradaki nokta, bu programýn artýk derlenmemesi çünkü value1 adlý member artýk
var olmamasý ve main() içindeki bir ifadenin hala bu tanýmlayýcýyý kullanýyor olmasýdýr.

Veri gizleme, sýnýflarýn nasýl uygulandýðýný deðiþtirme yeteneði saðlar, bunu kullanýlan programlarý bozmadan yapar.
--------------------------------------------------------------------------------------------------------------------
Ýþte m_value1'e eriþmek için fonksiyonlarý kullanan bu sýnýfýn orijinal sürümünün kapsüllenmiþ versiyonu:

                #include <iostream>

                class Something
                {
                private:
                    int m_value1 {};
                    int m_value2 {};
                    int m_value3 {};

                public:
                    void setValue1(int value) { m_value1 = value; }
                    int getValue1() const { return m_value1; }
                };

                int main()
                {
                    Something something;
                    something.setValue1(5);
                    std::cout << something.getValue1() << '\n';
                }
Þimdi, sýnýfýn uygulamasýný bir diziye geri döndürelim:

                #include <iostream>

                class Something
                {
                private:
                    int m_value[3]; // not: bu sýnýfýn uygulamasýný deðiþtirdik!

                public:
                    // Yeni uygulamayý yansýtacak þekilde tüm member fonksiyonlarý güncellememiz gerekiyor
                    void setValue1(int value) { m_value[0] = value; }
                    int getValue1() const { return m_value[0]; }
                };

                int main()
                {
                    // Ama sýnýfý kullanan programlarýmýzý güncellememize gerek yok!
                    Something something;
                    something.setValue1(5);
                    std::cout << something.getValue1() << '\n';
                }

Sýnýfýn public arayüzünü deðiþtirmediðimiz için, bu arayüzü kullanan programýmýz hiç deðiþmedi ve hala ayný þekilde iþlev görüyor.

Benzer þekilde, eðer gnomeler ( cüce ) gece evinize sýzýp TV kumandanýzýn içini farklý (ama uyumlu) bir teknolojiyle deðiþtirseydi, 
muhtemelen fark etmezdiniz!

Arayüzleri olan sýnýflarýn hata ayýklamasý daha kolaydýr
--------------------------------------------------------
Son olarak, kapsülleme, bir þeylerin yanlýþ gittiði durumlarda bir programýn hata ayýklamasýna yardýmcý olabilir. Genellikle bir
programýn doðru çalýþmamasýnýn nedeni, member deðiþkenlerimizden birinin yanlýþ bir deðer almasýdýr. Herkesin member deðiþkeni doðrudan
ayarlayabilmesi durumunda, hangi kod parçasýnýn aslýnda member deðiþkenini yanlýþ deðere deðiþtirdiðini bulmak zor olabilir. Bu, üye
deðiþkeni deðiþtiren her ifadeyi breakpoint'e getirebilir - ve bunlardan çok sayýda olabilir..

Ancak, bir member yalnýzca bir member fonksiyonu aracýlýðýyla deðiþtirilebiliyorsa, o zaman yalnýzca tek bir fonksiyonu kesme noktasýna
getirebilir ve her çaðrýnýn deðeri nasýl deðiþtirdiðini izleyebilirsiniz. Bu, suçlunun kim olduðunu belirlemeyi çok daha
kolaylaþtýrabilir.

member fonksiyonlar yerine Non-member fonksiyonlarý tercih edin
---------------------------------------------------------
Bir fonksiyon Non-member fonksiyon olarak uygulanabiliyorsa, onu bir member fonksiyon yerine Non-member fonksiyon olarak uygulamayý düþünün.
Bu, birçok avantaj saðlar:

*- Non-member fonksiyonlar, sýnýfýnýzýn arayüzünün bir parçasý deðildir. Bu nedenle, sýnýfýnýzýn arayüzü daha küçük ve daha basit olacak,
   bu da sýnýfýnýzý anlamayý kolaylaþtýracaktýr.
*- Non-member fonksiyonlar, kapsüllemeyi artýrýr, çünkü bu tür fonksiyonlar sýnýfýn public arayüzü aracýlýðýyla çalýþmalýdýr.
   Uygulamaya doðrudan eriþme konusunda bir cazibe yoktur, sadece bu uygun olduðu için.
*- Non-member fonksiyonlar, bir sýnýfýn uygulamasýna yapýlan deðiþiklikler yapýlýrken dikkate alýnmaz.
*- Non-member fonksiyonlarýn hata ayýklamasý genellikle daha kolaydýr.
Uygulamaya özgü veri ve mantýðý içeren Non-member fonksiyonlar, sýnýfýn yeniden kullanýlabilir bölümlerinden ayrýlabilir.
**** BEST -> Mümkün olduðunda, Fonksiyonlarý Non-member olarak uygulamayý tercih edin (özellikle uygulamaya özgü veri veya mantýðý
             içeren iþlevler).

Yazarýn notu

Örneklerimizin birçoðu, örnekleri mümkün olduðunca özlü tutmak amacýyla bu en iyi uygulamayý uygulamamaktadýr.

Ýþte en kötüden en iyiye doðru üç benzer örnek:

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }

                    // En kötüsü: print() member fonksiyonu, getter'ýn var olduðu halde m_flavor'a doðrudan eriþim kullanýr
                    void print() const
                    {
                        std::cout << "The yogurt has flavor " << m_flavor << '\n';
                    }
                };

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    y.print();

                    return 0;
                }
Yukarýdaki en kötü versiyondur. Print() member fonksiyonu, lezzet için zaten bir getter olduðunda m_flavor'a doðrudan eriþim 
kullanýr. Eðer sýnýfýn uygulamasý her zaman güncellenirse, print() de muhtemelen deðiþtirilmek zorunda kalacaktýr. Print() 
tarafýndan yazdýrýlan string, uygulamaya özgüdür (bu sýnýfý kullanan baþka bir uygulama baþka bir þey yazdýrmak isteyebilir, bu da
sýnýfýn klonlanmasýný veya deðiþtirilmesini gerektirecektir).

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }

                    // Daha iyi: print() member iþlevinin üyelere doðrudan eriþimi yok
                    void print(std::string_view prefix) const
                    {
                        std::cout << prefix << ' ' << getFlavor() << '\n';
                    }
                };

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    y.print("The yogurt has flavor");

                    return 0;
                }
Yukarýdaki versiyon daha iyidir, ancak hala harika deðildir. print() hala bir member fonksiyonu, ancak en azýndan artýk hiçbir
veri üyesine doðrudan eriþim yapmýyor. Eðer sýnýfýn uygulamasý her zaman güncellenirse, print()'in güncellenip güncellenmeyeceðini
belirlemek için deðerlendirilmesi gerekecektir (ama olmayacak). print() fonksiyonu için önek artýk parametrize edilmiþtir, bu da
öneki Non-member fonksiyon main() içine taþýmamýza olanak saðlar. Ancak fonksiyon hala þeylerin nasýl yazdýrýlacaðýna dair
kýsýtlamalar getirir (ör. her zaman önek, boþluk, lezzet, yeni satýr olarak yazdýrýr). Eðer bu, belirli bir uygulamanýn 
ihtiyaçlarýný karþýlamýyorsa, baþka bir fonksiyon eklenmesi gerekecektir.

                #include <iostream>
                #include <string>

                class Yogurt
                {
                    std::string m_flavor{ "vanilla" };

                public:
                    void setFlavor(std::string_view flavor)
                    {
                        m_flavor = flavor;
                    }

                    std::string_view getFlavor() const { return m_flavor; }
                };

                // En iyi: Non-member fonksiyon print() sýnýf arayüzünün bir parçasý deðildir
                void print(const Yogurt& y)
                {
                        std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
                }

                int main()
                {
                    Yogurt y{};
                    y.setFlavor("cherry");
                    print(y);

                    return 0;
                }
Yukarýdaki versiyon en iyisidir. print() artýk bir Non-member iþlev. Hiçbir üyeye doðrudan eriþim yapmaz. Eðer sýnýfýn uygulamasý
her zaman deðiþirse, print()'in hiçbir þekilde deðerlendirilmesine gerek kalmaz. Ek olarak, her uygulama kendi print() iþlevini
saðlayabilir ve tam olarak o uygulamanýn istediði þekilde yazdýrabilir.

Sýnýf member bildiriminin sýrasý
--------------------------------
Bir sýnýfýn dýþýnda kod yazarken, onlarý kullanmadan önce deðiþkenleri ve fonksiyonlarý bildirmemiz gereklidir. Ancak, bir sýnýfýn
içinde, bu kýsýtlama yoktur. 14.3 -- member Ýþlevler dersinde belirtildiði gibi, üyelerimizi istediðimiz herhangi bir sýrayla
sýralayabiliriz.

Peki onlarý nasýl sýralamalýyýz?
--------------------------------
Burada iki düþünce ekolü vardýr:

Önce özel üyelerinizi listeler, ardýndan public member iþlevlerinizi listeler. Bu, kullanmadan önce bildirme tarzýný izler.
Sýnýf kodunuza bakan herkes, veri üyelerinizi nasýl tanýmladýðýnýzý görür, bu da uygulama ayrýntýlarýný okumayý ve anlamayý
kolaylaþtýrabilir.

Önce public üyelerinizi listeler ve özel üyelerinizi en alta koyar. Sýnýfýnýzý kullanan biri public arayüzle ilgilendiði için, 
public üyelerinizi önce koymak, onlarýn ihtiyaç duyduklarý bilgileri en üste koyar ve uygulama ayrýntýlarýný (en az önemli 
olanlarý) sona koyar.

Modern C++'ta, ikinci yöntem (public üyeler önce gelir) genellikle diðer geliþtiricilerle paylaþýlacak kod için daha yaygýn olarak
önerilir.

**** BEST -> Önce public üyeleri, ardýndan protected üyeleri ve en son private üyeleri bildirin. Bu, public arayüzü öne çýkarýr ve
             uygulama ayrýntýlarýný önemsizleþtirir.

Yazarýn notu

Bu site üzerindeki örneklerin çoðu, önerilenin aksine bildirim sýrasýný kullanýr. Bu kýsmen tarihseldir, ancak ayrýca bu sýranýn,
dil mekaniklerini öðrenirken ve iþlerin nasýl çalýþtýðýný ayýklarken daha sezgisel olduðunu da buluyoruz.
*/