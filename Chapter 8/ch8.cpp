/*
																CHAPTER 8 - Kontrol Akýþýna Giriþ	
Bir program çalýþtýrýldýðýnda, CPU main() fonksiyonunun baþýnda iþlemi baþlatýr, belirli sayýda ifadeyi (varsayýlan olarak sýralý bir þekilde) yürütür ve ardýndan 
program main() fonksiyonunun sonunda sona erer. CPU'nun yürüttüðü belirli ifadeler dizisine programýn yürütme yolu - execution path -  (veya kýsaca path) denir.

örneðin:
			#include <iostream>

			int main()
			{
	5			std::cout << "Enter an integer: ";

	7			int x{};
	8			std::cin >> x;

	10			std::cout << "You entered " << x << '\n';

	12			return 0;
			}

Bu programýn yürütme yolu, sýrasýyla 5, 7, 8, 10 ve 12. satýrlarý içerir. Bu, bir doðrusal program örneðidir. Doðrusal programlar, her çalýþtýrýldýðýnda ayný yolu
izler (ayný ifadeleri ayný sýrayla yürütür). Ancak genellikle bu istediðimiz þey deðildir. Örneðin, kullanýcýdan giriþ istediðimizde ve kullanýcý geçersiz bir þey 
girerse, ideal olarak kullanýcýdan baþka bir seçim yapmasýný istemek isteriz. Bu, doðrusal bir programda mümkün deðildir. Aslýnda, kullanýcý tekrar tekrar geçersiz 
giriþ yapabilir, bu nedenle onlardan baþka bir seçim yapmalarýný istememiz gereken kez sayýsý çalýþma zamanýnda bilinemez. Neyse ki, C++, programýn normal yürütm
e yolunu deðiþtirmek için programcýnýn kullanmasýna izin veren bir dizi farklý kontrol akýþý ifadesi (ayrýca akýþ kontrol ifadeleri olarak da adlandýrýlýr) saðlar.
Zaten if ifadeleriyle (lesson 4.10 -- if Ýfadelerine Giriþ'te tanýtýlan) bir örnek gördünüz; bu ifadeler bize bir koþul ifadesi doðruysa yalnýzca bir ifadeyi yürütme
olanaðý tanýr. Bir kontrol akýþý ifadesi, yürütme noktasýný ardýþýk olmayan bir ifadeye taþýdýðýnda, buna dallanma (branching ) denir.

Akýþ kontrolü ifadelerinin kategorileri þunlardýr:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Kategori				|											Anlam														|	C++ Ýçinde Uygulanmýþ Hali
Koþullu ifadeler		|	Koþullu ifadeler, bir koþul karþýlandýðýnda yalnýzca belirli bir kod dizisini yürütmeye neden olur.	|	  if, switch
Atlamalar				|	Atlamalar, CPU'ya baþka bir konumda bulunan ifadeleri yürütmeye baþlamasýný söyler.					|	  goto, break, continue
Fonksiyon çaðrýlarý		|	Fonksiyon çaðrýlarý, baþka bir konuma ve geriye dönmek için atlama iþlevine sahiptir.				|	  Fonksiyon çaðrýlarý, return
Döngüler				|	Döngüler, belirli bir koþul karþýlanana kadar bir kod dizisini sýfýr veya daha fazla				|
						|	kez tekrarlamak için programý yönlendirir.															|	  while, do-while, for, ranged-for
Durdurmalar				|	Durdurmalar, programýn çalýþmasýný sonlandýrmasýný söyler.											|	  std::exit(), std::abort()
Ýstisnalar				|	Ýstisnalar, hata iþleme amacýyla tasarlanmýþ özel bir akýþ kontrol yapýsýdýr.						|	  try, throw, catch
----------------------------------------------------------------------------------------------------------------------------------------------------------------------												


Bu bölüm boyunca, istisnalar hariç (ha) tüm bu kategorileri detaylý bir þekilde ele alacaðýz ve istisnalarý (chapter 27'ye tamamen ayýrdýðýmýz) ilerleyen bir
bölüme býrakacaðýz. Bu bölümden önce, bir programýn yapabileceði þeyler oldukça sýnýrlýydý. Programýnýzýn akýþýný kontrol edebilmek (özellikle döngüler kullanarak) 
bir dizi ilginç þeyi mümkün kýlar! Artýk sadece oyuncak programlarla sýnýrlý kalmayacak, gerçek fayda saðlayan programlar yazabileceksiniz.
Ýþte gerçek eðlence burada baþlýyor. O zaman baþlayalým!
*/

