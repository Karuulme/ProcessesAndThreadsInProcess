**Selamlar**

Sizlere benimde çok memnun kaldığım ve kullandığım Microsoft'un ürünü olan `Hyper-V` sanal bilgisayarın kurulumunu anlatacağım.
Diğer sanal programlara kıyasla daha hızlı ve daha etkili olduğu için bunu tercih ettim.

Bilgisayarımızda Hyper-V yok ise  

Not defterine 
```
pushd "%~dp0"

dir /b %SystemRoot%\servicing\Packages\*Hyper-V*.mum >hyper-v.txt

for /f %%i in ('findstr /i . hyper-v.txt 2^>nul') do dism /online /norestart /add-package:"%SystemRoot%\servicing\Packages\%%i"

del hyper-v.txt

Dism /online /enable-feature /featurename:Microsoft-Hyper-V-All /LimitAccess /ALL
```
Yazarak `.bat` uzantılı olarak kayıt edin ve çalıştırın, dosyaları indirmesi biraz uzun sürebilir. güncelleme bittikten sonra yeniden başlatın.

Var ise Windows'da `Hyper-V Yöneticisi` olarak arama yaparak bulabilirsiniz.

`Hyper-V`'yi açalım 



Sağ taraftan, Yeni -> Sanal Makina dedikten sonra
-Bilgisayarın adını
-Bellek miktarını
-Disk boyutu 
ve yükleme seçeneklerinden daha önceden indirmiş olduğunuz işletim sistemine ait iso dosyasını gösterin ve kurulumu bitirin.

Gerisi klasik format atma adımları.

**hoşçakalın**



 
