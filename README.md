# n76e003_platformio
 Nuvoton MCUs (N76E003) example project with PlatformIO


## Introduction
I just got many N76E003 based modules and I want to develop and upload them my own firmware!  
Afte some searching it seems everyone uses keil + uVision IDE (free is limited to 4KB flash out of 18KB),  
So I knew my next project is to add this N76E003 board to [PlatformIO](https://platformio.org/) using free [SDCC](http://sdcc.sourceforge.net)!

## Features
* I wrote uploader script- currently `upload_protocol` = `custom` but I want to make tool-nulink so it will be `nulink`.
* The uploader script can use Nuvoton CLI tool or GUI tool for uploading - the GUI works much better and faster (~4s vs ~20s).
* Fully free, no code size limit and open source thanks to SDCC + PlatformIO.

## Getting Started

### Hardware
* Buy Nu-Link ICP programmer: [this](https://www.aliexpress.com/item/32815222785.html) and [this](https://www.aliexpress.com/item/4000410409070.html) works for me.
* Buy N76E003 EVB: [this](https://www.aliexpress.com/item/1005002134285257.html) and [this](https://www.aliexpress.com/item/1005001893572711.html) works for me, also many modules use them like [this](https://www.aliexpress.com/item/33034099678.html)

### Software
* Download and install [Visual code](https://code.visualstudio.com/download)
* Install [PlatformIO](https://platformio.org/platformio-ide) extension to Visual code.
* Download and install the NuMicroICP and/or NuLinkCLI from [Nuvoton tools](https://www.nuvoton.com/tool-and-software/software-development-tool/programmer).
* Clone this [repo](https://github.com/arduino12/n76e003_platformio), open it with Visual code and upload it via PlatformIO-upload command.

## TODO
* Add more examples.
* PR to [platform-intel_mcs51](https://github.com/platformio/platform-intel_mcs51) to add N76E003 board and examples.
* Move [uploader script](https://github.com/arduino12/n76e003_platformio/blob/main/extra_script.py) into a tool-nulink package repo of PlatformIO.
* Move [N76E003 lib](https://github.com/arduino12/n76e003_platformio/tree/main/lib/N76E003) into a freamwork package of PlatformIO or into tool-SDCC.
* Implement Arduino-like API like [this](https://tenbaht.github.io/sduino/api/migration/) amazing project - because the N76E003 is VERY simular to STM8S103.

## Enjoy!
A.E.TECH

