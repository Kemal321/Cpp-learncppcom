#include <iostream>

int main()
{
    return 0;
}
/*
19.1 — new ve delete ile dinamik bellek tahsisi
---------------------------------------------
Dinamik bellek tahsisine ihtiyaç

C++ üç temel bellek tahsis türünü destekler, bunlardan ikisini zaten görmüş olmalısınız.

Statik bellek tahsisi, statik ve global değişkenler için gerçekleşir. Bu tür değişkenler için bellek, programınız çalıştırıldığında bir kez tahsis edilir ve programınızın ömrü boyunca devam eder.
Otomatik bellek tahsisi, fonksiyon parametreleri ve yerel değişkenler için gerçekleşir. Bu tür değişkenler için bellek, ilgili bloğa girildiğinde tahsis edilir ve bloktan çıkıldığında serbest bırakılır, gerektiği kadar çok kez.
Dinamik bellek tahsisi, bu makalenin konusudur.
Hem statik hem de otomatik tahsisin iki ortak noktası vardır:

Değişkenin / dizinin boyutu derleme zamanında bilinmelidir.
Bellek tahsisi ve deallokasyon otomatik olarak gerçekleşir (değişken oluşturulduğunda / yok edildiğinde).
Çoğu zaman, bu gayet iyidir. Ancak, genellikle dış (kullanıcı veya dosya) girişiyle uğraşırken, bu kısıtlamaların biri veya her ikisi sorunlara neden olacak durumlarla karşılaşırsınız.

Örneğin, bir kişinin adını tutmak için bir dize kullanmak isteyebiliriz, ancak adının ne kadar uzun olduğunu ancak onu girdiklerinde bilebiliriz. Veya diskten bir dizi kaydı okumak isteyebiliriz, ancak kaç kayıt olduğunu önceden bilmiyoruz. Veya, değişken sayıda canavarın (zamanla bazı canavarlar ölür ve yenileri oluşturulur) oyuncuyu öldürmeye çalıştığı bir oyun oluşturuyor olabiliriz.

Her şeyin boyutunu derleme zamanında bildirmemiz gerekiyorsa, yapabileceğimiz en iyi şey, ihtiyaç duyacağımız değişkenlerin maksimum boyutunu tahmin etmek ve bu yeterli olacağını ummaktır:

```cpp
char name[25]; // umarım adları 25 karakterden azdır!
Record record[500]; // umarım 500'den az kayıt vardır!
Monster monster[40]; // en fazla 40 canavar
Polygon rendering[30000]; // bu 3d render'ın 30.000'den fazla çokgeni olmamalı!
```
Bu, en az dört nedenden dolayı kötü bir çözümdür:

Birincisi, değişkenler gerçekten kullanılmıyorsa bellek israfına yol açar. Örneğin, her ad için 25 karakter tahsis edersek, ancak adlar ortalama olarak sadece 12 karakter uzunluğunda ise, gerçekten ihtiyaç duyduğumuzdan iki kat fazla kullanıyoruz. Veya yukarıdaki render dizisini düşünün: bir render sadece 10.000 çokgen kullanıyorsa, 20.000 Polygon değerinde bellek kullanılmıyor!

ıkincisi, hangi bellek parçalarının gerçekten kullanıldığını nasıl anlarız? Dizeler için kolaydır: \0 ile başlayan bir dize açıkça kullanılmıyor. Peki ya monster[24]? şu anda canlı mı yoksa ölü mü? ılk başta bile başlatıldı mı? Bu, her canavarın durumunu belirlemenin bir yolunu gerektirir, bu karmaşıklık ekler ve ek bellek kullanabilir.

Üçüncüsü, çoğu normal değişken (sabit diziler dahil) belleğin yığın adı verilen bir bölümünde tahsis edilir. Bir program için yığın belleği genellikle oldukça küçüktür - Visual Studio yığın boyutunu varsayılan olarak 1MB olarak ayarlar. Bu sayıyı aşarsanız, yığın taşması sonucu oluşur ve işletim sistemi muhtemelen programı kapatır.

Visual Studio'da, bu programı çalıştırırken bunun gerçekleştiğini görebilirsiniz:

```cpp
int main()
{
    int array[1000000]; // 1 milyon tamsayı tahsis edin (muhtemelen 4MB bellek)
}
```
Sadece 1MB bellekle sınırlı olmak, özellikle grafiklerle uğraşan birçok program için sorunlu olurdu.

Dördüncüsü ve en önemlisi, yapay sınırlamalara ve/veya dizi taşmalarına yol açabilir. Kullanıcı diskten 600 kayıt okumayı denerse, ancak sadece maksimum 500 kayıt için bellek tahsis ettik mi? Ya kullanıcıya bir hata vermek zorunda kalırız, sadece 500 kayıt okuruz, veya (bu durumu hiç ele almadığımız en kötü durumda) kayıt dizisini taşırız ve kötü bir şey olmasını izleriz.

Ne yazık ki, bu sorunlar dinamik bellek tahsisi ile kolayca çözülebilir. Dinamik bellek tahsisi, çalışan programların gerektiğinde işletim sisteminden bellek istemesi için bir yoldur. Bu bellek, programın sınırlı yığın belleğinden gelmez - bunun yerine, işletim sistemi tarafından yönetilen çok daha büyük bir bellek havuzundan ayrılır, buna yığın denir. Modern makinelerde, yığın gigabaytlarca büyüklükte olabilir.

Dinamik olarak tek değişkenlerin tahsisi

Tek bir değişkeni dinamik olarak tahsis etmek için, new operatörünün skalar (dizi olmayan) formunu kullanırız:

```cpp
new int; // dinamik olarak bir tamsayı tahsis edin (ve sonucu atın)
```

Yukarıdaki durumda, işletim sisteminden bir tamsayının değerinde bellek istiyoruz. new operatörü, bu belleği kullanarak nesneyi oluşturur ve ardından tahsis edilen belleğin adresini içeren bir işaretçi döndürür.

Çoğu zaman, döndürülen değeri kendi işaretçi değişkenimize atarız, böylece daha sonra tahsis edilen belleğe erişebiliriz.

```cpp
int* ptr{ new int }; // dinamik olarak bir tamsayı tahsis edin ve adresi ptr'ye atayın, böylece daha sonra erişebiliriz
```

Daha sonra işaretçiyi dereferans yaparak belleğe erişebiliriz:

```cpp
*ptr = 7; // tahsis edilen belleğe 7 değerini atayın
```

Eğer önce değilse, işaretçilerin yararlı olduğu en az bir durumun şimdi açık olması gerekiyor. Tahsis edilen belleğin adresini tutacak bir işaretçimiz olmasaydı, bize tahsis edilen belleğe erişmenin bir yolu olmazdı!

Yığın üzerinde tahsis edilen nesnelere erişimin genellikle yığın üzerinde tahsis edilen nesnelere erişimden daha yavaş olduğunu unutmayın. Derleyici, yığın üzerinde tahsis edilen nesnelerin adresini bildiği için, bir değeri almak için doğrudan o adrese gidebilir. Yığın üzerinde tahsis edilen nesneler genellikle işaretçi aracılığıyla erişilir. Bu, nesnenin adresini almak (işaretçiden) ve başka bir değeri almak için iki adım gerektirir.

Dinamik bellek tahsisi nasıl çalışır?

Bilgisayarınızda, uygulamaların kullanabileceği bellek (muhtemelen çok fazla) vardır. Bir uygulamayı çalıştırdığınızda, işletim sisteminiz uygulamayı bu belleğin bir kısmına yükler. Uygulamanız tarafından kullanılan bu bellek, her biri farklı bir amaç hizmet eden farklı alanlara ayrılır. Bir alan kodunuzu içerir. Başka bir alan normal işlemler için kullanılır (hangi fonksiyonların çağrıldığını takip etmek, global ve yerel değişkenler oluşturmak ve yok etmek vb.). Daha sonra bunlardan daha fazla bahsedeceğiz. Ancak, mevcut belleğin çoğu orada durur, isteyen programlara verilmeyi bekler.

Belleği dinamik olarak tahsis ettiğinizde, işletim sisteminden programınızın kullanması için bazı bellekleri ayırmasını istersiniz. Bu isteği yerine getirebilirse, bu belleğin adresini uygulamanıza döndürür. Bu noktadan itibaren, uygulamanız bu belleği dilediği gibi kullanabilir. Uygulamanız bellekle işi bittiğinde, belleği işletim sistemine geri verebilir ve başka bir programa verilebilir.

Statik veya otomatik bellekten farklı olarak, programın kendisi dinamik olarak tahsis edilen belleği istemek ve atmakla sorumludur.
Anahtar içgörü

Yığın nesneleri için tahsis ve deallokasyon otomatik olarak yapılır. Bellek adresleriyle uğraşmamız gerekmez - derleyicinin yazdığı kod bunu bizim için yapabilir.

Yığın nesneleri için tahsis ve deallokasyon otomatik olarak yapılmaz. Bizim dahil olmamız gerekiyor. Bu, belirli bir yığın üzerinde tahsis edilen nesneye belirsiz bir şekilde atıfta bulunmamız gerektiği anlamına gelir, böylece hazır olduğumuzda onun yok edilmesini isteyebiliriz. Ve bu tür nesnelere atıfta bulunma şeklimiz bellek adresi üzerinden olur.

new operatörünü kullandığımızda, yeni tahsis edilen nesnenin bellek adresini içeren bir işaretçi döndürür. Genellikle bu adresi bir işaretçide saklamak isteriz, böylece daha sonra nesneye erişmek (ve sonunda, yok edilmesini istemek) için bu adresi kullanabiliriz.

Dinamik olarak ayrılan bir değişkeni başlatma

Bir değişkeni dinamik olarak ayırdığınızda, doğrudan başlatma veya uniform başlatma yoluyla da başlatabilirsiniz:

```cpp
int* ptr1{ new int (5) }; // doğrudan başlatmayı kullan
int* ptr2{ new int { 6 } }; // uniform başlatmayı kullan
```
Tek bir değişkeni silme

Dinamik olarak ayrılan bir değişkenle işimiz bittiğinde, belleği yeniden kullanmak için C++'a açıkça bildirmemiz gerekiyor. Tek değişkenler için bu, delete operatörünün skalar (dizi olmayan) formu ile yapılır:

```cpp
// varsayalım ki ptr daha önce new operatörü ile ayrılmış
delete ptr; // ptr'in işaret ettiği belleği işletim sistemine iade et
ptr = nullptr; // ptr'i null pointer yap
```
Belleği silmek ne anlama geliyor?

Delete operatörü aslında hiçbir şey silmez. Sadece işaret edilen belleği işletim sistemine geri verir. ışletim sistemi daha sonra bu belleği başka bir uygulamaya (veya bu uygulamaya tekrar) yeniden atamakta özgürdür.

Bir değişkeni sildiğimiz gibi görünse de, bu durum böyle değil! Pointer değişkeni hala önceki kapsama sahip ve diğer herhangi bir değişken gibi yeni bir değer atanabilir.

Dinamik olarak ayrılan belleği işaret etmeyen bir pointer'ı silmek kötü şeylere neden olabilir.

Asılı pointerlar

C++ deallocated belleğin içeriği veya silinen pointer'ın değeri hakkında herhangi bir garanti vermez. Çoğu durumda, işletim sistemine iade edilen bellek, iade edilmeden önce sahip olduğu değerleri içerecek ve pointer artık deallocated belleği işaret etmeye devam edecektir.

Deallocated belleği işaret eden bir pointer'a asılı pointer denir. Asılı bir pointer'ı dereferans etmek veya silmek tanımsız davranışa yol açar. Aşağıdaki programı düşünün:

```cpp
#include <iostream>

int main()
{
    int* ptr{ new int }; // dinamik olarak bir tamsayı ayır
    *ptr = 7; // o bellek konumuna bir değer koy

    delete ptr; // belleği işletim sistemine iade et. ptr artık bir asılı pointer.

    std::cout << *ptr; // Asılı bir pointer'ı dereferans etmek tanımsız davranışa neden olur
    delete ptr; // belleği tekrar deallocate etmeye çalışmak da tanımsız davranışa yol açar.

    return 0;
}
```
Yukarıdaki programda, daha önce ayrılan belleğe atanan 7 değeri muhtemelen hala orada olacak, ancak o bellek adresindeki değerin değişmiş olması mümkündür. Belleğin başka bir uygulamaya (veya işletim sisteminin kendi kullanımı için) ayrılmış olması da mümkündür ve bu belleğe erişmeye çalışmak işletim sistemini programı kapatmaya zorlar.

Belleği deallocate etmek birden çok asılı pointer oluşturabilir. Aşağıdaki örneği düşünün:

```cpp
#include <iostream>

int main()
{
    int* ptr{ new int{} }; // dinamik olarak bir tamsayı ayır
    int* otherPtr{ ptr }; // otherPtr artık aynı bellek konumunu işaret ediyor

    delete ptr; // belleği işletim sistemine iade et. ptr ve otherPtr artık asılı pointerlar.
    ptr = nullptr; // ptr artık bir nullptr

    // ancak, otherPtr hala bir asılı pointer!

    return 0;
}
```
Burada yardımcı olabilecek birkaç iyi uygulama var.

ılk olarak, birden çok pointer'ın aynı dinamik belleği işaret etmesinden kaçınmaya çalışın. Eğer bu mümkün değilse, hangi pointer'ın belleğe "sahip olduğunu" (ve onu silmekten sorumlu olduğunu) ve hangi pointer'ların sadece ona eriştiğini belirtin.

ıkinci olarak, bir pointer'ı sildiğinizde, eğer bu pointer hemen ardından kapsam dışına çıkmıyorsa, pointer'ı nullptr yapın. Null pointerlar ve neden yararlı oldukları hakkında biraz daha konuşacağız.

En iyi uygulama

Silinen pointerları nullptr yapın, eğer hemen ardından kapsam dışına çıkmıyorlarsa.

Operator new başarısız olabilir

ışletim sisteminden bellek talep ederken, nadir durumlarda, işletim sisteminin talebi karşılamak için herhangi bir belleği olmayabilir.

Varsayılan olarak, eğer new başarısız olursa, bir bad_alloc istisnası fırlatılır. Bu istisna düzgün bir şekilde ele alınmazsa (ve henüz istisnaları veya istisna işlemlerini ele almadığımız için ele alınmayacaktır), program sadece işlenmemiş bir istisna hatasıyla sonlandırılır (çöker).

Birçok durumda, new'in bir istisna fırlatması (veya programınızın çökmesi) istenmeyen bir durumdur, bu yüzden bellek ayrılamadığında new'in null bir işaretçi döndürmesini söylemek için new'in alternatif bir formu kullanılabilir. Bu, new anahtar kelimesi ve tahsis türü arasına std::nothrow sabitini ekleyerek yapılır:

```cpp
int* value { new (std::nothrow) int }; // eğer integer tahsisi başarısız olursa, value null bir işaretçiye ayarlanır
```
Yukarıdaki örnekte, eğer new bellek ayıramazsa, ayrılan belleğin adresi yerine null bir işaretçi döndürür.

Bu işaretçiyi daha sonra dereference etmeye çalışırsanız, tanımsız bir davranış sonucu oluşur (büyük olasılıkla, programınız çöker). Bu nedenle, en iyi uygulama, ayrılan belleği kullanmadan önce tüm bellek taleplerini kontrol etmek ve gerçekten başarılı olduklarını doğrulamaktır.

```cpp
int* value { new (std::nothrow) int{} }; // bir integer'ın değerine eşit bellek iste
if (!value) // new'in null döndürdüğü durumu ele al
{
    // Hata işlemesini burada yap
    std::cerr << "Bellek ayrılamadı\n";
}
```
New'den bellek istemek nadiren başarısız olur (ve neredeyse hiçbir zaman bir dev ortamında), bu kontrolü yapmayı unutmak yaygındır!

Null işaretçiler ve dinamik bellek tahsisi

Null işaretçiler (nullptr olarak ayarlanmış işaretçiler), dinamik bellek tahsisi ile uğraşırken özellikle kullanışlıdır. Dinamik bellek tahsisi bağlamında, bir null işaretçi temelde "bu işaretçiye hiçbir bellek ayrılmamıştır" der. Bu, şunları yapmamıza izin verir:

```cpp
// Eğer ptr zaten ayrılmamışsa, onu ayır
if (!ptr)
    ptr = new int;
```
Bir null işaretçiyi silmek hiçbir etkisi yoktur. Bu yüzden aşağıdakine ihtiyaç yoktur:

```cpp
if (ptr) // eğer ptr bir null işaretçi değilse
    delete ptr; // onu sil
// aksi takdirde hiçbir şey yapma
```
Bunun yerine, sadece şunu yazabilirsiniz:

```cpp
delete ptr;
```
Eğer ptr null değilse, dinamik olarak ayrılan değişken silinecektir. Eğer null ise, hiçbir şey olmayacaktır.

En ıyi Uygulama

Bir null işaretçiyi silmek tamam, ve hiçbir şey yapmaz. Delete ifadelerinizi koşullandırmanıza gerek yoktur.
Bellek sızıntıları

Dinamik olarak ayrılan bellek, açıkça deallocate edilene veya program sona erene (ve işletim sistemi onu temizler, işletim sisteminiz bunu yapıyorsa) kadar ayrılmış kalır. Ancak, dinamik olarak ayrılan bellek adreslerini tutmak için kullanılan işaretçiler, yerel değişkenler için normal kapsam kurallarını izler. Bu uyumsuzluk ilginç sorunlar yaratabilir.

Aşağıdaki fonksiyonu düşünün:

```cpp
void doSomething()
{
    int* ptr{ new int{} };
}
```
Bu fonksiyon dinamik olarak bir integer ayırır, ancak onu delete kullanarak hiçbir zaman serbest bırakmaz. ışaretçi değişkenler sadece normal değişkenler olduğu için, fonksiyon sona erdiğinde ptr kapsam dışına çıkar. Ve ptr, dinamik olarak ayrılan integer'ın adresini tutan tek değişken olduğu için, ptr yok edildiğinde dinamik olarak ayrılan belleğe daha fazla referans yoktur. Bu, programın artık dinamik olarak ayrılan belleğin adresini "kaybettiği" anlamına gelir. Sonuç olarak, bu dinamik olarak ayrılan integer silinemez.

Buna bellek sızıntısı denir. Bellek sızıntıları, programınız dinamik olarak ayrılan belleğin bir parçasının adresini işletim sistemine geri vermeden önce kaybettiğinde oluşur. Bu olduğunda, programınız dinamik olarak ayrılan belleği silemez, çünkü artık nerede olduğunu bilmiyor. ışletim sistemi de bu belleği kullanamaz, çünkü bu bellek hala programınız tarafından kullanımda olarak kabul edilir.

Buna bellek sızıntısı denir. Bellek sızıntıları, programınızın dinamik olarak ayrılan bir bellek parçasının adresini işletim sistemine geri vermeden önce kaybettiği durumlarda oluşur. Bu olduğunda, programınız dinamik olarak ayrılan belleği silmez, çünkü artık nerede olduğunu bilmez. ışletim sistemi de bu belleği kullanamaz, çünkü bu bellek hala programınız tarafından kullanılmakta olarak kabul edilir.

Bellek sızıntıları, program çalışırken boş belleği tüketir, bu da sadece bu programa değil, diğer programlara da daha az bellek sağlar. Ağır bellek sızıntısı sorunlarına sahip programlar, tüm mevcut belleği tüketebilir, bu da tüm makinenin yavaş çalışmasına veya hatta çökmesine neden olabilir. Yalnızca programınız sonlandıktan sonra işletim sistemi, sızan tüm belleği temizleyebilir ve "geri alabilir".

Bellek sızıntıları, bir işaretçinin kapsamının dışına çıkmasından kaynaklanabilir, ancak bellek sızıntılarının oluşabileceği başka yollar da vardır. Örneğin, dinamik olarak ayrılan belleğin adresini tutan bir işaretçiye başka bir değer atanırsa, bir bellek sızıntısı oluşabilir:

```cpp
int value = 5;
int* ptr{ new int{} }; // bellek ayır
ptr = &value; // eski adres kayboldu, bellek sızıntısı sonucu oluştu
```
Bu, işaretçiyi yeniden atamadan önce silerek düzeltilebilir:

```cpp
int value{ 5 };
int* ptr{ new int{} }; // bellek ayır
delete ptr; // belleği işletim sistemine geri ver
ptr = &value; // işaretçiyi value'nin adresine yeniden ata
```
ılgili olarak, çift tahsis yoluyla bir bellek sızıntısı elde etmek de mümkündür:

```cpp
int* ptr{ new int{} };
ptr = new int{}; // eski adres kayboldu, bellek sızıntısı sonucu oluştu
```
ıkinci tahsisin döndürdüğü adres, ilk tahsisin adresinin üzerine yazar. Sonuç olarak, ilk tahsis bir bellek sızıntısı olur!

Benzer şekilde, bu, işaretçiyi yeniden atamadan önce silmenizden emin olunarak önlenebilir.

Sonuç

Yeni ve silme operatörleri, programlarımız için tek değişkenleri dinamik olarak ayırmamıza izin verir.

Dinamik olarak ayrılan bellek, dinamik süreye sahiptir ve onu deallocate edene veya program sona erene kadar ayrılmış kalır.

Asılı veya null işaretçileri dereferans yapmamaya dikkat edin.

Bir sonraki derste, yeni ve silme kullanarak dizileri tahsis etmeyi ve silmeyi göreceğiz.
19.2 - Dinamik olarak dizileri tahsis etme
ALEX  20 KASIM, 2023
Tek değerlerin yanı sıra, değişkenlerin dizilerini de dinamik olarak tahsis edebiliriz. Sabit bir diziyle karşılaştırıldığında, bir diziyi dinamik olarak tahsis etmek, bir dizi uzunluğunu çalışma zamanında seçmemize olanak sağlar (yani uzunluğumuzun constexpr olması gerekmez).

Yazarın notu

Bu derslerde, en yaygın dinamik olarak ayrılan dizi türü olan C-stil dizileri dinamik olarak tahsis edeceğiz.

Bir std::array'yi dinamik olarak tahsis edebilirsiniz, ancak bu durumda genellikle dinamik olmayan bir std::vector kullanmak daha iyidir.

Bir diziyi dinamik olarak tahsis etmek için, yeni ve silmenin dizi formunu kullanırız (genellikle new[] ve delete[] olarak adlandırılır):

```cpp
#include <cstddef>
#include <iostream>

int main()
{
    std::cout << "Pozitif bir tam sayı girin: ";
    std::size_t length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // dizi yeni kullan.  Not edin ki uzunluğun sabit olması gerekmez!

    std::cout << "Sadece " << length << " uzunluğunda bir tam sayı dizisi tahsis ettim.\n";

    array[0] = 5; // eleman 0'ı değer 5 olarak ayarla

    delete[] array; // dizi silme ile diziyi deallocate

    // burada array'i nullptr/0 olarak ayarlamamıza gerek yok çünkü hemen sonra zaten kapsam dışına çıkıyor

    return 0;
}
```
Bir dizi tahsis ettiğimiz için, C++ yeni'nin skalar versiyonu yerine dizi versiyonunu kullanması gerektiğini bilir. Temelde, yeni[] operatörü çağrılır, yeni anahtar kelimesinin yanına [] konulmasa bile.

Dinamik olarak ayrılan dizilerin uzunluğu std::size_t türündedir. Eğer constexpr olmayan bir int kullanıyorsanız, daraltıcı bir dönüşüm olarak kabul edildiği için derleyiciniz aksi halde uyarı verecektir, bu yüzden std::size_t'ye static_cast yapmanız gerekecektir.

Bu belleğin, sabit diziler için kullanılan bellekten farklı bir yerden ayrıldığını unutmayın, bu yüzden dizinin boyutu oldukça büyük olabilir. Yukarıdaki programı çalıştırabilir ve 1.000.000 (veya muhtemelen 100.000.000) uzunluğunda bir dizi oluşturabilirsiniz. Deneyin! Bu yüzden, C++'da çok fazla bellek ayırmak gereken programlar genellikle bunu dinamik olarak yapar.

Dinamik Dizileri Silme

Dinamik olarak ayrılan bir diziyi silerken, delete[] olan dizi versiyonunu kullanmamız gerekiyor.

Bu, CPU'ya tek bir değişken yerine birden çok değişkeni temizlemesi gerektiğini söyler. Dinamik bellek ayırma ile uğraşırken yeni programcıların yaptığı en yaygın hatalardan biri, dinamik olarak ayrılan bir diziyi silerken delete yerine delete[] kullanmaktır. Bir dizide skalar delete versiyonunu kullanmak, veri bozulması, bellek sızıntıları, çökmeler veya diğer sorunlar gibi tanımlanmamış davranışlara yol açar.

Dizi delete[]'nin sıkça sorulan bir sorusu, "Dizi delete ne kadar belleği silmesi gerektiğini nasıl bilir?" Cevap, dizi new[]'nin bir değişkene ne kadar bellek ayrıldığını takip ettiği, böylece dizi delete[]'nin uygun miktarı silebildiğidir. Ne yazık ki, bu boyut/uzunluk programcıya erişilebilir değildir.

Dinamik diziler neredeyse sabit dizilere eşittir

17.8 -- C tarzı dizi çürümesi dersinde, sabit bir dizinin ilk dizi elemanının bellek adresini tuttuğunu öğrendiniz. Ayrıca, sabit bir dizinin, dizinin ilk elemanına işaret eden bir işaretçiye çürüyebileceğini de öğrendiniz. Bu çürümüş formda, sabit dizinin uzunluğu mevcut değildir (ve bu nedenle sizeof() aracılığıyla dizinin boyutu da mevcut değildir), ancak aksi takdirde pek bir fark yoktur.

Bir dinamik dizi, dizinin ilk elemanına işaret eden bir işaretçi olarak hayatına başlar. Sonuç olarak, uzunluğunu veya boyutunu bilmediği aynı sınırlamalara sahiptir. Bir dinamik dizi, programcının dinamik diziyi delete[] anahtar kelimesi aracılığıyla deallocate etmekten sorumlu olduğu istisna dışında, çürümüş bir sabit dizi ile aynı şekilde işlev görür.

Dinamik olarak ayrılan dizileri başlatma

Eğer dinamik olarak ayrılan bir diziyi 0'a başlatmak isterseniz, sözdizimi oldukça basittir:

```cpp
int* array{ new int[length]{} };
```
C++11'den önce, dinamik bir diziyi sıfır olmayan bir değere başlatmanın kolay bir yolu yoktu (başlatıcı listeleri sadece sabit diziler için çalışıyordu). Bu, dizinin üzerinden döngü yapmanız ve öğe değerlerini açıkça atamanız gerektiği anlamına geliyordu.

```cpp
int* array = new int[5];
array[0] = 9;
array[1] = 7;
array[2] = 5;
array[3] = 3;
array[4] = 1;
```
Çok sinir bozucu!

Ancak, C++11 ile başlayarak, artık başlatıcı listeleri kullanarak dinamik dizileri başlatmak mümkün!

```cpp
int fixedArray[5] = { 9, 7, 5, 3, 1 }; // C++11'den önce sabit bir dizi başlat
int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // C++11'den itibaren dinamik bir dizi başlat
// Tipi iki kez yazmamak için auto kullanabiliriz. Bu genellikle uzun isimli tipler için yapılır.
auto* array{ new int[5]{ 9, 7, 5, 3, 1 } };
```
Not: Bu sözdiziminde, dizi uzunluğu ve başlatıcı listesi arasında operator= yoktur.

Tutarlılık için, sabit diziler de uniform başlatma kullanılarak başlatılabilir:

```cpp
int fixedArray[]{ 9, 7, 5, 3, 1 }; // C++11'de sabit bir dizi başlat
char fixedArray[]{ "Hello, world!" }; // C++11'de sabit bir dizi başlat
```
Dizinin boyutunu açıkça belirtmek isteğe bağlıdır.
Dizileri yeniden boyutlandırma

Bir diziyi dinamik olarak ayırma, dizinin uzunluğunu ayırma zamanında ayarlamanıza olanak sağlar. Ancak, C++ zaten ayrılmış bir diziyi yeniden boyutlandırmanın yerleşik bir yolunu sağlamaz. Bu sınırlamayı aşmanın bir yolu, yeni bir dizi dinamik olarak ayırmak, öğeleri kopyalamak ve eski diziyi silmektir.

Buna bellek sızıntısı denir. Bellek sızıntıları, programınızın dinamik olarak ayrılan bir bellek parçasının adresini işletim sistemine geri vermeden önce kaybettiği durumlarda oluşur. Bu olduğunda, programınız dinamik olarak ayrılan belleği silmez, çünkü artık nerede olduğunu bilmez. ışletim sistemi de bu belleği kullanamaz, çünkü bu bellek hala programınız tarafından kullanılmakta olarak kabul edilir.

Bellek sızıntıları, program çalışırken boş belleği tüketir, bu da sadece bu programa değil, diğer programlara da daha az bellek sağlar. Ağır bellek sızıntısı sorunlarına sahip programlar, tüm mevcut belleği tüketebilir, bu da tüm makinenin yavaş çalışmasına veya hatta çökmesine neden olabilir. Yalnızca programınız sonlandıktan sonra işletim sistemi, sızan tüm belleği temizleyebilir ve "geri alabilir".

Bellek sızıntıları, bir işaretçinin kapsamının dışına çıkmasından kaynaklanabilir, ancak bellek sızıntılarının oluşabileceği başka yollar da vardır. Örneğin, dinamik olarak ayrılan belleğin adresini tutan bir işaretçiye başka bir değer atanırsa, bir bellek sızıntısı oluşabilir:

```cpp
int value = 5;
int* ptr{ new int{} }; // bellek ayır
ptr = &value; // eski adres kayboldu, bellek sızıntısı sonucu oluştu
```
Bu, işaretçiyi yeniden atamadan önce silerek düzeltilebilir:

```cpp
int value{ 5 };
int* ptr{ new int{} }; // bellek ayır
delete ptr; // belleği işletim sistemine geri ver
ptr = &value; // işaretçiyi value'nin adresine yeniden ata
```
ılgili olarak, çift tahsis yoluyla bir bellek sızıntısı elde etmek de mümkündür:

```cpp
int* ptr{ new int{} };
ptr = new int{}; // eski adres kayboldu, bellek sızıntısı sonucu oluştu
```
ıkinci tahsisin döndürdüğü adres, ilk tahsisin adresinin üzerine yazar. Sonuç olarak, ilk tahsis bir bellek sızıntısı olur!

Benzer şekilde, bu, işaretçiyi yeniden atamadan önce silmenizden emin olunarak önlenebilir.

Sonuç

Yeni ve silme operatörleri, programlarımız için tek değişkenleri dinamik olarak ayırmamıza izin verir.

Dinamik olarak ayrılan bellek, dinamik süreye sahiptir ve onu deallocate edene veya program sona erene kadar ayrılmış kalır.

Asılı veya null işaretçileri dereferans yapmamaya dikkat edin.

Bir sonraki derste, yeni ve silme kullanarak dizileri tahsis etmeyi ve silmeyi göreceğiz.
19.2 - Dinamik olarak dizileri tahsis etme
ALEX  20 KASIM, 2023
Tek değerlerin yanı sıra, değişkenlerin dizilerini de dinamik olarak tahsis edebiliriz. Sabit bir diziyle karşılaştırıldığında, bir diziyi dinamik olarak tahsis etmek, bir dizi uzunluğunu çalışma zamanında seçmemize olanak sağlar (yani uzunluğumuzun constexpr olması gerekmez).

Yazarın notu

Bu derslerde, en yaygın dinamik olarak ayrılan dizi türü olan C-stil dizileri dinamik olarak tahsis edeceğiz.

Bir std::array'yi dinamik olarak tahsis edebilirsiniz, ancak bu durumda genellikle dinamik olmayan bir std::vector kullanmak daha iyidir.

Bir diziyi dinamik olarak tahsis etmek için, yeni ve silmenin dizi formunu kullanırız (genellikle new[] ve delete[] olarak adlandırılır):

```cpp
#include <cstddef>
#include <iostream>

int main()
{
    std::cout << "Pozitif bir tam sayı girin: ";
    std::size_t length{};
    std::cin >> length;

    int* array{ new int[length]{} }; // dizi yeni kullan.  Not edin ki uzunluğun sabit olması gerekmez!

    std::cout << "Sadece " << length << " uzunluğunda bir tam sayı dizisi tahsis ettim.\n";

    array[0] = 5; // eleman 0'ı değer 5 olarak ayarla

    delete[] array; // dizi silme ile diziyi deallocate

    // burada array'i nullptr/0 olarak ayarlamamıza gerek yok çünkü hemen sonra zaten kapsam dışına çıkıyor

    return 0;
}
```
Bir dizi tahsis ettiğimiz için, C++ yeni'nin skalar versiyonu yerine dizi versiyonunu kullanması gerektiğini bilir. Temelde, yeni[] operatörü çağrılır, yeni anahtar kelimesinin yanına [] konulmasa bile.

Dinamik olarak ayrılan dizilerin uzunluğu std::size_t türündedir. Eğer constexpr olmayan bir int kullanıyorsanız, daraltıcı bir dönüşüm olarak kabul edildiği için derleyiciniz aksi halde uyarı verecektir, bu yüzden std::size_t'ye static_cast yapmanız gerekecektir.

Bu belleğin, sabit diziler için kullanılan bellekten farklı bir yerden ayrıldığını unutmayın, bu yüzden dizinin boyutu oldukça büyük olabilir. Yukarıdaki programı çalıştırabilir ve 1.000.000 (veya muhtemelen 100.000.000) uzunluğunda bir dizi oluşturabilirsiniz. Deneyin! Bu yüzden, C++'da çok fazla bellek ayırmak gereken programlar genellikle bunu dinamik olarak yapar.

Dinamik Dizileri Silme

Dinamik olarak ayrılan bir diziyi silerken, delete[] olan dizi versiyonunu kullanmamız gerekiyor.

Bu, CPU'ya tek bir değişken yerine birden çok değişkeni temizlemesi gerektiğini söyler. Dinamik bellek ayırma ile uğraşırken yeni programcıların yaptığı en yaygın hatalardan biri, dinamik olarak ayrılan bir diziyi silerken delete yerine delete[] kullanmaktır. Bir dizide skalar delete versiyonunu kullanmak, veri bozulması, bellek sızıntıları, çökmeler veya diğer sorunlar gibi tanımlanmamış davranışlara yol açar.

Dizi delete[]'nin sıkça sorulan bir sorusu, "Dizi delete ne kadar belleği silmesi gerektiğini nasıl bilir?" Cevap, dizi new[]'nin bir değişkene ne kadar bellek ayrıldığını takip ettiği, böylece dizi delete[]'nin uygun miktarı silebildiğidir. Ne yazık ki, bu boyut/uzunluk programcıya erişilebilir değildir.

Dinamik diziler neredeyse sabit dizilere eşittir

17.8 -- C tarzı dizi çürümesi dersinde, sabit bir dizinin ilk dizi elemanının bellek adresini tuttuğunu öğrendiniz. Ayrıca, sabit bir dizinin, dizinin ilk elemanına işaret eden bir işaretçiye çürüyebileceğini de öğrendiniz. Bu çürümüş formda, sabit dizinin uzunluğu mevcut değildir (ve bu nedenle sizeof() aracılığıyla dizinin boyutu da mevcut değildir), ancak aksi takdirde pek bir fark yoktur.

Bir dinamik dizi, dizinin ilk elemanına işaret eden bir işaretçi olarak hayatına başlar. Sonuç olarak, uzunluğunu veya boyutunu bilmediği aynı sınırlamalara sahiptir. Bir dinamik dizi, programcının dinamik diziyi delete[] anahtar kelimesi aracılığıyla deallocate etmekten sorumlu olduğu istisna dışında, çürümüş bir sabit dizi ile aynı şekilde işlev görür.

Dinamik olarak ayrılan dizileri başlatma

Eğer dinamik olarak ayrılan bir diziyi 0'a başlatmak isterseniz, sözdizimi oldukça basittir:

```cpp
int* array{ new int[length]{} };
```
C++11'den önce, dinamik bir diziyi sıfır olmayan bir değere başlatmanın kolay bir yolu yoktu (başlatıcı listeleri sadece sabit diziler için çalışıyordu). Bu, dizinin üzerinden döngü yapmanız ve öğe değerlerini açıkça atamanız gerektiği anlamına geliyordu.

```cpp
int* array = new int[5];
array[0] = 9;
array[1] = 7;
array[2] = 5;
array[3] = 3;
array[4] = 1;
```
Çok sinir bozucu!

Ancak, C++11 ile başlayarak, artık başlatıcı listeleri kullanarak dinamik dizileri başlatmak mümkün!

```cpp
int fixedArray[5] = { 9, 7, 5, 3, 1 }; // C++11'den önce sabit bir dizi başlat
int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // C++11'den itibaren dinamik bir dizi başlat
// Tipi iki kez yazmamak için auto kullanabiliriz. Bu genellikle uzun isimli tipler için yapılır.
auto* array{ new int[5]{ 9, 7, 5, 3, 1 } };
```
Not: Bu sözdiziminde, dizi uzunluğu ve başlatıcı listesi arasında operator= yoktur.

Tutarlılık için, sabit diziler de uniform başlatma kullanılarak başlatılabilir:

```cpp
int fixedArray[]{ 9, 7, 5, 3, 1 }; // C++11'de sabit bir dizi başlat
char fixedArray[]{ "Hello, world!" }; // C++11'de sabit bir dizi başlat
```
Dizinin boyutunu açıkça belirtmek isteğe bağlıdır.
Dizileri yeniden boyutlandırma

Bir diziyi dinamik olarak ayırma, dizinin uzunluğunu ayırma zamanında ayarlamanıza olanak sağlar. Ancak, C++ zaten ayrılmış bir diziyi yeniden boyutlandırmanın yerleşik bir yolunu sağlamaz. Bu sınırlamayı aşmanın bir yolu, yeni bir dizi dinamik olarak ayırmak, öğeleri kopyalamak ve eski diziyi silmektir.

Ancak, bu hata yapmaya açıktır, özellikle eleman türü bir sınıf olduğunda (nasıl oluşturulacaklarına dair özel kuralları vardır).

Sonuç olarak, bunu kendiniz yapmaktan kaçınmanızı öneririz. Bunun yerine std::vector kullanın.
19.3 — Yıkıcılar
ALEX  KASIM 30, 2023
Bir yıkıcı, bir sınıfın bir nesnesi yok edildiğinde çalıştırılan başka bir özel sınıf üye fonksiyonudur. Yapıcılar bir sınıfı başlatmak için tasarlanmışken, yıkıcılar temizlik yapmaya yardımcı olmak için tasarlanmıştır.

Bir nesne normalde kapsamdan çıktığında veya dinamik olarak ayrılan bir nesne delete anahtar kelimesi kullanılarak açıkça silindiğinde, sınıf yıkıcısı otomatik olarak çağrılır (varsa) nesne bellekten kaldırılmadan önce gerekli temizliği yapmak için. Basit sınıflar için (sadece normal üye değişkenlerin değerlerini başlatanlar), bir yıkıcıya ihtiyaç yoktur çünkü C++ sizin için belleği otomatik olarak temizler.

Ancak, sınıf nesneniz herhangi bir kaynak tutuyorsa (ör. dinamik bellek veya bir dosya veya veritabanı tanıtıcısı) veya nesne yok edilmeden önce herhangi bir bakım yapmanız gerekiyorsa, yıkıcı bunu yapmak için mükemmel bir yerdir, çünkü genellikle nesne yok edilmeden önce son olarak gerçekleşen şeydir.

Yıkıcı isimlendirme

Yapıcılar gibi, yıkıcıların da belirli isimlendirme kuralları vardır:

Yıkıcının adı, sınıfın adıyla aynı olmalı ve önünde bir tilda (~) olmalıdır.
Yıkıcı argüman alamaz.
Yıkıcının dönüş tipi yoktur.
Bir sınıfın sadece tek bir yıkıcısı olabilir.

Genellikle bir yıkıcıyı açıkça çağırmamalısınız (çünkü nesne yok edildiğinde otomatik olarak çağrılır), çünkü bir nesneyi birden fazla kez temizlemek isteyeceğiniz nadir durumlar vardır. Ancak, yıkıcılar güvenle diğer üye fonksiyonları çağırabilir çünkü nesne, yıkıcı çalıştıktan sonra yok edilmez.
Bir yıkıcı örneği

Bir yıkıcı kullanan basit bir sınıfa bir göz atalım:

```cpp
#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
    int* m_array{};
    int m_length{};

public:
    IntArray(int length) // constructor
    {
        assert(length > 0);

        m_array = new int[static_cast<std::size_t>(length)]{};
        m_length = length;
    }

    ~IntArray() // destructor
    {
        // Daha önce tahsis ettiğimiz diziyi dinamik olarak sil
        delete[] m_array;
    }

    void setValue(int index, int value) { m_array[index] = value; }
    int getValue(int index) { return m_array[index]; }

    int getLength() { return m_length; }
};

int main()
{
    IntArray ar ( 10 ); // 10 tam sayı tahsis et
    for (int count{ 0 }; count < ar.getLength(); ++count)
        ar.setValue(count, count+1);

    std::cout << "Element 5'in değeri: " << ar.getValue(5) << '\n';

    return 0;
} // ar burada yok edilir, bu yüzden ~IntArray() yıkıcı fonksiyonu burada çağrılır
```
ıpucu

Yukarıdaki örneği derlerseniz ve aşağıdaki hatayı alırsanız:

error: 'class IntArray' has pointer data members [-Werror=effc++]|
error:   but does not override 'IntArray(const IntArray&)' [-Werror=effc++]|
error:   or 'operator=(const IntArray&)' [-Werror=effc++]|
O zaman bu örnekte derleme ayarlarınızdan “-Weffc++” bayrağını kaldırabilirsiniz, veya sınıfa aşağıdaki iki satırı ekleyebilirsiniz:

```cpp
IntArray(const IntArray&) = delete;
IntArray& operator=(const IntArray&) = delete;
```
Üyeler için =delete'i ders 14.14 -- Kopya yapıcıya girişte tartışıyoruz

Bu program sonucu üretir:

Element 5'in değeri: 6
main()'in ilk satırında, ar adında yeni bir IntArray sınıf nesnesi oluşturuyoruz ve 10 uzunluğunda bir değer geçiriyoruz. Bu, yapıcıyı çağırır, bu da dizi üyesi için bellek ayırır. Derleme zamanında dizinin uzunluğunu bilmediğimiz için burada dinamik tahsis kullanmalıyız (arayan bunu belirler).

main() sonunda, ar kapsamdan çıkar. Bu, ~IntArray() yıkıcısının çağrılmasına neden olur, bu da yapıcıda tahsis ettiğimiz diziyi siler!

Kaynak: Bing ile konuşma, 12.03.2024
(1) github.com. https://github.com/tallsong/cpp/tree/31720a36c4a3045c3636c8a31477d6841953b0e3/08Basic%20object-oriented%20programming%2Fdestructors.cpp.
(2) github.com. https://github.com/CP-TSAI/learning-notes/tree/3e7389dd104c031b2f6a49e14d7fce8bc88e8588/program_tools%2Fcpp_knowledge%2FCh-8%2F08.7%20Destructors.md.
(3) github.com. https://github.com/meenurathi/CppNotes/tree/1baedcb2500e8ae24236983dd201e64ac6d87e71/notes%2FConstructors.cpp.

Bir hatırlatma

Ders 16.2'de -- std::vector ve list constructors'a giriş, bir dizi/konteyner/liste sınıfını bir uzunlukla (bir eleman listesi yerine) başlatırken parantez tabanlı başlatmanın kullanılması gerektiğini belirtiyoruz. Bu nedenle, IntArray'i `IntArray ar ( 10 );` kullanarak başlatıyoruz.

Constructor ve destructor zamanlaması

Daha önce de belirtildiği gibi, constructor bir nesne oluşturulduğunda çağrılır ve destructor bir nesne yok edildiğinde çağrılır. Aşağıdaki örnekte, constructor ve destructor içindeki cout ifadelerini kullanarak bunu gösteriyoruz:

```cpp
#include <iostream>

class Simple
{
private:
    int m_nID{};

public:
    Simple(int nID)
        : m_nID{ nID }
    {
        std::cout << "Constructing Simple " << nID << '\n';
    }

    ~Simple()
    {
        std::cout << "Destructing Simple" << m_nID << '\n';
    }

    int getID() { return m_nID; }
};

int main()
{
    // Allocate a Simple on the stack
    Simple simple{ 1 };
    std::cout << simple.getID() << '\n';

    // Allocate a Simple dynamically
    Simple* pSimple{ new Simple{ 2 } };

    std::cout << pSimple->getID() << '\n';

    // We allocated pSimple dynamically, so we have to delete it.
    delete pSimple;

    return 0;
} // simple goes out of scope here
```
Bu program aşağıdaki sonucu üretir:

```
Constructing Simple 1
1
Constructing Simple 2
2
Destructing Simple 2
Destructing Simple 1
```
“Simple 1”in “Simple 2”den sonra yok edildiğini unutmayın çünkü fonksiyonun sonuna gelmeden önce pSimple'ı sildik, oysa simple main() sonuna kadar yok edilmedi.

Global değişkenler main()den önce oluşturulur ve main()den sonra yok edilir.
RAII

RAII (Resource Acquisition Is Initialization), kaynak kullanımının otomatik süreli nesnelerin (ör. dinamik olarak ayrılmamış nesneler) ömrüne bağlandığı bir programlama tekniğidir. C++'da, RAII constructor ve destructor olan sınıflar aracılığıyla uygulanır. Bir kaynak (örneğin bellek, bir dosya veya veritabanı tanıtıcısı vb.) genellikle nesnenin constructor'ında edinilir (ancak nesne oluşturulduktan sonra edinilirse mantıklı olabilir). Bu kaynak, nesne canlıyken kullanılabilir. Kaynak, nesne yok edildiğinde destructor'da serbest bırakılır. RAII'nin temel avantajı, tüm kaynak tutan nesnelerin otomatik olarak temizlenmesi sayesinde kaynak sızıntılarının (ör. belleğin deallocate edilmemesi) önlenmesine yardımcı olmasıdır.

Bu dersin başındaki IntArray sınıfı, constructor'da tahsis ve destructor'da deallocation uygulayan bir sınıfın örneğidir. std::string ve std::vector, RAII'yi takip eden standart kütüphane sınıflarının örnekleridir -- dinamik bellek başlatmada edinilir ve yok edilme sırasında otomatik olarak temizlenir.

std::exit() fonksiyonu hakkında bir uyarı

std::exit() fonksiyonunu kullanırsanız, programınız sona erecek ve hiçbir destructor çağrılmayacaktır. Destructorlarınızın gerekli temizlik işlerini yapmasına güveniyorsanız (ör. çıkıştan önce bir günlük dosyasına veya veritabanına bir şey yazmak) dikkatli olun.

Özet

Gördüğünüz gibi, constructor ve destructorlar birlikte kullanıldığında, sınıflarınız kendilerini başlatabilir ve programcının herhangi bir özel iş yapmasına gerek kalmadan kendilerini temizleyebilir! Bu, bir hatayı yapma olasılığını azaltır ve sınıfları kullanmayı kolaylaştırır.

Kaynak: Bing ile konuşma, 12.03.2024
(1) github.com. https://github.com/nsikanikpoh/dev_cpp/tree/6847f85e5b35b7c2d23acad935d4ae752f1c5b56/Destructor2%2Fmain.cpp.
(2) github.com. https://github.com/Suineg-Darhnoel/Learning/tree/7a4a1c8a5bca13a3eabdda88d0df6d2c3bea143b/Cpp%2Fchap_8.7-Destructor.cpp.
(3) github.com. https://github.com/Nir3us/Cpp/tree/e140f20f7f0f13cf952a020cef1d015babf4f0a8/Destructor%2Fmain.cpp.
(4) github.com. https://github.com/wardogordo/learncppdotcom/tree/e185a306ee51be19c78e8b503c8b8ef611859277/learncppdotcom%2Fch-12-basic-oop%2Fdestructors01%2Fmain.cpp.
(5) github.com. https://github.com/nero211/Example/tree/9a30eeed01f794e9c038c194fbe05a56c2d14fff/main.cpp.

19.4 — ışaretçilerden ışaretçilere ve Dinamik Çok Boyutlu Dizilere
ALEX  EYLÜL 11, 2023
Bu ders isteğe bağlıdır, C++ hakkında daha fazla öğrenmek isteyen ileri düzey okuyucular içindir. Gelecekteki dersler bu ders üzerine kurulu değildir.

Bir işaretçiden bir işaretçiye tam olarak beklediğiniz şeydir: başka bir işaretçinin adresini tutan bir işaretçi.

ışaretçilerden ışaretçilere

Normal bir int'e işaretçi tek bir yıldız kullanılarak bildirilir:

```cpp
int* ptr; // int'e bir işaretçi, tek bir yıldız
```
Bir int'e işaretçiden bir işaretçi iki yıldız kullanılarak bildirilir

```cpp
int** ptrptr; // int'e işaretçiden bir işaretçiye, iki yıldız
```
Bir işaretçiden bir işaretçi, normal bir işaretçi gibi çalışır - işaret ettiği değeri almak için onu dereference edebilirsiniz. Ve çünkü bu değer kendisi bir işaretçi olduğu için, altta yatan değere ulaşmak için onu tekrar dereference edebilirsiniz. Bu dereferanslar ardışık olarak yapılabilir:

```cpp
int value { 5 };

int* ptr { &value };
std::cout << *ptr << '\n'; // int değerini almak için int'e işaretçi dereference edilir

int** ptrptr { &ptr };
std::cout << **ptrptr << '\n'; // int'e işaretçi almak için dereference, int değerini almak için tekrar dereference
```
Yukarıdaki programı yazdırır:

5
5
Bir işaretçiden bir işaretçiyi doğrudan bir değere ayarlayamazsınız:

```cpp
int value { 5 };
int** ptrptr { &&value }; // geçerli değil
```
Bu, adres operatörünün (operator&) bir lvalue gerektirir, ancak &value bir rvalue'dir.

Ancak, bir işaretçiden bir işaretçi null'a ayarlanabilir:

```cpp
int** ptrptr { nullptr };
```
ışaretçi Dizileri

ışaretçilerden işaretçilere birkaç kullanımı vardır. En yaygın kullanım, bir işaretçi dizisi dinamik olarak ayırmaktır:

```cpp
int** array { new int*[10] }; // 10 int işaretçisi olan bir dizi ayır
```
Bu, standart bir dinamik olarak ayrılmış dizi gibi çalışır, tek fark dizi elemanlarının türünün "integer'a işaretçi" yerine integer olmasıdır.

ıki Boyutlu Dinamik Olarak Ayrılmış Diziler

ışaretçilerden işaretçilere başka bir yaygın kullanım, dinamik olarak ayrılmış çok boyutlu dizileri kolaylaştırmaktır (çok boyutlu dizilerin bir incelemesi için 17.12 -- Çok Boyutlu C-stil Dizilere bakın).

ıki boyutlu sabit bir dizi, kolayca şu şekilde bildirilebilir:

```cpp
int array[10][5];
```
ıki boyutlu bir dizi dinamik olarak ayırmak biraz daha zorlayıcıdır. Böyle bir şey denemeye meyilli olabilirsiniz:

```cpp
int** array { new int[10][5] }; // çalışmaz!
```
Ama bu işe yaramaz.

Burada iki olası çözüm var. Sağdaki dizi boyutu constexpr ise, bunu yapabilirsiniz:

```cpp
int x { 7 }; // sabit olmayan
int (*array)[5] { new int[x][5] }; // sağdaki boyut constexpr olmalı
```
Burada doğru önceliği sağlamak için parantezlere ihtiyaç vardır. Bu, otomatik tip çıkarımını kullanmanın iyi bir yerdir:

```cpp
int x { 7 }; // sabit olmayan
auto array { new int[x][5] }; // çok daha basit!
```
Ne yazık ki, bu nispeten basit çözüm, sağdaki dizi boyutu bir derleme zamanı sabiti değilse işe yaramaz. Bu durumda, biraz daha karmaşık olmak zorundayız. Önce, bir işaretçi dizisi ayırıyoruz (yukarıda olduğu gibi). Sonra işaretçi dizisinden geçiyoruz ve her dizi elemanı için bir dinamik dizi ayırıyoruz. Dinamik iki boyutlu dizimiz, dinamik tek boyutlu dizilerin dinamik tek boyutlu bir dizisidir!

```cpp
int** array { new int*[10] }; // 10 int işaretçisi olan bir dizi ayır — bunlar satırlarımız
for (int count { 0 }; count < 10; ++count)
    array[count] = new int[5]; // bunlar sütunlarımız
```
Sonra dizimize her zamanki gibi erişebiliriz:

```cpp
array[9][4] = 3; // Bu, (array[9])[4] = 3 ile aynıdır;
```
Bu yöntemle, çünkü her dizi sütunu bağımsız olarak dinamik olarak ayrılmıştır, dikdörtgen olmayan dinamik olarak ayrılmış iki boyutlu diziler yapmak mümkündür. Örneğin, bir üçgen şeklinde bir dizi yapabiliriz:

```cpp
int** array { new int*[10] }; // 10 int işaretçisi olan bir dizi ayır — bunlar satırlarımız
for (int count { 0 }; count < 10; ++count)
    array[count] = new int[count+1]; // bunlar sütunlarımız
```

Yukarıdaki örnekte, array[0]'ın uzunluğu 1 olan bir dizi, array[1]'in uzunluğu 2 olan bir dizi vb. olduğuna dikkat edin.

Bu yöntemi kullanarak dinamik olarak ayrılan iki boyutlu bir diziyi deallocate etmek de bir döngü gerektirir:

```cpp
for (int count { 0 }; count < 10; ++count)
    delete[] array[count];
delete[] array; // bu en son yapılmalı
```
Diziyi oluşturduğumuz sıranın tersine sildiğimize dikkat edin (önce elemanlar, sonra dizi kendisi). Eğer diziyi dizi sütunlarından önce silersek, dizi sütunlarını silmek için deallocated belleğe erişmek zorunda kalırız. Ve bu tanımsız bir davranışa yol açar.

ıki boyutlu dizileri ayırma ve deallocate etme karmaşık ve hata yapması kolay olduğu için, genellikle bir iki boyutlu diziyi (x boyutunda y) düzleştirmek ve x * y boyutunda tek boyutlu bir diziye dönüştürmek daha kolaydır:

```cpp
// Bunun yerine:
int** array { new int*[10] }; // 10 int pointer'ı olan bir dizi ayır — bunlar satırlarımız
for (int count { 0 }; count < 10; ++count)
    array[count] = new int[5]; // bunlar sütunlarımız

// Bunu yapın
int *array { new int[50] }; // 10x5 dizi tek bir diziye düzleştirildi
```
Basit matematik, dikdörtgen bir iki boyutlu dizinin satır ve sütun indeksini, tek boyutlu bir dizinin tek bir indeksine dönüştürmek için kullanılabilir:

```cpp
int getSingleIndex(int row, int col, int numberOfColumnsInArray)
{
     return (row * numberOfColumnsInArray) + col;
}

// düzleştirilmiş dizimizi kullanarak array[9,4]'ü 3'e ayarla
array[getSingleIndex(9, 4, 5)] = 3;
```
Bir adresi geçerek bir pointer'ı geçme

Bir pointer parametresini kullanarak geçirilen alt argümanın gerçek değerini değiştirebildiğimiz gibi, bir fonksiyona bir pointer'ın pointer'ını geçirebilir ve bu pointer'ı, işaret ettiği pointer'ın değerini değiştirmek için kullanabiliriz (kafanız karıştı mı?).

Ancak, bir fonksiyonun bir pointer argümanının neyi işaret ettiğini değiştirebilmesini istiyorsak, bu genellikle bir pointer'a bir referans kullanarak daha iyi yapılır. Bu, ders 12.11 -- Adrese geçiş (part 2) konusunda ele alınmıştır.

Bir pointer'a bir pointer'a bir pointer'a...

Bir pointer'a bir pointer'a bir pointer tanımlamak da mümkündür:

```cpp
int*** ptrx3;
```
Bu, üç boyutlu bir dizi dinamik olarak ayırmak için kullanılabilir. Ancak, bunu yapmak bir döngü içinde bir döngü gerektirir ve doğru yapmak son derece karmaşıktır.

Bir pointer'a bir pointer'a bir pointer'a bir pointer bile tanımlayabilirsiniz:

```cpp
int**** ptrx4;
```
Veya daha yüksek, isterseniz.

Ancak, gerçekte bunlar çok fazla kullanılmaz çünkü genellikle bu kadar çok seviye indireksiyona ihtiyacınız olmaz.

Sonuç

Pointer'ların pointer'larını kullanmaktan kaçınmanızı öneririz, çünkü bunları kullanmak karmaşıktır ve potansiyel olarak tehlikelidir. Normal pointer'larla null veya dangling pointer'ı dereference etmek yeterince kolaydır - bir pointer'ın pointer'ı ile bu iki kat daha kolaydır çünkü altta yatan değere ulaşmak için çift dereference yapmanız gerekir!

19.5 — Void ışaretçiler
ALEX  29 EYLÜL, 2023
Void işaretçi, aynı zamanda genel işaretçi olarak da bilinir, herhangi bir veri türündeki nesnelere işaret edebilen özel bir işaretçi türüdür! Bir void işaretçi, işaretçinin türü olarak void anahtar kelimesini kullanarak normal bir işaretçi gibi bildirilir:

```cpp
void* ptr {}; // ptr bir void işaretçidir
```
Bir void işaretçi, herhangi bir veri türündeki nesnelere işaret edebilir:

```cpp
int nValue {};
float fValue {};

struct Something
{
    int n;
    float f;
};

Something sValue {};

void* ptr {};
ptr = &nValue; // geçerli
ptr = &fValue; // geçerli
ptr = &sValue; // geçerli
```
Ancak, void işaretçi işaret ettiği nesnenin ne tür olduğunu bilmediği için, bir void işaretçinin dereferansı yasadışıdır. Bunun yerine, void işaretçi önce başka bir işaretçi türüne dökülmeli ve ardından dereferans gerçekleştirilebilir.

```cpp
int value{ 5 };
void* voidPtr{ &value };

// std::cout << *voidPtr << '\n'; // illegal: void işaretçinin dereferansı

int* intPtr{ static_cast<int*>(voidPtr) }; // ancak, void işaretçimizi bir int işaretçisine dökersek...

std::cout << *intPtr << '\n'; // sonra sonucun dereferansını yapabiliriz
```
Bu, şunu yazdırır:

5
Sonraki bariz soru şudur: Eğer bir void işaretçi neye işaret ettiğini bilmiyorsa, onu neye dökeceğimizi nasıl biliriz? Sonuçta, bunu takip etmek size bağlıdır.

ışte bir void işaretçinin kullanıldığı bir örnek:

```cpp
#include <cassert>
#include <iostream>

enum class Type
{
    tInt, // not: burada "int" kullanamayız çünkü bu bir anahtar kelime, bu yüzden "tInt" kullanacağız
    tFloat,
    tCString
};

void printValue(void* ptr, Type type)
{
    switch (type)
    {
    case Type::tInt:
        std::cout << *static_cast<int*>(ptr) << '\n'; // int işaretçisine dök ve indireksiyonu gerçekleştir
        break;
    case Type::tFloat:
        std::cout << *static_cast<float*>(ptr) << '\n'; // float işaretçisine dök ve indireksiyonu gerçekleştir
        break;
    case Type::tCString:
        std::cout << static_cast<char*>(ptr) << '\n'; // char işaretçisine dök (indireksiyon yok)
        // std::cout, char*'ı bir C-stili dize olarak ele alacak
        // eğer sonucun indireksiyonunu gerçekleştirirsek, o zaman sadece ptr'nin işaret ettiği tek karakteri yazdırırız
        break;
    default:
        std::cerr << "printValue(): geçersiz tür sağlandı\n";
        assert(false && "tür bulunamadı");
        break;
    }
}

int main()
{
    int nValue{ 5 };
    float fValue{ 7.5f };
    char szValue[]{ "Mollie" };

    printValue(&nValue, Type::tInt);
    printValue(&fValue, Type::tFloat);
    printValue(szValue, Type::tCString);

    return 0;
}
```
Bu program, şunu yazdırır:

5
7.5
Mollie

Void ışaretçi Çeşitliliği

Void işaretçileri null değerine ayarlanabilir:

```cpp
void* ptr{ nullptr }; // ptr şu anda null bir işaretçi olan bir void işaretçidir
```
Bir void işaretçi işaret ettiği nesnenin ne tür olduğunu bilmediği için, bir void işaretçiyi silmek tanımsız davranışa yol açar. Eğer bir void işaretçiyi silmeniz gerekiyorsa, önce onu uygun türe geri dökün.

Bir void işaretçi üzerinde işaretçi aritmetiği yapmak mümkün değildir. Bu, işaretçinin ne boyutta bir nesneye işaret ettiğini bilmek zorunda olmasıdır, böylece işaretçiyi uygun şekilde artırabilir veya azaltabilir.

Bir void referansı olduğunu unutmayın. Bu, bir void referansının void & türünde olacağı ve hangi türde bir değeri referans aldığını bilmediği anlamına gelir.

Kaynak: Bing ile konuşma, 12.03.2024
(1) github.com. https://github.com/krishnakumarg1984/learncpp/tree/eb96567fb4699f6f3d06e191670d63df2e5cb7ed/10_chapter%2Fstatic_cast_voidptr.cpp.

Sonuç

Genel olarak, mutlaka gerekli olmadıkça void işaretçilerini kullanmaktan kaçınmak iyi bir fikirdir, çünkü bu etkin bir şekilde tip kontrolünü atmanızı sağlar. Bu, anlam ifade etmeyen şeyler yapmanıza yanlışlıkla izin verir ve derleyici bundan şikayet etmez. Örneğin, aşağıdaki geçerli olacaktır:

```cpp
int nValue{ 5 };
printValue(&nValue, Type::tCString);
```

Ama kim bilir sonuç aslında ne olurdu!

Yukarıdaki fonksiyon, tek bir fonksiyonun birden çok veri tipini ele almasının düzgün bir yolu gibi görünse de, C++ aslında aynı şeyi yapmanın (fonksiyon aşırı yüklemesi aracılığıyla) çok daha iyi bir yolunu sunar ve kötüye kullanmayı önlemek için tip kontrolünü korur. Void işaretçilerinin bir zamanlar birden çok veri tipini ele almak için kullanılacağı birçok yer şimdi şablonlar kullanılarak daha iyi yapılır, bu da güçlü tip kontrolü sunar.

Ancak, çok nadiren, void işaretçisi için makul bir kullanım bulabilirsiniz. Sadece, diğer dil mekanizmalarını kullanarak aynı şeyi yapmanın daha iyi (daha güvenli) bir yolu olmadığından emin olun!

*/
