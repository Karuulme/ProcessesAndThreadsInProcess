**Merhaba değerli okur,**
   
Bu program kodlarında, bilgisayarımızda çalışmakta olan `Process` ve bunların altında çalışmakta olan `Thread` leri listeleyeceğiz.
Her şeyden önce `Process`  ve `Thread` in ne olduklarını hatırlayalım.

- Process :   Belleğe yüklenmiş ve işlemcide yürütülmekte olan bir program.
- Thread :    Tanımlamalardan bağımsız kalırsak, `Process` laltında çalışan küçük işlemcik olarak tanımlanabilir.
- 
İlk olarak işe `ProsesList.cpp` dosyasından başlayalım, Windows fonksiyonlarını kullanabilmemiz için gerekli kütüphane eklentilerini belirttik. 

`Process32First` fonk. kullanabilmemiz için önce  `HANDLE`   tutamacını tanımladık.

- Handle : İşletim sisteminin o işe ilişkin bilgileri depolayacağı alan.

`Process `  bilgilerini okuyabilmemiz için `PROCESSENTRY32 ` tipinde bir class tanımladık.

Evet, şimdi  ise asıl konumuz olan windows fonk. kullanabilmemiz için daha öncesinden yapmamız gereken bir kaç işlem var. Bu işlemleri, kullanacağınız Windows fonk. ismini sonuna "msdn" ekleyerek aratırsanız öncesinde neler yapmanız gerektiğini görebilirsiniz.

Burada `Process32First`'u kullanacağız, tabi burada küçük bir açıklama getirmekte fayda var,  `Process32First` fonk. sonundaki "First" kelimesine dikkat edelim. Bu sistemde çalışan sadece ilk `Process`'i bize getirecektir. Bir sondaki `Process` bilgilerini alabilmemiz için `Process32Next`i kullanmamız gerekmektedir.






 









