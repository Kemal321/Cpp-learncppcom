// ch4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// learncpp.com -> Chapter 4 my solutions and class notes.


/*

Integers range -> The calculation is according to bits are used to hold math -> -(2^n-1) to (2^n-1) - 1 
8 bits -> 7 for numbers and 1 for sign ( positive or negative )
2^8 -> 256 = [-128,127]


** Signed integer overflow will result in undefined behaviour.
* 
** In C++ integer division C++ drops the fractional portion. !!! NOT ROUNDED, DROPPED.
*/
#include <iostream>
#include <string>
#include <cstdint> // for std::uint8_t
#include <string_view>
/*
void print(int x) {
	std::cout << x;
}
*/
std::string getName()
{
	std::string s { "Alex" };
	return s;
}
double star(double x, double y) {
	return (x * y);
}
double extraction(double x, double y) {
	return (x - y);
}
double division(double x, double y) {
	return (x / y);
}
double addition(double x, double y) {
	return (x + y);
}

double freeFall(double h,double t) {
	constexpr double gravity{ 9.8 };
	constexpr double timeConstant{ 0.5 };

	if (h > gravity * t * t * timeConstant) {
		h = h - (gravity * t * t);
		std::cout << "At " << t << " seconds, the ball is at height: " << h << "meters"<<'\n';
		t = t + 1;
		freeFall(h, t);
	}
	else{
		std::cout << "At " << t << " seconds, the ball is on the ground.";
	}
	return 3.3;
}
int main()
{

	// Modulo writing if there is an overflow. Compiler will wrap around the range. 
	//For example 1 byte is 0-255 = 256 then if we store 280 -> 280/256 = 24 this value will be stored.
	/*
	MODULO WRAPPING EXAMPLE
	unsigned short x{65535};
	std::cout << "x was: " << x << '\n';

	x = 65536;
	std::cout << "x is now: " << x << '\n';

	x = 65537;
	std::cout << "x is now: " << x << '\n';

	*/
	// 4-6 Fixed-width integers and size_t


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// CHARS //

	// Multiliteral character e.g '43' bunlardan kaçın bunlar c++ standartlarında yok normalde o yüzden 
	// farklı sistemlerde farklı şekilde tanımlanmış olabilirler ve kodların sonuçlarında beklenmedik 
	// etkilere neden olabilirler.
	/*
	double y{ 5 };
	print(y);


	Burada yine de 5 yazacak çünkü optimizasyon için cpp inisiyatif alarak 5.0 ı 5 ile aynı lojik olarak aynı sayacak
	ama y nin bir double a dönüştürülerek ve bu değer ile YENİ BİR DEĞİŞKEN üretildiği ve fonksiyona bu şekilde 
	iletildiğini unutmamak gerekiyor.
	*/
	
	/*
 	 print(static_cast<int>(5.5));
	 Böylece uyarı mesajı olmadan devam etmiş olduk fakat şunu unutma
	 static cast yaparken 1 kullanılan türe veya değişkene her hangi bir zarar verilmiyor 
	 2- Burada static cast yaparken mesela unsigned bir türü signed a çevirirsen
	 örn: int s { static_cast<int>(u) }; -> Burada u bir unsigned olursa 
	 static cast onun rangesine yani menziline depo miktarına bakmaz 
	 O yüzden böyle bir işlem yaparken eğer taşma olursa beklenmedik sonuçlarla karşılaşabiliriz.
	*/
	/*
	std::int8_t myInt {65}; 
	std::cout << myInt << '\n';

	// Burada int8_t ve uint8_t char gibi davranıyor bu bazı yerlerde u şekilde çıkabiliyor.
	// int yazılmış yani burada bazı programlarda tanımlı olan int8_t ile char aynı mantıkta olduğu için bu şekilde çıktı veriyor.
	// static_cast<gerekliTür>() i kullanman gerekebilir.
	// Bu durum aynı zamanda input alırken de sorunlar yaratabilir dikkatli olmakta fayda var. 
	// Diğer fixed_width türler ise her zaman tam sayı değerli olarak yazılır ve giriş alırlar. 

	*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Compile time contants 
	int x{ 3 + 4 };
  	std::cout << x;
	// Mesela burada kodu bir kere çalıştırdıktan sonra 3 + 4 değişmeyeceği ve bilinen şeyler olduğu için sonucu 
	// da bilinen bir şeydir o anlamda bir sabit ifadedir. Bir kere derlendikten sonra. Tekrar tekrar hesaplanmasına gerek
	// olmadığı için bilgisayar birinci defadan sonra int x { 7 } diyerek devam eder Bu şekilde optimize edilir.

	// bunlar sabir ifadelerdir yani constant expression Bir de compile-time constant lar var bunlarda değeri bilinen sabitlerdir
	// yani literaller örneğin sayılar veya stringler değerleri bilinir. Bunlara compile-time constant denir. 
	// değişkenlerde de bu durum gözükebilir tabi bunun olması için başlatıccısının bir const olması gerekir 
	// yani değişkenin değişmeyeceğini bilmemiz gerekir const int x { 7 }; gibi

	/*
	const int x { 6 };
	const int y { 4 };

	const int z { x + y };

	Mesela burada x ve y bilinen ve sabit ifadeler olduğu için z de değişmeyecektir bu yüzden z de bir comp.-time const olur.
	bu compile-time constlar genellikle sembolik sabitler olarak kullanılır. 
		
	*/

	/*
	Burada derleme zamanı sabitlerinin derleyiciye çalışma zamanında değil de derleme sırasında optimize edilebilecek
	optimizasyonlar yapma yeteneği verir.
	Örneğin bir sabit yerine bir değişken kullanıldığında derleyici bu sabiti doğrudan değeriyle değiştirebilir böylece kod hızlı çalışır.

	örneğin const double gravity { 9.8 } derleyici burada gravity gördüğünde gidip adresten almak yerine 9.8 kabul ederek devam eder.
	*/



	/*
	Burada runtime const lar ise runtime a kadar değerleri bilinmeyen constlardır. Bu yüzden runtime expression olarak adlandırılılrar. 
	-----------------------------------------------------------------------------------------------------------------------------------
	Herhangi bir değişken, başlatımdan sonra değiştirilmemeli ve başlatıcı derleme zamanında biliniyorsa constexpr olarak
	bildirilmelidir.
	Herhangi bir değişken, başlatımdan sonra değiştirilmemeli ve başlatıcı derleme zamanında bilinmiyorsa const olarak bildirilmelidir.

	Not: Gelecekte, şu an constexpr ile uyumlu olmayan bazı türleri 
	(std::string, std::vector gibi dinamik bellek tahsisi kullanan türler dahil) tartışacağız.
	Bu türlerin sabit nesneleri için const kullanın.

	// Kodalarda büyülü ( magic ) sayılar yani ne olduğu bilinmez sayılar kullanmamak en iyisidir. Onun yerine constexpr kullanmak en iyisi 
	// mesela gravity diyip constexpr yanımlamak varken 9.8 ile çarparsan kardeşim bizde sorarız bu nerden geldi diye.

	// std::cin>> boşluklarda kesiyor ve sonraki cin e aktarıyordu. Bundan dolayı std::string ler için burada std::getline()
	// ı kullanacağız. Tabi input manipülatörü ile std::ws ile std::getline(std::cin >> std::ws , stringName ); Bu şekilde kullanımı var.

	/*
	Burada stringlerin uzunluğunu sorarken member fonksiyon diye bir fonksiyon tipi var onu kullanıyoruz
	std::string name{"Kemaleddin"};
	burada uzunluk bilgisi için name.length() yapıyoruz aynı python gibi.

	normalde function(object) idi bu sefer object.function() olmuş oldu sadece buna da member function diyoz 
	dokümanlarda std::string::length() olarak da geçer özel bir fonksiyondur.
	
	*/
	/*
	Burada stringlerin boyunu lenth() fonksiyonu ile alırken bize unsigned int döner sıkıntı çıkarmaması için static_cast<int>() ile
	dönüşüm sağlamamız lazım. Ayrıca C++20 de std::ssize() fonksiyonu da signed int olarak uzunluğu verir.	
	*/
	/*
	std::string_view -> bize sadece salt okunur yani read-only şekilde kullanılan bir string olarak gelir c++17 den geliyor string_view
	başlığı altında gelir bu aynı string gibi std::string_view objeAdı{} şeklinde tanımlanır fakat bunu modify edemeyiz 
	sadece kullanabiliriz. BU yüzden kopyalama işlemleri olmadığı için daha hızlı şekilde işlem yaparız 
	Bunu özellikle fonksiyonların parametrelerinde ve kullanabileceğimiz her yerde kullanmak bize performas olarak çok daha 
	işe yarar avantaj katar.
	
	
	*en iyi özelliği bir çok şekilde başlatılabilir string ile c-style string ile veya başka bir string_view ile başlatılabilir.
	* Fonksiyonlarda da yine aynı şekilde bu 3 türü de kabul edecek ve bilinçsiz dönüşüm yapar yani implicit casting yapacacaktır.
	* std::string_view objesi std::string e dönüşmeyecektir *** Bunun için 2 yol var
	1 std::String i std::string_view ile başlatarak oluştururuz 
	2 veya std::string_view i static_cast ile dönüştürürüz 




	std::string ve std::string_view türlerinin ikiside constexpr i tam olarak destekler burada string sembolik sabitler lazım olduğunda 
	kullanılabilir. 
	*/

/*Improper use of std::string_view*/
/*
	std::string_view sv{};
	{
		std::string s {"Hello world!"};
		sv = s;

	}
	
	std::cout << sv << '\n';

	*/
	/*

	std::string_view name { getName() }; // name initialized with return value of function
	std::cout << name << '\n'; // undefined behavior
	*/
/*
	std::string s { "Hello, world!" };
	std::string_view sv { s }; // sv is now viewing s

	s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
	std::cout << sv << '\n';   // undefined behavior

*/

//	Yani burada s i sonradan değiştirmemiz s'e bakan string_view ler invalid olmuş oluyor sonradan tekrar tanımlamadığımız sürece 
//	invalid bir şekilde devam edecekler.




/*
Fonksiyonları return ederken string view kullanımında 1 eğer bir string e bakan bir string view return edersek bu sıkıntılı bir durum
olur çünkü stringler fonksiyon tamamlandığında silinir böylece tanımlanmayan ve beklenmedik sonuçlar ortaya çıkabilir.
Bir std::string_view'in güvenli bir şekilde döndürülebileceği iki ana durum vardır. İlk olarak, C tarzı dize değişmezleri programın 
tamamı için mevcut olduğundan, std::string_view dönüş türüne sahip bir işlevden C tarzı dize değişmezlerini döndürmek uygundur.

2- İkincisi, std::string_view türünde bir fonksiyon parametresinin döndürülmesi genellikle uygundur:


eğer stringview geçici bir nesneye bakıyorsa geçici nesne yok olmadan kullanılmalı yoksa sıkıntılar çıkabilir. 




*/
	std::cout << "How old are you?\n";

	std::uint8_t age{};
	std::cin >> age;

	std::cout << "Allowed to drive a car in Texas [";

	if (age >= 16)
		std::cout << "x";
	else
		std::cout << " ";

	std::cout << "]\n";
	return 0;
}
