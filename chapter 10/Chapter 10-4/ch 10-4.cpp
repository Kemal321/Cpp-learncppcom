#include <iostream>
template <typename T> 
T max(T x, T y) {
    return (x < y) ? y : x;
}
int main()
{

    std::cout << max(1, 2) << '\n';
    return 0;
}
/*
10.15 — Fonksiyon Þablonlarý - Function templates
-------------------------------------------------

Diyelim ki iki sayýnýn maksimumunu hesaplamak için bir fonksiyon yazmak istiyorsunuz. Bunu þu þekilde yapabilirsiniz:

                    int max(int x, int y) {
                        return (x < y) ? y : x;
                        // Not: std::max, < yerine > kullanýr.
                    }

Çaðrýcý farklý deðerleri fonksiyona iletebilirken, parametre türleri sabit olduðu için çaðrýcý yalnýzca int deðerlerini iletebilir. Bu, bu fonksiyonun
gerçekten yalnýzca tam sayýlar için iyi çalýþtýðý anlamýna gelir (ve int'e yükseltilebilen türler için).

Peki, ileride iki double deðerinin maksimumunu bulmak istediðinizde ne olur? Çünkü C++, tüm fonksiyon parametrelerinin türünü belirtmemizi gerektirdiði
için, çözüm, double türünde parametrelere sahip yeni bir aþýrý yüklenmiþ max sürümü oluþturmaktýr:

                    double max(double x, double y)
                    {
                        return (x < y) ? y: x;
                    }


Dikkat edin ki, maksimum iþleminin double versiyonunun uygulamasý, tam sayý versiyonu için olanýyla tam olarak ayný! Aslýnda, bu uygulama birçok farklý
türde çalýþýr: int, double, long, long double ve hatta kendinizin oluþturduðu yeni türler dahil (bu konuya gelecekteki derslerde nasýl yapýlacaðýný
öðreneceðiz).

Her desteklemek istediðimiz parametre türleri seti için ayný uygulamaya sahip aþýrý yüklenmiþ fonksiyonlar oluþturmak, bakým zorluklarýna, hatalarýn
kaynaðýna ve DRY (kendini tekrar etme) ilkesinin açýk bir ihlaline yol açar. Ayrýca, burada daha az açýk bir zorluk da var: max fonksiyonunu kullanmak
isteyen bir programcý, max'ýn yazarýnýn öngörmediði (ve bu nedenle aþýrý yüklenmiþ bir fonksiyon yazmadýðý) bir argüman türüyle çaðýrmak isteyebilir.

Gerçekten eksik olan þey, herhangi bir türdeki argümanlarla çalýþabilen tek bir max sürümü yazma yoludur (belki de max için kod yazýlýrken öngörülmeyen
türler dahil). Normal fonksiyonlar burada görevin altýndan kalkamazlar. Neyse ki, C++ bu tür bir problemi özel olarak çözmek için tasarlanmýþ baþka bir
özelliði destekler.

C++ þablon dünyasýna hoþ geldiniz.

C++ templatelerine giriþ
------------------------
C++'da, þablon sistemi farklý veri türleriyle çalýþabilen fonksiyonlarý (veya sýnýflarý) oluþturmayý kolaylaþtýrmak amacýyla tasarlanmýþtýr.

Farklý türler için ayrý ayrý neredeyse ayný fonksiyonlarý veya sýnýflarý manuel olarak oluþturmak yerine, tek bir þablon oluþturulur. Normal bir tanýma
benzer þekilde, bir þablon, bir fonksiyonun veya sýnýfýn nasýl göründüðünü açýklar. Normal bir tanýmýn aksine (tüm türlerin belirtilmesi gerektiði bir
yer), þablonlarda bir veya daha fazla yer tutucu tür kullanýlabilir. Bir yer tutucu tür, þablonun yazýldýðý zamanda bilinmeyen ancak daha sonra
saðlanacak bir türü temsil eder.

Bir þablon tanýmlandýðýnda, derleyici þablonu kullanarak ihtiyaç duyulan kadar çok aþýrý yüklenmiþ fonksiyonu (veya sýnýfý) üretebilir, her biri farklý
gerçek türleri kullanarak!

Sonuç aynýdýr - neredeyse ayný fonksiyon veya sýnýflara sahibiz (her bir farklý tür kümesi için bir tane). Ancak sadece tek bir þablon oluþturmak ve
sürdürmek zorundayýz ve derleyici tüm zor iþleri bizim için yapar.

Kilit nokta**

Derleyici, tek bir þablonu kullanarak farklý tür kümesini kullanan ilgili bir fonksiyon veya sýnýf ailesi oluþturabilir.

Öte yandan...
Þablonlarýn ardýndaki konsepti kelimelerle anlatmak zor olabileceðinden, bir benzetme deneyelim.

Sözlükte "þablon" sözcüðüne baktýðýnýzda þuna benzer bir taným bulursunuz: "þablon, benzer nesneler oluþturmak için kalýp görevi gören bir modeldir".
Anlaþýlmasý çok kolay olan þablon türlerinden biri stencillerdir. Bir stencil, üzerinde bir þekil (örneðin mutlu bir yüz) kesilmiþ ince bir malzeme
parçasýdýr (bir karton veya plastik parçasý gibi). Stencil'i baþka bir nesnenin üzerine yerleþtirerek ve ardýndan delikten boya püskürterek kesilen
þekli çok hýzlý bir þekilde kopyalayabilirsiniz. Stencilin kendisinin yalnýzca bir kez oluþturulmasý gerekir ve ardýndan istediðiniz sayýda farklý
renkte kesilmiþ þekli oluþturmak için istediðiniz kadar yeniden kullanýlabilir. Daha da iyisi, Stencilden oluþturulan þeklin renginin, stencil gerçekten
kullanýlýncaya kadar belirlenmesine gerek yoktur.

Þablon-template- aslýnda fonksiyonlar veya sýnýflar oluþturmaya yönelik bir stencildir. Þablonu (kalýbýmýzý - stencil yani -) bir kez yaratýrýz ve ardýndan
onu, belirli bir gerçek tür kümesi için bir fonksiyoni veya sýnýfý kalýplamak için gerektiði kadar kullanabiliriz. Þablon gerçekten kullanýlýncaya kadar
bu gerçek türlerin belirlenmesine gerek yoktur.


Çünkü gerçek türler, þablon bir programda kullanýldýðýnda belirlenir (þablon yazýldýðýnda deðil), þablonun yazarý tüm kullanýlabilecek gerçek türleri
tahmin etmeye çalýþmak zorunda deðildir. Bu, þablon kodunun, þablon yazýldýðýnda bile var olmayan türlerle kullanýlabilmesi anlamýna gelir! Bu, daha
sonra C++ standart kütüphanesini keþfetmeye baþladýðýmýzda ne kadar iþe yarayabileceðimizi göreceðimiz bir konudur; çünkü C++ standart kütüphanesi,
tamamen þablon koduyla doludur!

Kilit nokta**
Þablonlar, þablon yazýldýðýnda mevcut olmayan türlerle bile çalýþabilir. Bu, þablon kodunun hem esnek hem de geleceðe hazýr olmasýna yardýmcý olur!

Fonksiyon þablonlarý yani templateleri
--------------------------------------

Bir fonksiyon þablonu, farklý bir set gerçek türlerle her biri aþýrý yüklenmiþ bir veya daha fazla fonksiyon oluþturmak için kullanýlan bir fonksiyon
benzeri tanýmlamadýr. Bu, birçok farklý türle çalýþabilen fonksiyonlar oluþturmamýza olanak tanýyacaktýr.

Fonksiyon þablonumuzu oluþtururken, daha sonra belirtmek istediðimiz herhangi bir parametre türü, dönüþ türü veya fonksiyon gövdesinde kullanýlan 
tür için yer tutucu türler (ayrýca tür þablon parametreleri (type template parameters) veya gayri resmi olarak þablon türleri ( template types ) olarak 
adlandýrýlýr) kullanýrýz.


Fonksiyon þablonlarý en iyi örneklerle öðretilen bir konsepttir, bu yüzden yukarýdaki örnekteki normal max(int, int) fonksiyonumuzu bir fonksiyon
þablonuna dönüþtürelim. Þaþýrtýcý derecede kolaydýr ve yol boyunca neler olduðunu açýklayacaðýz.

Þablonlu bir max fonksiyonu oluþturmak
--------------------------------------

max fonksuyonunun integer hali:

                    int max(int x, int y)
                    {
                        return (x < y) ? y : x;
                    }

Bu fonksiyonda int türini üç kez kullanýyoruz: bir kez x parametresi için, bir kez y parametresi için ve bir kez de fonksiyonun dönüþ türi için.

Bir fonksiyon þablonu oluþturmak için iki þey yapacaðýz. Ýlk olarak, belirli türlerimizi tür þablon parametreleri ile deðiþtireceðiz. Bu durumda, 
yalnýzca bir türün yerine konmasý gerektiði için (int), yalnýzca bir tane tür þablon parametresine ihtiyacýmýz var (ki ona T diyeceðiz):

Ýþte tek bir þablon türü kullanan yeni fonksiyonumuz:

                    T max(T x, T y) // Bu þuan derlenmeyecek þünkü daha T yi tanýmlamadýk
                    {
                        return (x < y) ? y : x;
                    }

Bu iyi bir baþlangýç -- ancak derleyici T'nin ne olduðunu bilmediði için derlenmeyecek! Ve bu hala normal bir fonksiyon, bir fonksiyon þablonu deðil.

Ýkinci olarak, derleyiciye bu fonksiyonun bir fonksiyon þablonu olduðunu ve T'nin herhangi bir tür için yer tutucu olan bir tür þablon parametresi 
olduðunu söyleyeceðiz. Bunu, bir þablon parametre deklarasyonu olarak adlandýrýlan bir þeyle yaparýz. Bir þablon parametre deklarasyonunun kapsamý,
takip eden fonksiyon þablonuna (veya sýnýf þablonuna) sýnýrlýdýr. Bu nedenle, her fonksiyon þablonu (veya sýnýf) kendi þablon parametre deklarasyonuna
ihtiyaç duyar.

                    template <typename T> // bu, þablon parametre deklarasyonudur
                    T max(T x, T y) // bu, max<T> için fonksiyon þablonu tanýmýdýr
                    {
                        return (x < y) ? y : x;
                    }

Þablon parametre deklarasyonumuzda, bir þablon oluþturduðumuzu belirten anahtar kelime olarak template kullanýrýz. Ardýndan, þablonumuzun içinde
kullanacaðýmýz tüm þablon parametrelerini köþeli parantezler içinde belirtiriz (<>). Her tür þablon parametresi için typename veya class anahtar
kelimesini kullanýrýz, ardýndan tür þablon parametresinin adý gelir (örneðin, T).

Bir kenara not olarak...

Bu baðlamda typename ve class anahtar kelimeleri arasýnda hiçbir fark yoktur. Ýnsanlarý genellikle dilin daha önce tanýtýldýðý için class anahtar
kelimesini kullanýrken göreceksiniz. Ancak, daha yeni olan typename anahtar kelimesini tercih ediyoruz, çünkü bu, tür þablon parametresinin yalnýzca 
sýnýf türleri deðil, ayný zamanda temel türler gibi herhangi bir türle de deðiþtirilebileceðini daha açýk bir þekilde belirtir.


Ýnanýn veya inanmayýn, iþte bu kadar! Þimdi, farklý türlerdeki argümanlarý kabul edebilen max fonksiyonumuzun þablon versiyonunu oluþturduk.

Bu fonksiyon þablonu, T adlý bir þablon türüne sahip olduðu için ona max<T> olarak atýfta bulunacaðýz. Bir sonraki derste, max<T> fonksiyon 
þablonumuzu nasýl kullanacaðýmýzý ve farklý türlerdeki parametrelerle bir veya daha fazla max() fonksiyonunu nasýl oluþturacaðýmýzý inceleyeceðiz.

Template parametrelerinin adlandýrýlmasý
----------------------------------------
Bir deðiþkenin adýný (örneðin, x) basit durumlarda genellikle tek bir harfle adlandýrýyorsak, bu türin anlamý basit veya açýk olduðunda genellikle
tek bir büyük harf (T ile baþlayan) kullanmak alýþýlmýþ bir uygulamadýr. Örneðin, max fonksiyon þablonumuzda:

T'ye karmaþýk bir ad vermemize gerek yok, çünkü açýkça yalnýzca karþýlaþtýrýlan deðerler için bir yer tutucu türdür.

Genellikle fonksiyon þablonlarýmýz bu isimlendirme kurallarýný kullanacaktýr.

Eðer bir tür þablon parametresinin açýk olmayan bir kullanýmý veya anlamý varsa, o zaman daha açýklayýcý bir isim gereklidir. Bu tür isimlendirme için
iki yaygýn kural bulunmaktadýr:

Bir büyük harfle baþlamak (örneðin, Allocator). Standart kütüphane bu isimlendirme kuralýný kullanýr.
T ile baþlayýp sonra bir büyük harfle baþlamak (örneðin, TAllocator). Bu, türün bir tür þablon parametresi olduðunu daha kolay görmemizi saðlar.

Hangisini seçeceðimiz bize kalmýþ bir durumdur. 

*** BEST 
---------
Basit veya açýk bir þekilde kullanýlan tür þablon parametrelerine T, U, V gibi tek bir büyük harf baþlatýlýr.

Eðer tür þablon parametresinin açýk olmayan bir kullanýmý veya anlamý varsa, o zaman daha açýklayýcý bir isim gerekir (örneðin, Allocator veya 
TAllocator).

10.16 — Fonksiyon þablonu örneklemesi
-------------------------------------

Bu derste fonksiyon þablonlarýnýn nasýl kullanýlacaðýna odaklanacaðýz.

Fonksiyon þablonlarý aslýnda fonksiyonlar deðildir - kodlarý doðrudan derlenmez veya doðrudan yürütülmez. Bunun yerine, fonksiyon þablonlarýnýn bir 
görevi vardýr: fonksiyonlarý üretmek (derlenip yürütülen).

max<T> fonksiyon þablonumuzu kullanmak için aþaðýdaki sözdizimiyle bir fonksiyon çaðrýsý yapabiliriz:

                    max<actual_type>(arg1, arg2); // actual_type bir türdür, int veya double gibi           

Bu, normal bir fonksiyon çaðrýsýna oldukça benziyor - temel fark, þablon türü T'nin yerine kullanýlacak gerçek türü belirten açýk parantez içindeki
türdür (bu bir þablon argümaný olarak adlandýrýlýr).

Bunu basit bir örnekte inceleyelim:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // þablonu örnekler ve max<int>(int, int) fonksiyonunu çaðýrýr

                        return 0;
                    }

Derleyici, max<int>(1, 2) fonksiyon çaðrýsýný karþýlaþtýðýnda, max<int>(int, int) için bir fonksiyon tanýmýnýn zaten mevcut olmadýðýný belirleyecektir.
Sonuç olarak, derleyici max<T> fonksiyon þablonumuzu kullanarak bir tane oluþturacaktýr.

Fonksiyon þablonlarýndan (þablon türleri ile) fonksiyonlar oluþturma sürecine "fonksiyon þablonu örneklemesi (veya kýsaca Örnekleme) oluþturma" denir.
Bu süreç bir fonksiyon çaðrýsý nedeniyle gerçekleþtiðinde, buna "örtük örnekleme" denir. Bir örneklenmiþ fonksiyon, genellikle bir fonksiyon örneði
(kýsaca örnek) veya bir þablon fonksiyonu olarak adlandýrýlýr. Fonksiyon örnekleri her yönden normal fonksiyonlardýr.

Bir fonksiyonun anýnda yapýlma süreci basittir: derleyici temelde fonksiyon þablonunu klonlar ve þablon türini (T) belirttiðimiz gerçek tür ile 
deðiþtirir.

Bu nedenle max<int>(1, 2) çaðrýsýnda, anýnda oluþturulan fonksiyon þuna benzer bir þeydir:

                    template<> // Þuanlýk umursamayýn
                    int max<int>(int x, int y) // Örneklenmiþ fonksiyon max<int>(int, int)
                    {
                        return (x < y) ? y : x;
                    }

Yukarýdaki örneðin aynýsý aþaðýda gösterilmiþtir. Burada derleyicinin tüm anlamlandýrmalarý yaptýktan sonra aslýnda neyi derlediðini gösteriyor:

                    #include <iostream>

                    // Fonksiyon þablonumuzun bir deklarasyonu (artýk tanýmýna ihtiyaç duymuyoruz)
                    template <typename T>
                    T max(T x, T y);

                    // Belirli bir tür için özel birleþtirilmiþ (specialized) fonksiyon max<int>(int, int)
                    template <>
                    int max<int>(int x, int y) // oluþturulan fonksiyon max<int>(int, int)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // fonksiyon max<int>(int, int) instante edilir ve çaðrýlýr

                        return 0;
                    }

Kendi bilgisayarýnýzda derleyip çalýþtýrabilir ve iþlediðini görebilirsiniz. Bir fonksiyon þablonu, her çeviri biriminde bir fonksiyon çaðrýsý 
yapýldýðýnda yalnýzca ilk kez anýnda oluþturulur. Fonksiyona yapýlan sonraki çaðrýlar, zaten oluþturulmuþ olan fonksiyona yönlendirilir.

Tersine, bir çeviri biriminde bir fonksiyon þablonuna hiç çaðrý yapýlmazsa, o fonksiyon þablonu o çeviri biriminde anýnda oluþturulmaz.

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y) // max(T, T) için bir fonksiyon þablonu
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n';    // max<int>(int, int) þablonunu anýnda oluþturur ve çaðýrýr
                        std::cout << max<int>(4, 3) << '\n';    // zaten oluþturulmuþ max<int>(int, int) fonksiyonunu çaðýrýr
                        std::cout << max<double>(1, 2) << '\n'; // max<double>(double, double) þablonunu anýnda oluþturur ve çaðýrýr

                        return 0;
                    }

Bu C++ kodu, bir önceki örnekle benzer þekilde çalýþýr, ancak bu sefer fonksiyon þablonumuz iki fonksiyon oluþturmak için kullanýlýr: bir tanesi T'yi int 
ile deðiþtirerek, diðeri T'yi double ile deðiþtirerek. Tüm anlamlandýrmalar yapýldýktan sonra, program þu þekilde görünecektir.

                    #include <iostream>

                    // Fonksiyon þablonumuzun bir deklarasyonu (artýk tanýmýna ihtiyaç duymuyoruz)
                    template <typename T>
                    T max(T x, T y);

                    // int türü için özel birleþtirilmiþ (specialized) max fonksiyonu tanýmý: max<int>(int, int)
                    template <>
                    int max<int>(int x, int y)
                    {
                        return (x < y) ? y : x;
                    }

                    // double türü için özel birleþtirilmiþ (specialized) max fonksiyonu tanýmý: max<double>(double, double)
                    template <>
                    double max<double>(double x, double y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n';    // max<int>(int, int) þablonunu anýnda oluþturur ve çaðýrýr
                        std::cout << max<int>(4, 3) << '\n';    // zaten oluþturulmuþ max<int>(int, int) fonksiyonunu çaðýrýr
                        std::cout << max<double>(1, 2) << '\n'; // max<double>(double, double) þablonunu anýnda oluþturur ve çaðýrýr

                        return 0;
                    }
****
Burada dikkat edilmesi gereken bir baþka þey: max<double> örneklemi yapýldýðýnda, örneklemi oluþturulan fonksiyonun parametreleri double türündedir.
Çünkü int argümanlarý saðladýk, bu argümanlar otomatik olarak double türüne dönüþtürülür.

Þablon Argüman Çýkartýmý
------------------------
Çoðu durumda, anlamlandýrmak istediðimiz türler genellikle fonksiyon parametrelerimizin türleriyle eþleþir. Örneðin:

                    std::cout << max<int>(1, 2) << '\n'; // max<int> çaðrýsýný yapmak istediðimizi belirtiyoruz

Bu fonksiyon çaðrýsýnda, T'yi int ile deðiþtirmek istediðimizi belirttik, ancak ayný zamanda fonksiyonu int argümanlarý ile çaðýrýyoruz.

Argüman türleri, istediðimiz gerçek türle eþleþtiðinde, gerçek türü belirtmeye gerek yoktur. Bunun yerine, fonksiyon çaðrýsýndaki argüman
türlerinden gerçek türün çýkartýlmasý için þablon argüman çýkarsamasýný kullanabiliriz.

Örneðin, þu þekilde bir fonksiyon çaðrýsý yapmak yerine:

                    std::cout << max<>(1, 2) << '\n';
                    std::cout << max(1, 2) << '\n';

Her iki durumda da derleyici, gerçek bir tür saðlamadýðýmýzý görecektir, bu nedenle bir max() fonksiyonu oluþturmak için fonksiyon argümanlarýndan bir
gerçek tür çýkarmaya çalýþacaktýr. Bu, template parametrelerinin türüyle saðlanan argümanlarýn türü eþleþen bir max() fonksiyonu oluþturmasýna izin
verecek. Bu örnekte, derleyici, int türünü kullanarak max<T> fonksiyon þablonunu kullanarak, her iki template parametresinin türünün (int) saðlanan
argümanlarýn türüyle eþleþtiði max<int>(int, int) fonksiyonunu oluþturmanýn mümkün olduðunu çýkaracaktýr.

Ýki durum arasýndaki fark, derleyicinin aþýrý yüklenmiþ fonksiyonlarýn bir kümesinden bir fonksiyon çaðrýsýný nasýl çözdüðü ile ilgilidir. Üstteki
durumda (boþ açýlý parantezlerle), derleyici, hangi aþýrý yüklenmiþ fonksiyonu çaðýracaðýný belirlerken yalnýzca max<int> þablon fonksiyon aþýrý 
yüklemelerini göz önüne alacaktýr. Altta (açýlý parantez olmadan) durumda, derleyici hem max<int> þablon fonksiyon aþýrý yüklemelerini hem de max
þablon olmayan fonksiyon aþýrý yüklemelerini göz önüne alacaktýr.

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        std::cout << "max<int>(int, int) çaðrýldý\n";
                        return (x < y) ? y : x;
                    }

                    int max(int x, int y)
                    {
                        std::cout << "max(int, int) çaðrýldý\n";
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max<int>(1, 2) << '\n'; // max<int>(int, int) çaðrýlýr
                        std::cout << max<>(1, 2) << '\n';    // max<int>(int, int) çýkarým yapar (template olmayan fonksiyonlar dikkate alýnmaz)
                        std::cout << max(1, 2) << '\n';      // max(int, int) çaðrýlýr

                        return 0;
                    }

Not etmek önemlidir ki, alttaki durumdaki sözdizimi normal bir fonksiyon çaðrýsýyla tamamen ayný görünüyor! Çoðu durumda, bir fonksiyondan türetilmiþ
fonksiyonlari çaðýrmak için normal fonksiyon çaðrýsý sözdizimini kullanýrýz.

Bunun birkaç nedeni vardýr:

* Sözdizimi daha özdür.
* Eþleþen bir þablon olmayan fonksiyon ve bir fonksiyon þablonu genellikle nadiren olacaktýr.
* Eðer eþleþen bir þablon olmayan fonksiyon ve bir eþleþen fonksiyon þablonumuz varsa, genellikle þablon olmayan fonksiyone öncelik veririz.

Bu son nokta açýk olmayabilir. Bir fonksiyon þablonunun birden çok türle çalýþabilen bir uygulamasý vardýr - ancak bu nedenle geneldir. Bir þablon
olmayan fonksiyonun yalnýzca belirli bir tür kombinasyonuyla baþa çýkma yeteneði vardýr. Bu, belirli türler için optimize edilmiþ veya daha 
özelleþtirilmiþ bir uygulamaya sahip olabilir. Örneðin:

                    #include <iostream>

                    // Bu fonksiyon þablonu birçok türü iþleyebilir, bu nedenle uygulamasý geneldir
                    template <typename T>
                    void print(T x)
                    {
                        std::cout << x; // T'yi normalde nasýl yazdýrýyorsa öyle yazdýr
                    }

                    // Bu fonksiyon sadece bir bool deðerini nasýl yazdýracaðýný düþünmek zorundadýr, bu nedenle bool yazdýrma þeklini özelleþtirebilir
                    void print(bool x)
                    {
                        std::cout << std::boolalpha << x; // bool'ü 1 veya 0 deðil, true veya false olarak yazdýr
                    }

                    int main()
                    {
                        print<bool>(true); // print<bool>(bool) çaðýrýr -- 1'i yazdýrýr
                        std::cout << '\n';

                        print<>(true);     // print<bool>(bool) çýkarým yapar (template olmayan fonksiyonlar dikkate alýnmaz) -- 1'i yazdýrýr
                        std::cout << '\n';

                        print(true);       // print(bool) çaðýrýr -- true'yi yazdýrýr
                        std::cout << '\n';

                        return 0;
                    }

*** BEST -> Fonksiyon þablonundan türetilen bir fonksiyonu çaðýrýrken normal fonksiyon çaðrýsý sözdizimini tercih edin (eþleþen bir þablon olmayan 
fonksiyonu geçerli bir durumda tercih etmeniz gerekmiyorsa).

genellikle bir þablon fonksiyonundan türetilmiþ bir fonksiyonun yanýnda ayný parametrelerle çalýþan bir þablon olmayan fonksiyonun bulunma olasýlýðýnýn 
düþük olduðudur. Eðer böyle bir durum varsa ve þablondan türetilmiþ fonksiyonun spesifik durumlarý kontrol etmek için yazýlmýþsa, o durumda normal
fonksiyon çaðrýsý daha mantýklýdýr.

Ayrýca, eðer þablon olmayan bir fonksiyon mevcut deðilse, yani sadece þablondan türetilen bir fonksiyon varsa, normal fonksiyon çaðrýsý yapmak yine 
ayný sonuca yol açacaktýr. Çünkü derleyici, o parametrelerle çaðrýlan fonksiyon için þablondan çýkarým yaparak uygun þablon türlerini belirleyecek
ve fonksiyonu ona göre üretecektir.

Non-template parametreler ile Fonksiyon templateleri
----------------------------------------------------

Non-template parametreler içeren fonksiyon þablonlarý oluþturmak mümkündür. Tür þablon parametreleri herhangi bir türle eþleþtirilebilir ve 
non-template parametreler, normal fonksiyonlarýn parametreleri gibi çalýþýr.

Örneðin:

                    // T, bir tür þablon parametresidir
                    // double, bir þablon olmayan parametredir
                    template <typename T>
                    int birFonksiyon(T, double)
                    {
                        return 5;
                    }

                    int main()
                    {
                        birFonksiyon(1, 3.4); // someFcn(int, double) ile eþleþir
                        birFonksiyon(1, 3.4f); // someFcn(int, double) ile eþleþir -- float bir double'a dönüþtürülür
                        birFonksiyon(1.2, 3.4); // someFcn(double, double) ile eþleþir
                        birFonksiyon(1.2f, 3.4); // someFcn(float, double) ile eþleþir
                        birFonksiyon(1.2f, 3.4f); // someFcn(float, double) ile eþleþir -- float bir double'a dönüþtürülür

                        return 0;
                    }

Bu fonksiyon þablonunun þablonlanmýþ ilk parametresi bulunmakla birlikte, ikinci parametre türi double olarak sabittir. Geri dönüþ türünün de herhangi
bir tür olabileceðini unutmayýn. Bu durumda, fonksiyonumuz her zaman bir int deðeri döndürecektir.

Örneklenmiþ fonksiyonlar her zaman derlenmeyebilir 
--------------------------------------------------
Þu programa göz atalým:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }
Derleyici bunu etkili bir þekilde derleyip yürütecektir:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x);

                    template<>
                    int addOne<int>(int x)
                    {
                        return x + 1;
                    }

                    template<>
                    double addOne<double>(double x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne(1) << '\n';   // addOne<int>(int) fonksiyonunu çaðýrýr
                        std::cout << addOne(2.3) << '\n'; // addOne<double>(double) fonksiyonunu çaðýrýr

                        return 0;
                    }
Çýktý olarak ise:   2
                    3.3 
çýktýlarýný verir 
Peki ya böyle bir þey denersek? 

                    #include <iostream>
                    #include <string>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::string hello { "Hello, world!" };
                        std::cout << addOne(hello) << '\n';

                        return 0;
                    }

Derleyici, addOne(hello) ifadesini çözmeye çalýþtýðýnda addOne(std::string) için þablon olmayan bir fonksiyon eþleþmesi bulamayacak, ancak addOne(T) 
için fonksiyon þablonumuzu bulacak ve ondan addOne(std::string) fonksiyonunu üretebileceðini belirleyecektir. Bu nedenle, derleyici þunu üretecek ve
derleyecektir:

                    #include <iostream>
                    #include <string>

                    template <typename T>
                    T addOne(T x);

                    template<>
                    std::string addOne<std::string>(std::string x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::string hello{ "Hello, world!" };
                        std::cout << addOne(hello) << '\n';

                        return 0;
                    }

Ancak, bu, bir std::string türünde bir argümanla addOne() çaðýrmak mantýklý olmadýðý için derleme hatasý üretecektir. Burada açýk bir çözüm,
basitçe addOne()'ý std::string türünde bir argümanla çaðýrmamaktýr.

Örneklenmiþ fonksiyonlar her zaman anlamsal olarak anlamlý olmayabilir
----------------------------------------------------------------------

Derleyici, bir fonksiyon þablonunu baþarýyla derler, bu süreç, sentaktik olarak anlamlý olduðu sürece gerçekleþir. Ancak, derleyicinin böyle bir iþlemin 
semantik olarak anlamlý olup olmadýðýný kontrol etme yeteneði yoktur.

Örneðin:

                    #include <iostream>

                    template <typename T>
                    T addOne(T x)
                    {
                        return x + 1;
                    }

                    int main()
                    {
                        std::cout << addOne("Hello, world!") << '\n';

                        return 0;
                    }

Bu örnekte, bir C tarzý dize literali üzerinde addOne()'ý çaðýrýyoruz. Bu semantik olarak ne anlama geliyor? Kim bilir!

Þaþýrtýcý bir þekilde, C++ sentaktik olarak bir tamsayý deðerini bir dize literaliyle toplamaya izin verdiði için (bu konuyu ileriki ders 17.9'da ele 
alacaðýz - Ýþaretçi aritmetiði ve indeksleme), yukarýdaki örnek derlenir ve aþaðýdaki sonucu üretir:

              Çýktý: ello, world!

Uyarý

Derleyici, semantik olarak anlamlý olmayan fonksiyon þablonlarýný sentaktik olarak geçerli olduklarý sürece anýnda oluþturacak ve derleyecektir. Bu tür 
fonksiyon þablonlarýný anlamlý argümanlarla çaðýrdýðýnýzdan emin olmak sizin sorumluluðunuzdadýr.

Birden çok dosyada Fonksiyon þablonlarýný kullanma
--------------------------------------------------

Aþaðýdaki programý düþünün, bu program doðru çalýþmaz:

main.cpp: 
                    #include <iostream>

                    template <typename T>
                    T addOne(T x); // function template forward declaration

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }
add.cpp:
                    template <typename T>
                    T addOne(T x) // fonksiyon template tanýmý
                    {
                        return x + 1;
                    }

Eðer addOne bir þablon olmayan bir fonksiyon olsaydý, bu program sorunsuz çalýþacaktý: main.cpp'de derleyici addOne'ýn ileri bildiriminden memnun
olacak ve baðlayýcý, main.cpp'deki addOne() çaðrýsýný add.cpp'deki fonksiyon tanýmýna baðlayacaktý.

Ancak addOne bir þablon olduðu için, bu program çalýþmaz ve bir baðlayýcý hatasý alýrýz:

1>Project6.obj : error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main
1>Project6.obj : error LNK2019: unresolved external symbol "double __cdecl addOne<double>(double)" (??$addOne@N@@YANN@Z) referenced in function _main

main.cpp'de addOne<int> ve addOne<double> çaðýrýyoruz. Ancak, derleyici fonksiyon þablonu addOne'ýn tanýmýný göremediði için, bu fonksiyonlarý main.cpp 
içinde özelleþtiremez. Ancak addOne için ileri bildirimi görür ve bu fonksiyonlarýn baþka bir yerde var olduðunu ve daha sonra baðlanacaklarýný varsayar.

Derleyici add.cpp'yi derlerken, fonksiyon þablonu addOne'ýn tanýmýný görecek. Ancak, add.cpp'de bu þablonun kullanýldýðý bir yer olmadýðýndan,
derleyici hiçbir þey özelleþtirmeyecektir. Sonuç olarak, baðlayýcý, addOne<int> ve addOne<double> çaðrýlarýný main.cpp'de gerçek fonksiyonlara
baðlayamaz, çünkü bu fonksiyonlar hiçbir zaman özelleþtirilmedi.

Yaný sýra...

Eðer add.cpp, bu fonksiyonlarý özelleþtirmiþ olsaydý, program sorunsuz derlenir ve baðlanýrdý. Ancak, bu tür çözümler kýrýlgandýr ve kaçýnýlmalýdýr: 
eðer add.cpp'deki kod daha sonra bu fonksiyonlarý özelleþtirmiyorsa, program yeniden baðlantýda baþarýsýz olacaktýr. Ya da main.cpp add.cpp'de 
özelleþtirilmemiþ olan baþka bir addOne sürümünü (örneðin addOne<float>) çaðýrsaydý, yine ayný sorunla karþýlaþýrýz.

Bu sorunu çözmenin en geleneksel yolu, tüm þablon kodunuzu kaynak (.cpp) dosyasý yerine baþlýk (.h) dosyasýna koymaktýr:

add.h:
                    #ifndef ADD_H
                    #define ADD_H

                    template <typename T>
                    T addOne(T x) // Fonksiyon template tanýmý
                    {
                        return x + 1;
                    }

                    #endif
main.cpp:
                    #include "add.h" // Fonksiyon template tanýmýný içeri aktarýrýz
                    #include <iostream>

                    int main()
                    {
                        std::cout << addOne(1) << '\n';
                        std::cout << addOne(2.3) << '\n';

                        return 0;
                    }

Bu þekilde, þablona eriþim saðlamasý gereken herhangi bir dosya ilgili baþlýk dosyasýný #include edebilir ve þablon tanýmý ön iþlemci tarafýndan 
kaynak dosyasýna kopyalanacaktýr. Derleyici, ardýndan gereken herhangi bir fonksiyona özelleþtirebilecektir.

Bunu neden bir taným ihlali (ODR) oluþturmaz soruyor olabilirsiniz. ODR, türlerin, þablonlarýn, iç içe fonksiyonlarýn ve iç içe deðiþkenlerin farklý
dosyalarda ayný tanýma sahip olmalarýna izin verildiðini söyler. Bu nedenle, þablon tanýmýnýn birden çok dosyaya kopyalanmasý bir sorun teþkil etmez 
(her tanýmýn ayný olmasý koþuluyla).

Ancak özelleþtirilmiþ fonksiyonlar kendileri ne olacak? Eðer bir fonksiyon birden çok dosyada özelleþtirilirse, bu ODR'nin ihlaline yol açmaz mý? Cevap, 
þablondan önceden özelleþtirilmiþ fonksiyonlarýn dolaylý olarak olarak inline olduðudur. Ve bildiðiniz gibi,inline fonksiyonlar, tanýmýn her birinde ayný 
olduðu sürece birden çok dosyada tanýmlanabilir.

Temel Bilgi

Þablon tanýmlarý, sadece program baþýna tek bir tanýma izin veren tek bir tanýma kuralýnýn bu kýsmýndan muaf tutulmuþtur, bu nedenle ayný þablon
tanýmýnýn birden çok kaynak dosyasýna #include edilmesi sorun oluþturmaz. Fonksiyon þablonlarýndan dolaylý olarak olarak özelleþtirilen 
fonksiyonlar ise dolaylý olarak olarak inlinedir, bu nedenle her tanýmýn ayný olmasý koþuluyla birden çok dosyada tanýmlanabilir.

Þablonlar kendileri iç içe deðildir, çünkü iç içe kavramý yalnýzca deðiþkenler ve fonksiyonlar için geçerlidir.

Ýþte bir baþka örnek, bir baþlýk dosyasýna yerleþtirilen bir fonksiyon þablonu, böylece birden çok kaynak dosyaya dahil edilebilir:

max.h:
                    #ifndef MAX_H
                    #define MAX_H

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    #endif
foo.cpp:
                    #include "max.h" // max<T>(T, T) için þablon tanýmýný içe aktar
                    #include <iostream>

                    void foo()
                    {
                        std::cout << max(3, 2) << '\n';
                    }
main.cpp:
                    #include "max.h" // max<T>(T, T) için þablon tanýmýný içe aktar
                    #include <iostream>

                    void foo(); // fonksiyon foo için ileri bildirim

                    int main()
                    {
                        std::cout << max(3, 5) << '\n';
                        foo();

                        return 0;
                    }
Yukarýdaki örnekte, hem main.cpp hem de foo.cpp "max.h" dosyasýný #include eder, bu nedenle her iki dosyadaki kod da max<T>(T, T) fonksiyon þablonundan
yararlanabilir.

*** BEST -> Birden çok dosyada ihtiyaç duyulan þablonlar, bir baþlýk dosyasýnda tanýmlanmalý ve ardýndan gerektiði yerde #include edilmelidir. Bu, 
            derleyicinin tam þablon tanýmýný görmesine ve þablonu gerektiðinde özelleþtirmesine olanak tanýr.

Generic Programlama
-------------------
Þablon türleri, herhangi bir gerçek türle deðiþtirilebileceðinden, þablon türleri bazen genel türler olarak adlandýrýlýr. Ve çünkü þablonlar belirli 
türlerden baðýmsýz olarak yazýlabilir, þablonlarla programlama bazen genel programlama ( jenerik programlama - generic programming )
olarak adlandýrýlýr. C++ genellikle türler ve tür denetimine odaklanýrken, genel programlama, algoritmalarýn mantýðý ve veri yapýlarýnýn tasarýmýna 
odaklanmamýza, tür bilgisiyle fazla ilgilenmeden çalýþmamýza olanak tanýr.


Sonuç

Bir kere þablon fonksiyon yazmayý alýþtýðýnýzda, gerçek türlerle olan fonksiyonlardan çok daha uzun sürmediðini fark edeceksiniz. Fonksiyon þablonlarý,
yazýlmasý ve bakýmý gereken kod miktarýný minimize ederek kod bakýmýný ve hatalarý önemli ölçüde azaltabilir.

Fonksiyon þablonlarýnýn birkaç dezavantajý bulunmaktadýr ve bunlarý belirtmemek olmaz. Ýlk olarak, derleyici, her benzersiz argüman tür kümesi ile 
yapýlan her fonksiyon çaðrýsý için bir fonksiyon oluþturacaktýr (ve derleyecektir). Bu nedenle, fonksiyon þablonlarý yazmak kompakt olsa da, 
çýlgýnca miktarda kod haline gelebilir, bu da kod þiþmesine ve yavaþ derleme sürelerine neden olabilir. Fonksiyon þablonlarýnýn daha büyük bir 
dezavantajý, genellikle çýlgýnca görünen, sýnýrlý okunabilir hata mesajlarý üretmeye eðilimli olmalarýdýr ve bunlar düzenli fonksiyonlarýn hatalarýndan
çok daha zor çözülebilir. Bu hata mesajlarý oldukça korkutucu olabilir, ancak size ne anlatmaya çalýþtýklarýný anladýðýnýzda, iþaret ettikleri 
sorunlarýn genellikle oldukça basit çözümlere sahip olduðunu göreceksiniz.

Bu dezavantajlar, þablonlarýn programlama araç setinize getirdiði güç ve güvenlikle karþýlaþtýrýldýðýnda oldukça küçüktür, bu nedenle herhangi bir 
yerde tür esnekliðine ihtiyaç duyuyorsanýz þablonlarý özgürce kullanýn!

**** Ýyi bir kural, önce normal fonksiyonlar oluþturmak, sonra farklý parametre türleri için bir aþýrý yüklemeye ihtiyaç duyarsanýz bunlarý fonksiyon
     þablonlarýna dönüþtürmektir.

*** BEST -> Ýhtiyaç duyduðunuz her yerde geniþ bir tür yelpazesiyle çalýþabilen genel kod yazmak için fonksiyon þablonlarýný kullanýn.


10.17 — Birden Çok Þablon Türü Ýçeren Fonksiyon Þablonlarý
----------------------------------------------------------
Bir önceki derste yazdýðýmýz örneðin üzerinden devam edelim: 

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(1, 2) << '\n';   // max(int, int) ile örneklenecek
                        std::cout << max(1.5, 2.5) << '\n'; // max(double, double) ile örneklenecek

                        return 0;
                    }
Þimdi benzer bir programa bakalým:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';  // compile error

                        return 0;
                    }

Bu programýn derlenmeyeceðini görmek sizi þaþýrtabilir. Bunun yerine, derleyici bir dizi (muhtemelen çýlgýnca görünen) 
hata mesajý verecektir. Visual Studio'da, yazar þunlarý aldý:
                    Project3.cpp(11,18): error C2672: 'max': no matching overloaded function found
                    Project3.cpp(11,28): error C2782: 'T max(T,T)': template parameter 'T' is ambiguous
                    Project3.cpp(4): message : see declaration of 'max'
                    Project3.cpp(11,28): message : could be 'double'
                    Project3.cpp(11,28): message : or       'int'
                    Project3.cpp(11,28): error C2784: 'T max(T,T)': could not deduce template argument for 'T' from 'double'
                    Project3.cpp(4): message : see declaration of 'max'
    
Fonksiyon çaðrýmýmýz max(2, 3.5) ile iki farklý türde argümanlar geçiyoruz: biri int, diðeri double. Köþeli parantez kullanmadan bir fonksiyon çaðrýsý 
yapýyoruz çünkü gerçek bir tür belirtmiyoruz. Derleyici önce max(int, double) için þablon eþleþmesi olup olmadýðýný kontrol eder. Bulamaz.

Daha sonra, derleyici, template argument deduction kullanarak (ki bunu lesson 10.16 -- Function template instantiation bölümünde ele aldýk) bir 
fonksiyon þablonu eþleþmesi bulup bulamayacaðýný kontrol eder. Ancak bu da basit bir nedenle baþarýsýz olacaktýr: T, yalnýzca tek bir türü temsil
edebilir. T'nin, derleyicinin max<T>(T, T) fonksiyon þablonunu iki farklý parametre türüne sahip bir fonksiyona özelleþtirmesine izin verecek bir
türü yoktur. Baþka bir deyiþle, fonksiyon þablonundaki her iki parametre de T türündedir, bu nedenle ayný gerçek türe çözülmelidir.

Hiçbir þablon dýþý eþleþme bulunamadýðý ve hiçbir þablon eþleþmesi bulunamadýðý için, fonksiyon çaðrýsý çözülemiyor ve derleme hatasý alýyoruz.

Derleyicinin neden function max<double>(double, double) üretmediðini ve ardýndan int argümanýný double'a dönüþtürmek için sayýsal dönüþümü
kullanmadýðýný merak edebilirsiniz. Cevap basittir: tür dönüþümü, fonksiyon aþýrý yüklemeleri çözülürken yapýlýr, þablon argüman çýkarýmý yapýlýrken 
deðil.

Bu tür dönüþüm eksikliði en az iki nedenle kasýtlýdýr. Ýlk olarak, þeyleri basit tutmaya yardýmcý olur: ya fonksiyon çaðrý argümanlarý ile þablon tür
parametreleri arasýnda tam bir eþleþme buluruz, ya da bulamayýz. Ýkinci olarak, iki veya daha fazla parametrenin ayný türe sahip olmasýný istediðimiz
durumlar için fonksiyon þablonlarý oluþturmamýza izin verir (yukarýdaki örnekte olduðu gibi).

Bu sorunu (en azýndan) üç farklý þekilde çözebiliriz.

Argümanlarý eþleþen türlere dönüþtürmek için static_cast kullanýn
-----------------------------------------------------------------
Ýlk çözüm, çaðýranýn argümanlarý eþleþen türlere dönüþtürme yükünü taþýmasýný saðlamaktýr. Örneðin:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                       std::cout << max(static_cast<double>(2), 3.5) << '\n'; // int'i double'a dönüþtürerek max(double, double) fonksiyonunu çaðýrýyoruz

                       return 0;
                    }

Þimdi her iki argüman da double türünde olduðundan, derleyici bu fonksiyon çaðrýsýný karþýlayacak max(double, double) þablonunu özelleþtirebilecektir.

Ancak, bu çözüm sakar ve okunmasý zordur.

Açýkça bir tür þablon argümaný saðlamak
---------------------------------------
Eðer bir þablon olmayan max(double, double) fonksiyonu yazmýþ olsaydýk, o zaman max(int, double) çaðrýsýný yapabilir ve implicit tür dönüþüm
kurallarýnýn int argümanýmýzý double'a dönüþtürmesine izin verebilirdik, böylece fonksiyon çaðrýsý çözülebilirdi:

                    #include <iostream>

                    double max(double x, double y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n'; // argüman int türünden double türüne çevrilecekti.

                        return 0;
                    }

Ancak, derleyici þablon argüman çýkarsamasý yaparken herhangi bir tür dönüþümü yapmaz. Neyse ki, belirli bir tür þablon argümaný belirlediðimizde þablon
argüman çýkarsamasýný kullanmak zorunda deðiliz:

                    #include <iostream>

                    template <typename T>
                    T max(T x, T y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        // Türü açýkça double olarak belirttiðimizden dolayý, derleyici þablon argüman çýkarsamasýný kullanmayacak
                        std::cout << max<double>(2, 3.5) << '\n';

                        return 0;
                    }

Yukarýdaki örnekte, max<double>(2, 3.5) çaðrýsýný yaparýz. T'nin açýkça double ile deðiþtirilmesini belirttiðimiz için, derleyici þablon argüman
çýkarsamasýný kullanmayacak. Bunun yerine, sadece max<double>(double, double) fonksiyonunu özelleþtirecek ve ardýndan türleri eþleþmeyen argümanlarý
tür dönüþtürecektir. int parametremiz otomatik olarak bir double'a dönüþtürülacaktýr.

Bu, static_cast kullanmaktan daha okunaklý olsa da, max fonksiyonini çaðýrýrken hiç türleri düþünmememiz daha da güzel olurdu.

Birden fazla þablon tür parametresine sahip fonksiyon þablonlarý
----------------------------------------------------------------

Problemin kökeni, fonksiyon þablonumuz için yalnýzca tek bir þablon türünü (T) tanýmlamýþ olmamýz ve ardýndan her iki parametrenin de bu ayný türde 
olmasý gerektiðini belirtmiþ olmamýzdýr.

Bu sorunu çözmenin en iyi yolu, parametrelerimizin farklý türlere çözümlenebileceði bir þekilde fonksiyon þablonumuzu yeniden yazmaktýr. 
Artýk yalnýzca bir þablon türü parametresi (T) kullanmak yerine iki parametre kullanacaðýz (T ve U):

                    #include <iostream>

                    template <typename T, typename U> // Ýki tane T ve U adýnda þablon tür parametresi kullanýyoruz
                    T max(T x, U y) // x, T türüne çözümlenebilir ve y, U türüne çözümlenebilir
                    {
                        return (x < y) ? y : x; // burada bir daralma dönüþüm problemimiz var
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';

                        return 0;
                    }

Çünkü x'i þablon türü T ile ve y'yi þablon türü U ile tanýmladýk, x ve y þimdi baðýmsýz bir þekilde türlerini çözebilirler. max(2, 3.5) çaðrýsýný 
yaptýðýmýzda, T bir int ve U bir double olabilir. Derleyici, bizim için max<int, double>(int, double) türünü seve seve özümserecektir.

Ancak yukarýdaki kodun hala bir sorunu var: normal aritmetik kurallarý (10.5 - Aritmetik dönüþümler) kullanarak, double int'in üstünlüðünü alýr, 
bu nedenle koþullu operatörümüz bir double döndürecektir. Ancak fonksiyonumuz bir T döndürme þeklinde tanýmlanmýþtýr - T bir int'e çözündüðü durumlarda,
double döndürme deðerimiz bir int'e daraltma dönüþümüne uðrayacaktýr, bu da bir uyarýya (ve veri kaybýna) neden olabilir.

Dönüþ türünü U olarak yapmak da sorunu çözmez, çünkü T ve U'nun türlerini yer deðiþtirebileceðimiz bir durumda, türlerin sýrasýný deðiþtirebiliriz.

Bu sorunu nasýl çözebiliriz? Bu durum için otomatik dönüþ türü harika bir kullaným örneðidir - derleyiciye dönüþ türünün ne olmasý gerektiðini dönen 
ifadeden çýkarsamasýna izin vereceðiz.

                    #include <iostream>

                    template <typename T, typename U>
                    auto max(T x, U y)
                    {
                        return (x < y) ? y : x;
                    }

                    int main()
                    {
                        std::cout << max(2, 3.5) << '\n';

                        return 0;
                    }

Bu versiyonu ile max fonksiyonu, farklý türlerdeki iþlemlerle sorunsuz bir þekilde çalýþýr.


Kilit nokta

Her þablon tür parametresi, türünü baðýmsýz bir þekilde çözer.

Bu, T ve U adlý iki tür parametresine sahip bir þablonun T ve U'nun farklý türlerle çözünebileceði anlamýna gelir, veya ayný türe çözünebilirler.


Kýsaltýlmýþ fonksiyon þablonlarý
--------------------------------
C++20, `auto` anahtar kelimesinin yeni bir kullanýmýný tanýtýyor: Auto anahtar kelimesi, normal bir fonksiyonda bir parametre türü olarak 
kullanýldýðýnda, derleyici otomatik olarak fonksiyonu, her `auto` parametresini baðýmsýz bir þablon tür parametresi haline getiren bir 
fonksiyon þablonuna dönüþtürecektir. Bu yöntemle oluþturulan fonksiyon þablonuna "kýsaltýlmýþ fonksiyon þablonu" denir.

Örneðin:
                    auto max(auto x, auto y)
                    {
                        return (x < y) ? y : x;
                    }

C++20'de aþaðýdakilerin kýsaltmasýdýr:

                    template <typename T, typename U>
                    auto max(T x, U y)
                    {
                        return (x < y) ? y : x;
                    }

Bu, yukarýda yazdýðýmýz max fonksiyon þablonuyla aynýdýr.

Her þablon tür parametresinin baðýmsýz bir tür olmasýný istediðiniz durumlarda, bu form tercih edilir çünkü þablon parametre bildirimi satýrýnýn 
kaldýrýlmasý, kodunuzu daha özlü ve okunabilir hale getirir.

Bir veya daha fazla `auto` parametresinin ayný türde olmasýný istediðinizde, kýsaltýlmýþ fonksiyon þablonlarýný kullanmanýn özlü bir yolu
bulunmamaktadýr. Yani, þöyle bir durum için kolayca kýsaltýlmýþ bir fonksiyon þablonu bulunmamaktadýr:

                    template <typename T>
                    auto max(T x, T y) // ayný türün iki parametresi
                    {
                        return (x < y) ? y : x;
                    }


Tek bir auto parametreli kýsaltýlmýþ fonksiyon þablonlarýný veya her auto parametresinin baðýmsýz bir tür olmasýný istediðiniz durumlarý 
(ve dil standartýnýz C++20 veya daha yeni sürümde ise) özgürce kullanabilirsiniz.

10.18 — Non-type ( Tür dýþý ) template parametreleri
----------------------------------------------------

Önceki derslerde, tür þablon parametrelerini kullanan fonksiyon þablonlarýný nasýl oluþturacaðýmýzý tartýþtýk. Bir tür þablon parametresi, bir þablon
argümaný olarak geçirilen gerçek bir tür için bir yer tutucu olarak görev yapar.

tür þablon parametreleri, þüphesiz ki kullanýlan en yaygýn þablon parametre türüdür; ancak bilinmesi gereken baþka bir tür de vardýr: tür dýþý þablon
parametresi.

Non-type template parametreleri
-------------------------------

tür dýþý bir þablon parametresi, bir þablon argümaný olarak geçirilen bir constexpr deðeri temsil eden sabit bir türe sahip bir þablon parametresidir.

tür dýþý bir þablon parametresi, aþaðýdaki türlerden herhangi biri olabilir:

* - Bir tamsayý türi
* - Bir numaralandýrma türi
* - std::nullptr_t
* - Bir kayan nokta türi (C++20'den itibaren)
* - Bir nesnenin iþaretçisi veya referansý
* - Bir fonksiyonin iþaretçisi veya referansý
* - Bir üye fonksiyonin iþaretçisi veya referansý
* - Bir literal sýnýf türi (C++20'den itibaren)

Ýlk tür dýþý þablon parametresi örneðimizi, std::bitset'i ele aldýðýmýz O.1 dersinde gördük:

                    #include <bitset>

                    int main()
                    {
                        std::bitset<8> bits{ 0b0000'0101 }; // <8> bir non-type template parameteresidir

                        return 0;
                    }

(C++'ta) std::bitset örneðinde, tür dýþý þablon parametresi, std::bitset'e kaç bit saklamak istediðimizi bildirmek için kullanýlýr.

Kendi non-type template parametrelerimizi tanýmlama
---------------------------------------------------
Ýþte bir int türinde tür dýþý þablon parametresi kullanan basit bir fonksiyon örneði:

                    #include <iostream>

                    template <int N> // int türünde N isminde bir tür dýþý þablon parametresi tanýmla
                    void print()
                    {
                        std::cout << N << '\n'; // N'nin deðerini burada kullan
                    }

                    int main()
                    {
                        print<5>(); // 5, tür dýþý þablon argümanýmýzdýr

                        return 0;
                    }
          Çýktýmýz: 5

Satýr 3'te, þablon parametre deklarasyonumuzu bulunmaktadýr. Dik açýlý parantezler içinde, int türünde bir deðerin yerine konulacaðý bir tür dýþý
þablon parametresi olan N'yi tanýmlýyoruz. print() fonksiyonu içinde, N'nin deðerini kullanýyoruz.

Satýr 11'de, print() fonksiyonunu çaðýrýyoruz ve bunun için tür dýþý þablon argümaný olarak int türünde 5 deðerini kullanýyoruz. Derleyici bu 
çaðrýyý gördüðünde, aþaðýdaki gibi bir fonksiyonu özel olarak oluþturacaktýr:

                    template <>
                    void print<5>()
                    {
                        std::cout << 5 << '\n';
                    }

Çalýþma zamanýnda, bu fonksiyon `main()` fonksiyonundan çaðrýldýðýnda, 5'i ekrana yazdýrýr.

Ardýndan program sona erer. Oldukça basit, deðil mi?

Genellikle T, ilk tür þablon parametresi için kullanýldýðý gibi, N de bir int tür dýþý þablon parametresinin adý olarak yaygýn olarak kullanýlýr.

*** BEST -> N'yi bir int tür dýþý þablon parametresinin adý olarak kullanýn.

tür dýþý þablon parametreleri ne iþe yarar?
-------------------------------------------

C++20'den itibaren, Fonksiyon parametreleri `constexpr` olamaz. Bu durum, normal fonksiyonlar için geçerli olduðu gibi, `constexpr` fonksiyonlar için
de doðrudur (çünkü bunlar çalýþma zamanýnda çalýþtýrýlabilir olmalýdýr) ve belki de þaþýrtýcý bir þekilde,`consteval` fonksiyonlar için bile 
geçerlidir.

Dolayýsýyla, þöyle bir fonksiyonumuz olduðunu düþünelim:

                    #include <cassert>
                    #include <cmath> // std::sqrt için
                    #include <iostream>

                    double getSqrt(double d)
                    {
                        assert(d >= 0.0 && "getSqrt(): d must be non-negative");

                        if (d >= 0)
                            return std::sqrt(d);

                        return 0.0;
                    }

                    int main()
                    {
                        std::cout << getSqrt(5.0) << '\n';
                        std::cout << getSqrt(-5.0) << '\n';

                        return 0;
                    }


Çalýþtýrýldýðýnda, getSqrt(-5.0) çaðrýsý çalýþma zamanýnda bir assert hatasý üretecektir. Bu, hiç olmamasýndan daha iyidir, çünkü -5.0 bir sabit 
(ve dolaylý olarak constexpr olarak kabul edilir), ancak bu hatanýn derleme zamanýnda yakalanabilmesi için static_assert kullanmak daha iyi olacaktýr.
Ancak, static_assert bir sabit ifade gerektirir ve fonksiyon parametreleri constexpr olamaz...

Ancak, fonksiyon parametresini bir tür olmayan þablona dönüþtürürsek, istediðimizi tam olarak yapabiliriz:

                    #include <cmath> // std::sqrt
                    #include <iostream>

                    template <double D> // kayan noktalý olmayan tür þablon parametresi için c++20 gereklidir
                    double getSqrt()
                    {
                        static_assert(D >= 0.0, "getSqrt(): D negatif olamaz");

                        if constexpr (D >= 0) // Bu örnekte constexpr'ý görmezden gelebiliriz
                            return std::sqrt(D); // Garip bir þekilde, std::sqrt C++26'ya kadar bir constexpr fonksiyon deðil

                        return 0.0;
                    }

                    int main()
                    {
                        std::cout << getSqrt<5.0>() << '\n';   // Geçerli, karekökü hesaplar ve yazdýrýr.
                        std::cout << getSqrt<-5.0>() << '\n';  // Hata: Derleme zamanýnda bir assert hatasý üretecek.

                        return 0;
                    }

Bu sürüm derlenemeyecek. Derleyici, `getSqrt<-5.0>()` çaðrýsýný karþýlaþtýðýnda, þu þekilde bir fonksiyoni örnekleyip çaðýracaktýr:

                    template <>
                    double getSqrt<-5.0>()
                    {
                        static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

                        if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
                            return std::sqrt(-5.0);

                        return 0.0;
                    }

static_assert koþulu yanlýþ olduðu için, derleyici bu durumu kontrol eder ve uyarýda bulunur.

Kilit nokta
-----------
Non-type template parametreleri, bir sabit ifadeye ihtiyaç duyan baðlamlarda kullanýlacak constexpr deðerlerini fonksiyonlara (veya sýnýf türlerine) 
iletmek için kullanýlýr.

std::bitset sýnýf türü, depolanacak bit sayýsýný belirtmek için bir non-type template parametresi kullanýr çünkü bit sayýsý bir constexpr deðeri
olmalýdýr.

Yazarýn Notu

Fonksiyon parametrelerinin constexpr olamamasý kýsýtlamasýný atlatmak için non-type template parametrelerini kullanmak pek ideal deðil. Bu tür 
durumlarý ele almaya yönelik birçok farklý öneri deðerlendiriliyor. Gelecekteki bir C++ dil standardýnda bu tür durumlar için daha iyi bir çözüm
görebileceðimizi düþünüyorum.
    
Non-type template arguments için örtük dönüþümler
-------------------------------------------------
Bazý non-type template argümanlarý, farklý bir türün non-type template parametresine uymak için örtük dönüþümlere tabi tutulabilir. Örneðin:

                    #include <iostream>

                    template <int N> // int non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // Hiçbir dönüþüm gerekmez
                        print<'c'>(); // 'c' tipindeki deðer int'e dönüþtürülür, 99 yazdýrýr

                        return 0;
                    }
Çýktýsý: 
                    5
                    99
Yukarýdaki örnekte, 'c', print() fonksiyon þablonunun non-type template parametresine uymak için int'e dönüþtürülür, ardýndan deðer int olarak yazdýrýlýr.

Bu baðlamda, yalnýzca belirli türlerde constexpr dönüþümlere izin verilir. En yaygýn izin verilen dönüþüm türleri þunlarý içerir:

- Tamsayý promosyonlarý (örneðin, char'tan int'e)
- Tamsayý dönüþümleri (örneðin, char'dan long veya int'e)
- Kullanýcý tanýmlý dönüþümler (örneðin, belirli bir program tarafýndan tanýmlanan bir sýnýfýn int'e dönüþtürülmesi)
- Lvalue'den rvalue'ye dönüþümler (örneðin, bazý deðiþken x'in x'in deðerine dönüþtürülmesi)

Bu liste, listeleme baþlatma için izin verilen örtük dönüþüm türlerinden daha az hoþgörülüdür. Örneðin, bir constexpr int kullanarak bir double 
türündeki bir deðiþkeni liste baþlatmak mümkündür, ancak constexpr int non-type template argümaný bir double non-type template parametresine 
dönüþmeyecektir.

Ýzin verilen tüm dönüþümlerin tam listesine buradan ulaþabilirsiniz, "Converted constant expression" alt bölümünde bulunabilir.

Normal fonksiyonlarde olduðu gibi, fonksiyon þablon çaðrýlarýný fonksiyon þablon tanýmlarýyla eþleþtirmek için kullanýlan algoritma karmaþýk deðildir ve
belirli dönüþüm türüne (veya olmamasýna) dayalý olarak diðerlerine öncelik vermez. Bu, bir fonksiyon þablonunun farklý türde non-type template
parametreleri için aþýrý yüklendiðinde, çok kolay bir belirsiz eþleþme sonucuna yol açabilir.

                    #include <iostream>

                    template <int N> // int non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    template <char N> // char non-type template parameter
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // Belirsiz eþleþme: int N = 5 ve char N = 5 ile uyuþan iki versiyon olduðu için
                        print<'c'>(); // Belirsiz eþleþme: int N = 99 ve char N = 'c' ile uyuþan iki versiyon olduðu için

                        return 0;
                    }

Beklenmedik bir þekilde, print() fonksiyonuna yapýlan her iki çaðrý da belirsiz eþleþmelere neden olur.

'auto' kullanarak non-type template parametreleri için tür çýkarsama
------------------------------------------------------------------
C++17'den itibaren, non-type template parametreleri, derleyicinin template argümanýndan non-type template parametresini çýkarmasý için auto kullanabilir:

                    #include <iostream>

                    template <auto N> // template argümanýndan non-type template parametresini çýkarmak için auto kullanýlýr
                    void print()
                    {
                        std::cout << N << '\n';
                    }

                    int main()
                    {
                        print<5>();   // N, int `5` olarak çýkarýlýr
                        print<'c'>(); // N, char `c` olarak çýkarýlýr

                        return 0;
                    }
Bu, beklenen sonucu derler ve üretir:   
                    5
                    c

Baþardýn! Bu bölümdeki konular (özellikle tür takma adlarý, aþýrý yüklenmiþ iþlevler ve iþlev þablonlarý) C++ standart kitaplýðýnýn her yerinde görünür.
Artýk her þeyin nasýl çalýþtýðýný anlamaya bir adým daha yaklaþtýnýz!
*/
/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                     GENEL ÖZET

