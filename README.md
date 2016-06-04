[IMUCube](https://github.com/KitSprout/IMUCube)
========
* Author  : [Hom](http://about.me/Hom)
* Version : v2.0
* Update  : 2016/06/04

Description
========
IMUCube 是一個 IMU, LED 和 BLE 的開發套件，由 nRF51822(微控制器)、MPU6500(三軸加速度計、三軸陀螺儀)、WS2812B(One-Wire RGB888 LED) 組成，內部裝有鋰電池與開關，可以獨立供電，並預留了一個 ADC 來檢測電池電壓，另外引出 UART 與 SWD，方便針對 IMU 與 BLE 做開發、除錯，整體體積為 22 * 22 * 22 mm，上面共有 54 顆 LED，每個 LED 都是獨立可控的。

License
========
* 硬體(Hardware)採用 [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW)  方式授權 
  
　　<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"><img alt="創用 CC 授權條款" style="border-width:0" src="http://i.creativecommons.org/l/by-sa/3.0/tw/80x15.png" /></a>  
　　<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title"> IMUCube v2.0 </span>由<a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/KitSprout" property="cc:attributionName" rel="cc:attributionURL"> KitSprout </a>製作，以<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/deed.zh_TW"> 創用CC 姓名標示-相同方式分享 4.0 國際 授權條款 </a>釋出。  

* 軟體(Software)採用 [MIT License](http://opensource.org/licenses/MIT) 方式授權  

Hardware
========
* 控制器　 : [nRF51822](https://www.nordicsemi.com/eng/Products/Bluetooth-Low-Energy2/nRF51822)
* 感測器　 : [MPU6500]()
* 外接介面 : 1 x UART、1 x ADC、1 x KEY、1 x BUZZER、1 x VIB. MOTOR
* PCB 尺寸 : 22 x 22 x 22 mm
* 設計軟體 [Altium Designer 16](http://www.altium.com/en/products/altium-designer) ( PcbLib use AD [PcbLib v2.6](https://github.com/KitSprout/AltiumDesigner_PcbLibrary/releases/tag/v2.6) )

Software
========

Related Documents
========
* [Google Drive](https://goo.gl/QpaUXn)

View
========
<img src="https://lh3.googleusercontent.com/pZI6sJYHHOKX5Xg2YipZdv1p1tm3OHsWWRE2I9FLoyK4x-ant34PEV3ZA89H-0dPWu3LkQR-h0pgXvI00zNpjHNT6zWykLYP4uYz2D4XTuuWYVkN2hs6bcnt4DXLyhyU5Tvp6xadYC1HjF0IVoyAlEwIw_xbLHczEjdN1QrteHBu4w1alUO4WCotGMnhDjU5apUiFSpw9oEYSR8IvYmot51E-Xqqzb9yeX4i6_BX2gHYf1g4L2iGtFLTgGN-h4aTpZRuSNMjMqbGJPhrzjWF-EuzHDxmM0sr4k8HcTDB4J-pHqV4nBRjbL9d0-lnVfb-wBXjpGR2ckB06IcVq_PWPgYqOosbsG8S4Q0scmDhiealfHCu3ZNY0lPiX06Anb2_Ojo3Ef-yGdHoaiWZE3qKv6u7m9sJhgJt16SB00kvCRvlVmbD6xr2grcoZQGe0jD_JLOAOTb8HbH1YwDgPgyzSLNVrTsFljApHyIsuHtL5-GBGhSaFDvy2jVw7Hd5C9acC6DG77T-IVtt2hHre2yatdnp5DOLDNc55ssvF6mVxKv8APFjez8ENi4vI44JYuN8PoeOwiLCwVsDSWuFhLi0SfE1_JinYBZf=w1034-h775-no"/>

<br />
[more photo...](https://goo.gl/photos/v7azzwZ7SMtmSPbEA)

Config
========

Schematic
========
<img src="https://lh3.googleusercontent.com/A4N4uE2AySy7bPkcrP0glwFjeK1J1wSoaNLIzqmTMLZHWidxP4i0_QDwLCWGUdVPUZXjv-9lAwQgQrBazEaV3GPvmvBpzNyWXhnwnQ4zx0S4QBn3FH-1N5ec60uV7ILDj-ki_u8vt_fEXCAR2nKRTLykMKQzXRqCEVMmi5_WoonsvKEGxRMNs9wyPMLVpHKgi5xzHryB_xF-HZ7b3JJH3MMw3xApTUCIM8-cvy-TPwZL6DA71jvEH1NaHemIhxIzxUnxkkxb6lOcv9AKDX1R_YdRmLUfJQgoycSMphMhYzjs7xG3vIZcPbbX_FhRx8ss12J4PgYbUFmkzsmrbgUOZcfjLMEUyPWDgX1IeFe4C5bBDZ_IOEiZIoCOJ7HGNrgZCNgTEb0wodCjy-VjE7akNXF2ehSqgSfWgPk3ZcWNkv3Crjq_xO_6c_q0UElJvTEtilqezQsIf0GtJcz3Gn-Cf91SCMhdMGu6QdXa_CzJc7MizdKtSgYOaMoq4dP-BW1LvWNtGFwSGBWs4Vum-p9rtlrggBPPlRiFazifezOFgO0ZUpiQIeVItatA_UKMzslv_mDO4cADnYMI8d8aX4RtsosI8eGdlcOq=w1034-h775-no"/>
