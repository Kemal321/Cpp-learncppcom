// ch7.cpp : This file contains the 'main' function. Program execution begins and ends there
#include <iostream>
//#include "add.h"
int main()
{
	// 	{ } -> Buna Compound statements deniyor aynı zamanda block veya code bloğu deniyor. Sonunda noktalı virgül e ihtiyaç yok. 
	//  zaten burada block eklediğimize göre blocklar diğer blocklara eklenebilir. 
	/* Fonksiyonlarda kullanılan blokların seviyelerini 3 veya daha az tutmaya çalışın. Eğer fonksiyonunuz daha fazla iç içe geçmiş
	seviyelere ihtiyaç duyuyorsa, fonksiyonunuzu alt-fonksiyonlara bölerek yeniden düzenlemeyi düşünün. */

	
	// 2.9 un tekrarı Namespaceler.
	/*
	Bir "namespace" (isim alanı), isimleri birbirinden ayırt etmek amacıyla içinde isimler tanımlamanıza olanak tanıyan bir bölgedir.
	"namespace" içinde tanımlanan isimlere ait bir isim alanı kapsamı (namespace scope) sağlar.
	Bu da demek oluyor ki "namespace" içinde tanımlanan herhangi bir isim, diğer kapsamlardaki aynı isimlerle karıştırılmayacaktır.
	*/

	/*
	Her C++ dosyasının kendi global isim alanı (global scope) vardır ve bu global isim alanı dosya içinde tanımlanan her şeyi içerir.
	C++ da her hangi bir sınıf, fonksyion veya isim alanı (namespace) içinde tanımlanmayan. Tanımlayıcıların hepsini global scopede tanımlamış sayılır.

	*/
	/*
	* Sadece bildirimler (declarations) ve tanım (definition) ifadeleri global isim alanında görünebilir.
	* Bu, global isim alanında değişkenler tanımlayabileceğimiz anlamına gelir, ancak bu genellikle kaçınılması gereken bir uygulamadır.
	 
	#include <iostream> // handled by preprocessor

	// All of the following statements are part of the global namespace
	void foo();    // okay: function forward declaration in the global namespace
	int x;         // compiles but strongly discouraged: uninitialized variable definition in the global namespace
	int y { 5 };   // compiles but discouraged: variable definition with initializer in the global namespace
	x = 5;         // compile error: executable statements are not allowed in the global namespace	

	int main()     // okay: function definition in the global namespace
	{
	    return 0;
	}

	void goo();    // okay: another function forward declaration in the global namespace
	*/

	/*
	STD Namespace 
	--------------

	Aslında std::cout'un adı gerçekten std::cout değil. Aslında sadece cout'dur ve std, adlandırma alanı olan cout adlı tanımlamanın bir parçasıdır. 
	Çünkü cout, std adlı adlandırma alanında tanımlanmıştır, cout adındaki nesneler veya işlevlerin global adlandırma alanında tanımlanan cout
	adlı nesneler veya işlevlerle çakışmayacağını belirtir.

	Benzer şekilde, bir ad alanında tanımlanan bir tanımlayıcıya erişirken (örneğin std::cout),
	derleyiciye, tanımlanmış bir adlandırma alanının içindeki bir tanımlayıcıyı aradığımızı söylememiz gerekir.

	Önemli İpucu

	Bir adlandırma alanı içinde tanımlanan bir tanımlayıcıyı kullandığınızda, derleyiciye tanımlayıcının adlandırma
	alanının içinde olduğunu belirtmelisiniz.
	
	The "::" sembolü, kapsam çözüm operatörü(scope resolution operator) olarak adlandırılan bir operatördür. 
	:: sembolünün solundaki tanımlayıcı, :: sembolünün sağındaki adın hangi adlandırma alanında bulunduğunu belirler.
	Eğer :: sembolünün solunda bir tanımlayıcı belirtilmezse, global adlandırma alanı varsayılır.


	!!!!!!! en iyi hareket -> Bir adlandırma alanında tanımlanan tanımlayıcılara erişmek için açıkça adlandırma alanı ön eklerini kullanın.
	Bir tanımlayıcı bir adlandırma alanı ön eki içeriyorsa, tanımlayıcıya nitel ad denir.
	*/
	/*
	// using namespace std kullanımı - Ve neden kaçınmamız gerektiği 
	// örneğin helloworld programına bakalım. 
	using namespace std; -> buna "using directive" deniyor.
	int main(){
		cout<< "Hello, World!";
		return 0;
	}
	using directive bize std namespcesindeki tanımlayıcılara ( identifiers) ön ek olmadan ulaşabilme izni veriyor. Burada ilk zamandan beri merak
	ettiğimiz mevzu var aslında. Eğer using directive kullanırsak std:: lere gerek kalmaz ama bu durumda cout adında bir fonksiyon çalıştırdığımız
	da compiler std::cout mı yoksa bizim cout fonksiyonumuzun mu çalıştırılacağını anlamaz. Bu durum da hata verecektir. Bu da zaten namespacerlerin
	çıkış nedenine ters bir durum teşkil etmekte. O yüzden using directiveleri kullanmamak bizim için daha iyisidir. Belki bugün sorun yaşamayız ama 
	ileriki durumlarda standart kütüphaneye eklenecek fonksiyon veya değişkenlerin isimleri ile çakışması durumunda önceki yazdığımız kodlar patlayabilir.

	*/
	// 7.2 — User-defined namespaces and the scope resolution operator
	/*
	* Aynı programın ayrı dosyalarına (örneğin, iki kaynak dosyaya) aynı adı taşıyan iki veya daha fazla fonksiyon (veya global değişken) eklenirse,
	bu bir derleyici veya bağlayıcı (compiler or linker) hatasına yol açar, yukarıda gösterildiği gibi.
	* Aynı dosyaya iki veya daha fazla eş isimli fonksiyon (veya global değişken) eklenirse, bu bir derleyici hatasına yol açar.*/
	
	/*BİLGİ 
	Programlar büyüdükçe, tanımlayıcıların sayısı artar ve bu da bir isim çakışmasının olasılığının önemli ölçüde artmasına neden olur.
	Verilen bir kapsamdaki her isim, aynı kapsamdaki her diğer isimle potansiyel olarak çakışabilir, 
	bu nedenle tanımlayıcıları mümkün olan en küçük kapsamda tanımlama gerekliliği, 
	tanımlayıcıların sayısının doğrusal olarak artmasının potansiyel çakışmaların üssel olarak artmasına neden olan ana nedenlerden biridir.
	*/

	/*
												-----!!!!----KENDİ NAMESPACEMİZİ TANIMLAMAK -----!!!!----
	C++ "namespace" kelimesi ile kendi namespacemizi kurmamıza izin verir. Bunlara user-defined namespaces daha doğrusu program-defined namespaces denir
	örneğin	
	*/

/* BAŞARILI
////////////////////////QUIZ 7.3
	int x{};
	int y{};

	std::cout << "Enter an integer: ";
	std::cin >> x;
	std::cout << "Enter a larger integer: ";
	std::cin >> y;

	std::cout << "Swaping the values" << '\n';
	
	{
		int temp{};
		if (y < x) {
			temp = y;
			y = x;
			x = temp;
			std::cout << "The smaller value is " << x<<'\n';
			std::cout << "The larger value is " << y;
		}else
		{ 
			std::cout << "The smaller value is " << x << '\n';
			std::cout << "The larger value is " << y;
		}
		
	}*/
	return 0;
}
namespace namespaceIdentifier
{
	// namespacenin içeriği
	// namespacenin ismi namespaceIdentifier burada büyüz harfle yapmadık çoğu guru hala bunu öneriyor. 
	/*Büyük harfle başlayan isim alanı adlarını tercih etmenin bazı nedenleri:

	Program tanımlı türleri büyük harfle başlatmak gelenekseldir. Program tanımlı isim alanları için aynı kuralı kullanmak tutarlıdır (özellikle Foo::x gibi kalifiye bir isim kullanırken, burada Foo bir isim alanı veya sınıf türü olabilir).

	Diğer sistem veya kütüphane tarafından sağlanan küçük harfli isimlerle çakışmaları önlemeye yardımcı olur.

	C++20 standart belgesi bu stili kullanır.

	C++ Core yönergeleri belgesi bu stili kullanır.
	

	Burada gördüğünüz gibi namespace i global scopede tanımladık. Namespaceler global scope veya başka bir namespacenin içinde tanımlanmak zorundadır.
	Şidi foo.cpp ve goo.cpp örneğimizi tekrar bu bilgiler ışığında yapalım. 
	*/
}
namespace Foo // Foo adında bir namespace tanımladık.
{
	int doSomething(int x, int y) // Bu doSomething Foo namespaceye ait 
	{
		return x + y;
	}
}