Bir deðeri bir veri türünden baþka bir veri türüne dönüþtürme sürecine "tip dönüþümü" denir.

Otamatik tip dönüþümü veya zorlamasý olarak da adlandýrýlan içsel tip dönüþümü, bir veri türü beklenirken, farklý bir veri türü saðlandýðýnda 
gerçekleþir. Derleyici, iki tür arasýndaki dönüþümü nasýl gerçekleþtireceðini anlayabiliyorsa, bu dönüþümü gerçekleþtirir. Bilmiyorsa, derleme hatasý
ile baþarýsýz olur.

C++ dilinde, temel türleri arasýnda (ve bazý geliþmiþ türler için birkaç dönüþüm) tanýmlanan standart dönüþümler adý verilen bir dizi yerleþik dönüþüm
bulunmaktadýr. Bunlar sayýsal yükseltmeleri, sayýsal dönüþümleri ve aritmetik dönüþümleri içerir.

Sayýsal yükseltme, belirli küçük sayýsal türlerin belirli büyük sayýsal türlere (genellikle int veya double) dönüþtürülmesidir, böylece CPU, iþlemcinin
doðal veri boyutuna uyan veri üzerinde çalýþabilir. Sayýsal yükseltmeler, hem tamsayý yükseltmelerini hem de kayan nokta yükseltmelerini içerir. 
Sayýsal yükseltmeler, deðeri koruyan yani deðer veya hassasiyet kaybý olmayan dönüþümlerdir. Tüm geniþletme dönüþümleri yükseltme deðildir.

