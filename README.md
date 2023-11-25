# BK7252 A9 camera hello world

Basic "Hello World" firmware for an A9 camera on Beken BK7252 chip. This project serves as a proof of concept to verify whether my code can function as firmware on this particular device.

## Requirements

* usb uart adapter
* docker
* make
* tio or minicom
* https://github.com/tiancj/hid_download_py

Connect usb uart adapter to UART2 RX TX GND pins on device ([watch image](https://cdn.sparkfun.com/assets/2/5/c/4/5/50e1ce8bce395fb62b000000.png))

## Build and flash

Do a backup before flash!!!

```shell
uartprogram -r 0x00011000_app_$(date +%Y-%m-%d_%H%M%S)_crc.bin
```

Reconnect power if uartprogram not connected to port.

now build and flash

```shell
make
uartprogram -w src/build/hello-world_crc.bin
```

Ensure "new firmware" is working.

```shell
tio -b 115200 /dev/ttyUSB0
```

## Links
* https://github.com/daniel-dona/beken7252-opencam
* https://github.com/ghsecuritylab/tysdk_for_bk7231/tree/master/toolchain/encrypt_crc
* https://github.com/tiancj/hid_download_py