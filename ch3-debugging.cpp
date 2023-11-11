// ch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Quizler yapýlmýþ ama sanki bir atlama olmuþ burada o yüzden chapter 2  yi tekrar iþlicez ama quizleri yapmicaz sadece bi iþlicez not tutcaz.
// Önemli bir konu. 

#include <iostream>
//#include "add.h"

//int add(int x, int y);

int main() {

    //std::cout << add(4, 3) << '\n'; -> OLDU KARDEEEEÞ
    /*
    Ayný þekilde geçmiþ ve diðer bilgilerimizle ayný olduðu için yazmýyorum. Sadece bilmediðimi düþündüðüm þeyleri yazacam kral. 
    C++ baðlý fonksiyonlarý desteklemiyor yani bir fonksiyonun içinde yeni bir fonksiyon tanýmlayamazsýn. 

    Sanýrým bundan önceki sefer de de okumuþuz ama sadece not almamýþýz. Çünkü çoðunu biliyoruz. Hoþumuza giden ayrýntýlarý yazacaz sadece
    C++ 3 status code tanýmlýyor (main in dönüþü için) 0 , EXIT_SUCCESS, EXIT_FAILURE -> Taþýnabilirliði arttýrmak açýsýndan bunlarý kullanmak 
    lazým. 
    
    Dönüþ yapan fonksiyonlarda dönüþ yapmazsak tanýmlanamayan davranýþlar ortaya çýkabilir. 
    Fonksiyonlarda var olup kullanýlmayan parametreler uyarý verir. 

    Yerel deðiþkenler.
    Yerel deðiþkenlerinizi, ilk kullanacaklarý yere mümkün olduðunca yakýn bir þekilde tanýmlayýn.

                                        FONKSÝYONLARI ETKÝLÝ KULLANMAK
    Yeni programcýlarýn karþýlaþtýðý en büyük zorluklardan biri (dilin öðrenilmesi dýþýnda), ne zaman ve nasýl iþlevleri etkili bir
    þekilde kullanacaklarýný anlamaktýr. Ýþte iþlevler yazarken temel bazý kurallar:

    Bir programda birden fazla kez görünen ifade gruplarý genellikle bir iþlev haline getirilmelidir. Örneðin, kullanýcýdan giriþleri ayný 
    þekilde birden fazla kez alýyorsak, bu, bir iþlev için harika bir adaydýr. Ayný þekilde bir þeyi birden fazla yerde ayný þekilde çýkarýyorsak,
    bu da bir iþlev için mükemmel bir adaydýr.
    Belirli girdi ve çýktýlarý olan kod, bir iþlev için iyi bir adaydýr (özellikle karmaþýksa). Örneðin, sýralamak istediðimiz bir 
    öðeler listemiz varsa, sýralamayý yapmak için kod, yalnýzca bir kez yapýlsa bile harika bir iþlev olur. Giriþ sýralanmamýþ liste,
    çýkýþ sýralanmýþ listedir. Baþka bir olasý iþlev de 6 yüzlü bir zarýn atýlmasýný simüle eden kod olurdu. Mevcut programýnýz bunu
    yalnýzca bir kez kullanabilir, ancak iþlev haline getirirseniz, programýnýzý daha sonra geniþletirseniz veya gelecekteki bir programda
    yeniden kullanýma hazýr olur.
    Bir iþlev genellikle bir (ve yalnýzca bir) görevi yerine getirmelidir.
    Bir iþlev çok uzun, karmaþýk veya anlaþýlmasý zor hale geldiðinde, birden çok alt iþleve bölünebilir. Buna yeniden yapýlandýrma denir.
    Genellikle C++ öðrenirken, 3 alt görevi içeren programlar yazacaksýnýz:

    Kullanýcýdan giriþleri okuma
    Giriþlerden bir deðeri hesaplama
    Hesaplanan deðeri yazdýrma
    Basit programlar için (örneðin 20 satýrýn altýnda), bunlar ya da tümü main iþlevinde yapýlabilir. Ancak daha uzun programlar için
    (veya sadece pratiðin bir parçasý olarak), her biri ayrý bir iþlev için iyi bir adaydýr.
    
    Yeni programcýlar genellikle bir deðeri hesaplama ve hesaplanan deðeri yazdýrma iþlemlerini tek bir iþlevde birleþtirir. Bununla
    birlikte, bu iþlevlerin "bir görev" kuralýný ihlal ettiðini unuturlar. Bir iþlev, bir deðeri hesaplamalý ve hesaplanan deðeri çaðýran
    kiþiye döndürmeli ve hesaplanan deðeri yazmak gibi ne yapýlacaðýný belirlemeli (örneðin baþka bir iþleve çaðrýda bulunmak gibi) ve çaðýran
    kiþi hesaplanan deðeri yazmalýdýr.
    
    


    Programlarýnýzda derleme hatalarýný veya uyarýlarýný çözerken, önce listelenen ilk sorunu çözün ve ardýndan tekrar derleyin.

                                                FORWARD DECLARATION
    Bir ön deklarasyon, tanýmlayýcýyý tanýmlamadan önce tanýyýcý hakkýnda derleyiciye bilgi vermemizi saðlar.

    Fonksiyonlar için, bu, derleyiciye fonksiyonun varlýðý hakkýnda bilgi vermemize olanak tanýr, ancak fonksiyonun
    gövdesini tanýmlamadan önce. Bu þekilde, derleyici, bir fonksiyonu aradýðýmýzý anlayacaktýr. Fonksiyonun nasýl 
    veya nerede tanýmlandýðýný henüz bilmiyor olsa bile, fonksiyonu doðru bir þekilde çaðýrdýðýmýzý kontrol etmek için kullanabilir.

    Bir fonksiyon için bir ön deklarasyon yazmak için, bir fonksiyon deklarasyon ifadesi (ayný zamanda bir fonksiyon
    prototipi olarak da adlandýrýlýr) kullanýrýz. Fonksiyon deklarasyonu, fonksiyonun dönüþ türünü, adýný ve parametre
    türlerini içerir ve bir noktalý virgülle sona erer. Parametrelerin adlarý isteðe baðlý olarak dahil edilebilir. 
    Fonksiyon gövdesi deklarasyona dahil edilmez.
    


    Definition ve declaration ayný þey deðil tüm definition lar birer declarationdur fakat tüm declarationlar bir definition deðildir.
    Definition	Implements a function or instantiates a variable.
    Definitions are also declarations.	void foo() { } // function definition
    int x; // variable definition
    Declaration	Tells compiler about an identifier and its associated type information.	void foo(); // function declaration
    int x; // variable declaration
    Pure declaration	A declaration that isn’t a definition.	void foo();


                                            ***** The one definition rule (ODR) ******
    
    Tek Tanýmlama Kuralý (veya kýsaca ODR), C++ içinde iyi bilinen bir kuraldýr. ODR'nin üç bölümü vardýr:

    Bir dosya içinde, her bir fonksiyon, deðiþken, tür veya þablon sadece bir tanýma sahip olabilir. Farklý
    kapsamlarda (örneðin, farklý iþlevler içinde tanýmlanan yerel deðiþkenler veya farklý ad alanlar içinde
    tanýmlanan iþlevler) meydana gelen tanýmlar bu kuralý ihlal etmez.

    Bir program içinde, her bir fonksiyon veya deðiþken yalnýzca bir tanýma sahip olabilir. Bu kural, programlarýn 
    birden fazla dosyaya sahip olabileceði için var. Linker'a görünmeyen iþlevler ve deðiþkenler bu kuraldan hariç 
    tutulur (bu, ders 7.6'da daha ayrýntýlý olarak ele alýnýr).

    Türler, þablonlar, iç içe iþlevler ve iç içe deðiþkenler, her bir tanýmýn ayný olduðu sürece farklý dosyalarda
    yinelemeli tanýmlara sahip olabilir. Bu konularýn çoðunu henüz ele almadýk, bu nedenle þu an için bu konuyu dert
    etmeyin - ilgili olduðunda tekrar ele alacaðýz.

    ODR'nin 1. bölümünü ihlal etmek, derleyicinin yeniden tanýmlama hatasý vermesine neden olur. ODR'nin 2. bölümünü
    ihlal etmek, linkerin yeniden tanýmlama hatasý vermesine neden olur. ODR'nin 3. bölümünü ihlal etmek, tanýmsýz davranýþa neden olur.
                                            
    */

    /*
                                                PROJEYE DOSYA EKLEME
    Daha önce forward declaration ý anlatýrken mevzuya bi týkýrtý için add() fonksiyonunu örnek vermiþtik burada 
    farklý bir dosya üzerinden bakacak olursak yani add() fonksiyonunu farklý bir dosyaya koyduktan sonra çalýþtýrsak
    acaba hata alýr mýyýz ? Cevap evet burada da ayný cevabý alýrýz. Cpp add fonksiyonunun ne olduðunu bilmiyor.
    Oysa derlemiþtik. 
    Unutmayýn, derleyici her dosyayý ayrý ayrý derler. Diðer kod dosyalarýnýn içeriðini bilmez veya önceden
    derlenen kod dosyalarýnda gördüðü þeyleri hatýrlamaz. Yani, derleyici fonksiyon add'ýn tanýmýný daha 
    önce görmüþ olabilir (eðer önce add.cpp'yi derlediyse), ama hatýrlamaz.

    Bu sýnýrlý görünürlük ve kýsa bellek bilinçli olarak tasarlanmýþtýr ve birkaç nedeni vardýr:

   1 Bir projenin kaynak dosyalarýnýn herhangi bir sýrayla derlenmesine izin verir.
   2 Bir kaynak dosyasýný deðiþtirdiðimizde, yalnýzca o kaynak dosyasýnýn yeniden derlenmesi gerekir.
   3 Farklý dosyalardaki tanýmlayýcýlar arasýndaki isim çakýþmalarýnýn olasýlýðýný azaltýr.
    


    Sorunu yine forward declaration ile çözdük ama burada alman gereken key point þý 
    Bir tanýmlayýcý bir ifadede kullanýldýðýnda, tanýmlayýcý kendi tanýmýna baðlý olmalýdýr.

    Eðer derleyici, derlenmekte olan dosyada tanýmlayýcý için ne bir forward declaration ne de bir tanýmý daha görmemiþse, 
    tanýmlayýcý kullanýldýðý noktada hata verecektir.

    Eðer ayný dosyada bir taným mevcutsa, derleyici tanýmlayýcýnýn kullanýmýný tanýmýna baðlayacaktýr.

    Aksi takdirde, farklý bir dosyada bir taným mevcutsa (ve baðlayýcý için görünürse), baðlayýcý tanýmlayýcýnýn kullanýmýný tanýmýna baðlayacaktýr.
    Aksi takdirde, baðlayýcý hata verecektir.
    
    

    Birden fazla dosya ile çalýþmaya baþladýðýnýzda iþlerin ters gidebileceði pek çok durum olabilir.
    Yukarýdaki örneði denediyseniz ve bir hata ile karþýlaþtýysanýz, aþaðýdakileri kontrol edin:

    Eðer main.cpp dosyasýnda add iþlevi için önceden bildirimin eksik olduðu bir derleyici hatasý alýrsanýz,
    add iþlevi için önceden bildirimi unuttuðunuz olabilir.
    Eðer add iþlevi tanýmsýz olduðuna dair bir baðlayýcý hatasý alýrsanýz, örneðin:
    unresolved external symbol "int __cdecl add(int,int)" (?add@@YAHHH@Z) referenced in function _main

    2a. ... muhtemelen add.cpp dosyasýnýn projenize doðru þekilde eklenmediði anlamýna gelir. Derlediðinizde,
    derleyicinin hem main.cpp hem de add.cpp'yi listelediðini görmelisiniz. Eðer sadece main.cpp'yi görüyorsanýz,
    add.cpp kesinlikle derlenmiyor demektir. Visual Studio veya Code::Blocks kullanýyorsanýz, IDE'nin sol veya sað 
    tarafýnda Solution Explorer/proje panelinde add.cpp'yi görmelisiniz. Görmüyorsanýz, projenize sað týklayarak dosyayý 
    ekleyin ve ardýndan yeniden derlemeyi deneyin. Komut satýrýnda derliyorsanýz, komutunuzda main.cpp ve add.cpp'yi dahil 
    etmeyi unutmayýn.

    2b. ... add.cpp dosyasýný yanlýþ projeye eklemiþ olma olasýlýðýnýz var.

    2c. ... dosyanýn derlenmemesi veya baðlanmamasý için ayarlandýðý olasýlýðýnýz var. Dosya özelliklerini kontrol edin
    ve dosyanýn derlenmesi/baðlanmasý için yapýlandýrýldýðýndan emin olun. Code::Blocks'da derleme ve baðlantý ayrý onay
    kutularýdýr ve her ikisi de iþaretlenmelidir. Visual Studio'da "derlemeden hariç tut" seçeneði, "hayýr" olarak ayarlanmalý
    veya boþ býrakýlmalýdýr.

    Main.cpp dosyasýndan "add.cpp" dosyasýný #include etmeyin. Bu, öniþlemcinin add.cpp içeriðini doðrudan main.cpp'ye 
    eklemesine neden olur ve bunlarý ayrý dosyalar olarak iþlememesini saðlar.
    




    ÖZET
    C++, her kaynak dosyasýnýn, diðer dosyalardaki bilgi hakkýnda hiçbir bilgi olmadan
    baðýmsýz olarak derlenebilecek þekilde tasarlanmýþtýr. Bu nedenle, dosyalarýn aslýnda
    hangi sýrayla derlendiði önemli olmamalýdýr.

    Nesne yönelimli programlamaya girdiðimizde çok sayýda dosya ile çalýþmaya baþlayacaðýz,
    bu yüzden çoklu dosya projelerini nasýl ekleyip derleyeceðinizi anladýðýnýzdan emin olmanýz gereken bir zamandýr.

    Hatýrlatma: Her yeni kod (.cpp) dosyasý oluþturduðunuzda, derlenmesi için projenize eklemeniz gerekecektir.


    */

    // std::cout << BasicMath::add(4, 3); bunu da denemiþ olduk baþarýlý. 
    /*
                                                        INTRO TO PREPROCESSOR 
    Elbette! C++ derlemesi, belirli bir .cpp dosyasýný tam olarak yazdýðýnýz gibi derlemek yerine, önce bir ön iþleme (preprocessing) aþamasýndan
    geçer. Bu ön iþleme aþamasýnda, bir program olan ön iþlemci (preprocessor), kod dosyasýnýn metninde çeþitli deðiþiklikler yapar. Ancak ön iþlemci,
    aslýnda orijinal kod dosyalarýný herhangi bir þekilde deðiþtirmez. Yaptýðý tüm deðiþiklikler, geçici bellekte veya geçici dosyalarda yapýlýr.

    Ön iþleme aþamasýnýn amacý, derleme sürecini hazýrlamak ve kodun belirli gereksinimlerini karþýlamak için metni düzenlemektir. Ön iþlemci, özel
    iþaretleme (directives) olarak adlandýrýlan komutlarý ve metni iþler. Örneðin, #include direktifi, baþka bir dosyadaki kodu mevcut dosyaya ekler.
    Bu, farklý kod dosyalarýný birleþtirmek için yaygýn olarak kullanýlýr.

    Ön iþleme aþamasý, kodunun derlenmesinden önce gerçekleþir ve kodunuzu derleyicinin kullanabileceði bir þekle dönüþtürür. Bu, programcýlara daha
    fazla esneklik ve metin iþleme yeteneði saðlar. Derleme iþlemi sýrasýnda, derleyici bu ön iþlenmiþ kodu kullanarak makine koduna çevirir ve
    nihayetinde çalýþtýrýlabilir bir program oluþturur.

    Kýsacasý, ön iþleme, kodunuzu derlemeye hazýrlayan ve farklý kod dosyalarýný birleþtirmeye yardýmcý olan bir ara aþamadýr. Bu, C++'ýn 
    geniþletilmiþ yeteneklerini ve esnekliðini saðlar.
    
    Geçmiþte öniþlemci derleyiciden ayrý bir programdý, ancak modern derleyicilerde öniþlemci doðrudan derleyicinin içine yerleþtirilebilir.
    
    Ön iþlemcinin yaptýðý iþlerin çoðu oldukça sýkýcýdýr. Örneðin, yorumlarý (comments) kaldýrýr ve her kod dosyasýnýn bir satýr ile bittiðini saðlar.
    Ancak, ön iþlemcinin çok önemli bir rolü vardýr: #include direktiflerini iþlemesi (bu konuya birazdan daha fazla deðineceðiz).

    Ön iþlemci, bir kod dosyasýný iþledikten sonra elde edilen sonuca "çeviri birimi"(translation unit) denir. Bu çeviri birimi, ardýndan derleyici tarafýndan derlenir.

    Bu çeviri birimi(translation unit), ön iþlemci tarafýndan iþlenmiþ haldeki kodun sonucunu temsil eder ve bu, derleyici tarafýndan makine koduna 
    çevrilmek üzere kullanýlýr. Bu þekilde, C++ kodu derlenmiþ ve çalýþtýrýlabilir bir program haline gelir.

    Ön iþleme, derleme ve baðlama sürecinin tamamýna çeviri(translation) denir.
    
                                                            PREPROCESSOR DIRECTIVES
    Preprocessor çalýþtýðýnda, kod dosyasý üzerinde yukarýdan aþaðýya doðru tarar ve Preprocessor yönergelerini arar.
    Preprocessor yönergeleri(pre. directives)     (genellikle yalnýzca yönergeler(directives) olarak adlandýrýlýr) # sembolü ile baþlayýp 
    bir satýr sonuyla (noktalý virgül DEÐÝL) biter. Bu yönergeler, Preprocessor belirli metin iþleme görevlerini gerçekleþtirmesini 
    söyleyen talimatlar içerir. Ön iþleyici, C++ sözdizimini anlamaz -- bunun yerine yönergeler kendi sözdizimlerine sahiptir
    (bazý durumlarda C++ sözdizimine benzeyen ve bazý durumlarda benzemeyen).
    

    Zaten gördünüz #include yönergesini (genellikle #include <iostream>) kullanýrken. Bir dosyayý #include ettiðinizde, ön iþleyici #include 
    yönergesini dahil edilen dosyanýn içeriðiyle deðiþtirir. Dahil edilen içerik ön iþlemden geçer (bu, baþka #include'larýn daha fazla ön 
    iþleme tabi tutulmasýna neden olabilir), ardýndan dosyanýn geri kalaný ön iþlemden geçer.
    
    
    
     Ön iþleyici (preprocessor), belirli bir kod dosyasýný ve bu dosya içinde kullanýlan tüm #include ile dahil edilen içerikleri 
     iþledikten sonra elde edilen sonuca "çeviri birimi" (translation unit) denir. Bu çeviri birimi, derlenmek üzere derleyiciye 
     gönderilen iþlenebilir kodun son halini temsil eder. Çeviri birimi, ön iþleme komutlarýnýn uygulandýðý, tüm içeriklerin bir 
     araya getirildiði ve sonunda derlemeye uygun hale getirilen bir dosyayý ifade eder.

    Bu çeviri birimleri, derleme iþlemi sýrasýnda derleyici tarafýndan iþlenir ve makine koduna çevrilir, böylece çalýþtýrýlabilir
    bir program oluþturulur. Bu, C++ dilinde birden fazla dosyanýn bir araya getirilmesi ve ayrý ayrý derlenmesine olanak tanýr.
    Yani çeviri birimleri include dosyalarý dahil kod dosyasýndaki kodlarýn hepsini içerir.

                                                MACRO TANIMLAR
    #define yönergesi, bir makro oluþturmak için kullanýlabilir. C++ dilinde, bir makro, girdi metnin nasýl dönüþtürüldüðünü belirleyen bir kuraldýr.

    Ýki temel türde makro bulunur: nesne benzeri makrolar ve iþlev benzeri makrolar.

    Ýþlev benzeri makrolar, iþlevlere benzer þekilde davranýr ve benzer bir amaç taþýr. Genellikle kullanýmlarý güvensiz kabul edilir ve 
    neredeyse yapabildikleri her þey, normal bir iþlevle yapýlabilir.

    Nesne benzeri makrolar iki þekilde tanýmlanabilir:

    #define tanýmlayýcý
    #define tanýmlayýcý yerine_geçme_metni

    Ýlk tanýmýn yerine geçme metni yokken, ikinci tanýmda yerine geçme metni vardýr. Bu, ön iþleyici yönergeleri olduðu için her iki 
    biçim de noktalý virgülle bitmez.

    Makro için kullanýlan tanýmlayýcý, normal tanýmlayýcýlarla ayný adlandýrma kurallarýný kullanýr: harf, rakam ve alt çizgi kullanýlabilir, 
    bir rakamla baþlayamaz ve alt çizgi ile baþlamamalýdýr. Geleneksel olarak, makro adlarý genellikle büyük harfle yazýlýr ve alt çizgilerle ayrýlýr.
    

    ** Nesne benzeri makrolar.
    * #define MY_NAME "Alex"

    int main()
    {
    std::cout << "My name is: " << MY_NAME << '\n'; -> std::cout << "My name is: " << "Alex" << '\n'; E DÖNÜÞTÜRÜYOR 
    Substitution text ile birlikte olan obje benzeri makrolar (C'de) literallere isim atama amaçlý kullanýlýrdý.
    Ancak bu artýk C++'da gerekli deðildir, çünkü C++'da daha iyi yöntemler bulunmaktadýr. Artýk object-like macros 
    with substitution text, genellikle yalnýzca eski kodlarda görülür.
    

    * Bir de substitution text olmayan object-like makrolar var onlarda text in yerine hiç bir þey konmadan yapýlanlar. 
    * Çok gereksiz gibi geliyor fakat textli olana göre kabul edilebilir kabul edilir.
    
    ** Koþullu Derleme 
    * Adýndan da belli koþula baðlý olarak bazý kodlarýn derlenmesini saðlayan bu özelliðimiz için bir çok conditional compilation directive
    * i var ama ben sadece #ifdef #ifndef #endif i öðrencem.
    * Koþullu derleme ön iþlem yönergeleri, belirli koþullara baðlý olarak bir kod parçasýnýn derlenip derlenmeyeceðini kontrol etmek için kullanýlýr. Bu baðlamda, en yaygýn kullanýlan üç yönergeden bahsedeceðiz: #ifdef, #ifndef ve #endif.

#ifdef ön iþlem yönergesi belirli bir tanýmlayýcýnýn önceden #define ile tanýmlanýp tanýmlanmadýðýný kontrol eder. Eðer tanýmlayýcý daha önce tanýmlandýysa, #ifdef ve eþleþen #endif arasýndaki kod derlenir. Tanýmlanmamýþsa, kod görmezden gelinir.
Ýþte bunu gösteren bir örnek program:

    
    #include <iostream>
    
    #define ENABLE_FEATURE  // ENABLE_FEATURE tanýmlayýcýsýný tanýmla
    
    int main() {
    #ifdef ENABLE_FEATURE  // ENABLE_FEATURE tanýmlayýcýsý tanýmlandý mý diye kontrol et
        std::cout << "Özellik etkin." << std::endl;
    #else
        std::cout << "Özellik devre dýþý." << std::endl;
    #endif
    
        return 0;
    }
    Bu örnekte, ENABLE_FEATURE önceden tanýmlandýðý için #ifdef ENABLE_FEATURE ve #endif arasýndaki kod derlenecektir.
    * ifndef de zaten bunun tersi eðer #define ile tanýmlanmamýþsa blok çalýþtýrýlýr. if else yapýsý ile aynýdýr sadece c++ syntaxýna daha çok benzer demek o kadar
    
                                                                    #if 0 
    #if 0
        þþ
        þþþ
        þþþþ
    #endif       -> Burad if 0 ile endif arasýnda kalan yer derlenmez çoklu yorum satýrý gibi çalýþýr yani if ile endif arasýndaki alan derlenmez.
                    Burada o alanýn derlenmesini istersek eðer #if 0 -> #if 1 olarak deðiþtirmemiz yeterli olacaktýr. 
                -> Çoklu yorum satýrýnýn olduðu yerde tekrar bir çoklu yorum satýrý yapamayacaðýmýz için bize uygun yol saðlar. 
                örneðin:*/
                      #if 0 // Don't compile anything starting here
                             std::cout << "Bob\n";
                            /* Some
                             * multi-line
                             * comment here
                             */
                             std::cout << "Steve\n";
                      #endif // until this point
    /*
        #define PRINT_JOE
                                ---> Burda PRINT_JOE hiçbir þey ile deðiþtirilmez. Yani Object-like macrolar diðer directives leri etkilemez.
        #ifdef PRINT_JOE
    
    *   Program sonunda tüm preprocessorler çözümlenir ve çýkarýlýr çünkü derleyici bunlarla ne yapacaðýný bilemez.
    */
    /*
                                                                The scope of #defines
    * Yer farketmeksizin tanýmlandýklarý yerden dosyanýn sonuna kadar kapsam alanýna sahiptirler. Ayný projede bile diðer dosyalarý etkilemezler.
    
                                                                Header ( Baþlýk ) Dosyalarý
    Baþlýk dosyalarý tanýmlamalarý bir dosyaya koyup onlarý istediðimiz yerde import ederek kullanabileceðimiz bir dosyaya koymaktýr. Bu bizi bir 
    çok yazma iþinden kurtarýr. Hele ki çok dosyalý sistemlerde çok iþe yarar bir þeydir :)


   **BEST Baþlýk dosyalarýnýzý adlandýrýrken .h sonekini tercih edin (projeniz zaten baþka bir kurala uymuyorsa).

   **BEST Bu, C++ baþlýk dosyalarý için uzun süredir devam eden bir kuraldýr ve çoðu IDE, diðer seçeneklere göre hala varsayýlan olarak .h'dir.

   **BEST Bir baþlýk dosyasý bir kod dosyasýyla eþleþtirilmiþse (örneðin, add.h ile add.cpp), her ikisinin de ayný temel adý (add) olmasý gerekir.
    
    Bu baþlýk dosyasýný main.cpp'de kullanmak için, onu #include etmemiz gerekir (köþeli ayraçlar deðil, týrnak iþaretleri kullanarak). ADD.CPP örneðinde,
    olduðu gbi #include "add.h" yaparak ekleriz (kendi yazdýklarýmýzý)

    **Kaynak dosyalar, eþleþtirilmiþ baþlýk dosyalarýný (varsa) #include etmelidir. 
    * Böyle zamanlarda diyelim ki elinde add.h add.cpp ve main.cpp olsun burada add.h i hem add.cpp hem de main.cpp de include etmen olabilecek hatalarý 
    * linking time da deðil de compile time da görmeni saðlar. Hem complexity azalýr hem debugging hýzlanýr bu best practice dikkat et yani. 
    


    *** CPP KAYNAK DOSYALARINI INCLUDE ETMEKTEN KAÇINMALIYIZ NEDENLERÝ ?
    * Ýsim çakýþmalarýný önler: Birden fazla kaynak dosyasý ayný isimli iþlevleri veya deðiþkenleri tanýmladýðýnda, 
    isim çakýþmalarý meydana gelebilir. Baþlýk dosyalarý, bu tür isim çakýþmalarýný önlemek için gerekli iþlevleri ve 
    deðiþkenleri tanýmlamayý kolaylaþtýrýr.

    ODR sorunlarýný önler: Bir kaynak dosyasýnýn birden fazla kaynak dosya tarafýndan içe aktarýlmasý, bir tanýmlama
    kuralý ihlali (ODR) sorunlarýna neden olabilir. Baþlýk dosyalarý, bu tür sorunlarý önlemek için gerekli ön bildirimleri saðlar.

    Derlemeyi hýzlandýrýr: Kaynak dosyalarý genellikle baþlýk dosyalarýna göre daha sýk deðiþir. Kaynak dosyasýný 
    deðiþtirdiðinizde, yalnýzca o kaynak dosyasýnýn yeniden derlenmesi gerekir. Baþlýk dosyalarý daha az deðiþtiðinden,
    diðer kaynak dosyalarýnýn tekrar derlenmesi gerekmeyebilir.

    Geleneklere uygunluk: C++ topluluklarý ve projeler genellikle baþlýk dosyalarýnýn kullanýlmasýný teþvik eder ve bu,
    projenizin diðer geliþtiriciler veya ekibiniz için daha anlaþýlýr ve bakýmý daha kolay hale getirir.
    

                                                            SORUN ÇÖZME 
    Bu konudaki sorunlar þu iki madde ile bir çoðunu çözebiliriz :D
    "add.h" Bulunamayan Derleyici Hatasý:

    Baþlýk dosyasýnýn gerçekten "add.h" adýný taþýdýðýndan emin olun. Dosyanýn yanlýþ bir þekilde 
    adlandýrýlmýþ olmadýðýna, örneðin "add" (uzantýsýz) veya ".txt" veya ".hpp" gibi farklý bir uzantýyla adlandýrýlmýþ olmadýðýna dikkat edin.
    "add.h" dosyasýnýn diðer kaynak kod dosyalarýnýzla ayný dizinde bulunduðundan emin olun.
    "add" Fonksiyonunun Tanýmlanmadýðý Baðlayýcý Hatasý:

    "add.cpp" dosyasýný projenize eklediðinizden emin olun, böylece "add" fonksiyonu ve tanýmý programýnýza baðlanabilir.
    Bu adýmlarý takip ederek, projenizdeki baþlýk dosyalarý ve kaynak dosyalarýnýn varlýðý ve dahil edilmesiyle ilgili
    yaygýn sorunlarý çözebilirsiniz.




    Muhtemelen iostream için köþeli parantezler ve add.h için çift týrnaklarýn neden kullanýldýðýný merak ediyorsunuzdur.
    Ayný ada sahip baþlýk dosyalarýnýn birden fazla dizinde bulunma olasýlýðý vardýr. Köþeli parantezleri veya çift týrnaklarý 
    kullanmamýz, ön iþlemciye hangi baþlýk dosyalarýný aramasý gerektiði konusunda bir ipucu verir.

    Köþeli parantezleri kullandýðýmýzda, ön iþlemciye bu baþlýk dosyasýnýn kendimiz tarafýndan yazýlmadýðýný söylüyoruz. 
    Ön iþlemci, baþlýðý yalnýzca içerik dizinleri tarafýndan belirtilen dizinlerde arayacaktýr. Ýçerik dizinleri, projeniz/IDE 
    ayarlarýnýzýn bir parçasý olarak yapýlandýrýlýr ve genellikle derleyiciniz ve/veya iþletim sistemi ile birlikte gelen baþlýk
    dosyalarýný içeren dizinlere varsayýlan olarak ayarlanýr. Ön iþlemci, baþlýk dosyasýný projenizin kaynak kodu dizininde aramayacaktýr.

    Çift týrnaklarý kullandýðýmýzda, ön iþlemciye bu baþlýk dosyasýnýn kendimiz tarafýndan yazýldýðýný söylüyoruz. Ön iþlemci, 
    önce mevcut dizinde baþlýk dosyasýný arar. Eðer uygun bir baþlýk bulamazsa, ardýndan içerik dizinlerinde arama yapacaktýr.

    *******KURAL 
    * Yazdýðýnýz veya geçerli dizinde bulunmasý beklenen baþlýk dosyalarýný dahil etmek için çift týrnak iþareti kullanýn. 
    Derleyicinizle, iþletim sisteminizle veya sisteminizin baþka bir yerine yüklediðiniz üçüncü taraf kitaplýklarla birlikte
    gelen baþlýklarý dahil etmek için açýlý parantezleri kullanýn.


    ****
    *  standart kütüphane baþlýk dosyalarýný (#include <iostream> gibi) kullanýrken .h uzantýsýný kullanmamamýz gerektiði.
    Ancak, kullanýcý tarafýndan oluþturulan (user-defined) baþlýk dosyalarý için (.h uzantýlý olanlar), .h uzantýsýný kullanmamýz 
    gerektiði belirtiliyor. Yani standart kütüphane baþlýk dosyalarý için .h uzantýsý tercih edilmez, ama kullanýcý tanýmlý
    baþlýk dosyalarý için .h uzantýsý kullanýlýr.



                                             BAÞKA DÝZÝNDE BULUNAN BAÞLIK DOSYASINI EKLEMEK

    Bunu yapmanýn (kötü) bir yolu, #include satýrýnýn bir parçasý olarak eklemek istediðiniz baþlýk dosyasýna göreli bir yol eklemektir.
    Örneðin:

    #include "baþlýklar/myHeader.h"
    #include "../moreHeaders/myOtherHeader.h"
    Bu derlenecek olsa da (dosyalarýn ilgili dizinlerde mevcut olduðu varsayýlýrsa), bu yaklaþýmýn dezavantajý, dizin yapýnýzý kodunuza
    yansýtmanýzý gerektirmesidir. Dizin yapýnýzý güncellerseniz kodunuz artýk çalýþmaz.

    Daha iyi bir yöntem, derleyicinize veya IDE'nize, baþka bir konumda bir grup baþlýk dosyanýzýn bulunduðunu, böylece bunlarý geçerli 
    dizinde bulamadýðýnda oraya bakacaðýný söylemektir. Bu genellikle IDE proje ayarlarýnýzda bir içerme yolu veya arama dizini ayarlayarak
    yapýlabilir.


    ** Hocamýz bu ayarlarý göstermiþ. Hani kötü bir mantalite olduðu için uzatmicam burada kalsýn. 
                
                                                BAÞKA BAÞLIK DOSYALARINI ÝÇEREN BAÞLIK DOSYALARI
    Bir baþlýk dosyasýnýn farklý bir baþlýk dosyasýnda bulunan bir bildirime veya tanýma ihtiyaç duymasý yaygýndýr. Bu nedenle, baþlýk 
    dosyalarý sýklýkla diðer baþlýk dosyalarýný da içerir.

    Kod dosyanýz #include ilk baþlýk dosyasýný içerdiðinde, ilk baþlýk dosyasýnýn içerdiði diðer baþlýk dosyalarýný da (ve bunlarý içeren
    tüm baþlýk dosyalarýný vb.) alýrsýnýz. Bu ek baþlýk dosyalarýna bazen geçiþli içermeler(transitive includes) adý verilir, çünkü bunlar açýk bir þekilde
    deðil örtülü olarak dahil edilir.


    ** BEST**Her dosya, derlemesi gereken tüm baþlýk dosyalarýný açýkça #include etmelidir. Diðer baþlýklardan geçiþli olarak eklenen baþlýklara
    güvenmeyin.
    
    BURADA ne demek istiyor. Mesela a.hpp yi include ediyorum diyelim ve a.hpp nin içinde de iostream kütüphanesini include ettiðimi varsayalým.
    Bu durumda iostream i main de kullanacaksam a.hpp den ayrý olarak tekrar include etmemin daha iyi olacaðýndan mý bahsediyor. 

                                                 BAÞLIK DOSYALARININ SIRALAMASI
   
   
    Baþlýk dosyalarýnýz doðru þekilde yazýlmýþsa ve ihtiyaç duyduklarý her þeyi #include ediyorsa, dahil etme sýrasýnýn bir önemi olmamalýdýr.

    Þimdi aþaðýdaki senaryoyu düþünün: Diyelim ki baþlýk dosyasý A, baþlýk dosyasý B'den gelen bildirimlere ihtiyaç duyar, ancak B'yi dahil 
    etmeyi unutur. Kod dosyamýzda, baþlýk B'yi baþlýk A'dan önce dahil edersek, kodumuz hala derlenecektir! Bu, derleyici tarafýndan,
    bu bildirimlere ihtiyaç duyan kodu derlemeden önce B'den tüm bildirimleri derleyeceði için çalýþýr.

    Ancak önce baþlýk A'yý dahil edersek, derleyici bu sefer þikayet edecektir çünkü A'dan gelen kodu derlerken henüz B'den gelen bildirimleri 
    görmemiþtir. Aslýnda bu daha tercih edilir çünkü hata yüzeye çýkarýlmýþ ve ardýndan düzeltilmesi gereken bir hata tespit edilir.
   
   
    Eksik içeriklerin derleyici tarafýndan iþaretlenme olasýlýðýný en üst düzeye çýkarmak için #includes'ýnýzý aþaðýdaki gibi sýralayýn:

    Eþleþtirilmiþ baþlýk dosyasý
    Projenizdeki diðer baþlýklar
    3. taraf kitaplýk baþlýklarý
    Standart kitaplýk baþlýklarý
    Her gruplandýrmanýn baþlýklarý alfabetik olarak sýralanmalýdýr (3. taraf kitaplýk belgeleri size aksini söylemediði sürece).

    Bu þekilde, kullanýcý tanýmlý baþlýklarýnýzdan birinde 3. taraf kitaplýk veya standart kitaplýk baþlýðý için #include eksikse, derleme hatasýna
    neden olma olasýlýðý daha yüksektir, böylece düzeltebilirsiniz.


    Baþlýk dosyalarý için en iyi uygulamalar

    Ýþte baþlýk dosyalarý oluþtururken ve kullanýrken bazý öneriler.

    Her zaman baþlýk koruyucularýný içermelisiniz (sonraki ders).
    Baþlýk dosyalarýnda deðiþkenleri ve iþlevleri tanýmlamayýn (þu an için).
    Bir baþlýk dosyasýna, iliþkilendirildiði kaynak dosyanýn adýný verin (örneðin, grades.h ile grades.cpp eþleþtirilmiþtir).
    Her baþlýk dosyasý belirli bir göreve sahip olmalý ve mümkün olduðunca baðýmsýz olmalýdýr. Örneðin, A iþlevselliði ile ilgili
    tüm bildirimleri A.h'ye ve B iþlevselliði ile ilgili tüm bildirimleri B.h'ye yerleþtirebilirsiniz. Bu þekilde, daha sonra sadece 
    A ile ilgilenseniz bile A.h'yi içerebilir ve B ile ilgili olanlar hakkýnda hiçbir þey almak zorunda kalmazsýnýz.
    Kullandýðýnýz kod dosyalarýndaki iþlevselliði gerektiren baþlýklara dikkat edin.
    Yazdýðýnýz her baþlýk dosyasý kendi baþýna derlenmelidir (ihtiyaç duyduðu her baðýmlýlýðý #include etmelidir).
    Sadece ihtiyacýnýz olaný #include edin (her þeyi sadece yapabildiðiniz için #include etmeyin).
    .cpp dosyalarýný #include etmeyin.
    Bir þeyin ne yaptýðýný veya nasýl kullanýlacaðýný belirten belgelemeyi baþlýða koymayý tercih edin. Orada daha olasý görünür.
    Bir þeyin nasýl çalýþtýðýný açýklayan belgeleme kaynak dosyalarda kalmalýdýr.


                                                Header guards
    







    */

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    return 0;
}