Sayýsal dönüþüm, sayýsal bir yükseltme olmayan temel türler arasýndaki bir tür dönüþümüdür. Daraltma dönüþümü, deðer veya hassasiyet kaybýna neden 
olabilecek bir sayýsal dönüþümdür.

C++'da, bazý ikili operatörlerin operanlarýnýn ayný türden olmasýný gerektirdiði durumlar vardýr. Farklý türlerden operatörler saðlanýrsa, operanlardan
biri veya her ikisi de genel aritmetik dönüþümler adý verilen bir dizi kuralý kullanarak eþleþen türlere otomatik olarak dönüþtürülür.

Belirli bir veri türünden baþka bir veri türüne dönüþümü talep etmek için programcý tarafýndan açýkça istendiðinde açýk tip dönüþümü gerçekleþir.
Bir dönüþüm, programcýnýn açýkça bir tip dönüþümü yapýlmasýný talep ettiði bir istek olarak temsil eder. C++, C tarzý dönüþümler, static_cast, 
const_cast, dynamic_cast ve reinterpret_cast olmak üzere 5 tip dönüþümü destekler. Genellikle C tarzý dönüþümlerden, const dönüþümlerden ve reinterpret 
dönüþümlerinden kaçýnýlmalýdýr. static_cast, bir türden baþka bir türe bir deðeri dönüþtürmek için kullanýlýr ve C++'taki en yaygýn kullanýlan
dönüþümdür.

