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
    // Birleþik iþlemler matematikte iþlemlere operatör iþleme girenlere operand denir. 
    // 2 + 3   -> 2 ve 3 literalleri operand iken + iþaretide operatördür.
    // 4 + 2 * 3 = 18 mi 10 mu peki C++ iþlem sýrasýný nasýl bilebilir 
    
    
    /*
    
    Burada C++ ýn yaptýðý 2 þey var;
    1- ) Derleme zamanýnda, derleyici ifadeyi çözümlemeli ve operatörlerle nasýl gruplandýrýldýðýný belirlemelidir.
    2- ) Sonrasýnda derleme veya çalýþma zamanýnda iþlemciler deðerlendirilir ve iþlemler gerçekleþtirilerek sonuç üretilir
    
    */
    // Operator Precedence - Ýþlem önceliði 
    /*
    7-4-1 nasýl gruplandýrýlýr mesela. 
    Bir ifadede ayný öncelik seviyesine sahip iki operatör yan yana geldiðinde, operatörün iliþkilendirilme kurallarý derleyiciye 
    operatörleri soldan saða mý yoksa saðdan sola mý deðerlendirmesi gerektiðini söyler. Çýkarma iþlemi öncelik seviyesi 6'ya sahiptir
    ve öncelik seviyesi 6'daki operatörlerin iliþkilendirilme kurallarý soldan saða doðrudur. Bu nedenle, bu ifade soldan saða 
    gruplanýr: (7 - 4) - 1.*/

    // C++ de bir çok operatör level i var bunlar 1 den baþlayarak 17 ye kadar gidiyor ve () parantezler en yükselerden biri 
    // o yüzden bileþik iþlemler yapacaðýmýz zaman parantez kullanarak bunu daha kolay okunabilir hale getirmek en iyi yoldur.

    /*
    (a * b) + (c * d) -> Fonksiyonlarda ve operantlarýn deðerlendirme sýralarý belirtilmemiþtir. 
    Yani c++ yukarýda a *b veya c * d yi ilk olarak deðerlendirebilir bu biraz karýþýktýr. Bununla alakalý 6.1 konunun altlarýnda bir
    örnek var. 
    Dikkatli olmak lazým. 

    Kýsaca **** Ýþlemciler fonksiyon argümanlarý ve alt ifadelerin deðerlendirme sýrasý her hangi bir sýralamada olabilir. 
    Bundan kaçýnmanýn yollarý þu uyarýdýr. **** Yazdýðýmýz ifadelerin veya fonksiyon çaðrýlarýnýn operand veya argüman deðerlendirme
    sýrasýna baðlý olmadýðýndan emin olmalýyýz.
    */

    /*
    UNARY OOPERATORS 
    Unary yani birli operatörler isminden de belli olduðu gibi tek bir operand alýrlar. Unary operatörler + ve - dir 
    +x -x 
    - unary operatörü operandýný -1 ile çarparak return eder. 
    + operandýn deðerini döndürür. Gereksizdir sadece - operatörüne simetri saðlamasý için eklenmiþ bir operatördür :d

    BINARY OPERATORS
    Klasik 2 iþlemcili operatörlerdir bunlar + - / * % operatörleridir. Burada + - * iþlemcileri ayný normal hayattaki gibi çalýþýr 
    fakat bölme ve mod iþlemine biraz deðinmek gerekir.
    
    / -> operatöründe 1 veya 2 tarafýn kayan noktalý sayý olmasý bölümü de o þekilde yapar ki çýktýsýda kayan noktalý sayý olur 
    eðer 2 iþlemci de integer deðer olursa bölümün sonucu integer olur ve noktadan sonraki kýsým DÜÞÜLÜR.

    Burada 2 tamsayý varsa x ve y olsun bunlarý yine de floating point olarak bölmek istiyoruz dersen reis 
    static_cast<double>(x) / y veya her ikisini veya sadece y yi deðiþtirerek üstteki kurala göre float bölmesi yapabilirim.
    
    Burada 0 veya 0.0 a bölmek tanýmlanmayan davranýþa neden olabilir bazý derleyicilerde sistem mimarisinin tanýmlamasýna göre
    NaN veya Inf dönütü alabiliriz. 

    Kalan alma iþlemi (%) ayný bildiðimiz þey sadece eksili sayýlarda her zaman ilk iþlemcinin iþaretini alýyor. 
    += -= *= /= %= leri de kullanabiliyoruz bu saðdaki deðiþkeni soldaki ile iþleme sokarak sola tekrardan atar.

    kalan alma iþlemi ile iþlemler yaparken negatif sayýlar sorun çýkartabilir burada 0 ile karþýlaþtýrmak 
    daha mantýklýdýr yapýlabileceði her yerde 0 ile karþýlaþtýr.
    
    */

    // Quiz 6.3 exponentiation and remainder

    
    //isEven(getNumber());

    // Arttýrým / Azaltým Operatörleri ve yan etkileri
    /*
    
    ++x -> X i arttýr ve x i geri döndür
    --x -> X i azalt ve x i geri döndür
    x++ -> x i kopyala, x i arttýr, x i döndür ve kopyala
    x-- -> x i kopyala, x i azalt, x i döndür ve kopyala
    

    Burada zaten ++x --x in çalýþma mantýðýný biliyoruz klasik alýp deðerlendir ve arttýr sonrasýnda kullan. 
    Ama postfix iþlemlerde ise x++ ve x-- ilk olarak x in bir kopyasý oluþturulur ve asýl deðer arttýrýlýr veya azaltýlýr
    Sonrasýnda eðer deðer arttýrýlýr bunun etkisi nedir derseniz 
    int x { 5 } ;
    int y { ++x }; -> Burada y 6 olur yani prefix iþlemlerde önce arttýrým sonrasýnda deðerlendirme olur. 
    int z { x++ }; -> Burada ise x in kopyasý oluþturulur ve orjinal arttýrýlýr bu sýrada z deðiþkenine x in kopyasý ile iþlem
    yapýlýr yani z 5 olarak atanýr. Sonrasýnda x in deðeri bir arttýrýlýr. 
    Postfix de iþlemlerin fazlalýðý belli yani performans konusunda prefix iþlemden daha kötü olduðunu bil.

    */
    /* Burada prefix iþlemler daha performanslý ve süpriz oluþturmaya daha uzak olduðu için tercih edilebildiði her yerde tercih
    edilmeli
    */


    /*
    Yan etkiler
    
    Bir fonksiyon veya ifade bir dönüþ deðeri üretmek dýþýnda gözlemlenebilir bir etkiye sahipse, bu iþlevin yan etkisi olduðu söylenir.
    * Bana biraz saçma geldi aga bunlara neden yan etki diyoz amk kutuyu itersen kutu ileri gider zaten bunun için itersin 
    * Buna yan etki demek çok garip geliyor. He amaç x = 5 yazmak sa bilemem ama x = 5 i zaten x e 5 atamak için yazýyoz yani bu yan
    * etki olmaz bence amk böyle mantalitenin.
    * ** Hocam burada yazýlan kodda oluþan yan etki bazen emirlerin sýrasýnda bir hataya neden olabilri 
    * örnek bir toplama fonksiyonna 2 deðer yolayaým mesela 
    * int x { 5 };
    * add(x, ++x);
    * Burada add fonksiyonu 5 + 6 mý yapacak 6 + 6 mý undefined behaviour olur yani.
    
    ***  C++ fonksiyon argümanlarý ve iþleçlerin iþlenenleri için bir deðerlendirme sýrasý tanýmlamaz.
    ***  Çoðu durumda, C++ ayný ifadede birden fazla kullanýlan bir yan etkisi olan bir nesnenin yan 
    ***  etkilerinin ne zaman uygulanmasý gerektiðini de belirtmez. Bu, ayný ifadede bir nesne daha fazla
    ***  kullanýldýðýnda belirsiz davranýþa yol açabilir.    
    */
    /*
    Virgül Operatörü
    Virgül operatörü (,) bir ifade yerine birden fazla ifadeyi deðerlendirmenize olanak tanýr. Virgül operatörü sol operandý
    deðerlendirir, ardýndan sað operandý deðerlendirir ve son olarak sað operandýn sonucunu döndürür.

    Genellikle, virgül operatörünü kullanarak yazýlan bir ifade, ayrý ifadeler olarak yazýlmýþ bir þekilde daha iyi anlaþýlýr olur.
    Yani, birçok ifadeyi virgül operatörü ile bir arada yazmak yerine her bir ifadeyi ayrý ayrý yazmak, 
    kodun daha okunaklý ve anlaþýlýr olmasýný saðlar. Örneðin, verilen kod, aþaðýdaki gibi daha anlaþýlýr bir þekilde yazýlabilir:
    
    Tabi iþlem önceliðinde en son seviye olmasýndan dolayý da dikkatli olmak gerekir örneðin
    Örnek
    z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.


    Çoðu yazýlýmcý virgül operatörünü kullanmaktan çekinir. En iyi yaklaþým da loop lar dýþýnda 
    virgül operatörünü kullanmaktan çekinmektir

    */

    /*
    int x{ 5 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n';
    */

    /*
    Ternary Operator - Arithmetic if -> ?: - Kullanýmý : (contidion) ? expression1 : expression2; 
    Bu kullanýma göre zaten aritmetik if olarak da bilinir. Condition doðruysa expression1 çalýþtýrýlýr. Aksi takdirde expression 2 çalýþtýrýlýr. 
    Önemli bir nokta expression2 opsiyonel deðildir. Yani kesinlikle deðer döndürmelidir.

    Doðruysa expression 1 çalýþýr yanlýþsa expression 2 çalýþýr. 

    örneðin -> int x = ( condition ) ? expression 1 : expression 2;
    örneðin -> larger = (x > y) ? x : y;

    Tabi burada en önemli þeylerden biri koþul operatörünün iþlem seviyesi çok düþüktür o yüzden her zaman parantez ile kullanýlmasý en iyi harekettir
    
    Tabi burada kullandýðýmýz ifadelerin türleri birbirine eþit olmasý gerek ya da ortak bir türe dönüþtürülebilir türler olmalý 
    örnek -> std::cout<< (x != 5 ) ? x : "x is 5"); -> Bu derlenmez çünkü bir tarafta x yani int deðiþkeni var ikeN 
    diðer tarafta C-style string literali
    var türleri uyumsuz olduðu için bu ifade derlenemeyecektir. Bu gibi durumlarda mecburen if else kalýbý kullanýlmalýdýr.

    */
    
    // ** Fonksiyonlarýn içinde tanýmlanan deðiþkenler fonksiyonun sonunda yok olduðu gibi if else içinde tanýmlanan deðiþkenler de if yada else 
    // ** ifadesinin sonunda sona erer. Koþul ifadeleri bunun gibi durumlarda kullanýlabilir. If else nin kullanýlamayacaðý yerler yani.
    
    /*
    Peki koþul operatörünü ne zaman kullanmalýyýz ? 
     
    ** Koþul operatörünü basit koþul olduðu durumlarda.Sonucun kullanýlabileceði okunabilirliði arttýrabilecek noktalarda kullanmak gerekir 
    * Aksi halde hata yapmaya yatkýn okunaksýz kodlar oluþturmuþ oluruz.
    
    */

    // RELATIONAL OOERATORS AND FLOATING POINT COMPARISIONS
    
    /*Benim çevirim iliþkisel operatörler ve kayan noktalý karþýlaþtýrma
    > , < , >= , <= == != klasik matematiksel karþýlaþtýrmadýr 
    Çokça gördüðümüz için örneðini yazmicam
    */

