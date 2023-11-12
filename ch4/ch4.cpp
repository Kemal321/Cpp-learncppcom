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



	// Multiliteral character e.g '43' bunlardan kaçýn bunlar c++ standartlarýnda yok normalde o yüzden 
	// farklý sistemlerde farklý þekilde tanýmlanmýþ olabilirler ve kodlarýn sonuçlarýnda beklenmedik 
	// etkilere neden olabilirler.
	/*
	int y{ 4 };
	print(y);


	Burada yine de 5 yazacak çünkü optimizasyon için cpp inisiyatif alarak 5.0 ý 5 ile ayný lojik olarak ayný sayacak
	ama y nin bir double a dönüþtürülerek ve bu deðer ile YENÝ BÝR DEÐÝÞKEN üretildiði ve fonksiyona bu þekilde 
	iletildiðini unutmamak gerekiyor.

	Sonradan örnekleri deðiþtirirken deðiþen parçalarý yoruma çevirip yenisini yazýyorum unutma kafan karýþmasýn.

	print(5);
	*/


	/*print(static_cast<int>(5.5));


	// Böylece uyarý mesajý olmadan devam etmiþ olduk fakat þunu unutma
	// static cast yaparken 1 kullanýlan türe veya deðiþkene her hangi bir zarar verilmiyor 
	// 2- Burada static cast yaparken mesela unsigned bir türü signed a çevirirsen
	// örn: int s { static_cast<int>(u) }; -> Burada u bir unsigned olursa 
	// static cast onun rangesine yani menziline depo miktarýna bakmaz 
	// O yüzden böyle bir iþlem yaparken eðer taþma olursa beklenmedik sonuçlarla karþýlaþabiliriz.
	*/


	/*
	std::int8_t myInt {65}; 
	std::cout << myInt << '\n';

	// Burada int8_t ve uint8_t char gibi davranýyor bu bazý yerlerde u þekilde ama normalde gördüðün gibi 
	// int yazýlmýþ yani burada seni kandýrýyorlar buna dikkat etmen gerekiyor bunun gibi yerlerde 
	// static_cast<gerekliTür>() i kullanman gerekebilir.
	// Bu durum ayný zamanda input alýrken de sorunlar yaratabilir dikkatli olmakta fayda var. 
	// Diðer fixed_width türler ise her zaman tam sayý deðerli olarak yazýlýr ve giriþ alýrlar. 

	*/
	
	/*// QUIZ - QUESTINO 1
	char ch{};
	std::cout << "Enter a single character: ";
	
	std::cin >> ch;

	std::cout << "You entered " << "'" << ch << "', " << "which has ASCII code " << static_cast<int>(ch) << ".";
	*/

	/* QUESTÝON 2 - OK
	char ch{};
	std::cout << "Enter a single character: ";

	std::cin >> ch;

	std::cout << "You entered " << "'" << ch << "', " << "which has ASCII code ";
	print(ch);
	std::cout << ".\n";
	*/
	// bir çok yolu varmýþ biz birini yaptýk en zekice olaný bir sayý ile çarpmak 1 ile mesela yada 1 çýkartýp eklemek gibi
	// veya int fonksiyondan return almak felan filan.


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Compile time contants 
	//int x{ 3 + 4 };
