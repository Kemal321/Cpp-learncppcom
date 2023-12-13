#include <iostream>

int main()
{
    return 0;
}
/*
                                                10.10 — Fonksiyon Aþýrý Yüklemeye Giriþ
                                                ---------------------------------------

Örneklerle inceleyerek baþlayalým:

                            int add(int x, int y)
                            {
                                return x + y;
                            }

Bu basit fonksiyon, iki tamsayýyý ekler ve bir tamsayý sonuç döndürür. Ancak, iki ondalýklý sayýyý ekleyebilen bir fonksiyon da istesek, bu add() 
fonksiyonu uygun deðildir, çünkü herhangi bir ondalýklý nokta parametresi, ondalýklý sayý argümanlarýnýn kesirli deðerlerini kaybetmesine neden
olacak þekilde tamsayýlara dönüþtürülür.

Bu sorunu aþmanýn bir yolu, birkaç farklý isme sahip çok sayýda fonksiyon tanýmlamaktýr:

                            int addInteger(int x, int y)
                            {
                                return x + y;
                            }

                            double addDouble(double x, double y)
                            {
                                return x + y;
                            }

Ancak, en iyi sonuç için, farklý türlerde parametrelere sahip benzer fonksiyonlar için tutarlý bir fonksiyon adlandýrma standardý belirlemeniz, 
bu fonksiyonlarýn isimlerini hatýrlamanýz ve gerçekten doðru olaný çaðýrmanýz gerekmektedir.

Ve sonra 2 yerine 3 tamsayý ekleyen benzer bir fonksiyona ihtiyaç duyduðumuzda ne olur? Her fonksiyon için benzersiz isimleri yönetmek hýzlý bir
þekilde yük oluþturabilir.

Fonksiyon aþýrýyüklemeye giriþ
------------------------------

Neyse ki, C++ bu tür durumlarý ele almak için zarif bir çözüme sahiptir. Fonksiyon aþýrý yükleme, ayný adý taþýyan birden fazla fonksiyon oluþturmamýza
izin verir, yeter ki her biri ayný adý taþýyan fonksiyon farklý parametre tiplerine sahip olsun (veya fonksiyonlar baþka þekilde ayýrt edilebilsin).
Ayný adý paylaþan her fonksiyon (ayný kapsamda) aþýrý yüklenmiþ bir fonksiyon olarak adlandýrýlýr (bazen kýsaltma olarak bir aþýrý yükleme olarak 
adlandýrýlýr).

add() fonksiyonumuzu aþýrý yüklemek için, basitçe double parametreleri alan baþka bir add() fonksiyonu bildirebiliriz:

                            int add(int x, int y) // integer version
                            {
                                return x + y;
                            }

                            double add(double x, double y) // floating point version
                            {
                                return x + y;
                            }

                            int main()
                            {
                                return 0;
                            }

Artýk ayný kapsamda add()'ýn iki sürümüne sahibiz:


Yukarýdaki program derlenecektir. Bu fonksiyonlardan bir isim çakýþmasý bekleseniz de, burada durum böyle deðildir. Bu fonksiyonlarýn parametre tipleri
farklý olduðu için, derleyici bu fonksiyonlarý ayýrt edebilir ve bunlarý yalnýzca bir adý paylaþan ayrý fonksiyonlar olarak ele alacaktýr.

Anahtar Bilgi

Fonksiyonlar, her biri derleyici tarafýndan ayýrt edilebiliyorsa aþýrý yüklenebilir. Aþýrý yüklenmiþ bir fonksiyon ayýrt edilemiyorsa, derleme hatasý 
alýnýr.


Aþýrý Yükleme Çözümü Giriþ
--------------------------

Ayrýca, bir aþýrý yüklenmiþ fonksiyona yapýlan bir çaðrýda, derleyici fonksiyon çaðrýsýný, kullanýlan argümanlara dayanarak uygun aþýrý yükleme ile 
eþleþtirmeye çalýþacaktýr. Buna aþýrý yükleme çözümü denir. Bunu gösteren basit bir örnek:

                            #include <iostream>

                            int add(int x, int y)
                            {
                                return x + y;
                            }

                            double add(double x, double y)
                            {
                                return x + y;
                            }

                            int main()
                            {
                                std::cout << add(1, 2); // calls add(int, int)
                                std::cout << '\n';
                                std::cout << add(1.2, 3.4); // calls add(double, double)

                                return 0;
                            }
Yukarýdaki program sonucu derler ve üretir:
                            3
                            4.6

add(1, 2) çaðrýsýnda tamsayý argümanlarý saðladýðýmýzda, derleyici add(int, int) fonksiyonunu çaðýrmaya çalýþtýðýmýzý belirleyecektir. Ve 
add(1.2, 3.4) çaðrýsýnda ondalýk sayý argümanlarý saðladýðýmýzda, derleyici add(double, double) fonksiyonunu çaðýrmaya çalýþtýðýmýzý belirleyecektir.

Derlenmesini saðla
------------------
Aþýrý yüklenmiþ fonksiyonlarý kullanan bir programýn derlenmesi için iki þeyin doðru olmasý gerekir:

1 - Her aþýrý yüklenmiþ fonksiyonun diðerlerinden ayýrt edilebilmesi gerekir.
2 - Her aþýrý yüklenmiþ fonksiyona yapýlan her çaðrýnýn bir aþýrý yüklenmiþ fonksiyona çözümlenmesi gerekir.

Eðer bir aþýrý yüklenmiþ fonksiyon ayýrt edilemiyorsa veya bir aþýrý yüklenmiþ fonksiyona yapýlan bir fonksiyon çaðrýsý bir aþýrý yüklenmiþ fonksiyona 
çözümlenemiyorsa, derleme hatasý oluþur.

Sonraki derste, aþýrý yüklenmiþ fonksiyonlarýn birbirinden nasýl ayrýlabileceðini keþfedeceðiz. Ardýndan, bir sonraki derste, derleyicinin fonksiyon 
çaðrýlarýný aþýrý yüklenmiþ fonksiyonlara nasýl çözümleyeceðini keþfedeceðiz.

Sonuç
-----
Fonksiyon aþýrý yükleme, programýnýzýn karmaþýklýðýný azaltmak için ihtiyacýnýz olan fonksiyon adý sayýsýný azaltarak harika bir yol saðlar. 
Özgürce kullanýlabilir ve kullanýlmalýdýr.

*** BEST -> Programýnýzý basitleþtirmek için fonksiyon aþýrý yüklemeyi kullanýn.

10.11 — Fonksiyon Aþýrý Yükleme Ayýrt Edilmesi
----------------------------------------------

Doðru þekilde ayýrt edilmemiþ aþýrý yüklenmiþ fonksiyonlar, derleyicinin derleme hatasý vermesine neden olacaktýr.

Aþýrý yüklenmiþ fonksiyonlar nasýl ayýrt edilir
-----------------------------------------------

Fonksiyon Özelliði | Ayýrt Edilmesinde Kullaným | Notlar                                                                                            |
----------------------------------------------------------------------------------------------------------------------------------------------------|
Parametre Sayýsý   |         Evet               |                                                                                                   |
Parametre Türü	   |         Evet	            | typedef'leri, tür takma adlarýný ve deðer parametrelerindeki const niteliðini hariç tutar         |
Dönüþ Türü	       |         Hayýr              | Elipsleri içerir.                                                                                 |
----------------------------------------------------------------------------------------------------------------------------------------------------

Unutmayýn ki bir fonksiyonun dönüþ türü, aþýrý yüklenmiþ fonksiyonlarý ayýrt etmek için kullanýlmaz.

Parametre sayýsýna dayalý aþýrý yükleme
--------------------------------------- 
Her aþýrý yüklenmiþ fonksiyon, farklý bir parametre sayýsýna sahip olduðu sürece ayýrt edilir. Örneðin:

                    int add(int x, int y)
                    {
                        return x + y;
                    }

                    int add(int x, int y, int z)
                    {
                        return x + y + z;
                    }
Derleyici, iki tamsayý parametreli bir fonksiyon çaðrýsýnýn add(int, int)'e gitmesi gerektiðini ve üç tamsayý 
parametreli bir fonksiyon çaðrýsýnýn add(int, int, int)'e gitmesi gerektiðini kolayca anlayabilir.

Parametre türüne dayalý aþýrý yükleme
-------------------------------------
Bir fonksiyon, her bir aþýrý yüklenmiþ fonksiyonun parametre türü listesinin farklý olduðu sürece ayýrt edilebilir. Örneðin, aþaðýdaki tüm 
aþýrý yüklemeler farklýdýr:
                    int add(int x, int y); // integer version
                    double add(double x, double y); // floating point version
                    double add(int x, double y); // mixed version
                    double add(double x, int y); // mixed version

Çünkü tür takma adlarý (veya typedef'ler) ayýrt edici türler deðildir, tür takma adlarý kullanýlarak yapýlan aþýrý yüklemeler, tür takma adý
kullanýlan türden ayýrt edilmez. Örneðin, aþaðýdaki tüm aþýrý yüklemeler ayýrt edilmez (ve derleme hatasýna neden olur):

                    typedef int Height; // typedef
                    using Age = int; // type alias

                    void print(int value);
                    void print(Age value); // print(int) ile ayýrt edilmez
                    void print(Height value); // print(int) ile ayýrt edilmez

Deðer ile geçilen parametreler için const niteliði de dikkate alýnmaz. Bu nedenle, aþaðýdaki fonksiyonlar ayýrt edildiði kabul edilmez:

                    void print(int);
                    void print(const int); // print(int) ile ayýrt edilmez

Bir fonksiyonun dönüþ türü, aþýrý yüklenmiþ fonksiyonlarý ayýrt etme konusunda dikkate alýnmaz.

Aþaðýdaki gibi bir durumu düþünün: Rastgele bir sayý döndüren bir fonksiyon yazmak istiyorsunuz, ancak bir tane int döndüren bir versiyona ve bir tane
de double döndüren bir versiyona ihtiyacýnýz var. Þöyle yapmaya yönelebilirsiniz:
                    int getRandomValue();
                    double getRandomValue();
Visual Studio 2019'da bu, aþaðýdaki derleme hatasýna neden olur:
                    error C2556: 'double getRandomValue(void)': overloaded function differs only by return type from 'int getRandomValue(void)'
Bu mantýklý. Eðer derleyici olsaydýnýz ve þu ifadeyi görseydiniz:
                    getRandomValue();
Ýki aþýrý yüklenmiþ fonksiyonun hangisini çaðýrýrdýnýz? Bu belirsizdir.


Yaný sýra...
Bu, bir fonksiyon çaðrýsýnýn davranýþýnýn, karmaþýk ifadelerin geri kalanýndan baðýmsýz olarak belirlenebilmesini saðlamak için bilinçli bir seçimdi, 
bu da karmaþýk ifadelerin anlaþýlmasýný çok daha basitleþtirir. Baþka bir deyiþle, bir fonksiyon çaðrýsýnýn hangi sürümünün yalnýzca fonksiyon 
çaðrýsýndaki argümanlara dayanarak belirlenebileceðini her zaman söyleyebiliriz. Eðer dönüþ deðerleri ayrým için kullanýlsaydý, o zaman bir fonksiyonun
hangi aþýrý yüklemesinin çaðrýldýðýný anlamanýn kolay bir sözdizimi yolu olmazdý - ayrýca dönüþ deðerinin nasýl kullanýldýðýný anlamamýz gerekecekti, 
bu da daha fazla analiz gerektirir.

Bu sorunu çözmenin en iyi yolu iþlevlere farklý adlar vermektir:

                    int getRandomInt();
                    double getRandomDouble();

Tür imzasý

Bir fonksiyonun tür imzasý (genellikle bir imza olarak adlandýrýlýr), fonksiyonun ayrýlmak için kullanýlan fonksiyon baþlýðýnýn bölümlerini tanýmlar.
C++'da bu, fonksiyon adýný, parametre sayýsýný, parametre türünü ve fonksiyon düzeyindeki nitelikleri içerir. Özellikle dönüþ türünü içermez.


Ýsim karýþtýrma - Name Mangling
-------------------------------
Yaný sýra 
Derleyici bir fonksiyonu derlediðinde, fonksiyonun derlenmiþ adýný çeþitli kriterlere dayanarak (örneðin, parametre sayýsý ve türü gibi) deðiþtirir
("mangle" eder), böylece baðlayýcý benzersiz adlarla çalýþabilir.

Örneðin, int fcn() prototipi olan bir fonksiyon adý __fcn_v'ye derlenmiþ olabilir, oysa int fcn(int) fonksiyonu __fcn_i adýna derlenmiþ olabilir.
Bu nedenle kaynak kodunda iki aþýrý yüklenmiþ fonksiyon ayný adý paylaþsa da, derlenmiþ kodda adlar aslýnda benzersizdir.

Adlarýn nasýl mangle edilmesi gerektiði konusunda standartlaþma olmadýðý için, farklý derleyiciler farklý mangled adlar üretecektir.
*/