namespace Goo 
{
	int doSomething(int x, int y) // Bu doSomething Goo namespaceye ait 
	{
		return x + y;
	}
}
// Buradan sonrasında ise main fonksiyonumuzda doSomething i kullanmak fakat burada hangi doSomething fonksiyonunun
// kullanılacağını derleyiciye iletmek durumundayız bunu yapmak için de 2 yol var 1 kapsam çözümleme operatörü veya using ifadeleridir.
/*
		Scope Resolution Operator (::) kullanarak namespaceye ulaşmak. 
		Bir namespaceye ulaşmanın en iyi yolu Scope Resolution Operator kullanmaktır. 
		int main(){
		std::cout<<Foo::doSomething(4,3)<<'\n';  -> İşte bu da kullanım örneği :))

		// Burada kapsam operatörünün bize sağladığı en büyük avantaj açıkça hangi namespaceyi kullanacağımızı seçebiliriz.
		// Bu da potansiyel belirsizlikleri ortadan kaldırır. 

		** ::doSomething() demiş olsaydık daha öncesinde söylediğimiz gibi ön eki olmayan kapsam operatörü bize global scopeyi vurgular. Yani 
		* burada doSomething her iki namespacede de olsa aynı zamanda global scopede olsa. Ön eksiz doSomething global daki fonksiyonu çağıracaktır.
		* 
		***
		* Bir tanımlayıcı (identifier) bir ad alanı içinde scope resolution olmadan kullanıldığında program nasıl çalışır ?
		* 1 - Program ilk olarak tanımlayıcı ile aynı isme sahip bir tanımlayıcı ile eşlemek için sırası ile ad alanlarını gezer. 
		* 2 - Eğer ad alanlarında bulamazsa en son olarak global scopeyi kontrol eder. 
		** Not olarak, global versiyonu çağırmak için kapsam belirtmeksizin scope resolution operatörü kullanıldığında
		**(::print()), global ad alanındaki print() fonksiyonu açıkça çağrılmış olur.
		}
		
*/
/*
					FORWARD DECLARATİON OF CONTENT İN NAMESPACES
	namespace içindeki tanımlayıcılar için bu ileri bildirimlerin(Forward declarations) de aynı namespace içinde olması gerekir.
*/
/*
					MULTIPLE NAMESPACE BLOCKS ARE ALLOWED 
	aynı ad alanını birden fazla yerde veya dosyada tanımlamanıza ve bu tanımların birbirleriyle birleştirilmesine olanak tanır. 
	Bu, büyük projelerde ve kodun modüler olması gereken durumlarda kullanışlıdır. Örneğin,
	bir projeyi birden fazla dosyaya veya bileşene ayırdığınızda,
	her bileşen kendi namespace bloğunu tanımlayabilir ve bu bloklar sonunda birleştirilir.
	Bu, kodunuzu organize etmenize ve farklı parçalar arasında çakışma olmadan aynı ad alanı içinde çalışmanıza yardımcı olabilir.
	Yani burada Standart kütüphaneye kendi fonksiyonlarımızı ekleyebileceğimiz anlamına geliyor. Ama !! STD ye ekleme yapmamalıyız
	Bu tanımlanamayan hata veya davranışların ortaya çıkmasına neden olabilir işte orada patlarız gardaş.
*/
/*
					Nested Namespaces
	Namespaceler bir birine bağlanabilir yani bloklar şeklinde birleştirebiliriz örneğin:
*/
namespace Fooo
{
	namespace Gooo // Goo is a namespace inside the Foo namespace
	{
		int add(int x, int y)
		{
			return x + y;
		}
	}
}
// çağırma işlemi de bu şekilde gerçekleşir. 
//	std::cout << Fooo::Gooo::add(1, 2) << '\n';
// C++17 de ise stili biraz farklı 
namespace Foooo::Goooo // Goo is a namespace inside the Foo namespace (C++17 style)
{
	int add(int x, int y)
	{
		return x + y;
	}
}
// Ama çağırım şekli değişmiyor aynı şekilde çağırarak kullansakta tanımlaması biraz farklı.

/* 
					NAMESPACE ALIASES
Bu ifade, iç içe geçmiş bir ad alanında bir değişkenin veya fonksiyonun tam adını yazmak zor olabileceğinden,
C++'ın ad alanlarını geçici olarak kısaltmanıza izin veren ad alan takma adları (namespace alias) oluşturmanıza izin verildiğini belirtiyor.
Yani, uzun bir ad alanı dizisini geçici olarak daha kısa bir şey haline getirmenizi sağlar. Örneğin:

*/
namespace ns1 {
	namespace ns2 {
		namespace ns3 {
			int someVariable = 42;
		}
	}
}
/*Yukarıdaki gibi iç içe geçmiş ad alanlarının içinde bulunan someVariable 
değişkenine erişmek için tam adı yazmak zor olabilir. Bu nedenle, bir takma ad oluşturarak 
bu ad alanlarını daha kısa bir şekilde kullanabilirsiniz:*/
namespace n = ns1::ns2::ns3;
// Kullanımı
//	int value = n::someVariable;


/* Ad alanı takma adlarının güzel bir avantajı, eğer ns1::ns2::ns3 içindeki işlevselliği farklı bir yere taşımak isterseniz,
sadece n takma adını yeni hedefi yansıtacak şekilde güncellemeniz gerekeceğidir.
Böylece ns1::ns2::ns3'nun her bir örneğini bulup değiştirmeniz gerekmez. Bu, kodunuzu daha esnek hale getirebilir
ve büyük projelerde yeniden düzenlemeyi kolaylaştırabilir.*/


// Genel olarak bakacak olursak çok derin namespacelerden uzak durmak gerek. 

/*
					EN ÖNEMLİ KISIM TABİ ÖĞRENDİKTEN SONRA NEREDE KULLANCAZ
		Uygulamalarda, ad alanları uygulamaya özgü kodu daha sonra yeniden kullanılabilir 
		kodlardan (örneğin, matematik işlevleri) ayırmak için kullanılabilir. Örneğin, fizik ve
		matematik işlevleri bir ad alanında (örneğin, Math::) yer alabilir. Dil ve yerelleştirme
		işlevleri başka bir ad alanda (örneğin, Lang::) yer alabilir.Başkalarına dağıtmak istediğiniz
		bir kütüphane veya kod yazdığınızda, kodunuzu her zaman bir ad alanı içine koyun. 
		Kütüphanenizin kullanıldığı kodlar her zaman en iyi uygulamaları takip etmeyebilir.
		Bu durumda, kütüphanenizin deklarasyonlarının bir ad içinde olmaması, isim çakışmalarının
		meydana gelme olasılığını artırır. Ek bir avantaj olarak, kütüphane kodunu bir ad alanı içine koymak,
		kullanıcının kod editörünün otomatik tamamlama ve öneri özelliğini kullanarak kütüphanenizin içeriğini görmesini sağlar.

*/

/*
					LOCAL VARIABLES -> Ya dayı biraz eskiden kalan bilgiler yeterli gibi geldi o yüzden çok not almicam.
	Yerel değişkenlerin hiçbir bağlantısı yoktur. Bağlantı, tanımlayıcının diğer aynı adın deklarasyonlarının aynı nesneyi ifade edip 
	etmediğini belirler.	Yerel değişkenlerin bağlantısı yoktur, bu da her deklarasyonun benzersiz bir nesneye işaret ettiği anlamına gelir.
	Örnek olarak:
	int main()
{
	int x { 2 }; // local variable, no linkage

	{
		int x { 3 }; // this identifier x refers to a different object than the previous x
	}

	return 0;
}


	Scope ve linkage benzer gibi görünebilir. Ancak, scope bir deklarasyonun nerede görülebileceğini ve kullanılabileceğini tanımlar. 
	Linkage ise birden fazla deklarasyonun aynı nesneye işaret edip etmediğini belirler.
		
	*BEST*Değişkenleri en sınırlı mevcut scope de tanımlayın. Değişkenlerin kapsamını sınırlamak için
	yeni bloklar oluşturmak yerine mevcut en kapsamlı blokları kullanmaya çalışın
*/

/*
											GLOBAL VARIABLES
	Sıra geldi Global değişkenlere. Global değişkenler fonksiyonın dışında tanımlanan değişkenlerdir. 
	Geleneksel olarak Global değişkenler include nin altında main in üstünde tanımlanır. Global değ. 
	her yerde kullanılırlar. Farklı olarak başka ad alanları içinde de tanımlanabilir örneğin:*/
