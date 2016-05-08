[IMUCube](https://github.com/KitSprout/IMUCube)
========
* Author  : [Hom](http://about.me/Hom)
* Version : v1.2
* Update  : 2016/05/08

Description
========
IMUCube 是一個 IMU / LED 的開發套件，由 STM32F103T8(微控制器)、MPU6500(三軸加速度計、三軸陀螺儀)、WS2812B(One-Wire RGB888 LED) 組成，內部裝有鋰電池與開關，可以獨立供電，並預留了一個 ADC 來檢測電池電壓，另外引出 UART 與 SWD，方便針對 IMU 與 STM32 做開發、除錯，整體體積為 20 * 20 * 20 mm，上面共有 54 顆 LED，每個 LED 都是獨立可控的。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW)  方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> IMUCube v1.2 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [STM32F103T8]() 72MHz DSP FPU
* 感測器　 : [MPU6500]()
* 外接介面 : 1 x UART、1 x ADC
* PCB 尺寸 : 20 x 20 x 20 mm
* 設計軟體 [Altium Designer 16](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.4](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.4) )

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
<img src="https://lh3.googleusercontent.com/3vOuJHK602WdE9JJrPVLKMBzVQuPhuttNbBmuYhzaD3Oh5j7edaBZiDA8NgQkUKIIrSbds_ypn4HW7lDdYXShp1fmnuJQqF788T85rjjObApoat5T4xnZEvA5zz5VcwvT1ZkO4_RBKuh7i6DWqkt4-IXMP_PgfTkI0QHX7JGaHqFahu3jdpwNUsSXNn0QOg1S7dwT03Qjai2cuMHerPke0g_C1B0F9PXBiRNGWJHYadEQOIgiTmlEptl44fzR5OllEeyrzGkAGeqOcV0OLo3uq56-jnCNRQxOFu9zqHrGGui0C_Dzfm_SosNs0ZdZclSJqh6pA6vcuTnvUwRegxGhml59JmOS9E6BWQEaSJ4rtn8o_STjrOq_RUvHtMrfFJW_72XmodpEjQBd13RiHWXKF8vcGJngHaPQbwH6I92u6qMO3OVyp8-nmdj9w5dLW5FwuUYyTQ4qlm39GctWtwpjV796ADGQEeQYwHJ8F5i81WEZ10pWZes6kOapupktW1hKnJpLuMq2v27NoLtocAqrLK7HwS0k2XkTEYBP3VRWUb-XP8oUVgUQDnQWgAW0Xbhmqrbp-OSuNqMRh5capD65hVI9kNSGmU=w1034-h775-no"/>

<br />
[more photo...](https://goo.gl/photos/v7azzwZ7SMtmSPbEA)

Config
========

Schematic
========
<img src="https://lh3.googleusercontent.com/l7EID0d9houSJCsG7prcSlH9u2aFUdXL_RzBNE2tbCsE2dxx65V21bErwcftDz3rpUW-IkQuVmRdNdeWSCo25XxPe-eMxTTt8_fVl1DiuaS1CoT8rYbkvwckCGp8adHO7KyWHi671D4m0XbKpgcg9BV8K3_XuB1J7-hFZyH4cQznR9Dg5ZjJyIsAJDhv36WaTyO3Btqjn4RMFnQTlB4xb7SZyeUMAbJkifjzGKEaCupum50AZ6cHlwj_8HZn7falMc8cTK2AXT_-0hrZsK9W0jWSXifxayDf7JWN6IXvyl0sHfiyrFL5xiUEl247_hSHvLe8vpR5nDDeNqGa2XxrHRP6XZ4DWm_3axqXRT83QKUotbBCVDz6gr9mHx7AgJc2-p87Ye0oBFpn9mjOYSY1pCcOh7yVa-zP2ew9KRIhn_Thu6XFpAg4b92HG2w2qY47jYC2C1mBu5VsIE50gtO4RdLEcUl76KFRKM3N1kucOpLB4ZmgLEY5xx97sBjUz2T31uIP39hHuiw_wSUPgu3K9aGziEpnyjie1KgalJTtbtcQRkVBSMVVVeQ4IdDSNGqVP0iJV58sbF5uozaKarq-d08_1TTqQ4Y=w1034-h775-no"/>