Typedef'ler ve tip takma adlarý, programcýnýn bir veri türü için bir takma ad oluþturmasýna olanak tanýr. Bu takma adlar yeni türler deðildir ve takma 
adlandýrýlan türle ayný þekilde davranýr. Typedef'ler ve tip takma adlarý, herhangi bir tür güvenliði saðlamaz ve takma adýn asýl türden farklý 
olduðunu varsaymamak önemlidir.

auto anahtar kelimesinin birkaç kullanýmý vardýr. Ýlk olarak, auto, bir deðiþkenin türünü baþlatýcýsýndan çýkaracak olan tür çýkarsama (ayný zamanda 
tür çýkarsama olarak da adlandýrýlýr) için kullanýlabilir. Tür çýkarsama, const ve referanslarý düþürür, bu nedenle bunlarý geri eklemek istiyorsanýz 
eklemelisiniz.

Auto ayrýca bir fonksiyonun dönüþ türünü belirlemek için de kullanýlabilir. Ancak bu, normal fonksiyonlar için kaçýnýlmasý gereken bir durumdur. Auto,
takip eden return sözdizimi kýsmýnýn bir parçasý olarak kullanýlýr.

Fonksiyon aþýrý yükleme, ayný isme sahip birden çok fonksiyon oluþturmamýza olanak tanýr, adý geçen fonksiyonlarýn her biri farklý bir parametre türü 
setine sahip olmalýdýr (veya fonksiyonlar baþka þekilde ayýrt edilebilmelidir). Böyle bir fonksiyon bir aþýrý yüklenmiþ fonksiyon (veya kýsaca aþýrý
yükleme) olarak adlandýrýlýr. Döndürme türleri farklýlaþtýrma için kullanýlmaz.

