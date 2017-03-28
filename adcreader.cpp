#include "adcreader.h"
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
#include <QDebug>
#include <QMutex>
#include "ad7705.h"

ADCreader::ADCreader(ring_buffer_t &buffer, QMutex &mutex) : ring_buffer(buffer), mutex(mutex)
{
}

void ADCreader::run()
{
    running = true;
    int ret = 0;
    int fd;
    int sysfs_fd;

    int no_tty = !isatty( fileno(stdout) );

    fd = open(device, O_RDWR);
    if (fd < 0)
        pabort("can't open device");

    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)

        pabort("can't set spi mode");

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        pabort("can't get spi mode");

    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't set bits per word");

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("can't get bits per word");

    fprintf(stderr, "spi mode: %d\n", mode);
    fprintf(stderr, "bits per word: %d\n", bits);

    // enable master clock for the AD
    // divisor results in roughly 4.9MHz
    // this also inits the general purpose IO
    gz_clock_ena(GZ_CLK_5MHz,5);

    // enables sysfs entry for the GPIO pin
    gpio_export(drdy_GPIO);
    // set to input
    gpio_set_dir(drdy_GPIO,0);
    // set interrupt detection to falling edge
    gpio_set_edge(drdy_GPIO,"falling");
    // get a file descriptor for the GPIO pin
    sysfs_fd = gpio_fd_open(drdy_GPIO);

    // resets the AD7705 so that it expects a write to the communication register
    printf("sending reset\n");
    writeReset(fd);

    // tell the AD7705 that the next write will be to the clock register
    writeReg(fd,0x20);
    // write 00001100 : CLOCKDIV=1,CLK=1,expects 4.9152MHz input clock
    writeReg(fd,0x0C);

    // tell the AD7705 that the next write will be the setup register
    writeReg(fd,0x10);
    // intiates a self calibration and then after that starts converting
    writeReg(fd,0x40);

	while (running) {
        // let's wait for data for max one second
        ret = gpio_poll(sysfs_fd,1000);
        if (ret<1) {
          fprintf(stderr,"Poll error %d\n",ret);
        }

        // tell the AD7705 to read the data register (16 bits)
        writeReg(fd,0x38);
        // read the data register by performing two 8 bit reads
        int value = readData(fd)-0x8000;
        mutex.lock();
        ring_buffer_queue(&ring_buffer, value);
        mutex.unlock();
    }
}

void ADCreader::quit()
{
	running = false;
	exit(0);
}
