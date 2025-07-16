// ch2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Quizler yapılmış ama sanki bir atlama olmuş burada o yüzden chapter 2  yi tekrar işlicez ama quizleri yapmicaz sadece bi işlicez not tutcaz.
// Önemli bir konu. 

#include <iostream>
//#include "add.h"

//int add(int x, int y);

int main() {

    //std::cout << add(4, 3) << '\n'; -> OLDU KARDEEEEŞ
    /*
    Notların bir kısmı çevrilmedi özet niteliğinde düşünülmelidir. 

    * C++ 3 status code tanımlıyor (main in dönüşü için) 0 , EXIT_SUCCESS, EXIT_FAILURE -> Taşınabilirliği arttırmak açısından bunları kullanmak lazım. 
    * Dönüş yapan fonksiyonlarda dönüş yapmazsak tanımlanamayan davranışlar ortaya çıkabilir. 
    * Fonksiyonlarda var olup kullanılmayan parametreler uyarı verir. 
    * Yerel değişkenlerinizi, ilk kullanacakları yere mümkün olduğunca yakın bir şekilde tanımlayın.

                                        FONKSİYONLARI ETKİLİ KULLANMAK
    Yeni programcıların karşılaştığı en büyük zorluklardan biri (dilin öğrenilmesi dışında), ne zaman ve nasıl işlevleri etkili bir
    şekilde kullanacaklarını anlamaktır. İşte işlevler yazarken temel bazı kurallar:

    Bir programda birden fazla kez görünen ifade grupları genellikle bir işlev haline getirilmelidir. Örneğin, kullanıcıdan girişleri aynı 
    şekilde birden fazla kez alıyorsak, bu, bir işlev için harika bir adaydır. Aynı şekilde bir şeyi birden fazla yerde aynı şekilde çıkarıyorsak,
    bu da bir işlev için mükemmel bir adaydır.
    Belirli girdi ve çıktıları olan kod, bir işlev için iyi bir adaydır (özellikle karmaşıksa). Örneğin, sıralamak istediğimiz bir 
    öğeler listemiz varsa, sıralamayı yapmak için kod, yalnızca bir kez yapılsa bile harika bir işlev olur. Giriş sıralanmamış liste,
    çıkış sıralanmış listedir. Başka bir olası işlev de 6 yüzlü bir zarın atılmasını simüle eden kod olurdu. Mevcut programınız bunu
    yalnızca bir kez kullanabilir, ancak işlev haline getirirseniz, programınızı daha sonra genişletirseniz veya gelecekteki bir programda
    yeniden kullanıma hazır olur.
    * Bir işlev genellikle bir (ve yalnızca bir) görevi yerine getirmelidir.
    * Bir işlev çok uzun, karmaşık veya anlaşılması zor hale geldiğinde, birden çok alt işleve bölünebilir. Buna yeniden yapılandırma ( refactoring ) denir.
    Genellikle C++ öğrenirken, 3 alt görevi içeren programlar yazacaksınız:

    Kullanıcıdan girişleri okuma
    Girişlerden bir değeri hesaplama
    Hesaplanan değeri yazdırma
    Basit programlar için (örneğin 20 satırın altında), bunlar ya da tümü main işlevinde yapılabilir. Ancak daha uzun programlar için
    (veya sadece pratiğin bir parçası olarak), her biri ayrı bir işlev için iyi bir adaydır.
    
    Yeni programcılar genellikle bir değeri hesaplama ve hesaplanan değeri yazdırma işlemlerini tek bir işlevde birleştirir. Bununla
    birlikte, bu işlevlerin "bir görev" kuralını ihlal ettiğini unuturlar. Bir işlev, bir değeri hesaplamalı ve hesaplanan değeri çağıran
    kişiye döndürmeli ve hesaplanan değeri yazmak gibi ne yapılacağını belirlemeli (örneğin başka bir işleve çağrıda bulunmak gibi) ve çağıran
    kişi hesaplanan değeri yazmalıdır.
    
    * Programlarınızda derleme hatalarını veya uyarılarını çözerken, önce listelenen ilk sorunu çözün ve ardından tekrar derleyin.

                                                FORWARD DECLARATION
    Bir ön deklarasyon, tanımlayıcıyı tanımlamadan önce tanıyıcı hakkında derleyiciye bilgi vermemizi sağlar.

    Fonksiyonlar için, bu, derleyiciye fonksiyonun varlığı hakkında bilgi vermemize olanak tanır, ancak fonksiyonun
    gövdesini tanımlamadan önce. Bu şekilde, derleyici, bir fonksiyonu aradığımızı anlayacaktır. Fonksiyonun nasıl 
    veya nerede tanımlandığını henüz bilmiyor olsa bile, fonksiyonu doğru bir şekilde çağırdığımızı kontrol etmek için kullanabilir.

    Bir fonksiyon için bir ön deklarasyon yazmak için, bir fonksiyon deklarasyon ifadesi (aynı zamanda bir fonksiyon
    prototipi olarak da adlandırılır) kullanırız. Fonksiyon deklarasyonu, fonksiyonun dönüş türünü, adını ve parametre
    türlerini içerir ve bir noktalı virgülle sona erer. Parametrelerin adları isteğe bağlı olarak dahil edilebilir. 
    Fonksiyon gövdesi deklarasyona dahil edilmez.
    

    Definition ve declaration aynı şey değil tüm definition lar birer declarationdur fakat tüm declarationlar bir definition değildir.
    Definition	Implements a function or instantiates a variable.
    Definitions are also declarations.	void foo() { } // function definition
    int x; // variable definition
    Declaration	Tells compiler about an identifier and its associated type information.	void foo(); // function declaration
    int x; // variable declaration
    Pure declaration	A declaration that isn’t a definition.	void foo();


                                            ***** The one definition rule (ODR) ******
    
    Tek Tanımlama Kuralı (veya kısaca ODR), C++ içinde iyi bilinen bir kuraldır. ODR'nin üç bölümü vardır:

    Bir dosya içinde, her bir fonksiyon, değişken, tür veya şablon sadece bir tanıma sahip olabilir. Farklı
    kapsamlarda (örneğin, farklı işlevler içinde tanımlanan yerel değişkenler veya farklı ad alanlar içinde
    tanımlanan işlevler) meydana gelen tanımlar bu kuralı ihlal etmez.

    Bir program içinde, her bir fonksiyon veya değişken yalnızca bir tanıma sahip olabilir. Bu kural, programların 
    birden fazla dosyaya sahip olabileceği için var. Linker'a görünmeyen işlevler ve değişkenler bu kuraldan hariç 
    tutulur (bu, ders 7.6'da daha ayrıntılı olarak ele alınır).

    Türler, şablonlar, iç içe işlevler ve iç içe değişkenler, her bir tanımın aynı olduğu sürece farklı dosyalarda
    yinelemeli tanımlara sahip olabilir. Bu konuların çoğunu henüz ele almadık, bu nedenle şu an için bu konuyu dert
    etmeyin - ilgili olduğunda tekrar ele alacağız.

    ODR'nin 1. bölümünü ihlal etmek, derleyicinin yeniden tanımlama hatası vermesine neden olur. ODR'nin 2. bölümünü
    ihlal etmek, linkerin yeniden tanımlama hatası vermesine neden olur. ODR'nin 3. bölümünü ihlal etmek, tanımsız davranışa neden olur.
                                            
    */

    /*
                                                PROJEYE DOSYA EKLEME
    Daha önce forward declaration ı anlatırken add() fonksiyonunu örnek vermiştik burada farklı bir dosya üzerinden bakacak olursak yani add() fonksiyonunu farklı bir dosyaya koyduktan sonra çalıştırsak
    acaba hata alır mıyız ? Cevap evet burada da aynı cevabı alırız. Cpp add fonksiyonunun ne olduğunu bilmiyor.
    Oysa derlemiştik. 
    Unutmayın, derleyici her dosyayı ayrı ayrı derler. Diğer kod dosyalarının içeriğini bilmez veya önceden
    derlenen kod dosyalarında gördüğü şeyleri hatırlamaz. Yani, derleyici fonksiyon add'ın tanımını daha 
    önce görmüş olabilir (eğer önce add.cpp'yi derlediyse), ama hatırlamaz.

    Bu sınırlı görünürlük ve kısa bellek bilinçli olarak tasarlanmıştır ve birkaç nedeni vardır:

   1 Bir projenin kaynak dosyalarının herhangi bir sırayla derlenmesine izin verir.
   2 Bir kaynak dosyasını değiştirdiğimizde, yalnızca o kaynak dosyasının yeniden derlenmesi gerekir.
   3 Farklı dosyalardaki tanımlayıcılar arasındaki isim çakışmalarının olasılığını azaltır.
    


    Sorunu yine forward declaration ile çözdük ama burada anlamamız gereken şey;
    Bir tanımlayıcı bir ifadede kullanıldığında, tanımlayıcı kendi tanımına bağlı olmalıdır.

    Eğer derleyici, derlenmekte olan dosyada tanımlayıcı için ne bir forward declaration ne de bir tanımı daha görmemişse, 
    tanımlayıcı kullanıldığı noktada hata verecektir.

    Eğer aynı dosyada bir tanım mevcutsa, derleyici tanımlayıcının kullanımını tanımına bağlayacaktır.

    Aksi takdirde, farklı bir dosyada bir tanım mevcutsa (ve bağlayıcı için görünürse), bağlayıcı tanımlayıcının kullanımını tanımına bağlayacaktır.
    Aksi takdirde, bağlayıcı hata verecektir.

    Birden fazla dosya ile çalışmaya başladığınızda işlerin ters gidebileceği pek çok durum olabilir.
    Yukarıdaki örneği denediyseniz ve bir hata ile karşılaştıysanız, aşağıdakileri kontrol edin:

    Eğer main.cpp dosyasında add işlevi için önceden bildirimin eksik olduğu bir derleyici hatası alırsanız,
    add işlevi için önceden bildirimi unuttuğunuz olabilir.
    Eğer add işlevi tanımsız olduğuna dair bir bağlayıcı hatası alırsanız, örneğin:
    unresolved external symbol "int __cdecl add(int,int)" (?add@@YAHHH@Z) referenced in function _main

    2a. ... muhtemelen add.cpp dosyasının projenize doğru şekilde eklenmediği anlamına gelir. Derlediğinizde,
    derleyicinin hem main.cpp hem de add.cpp'yi listelediğini görmelisiniz. Eğer sadece main.cpp'yi görüyorsanız,
    add.cpp kesinlikle derlenmiyor demektir. Visual Studio veya Code::Blocks kullanıyorsanız, IDE'nin sol veya sağ 
    tarafında Solution Explorer/proje panelinde add.cpp'yi görmelisiniz. Görmüyorsanız, projenize sağ tıklayarak dosyayı 
    ekleyin ve ardından yeniden derlemeyi deneyin. Komut satırında derliyorsanız, komutunuzda main.cpp ve add.cpp'yi dahil 
    etmeyi unutmayın.

    2b. ... add.cpp dosyasını yanlış projeye eklemiş olma olasılığınız var.

    2c. ... dosyanın derlenmemesi veya bağlanmaması için ayarlandığı olasılığınız var. Dosya özelliklerini kontrol edin
    ve dosyanın derlenmesi/bağlanması için yapılandırıldığından emin olun. Code::Blocks'da derleme ve bağlantı ayrı onay
    kutularıdır ve her ikisi de işaretlenmelidir. Visual Studio'da "derlemeden hariç tut" seçeneği, "hayır" olarak ayarlanmalı
    veya boş bırakılmalıdır.

    Main.cpp dosyasından "add.cpp" dosyasını #include etmeyin. Bu, önişlemcinin add.cpp içeriğini doğrudan main.cpp'ye 
    eklemesine neden olur ve bunları ayrı dosyalar olarak işlememesini sağlar.
    




    ÖZET
    C++, her kaynak dosyasının, diğer dosyalardaki bilgi hakkında hiçbir bilgi olmadan
    bağımsız olarak derlenebilecek şekilde tasarlanmıştır. Bu nedenle, dosyaların aslında
    hangi sırayla derlendiği önemli olmamalıdır.

    Nesne yönelimli programlamaya girdiğimizde çok sayıda dosya ile çalışmaya başlayacağız,
    bu yüzden çoklu dosya projelerini nasıl ekleyip derleyeceğinizi anladığınızdan emin olmanız gereken bir zamandır.

    Hatırlatma: Her yeni kod (.cpp) dosyası oluşturduğunuzda, derlenmesi için projenize eklemeniz gerekecektir.


    */

    // std::cout << BasicMath::add(4, 3); bunu da denemiş olduk başarılı. 
    /*
                                                        INTRO TO PREPROCESSOR 
    Elbette! C++ derlemesi, belirli bir .cpp dosyasını tam olarak yazdığınız gibi derlemek yerine, önce bir ön işleme (preprocessing) aşamasından
    geçer. Bu ön işleme aşamasında, bir program olan ön işlemci (preprocessor), kod dosyasının metninde çeşitli değişiklikler yapar. Ancak ön işlemci,
    aslında orijinal kod dosyalarını herhangi bir şekilde değiştirmez. Yaptığı tüm değişiklikler, geçici bellekte veya geçici dosyalarda yapılır.

    Ön işleme aşamasının amacı, derleme sürecini hazırlamak ve kodun belirli gereksinimlerini karşılamak için metni düzenlemektir. Ön işlemci, özel
    işaretleme (directives) olarak adlandırılan komutları ve metni işler. Örneğin, #include direktifi, başka bir dosyadaki kodu mevcut dosyaya ekler.
    Bu, farklı kod dosyalarını birleştirmek için yaygın olarak kullanılır.

    Ön işleme aşaması, kodunun derlenmesinden önce gerçekleşir ve kodunuzu derleyicinin kullanabileceği bir şekle dönüştürür. Bu, programcılara daha
    fazla esneklik ve metin işleme yeteneği sağlar. Derleme işlemi sırasında, derleyici bu ön işlenmiş kodu kullanarak makine koduna çevirir ve
    nihayetinde çalıştırılabilir bir program oluşturur.

    Kısacası, ön işleme, kodunuzu derlemeye hazırlayan ve farklı kod dosyalarını birleştirmeye yardımcı olan bir ara aşamadır. Bu, C++'ın 
    genişletilmiş yeteneklerini ve esnekliğini sağlar.
    
    Geçmişte önişlemci derleyiciden ayrı bir programdı, ancak modern derleyicilerde önişlemci doğrudan derleyicinin içine yerleştirilebilir.
    
    Ön işlemcinin yaptığı işlerin çoğu oldukça sıkıcıdır. Örneğin, yorumları (comments) kaldırır ve her kod dosyasının bir satır ile bittiğini sağlar.
    Ancak, ön işlemcinin çok önemli bir rolü vardır: #include direktiflerini işlemesi (bu konuya birazdan daha fazla değineceğiz).

    Ön işlemci, bir kod dosyasını işledikten sonra elde edilen sonuca "çeviri birimi"(translation unit) denir. Bu çeviri birimi, ardından derleyici tarafından derlenir.

    Bu çeviri birimi(translation unit), ön işlemci tarafından işlenmiş haldeki kodun sonucunu temsil eder ve bu, derleyici tarafından makine koduna 
    çevrilmek üzere kullanılır. Bu şekilde, C++ kodu derlenmiş ve çalıştırılabilir bir program haline gelir.

    Ön işleme, derleme ve bağlama sürecinin tamamına çeviri(translation) denir.
    
                                                            PREPROCESSOR DIRECTIVES
    Preprocessor çalıştığında, kod dosyası üzerinde yukarıdan aşağıya doğru tarar ve Preprocessor yönergelerini arar.
    Preprocessor yönergeleri(pre. directives)     (genellikle yalnızca yönergeler(directives) olarak adlandırılır) # sembolü ile başlayıp 
    bir satır sonuyla (noktalı virgül DEĞİL) biter. Bu yönergeler, Preprocessor belirli metin işleme görevlerini gerçekleştirmesini 
    söyleyen talimatlar içerir. Ön işleyici, C++ sözdizimini anlamaz -- bunun yerine yönergeler kendi sözdizimlerine sahiptir
    (bazı durumlarda C++ sözdizimine benzeyen ve bazı durumlarda benzemeyen).
    

    Zaten gördünüz #include yönergesini (genellikle #include <iostream>) kullanırken. Bir dosyayı #include ettiğinizde, ön işleyici #include 
    yönergesini dahil edilen dosyanın içeriğiyle değiştirir. Dahil edilen içerik ön işlemden geçer (bu, başka #include'ların daha fazla ön 
    işleme tabi tutulmasına neden olabilir), ardından dosyanın geri kalanı ön işlemden geçer.
    
    
    
     Ön işleyici (preprocessor), belirli bir kod dosyasını ve bu dosya içinde kullanılan tüm #include ile dahil edilen içerikleri 
     işledikten sonra elde edilen sonuca "çeviri birimi" (translation unit) denir. Bu çeviri birimi, derlenmek üzere derleyiciye 
     gönderilen işlenebilir kodun son halini temsil eder. Çeviri birimi, ön işleme komutlarının uygulandığı, tüm içeriklerin bir 
     araya getirildiği ve sonunda derlemeye uygun hale getirilen bir dosyayı ifade eder.

    Bu çeviri birimleri, derleme işlemi sırasında derleyici tarafından işlenir ve makine koduna çevrilir, böylece çalıştırılabilir
    bir program oluşturulur. Bu, C++ dilinde birden fazla dosyanın bir araya getirilmesi ve ayrı ayrı derlenmesine olanak tanır.
    Yani çeviri birimleri include dosyaları dahil kod dosyasındaki kodların hepsini içerir.

                                                MACRO TANIMLAR
    #define yönergesi, bir makro oluşturmak için kullanılabilir. C++ dilinde, bir makro, girdi metnin nasıl dönüştürüldüğünü belirleyen bir kuraldır.

    İki temel türde makro bulunur: nesne benzeri makrolar ve işlev benzeri makrolar.

    İşlev benzeri makrolar, işlevlere benzer şekilde davranır ve benzer bir amaç taşır. Genellikle kullanımları güvensiz kabul edilir ve 
    neredeyse yapabildikleri her şey, normal bir işlevle yapılabilir.

    Nesne benzeri makrolar iki şekilde tanımlanabilir:

    #define tanımlayıcı
    #define tanımlayıcı yerine_geçme_metni

    İlk tanımın yerine geçme metni yokken, ikinci tanımda yerine geçme metni vardır. Bu, ön işleyici yönergeleri olduğu için her iki 
    biçim de noktalı virgülle bitmez.

    Makro için kullanılan tanımlayıcı, normal tanımlayıcılarla aynı adlandırma kurallarını kullanır: harf, rakam ve alt çizgi kullanılabilir, 
    bir rakamla başlayamaz ve alt çizgi ile başlamamalıdır. Geleneksel olarak, makro adları genellikle büyük harfle yazılır ve alt çizgilerle ayrılır.
    

    ** Nesne benzeri makrolar.
    * #define MY_NAME "Alex"

    int main()
    {
    std::cout << "My name is: " << MY_NAME << '\n'; -> std::cout << "My name is: " << "Alex" << '\n'; E DÖNÜŞTÜRÜYOR 
    Substitution text ile birlikte olan obje benzeri makrolar (C'de) literallere isim atama amaçlı kullanılırdı.
    Ancak bu artık C++'da gerekli değildir, çünkü C++'da daha iyi yöntemler bulunmaktadır. Artık object-like macros 
    with substitution text, genellikle yalnızca eski kodlarda görülür.
    

    * Bir de substitution text olmayan object-like makrolar var onlarda text in yerine hiç bir şey konmadan yapılanlar. 
    * Çok gereksiz gibi geliyor fakat textli olana göre kabul edilebilir kabul edilir.
    
    ** Koşullu Derleme 
    * Adından da belli koşula bağlı olarak bazı kodların derlenmesini sağlayan bu özelliğimiz için bir çok conditional compilation directive
    * i var ama ben sadece #ifdef #ifndef #endif i öğrencem.
    * Koşullu derleme ön işlem yönergeleri, belirli koşullara bağlı olarak bir kod parçasının derlenip derlenmeyeceğini kontrol etmek için kullanılır. Bu bağlamda, en yaygın kullanılan üç yönergeden bahsedeceğiz: #ifdef, #ifndef ve #endif.

#ifdef ön işlem yönergesi belirli bir tanımlayıcının önceden #define ile tanımlanıp tanımlanmadığını kontrol eder. Eğer tanımlayıcı daha önce tanımlandıysa, #ifdef ve eşleşen #endif arasındaki kod derlenir. Tanımlanmamışsa, kod görmezden gelinir.
İşte bunu gösteren bir örnek program:

    
    #include <iostream>
    
    #define ENABLE_FEATURE  // ENABLE_FEATURE tanımlayıcısını tanımla
    
    int main() {
    #ifdef ENABLE_FEATURE  // ENABLE_FEATURE tanımlayıcısı tanımlandı mı diye kontrol et
        std::cout << "Özellik etkin." << std::endl;
    #else
        std::cout << "Özellik devre dışı." << std::endl;
    #endif
    
        return 0;
    }
    Bu örnekte, ENABLE_FEATURE önceden tanımlandığı için #ifdef ENABLE_FEATURE ve #endif arasındaki kod derlenecektir.
    * ifndef de zaten bunun tersi eğer #define ile tanımlanmamışsa blok çalıştırılır. if else yapısı ile aynıdır sadece c++ syntaxına daha çok benzer demek o kadar
    
                                                                    #if 0 
    #if 0
        şş
        şşş
        şşşş
    #endif       -> Burad if 0 ile endif arasında kalan yer derlenmez çoklu yorum satırı gibi çalışır yani if ile endif arasındaki alan derlenmez.
                    Burada o alanın derlenmesini istersek eğer #if 0 -> #if 1 olarak değiştirmemiz yeterli olacaktır. 
                -> Çoklu yorum satırının olduğu yerde tekrar bir çoklu yorum satırı yapamayacağımız için bize uygun yol sağlar. 
                örneğin:*/
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
                                ---> Burda PRINT_JOE hiçbir şey ile değiştirilmez. Yani Object-like macrolar diğer directives leri etkilemez.
        #ifdef PRINT_JOE
    
    *   Program sonunda tüm preprocessorler çözümlenir ve çıkarılır çünkü derleyici bunlarla ne yapacağını bilemez.
    */
    /*
                                                                The scope of #defines
    * Yer farketmeksizin tanımlandıkları yerden dosyanın sonuna kadar kapsam alanına sahiptirler. Aynı projede bile diğer dosyaları etkilemezler.
    
                                                                Header ( Başlık ) Dosyaları
    Başlık dosyaları tanımlamaları bir dosyaya koyup onları istediğimiz yerde import ederek kullanabileceğimiz bir dosyaya koymaktır. Bu bizi bir 
    çok yazma işinden kurtarır. Hele ki çok dosyalı sistemlerde çok işe yarar bir şeydir :)


   **BEST Başlık dosyalarınızı adlandırırken .h sonekini tercih edin (projeniz zaten başka bir kurala uymuyorsa).

   **BEST Bu, C++ başlık dosyaları için uzun süredir devam eden bir kuraldır ve çoğu IDE, diğer seçeneklere göre hala varsayılan olarak .h'dir.

   **BEST Bir başlık dosyası bir kod dosyasıyla eşleştirilmişse (örneğin, add.h ile add.cpp), her ikisinin de aynı temel adı (add) olması gerekir.
    
    Bu başlık dosyasını main.cpp'de kullanmak için, onu #include etmemiz gerekir (köşeli ayraçlar değil, tırnak işaretleri kullanarak). ADD.CPP örneğinde,
    olduğu gbi #include "add.h" yaparak ekleriz (kendi yazdıklarımızı)

    **Kaynak dosyalar, eşleştirilmiş başlık dosyalarını (varsa) #include etmelidir. 
    * Böyle zamanlarda diyelim ki elinde add.h add.cpp ve main.cpp olsun burada add.h i hem add.cpp hem de main.cpp de include etmen olabilecek hataları 
    * linking time da değil de compile time da görmeni sağlar. Hem complexity azalır hem debugging hızlanır bu best practice dikkat et yani. 
    


    *** CPP KAYNAK DOSYALARINI INCLUDE ETMEKTEN KAÇINMALIYIZ NEDENLERİ ?
    * İsim çakışmalarını önler: Birden fazla kaynak dosyası aynı isimli işlevleri veya değişkenleri tanımladığında, 
    isim çakışmaları meydana gelebilir. Başlık dosyaları, bu tür isim çakışmalarını önlemek için gerekli işlevleri ve 
    değişkenleri tanımlamayı kolaylaştırır.

    ODR sorunlarını önler: Bir kaynak dosyasının birden fazla kaynak dosya tarafından içe aktarılması, bir tanımlama
    kuralı ihlali (ODR) sorunlarına neden olabilir. Başlık dosyaları, bu tür sorunları önlemek için gerekli ön bildirimleri sağlar.

    Derlemeyi hızlandırır: Kaynak dosyaları genellikle başlık dosyalarına göre daha sık değişir. Kaynak dosyasını 
    değiştirdiğinizde, yalnızca o kaynak dosyasının yeniden derlenmesi gerekir. Başlık dosyaları daha az değiştiğinden,
    diğer kaynak dosyalarının tekrar derlenmesi gerekmeyebilir.

    Geleneklere uygunluk: C++ toplulukları ve projeler genellikle başlık dosyalarının kullanılmasını teşvik eder ve bu,
    projenizin diğer geliştiriciler veya ekibiniz için daha anlaşılır ve bakımı daha kolay hale getirir.
    

                                                            SORUN ÇÖZME 
    Bu konudaki sorunlar şu iki madde ile bir çoğunu çözebiliriz :D
    "add.h" Bulunamayan Derleyici Hatası:

    Başlık dosyasının gerçekten "add.h" adını taşıdığından emin olun. Dosyanın yanlış bir şekilde 
    adlandırılmış olmadığına, örneğin "add" (uzantısız) veya ".txt" veya ".hpp" gibi farklı bir uzantıyla adlandırılmış olmadığına dikkat edin.
    "add.h" dosyasının diğer kaynak kod dosyalarınızla aynı dizinde bulunduğundan emin olun.
    "add" Fonksiyonunun Tanımlanmadığı Bağlayıcı Hatası:

    "add.cpp" dosyasını projenize eklediğinizden emin olun, böylece "add" fonksiyonu ve tanımı programınıza bağlanabilir.
    Bu adımları takip ederek, projenizdeki başlık dosyaları ve kaynak dosyalarının varlığı ve dahil edilmesiyle ilgili
    yaygın sorunları çözebilirsiniz.




    Muhtemelen iostream için köşeli parantezler ve add.h için çift tırnakların neden kullanıldığını merak ediyorsunuzdur.
    Aynı ada sahip başlık dosyalarının birden fazla dizinde bulunma olasılığı vardır. Köşeli parantezleri veya çift tırnakları 
    kullanmamız, ön işlemciye hangi başlık dosyalarını araması gerektiği konusunda bir ipucu verir.

    Köşeli parantezleri kullandığımızda, ön işlemciye bu başlık dosyasının kendimiz tarafından yazılmadığını söylüyoruz. 
    Ön işlemci, başlığı yalnızca içerik dizinleri tarafından belirtilen dizinlerde arayacaktır. İçerik dizinleri, projeniz/IDE 
    ayarlarınızın bir parçası olarak yapılandırılır ve genellikle derleyiciniz ve/veya işletim sistemi ile birlikte gelen başlık
    dosyalarını içeren dizinlere varsayılan olarak ayarlanır. Ön işlemci, başlık dosyasını projenizin kaynak kodu dizininde aramayacaktır.

    Çift tırnakları kullandığımızda, ön işlemciye bu başlık dosyasının kendimiz tarafından yazıldığını söylüyoruz. Ön işlemci, 
    önce mevcut dizinde başlık dosyasını arar. Eğer uygun bir başlık bulamazsa, ardından içerik dizinlerinde arama yapacaktır.

    *******KURAL 
    * Yazdığınız veya geçerli dizinde bulunması beklenen başlık dosyalarını dahil etmek için çift tırnak işareti kullanın. 
    Derleyicinizle, işletim sisteminizle veya sisteminizin başka bir yerine yüklediğiniz üçüncü taraf kitaplıklarla birlikte
    gelen başlıkları dahil etmek için açılı parantezleri kullanın.


    ****
    *  standart kütüphane başlık dosyalarını (#include <iostream> gibi) kullanırken .h uzantısını kullanmamamız gerektiği.
    Ancak, kullanıcı tarafından oluşturulan (user-defined) başlık dosyaları için (.h uzantılı olanlar), .h uzantısını kullanmamız 
    gerektiği belirtiliyor. Yani standart kütüphane başlık dosyaları için .h uzantısı tercih edilmez, ama kullanıcı tanımlı
    başlık dosyaları için .h uzantısı kullanılır.



                                             BAŞKA DİZİNDE BULUNAN BAŞLIK DOSYASINI EKLEMEK

    Bunu yapmanın (kötü) bir yolu, #include satırının bir parçası olarak eklemek istediğiniz başlık dosyasına göreli bir yol eklemektir.
    Örneğin:

    #include "başlıklar/myHeader.h"
    #include "../moreHeaders/myOtherHeader.h"
    Bu derlenecek olsa da (dosyaların ilgili dizinlerde mevcut olduğu varsayılırsa), bu yaklaşımın dezavantajı, dizin yapınızı kodunuza
    yansıtmanızı gerektirmesidir. Dizin yapınızı güncellerseniz kodunuz artık çalışmaz.

    Daha iyi bir yöntem, derleyicinize veya IDE'nize, başka bir konumda bir grup başlık dosyanızın bulunduğunu, böylece bunları geçerli 
    dizinde bulamadığında oraya bakacağını söylemektir. Bu genellikle IDE proje ayarlarınızda bir içerme yolu veya arama dizini ayarlayarak
    yapılabilir.


    ** Hocamız bu ayarları göstermiş. Hani kötü bir mantalite olduğu için uzatmicam burada kalsın. 
                
                                                BAŞKA BAŞLIK DOSYALARINI İÇEREN BAŞLIK DOSYALARI
    Bir başlık dosyasının farklı bir başlık dosyasında bulunan bir bildirime veya tanıma ihtiyaç duyması yaygındır. Bu nedenle, başlık 
    dosyaları sıklıkla diğer başlık dosyalarını da içerir.

    Kod dosyanız #include ilk başlık dosyasını içerdiğinde, ilk başlık dosyasının içerdiği diğer başlık dosyalarını da (ve bunları içeren
    tüm başlık dosyalarını vb.) alırsınız. Bu ek başlık dosyalarına bazen geçişli içermeler(transitive includes) adı verilir, çünkü bunlar açık bir şekilde
    değil örtülü olarak dahil edilir.


    ** BEST**Her dosya, derlemesi gereken tüm başlık dosyalarını açıkça #include etmelidir. Diğer başlıklardan geçişli olarak eklenen başlıklara
    güvenmeyin.
    
    BURADA ne demek istiyor. Mesela a.hpp yi include ediyorum diyelim ve a.hpp nin içinde de iostream kütüphanesini include ettiğimi varsayalım.
    Bu durumda iostream i main de kullanacaksam a.hpp den ayrı olarak tekrar include etmemin daha iyi olacağından mı bahsediyor. 

                                                 BAŞLIK DOSYALARININ SIRALAMASI
   
   
    Başlık dosyalarınız doğru şekilde yazılmışsa ve ihtiyaç duydukları her şeyi #include ediyorsa, dahil etme sırasının bir önemi olmamalıdır.

    Şimdi aşağıdaki senaryoyu düşünün: Diyelim ki başlık dosyası A, başlık dosyası B'den gelen bildirimlere ihtiyaç duyar, ancak B'yi dahil 
    etmeyi unutur. Kod dosyamızda, başlık B'yi başlık A'dan önce dahil edersek, kodumuz hala derlenecektir! Bu, derleyici tarafından,
    bu bildirimlere ihtiyaç duyan kodu derlemeden önce B'den tüm bildirimleri derleyeceği için çalışır.

    Ancak önce başlık A'yı dahil edersek, derleyici bu sefer şikayet edecektir çünkü A'dan gelen kodu derlerken henüz B'den gelen bildirimleri 
    görmemiştir. Aslında bu daha tercih edilir çünkü hata yüzeye çıkarılmış ve ardından düzeltilmesi gereken bir hata tespit edilir.
   
   
    Eksik içeriklerin derleyici tarafından işaretlenme olasılığını en üst düzeye çıkarmak için #includes'ınızı aşağıdaki gibi sıralayın:

    Eşleştirilmiş başlık dosyası
    Projenizdeki diğer başlıklar
    3. taraf kitaplık başlıkları
    Standart kitaplık başlıkları
    Her gruplandırmanın başlıkları alfabetik olarak sıralanmalıdır (3. taraf kitaplık belgeleri size aksini söylemediği sürece).

    Bu şekilde, kullanıcı tanımlı başlıklarınızdan birinde 3. taraf kitaplık veya standart kitaplık başlığı için #include eksikse, derleme hatasına
    neden olma olasılığı daha yüksektir, böylece düzeltebilirsiniz.


    Başlık dosyaları için en iyi uygulamalar

    İşte başlık dosyaları oluştururken ve kullanırken bazı öneriler.

    Her zaman başlık koruyucularını içermelisiniz (sonraki ders).
    Başlık dosyalarında değişkenleri ve işlevleri tanımlamayın (şu an için).
    Bir başlık dosyasına, ilişkilendirildiği kaynak dosyanın adını verin (örneğin, grades.h ile grades.cpp eşleştirilmiştir).
    Her başlık dosyası belirli bir göreve sahip olmalı ve mümkün olduğunca bağımsız olmalıdır. Örneğin, A işlevselliği ile ilgili
    tüm bildirimleri A.h'ye ve B işlevselliği ile ilgili tüm bildirimleri B.h'ye yerleştirebilirsiniz. Bu şekilde, daha sonra sadece 
    A ile ilgilenseniz bile A.h'yi içerebilir ve B ile ilgili olanlar hakkında hiçbir şey almak zorunda kalmazsınız.
    Kullandığınız kod dosyalarındaki işlevselliği gerektiren başlıklara dikkat edin.
    Yazdığınız her başlık dosyası kendi başına derlenmelidir (ihtiyaç duyduğu her bağımlılığı #include etmelidir).
    Sadece ihtiyacınız olanı #include edin (her şeyi sadece yapabildiğiniz için #include etmeyin).
    .cpp dosyalarını #include etmeyin.
    Bir şeyin ne yaptığını veya nasıl kullanılacağını belirten belgelemeyi başlığa koymayı tercih edin. Orada daha olası görünür.
    Bir şeyin nasıl çalıştığını açıklayan belgeleme kaynak dosyalarda kalmalıdır.
    */
    return 0;
}