Aþýrý yüklü fonksiyonlarý çözerken, eðer tam eþleþme bulunamazsa, derleyici sayýsal yükseltmeleri gerektiren aþýrý yüklenmiþ fonksiyonlarý, 
gerektirmeyenlere göre tercih eder. Bir iþlev çaðrýsý, aþýrý yüklenmiþ bir iþleve eþleþmesi için kullanýlan argümanlara dayanarak uygun aþýrý yüklenmiþ
iþlevi bulmaya çalýþýr. Buna aþýrý yük çözümleme denir.

Belirli bir iþlev çaðrýsý çözümlenirken, aþýrý yüklenmiþ iþlevlerden eþleþen biri bulunamazsa, derleyici sayýsal yükseltme gerektiren aþýrý yüklenmiþ
iþlevleri, gerektirmeyenlere göre tercih eder. Bir iþlev çaðrýsý yapýlýrken, derleyici, iþlev çaðrýsýnda kullanýlan argümanlara dayanarak uygun aþýrý 
yüklenmiþ iþlevi bulmaya çalýþýr. Buna aþýrý yük çözümleme denir.

Belirsiz bir eþleþme, derleyicinin bir iþlev çaðrýsýný bir aþýrý yüklenmiþ iþleve eþleþtirmek için iki veya daha fazla iþlev bulmasý durumunda ortaya
çýkar ve hangisinin en iyi olduðunu belirleyemez.

