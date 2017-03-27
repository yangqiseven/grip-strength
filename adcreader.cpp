#include "adcreader.h"
//#include "ringBuffer.h"
#include <QDebug>
//#include "global.h"
#include <QMutex>

ADCreader::ADCreader(ring_buffer_t &buffer) : ring_buffer(buffer)
{
}

void ADCreader::run()
{
    uint8_t count = 1;

	running = true;
	while (running) {
        qDebug() << count;
        //mutex.lock();
        ring_buffer_queue(&ring_buffer, count);
        //mutex.unlock();
        count += 1;
        usleep(100000);
    }
}

void ADCreader::quit()
{
	running = false;
	exit(0);
}


