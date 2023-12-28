#include <iostream>

int main()
{
    return 0;
}
/*
                                         Opsiyonel Chapterdi ama öðrenmek lazým gibi hissettik

Modern bilgisayar mimarilerinde, hafýzanýn en küçük adreslenebilir birimi bir bayttýr. Tüm nesnelerin benzersiz hafýza adreslerine
sahip olmasý gerektiði için, bu nesnelerin en az bir bayt boyutunda olmasý gerektiði anlamýna gelir. Çoðu deðiþken türü için bu
uygundur. Ancak, Boolean deðerler için bu biraz israftýr . Boolean türleri yalnýzca iki duruma sahiptir:doðru (1) veya yanlýþ (0).
Bu durum setinin saklanmasý yalnýzca bir bit gerektirir. Ancak, bir deðiþkenin en az bir bayt olmasý gerekiyorsa ve bir bayt 8 bit
ise, bu, bir Boolean'ýn 1 biti kullanýp diðer 7'sini kullanmadýðý anlamýna gelir.

Çoðu durumda, bu uygundur - genellikle hafýzada 7 israf biti hakkýnda endiþelenmemiz gerektirecek kadar sýký çalýþmak durumunda deðiliz
(anlaþýlýrlýk ve bakým kolaylýðý için optimize etmek daha iyidir). Ancak, bazý depolama yoðunluðu yüksek durumlarda, depolama
verimliliði amaçlarý için 8 ayrý Boolean deðerini tek bir bayta koyarak paket þeklinde kullanmak yararlý olabilir.
Bu iþlemleri yapabilmemiz için nesneleri bit düzeyinde manipüle edebilmemiz gerekmektedir. Neyse ki, C++ bize bunu yapmak
için araçlar sunar. Bir nesnenin içindeki tekil bitleri deðiþtirmeye bit manipülasyonu denir.

Bit manipülasyonu belirli programlama baðlamlarýnda (örneðin, grafikler, þifreleme, sýkýþtýrma, optimizasyon) çok kullanýlýr, 
ancak genel programlamada o kadar fazla kullanýlmaz.

Bu nedenle bu bölümün tamamý isteðe baðlý olarak okunacaktýr. Atlamaktan veya gözden geçirmekten çekinmeyin ve daha sonra tekrar gelin.

Bit bayraklarý ( Bit Flags )
----------------------------
Bu noktaya kadar deðiþkenleri tek deðerleri tutmak için kullandýk:

                    int foo { 5 }; // foo'ya 5 deðerini atar (muhtemelen 32 bit depolama kullanýr)
                    std::cout << foo; // 5 deðerini yazdýrýr;

Ancak, nesneleri tek bir deðer taþýyan olarak deðil, bunun yerine bireysel bitlerin bir koleksiyonu olarak görebiliriz. Bir nesnenin bireysel 
bitleri Boolean deðerler olarak kullanýldýðýnda, bu bitlere "bit bayraklarý" denir.

Not- Hesaplamada bayrak, bir programda bazý koþullar mevcut olduðunda sinyal veren bir deðerdir. Bit bayraðýyla true deðeri, koþulun var olduðu 
anlamýna gelir.

Benzer þekilde, Amerika Birleþik Devletleri'nde birçok posta kutusunun yan tarafýnda küçük (genellikle kýrmýzý) fiziksel bayraklar bulunur. 
Giden posta taþýyýcý tarafýndan alýnmayý beklerken, giden postanýn olduðunu belirtmek için bayrak kaldýrýlýr.

Bir bit bayraðý kümesini tanýmlamak için genellikle uygun boyutta iþaretsiz bir tamsayý (sahip olduðumuz bayrak sayýsýna baðlý olarak 8 bit, 
16 bit, 32 bit vb.) veya std::bitset kullanýrýz.

                    #include <bitset> // std::bitset için

                    std::bitset<8> mybitset {}; // 8 bit boyutu 8 flag için yer demektir

*** BEST -> Bit manipülasyonu, iþaretsiz tamsayýlarý (veya std::bitset) açýkça kullanmanýz gereken birkaç durumdan biridir.

Bu derste, std::bitset aracýlýðýyla bit manipülasyonunun kolay yoldan nasýl yapýlacaðýný göstereceðiz. Bir sonraki ders setinde 
bunu daha zor ama çok yönlü bir þekilde nasýl yapacaðýmýzý keþfedeceðiz.
                    
Bit numaralandýrma ve bit konumlarý
-----------------------------------
Bir bit dizisi verildiðinde, genellikle bitleri 0'dan (1 deðil) baþlayarak saðdan sola doðru numaralandýrýrýz. Her sayý bir bit konumunu belirtir.

                    76543210  Bit konumlarý
                    00000101  Bit dizisi
0000 0101 bit dizisi verildiðinde, 0 ve 2 konumundaki bitlerin deðeri 1, diðer bitlerin deðeri ise 0'dýr.
                    
Bitleri std::bitset aracýlýðýyla iþlemek
----------------------------------------
std::bitset, bit manipülasyonu yapmak için yararlý olan 4 temel üye fonksiyon saðlar:

                    test(), bir bitin 0 mý yoksa 1 mi olduðunu sorgulamamýzý saðlar.
                    set() , bir biti açmamýza ( 1 yapmak ) izin verir (eðer bit zaten açýksa bu hiçbir þey yapmaz).
                    reset() bir bit i kapatmamýza ( 0 yapmak ) izin verir (eðer bit zaten kapalýysa bu hiçbir iþe yaramaz).
                    flip(), bir bit deðerini 0'dan 1'e veya tam tersi þekilde çevirmemize olanak tanýr.

Bu iþlevlerin her biri, üzerinde çalýþmak istediðimiz bitin konumunu tek argüman olarak alýr. Örneðin:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<8> me{ 0b0000'0101 }; // 8 bit'e ihtiyacýmýz var, bit deseni 0000 0101 ile baþlýyoruz
                        me.set(3);   // 3. pozisyondaki biti 1 olarak ayarla (þimdi 0000 1101)
                        me.flip(4);  // 4. biti ters çevir (þimdi 0001 1101)
                        me.reset(4); // 4. biti tekrar 0'a sýfýrla (þimdi 0000 1101)

                        std::cout << "Tüm bitler: " << me << '\n';
                        std::cout << "3. bitin deðeri: " << me.test(3) << '\n';
                        std::cout << "4. bitin deðeri: " << me.test(4) << '\n';

                        return 0;
                    }

                    Tüm bitler: 00001101
                    3. bitin deðeri: 1
                    4. bitin deðeri: 0

Bitlerimizin adlarýný vermek kodumuzu daha okunaklý hale getirmeye yardýmcý olabilir:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr int  isHungry   { 0 }; // Aç mýyým
                        [[maybe_unused]] constexpr int  isSad      { 1 }; // Üzgün müyüm
                        [[maybe_unused]] constexpr int  isMad      { 2 }; // Kýzgýn mýyým
                        [[maybe_unused]] constexpr int  isHappy    { 3 }; // Mutlu muyum
                        [[maybe_unused]] constexpr int  isLaughing { 4 }; // Gülüyor muyum
                        [[maybe_unused]] constexpr int  isAsleep   { 5 }; // Uykuda mýyým
                        [[maybe_unused]] constexpr int  isDead     { 6 }; // Ölü müyüm
                        [[maybe_unused]] constexpr int  isCrying   { 7 }; // Aðlýyor muyum

                        std::bitset<8> me{ 0b0000'0101 }; // 8 bit'e ihtiyacýmýz var, bit deseni 0000 0101 ile baþlýyoruz
                        me.set(isHappy);      // 3. pozisyondaki biti 1 olarak ayarla (þimdi 0000 1101)
                        me.flip(isLaughing);  // 4. biti ters çevir (þimdi 0001 1101)
                        me.reset(isLaughing); // 4. biti tekrar 0'a sýfýrla (þimdi 0000 1101)

                        std::cout << "Tüm bitler: " << me << '\n';
                        std::cout << "Mutlu muyum: " << me.test(isHappy) << '\n';
                        std::cout << "Gülüyor muyum: " << me.test(isLaughing) << '\n';

                        return 0;
                    }

Ayný anda birden fazla bit almak veya ayarlamak istersek ne olur?
-----------------------------------------------------------------
std::bitset bunu kolaylaþtýrmýyor. Bunu yapabilmek için veya std::bitset yerine iþaretsiz tamsayý bit bayraklarý kullanmak 
istiyorsak daha geleneksel yöntemlere yönelmemiz gerekiyor.

Std::bitset'in boyutu
---------------------
std::bitset'in hýz için optimize edilmiþ olmasýdýr, bellek tasarrufu deðil. Bir std::bitset'in boyutu, genellikle bitleri tutmak için gerekli
olan bayt sayýsýdýr, en yakýn sizeof(size_t)'e yuvarlanmýþtýr. Bu, 32-bit makinelerde 4 bayt ve 64-bit makinelerde 8 bayttýr.

Bu nedenle, bir std::bitset<8>, teknik olarak sadece 8 biti saklamak için 1 bayt'a ihtiyaç duyduðu halde, genellikle 4 veya 8 bayt bellek 
kullanacaktýr. Dolayýsýyla, std::bitset, bellek tasarrufu deðil, kullaným kolaylýðý istediðimizde daha faydalý olacaktýr

std::bitset Sorgulama
---------------------
Sýklýkla kullanýþlý olan birkaç baþka üye fonksiyon bulunmaktadýr:

                    - `size()`, bit kümesindeki bit sayýsýný döndürür.
                    - `count()`, bit kümesinde true olarak ayarlanan bitlerin sayýsýný döndürür. Bu, tüm bitlerin 0 olduðunu veya herhangi bir
                                 bitin 1 olduðunu belirlemek için kullanýlabilir.
                    - `all()`, tüm bitlerin true olarak ayarlanýp ayarlanmadýðýný belirten bir Boolean deðer döndürür.
                    - `any()`, herhangi bir bitin true olarak ayarlanýp ayarlanmadýðýný belirten bir Boolean deðer döndürür.
                    - `none()`, hiçbir bitin true olarak ayarlanýp ayarlanmadýðýný belirten bir Boolean deðer döndürür.

#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'1101 };
    std::cout << bits.size() << " bit bitset içinde bulunmaktadýr\n"; // Bitset içindeki bit sayýsýný yazdýrýr
    std::cout << bits.count() << " bit true olarak ayarlanmýþtýr\n"; // True olarak ayarlanmýþ bit sayýsýný yazdýrýr

    std::cout << std::boolalpha; // Bool deðerlerini yazarken "true" veya "false" yerine "true" veya "false" olarak yazdýrmak için kullanýlýr

    std::cout << "Tüm bitler true olarak ayarlanmýþ mý: " << bits.all() << '\n'; // Tüm bitlerin true olarak ayarlanýp ayarlanmadýðýný kontrol eder
    std::cout << "Bazý bitler true olarak ayarlanmýþ mý: " << bits.any() << '\n'; // Herhangi bir bitin true olarak ayarlanýp ayarlanmadýðýný kontrol eder
    std::cout << "Hiçbir bit true olarak ayarlanmýþ mý: " << bits.none() << '\n'; // Hiçbir bitin true olarak ayarlanýp ayarlanmadýðýný kontrol eder

    return 0;
}

8 bit bitset içinde bulunmaktadýr
3 bit true olarak ayarlanmýþtýr
Tüm bitler true olarak ayarlanmýþ mý: false
Bazý bitler true olarak ayarlanmýþ mý: true
Hiçbir bit true olarak ayarlanmýþ mý: false

Bit iþlemcileri (bitwise operators)
-----------------------------------

| Operatör        | Sembol | Formül  | Ýþlem                                                                       |
|-----------------|--------|---------|-----------------------------------------------------------------------------|
| Sol Kaydýrma    | <<     | x << y  | x içindeki tüm bitler y bit sola kaydýrýlýr                                 |
| Sað Kaydýrma    | >>     | x >> y  | x içindeki tüm bitler y bit saða kaydýrýlýr                                 |
| Bitwise NOT     | ~      | ~x      | x içindeki tüm bitler ters çevrilir                                         |
| Bitwise AND     | &      | x & y   | x içindeki her bir bit, y içindeki ilgili bit ile AND iþlemine tabi tutulur |
| Bitwise OR      | |      | x | y   | x içindeki her bir bit, y içindeki ilgili bit ile OR iþlemine tabi tutulur  |
| Bitwise XOR     | ^      | x ^ y   | x içindeki her bir bit, y içindeki ilgili bit ile XOR iþlemine tabi tutulur |
--------------------------------------------------------------------------------------------------------------------

Aþaðýdaki örneklerde büyük ölçüde 4-bit ikili deðerlerle çalýþacaðýz. Bu, kolaylýk ve örnekleri basit tutma amacýyla yapýlmýþtýr. Gerçek
programlarda, kullanýlan bit sayýsý nesnenin boyutuna baðlýdýr (örneðin, 2 byte bir nesne 16 bit saklar).

Okunabilirlik açýsýndan, 0b önekini (örneðin, 0b0101 yerine sadece 0101 kullanacaðýz) kod örneklerinin dýþýnda atlayacaðýz.

Bit iþlemcileri, tamsayý tipleri ve std::bitset için tanýmlanmýþtýr. Örneklerimizde çýktýyý ikili biçimde yazdýrmak daha kolay olduðu için
std::bitset kullanacaðýz.

Ýþaretli operatörlerle iþlem yaparken C++20'den önce birçok operatör, uygulamaya özgü sonuçlar döndürebilir veya diðer potansiyel sorunlara yol
açabilir. Bu tür sorunlarý önlemek için iþaretsiz operatörleri (veya std::bitset) kullanmak genellikle daha iyidir.

Sürprizleri önlemek için, bit iþlemcilerini iþaretsiz iþlemciler veya std::bitset ile kullanýn.

Bit bazýnda sola kaydýrma (<<) ve bit bazýnda saða kaydýrma (>>) operatörleri
-----------------------------------------------------------------------------

Bitwise left shift (<<) operatörü, bitleri sola kaydýrýr. Sol operand, bitleri kaydýrmak için ifadeyi temsil eder ve sað operand, sola kaç
bit kaydýrýlacaðýný belirten bir tamsayýdýr.

Yani x << 1 dediðimizde, "deðiþken x içindeki bitleri bir yer sola kaydýr" diyoruz. Sað taraftan kaydýrýlan yeni bitlere 0 deðeri atanýr.

Örneðin:

0011 << 1, 0110'dýr.
0011 << 2, 1100'dir.
0011 << 3, 1000'dir.
Üçüncü durumda dikkat edilmesi gereken önemli bir nokta, sayýnýn sonundan bir bitin kaydýrýlmasýdýr! Binary sayýnýn sonundan kaydýrýlan bitler
kalýcý olarak kaybolur.

Bitwise right shift (>>) operatörü ise bitleri saða kaydýrýr.

Örneðin:

1100 >> 1, 0110'dýr.
1100 >> 2, 0011'dir.
1100 >> 3, 0001'dir.
Üçüncü durumda dikkat edilmesi gereken bir baþka önemli nokta, sayýnýn sað ucundan bir bitin kaydýrýlmasýdýr ve bu bit kaybolur.

Ýþte bir bit kaydýrma örneði:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> x{0b1100};

                        std::cout << x << '\n'; // x'i binary olarak yazdýr
                        std::cout << (x >> 1) << '\n'; // 1 saða kaydýr, sonuç: 0110
                        std::cout << (x << 1) << '\n'; // 1 sola kaydýr, sonuç: 1000

                        return 0;
                    }
                    Çýktý: 
                    1100
                    0110
                    1000

Nasýl!? operator<< ve operator>> giriþ ve çýkýþ için kullanýlmýyor mu?
----------------------------------------------------------------------

Evet, kesinlikle.

Günümüzde, programlar genellikle bitleri kaydýrmak için bitiþik sola ve saða kaydýrma operatörlerini çokça kullanmazlar. Bunun yerine,
genellikle bitwise sola kaydýrma operatörü, std::cout (veya diðer akýþ nesneleri) ile metin çýktýsý almak için kullanýlýr. Aþaðýdaki 
programý düþünün:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        unsigned int x{0b0100};
                        x = x << 1; // Sol kaydýrma için operator<< kullan
                        std::cout << std::bitset<4>{x} << '\n'; // Çýktý için operator<< kullan

                        return 0;
                    }
                    Çýktýsý:
                    1000


Yukarýdaki programda, operator<<'in bir durumda bitleri kaydýrmak, diðer durumda ise x'i çýktý olarak göstermek için nasýl çalýþtýðýný nasýl
anlýyor? Cevap þudur: std::cout, operator<<'in aþýrý yüklenmiþ (alternatif bir taným saðlamýþ) versiyonuna sahiptir ve bu versiyon, bit kaydýrma
yerine konsol çýktýsý yapar.

Derleyici, operator<<'in sol operandýnýn std::cout olduðunu gördüðünde, std::cout tarafýndan aþýrý yüklenmiþ olan ve çýktý yapmak için kullanýlan
operator<< versiyonunu çaðýrmasý gerektiðini bilir. Eðer sol operand integral bir tür ise, operator<<, genellikle yaptýðý bit kaydýrma
davranýþýný gerçekleþtirmesi gerektiðini bilir.

Aynýsý operator>> için de geçerlidir.

Unutmayýn ki hem çýktý hem de sola kaydýrma için operator<< kullanýyorsanýz, parantez içine almak gereklidir:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> x{ 0b0110 };

                        std::cout << x << 1 << '\n'; // x'in deðerini (0110) yazdýr, ardýndan 1'i ekle ve yeni satýra geç
                        std::cout << (x << 1) << '\n'; // x'i 1 sola kaydýrýlmýþ halini (1100) yazdýr ve yeni satýra geç

                        return 0;
                    }

                    Çýktýsý:
                    01101
                    1100    

Ýlk satýr, x'in deðerini (0110) ve ardýndan 1 sayýsýný yazdýrýr. Ýkinci satýr ise x'in 1 sola kaydýrýlmýþ deðerini (1100) yazdýrýr.

Operator aþýrý yüklenmesi hakkýnda daha fazla bilgi, kendi amaçlarýnýz için operatörleri nasýl aþýrý yükleyeceðiniz konusunda
gelecekteki bir bölümde tartýþýlacaktýr.

Bitwise NOT
-----------
Bitwise NOT (~) operatörü, belki de tüm bitwise operatörlerin en kolay anlaþýlabileni olabilir. Bu operatör, her bir biti basitçe 0'dan 1'e veya
tam tersine çevirir. Unutmayýn ki bitwise NOT'un sonucu veri tipinizin boyutuna baðlýdýr.

4 bit çevirme:
~0100, 1011'dir

8 bit çevirme:
~0000 0100, 1111 1011'dir

Hem 4 bit hem de 8 bit durumlarýnda, ayný sayýyla baþlarýz (binary 0100, decimal 7'nin 07 ile ayný olduðu gibi), ancak farklý bir sonuç elde ederiz.

Bunu aþaðýdaki programda görebiliriz:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << ~std::bitset<4>{ 0b0100 } << ' ' << ~std::bitset<8>{ 0b0100 } << '\n';

                        return 0;
                    }
                    Çýktý olarak:
                    1011 11111011
Bitwise OR
----------

Bitwise OR (|) mantýksal OR operatörünün benzer þekilde çalýþýr. Ancak, OR operatörünü kullanarak operatörleri tek bir sonuç üretmek yerine,
bitwise OR her bir bite uygular! Örneðin, ifade 0b0101 | 0b0110'ý düþünün.

Herhangi bir bitwise iþlemi yapmak için, iki operandý þu þekilde hizalamak en kolaydýr:

                    0 1 0 1 OR
                    0 1 1 0

Ve sonra iþlemi her bit sütununa uygula.

Hatýrlarsanýz, mantýksal OR, sol operandýn, sað operandýn veya her ikisinin de doðru (1) olduðu durumda doðru (1) olarak deðerlendirilir ve aksi
takdirde 0'dýr. Bitwise OR ise sol, sað veya her ikisi de 1 olduðunda 1'e ve aksi takdirde 0'a deðerlendirilir. Bu nedenle, ifade þu þekilde
deðerlendirilir:

                    0 1 0 1 OR
                    0 1 1 0
                    -------
                    0 1 1 1

                    Sonucumuz 0111 ikilisidir.

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0101 } | std::bitset<4>{ 0b0110 }) << '\n';

                        return 0;
                    }
                    Çýktý olarak:
                    0111

Ayný þeyi 0b0111 | gibi OR ifadelerini bileþik hale getirmek için de yapabiliriz. 0b0011 | 0b0001. Bir sütundaki bitlerden herhangi biri 1 ise 
o sütunun sonucu 1 olur.

                    0 1 1 1 OR
                    0 0 1 1 OR
                    0 0 0 1
                    --------
                    0 1 1 1
                    Ýþte yukarýdakilerin kodu:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0111 } | std::bitset<4>{ 0b0011 } | std::bitset<4>{ 0b0001 }) << '\n';

                        return 0;
                    }
                    Çýktý:
                    0111
                    
Bitwise AND
-----------

Bitwise AND (&) yukarýdakine benzer þekilde çalýþýr. Mantýksal AND, sol operand ve sað operand ikisi de doðru (1) olduðunda doðru olarak
deðerlendirilir. Bitwise AND ise sütundaki her iki bit de 1 ise 1'e deðerlendirilir. 0b0101 & 0b0110 ifadesini düþünün. Her bir biti hizalayýp
her bit sütunu için AND iþlemi uygulayarak:

                    0 1 0 1 AND
                    0 1 1 0
                    --------
                    0 1 0 0

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0101 } & std::bitset<4>{ 0b0110 }) << '\n';

                        return 0;
                    }
                    Çýktý:
                    0100

Benzer þekilde, 0b0001 & 0b0011 & 0b0111 gibi AND ifadelerini bileþik hale getirmek için de ayný þeyi yapabiliriz. Bir sütundaki tüm bitler 1 
ise o sütunun sonucu 1 olur.

                    0 0 0 1 AND
                    0 0 1 1 AND
                    0 1 1 1
                    --------
                    0 0 0 1

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::cout << (std::bitset<4>{ 0b0001 } & std::bitset<4>{ 0b0011 } & std::bitset<4>{ 0b0111 }) << '\n';

                        return 0;
                    }
                    Çýktý:
                    0001

Bitwise XOR
-----------

Son operatör, bitwise XOR (^) veya diðer adýyla exclusive or (özel veya) olarak bilinen operatördür.

Ýki operandý deðerlendirirken, XOR, operandlardan biri ve sadece biri doðru (1) ise doðru olarak deðerlendirilir. Eðer ikisi de 
doðru veya ikisi de yanlýþ ise 0 olarak deðerlendirilir. 0b0110 ^ 0b0011 ifadesini düþünün:

                    0 1 1 0 XOR
                    0 0 1 1
                    -------
                    0 1 0 1

0b0001 ^ 0b0011 ^ 0b0111 gibi bileþik XOR ifadesi sütun stilini de deðerlendirmek mümkündür. Bir sütunda çift sayýda 1 bit varsa sonuç 0
olur. Bir sütunda tek sayýda 1 bit varsa sonuç 1 olur.
                    0 0 0 1 XOR
                    0 0 1 1 XOR
                    0 1 1 1
                    --------
                    0 1 0 1

Bitsel atama operatörleri
-------------------------
Aritmetik atama operatörlerine benzer þekilde C++, deðiþkenlerin kolay deðiþtirilmesini kolaylaþtýrmak için bit düzeyinde atama operatörleri saðlar.

| Operatör                   | Sembol | Form      | Ýþlem                                       |
|----------------------------|--------|-----------|---------------------------------------------|
| Sol kaydýrma atama         | <<=    | x <<= y   | x'i y bit sola kaydýr                       |
| Sað kaydýrma atama         | >>=    | x >>= y   | x'i y bit saða kaydýr                       |
| Bitwise OR atama           | |=     | x |= y    | x'i x | y'ye atar                           |
| Bitwise AND atama          | &=     | x &= y    | x'i x & y'ye atar                           |
| Bitwise XOR atama          | ^=     | x ^= y    | x'i x ^ y'ye atar                           |
|----------------------------|--------|-----------|---------------------------------------------|

Örneðin x = x >> 1; yazmak yerine x >>= 1; yazabilirsiniz.

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        std::bitset<4> bits { 0b0100 };
                        bits >>= 1;
                        std::cout << bits << '\n';

                        return 0;
                    }
                    Çýktý:
                    0010

Bitwise NOT atama operatörü yoktur. Bu, diðer bitwise operatörlerinin ikili (binary) olmasýna karþýn, bitwise NOT'un tekil (unary) olmasý
nedeniyledir (yani bir ~= operatörünün sað tarafýnda ne olacaktýr?). Eðer tüm bitleri çevirmek istiyorsanýz, burada normal atama
kullanabilirsiniz: x = ~x;

Özet

Bitwise operasyonlarý sütun yöntemini kullanarak nasýl deðerlendireceðimizi özetleyerek:

Bitwise OR deðerlendirilirken, bir sütundaki herhangi bir bit 1 ise, o sütunun sonucu 1'dir.
Bitwise AND deðerlendirilirken, bir sütundaki tüm bitler 1 ise, o sütunun sonucu 1'dir.
Bitwise XOR deðerlendirilirken, bir sütunda tek sayýda 1 biti varsa, o sütunun sonucu 1'dir.
Bir sonraki derste, bu operatörlerin nasýl bit maskeleriyle birlikte kullanýlabileceðini ve bit manipülasyonunu nasýl kolaylaþtýrdýðýný
keþfedeceðiz

O.3 – Bitsel operatörler ve bit maskeleriyle bit manipülasyonu
--------------------------------------------------------------
Bu ders operatörlerin nasýl daha yaygýn bir þekilde kullanýldýðýna bir göz atalým.

Bit Maskeleri
-------------

Bireysel bitleri manipüle etmek (örneðin, açmak veya kapatmak) için belirli bitleri tanýmlamanýn bir yolu olmalýdýr. Ne yazýk ki, bitwise
operatörler bit pozisyonlarýyla nasýl çalýþacaklarýný bilmezler. Bunun yerine, bit maskeleri ile çalýþýrlar.

Bir bit maskesi, ardýþýk iþlemler tarafýndan deðiþtirilecek belirli bitleri seçmek için kullanýlan önceden tanýmlanmýþ bir bit kümesidir.

Gerçek bir örnek düþünün: Bir pencere çerçevesini boyamak istiyorsunuz. Dikkatli olmazsanýz, sadece pencere çerçevesini deðil, ayný zamanda camý
da boyama riskiyle karþýlaþýrsýnýz. Camý ve boyanmasýný istemediðiniz diðer kýsýmlarý belirleyip maskeleme bandý uygulayabilirsiniz. Sonra 
boyadýðýnýzda, maskeleme bandý boyanmasýný istemediðiniz her þeyi engeller. Sonuç olarak, sadece maskeleme yapýlmayan kýsýmlar
(boyanmasýný istediðiniz kýsýmlar) boyanýr.

Bir bit maskesi, bitler için esasen ayný iþlevi yerine getirir. Bit maskesi, bitwise operatörleri istenmeyen bitlere dokunmaktan alýkoyar ve
deðiþtirmek istediðimizlere eriþim saðlar.

Önce basit birkaç bit maskesini nasýl tanýmlayacaðýmýzý keþfedin, ardýndan onlarý nasýl kullanacaðýnýzý göstereceðiz.

C++14'te Bit Maskelerini Tanýmlama
----------------------------------

En basit bit maskesi seti, her bir bit pozisyonu için bir bit maskesi tanýmlamaktýr. Ýlgilenmediðimiz bitleri maskelemek için 0'larý kullanýrýz ve
deðiþtirmek istediðimiz bitleri belirtmek için 1'leri kullanýrýz.

Bit maskeleri literal olabilir, ancak genellikle anlamlý bir isim verilebilmesi ve kolayca yeniden kullanýlabilmesi için sembolik sabitler olarak
tanýmlanýrlar.

C++14, ikili literalleri desteklediði için bu bit maskelerini tanýmlamak kolaydýr:

                    #include <cstdint>

                    // Bit maskelerini tanýmla
                    constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                    constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                    constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                    constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                    constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                    constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                    constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                    constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

Artýk her bit konumunu temsil eden bir dizi sembolik sabitimiz var. Bunlarý bitleri deðiþtirmek için kullanabiliriz (bunun nasýl yapýlacaðýný
birazdan göstereceðiz).

C++11 veya daha önceki sürümlerde Bit Maskelerini Tanýmlama
-----------------------------------------------------------

C++11, ikili literalleri desteklemediði için sembolik sabitleri ayarlamak için baþka yöntemler kullanmamýz gerekiyor. Bu iþi yapmanýn
iki iyi yöntemi bulunmaktadýr.

Ýlk yöntem, onaltýlýk literalleri kullanmaktýr.

Hexadecimal	   0	 1	      2	      3      4       5        6       7	      8	      9	      A       B	      C	      D	      E	      F
Binary	     0000	0001	0010	0011	0100	0101	0110	0111	1000	1001	1010	1011	1100	1101	1110	1111

Bu nedenle, bit maskelerini onaltýlýk sayý kullanarak þu þekilde tanýmlayabiliriz:

                    constexpr std::uint8_t mask0{ 0x01 }; // 0000 0001 için onaltýlýk
                    constexpr std::uint8_t mask1{ 0x02 }; // 0000 0010 için onaltýlýk
                    constexpr std::uint8_t mask2{ 0x04 }; // 0000 0100 için onaltýlýk
                    constexpr std::uint8_t mask3{ 0x08 }; // 0000 1000 için onaltýlýk
                    constexpr std::uint8_t mask4{ 0x10 }; // 0001 0000 için onaltýlýk
                    constexpr std::uint8_t mask5{ 0x20 }; // 0010 0000 için onaltýlýk
                    constexpr std::uint8_t mask6{ 0x40 }; // 0100 0000 için onaltýlýk
                    constexpr std::uint8_t mask7{ 0x80 }; // 1000 0000 için onaltýlýk


Bazen önceden gelen onaltýlýk 0'lar atlanabilir (örneðin, 0x01 yerine sadece 0x1 görürsünüz). Her iki durumda da, bu, onaltýlýk-birlik dönüþüne 
aþina deðilseniz biraz zor okunabilir olabilir.

Daha kolay bir yöntem, tek bir biti uygun konuma kaydýrmak için sol kaydýrma operatörünü kullanmaktýr:

                    constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
                    constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
                    constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
                    constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
                    constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
                    constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
                    constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
                    constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000

Bir biti test etme (açýk veya kapalý olduðunu kontrol etme)
-----------------------------------------------------------

Artýk bir dizi bit maskemiz olduðuna göre, bu maskeleri bit bayrak deðiþkeniyle birleþtirerek bit bayraklarýmýzý deðiþtirebiliriz.

Bir bitin açýk veya kapalý olup olmadýðýný belirlemek için, uygun bit maskesi ile bitiþikte bitwise AND kullanýrýz:

#include <cstdint>
#include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bit boyutunda, 8 bayrak için yer var

                        std::cout << "bit 0 " << (static_cast<bool>(flags & mask0) ? "açýk\n" : "kapalý\n");
                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "açýk\n" : "kapalý\n");

                        return 0;
                    }
                    Çýktý:
                    bit 0 is açýk
                    bit 1 is kapalý

Bunu nasýl çalýþtýðýný inceleyelim.

flags & mask0 durumunda, 0000'0101 & 0000'0001'e sahibiz. Bunlarý hizalayalým:
                    flags:   0000 0101 &
                    mask0:   0000 0001
                    -----------------
                    sonuç:   0000 0001

Sonra 0000'0001'i bir bool'e dönüþtürüyoruz. Çünkü herhangi bir sýfýr olmayan sayý true'ya dönüþür ve bu deðer bir sýfýr olmayan bir basamaða
sahip olduðu için bu, true olarak deðerlendirilir.

flags & mask1 durumunda, 0000'0101 & 0000'0010'a sahibiz. Bunlarý hizalayalým:

                    0000'0101 &
                    0000'0010
                    ---------
                    0000'0000

Sýfýr deðeri false deðerine dönüþtüðünden ve bu deðer yalnýzca sýfýr basamaktan oluþtuðundan, bu false olarak deðerlendirilir.

Bir bit i açmak ( Set )
-----------------------
Bir biti (deðeri 1'e çevirmek) açmak için, uygun bit için bit maskesi ile bitwise OR equals (operator |=) kullanýrýz:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bitlik bir alan, 8 bayrak için yer

                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "açýk\n" : "kapalý\n");

                        flags |= mask1; // 1. bit'i aç

                        std::cout << "bit 1 " << (static_cast<bool>(flags & mask1) ? "açýk\n" : "kapalý\n");

                        return 0;
                    }
                    Çýktý:
                    bit 1 is kapalý
                    bit 1 is açýk

Bitwise OR kullanarak ayný anda birden fazla biti de açabiliriz:

                    flags |= (mask4 | mask5); // 4 ve 5. bitleri ayný anda açýyoruz

Bir bit i kapatmak ( resetting ) 
--------------------------------
Bir biti (0 deðerine) kapatmak (temizlemek) için Bitwise AND ve Bitwise NOT'u birlikte kullanýrýz:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // bit 0'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // bit 1'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // bit 2'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // bit 3'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // bit 4'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // bit 5'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // bit 6'ý temsil eder 
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // bit 7'ý temsil eder 

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bit boyutu, 8 bayrak için yer anlamýna gelir

                        std::cout << "bit 2: " << (static_cast<bool>(flags & mask2) ? "açýk\n" : "kapalý\n");

                        flags &= ~mask2; // bit 2 yi kapat

                        std::cout << "bit 2: " << (static_cast<bool>(flags & mask2) ? "açýk\n" : "kapalý\n");

                        return 0;
                    }

                    Çýktý:
                    bit 2: açýk
                    bit 2: kapalý

Ayný anda birden fazla biti kapatabiliriz:

                    flags &= ~(maske4 | maske5); // 4 ve 5. bitleri ayný anda kapatýyoruz

Bazý derleyiciler bu durumda uyarý verebilir çünkü signed bir deðeri unsigned deðere dönüþtürüyoruz bu da narrowing conversion olur. 
Bu durumu atlatmak için static_cast<>() yaparak çözebiliriz. 

Bir biti çevirme
----------------
Bir bit durumunu (0'dan 1'e veya 1'den 0'a) deðiþtirmek için Bitwise XOR kullanýrýz:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::uint8_t flags{ 0b0000'0101 }; // 8 bitlik boyut, 8 bayrak için yer demektir

                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "açýk\n" : "kapalý\n");
                        flags ^= mask2; // 2. bit'i çevir
                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "açýk\n" : "kapalý\n");
                        flags ^= mask2; // 2. bit'i çevir
                        std::cout << "2. bit " << (static_cast<bool>(flags & mask2) ? "açýk\n" : "kapalý\n");

                        return 0;
                    }
                    Çýktý:
                    bit 2 açýk
                    bit 2 kapalý
                    bit 2 açýk

Ayný anda birden fazla biti çevirebiliriz:
                    flags ^= (mask4 | mask5); // 4 ve 5. bitleri ayný anda çevir

Bit maskeleri ve std::bitset
----------------------------
std::bitset, tam bir bit iþlemcisi setini destekler. Bu nedenle, bireysel bitleri deðiþtirmek için fonksiyonlarý (test, set, reset ve flip) 
kullanmak daha kolay olsa da, isterseniz bit iþlemcileri ve bit maskelerini kullanabilirsiniz.

Neden istersiniz? Fonksiyonlar yalnýzca bireysel bitleri deðiþtirmenize izin verir. Bit iþlemcileri size ayný anda birden çok biti
deðiþtirme olanaðý tanýr.

                    #include <bitset>
                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        [[maybe_unused]] constexpr std::bitset<8> mask0{ 0b0000'0001 }; // 0. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask1{ 0b0000'0010 }; // 1. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask2{ 0b0000'0100 }; // 2. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask3{ 0b0000'1000 }; // 3. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask4{ 0b0001'0000 }; // 4. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask5{ 0b0010'0000 }; // 5. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask6{ 0b0100'0000 }; // 6. bit'i temsil eder
                        [[maybe_unused]] constexpr std::bitset<8> mask7{ 0b1000'0000 }; // 7. bit'i temsil eder

                        std::bitset<8> flags{ 0b0000'0101 }; // 8 bitlik boyut, 8 bayrak için yer demektir
                        std::cout << "1. bit " << (flags.test(1) ? "açýk\n" : "kapalý\n");
                        std::cout << "2. bit " << (flags.test(2) ? "açýk\n" : "kapalý\n");

                        flags ^= (mask1 | mask2); // 1. ve 2. bitleri çevir
                        std::cout << "1. bit " << (flags.test(1) ? "açýk\n" : "kapalý\n");
                        std::cout << "2. bit " << (flags.test(2) ? "açýk\n" : "kapalý\n");

                        flags |= (mask1 | mask2); // 1. ve 2. bitleri aç
                        std::cout << "1. bit " << (flags.test(1) ? "açýk\n" : "kapalý\n");
                        std::cout << "2. bit " << (flags.test(2) ? "açýk\n" : "kapalý\n");

                        flags &= ~(mask1 | mask2); // 1. ve 2. bitleri kapat
                        std::cout << "1. bit " << (flags.test(1) ? "açýk\n" : "kapalý\n");
                        std::cout << "2. bit " << (flags.test(2) ? "açýk\n" : "kapalý\n");

                        return 0;
                    }

                    Çýktý:
                    bit 1 kapalý
                    bit 2 açýk
                    bit 1 açýk
                    bit 2 kapalý
                    bit 1 açýk
                    bit 2 açýk
                    bit 1 kapalý
                    bit 2 kapalý

Bit maskelerini anlamlý hale getirme

Bit maskelerimize "mask1" veya "mask2" gibi isimler vermek bize hangi bitin manipüle edildiðini söyler, ancak bu bit bayraðýnýn aslýnda ne
için kullanýldýðýna dair herhangi bir gösterge vermez.

*** BEST -> bit bayraklarýnýn anlamýný belgeleme amacýyla bit maskelerine anlamlý isimler vermektedir. Ýþte yazabileceðimiz bir oyundan örnek:

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        // Bir dizi fiziksel/duygusal durumu tanýmla
                        [[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
                        [[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
                        [[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
                        [[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
                        [[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
                        [[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
                        [[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
                        [[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

                        std::uint8_t me{}; // Baþlangýçta tüm bayraklar/konfigürasyonlar kapalý
                        me |= (isHappy | isLaughing); // Mutlu ve gülüyorum
                        me &= ~isLaughing; // Artýk gülümsemiyorum

                        // Birkaç durumu sorgula
                        // (Sonuçlarý boolean bir deðer olarak yorumlamak için static_cast<bool> kullanacaðýz)
                        std::cout << std::boolalpha; // 1 veya 0 yerine true veya false yazdýr
                        std::cout << "Mutluyum mu? " << static_cast<bool>(me & isHappy) << '\n';
                        std::cout << "Gülüyor muyum? " << static_cast<bool>(me & isLaughing) << '\n';

                        return 0;
                    }
Std::bitset kullanýlarak uygulanan ayný örnek:

                    #include <bitset>
                    #include <iostream>

                    int main()
                    {
                        // Bir dizi fiziksel/duygusal durumu tanýmla
                        [[maybe_unused]] constexpr std::bitset<8> isHungry   { 0b0000'0001 };
                        [[maybe_unused]] constexpr std::bitset<8> isSad      { 0b0000'0010 };
                        [[maybe_unused]] constexpr std::bitset<8> isMad      { 0b0000'0100 };
                        [[maybe_unused]] constexpr std::bitset<8> isHappy    { 0b0000'1000 };
                        [[maybe_unused]] constexpr std::bitset<8> isLaughing { 0b0001'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isAsleep   { 0b0010'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isDead     { 0b0100'0000 };
                        [[maybe_unused]] constexpr std::bitset<8> isCrying   { 0b1000'0000 };

                        std::bitset<8> me{}; // Baþlangýçta tüm bayraklar/konfigürasyonlar kapalý
                        me |= (isHappy | isLaughing); // Mutlu ve gülüyorum
                        me &= ~isLaughing; // Artýk gülümsemiyorum

                        // Birkaç durumu sorgula (any() fonksiyonunu kullanarak herhangi bir bitin ayarlý olup olmadýðýný kontrol ediyoruz)
                        std::cout << std::boolalpha; // 1 veya 0 yerine true veya false yazdýr
                        std::cout << "Mutluyum mu? " << (me & isHappy).any() << '\n';
                        std::cout << "Gülüyor muyum? " << (me & isLaughing).any() << '\n';

                        return 0;
                    }

Ýki not burada: Ýlk olarak, std::bitset, bit maskelerini kullanarak bit sorgulamak için güzel bir fonksiyona sahip deðildir. Bu nedenle,
konumsal dizinler yerine bit maskelerini kullanmak istiyorsanýz, Bitwise AND'i kullanarak bitleri sorgulamanýz gerekecek. Ýkinci olarak,
any() fonksiyonunu kullanýyoruz, bu fonksiyon herhangi bir bit ayarlýysa true döndürür ve aksi takdirde false döndürür, böylece sorguladýðýmýz
bitin açýk veya kapalý olup olmadýðýný kontrol edebiliriz.

Bit bayraklarý en çok benzer bayrak deðiþkenlerinizin çok sayýda olduðu durumlarda anlam kazanýr. Yukarýdaki örneklerde dikkat eden okuyucular,
aslýnda hiçbir bellek tasarrufu yapýlmadýðýný fark edebilirler. Normalde 8 ayrý boolean deðeri 8 byte alýrdý. Ancak yukarýdaki örnekler 
(std::uint8_t kullanarak) 9 byte kullanýyor - 8 byte bit maskeleri tanýmlamak için ve 1 byte bayrak deðiþkeni için!

Bit bayraklarý, birçok benzer bayrak deðiþkeniniz olduðunda en mantýklýdýr. Örneðin, yukarýdaki örnekte olduðu gibi, bir kiþi (ben) yerine 100
kiþinizin olduðunu hayal edin. Her bir kiþi için 8 booleen kullanýrsanýz (her bir olasý durum için bir tane), 800 byte bellek kullanýrdýnýz.
Bit bayraklarý kullanarak, 8 byte'lýk bit maskeleri ve 100 byte'lýk bit bayrak deðiþkenleri kullanýrsýnýz, toplamda 108 byte bellek kullanýmý
olur - yaklaþýk olarak 8 kat daha az bellek.

Çoðu program için, bit bayraklarý kullanarak tasarruf edilen bellek miktarý, eklenen karmaþýklýðý haklý çýkarmaz. Ancak on binlerce veya 
milyonlarca benzer nesnenin bulunduðu programlarda, bit bayraklarý kullanmak bellek kullanýmýný önemli ölçüde azaltabilir. Ýhtiyaç duyulduðunda 
kullanýlabilen yararlý bir optimizasyon aracýdýr.

Bit bayraklarý ve bit maskelerinin mantýklý olabileceði baþka bir durum daha vardýr. Diyelim ki 32 farklý seçeneði alabilen bir fonksiyonunuz
var. Bu fonksiyonu yazmanýn bir yolu, 32 ayrý boolean parametre kullanmaktýr.
örnek: 

void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8, bool option9, 
bool option10, bool option11, bool option12, bool option13, bool option14, bool option15, bool option16, bool option17, bool option18, 
bool option19, bool option20, bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27,
bool option28, bool option29, bool option30, bool option31, bool option32);


Umuyorum ki parametrelerinize daha açýklayýcý isimler verirsiniz, ancak buradaki amaç parametre listesinin ne kadar uzun olduðunu göstermektir.

Sonra fonksiyonu 10 ve 32 numaralý seçeneklerin true olarak ayarlandýðý bir çaðrý yapmak istediðinizde, bunu þu þekilde yapmanýz gerekirdi:

someFunction(false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false, false, false, false, false, true);


Bu okumasý oldukça zor (true olarak ayarlanan seçenek 9, 10 veya 11 mi?), ve ayný zamanda hangi argümanýn hangi seçeneðe karþýlýk geldiðini
hatýrlamanýzý gerektirir ("düzenleme bayraðýný" 9., 10. veya 11. parametre mi ayarlýyoruz?).

Bunun yerine, eðer fonksiyonu þu þekilde bit bayraklarý kullanarak tanýmlarsanýz:

                        void someFunction(std::bitset<32> options);

Daha sonra yalnýzca istediðiniz seçenekleri iletmek için bit bayraklarýný kullanabilirsiniz:

                        someFunction(option10 | option32);


Bu çok daha okunaklý.

Bu, OpenGL'in, sayýsýz ardýþýk Boolean parametre yerine bit bayrak parametrelerini kullanmayý tercih ettiði nedenlerden biridir.

Ýþte OpenGL'den bir örnek fonksiyon çaðrýsý:

                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // rengi ve derinlik arabelleðini temizle

GL_COLOR_BUFFER_BIT ve GL_DEPTH_BUFFER_BIT, aþaðýdaki gibi tanýmlanan bit maskeleridir (gl2.h dosyasýnda):

                        #define GL_DEPTH_BUFFER_BIT               0x00000100
                        #define GL_STENCIL_BUFFER_BIT             0x00000400
                        #define GL_COLOR_BUFFER_BIT               0x00004000

Çoklu bitleri içeren bit maskeleri
----------------------------------
Genellikle bit maskeleri tek bir biti seçmek için kullanýlsa da, ayný zamanda birden çok biti seçmek için de kullanýlabilirler. Bunu yaparken
biraz daha karmaþýk bir örneðe bakalým.

TV'ler ve monitörler gibi renkli görüntü cihazlarý, her biri bir renk noktasýný görüntüleyebilen milyonlarca pikselden oluþur. Her renk noktasý,
üç ýþýn kombinasyonunun bir sonucudur: bir kýrmýzý, bir yeþil ve bir mavi (RGB). Bu ýþýnlarýn yoðunluðu, farklý renkleri üretmek için deðiþtirilir.

Genellikle, belirli bir piksel için R, G ve B'nin yoðunluðu 8 bitlik iþaretsiz bir tamsayý tarafýndan temsil edilir. Örneðin, kýrmýzý bir pikselin
R=255, G=0, B=0 olabilir. Mor bir pikselin R=255, G=0, B=255 olabilir. Orta gri bir pikselin R=127, G=127, B=127 olabilir.

Bir piksele renk deðerleri atandýðýnda, R, G ve B'nin yaný sýra genellikle bir 4. deðer olan A da kullanýlýr. "A", "alfa"nýn kýsaltmasýdýr ve 
rengin ne kadar saydam olduðunu kontrol eder. Eðer A=0 ise, renk tamamen þeffaftýr. Eðer A=255 ise, renk opaktýr.

Genellikle, R, G, B ve A bir tamsayýda tek bir 32 bitlik tamsayý olarak depolanýr, her bir bileþen için 8 bit kullanýlýr:

                    | Bits 31-24 | Bits 23-16 | Bits 15-8 | Bits 7-0     |
                    |------------|------------|-----------|--------------|
                    | RRRRRRRR   | GGGGGGGG   | BBBBBBBB  | AAAAAAAAA    |
                    | Red        | Green      | Blue      | Alpha        |


Aþaðýdaki program, kullanýcýdan 32 bitlik onaltýlýk bir deðer girmesini ister ve ardýndan R, G, B ve A için 8 bitlik renk deðerlerini çýkarýr.

                    #include <cstdint>
                    #include <iostream>

                    int main()
                    {
                        // Kýrmýzý (Red), Yeþil (Green), Mavi (Blue) ve Alfa (Alpha) bileþenlerini maskelemek için kullanýlan bit maskeleri
                        constexpr std::uint32_t redBits{ 0xFF000000 };
                        constexpr std::uint32_t greenBits{ 0x00FF0000 };
                        constexpr std::uint32_t blueBits{ 0x0000FF00 };
                        constexpr std::uint32_t alphaBits{ 0x000000FF };

                        // Kullanýcýdan 32-bit RGBA renk deðerini onaltýlýk (hexadecimal) olarak girmesini isteyen bir çýkýþ
                        std::cout << "Onaltýlýk (hexadecimal) olarak bir 32-bit RGBA renk deðeri girin (örn. FF7F3300): ";
                        std::uint32_t pixel{};
                        std::cin >> std::hex >> pixel; // std::hex, onaltýlýk bir deðeri okumamýza izin verir

                        // Bitwise AND kullanarak verilen rengin piksellerini izole etmek,
                        // ardýndan deðeri alt 8 bit içine saða kaydýrmak için kullanýlýr
                        std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
                        std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
                        std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
                        std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

                        // Kullanýcýnýn rengini içerdiði mesajý
                        std::cout << "Renk içeriyor:\n";
                        std::cout << std::hex; // Aþaðýdaki deðerleri onaltýlýk olarak yazdýrmak için

                        // Hatýrlatma: std::uint8_t muhtemelen bir char olarak yazdýrýlýr
                        // Bu, onu bir tam sayý olarak yazdýrmak için static_cast kullanmamýzý saðlar
                        std::cout << static_cast<int>(red)   << " kýrmýzý\n";
                        std::cout << static_cast<int>(green) << " yeþil\n";
                        std::cout << static_cast<int>(blue)  << " mavi\n";
                        std::cout << static_cast<int>(alpha) << " alfa\n";

                        return 0;
                    }
                    Çýktý:
                    Onaltýlý olarak 32 bitlik bir RGBA renk deðeri girin (ör. FF7F3300): FF7F3300
                    Renginiz þunlarý içerir:
                    ff kýrmýzý
                    7f yeþil
                    33 mavi
                    0 alfa

Yukarýdaki programda, ilgilendiðimiz 8 bitlik kümeyi sorgulamak için bitsel AND kullanýyoruz ve ardýndan bunlarý 8
bitlik bir deðere saða kaydýrýyoruz, böylece bunlarý onaltýlýk deðerler olarak geri yazdýrabiliriz.

                                                                ÖZET
Bit bayraklarýný ayarlamak, temizlemek, ters çevirmek ve sorgulamak için özetleme:

Bit durumlarýný sorgulamak için, bit iþlemcisini (bitwise AND) kullanýrýz:

                    if (flags & option4) ... // eðer option4 ayarlandýysa bir þeyler yapýn

Bitleri ayarlamak (açmak) için bitwise OR kullanýrýz:

                    flags |= option4; //option4'ü açýn.
                    flags |= (option4 | option6); // 4 ve 5 numaralý optionlarý açýn.

Bitleri temizlemek (kapatmak) için bitsel AND ile bitsel NOT'u kullanýrýz:

                    flags &= ~option4; //option4'ü kapat
                    flags &= ~(option4 | option5); // 4 ve 5 numaralý optionlarý kapatýyoruz

Bit durumlarýný çevirmek için bitsel XOR kullanýrýz:

                    flags ^= option4; // option4'ü açýktan kapalýya veya tam tersi þekilde çevirin
                    flags ^= (option4 | option5); // 4 ve 5 numaralý optionlarý çevir

0.4 — Ýkilik ve ondalýk gösterim arasýnda tamsayýlarý dönüþtürme
----------------------------------------------------------------
Düþünün ki ondalýk bir tam sayý deðeri var, örneðin 5623. Sezgisel olarak, bu rakamlarýn (5 * 1000) + (6 * 100) + (2 * 10) + (3 * 1) anlamýna
geldiðini anlarýz. Her bir soldaki basamaðýn deðeri 10 kat arttýðýndan, 10 ondalýk rakamýmýz olduðunu düþünüyoruz.

Ýkili sayýlar da ayný þekilde çalýþýr, ancak yalnýzca 2 ikili rakam (0 ve 1) olduðu için, her basamaðýn deðeri 2 kat artar. Büyük bir 
ondalýk sayýyý okunabilir kýlmak için virgül kullanýldýðý gibi (örneðin 1.427.435), ikili sayýlarý genellikle okunabilir olmalarý için 4
bitlik gruplar halinde yazarýz (örneðin 1101 0101).
Aþaðýdaki tablo, ondalýk ve ikili olarak 15'e kadar sayar:

+--------+--------+
| Decimal| Binary |
+--------+--------+
|   0    |   0000 |
|   1    |   0001 |
|   2    |   0010 |
|   3    |   0011 |
|   4    |   0100 |
|   5    |   0101 |
|   6    |   0110 |
|   7    |   0111 |
|   8    |   1000 |
|   9    |   1001 |
|   10   |   1010 |
|   11   |   1011 |
|   12   |   1100 |
|   13   |   1101 |
|   14   |   1110 |
|   15   |   1111 |
+--------+--------+
*/
/*
Sayýlarýn çevirimi vardý ikiliden onlu sisteme onludan ikiliye unsigned signed mevzusu vardý o yüzden yazmadým temel olarak zaten bir 
çoðuna vakýfýz tamamýna da aþina olduðumuz için lazým olunca hatýrlamazsak açar bakarýz. 

*/