#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "ringBuffer.h"
#include <QMutex>

class ADCreader : public QThread
{
public:
    ADCreader(ring_buffer_t &buffer, QMutex &mutex);
	void quit();
    void run();
private:
	bool running;
    ring_buffer_t& ring_buffer;
    QMutex& mutex;
};

#endif
