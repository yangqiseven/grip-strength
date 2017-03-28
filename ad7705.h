#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "gz_clk.h"
#include "gpio-sysfs.h"

#ifndef AD7705_H
#define AD7705_H

static const char *device;
static uint8_t mode;
static uint8_t bits;
static int drdy_GPIO;

static void pabort(const char *s);

static void writeReset(int fd);

static void writeReg(int fd, uint8_t v);

static uint8_t readReg(int fd);

static int readData(int fd);
