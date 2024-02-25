#include <iostream>
#include <string_view>
/*
Soru #1
Adý MonsterType olan bir numaralandýrma türü tanýmla, Þu ýrklar arasýnda seçim yapsýn: 
*- orc, goblin, troll, ogre, and skeleton.

*//*
// Soru #1 Cevap
enum MonsterType {
	orc,
	goblin,
	troll,
	ogre,
	skeleton,
};
*/
/*
Soru #2
MonsterType numaralandýrmasýný bir ad alanýna yerleþtirin. Ardýndan bir main() iþlevi oluþturun ve bir trol baþlatýn.
Program derlenmelidir.
*//*
//Soru #2 Cevap
namespace Monster {
	enum MonsterType {
		orc,
		goblin,
		troll,
		ogre,
		skeleton,
	};
}
*/
/*
Soru #3
Numaralandýrýcýlar verilen bir tamsayý deðeri olabilir ? - Doðru, Temelde belirlenen bir tam sayý deðeri yoksa int sayýlýr.
Verilen açýk bir deðer deðildir. - Doðru sadece implicit olarak dönüþtürülürler. Fakat enum class lar bu dönüþüme uðramazlar.
*/
/*
Soru #4
Þu hayvanlarý içeren Animal adýnda bir numaralandýrma sýnýfý tanýmlayýn: domuz, tavuk, keçi, kedi, köpek, ördek. 
Bir Animal parametresi alan ve bu hayvanýn adýný std::string_view (veya C++14 kullanýyorsanýz std::string) olarak 
döndürmek için bir switch ifadesi kullanan getAnimalName() adýnda bir iþlev yazýn. Her hayvanýn yürüdüðü bacak sayýsýný
yazdýrmak için switch ifadesini kullanan printNumberOfLegs() adýnda baþka bir iþlev yazýn. Her iki iþlevin de hata mesajý
yazdýran varsayýlan bir büyük/küçük harfe sahip olduðundan emin olun. Bir kedi ve tavukla birlikte main() öðesinden
printNumberOfLegs() öðesini çaðýrýn. Çýktýnýz þöyle görünmeli:

'''A cat has 4 legs.
   A chicken has 2 legs.'''
*//*
enum class Animal {
	pig,
	chicken,
	goat,
	cat,
	dog,
	duck,
};
std::string_view getAnimalName(Animal animal) {
	switch (animal)
	{
	case Animal::pig:
		return "pig";
	case Animal::chicken:
		return "chicken";
	case Animal::goat:
		return "goat";
	case Animal::cat:
		return "cat";
	case Animal::dog:
		return "dog";
	case Animal::duck:
		return "duck";
	default:
		std::cout << "This is not an animal :) Sorry." << '\n';
		return "No-Animal";
	}
}
void printNumberOfLegs(Animal animal) {
	switch (animal)
	{
	case Animal::pig:
		std::cout << "A pig has 4 legs." << '\n';
		break;
	case Animal::chicken:
		std::cout << "A chicken has 4 legs." << '\n';
		break;
	case Animal::goat:
		std::cout << "A goat has 4 legs." << '\n';
		break;
	case Animal::cat:
		std::cout << "A cat has 4 legs." << '\n';
		break;
	case Animal::dog:
		std::cout << "A dog has 4 legs." << '\n';
		break;
	case Animal::duck:
		std::cout << "A duck has 4 legs." << '\n';
		break;
	default:
		std::cout << "Sorry this is not an animal." << '\n';
		break;
	}
}*/
/*
Soru #5
Bir web sitesi iþletiyorsunuz ve reklam gelirinizi hesaplamaya çalýþýyorsunuz. 3 parça veri girmenizi saðlayan bir program yazýn:

Kaç reklam izlendi?
Kullanýcýlarýn yüzde kaçý bir reklama týkladý?
Týklanan reklam baþýna ortalama kazanç.
Bu 3 deðeri bir yapýda saklayýn. Bu yapýyý, deðerlerin her birini yazdýran baþka bir iþleve iletin. Yazdýrma iþlevi ayný 
zamanda o gün için ne kadar kazandýðýnýzý da yazdýrmalýdýr (3 alaný birlikte çarpýn).
*//*
struct Advertising {
	int howManyAdds{};
	int howManyClick{};
	double earningPerClick{};
};
void howMuchEarned(const Advertising& website) {
	std::cout << "Today " << website.howManyAdds << " adds watched." << '\n';
	std::cout << "Today " << website.howManyClick << " adds clicked." << '\n';
	std::cout << (website.earningPerClick * website.howManyAdds * website.howManyClick) << " $ Earned by adds"<<'\n';
}
// Hoca da vardý ben direktmen kullanýcý olarak düþünemedim. 
/*
Advertising getAdvertising()
{
	Advertising temp{};
	std::cout << "How many ads were shown today? ";
	std::cin >> temp.adsShown;
	std::cout << "What percentage of ads were clicked on by users? ";
	std::cin >> temp.clickThroughRatePercentage;
	std::cout << "What was the average earnings per click? ";
	std::cin >> temp.averageEarningsPerClick;

	return temp;
}
*/