/*
                                            10.12 — Fonksiyon aþýrý yükü çözünürlüðü ve belirsiz eþleþmeler
                                            -----------------------------------------------------------

Eðer bir aþýrý yüklenmiþ fonksiyon, ayný isme sahip diðer aþýrý yüklemelerden doðru þekilde ayýrt edilemiyorsa, derleyici bir derleme hatasý verir.

Ancak, ayýrt edilmiþ aþýrý yüklenmiþ fonksiyonlara sahip olmak resmin yalnýzca yarýsýdýr. Herhangi bir fonksiyon çaðrýsý yapýldýðýnda, derleyici ayný 
zamanda eþleþen bir fonksiyon bildirimini bulabilmesini saðlamalýdýr.

Aþýrý yüklenmiþ olmayan fonksiyonlarda (benzersiz adlara sahip fonksiyonlar), bir fonksiyon çaðrýsýný eþleþtirebilecek potansiyel bir fonksiyon vardýr.
Bu fonksiyon ya eþleþir (veya tür dönüþümleri uygulandýktan sonra eþleþtirilebilir), ya da eþleþmez (ve bir derleme hatasý ortaya çýkar). 
Aþýrý yüklenmiþ fonksiyonlarda, bir fonksiyon çaðrýsýna potansiyel olarak eþleþebilecek birçok fonksiyon olabilir. Çünkü bir fonksiyon çaðrýsý 
yalnýzca bunlardan birine çözümlenebilir, derleyici en iyi eþleþen aþýrý yüklenmiþ fonksiyonu belirlemelidir. Fonksiyon çaðrýlarýný belirli bir 
aþýrý yüklenmiþ fonksiyona eþleþtirme sürecine "aþýrý yükleme çözümleme" denir.

Fonksiyon argümanlarýnýn türü ve fonksiyon parametrelerinin türü tam olarak eþleþtiðinde, bu (genellikle) basittir:

                    #include <iostream>

                    void print(int x)
                    {
                         std::cout << x << '\n';
                    }

                    void print(double d)
                    {
                         std::cout << d << '\n';
                    }

                    int main()
                    {
                         print(5); // 5 bir int olduðu için bu, print(int) ile eþleþir
                         print(6.7); // 6.7 bir double olduðu için bu, print(double) ile eþleþir

                         return 0;
                    }

Ancak, aþýrý yüklenmiþ fonksiyonlardan hiçbirinin parametre türleriyle tam olarak eþleþmeyen durumlarda ne olur? Örneðin:

                #include <iostream>

                void print(int x)
                {
                     std::cout << x << '\n';
                }

                void print(double d)
                {
                     std::cout << d << '\n';
                }

                int main()
                {
                     print('a'); // char, int veya double ile eþleþmez
                     print(5L); // long, int veya double ile eþleþmez

                     return 0;
                }

"Sadece burada tam bir eþleþme olmamasý, bir eþleþmenin bulunamayacaðý anlamýna gelmez – sonuçta, bir char veya long tipi, 
bir int veya double'a otomatik olarak tür dönüþtürülebilir. Ancak her durumda en iyi dönüþüm hangisi?"

Aþýrý yüklenmiþ (overloaded) fonksiyon çaðrýldýðýnda, derleyici aþýrý yüklenmiþ fonksiyonlarýn hangisinin (varsa) en iyi eþleþme
olduðunu belirlemek için bir dizi kuralý takip eder.

Her adýmda, derleyici, fonksiyon çaðrýsýndaki argüman(lar)a çeþitli tür dönüþümlerini uygular. Her uygulanan dönüþüm için, derleyici aþýrý 
yüklenmiþ fonksiyonlardan herhangi birinin þimdi bir eþleþip eþleþmediðini kontrol eder. Farklý tür dönüþümleri uygulandýktan ve eþleþme 
kontrol edildikten sonra adým tamamlanýr. Sonuç, üç olasý durumdan biri olacaktýr:

1. Eþleþen fonksiyon bulunamadý. Derleyici, sýradaki adýma geçer.
2. Tek bir eþleþen fonksiyon bulundu. Bu fonksiyon en iyi eþleþme olarak kabul edilir. Eþleþme süreci tamamlanýr ve sonraki adýmlar gerçekleþtirilmez.
3. Birden fazla eþleþen fonksiyon bulundu. Derleyici, belirsiz bir eþleþme derleme hatasý verecektir. Bu durumu biraz daha detaylý bir þekilde
   tartýþacaðýz.

Eðer derleyici, tüm dizi boyunca bir eþleþme bulamadan sona erirse, fonksiyon çaðrýsý için eþleþen aþýrý yüklenmiþ fonksiyon bulunamadýðýna dair 
bir derleme hatasý üretecektir.

Argüman eþleme sýrasý
---------------------

Adým 1) Derleyici tam bir eþleþme bulmaya çalýþýr. Bu iki aþamada gerçekleþir. Ýlk olarak, derleyici, fonksiyon çaðrýsýndaki argümanlarýn türünün, 
aþýrý yüklenmiþ fonksiyonlardaki parametrelerin türüyle tam olarak eþleþtiði bir aþýrý yüklenmiþ fonksiyon olup olmadýðýný kontrol eder. Örneðin:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print(0);   // print(int) ile tam bir eþleþme
                        print(3.4); // print(double) ile tam bir eþleþme

                        return 0;
                    }

Çünkü fonksiyon çaðrýsýndaki 0 bir int olduðundan, derleyici bir print(int) aþýrý yüklemesi tanýmlanmýþ mý diye bakacaktýr. Var ise, derleyici 
print(int) fonksiyonunu tam bir eþleþme olarak belirler.

Ýkinci olarak, derleyici, fonksiyon çaðrýsýndaki argümanlara bir dizi basit dönüþüm uygular. Basit dönüþümler, eþleþme bulma amacýyla türleri 
(deðerleri deðiþtirmeden) deðiþtirecek belirli dönüþüm kurallarýdýr. Örneðin, bir const olmayan tür, basitçe bir const türüne dönüþtürülebilir:

                    void print(const int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        int x { 0 };
                        print(x); // x, basitçe const int'ye dönüþtürülür

                        return 0;
                    }

Yukarýdaki örnekte, print(x) çaðrýsýný yaptýk, burada x bir int. Derleyici x'i int'ten const int'e basitçe dönüþtürecek, ardýndan print(const int)
ile eþleþecektir.

Basit dönüþümler aracýlýðýyla yapýlan eþleþmeler tam eþleþme olarak kabul edilir.

Adým 2) Eðer tam bir eþleþme bulunmazsa, derleyici argüman(lar)a sayýsal yükseltme uygulayarak bir eþleþme bulmaya çalýþýr. 10.1 dersinde
(Örtülü tür dönüþümü) belirli dar tamsayýsal ve kayan noktalý türlerin otomatik olarak daha geniþ türlere, örneðin int veya double, 
yükseltilebileceðini ele almýþtýk. Sayýsal yükseltme sonrasýnda bir eþleþme bulunursa, fonksiyon çaðrýsý çözülür.

Örneðin:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print('a');    // print(int) ile eþleþecek þekilde yükseltilir
                        print(true);   // print(int) ile eþleþecek þekilde yükseltilir
                        print(4.5f);   // print(double) ile eþleþecek þekilde yükseltilir

                        return 0;
                    }

print('a') için, print(char) için tam bir eþleþme bulunamadýðýndan, derleyici char 'a'yý bir int'e yükseltir ve eþleþme arar. Bu, print(int) ile
eþleþir, bu nedenle fonksiyon çaðrýsý print(int) olarak çözülür.

Adým 3) Eðer sayýsal yükseltme aracýlýðýyla bir eþleþme bulunamazsa, derleyici argümanlara sayýsal dönüþümleri uygulayarak bir eþleþme bulmaya çalýþýr.

Örneðin:

                    #include <string> // for std::string

                    void print(double)
                    {
                    }

                    void print(std::string)
                    {
                    }

                    int main()
                    {
                        print('a'); // 'a', print(double) ile eþleþecek þekilde dönüþtürülür

                        return 0;
                    }

Bu durumda, print(char) (tam eþleþme) ve print(int) (yükseltme eþleþmesi) olmadýðý için 'a', sayýsal olarak bir double'ye dönüþtürülür ve print(double)
ile eþleþir.

Anahtar Ýpucu

Sayýsal yükseltmeler uygulayarak yapýlan eþleþmeler, sayýsal dönüþümler uygulayarak yapýlan eþleþmelerin üstündedir.


Adým 4) Eðer sayýsal dönüþüm aracýlýðýyla bir eþleþme bulunamazsa, derleyici herhangi bir kullanýcý tanýmlý dönüþüm aracýlýðýyla bir eþleþme bulmaya 
çalýþýr. Henüz kullanýcý tanýmlý dönüþümleri ele almadýk, ancak belirli tipler (örneðin, sýnýflar) baþka tiplere dönüþümleri tanýmlayabilir ve bu 
dönüþümler, dolaylý olarak çaðrýlabilir. Ýþte noktayý açýklamak için bir örnek:

(Not: Burada, kullanýcý tanýmlý dönüþümleri iþlememiþ olabiliriz, ancak konsepti anlatmak için basit bir örnek kullanýlýyor.)

                    // Sýnýflarý henüz ele almadýk, bu nedenle bu anlamsýz geliyorsa endiþelenmeyin
                    class X // this defines a new type called X
                    {
                    public:
                        operator int() { return 0; } // Ýþte X türünden int'e olan kullanýcý tanýmlý dönüþüm
                    };

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        X x; // Burada, X türünde bir nesne oluþturuyoruz (isimlendirilmiþ x)
                        print(x); // x, X'ten int'e olan kullanýcý tanýmlý dönüþümü kullanarak int türüne dönüþtürülüyor

                        return 0;
                    }

Bu örnekte, derleyici önce `print(X)` için tam bir eþleþme olup olmadýðýný kontrol eder. Biz böyle bir eþleþme tanýmlamadýk. Daha sonra derleyici,
`x`'in sayýsal olarak yükseltilip yükseltilmediðini kontrol eder, ancak bu mümkün deðildir çünkü kullanýcý tanýmlý bir tür olan `X`'ten doðrudan
sayýsal bir yükseltme yoktur.

Ardýndan, derleyici `x`'in sayýsal olarak dönüþtürülüp dönüþtürülemediðini kontrol eder, ancak bu durumda da mümkün deðildir.

Son olarak, derleyici herhangi bir kullanýcý tanýmlý dönüþüme bakar. `X` sýnýfýndaki `operator int()` kullanýcý tanýmlý dönüþümü bulur. Sonuç olarak,
`x` adlý `X` türündeki nesne, `int` türüne kullanýcý tanýmlý dönüþümü kullanarak dönüþtürülür ve `print(int)` ile eþleþmesi saðlanýr.

Kullanýcý tanýmlý dönüþüm uygulandýktan sonra, derleyici eþleþme bulabilmek için ek implicit (otomatik) yükseltmeler veya dönüþümler uygulayabilir.
Bu örnekte, eðer kullanýcý tanýmlý dönüþüm `int` yerine `char` türüne yapýlmýþ olsaydý, derleyici kullanýcý tanýmlý dönüþümü `char` türüne kullanacak
ve ardýndan sonucu `int` türüne yükseltecekti, böylece `print(int)` fonksiyonuyla eþleþebilirdi.

Adým 5) Eðer kullanýcý tanýmlý dönüþüm aracýlýðýyla bir eþleþme bulunamazsa, derleyici üç nokta (...) kullanan bir eþleþen fonksiyon arayacaktýr.

Adým 6) Eðer bu noktaya kadar hiçbir eþleþme bulunamazsa, derleyici vazgeçer ve eþleþen bir fonksiyon bulunamadýðýna dair bir derleme hatasý verecektir.

Karýþýk Eþleþmeler
------------------

Overloaded olmayan fonksiyonlarla, her fonksiyon çaðrýsý ya bir fonksiyona çözülecek ya da hiç eþleþme bulunamayacak ve derleyici bir derleme hatasý 
verecektir:

                    void foo()
                    {
                    }

                    int main()
                    {
                         foo(); // Tamam: Eþleþme bulundu
                         goo(); // Derleme hatasý: Eþleþme bulunamadý

                         return 0;
                    }

Overloaded fonksiyonlarla, üçüncü bir olasýlýk daha vardýr: belirsiz bir eþleþme bulunabilir. Belirsiz bir eþleþme, derleyicinin ayný adý taþýyan iki 
veya daha fazla fonksiyonu ayný adýmda eþleþtirebileceði durumu ifade eder. Bu durumda, derleyici eþleþmeyi durdurur ve belirsiz bir fonksiyon çaðrýsý
bulduðunu belirten bir derleme hatasý verir.

Her yüklenmiþ fonksiyonun derlenebilmesi için diferansiyasyon yapýlmasý gerektiðinden, bir fonksiyon çaðrýsýnýn nasýl oluyor da birden fazla eþleþmeye
neden olabileceðini merak ediyor olabilirsiniz. Bunu gösteren bir örneðe bakalým:

                    void print(int)
                    {
                    }

                    void print(double)
                    {
                    }

                    int main()
                    {
                        print(5L); // 5L long türüdür

                        return 0;
                    }

Evet, tabii ki! Ýþte metnin Türkçe çevirisi:

"5L ifadesi tipi long olduðundan, derleyici önce print(long) için tam bir eþleþme bulup bulamayacaðýný kontrol edecektir, ancak böyle bir eþleþme
bulamayacaktýr. Sonrasýnda, derleyici sayýsal yükseltmeyi deneyecek, ancak long tipindeki deðerler yükseltilmediði için burada da bir eþleþme
olmayacaktýr.

Bundan sonra, derleyici long argümaný üzerinde sayýsal dönüþümleri uygulayarak bir eþleþme bulmaya çalýþacaktýr. Sayýsal dönüþüm kurallarýný kontrol 
ederken, derleyici iki potansiyel eþleþme bulacaktýr. Eðer long argümaný bir int'e numerik olarak dönüþtürülürse, fonksiyon çaðrýsý print(int) ile
eþleþecektir. Eðer long argümaný bir double'a dönüþtürülürse, o zaman print(double) ile eþleþecektir. Ýki farklý sayýsal dönüþüm yoluyla iki potansiyel
eþleþme bulunduðu için, fonksiyon çaðrýsý belirsiz kabul edilir.

Visual Studio 2019'da, bu durum þu hata mesajýna yol açacaktýr:"

                    Hata C2668: 'print': aþýrý yüklenmiþ fonksiyona belirsiz çaðrý
                    mesajý: 'void print(double)' olabilir
                    mesajý: veya 'void print(int)' olabilir
                    mesajý: '(long)' argüman listesine eþleþmeye çalýþýrken


Ana Ýpucu

Eðer derleyici bir adýmda birden fazla eþleþme bulursa, belirsiz bir fonksiyon çaðrýsý ortaya çýkar. Bu durumda, bir adýmdan elde edilen hiçbir eþleþme,
ayný adýmdan diðer herhangi bir eþleþmeden daha iyi kabul edilmez.

Ýþte baþka bir örnek, belirsiz eþleþmelere neden olan:

                    void print(unsigned int)
                    {
                    }

                    void print(float)
                    {
                    }

                    int main()
                    {
                        print(0); // int, unsigned int'e veya floata sayýsal olarak dönüþtürülebilir
                        print(3.14159); // double, unsigned int'e veya floata sayýsal olarak dönüþtürülebilir

                        return 0;
                    }

0'ýn `print(unsigned int)` olarak çözünmesini ve 3.14159'un `print(float)` olarak çözünmesini bekleyebilirsiniz, ancak her iki çaðrý da belirsiz 
eþleþmelere neden olur. int deðeri 0, hem `unsigned int`'e hem de `float`'e sayýsal olarak dönüþtürülebilir, bu nedenle her iki aþýrý yüklenmiþ 
fonksiyon da eþit derecede iyi eþleþir ve sonuç belirsiz bir fonksiyon çaðrýsýdýr.

Ayný durum, bir `double`'ýn hem `float`'a hem de `unsigned int`'e dönüþtürülmesi için geçerlidir. Her ikisi de sayýsal dönüþümler olduðundan, her
iki aþýrý yükleme de eþit derecede iyi eþleþir ve sonuç yine belirsizdir.

Belirsiz eþleþmeleri çözme
--------------------------

"Belirsiz eþleþmeler derleme zamaný hatasý olduðu için programýnýzýn derlenmesi için bir belirsiz eþleþme çözülmelidir. Belirsiz eþleþmeleri çözmek 
için birkaç yol vardýr:

Genellikle en iyi yol, doðrudan çaðýrmaya çalýþtýðýnýz fonksiyon için tam olarak ayný türde parametrelere sahip yeni bir aþýrý yüklenmiþ fonksiyon 
tanýmlamaktýr. Bu durumda C++, fonksiyon çaðrýsý için tam bir eþleþme bulabilecektir.

Alternatif olarak, belirsiz argüman(lar)ý açýkça istediðiniz fonksiyon türüne eþleþecek þekilde dönüþtürebilirsiniz. Örneðin, yukarýdaki örnekte 
print(0)'ý print(unsigned int) ile eþleþtirmek için þunu yapabilirsiniz:"

                    int x{ 0 };
                    print(static_cast<unsigned int>(x)); // print(unsigned int) ý çaðýracak

Eðer argümanýnýz bir literal ise, literal öneki kullanarak literalinizi doðru tür olarak yorumlanmasýný saðlayabilirsiniz:

                    print(0u); // 'u' öneki unsigned int olduðu için print(unsigned int) fonksiyonunu çaðýracaktýr, bu nedenle bu þimdi tam bir eþleþme

Birden fazla baðýmsýz deðiþkene sahip fonksiyonlar için eþleþtirme
------------------------------------------------------------------
Eðer birden çok argüman varsa, derleyici her argümana sýrayla eþleþme kurallarýný uygular. Seçilen fonksiyon, her bir argümanýn en az diðer tüm
fonksiyonlarla ayný derecede eþleþtiði ve en az bir argümanýn diðer tüm fonksiyonlardan daha iyi eþleþtiði fonksiyondur. Baþka bir deyiþle, seçilen
fonksiyon, en az bir parametre için diðer tüm aday fonksiyonlardan daha iyi bir eþleþme saðlamalý ve diðer tüm parametreler için daha kötü olmamalýdýr.

Bu tür bir fonksiyon bulunduðunda, açýkça ve belirsiz olmadan en iyi seçenek olduðu anlaþýlýr. Eðer böyle bir fonksiyon bulunamazsa, çaðrý belirsiz
(veya uyuþmaz) olarak kabul edilecektir.

Örneðin:

                    #include <iostream>

                    void print(char, int)
                    {
                        std::cout << 'a' << '\n';
                    }

                    void print(char, double)
                    {
                        std::cout << 'b' << '\n';
                    }

                    void print(char, float)
                    {
                        std::cout << 'c' << '\n';
                    }

                    int main()
                    {
                        print('x', 'a');

                        return 0;
                    }

Yukarýdaki programda, tüm fonksiyonlar ilk argümaný tam olarak eþleþtirir. Ancak, en üstteki fonksiyon ikinci parametreyi yükseltme yoluyla 
eþleþtirirken, diðer fonksiyonlar bir dönüþüme ihtiyaç duyar. Bu nedenle, print(char, int) fonksiyonu belirsiz bir þekilde en iyi eþleþmedir.

10.13 — Fonksiyonlarý Silme
---------------------------

Belirli durumlarda, belirli tiplerdeki deðerlerle çaðrýldýðýnda istenen þekilde davranmayan fonksiyonlar yazmak mümkündür.

Aþaðýdaki örneði düþünün:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    int main()
                    {
                        printInt(5);    // tamam: 5'i yazdýrýr
                        printInt('a');  // 97 yazdýrýr -- bu mantýklý mý?
                        printInt(true); // 1'i yazdýrýr -- bu mantýklý mý?

                        return 0;
                    }

Bu örnekte çýktý:

                    5
                    97
                    1

printInt(5) açýkça uygunken, printInt()'e yapýlan diðer iki çaðrý daha tartýþmalýdýr. printInt('a') çaðrýsýnda derleyici, 'a'yý int deðeri 97'ye
yükseltebileceðini belirleyecek ve bu þekilde fonksiyon çaðrýsýný fonksiyon tanýmýyla eþleþtirecektir. Ayný þekilde, true deðerini int deðeri 1'e
yükseltecektir. Ve bu iþlem uyarý vermeden gerçekleþecektir.

Varsayalým ki printInt() fonksiyonuna char veya bool türünden bir deðerle çaðrýlmasýnýn mantýklý olmadýðýný düþünüyoruz. Ne yapabiliriz?

Fonksiyonu = delete belirleyicisi kullanarak silme
--------------------------------------------------
Belirli bir fonksiyonun bilinçli olarak çaðrýlamamasýný istediðimiz durumlarda, bu fonksiyonu = delete belirleyicisini kullanarak silmek mümkündür. 
Derleyici, bir fonksiyon çaðrýsýný silinmiþ bir fonksiyonla eþleþtirirse, derleme, derleme hatasý ile durdurulacaktýr.

Ýþte yukarýdaki örneði bu sözdizimini kullanarak güncelleyen bir versiyon:

                    #include <iostream>

                    void printInt(int x)
                    {
                        std::cout << x << '\n';
                    }

                    void printInt(char) = delete; // bu fonksiyona yapýlan çaðrýlar derlemeyi durduracaktýr
                    void printInt(bool) = delete; // bu fonksiyona yapýlan çaðrýlar derlemeyi durduracaktýr

                    int main()
                    {
                        printInt(97);   // tamam

                        printInt('a');  // derleme hatasý: fonksiyon silinmiþ
                        printInt(true); // derleme hatasý: fonksiyon silinmiþ

                        printInt(5.0);  // derleme hatasý: belirsiz eþleþme

                        return 0;
                    }

Hadi bunlara bir göz atalým. Ýlk olarak, printInt('a'), silinmiþ olan printInt(char) için doðrudan bir eþleþmedir. Bu nedenle derleyici bir derleme
hatasý üretir. printInt(true), silinmiþ olan printInt(bool) için doðrudan bir eþleþmedir ve bu nedenle ayný þekilde derleme hatasý üretir.

printInt(5.0) ilginç bir durumdur ve belki de beklenmeyen sonuçlara neden olabilir. Ýlk olarak, derleyici, tam eþleþme olan printInt(double)'ýn
varlýðýný kontrol eder. Ancak böyle bir fonksiyon yoktur. Sonraki adýmda, derleyici en iyi eþleþmeyi bulmaya çalýþýr. printInt(int) tek silinmeyen
fonksiyon olmasýna raðmen, silinmiþ fonksiyonlar hala fonksiyon aþýrý yüklenme çözümlemesinde aday olarak kabul edilir. Bu fonksiyonlardan hiçbiri
açýkça en iyi eþleþme deðildir, bu nedenle derleyici belirsiz eþleþme derleme hatasý verecektir.

= delete, 'Bunu yasaklýyorum' anlamýna gelir, 'Bu mevcut deðil' anlamýna gelmez.

Silinmiþ fonksiyonlar, fonksiyon aþýrý yükleme çözümlemesinin tüm aþamalarýnda (yalnýzca tam eþleþme aþamasýnda deðil) yer alýr. Eðer bir silinmiþ
fonksiyon seçilirse, o zaman bir derleme hatasý ortaya çýkar.

10.14 — Varsayýlan Argümanlar
-----------------------------
Bir varsayýlan argüman, bir fonksiyon parametresi için saðlanan varsayýlan bir deðerdir. Örneðin:

                    void print(int x, int y=10) // 10 is the default argument
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

Fonksiyon çaðrýsý yapýlýrken, çaðrýcý isteðe baðlý olarak varsayýlan bir argümaný olan herhangi bir fonksiyon parametresi için bir argüman saðlayabilir.
Çaðrýcý bir argüman saðlarsa, fonksiyon çaðrýsýndaki argüman deðeri kullanýlýr. Çaðrýcý bir argüman saðlamazsa, varsayýlan argümanýn deðeri kullanýlýr.

Aþaðýdaki programý düþünün:

                    #include <iostream>

                    void print(int x, int y=4) // 4 varsayýlan argümandýr
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

                    int main()
                    {
                        print(1, 2); // y kullanýcý tarafýndan saðlanmýþ 2 deðerini kullanýr.
                        print(3); // y varsayýlan argüman olan 4 ü kullanýr, print(3, 4) olarak çaðýrmýþýz gibi.

                        return 0;
                    }
Bu program þu çýktýyý verir:
                    x: 1
                    y: 2
                    x: 3
                    y: 4

Ýlk fonksiyon çaðrýsýnda, çaðrýcý her iki parametre için de açýkça argüman saðladý, bu nedenle bu argüman deðerleri kullanýldý. Ýkinci fonksiyon 
çaðrýsýnda, çaðrýcý ikinci argümaný atladý, bu nedenle varsayýlan deðer olan 4'ün deðeri kullanýldý.

Varsayýlan bir argümaný belirtmek için eþittir iþaretini kullanmanýz gerektiðini unutmayýn. Parantez veya süslü parantez baþlatma kullanmak iþe yaramaz:

                    void foo(int x = 5);   // ok
                    void goo(int x ( 5 )); // compile error
                    void boo(int x { 5 }); // compile error


Belki de þaþýrtýcý bir þekilde, varsayýlan argümanlar derleyici tarafýndan çaðrý noktasýnda iþlenir. Yukarýdaki örnekte, derleyici print(3) ifadesini
gördüðünde, bu fonksiyon çaðrýsýný print(3, 4) olarak yeniden yazacak ve argüman sayýsý parametre sayýsýyla eþleþecektir. Yeniden yazýlmýþ fonksiyon
çaðrýsý ardýndan normal þekilde çalýþýr.

Varsayýlan argümanlarý ne zaman kullanmalýsýnýz
-----------------------------------------------
Varsayýlan argümanlar, bir fonksiyonun mantýklý bir varsayýlan deðere ihtiyaç duyduðu durumlarda ve çaðrýcýya bu deðeri isteðe baðlý olarak geçme
olanaðý tanýmak istediðiniz durumlarda mükemmel bir seçenektir.

Örneðin, burada varsayýlan argümanlarýn yaygýn olarak kullanýlabileceði birkaç fonksiyon prototipi bulunmaktadýr:

                    int rollDie(int sides=6);
                    void openLogFile(std::string filename="default.log");

Yazarýn Notu:

Kullanýcý, belirli bir argüman deðeri saðlayýp saðlamamayý seçebildiði için, bir varsayýlan deðerle saðlanan bir parametre bazen "isteðe baðlý
parametre" olarak adlandýrýlýr. Ancak, "isteðe baðlý parametre" terimi ayný zamanda baþka türden parametreleri de ifade etmek için kullanýlýr
(örneðin, adresle geçirilen parametreler ve std::optional kullanýlan parametreler), bu nedenle bu terimi kullanmaktan kaçýnmanýzý öneririz.

Birden fazla varsayýlan argüman
-------------------------------

Bir fonksiyon bir çok varsayýlan argümana sahip olabilir:

                    #include <iostream>

                    void print(int x=10, int y=20, int z=30)
                    {
                        std::cout << "Values: " << x << " " << y << " " << z << '\n';
                    }

                    int main()
                    {
                        print(1, 2, 3); // tümü kasýtlý argümanlar
                        print(1, 2); // en saðdaki argüman varsayýlandýr
                        print(1); // en saðdan ikisi varsayýlan argümandýr
                        print(); // tüm argümanlar default olarak seçilmiþtir

                        return 0;
                    }
Çýktý:
                    Values: 1 2 3
                    Values: 1 2 30
                    Values: 1 20 30
                    Values: 10 20 30

C++ (en azýndan C++20'ye kadar) print(,,3) gibi bir fonksiyon çaðrý sözdizimini desteklemez (x ve y için varsayýlan argümanlarý kullanýrken z
için açýk bir deðer saðlama yöntemi olarak). Bu iki önemli sonuç doðurur:
1- Eðer bir parametre varsayýlan bir argüman alýyorsa, bütün sonraki parametreler (sað taraftakiler) de varsayýlan argümanlar almak zorundadýr.
Aþaðýdaki örnek izin verilmez:

                    void print(int x=10, int y); // not allowed
yani default argüman tanýmlarken her zaman en sonda veya sað tarafýndaki tüm argümanlar default olmalý Bu kuraldýr.

2- Eðer birden fazla parametre varsayýlan bir argüman alýyorsa, sol taraftaki parametre genellikle kullanýcý tarafýndan açýkça belirlenecek olan
parametre olmalýdýr.

Varsayýlan argümanlar yeniden bildirilemez
------------------------------------------

Bir kez bildirildikten sonra, bir varsayýlan argüman ayný dosyada tekrar bildirilemez. Yani, bir fonksiyonun önceden bildirimi (forward declaration) 
ve bir fonksiyon tanýmý için, varsayýlan argüman ya önceden bildirimde ya da fonksiyon tanýmýnda bildirilebilir, ancak her ikisinde birden bildirilemez.

                    #include <iostream>

                    void print(int x, int y=4); // forward declaration

                    void print(int x, int y=4) // error: redefinition of default argument
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

*** BEST -> varsayýlan argümaný önceden bildiride (forward declaration) bildirmek, fonksiyon tanýmýnda bildirmektense daha iyidir, çünkü önceden
            bildiri, diðer dosyalar tarafýndan daha olasý bir þekilde görülecektir (özellikle bir baþlýk dosyasýndaysa).

foo.h da
                    #ifndef FOO_H
                    #define FOO_H
                    void print(int x, int y=4);
                    #endif
main.cpp de
                    #include "foo.h"
                    #include <iostream>

                    void print(int x, int y)
                    {
                        std::cout << "x: " << x << '\n';
                        std::cout << "y: " << y << '\n';
                    }

                    int main()
                    {
                        print(5);

                        return 0;
                    }


Yukarýdaki örnekte, print() fonksiyonu için varsayýlan argümaný kullanabiliyoruz çünkü main.cpp, varsayýlan argümaný tanýmlayan bir önceden bildirim
içeren foo.h dosyasýný içeriyor.

*** BEST -> Eðer bir fonksiyonun önceden bildirimi varsa (özellikle bir baþlýk dosyasýnda ise), varsayýlan argümaný oraya koyun. Aksi takdirde, 
            varsayýlan argümaný fonksiyon tanýmýna koyun.

Varsayýlan Argümanlar ve Fonksiyon Aþýrý Yükleme
------------------------------------------------

Varsayýlan argümanlara sahip fonksiyonlar aþýrý yüklenebilir. Örneðin, aþaðýdaki gibi bir durum mümkündür:

                    #include <string>

                    void print(std::string)
                    {
                    }

                    void print(char=' ')
                    {
                    }

                    int main()
                    {
                        print("Hello, world"); // print(std::string) olarak çözülür
                        print('a'); // print(char) olarak çözülür
                        print(); // print(char) olarak çözülür

                        return 0;
                    }

print() fonksiyonu çaðrýsý, kullanýcýnýn açýkça print(' ') þeklinde çaðýrdýðýný varsayarak iþlev görür ve bu da print(char) olarak çözülür.

Þimdi bu durumu düþünelim:

                    void print(int x);
                    void print(int x, int y = 10);
                    void print(int x, double y = 20.5);

Varsayýlan deðerlere sahip parametreler, bir fonksiyon aþýrý yüklemesini ayýrt eder (yani yukarýdaki örnek derlenebilir).
Ancak, bu tür fonksiyonlar potansiyel olarak belirsiz fonksiyon çaðrýlarýna neden olabilir. Örneðin:

                    print(1, 2);    // print(int, int) olarak çözülür
                    print(1, 2.5);  // print(int, double) olarak çözülür
                    print(1);       // belirsiz fonksiyon çaðrýsý

Son durumda, derleyiciye `print(1)` ifadesinin `print(int)` olarak mý yoksa ikinci parametresi varsayýlan bir deðere sahip iki fonksiyondan birine 
mi çözülmesi gerektiðini belirleme yeteneði yoktur. Sonuç, belirsiz bir fonksiyon çaðrýsýdýr.

Özet

Varsayýlan argümanlar, kullanýcýnýn isteðe baðlý olarak geçip geçmeyeceði parametreler için deðerler belirtmek için kullanýþlý bir mekanizma saðlar.
C++'da sýkça kullanýlýrlar ve gelecek derslerde sýkça karþýlaþacaksýnýz.
*/