namespace Foo // Foo is defined in the global scope
{
	int g_x{}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
	// global variables can be seen and used everywhere in the file
	Foo::g_x = 3;
	std::cout << Foo::g_x << '\n';
}//int main()
/*	"G_x" tanımlayıcısı artık "Foo" ad alanının kapsamına sınırlı olsa da bu isim hala genel olarak
	 erişilebilir durumdadır (Foo::g_x aracılığıyla) ve "g_x" hala bir global değişkendir. Yani foo yok edilirse o da yok olacaktır.
	 Global değişkenler program başladığında başlar ve program sonlandığından sonlanır bu yüzden onlara static duration veya statik değişken denir.

														İsimlendirme
	 Geleneksel olarak global değişkenleri belirtmek için g ve g_ ön eki kullanılır. BUnun 3 nedeni vardır. 
	 Diğer küresel ad alanındaki tanımlarla ad çakışmalarını önlemeye yardımcı olur.
	 İsimsizlik (ad gizleme) adını verdiğimiz durumları önlemeye yardımcı olur (bu konuyu 7.5. dersimizde daha fazla ele alıyoruz).
	 Önekli değişkenlerin, fonksiyonun kapsamının ötesinde var olduğunu ve bu nedenle yaptığımız değişikliklerin de kalıcı olacağını göstermeye yardımcı ol
	 
	 Tabi küresel değişken bir ad alanı içerisindeyse o zaman kullanmaya gerek kalmayabilir çünkü ilk 2 neden artık göz ardı edilebilir olur. 
	 Fakat yine de kullanmakta 3.neden den doalyı bir sorun görülmemekte. 


	** BEST**sabit olmayan küresel değişkenleri, local değişkenlerden ve fonk. paramlardan ayırt etmek için g, g_ ön eklerini kullanmayı düşünmeliyiz.
	 *
										GLOBAL DEĞİŞKENLERİN BAŞLATILMASI
	 
	 Global değişkenler C++ de bşalatılmadığı zaman 0 ile otomatik olarak başlatılır. Ek olarak global değişkenlerde sabit değer olur 
	 fakat sabit değerli global değişkenler initialize edilmelidir. 

	 int g_x;       // no explicit initializer (zero-initialized by default)
	 int g_y {};    // value initialized (resulting in zero-initialization)
	 int g_z { 1 }; // list initialized with specific value
	 
	 Genel Özet
	 // Non-constant global variables
	 int g_x;                 // defines non-initialized global variable (zero initialized by default)
	 int g_x {};              // defines explicitly value-initialized global variable
	 int g_x { 1 };           // defines explicitly initialized global variable

	 // Const global variables
	 const int g_y;           // error: const variables must be initialized
	 const int g_y { 2 };     // defines initialized global const

	 // Constexpr global variables
	 constexpr int g_y;       // error: constexpr variables must be initialized
	 constexpr int g_y { 3 }; // defines initialized global constexpr
	 */

	/*
								7.5 İsim gölgeleme

	Her bir block kendi scope alanını oluşturur fakat block içinde ve dışında aynı ada sahip 2 
	değişken olduğu zaman Bağımlı değişkenler dış taraftaki değişkeni saklar. Buna isim saklama (name hiding) veya gölgeleme
	(shadowing) denir.

	Local değişkenleri gölgeleme
	----------------------------

	int main()
	{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
	} // outer block apples destroyed
	
	Burada içeride apples tanımladığımız için sonradan apples a 10 atamamız dışarıdaki apples i etkilemiyor yani onu saklıyoruz ve yeni
	oluşturduğumuz apples değişkeni üzerinde çalışıyoruz. Nested block bitince değişkenler öldükten sonra. Dış blockta var olan apples değişkeni 
	kaldığı yerden devam eder.

	!!!! Burada içeride bir apples değişkeni oluşturmamış olsaydık bu gölgeleme olmazdı yani dışarıdaki apples üstünden işlem yapmaya devam ederdik
	yani bu durumda yaptığımız değişimler dışarıda var olan apples değişkenini etkilerdi.

	Bağlı blocka girdiğimiz zaman outer blocktan gölgelenmiş apples e ulaşmanın bir yolu yoktur. !!!!!!!


	GLOBAL DEĞİŞKENLERİ GÖLGELEME 
	-----------------------------
	 yerel değişkenlerin, aynı ada sahip global değişkenleri gölgeler. Yani, bir yerel değişkenin adı, 
	 bir global değişkenin adıyla aynı olduğunda, bu yerel değişken, tanımlandığı kapsam içinde bu ada sahip
	 global değişkeni geçersiz kılacaktır. Bu, programcılara aynı ada sahip farklı değişkenlerin farklı
	 kapsamlarda kullanılmasına olanak tanır. Gölgeleme (shadowing) olarak adlandırılan bu durum, yerel bir 
	 değişkenin daha öncelikli olduğu anlamına gelir ve bu kapsamda kullanıldığında global değişkeni gölgeleyebilir.
	 Bu, yerel ve global değişkenlerin adlarının çakışmasını önler.


	 #include <iostream>
	 int value { 5 }; // global variable

	 void foo()
	 {
	 std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
	 }

	 int main()
	 {
	 int value { 7 }; // hides the global variable value until the end of this block

	 ++value; // increments local value, not global value

	 std::cout << "local variable value: " << value << '\n';

	 foo();

	 return 0;
	 } // local value is destroyed
	 This code prints:

	 local variable value: 8
	 global variable value: 5



	 !!!!*** Burada namespace konusunda gördüğümüz gibi (::) scope resolution operatörü ile beraber kullandığımızda global değişken üzerinde 
	 değişimler gerçekleştirdiğimizi anlamış oluruz. --(::value) -> Global değişkende azalma yapar locak de değil yani.
	 gcc de bunun Wshadow=global veya local diyerek kodları varmış. 

	 !!!!! BEST -> Değişken gölgelemeden kaçının.
	*/


