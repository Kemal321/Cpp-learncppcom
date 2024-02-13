#include <iostream>

int main()
{
    return 0;
}
/*
18.1 — Bir diziyi seçim sýralamasý kullanarak sýralama ( Selection Sort )
-------------------------------------------------------------------------
Sýralama için bir durum
-----------------------
Bir diziyi sýralama, dizideki tüm öðeleri belirli bir sýraya göre düzenleme sürecidir. Bir diziyi sýralamanýn faydalý olabileceði birçok farklý
durum vardýr. Örneðin, e-posta programýnýz genellikle e-postalarý alýndýðý zamana göre gösterir, çünkü en son e-postalar genellikle daha alakalý
kabul edilir. Kiþi listesine gittiðinizde, isimler genellikle alfabetik sýradadýr, çünkü aradýðýnýz ismi bu þekilde bulmak daha kolaydýr.
Her iki sunum da verileri sunmadan önce sýralama iþlemi gerektirir.

Bir diziyi sýralamak, bir diziyi aramayý sadece insanlar için deðil, bilgisayarlar için de daha verimli hale getirebilir. Örneðin, bir ismin bir
isim listesinde olup olmadýðýný bilmek istediðimiz bir durumu düþünün. Bir ismin listede olup olmadýðýný görmek için, dizideki her öðeyi kontrol 
etmemiz ve ismin orada olup olmadýðýný görmemiz gerekir. Birçok öðesi olan bir dizi için, hepsini aramak pahalý olabilir.

Ancak, þimdi isimlerin alfabetik olarak sýralandýðý bir dizimiz olduðunu varsayalým. Bu durumda, alfabetik olarak aradýðýmýzdan daha büyük bir
isimle karþýlaþtýðýmýz noktaya kadar sadece arama yapmamýz gerekiyor. O noktada, ismi bulamadýysak, geri kalan dizide olmadýðýný biliyoruz,
çünkü dizide bakmadýðýmýz tüm isimlerin alfabetik olarak daha büyük olduðu garanti edilir!

Sýralanmýþ dizileri aramak için daha iyi algoritmalar olduðu ortaya çýktý. Basit bir algoritma kullanarak, 1.000.000 öðe içeren bir diziyi sadece
20 karþýlaþtýrma kullanarak arayabiliriz! Dezavantajý tabii ki, bir diziyi sýralamanýn nispeten pahalý olmasýdýr ve genellikle bir diziyi aramayý 
hýzlandýrmak için bir diziyi sýralamaya deðmez, aksi takdirde birçok kez arayacaksýnýz.

Bazý durumlarda, bir diziyi sýralamak aramayý gereksiz kýlar. En iyi test skorunu bulmak istediðimiz baþka bir örneði düþünün. Dizi sýralanmamýþsa,
en yüksek test skorunu bulmak için dizideki her öðeye bakmamýz gerekir. Liste sýralanmýþsa, en iyi test skoru ilk veya son pozisyonda olacaktýr
(artan veya azalan sýraya göre sýraladýðýmýza baðlý olarak), bu yüzden hiç arama yapmamýza gerek yok!

Sýralamanýn nasýl çalýþtýðý
---------------------------
Sýralama genellikle, dizi öðelerinin çiftlerini tekrar tekrar karþýlaþtýrarak ve belirli bir kriteri karþýladýklarýnda onlarý deðiþtirerek 
gerçekleþtirilir. Bu öðelerin hangi sýrayla karþýlaþtýrýldýðý, hangi sýralama algoritmasýnýn kullanýldýðýna baðlýdýr. Kriter, listenin nasýl
sýralanacaðýna (ör. artan veya azalan sýra) baðlýdýr.

Ýki öðeyi deðiþtirmek için, C++ standart kütüphanesinden std::swap() fonksiyonunu kullanabiliriz, bu fonksiyon utility baþlýðýnda tanýmlanmýþtýr.

                #include <iostream>
                #include <utility>

                int main()
                {
                    int x{ 2 };
                    int y{ 4 };
                    std::cout << "Takas öncesi: x = " << x << ", y = " << y << '\n';
                    std::swap(x, y); // x ve y deðerlerini takas et
                    std::cout << "Takas sonrasý:  x = " << x << ", y = " << y << '\n';

                    return 0;
                }

                Bu program þunu yazdýrýr:

                Takas öncesi: x = 2, y = 4
                Takas sonrasý:  x = 4, y = 2
Takas sonrasý, x ve y'nin deðerlerinin deðiþtirildiðini unutmayýn!

Seçim sýralamasý ( Selection Sort )
-----------------------------------
Bir diziyi sýralamanýn birçok yolu vardýr. Seçim sýralamasý muhtemelen anlamasý en kolay sýralamadýr, bu da onu daha yavaþ sýralamalardan biri 
olmasýna raðmen öðretmek için iyi bir aday yapar.

Seçim sýralamasý, bir diziyi en küçükten en büyüðe sýralamak için aþaðýdaki adýmlarý gerçekleþtirir:

*- Dizi indeksi 0'dan baþlayarak, tüm diziyi en küçük deðeri bulmak için ara
*- Dizide bulunan en küçük deðeri, indeks 0'daki deðerle deðiþtir
*- Sonraki indeksten baþlayarak adýmlarý 1 ve 2'yi tekrarla

Baþka bir deyiþle, dizideki en küçük öðeyi bulacaðýz ve onu ilk konuma taþýyacaðýz. Sonra bir sonraki en küçük öðeyi bulacaðýz ve onu ikinci konuma
taþýyacaðýz. Bu süreç, öðelerimiz tükenene kadar tekrarlanacak.

Ýþte bu algoritmanýn 5 öðe üzerinde çalýþmasýnýn bir örneði. Bir örnek diziyle baþlayalým:

                { 30, 50, 20, 10, 40 }

Öncelikle, en küçük öðeyi buluyoruz, indeks 0'dan baþlayarak:

                { 30, 50, 20, 10, 40 }

Sonra bunu indeks 0'daki öðeyle deðiþtiriyoruz:

                { 10, 50, 20, 30, 40 }

Artýk ilk öðe sýralandýðýna göre, onu görmezden gelebiliriz. Þimdi, en küçük öðeyi buluyoruz, indeks 1'den baþlayarak:

                { 10, 50, 20, 30, 40 }

Ve bunu indeks 1'deki öðeyle deðiþtiriyoruz:

                { 10, 20, 50, 30, 40 }

Artýk ilk iki öðeyi görmezden gelebiliriz. Ýndeks 2'den baþlayarak en küçük öðeyi bulun:

                { 10, 20, 50, 30, 40 }

Ve bunu indeks 2'deki öðeyle deðiþtirin:

                { 10, 20, 30, 50, 40 }

Ýndeks 3'ten baþlayarak en küçük öðeyi bulun:

                { 10, 20, 30, 50, 40 }

Ve bunu indeks 3'teki öðeyle deðiþtirin:

                { 10, 20, 30, 40, 50 }

Son olarak, indeks 4'ten baþlayarak en küçük öðeyi bulun:

                { 10, 20, 30, 40, 50 }

Ve bunu indeks 4'teki öðeyle deðiþtirin (ki bu hiçbir þey yapmaz):

                { 10, 20, 30, 40, 50 }

Bitti!
                { 10, 20, 30, 40, 50 }

Son karþýlaþtýrmanýn her zaman kendisiyle olacaðýný unutmayýn (ki bu gereksizdir), bu yüzden aslýnda dizinin sonundan 1 öðe önce durabiliriz.

C++'da Seçim Sýralamasý
-----------------------
Ýþte bu algoritmanýn C++'da nasýl uygulandýðý:

                #include <iostream>
                #include <iterator>
                #include <utility>

                int main()
                {
	                int array[]{ 30, 50, 20, 10, 40 };
	                constexpr int length{ static_cast<int>(std::size(array)) };

	                // Dizinin her bir öðesinden geçin
	                // (sonuncusu hariç, çünkü oraya geldiðimizde zaten sýralanmýþ olacak)
	                for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	                {
		                // smallestIndex, bu iterasyonda karþýlaþtýðýmýz en küçük öðenin indeksidir
		                // Ýlk olarak, en küçük öðenin bu iterasyonun ilk öðesi olduðunu varsayýn
		                int smallestIndex{ startIndex };

		                // Sonra geri kalan dizide daha küçük bir öðe arayýn
		                for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
		                {
			                // Eðer daha önce bulduðumuz en küçükten daha küçük bir öðe bulmuþsak
			                if (array[currentIndex] < array[smallestIndex])
				                // o zaman onu takip edin
				                smallestIndex = currentIndex;
		                }

		                // smallestIndex þimdi kalan dizideki en küçük öðenin indeksidir
				                // baþlangýç öðemizi en küçük öðemizle deðiþtirin (bu onu doðru yere sýralar)
		                std::swap(array[startIndex], array[smallestIndex]);
	                }

	                // Artýk tüm dizi sýralandýðýna göre, iþe yaradýðýnýn kanýtý olarak sýralanmýþ dizimizi yazdýrýn
	                for (int index{ 0 }; index < length; ++index)
		                std::cout << array[index] << ' ';

	                std::cout << '\n';

	                return 0;
                }

Bu algoritmanýn en kafa karýþtýrýcý kýsmý, bir döngünün içinde baþka bir döngü (iç içe döngü denir). Dýþ döngü (startIndex) her bir öðeyi tek tek
yinelemektedir. Dýþ döngünün her iterasyonu için, iç döngü (currentIndex) kalan dizideki en küçük öðeyi bulmak için kullanýlýr (startIndex+1'den
baþlayarak). smallestIndex, iç döngü tarafýndan bulunan en küçük öðenin indeksini takip eder. Sonra smallestIndex, startIndex ile deðiþtirilir. 
Son olarak, dýþ döngü (startIndex) bir öðe ilerler ve süreç tekrarlanýr.

Ýpucu: Eðer yukarýdaki programýn nasýl çalýþtýðýný anlamakta zorlanýyorsanýz, bir örnek durumu kaðýda çizerek çalýþmak yardýmcý olabilir.
Baþlangýçtaki (sýralanmamýþ) dizi elemanlarýný kaðýdýn üst kýsmýna yatay olarak yazýn. Hangi elemanlarýn startIndex, currentIndex ve smallestIndex
tarafýndan indekslendiðini gösteren oklar çizin. Programý manuel olarak izleyin ve indeksler deðiþtikçe oklarý yeniden çizin. Dýþ döngünün her 
iterasyonu için, dizinin mevcut durumunu gösteren yeni bir satýr baþlatýn.

Ýsimleri sýralamak ayný algoritmayý kullanýr. Sadece dizi türünü int'ten std::string'e deðiþtirin ve uygun deðerlerle baþlatýn.

std::sort
---------
Dizileri sýralamak çok yaygýn olduðu için, C++ standart kütüphanesi std::sort adýnda bir sýralama fonksiyonu içerir. std::sort, <algorithm>
baþlýðýnda bulunur ve bir dizi üzerinde þu þekilde çaðrýlabilir:

                #include <algorithm> // for std::sort
                #include <iostream>
                #include <iterator> // for std::size

                int main()
                {
                    int array[]{ 30, 50, 20, 10, 40 };

                    std::sort(std::begin(array), std::end(array));

                    for (int i{ 0 }; i < static_cast<int>(std::size(array)); ++i)
                        std::cout << array[i] << ' ';

                    std::cout << '\n';

                    return 0;
                }

Varsayýlan olarak, std::sort, eleman çiftlerini karþýlaþtýrmak için operator< kullanarak ve gerekirse onlarý deðiþtirerek (yukarýdaki seçim
sýralama örneðimiz gibi) artan sýra ile sýralar.

18.2 — Ýteratörlere Giriþ
-------------------------
Bir dizi (veya baþka bir yapý) veriyi yinelemek programlamada oldukça yaygýn bir þeydir. Ve þimdiye kadar, bunu yapmanýn birçok farklý yolunu
ele aldýk: döngüler ve bir indeks (for-döngüleri ve while döngüleri), iþaretçiler ve iþaretçi aritmetiði ve aralýk tabanlý for-döngüleri ile:

                #include <array>
                #include <cstddef>
                #include <iostream>

                int main()
                {
                    // In C++17, the type of variable data is deduced to std::array<int, 7>
                    // If you get an error compiling this example, see the warning below
                    std::array data{ 0, 1, 2, 3, 4, 5, 6 };
                    std::size_t length{ std::size(data) };

                    // while-loop with explicit index
                    std::size_t index{ 0 };
                    while (index < length)
                    {
                        std::cout << data[index] << ' ';
                        ++index;
                    }
                    std::cout << '\n';

                    // for-loop with explicit index
                    for (index = 0; index < length; ++index)
                    {
                        std::cout << data[index] << ' ';
                    }
                    std::cout << '\n';

                    // for-loop with pointer (Note: ptr can't be const, because we increment it)
                    for (auto ptr{ &data[0] }; ptr != (&data[0] + length); ++ptr)
                    {
                        std::cout << *ptr << ' ';
                    }
                    std::cout << '\n';

                    // range-based for loop
                    for (int i : data)
                    {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';

                    return 0;
                }

Uyarý

Bu dersin örnekleri, bir þablon deðiþkeninin baþlatýcýsýndan þablon argümanlarýný çýkarmak için C++17 özelliði olan sýnýf þablonu argüman
çýkarýmýný kullanýr. Yukarýdaki örnekte, derleyici std::array data{ 0, 1, 2, 3, 4, 5, 6 }; görünce, std::array<int, 7> data { 0, 1, 2, 3, 4, 5, 6 };
istediðimizi çýkarýr.

Eðer derleyiciniz C++17'yi desteklemiyorsa, “data’dan önce eksik þablon argümanlarý” gibi bir hata alýrsýnýz. Bu durumda, en iyi seçeneðiniz,
ders 0.12 -- Derleyicinizi Yapýlandýrma: Bir dil standardý seçme bölümüne göre C++17'yi etkinleþtirmektir. Eðer yapamazsanýz, sýnýf þablonu argüman
çýkarýmýný kullanan satýrlarý, açýk þablon argümanlarý olan satýrlarla deðiþtirebilirsiniz (örneðin, std::array data{ 0, 1, 2, 3, 4, 5, 6 }; yerine
std::array<int, 7> data { 0, 1, 2, 3, 4, 5, 6 }; kullanýn).

Ýndeksleri kullanarak döngü yapmak, yalnýzca indisi elemanlara eriþim için kullanýyorsak gereðinden fazla yazým gerektirir. Ayrýca bu, yalnýzca
konteynýrýn (ör. dizi) elemanlara doðrudan eriþim saðlamasý durumunda çalýþýr (diziler bunu yapar, ancak listeler gibi diðer bazý konteynýr türleri
yapmaz).

Ýþaretçilerle ve iþaretçi aritmetiði ile döngü yapmak, ayrýntýlýdýr ve iþaretçi aritmetiðinin kurallarýný bilmeyen okuyucular için kafa karýþtýrýcý
olabilir. Ýþaretçi aritmetiði de yalnýzca elemanlar hafýzada ardýþýk olduðunda çalýþýr (bu diziler için doðru, ancak listeler, tree'ler ve map'lar
gibi diðer konteynýr türleri için doðru deðil).

Aralýk tabanlý for-döngüleri biraz daha ilginçtir, çünkü konteynýrýmýzdan geçme mekanizmasý gizlidir - ve yine de, tüm çeþitli yapýlar için çalýþýr
(diziler, listeler, tree'ler, map'lar, vb...). Bunlar nasýl çalýþýr? Ýteratörler kullanýrlar.

Ýteratörler
-----------
Bir iteratör, bir konteynýrýn (ör. bir dizideki deðerler veya bir stringdeki karakterler) üzerinden geçmek için tasarlanmýþ bir nesnedir ve 
bu yolculuk boyunca her bir elemana eriþim saðlar.

Bir konteynýr, farklý türlerde iteratörler saðlayabilir. Örneðin, bir dizi konteynýrý, dizinin ileri sýrasýnda yürüyen bir ileri iteratör ve
dizinin ters sýrasýnda yürüyen bir ters iteratör sunabilir.

Uygun türde bir iteratör oluþturulduðunda, programcý daha sonra iteratörün saðladýðý arayüzü kullanabilir ve hangi türden bir gezinme yapýldýðý 
veya verilerin konteynýrda nasýl saklandýðý konusunda endiþelenmeden elemanlarý gezinebilir ve eriþebilir. Ve çünkü C++ iteratörleri genellikle
gezinme (operator++ ile bir sonraki elemana geçme) ve eriþim (operator* ile mevcut elemana eriþme) için ayný arayüzü kullanýr, tutarlý bir yöntemle
çeþitli farklý konteynýr türlerinden geçebiliriz.

Ýþaretçiler bir iteratör olarak
-------------------------------
En basit türde iteratör bir iþaretçidir, bu (iþaretçi aritmetiði kullanarak) hafýzada ardýþýk olarak saklanan veriler için çalýþýr. Ýþte bir 
iþaretçi ve iþaretçi aritmetiði kullanarak basit bir dizi gezinmesine dönelim:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array data{ 0, 1, 2, 3, 4, 5, 6 };

                    auto begin{ &data[0] };
                    // not edin ki bu, son elemandan bir adým ötesini gösterir
                    auto end{ begin + std::size(data) };

                    // iþaretçi ile for-döngüsü
                    for (auto ptr{ begin }; ptr != end; ++ptr) // ++ bir sonraki elemana geçmek için
                    {
                        std::cout << *ptr << ' '; // Ýndireksiyon ile mevcut elemanýn deðerini alýr
                    }
                    std::cout << '\n';

                    return 0;
                }

                Çýktý:

                0 1 2 3 4 5 6
Yukarýda, iki deðiþken tanýmladýk: begin (konteynýrýmýzýn baþlangýcýný gösterir) ve end (bir bitiþ noktasýný iþaretler). Diziler için,
bitiþ iþaretçisi genellikle konteynýrýn bir eleman daha içerdiði durumda son elemanýn olacaðý yerdir.

Ýþaretçi daha sonra baþlangýç ve bitiþ arasýnda döngü yapar ve mevcut eleman, iþaretçinin dereferansý ile eriþilebilir.

Uyarý

Bitiþ iþaretçisini adres operatörü ve dizi sözdizimi kullanarak hesaplamaya meyilli olabilirsiniz:

                int* end{ &data[std::size(data)] };

Ancak bu, tanýmsýz bir davranýþa neden olur, çünkü data[std::size(data)] açýkça dizinin sonundaki bir elemaný dereferans eder.

Bunun yerine, kullanýn:

                int* end{ data.data() + std::size(data) }; // data() ilk elemana bir iþaretçi döndürür

Standart kütüphane yineleyicileri
---------------------------------
Yineleme o kadar yaygýn bir iþlem ki, tüm standart kütüphane konteynerleri yinelemeyi doðrudan destekler. Kendi baþlangýç ve bitiþ noktalarýmýzý
hesaplamak yerine, konteynere baþlangýç ve bitiþ noktalarýný, uygun þekilde begin() ve end() adlý üye fonksiyonlar aracýlýðýyla sorabiliriz:

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Dizimizden baþlangýç ve bitiþ noktalarýný isteyin (begin ve end üye fonksiyonlarý aracýlýðýyla).
                    auto begin{ array.begin() };
                    auto end{ array.end() };

                    for (auto p{ begin }; p != end; ++p) // Sonraki elemana geçmek için ++.
                    {
                        std::cout << *p << ' '; // Mevcut elemanýn deðerini almak için indireksiyon.
                    }
                    std::cout << '\n';

                    return 0;
                }

                Bu, þunu yazdýrýr:

                1 2 3
Yineleyici baþlýðý ayrýca kullanýlabilen iki genel fonksiyon (std::begin ve std::end) içerir.

Ýpucu -> C tarzý diziler için std::begin ve std::end, <iterator> baþlýðýnda tanýmlanmýþtýr.

Yineleyicileri destekleyen konteynerler için std::begin ve std::end, bu konteynerlerin baþlýk dosyalarýnda tanýmlanmýþtýr (ör. <array>, <vector>).

                #include <array>    // <iterator> dahil eder
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Baþlangýç ve bitiþ noktalarýný almak için std::begin ve std::end kullanýn.
                    auto begin{ std::begin(array) };
                    auto end{ std::end(array) };

                    for (auto p{ begin }; p != end; ++p) // Sonraki elemana geçmek için ++
                    {
                        std::cout << *p << ' '; // Mevcut elemanýn deðerini almak için indireksiyon
                    }
                    std::cout << '\n';

                    return 0;
                }

                Bu da þunu yazdýrýr:

                1 2 3
Þimdilik yineleyicilerin türleri hakkýnda endiþelenmeyin, daha sonraki bir bölümde yineleyicilere geri döneceðiz. Önemli olan þey, yineleyicinin
konteynerden geçme ayrýntýlarýný halletmesidir. Dört þeye ihtiyacýmýz var: baþlangýç noktasý, bitiþ noktasý, sonraki elemana (veya sona) 
geçmek için operator++, ve mevcut elemanýn deðerini almak için operator*.

Yineleyiciler için operator< vs operator!=
------------------------------------------
8.10 -- For ifadeleri dersinde, döngü koþulunda sayýsal karþýlaþtýrmalar yaparken operator< kullanmanýn operator!='den tercih edildiðini 
belirtmiþtik:

                for (index = 0; index < length; ++index)

Yineleyicilerle, yineleyicinin son elemana ulaþýp ulaþmadýðýný test etmek için genellikle operator!= kullanýlýr:

                for (auto p{ begin }; p != end; ++p)

Bu, bazý yineleyici türlerinin iliþkisel olarak karþýlaþtýrýlamaz olmasýndandýr. operator!=, tüm yineleyici türleriyle çalýþýr.

Aralýk tabanlý for döngülerine geri dönüþ
-----------------------------------------
Hem begin() hem de end() üye fonksiyonlarýna sahip olan tüm türler, veya std::begin() ve std::end() ile kullanýlabilen türler, ,
aralýk tabanlý for-döngülerinde kullanýlabilir.

                #include <array>
                #include <iostream>

                int main()
                {
                    std::array array{ 1, 2, 3 };

                    // Bu, daha önce kullandýðýmýz döngüyle tam olarak ayný þeyi yapar.
                    for (int i : array)
                    {
                        std::cout << i << ' ';
                    }
                    std::cout << '\n';

                    return 0;
                }

Perde arkasýnda, aralýk tabanlý for-döngüsü, üzerinde yineleme yapýlacak türün begin() ve end() fonksiyonlarýný çaðýrýr. std::array'ýn begin ve
end üye fonksiyonlarý vardýr, bu yüzden onu bir aralýk tabanlý döngüde kullanabiliriz. C tarzý sabit diziler, std::begin ve std::end
fonksiyonlarýyla kullanýlabilir, bu yüzden onlarý da bir aralýk tabanlý döngü ile döngüye alabiliriz. Ancak, dinamik C tarzý diziler
(veya bozunmuþ C tarzý diziler) çalýþmaz, çünkü onlar için bir std::end fonksiyonu yoktur (çünkü tür bilgisi dizinin uzunluðunu içermez).

Bu fonksiyonlarý kendi türlerinize nasýl ekleyeceðinizi daha sonra öðreneceksiniz, böylece onlar da aralýk tabanlý for-döngülerinde kullanýlabilir.
Aralýk tabanlý for-döngüleri, yineleyicileri kullanan tek þey deðildir. Ayrýca std::sort ve diðer algoritmalarýnda da kullanýlýrlar. Artýk onlarýn
ne olduðunu bildiðinize göre, standart kütüphanede oldukça fazla kullanýldýklarýný fark edeceksiniz.

Ýteratör geçersizleþtirme (sallanan iteratörler)
------------------------------------------------
Ýþaretçiler ve referanslar gibi, iteratörler de üzerinde yineleme yapýlan öðelerin adresi deðiþtirildiðinde veya yok edildiðinde "sallanabilir".
Böyle bir durumda, iteratörün geçersizleþtirildiðini söyleriz. Geçersizleþtirilmiþ bir iteratöre eriþmek tanýmsýz davranýþa neden olur.

Konteynerleri deðiþtiren bazý iþlemler (örneðin bir std::vector'a bir öðe eklemek gibi) konteynerdaki öðelerin adreslerinin deðiþmesine neden
olabilir. Böyle bir durumda, bu öðelere olan mevcut iteratörler geçersizleþtirilir. Ýyi bir C++ referans belgesi, hangi konteyner iþlemlerinin
iteratörleri geçersizleþtirebileceðini veya geçersizleþtireceðini belirtmelidir. Örnek olarak, cppreference'deki std::vector'ün "Iterator
invalidation" bölümüne bakabilirsiniz. https://en.cppreference.com/w/cpp/container/vector#Iterator_invalidation

Aralýk tabanlý for döngüleri arka planda iteratörleri kullandýðýndan, aktif olarak gezdiðimiz konteynerin iteratörlerini geçersizleþtirecek 
bir þey yapmamaya dikkat etmeliyiz:

                #include <vector>

                int main()
                {
                    std::vector v { 0, 1, 2, 3 };

                    for (auto num : v) // v üzerinde dolaylý olarak yineleme yapar
                    {
                        if (num % 2 == 0)
                            v.push_back(num + 1); // bu, v'nin iteratörlerini geçersizleþtirdiðinde, tanýmsýz davranýþ ortaya çýkar
                    }

                    return 0;
                }

Ýþte iteratör geçersizleþtirmenin baþka bir örneði:

                #include <iostream>
                #include <vector>

                int main()
                {
                    std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

                    auto it{ v.begin() };

                    ++it; // ikinci öðeye geç
                    std::cout << *it << '\n'; // tamam: 2 yazdýrýr

                    v.erase(it); // þu anda üzerinde yineleme yapýlan öðeyi sil

                    // erase() silinen öðeye (ve sonraki öðelere) olan iteratörleri geçersizleþtirir
                    // bu yüzden "it" iteratörü þimdi geçersizleþtirildi

                    ++it; // tanýmsýz davranýþ
                    std::cout << *it << '\n'; // tanýmsýz davranýþ

                    return 0;
                }

Geçersizleþtirilmiþ iteratörler, onlara geçerli bir iteratör atayarak (ör. begin(), end() veya bir iteratör döndüren baþka bir fonksiyonun
dönüþ deðeri) yeniden geçerli hale getirilebilir.

Erase() fonksiyonu, silinen öðeden bir sonraki öðeye (veya son öðe kaldýrýldýysa end() 'e) bir iteratör döndürür. Bu nedenle, yukarýdaki kodu þu 
þekilde düzeltebiliriz:

#include <iostream>
#include <vector>

                int main()
                {
                    std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

                    auto it{ v.begin() };

                    ++it; // ikinci öðeye geç
                    std::cout << *it << '\n';

                    it = v.erase(it); // þu anda üzerinde yineleme yapýlan öðeyi sil, `it`'yi bir sonraki öðeye ayarla

                    std::cout << *it << '\n'; // þimdi tamam, 3 yazdýrýr

                    return 0;
                }

18.3 — Standart kütüphane algoritmalarýna giriþ
-----------------------------------------------
Yeni programcýlar genellikle, dizileri sýralama veya sayma veya arama gibi nispeten basit görevleri gerçekleþtirmek için çok fazla zaman harcarlar.
Bu döngüler, bir hatayý ne kadar kolay yapabileceðiniz ve genel bakým açýsýndan sorunlu olabilir, çünkü döngüler anlamasý zor olabilir.

Arama, sayma ve sýralama gibi iþlemler bu kadar yaygýn olduðu için, C++ standart kütüphanesi bu iþlemleri sadece birkaç satýr kodda yapmak için bir
dizi fonksiyonla gelir. Ek olarak, bu standart kütüphane fonksiyonlarý önceden test edilmiþtir, verimlidir, çeþitli farklý konteyner türlerinde
çalýþýr ve birçoklarý paralelleþtirme destekler (ayný görevi daha hýzlý tamamlamak için birden çok CPU iþ parçacýðýný ayný göreve ayýrma yeteneði).

Algoritmalar kütüphanesinde saðlanan iþlevsellik genellikle üç kategoriye ayrýlýr:
----------------------------------------------------------------------------------
*- Denetleyiciler (Inspectors ) -- Bir konteynerdeki verileri görüntülemek (ancak deðiþtirmemek) için kullanýlýr. Örnekler arama ve saymayý içerir.
*- Deðiþtiriciler ( Mutators ) -- Bir konteynerdeki verileri deðiþtirmek için kullanýlýr. Örnekler sýralama ve karýþtýrmayý içerir.
*- Kolaylaþtýrýcýlar ( Facilitators ) -- Veri üyelerinin deðerlerine dayalý bir sonuç oluþturmak için kullanýlýr. 
   Örnekler, deðerleri çarpan nesneleri veya öðe çiftlerinin hangi sýrayla sýralanmasý gerektiðini belirleyen nesneleri içerir.

   Bu algoritmalar, "algorithms" kütüphanesinde bulunur. Bu derste, daha yaygýn algoritmalarýn bazýlarýný inceleyeceðiz - ancak çok daha fazlasý
   var ve baðlantýlý referansý okuyarak her þeyi görmek için sizi teþvik ediyoruz!

Not: Bunlarýn hepsi yineleyicileri kullanýr, bu yüzden temel yineleyicilerle tanýdýk deðilseniz, lütfen 18.2 -- Yineleyicilere Giriþ dersini gözden
geçirin.

Bir elemaný deðeriyle bulmak için std::find kullanma
----------------------------------------------------
std::find, bir deðerin bir konteynýrda ilk oluþumunu arar. std::find 3 parametre alýr: dizinin baþlangýç elemanýna bir yineleyici, dizinin bitiþ
elemanýna bir yineleyici ve aranacak bir deðer. Bulunan elemana (eðer bulunursa) veya konteynýrýn sonuna (eðer eleman bulunamazsa) iþaret eden bir
yineleyici döndürür Örneðin:

                #include <algorithm>
                #include <array>
                #include <iostream>

                int main()
                {
                    std::array arr{ 13, 90, 99, 5, 40, 80 };

                    std::cout << "Aranacak ve yerine konulacak bir deðer girin: ";
                    int search{};
                    int replace{};
                    std::cin >> search >> replace;

                    // Giriþ doðrulamasý atlandý

                    // std::find, bulunan elemana (veya konteynýrýn sonuna) iþaret eden bir yineleyici döndürür
                    // bunu bir deðiþkende saklayacaðýz, yineleyicinin türünü çýkarmak için tür çýkarýmýný kullanýyoruz
                    // (çünkü umursamýyoruz)
                    auto found{ std::find(arr.begin(), arr.end(), search) };

                    // Aradýklarýný bulamayan algoritmalar, son yineleyiciyi döndürür.
                    // Bunu end() üye fonksiyonunu kullanarak eriþebiliriz.
                    if (found == arr.end())
                    {
                        std::cout << search << " bulunamadý" << '\n';
                    }
                    else
                    {
                        // Bulunan elemanýn üzerine yaz.
                        *found = replace;
                    }

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }
                Çýktýlar:

                Aranacak ve yerine konulacak bir deðer girin: 5 234
                13 90 99 234 40 80
                Eleman bulunamadýðýnda örnek çalýþtýrma

                Aranacak ve yerine konulacak bir deðer girin: 0 234
                0 bulunamadý
                13 90 99 5 40 80
Bir elemanýn belirli bir koþulu karþýlayýp karþýlamadýðýný bulmak için std::find_if kullanma
--------------------------------------------------------------------------------------------
Bazen, bir konteynýrda belirli bir koþulu karþýlayan bir deðer olup olmadýðýný görmek istiyoruz (ör. belirli bir alt dizeyi içeren bir dize) 
belirli bir deðerden ziyade. Bu tür durumlarda, std::find_if mükemmeldir.

std::find_if fonksiyonu, std::find'a benzer þekilde çalýþýr, ancak aranacak belirli bir deðer yerine, çaðrýlabilir bir nesne geçiririz,
örneðin bir fonksiyon iþaretçisi (veya bir lambda, daha sonra ele alacaðýz). Yinelenecek her öðe için, std::find_if bu fonksiyonu çaðýrýr 
(öðeyi fonksiyona argüman olarak geçirir) ve fonksiyon, bir eþleþme bulunursa true dönebilir veya aksi takdirde false dönebilir.

Ýþte, herhangi bir öðenin "nut" alt dizgesini içerip içermediðini kontrol etmek için std::find_if'i kullandýðýmýz bir örnek:

                #include <algorithm>
                #include <array>
                #include <iostream>
                #include <string_view>

                // Fonksiyonumuz, öðe eþleþirse true dönecektir
                bool containsNut(std::string_view str)
                {
                    // std::string_view::find, alt dizeyi bulamazsa std::string_view::npos döndürür
                    // Aksi takdirde, alt dizgenin str'de nerede olduðunu döndürür.
                    return (str.find("nut") != std::string_view::npos);
                }

                int main()
                {
                    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

                    // Dizimizi tarayýn ve herhangi bir öðenin "nut" alt dizgesini içerip içermediðini görün
                    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

                    if (found == arr.end())
                    {
                        std::cout << "Fýndýk yok\n";
                    }
                    else
                    {
                        std::cout << *found << " bulundu" << '\n';
                    }

                    return 0;
                }
                Çýktý

                Walnut bulundu

Yukarýdaki örneði el ile yazmak isterseniz, en az üç döngüye ihtiyacýnýz olurdu (diziyi döngüye almak için bir ve alt dizeyi eþleþtirmek için iki).
Standart kütüphane fonksiyonlarý, ayný þeyi sadece birkaç kod satýrýyla yapmamýzý saðlar!

std::count ve std::count_if kullanarak kaç tane örneðin olduðunu sayma
----------------------------------------------------------------------
std::count ve std::count_if, bir öðenin veya bir koþulu karþýlayan bir öðenin tüm örneklerini arar.
Aþaðýdaki örnekte, kaç öðenin "nut" alt dizesini içerdiðini sayacaðýz:

                #include <algorithm>
                #include <array>
                #include <iostream>
                #include <string_view>

                bool containsNut(std::string_view str)
                {
                    return (str.find("nut") != std::string_view::npos);
                }

                int main()
                {
                    std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" };

                    auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };

                    std::cout << "Counted " << nuts << " nut(s)\n";

                    return 0;
                }

                Çýktý

                Counted 2 nut(s)

std::sort kullanarak özel sýralama
----------------------------------
Daha önce std::sort'u bir diziyi artan sýrayla sýralamak için kullanmýþtýk, ancak std::sort daha fazlasýný yapabilir. std::sort'un, istediðimiz
gibi sýralamamýza izin veren üçüncü bir parametre olarak bir iþlev alan bir sürümü vardýr. Ýþlev, iki parametreyi karþýlaþtýrýr ve ilk argümanýn 
ikinciden önce sýralanmasý gerekiyorsa true döndürür. Varsayýlan olarak, std::sort öðeleri artan sýrayla sýralar.

Bir diziyi ters sýrayla sýralamak için std::sort'u, greater adlý özel bir karþýlaþtýrma iþlevi kullanarak kullanalým:

                #include <algorithm>
                #include <array>
                #include <iostream>

                bool greater(int a, int b)
                {
                    // Eðer @a, @b'den büyükse, @a'yý @b'den önce sýrala.
                    return (a > b);
                }

                int main()
                {
                    std::array arr{ 13, 90, 99, 5, 40, 80 };

                    // greater'ý std::sort'a geçirin
                    std::sort(arr.begin(), arr.end(), greater);

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }

                Çýktý

                99 90 80 40 13 5
Bir kez daha, kendi özel döngü iþlevlerimizi yazmak yerine, dizimizi sadece birkaç kod satýrýnda istediðimiz gibi sýralayabiliriz!

Greater iþlevimizin 2 argümana ihtiyacý var, ancak ona hiçbir þey geçmiyoruz, bu yüzden nereden geliyorlar? Parantez olmadan bir iþlevi () 
kullanýldýðýnda, bu sadece bir iþlev iþaretçisidir, bir çaðrý deðildir. Bunu, bir iþlevi parantezsiz yazdýrmayý denediðimizde ve std::cout'un
"1" yazdýrdýðý durumdan hatýrlayabilirsiniz. std::sort, bu iþaretçiyi kullanýr ve gerçek greater iþlevini dizinin herhangi 2 öðesiyle çaðýrýr.
Greater'ýn hangi öðelerle çaðrýlacaðýný bilmiyoruz, çünkü std::sort'un altýnda hangi sýralama algoritmasýný kullandýðý tanýmlanmamýþtýr. 
Daha sonraki bir bölümde iþlev iþaretçileri hakkýnda daha fazla konuþuyoruz.

Ýpucu

Azalan sýrayla sýralama o kadar yaygýndýr ki, C++ bunun için de özel bir tür (std::greater adlý) saðlar (bu, functional baþlýðýnýn bir parçasýdýr).
Yukarýdaki örnekte, þunu deðiþtirebiliriz:

                std::sort(arr.begin(), arr.end(), greater); // özel greater iþlevimizi çaðýrýn
þununla:
                std::sort(arr.begin(), arr.end(), std::greater{}); // standart kütüphane greater karþýlaþtýrmasýný kullanýn
                // C++17'den önce, std::greater'ý oluþtururken öðe türünü belirtmemiz gerekiyordu
                std::sort(arr.begin(), arr.end(), std::greater<int>{}); // standart kütüphane greater karþýlaþtýrmasýný kullanýn
std::greater{}'ýn süslü parantezlere ihtiyacý olduðunu unutmayýn çünkü bu çaðrýlabilir bir iþlev deðildir. Bu bir türdür ve onu kullanmak için,
bu türden bir nesne oluþturmamýz gerekiyor. Süslü parantezler, bu türden anonim bir nesne oluþturur (daha sonra std::sort'a bir argüman olarak 
geçer).

Bir konteynýrýn tüm elemanlarýna bir þey yapmak için std::for_each kullanma
---------------------------------------------------------------------------
std::for_each, bir listeyi girdi olarak alýr ve her bir elemana özel bir fonksiyon uygular. Bu, bir listesindeki her bir elemana ayný iþlemi 
gerçekleþtirmek istediðimizde kullanýþlýdýr.

Ýþte bir örnekte, std::for_each'i bir dizideki tüm sayýlarý ikiye katlamak için kullanýyoruz:

                #include <algorithm>
                #include <array>
                #include <iostream>

                void doubleNumber(int& i)
                {
                    i *= 2;
                }

                int main()
                {
                    std::array arr{ 1, 2, 3, 4 };

                    std::for_each(arr.begin(), arr.end(), doubleNumber);

                    for (int i : arr)
                    {
                        std::cout << i << ' ';
                    }

                    std::cout << '\n';

                    return 0;
                }
                Çýktý

                2 4 6 8

Bu, genellikle yeni geliþtiriciler için en gereksiz algoritma gibi görünür, çünkü aralýk tabanlý bir for döngüsü ile eþdeðer kod daha kýsa ve daha
kolaydýr. Ancak std::for_each'in faydalarý vardýr. std::for_each'i bir aralýk tabanlý for döngüsü ile karþýlaþtýralým.

                std::ranges::for_each(arr, doubleNumber); // C++20'den itibaren, begin() ve end() kullanmak zorunda deðiliz.
                // std::for_each(arr.begin(), arr.end(), doubleNumber); // C++20'den önce

                for (auto& i : arr)
                {
                    doubleNumber(i);
                }
std::for_each ile niyetlerimiz açýktýr. arr'ýn her bir elemaný ile doubleNumber'ý çaðýrýn. Aralýk tabanlý for döngüsünde, yeni bir deðiþken
eklememiz gerekiyor, i. Bu, bir programcýnýn yorgun olduðunda veya dikkat etmediðinde yapabileceði birkaç hataya yol açar. Öncelikle, otomatik 
kullanmazsak bir açýk dönüþüm olabilir. Ampersandi unutabiliriz ve doubleNumber diziyi etkilemez. Yanlýþlýkla i dýþýnda bir deðiþkeni
doubleNumber'a geçirebiliriz. Bu hatalar std::for_each ile olamaz.

Ayrýca, std::for_each, bir konteynýrýn baþýndaki veya sonundaki elemanlarý atlayabilir, örneðin arr'ýn ilk elemanýný atlamak için, std::next
kullanýlabilir ve baþlangýcý bir sonraki elemana ilerletebilir.

                std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
                // Þimdi arr [1, 4, 6, 8]. Ýlk eleman ikiye katlanmadý.
Bu, bir aralýk tabanlý for döngüsü ile mümkün deðildir.

Birçok algoritma gibi, std::for_each paralelize edilebilir ve daha hýzlý iþlem saðlar, bu da onu büyük projeler ve büyük veriler için bir aralýk
tabanlý for döngüsünden daha uygun hale getirir.

Performans ve yürütme sýrasý
----------------------------
Algoritmalar kütüphanesindeki birçok algoritma, nasýl çalýþacaklarýna dair bir tür garanti verir. Genellikle bunlar ya performans garantileri ya da
hangi sýrayla çalýþacaklarýna dair garantilerdir. Örneðin, std::for_each, her bir elemanýn yalnýzca bir kez eriþileceðini ve elemanlarýn ileri
sýralý sýrayla eriþileceðini garanti eder.

Çoðu algoritma bir tür performans garantisi saðlarken, daha azýnýn yürütme sýrasý garantileri vardýr. Bu tür algoritmalar için, elemanlarýn hangi 
sýrayla eriþileceði veya iþleneceði konusunda varsayýmlar yapmamaya dikkat etmemiz gerekiyor.

Örneðin, bir standart kütüphane algoritmasýný kullanarak ilk deðeri 1 ile, ikinci deðeri 2 ile, üçüncüyü 3 ile çarpmak vb. istiyorsak, ileri sýralý
yürütme sýrasýný garanti etmeyen herhangi bir algoritmayý kullanmaktan kaçýnmak isteriz!

Aþaðýdaki algoritmalar sýralý yürütme garanti eder: std::for_each, std::copy, std::copy_backward, std::move ve std::move_backward. Birçok diðer 
algoritma (özellikle ileri yineleyici kullananlar) ileri yineleyici gereksinimi nedeniyle dolaylý olarak sýralýdýr.

*** BEST -> Belirli bir algoritmayý kullanmadan önce, performans ve yürütme sýrasý garantilerinin belirli kullaným durumunuz için çalýþtýðýndan
            emin olun.

C++20'de Aralýklar ( Ranges )
-----------------------------
Her algoritmaya açýkça arr.begin() ve arr.end() geçirmek biraz sinir bozucu. Ama korkmayýn - C++20, bize sadece arr'ý geçmemizi saðlayan aralýklar
ekler. Bu, kodumuzu daha da kýsa ve okunabilir hale getirecektir.

Sonuç

Algoritmalar kütüphanesi, kodunuzu daha basit ve daha saðlam hale getirebilecek bir ton kullanýþlý iþlevsellik içerir. Bu derste sadece küçük bir
alt kümesini ele alýyoruz, ancak bu fonksiyonlarýn çoðu çok benzer þekilde çalýþtýðý için, birkaçýnýn nasýl çalýþtýðýný bildiðinizde, çoðunu
kullanabilirsiniz.

Not:
Bu https://www.youtube.com/watch?v=2olsGf6JIkU video, kütüphanedeki çeþitli algoritmalarý özlü bir þekilde açýklama konusunda iyi bir iþ çýkarýyor.

*** BEST ->  Ayný þeyi yapmak için kendi iþlevselliðinizi yazmak yerine algoritmalar kütüphanesinden fonksiyonlarý kullanmayý tercih edin.

18.4 — Kodunuzu Zamanlama
-------------------------
Kodunuzu yazarken, bazen hangi yöntemin daha performanslý olacaðýndan emin olmadýðýnýz durumlarla karþýlaþýrsýnýz. Peki, bunu nasýl anlarsýnýz?
Bir yol, kodunuzu zamanlayarak ne kadar sürede çalýþtýðýný görmektir. C++11, bunu yapmak için chrono kütüphanesinde bazý iþlevlerle birlikte gelir.
Ancak, chrono kütüphanesini kullanmak biraz gizemlidir. Ýyi haber þu ki, ihtiyacýmýz olan tüm zamanlama iþlevselliðini kendi programlarýmýzda 
kullanabileceðimiz bir sýnýfa kolayca kapsülleyebiliriz.

Ýþte sýnýf:

                #include <chrono> // std::chrono iþlevleri için

                class Timer
                {
                private:
                    // Ýç içe geçmiþ türleri eriþmeyi kolaylaþtýrmak için tür takma adlarý
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg { Clock::now() };

                public:
                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

Ýþte bu! Kullanmak için, ana fonksiyonumuzun baþýnda (veya zamanlamaya baþlamak istediðimiz herhangi bir yerde) bir Timer nesnesi oluþturuyoruz 
ve ardýndan programýn o noktaya kadar çalýþmasýnýn ne kadar sürdüðünü bilmek istediðimizde elapsed() üye fonksiyonunu çaðýrýyoruz.

                #include <iostream>

                int main()
                {
                    Timer t;

                    // Zamanlanacak kod buraya gider

                    std::cout << "Geçen süre: " << t.elapsed() << " saniye\n";

                    return 0;
                }
Þimdi, bunu 10000 elemanlý bir dizi sýraladýðýmýz gerçek bir örnekte kullanalým. Önce, önceki bir bölümde geliþtirdiðimiz seçim sýralama
algoritmasýný kullanalým:

                #include <array>
                #include <chrono> // std::chrono iþlevleri için
                #include <cstddef> // std::size_t için
                #include <iostream>
                #include <numeric> // std::iota için

                const int g_arrayElements { 10000 };

                class Timer
                {
                private:
                    // Ýç içe geçmiþ türleri eriþmeyi kolaylaþtýrmak için tür takma adlarý
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg{ Clock::now() };

                public:

                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

                void sortArray(std::array<int, g_arrayElements>& array)
                {

                    // Dizinin her bir elemanýndan geçin
                    // (sonuncusu hariç, oraya geldiðimizde zaten sýralanmýþ olacak)
                    for (std::size_t startIndex{ 0 }; startIndex < (g_arrayElements - 1); ++startIndex)
                    {
                        // smallestIndex, bu iterasyonda karþýlaþtýðýmýz en küçük elemanýn indeksidir
                        // En küçük elemanýn bu iterasyonun ilk elemaný olduðunu varsayarak baþlayýn
                        std::size_t smallestIndex{ startIndex };

                        // Sonra geri kalan dizide daha küçük bir eleman arayýn
                        for (std::size_t currentIndex{ startIndex + 1 }; currentIndex < g_arrayElements; ++currentIndex)
                        {
                            // Daha önce bulduðumuz en küçükten daha küçük bir eleman bulduysak
                            if (array[currentIndex] < array[smallestIndex])
                            {
                                // onu takip edin
                                smallestIndex = currentIndex;
                            }
                        }

                        // smallestIndex þimdi kalan dizideki en küçük elemandýr
                        // baþlangýç elemanýmýzý en küçük elemanýmýzla deðiþtirin (bu onu doðru yere sýralar)
                        std::swap(array[startIndex], array[smallestIndex]);
                    }
                }

                int main()
                {
                    std::array<int, g_arrayElements> array;
                    std::iota(array.rbegin(), array.rend(), 1); // diziyi 10000'den 1'e kadar deðerlerle doldurun

                    Timer t;

                    sortArray(array);

                    std::cout << "Harcanan zaman: " << t.elapsed() << " saniye\n";

                    return 0;
                }


Yazarýn makinesinde, üç çalýþma 0.0507, 0.0506 ve 0.0498 zamanlamalarýný üretti. Yani yaklaþýk 0.05 saniye diyebiliriz.

Þimdi, ayný testi standart kütüphaneden std::sort kullanarak yapalým.

                #include <algorithm> // std::sort için
                #include <array>
                #include <chrono> // std::chrono fonksiyonlarý için
                #include <cstddef> // std::size_t için
                #include <iostream>
                #include <numeric> // std::iota için

                const int g_arrayElements { 10000 };

                class Timer
                {
                private:
                    // Ýç içe geçmiþ türleri daha kolay eriþilebilir hale getirmek için tür takma adlarý
                    using Clock = std::chrono::steady_clock;
                    using Second = std::chrono::duration<double, std::ratio<1> >;

                    std::chrono::time_point<Clock> m_beg{ Clock::now() };

                public:

                    void reset()
                    {
                        m_beg = Clock::now();
                    }

                    double elapsed() const
                    {
                        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
                    }
                };

                int main()
                {
                    std::array<int, g_arrayElements> array;
                    std::iota(array.rbegin(), array.rend(), 1); // diziyi 10000'den 1'e kadar deðerlerle doldurun

                    Timer t;

                    std::ranges::sort(array); // C++20'den itibaren
                    // Eðer derleyiciniz C++20 uyumlu deðilse
                    // std::sort(array.begin(), array.end());

                    std::cout << "Geçen süre: " << t.elapsed() << " saniye\n";

                    return 0;
                }

Yazarýn makinesinde, bu sonuçlarý üretti: 0.000693, 0.000692 ve 0.000699. Yani temelde tam olarak 0.0007 civarýnda.

Baþka bir deyiþle, bu durumda, std::sort kendimizin yazdýðý seçim sýralamasýndan 100 kat daha hýzlýdýr!

Programýnýzýn performansýný etkileyebilecek þeyler
--------------------------------------------------
Programýnýzýn bir çalýþmasýný zamanlamak oldukça basittir, ancak sonuçlarýnýz bir dizi þeyden önemli ölçüde etkilenebilir ve nasýl düzgün bir
þekilde ölçüleceðini ve hangi þeylerin zamanlamayý etkileyebileceðini bilmek önemlidir.

Ýlk olarak, bir hata ayýklama hedefi oluþturmak yerine bir sürüm hedefi oluþturduðunuzdan emin olun. Hata ayýklama hedefleri genellikle
optimizasyonu kapatýr ve bu optimizasyon sonuçlarý önemli ölçüde etkileyebilir. Örneðin, bir hata ayýklama hedefi kullanarak, yukarýdaki std::sort 
örneðini yazarýn makinesinde çalýþtýrmak 0.0235 saniye sürdü -- 33 kat daha uzun!

Ýkinci olarak, zamanlama sonuçlarýnýz sistemizin arka planda yapabileceði diðer þeylerden etkilenebilir. Sisteminizin CPU, bellek veya sabit disk 
yoðun bir þey yapmadýðýndan emin olun (ör. bir oyun oynama, bir dosya arama, bir antivirüs taramasý çalýþtýrma veya arka planda bir güncelleme
yükleme). Görünüþte masum þeyler, aktif sekme yeni bir reklam afiþi döndürdüðünde ve bir dizi javascript'i ayrýþtýrmak zorunda kaldýðýnda, 
boþta olan web tarayýcýlarýnýz CPU kullanýmýnýzý geçici olarak %100'e çýkarabilir. Ölçüm yapmadan önce kapatabileceðiniz uygulama sayýsý ne kadar 
fazla olursa, sonuçlarýnýzdaki varyans o kadar az olur.

Üçüncü olarak, programýnýz bir rastgele sayý üreteci kullanýyorsa, üretilen rastgele sayýlarýn belirli bir sýrasý zamanlamayý etkileyebilir.
Örneðin, rastgele sayýlarla dolu bir dizi sýralýyorsanýz, sonuçlar muhtemelen çalýþmadan çalýþmaya deðiþir çünkü diziyi sýralamak için gereken
takas sayýsý çalýþmadan çalýþmaya deðiþir. Programýnýzýn birden çok çalýþmasýnda daha tutarlý sonuçlar elde etmek için, rastgele sayý üretecinizi 
geçici olarak bir literal deðerle (std::random_device veya sistem saati yerine) çekirdekleyebilirsiniz, böylece her çalýþmada ayný sayý dizisini
üretir. Ancak, programýnýzýn performansý üretilen belirli rastgele sýraya çok baðlýysa, bu da genel olarak yanýltýcý sonuçlara yol açabilir.

Dördüncü olarak, kullanýcý giriþini beklerken zamanlamadýðýnýzdan emin olun, çünkü kullanýcýnýn bir þeyi ne kadar sürede girdiði zamanlama
düþüncelerinizin bir parçasý olmamalýdýr. Kullanýcý giriþi gerekiyorsa, kullanýcýyý beklemeyen bir giriþ saðlama yolu eklemeyi düþünün 
(ör. komut satýrý, bir dosyadan, giriþi çevreleyen bir kod yolu).

Performans ölçümü
-----------------
Programýnýzýn performansýný ölçerken, en az 3 sonuç toplayýn. Sonuçlar benzerse, bunlar muhtemelen programýnýzýn o makinedeki gerçek performansýný
temsil eder. Aksi takdirde, benzer sonuçlarýn bir kümesine sahip olana kadar ölçümler yapmaya devam edin (ve hangi diðer sonuçlarýn aykýrý olduðunu
anlayýn). Sisteminizin bazý çalýþmalar sýrasýnda arka planda bir þeyler yapmasý nedeniyle bir veya daha fazla aykýrý deðere sahip olmak alýþýlmadýk
bir durum deðildir.

Sonuçlarýnýzda çok fazla deðiþkenlik varsa (ve iyi bir þekilde kümeleþmiyorsa), programýnýz muhtemelen sistemde olup biten diðer þeylerden önemli
ölçüde etkileniyor veya uygulamanýzdaki rastgeleleþtirme etkilerinden etkileniyordur.

Performans ölçümleri o kadar çok þeyden etkilendiði için (özellikle donaným hýzý, ama ayný zamanda iþletim sistemi, çalýþan uygulamalar, vb.),
mutlak performans ölçümleri (ör. "program 10 saniyede çalýþýr") genellikle yalnýzca programýn sizin önemsediðiniz bir makinede ne kadar iyi 
çalýþtýðýný anlamak dýþýnda pek kullanýþlý deðildir. Farklý bir makinede, ayný program 1 saniye, 10 saniye veya 1 dakika içinde çalýþabilir.
Farklý donanýmlar arasýnda gerçekten ölçüm yapmadan bunu bilmek zordur.

Ancak, tek bir makinede, göreceli performans ölçümleri yararlý olabilir. Bir programýn çeþitli varyantlarýndan performans sonuçlarý toplayabilir ve
hangi varyantýn en performanslý olduðunu belirleyebiliriz. Örneðin, varyant 1 10 saniyede çalýþýyorsa ve varyant 2 8 saniyede çalýþýyorsa,
varyant 2 muhtemelen tüm benzer makinelerde mutlak makine hýzýndan baðýmsýz olarak daha hýzlý olacaktýr.

Ýkinci varyantý ölçtükten sonra, iyi bir mantýk kontrolü ilk varyantý tekrar ölçmektir. Ýlk varyantýn sonuçlarý, o varyant için ilk ölçümlerinizle
tutarlýysa, her iki varyantýn sonucu makul ölçüde karþýlaþtýrýlabilir olmalýdýr. Örneðin, varyant 1 10 saniyede çalýþýyor, varyant 2 8 saniyede 
çalýþýyor ve sonra varyant 1'i tekrar ölçüyoruz ve 10 saniye alýyorsak, her iki varyantýn ölçümlerinin adil bir þekilde ölçüldüðünü ve varyant 2'nin
daha hýzlý olduðunu makul bir þekilde sonuçlandýrabiliriz.

Ancak, ilk varyantýn sonuçlarý artýk o varyant için ilk ölçümlerinizle tutarlý deðilse, makinede þimdi performansý etkileyen bir þey olmuþtur ve
ölçümdeki farklýlýklarýn varyanttan mý yoksa makinenin kendisinden mi kaynaklandýðýný anlamak zor olacaktýr. Bu durumda, mevcut sonuçlarý atmak 
ve yeniden ölçmek en iyisidir.
*/