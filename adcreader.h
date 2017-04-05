#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "ringBuffer.h"
#include <QMutex>
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

class ADCreader : public QThread
{
public:
    ADCreader(ring_buffer_t &buffer, QMutex &mutex);
	void quit();
    void run();
    static void pabort(const char *s);
    static void writeReset(int fd);
    static void writeReg(int fd, uint8_t v);
    static uint8_t readReg(int fd);
    static int readData(int fd);
private:
	bool running;
    ring_buffer_t& ring_buffer;
    QMutex& mutex;
    const char *device;
    uint8_t mode;
    uint8_t bits;
    int drdy_GPIO;
};

#endif
