[IMUCube](https://github.com/KitSprout/IMUCube)
========
* Author  : [Hom](http://about.me/Hom)
* Version : v1.0
* Update  : 2016/03/29

Description
========
IMUCube 是一個 IMU / LED 的開發套件，由 STM32F103T8(微控制器)、MPU6500(三軸加速度計、三軸陀螺儀)、WS2812B(One-Wire RGB888 LED) 組成，內部裝有鋰電池與開關，可以獨立供電，並預留了一個 ADC 來檢測電池電壓，另外引出 UART 與 SWD，方便針對 IMU 與 STM32 做開發、除錯，整體體積為 25.4 * 25.4 * 25.4 mm，上面共有 54 顆 LED，每個 LED 都是獨立可控的。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW)  方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> IMUCube v1.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F103T8]() 72MHz DSP FPU
* 感測器　 : [MPU6500]()
* 外接介面 : 1 x UART、1 x ADC
* PCB 尺寸 : 25.4 x 25.4 x 25.4 mm
* 設計軟體 [Altium Designer 16](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.1](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.1) )

Software
========
* [IMUCube_Demo](https://github.com/KitSprout/IMUCube/tree/master/Software/IMUCube_Demo)
* [IMUCube_ModuleSTD_MPU6500-SPI](https://github.com/KitSprout/IMUCube/tree/master/Software/IMUCube_ModuleSTD_MPU6500-SPI)
* [IMUCube_ModuleSTD_WS2812B](https://github.com/KitSprout/IMUCube/tree/master/Software/IMUCube_ModuleSTD_WS2812B)
* [IMUCube_PeripheralSTD_UART](https://github.com/KitSprout/IMUCube/tree/master/Software/IMUCube_PeripheralSTD_UART)

Related Documents
========
* [Google Drive](https://goo.gl/QpaUXn)

View
========
<img src="https://lh3.googleusercontent.com/f9juaqZuWO6ST63XcYH74C-snFi3tr0tRy90cshVte5Gi1Bu_ZyT0XXz-Eh_eQ6AeakgYHEzxsISAJoRNM1bfeP3KOoY-u4B0p0AznQ7utMEOzEdu5KQg4-pqx48plUR8xau0EMvZppxmEsXliYLMEtLqWUM7FT9SmLOvGl5GbH2UqhGmMWoE4w2MWv3FRlr2m2ykXzg4R0-gM5rq5rqjDbJEWQRSHRWrSlcoIe5Trx7_91OTfGeHACOortktvsy4Oo-iWIOI73pCvynNsxUHJPWA2SKThfI2ErLTYw_fmUwXQPZlZfYsA5sK6KOSswwPA6PZ9GikqjNKTPDxciKtFK_WgMKgpMlOzN-arO6KCrIcaQmFtHGnA0pBpmIpdUs6wfEHXFMWRp8KX7QDle7AKwag4GUG2YTUWLqFUB-dBFXSWmbwKXddA73ie6Ho3MaagAXrmANRBOBHlzC9blJ8nuVj5p-moiWfed6g7_Na31aO9CSlDlFFD0Okx7_PmAW12pwv61Fqb95pUuv2L8AxObBzeDv3ISTdpp-B3kGYfTgwWhdq95GDHNlSvGChQhOYD1D=w1034-h775-no"/>

<br />
[more photo...](https://goo.gl/photos/v7azzwZ7SMtmSPbEA)

Config
========

Schematic
========
