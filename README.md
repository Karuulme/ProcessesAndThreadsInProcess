**Merhaba değerli okur,**
   
Bu program kodlarında, bilgisayarımızda çalışmakta olan `Process` ve bunların altında çalışmakta olan `Thread` leri listeleyeceğiz.
Her şeyden önce `Process`  ve `Thread` in ne olduklarını hatırlayalım.

- Process :   Belleğe yüklenmiş ve işlemcide yürütülmekte olan bir program.
- Thread :    Tanımlamalardan bağımsız kalırsak, `Process` lerin altında çalışan küçük işlemcik olarak tanımlanabilir.
İlk olarak işe [`ProsesList.cpp` ](https://github.com/Karuulme/ProcessesAndThreadsInProcess/blob/main/ProsesList.cpp)dosyasından başlayalım, Windows fonksiyonlarını kullanabilmemiz için gerekli kütüphane eklentilerini belirttik. 

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













 









