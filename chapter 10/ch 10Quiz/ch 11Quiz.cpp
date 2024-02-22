#include <iostream>
/*
1a) What is the output of this program and why? -> Bu programýn çýktýsý nedir ve neden bu çýktýyý vermekte

#include <iostream>

void print(int x)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    short s { 5 };
    print(s);

    return 0;
}
Cevap: Çýktý int 5 olacaktýr çünkü short un int türüne dönüþümü bir nümerik yükseltmedir oysa double türüne dönüþümü bir nümeric
dönüþümdür nümerik yükseltme nümeric dönüþümden önce gelir yani daha yüksek önceliðe sahiptir.

1b) Why won’t the following compile? -> Aþaðýdaki kod neden derlenmez

#include <iostream>

void print()
{
    std::cout << "void\n";
}

void print(int x=0)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5.0f);
    print();

    return 0;
}
Cevap: print() çaðrýsý hem print() ile hem de print(int) ile eþleþir çünkü varsayýlan deðer olarak x = 0 ibaresinin çaðrýmý da 
print() dir bu yüzden belirsiz eþleþme olur ve derlenemez.

1c) Why won’t the following compile? -> Aþaðýdaki kod neden derlenmez

#include <iostream>

void print(long x)
{
    std::cout << "long " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5);

    return 0;
}

Cevap: int 5 deðeri hem long a hem de double türüne dönüþebilir fakat bu dönüþüm nümerik dönüþüm olacaðýndan dolayý ikiside eþit 
derecede makuldür bu da bir belirsiz eþleþme meydana getirir.Derleyici hangi eþleþmenin daha iyi olduðuna karar veremez.
*/
template <typename T>
auto add(T x, T y) {
    return (x + y);
}

template <typename T>
T mult(T x, int y) {
    return (x * y);
}

template <typename T, typename U>
auto sub(T x, U y) {
    return (x - y);
}
int main()
{
    // Question 2
    /*
    Kullanýcýlarýn ayný türden 2 deðer eklemesine olanak tanýyan add() adýnda bir iþlev þablonu yazýn. Aþaðýdaki program 
    çalýþmalýdýr:*/
    std::cout << add(2, 3) << '\n';
    std::cout << add(1.2, 3.4) << '\n';
    
    
    /*Kullanýcýnýn herhangi türden bir deðeri (ilk parametre) ve bir tamsayýyý (ikinci parametre) çarpmasýna olanak tanýyan 
    mult() adýnda bir iþlev þablonu yazýn. Ýþlev, ilk parametreyle ayný türü döndürmelidir. Aþaðýdaki program çalýþmalýdýr:*/
    std::cout << mult(2, 3) << '\n';
    std::cout << mult(1.2, 3) << '\n';


    /*Kullanýcýnýn farklý türden iki deðeri çýkarmasýna olanak tanýyan sub() adýnda bir iþlev þablonu yazýn. Aþaðýdaki program 
    çalýþmalýdýr:*/
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';

    /*
    What is the output of this program and why? - Bu programýn çýktýsý nedir ve neden?

    #include <iostream>

    template <typename T>
    int count(T) // This is the same as int count(T x), except we're not giving the parameter a name since we don't use the
                    parameter
    {
        static int c { 0 };
        return ++c;
    }

    int main()
    {
        std::cout << count(1) << '\n';
        std::cout << count(1) << '\n';
        std::cout << count(2.3) << '\n';
        std::cout << count<double>(1) << '\n';

        return 0;
    }
    Cevabým: 
    0
    1
    2
    3
    Çünkü static int c{0} static local deðiþkeni static keywordünden dolayý global kapsam a sahip olmuþtur static local
    deðiþkenlerin özelliði bir kere baþlatýldýktan sonra global deðiþken gibi davranmasýdýr. Bu durumda 0 ile baþlatýldýktan sonra
    fonksiyon 4 kez çaðrýlmýþtýr bu her defasýnda güncel deðerin yazdýrýlmasý ile sonuçlanacak bir iþlem yýðýnýný oluþturur ve 
    bu çýktýyý verir. Ve cevabým yanlýþ çýktý nedeni count(1) çaðrýldýðýnda, derleyici count<int>(int) iþlevini baþlatacak ve 
    onu çaðýracaktýr. Bu, 1 deðerini döndürecektir.

    count(1) tekrar çaðrýldýðýnda, derleyici count<int>(int)'in zaten mevcut olduðunu görecek ve onu tekrar arayacaktýr. 
    Bu, 2 deðerini döndürecektir.

    count(2.3) çaðrýldýðýnda, derleyici iþlevi count<double>(double) prototipiyle baþlatacak ve çaðýracaktýr. 
    Bu, kendi statik c deðiþkenine sahip yeni bir fonksiyondur, dolayýsýyla 1 deðerini döndürecektir.

    count<double>(1) çaðrýldýðýnda, derleyici bizim açýkça count()'un double versiyonunu istediðimizi görecektir. 
    Bu iþlev önceki ifade nedeniyle zaten mevcuttur, dolayýsýyla count<double>(double) çaðrýlacak
    ve int argümaný örtülü olarak double'a dönüþtürülecektir. Bu fonksiyon 2 deðerini döndürecektir.*/

    /*Question 4
    What is the output of this program? - Bu programýn çýktýsý nedir

    #include <iostream>

    int foo(int n)
    {
        return n + 10;
    }

    template <typename T>
    int foo(T n)
    {
        return n;
    }

    int main()
    {
        std::cout << foo(1) << '\n'; // #1

        short s { 2 };
        std::cout << foo(s) << '\n'; // #2

        std::cout << foo<int>(4) << '\n'; // #3

        std::cout << foo<int>(s) << '\n'; // #4

        std::cout << foo<>(6) << '\n'; // #5

        return 0;
    },
    cevabým
    11
    12
    4
    2
    6
    12 çýktýsý yanlýþmýþ nedeni 
    2. durumda, foo(s), þablon olmayan foo(int) iþleviyle tam olarak eþleþmez, ancak s argümaný bir int'ye dönüþtürülebilir,
    böylece foo(int) bir aday olur. Ancak derleyici foo<T>(T) iþlev þablonunu foo<short>(short) ile tam eþleþmeyi kalýplamak
    için kullanmayý tercih edecektir. Yani buna foo<short>(short) denir.*/
    return 0;


}
