// ch6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
void isEven(int x){
    if (x % 2 == 0) {
        std::cout << x << " is even";
    }
    else {
        std::cout << x << " is odd";
    }


}
int getNumber() {
    int x{};
    std::cout << "Enter an integer: ";
    
    std::cin >> x;

    return x;
}
int main()
{
    // Birleşik işlemler matematikte işlemlere operatör işleme girenlere operand denir. 
    // 2 + 3   -> 2 ve 3 literalleri operand iken + işaretide operatördür.
    // 4 + 2 * 3 = 18 mi 10 mu peki C++ işlem sırasını nasıl bilebilir 
    
    
    /*
    
    Burada C++ ın yaptığı 2 şey var;
    1- ) Derleme zamanında, derleyici ifadeyi çözümlemeli ve operatörlerle nasıl gruplandırıldığını belirlemelidir.
    2- ) Sonrasında derleme veya çalışma zamanında işlemciler değerlendirilir ve işlemler gerçekleştirilerek sonuç üretilir
    
    */
    // Operator Precedence - İşlem önceliği 
    /*
    7-4-1 nasıl gruplandırılır mesela. 
    Bir ifadede aynı öncelik seviyesine sahip iki operatör yan yana geldiğinde, operatörün ilişkilendirilme kuralları derleyiciye 
    operatörleri soldan sağa mı yoksa sağdan sola mı değerlendirmesi gerektiğini söyler. Çıkarma işlemi öncelik seviyesi 6'ya sahiptir
    ve öncelik seviyesi 6'daki operatörlerin ilişkilendirilme kuralları soldan sağa doğrudur. Bu nedenle, bu ifade soldan sağa 
    gruplanır: (7 - 4) - 1.*/

    // C++ de bir çok operatör level i var bunlar 1 den başlayarak 17 ye kadar gidiyor ve () parantezler en yükselerden biri 
    // o yüzden bileşik işlemler yapacağımız zaman parantez kullanarak bunu daha kolay okunabilir hale getirmek en iyi yoldur.

    /*
    (a * b) + (c * d) -> Fonksiyonlarda ve operantların değerlendirme sıraları belirtilmemiştir. 
    Yani c++ yukarıda a *b veya c * d yi ilk olarak değerlendirebilir bu biraz karışıktır. Bununla alakalı 6.1 konunun altlarında bir
    örnek var. 
    Dikkatli olmak lazım. 

    Kısaca **** İşlemciler fonksiyon argümanları ve alt ifadelerin değerlendirme sırası her hangi bir sıralamada olabilir. 
    Bundan kaçınmanın yolu ise "Yazdığımız ifadelerin veya fonksiyon çağrılarının operand veya argüman değerlendirme
    sırasına bağlı olmadığından emin olmaktır".
 
    UNARY OOPERATORS 
    Unary yani birli operatörler isminden de belli olduğu gibi tek bir operand alırlar. Unary operatörler + ve - dir 
    +x -x 
    - unary operatörü operandını -1 ile çarparak return eder. 
    + operandın değerini döndürür. Gereksizdir sadece - operatörüne simetri sağlaması için eklenmiş bir operatördür :d

    BINARY OPERATORS
    Klasik 2 işlemcili operatörlerdir bunlar + - / * % operatörleridir. Burada + - * işlemcileri aynı normal hayattaki gibi çalışır 
    fakat bölme ve mod işlemine biraz değinmek gerekir.
    
    / -> operatöründe 1 veya 2 tarafın kayan noktalı sayı olması bölümü de o şekilde yapar ki çıktısıda kayan noktalı sayı olur 
    eğer 2 işlemci de integer değer olursa bölümün sonucu integer olur ve noktadan sonraki kısım DÜŞÜLÜR.

    Burada 2 tamsayı varsa x ve y olsun bunları yine de floating point olarak bölmek istiyoruz dersen reis 
    static_cast<double>(x) / y veya her ikisini veya sadece y yi değiştirerek üstteki kurala göre float bölmesi yapabilirim.
    
    Burada 0 veya 0.0 a bölmek tanımlanmayan davranışa neden olabilir bazı derleyicilerde sistem mimarisinin tanımlamasına göre
    NaN veya Inf dönütü alabiliriz. 

    Kalan alma işlemi (%) aynı bildiğimiz şey sadece eksili sayılarda her zaman ilk işlemcinin işaretini alıyor. 
    += -= *= /= %= leri de kullanabiliyoruz bu sağdaki değişkeni soldaki ile işleme sokarak sola tekrardan atar.

    kalan alma işlemi ile işlemler yaparken negatif sayılar sorun çıkartabilir burada 0 ile karşılaştırmak 
    daha mantıklıdır yapılabileceği her yerde 0 ile karşılaştır.
    
    */
    // Arttırım / Azaltım Operatörleri ve yan etkileri
    /*
    
    ++x -> X i arttır ve x i geri döndür
    --x -> X i azalt ve x i geri döndür
    x++ -> x i kopyala, x i arttır, x i döndür ve kopyala
    x-- -> x i kopyala, x i azalt, x i döndür ve kopyala
    

    Burada zaten ++x --x in çalışma mantığını biliyoruz klasik alıp değerlendir ve arttır sonrasında kullan. 
    Ama postfix işlemlerde ise x++ ve x-- ilk olarak x in bir kopyası oluşturulur ve asıl değer arttırılır veya azaltılır
    Sonrasında eğer değer arttırılır bunun etkisi nedir derseniz 
    int x { 5 } ;
    int y { ++x }; -> Burada y 6 olur yani prefix işlemlerde önce arttırım sonrasında değerlendirme olur. 
    int z { x++ }; -> Burada ise x in kopyası oluşturulur ve orjinal arttırılır bu sırada z değişkenine x in kopyası ile işlem
    yapılır yani z 5 olarak atanır. Sonrasında x in değeri bir arttırılır. 
    Postfix de işlemlerin fazlalığı belli yani performans konusunda prefix işlemden daha kötü olduğunu bil.

    */
    /* Burada prefix işlemler daha performanslı ve süpriz oluşturmaya daha uzak olduğu için tercih edilebildiği her yerde tercih
    edilmeli
    */


    /*
    Yan etkiler
    
    Bir fonksiyon veya ifade bir dönüş değeri üretmek dışında gözlemlenebilir bir etkiye sahipse, bu işlevin yan etkisi olduğu söylenir.
    * Burada yazılan kodda oluşan yan etki bazen emirlerin sırasında bir hataya neden olabilri 
    * örnek bir toplama fonksiyonna 2 değer yolayaım mesela 
    * int x { 5 };
    * add(x, ++x);
    * Burada add fonksiyonu 5 + 6 mı yapacak 6 + 6 mı undefined behaviour olur yani.
    
    ***  C++ fonksiyon argümanları ve işleçlerin işlenenleri için bir değerlendirme sırası tanımlamaz.
    ***  Çoğu durumda, C++ aynı ifadede birden fazla kullanılan bir yan etkisi olan bir nesnenin yan 
    ***  etkilerinin ne zaman uygulanması gerektiğini de belirtmez. Bu, aynı ifadede bir nesne daha fazla
    ***  kullanıldığında belirsiz davranışa yol açabilir.    
    */
    /*
    Virgül Operatörü
    Virgül operatörü (,) bir ifade yerine birden fazla ifadeyi değerlendirmenize olanak tanır. Virgül operatörü sol operandı
    değerlendirir, ardından sağ operandı değerlendirir ve son olarak sağ operandın sonucunu döndürür.

    Genellikle, virgül operatörünü kullanarak yazılan bir ifade, ayrı ifadeler olarak yazılmış bir şekilde daha iyi anlaşılır olur.
    Yani, birçok ifadeyi virgül operatörü ile bir arada yazmak yerine her bir ifadeyi ayrı ayrı yazmak, 
    kodun daha okunaklı ve anlaşılır olmasını sağlar. Örneğin, verilen kod, aşağıdaki gibi daha anlaşılır bir şekilde yazılabilir:
    
    Tabi işlem önceliğinde en son seviye olmasından dolayı da dikkatli olmak gerekir örneğin
    Örnek
    z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.


    Çoğu yazılımcı virgül operatörünü kullanmaktan çekinir. En iyi yaklaşım da loop lar dışında 
    virgül operatörünü kullanmaktan çekinmektir

    */

    /*
    int x{ 5 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n';
    */

    /*
    Ternary Operator - Arithmetic if -> ?: - Kullanımı : (contidion) ? expression1 : expression2; 
    Bu kullanıma göre zaten aritmetik if olarak da bilinir. Condition doğruysa expression1 çalıştırılır. Aksi takdirde expression 2 çalıştırılır. 
    Önemli bir nokta expression2 opsiyonel değildir. Yani kesinlikle değer döndürmelidir.

    Doğruysa expression 1 çalışır yanlışsa expression 2 çalışır. 

    örneğin -> int x = ( condition ) ? expression 1 : expression 2;
    örneğin -> larger = (x > y) ? x : y;

    Tabi burada en önemli şeylerden biri koşul operatörünün işlem seviyesi çok düşüktür o yüzden her zaman parantez ile kullanılması en iyi harekettir
    
    Tabi burada kullandığımız ifadelerin türleri birbirine eşit olması gerek ya da ortak bir türe dönüştürülebilir türler olmalı 
    örnek -> std::cout<< (x != 5 ) ? x : "x is 5"); -> Bu derlenmez çünkü bir tarafta x yani int değişkeni var ikeN 
    diğer tarafta C-style string literali
    var türleri uyumsuz olduğu için bu ifade derlenemeyecektir. Bu gibi durumlarda mecburen if else kalıbı kullanılmalıdır.
    */    
    // Fonksiyonların içinde tanımlanan değişkenler fonksiyonun sonunda yok olduğu gibi if else içinde tanımlanan değişkenler de if yada else ifadesinin sonunda sona erer. Koşul ifadeleri bunun gibi durumlarda kullanılabilir. If else nin kullanılamayacağı yerler yani.
    
    /*
    Peki koşul operatörünü ne zaman kullanmalıyız ? 
     
    ** Koşul operatörünü basit koşul olduğu durumlarda.Sonucun kullanılabileceği okunabilirliği arttırabilecek noktalarda kullanmak gerekir. Aksi halde hata yapmaya yatkın okunaksız kodlar oluşturmuş oluruz.
    */
    // RELATIONAL OOERATORS AND FLOATING POINT COMPARISIONS
    /*Benim çevirim ilişkisel operatörler ve kayan noktalı karşılaştırma
    > , < , >= , <= == != klasik matematiksel karşılaştırmadır 
    Çokça gördüğümüz için örneğini yazmicam
    */

/*
Boolean koşul değerleri

burada yeni öğrenenler 
if (b1 == true ) -> gibi şeyler yapıyor ve bu gereksiz bir durum bunun yerine if(b1) yazabiliriz. Çünkü burada ekstra bir değer sunmadığımız
için bunu yazmak gereksiz oluyor o yüzden okumayı güçleştiriyor. == != karşılaştırmalarını tekli ifadelerde kullanmamak ve onun yerine 
!b1 veya b1 -> false ve true için bunları kullanmak daha mantıklı. 
*//*
    Hesaplanan kayan noktalı sayıların karşılaştırılması sorunlu olabilir. Bunun nedeni de yuvarlama hatalarıdır 
    Örneğin 100.0 - 99.99 ile 10.0 - 9.99  ikisinin de sonucu 0.01 dir fakat C++ da oluşan yuvarlama hatalarından dolayı kullanımı tehlikelidir. 
    Bunu if else bloğu ile görebiliriz. 
    
    ** tabi bu hesaplanan değerler arasında low-precision yani düşük hassasiyet varsa burda karşılaştırma yapma da her hangi bir sorun yok demektir. 

    Veya bir fonksiyonun dönüş değeri 0.0 ise burada direkt karşılaştırma yapılabilir 

    if (someFunc() == 0.0 ){
        do something 
    }  

    Gibisinden bir örnek verilebilir. 

    ** Veya constexpr double gravity {9.8} gibi bir kayan noktalı sayı; yani değişmeyeceği garanti edilmiş bir literal ise burada da 
    * direkt karşılaştırma yapılabilir. Üstteki fonksiyon örneği gibi. 
    *
    * Burada karşılaştırma yaparken belirli bir yüzde hatayı kabul ederim dersen sorun yok. Bunun için de klasik karşılaştırma ypaıyor hoca yani 
    * tolerans veriyor hoca. ApproximatelyEqual diyerek relAbs yani Knuth un algoritması ve normal algoritma yaptı. İşin düşerse 
    * 6.6 ch yi tekrar advanced okuyucular için olan bölümü okursun.    
    */
    
    // CH 6.7 Logical Operators ye geldik
    /*
    C++ ta 3 tane mantık operatörü vardır. ! Logical Not 
                                           && Logical AND
                                           || Logical OR
    Burada en çok yapılan hata Logical NOT operatörünün işlem önceliği seviyesinin yüksekliğinden dolayı. Ne demek istediğimi anladın
    Bu hatalardan kaçınmak için; Eğer Logical Not operatörünü kullanacaksan kullandığın yerde parantezlerle durumu kontrol altına almalısın.


    Logical OR operatöründe yapılan en büyük yanlış ise ona benzeyen Bitwise or operatörü ile karıştırılmasıdır. 
    || -> Lo. Op.
    |  -> Bi. Op.   Bu şekildedir. İkisi farklı fonksiyonları yürüttüğü için sonuçların yanlış çıkmasına sebep olabilir. 


    Logical AND operatöründe yapılan en büyük yanlış ise ona benzeyen Bitwise AND operatörü ile karıştırılmasıdır.
    && -> Lo. Op.
    &  -> Bi. Op.   Bu şekildedir. İkisi farklı fonksiyonları yürüttüğü için sonuçların yanlış çıkmasına sebep olabilir.

    ** Burada hem Log. Or hem de Log. And kapılarını bir den fazla olacak şekilde kullanabiliriz. -> örn: if (value > 10 && value < 20 && value != 16)

    ***Kısa devre değerlendirmesi.
    * Burada Logical Or ve Logical And işlemlerinde sol operatör Or için true olduğunda sonuç true olacağı için sağ operatör değerlendirilmeden 
    * geçilir. Logical And de de sol operator false olursa sağ operatör değerlendirilmez buna Kısa devre değerlendirmesi yani Short Circuit Evaluation
    * denir. Performansla alakalı yerlerde çok iyi olur.
    * ** Burada dikkat edilmesi gereken en önemli nokta yan etkili işlemlerde örneğin ++x x++ gibi işlemlerde seri şeklinde logic devrelerde 
    * dikkatli olunmalı en mantıklı hareket bunları aynı seride kullanmamaktır. 
    * Örn: if (x == 1 && ++y == 2)
               // do something

               Yukarıdaki örnekte gördüğün gibi.

    Normalde her hangi bir sıra ile değerlendirme olurken Logical operatörlerde standart açıkça "ilk olarak sol operatör değerlendirilir" Demekte.

    Burada kısa devre yerleşik versiyonlarda olmakta yani overload ederek kendi tipimizi oluşturursak Kısa devre de yapmayacaktır. 
    *//*
    OR VE AND Kapılarının karışık kullanımı
    ---------------------------------------
    Burada yeniler AND ve OR kapılarının aynı işlem seviyesine sahip olduğunu düşünür + ve - gibi fakat bu noktada 
    yanılırlar.
    
    AND kapısı OR kapısından daha yüksek seviye işlem önceliğine sahip olduğu için hata yapmaya müsait bir alandır DİKKAT !!!!
    
    Buralarda parantezlerle sistemi kontrol etmek hem okunaklılığı arttırır hem daja iyi kod yazmış olursunuz ve hataları önler.


    DE MORGAN IN KURALLARI ( Bi salmadın bizi amk )
    -----------------------------------------------

    Çoğu programcı !(x && y) ifadesinin  !x && !y Bu ifadeye eşit olduğunu düşünür. Fakat, not operatörü işlemler üzerine de dağılır.

    !(x && y) => !x || !y
    !(x || y) => !x && !y  Bu şekilde dağılır yani
    

    Kanıt:
    x   	y	    !x  	!y	   !(x || y)  !x && !y
    false	false	true	true	true	    true
    false	true	true	false	false	    false
    true	false	false	true	false	    false
    true	true	false	false	false	    false

    LOGİCAL XOR
    -----------
    C++ mantıksal bir XOR operatörü sağlamaz (operatör^ mantıksal bir XOR değil, bit düzeyinde bir XOR'dur).
    Mantıksal VEYA veya mantıksal VE'den farklı olarak mantıksal XOR, kısa devre olarak değerlendirilemez.
    Bu nedenle, mantıksal OR ve mantıksal AND operatörlerinden mantıksal bir XOR operatörü oluşturmak zordur.
    Ancak eşitsizlik operatörünü (!=) kullanarak mantıksal XOR'u kolayca taklit edebilirsiniz:

    ÖRNEĞİN: f (a != b) ... // a XOR b, assuming a and b are Booleans Bu birden çok olabilir. Mesela a XOR b XOR c şeklinde de yapbiliriz
    sadece eklicez.
    *** Burada bilinmesi gereken tek şey şu operandlar yani işlenenler boolean olmalı integer olmaz.
    * İlla başka bir type ı kullancam dersen static_cast<bool>(işlenen) yaparak bool a çevirirsin zaten hepsi çevriliyor.
    
    bazı klavyeler bu işaretleri desteklemediği için 
    && -> and 
    || -> or
    !  -> not 

    kelimeleri kullanılabilir. 

    */
    return 0;
}