/*
													7.7 INTERNAL LINKAGE
	Linkage yani bağlantı daha öncesinde bağlantının bir identifier ın aynı isme sahip diğer identifier ile aynı nesneye refer edip etmediğini 
	belirtmek için kullanıldığını not almışız. ve local değişkenlerin bağlantılarının olmadığından bahsettik.

	Fakat- Global değişkenler ve fonksiyonlar iç bağlantı (internal linkage) veya dış bağlantıya (external linkage) sahip olabilirler.

	Dahili bağlantıya sahip bir tanımlayıcı, yalnızca tek bir çeviri birimi içinde görülebilir ve kullanılabilir, ancak diğer çeviri birimlerinden
	erişilemez (yani, bağlayıcıya açık değildir). Bu, iki kaynak dosyanın dahili bağlantıya sahip eşit adlı tanımlayıcılara sahipse, bu
	tanımlayıcıların bağımsız olarak işleme alınacağı anlamına gelir (ve aynı tanımlamaları çift olarak yapma nedeniyle ODR ihlali ortaya çıkmaz).

	Yani Dahili bağlantıya sahip bir tanımlayıcı, yalnızca tek bir çeviri birimi içinde görülebilir ve kullanılabilir, ancak diğer çeviri 
	birimlerinden erişilemez (yani, bağlayıcıya açık değildir). Bu, iki kaynak dosyanın dahili bağlantıya sahip eşit adlı tanımlayıcılara sahipse,
	bu tanımlayıcıların bağımsız olarak işleme alınacağı anlamına gelir (ve aynı tanımlamaları çift olarak yapma nedeniyle ODR ihlali ortaya çıkmaz).

										GLOBAL DEĞİŞKENLERDE İÇ BAĞLANTI

	İç bağlantılı global değişkenlere bazen iç değişkenler(internal variable) adı verilir.

	Sabit olmayan bir global değişkeni dahili(İNTERNAL) yapmak için "static" anahtar sözcüğünü kullanırız.

	#include <iostream>

	static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

	const int g_y{ 1 }; // const globals have internal linkage by default
	constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

	int main()
	{
		std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
		return 0;
	}

	Const ve constexpr global değişkenler, varsayılan olarak iç bağlantıya sahiptir
	(bu nedenle static anahtar kelimesine ihtiyaç duymazlar - kullanılırsa, yoksayılır).

	Mesela a.cpp dosyasında		[[maybe_unused]] constexpr int g_x { 2 }; olsun Bu iç g_x sadece a.cpp içinden erişilebilir 

	For advanced readers
	Yukarıda kullanılan static anahtar kelimesi, bir depolama sınıf belirleyicisi( storage class specifier ) örneğidir ve hem ismin bağlantısını 
	hem de 	depolama süresini ayarlar. En yaygın kullanılan depolama sınıf belirleyicileri static, extern ve mutable'dir. Depolama sınıf
	belirleyicisi terimi genellikle teknik belgelerde kullanılır.

														FONKSİYONLARDA İÇ BAĞLANTI
	Her bir "tanımlayıcı" (identifier), bir şeyin (değişken, fonksiyon vb.) adını temsil eder. Bu tanımlayıcıların bağlantı özelliği vardır. 
	"Bağlantı," bir tanımlayıcının bir program içinde nasıl kullanılabileceğini belirler.

	Özellikle "fonksiyon tanımlayıcıları"nın (fonksiyon isimleri) değişken isimleri gibi bir bağlantı özelliğine sahiptir. Fonksiyonlar varsayılan
	olarak "dış bağlantıya" sahiptir. Yani, bir fonksiyonun adı farklı kaynak dosyalarında veya çeviri birimlerinde paylaşılabilir.

	Ancak, "static" anahtar kelimesi kullanılarak bir fonksiyonun bağlantı özelliği "iç bağlantıya" çevrilebilir. Bu durumda, bu fonksiyon sadece
	tanımlandığı aynı kaynak dosyasında kullanılabilir ve dışarıdan erişilemez hale gelir.

	Yani, "fonksiyonların bağlantı özellikleri, değişkenlerinkiyle aynıdır ve bir fonksiyonun bağlantı özelliği 'dış' olabilir (varsayılan) veya 
	'iç' olabilir (static anahtar kelimesi kullanılarak belirlenmiş)."

	a.cpp diye bir fonksiyon olsun:
	// Bu fonksiyon static olarak tanımlandı, artık sadece bu dosya içerisinden ulaşılabilir.
	// başka bir dosyadan ulaşmak için forward declaration kullandığımızda failleyeceğiz.
	[[maybe_unused]] static int add(int x, int y)
	{
		return x + y;
	}

	örneği main.cpp: -> Bu dosya bağlanmayacaktır çünkü a.cpp de add fonksiyonu dışarıdan erişilebilir değil.
	#include <iostream>

	static int add(int x, int y); // forward declaration for function add

	int main()
	{
		std::cout << add(3, 4) << '\n';

		return 0;
	}


	ODR kuralının, bir nesnenin veya fonksiyonun, bir dosya veya program içinde birden fazla tanımı olamayacağını söyledi.
	Ancak, farklı dosyalarda tanımlanan dahili nesnelerin (ve fonksiyonların) bağımsız varlıklar olarak kabul edildiğini 
	(isimleri ve türleri aynı olsa bile) ve dolayısıyla ODR kuralının ihlal edilmediğini belirtmekte fayda var.
	Her dahili nesnenin yalnızca bir tanımı vardır.

											STATIC VS. İSİMSİZ AD ALANLARI
	Modern C++'ta, tanımlayıcılara iç bağlantı sağlamak için static anahtar kelimesi kullanımı pek tercih edilmiyor. Adlandırılmamış 
	(unnamed) isim alanları, daha geniş bir tanımlayıcı yelpazesine (örneğin, tür tanımlayıcıları) iç bağlantı sağlayabilir ve birçok
	tanımlayıcıya iç bağlantı sağlamak için daha uygun bir seçenektir.

	Neden tanımlayıcılara iç bağlantı verme zahmetine girmeliyiz?

	Genellikle tanımlayıcılara iç bağlantı vermenin iki yaygın nedeni vardır:

	1- Başka dosyalardan erişilemez olmasını istediğimiz bir tanımlayıcı vardır. Bu, karıştırılmasını istemediğimiz bir global değişken 
	olabilir veya çağrılmasını istemediğimiz bir yardımcı fonksiyon olabilir.
	
	2- İsim çakışmalarından kaçınma konusunda pedantik olmak. İç bağlantıya sahip tanımlayıcılar, bağlayıcıya açık olmadıkları için yalnızca
	aynı çeviri birimindeki isimlerle çakışabilir, programın genelinde değil.
	Birçok modern geliştirme kılavuzu, başka bir dosyadan kullanılmayacak her değişken ve fonksiyona iç bağlantı verilmesini önerir. 
	Eğer disiplinli bir yaklaşımınız varsa, bu iyi bir öneridir.

	Şu anda, minimum olarak bir hafif yaklaşımı öneriyoruz: Başka dosyalardan erişimi yasaklamak için açık bir nedeni olan her 
	tanımlayıcıya iç bağlantı verin. Tanımlayıcılara iç bağlantı verin, başka dosyalardan erişimi açıkça engellemek istediğiniz bir 
	nedeniniz olduğunda.
	Başka dosyalardan erişime izin vermek istemediğiniz tüm tanımlayıcılara iç bağlantı vermeyi düşünün (bunun için adlandırılmamış 
	bir isim alanı kullanın).


	GENEL ÖZET::::::
	// İç bağlantılı global değişken tanımlamaları:
	static int g_x;          // başlatılmamış iç bağlantılı global değişkeni tanımlar (varsayılan olarak sıfırlanır)
	static int g_x{ 1 };     // başlatılmış iç bağlantılı global değişkeni tanımlar

	const int g_y { 2 };     // başlatılmış iç bağlantılı global sabit değişkeni tanımlar
	constexpr int g_y { 3 }; // başlatılmış iç bağlantılı global constexpr değişkeni tanımlar

	// İç bağlantılı fonksiyon tanımlamaları:
	static int foo() {};     // iç bağlantılı fonksiyonu 
*/
	
/*
														7.7 EXTERNAL LİNKAGE
	Dış bağlantıya sahip bir tanımlayıcı, tanımlandığı dosyanın yanı sıra diğer kod dosyalarından da görülebilir ve kullanılabilir
	(bir önceden bildirim aracılığıyla). Bu bağlamda, dış bağlantıya sahip tanımlayıcılar gerçekten "genel"dir çünkü programınızın
	herhangi bir yerinde kullanılabilirler!

	Fonksiyonlar varsayılan olarak harici bağlatıya ( External linkage ) sahiptir. 
	Daha önce farklı dosyalara koyduğumuz fonksiyonları kullanabilmemizin nedeni buydu zaten. Forward declaration yaptıktan sonra compiler
	Bu durumu okeyler ve linker da bağlantıyı yapmaya hak kazanır gibi bir durum var yani. 

	Global değişkenler external linkage ile kullanıldığın external variable olarak da adlandırılabilirler. Bir global değişkeni external yapmak için
	"external" kelimesini kullanmamız yeterli örneğin: 
	int g_x{2}; -> non-const global değişkenler Varsayılan olarak zaten external linkage olur extern kelimesini kullanırsak umursanmaz yani atlanır. 
	extern const int g_y {3}; -> Const global değişkenler Varsayılan olarak internal linkageleri olur.const veya constexpr external olarak tanımlanabilir.
	Bir external linkageli sabit değişkeni kullanmak için ( başka bir dosyada ) onu forward declaration ile tanımlamamız lazım bunu da yine 
	"external" kelimesi ile yaparız. Mesela :
	a.cpp -> extern const int g_y {3}; olsun bunu b.cpp den çağırmak için başına extern const int g_y; diyerek initialize etmeden forward declaration
	yapmamız gerekir. Burada "extern" kelimesi bir değişkeni extern yaparken başka bir yerde forward yapıyor yani farklı bağlamlarda farklı anlam alıyor. 
	İleride anlatılacak. 

	AMA *** Başlatılmamış, const olmayan bir global değişken tanımlamak istiyorsanız extern anahtar sözcüğünü kullanmayın, aksi takdirde C++, değişken
	için bir ileri bildirim yapmaya çalıştığınızı düşünecektir.

	AMA *** Constexpr değişkenlerine extern anahtar sözcüğü aracılığıyla harici bağlantı verilebilmesine rağmen, bunlar ileriye doğru bildirilemezler,
	dolayısıyla onlara harici bağlantı vermenin hiçbir değeri yoktur.
	Bunun nedeni, derleyicinin constexpr değişkeninin değerini (derleme zamanında) bilmesi gerekmesidir. Bu değer başka bir dosyada tanımlanmışsa,
	derleyicinin o diğer dosyada hangi değerin tanımlandığı konusunda görünürlüğü yoktur.

	Değişken ileri bildirimleri, başlatılmamış değişken tanımlarını değişken ileri bildirimlerinden ayırt etmeye yardımcı olmak için extern anahtar
	sözcüğüne ihtiyaç duyar (aksi takdirde aynı görünürler): Fakat fonksiyonların böyle bir ihtiyacı yoktur çünkü fonksiyonu ileri yönde tanımlayıp
	tanımlamadığımız o fonksiyonun gövdesini oluşturup oluşturmamamıza bağlı olarak anlaşılır zaten. 

	Kısaca 
	// non-constant
	int g_x;               // değişken tanımı (istendiğinde başlatıcıya sahip olabilir)
	extern int g_x;        // ileri bildirim (başlatıcı yok)

	// constant
	extern const int g_y { 1 };   // değişken tanımı (const başlatıcıya sahip olmayı gerektirir)
	extern const int g_y;         // ileri bildirim (başlatıcı yok)

	// External global variable definitions:
	int g_x;                          // başlatılmamış dış bağlantılı global değişken tanımlar (varsayılan olarak sıfırlanır)
	extern const int g_x{ 1 };        // başlatılmış sabit dış bağlantılı global değişken tanımlar
	extern constexpr int g_x{ 2 };    // başlatılmış constexpr dış bağlantılı global değişken tanımlar

	// Forward declarations
	extern int g_y;                   // başlatılmamış olmayan sabit dış bağlantılı global değişken için ileri bildirim
	extern const int g_y;             // başlatılmış sabit dış bağlantılı global değişken için ileri bildirim
	extern constexpr int g_y;         // izin verilmez: constexpr değişkenleri ileri bildirim yapalamaz



	Kısa özet 2

	Kapsam (scope), bir değişkenin nereden erişilebilir olduğunu belirler. Süre (duration), bir değişkenin ne zaman oluşturulup yok edileceğini 
	belirler. Bağlantı (linkage), değişkenin başka bir dosyaya ihraç edilip edilemeyeceğini belirler.

	Global değişkenler, genel kapsama (ya da dosya kapsamı) sahiptir, yani onlara deklare edildikleri noktadan başladığı dosyanın sonuna kadar
	erişilebilir.

	Global değişkenler, statik süreye sahiptir, yani program başladığında oluşturulur ve program sona erdiğinde yok edilir.

	Global değişkenler, static ve extern anahtar kelimeleri aracılığıyla sırasıyla iç bağlantıya veya dış bağlantıya sahip olabilir.
*/