/*
																	IF STATEMENTS AND BLOCKS

If else yapýlarýnda blok oluþturmazsak sadece tek bir satýr if else sistemine baðlý olacaktýr. Yani þu þekilde;
if(condition)
	statement 
else									Buradaki gibi her hangi bir compound statement koymadýðýmýz için yani blok koymadýðýmýz için burada else in altýndaki statement 
	statement1							statement 2 hep çalýþýr birden çok statement yürütmek istiyorsak blok kullanacaðýz.
	statement2 
Tekli ifadelerde blok kullanmak veya kullanmamak
------------------------------------------------
Bu konuda komünite ve bazý deneyimli c++ geliþtiricileri 2 ye ayrýlmýþ. Komünite her durumda kullanýn diyor. Kullanmamayý savunan geliþtiricilerin argümaný ise 
kodu dikey olarak uzattýðý için bir seferde daha az kod göreceðimiz yönünde bu da baþka hatalarý vs. gözden kaçýracaðýmýzý ileri sürüyor. 
*** BEST -> En iyi hareket Bu if veya else ile iliþkilendirilmiþ tek ifadeleri bloklara koymayý düþünün (özellikle öðrenme aþamasýndayken). Daha deneyimli C++
			geliþtiricileri, dikey boþluðu sýkýlaþtýrmak lehine, bazen bu uygulamayý göz ardý edebilirler.

Orta bir yol alternatifi, tek satýrlarý if veya else ile ayný satýra koymaktýr: yani :
			if (age >= minDrinkingAge) purchaseBeer(); -> Bunun gibi
Bu, yukarýda bahsedilen her iki olumsuz durumu da önlerken, okunabilirlik açýsýndan bazý küçük maliyetlerle birlikte gelir.

Programcý bir if ifadesinin veya else ifadesinin ifade kýsmýnda bir blok bildirmezse, derleyici örtülü olarak bir blok beyan edecektir. Böylece:
											if ( condition )
											{	
			if (condition)						true_statement;
				true_statement;		->		}
			else							else
				false_statement;									{
												false_statement;
											}
				
Genel If-Else hatalarý
----------------------
Bir if else yapýsýný bir birine baðlayabiliriz örneðin:
	
				if (x >= 0) // outer if statement
					// if i bu þekilde baðlamak kötü bir kod stili
					if (x <= 20) // inner if statement
						std::cout << x << " is between 0 and 20\n";

				// Bu else hangi if e ait
				else
					std::cout << x << " is negative\n";

Yukarýdaki program, bir potansiyel belirsizlik kaynaðý olan "dangling else" problemine yol açar. Yukarýdaki programdaki else ifadesi, dýþtaki 
if ifadesiyle mi yoksa içteki if ifadesiyle mi eþleþmiþtir?

Cevap þudur: Bir else ifadesi, ayný bloktaki son eþleþmemiþ if ifadesi ile eþleþir. Bu nedenle, yukarýdaki programda else ifadesi, içteki if ifadesi
ile eþleþir; sanki program þu þekilde yazýlmýþ gibi davranýr:

					if (condition1)
					{
						if (condition2)
							statement1;
						else
							statement2;
					}

Bu durumu önlemek için bloklarý ekleyerek ifadeleri açýkça belirtmek iyi bir uygulamadýr.
Ýç içe geçmiþ if ifadeleri kullanýrken bu tür belirsizlikleri önlemek için iyi bir fikir, içteki if ifadesini açýkça bir blok içine almak. 
Bu, bir else ifadesini her iki ifadeye de belirsizlik olmadan eklememize olanak tanýr:

						#include <iostream>

						int main()
						{
							std::cout << "Bir sayý girin: ";
							int x{};
							std::cin >> x;

							if (x >= 0)
							{
								if (x <= 20)
									std::cout << x << " 0 ile 20 arasýndadýr\n";
								else // içteki if ifadesine baðlý
									std::cout << x << " 20'den büyüktür\n";
							}
							else // dýþtaki if ifadesine baðlý
								std::cout << x << " negatiftir\n";

							return 0;
						}

Bloktaki else ifadesi içteki if ifadesine baðlýdýr ve blok dýþýndaki else ifadesi dýþtaki if ifadesine baðlýdýr.

veya else if kullanarak daha iyi çözerik ( Buna da flattened if else deniyor. ) burada logical operatörler kullanarak durumlarý teke indirmek gibi bir mantýk var. 

Null statement - geçtim 
== operatörü ile = operatörünü karýþtýrmamak lazým çünkü program burada her hangi bir hata üretmeden kodu çalýþtýrabilir fakat istediðimiz þekilde çalýþmayabilir.
*/
/*
																CONSTEXPR IF IFADESÝ

Genellikle, bir if ifadesinin koþulu çalýþma zamanýnda deðerlendirilir.

Ancak, koþul bir sabit ifade ise, aþaðýdaki örnekte olduðu gibi, durum þu þekilde düþünülebilir:

			#include <iostream>

			int main()
			{
				constexpr double gravity{ 9.8 };

				// reminder: low-precision floating point literals of the same type can be tested for equality
				if (gravity == 9.8) // constant expression, always true
					std::cout << "Gravity is normal.\n";   // will always be executed
				else
					std::cout << "We are not on Earth.\n"; // will never be executed

				return 0;
			}

Çünkü gravity sabit ifadesi olarak tanýmlanmýþ ve deðeri 9.8 ile baþlatýlmýþtýr, gravity == 9.8 koþulu her zaman doðru deðeri verecektir. Sonuç olarak, 
else ifadesi hiçbir zaman çalýþtýrýlmayacaktýr. Bir constexpr koþulu çalýþma zamanýnda deðerlendirmek israf olabilir (çünkü sonuç hiçbir zaman deðiþmeyecek).
Ayrýca, hiçbir zaman çalýþtýrýlamayacak kodu yürütülebilir bir programa dahil etmek de israf olacaktýr.
			
			
koþulun sabit bir ifade olmasýný gerektiren constexpr if ifadesini tanýtýr. Bir constexpr-if-ifadesinin koþulu derleme zamanýnda deðerlendirilir.

Eðer constexpr koþulu true deðerine deðerlendirilirse, tüm if-else ifadesi true-ifadesi ile deðiþtirilecektir. Eðer constexpr koþulu false deðerine 
deðerlendirilirse, tüm if-else ifadesi false-ifadesi ile (varsa) veya hiçbir þeyle (else yoksa) deðiþtirilecektir.

Bir constexpr-if-ifadesi kullanmak için, if ifadesinden sonra constexpr anahtar kelimesini ekleriz:
			
				#include <iostream>

				int main()
				{
					constexpr double gravity{ 9.8 };

					if constexpr (gravity == 9.8) // now using constexpr if
						std::cout << "Gravity is normal.\n";
					else
						std::cout << "We are not on Earth.\n";

					return 0;
				}			
			
Yukarýdaki kod derlendiðinde, derleyici koþulu derleme zamanýnda deðerlendirecek, her zaman doðru olduðunu görecek ve yalnýzca tek bir ifadeyi olan 
`std::cout << "Gravity is normal.\n";` ifadesini koruyacaktýr.
Baþka bir deyiþle, bu kodu derleyecektir:

				int main()
				{
					std::cout << "Gravity is normal.\n";

					return 0;
				}
*** Best -> Koþullu sabit bir ifade olduðunda constexpr if ifadelerini constexpr olmayan if ifadelerine tercih edin.
* 
Modern derleyiciler ve sabit if ifadeleri
-----------------------------------------
Optimizasyon amaçlarýyla, modern derleyiciler genellikle, constexpr koþullarý olan non-constexpr if ifadelerini adeta constexpr-if-ifadeleri gibi ele alacaktýr.
Ancak, bunu yapmak zorunda deðillerdir.

Derleyici, constexpr koþulu olan bir non-constexpr if ifadesi ile karþýlaþtýðýnda, size if constexpr kullanmanýzý öneren bir uyarý verebilir. Bu, derleme zamanýnda
deðerlendirmenin gerçekleþmesini saðlar (optimizasyonlar devre dýþý býrakýlsa bile).
*/
/*
																	SWITCH STATEMENTS

Bir deðiþken veya ifadeyi uzun bir if else zincirine sokmak hem okunaklýlýðý azaltýr hem de çok etkisiz bir yöntem olmuþ olur. 
Bir deðiþkeni veya ifadeyi bir dizi farklý deðere karþý test etmek yaygýn olduðundan, C++, bu amaç için özel olarak tasarlanmýþ bir switch ifadesi adýnda alternatif
bir koþul ifadesi saðlar. Ýþte ayný programý, bir switch kullanarak, yukarýdakiyle ayný þekilde:

										#include <iostream>

										void printDigitName(int x)
										{
											switch (x)
											{
												case 1:
													std::cout << "One";
													return;
												case 2:
													std::cout << "Two";
													return;
												case 3:
													std::cout << "Three";
													return;
												default:
													std::cout << "Unknown";
													return;
											}
										}

										int main()
										{
											printDigitName(2);
											std::cout << '\n';

											return 0;
										}


Switch ifadesinin temel fikri basittir: bir ifade (bazen koþul olarak adlandýrýlýr) bir deðer üretmek üzere deðerlendirilir. Eðer ifadenin deðeri, herhangi bir
case etiketinden sonraki deðere eþitse, eþleþen case etiketi sonrasýndaki ifadeler yürütülür. Eðer eþleþen bir deðer bulunamazsa ve bir default etiketi varsa,
default etiketinin sonrasýndaki ifadeler yürütülür.

Orijinal if ifadesine kýyasla, switch ifadesinin bir avantajý sadece bir kez ifadeyi deðerlendirmesidir (bu da daha verimli yapar), ayrýca switch ifadesi,
her durumda eþitlik testine tabi tutulan ifadenin ayný olduðunu okuyucuya daha açýk bir þekilde belirtir.

*** BEST -> Bir seçenek olduðunda if-else zincirleri yerine switch ifadelerini tercih edin.
* 
Switch  i baþlatma
------------------

Switch ifadesini kullanmaya baþlamak için switch anahtar kelimesini kullanýrýz. Bu anahtar kelimenin ardýndan, içinde deðerlendirmek istediðimiz koþulu içeren
parantezleri kullanýrýz. Genellikle ifade sadece tek bir deðiþken olacaktýr, ancak bu geçerli bir ifade olabilir.

Tek bir kýsýtlama vardýr: koþulun bir integral türüne deðerlendirilmesi gerekir (hangi temel türlerin integral tür olarak kabul edildiðini hatýrlamak için 4.1
dersine bakabilirsiniz) veya bir numaralandýrma türü olmalýdýr (gelecekteki 13.2 dersinde ele alýnacak olan baðlantýsýz numaralandýrmalar). veya buna 
dönüþtürülebilir olmalýdýr. Yüzen nokta türlerine, dizgilere ve çoðu diðer integral olmayan türlere deðerlendirilen ifadeler burada kullanýlamaz.
Koþul ifadesini takiben bir blok tanýmlarýz. Blok içinde, eþitlik testi yapmak istediðimiz tüm deðerleri tanýmlamak için etiketleri kullanýrýz. 
Ýki tür etiket bulunmaktadýr.
	1 - Case etiketi
	2 - Default etiketi
Case label
----------
Ýlk tür etiket, case anahtar kelimesi kullanýlarak bildirilen bir durum etiketidir ve bir sabit ifade ile takip edilir. Sabit ifade, koþulun türüyle eþleþmelidir
veya o türe dönüþtürülebilir olmalýdýr. Koþul ifadesinin deðeri, bir durum etiketinden sonraki ifadeye eþitse, yürütme o durum etiketinden sonraki 
ilk ifadeyle baþlar ve ardýndan sýralý olarak devam eder.

Ýþte koþulun bir durum etiketiyle eþleþtiði bir örnek:

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x, deðeri 2'yi üretmek üzere deðerlendirilir
					{
						case 1:
							std::cout << "Bir";
							return;
						case 2: // burada case ifadesi ile eþleþen
							std::cout << "Ýki"; // bu yüzden yürütme buradan baþlar
							return; // ve ardýndan çaðrýyý yapana geri döneriz
						case 3:
							std::cout << "Üç";
							return;
						default:
							std::cout << "Bilinmeyen";
							return;
					}
				}

				int main()
				{
					printDigitName(2);
					std::cout << '\n';

					return 0;
				}
				Bu kod : 2 Ýki çýktýsýný verir. 

Yukarýdaki programda x, deðeri 2'yi üretmek üzere deðerlendirilir. Deðer 2 olan bir case etiketi olduðu için, yürütme bu eþleþen case etiketi altýndaki ifadeye geçer.
Program Ýki'yi yazdýrýr ve ardýndan return ifadesi yürütülerek çaðrýcýya geri döner.

Switch içinde sahip olabileceðiniz durum etiketlerine pratik bir sýnýrlama yoktur, ancak bir switch içindeki tüm durum etiketleri benzersiz olmalýdýr. Yani þunu 
yapamazsýnýz:

			switch (x)
			{
				case 54:
				case 54:  // error: zaten var olan deðer 54 !
				case '6': // error: '6', halihazýrda kullanýlan 54 tamsayý deðerine dönüþtürülüyor
			}

Koþullu ifade case etiketlerinden herhangi biriyle eþleþmiyorsa hiçbir case yürütülmez. Bunun bir örneðini birazdan göstereceðiz.


Default Etiketi
---------------
Ýkinci tür etiket ise default etiketi (genellikle default case olarak adlandýrýlýr) olup, default anahtar kelimesi kullanýlarak bildirilir.
Eðer koþullu ifade hiçbir case etiketi ile eþleþmezse ve bir default etiketi varsa, yürütme default etiketinin hemen sonrasýndaki ilk ifadede baþlar.

Ýþte koþulun default etiketi ile eþleþtiði bir örnek:

					#include <iostream>

					void printDigitName(int x)
					{
						switch (x) // x, deðeri 5'i üretmek için deðerlendirilir
						{
							case 1:
								std::cout << "Bir";
								return;
							case 2:
								std::cout << "Ýki";
								return;
							case 3:
								std::cout << "Üç";
								return;
							default: // ki hiçbir case etiketi ile eþleþmez
								std::cout << "Bilinmeyen"; // bu nedenle yürütme buradan baþlar
								return; // ve ardýndan çaðýran konuma dönülür
						}
					}

					int main()
					{
						printDigitName(5);
						std::cout << '\n';

						return 0;
					}

					Bu kodun çýktýsý: "Bilinmeyen" OLUR 
Varsayýlan etiket isteðe baðlýdýr ve bir switch ifadesinde yalnýzca bir varsayýlan etiket olabilir. Geleneksel olarak, varsayýlan durum switch bloðunun
en sonuna yerleþtirilir.

*** BEST -> Switch bloðundaki varsayýlan durumu en sona yerleþtiriniz
*/

