# grip-strength

## Introduction

This program interfaces with the Phidgets [CZL301C](http://www.phidgets.com/products.php?product_id=3138) load cell. It graphically displays the force value (in kg) which is acting on the load cell. It is designed to operate on a Raspberry Pi.

It was originally envisioned to work as a grip strength measuring device. However, it could be re-purposed for other uses.

The load cell has an internal wheatstone bridge. Its output voltage varies linearly with the force applied on the load cell. It works when the load cell is compressed ("pushed") and when it is contracted ("pulled"). The current implementation only works during compression. The output voltage of the load cell is then amplified with the [AD623](http://docs-europe.electrocomponents.com/webdocs/10d9/0900766b810d9003.pdf) amplifier. This amplified voltage is fed to the [AD7705](http://docs-europe.electrocomponents.com/webdocs/077f/0900766b8077ff32.pdf) ADC. The output values of the ADC connects to the Raspberry Pi via SPI.

The program uses QT4 to graphically plot the data.

## Hardware setup

## Installation & Usage

### Pre-requisites & Dependencies

You must have the following libraries and frameworks installed:

1. [BCM2835](http://www.airspayce.com/mikem/bcm2835/)
2. [QT4.8](http://doc.qt.io/qt-4.8/installation.html)

The Raspberry Pi must have [SPI](https://www.raspberrypi.org/documentation/hardware/raspberrypi/spi/README.md) enabled. The most straight forward method of enabling SPI is using [raspi-config](https://www.raspberrypi.org/documentation/configuration/raspi-config.md):

```
sudo raspi-config
```

In addition, you need to have an X server such as [Xorg](https://www.x.org/wiki/) running for `startx` to display the graphical output.

### Compiling & Running

To compile the program use `qmake`, which generates a makefile, you can then run `make` to compile an output program file.

```
qmake
make
```

To run the program:

```
startx ./grip-strength
```

## Testing

As it is difficult to test both the GUi thread and the thread which reads from the ADC (as it needs to interface with physical hardware) the project currently only tests the ring buffer (which is used to store data between the two threads) implementation. The file `test.c` is used to check assumptions using assert.

To complie:

```
gcc -std=c99 -o test/buffer test/test.c  ringBuffer.c
```

To run:

```
./test/buffer
```


## Acknowledgements

The source code in this project which is used for interacting with the SPI is originally from [rpi_AD7705_test_software](https://github.com/berndporr/rpi_AD7705_test_software).