//	std::cout << x;
	// Mesela burada kodu bir kere çalýþtýrdýktan sonra 3 + 4 deðiþmeyeceði ve bilinen þeyler olduðu için sonucu 
	// da bilinen bir þeydir o anlamda bir sabit ifadedir. Bir kere derlendikten sonra. Tekrar tekrar hesaplanmasýna gerek
	// olmadýðý için bilgisayar birinci defadan sonra int x { 7 } diyerek devam eder bir nevi. Bu optimizasyon saðlar aslýnda.

	// bunlar sabir ifadelerdir yani constant expression Bir de compile-time constant lar var bunlarda deðeri bilinen sabitlerdir
	// yani literaller örneðin sayýlar veya stringler deðerleri bilinir. BUnalra compile-time constant denir. 
	// deðiþkenlerde de bu durum gözükebilir tabi bunun olmasý için baþlatýccýsýnýn bir const olmasý gerekir 
	// yani deðiþkenin deðiþmeyeceðini bilmemiz gerekir const int x { 7 }; gibi

	/*
	const int x { 6 };
	const int y { 4 };

	const int z { x + y };

	Mesela burada x ve y bilinen ve sabit ifadeler olduðu için z de deðiþmeyecektir bu yüzden z de bir comp.-time const olur.
	bu compile-time constlar genellikle sembolik sabitler olarak kullanýlýr. 
		
	*/

	/*
	Burada derleme zamaný sabitlerinin derleyiciye çalýþma zamanýnda deðil de derleme sýrasýnda optimize edilebilecek
	optimizasyonlar yapma yeteneði verir.
	Örneðin bir sabit yerine bir deðiþken kullanýldýðýnda derleyici bu sabiti doðrudan deðeriyle deðiþtirebilir böylece kod hýzlý çalýþýr.

	örneðin const double gravity { 9.8 } derleyici burada gravity gördüðünde gidip adresten almak yerine 9.8 kabul ederek devam eder.
	*/



	/*
	Burada runtime const lar ise runtime a kadar deðerleri bilinmeyen constlardýr. Bunalrda iþte runtime expression olmuþ olur.
	---------------------------------------------------------------------------------------------------------------------------
	Herhangi bir deðiþken, baþlatýmdan sonra deðiþtirilmemeli ve baþlatýcý derleme zamanýnda biliniyorsa constexpr olarak
	bildirilmelidir.
	Herhangi bir deðiþken, baþlatýmdan sonra deðiþtirilmemeli ve baþlatýcý derleme zamanýnda bilinmiyorsa const olarak bildirilmelidir.

	Not: Gelecekte, þu an constexpr ile uyumlu olmayan bazý türleri 
	(std::string, std::vector gibi dinamik bellek tahsisi kullanan türler dahil) tartýþacaðýz.
	Bu türlerin sabit nesneleri için const kullanýn.
	

	// Hoca devamý var fakat biraz kafa karýþtýrýcý oluduðu için tekrar okursun sonraki zamnalarda. Performans açýsýndan buralarý 
	// bilmek iyi olur gibi. 




	// Kodalarda büyülü sayýlar yani ne olduðu bilinmez sayýlar kullanmamak en iyisidir. Onun yerine constexpr kullanmak en iyisi 
	// mesela gravity diyip constexpr yanýmlamak varken 9.8 ile çarparsan kardeþim bizde sorarýz bu nerden geldi be amk. diye. ehehhehe



	// std::cin>> boþluklarda kesiyor ve sonraki cin e aktarýyordu. Bundan dolayý std::string ler için burada std::getline()
	// ý kullanacaðýz. Tabi input manipülatörü ile std::ws ile std::getline(std::cin >> std::ws , stringName ); Bu þekilde kullanýmý var.

	/*
	Burada stringlerin uzunluðunu sorarken member fonksiyon diye bir fonksiyon tipi var onu kullanýyoruz
	std::string name{"Kemaleddin"};
	burada uzunluk bilgisi için name.length() yapýyoruz ayný python gibi.

	normalde function(object) idi bu sefer object.function() olmuþ oldu sadece buna da member function diyoz 
	dokümanlarda std::string::length() olarak da geçer özel bir fonksiyondur.
	
	*/
	/*
	Burada stringlerin boyunu lenth() fonksiyonu ile alýrken bize unsigned int döner sýkýntý çýkarmamasý için static_cast<int>() ile
	dönüþüm saðlamamýz lazým. Ayrýca C++20 de std::ssize() fonksiyonu da signed int olarak uzunluðu verir.	
	*/

	/*QUIZ - STD::STRINGS - basarili :D
	* 

	std::string name{};
	int age{};

	std::cout << " Enter your full name: ";
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter your age: ";
	std::cin >> age;

	int lengthOfName{ static_cast<int>(name.length()) };


	std::cout << "Your age + length of name is: " << age + lengthOfName ;
	

	*/


	/*
	std::string_view -> bize sadece salt okunur yani read-only þekilde kullanýlan bir string olarak gelir c++17 den geliyor string_view
	baþlýðý altýnda gelir bu ayný string gibi std::string_view objeAdý{} þeklinde tanýmlanýr fakat bunu modify edemeyiz 
	sadece kullanabiliriz. BU yüzden kopyalama iþlemleri olmadýðý için daha hýzlý þekilde iþlem yaparýz 
	Bunu özellikle fonksiyonlarýn parametrelerinde ve kullanabileceðimiz her yerde kullanak bize performas olarak çok daha 
	iþe yarar avantaj katar.
	
	
	*en iyi özelliði bir çok þekilde baþlatýlabilir string ile c-style string ile veya baþka bir string_view ile baþlatýlabilir.
	* Fonksiyonlarda da yine ayný þekilde bu 3 türü de kabul edecek ve bilinçsiz dönüþüm yapar yani implicit casting yapacacaktýr.
	* std::string_view objesi std::string e dönüþmeyecektir *** Bunun için 2 yol var
	1 std::String i std::string_view ile baþlatarak oluþtururuz 
	2 veya std::string_view i static_cast ile dönüþtürürüz 




	std::string ve std::string_view türlerinin ikiside constexpr i tam olarak destekler burada string sembolik sabitler lazým olduðunda 
	kullanýlabilir. 
	*/

