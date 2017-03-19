# grip-strength

## Introduction

This program interfaces with the Phidgets [CZL301C](http://www.phidgets.com/products.php?product_id=3138) load cell. It graphically displays the force value (in kg) which is acting on the load cell. It is designed to operate on a Raspberry Pi.

It was originally envisioned to work as a grip strength measuring device. However, it could be re-purposed for other uses.

The load cell has an internal wheatstone bridge. Its output voltage varies linearly with the force applied on the load cell. It works when the load cell is compressed ("pushed") and when it is contracted ("pulled"). The output voltage of the load cell is then amplified with the [AD623](http://docs-europe.electrocomponents.com/webdocs/10d9/0900766b810d9003.pdf) amplifier. This amplified voltage is fed to the [AD7705](http://docs-europe.electrocomponents.com/webdocs/077f/0900766b8077ff32.pdf) ADC. The output values of the ADC connects to the Raspberry Pi via SPI.

The program uses QT5 to graphically plot the data.

## Installation & Usage

### Pre-requisites

### Downloading

### Compiling

## Testing