/*
Boolean koþul deðerleri

burada yeni öðrenenler 
if (b1 == true ) -> gibi þeyler yapýyor ve bu gereksiz bir durum bunun yerine if(b1) yazabiliriz. Çünkü burada ekstra bir deðer sunmadýðýmýz
için bunu yazmak gereksiz oluyor o yüzden okumayý güçleþtiriyor. == != karþýlaþtýrmalarýný tekli ifadelerde kullanmamak ve onun yerine 
!b1 veya b1 -> false ve true için bunlarý kullanmak daha mantýklý. 
*/
    
    /*
    Hesaplanan kayan noktalý sayýlarýn karþýlaþtýrýlmasý sorunlu olabilir. Bunun nedeni de yuvarlama hatalarýdýr 
    Örneðin 100.0 - 99.99 iile 10.0 - 9.99  ikisinin de sonucu 0.01 dir fakat C++ da oluþan yuvarlama hatalarýndan dolayý kullanýmý tehlikelidir. 
    Bunu if else bloðu ile görebiliriz. 
    
    ** tabi bu hesaplanan deðerler arasýnda low-precision yani düþük hassasiyet varsa burda karþýlaþtýrma yapma da her hangi bir sorun yok demektir. 

    Veya bir fonksiyonun dönüþ deðeri 0.0 ise burada direkt karþýlaþtýrma yapýlabilir 

    if (someFunc() == 0.0 ){
        do something 
    }  

    Gibisinden bir örnek verilebilir. 

    ** Veya constexpr double gravity {9.8} gibi bir kayan noktalý sayý; yani deðiþmeyeceði garanti edilmiþ bir literal ise burada da 
    * direkt karþýlaþtýrma yapýlabilir. Üstteki fonksiyon örneði gibi. 
    *
    * Burada karþýlaþtýrma yaparken belirli bir yüzde hatayý kabul ederim dersen sorun yok. Bunun için de klasik karþýlaþtýrma ypaýyor hoca yani 
    * tolerans veriyor hoca. ApproximatelyEqual diyerek relAbs yani Knuth un algoritmasý ve normal algoritma yaptý. Ýþin düþerse 
    * 6.6 ch yi tekrar advanced okuyucular için olan bölümü okursun.
    
    */
    
    // CH 6.7 Logical Operators ye geldik
    /*
    C++ ta 3 tane mantýk operatörü vardýr. ! Logical Not 
                                           && Logical AND
                                           || Logical OR
    Burada en çok yapýlan hata Logical NOT operatörünün iþlem önceliði seviyesinin yüksekliðinden dolayý. Ne demek istediðimi anladýn
    Bu hatalardan kaçýnmak için; Eðer Logical Not operatörünü kullanacaksan kullandýðýn yerde parantezlerle durumu kontrol altýna almalýsýn.


    Logical OR operatöründe yapýlan en büyük yanlýþ ise ona benzeyen Bitwise or operatörü ile karýþtýrýlmasýdýr. 
    || -> Lo. Op.
    |  -> Bi. Op.   Bu þekildedir. Ýkisi farklý fonksiyonlarý yürüttüðü için sonuçlarýn yanlýþ çýkmasýna sebep olabilir. 


    Logical AND operatöründe yapýlan en büyük yanlýþ ise ona benzeyen Bitwise AND operatörü ile karýþtýrýlmasýdýr.
    && -> Lo. Op.
    &  -> Bi. Op.   Bu þekildedir. Ýkisi farklý fonksiyonlarý yürüttüðü için sonuçlarýn yanlýþ çýkmasýna sebep olabilir.

    ** Burada hem Log. Or hem de Log. And kapýlarýný bir den fazla olacak þekilde kullanabiliriz. -> örn: if (value > 10 && value < 20 && value != 16)

    ***Kýsa devre deðerlendirmesi.
    * Burada Logical Or ve Logical And iþlemlerinde sol operatör Or için true olduðunda sonuç true olacaðý için sað operatör deðerlendirilmeden 
    * geçilir. Logical And de de sol operator false olursa sað operatör deðerlendirilmez buna Kýsa devre deðerlendirmesi yani Short Circuit Evaluation
    * denir. Performansla alakalý yerlerde çok iyi olur.
    * ** Burada dikkat edilmesi gereken en önemli nokta yan etkili iþlemlerde örneðin ++x x++ gibi iþlemlerde seri þeklinde logic devrelerde 
    * dikkatli olunmalý en mantýklý hareket bunlarý ayný seride kullanmamaktýr. 
    * Örn: if (x == 1 && ++y == 2)
               // do something

               Yukarýdaki örnekte gördüðün gibi.

    Normalde her hangi bir sýra ile deðerlendirme olurken Logical operatörlerde standart açýkça "ilk olarak sol operatör deðerlendirilir" Demekte.

    Burada kýsa devre yerleþik versiyonlarda olmakta yani overload ederek kendi tipimizi oluþturursak Kýsa devre de yapmayacaktýr. Advanced reader.    
    */
    

    /*
    OR VE AND Kapýlarýnýn karýþýk kullanýmý
    ---------------------------------------
    Burada yeniler AND ve OR kapýlarýnýn ayný iþlem seviyesine sahip olduðunu düþünür + ve - gibi fakat bu noktada 
    yanýlýrlar.
    
    AND kapýsý OR kapýsýndan daha yüksek seviye iþlem önceliðine sahip olduðu için hata yapmaya müsait bir alandýr DÝKKAT !!!!
    
    Buralarda parantezlerle sistemi kontrol etmek hem okunaklýlýðý arttýrýr hem daja iyi kod yazmýþ olursunuz ve hatalarý önler.


    DE MORGAN IN KURALLARI ( Bi salmadýn bizi amk )
    -----------------------------------------------

    Çoðu programcý !(x && y) ifadesinin  !x && !y Bu ifadeye eþit olduðunu düþünür. Fakat, not operatörü iþlemler üzerine de daðýlýr.

    !(x && y) => !x || !y
    !(x || y) => !x && !y  Bu þekilde daðýlýr yani
    

    Kanýt:
    x   	y	    !x  	!y	   !(x || y)  !x && !y
    false	false	true	true	true	    true
    false	true	true	false	false	    false
    true	false	false	true	false	    false
    true	true	false	false	false	    false



    LOGÝCAL XOR
    -----------
    C++ mantýksal bir XOR operatörü saðlamaz (operatör^ mantýksal bir XOR deðil, bit düzeyinde bir XOR'dur).
    Mantýksal VEYA veya mantýksal VE'den farklý olarak mantýksal XOR, kýsa devre olarak deðerlendirilemez.
    Bu nedenle, mantýksal OR ve mantýksal AND operatörlerinden mantýksal bir XOR operatörü oluþturmak zordur.
    Ancak eþitsizlik operatörünü (!=) kullanarak mantýksal XOR'u kolayca taklit edebilirsiniz:

    ÖRNEÐÝN: f (a != b) ... // a XOR b, assuming a and b are Booleans Bu birden çok olabilir. Mesela a XOR b XOR c þeklinde de yapbiliriz
    sadece eklicez.
    *** Burada bilinmesi gereken tek þey þu operandlar yani iþlenenler boolean olmalý integer olmaz.
    * 
    * Ýlla baþka bir type ý kullancam dersen static_cast<bool>(iþlenen) yaparak bool a çevirirsin zaten hepsi çevriliyor.
    
    bazý klavyeler bu iþaretleri desteklemediði için 
    && -> and 
    || -> or
    !  -> not 

    kelimeleri kullanýlabilir. 

    */


    /*
    
           ÖZET
    -----------------
    
    Özeti ordan okumak daha mantýklý geldi o yüzden yazmadým. CH Optional veya CH 7 ye geçecez. 
    */
    
    
    
    
    
    
    
    
    





















    return 0;
}