/*Imporoper use of std::string_view*/
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

//	Yani burada s i sonradan deðiþtirmemiz s e bakan string_view ler invalid olmuþ oluyor sonradan tekrar tanýmlamadýðýmýz sürece 
	//	invalid bir þekilde devam edecekler.




/*
Fonksiyonlarý return ederken string view kullanýmýnda 1 eðer bir string e bakan bir string view return edersek bu sýkýntýlý bir durum
olur çünkü stringler fonksiyon tamamlandýðýnda silinir böylece tanýmlanmayan ve beklenmedik sonuçlar ortaya çýkabilir.
Bir std::string_view'in güvenli bir þekilde döndürülebileceði iki ana durum vardýr. Ýlk olarak, C tarzý dize deðiþmezleri programýn 
tamamý için mevcut olduðundan, std::string_view dönüþ türüne sahip bir iþlevden C tarzý dize deðiþmezlerini döndürmek uygundur.

2- Ýkincisi, std::string_view türünde bir fonksiyon parametresinin döndürülmesi genellikle uygundur:


eðer stringview geçici bir nesneye bakýyorsa geçici nesne yok olmadan kullanýlmalý yoksa sýkýntýlar çýkabilir. 




*/
/*
* Yaptýk gardeeeeeeeeeeeeeeþ

// CH4 REVÝEW QUÝZ 1

double x{};
double y{};
char c{};

std::cout << "Enter a double value: ";
std::cin >> x;

std::cout << "Enter a double value: ";
std::cin >> y;

std::cout << "Enter one of the following: +, -, *, or /: ";
std::cin >> c;

if (c == '*')
	std::cout << x <<" " << c << " " << y << " is: " << star(x, y);
else if(c == '/')
	std::cout << x << " " << c << " " << y << "is: " << division(x, y);
else if(c == '+')
	std::cout << x << " " << c <<" " << y << "is: " << addition(x, y);
else
	std::cout << x << " " << c << " " << y << "is: " << extraction(x, y);


*/

/*
* 
* Hoca garip yapmýþ yav neyse 
* buradan öðrenilen best practice her fonksiyon tek bir görevi üstlensin ******
// CH4 REVÝEW QUÝZ2
int height{};
int t{ 1 };
std::cout << "Enter the height of the tower in meters: ";
std::cin >> height;

freeFall(height, t);
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