/*
												7.8 — Neden (const olmayan) global değişkenler kötüdür
Eğer bir deneyimli programcıdan iyi programlama uygulamaları konusunda bir tavsiye isteseniz, muhtemelen düşündükten sonra en olası cevap şu olacaktır:
"Global değişkenlerden kaçının!". Ve bunun iyi bir nedeni var: global değişkenler dil içinde tarihsel olarak en çok kötüye kullanılan kavramlardan
biridir. Küçük akademik programlarda zararsız gibi görünebilirler, ancak geniş programlarda genellikle sorunlara yol açarlar.

Yeni programcılar genellikle birçok global değişken kullanma eğilimindedir, çünkü özellikle farklı fonksiyonlara yapılan birçok çağrı içeriyorsa 
(veriyi fonksiyon parametreleri aracılığıyla iletmek uğraştırıcıdır), global değişkenlerle çalışmak kolaydır. Ancak genellikle bu iyi bir fikir 
değildir. Birçok geliştirici, değiştirilebilir olmayan (const) global değişkenlerin tamamen kaçınılması gerektiğine inanmaktadır.

Ancak bu konuya geçmeden önce bir açıklama yapmalıyız. Geliştiriciler size global değişkenlerin kötü olduğunu söylediklerinde, genellikle tüm 
global değişkenlerden bahsetmiyorlar. Genellikle değiştirilebilir olmayan (const) global değişkenlerden bahsediyorlar.

Aga kullanma işte ya çok uzun ama çok güzel yazmış hoca mevzuyu güzel açıklamış aynı benim kafadan. 

Kısacası global değişkenler programın durumunu öngörülemez hale getiriyor. Her işlev çağrısı potansiyel olarak tehlikeli hale gelir ve programcının 
hangilerinin tehlikeli, hangilerinin olmadığını bilmesinin kolay bir yolu yoktur! Yerel değişkenler çok daha güvenlidir çünkü diğer işlevler onları
doğrudan etkileyemez. Yani global değişken nerede değiştirildi farketmeden bir yerde değiştirilirse paket olursun.

Özellikle, önemli "karar noktası" değişkenleri için (örneğin, yukarıdaki örnekte olduğu gibi bir koşullu ifadede kullanacağınız değişkenler, g_mode 
gibi) global değişkenler kullanmaktan kaçının. Programınız, bilgi değerini taşıyan bir global değişken değişirse (örneğin, kullanıcının adı gibi),
muhtemelen bozulmaz. Ancak programınızın gerçekten nasıl çalıştığını etkileyen bir global değişkeni değiştirirseniz, muhtemelen bozulur.

***BEST ** Mümkün olduğunda global değişkenler yerine yerel değişkenleri kullanın.

											Global değişkenlerin başlatma sırası problemi
Statik değişkenlerin (buna global değişkenler de dahil) başlatılması, program başlatılma aşamasının bir parçası olarak, main fonksiyonunun 
yürütülmesinden önce gerçekleşir. Bu iki aşamada ilerler.

İlk aşama, statik başlatma olarak adlandırılır. Statik başlatma aşamasında, constexpr başlatıcılara (sabitler de dahil) sahip global değişkenler, 
bu değerlere başlatılır. Ayrıca, başlatıcısı olmayan global değişkenler sıfır başlatılır.

İkinci aşama, dinamik başlatma olarak adlandırılır. Bu aşama daha karmaşık ve ince detaylara sahiptir, ancak özeti, constexpr başlatıcılara sahip
olmayan global değişkenlerin başlatılmasıdır.

!!!!!!!!!! Notların tamamı önemli okuyarak geçmeye karar verdim çünkü her satır vs.leri yazmam gerekecek diğerlerinden çok fazla zaten 1000 satır olcez
bu gidişler o yüzden sayfanın kendisinden okuyalım tekrar ederken. 
*/
/*
								7.9 — Global sabitleri birden fazla dosyada paylaşma (satır içi değişkenleri kullanarak)
Bazı uygulamalarda, belirli sembolik sabitler kodunuzun genelinde (sadece bir konumda değil) kullanılması gerekebilir. Bu, değişmeyen fizik veya
matematiksel sabitleri (örneğin, pi sayısı veya Avogadro sayısı) veya uygulama özelinde "ayar" değerlerini (örneğin, sürtünme veya yerçekimi 
katsayıları) içerebilir. Bu sabitleri her dosyada yeniden tanımlamak yerine (bu, "Kendini Tekrar Etme" kuralının ihlali anlamına gelir), daha
iyi bir yaklaşım, bunları bir kez merkezi bir konumda bildirmek ve gerektiğinde kullanmaktır. Böylece, bunları herhangi bir yerde değiştirmeniz
gerektiğinde, bunu yalnızca bir yerde değiştirmeniz ve bu değişikliklerin dışa yayılabilmesidir.

Global değişkenlerin Dahili değişken olarak ele almak.
--------------------------------------------------------
Bu başlık bir .cpp dosyasına #include edildiğinde, bu başlıkta tanımlanan her bir değişken, dahil edildiği kod dosyasına dahil edildiği noktada
kopyalanacaktır. Bu değişkenler bir işlevin dışında yaşadıkları için, dahil edildikleri dosya içinde global değişkenler olarak kabul edilir, 
bu nedenle bu dosyada herhangi bir yerde kullanabiliriz. Const global değişkenler iç bağlantıya sahip olduğundan, her .cpp dosyası,
bağlayıcının göremediği bağımsız bir global değişken sürümü alır. Çoğu durumda, bunlar const olduğundan, derleyici değişkenleri basitçe optimize eder
ve kullanılmaz hale getirir. Burada kullanılmazdan kastı compile time constlarda gördüğümüz işlem yani compile time constlarda derleyici sabit olan 
değerin zaten her zaman sabit olduğunu bildiği için örneğin constexpr int gravity {9.8}; kodda gravity nin değişmeyeceğini bildiği için gravity gördüğü
her yere 9.8 yazarak her hangi bir kopyalama işlemi yapmaz yani kullanılmaz olarak addedebiliriz sanırım.

"Optimize etme" terimi, derleyicinin programınızın performansını artırmak için çıktınızı etkilemeyen bir şekilde şeyleri kaldırma işlemine atıfta 
bulunur. Örneğin, bir const değişkeni x'in değeri 4'e başlatılmışsa ve kodunuz herhangi bir yerde x'e başvuruyorsa, derleyici x'i sadece 4 ile 
değiştirebilir (çünkü x const olduğundan, başka bir değere değişmeyecek) ve değişken oluşturup başlatma işlemini tamamen önleyebilir.

Global değişkenlerin harici değişken olarak ele alınması
--------------------------------------------------------
Yukarıda metod bir kaç dezavantaja sahiptir. 

Bu, basit bir yöntem olabilir (ve küçük programlar için uygundur), ancak her seferinde constants.h bir farklı kod dosyasına #include edildiğinde,
bu değişkenlerin her biri dahil olan kod dosyasına kopyalanır. Bu nedenle, constants.h'nin 20 farklı kod dosyasına dahil edilmesi durumunda,
bu değişkenlerin her biri 20 kez çoğaltılır. Header korumaları bunun önlenmesini sağlamaz, çünkü bunlar sadece bir başlık dosyasının bir dosyaya
birden fazla kez dahil edilmesini engeller, farklı kod dosyalarına bir kez dahil edilmesini değil. Bu durum iki zorluk ortaya çıkarır:

	1- Tek bir sabit değeri değiştirmek, sabit başlık dosyasını içeren her dosyanın yeniden derlenmesini gerektirebilir, bu da daha büyük projeler için
	uzun süren yeniden derleme sürelerine yol açabilir.
	2- Sabitler büyükse ve optimize edilemiyorsa, bu çok fazla bellek kullanabilir.
Bu sorunlardan kaçınmanın bir yolu, bu sabitleri harici değişkenlere dönüştürmektir, çünkü bu durumda bir kere başlatılmış tek bir değişkenimiz 
olabilir ve bu değişken tüm dosyalar arasında paylaşılır. Bu yöntemde sabitleri bir .cpp dosyasında tanımlayacağız (tanımlamaların yalnızca bir 
yerde bulunmasını sağlamak için) ve başlık dosyasında ileri bildirimler ekleyeceğiz (diğer dosyalar tarafından dahil edilecek).

*** Bu yöntemde constexpr yerine const kullanıyoruz çünkü constexpr değişkenler ileri bildirilemez, hatta dış bağlantıya sahip olsalar bile.
Bu, derleyicinin değişkenin değerini derleme zamanında bilmesi gerektiği için, bir ileri bildirim bu bilgiyi sağlamaz.
ÖRNEK:
		constants.cpp 
		-----------------------------------------------------------------------------------------------------------------------
		#include "constants.h"

		namespace constants
		{
			// actual global variables
			extern const double pi { 3.14159 };
			extern const double avogadro { 6.0221413e23 };
			extern const double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
		}

		constants.h
		------------------------------------------------------------------------------------------------------------------------
		#ifndef CONSTANTS_H
		#define CONSTANTS_H

		namespace constants
		{
			// Çünkü gerçek değişkenler bir ad alanının içinde olduğundan, ileri bildirimlerin de bir ad alanının içinde olması gerekir.
			extern const double pi;
			extern const double avogadro;
			extern const double myGravity;
		}

		#endif
		

		Kod dosyasındaki kullanım aynı kalır:
		main.cpp:
		-------------------------------------------------------------------------------------------------------------------------
		#include "constants.h" // include all the forward declarations

		#include <iostream>

		int main()
		{
			std::cout << "Enter a radius: ";
			double radius{};
			std::cin >> radius;

			std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

			return 0;
		}


	Global sembolik sabitlerin ad alanlı olması gerektiği için "g_" öneki kullanılmasına gerek yoktur.

	Şimdi sembolik sabitler yalnızca bir kez (constants.cpp'de) örneklendirilecek, constants.h'nin #included olduğu her kod dosyasında değil,
	bu sabitlerin tüm kullanımları constants.cpp'de örneklendirilen sürümle bağlantılandırılacaktır. constants.cpp'de yapılan herhangi bir 
	değişiklik sadece constants.cpp'nin yeniden derlenmesini gerektirecektir.

	Ancak, bu yöntemin bazı dezavantajları vardır. İlk olarak, bu sabitler artık yalnızca gerçekten tanımlandıkları dosya (constants.cpp) 
	içinde derleme zamanı sabitleri olarak kabul edilir. Diğer dosyalarda derleyici yalnızca ileri bildirimi görecek, bu da bir sabit değeri
	tanımlamaz (ve bağlayıcı tarafından çözülmelidir). Bu, diğer dosyalarda bunların derleme zamanı sabiti gerektiren herhangi bir yerde 
	kullanılamayacağı anlamına gelir. İkinci olarak, derleme zamanı sabitleri genellikle çalışma zamanı sabitlerinden daha fazla optimize 
	edilebildiğinden, derleyici bunları o kadar çok optimize edemeyebilir.


	Derleyici, bir değişkeni derleme zamanında (compile-time) bağlamda kullanılabilir kılmak için, yalnızca ileri bildirim (forward declaration) değil,
	tam tanımını görmelidir.

	Örneğin, bir dizi boyutunu belirlerken veya şablonlarda kullanırken, derleyiciye bu değerin derleme zamanında bilinmesi gerekir. Sadece ileri 
	bildirim, derleyicinin değişkenin tam tanımına erişmesine izin vermez. Dolayısıyla, derleyici, değişkenin tam tanımını gördüğünde, bu değeri 
	derleme zamanında kullanabilir ve optimize edebilir.

	Çünkü derleyici her kaynak dosyasını ayrı ayrı derlediği için, değişken tanımları sadece derlenen kaynak dosyasında (dahil edilen başlık dosyaları
	da bu kapsamda) görülebilir. Örneğin, constants.cpp'deki değişken tanımları, derleyici main.cpp'yi derlediğinde gözükmez. Bu nedenle, constexpr 
	değişkenleri başlık dosyasından ayrı bir şekilde tanımlamak mümkün değildir; bunlar başlık dosyasında tanımlanmalıdır.

	Yukarıda belirtilen dezavantajlardan dolayı, sabitlerinizi bir başlık dosyasında tanımlamayı tercih edin (ya önceki bölüme göre ya da bir sonraki 
	bölüme göre). Eğer sabitlerinizin değerleri sık sık değişiyorsa (örneğin, programı ayarlıyorsanız) ve bu durum uzun derleme sürelerine neden 
	oluyorsa, sadece sorunlu sabitleri ihtiyaç duyulduğunda bir .cpp dosyasına taşıyabilirsiniz.

	Global sabitlerin inline değişken olarak ele alınması
	-----------------------------------------------------
	Ders 5.7 -- Inline Fonksiyonlar ve Değişkenlerde, aynı olmaları koşuluyla birden fazla tanıma sahip olabilen "inline" değişkenleri ele almıştık. 
	Constexpr değişkenlerimizi "inline" yaparak, bunları bir başlık dosyasında tanımlayabilir ve ardından bunları ihtiyaç duyan herhangi bir .cpp
	dosyasına #include edebiliriz. Bu, hem ODR ihlallerini önler hem de değişkenlerin tekrarlanması dezavantajının önüne geçer.

	Constexpr işlevleri örtülü olarak satır içidir, ancak constexpr değişkenleri örtülü olarak satır içi değildir.

	örneğin: 
	constants.h:
	------------
	#ifndef CONSTANTS_H
	#define CONSTANTS_H

	// define your own namespace to hold constants
	namespace constants
	{
		inline constexpr double pi { 3.14159 }; // note: now inline constexpr
		inline constexpr double avogadro { 6.0221413e23 };
		inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
		// ... other related constants
	}
	#endif

	main.cpp:
	---------
	#include "constants.h"

	#include <iostream>

	int main()
	{
		std::cout << "Enter a radius: ";
		double radius{};
		std::cin >> radius;

		std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

		return 0;
	}

	Constants.h'yi istediğimiz kadar kod dosyasına dahil edebiliriz, ancak bu değişkenler yalnızca bir kez örneklenecek ve tüm kod dosyalarında
	paylaşılacaktır.

	Bu yöntem, herhangi bir sabit değer değiştirilirse, sabitler başlığını içeren her dosyanın yeniden derlenmesini gerektirme dezavantajını korur.

	**** BEST 
	* Genel sabitlere ihtiyacınız varsa ve derleyiciniz C++17 uyumluysa, satır içi constexpr genel değişkenlerini bir başlık dosyasında tanımlamayı
	*tercih edin.

	*** AR
	* Use std::string_view for constexpr strings. We cover this in lesson 5.10 -- Introduction to std::string_view.
*/
/*
															7.10 Static local değişkenler 
	"Static" terimi, büyük ölçüde farklı bağlamlarda farklı anlamlara sahip olduğu için C++ dilindeki en kafa karıştırıcı terimlerden biridir.

	Daha önceki derslerde, global değişkenlerin "static duration" (statik süre) özelliğine sahip olduğunu öğrendik, bu da program başladığında
	oluşturuldukları ve program sona erdiğinde yok edildikleri anlamına gelir.

	Aynı zamanda, static kelimesinin global bir tanımlayıcıya iç bağlantı sağladığını, bu da tanımlı olduğu dosya dışında kullanılamayacağı 
	anlamına geldiğini tartıştık.

	Bu derste, static anahtar kelimesinin yerel bir değişkene uygulandığında nasıl kullanıldığını inceleyeceğiz.

	Ders 2.5 - Yerel Kapsama Giriş'te öğrendiğiniz gibi, yerel değişkenler varsayılan olarak otomatik süreye sahiptir, bu da onların tanımlandıkları 
	noktada oluşturuldukları ve bloktan çıkıldığında yok edildikleri anlamına gelir.

	Static anahtar kelimesini bir yerel değişkene uygulamak, değişkenin süresini otomatik süreden statik süreye değiştirir. Bu, değişkenin artık
	programın başlangıcında oluşturulduğu ve programın sonunda yok edildiği anlamına gelir (tam olarak bir global değişken gibi). Sonuç olarak, 
	static değişken, kapsamı dışına çıktıktan sonra bile değerini koruyacaktır!

	Bir örnekle açıklamak daha iyi olacaktır:
	#include <iostream>

	void incrementAndPrint()
	{
		int value{ 1 }; // automatic duration by default
		++value;
		std::cout << value << '\n';
	} // value is destroyed here

	int main()
	{
		incrementAndPrint();
		incrementAndPrint();
		incrementAndPrint();

		return 0;
	}


	IncrementAndPrint() her çağrıldığında, value adında bir değişken oluşturulur ve 1 değerine atanır. IncrementAndPrint(),
	değeri 2'ye artırır ve ardından 2 değerini yazdırır. IncrementAndPrint()'in çalışması bittiğinde, değişken kapsamın dışına çıktığında yok edilir.
	Sonuç olarak, bu program çıktısını verir:
	2
	2
	2

	Birde static keyword ü ile tanımlandığında ne olacağına bakarsak daha iyi anlarız:
	#include <iostream>

	void incrementAndPrint()
	{
		static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
		++s_value;
		std::cout << s_value << '\n';
	} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

	int main()
	{
		incrementAndPrint();
		incrementAndPrint();
		incrementAndPrint();

		return 0;
	}

	Bu programda,s_value'nin static olarak bildiğildiği için program başında oluşturulur.

	Sıfır ile başlatılan veya bir constexpr başlatıcısı olan static yerel değişkenler, program başlangıcında başlatılabilir.
	
	
	Başlatıcısı olmayan veya bir consexpr başlatıcısı olmayan static yerel değişkenler, program başlangıcında sıfır olarak başlatılır.
	Başlatıcısı olmayan veya bir constexpr başlatıcısı olmayan static yerel değişkenler, değişken tanımı ilk kez karşılaşıldığında ilk kez başlatılır.
	Tanım sonraki çağrılarda atlanır, bu nedenle başka bir başlangıç ​​başlatması olmaz. Statik süreleri olduğu için açıkça başlatılmayan static yerel
	değişkenler varsayılan olarak sıfır olarak başlatılır.
	
	S_value'nin bir constexpr başlatıcısı olduğundan, s_value program başında başlatılacaktır.
	
	S_value'nin işlevin sonunda kapsamı dışına çıktığında, yok edilmez. Her seferinde incrementAndPrint() işlevi çağrıldığında, s_value'nin değeri
	önceki durumda bıraktığımız değerde kalır. Sonuç olarak, bu program şu çıktıyı üretir:
	2 
	3
	4

	Nerede kullancaz ?
	------------------
	"Tıpkı global değişkenleri "g_" ön ekiyle kullanmamız gibi, genellikle statik (static duration) yerel değişkenlere "s_" ön eki kullanmak yaygındır.

	Statik süreli yerel değişkenlerin en yaygın kullanımlarından biri benzersiz kimlik oluşturucular içindir. Bir program hayal edin ki birçok benzer
	nesneniz var (örneğin, bir oyunda birçok zombi tarafından saldırıya uğruyorsunuz veya bir simülasyonda birçok üçgen görüntülüyorsunuz). Bir hata 
	fark ettiğinizde, sorun yaşayan nesnenin hangisi olduğunu ayırt etmek neredeyse imkansız olabilir. Ancak her nesne yaratıldığında benzersiz bir
	tanımlayıcıya sahipse, nesneleri daha iyi ayırt etmek için sorun giderme yapmak daha kolay olabilir.

	Bir benzersiz kimlik numarası oluşturmak, statik süreli yerel bir değişkenle çok kolaydır:"
	int generateID()
	{
		static int s_itemID{ 0 };
		return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
	}
	Şimdi burada generateID fonksiyonunu inceleyelim:

	Bu işlev ilk çağrıldığında 0 değerini döndürür. İkinci kez çağrıldığında 1 değerini döndürür. Her çağrıldığında, önceki çağrıdan bir fazla 
	sayı döndürür. Bu sayıları nesneleriniz için benzersiz kimlikler olarak atayabilirsiniz. Çünkü s_itemID bir yerel değişken olduğu için,
	diğer işlevler tarafından "oynanması" mümkün değildir.

	Statik değişkenler, global değişkenlerin bazı avantajlarını sunar (programın sonuna kadar yok olmazlar), ancak görünürlüklerini blok 
	kapsamına sınırlar. Bu, onları anlamayı daha kolay ve değerlerini düzenli olarak değiştirseniz bile kullanmayı daha güvenli hale getirir.
	*/
