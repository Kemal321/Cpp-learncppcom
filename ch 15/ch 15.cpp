#include <iostream>

int main()
{
    return 0;
}
/*
15.1 — Gizli “this” iþaretçisi ve üye fonksiyon zincirleme
----------------------------------------------------------
Yeni programcýlarýn sýnýflar hakkýnda sýkça sorduðu sorulardan biri, "Bir üye fonksiyonu çaðrýldýðýnda, C++'ýn hangi nesnenin
üzerinde çaðrýldýðýný nasýl takip ettiði"dir.

Öncelikle, çalýþabileceðimiz basit bir sýnýf tanýmlayalým. Bu sýnýf, bir tam sayý deðerini kapsular ve bu deðeri almak ve 
ayarlamak için bazý eriþim fonksiyonlarý saðlar:

                #include <iostream>

                class Simple
                {
                private:
                    int m_id{};

                public:
                    Simple(int id)
                        : m_id{ id }
                    {
                    }

                    int getID() { return m_id; }
                    void setID(int id) { m_id = id; }

                    void print() { std::cout << m_id; }
                };

                int main()
                {
                    Simple simple{1};
                    simple.setID(2);

                    simple.print();

                    return 0;
                }

                Beklendiði gibi, bu program sonucu üretir:

                2
Bir þekilde, simple.setID(2); çaðrýsýný yaptýðýmýzda, C++ setID() fonksiyonunun simple nesnesi üzerinde çalýþmasý gerektiðini ve 
m_id'nin aslýnda simple.m_id'ye atýfta bulunduðunu biliyor.

Cevap, C++'ýn "this" adýnda gizli bir iþaretçi kullanmasýdýr! Bu derste, bu konuyu daha ayrýntýlý olarak inceleyeceðiz.

Gizli this iþaretçisi
---------------------
Her üye fonksiyonun içinde, this anahtar kelimesi, mevcut implicit nesnenin adresini tutan bir const iþaretçidir.
Çoðu zaman, this'i açýkça belirtmeyiz, ama kanýtlamak için belirtebiliriz:

                #include <iostream>

                class Simple
                {
                private:
                    int m_id{};

                public:
                    Simple(int id)
                        : m_id{ id }
                    {
                    }

                    int getID() { return m_id; }
                    void setID(int id) { m_id = id; }

                    void print() { std::cout << this->m_id; } // `this` iþaretçisini kullanarak örtülü nesneye eriþin ve
                                                              // operator-> ile m_id üyesini seçin
                };

                int main()
                {
                    Simple simple{ 1 };
                    simple.setID(2);

                    simple.print();

                    return 0;
                }

                Bu, önceki örnekle ayný þekilde çalýþýr ve yazdýrýr:

                2
Önceki iki örnekteki print() üye fonksiyonlarýnýn tamamen ayný þeyi yaptýðýna dikkat edin:


                void print() { std::cout << m_id; }       // this'in örtülü kullanýmý
                void print() { std::cout << this->m_id; } // this'in açýk kullanýmý

Ortaya çýktýðý üzere, birincisi ikincisinin kýsa yoludur. Programlarýmýzý derlediðimizde, derleyici, örtülü nesneyi referans 
veren herhangi bir üyeyi bu þekilde örtülü olarak öne alýr. Bu, kodumuzu daha özlü tutmamýza yardýmcý olur ve this->'yi açýkça
yazmak zorunda kalmadan tekrarlamayý önler.

Bir hatýrlatma -> Bir nesneye iþaret eden bir iþaretçiden bir üyeyi seçmek için -> kullanýrýz. this->m_id, (*this).m_id ile 
eþdeðerdir. Ýþaretçiler ve referanslarla üye seçimi konusunu 13.10 dersinde ele alýyoruz.

Peki this nasýl ayarlanýr?
--------------------------
Bu fonksiyon çaðrýsýna daha yakýndan bakalým:

                simple.setID(2);
Fonksiyon setID(2)'ye yapýlan çaðrýnýn sadece bir argümaný olduðu gibi görünse de, aslýnda iki argümaný vardýr! Derlendiðinde,
derleyici simple.setID(2); ifadesini aþaðýdaki gibi yeniden yazar:

                Simple::setID(&simple, 2); // simple'ýn bir nesne önekinden bir fonksiyon argümanýna dönüþtüðüne dikkat edin!
Bu artýk sadece standart bir fonksiyon çaðrýsýdýr ve simple nesnesi (daha önce bir nesne öneki olan) artýk fonksiyona bir argüman 
olarak adres üzerinden geçirilir.

Ama bu sadece yanýtýn yarýsý. Fonksiyon çaðrýsýnýn artýk ek bir argümaný olduðundan, üye fonksiyon tanýmý da bu argümaný bir 
parametre olarak kabul etmek (ve kullanmak) için deðiþtirilmelidir. Ýþte setID() için orijinal üye fonksiyon tanýmýmýz:

                void setID(int id) { m_id = id; }
Derleyicinin fonksiyonlarý nasýl yeniden yazdýðý, uygulamaya özgü bir ayrýntýdýr, ancak sonuç þuna benzer bir þeydir:

                static void setID(Simple* const this, int id) { this->m_id = id; }
setID fonksiyonumuzun yeni bir en sol parametresi olan this olduðuna dikkat edin, bu bir const iþaretçidir (yani yeniden 
iþaret edilemez, ancak iþaretçinin içeriði deðiþtirilebilir). m_id üyesi de this->m_id olarak yeniden yazýlmýþtýr, bu iþaretçiyi 
kullanýr.

Ýleri düzey okuyucular için

Bu baðlamda, static anahtar kelimesi, fonksiyonun sýnýfýn nesneleriyle iliþkili olmadýðý anlamýna gelir, ancak bunun yerine 
sýnýfýn kapsam bölgesindeki normal bir fonksiyonmuþ gibi ele alýnýr. Statik üye fonksiyonlarý 15.7 dersinde -- Statik üye 
fonksiyonlarý konusunda ele alýyoruz.

Hepsini bir araya getirerek:

simple.setID(2) çaðrýsýný yaptýðýmýzda, derleyici aslýnda Simple::setID(&simple, 2) çaðrýsýný yapar ve simple fonksiyona adres 
üzerinden geçirilir.
Fonksiyonun, simple'ýn adresini alan this adýnda gizli bir parametresi vardýr.
setID() içindeki üye deðiþkenler, simple'a iþaret eden this-> ile öne alýnýr. Yani derleyici this->m_id'yi deðerlendirdiðinde,
aslýnda simple.m_id'yi çözümlüyor.
Ýyi haber þu ki, bunlarýn hepsi otomatik olarak gerçekleþir ve bunun nasýl çalýþtýðýný hatýrlamanýzýn veya hatýrlamamanýzýn
gerçekten bir önemi yoktur. Hatýrlamanýz gereken tek þey, tüm statik olmayan üye fonksiyonlarýn, fonksiyonun çaðrýldýðý nesneyi
referans veren bir this iþaretçisine sahip olmasýdýr.

Anahtar nokta þudur yani, Tüm statik olmayan üye fonksiyonlar, örtülü nesnenin adresini tutan bir this const iþaretçisinesahiptir.
this her zaman üzerinde iþlem yapýlan nesneyi gösterir

Yeni programcýlar bazen kaç tane this iþaretçisi olduðu konusunda karýþýklýk yaþarlar. Her üye fonksiyonun, örtülü nesneyi 
gösteren tek bir this iþaretçi parametresi vardýr. Dikkate alýn:

                int main()
                {
                    Simple a{1}; // this = &a inside the Simple constructor
                    Simple b{2}; // this = &b inside the Simple constructor
                    a.setID(3); // this = &a inside member function setID()
                    b.setID(4); // this = &b inside member function setID()

                    return 0;
                }

this iþaretçisinin, a veya b nesnesinin adresini tuttuðuna dikkat edin, bu da a veya b nesnesi üzerinde bir üye fonksiyon çaðrýp 
çaðýrmadýðýmýza baðlýdýr. Çünkü this sadece bir fonksiyon parametresidir (ve bir üye deðildir), bu nedenle sýnýfýnýzýn örneklerini
bellek açýsýndan daha büyük yapmaz.

Açýkça this'e baþvurma
----------------------
Çoðu zaman, this iþaretçisine açýkça baþvurmanýz gerekmez. Ancak, bunu yapmanýn faydalý olabileceði birkaç durum vardýr:

Öncelikle, ayný adý taþýyan bir veri üyesi ve bir parametresi olan bir üye fonksiyonunuz varsa, bunlarý this kullanarak ayýrt 
edebilirsiniz:

                struct Something
                {
                    int data{}; // m_ öneki kullanýlmýyor çünkü bu bir yapý

                    void setData(int data)
                    {
                        this->data = data; // this->data üyedir, data yerel parametredir
                    }
                };

Bu Something sýnýfýnýn data adýnda bir üyesi var. setData() fonksiyonunun da data adýnda bir parametresi var. setData() fonksiyonu
içinde, data fonksiyon parametresine atýfta bulunur (çünkü fonksiyon parametresi veri üyesini gölgede býrakýr), bu yüzden veri 
üyesine baþvurmak istiyorsak, this->data kullanýrýz.

Bazý geliþtiriciler, bir üyeye baþvurduklarýný açýkça belirtmek için tüm sýnýf üyelerine this-> eklemeyi tercih eder.
Bunu yapmanýzý önermiyoruz, çünkü bu genellikle kodunuzu az fayda karþýlýðýnda daha az okunabilir hale getirir. "m_" öneki,
özel üye deðiþkenleri ile üye olmayan (yerel) deðiþkenleri ayýrt etmenin daha özlü bir yoludur.

*this'i döndürme
----------------
Ýkincisi, bir üye fonksiyonun dönüþ deðeri olarak örtülü nesneyi döndürmesi bazen faydalý olabilir. Bunu yapmanýn temel nedeni,
üye fonksiyonlarýn "zincirlenmesine" izin vermek, böylece tek bir ifadede ayný nesne üzerinde birkaç üye fonksiyon çaðrýlabilir!
Bu, fonksiyon zincirleme (veya yöntem zincirleme) olarak adlandýrýlýr.

std::cout kullanarak birkaç metin parçasýný çýktý olarak verdiðiniz bu yaygýn örneði düþünün:

std::cout << "Hello, " << userName;
Derleyici, yukarýdaki kod parçacýðýný þu þekilde deðerlendirir:

(std::cout << "Hello, ") << userName;
Öncelikle, operator<<, std::cout ve "Hello, " dize sabitini kullanarak konsola "Hello, " yazdýrýr. Ancak, bu bir ifadenin parçasý
olduðundan, operator<<'in de bir deðer (veya void) döndürmesi gerekir. Eðer operator<< void döndürürse, kýsmen deðerlendirilmiþ
ifade þu þekilde olur:

void{} << userName;
bu açýkça hiçbir anlam ifade etmez (ve derleyici bir hata atar). Bunun yerine, operator<<, bu durumda std::cout olan geçirilen 
akýþ nesnesini döndürür. Bu þekilde, ilk operator<< deðerlendirildikten sonra, þunu elde ederiz:

(std::cout) << userName;
bu da kullanýcýnýn adýný yazdýrýr.

Bu þekilde, yalnýzca bir kez std::cout belirtmemiz gerekir ve ardýndan istediðimiz kadar metin parçasýný operator<< kullanarak 
bir araya getirebiliriz. Her operator<< çaðrýsý, std::cout'u döndürür, böylece sonraki operator<< çaðrýsý, std::cout'u sol iþlenen
olarak kullanýr.

Bu tür bir davranýþý üye fonksiyonlarýmýzda da uygulayabiliriz. Aþaðýdaki sýnýfý düþünün:

                class Calc
                {
                private:
                    int m_value{};

                public:

                    void add(int value) { m_value += value; }
                    void sub(int value) { m_value -= value; }
                    void mult(int value) { m_value *= value; }

                    int getValue() { return m_value; }
                };

Eðer 5 eklemek, 3 çýkarmak ve 4 ile çarpmak isterseniz, bunu yapmanýz gerekir:

                #include <iostream>

                int main()
                {
                    Calc calc{};
                    calc.add(5); // void döndürür
                    calc.sub(3); // void döndürür
                    calc.mult(4); // void döndürür

                    std::cout << calc.getValue() << '\n';

                    return 0;
                }

Ancak, her fonksiyonun *this'i referans olarak döndürmesi durumunda, çaðrýlarý bir araya getirebiliriz. Ýþte "zincirlenebilir" 
fonksiyonlara sahip Calc'ýn yeni versiyonu:

                class Calc
                {
                private:
                    int m_value{};

                public:
                    Calc& add(int value) { m_value += value; return *this; }
                    Calc& sub(int value) { m_value -= value; return *this; }
                    Calc& mult(int value) { m_value *= value; return *this; }

                    int getValue() { return m_value; }
                };
add(), sub() ve mult()'un artýk *this'i referans olarak döndürdüðüne dikkat edin. Sonuç olarak, aþaðýdakileri yapmamýza izin verir:

                #include <iostream>

                int main()
                {
                    Calc calc{};
                    calc.add(5).sub(3).mult(4); // method chaining

                    std::cout << calc.getValue() << '\n';

                    return 0;
                }
Üç satýrý etkili bir þekilde tek bir ifadeye sýkýþtýrdýk! Bunun nasýl çalýþtýðýna daha yakýndan bakalým.

Öncelikle, calc.add(5) çaðrýlýr, bu da m_value'ye 5 ekler. add() daha sonra *this'i döndürür, bu da sadece calc'a referanstýr,
bu yüzden calc, sonraki deðerlendirmede kullanýlacak nesne olacaktýr. Sonraki adýmda calc.sub(3) deðerlendirilir, 
bu da m_value'den 3 çýkarýr ve yine calc'ý döndürür. Son olarak, calc.mult(4) m_value'yi 4 ile çarpar ve calc'ý döndürür,
bu daha fazla kullanýlmaz ve bu nedenle göz ardý edilir.
Her fonksiyon, calc'ý çalýþtýrýldýkça deðiþtirdiðinden, calc'ýn m_value'si þimdi (((0 + 5) - 3) * 4) deðerini içerir, bu da 8'dir.
Bu, this'in en yaygýn açýk kullanýmýdýr ve üye fonksiyonlarýn zincirlenebilir olmasý mantýklý olduðunda bunu düþünmelisiniz.
Çünkü this her zaman implicit nesneyi gösterir, bu yüzden onu dereferans yapmadan önce null iþaretçi olup olmadýðýný kontrol 
etmemiz gerekmez.

Bir sýnýfý varsayýlan durumuna sýfýrlama
----------------------------------------
Eðer sýnýfýnýzýn bir varsayýlan yapýcý fonksiyonu varsa, mevcut bir nesneyi varsayýlan durumuna geri döndürme yolunu saðlamakla
ilgilenebilirsiniz. Önceki derslerde belirtildiði gibi (14.12 -- Yapýcýlarý Devretme), yapýcýlar yalnýzca yeni nesnelerin 
baþlatýlmasý içindir ve doðrudan çaðrýlmamalýdýr. Bunu yapmak beklenmeyen bir davranýþa yol açar.

Bir sýnýfý varsayýlan bir duruma geri döndürmenin en iyi yolu, bir reset() üye fonksiyonu oluþturmak, bu fonksiyonun yeni bir 
nesne oluþturmasýný (varsayýlan yapýcýyý kullanarak) ve daha sonra bu yeni nesneyi mevcut örtülü nesneye atamasýný saðlamaktýr:

                void reset()
                {
                    *this = {}; // yeni bir nesneyi deðer baþlatýn ve örtülü nesnenin üzerine yazýn
                }

Ýþte bu reset() fonksiyonunu gösteren tam bir program:

                #include <iostream>

                class Calc
                {
                private:
                    int m_value{};

                public:
                    Calc& add(int value) { m_value += value; return *this; }
                    Calc& sub(int value) { m_value -= value; return *this; }
                    Calc& mult(int value) { m_value *= value; return *this; }

                    int getValue() { return m_value; }

                    void reset() { *this = {}; }
                };


                int main()
                {
                    Calc calc{};
                    calc.add(5).sub(3).mult(4);

                    std::cout << calc.getValue() << '\n'; // 8 yazdýrýr

                    calc.reset();

                    std::cout << calc.getValue() << '\n'; // 0 yazdýrýr

                    return 0;
                }
this ve const nesneler
----------------------
Statik olmayan üye fonksiyonlar için, this bir const iþaretçisidir ve non-const bir deðere iþaret eder (yani this baþka bir þeye 
iþaret edemez, ancak iþaret edilen nesne deðiþtirilebilir). Const üye fonksiyonlarý ile this, const bir iþaretçiye const bir 
deðere iþaret eder (yani iþaretçi baþka bir þeye iþaret edemez, ayrýca iþaret edilen nesne de deðiþtirilemez).

Const olmayan bir üyeyi const bir nesne üzerinde çaðýrmaya çalýþmak, biraz karmaþýk hatalar oluþturabilir:

error C2662: 'int Something::getValue(void)': cannot convert 'this' pointer from 'const Something' to 'Something &'
error: passing 'const Something' as 'this' argument discards qualifiers [-fpermissive]

Const olmayan bir üye fonksiyonu const bir nesne üzerinde çaðýrdýðýmýzda, örtülü this fonksiyon parametresi non-const bir nesneye
const bir iþaretçidir. Ancak argümanýn türü const bir nesneye const bir iþaretçidir. Const bir nesneye iþaret eden bir iþaretçiyi 
non-const bir nesneye iþaret eden bir iþaretçiye dönüþtürmek, const niteliðinin atýlmasýný gerektirir, bu da örtülü olarak 
yapýlamaz. Bazý derleyiciler tarafýndan oluþturulan derleyici hatasý, derleyicinin böyle bir dönüþümü gerçekleþtirmek üzere talep
edildiðinden þikayet ettiðini yansýtýr.

Bu nedenle this bir iþaretçi ve bir referans deðil

this iþaretçisi her zaman örtülü nesneyi gösterir (ve eðer tanýmsýz bir davranýþa neden olan bir þey yapmadýysak hiçbir zaman null
iþaretçi olamaz), bu yüzden this'in neden bir iþaretçi olduðunu ve bir referans olmadýðýný merak ediyor olabilirsiniz.
Cevap basit: this C++'a eklendiðinde, referanslar henüz mevcut deðildi.

Eðer this bugün C++ diline eklenseydi, hiç þüphesiz bir referans olurdu, bir iþaretçi deðil. Java ve C# gibi daha modern 
C++ benzeri dillerde, this bir referans olarak uygulanmýþtýr.

15.2 — Sýnýflar ve Baþlýk Dosyalarý
-----------------------------------
Þimdiye kadar yazdýðýmýz tüm sýnýflar, üye fonksiyonlarý doðrudan sýnýf tanýmýnýn içinde uygulayabilecek kadar basitti. Örneðin,
iþte tüm üye fonksiyonlarýn Date sýnýfý tanýmýnýn içinde tanýmlandýðý basit bir Date sýnýfý:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day)
                        : m_year { year }
                        , m_month { month }
                        , m_day { day}
                    {
                    }

                    void print() const { std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; };

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const { return m_day; }
                };

                int main()
                {
                    Date d { 2015, 10, 14 };
                    d.print();

                    return 0;
                }
Ancak, sýnýflar daha uzun ve karmaþýk hale geldikçe, tüm üye fonksiyon tanýmlarýnýn sýnýfýn içinde olmasý, sýnýfýn yönetilmesini
ve çalýþýlmasýný zorlaþtýrabilir. Zaten yazýlmýþ bir sýnýfý kullanmak, sadece onun genel arayüzünü (genel üye fonksiyonlar)
anlamayý gerektirir, sýnýfýn kaputunun altýnda nasýl çalýþtýðýný deðil. Üye fonksiyon uygulamalarý, sýnýfýn kullanýlmasýyla 
ilgili olmayan ayrýntýlarla genel arayüzü karýþtýrýr.

Bu durumu ele almak için, C++ bize sýnýfýn "bildirim" kýsmýný "uygulama" kýsmýndan ayýrma olanaðý saðlar, yani üye fonksiyonlarý 
sýnýf tanýmýnýn dýþýnda tanýmlar.

Ýþte ayný Date sýnýfý, yapýcý fonksiyon ve print() üye fonksiyonlarý sýnýf tanýmýnýn dýþýnda tanýmlanmýþ olarak. Bu üye
fonksiyonlarýn prototiplerinin hala sýnýf tanýmýnýn içinde var olduðuna dikkat edin (çünkü bu fonksiyonlarýn sýnýf tipi tanýmýnýn
bir parçasý olarak bildirilmesi gerekiyor), ancak gerçek uygulama dýþarýya taþýndý:

                #include <iostream>

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day); // constructor declaration

                    void print() const; // print function declaration

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const  { return m_day; }
                };

                Date::Date(int year, int month, int day) // constructor definition
                    : m_year{ year }
                    , m_month{ month }
                    , m_day{ day }
                {
                }

                void Date::print() const // print function definition
                {
                    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
                };

                int main()
                {
                    const Date d{ 2015, 10, 14 };
                    d.print();

                    return 0;
                }
Üye fonksiyonlar, sýnýf tipinin dýþýnda tanýmlanýr, týpký üye olmayan fonksiyonlar gibi. Tek fark, üye fonksiyon adlarýnýn önüne
sýnýf tipinin adýný (bu durumda, Date::) eklememiz gerektiðidir, böylece derleyici, bir üye olmayaný deðil, o sýnýf tipinin bir 
üyesini tanýmladýðýmýzý bilir.

Eriþim fonksiyonlarýnýn sýnýf tanýmýnýn içinde tanýmlandýðýný býraktýðýmýza dikkat edin. Çünkü eriþim fonksiyonlarý genellikle
sadece bir satýrdýr, bu fonksiyonlarý sýnýf tanýmýnýn içinde tanýmlamak, minimal düzeyde karýþýklýk yaratýrken, onlarý sýnýf
tanýmýnýn dýþýna taþýmak, çok fazla ekstra kod satýrýna neden olur. Bu nedenle, eriþim fonksiyonlarýnýn tanýmlarý (ve diðer basit,
tek satýrlýk fonksiyonlar) genellikle sýnýf tanýmýnýn içinde býrakýlýr.

*** BEST -> Basit, tek satýrlýk bir uygulamaya sahip üye fonksiyonlar, sýnýf tanýmýnýn içinde tanýmlanabilir. Karmaþýk veya çok
            satýrlý bir uygulamaya sahip üye fonksiyonlar, bir kaynak dosyasýnda, sýnýf tanýmýnýn dýþýnda tanýmlanmalýdýr.

Sýnýf tanýmlarýný bir baþlýk dosyasýna koymak
---------------------------------------------
Bir sýnýfý bir kaynak (.cpp) dosyasýnýn içinde tanýmlarsanýz, bu sýnýf yalnýzca o belirli kaynak dosyasý içinde kullanýlabilir.
Daha büyük programlarda, yazdýðýmýz sýnýflarý birden çok kaynak dosyasýnda kullanmak yaygýndýr.

2.11 -- Baþlýk dosyalarý dersinde, fonksiyon bildirimlerini bir baþlýk dosyasýna koyabileceðinizi öðrendiniz. Sonra bu fonksiyon
bildirimlerini birden çok kod dosyasýna (veya hatta birden çok projeye) #include edebilirsiniz. Sýnýflar da farklý deðildir. Bir
sýnýf tanýmlamasý bir baþlýk dosyasýna konabilir ve sonra sýnýf türünü kullanmak isteyen herhangi bir dosyaya #include edilebilir.

Fonksiyonlarýn aksine, kullanýlmak üzere sadece bir ileri bildirime ihtiyaç duyan, derleyici genellikle bir türün kullanýlabilmesi
için sýnýfýn (veya herhangi bir program tanýmlý türün) tam tanýmýný görmeye ihtiyaç duyar. Bu, derleyicinin üyelerin nasýl
bildirildiðini anlamasý ve bunlarýn doðru bir þekilde kullanýldýðýndan emin olmasý gerektiði ve bir türün nesnelerinin ne kadar
büyük olduðunu hesaplayabilmesi için gereklidir. Bu yüzden baþlýk dosyalarýmýz genellikle bir sýnýfýn tam tanýmýný içerir,
sadece sýnýfýn ileri bildirimini deðil.

Sýnýf baþlýk ve kod dosyalarýnýzý adlandýrma
--------------------------------------------
Çoðu zaman, sýnýflar sýnýf ile ayný adý taþýyan baþlýk dosyalarýnda tanýmlanýr ve sýnýfýn dýþýnda tanýmlanan herhangi bir üye 
fonksiyon, sýnýf ile ayný adý taþýyan bir .cpp dosyasýna konulur.

Ýþte Date sýnýfýmýzý tekrar, bir .cpp ve .h dosyasýna bölünmüþ olarak:

Date.h:

                #ifndef DATE_H
                #define DATE_H

                class Date
                {
                private:
                    int m_year{};
                    int m_month{};
                    int m_day{};

                public:
                    Date(int year, int month, int day); // constructor declaration

                    void print() const; // print function declaration

                    int getYear() const { return m_year; }
                    int getMonth() const { return m_month; }
                    int getDay() const { return m_day; }
                };

                #endif
Date.cpp:

                #include "Date.h"

                Date::Date(int year, int month, int day) // constructor definition
                    : m_year{ year }
                    , m_month{ month }
                    , m_day{ day }
                {
                }

                void Date::print() const // print function definition
                {
                    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
                };

Þimdi Date sýnýfýný kullanmak isteyen herhangi bir baþlýk veya kod dosyasý basitçe #include "Date.h" yapabilir. Üye fonksiyonlarýn
çaðrýlarýný tanýmlamalarýna baðlayabilmesi için baðlayýcýnýn Date.h'yi kullanan her projeye Date.cpp'nin de derlenmesi gerektiðini
unutmayýn.

*** BEST -> Sýnýf tanýmlarýnýzý, sýnýf ile ayný adý taþýyan bir baþlýk dosyasýna koymayý tercih edin. Önemsiz üye fonksiyonlar 
            (örneðin eriþim fonksiyonlarý, boþ gövdeleri olan yapýlandýrýcýlar vb.) sýnýf tanýmýnýn içinde tanýmlanabilir.
            Sýnýf ile ayný adý taþýyan bir kaynak dosyada önemsiz olmayan üye fonksiyonlarý tanýmlamayý tercih edin.

Bir sýnýfý bir baþlýk dosyasýnda tanýmlamak, baþlýk birden fazla kez #include edilirse tek tanýmlama kuralýný (ODR) ihlal etmiyor 
mu?
----------------------------------------------------------------------------------------------------------------------------------
Türler, bir programda yalnýzca bir taným olmasý gerektiðini söyleyen tek tanýmlama kuralýnýn (ODR) bir bölümünden muaf tutulmuþtur
Bu nedenle, sýnýf tanýmlarýný birden çok kod dosyasýna #include etmek bir sorun teþkil etmez. Eðer öyle olsaydý, sýnýflar çok 
fazla iþe yaramazdý.

Bir sýnýf tanýmýný tek bir kaynak dosyasýna birden fazla kez dahil etmek hala bir ODR ihlalidir. Ancak, baþlýk korumalarý
(veya #pragma once) bunun olmasýný önleyecektir.

Üye fonksiyonlarýný header'da tanýmlamak tek-tanýmlama kuralýný ihlal eder mi?
------------------------------------------------------------------------------
Bu duruma baðlýdýr. Sýnýf tanýmýnýn içinde tanýmlanan üye fonksiyonlar dolaylý olarak inline'dýr. Inline fonksiyonlar, 
tek-tanýmlama kuralýnýn program baþýna bir tanýmlama bölümünden muaf tutulur. Bu, basit üye fonksiyonlarýn
(örneðin eriþim fonksiyonlarý gibi) sýnýf tanýmýnýn kendisi içinde tanýmlanmasýnda bir sorun olmadýðý anlamýna gelir.

Sýnýf tanýmýnýn dýþýnda tanýmlanan üye fonksiyonlar dolaylý olarak inline deðildir (ve bu nedenle tek-tanýmlama kuralýnýn program
baþýna bir tanýmlama bölümüne tabidir). Bu nedenle, bu tür fonksiyonlar genellikle bir kod dosyasýnda tanýmlanýr 
(burada tüm program boyunca yalnýzca bir tanýmlamalarý olacaktýr). Ancak, eðer inline olarak iþaretlenmiþlerse, header dosyasýnda
da tanýmlanabilirler (bu onlarý inline fonksiyon yapar).

Kilit nokta þudur ki, Sýnýf tanýmýnýn içinde tanýmlanan fonksiyonlar dolaylý olarak inline'dýr, bu da onlarýn ODR'yi ihlal etmeden
birden çok kod dosyasýna dahil edilebileceði anlamýna gelir.

Sýnýf tanýmýnýn dýþýnda tanýmlanan fonksiyonlar dolaylý olarak inline deðildir. Inline anahtar kelimesini kullanarak inline
yapýlabilirler.

Peki, neden her þeyi bir header dosyasýna koymuyoruz?
-----------------------------------------------------
Header dosyanýza tüm üye fonksiyon tanýmlarýnýzý koymak için cazip olabilirsiniz, ya sýnýf tanýmýnýn içinde ya da sýnýf tanýmýnýn 
altýnda inline fonksiyonlar olarak. Bu derlenecektir, ancak bunu yapmanýn birkaç dezavantajý vardýr. Ýlk olarak, yukarýda
belirtildiði gibi, sýnýf tanýmýnýn içinde üyeleri tanýmlamak sýnýf tanýmýnýzý karýþtýrýr. Ýkincisi, eðer header'daki herhangi bir
kodu deðiþtirirseniz, o header'ý içeren her dosyayý yeniden derlemeniz gerekecektir. Bu, bir programýn tamamýnýn yeniden
derlenmesine neden olan bir dalga etkisi yaratabilir (bu yavaþ olabilir). Eðer .cpp dosyasýndaki kodu deðiþtirirseniz, sadece o
.cpp dosyasýnýn yeniden derlenmesi gereklidir!

Sýnýf tanýmýný bir header'a ve önemsiz olmayan üye fonksiyonlarý bir kod dosyasýna koyma en iyi uygulamasýný ihlal etmek mantýklý
olabilecek birkaç durum vardýr.

Ýlk olarak, yalnýzca bir kod dosyasýnda kullanýlan ve genel olarak yeniden kullanýlmak üzere tasarlanmamýþ küçük bir sýnýf için,
sýnýfý (ve tüm üye fonksiyonlarý) doðrudan kullanýldýðý tek .cpp dosyasýnda tanýmlamayý tercih edebilirsiniz. Bu, sýnýfýn yalnýzca
o tek dosya içinde kullanýldýðýný ve daha geniþ bir kullaným için tasarlanmadýðýný açýkça belirtir. Daha sonra, sýnýfý birden 
fazla dosyada kullanmak isterseniz veya sýnýf ve üye fonksiyon tanýmlarýnýn kaynak dosyanýzý karýþtýrdýðýný fark ederseniz,
sýnýfý ayrý bir header/kod dosyasýna taþýyabilirsiniz.

Ýkinci olarak, bir sýnýfýn yalnýzca küçük bir sayýda önemsiz olmayan üye fonksiyonu varsa, yalnýzca bir veya iki taným içeren bir 
.cpp dosyasý oluþturmak çabanýn karþýlýðýný vermeyebilir. Bu tür durumlarda, üye fonksiyonlarý inline yapmak ve onlarý header'daki
sýnýf tanýmýnýn altýna koymak tercih edilebilir.

Üçüncü olarak, modern C++'da, sýnýflar veya kütüphaneler giderek daha fazla "header-only" olarak daðýtýlýyor, yani sýnýf veya 
kütüphane için tüm kod bir header dosyasýna yerleþtiriliyor. Bu, öncelikle bu tür dosyalarýn daðýtýmýný ve kullanýmýný 
kolaylaþtýrmak için yapýlýr, çünkü bir header yalnýzca #include edilmesi gerekirken, bir kod dosyasý, derlenebilmesi için onu 
kullanan her projeye açýkça eklenmelidir. Bilinçli bir þekilde bir header-only sýnýfý veya kütüphaneyi daðýtmak için, tüm önemsiz 
olmayan üye fonksiyonlar inline yapýlabilir ve sýnýf tanýmýnýn altýndaki header dosyasýna yerleþtirilebilir.

Son olarak, þablon sýnýflar için, sýnýfýn dýþýnda tanýmlanan þablon üye fonksiyonlar hemen hemen her zaman header dosyasýnýn
içinde, sýnýf tanýmýnýn altýnda tanýmlanýr. Üye olmayan þablon fonksiyonlar gibi, derleyicinin onu örnekleþtirebilmesi için tam 
þablon tanýmýný görmesi gereklidir. Þablon üye fonksiyonlarý, 15.5 dersinde -- Üye fonksiyonlarý olan sýnýf þablonlarý konusunu 
ele alýyoruz.

Yazarýn notu

Gelecekteki derslerde, sýnýflarýmýzýn çoðu tek bir .cpp dosyasýnda tanýmlanacak ve tüm fonksiyonlar doðrudan sýnýf tanýmýnda 
uygulanacaktýr. Bu, örneklerin özlü ve kolay derlenebilir olmasýný saðlamak için yapýlýr. Gerçek projelerde, sýnýflarýn kendi kod
ve header dosyalarýna konulmasý çok daha yaygýndýr ve bunu yapmaya alýþmalýsýnýz.

Üye fonksiyonlarý için varsayýlan argümanlar
--------------------------------------------
11.5 dersinde -- Varsayýlan argümanlar, üye olmayan fonksiyonlarýn varsayýlan argümanlarý için en iyi uygulamayý tartýþtýk:
"Eðer fonksiyonun bir ileri bildirimi varsa (özellikle bir baþlýk dosyasýnda), varsayýlan argümaný oraya koyun. Aksi takdirde,
varsayýlan argümaný fonksiyon tanýmýna koyun."

Üye fonksiyonlar her zaman sýnýf tanýmýnýn bir parçasý olarak bildirildiði (veya tanýmlandýðý) için, üye fonksiyonlarý için en iyi
uygulama aslýnda daha basittir: varsayýlan argümaný her zaman sýnýf tanýmýnýn içine koyun.

*** BEST -> Üye fonksiyonlarý için herhangi bir varsayýlan argümaný sýnýf tanýmýnýn içine koyun.

Kütüphaneler
------------
Programlarýnýz boyunca, std::string gibi standart kütüphanenin bir parçasý olan sýnýflarý kullandýnýz. Bu sýnýflarý kullanmak için,
yalnýzca ilgili baþlýðý dahil etmeniz gerekir (örneðin #include <string>). Not edin ki projelerinize herhangi bir kod dosyasý 
eklemeniz gerekmedi (örneðin string.cpp veya iostream.cpp).

Baþlýk dosyalarý, yazdýðýnýz programlarýn sözdizimsel olarak doðru olduðunu doðrulamak için derleyicinin gerektirdiði bildirimleri
saðlar. Ancak, C++ standart kütüphanesine ait sýnýflarýn uygulamalarý, baðlama aþamasýnda otomatik olarak baðlanan bir önceden
derlenmiþ dosyada bulunur. Kodu asla görmezsiniz.

Birçok açýk kaynaklý yazýlým paketi, programýnýza derlemek üzere hem .h hem de .cpp dosyalarý saðlar. Ancak, çoðu ticari kütüphane 
yalnýzca .h dosyalarý ve önceden derlenmiþ bir kütüphane dosyasý saðlar. Bunun birkaç nedeni vardýr:
        1) Her seferinde yeniden derlemekten daha hýzlýdýr.
        2) Önceden derlenmiþ bir kütüphanenin tek bir kopyasý birçok uygulama tarafýndan paylaþýlabilir, 
        oysa derlenmemiþ kod her kullanýlan uygulamaya derlenir (dosya boyutlarýný þiþirir)
        3) Fikri mülkiyet nedenleri (kodunuzun çalýnmasýný istemezsiniz).

Ekte, 3. parti önceden derlenmiþ kütüphaneleri projelerinize nasýl dahil edeceðinizi tartýþýyoruz.

Muhtemelen bir süreliðine kendi kütüphanelerinizi oluþturup daðýtmayacaksýnýz, ancak sýnýflarýnýzý baþlýk dosyalarý ve kaynak
dosyalarýna ayýrmak sadece iyi bir biçim deðil, ayný zamanda kendi özel kütüphanelerinizi oluþturmayý da kolaylaþtýrýr.
Kendi kütüphanelerinizi oluþturmak bu derslerin kapsamý dýþýndadýr, ancak bildiriminizi ve uygulamanýzý ayýrmak, önceden derlenmiþ
ikililer daðýtmak istiyorsanýz bunu yapmanýn bir ön koþuludur.

15.3 — Ýç Ýçe ( Nested - Baðlý olarak da çevriliyor) Türler (Üye Türler)
------------------------------------------------------------------------
Aþaðýdaki kýsa programý düþünün:

                #include <iostream>

                enum class FruitType
                {
                    apple,
                    banana,
                    cherry
                };

                class Fruit
                {
                private:
                    FruitType m_type { };
                    int m_percentageEaten { 0 };

                public:
                    Fruit(FruitType type) :
                        m_type { type }
                    {
                    }

                    FruitType getType() { return m_type; }
                    int getPercentageEaten() { return m_percentageEaten; }

                    bool isCherry() { return m_type == FruitType::cherry; }

                };

                int main()
                {
                    Fruit apple { FruitType::apple };

                    if (apple.getType() == FruitType::apple)
                        std::cout << "I am an apple";
                    else
                        std::cout << "I am not an apple";

                    return 0;
                }

Bu programda hiçbir yanlýþlýk yok. Ancak, enum class FruitType'ýn Fruit sýnýfý ile birlikte kullanýlmasý amaçlandýðýndan,
sýnýftan baðýmsýz olarak var olmasý, bunlarýn nasýl baðlantýlý olduðunu çýkarým yapmamýzý gerektirir.

Ýç Ýçe Türler (Üye Türler)

Þimdiye kadar, iki farklý türde üyeye sahip sýnýf türlerini gördük: veri üyeleri ve üye fonksiyonlar. Yukarýdaki örnekteki
Fruit sýnýfýmýzýn her ikisi de var.

Sýnýf türleri, baþka bir tür üyeyi destekler: iç içe türler (ayný zamanda üye türler olarak da adlandýrýlýr). Bir iç içe tür 
oluþturmak için, türü sýnýfýn içinde, uygun eriþim belirleyicisi altýnda tanýmlamanýz yeterlidir.

Ýþte yukarýdaki programýn aynýsý, Fruit sýnýfýnýn içinde tanýmlanan bir iç içe tür kullanýlarak yeniden yazýlmýþ hali:

                #include <iostream>

                class Fruit
                {
                public:
                    // FruitType, public eriþim belirleyicisi altýnda sýnýfýn içine taþýndý
                        // Ayrýca onu Type olarak yeniden adlandýrdýk ve bir enum yerine bir enum class yaptýk
                    enum Type
                    {
                        apple,
                        banana,
                        cherry
                    };

                private:
                    Type m_type {};
                    int m_percentageEaten { 0 };

                public:
                    Fruit(Type type) :
                        m_type { type }
                    {
                    }

                    Type getType() { return m_type;  }
                    int getPercentageEaten() { return m_percentageEaten;  }

                    bool isCherry() { return m_type == cherry; } // Fruit'ün üyeleri içinde, artýk 
                                                                 // FruitType:: ile öne koymamýza gerek yok
                };

                int main()
                {
                    // Not: Sýnýfýn dýþýnda, numaralandýrýcýlarý artýk Fruit:: öneki ile eriþiyoruz
                    Fruit apple { Fruit::apple };

                    if (apple.getType() == Fruit::apple)
                        std::cout << "I am an apple";
                    else
                        std::cout << "I am not an apple";

                    return 0;
                }
Burada belirtmeye deðer birkaç þey var.

Ýlk olarak, FruitType'ýn artýk sýnýfýn içinde tanýmlandýðýný ve kýsa süre sonra tartýþacaðýmýz nedenlerle Type olarak yeniden
adlandýrýldýðýný belirtmek gerekir.

Ýkinci olarak, iç içe tür olan Type, sýnýfýn en üstünde tanýmlandý. Ýç içe tür adlarý, kullanýlmadan önce tamamen tanýmlanmalýdýr,
bu yüzden genellikle ilk olarak tanýmlanýrlar.

*** BEST -> Sýnýf türünüzün en üstünde herhangi bir iç içe türü tanýmlayýn.

Üçüncü olarak, iç içe türler normal eriþim kurallarýna uyar. Type, tür adýnýn ve numaralandýrýcýlarýn doðrudan public
bir þekilde eriþilebilmesi için public eriþim belirleyicisi altýnda tanýmlandý.

Dördüncü olarak, sýnýf türleri, içinde bildirilen adlar için bir kapsam bölgesi olarak hareket eder, týpký ad alanlarýnýn
yaptýðý gibi. Bu nedenle, Type'ýn tam nitelikli adý Fruit::Type ve apple numaralandýrýcýsýnýn tam nitelikli adý Fruit::apple'dir.

Sýnýfýn üyeleri içinde, tam nitelikli adý kullanmamýza gerek yoktur. Örneðin, isCherry() üye fonksiyonunda, Fruit:: kapsam
belirleyicisi olmadan cherry numaralandýrýcýsýna eriþiriz.

Sýnýfýn dýþýnda, tam nitelikli adý kullanmalýyýz (ör. Fruit::apple). FruitType'ý Type olarak yeniden adlandýrdýk,
böylece ona Fruit::Type olarak eriþebiliriz (daha fazla gereksiz olan Fruit::FruitType yerine).

Son olarak, numaralandýrýlmýþ türümüzü kapsamlýdan kapsamsýza deðiþtirdik. Artýk sýnýfýn kendisi bir kapsam bölgesi olarak
hareket ettiðinden, kapsamlý bir numaralandýrýcý kullanmak biraz gereksizdir. Kapsamsýz bir enum'a geçiþ, numaralandýrýcýlarý
Fruit::apple olarak eriþmemizi saðlar, bu da numaralandýrýcýnýn kapsamlý olmasý durumunda kullanmamýz gereken daha uzun
Fruit::Type::apple yerine.

Ýç içe typedef'lar ve tür takma adlarý
--------------------------------------
Sýnýf türleri ayrýca iç içe typedef'larý veya tür takma adlarýný da içerebilir:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                public:
                    using IDType = int;

                private:
                    std::string m_name{};
                    IDType m_id{};
                    double m_wage{};

                public:
                    Employee(std::string_view name, IDType id, double wage)
                        : m_name { name }
                        , m_id { id }
                        , m_wage { wage }
                    {
                    }

                    const std::string& getName() { return m_name; }
                    IDType getId() { return m_id; } // sýnýf içinde niteliksiz isim kullanýlabilir
                };

                int main()
                {
                    Employee john { "John", 1, 45000 };
                    Employee::IDType id { john.getId() }; // sýnýf dýþýnda tam nitelikli isim kullanýlmalýdýr

                    std::cout << john.getName() << " has id: " << id << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                John has id: 1
Sýnýfýn içinde sadece IDType'ý kullanabiliriz, ancak sýnýfýn dýþýnda tam nitelikli isim Employee::IDType'ý kullanmalýyýz.

Tür takma adlarýnýn faydalarýný 10.7 -- Typedefs and type aliases dersinde tartýþýyoruz ve burada ayný amaca hizmet ediyorlar.
C++ standart kütüphanesindeki sýnýflarýn iç içe typedef'larý kullanmasý çok yaygýndýr. Yazma zamanýnda, std::string on iç içe
typedef tanýmlar!

Ýç içe sýnýflar ve dýþ sýnýf üyelerine eriþim
---------------------------------------------
Sýnýflarýn baþka sýnýflarý iç içe bir tür olarak içermesi oldukça nadirdir, ancak mümkündür. C++'da, iç içe bir sýnýf, 
dýþ (içeren) sýnýfýn this iþaretçisine eriþemez, bu nedenle iç içe sýnýflar dýþ sýnýfýn üyelerine doðrudan eriþemez.
Bu, iç içe bir sýnýfýn dýþ sýnýftan baðýmsýz olarak örneklenebileceði için böyledir (ve böyle bir durumda, eriþilecek dýþ sýnýf
üyeleri olmaz!)

Ancak, iç içe sýnýflar dýþ sýnýfýn üyeleri olduðu için, kapsamdaki dýþ sýnýfýn herhangi bir özel üyesine eriþebilirler.
Bir örnekle açýklayalým:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                public:
                    using IDType = int;

                    class Printer
                    {
                    public:
                        void print(const Employee& e) const
                        {
                            // Printer, Employee'ýn `this` iþaretçisine eriþemez
                            // bu yüzden m_name ve m_id'yi doðrudan yazdýramayýz
                            // Bunun yerine, kullanmak için bir Employee nesnesi geçmemiz gerekiyor
                            // Çünkü Printer, Employee'nin bir üyesidir,
                            // bu yüzden özel üyeler e.m_name ve e.m_id'ye doðrudan eriþebiliriz
                            std::cout << e.m_name << " has id: " << e.m_id << '\n';
                        }
                    };

                private:
                    std::string m_name{};
                    IDType m_id{};
                    double m_wage{};

                public:
                    Employee(std::string_view name, IDType id, double wage)
                        : m_name{ name }
                        , m_id{ id }
                        , m_wage{ wage }
                    {
                    }

                    // bu örnekte eriþim fonksiyonlarýný kaldýrdýk (çünkü kullanýlmýyorlar)
                };

                int main()
                {
                    const Employee john{ "John", 1, 45000 };
                    const Employee::Printer p{}; // iç sýnýfýn bir nesnesini örneklendir
                    p.print(john);

                    return 0;
                }

                Bu, þunu yazdýrýr:

                John has id: 1
Ýç içe sýnýflarýn daha yaygýn olarak kullanýldýðý bir durum vardýr. Standart kütüphanede, çoðu yineleyici sýnýfý,
üzerinde yinelemeyi tasarladýklarý konteynýrýn iç içe bir sýnýfý olarak uygulanýr. Örneðin, std::string::iterator,
std::string'in iç içe bir sýnýfý olarak uygulanmýþtýr. Yineleyicileri gelecekteki bir bölümde ele alacaðýz.

Ýç içe türler ileri bildirilemez
--------------------------------
Ýç içe türlerin bahsetmeye deðer bir baþka sýnýrlamasý daha var -- iç içe türler ileri bildirilemez. 
Bu sýnýrlama, gelecekteki bir C++ sürümünde kaldýrýlabilir.

15.4 — Yýkýcýlar'a (Destructors) Giriþ
--------------------------------------
Temizleme Sorunu
----------------
Bir program yazdýðýnýzý ve bu programýn bir að üzerinden bazý verileri göndermesi gerektiðini varsayalým. Ancak, sunucuya bir 
baðlantý kurmak maliyetlidir, bu yüzden bir sürü veri toplamak ve sonra hepsini bir seferde göndermek istersiniz. Böyle bir sýnýf
þu þekilde yapýlandýrýlabilir:

                class NetworkData
                {
                private:
                    std::string m_serverName{};
                    DataStore m_data{};

                public:
                    NetworkData(std::string_view serverName)
                        : m_serverName { serverName }
                    {
                    }

                    void addData(std::string_view data)
                    {
                        m_data.add(data);
                    }

                    void sendData()
                    {
                        // sunucuya baðlan
                        // tüm verileri gönder
                        // verileri temizle
                    }
                };

                int main()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    n.sendData();

                    return 0;
                }

Ancak, bu NetworkData'nýn potansiyel bir sorunu var. Program kapatýlmadan önce sendData() fonksiyonunun açýkça çaðrýlmasýna 
baðlýdýr. NetworkData'nýn kullanýcýsý bunu unutursa, veriler sunucuya gönderilmeyecek ve program çýktýðýnda kaybolacaktýr.
Þimdi, "peki, bunu hatýrlamak zor deðil!" diyebilirsiniz ve bu özel durumda haklý olabilirsiniz. Ancak, biraz daha karmaþýk
bir örneði düþünün, örneðin bu fonksiyon gibi:

                bool someFunction()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    if (someCondition)
                        return false;

                    n.sendData();
                    return true;
                }

Bu durumda, eðer someCondition doðruysa, fonksiyon erken dönecek ve sendData() çaðrýlmayacaktýr. Bu, sendData() çaðrýsýnýn mevcut 
olduðu, ancak programýn her durumda ona yönlendirmediði için daha kolay bir hata yapmaktýr.

Bu sorunu genelleþtirmek için, bir kaynak kullanan sýnýflar (çoðunlukla bellek, ancak bazen dosyalar, veritabanlarý, 
að baðlantýlarý vb.) genellikle sýnýf nesnesi yok edilmeden önce açýkça gönderilmesi veya kapatýlmasý gereklidir.
Diðer durumlarda, nesnenin yok edilmesinden önce bazý kayýtlar tutmak isteyebiliriz, örneðin bir günlük dosyasýna bilgi yazmak 
veya bir sunucuya bir telemetri parçasý göndermek. "Temizleme" terimi, genellikle bir sýnýfýn, sýnýfýn bir nesnesi yok edilmeden 
önce beklenildiði gibi davranmak için gerçekleþtirmesi gereken herhangi bir görev kümesine atýfta bulunmak için kullanýlýr.
Eðer bu tür bir sýnýfýn kullanýcýsýna, temizleme iþlemini gerçekleþtiren fonksiyonun nesne yok edilmeden önce çaðrýlmasýný
saðlamak zorunda kalýrsak, muhtemelen bir yerlerde hatalarla karþýlaþýrýz.

Ama neden kullanýcýdan bunu saðlamasýný bile istiyoruz? Eðer nesne yok ediliyorsa, o zaman temizlemenin o noktada
gerçekleþtirilmesi gerektiðini biliyoruz. Bu temizleme otomatik olarak mý gerçekleþmeli?

Yýkýcýlar kurtarmaya koþuyor
----------------------------
14.9 dersinde -- Yapýcýlar (Constructors) Hakkýnda Giriþ konusunda, bir non-aggregate sýnýf türünün bir nesnesi oluþturulduðunda
çaðrýlan özel üye fonksiyonlarý olan yapýcýlarý ele aldýk. Yapýcýlar, üye deðiþkenlerini baþlatmak ve sýnýfýn nesnelerinin 
kullanýma hazýr olmasýný saðlamak için gereken diðer tüm kurulum görevlerini yapmak için kullanýlýr.

Benzer þekilde, sýnýflarýn, bir non-aggregate sýnýf türünün bir nesnesi yok edildiðinde otomatik olarak çaðrýlan baþka bir tür
özel üye fonksiyonu vardýr. Bu fonksiyona yýkýcý (destructor) denir. Yýkýcýlar, bir sýnýfýn, sýnýfýn bir nesnesi yok edilmeden
önce herhangi bir gerekli temizlemeyi yapmasýna olanak saðlar.

Yýkýcýlarýn Ýsimlendirilmesi
----------------------------
Yapýcýlar gibi, yýkýcýlarýn da belirli isimlendirme kurallarý vardýr:

*- Yýkýcýnýn adý, sýnýfýn adýyla ayný olmalý ve önünde bir tilde (~) olmalýdýr.
*- Yýkýcý argüman alamaz.
*- Yýkýcýnýn dönüþ tipi yoktur.
*- Bir sýnýfýn yalnýzca tek bir yýkýcýsý olabilir.

Genellikle bir yýkýcýyý açýkça çaðýrmamalýsýnýz (çünkü nesne yok edildiðinde otomatik olarak çaðrýlýr), çünkü bir nesneyi birden
fazla kez temizlemek isteyeceðiniz nadir durumlar vardýr.

Yýkýcýlar, nesne yýkýcý çalýþtýktan sonra yok edilene kadar diðer üye fonksiyonlarý güvenle çaðýrabilir.

Bir yýkýcý örneði

                #include <iostream>

                class Simple
                {
                private:
                    int m_id {};

                public:
                    Simple(int id)
                        : m_id { id }
                    {
                        std::cout << "Constructing Simple " << m_id << '\n';
                    }

                    ~Simple() // iþte bizim yýkýcý
                    {
                        std::cout << "Destructing Simple " << m_id << '\n';
                    }

                    int getID() const { return m_id; }
                };

                int main()
                {
                    // Bir Simple tahsis et
                    Simple simple1{ 1 };
                    {
                        Simple simple2{ 2 };
                    } // simple2 burada ölür

                    return 0;
                } // simple1 burada ölür

                Bu program aþaðýdaki sonucu üretir:


                Constructing Simple 1
                Constructing Simple 2
                Destructing Simple 2
                Destructing Simple 1

Her Simple nesnesi yok edildiðinde, yýkýcý çaðrýlýr ve bir mesaj yazdýrýr. "Destructing Simple 1" ifadesi,
"Destructing Simple 2" ifadesinden sonra yazdýrýlýr çünkü simple2, fonksiyonun sona ermesinden önce yok edilmiþtir, oysa simple1, 
main() sona erene kadar yok edilmez.

Statik deðiþkenlerin (global deðiþkenler ve statik yerel deðiþkenler dahil) program baþlangýcýnda oluþturulduðunu ve program 
kapanýþýnda yok edildiðini unutmayýn.

UserSettings programýný iyileþtirme
-----------------------------------
Dersin baþýndaki örneðimize geri dönersek, kullanýcýnýn açýkça sendData() çaðýrma ihtiyacýný, bir yýkýcýnýn bu fonksiyonu 
çaðýrmasýyla ortadan kaldýrabiliriz:

                class NetworkData
                {
                private:
                    std::string m_serverName{};
                    DataStore m_data{};

                public:
                    NetworkData(std::string_view serverName)
                        : m_serverName { serverName }
                    {
                    }

                    ~NetworkData()
                    {
                        sendData(); // nesne yok edilmeden önce tüm verilerin gönderildiðinden emin olun
                    }

                    void addData(std::string_view data)
                    {
                        m_data.add(data);
                    }

                    void sendData()
                    {
                        // sunucuya baðlan
                        // tüm verileri gönder
                        // verileri temizle
                    }
                };

                int main()
                {
                    NetworkData n("someipAddress");

                    n.addData("somedata1");
                    n.addData("somedata2");

                    return 0;
                }

Böyle bir yýkýcý ile, NetworkData nesnemiz her zaman nesne yok edilmeden önce sahip olduðu tüm verileri gönderecektir! 
Temizlik otomatik olarak gerçekleþir, bu da hatalarýn daha az olasýlýðýný ve düþünülmesi gereken daha az þey anlamýna gelir.

Bir implicit yýkýcý
-------------------
Eðer bir toplu olmayan sýnýf tipi nesnenin kullanýcý tarafýndan bildirilen bir yýkýcýsý yoksa, derleyici boþ bir gövdeye sahip
bir yýkýcý oluþturur. Bu yýkýcýya implicit yýkýcý denir ve etkin olarak sadece bir yer tutucudur.

Eðer sýnýfýnýzýn yok edilmesi sýrasýnda herhangi bir temizlik yapmasýna gerek yoksa, hiçbir yýkýcý tanýmlamamanýz ve derleyicinin
sýnýfýnýz için bir implicit yýkýcý oluþturmasýna izin vermeniz tamam.

std::exit() fonksiyonu hakkýnda bir uyarý

8.12 dersinde -- Duraklatmalar (programýnýzý erken sonlandýrma), std::exit() fonksiyonunu tartýþtýk, programýnýzý hemen
sonlandýrmak için kullanýlabilir. Program hemen sonlandýrýldýðýnda, program sadece sona erer. Öncelikle yerel deðiþkenler yok
edilmez ve bu nedenle hiçbir yýkýcý çaðrýlmaz. Böyle bir durumda yýkýcýlarýnýzýn gerekli temizlik iþlerini yapmasýna 
güveniyorsanýz dikkatli olun.

15.5 — Üye Fonksiyonlarý olan Sýnýf Þablonlarý
----------------------------------------------
11.6 -- Fonksiyon Þablonlarý dersinde, fonksiyon þablonlarýna bir göz attýk:

                template <typename T> // bu þablon parametre bildirimidir
                T max(T x, T y) // bu max<T> için fonksiyon þablonu tanýmýdýr
                {
                    return (x < y) ? y : x;
                }

Bir fonksiyon þablonu ile, tür þablon parametrelerini (ör. typename T) tanýmlayabilir ve ardýndan bunlarý fonksiyon
parametrelerimizin türü olarak kullanabiliriz (T x, T y).

13.11 -- Sýnýf Þablonlarý dersinde, sýnýf þablonlarýný ele aldýk, bu da bize sýnýf türlerinin (struct, sýnýflar ve unions) 
veri üyelerinin türü için tür þablon parametrelerini kullanma imkaný verir:

                #include <iostream>

                template <typename T>
                struct Pair
                {
                    T first{};
                    T second{};
                };

                // Ýþte Pair için bir çýkarým kýlavuzu (C++17 veya daha eski sürümlerde gereklidir)
                // T ve T türündeki argümanlarla baþlatýlan Pair nesneleri Pair<T> olarak çýkarýlmalýdýr
                template <typename T>
                Pair(T, T) -> Pair<T>;

                int main()
                {
                    Pair<int> p1{ 5, 6 };        // Pair<int> örneðini oluþturur ve p1 nesnesini oluþturur
                    std::cout << p1.first << ' ' << p1.second << '\n';

                    Pair<double> p2{ 1.2, 3.4 }; // Pair<double> örneðini oluþturur ve p2 nesnesini oluþturur
                    std::cout << p2.first << ' ' << p2.second << '\n';

                    Pair<double> p3{ 7.8, 9.0 }; // önceki Pair<double> tanýmýný kullanarak p3 nesnesini oluþturur
                    std::cout << p3.first << ' ' << p3.second << '\n';

                    return 0;
                }

Ýlgili içerik

Çýkarým kýlavuzlarýný 13.12 -- Sýnýf Þablonu Argüman Çýkarýmý (CTAD) ve Çýkarým Kýlavuzlarý dersinde tartýþýyoruz.

Bu derste, hem fonksiyon þablonlarýnýn hem de sýnýf þablonlarýnýn unsurlarýný birleþtirirken, üye fonksiyonlarý olan sýnýf 
þablonlarýna daha yakýndan bakacaðýz.

Üye Fonksiyonlarda Tür Þablon Parametreleri
-------------------------------------------
Bir sýnýf þablonu parametre bildiriminin bir parçasý olarak tanýmlanan tür þablon parametreleri, hem veri üyelerinin türü olarak 
hem de üye fonksiyon parametrelerinin türü olarak kullanýlabilir.

Aþaðýdaki örnekte, yukarýdaki Pair sýnýf þablonunu yeniden yazýyoruz, onu bir yapýdan bir sýnýfa dönüþtürüyoruz:

                #include <ios>       // for std::boolalpha
                #include <iostream>

                template <typename T>
                class Pair
                {
                private:
                    T m_first{};
                    T m_second{};

                public:
                    // Bir üye fonksiyonu sýnýf tanýmýnýn içinde tanýmladýðýmýzda,
                    // sýnýfa ait þablon parametre bildirimi geçerli olur
                    Pair(const T& first, const T& second)
                        : m_first{ first }
                        , m_second{ second }
                    {
                    }

                    bool isEqual(const Pair<T>& pair);
                };

                // Bir üye fonksiyonu sýnýf tanýmýnýn dýþýnda tanýmladýðýmýzda,
                // bir þablon parametre bildirimini yeniden saðlamamýz gerekiyor
                template <typename T>
                bool Pair<T>::isEqual(const Pair<T>& pair)
                {
                    return m_first == pair.m_first && m_second == pair.m_second;
                }

                int main()
                {
                    Pair p1{ 5, 6 }; // CTAD'yi kullanarak Pair<int> türünü çýkarýr
                    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
                    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

                    return 0;
                }

Yukarýdaki oldukça basit olmalý, ancak belirtmeye deðer birkaç þey var.

Ýlk olarak, sýnýfýmýzýn özel üyeleri olduðu için, bir topluluk deðildir ve bu nedenle topluluk baþlatmasýný kullanamaz.
Bunun yerine, sýnýf nesnelerimizi bir yapýlandýrýcý kullanarak baþlatmamýz gerekiyor.

Sýnýf veri üyelerimiz T türünde olduðundan, yapýlandýrýcýmýzýn parametrelerini const T& türünde yaparýz, böylece kullanýcý ayný
türde baþlatma deðerleri saðlayabilir. T'nin kopyalanmasý pahalý olabileceðinden, deðerden ziyade const referans ile geçmek daha 
güvenlidir.

Bir üye fonksiyonunu sýnýf þablonu tanýmýnýn içinde tanýmladýðýmýzda, üye fonksiyon için bir þablon parametre bildirimi
saðlamamýza gerek yoktur. Bu tür üye fonksiyonlar, sýnýf þablonu parametre bildirimini dolaylý olarak kullanýr.

Ýkinci olarak, topluluk olmayan sýnýflarla CTAD'yi çalýþtýrmak için çýkarým kýlavuzlarýna ihtiyacýmýz yoktur.
Eþleþen bir yapýlandýrýcý, derleyiciye baþlatýcýlarýndan þablon parametrelerini çýkarmak için gereken bilgileri saðlar.

Üçüncü olarak, bir sýnýf þablonu için bir üye fonksiyonu sýnýf þablonu tanýmýnýn dýþýnda tanýmladýðýmýz durumu daha yakýndan
inceleyelim:

                template <typename T>
                bool Pair<T>::isEqual(const Pair<T>& pair)
                {
                    return m_first == pair.m_first && m_second == pair.m_second;
                }

Bu üye fonksiyon tanýmý, sýnýf þablonu tanýmýndan ayrý olduðu için, derleyicinin T'nin ne olduðunu bilmesi için bir þablon
parametre bildirimini (template <typename T>) yeniden saðlamamýz gerekiyor.

Ayrýca, bir üye fonksiyonu sýnýfýn dýþýnda tanýmladýðýmýzda, üye fonksiyon adýný sýnýf þablonunun tamamen þablonlanmýþ adýyla
nitelendirmemiz gerekiyor (Pair<T>::isEqual, not Pair::isEqual).

Sýnýf Þablonlarý Ýçin Üye Fonksiyonlarý Nerede Tanýmlanmalý
-----------------------------------------------------------
Sýnýf þablonlarý için üye fonksiyonlarla, derleyicinin hem sýnýf tanýmýný (üye fonksiyon þablonunun sýnýfýn bir parçasý olarak 
bildirildiðinden emin olmak için) hem de þablon üye fonksiyon tanýmýný (þablonu nasýl örnekleneceðini bilmek için) 
görmesi gerekiyor. Bu nedenle, genellikle hem bir sýnýfý hem de üye fonksiyon þablonlarýný ayný yerde tanýmlamak istiyoruz.

Bir üye fonksiyon þablonu, sýnýf tanýmýnýn içinde tanýmlandýðýnda, þablon üye fonksiyon tanýmý, sýnýf tanýmýnýn bir parçasýdýr,
bu yüzden sýnýf tanýmýnýn görülebildiði her yerde, þablon üye fonksiyon tanýmý da görülebilir. Bu, iþleri kolaylaþtýrýr 
(sýnýf tanýmýmýzý karýþtýrma pahasýna).

Bir üye fonksiyon þablonu, sýnýf tanýmýnýn dýþýnda tanýmlandýðýnda, genellikle sýnýf tanýmýnýn hemen altýnda tanýmlanmalýdýr.
Bu þekilde, sýnýf tanýmýnýn görülebildiði her yerde, sýnýf tanýmýnýn hemen altýndaki üye fonksiyon þablon tanýmlarý da görülebilir

Bir sýnýfýn tipik olarak bir header dosyasýnda tanýmlandýðý durumda, bu, sýnýfýn dýþýnda tanýmlanan herhangi bir üye fonksiyon
þablonunun da ayný header dosyasýnda, sýnýf tanýmýnýn altýnda tanýmlanmasý gerektiði anlamýna gelir.

Anahtar nokta þudur ki, 11.7 -- Function template instantiation dersinde, þablonlardan dolaylý olarak örneklendirilen
fonksiyonlarýn dolaylý olarak inline olduðunu belirttik. Bu, hem üye olmayan hem de üye fonksiyon þablonlarýný içerir.
Bu nedenle, header dosyalarýnda tanýmlanan üye fonksiyon þablonlarýný birden çok kod dosyasýna dahil etmede bir sorun yoktur,
çünkü bu þablonlardan örneklendirilen fonksiyonlar dolaylý olarak inline olacaktýr (ve linker bunlarý çoðaltacaktýr).

*** BEST -> Sýnýf tanýmýnýn dýþýnda tanýmlanan herhangi bir üye fonksiyon þablonu, sýnýf tanýmýnýn hemen altýnda tanýmlanmalýdýr 
            (ayný dosyada).

15.6 — Statik Üye Deðiþkenler
-----------------------------
7.4 -- Global deðiþkenlere giriþ dersinde, global deðiþkenleri ve 7.10 -- Statik yerel deðiþkenler dersinde statik yerel
deðiþkenleri tanýttýk. Bu tür deðiþkenlerin her ikisi de statik süreye sahiptir, yani programýn baþýnda oluþturulur ve
programýn sonunda yok edilir. Bu tür deðiþkenler, kapsamlarý dýþýna çýksalar bile deðerlerini korurlar.
Örneðin:

                #include <iostream>

                int generateID()
                {
                    static int s_id{ 0 }; // statik yerel deðiþken
                    return ++s_id;
                }

                int main()
                {
                    std::cout << generateID() << '\n';
                    std::cout << generateID() << '\n';
                    std::cout << generateID() << '\n';

                    return 0;
                }
                Bu program þunu yazdýrýr:
                1
                2
                3
Statik yerel deðiþken s_id'nin birden çok fonksiyon çaðrýsý boyunca deðerini koruduðunu unutmayýn.

Sýnýf türleri, statik anahtar kelimesi için iki yeni kullaným getirir: statik üye deðiþkenler ve statik üye fonksiyonlar.
Neyse ki, bu kullanýmlar oldukça basittir. Bu derste statik üye deðiþkenlerden bahsedeceðiz ve bir sonraki derste 
statik üye fonksiyonlardan bahsedeceðiz.

Statik Üye Deðiþkenler
----------------------
Üye deðiþkenlere uygulanan statik anahtar kelimesine girmeden önce, aþaðýdaki sýnýfý düþünün:

                #include <iostream>

                struct Something
                {
                    int value{ 1 };
                };

                int main()
                {
                    Something first{};
                    Something second{};

                    first.value = 2;

                    std::cout << first.value << '\n';
                    std::cout << second.value << '\n';

                    return 0;
                }

Bir sýnýf nesnesi oluþturduðumuzda, her nesne tüm normal üye deðiþkenlerinin kendi kopyasýný alýr. Bu durumda, iki Something sýnýf
nesnesi bildirdiðimiz için, value'nun iki kopyasýna sahip oluruz: first.value ve second.value. first.value, second.value'dan 
farklýdýr. Sonuç olarak, yukarýdaki program þunu yazdýrýr:

                2
                1
Bir sýnýfýn üye deðiþkenleri, static anahtar kelimesi kullanýlarak statik yapýlabilir. Normal üye deðiþkenlerin aksine, 
statik üye deðiþkenler tüm sýnýf nesneleri tarafýndan paylaþýlýr. Yukarýdakine benzer aþaðýdaki programý düþünün:

                #include <iostream>

                struct Something
                {
                    static int s_value; // þimdi statik
                };

                int Something::s_value{ 1 }; // s_value'yi 1'e baþlat

                int main()
                {
                    Something first{};
                    Something second{};

                    first.s_value = 2;

                    std::cout << first.s_value << '\n';
                    std::cout << second.s_value << '\n';
                    return 0;
                }
                Bu program aþaðýdaki çýktýyý üretir:

                2
                2
Çünkü s_value bir statik üye deðiþken olduðu için, s_value tüm sýnýf nesneleri arasýnda paylaþýlýr. Sonuç olarak, first.s_value,
second.s_value ile ayný deðiþkendir. Yukarýdaki program, first kullanarak ayarladýðýmýz deðerin second kullanýlarak 
eriþilebildiðini gösterir!

Statik üyeler sýnýf nesneleriyle iliþkili deðildir
--------------------------------------------------
Statik üyelere bir sýnýfýn nesneleri aracýlýðýyla eriþebilirsiniz (yukarýdaki örnekte first.s_value ve second.s_value ile 
gösterildiði gibi), statik üyeler, sýnýfýn hiçbir nesnesi oluþturulmamýþ olsa bile var olur! Bu mantýklýdýr: programýn baþýnda 
oluþturulurlar ve programýn sonunda yok edilirler, bu yüzden ömürleri normal bir üye gibi bir sýnýf nesnesine baðlý deðildir.

Temelde, statik üyeler, sýnýfýn kapsam bölgesi içinde yaþayan global deðiþkenlerdir. Bir sýnýfýn statik üyesi ile bir ad alaný
içindeki normal bir deðiþken arasýnda çok az fark vardýr.

Anahtar nokta þudur ki, Statik üyeler, sýnýfýn kapsam bölgesi içinde yaþayan global deðiþkenlerdir.

Statik üye s_value, herhangi bir sýnýf nesnesinden baðýmsýz olarak var olduðu için, sýnýf adý ve kapsam çözümleme operatörü 
kullanýlarak doðrudan eriþilebilir (bu durumda, Something::s_value):

                class Something
                {
                public:
                    static int s_value; // statik üye deðiþkenini bildirir
                };

                int Something::s_value{ 1 }; // statik üye deðiþkenini tanýmlar (bu bölümü aþaðýda tartýþacaðýz)

                int main()
                {
                    // not: Something tipinde herhangi bir nesne oluþturmuyoruz

                    Something::s_value = 2;
                    std::cout << Something::s_value << '\n';
                    return 0;
                }
Yukarýdaki parçada, s_value bir nesne yerine Something sýnýf adý tarafýndan referans alýnýr. Something tipinde bir nesne bile
oluþturmadýðýmýzý not edin, ancak hala Something::s_value'ye eriþebiliyor ve kullanabiliyoruz. Bu, statik üyelere eriþmek için 
tercih edilen yöntemdir.

*** BEST -> Statik üyelere, sýnýf adýný ve kapsam çözümleme operatörünü (::) kullanarak eriþin.

Statik Üye Deðiþkenlerin Tanýmlanmasý ve Baþlatýlmasý
-----------------------------------------------------   
Bir sýnýf türü içinde bir statik üye deðiþkeni bildirdiðimizde, derleyiciye bir statik üye deðiþkeninin varlýðý hakkýnda bilgi
veriyoruz, ancak aslýnda onu tanýmlamýyoruz (týpký bir ileri bildirim gibi). Statik üye deðiþkenler esasen global deðiþkenler
olduðu için, statik üyeyi sýnýfýn dýþýnda, global kapsamda açýkça tanýmlamalý ve isteðe baðlý olarak baþlatmalýsýnýz.

Yukarýdaki örnekte, bunu bu satýr aracýlýðýyla yapýyoruz:

                int Something::s_value{ 1 }; // statik üye deðiþkenini tanýmlar

Bu satýr iki amaca hizmet eder: statik üye deðiþkenini oluþturur (týpký bir global deðiþken gibi) ve onu baþlatýr. Bu durumda,
baþlatma deðeri olarak 1'i saðlýyoruz. Baþlatýcý saðlanmazsa, statik üye deðiþkenler varsayýlan olarak sýfýra baþlatýlýr.

Bu statik üye tanýmýnýn eriþim kontrollerine tabi olmadýðýný unutmayýn: deðeri tanýmlayabilir ve baþlatabilirsiniz,
hatta sýnýfta özel (veya korumalý) olarak bildirilmiþ olsa bile.

Eðer sýnýf bir baþlýk (.h) dosyasýnda tanýmlanmýþsa, statik üye tanýmý genellikle sýnýf için iliþkili kod dosyasýna 
(örneðin Something.cpp) yerleþtirilir. Eðer sýnýf bir kaynak (.cpp) dosyasýnda tanýmlanmýþsa, statik üye tanýmý genellikle sýnýfýn
hemen altýna yerleþtirilir. Statik üye tanýmýný bir baþlýk dosyasýna koymayýn (global bir deðiþken gibi, eðer bu baþlýk dosyasý
birden fazla kez dahil edilirse, birden fazla tanýmýnýz olacak ve bu bir derleme hatasýna neden olacaktýr).

Sýnýf tanýmý içinde statik üye deðiþkenlerinin baþlatýlmasý
-----------------------------------------------------------
Yukarýdakilere birkaç kýsayol vardýr. Ýlk olarak, statik üye bir sabit integral tip (char ve bool dahil) veya const enum olduðunda
statik üye sýnýf tanýmý içinde baþlatýlabilir:

                class Whatever
                {
                public:
                    static const int s_value{ 4 }; // bir static const int doðrudan tanýmlanabilir ve baþlatýlabilir
                };
Yukarýdaki örnekte, statik üye deðiþkeni bir const int olduðu için, açýk bir taným satýrýna gerek yoktur.

7.9 dersinde -- Global sabitleri birden çok dosya arasýnda paylaþma (inline deðiþkenler kullanarak), birden çok tanýma sahip
olabilen deðiþkenler olan inline deðiþkenleri tanýttýk. C++17, statik üyelerin inline deðiþken olmasýna izin verir:

                class Whatever
                {
                public:
                    static inline int s_value{ 4 }; // bir static inline deðiþken doðrudan tanýmlanabilir ve baþlatýlabilir
                };

Bu tür deðiþkenler, sabit olup olmadýklarýna bakýlmaksýzýn sýnýf tanýmý içinde baþlatýlabilir.
Bu, statik üyeleri tanýmlama ve baþlatma yöntemidir.

Çünkü constexpr üyeler implicit olarak inline'dýr (C++17 itibariyle), static constexpr üyeler de inline anahtar kelimesinin açýkça
kullanýlmasýna gerek kalmadan sýnýf tanýmý içinde baþlatýlabilir:

                #include <string_view>

                class Whatever
                {
                public:
                    static constexpr double s_value{ 2.2 }; // tamam
                    static constexpr std::string_view s_view{ "Hello" }; // bu, constexpr baþlatmayý 
                                                                         // destekleyen sýnýflar için bile çalýþýr
                };

*** BEST -> Statik üyelerinizi inline veya constexpr yapýn, böylece sýnýf tanýmý içinde baþlatýlabilirler.

Statik üye deðiþkenlerin bir örneði
-----------------------------------
Neden sýnýflarýn içinde statik deðiþkenler kullanýlýr? Bir kullanýmý, her sýnýf örneðine benzersiz bir ID atamaktýr. 
Ýþte bir örnek:

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_idGenerator { 1 };
                    int m_id {};

                public:
                    // id oluþturucudan sonraki deðeri al
                    Something() : m_id { s_idGenerator++ }
                    {
                    }

                    int getID() const { return m_id; }
                };

                int main()
                {
                    Something first{};
                    Something second{};
                    Something third{};

                    std::cout << first.getID() << '\n';
                    std::cout << second.getID() << '\n';
                    std::cout << third.getID() << '\n';
                    return 0;
                }
                Bu program þunu yazdýrýr:
                1
                2
                3

Çünkü s_idGenerator tüm Something nesneleri tarafýndan paylaþýldýðý için, yeni bir Something nesnesi oluþturulduðunda,
yapýcý m_id'yi s_idGenerator'un mevcut deðeriyle baþlatýr ve sonra bir sonraki nesne için deðeri artýrýr. Bu, her oluþturulan
Something nesnesinin benzersiz bir id almasýný garanti eder (oluþturma sýrasýna göre artýrýlýr).

Her nesneye benzersiz bir ID vermek, hata ayýklamada yardýmcý olabilir, çünkü aksi halde ayný verilere sahip nesneleri ayýrt etmek
için kullanýlabilir. Bu, veri dizileriyle çalýþýrken özellikle doðrudur.

Statik üye deðiþkenler ayrýca sýnýfýn bir arama tablosunu kullanmasý gerektiðinde de yararlýdýr (örneðin, bir dizi, bir dizi
önceden hesaplanmýþ deðerleri saklamak için kullanýlýr). Arama tablosunu statik yaparak, tüm nesneler için yalnýzca bir kopya
vardýr, her oluþturulan nesne için bir kopya yapmak yerine. Bu, önemli miktarda bellek tasarrufu saðlayabilir.

Statik Üye Fonksiyonlar
-----------------------
15.6 -- Statik Üye Deðiþkenler dersinde, statik üye deðiþkenlerin sýnýfa deðil, sýnýfýn nesnelerine ait olduðunu öðrendiniz. Eðer
bir statik üye deðiþken public ise, sýnýf adý ve kapsam çözümleme operatörü kullanýlarak doðrudan eriþilebilir:

                #include <iostream>

                class Something
                {
                public:
                    static inline int s_value { 1 };
                };

                int main()
                {
                    std::cout << Something::s_value; // s_value public'tir, doðrudan eriþebiliriz
                }
Peki ya bir statik üye deðiþken private ise? Aþaðýdaki örneði düþünün:

                #include <iostream>

                class Something
                {
                private: // þimdi private
                    static inline int s_value { 1 };
                };

                int main()
                {
                    std::cout << Something::s_value; // hata: s_value private ve sýnýfýn dýþýndan doðrudan eriþilemez
                }
Bu durumda, Something::s_value'ye main() fonksiyonundan doðrudan eriþemeyiz, çünkü bu private'dir. Normalde private üyelere public
üye fonksiyonlar aracýlýðýyla eriþiriz. s_value'ye eriþmek için normal bir public üye fonksiyon oluþturabilirdik, ancak bu durumda
fonksiyonu kullanmak için sýnýf türünde bir nesne oluþturmamýz gerekirdi!

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_value { 1 };

                public:
                    int getValue() { return s_value; }
                };

                int main()
                {
                    Something s{};
                    std::cout << s.getValue(); // çalýþýr, ancak getValue() çaðrýsýný yapmak için bir nesne oluþturmayý gerektirir
                }
Daha iyisini yapabiliriz.

Statik Üye Fonksiyonlar
-----------------------
Üye deðiþkenler, statik yapýlabilecek tek türde üye deðildir. Üye fonksiyonlar da statik yapýlabilir. Ýþte yukarýdaki örnekle
bir statik üye fonksiyon eriþimcisi:

                #include <iostream>

                class Something
                {
                private:
                    static inline int s_value { 1 };

                public:
                    static int getValue() { return s_value; } // statik üye fonksiyon
                };

                int main()
                {
                    std::cout << Something::getValue() << '\n';
                }
Statik üye fonksiyonlar belirli bir nesneyle iliþkili olmadýðýndan, sýnýf adý ve kapsam çözümleme operatörünü 
(ör. Something::getValue()) kullanarak doðrudan çaðrýlabilir. Statik üye deðiþkenler gibi, sýnýf türündeki nesneler aracýlýðýyla
da çaðrýlabilirler, ancak bu önerilmez.

Statik Üye Fonksiyonlarýnýn *this Ýþaretçisi Yoktur
---------------------------------------------------
Statik üye fonksiyonlarýn dikkate deðer iki ilginç özelliði vardýr. Ýlk olarak, statik üye fonksiyonlar bir nesneye baðlý
olmadýðýndan, *this iþaretçileri yoktur! Bu, düþündüðünüzde mantýklýdýr -- *this iþaretçisi her zaman üye fonksiyonun üzerinde 
çalýþtýðý nesneyi gösterir. Statik üye fonksiyonlar bir nesne üzerinde çalýþmaz, bu yüzden *this iþaretçisine ihtiyaç yoktur.

Ýkinci olarak, statik üye fonksiyonlar diðer statik üyelere (deðiþkenler veya fonksiyonlar) doðrudan eriþebilir, ancak statik 
olmayan üyelere eriþemezler. Bu, statik olmayan üyelerin bir sýnýf nesnesine ait olmasý gerektiði ve statik üye fonksiyonlarýnýn 
çalýþacak bir sýnýf nesnesi olmadýðý içindir!

Baþka bir Örnek

Statik üye fonksiyonlar da sýnýf bildiriminin dýþýnda tanýmlanabilir. Bu, normal üye fonksiyonlar için olduðu gibi ayný þekilde 
çalýþýr.

                #include <iostream>

                class IDGenerator
                {
                private:
                    static inline int s_nextID { 1 };

                public:
                     static int getNextID(); // Ýþte bir statik fonksiyon için bildirim
                };

                // Ýþte sýnýfýn dýþýndaki statik fonksiyonun tanýmý. Burada statik anahtar kelimesini kullanmýyoruz.
                int IDGenerator::getNextID() { return s_nextID++; }

                int main()
                {
                    for (int count{ 0 }; count < 5; ++count)
                        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

                    return 0;
                }

                Bu program þunu yazdýrýr:

                The next ID is: 1
                The next ID is: 2
                The next ID is: 3
                The next ID is: 4
                The next ID is: 5
Not edin ki, bu sýnýftaki tüm veri ve fonksiyonlar statik olduðu için, iþlevselliðinden yararlanmak için bir nesne oluþturmamýza
gerek yok! Bu sýnýf, atanacak bir sonraki ID'nin deðerini tutmak için bir statik üye deðiþken kullanýr ve bu ID'yi döndürmek 
ve artýrmak için bir statik üye fonksiyon saðlar.

Tüm statik üyelere sahip sýnýflar hakkýnda bir uyarý
----------------------------------------------------
Tüm statik üyelere sahip sýnýflarý yazarken dikkatli olun. Bu tür "saf statik sýnýflar" (veya "monostatlar") yararlý olabilir, 
ancak bazý potansiyel dezavantajlarý da vardýr.

Öncelikle, tüm statik üyeler yalnýzca bir kez örneklendiði için, saf bir statik sýnýfýn birden çok kopyasýný oluþturmanýn bir yolu
yoktur (sýnýfý klonlamadan ve yeniden adlandýrmadan). Örneðin, iki baðýmsýz IDGenerator'a ihtiyacýnýz varsa, bu saf bir statik
sýnýf ile mümkün olmaz.

Ýkincisi, global deðiþkenler dersinde, global deðiþkenlerin tehlikeli olduðunu öðrendiniz çünkü herhangi bir kod parçasý global
deðiþkenin deðerini deðiþtirebilir ve baþka bir görünüþte ilgisiz kod parçasýný bozabilir. Aynýsý saf statik sýnýflar için de 
geçerlidir. Tüm üyelerin sýnýfa (sýnýfýn nesnesi yerine) ait olmasý ve sýnýf bildirimlerinin genellikle global kapsama sahip
olmasý nedeniyle, saf bir statik sýnýf, global deðiþkenlerin tüm gerekli dezavantajlarýna sahip olan, global olarak eriþilebilir
bir ad alanýnda fonksiyonlar ve global deðiþkenler bildirmenin esasen eþdeðeridir.

Tüm statik üyelere sahip bir sýnýf yazmak yerine, normal bir sýnýf yazmayý ve onun global bir örneðini oluþturmayý düþünün
(global deðiþkenler statik süreye sahiptir). Bu þekilde, global örnek uygun olduðunda kullanýlabilir, ancak yerel örnekler
gerektiðinde hala örneklenebilir.

Saf statik sýnýflar vs. ad alanlarý
-----------------------------------
Saf statik sýnýflarýn ad alanlarýyla çok fazla örtüþmesi vardýr. Her ikisi de statik süreye sahip deðiþkenleri ve kapsam
bölgesindeki fonksiyonlarý tanýmlamanýza izin verir. Ancak, önemli bir fark, sýnýflarýn eriþim kontrollerine sahip olmasý,
ad alanlarýnýn ise olmamasýdýr.

Genel olarak, statik veri üyelerine ve/veya eriþim kontrollerine ihtiyacýnýz varsa, statik bir sýnýf tercih edilir. Aksi takdirde,
bir ad alanýný tercih edin.

C++ statik yapýlandýrýcýlarý desteklemez
----------------------------------------
Normal üye deðiþkenlerini bir yapýlandýrýcý aracýlýðýyla baþlatabiliyorsanýz, o zaman statik üye deðiþkenlerini bir statik
yapýlandýrýcý aracýlýðýyla baþlatmanýn mantýklý olduðunu düþünmek mantýklýdýr. Ve bazý modern diller, tam da bu amaçla statik
yapýlandýrýcýlarý desteklerken, ne yazýk ki C++ bunlardan biri deðildir.
Statik deðiþkeninizi doðrudan baþlatabiliyorsanýz, bir yapýlandýrýcýya ihtiyaç yoktur: statik üye deðiþkenini taným noktasýnda 
baþlatabilirsiniz (özel olsa bile). Bunu yukarýdaki IDGenerator örneðinde yapýyoruz. Ýþte baþka bir örnek:

                #include <iostream>

                struct Chars
                {
                    char first{};
                    char second{};
                    char third{};
                    char fourth{};
                    char fifth{};
                };

                struct MyClass
                {
                    static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // statik deðiþkeni taným noktasýnda baþlat
                };

                int main()
                {
                    std::cout << MyClass::s_mychars.third; // i yazdýr

                    return 0;
                }
Statik üye deðiþkeninizi baþlatmak kodun çalýþtýrýlmasýný gerektiriyorsa (örneðin bir döngü), bunu yapmanýn birçok farklý,
biraz karmaþýk yolu vardýr. Tüm deðiþkenlerle, statik olsun veya olmasýn, çalýþan bir yol, bir nesne oluþturmak, onu verilerle
doldurmak ve çaðýran kiþiye döndürmek için bir fonksiyon kullanmaktýr. Bu döndürülen deðer, baþlatýlan nesneye kopyalanabilir.

                #include <iostream>

                struct Chars
                {
                    char first{};
                    char second{};
                    char third{};
                    char fourth{};
                    char fifth{};
                };

                class MyClass
                {
                private:
                    static Chars generate()
                    {
                        Chars c{}; // bir nesne oluþtur
                        c.first = 'a'; // onu istediðiniz gibi deðerlerle doldurun
                        c.second = 'e';
                        c.third = 'i';
                        c.fourth = 'o';
                        c.fifth = 'u';

                        return c; // nesneyi döndür
                    }

                public:
                    static inline Chars s_mychars { generate() }; // döndürülen nesneyi s_mychars'a kopyala
                };

                int main()
                {
                    std::cout << MyClass::s_mychars.third; // i yazdýr

                    return 0;
                }
Ýlgili içerik
Bunun için bir lambda da kullanýlabilir.
Bu metodolojinin pratik bir örneðini 8.15 -- Global random numbers (Random.h) dersinde gösteriyoruz (bunu bir ad alaný yerine bir
statik sýnýf ile yapýyoruz, ayný þekilde çalýþýr)

15.8 — Friend Non-Member Fonksiyonlar
-------------------------------------
Bu bölüm ve önceki bölüm boyunca, bir sýnýfýn çeþitli üyelerine kimin eriþebileceðini kontrol etmek için bir mekanizma saðlayan
eriþim kontrollerinin erdemlerini övdük. Özel üyeler yalnýzca sýnýfýn diðer üyeleri tarafýndan eriþilebilir ve genel üyeler
herkes tarafýndan eriþilebilir. 14.6 dersinde -- Eriþim Fonksiyonlarý konusunda, verilerinizi özel tutmanýn ve dýþ üyeler
için bir genel arayüz oluþturmanýn faydalarýný tartýþtýk.

Ancak, bu düzenlemenin yeterli olmadýðý veya ideal olmadýðý durumlar vardýr.

Örneðin, bazý verileri yönetmeye odaklanan bir depolama sýnýfýný düþünün. Þimdi diyelim ki bu verileri de göstermek istiyorsunuz,
ancak gösterimi yöneten kodun birçok seçeneði vardýr ve bu nedenle karmaþýktýr. Hem depolama yönetimi fonksiyonlarýný hem de
gösterim yönetimi fonksiyonlarýný ayný sýnýfa koyabilirsiniz, ancak bu iþleri karýþtýrýr ve karmaþýk bir arayüz oluþturur.
Ayrýca onlarý ayrý tutabilirsiniz: depolama sýnýfý depolamayý yönetir ve baþka bir gösterim sýnýfý tüm gösterim yeteneklerini 
yönetir. Bu, güzel bir sorumluluk ayrýmý yaratýr. Ancak gösterim sýnýfý, daha sonra depolama sýnýfýnýn özel üyelerine eriþemeyecek
ve iþini yapamayabilir.

Alternatif olarak, sözdizimsel olarak bir üye fonksiyon yerine bir dýþ üye fonksiyonu kullanmayý tercih edebileceðimiz durumlar 
vardýr (bunu aþaðýda bir örnekle göstereceðiz). Bu, genellikle operatörlerin aþýrý yüklenmesi durumunda geçerlidir, bu konuyu 
gelecekteki derslerde tartýþacaðýz. Ancak dýþ üye fonksiyonlar ayný soruna sahiptir - sýnýfýn özel üyelerine eriþemezler.

Eðer eriþim fonksiyonlarý (veya diðer genel üye fonksiyonlar) zaten var ve uygulamaya çalýþtýðýmýz yetenek için yeterliyse, 
o zaman harika - bunlarý kullanabiliriz (ve kullanmalýyýz). Ancak bazý durumlarda, bu fonksiyonlar mevcut deðildir.
O zaman ne yapmalý?

Bir seçenek, sýnýfa yeni üye fonksiyonlar eklemek olabilir, böylece diðer sýnýflarýn veya dýþ üye fonksiyonlarýn baþka türlü 
yapamayacaklarý iþi yapmalarýna izin verir. Ancak eðer sýnýf bizim deðilse (belki bir üçüncü taraf kütüphanesinin bir parçasýdýr),
muhtemelen sýnýfý deðiþtirmek istemeyiz (çünkü kütüphaneyi güncellersek, bu eklemelerin üzerine yazýlýr). Hatta sýnýf bizim olsa 
bile, belirli þeylerin genel halka açýk olmasýný istemeyebiliriz.

Aslýnda ihtiyacýmýz olan þey, eriþim kontrol sistemini duruma göre aþmanýn bir yoludur.

Arkadaþlýk sihirlidir
---------------------
Bu zorluðun cevabý, arkadaþlýktýr.

Bir sýnýfýn gövdesi içinde, bir arkadaþ bildirimi (friend anahtar kelimesi kullanýlarak) derleyiciye baþka bir sýnýfýn veya
fonksiyonun artýk bir arkadaþ olduðunu söylemek için kullanýlabilir. C++, bir arkadaþ, baþka bir sýnýfýn özel ve korumalý 
üyelerine tam eriþim hakký verilmiþ bir sýnýf veya fonksiyon (üye veya dýþ üye) anlamýna gelir. Bu þekilde, bir sýnýf diðer
sýnýflara veya fonksiyonlara üyelerine tam eriþim hakký verebilir ve baþka hiçbir þeyi etkilemez.

Anahtar nokta þudur ki, Arkadaþlýk her zaman üyelerine eriþilecek olan sýnýf tarafýndan saðlanýr (eriþim isteyen sýnýf veya 
fonksiyon tarafýndan deðil).Eriþim kontrolleri ve arkadaþlýk verme arasýnda, bir sýnýf her zaman üyelerine kimlerin
eriþebileceðini kontrol etme yeteneðini korur.

Örneðin, depolama sýnýfýmýz gösterim sýnýfýný bir arkadaþ yaptýysa, o zaman gösterim sýnýfý depolama sýnýfýnýn tüm üyelerine
doðrudan eriþebilir. Gösterim sýnýfý, bu doðrudan eriþimi depolama sýnýfýnýn gösterimini uygulamak için kullanabilirken,
yapýsal olarak ayrý kalabilir.

Arkadaþ bildirimi, eriþim kontrollerinden etkilenmez, bu yüzden sýnýf gövdesi içinde nerede yer aldýðý önemli deðildir.


Artýk arkadaþýn ne olduðunu bildiðimize göre, üye olmayan iþlevlere, üye iþlevlerine ve diðer sýnýflara arkadaþlýðýn verildiði
belirli örneklere bakalým. Bu derste üye olmayan arkadaþlarýn fonksiyonlarýný tartýþacaðýz ve ardýndan bir sonraki ders 
15.9 - Arkadaþ sýnýflarý ve arkadaþ üye fonksiyonlarýnda arkadaþ sýnýflarýna ve arkadaþ üye fonksiyonlarýna bir göz atacaðýz.

Friend Non-member Fonksiyonlar
------------------------------
Bir arkadaþ fonksiyon, bir sýnýfýn özel ve korumalý üyelerine sanki o sýnýfýn bir üyesiymiþ gibi eriþebilen bir fonksiyondur
(üye veya üye olmayan). Diðer tüm konularda, arkadaþ fonksiyon normal bir fonksiyondur.

Bir sýnýfýn bir üye olmayan fonksiyonu bir arkadaþ yapma örneðine bakalým:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }

                    // Ýþte Accumulator'un arkadaþý olan üye olmayan fonksiyon void print(const Accumulator& accumulator) 
                    // için arkadaþ bildirimi
                    friend void print(const Accumulator& accumulator);
                };

                void print(const Accumulator& accumulator)
                {
                    // Çünkü print() Accumulator'un bir arkadaþýdýr
                    // Accumulator'un özel üyelerine eriþebilir
                    std::cout << accumulator.m_value;
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplayýcýya 5 ekler

                    print(acc); // print() üye olmayan fonksiyonunu çaðýrýr

                    return 0;
                }

Bu örnekte, Accumulator sýnýfýnýn bir nesnesini alan print() adýnda bir üye olmayan fonksiyon bildirdik. Print() Accumulator 
sýnýfýnýn bir üyesi olmadýðý için, normalde özel üye m_value'ye eriþemezdi. Ancak, Accumulator sýnýfýnýn 
print(const Accumulator& accumulator) fonksiyonunu bir arkadaþ yapan bir arkadaþ bildirimi var, bu artýk mümkün.

Print() bir üye olmayan fonksiyon olduðu için (ve dolayýsýyla implicit bir nesnesi yok), print() ile çalýþmak için açýkça bir 
Accumulator nesnesi geçmemiz gerektiðini unutmayýn.

Bir friend non-member bir sýnýf içinde tanýmlama
------------------------------------------------
Ýstenirse üye fonksiyonlarýn bir sýnýf içinde tanýmlanabileceði gibi, friend non-member fonksiyonlar da bir sýnýf içinde 
tanýmlanabilir. Aþaðýdaki örnekte, arkadaþ üye olmayan fonksiyon print() Accumulator sýnýfý içinde tanýmlanmýþtýr:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }

                    // Sýnýf içinde tanýmlanan arkadaþ fonksiyonlar üye olmayan fonksiyonlardýr
                    friend void print(const Accumulator& accumulator)
                    {
                        // Çünkü print() Accumulator'un bir arkadaþýdýr
                        // Accumulator'un özel üyelerine eriþebilir
                        std::cout << accumulator.m_value;
                    }
                };

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplayýcýya 5 ekler

                    print(acc); // print() üye olmayan fonksiyonunu çaðýrýr

                    return 0;
                }

Print() fonksiyonunun Accumulator içinde tanýmlandýðý için, print() fonksiyonunun Accumulator'un bir üyesi olduðunu
varsayabilirsiniz, ancak bu doðru deðil. Print() bir arkadaþ olarak tanýmlandýðý için, bunun yerine bir non-member fonksiyon
olarak kabul edilir (sanki Accumulator dýþýnda tanýmlanmýþ gibi).

Sözdizimsel olarak bir friend non-member fonksiyonu tercih etme
---------------------------------------------------------------
Bu dersin giriþinde, bazen bir üye fonksiyon yerine bir üye olmayan fonksiyonu tercih edebileceðimiz zamanlardan bahsetmiþtik.
Þimdi bunun bir örneðini gösterelim.

                #include <iostream>

                class Value
                {
                private:
                    int m_value{};

                public:
                    explicit Value(int v): m_value { v }  { }

                    bool isEqualToMember(const Value& v) const;
                    friend bool isEqualToNonmember(const Value& v1, const Value& v2);
                };

                bool Value::isEqualToMember(const Value& v) const
                {
                    return m_value == v.m_value;
                }

                bool isEqualToNonmember(const Value& v1, const Value& v2)
                {
                    return v1.m_value == v2.m_value;
                }

                int main()
                {
                    Value v1 { 5 };
                    Value v2 { 6 };

                    std::cout << v1.isEqualToMember(v2) << '\n';
                    std::cout << isEqualToNonmember(v1, v2) << '\n';

                    return 0;
                }
Bu örnekte, iki Value nesnesinin eþit olup olmadýðýný kontrol eden iki benzer fonksiyon tanýmladýk. isEqualToMember() bir üye
fonksiyonu ve isEqualToNonmember() bir üye olmayan fonksiyondur. Bu fonksiyonlarýn nasýl tanýmlandýðýna odaklanalým.

isEqualToMember() fonksiyonunda, bir nesneyi dolaylý ve diðerini açýkça geçiriyoruz. Fonksiyonun uygulanmasý bunu yansýtýr 
ve m_value'nin dolaylý nesneye ait olduðunu ve v.m_value'nin açýk parametreye ait olduðunu zihinsel olarak uzlaþtýrmamýz gerekir.

isEqualToNonmember() fonksiyonunda, her iki nesne de açýkça geçirilir. Bu, fonksiyonun uygulanmasýnda daha iyi bir paralellik
saðlar, çünkü m_value üyesi her zaman açýkça bir açýk parametre ile öne çýkar.

Hala v1.isEqualToMember(v2) çaðrý sözdizimini isEqualToNonmember(v1, v2) üzerinde tercih edebilirsiniz. Ancak operatör aþýrý 
yüklemeyi ele aldýðýmýzda, bu konunun tekrar gündeme geleceðini göreceðiz.

Çoklu Arkadaþ
-------------
Bir fonksiyon ayný anda birden çok sýnýfýn arkadaþý olabilir. Örneðin, aþaðýdaki örneði düþünün:

                #include <iostream>

                class Humidity; // Humidity'nin ileri bildirimi

                class Temperature
                {
                private:
                    int m_temp { 0 };
                public:
                    explicit Temperature(int temp) : m_temp { temp } { }

                    // bu satýr için ileri bildirim gereklidir
                    friend void printWeather(const Temperature& temperature, const Humidity& humidity); 
                };

                class Humidity
                {
                private:
                    int m_humidity { 0 };
                public:
                    explicit Humidity(int humidity) : m_humidity { humidity } {  }

                    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
                };

                void printWeather(const Temperature& temperature, const Humidity& humidity)
                {
                    std::cout << "The temperature is " << temperature.m_temp <<
                       " and the humidity is " << humidity.m_humidity << '\n';
                }

                int main()
                {
                    Humidity hum { 10 };
                    Temperature temp { 12 };

                    printWeather(temp, hum);

                    return 0;
                }

Bu örnekle ilgili belirtmeye deðer üç þey var. Ýlk olarak, printWeather() hem Humidity hem de Temperature'ý eþit derecede 
kullandýðý için, bunun herhangi birine ait bir üye olmasý mantýklý deðildir. Üye olmayan bir fonksiyon daha iyi çalýþýr. 
Ýkinci olarak, printWeather() hem Humidity hem de Temperature'ýn arkadaþý olduðu için, her iki sýnýfýn nesnelerinden özel verilere
eriþebilir. Son olarak, örneðin en üstündeki aþaðýdaki satýra dikkat edin:

                class Humidity;

Bu, Humidity sýnýfý için bir ileri bildirimdir. Sýnýf ileri bildirimleri, fonksiyon ileri bildirimlerinin ayný rolünü oynar --
derleyiciye daha sonra tanýmlanacak bir tanýmlayýcý hakkýnda bilgi verirler. Ancak, fonksiyonlarýn aksine, sýnýflarýn dönüþ
türleri veya parametreleri yoktur, bu yüzden sýnýf ileri bildirimleri her zaman sadece class ClassName þeklindedir
(eðer bunlar sýnýf þablonlarý deðilse).

Bu satýr olmadan, derleyici bize Humidity'nin ne olduðunu bilmediðini söylerken Temperature içindeki arkadaþ bildirimini
ayrýþtýrýrdý.

Arkadaþlýk, veri gizleme ilkesini ihlal eder mi?
------------------------------------------------
Hayýr. Arkadaþlýk, arkadaþýn özel üyelerine eriþeceði beklentisiyle veri gizlemeyi yapan sýnýf tarafýndan verilir.
Bir arkadaþý, tüm ayný eriþim haklarýna sahip olan sýnýfýn bir uzantýsý olarak düþünün. Bu nedenle, eriþim beklenir, 
ihlal deðildir.

Doðru kullanýldýðýnda, arkadaþlýk, iþlevselliðin tasarým açýsýndan mantýklý olduðunda ayrýlmasýna izin vererek bir programý 
daha bakýmý kolay hale getirebilir (eriþim kontrolü nedenleriyle bir arada tutmak zorunda kalmak yerine). Veya bir üye fonksiyonu
yerine bir üye olmayan fonksiyon kullanmanýn daha mantýklý olduðu durumlarda.

Ancak, arkadaþlar bir sýnýfýn uygulamasýna doðrudan eriþim hakkýna sahip olduðu için, sýnýfýn uygulamasýndaki deðiþiklikler 
genellikle arkadaþlarda da deðiþiklik yapmayý gerektirir. Bir sýnýfýn çok sayýda arkadaþý varsa (veya bu arkadaþlarýn arkadaþlarý
varsa), bu bir dalga etkisi yaratabilir.

Bir arkadaþ fonksiyonu uygularken, mümkün olduðunda doðrudan eriþim yerine sýnýf arayüzünü kullanmayý tercih edin. Bu, arkadaþ
fonksiyonunuzu gelecekteki uygulama deðiþikliklerinden koruyacak ve daha sonra deðiþtirilmesi ve/veya yeniden test edilmesi
gereken kod miktarýný azaltacaktýr.

*** BEST -> Bir arkadaþ fonksiyonu, mümkün olduðunda doðrudan eriþim yerine sýnýf arayüzünü kullanmayý tercih etmelidir.

Arkadaþ fonksiyonlarý yerine Arkadaþ olmayan fonksiyonlarý tercih edin
----------------------------------------------------------------------
14.8 -- Veri gizlemenin faydalarý (kapsülleme) dersinde, üye olmayan fonksiyonlarý üye fonksiyonlara tercih etmemiz gerektiðini 
belirttik. Orada verilen ayný nedenlerle, arkadaþ fonksiyonlarý yerine üye olmayan fonksiyonlarý tercih etmeliyiz.

Örneðin, aþaðýdaki örnekte, Accumulator'un uygulamasý deðiþtirilirse (örneðin, m_value'yi yeniden adlandýrýrsak), print()
fonksiyonunun uygulamasý da deðiþtirilmelidir:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 }; // eðer bunu yeniden adlandýrýrsak

                public:
                    void add(int value) { m_value += value; } // bunu deðiþtirmemiz gerekecek

                    friend void print(const Accumulator& accumulator);
                };

                void print(const Accumulator& accumulator)
                {
                    std::cout << accumulator.m_value; // ve bunu da deðiþtirmemiz gerekecek
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplayýcýya 5 ekleyin

                    print(acc); // print() üye olmayan fonksiyonunu çaðýrýn

                    return 0;
                }

Daha iyi bir fikir þu þekildedir:

                #include <iostream>

                class Accumulator
                {
                private:
                    int m_value { 0 };

                public:
                    void add(int value) { m_value += value; }
                    int value() const { return m_value; } // bu makul eriþim fonksiyonunu ekledik
                };

                void print(const Accumulator& accumulator) // artýk Accumulator'un arkadaþý deðil
                {
                    std::cout << accumulator.value(); // doðrudan eriþim yerine eriþim fonksiyonunu kullan
                }

                int main()
                {
                    Accumulator acc{};
                    acc.add(5); // toplayýcýya 5 ekleyin

                    print(acc); // print() üye olmayan fonksiyonunu çaðýrýn

                    return 0;
                }

Bu örnekte, print() fonksiyonu m_value'nin deðerini almak için value() eriþim fonksiyonunu kullanýr, m_value'ye doðrudan eriþmez.
Þimdi Accumulator'un uygulamasý herhangi bir zaman deðiþtirilirse, print() fonksiyonunun güncellenmesi gerekmeyecektir.

*** BEST -> Mümkün ve makul olduðunda, bir fonksiyonu Arkadaþ olmayan bir fonksiyon olarak uygulamayý tercih edin.

Mevcut bir sýnýfýn genel arayüzüne yeni üyeler eklerken dikkatli olun, çünkü her fonksiyon (hatta basit olanlar bile) bir seviye 
karmaþýklýk ve karýþýklýk ekler. Accumulator örneðinde yukarýda, mevcut birikmiþ deðeri almak için bir eriþim fonksiyonuna sahip
olmanýn tamamen makul olduðunu söyleyebiliriz. Daha karmaþýk durumlarda, bir sýnýfýn arayüzüne birçok yeni eriþim fonksiyonu
eklemek yerine arkadaþlýðý kullanmak tercih edilebilir.

15.9 — Arkadaþ Sýnýflar ve Arkadaþ Üye Fonksiyonlar
---------------------------------------------------
Arkadaþ Sýnýflar
----------------
Bir arkadaþ sýnýf, baþka bir sýnýfýn özel ve korumalý üyelerine eriþebilen bir sýnýftýr.

Ýþte bir örnek:

                #include <iostream>

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                       : m_nValue { nValue }, m_dValue { dValue }
                    { }

                    // Display sýnýfýný Storage'ýn arkadaþý yap
                    friend class Display;
                };

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                         : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    // Çünkü Display, Storage'ýn arkadaþýdýr, Display üyeleri Storage'ýn özel üyelerine eriþebilir
                    void displayStorage(const Storage& storage)
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // önce double'ý göster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }

                    void setDisplayIntFirst(bool b)
                    {
                         m_displayIntFirst = b;
                    }
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };

                    display.displayStorage(storage);

                    display.setDisplayIntFirst(true);
                    display.displayStorage(storage);

                    return 0;
                }
Çünkü Display sýnýfý, Storage'ýn bir arkadaþýdýr, Display üyeleri eriþim haklarýna sahip olduklarý herhangi bir Storage nesnesinin
özel üyelerine eriþebilir.

                Bu program aþaðýdaki sonucu üretir:

                6.7 5
                5 6.7
Arkadaþ sýnýflar hakkýnda birkaç ek not
---------------------------------------
Ýlk olarak, Display, Storage'ýn bir arkadaþý olsa bile, Display'in Storage nesnelerinin *this iþaretçisine eriþimi yoktur 
(çünkü *this aslýnda bir fonksiyon parametresidir).

Ýkinci olarak, arkadaþlýk karþýlýklý deðildir. Sadece Display, Storage'ýn bir arkadaþýdýr diye Storage'ýn da Display'in 
bir arkadaþý olduðu anlamýna gelmez. Ýki sýnýfýn birbirinin arkadaþý olmasýný istiyorsanýz, her ikisi de diðerini bir arkadaþ
olarak bildirmelidir.

Yazarýn Notu -> Eðer bu sizi canevinizden vurduysa özür dilerim.

Sýnýf arkadaþlýðý da transitif deðildir. Eðer A sýnýfý B'nin bir arkadaþýysa ve B, C'nin bir arkadaþýysa, bu A'nýn C'nin
bir arkadaþý olduðu anlamýna gelmez.

Arkadaþ Üye Fonksiyonlar
------------------------
Bir sýnýfýn tamamýný bir arkadaþ yapmak yerine, tek bir üye fonksiyonu bir arkadaþ yapabilirsiniz. Bu, bir dýþ üye fonksiyonu 
bir arkadaþ yapmakla benzer þekilde yapýlýr, tek fark üye fonksiyonun adýnýn kullanýlmasýdýr.

Ancak, aslýnda bu beklenenden biraz daha zor olabilir. Önceki örneði Display::displayStorage'ý bir arkadaþ üye fonksiyon yapacak
þekilde dönüþtürelim. Böyle bir þey deneyebilirsiniz:

                #include <iostream>

                class Display; // Display sýnýfý için ileri bildirim

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage üye fonksiyonunu Storage sýnýfýnýn bir arkadaþý yap
                    friend void Display::displayStorage(const Storage& storage); // hata: Storage, Display sýnýfýnýn tam 
                                                                                 // tanýmýný görmedi
                };

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage)
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // önce double'ý göster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }


Ancak, bu iþe yaramayabilir. Bir üye fonksiyonunu arkadaþ yapabilmek için, derleyicinin arkadaþ üye fonksiyonunun sýnýfýnýn 
tam tanýmýný görmüþ olmasý gerekir (sadece ileri bildirim deðil). Storage sýnýfý henüz Display sýnýfýnýn tam tanýmýný görmediði
için, üye fonksiyonunu arkadaþ yapmaya çalýþtýðýmýz noktada derleyici hata verecektir.

Neyse ki, bu, Display sýnýfýnýn tanýmýný Storage sýnýfýnýn tanýmýndan önceye taþýyarak kolayca çözülür
(ayný dosyada veya Display tanýmýný bir baþlýk dosyasýna taþýyarak ve Storage tanýmlanmadan önce #include ederek).

                #include <iostream>

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage) // derleme hatasý: derleyici bir Storage'ýn ne olduðunu bilmiyor
                    {
                        if (m_displayIntFirst)
                            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                        else // önce double'ý göster
                            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                    }
                };

                class Storage
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage üye fonksiyonunu Storage sýnýfýnýn bir arkadaþý yap
                    friend void Display::displayStorage(const Storage& storage); // þimdi tamam
                };

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }
Ancak, þimdi baþka bir sorunumuz var. Üye fonksiyonu Display::displayStorage() Storage'ý bir referans parametre olarak kullanýyor
ve biz sadece Storage tanýmýný Display tanýmýnýn altýna taþýdýk, derleyici bir Storage'ýn ne olduðunu bilmediðinden þikayet edecek
Bu sorunu, taným sýrasýný yeniden düzenleyerek çözemeyiz, çünkü o zaman önceki düzeltmemizi geri alýrýz.

Neyse ki, bu da birkaç basit adýmla düzeltilebilir. Ýlk olarak, Storage sýnýfýný bir ileri bildirim olarak ekleyebiliriz,
böylece derleyici, sýnýfýn tam tanýmýný görmeden önce bir Storage referansýyla iyi olacaktýr.

Ýkinci olarak, Display::displayStorage() tanýmýný sýnýfýn dýþýna, Storage sýnýfýnýn tam tanýmýndan sonraya taþýyabiliriz.

Ýþte bu neye benziyor:

                #include <iostream>

                class Storage; // Storage sýnýfý için ileri bildirim

                class Display
                {
                private:
                    bool m_displayIntFirst {};

                public:
                    Display(bool displayIntFirst)
                        : m_displayIntFirst { displayIntFirst }
                    {
                    }

                    void displayStorage(const Storage& storage); // burada referans için Storage ileri bildirimi gereklidir
                };

                class Storage // Storage sýnýfýnýn tam tanýmý
                {
                private:
                    int m_nValue {};
                    double m_dValue {};
                public:
                    Storage(int nValue, double dValue)
                        : m_nValue { nValue }, m_dValue { dValue }
                    {
                    }

                    // Display::displayStorage üye fonksiyonunu Storage sýnýfýnýn bir arkadaþý yap
                    // Sýnýf Display'ýn tam tanýmýný görmeyi gerektirir (çünkü displayStorage bir üye)
                    friend void Display::displayStorage(const Storage& storage);
                };

                // Þimdi Display::displayStorage'ý tanýmlayabiliriz
                // Storage üyelerine eriþtiðimiz için Storage sýnýfýnýn tam tanýmýný görmeyi gerektirir
                void Display::displayStorage(const Storage& storage)
                {
                    if (m_displayIntFirst)
                        std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                    else // önce double'ý göster
                        std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
                }

                int main()
                {
                    Storage storage { 5, 6.7 };
                    Display display { false };
                    display.displayStorage(storage);

                    return 0;
                }
Þimdi her þey düzgün bir þekilde derlenecek: Storage sýnýfýnýn ileri bildirimi, Display sýnýfý içindeki Display::displayStorage()
bildirimini karþýlamak için yeterlidir. Display'ýn tam tanýmý, Display::displayStorage()'ý Storage'ýn bir arkadaþý olarak
bildirmeyi karþýlar. Ve Storage sýnýfýnýn tam tanýmý, üye fonksiyonu Display::displayStorage()'ýn tanýmýný karþýlar.

Eðer bu biraz kafa karýþtýrýcýysa, programýn üzerindeki yorumlara bakýn. Anahtar noktalar, bir sýnýf ileri bildiriminin sýnýfa
olan referanslarý karþýladýðýdýr. Ancak, bir sýnýfýn üyelerine eriþmek, derleyicinin tam sýnýf tanýmýný görmüþ olmasýný gerektirir.

Eðer bu biraz can sýkýcý gibi görünüyorsa -- öyledir. Neyse ki, bu dans sadece her þeyi tek bir dosyada yapmaya çalýþtýðýmýz
için gereklidir. Daha iyi bir çözüm, her sýnýf tanýmýný ayrý bir baþlýk dosyasýna koymak ve üye fonksiyon tanýmlarýný karþýlýk 
gelen .cpp dosyalarýna koymaktýr. Bu þekilde, tüm sýnýf tanýmlarý .cpp dosyalarýnda mevcut olur ve sýnýflarýn veya fonksiyonlarýn
yeniden düzenlenmesi gerekmez!

15.10 — Ref Niteliklendiriciler ( Qualifiers )
----------------------------------------------
Yazarýn Notu

Bu bir seçmeli derstir. Materyalle tanýþmak için hafif bir okuma yapmanýzý öneririz, ancak gelecek derslere devam etmek için
kapsamlý bir anlama gerekli deðildir.

14.7 -- Üye Fonksiyonlar Veri Üyelerine Referans Döndürme dersinde, veri üyelerine referans döndüren eriþim fonksiyonlarýnýn
çaðrýlmasýnýn, dolaylý nesnenin bir rvalue olduðunda tehlikeli olabileceðini tartýþtýk. Ýþte hýzlý bir özet:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }
                    const auto& getName() const { return m_name; } //  getter const referans döndürür
                };

                // createEmployee() bir Employee'yi deðer olarak döndürür (bu, döndürülen deðerin bir rvalue olduðu anlamýna gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    // Durum 1: tamam: rvalue sýnýf nesnesinin üyesine döndürülen referansý ayný ifade içinde kullan
                    std::cout << createEmployee("Frank").getName() << '\n';

                    // Durum 2: kötü: rvalue sýnýf nesnesinin üyesine döndürülen referansý daha sonra kullanmak üzere kaydet
                    const std::string& ref { createEmployee("Garbo").getName() }; // createEmployee()'nin döndürdüðü deðer yok 
                                                                                  // edildiðinde referans dangling olur
                    std::cout << ref << '\n'; // tanýmsýz davranýþ

                    return 0;
                }

Durum 2'de, createEmployee("Garbo")'dan döndürülen rvalue nesne, ref'i baþlatýldýktan sonra yok edilir, bu da ref'in yeni yok
edilen bir veri üyesine referans vermesine neden olur. ref'in sonraki kullanýmý tanýmsýz davranýþ sergiler.

Bu, biraz bir çýkmaz sunar.

Eðer getName() fonksiyonumuz deðer döndürürse, bu, dolaylý nesnemiz bir rvalue olduðunda güvenlidir, ancak dolaylý nesnemiz bir
lvalue olduðunda (ki bu en yaygýn durumdur) pahalý ve gereksiz bir kopya yapar.

Eðer getName() fonksiyonumuz const referans döndürürse, bu verimlidir (std::string'in hiçbir kopyasý yapýlmaz), ancak dolaylý
nesne bir rvalue olduðunda yanlýþ kullanýlabilir (bu, tanýmsýz davranýþa neden olur).

Üye fonksiyonlar genellikle lvalue dolaylý nesneler üzerinde çaðrýldýðýndan, geleneksel seçenek const referans döndürmektir ve 
sadece dolaylý nesne bir rvalue olduðunda döndürülen referansýn yanlýþ kullanýlmasýndan kaçýnmaktýr.

Ref Niteliklendiriciler ( Qualifiers )
--------------------------------------
Yukarýda gösterilen zorluðun kökü, yalnýzca bir fonksiyonun iki farklý durumu hizmet etmesini istememizdir 
(dolaylý nesnemiz bir lvalue olduðunda bir durum ve dolaylý nesnemiz bir rvalue olduðunda bir durum). 
Bir durum için en uygun olan diðer durum için ideal deðildir.

Bu tür sorunlara yardýmcý olmak için, C++11, bir üye fonksiyonun bir lvalue veya rvalue dolaylý nesne üzerinde çaðrýlýp 
çaðrýlmadýðýna dayalý olarak bir üye fonksiyonu aþýrý yüklememize izin veren az bilinen bir özellik olan bir
ref-niteliklendirici tanýttý. Bu özelliði kullanarak, getName() için iki versiyon oluþturabiliriz -- dolaylý nesnemiz 
bir lvalue olduðunda bir durum ve dolaylý nesnemiz bir rvalue olduðunda bir durum için biri.

Öncelikle, ref-qualify olmayan getName() versiyonumuzla baþlayalým:


                auto& getName() const { return m_name; } // hem lvalue hem de rvalue implicit nesnelerle çaðrýlabilir

Bu fonksiyonu ref-qualify etmek için, yalnýzca lvalue implicit nesneleri eþleþtirecek aþýrý yüklemeye bir & nitelik ekleriz 
ve yalnýzca rvalue implicit nesneleri eþleþtirecek aþýrý yüklemeye bir && nitelik ekleriz:

                //  & nitelik, yalnýzca lvalue implicit nesneleri eþleþtiren fonksiyonu aþýrý yükler, referans olarak döndürür
                const auto& getName() const &  { return m_name; } 

                // && nitelik, yalnýzca rvalue implicit nesneleri eþleþtiren fonksiyonu aþýrý yükler, deðer olarak döndürür
                auto        getName() const && { return m_name; } 

Bu fonksiyonlar farklý aþýrý yüklemeler olduðu için, farklý dönüþ türlerine sahip olabilirler! Lvalue-qualified aþýrý yüklemimiz
const referans olarak döndürürken, rvalue-qualified aþýrý yüklemimiz deðer olarak döndürür.

Aþaðýda bunun tam bir örneði verilmiþtir:

                #include <iostream>
                #include <string>
                #include <string_view>

                class Employee
                {
                    std::string m_name{};

                public:
                    void setName(std::string_view name) { m_name = name; }

                    //  & nitelik, yalnýzca lvalue implicit nesneleri eþleþtiren fonksiyonu aþýrý yükler
                    const auto& getName() const &  { return m_name; } 
                    // && nitelik, yalnýzca rvalue implicit nesneleri eþleþtiren fonksiyonu aþýrý yükler
                    auto        getName() const && { return m_name; } 
                };

                // createEmployee() bir Employee'yi deðer olarak döndürür (bu, döndürülen deðerin bir rvalue olduðu anlamýna gelir)
                Employee createEmployee(std::string_view name)
                {
                    Employee e;
                    e.setName(name);
                    return e;
                }

                int main()
                {
                    Employee joe{};
                    joe.setName("Joe");
                    // Joe bir lvalue'dir, bu yüzden bu std::string& getName() & 'yi çaðýrýr (bir referans döndürür)
                    std::cout << joe.getName() << '\n'; 

                    // Frank bir rvalue'dir, bu yüzden bu std::string getName() && 'yi çaðýrýr (bir kopya yapar)
                    std::cout << createEmployee("Frank").getName() << '\n'; 

                    return 0;
                }

Bu, implicit nesnemiz bir lvalue olduðunda performanslý þeyi yapmamýza ve implicit nesnemiz bir rvalue olduðunda güvenli þeyi
yapmamýza olanak saðlar.

Ref-qualified üye fonksiyonlar hakkýnda bazý notlar
---------------------------------------------------
Öncelikle, ref-qualified olmayan aþýrý yüklemeler ve ref-qualified aþýrý yüklemeler bir arada bulunamaz. 
Birini veya diðerini kullanýn.

Ýkincisi, yalnýzca bir lvalue-qualified aþýrý yüklem saðlanýrsa (yani rvalue-qualified versiyon tanýmlanmamýþsa),
bir rvalue implicit nesne ile fonksiyonun herhangi bir çaðrýsý bir derleme hatasý sonucunu verir. Bu, bir fonksiyonun rvalue
implicit nesnelerle kullanýlmasýný tamamen önlemenin kullanýþlý bir yolunu saðlar.

Peki neden ref-qualifiers kullanmayý önermiyoruz?
-------------------------------------------------
Ref-qualifiers güzel olsa da, bu þekilde kullanmanýn bazý dezavantajlarý vardýr.

*- Bir referans döndüren her getter'a rvalue aþýrý yüklemeler eklemek, sýnýfa karýþýklýk ekler, bu da çok yaygýn olmayan ve iyi 
   alýþkanlýklarla kolayca kaçýnýlabilen bir durumu hafifletir.

*- Bir rvalue aþýrý yüklemesini deðer olarak döndürmek, bir referansý güvenle kullanabileceðimiz durumlarda bile bir kopya
   (veya taþýma) maliyetini ödememiz gerektiði anlamýna gelir (örneðin, dersin baþýndaki örnekteki durum 1).

Ayrýca:

Çoðu C++ geliþtiricisi bu özelliðin farkýnda deðildir (bu, kullanýmdaki hatalara veya verimsizliklere yol açabilir).
Standart kütüphane genellikle bu özelliði kullanmaz.
Yukarýdaki tüm nedenlere dayanarak, ref-qualifiers kullanmayý en iyi uygulama olarak önermiyoruz. Bunun yerine,
her zaman bir eriþim fonksiyonunun sonucunu hemen kullanmayý ve döndürülen referanslarý daha sonra kullanmak için kaydetmemeyi
öneririz.

15.x — Bölüm 15 Özeti ve Sýnav
------------------------------
Bölüm Ýncelemesi

Her (statik olmayan) üye fonksiyonun içinde, this anahtar kelimesi, geçerli örtük nesnenin adresini tutan bir const iþaretçidir.
Fonksiyonlarýn *this'i referans olarak döndürmesine izin verebiliriz, böylece yöntem zincirlemesi saðlanýr, burada birkaç üye 
fonksiyon tek bir ifadede ayný nesne üzerinde çaðrýlabilir.

Sýnýf tanýmlarýnýzý, sýnýf ile ayný adý taþýyan bir header dosyasýna koymayý tercih edin. Önemsiz üye fonksiyonlar 
(örneðin eriþim fonksiyonlarý, boþ gövdeleri olan yapýlandýrýcýlar vb.) sýnýf tanýmýnýn içinde tanýmlanabilir.

Önemsiz olmayan üye fonksiyonlarý, sýnýf ile ayný adý taþýyan bir kaynak dosyasýnda tanýmlamayý tercih edin.

Bir sýnýf türü içinde tanýmlanan bir tür, iç içe tür (veya üye tür) olarak adlandýrýlýr. Tür takma adlarý da iç içe olabilir.

Bir sýnýf þablonu tanýmýnýn içinde tanýmlanan üye fonksiyonlar, sýnýf þablonunun kendisinin þablon parametrelerini kullanabilir.
Sýnýf þablonu tanýmýnýn dýþýnda tanýmlanan üye fonksiyonlar, bir þablon parametre bildirimini yeniden saðlamalý ve sýnýf þablonu
tanýmýnýn hemen altýnda (ayný dosyada) tanýmlanmalýdýr.

Statik üye deðiþkenler, sýnýfýn tüm nesneleri tarafýndan paylaþýlan statik süreli üyelerdir. Statik üyeler, sýnýfýn hiçbir nesnesi
oluþturulmamýþ olsa bile var olur. Onlara eriþmek için sýnýf adýný, kapsam çözümleme operatörünü ve üye adýný kullanmayý tercih
edin.

Statik üyeleri inline yapmak, onlarýn sýnýf tanýmýnýn içinde baþlatýlmasýna olanak saðlar.

Statik üye fonksiyonlar, hiçbir nesne olmadan çaðrýlabilen üye fonksiyonlardýr. Bir *this iþaretçileri yoktur ve statik olmayan
veri üyelerine eriþemezler.

Bir sýnýfýn gövdesinin içinde, bir arkadaþ bildirimi (friend anahtar kelimesi kullanýlarak) derleyiciye baþka bir sýnýfýn veya 
fonksiyonun artýk bir arkadaþ olduðunu söylemek için kullanýlabilir. Bir arkadaþ, baþka bir sýnýfýn özel ve korumalý üyelerine
tam eriþim hakký verilmiþ bir sýnýf veya fonksiyon (üye veya dýþ üye) anlamýna gelir. Bir arkadaþ fonksiyon, bir sýnýfýn özel
ve korumalý üyelerine, sanki o sýnýfýn bir üyesiymiþ gibi eriþebilen bir fonksiyon (üye veya dýþ üye) anlamýna gelir. 
Bir arkadaþ sýnýf, baþka bir sýnýfýn özel ve korumalý üyelerine eriþebilen bir sýnýftýr.
*/