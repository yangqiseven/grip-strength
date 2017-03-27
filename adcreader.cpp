#include "adcreader.h"
#include <QDebug>
#include <QMutex>

ADCreader::ADCreader(ring_buffer_t &buffer, QMutex &mutex) : ring_buffer(buffer), mutex(mutex)
{
}

void ADCreader::run()
{
    uint8_t count = 1;
    uint8_t buf = 1;

	running = true;
	while (running) {
        mutex.lock();
        ring_buffer_queue(&ring_buffer, count);
        mutex.unlock();
        count += 1;
        if (count == 128) {
            count = 0;
        }
        usleep(100000);
    }
}

void ADCreader::quit()
{
	running = false;
	exit(0);
}