/*
Case veya Default deðer ile eþleþmediði durum da ne olur
--------------------------------------------------------
Eðer koþullu ifadenin deðeri herhangi bir case etiketi ile eþleþmiyorsa ve varsayýlan bir durum belirlenmediyse, switch bloðundaki hiçbir case çalýþtýrýlmaz.
Ýþlem, switch bloðunun sonundan sonra devam eder.

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x, deðeri 5 üretmek için deðerlendirilir
					{
					case 1:
						std::cout << "Bir";
						return;
					case 2:
						std::cout << "Ýki";
						return;
					case 3:
						std::cout << "Üç";
						return;
					// eþleþen bir case bulunmuyor ve varsayýlan durum da yok
					}

					// bu nedenle yürütme buradan devam eder
					std::cout << "Merhaba";
				}

				int main()
				{
					printDigitName(5);
					std::cout << '\n';

					return 0;
				}

Yukarýdaki örnekte, x'in deðeri 5 olarak deðerlendirilir, ancak 5'e eþleþen bir case etiketi bulunmamakta ve varsayýlan bir durum da bulunmamaktadýr. 
Sonuç olarak, hiçbir case çalýþtýrýlmaz. Yürütme, switch bloðunun sonrasýnda devam eder ve "Merhaba" yazdýrýlýr.

Break keywordünü kullanmak. 
---------------------------

Yukarýdaki örneklerde etiketlerden sonraki ifadelerin yürütülmesini durdurmak için return ifadelerini kullandýk. Ancak bu ayný zamanda tüm fonksiyondan çýkýþý
saðlar. Break ifadesi (break anahtar kelimesi kullanýlarak tanýmlanan), derleyiciye switch içindeki ifadeleri tamamladýðýmýzý ve yürütmenin switch bloðunun 
sonundaki ifadeyle devam etmesi gerektiðini söyler. Bu, switch ifadesinden çýkmamýza, ancak tüm fonksiyondan çýkmamýza izin vermeden switch ifadesinden çýkýþ
yapmamýza olanak tanýr.
Aþaðýda, return ifadeleri yerine break kullanýlarak biraz deðiþtirilmiþ bir örnek verilmiþtir:

				#include <iostream>

				void printDigitName(int x)
				{
					switch (x) // x 3'e eþitlenir
					{
						case 1:
							std::cout << "Bir";
							break;
						case 2:
							std::cout << "Ýki";
							break;
						case 3:
							std::cout << "Üç"; // buradan yürütme baþlar
							break; // switch bloðunun sonuna atlar
						default:
							std::cout << "Bilinmiyor";
							break;
					}

					// yürütme buradan devam eder
					std::cout << " Ah-Ah-Ah!";
				}

				int main()
				{
					printDigitName(3);
					std::cout << '\n';

					return 0;
				}
Yukarýdaki program:  Üç Ah-Ah-Ah !
Her bir etiket altýndaki ifadeler, bir break ifadesi veya bir return ifadesi ile sonlanmalýdýr. Bu, switch'in en sonundaki etiket altýndaki ifadeleri de kapsar.
Eðer bir etiket altýndaki ifadeleri bir break veya return ifadesi ile sonlandýrmazsanýz ne olacaðýný bir sonraki derste keþfedeceðiz.
*/
/*
Switch düþüþü (fallthrough) ve kapsam (scoping)
-----------------------------------------------

Düþüþ (Fallthrough)

Bir switch ifadesi bir case etiketi veya isteðe baðlý bir varsayýlan etiketi ile eþleþtiðinde, yürütme eþleþen etiketi takip eden ilk ifadeden baþlar.
Yürütme ardýndan þu sonlandýrma koþullarýndan biri gerçekleþene kadar sýralý olarak devam eder:

* Switch bloðunun sonuna ulaþýlýr.
* Baþka bir kontrol akýþ ifadesi (genellikle bir break veya return), switch bloðunu veya fonksiyonu çýkartýr.
* Baþka bir þey programýn normal akýþýný kesintiye uðratýr (örneðin, iþletim sistemi programý kapatýr, evren çöker, vb.).
* Baþka bir case etiketinin varlýðý, bu sonlandýrma koþullarýndan biri deðildir - bu nedenle bir break veya return olmadan yürütme, sonraki case'lere taþacaktýr.

Ýþte bu davranýþý sergileyen bir program örneði:

					#include <iostream>

					int main()
					{
						switch (2)
						{
						case 1: // Eþleþmez
							std::cout << 1 << '\n'; // Atlandý
						case 2: // Eþleþme!
							std::cout << 2 << '\n'; // Yürütme burada baþlar
						case 3:
							std::cout << 3 << '\n'; // Bu da yürütülür
						case 4:
							std::cout << 4 << '\n'; // Bu da yürütülür
						default:
							std::cout << 5 << '\n'; // Bu da yürütülür
						}

						return 0;
					}
					Bu programýn çýktýsý 2 3 4 5 
Bu muhtemelen istediðimiz sonuç deðil! Bir etiket altýndaki bir ifadeden sonraki ifadelere akýþ gerçekleþtiðinde, buna düþüþ (fallthrough) denir.
Bir case veya default etiketi altýndaki ifadeler bir kere yürütülmeye baþladýðýnda, bunlar ardýþýk case'lere taþabilir (fallthrough). Bu durumu
engellemek için genellikle break veya return ifadeleri kullanýlýr.
Düþüþ (fallthrough) genellikle istenmeyen veya kasýtlý olarak yapýlmayan bir durum olduðu için, birçok derleyici ve kod analiz aracý düþüþü bir uyarý olarak iþaretler.

[[fallthrough]] Özniteliði
--------------------------

Kasýtlý düþüþü belirtmek için yorum eklemek, düþüþün amaçlandýðýný diðer geliþtiricilere bildirmek için yaygýn bir uygulamadýr. Bu diðer geliþtiriciler için iþe yarar,
ancak derleyici ve kod analiz araçlarý yorumlarý nasýl yorumlayacaklarýný bilmediði için uyarýlarý ortadan kaldýrmaz.
Bu durumu ele almak için, C++17 yeni bir öznitelik ekler, bu öznitelik [[fallthrough]] olarak adlandýrýlýr.
Öznitelikler, programcýnýn kod hakkýnda derleyiciye ek bilgi saðlamasýna olanak tanýyan modern bir C++ özelliðidir. Bir öznitelik belirtmek için öznitelik adý çift
köþeli parantez arasýna yerleþtirilir. Öznitelikler ifadeler deðildir - bunun yerine, baðlamsal olarak ilgili olduklarý hemen hemen her yerde kullanýlabilirler.

[[fallthrough]] özniteliði, düþüþün kasýtlý olduðunu belirtmek için bir null statement'i deðiþtirir (ve uyarýlarýn tetiklenmemesi gerekir):

					#include <iostream>

					int main()
					{
						switch (2)
						{
						case 1:
							std::cout << 1 << '\n';
							break;
						case 2:
							std::cout << 2 << '\n'; // Yürütme burada baþlar
							[[fallthrough]]; // Kasýtlý düþüþ - null ifadeyi belirtmek için noktalý virgül kullanýlmalýdýr
						case 3:
							std::cout << 3 << '\n'; // Bu da yürütülür
							break;
						}

						return 0;
					} -> Bu program 2 3 çýktýsýný verir. Ve fallthrough hakkýnda bir uyarý oluþturmaz.

Bu örnek, C++17'de tanýtýlan [[fallthrough]] özniteliðini kullanarak kasýtlý düþüþü göstermektedir. Bu öznitelik, derleyiciye düþüþün kasýtlý olduðunu belirtir ve
uyarýlarýn tetiklenmemesi gerektiðini ifade eder.

*** Best -> Kasýtlý düþüþü belirtmek için [[fallthrough]] özniteliðini (bir null ifade ile birlikte) kullanýn.





Sýralý Case labeller.
---------------------
Unutmayýn ki yürütme, eþleþen bir case etiketinden sonraki ilk ifade ile baþlar. Case etiketleri ifadeler deðildir (etiketlerdir), bu nedenle sayýlmazlar.

Yukarýdaki programdaki tüm case ifadelerinden sonraki ilk ifade return true olduðu için, herhangi bir case etiketi eþleþirse, fonksiyon true deðerini döndürecektir.

Bu nedenle, tüm bu case etiketlerini ayný ifadeler kümesini paylaþacak þekilde "yýðýp" (stack) kullanabiliriz. Bu, düþüþ (fallthrough) davranýþý olarak kabul
edilmez, bu nedenle burada yorum veya [[fallthrough]] kullanýmýna gerek yoktur.

* if else ler gibi switc-case yapýsýnda caselerin bir scop u yoktur hepsi switch in scopunda sayýlýrlar. 
* case 'a':
* case 'b': -> bu þekilde býraktýðýnda bu fallthrough sayýlmaz o yüzden uyarý vermez bu logical or gibi durumlarý kullanmak yerine de tercih edilebilecek bir yol. 
* case 'c':

Switch içinde deðiþken bildirimi ve baþlatýlmasý
------------------------------------------------
Switch içinde, case etiketlerinden önce ve sonra deðiþkenleri bildirebilir veya tanýmlayabilirsiniz (ancak baþlatamazsýnýz):

			switch (1)
			{
				int a; // uygun: case etiketlerinden önce tanýmlama izin verilir
				int b{ 5 }; // hatalý: case etiketlerinden önce baþlatma izin verilmez

				case 1:
					int y; // uygun fakat iyi bir uygulama deðil: bir case içinde tanýmlama izin verilir
					y = 4; // uygun: atama izin verilir
					break;

				case 2:
					int z{ 4 }; // hatalý: baþka case'ler varsa baþlatma izin verilmez
					y = 5; // uygun: y yukarýda bildirildiði için burada da kullanabiliriz
					break;

				case 3:
					break;
			}

Her ne kadar deðiþken y, case 1'de tanýmlanmýþ olsa da, case 2'de de kullanýlmýþtýr. Switch içindeki tüm ifadeler ayný kapsamýn bir parçasý olarak kabul edilir.
Bu nedenle, bir case içinde tanýmlanan bir deðiþken, o deðiþkenin tanýmlandýðý case hiç çalýþtýrýlmasa bile (çünkü switch onu atladý) daha sonraki bir case içinde
kullanýlabilir!

Ancak, deðiþkenlerin baþlatýlmasý, tanýmýn çalýþtýrýlmasýný gerektirir (çünkü baþlatýcýnýn deðeri o noktada belirlenmelidir). Deðiþkenlerin baþlatýlmasý, baþlatýcý
atlanabileceði için son case dýþýnda herhangi bir case'te izin verilmez (bu, deðiþkenin baþlatýlmamýþ kalmasýna neden olabilir). Baþlatma, ayrýca switch'in bunlara
ulaþma þansý olmadýðý için ilk case'ten önce de izin verilmez.

Bir case, yeni bir deðiþken tanýmlamaya ve/veya baþlatmaya ihtiyaç duyuyorsa, en iyi uygulama, bunu case ifadesinin altýnda açýk bir blok içinde yapmaktýr:

			switch (1)
			{
				case 1:
				{ // burada açýk bir blok eklemenin farkýna bakýn
					int x{ 4 }; // uygun, deðiþkenler bir case içindeki bir blok içinde baþlatýlabilir
					std::cout << x;
					break;
				}
				default:
					std::cout << "varsayýlan durum\n";
					break;
			}


Eðer bir case ifadesinde kullanýlan deðiþkenleri tanýmlýyorsanýz, bunu case içinde bir blok içinde yapýn.

Goto ifadesi
------------
Ýnceleyeceðimiz bir sonraki kontrol akýþ ifadesi, koþulsuz atlama ifadesidir. Koþulsuz atlama, yürütmenin kod içinde baþka bir noktaya atlamasýna neden olur.
"Koþulsuz" terimi, atlamanýn her zaman gerçekleþtiði anlamýna gelir (bir if ifadesi veya switch ifadesinin aksine, atlama yalnýzca bir ifadenin sonucuna baðlý
olarak koþullu olarak gerçekleþir).

C++'ta, koþulsuz atlama ifadeleri, bir goto ifadesi aracýlýðýyla uygulanýr ve atlamanýn yapýlacaðý konum, bir ifade etiketi kullanýlarak belirlenir. Aþaðýdaki örnek,
bir goto ifadesi ve ifade etiketi kullanýmýný göstermektedir:

			#include <iostream>
			#include <cmath> // sqrt() fonksiyonu için

			int main()
			{
				double x{};
			tryAgain: // bu bir ifade etiketidir
				std::cout << "Bir non-negatif sayý girin: ";
				std::cin >> x;

				if (x < 0.0)
					goto tryAgain; // bu goto ifadesidir

				std::cout << x << " sayýsýnýn karekökü " << std::sqrt(x) << '\n';
				return 0;
			}

Bu programda, kullanýcýya non-negatif bir sayý girmesi istenir. Ancak, eðer bir negatif sayý girilirse, program tryAgain etiketine geri dönmek için bir goto ifadesini
kullanýr. Kullanýcýya tekrar yeni bir sayý girmesi istenir. Bu þekilde, kullanýcý geçerli bir giriþ yapana kadar sürekli olarak kullanýcýdan giriþ isteyebiliriz.

Output bu þekilde: 
			Bir non-negatif sayý girin: -4
			Bir non-negatif sayý girin: 4
			4 sayýsýnýn karekökü 2

Ýfade etiketlerinin fonksiyon kapsamý vardýr
--------------------------------------------

Nesne kapsamýyla ilgili (7. bölümdeki) bölümde, iki tür kapsamý ele almýþtýk: yerel (blok) kapsam ve dosya (global) kapsam. Ýfade etiketleri, üçüncü bir kapsam türünü
kullanýr: fonksiyon kapsamý, yani etiket, bildirim noktasýndan önce bile fonksiyon boyunca görünür. Goto ifadesi ve ilgili ifade etiketi ayný fonksiyonda görünmelidir.

Yukarýdaki örnek, geriye doðru atlama yapan bir goto ifadesini gösterir (fonksiyon içinde önceki bir noktaya). Goto ifadeleri ayný zamanda ileri doðru da atlayabilir:

			#include <iostream>

			void printCats(bool skip)
			{
				if (skip)
					goto end; // ileri doðru atlama; ifade etiketi 'end' burada fonksiyon kapsamýna sahip olduðu için görünür

				std::cout << "kedi\n";
			end:
				; // ifade etiketleri bir ifade ile iliþkilendirilmelidir
			}

			int main()
			{
				printCats(true);  // yazdýrma ifadesini atlar ve hiçbir þey yazdýrmaz
				printCats(false); // "kedi" yazdýrýr

				return 0;
			}

Çýktýmýz : kedi


Ýleri atlama ötesinde, yukarýdaki programda deðinmeye deðer birkaç ilginç nokta bulunmaktadýr.

Ýlk olarak, ifade etiketlerinin bir ifade ile iliþkilendirilmesi gerektiðini unutmayýn (bu nedenle adlarý: bir ifadeyi etiketlerler). Fonksiyonun sonunda bir ifade
olmadýðýndan, bir ifadeye etiket eklemek için bir null ifadesi kullanmak zorunda kaldýk. Ýkinci olarak, ifade etiketlerinin fonksiyon kapsamýna sahip olmalarý
nedeniyle, henüz etiket bildirmemiþ olmamýza raðmen etiketlenmiþ ifadeye atlamayý baþarabildik. Ýleriye doðru ifade etiketlerinin önceden bildirilmesine gerek yoktur.
Üçüncüsü, yukarýdaki programýn iyi bir örnek olmadýðýný açýkça belirtmek önemlidir - yazdýrmayý atlamak için bir goto ifadesi yerine bir if ifadesi kullanmak daha 
iyiydi. Atlamanýn iki temel kýsýtlamasý vardýr: Bir fonksiyonun sýnýrlarý içinde yalnýzca atlama yapabilirsiniz (bir fonksiyondan baþka bir fonksiyona atlama 
yapamazsýnýz) ve ileri atlama yaparsanýz, atlama yapýlan konumda hala kapsamda olan herhangi bir deðiþkenin baþlatýlmasýnýn üzerine atlama yapamazsýnýz. Örneðin:

				int main()
				{
					goto skip;   // hata: bu atlama yasa dýþýdýr çünkü...
					int x { 5 }; // bu baþlatýlmýþ deðiþken, 'skip' ifade etiketinde hala kapsamdadýr
				skip:
					x += 3;      // x baþlatýlmamýþ olsaydý bu ne deðerlendirilirdi ki?
					return 0;
				}

Dikkat edin ki, bir deðiþken baþlatýmýnýn üzerine geriye doðru atlayabilirsiniz ve baþlatým gerçekleþtirildiðinde deðiþken yeniden baþlatýlacaktýr.

go to kullanýmýndan kaçýn
-------------------------
C++ (ve diðer modern yüksek seviyeli dillerde de) goto ifadesi kullanýmý kaçýnýlmalýdýr. Edsger W. Dijkstra, ünlü ama okunmasý zor olan "Go To Statement Considered
Harmful" adlý bir makalede goto ifadesinden kaçýnýlmasýný savunmuþtur. Goto'nun temel sorunu, bir programcýnýn kod içinde istediði yere rastgele atlamasýna izin 
vermesidir. Bu, bilgi akýþýný takip etmeyi son derece zorlaþtýran "spaghetti code" olarak da bilinen bir þeyi yaratýr. Spaghetti code, bir tabaðý andýran (tümüyle
karýþýk ve dolanmýþ) bir yürütme yoluna sahip olan kodu ifade eder, bu da böyle bir kodun mantýðýný takip etmeyi son derece zorlaþtýrýr.

Dijkstra, biraz mizahi bir dille, "programcýlarýn kalitesi, ürettikleri programlardaki goto ifadelerinin yoðunluðunun azalan bir fonksiyonudur" diyor.

Goto ifadesi kullanýlarak yazýlan neredeyse herhangi bir kod, C++'taki diðer yapýlarda daha açýk bir þekilde yazýlabilir, örneðin if ifadeleri ve döngüler gibi. 
Bir istisna, iç içe geçmiþ bir döngüden çýkmanýz gerektiðinde, ancak tüm fonksiyondan çýkmamanýz gerektiðinde ortaya çýkar - bu durumda, döngülerin hemen ötesine
gitmek için bir goto muhtemelen en temiz çözümdür.

*** BEST -> Goto ifadelerinden kaçýnýn (alternatifler kodun okunabilirliði açýsýndan önemli ölçüde daha kötü deðilse).
*/
/*
												8.8 LOOPLAR ( DÖNGÜLER ) VE WHÝLE ÝFADELERÝ

While Döngüleri 
---------------
while (condition)
	statement;

þeklinde tanýmlanan C++ ýn saðladýðý 3 döngüden biridir. Condition true olduðu sürece while bloðundaki ifadeler çalýþacaktýr. condition her zaman true ise while her 
zaman çalýþacaktýr buna sonsuz döngü denir. Kasýtlý olarak döngüyü loop a sokabiliriz.
Kasýtlý sonsuz döngü:  -> while(True) ... þeklindedir. 

burada döngü þartýnda kullanýlan deðiþkenlere döngü deðiþkeni denir. Fortran dan kalan bir gelenek olarak i j k harfleri kullanýlsa da bu deðiþkenleri aradýðýmýzda 
i j k harfi her hangi biri ile alaký bir geçtikleri tüm yerler gelebilri o yüzden bazý programcýlar iii jjj kkk isimlendirmelerini kullanmayý tercih ediyorlar.
Tamsayý döngü deðiþkenleri genellikle iþaretli olmalýdýr, çünkü iþaretsiz tamsayýlar beklenmeyen sorunlara yol açabilir. Aþaðýdaki kodu düþünün:
				#include <iostream>

				int main()
				{
					unsigned int count{ 10 }; // not: unsigned

					// 10'dan 0'a kadar say
					while (count >= 0)
					{
						if (count == 0)
						{
							std::cout << "blastoff!";
						}
						else
						{
							std::cout << count << ' ';
						}
						--count;
					}

					std::cout << '\n';

					return 0;
				}

Yukarýdaki örneðe bir göz atýn ve hatayý fark edebiliyor musunuz? Bu konuda daha önce görmemiþseniz pek açýk deðil.

Bu programýn aslýnda sonsuz bir döngü olduðu ortaya çýkýyor. Ýstenildiði gibi, 10 9 8 7 6 5 4 3 2 1 blastoff! yazdýrmaya baþlar, ancak sonra döngü deðiþkeni count
taþar ve 4294967295'ten (32 bit tamsayýlar varsayýlarak) geri saymaya baþlar. Neden? Çünkü döngü koþulu count >= 0 asla false olmayacak! Count 0 olduðunda, 0 >= 0
true'dir. Ardýndan --count çalýþtýrýlýr ve count 4294967295'e geri döner. Ve çünkü 4294967295 >= 0 true'dir, program devam eder. Count iþaretsiz olduðundan, negatif
olamaz ve negatif olamadýðýndan döngü sona ermez.

*** BEST -> Tamsayý döngü deðiþkenleri genellikle iþaretli bir tamsayý türü olmalýdýr
* 
* 
Ýç içe döngüler
---------------
Ayrýca, diðer döngülerin içine gömülmüþ döngüler kullanmak da mümkündür. Aþaðýdaki örnekte, iç içe geçmiþ döngü (iç döngü olarak adlandýrdýðýmýz) ve dýþ döngü
her birinin kendi sayacýna sahiptir. Ýç döngün döngü ifadesinin, dýþ döngün sayacýný da kullanmasý dikkat çekicidir!

				#include <iostream>

				int main()
				{
					// dýþ döngü 1 ile 5 arasýnda
					int outer{ 1 };
					while (outer <= 5)
					{
						// Her dýþ döngü iterasyonu için, döngü gövdesindeki kod bir kez çalýþýr

						// iç döngü 1 ile dýþ döngü arasýnda
						int inner{ 1 };
						while (inner <= outer)
						{
							std::cout << inner << ' ';
							++inner;
						}

						// her satýrýn sonunda yeni bir satýr yazdýr
						std::cout << '\n';
						++outer;
					}

					return 0;
				}

program çýktýsý 
					1
					1 2
					1 2 3
					1 2 3 4
					1 2 3 4 5


Do While ifadesi
----------------
Bir `do-while` ifadesi, bir `while` döngüsü gibi çalýþan bir döngü yapýsýdýr, ancak ifade her zaman en az bir kez çalýþýr. Ýfade yürütüldükten sonra,
do-while döngüsü koþulu kontrol eder. Eðer koþul true olarak deðerlendirilirse, yürütme yolu do-while döngüsünün baþýna atlar ve tekrar yürütülür.

Pratikte, do-while döngüleri genellikle kullanýlmaz. Koþulu döngünün altýnda bulundurmak, döngü koþulunu belirsiz kýlabilir ve bu da hatalara neden olabilir.
Birçok geliþtirici, bu nedenle do-while döngülerinden kaçýnmayý önerir. Biz daha yumuþak bir tavýr alacak ve eþit bir seçenek olduðunda while döngülerini do-while
döngülerine tercih etmeyi savunacaðýz.
Kullanýmý 
			do{
			statements
			}
			while(condition);

Bunlarý hatýrladýðýmýz için çok not almadým. Çok özel konular deðil çoðu programlama dilinde ortak olan genel ama çok efektif yapýlardýr. Anlamadýðýn veya
hatýrlamadýðýn bir þey olursa tekrar siteden kontrol etmen de fayda var. 

For Ýfadeleri 
-------------
Çok uzun zamandýr, C++ dilinde en çok kullanýlan döngü ifadesi for ifadesidir. For ifadesi (ayný zamanda for döngüsü olarak adlandýrýlýr), açýk bir döngü
deðiþkenimiz olduðunda tercih edilir çünkü bize döngü deðiþkenlerini tanýmlama, baþlatma, test etme ve deðerini deðiþtirme imkaný tanýr, bunu kolayca ve 
özlü bir þekilde yapmamýza olanak saðlar.

C++11'den itibaren iki farklý türde for döngüsü bulunmaktadýr. Bu derste klasik for ifadesini ele alacaðýz ve gelecekteki bir derste (16.7 -- Aralýk tabanlý 
for döngüleri (for-each)) diziler ve iteratorlar gibi diðer önceden gereken konularý ele aldýktan sonra daha yeni olan aralýk tabanlý for ifadesini ele alacaðýz.

Kullanýmý:
			for (init-statement; condition; end-expression)
			   statement;
for döngüsünüz daha iyi anlamak için for döngüsünü bir while döngüsüne dönüþtürelim:
					{ // buradaki bloða dikkat edin
						init-ifadesi; // döngüde kullanýlan deðiþkenleri tanýmlamak için kullanýlýr
						while (koþul)
						{
							ifade;
							son-ifade; // koþulun tekrar deðerlendirilmeden önce döngü deðiþkenini deðiþtirmek için kullanýlýr
						}
					} // döngü içinde tanýmlanan deðiþkenler burada kapsam dýþýna çýkar

for-döngüsünün deðerlendirilmesi 3 kýsýmda gerçekleþir:

Ýlk olarak, init-ifadesi yürütülür. Bu, döngü baþlatýldýðýnda yalnýzca bir kez gerçekleþir. Init-ifadesi genellikle deðiþken tanýmlama ve baþlatma için kullanýlýr.
Bu deðiþkenlere "döngü kapsamý" denir, bu aslýnda bu deðiþkenlerin taným noktasýndan döngü ifadesinin sonuna kadar var olduðu bir blok kapsamý biçimidir. While döngü
eþdeðerimizde init-ifadesinin, döngüyü içeren bir bloðun içinde olduðunu görebilirsiniz, bu nedenle init-ifadesinde tanýmlanan deðiþkenler, döngüyü içeren bloðun 
sona erdiði noktada kapsam dýþýna çýkar.

Ýkinci olarak, her döngü iterasyonu için koþul deðerlendirilir. Bu, true olarak deðerlendirilirse ifade yürütülür. Bu, false olarak deðerlendirilirse döngü sona 
erer ve yürütme, döngüden sonraki sonraki ifade ile devam eder.

Son olarak, ifade yürütüldükten sonra end-ifadesi deðerlendirilir. Genellikle bu ifade, init-ifadesinde tanýmlanan döngü deðiþkenlerini artýrmak veya azaltmak
için kullanýlýr. End-ifadesi deðerlendirildikten sonra yürütme ikinci adýma geri döner (ve koþul tekrar deðerlendirilir).

Hadi örnek bir for döngüsüne bakalým ve nasýl çalýþtýðýný tartýþalým:
						#include <iostream>

						int main()
						{
							for (int i{ 1 }; i <= 10; ++i)
								std::cout << i << ' ';

							std::cout << '\n';

							return 0;
						}


Ýlk olarak, i adýnda bir döngü deðiþkeni bildiriyoruz ve ona 1 deðerini atýyoruz.

Ýkinci olarak, i <= 10 deðerlendirilir ve çünkü i'nin deðeri 1'dir, bu true olarak deðerlendirilir. Sonuç olarak, ifade yürütülür, bu da 1 ve bir boþluk yazdýrýr.

Son olarak, ++i deðerlendirilir, bu da i'yi 2'ye artýrýr. Ardýndan döngü ikinci adýma geri döner.

Þimdi, i <= 10 tekrar deðerlendirilir. i'nin deðeri 2 olduðu için bu true olarak deðerlendirilir, bu nedenle döngü tekrar iter. Ýfade 2 ve bir boþluk yazdýrýr ve i 3'e arttýrýlýr. Döngü, sonunda i 11'e artýrýldýðýnda, i <= 10 false olarak deðerlendirilir ve döngü çýkar.

Bu nedenle, bu program þu sonucu yazdýrýr:

1 2 3 4 5 6 7 8 9 10
Örnek olmasý açýsýndan yukarýdaki for döngüsünü eþdeðer bir while döngüsüne çevirelim:
						#include <iostream>

						int main()
						{
							{ // Buradaki blok, i için blok kapsamýný saðlar
								int i{ 1 }; // Ýlk ifademiz
								while (i <= 10) // Koþulumuz
								{
									std::cout << i << ' '; // Ýfademiz
									++i; // Bitiþ ifademiz
								}
							}

							std::cout << '\n';
						}
Tabii ki, iþte çevirisi:

"Bu kadar da kötü görünmüyor, deðil mi? Dikkat edin ki, dýþtaki süslü parantezler burada gereklidir çünkü i, döngü sona erdiðinde kapsam dýþýna çýkar.

For döngüleri, yeni programcýlar için okunmasý zor olabilir -- ancak, deneyimli programcýlar bunlarý sever çünkü bunlar, döngü deðiþkenleri, döngü koþullarý
ve döngü deðiþkeni deðiþtiricileri hakkýnda gereken tüm bilgileri önde sunan çok kompakt bir döngü yapma yoludur. Bu, hatalarý azaltmaya yardýmcý olur."

Burada i yi bir arttýrdýðýmýz örnekleri gördük sürekli olarak fakat bunu sabit olarak düþünme. Örneðin i yi 2 arttýrdýðýmýz örneðe bakalým:
						#include <iostream>

						int main()
						{
							for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
								std::cout << i << ' ';

							std::cout << '\n';

							return 0;
						}
Ayný zaman da azaltabiliriz. Kendini bu konuda kýsýtlamadan syntax ve semantiðe uyduðun sürece bozmadan oynayabileceðin bir oyuncak gibi düþün :D

for-döngü koþullarýnda operator!='ýn tehlikeleri
------------------------------------------------
Bir döngü koþulu yazarken, genellikle koþulu birçok farklý þekilde ifade edebiliriz. Aþaðýdaki iki döngü de ayný þekilde çalýþýr:
						#include <iostream>

						int main()
						{
							for (int i { 0 }; i < 10; ++i) // < operatörünü kullanýr.
								 std::cout << i;

							for (int i { 0 }; i != 10; ++i) // != operatörünü kullanýr.
								 std::cout << i;

							 return 0;
						}
Hangi tercih edilmelidir? Ýlk seçenek tercih edilmelidir çünkü i'nin deðeri 10'u geçse bile döngü sona erer, oysa ikinci seçenek böyle bir durumu sonlandýrmaz.
Aþaðýdaki örnek bunu göstermektedir:

						#include <iostream>

						int main()
						{
							for (int i { 0 }; i < 10; ++i) // uses <, still terminates
							{
									std::cout << i;
									if (i == 9) ++i; // jump over value 10
							}

							for (int i { 0 }; i != 10; ++i) // uses !=, sonsuz döngü
							{
									std::cout << i;
									if (i == 9) ++i; // 10 deðerini atlar 11 != 10 sorgusu da true deðeri döneceði için devam edecektir.
							}

								return 0;
						}
*** BEST -> For-döngü koþulu içinde sayýsal karþýlaþtýrmalar yaparken != (eþit deðil) operatöründen kaçýnýlmalýdýr.

Bir Hata ile Bir Kayýp" veya "Bir Eksik Hata -> Off-by-one error 
----------------------------------------------------------------
Yeni programcýlarýn for döngüleri (ve sayacý kullanan diðer döngüler) ile en büyük sorunlarýndan biri, bir fazla veya bir eksik iþlemle istenen sonucu üreten
off-by-one hatalarýdýr. Bir örnek görelim:

			#include <iostream>

			int main()
			{
				// oops, <= yerine < operatörünü kullandýk.
				for (int i{ 1 }; i < 5; ++i)
				{
					std::cout << i << ' ';
				}

				std::cout << '\n';

				return 0;
			}
Bu programýn 1 2 3 4 5 yazdýrmasý bekleniyordu, ancak yanlýþ iliþkisel operatörü kullandýðýmýz için sadece 1 2 3 4 yazdýrýyor.

Bu hatalarýn en yaygýn nedeni yanlýþ iliþkisel operatörü kullanmaktýr, ancak bazen post-artýrma veya post-azaltma yerine pre-artýrma veya pre-azaltma 
kullanarak veya tam tersiyle de meydana gelebilirler.

Atlanan ifadeler - Omitted Expressions
--------------------------------------
"For loops" içinde herhangi bir veya tüm ifadeleri atlayan döngüler yazmak mümkündür. Örneðin, aþaðýdaki örnekte init-ifadesini ve end-ifadesini atlayarak 
sadece koþulu býrakacaðýz:
				#include <iostream>

				int main()
				{
					int i{ 0 };
					for ( ; i < 10; ) // init-statement yok veya end-expression yok
					{
						std::cout << i << ' ';
						++i;
					}

					std::cout << '\n';

					return 0;
				}

Bu for döngüsü	"0 1 2 3 4 5 6 7 8 9" sonucunu üretir. 
Döngü deðiþkeninin baþlatýlmasýný ve artýrýlmasýný for döngüsüne býrakmak yerine bunu manuel olarak gerçekleþtirdik. Bu örnekte bunu sadece akademik amaçlarla yaptýk,
ancak zaten bir döngü deðiþkeniniz varsa (çünkü baþka bir yerde tanýmlanmýþ olabilir) veya baþka bir þekilde artýrmýyorsanýz, döngü deðiþkenini bildirmemek veya 
end-ifadesinde artýrmamak istediðiniz durumlar olabilir.

Çok sýk karþýlaþýlmamakla birlikte, þu örnek sonsuz bir döngü oluþturur:

				for (;;)
					ifade;
Yukarýdaki örnek, þu ifade ile eþdeðerdir:

				while (true)
					ifade;

Bu biraz beklenmedik olabilir, çünkü genellikle atlanan bir koþul ifadesinin false olarak ele alýnmasý beklenir. Ancak, C++ standardý atlanan bir koþul ifadesinin 
for döngüsünde true olarak ele alýnmasý þeklinde açýkça (ve tutarsýz bir þekilde) tanýmlar.
Bu tür bir for döngüsü biçiminden kaçýnýlmasýný ve bunun yerine while(true) kullanýlmasýný öneririz.

Çok sayaçlý for döngüleri
-------------------------

For-döngüleri genellikle yalnýzca bir deðiþken üzerinde döner, ancak bazen for-döngüleri birden çok deðiþkenle çalýþmak zorunda kalabilir. Bu durumu desteklemek
için programcý, init-ifadesinde birden çok deðiþkeni tanýmlayabilir ve end-ifadesinde virgül operatörünü kullanarak birden çok deðiþkenin deðerini deðiþtirebilir:

						#include <iostream>

						int main()
						{
							for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
								std::cout << x << ' ' << y << '\n';

							return 0;
						}
Bu döngü, iki yeni deðiþkeni tanýmlar ve baþlatýr: x ve y. x'i 0 ile 9 arasýnda bir aralýkta döndürür ve her iterasyonun ardýndan x arttýrýlýrken y azaltýlýr.

Bu program aþaðýdaki sonucu üretir:
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0


Bu, C++ dilinde ayný ifadede birden çok deðiþken tanýmlamanýn ve virgül operatörünün kullanýlmasýnýn kabul edilebilir bir uygulama olarak düþünüldüðü neredeyse
tek yerdir.

*** BEST -> Bir for ifadesi içinde birden çok deðiþken tanýmlamak (init-ifadesinde) ve virgül operatörünü (end-ifadesinde) kullanmak kabul edilebilir bir uygulamadýr.


Ýç içe for döngüleri
--------------------

Diðer döngü türleri gibi, for döngüleri de baþka döngülerin içine yerleþtirilebilir. Aþaðýdaki örnekte, bir for döngüsünü baþka bir for döngüsünün içine
yerleþtiriyoruz:


						#include <iostream>

						int main()
						{
							for (char c{ 'a' }; c <= 'e'; ++c) // harfler üzerinde dýþ döngü
							{
								std::cout << c; // önce harfimizi yazdýr

								for (int i{ 0 }; i < 3; ++i) // tüm sayýlar üzerinde iç içe döngü
									std::cout << i;

								std::cout << '\n';
							}

							return 0;
						}

Her dýþ döngü iterasyonu için içteki döngü tamamen çalýþýr. Sonuç olarak çýktý þu þekildedir:
a012
b012
c012
d012
e012
Buradaki olay þöyle açýklanabilir: Dýþtaki döngü ilk olarak çalýþýr ve char c 'a' olarak baþlatýlýr. Ardýndan c <= 'e' deðerlendirilir, bu doðru olduðundan döngü
gövdesi çalýþtýrýlýr. c 'a' olarak ayarlandýðýndan, ilk olarak 'a' yazdýrýlýr. Ardýndan içteki döngü tamamen çalýþýr (0, 1 ve 2'yi yazdýrýr). Sonra bir satýr 
sonlandýrýcýsý (\n) yazdýrýlýr. Þimdi dýþtaki döngü gövdesi tamamlanmýþtýr, bu nedenle dýþtaki döngü tekrar en baþa döner, c 'b' olarak arttýrýlýr ve döngü koþulu 
yeniden deðerlendirilir. Döngü koþulu hala doðru olduðundan, dýþtaki döngünün bir sonraki iterasyonu baþlar. Bu, b012\n'yi yazdýrýr. Ve böyle devam eder.




																				ÖZET
																				----

`for` ifadeleri, C++ dilinde en yaygýn kullanýlan döngü türüdür. Sözdizimi genellikle yeni programcýlara biraz karmaþýk görünse de, onlarý o kadar sýk göreceksiniz ki kýsa sürede anlayacaksýnýz!

`for` ifadeleri, bir sayaç deðiþkeniniz olduðunda mükemmel bir performans gösterir. Eðer bir sayaca sahip deðilseniz, `while` ifadesi muhtemelen daha iyi bir seçenektir.

**** BEST
* -Açýk bir döngü deðiþkeni varsa `for` döngülerini tercih edin.
* - Açýk bir döngü deðiþkeni yoksa `while` döngülerini tercih edin.

*/














































































































































































































































































































































































































/*
Write a function called calculate() that takes two integers and a char representing one of the following mathematical operations: +, -, *, /, or % (remainder).
Use a switch statement to perform the appropriate mathematical operation on the integers, and return the result. If an invalid operator is passed into the function, 
the function should print an error message. For the division operator, do an integer division, and don’t worry about divide by zero.

Hint: “operator” is a keyword, variables can’t be named “operator”.
*/