Varsayýlan bir argüman, bir iþlev parametresi için saðlanan bir varsayýlan deðerdir. Varsayýlan argümanlara sahip parametreler her zaman en saðda 
olmalýdýr ve aþýrý yüklenmiþ iþlevleri çözümlemede kullanýlmazlar.

Fonksiyon þablonlarý, ilgili fonksiyonlarý oluþturmak için bir þablon olarak hizmet eden bir fonksiyon benzeri tanýmý oluþturmamýza olanak tanýr. Bir 
fonksiyon þablonunda, daha sonra belirtilmesi istenen herhangi bir tür için tip þablon parametreleri olarak kullanýlýr. Derleyiciye bir þablon 
tanýmladýðýmýzda ve þablon türlerini bildirdiðimizde fonksiyonlarý oluþturma sürecine fonksiyon þablonu anlamýna gelen þablonun anlamýna gelir.

Fonksiyon þablonu çaðrýldýðýnda (fonksiyon þablonu argümanlarý belirtildiðinde), bu sürece fonksiyon þablonu anlamýna gelen anlamýna gelir. Bu süreç 
bir fonksiyon çaðrýsý nedeniyle gerçekleþirse, bu süreç 'örtük anlamlandýrma' olarak adlandýrýlýr ve örnekleme bir fonksiyon örneði (veya kýsacasý
bir örnek veya bazen bir þablon fonksiyonu) olarak adlandýrýlýr.

Þablon argüman çýkarsama, derleyicinin bir fonksiyon çaðrýsýnýn argümanlarýndan þablonun anlamýný çýkarma yeteneðidir. Þablon argüman çýkarsama, tip 
dönüþümü gerçekleþtirmez.

Þablon türleri bazen generic türler olarak adlandýrýlýr ve þablonlar kullanýlarak programlama bazen generic programlama olarak adlandýrýlýr.

C++20'de auto anahtar kelimesi, bir normal fonksiyonda bir parametre türü olarak kullanýldýðýnda, derleyici otomatik olarak her auto parametreyi 
baðýmsýz bir þablon tür parametre haline getirecek ve bunu yapmak için bu türde bir fonksiyon þablonu oluþturacaktýr. Bu yönteme kýsaltýlmýþ bir 
fonksiyon þablonu denir.

Bir non-type template parametresi, bir sabit ifade olarak bir þablon argümaný olarak iletilen bir sabit türüne sahip olan bir þablon parametresidir.




























*/