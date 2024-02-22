/*Quesiton 1

Determine what values the following program prints
by yourself (do not compile the program). -> Aşağıdaki program ne yazdırır kendi başınıza yapın derlemeden görün

#include <iostream>

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n';

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << ref << '\n';

    x = 4;

    std::cout << x << ref << '\n';

    return 0;
}
Cevabım:
11
22
44

Soru #1

1a) Can we determine whether a pointer is a null pointer or not? If so, how?
1a) Bir pointerin null olup olmadığına karar verebilir miyiz eğer verebiliyorsak nasıl karar veririz ?
Cevap: Evet bir pointerin null pointer olup olmadığına karar verebiliriz. Her nesne gibi pointerlerde boolean değerlere dönüşebilir 
bir null pointer boolean değerine dönüştüğünde false olarak dönüşür null olmayanlar ise true olarak dönüşür. Bir koşul ifadesi ile bunu 
kontrol edebiliriz.

1b) Can we determine whether a non-null pointer is valid or dangling? If so, how?
1b) Bir non-null pointerin geçerli bir değere işaret ettiğini veya etmediğine karar verebilir miyiz Eğer öyleyse nasıl ?
Cevap: Bir non-null pointerin sarkık olup olmadığına karar veremeyiz. 
---------------------------------------------------------------------------------------------------------------------------------------------------
Soru #2
Her alt öğe için, açıklanan eylemin tahmin edilebilir, tanımsız veya muhtemelen tanımsız bir davranışla sonuçlanıp sonuçlanmayacağını yanıtlayın.
Yanıt “muhtemelen tanımsız” ise ne zaman olduğunu açıklayın.

2a) Assigning a new address to a non-const pointer - Non-const pointer e yeni adres atama
*- tahmin edilebilir
2b) Assigning nullptr to a pointer  - Bir pointer e null pointer atama
*- Tahmin edilebilir
2c) Dereferencing a pointer to a valid object - Geçerli bir nesneye işaret eden bir pointer i dereferans etmek
*- Tahmin edilebilir 
2d) Dereferencing a dangling pointer - Sarkık pointeri dereferense etmek
*- Tanımsız Davraşına neden olur
2e) Dereferencing a null pointer - Null pointer i dereferense etmek
*- Tanımsız davranışa neden olur
2f) Dereferencing a non-null pointer
*- Muhtemelen tanımsız bir davranış, Çünkü eğer pointerin işaret ettiği nesne pointerden önce yok edilirse. Bu durumda pointer dangling olur. 
Ve dereferans işlemleri tanımsız davranışa neden olur.

Soru #3

Why should we set pointers that aren’t pointing to a valid object to ‘nullptr’?
Geçerli bir nesneye işaret etmeyen işaretçileri neden 'nullptr' olarak ayarlamalıyız?

Cevap: Böylece sarkık pointerlardan kurtulmuş oluruz. Bir non-null pointerin sarkık mı değil mi diye kontrol etmek zor bir durumdur. Ama bir 
nullptr null değere işaret ettiğinden dolayı tanımsız davranışa neden olmadan önce kontrolünü sağlayabiliriz. 


Soru #4

<< operatörünün sağ tarafındaki aşağıdaki ifadelerin her biri için, ifadenin bir lvalue veya rvalue olduğunu belirtin:

std::cout << 5;  - rvalue

int x { 5 };
std::cout << x;  - lvalue

int x { 5 };
std::cout << x + 1; - rvalue

int foo() { return 5; }
std::cout << foo(); - rvalue

int& max(int &x, int &y) { return x > y ? x : y; }
int x { 5 };
int y { 6 };
std::cout << max(x, y);  - Burada dönüş değeri lvalue referansı olduğu için cevap lvalue olur. 

Soru #5

What is the output of this program? - Bu programın çıktısı nedir ?

#include <iostream>

int main()
{
    int x{ 4 };
    int y{ 6 };

    int& ref{ x };
    ++ref;
    ref = y;
    ++ref;

    std::cout << x << ' ' << y;

    return 0;
}
Cevap: 7 6 Çünkü ref = y de oluşan durum referansı alınan nesnenin değerinin değiştirilmesidir. Referans olunan nesnenin değiştirilmesi değildir.

Soru #6

Name two reasons why we prefer to pass arguments by const reference instead of by non-const reference whenever possible.
Argümanları const referans ile geçmenin mümkün olduğu yerde const ref ile geçmek için 2 neden söyleyin. 

Cevap: Bağımsız değişkenin değerini değiştirmek için const olmayan bir referans parametresi kullanılabilir. Bu yeteneğe ihtiyacımız yoksa,
argümanı kazara değiştirmemek için const referansını geçmek daha iyidir.
Const olmayan bir referans parametresi yalnızca değiştirilebilir bir lvalue'yi argüman olarak kabul edebilir. Bir const referans parametresi,
değiştirilebilir bir lvalue'yu, değiştirilemeyen bir lvalue'yu veya bir rvalue'yi bağımsız değişken olarak kabul edebilir.


Soru #4
Const işaretçisi ile const işaretçisi arasındaki fark nedir?

Cevap: Const işaretçisi, adresi değiştirilemeyen bir işaretçidir (başka bir nesneye yeniden işaret edilemez). Ancak işaret edilen nesnenin değeri
değiştirilebilir.
Const işaretçisi, değeri işaretçi aracılığıyla değiştirilemeyen bir nesneyi işaret eden bir işaretçidir. Ancak işaretçi başka bir nesneye yeniden
yönlendirilebilir.


Soru #5

Arayanın 2 int değişkeni argüman olarak iletmesine olanak tanıyan sort2 adında bir işlev yazın. İşlev geri döndüğünde, ilk argüman iki değerden
küçük olanı, ikinci argüman ise iki değerden büyük olanı tutmalıdır.

Aşağıdaki kod, yorumlarda belirtilen değerleri çalıştırmalı ve yazdırmalıdır:

#include <iostream>

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}
Cevap hemen aşağıdadır:
*/
void sort2(int& num1, int& num2) {
    int temp{};
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
#include <iostream>

int main()
{
    int x{ 7 };
    int y{ 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7
    return 0;
}