/*
Soru #6
Bir kesri tutacak bir yapý oluþturun. Yapýnýn bir tamsayý pay ve bir tamsayý payda üyesi olmasý gerekir.

Kullanýcýdan bir Kesirde okunacak bir fonksiyon yazýn ve bunu iki kesir nesnesini okumak için kullanýn.
Ýki Kesri birbiriyle çarpmak ve sonucu Kesir olarak döndürmek için baþka bir fonksiyon yazýn (kesri azaltmanýza gerek
yoktur). Kesir yazdýran baþka bir fonksiyon yazýn.
*//*
struct Fraction {
	int numerator{};
	int denominator{ 1 };
};

Fraction getFraction() {
	Fraction temp{};
	std::cout << "Enter a value for the numerator: ";
	std::cin >> temp.numerator;
	std::cout << "Enter a value for the denominator: ";
	std::cin >> temp.denominator;
	return temp;
}
void printFraction(const Fraction& fraction1, const Fraction& fraction2) {
	std::cout << "Your fractions multiplied together: ";
	std::cout << (fraction1.numerator * fraction2.numerator) << '/' << (fraction1.denominator * fraction2.denominator);

}

/*
Soru #7
Önceki test sorusunun çözümünde getFraction() neden referans yerine deðere göre dönüyor?

*- Cevap: Temp Fraction'ýmýz yerel bir deðiþken olduðundan, fonksiyonun sonunda kapsam dýþýna çýkacaktýr.
Temp'i referans olarak döndürecek olsaydýk, arayan kiþiye sarkan bir referansý geri döndürürdük.
*/

/*
Soru #8 
Bir oyun tasarlarken canavarlara sahip olmak istediðimize karar veririz çünkü herkes canavarlarla savaþmayý sever. Öyle bir yapý bildirin ki
senin canavarýný temsil ediyor. Canavar aþaðýdakilerden biri olabilecek bir türe sahip olmalýdýr: bir dev, bir ejderha, bir ork,
dev bir örümcek veya bir balçýk. Bunun için bir enum sýnýfý kullanýn.

Her bir canavarýn ayrýca bir adý (std::string veya std::string_view kullanýn) ve bir miktar saðlýðý olmalýdýr.
bu ölmeden önce ne kadar hasar alabileceklerini temsil ediyor. Çýktýyý yazdýran printMonster() adýnda bir iþlev yazýn
yapýnýn tüm üyeleri. Bir dev ve bir balçýk örneði oluþturun, bunlarý bir baþlatýcý listesi kullanarak baþlatýn ve iletin
Monster()'ý yazdýrmak için.

Your program should produce the following output:

enum class Monsters {
	ogre,
	dragon,
	orc,
	giantSpider,
	slime,
};
struct Monster{
	
	Monsters myMonster{};
	std::string_view monstersName{};
	int health{};
};
std::string_view printMonsterType(Monsters mons) {
	switch (mons)
	{
	case Monsters::ogre:
		return "Ogre";
	case Monsters::dragon:
		return "Dragon";
	case Monsters::orc:
		return "Orc";
	case Monsters::giantSpider:
		return "Giant Spider";
	case Monsters::slime:
		return "Slime";
	default:
		return "Unknown Monster";
	}
}
void printMonster(const Monster& monster) {
	std::cout << "This " << printMonsterType(monster.myMonster);
	std::cout<< " is named " << monster.monstersName << " and has " << monster.health << " health." << '\n';
}*/

/*
Soru #9 - Klasik sorulardan biriydi o yüzden cevaplamayacaðým.

Verilen türlerin her birindeki nesnelerin deðere, sabit adrese veya sabit referansa göre iletilmesi gerekip
gerekmediðini belirtin. Bu türleri alan iþlevin bunlarý deðiþtirmediðini varsayabilirsiniz.
*/

/*
Soru #10

Ayný þablon türünden 3 üyeye sahip Triad adlý bir sýnýf þablonu oluþturun. Ayrýca Triad'ý yazdýrabilen print
adlý bir iþlev þablonu da oluþturun. Aþaðýdaki program derlenmelidir:

int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}


*/
// Triad(T,T,T) -> Triad<T,T,T>  -> This is only if you are using C++17, This property is added to C++ in C++20
template <typename T>
struct Triad{
	T t1{};
	T t2{};
	T t3{};
};

template <typename T>
void print(const Triad<T>& triad) {
	std::cout << '[' << triad.t1 << ',' << triad.t2 << ',' << triad.t3 << ']';
}
int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);
	/*
	Monster::MonsterType monster{ Monster::troll };
	std::cout << "Bu bir : " << monster << " dur." << '\n';
	*/

	/*
	// Soru 4
	Animal cat{ Animal::cat };
	Animal chicken{ Animal::chicken };
	printNumberOfLegs(cat);
	printNumberOfLegs(chicken);
	*/

	/*
	//Soru 5
	Advertising reklam{ 3,2,1 };
	howMuchEarned(reklam);
	*/
	
	/*
	//Soru 6
	Fraction usersFraction{ getFraction() };
	Fraction usersSecondFraction{ getFraction() };
	printFraction(usersFraction, usersSecondFraction);
	*/

	/*
	//Soru 8
	Monster myMonsterým{ {Monsters::ogre},"Torg",145 };
	Monster myMonsterým2{ {Monsters::slime},"Blurp",23 };

	printMonster(myMonsterým);
	printMonster(myMonsterým2);
	*/



	return 0;
}
