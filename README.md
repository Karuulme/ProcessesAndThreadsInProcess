**Selamlar**
   
Bu program kodlarında, bilgisayarımızda çalışmakta olan `Process` ve bunların altında çalışmakta olan `Thread` leri listeleyeceğiz.
Her şeyden önce `Process`  ve `Thread` in ne olduklarını hatırlayalım.

- Process :   Belleğe yüklenmiş ve işlemcide yürütülmekte olan bir program.
- Thread :    Tanımlamalardan bağımsız kalırsak, `Process` lerin altında çalışan küçük işlemcik olarak tanımlanabilir.
İlk olarak işe [`ProsesList.cpp` ](https://github.com/Karuulme/ProcessesAndThreadsInProcess/blob/main/ProsesList.cpp)dosyasından başlayalım, Windows fonksiyonlarını kullanabilmemiz için gerekli kütüphane eklentilerini belirttik. 

```
	HANDLE hProcessShot;
	PROCESSENTRY32 ProcessInformation;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessInformation.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessShot, &ProcessInformation) && INVALID_HANDLE_VALUE!= hProcessShot) {
		do
		{
			printf("PROCESS NAME:  %ls  -  ", ProcessInformation.szExeFile );
			printf("PROCESS ID:  %i \n", ProcessInformation.th32ProcessID );
		}
		while (Process32Next(hProcessShot, &ProcessInformation));
	}
	else {

	}
	CloseHandle(hProcessShot);
```
`Process32First` fonk. kullanabilmemiz için önce  `HANDLE`   tutamacını tanımladık.

- Handle : İşletim sisteminin o işe ilişkin bilgileri depolayacağı alan.

`Process `  bilgilerini okuyabilmemiz için `PROCESSENTRY32 ` tipinde bir class tanımladık.

Evet, şimdi  ise asıl konumuz olan windows fonk. kullanabilmemiz için daha öncesinden yapmamız gereken bir kaç işlem var. Bu işlemleri, kullanacağınız Windows fonk. ismini sonuna "msdn" ekleyerek aratırsanız öncesinde neler yapmanız gerektiğini görebilirsiniz.

Burada `Process32First`'u kullanacağız, tabi burada küçük bir açıklama getirmekte fayda var,  `Process32First` fonk. sonundaki "First" kelimesine dikkat edelim. Bu sistemde çalışan sadece ilk `Process`'i bize getirecektir. Bir sondaki `Process` bilgilerini alabilmemiz için `Process32Next`i kullanmamız gerekmektedir.

`Process32First`i kullanabilmemiz için aldığı parametrelere bakmamız gerekiyor.
```
BOOL Process32First(
  [in]      HANDLE           hSnapshot,
  [in, out] LPPROCESSENTRY32 lppe
); 
```
Başlangıçta tanımladığımız `HADNLE` ve  `PROCESSENTRY32 ` tipinde değişkenleri almakta.  Tabi `HANDLE`'ı kullanabilmemiz için ilgili yerden bir tutamaç oluşturmamız gerekiyor. 
`[in] hSnapshot`  tanımına bakarsak `CreateToolhelp32Snapshot` kullanacağımızı görmüş oluruz.
`CreateToolhelp32Snapshot`'e bakarsak, ilgili yerin anlık görüntüsünü almakta.
```
HANDLE CreateToolhelp32Snapshot(
  [in] DWORD dwFlags,
  [in] DWORD th32ProcessID
);
```
Burada da görüldüğü gibi  2 parametre almakta.  Her parametrenin kendine ait fonk. ları var, bizim için ilgili olan 1. parametre `TH32CS_SNAPPROCESS` ve 2. parametre olarak `0` olarak belirttik.
Bunların neye göre belirlediğimizi [`CreateToolhelp32Snapshot`](https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot)'e tıklayarak kullanım detaylarını görebilirsiniz.

`Process32First`'i kullanmadan hemen öncesinde `PROCESSENTRY32` classını tanımladığımız classın içerisine `PROCESSENTRY32` classının boyutunu belirtiyoruz.
`if` de yaptığımız işlem, bir `Process` in olmaması durumunda ve bir hatayla karşılaştığımızdaki durum kontrolü.

İlk gelen `Process `bilgisini ekrana yazdırıyoruz ve `while` da ise `Process32Next`'i tanımlıyoruz, Buradaki işlem bize çağrılan en son `Process `den sonraki `Process`'i döndürür, bir `Process `bulamadığında döngüden çıkacaktır. 
işlemimiz bu kadar, son olarak `HANDLE `mizi serbes bırakmamız gerekiyor onuda `CloseHandle `ile yapıyoruz ve programı bitiriyoruz .

 Gel gelelim [`ThreaInsProsses.cpp`](https://github.com/Karuulme/ProcessesAndThreadsInProcess/blob/main/ThreaInsProsses.cpp) dosyasına. `Process` leri açıklamıştım. `Thread` lerde de aynı işlemler uygulanıyor değişen 2 şey var 1.si `Thread` lerin bilgilerine uyuşabilmemiz için `THREADENTRY32  ` sınıfını tanımlamamız gerekiyor. Hatırlarsanız `Process` lerde de `PROCESSENTRY32 `'yi kullanmıştık.
2.si `CreateToolhelp32Snapshot` da  ilk parametreye `TH32CS_SNAPTHREAD` giriyoruz.
```
	HANDLE hProcessShot;
	THREADENTRY32  Information;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	Information.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hProcessShot, &Information) && INVALID_HANDLE_VALUE != hProcessShot) {
		do
		{
                     printf("THREAD ID:  %i  -  ", Information.th32ThreadID);
                     printf("PROCESS ID:  %i  -  ", Information.th32OwnerProcessID);
		} while (Thread32Next(hProcessShot, &Information));
	}
	else {
		printf("Error");

	}
	CloseHandle(hProcessShot);
```
`Process `lerde yaptığımız gibi `Process32Next` için `Thread `lerde de `Thread32First` kullanacağız. Tüm mantık aynı. 
Bu değişiklikleri yaptıktan sonra `Thread `lerin listesini de aldık.

Bu programda List<int> kullandık. çünkü biz `Process` lerin altındaki `Thread`leri yazdırabilmemiz için `Process` ID sini  `void ThreadsInProsses()` buraya parametre olarak gönderip  `Thread` in `Process` ID si ile karşılaştırarak listeleyebilirdik her seferinde.
Fakat bunu yaptığımızda her `Process` için `Thread`lerin listesi tekrardan bilgisayardan çekilecekti. Bu bilgisayar için fazladan iş gücü demek.

[`DynamicArray`](https://github.com/Karuulme/DynamicArray)'da dinamik diziyi inceleyebilirsiniz.

`Process `leri ve `Thread `leri listeye aktarıp sonradan karşılaştırma yapmak daha az bilgisayar gücü gerektirdiği için bunu tercih ettim.