// ****BEST  Statik local değişkenleri başlatmak en iyi davranış olur. Çünkü Statik yerel değişkenler, sonraki çağrılarda değil, 
// yalnızca kodun ilk çalıştırıldığında başlatılır.

/*
* Static local constants
Static yerel değişkenler const (veya constexpr) yapılabilir. Bir const static yerel değişkenin iyi bir kullanımı, bir fonksiyonun bir const değerini
kullanması gerektiğinde, ancak nesneyi oluşturmak veya başlatmak maliyetli olduğunda ortaya çıkar (örneğin, değeri bir veritabanından okumanız 
gerekiyorsa). Normal bir yerel değişken kullanırsanız, değişken her fonksiyon çalıştırıldığında oluşturulur ve başlatılır. Const/constexpr static 
yerel bir değişken ile maliyetli nesneyi bir kez oluşturabilir ve başlatabilir, ardından fonksiyon her çağrıldığında yeniden kullanabilirsiniz.

Statik yerel değişkenleri akışı değiştirmek için kullanma

Aşağıdaki kodu düşünün:

cpp
Copy code
#include <iostream>

	int getInteger()
	{
		static bool s_isFirstCall{ true };

		if (s_isFirstCall)
		{
			std::cout << "Bir tamsayı girin: ";
			s_isFirstCall = false;
		}
		else
		{
			std::cout << "Başka bir tamsayı girin: ";
		}

		int i{};
		std::cin >> i;
		return i;
	}

	int main()
	{
		int a{ getInteger() };
		int b{ getInteger() };

		std::cout << a << " + " << b << " = " << (a + b) << '\n';

		return 0;
	}
	Örnek çıkış

	yaml
	Copy code
	Bir tamsayı girin: 5
	Başka bir tamsayı girin: 9
	5 + 9 = 14
Bu kod işlevini yerine getirir, ancak statik yerel bir değişken kullandığımız için kodu anlamak daha zor hale getirdik. Eğer biri main()
fonksiyonundaki kodu, getInteger()'ın uygulamasını okumadan okursa, getInteger()'ın iki çağrısının farklı bir şey yaptığını varsaymak için 
hiçbir nedeni olmazdı. Ancak iki çağrı farklı bir şey yapıyor, bu farklılık bir değişiklikli bir uyarıdan daha fazlaysa çok kafa karıştırıcı olabilir.

Örneğin, mikrodalga fırınızda +1 düğmesine basarsanız, mikrodalga fırını 1 dakika ekler ve yemeğiniz sıcak olur. Yemeğinizi mikrodalga fırından
çıkarmadan önce pencerenizde bir kedi görürsünüz ve kediyi izlersiniz, çünkü kediler harikadır. An beklediğinizden daha uzun sürdü ve ilk 
ısırığınızı alırken yemeğiniz yine soğudu. Sorun değil, sadece onu tekrar mikrodalga fırına koyun ve +1'e basarak bir dakika çalıştırın.
Ancak bu sefer mikrodalga fırını sadece 1 saniye ekler ve 1 dakika eklenmez. İşte bu durumda "Hiçbir şey değiştirmedim ve şimdi bozuk" veya 
"Geçen sefer çalıştı" dersiniz. Aynı şeyi tekrar yaparsanız, geçen seferki davranışı beklersiniz. Fonksiyonlar için de aynı şey geçerlidir.


Ekstra olarak burada 2.bir işlem olarak çıkarma işlemi yapmaya çalışmış olsaydık 
s_isFirstCall static local değişkenimiz "False" olarak kaldığı için Enter another integer: diyerek 2 dönüt almış olacaktık. 
Yani fonksiyonumuz tekrar kullanılabilir bir fonksiyon değil çünkü static local değişkenimiz dışarıdan değiştirilebilen bir değişken değil 
Böyle durumlardan kaçınmak gerekiyor.
*/

// ***BEST Değişkenin hiçbir zaman sıfırlanması gerekmediği sürece statik yerel değişkenlerden kaçının. Yani kullancaksan sıfırlama ihtiyacın olmasın.

/*Quiz - Static keywordünün local ve global değişkenlere etkisi nedir ? 
Bir global değişkene uygulandığında, static anahtar sözcüğü global değişkeni dahili bağlantıya sahip olarak tanımlar; bu, değişkenin diğer 
dosyalara aktarılamayacağı anlamına gelir.

Yerel bir değişkene uygulandığında static anahtar sözcüğü, yerel değişkenin statik süreye sahip olduğunu tanımlar; bu, değişkenin yalnızca
bir kez oluşturulacağı ve programın sonuna kadar yok edilmeyeceği anlamına gelir.*/
/*
											-=--=--=--=--=--=--=--=--=-GENEL ÖZET-=--=--=--=--=--=--=--=--=--=--=--=-	
														 7.11 KAPSAM, DEVAMLILIK SÜRESİ ve BAĞLANTI
	Kapsam Özeti
	------------

Bir tanımlayıcının kapsamı, tanımlayıcının kaynak kodu içinde nereden erişilebileceğini belirler.

Blok (yerel) kapsama sahip değişkenlere yalnızca tanımlandıkları noktadan başlayarak bildiri yapıldığı bloğun sonuna kadar (iç içe geçmiş
blokları içeren) erişilebilir. Bu, şunları içerir:
	* Yerel değişkenler
	* Fonksiyon parametreleri
	* Bir blok içinde bildirilen enum ve sınıf gibi program-defined tür tanımlamaları. 
Global kapsama sahip değişkenlere ve fonksiyonlara, tanımlandıkları noktadan dosyanın sonuna kadar erişilebilir. Bu, şunları içerir:

	* Global değişkenler
	* Fonksiyonlar
	* Bir namespace içinde veya genel kapsamda bildirilen enum ve sınıf gibi program tarafından tanımlanan tür tanımlamaları

	Süre Özeti
	----------

Bir değişkenin süresi, ne zaman oluşturulduğunu ve ne zaman yok edildiğini belirler.

Otomatik süreli değişkenler, tanımlama noktasında oluşturulur ve içinde bulundukları blok çıkıldığında yok edilir. Bu, şunları içerir:
	* Yerel değişkenler
	* Fonksiyon parametreleri
Statik süreli değişkenler, program başladığında oluşturulur ve program sona erdiğinde yok edilir. Bu, şunları içerir:
	* Global değişkenler
	* Statik yerel değişkenler
Dinamik süreli değişkenler, programcı talebiyle oluşturulur ve yok edilir. Bu, şunları içerir:
	* Dinamik olarak ayrılan değişkenler
	
	Bağlantı konusu özet
	--------------------
	
Bir tanımlayıcının bağlantısı, bir tanımlayıcının birden çok bildiriminin aynı varlık (nesne, fonksiyon, referans, vb.) için mi 
yoksa farklı varlıklar için mi olduğunu belirler.
Bağlantısı olmayan bir tanımlayıcı, yalnızca kendisine atıfta bulunur. Bu, şunları içerir:
	* Yerel değişkenler
	* Blok içinde bildirilen program tanımlı tür tanımlamaları (örneğin enums ve sınıflar)

İç bağlantıya sahip bir tanımlayıcı, bildirildiği dosya içinde herhangi bir yerden erişilebilir. Bu, şunları içerir:
	* Statik global değişkenler (başlatılmış veya başlatılmamış)
	* Statik fonksiyonlar
	* Sabit global değişkenler
	* Adlandırılmamış bir ad alanı içinde bildirilen fonksiyonlar
	* Adlandırılmamış bir ad alanı içinde bildirilen program tanımlı tür tanımlamaları (örneğin, enums ve sınıflar)

Dış bağlantıya sahip bir tanımlayıcı, bildirildiği dosya içinde veya diğer dosyalarda (bir önyükleme bildirimi aracılığıyla) herhangi bir yerden
erişilebilir. Bu, şunları içerir:
	* Fonksiyonlar
	* Başlatılmış veya başlatılmamış değişkenler
	* Extern sabit global değişkenler
	* Inline sabit global değişkenler

Dış bağlantıya sahip tanımlayıcılar genellikle, tanımlamaların birden fazla .cpp dosyasına dahil edilmesi durumunda (bir tanım kuralını ihlal 
ettiği ( odr ) için), çoğaltılmış tanım bağlantı hatası oluşturabilirler. Bu kuralın bazı istisnaları vardır (türler, şablonlar ve inline fonksiyonlar
ve değişkenlerle ilgili konuları daha ayrıntılı bir şekilde ele aldığımızda bunları daha ileri derslerde inceleyeceğiz).

Ayrıca, fonksiyonlar varsayılan olarak dış bağlantıya sahiptir. Bunlar, static anahtar kelimesini kullanarak iç bağlantıya sahip hale getirilebilir.

Özet tablo 

Type										|		Example							|	Scope |	Duration  |	Linkage	|	Notes
-------------------------------------------------------------------------------------------------------------------------------------------------------
Local variable								|		int x;							|	Block |	Automatic |	None    |
Static local variable						|		static int s_x;					|	Block |	Static    |	None	|
Dynamic local variable						|		int* x { new int{} };			|	Block |	Dynamic	  | None	|
Function parameter							|		void foo(int x)					|	Block |	Automatic |	None	|
External non-constant global variable		|		int g_x;						|	Global|	Static    |	External|	Initialized or uninitialized
Internal non-constant global variable		|		static int g_x;					|	Global|	Static	  | Internal|	Initialized or uninitialized
Internal constant global variable			|		constexpr int g_x { 1 };		|	Global|	Static	  |	Internal|	Must be initialized
External constant global variable			|		extern const int g_x { 1 };		|	Global|	Static	  |	External|	Must be initialized
Inline constant global variable (C++17)		|		inline constexpr int g_x { 1 };	|	Global|	Static	  |	External|	Must be initialized
-------------------------------------------------------------------------------------------------------------------------------------------------------												
												
Başka bir dosyadaki bir fonksiyonu veya değişkeni erişmek için bir ileri bildirim kullanabilirsiniz. Bildirilen değişkenin kapsamı normalde olduğu
gibidir (global değişkenler için genel kapsam, yerel değişkenler için blok kapsamı).

Type									  |	Example						|	Notes
-------------------------------------------------------------------------------------------------------------------------------------------------------
Function forward declaration			  |	void foo(int x);			|	Prototype only, no function body
Non-constant variable forward declaration |	extern int g_x;				|	Must be uninitialized
Const variable forward declaration		  |	extern const int g_x;		|	Must be uninitialized
Constexpr variable forward declaration	  |	extern constexpr int g_x;	|	Not allowed, constexpr cannot be forward declared
-------------------------------------------------------------------------------------------------------------------------------------------------------

Depolama Sınıf Belirteci nedir ?
Bir tanımlayıcı bildiriminin parçası olarak kullanıldığında, static ve extern anahtar sözcüklerine depolama sınıfı belirticileri adı verilir. 
Bu bağlamda tanımlayıcının saklama süresini ve bağlantısını belirlerler.

C++ 4 aktif depolama sınıfı belirticisini destekler:
Tanımlayıcı			|			Anlamı																	  |			Not
-------------------------------------------------------------------------------------------------------------------------------------------------------
extern				|			static (or thread_local) storage duration and external linkage			  |
static				|			static (or thread_local) storage duration and internal linkage			  |
thread_local		|			thread storage duration													  |
mutable				|			object allowed to be modified even if containing class is const			  |
auto				|			automatic storage duration												  |	Deprecated in C++11
register			|			automatic storage duration and hint to the compiler to place in a register|	Deprecated in C++17
-------------------------------------------------------------------------------------------------------------------------------------------------------
Depolama sınıfı belirtici terimi genellikle yalnızca resmi belgelerde kullanılır.



												
												
												
												
												
												
												*/



















































































































